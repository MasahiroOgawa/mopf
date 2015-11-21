#include "../hill_climbing.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace mo;


double f(const double& x){
    return -x*x;
}

double df(const double& x){
    return -2*x;
}


int main(){
    double h0 = 1.0;
    double eps = 1.0e-3;
    double delta = 1.0e-3;
    Hill_climbing hc(h0,eps,delta);

    cout << "----------------------------------------\n"
         << "run test Hill_climbing::linear_search()\n";
    double x0 = 8.0;
    double x = hc.linear_search(f,df,x0);
    if(fabs(x) < eps){
        cout << "[PASS] \n";
    }else{
        cout << "[ERROR] it returns " << x << ", but should be 0.\n";
    }


    return 0;
}
