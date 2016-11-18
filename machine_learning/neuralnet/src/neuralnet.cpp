#include "neuralnet.h"
#include <iostream>
#include <set>
#include "visualizer.h"
#include <iomanip>  //for setprecision
#include "visualizer.h"
#include "util.h"
#include <opencv2/highgui.hpp>  //for waitKey()

//#define DEBUG_
//#define DEBUG2_
using namespace std;

Neuralnet::Neuralnet(const NN_param& prm, const Vis_param& visprm, const int id)
    : prm_(prm), vis_(visprm), id_{id}, topology_unchange_cnt_{0} {
  topology_ = prm.hidden_topology;
  num_layers_ = prm.hidden_topology.size() + 2;  // add input & output layer.
  num_iterate_ = 0;
  J_ = prm.th_J + 1;  // J must be larger than th_J.
  dJ_ = prm.th_dJ + 1;  // dJ must be larger than th_dJ.
  state_ = State::intermediate;
}

Neuralnet::Neuralnet(const Neuralnet& nn)
    : prm_(nn.prm_),
      vis_{nn.vis_},
      id_{nn.id_},
      topology_{nn.topology_},
      num_data_{nn.num_data_},
      num_layers_{nn.num_layers_},
      in_dim_{nn.in_dim_},
      B_{nn.B_},
      out_dim_{nn.out_dim_},
      topology_unchange_cnt_{0},
      num_corrected_{nn.num_corrected_},
      num_iterate_{nn.num_iterate_},
      J_{nn.J_},
      eps_{nn.eps_},
      eps_next_{nn.eps_next_},
      Xs_{nn.Xs_},
      Ws_hom_{nn.Ws_hom_},
      dWs_hom_{nn.dWs_hom_},
      state_{nn.state_} {
  ofs_.open(prm_.outdirname + "/id" + to_string(id_) + prm_.outfname);
  ofs_ << "number of learning iteration, cost J" << endl;
}

///**
// * @brief Neuralnet::operator =
// * first copy the argument and swap it and return.
// * @param nn
// * @return
// */
// Neuralnet& Neuralnet::operator=(Neuralnet nn){
//  swap(*this, nn);

//  return *this;
//}

/**
 * @brief Neuralnet::learn
 * @param X
 * @param b
 */
void Neuralnet::learn(const cv::Mat& X0, const cv::Mat& B) {
  time_t start = clock();

  init(X0, B);
  while (state_ != State::solved && state_ != State::overiterate) {
    update();
  }

  time_t end = clock();
  ofs_ << "learning time= " << double(end - start) / CLOCKS_PER_SEC << " [sec]\n";
}

/**
 * @brief Neuralnet::init
 * @param X0
 * @param B
 */
void Neuralnet::init(const cv::Mat& X0, const cv::Mat& B) {
  read_data(X0, B);
#ifdef DEBUG_
  ofs_ << "X0=" << Xs_[0](cv::Rect(0, 0, 5, Xs_[0].rows)) << "...\n";
  ofs_ << "B=" << B_(cv::Rect(0, 0, 5, B_.rows)) << "...\n";
#endif

  init_weight();

  if (vis_.prm().show_opt) {
    vis_.init(*this);
    vis_.show_input();
  }
}

void Neuralnet::reset() {
  ofs_ << "reset called.\n";

  // constructor part
  J_ = prm_.th_J + 1;  // J must be larger than th_J.
  dJ_ = prm_.th_dJ + 1;  // dJ must be larger than th_dJ.
  state_ = State::intermediate;

  // init part
  init_weight();
}

/**
 * @brief Neuralnet::update
 * update weight only 1 time.
 */
void Neuralnet::update() {
  cout << "id=" << id_ << ", number of learning iteration = " << num_iterate_ << '\r';
#ifdef DEBUG_
  ofs_ << "--------------------------------------------------------------------\n";
  ofs_ << "id=" << id_ << ", number of learning iteration = " << num_iterate_ << '\n';
#endif

  feedforward_backprop();
  comp_J();
  update_state();
  update_learningrate();
  try_create_annihilate();

  output_log();
  if (vis_.prm().show_opt) show_output();

  ++num_iterate_;
}

