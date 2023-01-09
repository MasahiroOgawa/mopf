#include "../hill_climbing.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace mo;


//----------------------------------------
//test functions

double f(const double& x){
    return -x*x;
}

double df(const double& x){
    return -2*x;
}

double f2(const double& x){
    return sin(x) * (-x*x);
}

double df2(const double& x){
    return cos(x) * (-x*x) - 2*x*sin(x);
}

//----------------------------------------

double mf(const Matrix& m){ //multidimentional function
    assert(m.cols==1);
    double x = m.at<double>(0,0);
    double y = m.at<double>(1,0);
    return -x*x-y*y;
}

Matrix dmf(const Matrix& m){
    double x = m.at<double>(0,0);
    double y = m.at<double>(1,0);
    return (Matrix(2,1) << -2*x, -2*y);
}

//----------------------------------------

int main()try{
    double h0 = 1.0;
    double eps = 1.0e-3;
    double delta = 1.0e-3;
    int max_loopcount = 1e+6;
    Hill_climbing hc(h0,eps,delta,max_loopcount);

    cout << "----------------------------------------\n"
         << "run test Hill_climbing::linear_search()\n";
    double x0 = 80.0;
    cout << "test for f1=-x^2\n";
    double x = hc.linear_search(f,df,x0);
    if(fabs(x) < eps){ //maybe this should be 2*eps or larger.
        cout << "[PASS] \n";
    }else{
        cout << "[ERROR] it returns " << x << ", but should be 0.\n";
    }

    cout << "test for f2=-x^2*sin(x)\n";
    x = hc.linear_search(f2,df2,x0);
    if(fabs(x) < eps){ //maybe this should be 2*eps or larger.
        cout << "[PASS] \n";
    }else{
        cout << "[ERROR] it returns " << x << ", but should be 0.\n";
    }

    cout << "----------------------------------------\n"
         << "run test Hill_climbing::compute()\n";
    Matrix mx0 = (Matrix(2,1) << 100, 200);
    hc.compute(mf,dmf,mx0);
    Matrix mx = hc.x();
    if(norm(mx) < eps){ //maybe this should be 2*eps or larger.
        cout << "[PASS] \n";
    }else{
        cout << "[ERROR] it returns " << x << ", but should be 0.\n";
    }


    return 0;
}catch(runtime_error& e){
    cerr << "runtime error: " << e.what() << endl;
}catch(...){
    cerr << "unknown error!\n";
}
