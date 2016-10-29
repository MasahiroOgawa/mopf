#include "visualizer.h"
#include <set>
#include <iostream>
#include <opencv2/core/core_c.h> //for CV_PCA_DATA_AS_COL
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "neuralnet.h"
//#define DEBUG_
using namespace std;


Visualizer::Visualizer(const Vis_param& prm){
  prm_ = prm;
}


Visualizer::~Visualizer(){cv::destroyAllWindows();} //noeffect. so this can be deleted.


void Visualizer::init(const Neuralnet& nn){
  //set values
  X0_ = nn.X0();
  B_ = nn.B();
  num_data_ = nn.num_data();
  num_layers_ = nn.num_layers();
  id_ = nn.id();
  display_dim_ = 3; //cv::viz::WCloud only allow 3 or 4 channel matrix.
  topology_ = nn.topology();

  //preprocess
  comp_labels(B_);
  set_colors(); //compute based on labels and X0compress
  create_wins();
}


/**
 * @brief refresh
 * @param topology
 */
void Visualizer::refresh(const std::list<unsigned>& topology){
  topology_ = topology;
  num_layers_ = topology.size();
  ws_.release(); //currently refresh past movement of weights to fast implementation.
  Js_.clear(); //need to clear because we draw WJ, so it'S the size must be the same with ws_.
}


/**
 * @brief Visualizer::show_input
 */
void Visualizer::show_input(){
  show_layer(X0_, 0);
}


/**
 * @brief Visualizer::show
 */
void Visualizer::show_output(const cv::Mat& YL){
  switch (static_cast<Showopt>(prm_.show_opt)) {
  case Showopt::inpos_compclscol:
    comp_labels(YL);
    set_colors();
    show_layer(X0_, 0);
    break;
  case Showopt::outpos_inclscol:
  case Showopt::outpos_inposcol:
    show_outsp(YL);
    break;
  default:
    break;
  }
}


/**
 * @brief Visualizer::show_layer
 * @param Y
 */
void Visualizer::show_layer(const cv::Mat& Y, const int layer){
  wins_[layer].showWidget("coordinate", cv::viz::WCoordinateSystem());

  //compress
  cv::Mat Ycompress;
  compress(Y, Ycompress);

  //create pointcloud of Ycompress
  cv::Mat cloud_3d = load_cloud(Ycompress);
  cv::viz::WCloud cloud_widget(cloud_3d, colors_); //this only allow 3 or 4 channel matrix

  //display
  cloud_widget.setRenderingProperty(cv::viz::RenderingProperties::POINT_SIZE, 5.0);
  wins_[layer].showWidget("point clouds", cloud_widget);
  if(prm_.waitms < 0)
    wins_[layer].spin();
  else
    wins_[layer].spinOnce(prm_.waitms, true);
}


/**
 * @brief Visualizer::record_WJ
 * @param Wshom_
 * @param J
 */
void Visualizer::record_WJ(const std::vector<cv::Mat>& Wshom, const double& J){
  Ws_hom_ = Wshom;
  Js_.push_back(J);

  cv::Mat wt;
  for(auto Wl : Wshom){
    cv::Mat wtl = Wl.reshape(1,1).t(); //1 channel, (dl+1)*(d(l+1)) x 1 dim
    wt.push_back(wtl); // * x 1 dim
  }
  if(ws_.empty()) ws_ = wt;
  else{
    if(ws_.rows != wt.rows)
      throw runtime_error("ws_.rows="+to_string(ws_.rows)+" != wt.rows="+to_string(wt.rows)+" @Visualizer::record_WJ()");
    cv::hconcat(ws_, wt, ws_);
  }
}


/**
 * @brief show_error
 */
void Visualizer::show_error(){
  show_error3d();
  show_error2d();
}


/**
 * @brief Neuralnet::show_network
 */
