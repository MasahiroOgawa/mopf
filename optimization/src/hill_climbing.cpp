#include "hill_climbing.h"
#include <iostream>
#include <cmath> //for fabs()
using namespace std;

Hill_climbing::Hill_climbing(const double& h0, const double& eps, const double& delta)
    : h0_{h0}, eps_{eps}, delta_{delta}
{

}


void Hill_climbing::compute(){

}

double Hill_climbing::linear_search(double (*f)(const double&), double(*df)(const double&), const double& x0){
    double h = h0_;
    double x = x0;

    while(fabs(df(x)) > eps_){
//        h =
    }

    return x;
}