void Neuralnet::output_log() {
#ifdef DEBUG_
  //    ofs_<<setprecision(3); //setpreciison() doesn't work.
  ofs_ << "cost J = " << J_ << endl;
  if (J_ < -1.0e+4) {
    ofs_ << "last eps_=" << eps_ << endl;
    for (unsigned int l = 0; l < num_layers_ - 1; ++l) ofs_ << "Ws_hom_[" << l << "]=" << Ws_hom_[l] << endl;
    for (unsigned int l = 0; l < num_layers_; ++l) {
      ofs_ << "Xs_[" << l << "]=" << Xs_[l] << endl;
      ofs_ << "Ys_[" << l << "]=" << Ys_[l] << endl;
    }
    cv::waitKey(0);
  }
  ofs_ << "rho = " << prm_.rho << endl;
  ofs_ << "topology=";
  for (auto t : topology_) ofs_ << t << ' ';
  ofs_ << endl;
#endif
  ofs_ << num_iterate_ << ' ' << J_ << endl;

#ifdef DEBUG_
  // compute root mean squared error at the last iteration for comparison.
  if (num_iterate_ == prm_.th_maxit) {
    // save original info
    int orig_pt = prm_.problem_type;
    double orig_J = J_;
    double orig_dJ = dJ_;

    // compute rmse
    prm_.problem_type = Problem_type::regression;
    comp_J();
    ofs_ << "final root mean squared error(id=" << id_ << ", iteration=" << num_iterate_
         << ") = " << sqrt(J_) / num_data() << endl;

    // revert info
    prm_.problem_type = orig_pt;
    J_ = orig_J;
    dJ_ = orig_dJ;
  }
#endif
}

/**
 * @brief Neuralnet::show_all
 * @detail visualize network, each layer's space and J.
 */
void Neuralnet::show_output() {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::show_output()\n";
#endif
  vis_.record_WJ(Ws_hom_, J_);

  if (num_iterate_ % vis_.prm().display_step == 0 || J_ < prm_.th_J)  // show anyway at the final step.
  {
    vis_.show_network();
    for (unsigned l = 1; l < num_layers_ - 1; ++l) vis_.show_layer(Ys_[l], l);
    vis_.show_output(Ys_[num_layers_ - 1]);
    vis_.show_error();
  }
}

/**
 * @brief Neuralnet::update_state
 */
void Neuralnet::update_state() {
  if (J_ < prm_.th_J)
    state_ = State::solved;
  else if (num_iterate_ >= prm_.th_maxit)
    state_ = State::overiterate;
  else if (fabs(dJ_) < prm_.th_dJ)
    state_ = State::localminimum;
  else
    state_ = State::intermediate;
}

void Neuralnet::feedforward_backprop() {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::feedforward_backprop()\n";
#endif
  if (prm_.iterative_update) {
    // update weights for each data
    for (unsigned int n = 0; n < num_data_; ++n) {
      feed_forward(n);
      back_prop(n);
    }
  } else {
    // update weights simultaneously
    feed_forward();
    back_prop();
  }
}

void Neuralnet::try_create_annihilate() {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::try_create_annihilate()\n";
#endif
  try_create();
  try_annihilate();
  ++topology_unchange_cnt_;
}

void Neuralnet::try_create() {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::try_create()\n";
#endif
  if (state_ == State::localminimum && topology_unchange_cnt_ > prm_.th_topology_unchange) {
    create_neuron(num_layers_ - 2);  // add a neuron to previous to output layer

    if (vis_.prm().show_opt) vis_.refresh(topology_);
    state_ = State::intermediate;
    topology_unchange_cnt_ =
        -1;  // the value will be incremented afterward, so at this time -1 to let this value be 0 in case non change.
  }
}

void Neuralnet::create_neuron(unsigned layer_num) {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::create_neuron()\n";
#endif
  update_topology(layer_num, '+');
  create_input_weights(layer_num);
  create_output_weights(layer_num);
}