void Visualizer::show_network(){
  //create network image
  cv::Mat net_img(prm_.win_h, prm_.win_w, CV_8UC3, cv::Scalar::all(0));

  //draw connections
#ifdef DEBUG_
  cout<<"show_network: Ws_hom_[0]="<<Ws_hom_[0]<<"\n";
#endif
  unsigned wstep = prm_.win_w/(topology_.size()+1);
  unsigned maxnum_neuron = *max_element(topology_.begin(), topology_.end()) + 1; //add bias neuron
  unsigned hstep = prm_.win_h/(maxnum_neuron + 1);
  list<unsigned>::iterator it = topology_.begin();
  unsigned num_prev_neuron = *it++ + 1; //add bias neuron
  cv::Scalar plus_weightcolor(255,0,0);
  cv::Scalar minus_weightcolor(0,48,255);
  for(unsigned l=1; l<topology_.size(); ++l){
    unsigned num_neuron = *it++ + 1;
    double max_weight;
    double min_weight;
    cv::minMaxIdx(Ws_hom_[l-1], &min_weight, &max_weight);
    double maxabs_weight = max(fabs(min_weight), fabs(max_weight));
    for(unsigned n=1; n<num_neuron; ++n){
      int cx = (l+1)*wstep;
      int cy = (n+1)*hstep;
      for(unsigned pn=0; pn<num_prev_neuron; ++pn){
        int pcx = l*wstep;
        int pcy = (pn+1)*hstep;
        double weight = Ws_hom_[l-1].at<double>(pn,n-1); //normalize each link using each layer's max weight value.
        cv::Scalar line_color = (weight > 0) ? plus_weightcolor*weight/maxabs_weight : minus_weightcolor*(-weight)/maxabs_weight;
        cv::line(net_img, cv::Point(pcx,pcy), cv::Point(cx,cy), line_color, 2);
      }
    }
    num_prev_neuron = num_neuron;
  }

  //draw neurons
  int radius = min(wstep,hstep)/3;
  it = topology_.begin();
  cv::Scalar neuron_color(255,0,64);
  for(unsigned l=0; l<topology_.size(); ++l){
    unsigned num_neuron = *it++ + 1;
    if(l!=topology_.size()-1) cv::circle(net_img, cv::Point((l+1)*wstep, hstep), radius, neuron_color*0.7,-1); //bias neuron
    for(unsigned n=1; n<num_neuron; ++n){
      int cx = (l+1)*wstep;
      int cy = (n+1)*hstep;
      cv::circle(net_img, cv::Point(cx,cy), radius, neuron_color, -1);
    }
  }

  cv::imshow(net_winname_,net_img);
  if(id_==0) //to avoid GLib-GObject-CRITICAL error.
    cv::waitKey(prm_.waitms); //cause following error: GLib-GObject-CRITICAL **: g_object_unref: assertion 'G_IS_OBJECT (object)' failed
}


/**
 * @brief Visualizer::load_3dcloud
 */
cv::Mat Visualizer::load_cloud(const cv::Mat& Xcompress){
  cv::Mat cloud_3d;
  cv::Point3d point;
  for(int i=0; i<Xcompress.cols; ++i){
    point.x = Xcompress.at<double>(0,i);
    point.y = Xcompress.at<double>(1,i);
    point.z = Xcompress.at<double>(2,i);
    cloud_3d.push_back(point);
  }
  cloud_3d = cloud_3d.t(); //cloud_3d = (p(1),p(2),...,p(num_data))
  return cloud_3d;
}




/**
 * @brief Visualizer::compress
 * @param X
 * @param Xcompress
 * @detail in case X.rows < display_dim_, add zeros and let Xcompress row vectors have more than 3dim.
 * @return
 */
cv::PCA Visualizer::compress(const cv::Mat& X, cv::Mat& Xcompress){
  if(X.empty()) throw runtime_error("input matrix is empty @Visualizer::compress()");

  cv::PCA pca(X, cv::Mat(), CV_PCA_DATA_AS_COL, display_dim_);
  if(X.rows < display_dim_) cv::vconcat(X, cv::Mat::zeros(display_dim_-X.rows, X.cols, X.type()), Xcompress);
  else pca.project(X, Xcompress);

  return pca;
}


/**
 * @brief Visualizer::comp_labels
 * get existed class index and covert it to int and fill it to c_.
 * @param B
 */
void Visualizer::comp_labels(const cv::Mat& B){
  c_.clear();
  int maxIdx[2];

  for(int n=0; n<B.cols; ++n){
    cv::minMaxIdx(B.col(n),0,0,0,maxIdx);
    int c = maxIdx[0]; //assume class number=0,1,2,...
    c_.push_back(c);
  }
}


/**
 * @brief Visualizer::show_outsp
 */
