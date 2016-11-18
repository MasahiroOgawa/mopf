#ifndef Neuralnet_H
#define Neuralnet_H
#include <opencv2/core.hpp>
#include <list>
#include "param.h"
#include <fstream>
#include <memory>
#include "visualizer.h"
#include <deque>

enum class State{
  intermediate,
  localminimum,
  solved,
  overiterate,
};

enum Problem_type{
  regression=1,
  binary_classification,
  multiclass_classification,
};


class Neuralnet
{
public:
//  Neuralnet(){} //for Neuralnet(Neuralnet&&)
  Neuralnet(const NN_param& prm, const Vis_param& visprm, const int id=0);
  Neuralnet(const Neuralnet& nn); /// we need this because we use vector::push_back().
//  Neuralnet(Neuralnet&& other) : Neuralnet() {std::swap(*this, other);}
//  Neuralnet& operator=(Neuralnet nn);
  void learn(const cv::Mat& X0, const cv::Mat& B); /// init & while(update)
  void init(const cv::Mat& X0, const cv::Mat& B);
  void reset();
  void update();

  //getter
  const cv::Mat& B() const {return B_;}
  const cv::Mat& X0() const {return Xs_[0];}
  const unsigned& num_data() const {return num_data_;}
  const unsigned& num_layers() const {return num_layers_;}
  const double& J() const {return J_;}
  const double& dJ() const {return dJ_;}
  const State& state() const {return state_;}
  const int& id() const {return id_;}
  const std::list<unsigned> topology()const{return topology_;}
  const unsigned& num_iterate()const{return num_iterate_;}
  const NN_param& prm()const{return prm_;}

private:
  void read_data(const cv::Mat& X0, const cv::Mat& B);
  void init_weight();
  unsigned dim(const unsigned layer)const;
  void comp_J();

  ///
  /// \brief activation_func
  /// \param X
  /// \param Y
  /// I use tanh() as activation function in this program.
  /// This function is common with iterative and matrix version.
  void activation_func(const cv::Mat& X, cv::Mat& Y);

  void outlayer_activation(const cv::Mat& X, cv::Mat& Y);
  void output_log();
  void show_output();
  void update_state();
  void feedforward_backprop();
  void try_create_annihilate();
  void try_create();
  void create_neuron(unsigned layer_num);
  void update_topology(unsigned layer_num, char flag); //flag='+' or '-'
  void create_input_weights(unsigned layer_num);
  void create_output_weights(unsigned layer_num);
  void try_annihilate();
  void annihilate_neuron(unsigned layer_num, int neuron_num);
  void annihiate_input_weights(unsigned layer_num, int neuron_num);
  void annihiate_output_weights(unsigned layer_num, int neuron_num);
  void update_learningrate();
  void automatic_update_learningrate();
  //for iterative version
  void deriv_activation_func(const unsigned layer, const unsigned data_num, cv::Mat& dfx);
  void feed_forward(unsigned data_num);
  void back_prop(unsigned data_num);
  void comp_eps(const unsigned layer, const unsigned data_num);
  void update_weights(const unsigned layer, const unsigned data_num);
  //for matrix version
  void feed_forward();
  void back_prop();
  void comp_eps(const unsigned layer);
  void deriv_activation_func(const unsigned layer, cv::Mat& dfX);

  //inputs
  NN_param prm_;
  Visualizer vis_;
  int id_; //for treating multiple NN
  std::list<unsigned> topology_; //to use push_front(), I use list.
  unsigned num_data_;
  unsigned num_layers_;
  unsigned in_dim_;
  cv::Mat B_;
  unsigned out_dim_;
  int topology_unchange_cnt_;

  //outputs
  unsigned num_corrected_;
  unsigned num_iterate_;
  double J_;
  double dJ_;
  std::deque<double> dJs_; //for automatic update learningrate.
  cv::Mat eps_;
  cv::Mat eps_next_; //next layer's epsilon
  std::vector<cv::Mat> Xs_; //Xs_=(X0,...,XL); each layer's X.
  std::vector<cv::Mat> Ys_; //Ys_=(Y0,Y1,...,YL); each layer's Y.
  std::vector<cv::Mat> Ws_hom_; //each layer's weight. element's type = CV_64FC1.
  std::vector<cv::Mat> dWs_hom_; //each layer's delta weight = W(k+1)-W(k); incremental quantity.
  State state_;
  std::ofstream ofs_;
};

#endif // Neuralnet_H