void Neuralnet::update_topology(unsigned layer_num, char flag) {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::update_topology()\n";
#endif
  auto it = topology_.begin();
  advance(it, layer_num);
  switch (flag) {
    case '+':
      ++(*it);
      break;
    case '-':
      --(*it);
      break;
    default:
      throw runtime_error("unkown flag");
  }
}

void Neuralnet::create_input_weights(unsigned layer_num) {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::create_input_weights()\n";
#endif
  cv::Mat w_in(dim(layer_num - 1) + 1, 1, CV_64FC1);
  cv::randu(w_in, cv::Scalar::all(-1.0), cv::Scalar::all(1.0));
  cv::hconcat(Ws_hom_[layer_num - 1], w_in, Ws_hom_[layer_num - 1]);
  cv::Mat dw_in = cv::Mat::zeros(dim(layer_num - 1) + 1, 1, CV_64FC1);
  cv::hconcat(dWs_hom_[layer_num - 1], dw_in, dWs_hom_[layer_num - 1]);
#ifdef DEBUG2_
  ofs_ << "added weight = " << w_in << endl;
  ofs_ << "added dweight = " << dw_in << endl;
#endif
}

void Neuralnet::create_output_weights(unsigned layer_num) {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::create_output_weights()\n";
#endif
  cv::Mat w_out(1, dim(layer_num + 1), CV_64FC1);
  cv::randu(w_out, cv::Scalar::all(-1.0), cv::Scalar::all(1.0));
  cv::vconcat(Ws_hom_[layer_num], w_out, Ws_hom_[layer_num]);
  cv::Mat dw_out = cv::Mat::zeros(1, dim(layer_num + 1), CV_64FC1);
  cv::vconcat(dWs_hom_[layer_num], dw_out, dWs_hom_[layer_num]);
#ifdef DEBUG2_
  ofs_ << "added weight = " << w_out << endl;
  ofs_ << "added dweight = " << dw_out << endl;
#endif
}

void Neuralnet::try_annihilate() {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::try_annihilate()\n";
#endif

  // check precondition
  if (topology_unchange_cnt_ < prm_.th_topology_unchange) return;

  unsigned layer_num = num_layers_ - 2;  // check the layer previous to output layer
  if (dim(layer_num) < 2) return;  // do not annihilate if number of neuron < 2

  // compute min of sum of output weights
  double abssum_allweights = cv::sum(abs(Ws_hom_[layer_num]))[0];

  cv::Mat abs_Wsl = abs(Ws_hom_[layer_num](
      cv::Rect(0, 1, Ws_hom_[layer_num].cols,
               Ws_hom_[layer_num].rows - 1)));  // exclude bias neuron because we don't want to annihilate the one.
  cv::Mat abssum_neuronweights;  // sum of absolute value of each neuron's output weights(exclude bias neuron). =
                                 // (neuron1's sum of absolute value of output weights; neuron2's ; ...) :
                                 // (num_neurons-1) x 1 dim
  cv::reduce(abs_Wsl, abssum_neuronweights, 1, CV_REDUCE_SUM);

  double min_val;
  int min_idx[2];
  cv::minMaxIdx(abssum_neuronweights, &min_val, nullptr, min_idx);
#ifdef DEBUG2_
  ofs_ << "abssum_allweights=" << abssum_allweights << endl;
  ofs_ << "abssum_neuronweights=" << abssum_neuronweights << endl;
  ofs_ << "min =" << min_val << " at " << min_idx[0] + 1 << endl;
#endif

  // annihilate
  if (min_val < prm_.th_annihilate * abssum_allweights) {
    annihilate_neuron(layer_num,
                      min_idx[0] + 1);  // include index of bias neuron which is excluded in calculating min_idx.
    if (vis_.prm().show_opt) vis_.refresh(topology_);
    topology_unchange_cnt_ =
        -1;  // the value will be incremented afterward, so at this time -1 to let this value be 0 in case non change.
  }
}