void Visualizer::show_outsp(const cv::Mat& YL){
  wins_[num_layers_-1].showWidget("coordinate", cv::viz::WCoordinateSystem());

  //compress YL
  cv::Mat YLcompress;
  cv::PCA pca = compress(YL,YLcompress);

  //project B
  if(B_.rows < display_dim_ ) cv::vconcat(B_, cv::Mat::zeros(display_dim_-B_.rows, B_.cols, B_.type()), Bcompress_);
  else pca.project(B_, Bcompress_);
#ifdef DEBUG_
  cout<<"Bcomp="<<Bcompress_(cv::Rect(0,0,10,3))<<endl;
#endif

  //create point cloud
  cv::viz::WCloudCollection clouds_widget;
  //    cv::Mat cloud_B = load_cloud(Bcompress_); //we cannot do addCloud(Bcompress), because addCloud() only accept 3 or 4 channel mat, but Bcompress have 1 channel.
  //    clouds_widget.addCloud(cloud_B);
  cv::Mat cloud_YL = load_cloud(YLcompress);
  clouds_widget.addCloud(cloud_YL, colors_);

  //draw error lines
  for(unsigned n=0; n<num_data_; ++n){
    cv::viz::WLine line(static_cast<cv::Point3d>(Bcompress_.col(n)), static_cast<cv::Point3d>(YLcompress.col(n)));
    wins_[num_layers_-1].showWidget(to_string(n),line);
  }

  //display
  clouds_widget.setRenderingProperty(cv::viz::RenderingProperties::POINT_SIZE, 5.0);
  wins_[num_layers_-1].showWidget("point clouds", clouds_widget);
  if(prm_.waitms < 0)
    wins_[num_layers_-1].spin();
  else
    wins_[num_layers_-1].spinOnce(prm_.waitms, true);
}


/**
 * @brief Visualizer::set_colors
 */
void Visualizer::set_colors(){
  colors_ = cv::Mat(1, num_data_, CV_8UC(display_dim_));

  switch (static_cast<Showopt>(prm_.show_opt)) {
  case Showopt::inpos_compclscol:
  case Showopt::outpos_inclscol:
    set_color_byclass();
    break;
  case Showopt::outpos_inposcol:
    set_color_bypos();
    break;
  default:
    throw runtime_error("no such show option @Visualizer::set_colors()");
  }
}


/**
 * @brief Visualizer::set_color_byclass
 */
void Visualizer::set_color_byclass(){
  //create a color of each class
  int max_class = *max_element(c_.begin(),c_.end());
  vector<cv::Scalar_<unsigned char> > inpos_compclscols;
  for(int i=0; i<=max_class; ++i){
    //    cv::randu(color,cv::Scalar(0),cv::Scalar(255)); //note: viz::Widget does not support alpha value, it will be neglected. this sometimes create close colors.
    cv::Scalar_<unsigned char> color(255*i/max_class, 255*(1-fabs(1-2*i/max_class)), 255*(1-i/max_class)); //this create strongly separated BGR colors according to class.
    inpos_compclscols.push_back(color);
  }

  //set color based on class
  for(unsigned int n=0; n<num_data_; ++n){
    colors_.col(n) = inpos_compclscols[c_[n]];
  }
}


/**
 * @brief Visualizer::set_color_bypos
 * color is defined by position. minimum corresponds to 0, max to 255.
 */
void Visualizer::set_color_bypos(){
  //compress X0
  cv::Mat X0compress;
  compress(X0_, X0compress);

  //compute each colors min,max
  vector<double> min(display_dim_);
  vector<double> max(display_dim_);
  for(int i=0; i<display_dim_; ++i){
    cv::minMaxIdx(X0compress.row(i), &min[i], &max[i]);
  }

  for(unsigned int n=0; n<num_data_; ++n){
    unsigned char* color = colors_.ptr<uchar>(0);
    for(int i=0; i<display_dim_; ++i){
      double x = X0compress.at<double>(i,n);
      color[n*display_dim_+(display_dim_-1-i)] = (x-min[i])*255/(max[i]-min[i]); //the reason I use (3-1-i) is OpenCV's color order is BGR, but I want to render xyz as RGB.
    }
  }
}


/**
 * @brief create_wins
 * @param num_wins
 */
