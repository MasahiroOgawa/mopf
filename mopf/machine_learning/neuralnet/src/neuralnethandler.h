#ifndef NEURALNETHANDLER_H
#define NEURALNETHANDLER_H
#include <vector>
#include "neuralnet.h"
#include "param.h"

class NeuralnetHandler
{
public:
  NeuralnetHandler(const NN_param& nnprm, const Vis_param& visprm);
  ~NeuralnetHandler();
  void learn(const cv::Mat& X0, const cv::Mat& B);

private:
  std::vector<Neuralnet> neuralnets_;
  NN_param nnprm_;
  Vis_param visprm_;
};

#endif // NEURALNETHANDLER_H
