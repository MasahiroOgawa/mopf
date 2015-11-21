#include "hill_climbing.h"
#include <iostream>
#include <cmath> //for fabs()
#include "../../analysis/src/analysis.h" //for sgn()
using namespace std;

namespace mo {

Hill_climbing::Hill_climbing(const double& h0, const double& eps, const double& delta)
    : h0_{h0}, eps_{eps}, delta_{delta}
{

}


void Hill_climbing::compute(){

}


double Hill_climbing::linear_search(double (*f)(const double&), double(*df)(const double&), const double& x0){
    double h = h0_;
    double x = x0;

    //search until |df(x)| ~ 0
    while(fabs(df(x)) > eps_){
        //init x_next
        h = sgn(df(x)) * fabs(h);
        double x_next = x + h;

        if(f(x) < f(x_next)){ //in case f(x_next) does not yet reached the neighborhood of maximal
            while(f(x) < f(x_next)){ //loop until over maximal
                h *= 2.0;
                x = x_next;
                x_next = x + h;
            }
            h /= 2.0;
        }else{ //in case f(x_next) over the neighborhood of maximal
            while(f(x) >= f(x_next)){ //loop until it finds
                h /= 2.0;
                x_next -= h;
            }
            x = x_next;
            h *= 2.0;
        }
    }

    return x;
}

} //namespace mo
