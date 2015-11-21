#include "../hill_climbing.h"

using namespace std;

double f(const double& x){
    return x*x;
}

int main(){
    double h0 = 1.0;
    double eps = 1.0e-5;
    double delta = 1.0e-5;
    Hill_climbing hc(h0,eps,delta);

    hc.linear_search(f);


    return 0;
}
