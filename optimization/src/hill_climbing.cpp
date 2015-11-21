#include "hill_climbing.h"
#include <iostream>
using namespace std;

Hill_climbing::Hill_climbing(const double& h0, const double& eps, const double& delta)
    : h0_{h0}, eps_{eps}, delta_{delta}
{

}


void Hill_climbing::compute(){

}

void Hill_climbing::linear_search(double (*f)(const double&)){
    cout << "f(0)=" << f(0) << endl;
    cout << "f(2)=" << f(2) << endl;
}
