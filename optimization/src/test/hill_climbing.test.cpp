#include "../hill_climbing.h"

using namespace std;
using namespace mo;


double f(const double& x){
    return x*x;
}

double df(const double& x){
    return 2*x;
}


int main(){
    double h0 = 1.0;
    double eps = 1.0e-5;
    double delta = 1.0e-5;
    Hill_climbing hc(h0,eps,delta);

    double x0 = 8.0;
    double x = hc.linear_search(f,df,x0);


    return 0;
}
