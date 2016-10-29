#include "neuralnethandler.h"
using namespace std;


NeuralnetHandler::NeuralnetHandler(const NN_param& nnprm, const Vis_param& visprm)
  : nnprm_(nnprm), visprm_(visprm)
{
  for(int i=0; i<nnprm.num_neuralnets; ++i){
    Neuralnet nn(nnprm, visprm, i);
    neuralnets_.push_back(nn);
  }
}


NeuralnetHandler::~NeuralnetHandler(){
}


void NeuralnetHandler::learn(const cv::Mat& X0, const cv::Mat& B){
  for(auto& nn : neuralnets_){
    nn.init(X0,B);
  }

  bool intermediate = true;
  while(intermediate){
    for(auto it=neuralnets_.begin(); it!=neuralnets_.end(); ++it){
      it->update();

      if(it->state()==State::solved || it->state()==State::overiterate){
        intermediate = false;
      }else if(it->state()==State::localminimum){
        if(visprm_.show_opt)
        it->reset();
      }
    }
  }
}
