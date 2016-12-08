#include "neuralnethandler.h"
#include <thread>
using namespace std;


NeuralnetHandler::NeuralnetHandler(const NN_param& nnprm, const Vis_param& visprm)
    : nnprm_(nnprm), visprm_(visprm)
{
    for(int i=0; i<nnprm_.num_neuralnets; ++i)
        neuralnets_.push_back(Neuralnet(nnprm_, visprm_, i)); // Neuralnet's 3rd arg i is its id.
}


NeuralnetHandler::~NeuralnetHandler(){
}


void NeuralnetHandler::learn(const cv::Mat& X0, const cv::Mat& B)try{
    vector<thread> threads;
    for(int i=0;i<nnprm_.num_neuralnets; ++i)
        threads.push_back(thread(&Neuralnet::learn, &neuralnets_[i], X0, B));

    for(auto& t : threads)
        t.join();
}catch(...){
cerr << "[ERROR] @NeuralnetHandler::learn\n";
throw;
}