void Neuralnet::annihilate_neuron(unsigned layer_num, int neuron_num) {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::annihilate_neuron()\n";
#endif
  update_topology(layer_num, '-');
  annihiate_input_weights(layer_num, neuron_num);
  annihiate_output_weights(layer_num, neuron_num);
}

void Neuralnet::annihiate_input_weights(unsigned layer_num, int neuron_num) {
  Util::delete_col(neuron_num - 1, Ws_hom_[layer_num - 1]);  // note: neuron number(0,1,2,...) corresponds to Ws_hom_'s
                                                             // col number(1,2,3,...). and delete_col use 0 start index.
  Util::delete_col(neuron_num - 1, dWs_hom_[layer_num - 1]);
}

void Neuralnet::annihiate_output_weights(unsigned layer_num, int neuron_num) {
  Util::delete_row(neuron_num, Ws_hom_[layer_num]);  // because of bias neuron, last neuron number = M.rows - 1.
  Util::delete_row(neuron_num, dWs_hom_[layer_num]);
}

//----------------------
void Neuralnet::update_learningrate() {
  if(prm_.rho_descendingrate <= 0) automatic_update_learningrate();
  else prm_.rho *= prm_.rho_descendingrate;
}

//----------------------
void Neuralnet::automatic_update_learningrate(){
  dJs_.push_back(J_);
  if(dJs_.size() > 3 ){
    dJs_.pop_front();
    if(dJs_.at(0) > 0 && dJs_.at(1) > 0 && dJs_.at(2) > 0) prm_.rho *= 0.5;
    else if(dJs_.at(0) < 0 && dJs_.at(1) < 0 && dJs_.at(2) < 0) prm_.rho *= 2;
  }
}

//----------------------
/**
 * @brief Neuralnet::read_data
 * @param X0
 * @param b
 */
void Neuralnet::read_data(const cv::Mat& X0, const cv::Mat& B) {
  if (B.cols != X0.cols) throw runtime_error("number of input data must coinside with number of ouput data.");

  // create Y0,B_
  num_data_ = X0.cols;
  in_dim_ = X0.rows;
  B_ = B;
  out_dim_ = B_.rows;
  topology_.push_front(in_dim_);
  topology_.push_back(out_dim_);
  // below will be also used in reset()
  Xs_.push_back(X0);
  Ys_.push_back(X0);
  Xs_.resize(num_layers_);
  Ys_.resize(num_layers_);

  if (static_cast<Problem_type>(prm_.problem_type) == Problem_type::binary_classification && B_.rows != 1)
    throw runtime_error("dim b must be 1 in binary classification @read_data");
}

/**
 * @brief Neuralnet::init_weight
 */
void Neuralnet::init_weight() {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::init_weight()\n";
#endif
  // clear for reset()
  Ws_hom_.clear();
  dWs_hom_.clear();

  auto dk = topology_.begin();  // dk=&d(j+1); next layer's dim.
  for (auto dj = topology_.begin(); dj != prev(topology_.end()); ++dj) {
    ++dk;
    cv::Mat W_hom(*dj + 1, *dk, CV_64FC1);
    cv::randu(W_hom, cv::Scalar::all(-1.0), cv::Scalar::all(1.0));
    Ws_hom_.push_back(W_hom);
    dWs_hom_.push_back(cv::Mat::zeros(W_hom.size(), W_hom.type()));
  }
#ifdef DEBUG2_
  int i = 0;
  for (auto w : Ws_hom_) ofs_ << "Ws_hom_[" << i++ << "]=" << w << endl;
  i = 0;
  for (auto w : dWs_hom_) ofs_ << "dWs_hom_[" << i++ << "]=" << w << endl;
#endif
}

/**
 * @brief Neuralnet::dim
 * @param layer
 */
unsigned Neuralnet::dim(const unsigned layer) const {
  auto it = topology_.begin();
  advance(it, layer);
  return *it;
}

