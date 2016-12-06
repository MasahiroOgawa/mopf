#include "neuralnethandler.h"
#include <thread>
using namespace std;


NeuralnetHandler::NeuralnetHandler(const NN_param& nnprm, const Vis_param& visprm)
    : neuralnet_(nnprm,visprm) , nnprm_(nnprm), visprm_(visprm)
{


}


NeuralnetHandler::~NeuralnetHandler(){
}


void NeuralnetHandler::learn(const cv::Mat& X0, const cv::Mat& B){
    thread t(&Neuralnet::learn, &neuralnet_, X0,B);
    t.join();

//    vector<thread> v;
//    for(int i=0;i<nnprm_.num_neuralnets; ++i)
//        v.push_back(thread(&Neuralnet::learn, &neuralnet_, X0,B));

//    for_each(v.begin(), v.end(), [](thread& t){t.join();} );
}
