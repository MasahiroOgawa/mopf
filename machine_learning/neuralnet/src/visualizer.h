#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <opencv2/core.hpp>
#include <opencv2/viz.hpp>
#include "param.h"

enum class Showopt{
  none=0,
  inpos_compclscol,
  outpos_inclscol,
  outpos_inposcol,
};

class Neuralnet;

class Visualizer
{
public:
  Visualizer(){} //for Neuralnet::Neuralnet()
  Visualizer(const Vis_param& prm);
  ~Visualizer();
  void init(const Neuralnet& nn);
  void refresh(const std::list<unsigned>& topology);
  void show_input();
  void show_output(const cv::Mat& YL);
  void show_layer(const cv::Mat& Y, const int layer = 0);
  void record_WJ(const std::vector<cv::Mat>& Wshom, const double& J);
  void show_error();
  void show_network();
  const Vis_param& prm()const{return prm_;}

private:
  Vis_param prm_;
  int id_;
  cv::Mat X0_; //data vectors; X0_=(x1,...,xn). we need this because we draw input and output using X0.
  cv::Mat B_; ///<instruction signals; B_=(b1,...,bn), bi is a vector. we need this because we use this after compress at show_outsp().
  std::vector<int> c_; //class vector; c_=(c1,...,cn), ci=0,1,2,...
  cv::Mat Bcompress_; //compressed B using PCA
  int display_dim_; ///< cv::viz::WCloud only allow 3 or 4 channel matrix.
  cv::Mat colors_;
  std::vector<cv::viz::Viz3d> wins_;
  unsigned int num_data_;
  unsigned int num_layers_;
  //for show_network
  std::list<unsigned> topology_;
  std::vector<cv::Mat> Ws_hom_;
  std::string net_winname_;
  //for show error
  std::vector<double> Js_;
  cv::Mat ws_; //ws=(w(0),...,w(T)); w(t)=(Wshom_(t)[l][i][j],...); vectorized Wshom_.
  cv::Mat wJcompress_; //wJcompress_=(wJ(0),...,wJ(T)); wJ(t)=(wcompress0(t), wcompress1(t), J(t))
  std::string err2d_winname_;

  cv::Mat load_cloud(const cv::Mat& Xcompress);
  cv::PCA compress(const cv::Mat& X, cv::Mat& Xcompress);
  void comp_labels(const cv::Mat& B);
  void show_outsp(const cv::Mat& YL);
  void set_colors();
  void set_color_byclass();
  void set_color_bypos();
  void create_wins();
  void show_error2d();
  void show_error3d();
};


#endif // VISUALIZER_H