void Neuralnet::comp_J() {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::comp_J()\n";
#endif
  double prev_J = J_;

  J_ = 0;
  for (unsigned int n = 0; n < num_data_; ++n) {
    switch (prm_.problem_type) {
      case regression: {
        double d = cv::norm(Ys_[num_layers_ - 1].col(n) - B_.col(n), cv::NORM_L2);
        J_ += d * d / 2;
        break;
      }
      case binary_classification:
        J_ -= B_.at<double>(0, n) * log(Ys_[num_layers_ - 1].at<double>(0, n)) +
              (1 - B_.at<double>(0, n)) * log(1 - Ys_[num_layers_ - 1].at<double>(0, n));
        break;
      case multiclass_classification: {
        cv::Mat lnY;
        cv::log(Ys_[num_layers_ - 1].col(n), lnY);
        cv::Mat Jn = B_.col(n).t() * lnY;
        J_ -= Jn.at<double>(0, 0);
        break;
      }
      default:
        throw runtime_error("no such Problem_type option");
        break;
    }
  }

  dJ_ = prev_J - J_;
}

//----------------------------------------------------------------------------------------------------------
void Neuralnet::activation_func(const cv::Mat& X, cv::Mat& Y) {
  if (X.size() != Y.size()) throw runtime_error("output size must be the same with input.");
  for (int r = 0; r < X.rows; ++r) {
    double* Yr = Y.ptr<double>(r);
    const double* Xr = X.ptr<double>(r);
    for (int c = 0; c < X.cols; ++c) Yr[c] = tanh(Xr[c]);
  }
}

/**
 * @brief Neuralnet::outlayer_activation
 * @param X
 * @param Y
 */
void Neuralnet::outlayer_activation(const cv::Mat& X, cv::Mat& Y) {
  if (X.size() != Y.size()) throw runtime_error("output size must be the same with input.");
  switch (static_cast<Problem_type>(prm_.problem_type)) {
    case regression:
      Y = X;  // shallow copy. it's OK because we won't change X and Y.
      break;
    case binary_classification:
      if (X.rows != 1) throw runtime_error("dim x must be 1 in binary classification @outlayer_activation");
      for (int c = 0; c < X.cols; ++c) Y.at<double>(0, c) = 1 / (1 + exp(-X.at<double>(0, c)));
      break;
    case multiclass_classification: {
      if (X.rows == 1) throw runtime_error("in multiclass classification, dim x must be larger than 1.");
      for (int c = 0; c < X.cols; ++c) {
        double denominator = 0.0;
        for (int r = 0; r < X.rows; ++r) denominator += exp(X.at<double>(r, c));
        if (denominator == 0.0) throw runtime_error("sum exp(xj)==0 @outlayer_activation");
        for (int r = 0; r < X.rows; ++r) Y.at<double>(r, c) = exp(X.at<double>(r, c)) / denominator;
      }
      break;
    }
    default:
      throw runtime_error("Problem_type: no such option.");
  }
}

/**
 * @brief Neuralnet::deriv_activation_func
 * @param x
 * @param dfx
 */
void Neuralnet::deriv_activation_func(const unsigned layer, const unsigned data_num, cv::Mat& dfx) {
  const cv::Mat& yl = Ys_[layer].col(data_num);
  if (static_cast<int>(dim(layer)) != yl.rows)
    throw runtime_error("the dimension of topology[" + to_string(layer) + "]=" + to_string(dim(layer)) +
                        " and dim(Yl)=" + to_string(yl.rows) + " does not match. @Neuralnet::deriv_activation_func");
  dfx = cv::Mat::ones(dim(layer), 1, cv::DataType<double>::type) - yl.mul(yl);
}

/**
 * @brief Neuralnet::feed_forward
 * @param data_num
 */