void Visualizer::create_wins(){
  //layer windows
  for(unsigned i=0; i<num_layers_; ++i){
    string winname = "id=" + to_string(id_) + ",layer=" + to_string(i);
    cv::viz::Viz3d win(winname);
    win.setWindowSize(cv::Size(prm_.win_w, prm_.win_h));
    win.setWindowPosition(cv::Point(i*prm_.win_w, id_*prm_.win_h));
    wins_.push_back(win);
  }

  //3d error window
  cv::viz::Viz3d err_win("id="+to_string(id_)+"weight1-weight2-error");
  err_win.setWindowSize(cv::Size(prm_.win_w, prm_.win_h));
  err_win.setWindowPosition(cv::Point(num_layers_*prm_.win_w,id_*prm_.win_h));
  wins_.push_back(err_win);

  //2d error window
  err2d_winname_ = "id=" + to_string(id_) + "iteration-error";
  cv::namedWindow(err2d_winname_);
  cv::moveWindow(err2d_winname_, (num_layers_+1)*prm_.win_w, id_*prm_.win_h);

  //network window
  net_winname_ = "id=" + to_string(id_) + "network";
  cv::namedWindow(net_winname_);
  cv::moveWindow(net_winname_, (num_layers_+2)*prm_.win_w, id_*prm_.win_h);
}


void Visualizer::show_error2d(){
  cv::Mat err2d_img(prm_.win_h, prm_.win_w, CV_8UC3, cv::Scalar::all(0));

  //compute graph scale
  double maxJ = *max_element(Js_.begin(), Js_.end());
  double upper_graphspace = 10.0; //in J's unit.
  double factor = 255/(maxJ + upper_graphspace);

  //draw graph
  int num_iterate = Js_.size();
  if(num_iterate>1)
    for(int  n=1; n<num_iterate; ++n){
      int x = n%prm_.win_w;
      if(x==0){
        err2d_img = cv::Mat(prm_.win_h, prm_.win_w, CV_8UC3, cv::Scalar::all(0)); //clear previous graph.
      }
      cv::line(err2d_img, cv::Point(x,prm_.win_h-Js_[n-1]*factor), cv::Point(x,prm_.win_h-Js_[n]*factor), cv::Scalar(255,255,255)); //note: y coordinate is upside down, so we have to plot (x,win_h-J).
    }

  //draw value by text
  double minJ = *min_element(Js_.begin(), Js_.end()); //just for drawing
  cv::putText(err2d_img, "iter="+to_string(num_iterate), cv::Point(0,10), cv:: FONT_HERSHEY_PLAIN, 1.0, cv::Scalar::all(255));
  cv::putText(err2d_img, "curr="+to_string(Js_.back()), cv::Point(0,25), cv:: FONT_HERSHEY_PLAIN, 1.0, cv::Scalar::all(255));
  cv::putText(err2d_img, "min="+to_string(minJ)+", max="+to_string(maxJ), cv::Point(0,40), cv:: FONT_HERSHEY_PLAIN, 1.0, cv::Scalar::all(255));

  cv::imshow(err2d_winname_,err2d_img);
}


void Visualizer::show_error3d(){
  //show coordinate
  wins_[num_layers_].showWidget("coordinate", cv::viz::WCoordinateSystem()); //wins_[num_layers] is error window.

  //compress W
  --display_dim_; //w is 2D. we will display (w,J) in 3D.
  compress(ws_, wJcompress_);
  ++display_dim_;

  //concatenate J and W
  cv::Mat Js(Js_);
  Js = Js.t(); //Js_ must be 1 x T dim. Js_.reshape(1,1) doesn't work.
  if(wJcompress_.cols != Js.cols) throw runtime_error("iteration num doen't match in ws and Js!");
  wJcompress_.push_back(Js);

  //create lines
  int num_iterate = Js_.size();
  if(num_iterate>1)
    for(int  n=1; n<num_iterate; ++n){
      cv::viz::WArrow arrow(static_cast<cv::Point3d>(wJcompress_.col(n-1)), static_cast<cv::Point3d>(wJcompress_.col(n)));
      wins_[num_layers_].showWidget(to_string(n),arrow);
    }

  //display
  if(prm_.waitms < 0)
    wins_[num_layers_].spin();
  else
    wins_[num_layers_].spinOnce(prm_.waitms, true);
}
