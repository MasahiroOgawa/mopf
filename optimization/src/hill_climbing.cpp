#include "hill_climbing.h"
#include <iostream>
#include <cmath> //for fabs()
#include "../../analysis/src/analysis.h" //for sgn()
using namespace std;

namespace mo {

Hill_climbing::Hill_climbing(const double& h0, const double& eps, const double& delta, const int& max_loopcount)
    : h0_{h0}, eps_{eps}, delta_{delta}, max_loopcount_{max_loopcount}
{
}


void Hill_climbing::compute(double (*f)(const Matrix&), Matrix (*df)(const Matrix&), const Matrix& x0){
    //initialize
    int loop_count{0};
    x_ = x0;
    Matrix dx = (delta_ + 1.0)*Matrix::ones(x_.size()); //any value is OK if it is larger than delta_.

    while(norm(dx) > delta_){
        auto F = [f,df,this](const double& t){return f(x_ + t*df(x_));};
        auto dF = [df,this](const double& t){cv::Mat_<double> Dfdf(df(x_ + t*df(x_)).t() * df(x_)); return Dfdf.at<double>(0,0);};

        double t = linear_search(F,dF,0.0);
        dx = t * df(x_);
        x_ += dx;
        check_loopcount(++loop_count);
    }

}


void Hill_climbing::check_loopcount(const int loop_count){
    if(loop_count > max_loopcount_){
        std::string errmsg = "@Hill_climbing::check_loopcount(): loop count=" + std::to_string(loop_count) + " is over max_loopcount=" + std::to_string(max_loopcount_);
        throw std::overflow_error(errmsg);
    }
}

} //namespace mo