void Neuralnet::feed_forward(unsigned data_num) {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::feed_forward()\n";
#endif
  cv::Mat y_prehom;
  cv::vconcat(1, Ys_[0].col(data_num), y_prehom);  // get y0 in homogeneous coordinate

#ifdef DEBUG2_
  ofs_ << "data num=" << data_num << ", l=0, x=" << Xs_[0].col(data_num) << ", y=" << Ys_[0].col(data_num) << endl;
#endif
  for (unsigned int l = 1; l < num_layers_; ++l) {
    cv::Mat x = Ws_hom_[l - 1].t() * y_prehom;
    cv::Mat y = cv::Mat(x.size(), x.type());
    (l != num_layers_ - 1) ? activation_func(x, y) : outlayer_activation(x, y);
#ifdef DEBUG2_
    if (l != num_layers_ - 1) { //in case not output layer.
      for (int i = 0; i < y.rows; ++i) {
        double fx = y.at<double>(i, 0);
        if (fx < -1 || fx > 1) {
          ostringstream errmsg;
          errmsg << "fx<-1 or fx>1!, datanum=" << data_num << ", layernum=" << l << ", neuronnum=" << i << ", fx=" << fx
                 << " @Neuralnet::feed_forward()";
          throw runtime_error(errmsg.str());
        }
      }
    }
    ofs_ << "data num=" << data_num << ", l=" << l << "\nx=" << x << "\ny=" << y << endl;
#endif

    // save x,y
    if (data_num == 0) {  // re-initialize Xs_[l] by only 1 column matrix.
      Xs_[l] = x;
      Ys_[l] = y;
    } else {
      cv::hconcat(Xs_[l], x, Xs_[l]);
      cv::hconcat(Ys_[l], y, Ys_[l]);
    }

    cv::vconcat(1, y, y_prehom);
  }
}

/**
 * @brief Neuralnet::back_prop
 * @param data_num
 */
void Neuralnet::back_prop(unsigned data_num) {
  for (int l = num_layers_ - 1; l > 0; --l) {  // exclude input layer; l=0
    comp_eps(l, data_num);
    update_weights(l, data_num);
  }
}

/**
 * @brief Neuralnet::comp_eps
 * @param layer
 * @param data_num
 */
void Neuralnet::comp_eps(const unsigned layer, const unsigned data_num) {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::comp_eps()\n";
#endif
#ifdef DEBUG2_
    ofs_ << "laryer=" << layer << ", data_num=" << data_num << "\n";
#endif

  if (layer < 1 || layer > num_layers_ - 1) throw runtime_error("layer must be [1,2,...,num_layer-1]");

  if (layer == num_layers_ - 1) {
    const cv::Mat& yL = Ys_[num_layers_ - 1].col(data_num);
    eps_ = yL - B_.col(data_num);
    eps_next_ = eps_;
  } else {
    cv::Mat dfxl;
    deriv_activation_func(layer, data_num, dfxl);

    const cv::Mat& Wl = Ws_hom_[layer](cv::Rect(0, 1, Ws_hom_[layer].cols, Ws_hom_[layer].rows - 1));
    eps_ = (Wl * eps_next_).mul(dfxl);
    eps_next_ = eps_;

#ifdef DEBUG2_
    ofs_ << "dfxl=" << dfxl << "\n";
    ofs_ << "Wl=" << Wl << "\n";
#endif
  }

#ifdef DEBUG2_
    ofs_ << "eps_=" << eps_ << "\n";
#endif
    if(!Util::is_valid(eps_)){
      throw runtime_error("on data_num=" + to_string(data_num) + ", layer=" + to_string(layer) +
                          ",eps_ has invalid(NaN) values. @Neuralnet::comp_eps()");
    }
}

/**
 * @brief Neuralnet::update_weights
 * @param layer
 * @param data_num
 */
void Neuralnet::update_weights(const unsigned layer, const unsigned data_num) {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::update_weights()\n";
#endif
  cv::Mat y_prehom;
  cv::vconcat(1, Ys_[layer - 1].col(data_num), y_prehom);
  dWs_hom_[layer - 1] = prm_.momentum * dWs_hom_[layer - 1] - prm_.rho * y_prehom * eps_.t();
  Ws_hom_[layer - 1] += dWs_hom_[layer - 1];

  // check there is no Nan value.
  if (!Util::is_valid(dWs_hom_[layer - 1])) {
    throw runtime_error("on data_num=" + to_string(data_num) + ", dWs_hom_[" + to_string(layer - 1) +
                        "] has invalid(NaN) values. @Neuralnet::update_weights()");
  }
#ifdef DEBUG2_
  ofs_ << "correction(l-1=" << layer - 1 << ", data num=" << data_num << ")=" << prm_.rho* y_prehom* eps_.t() << endl;
  ofs_ << "Ws_hom_[" << layer - 1 << "]=" << Ws_hom_[layer - 1] << endl;
#endif
}


/**
 * @brief Neuralnet::feed_forward
 */
void Neuralnet::feed_forward() {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::feed_forward()\n";
#endif
  cv::Mat Y_prehom;
  for (unsigned int l = 1; l < num_layers_; ++l) {
    cv::vconcat(cv::Mat::ones(1, num_data_, Xs_[l - 1].type()), Ys_[l - 1], Y_prehom);

    Xs_[l] = Ws_hom_[l - 1].t() * Y_prehom;

    Ys_[l] = cv::Mat(Xs_[l].size(), Xs_[l].type());
    (l != num_layers_ - 1) ? activation_func(Xs_[l], Ys_[l]) : outlayer_activation(Xs_[l], Ys_[l]);
  }

#ifdef DEBUG_
  //    ofs_<<setprecision(3); //setpreciison() doesn't work.
  int i = 0;
  for (auto&& xs : Xs_) ofs_ << "Xs[" << i++ << "]=" << xs(cv::Rect(0, 0, 5, xs.rows)) << "...\n";
  i = 0;
  for (auto&& ys : Ys_) ofs_ << "Ys[" << i++ << "]=" << ys(cv::Rect(0, 0, 5, ys.rows)) << "...\n";
#endif
}

/**
 * @brief Neuralnet::back_prop
 */
void Neuralnet::back_prop() {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::back_prop()\n";
#endif
  for (int l = num_layers_ - 1; l > 0; --l) {  // exclude input layer; l=0
    comp_eps(l);
    cv::Mat Y_prehom;
    cv::vconcat(cv::Mat::ones(1, num_data_, Xs_[l - 1].type()), Ys_[l - 1], Y_prehom);
    Ws_hom_[l - 1] -= prm_.rho * Y_prehom * eps_.t();
#ifdef DEBUG2_
    ofs_ << "correction(" << l - 1 << ")=" << -prm_.rho* Y_prehom* eps_.t() << endl;
    ofs_ << "Ws_hom_[" << l - 1 << "]=" << Ws_hom_[l - 1] << endl;
#endif
  }
}

/**
 * @brief Neuralnet::comp_eps
 * @param layer
 */
void Neuralnet::comp_eps(const unsigned layer) {
#ifdef DEBUG_
  ofs_ << "enter Neuralnet::comp_eps()\n";
#endif
  if (layer < 1 || layer > num_layers_ - 1) throw runtime_error("layer must be [1,2,...,num_layer-1]");

  cv::Mat dfXl;
  deriv_activation_func(layer, dfXl);

  if (layer == num_layers_ - 1) {
    const cv::Mat& YL = Ys_[num_layers_ - 1];
//    eps_ = (YL - B_).mul(dfXl); //YL-B_ ?
    eps_ = YL - B_;
  } else {
    const cv::Mat& Wl = Ws_hom_[layer](cv::Rect(0, 1, Ws_hom_[layer].cols, Ws_hom_[layer].rows - 1));
    eps_ = (Wl * eps_next_).mul(dfXl);
  }
  eps_next_ = eps_;

#ifdef DEBUG_
  ofs_ << "dfXl(" << layer << ")=" << dfXl(cv::Rect(0, 0, 5, dfXl.rows)) << "...\n";
  ofs_ << "eps_(" << layer << ")=" << eps_(cv::Rect(0, 0, 5, eps_.rows)) << "...\n";
#endif
}

/**
 * @brief Neuralnet::deriv_activation_func
 * @param layer
 * @param dfX
 */
void Neuralnet::deriv_activation_func(const unsigned layer, cv::Mat& dfX) {
  const cv::Mat& Yl = Ys_[layer];
  dfX = cv::Mat::ones(dim(layer), num_data_, cv::DataType<double>::type) - Yl.mul(Yl);
}
