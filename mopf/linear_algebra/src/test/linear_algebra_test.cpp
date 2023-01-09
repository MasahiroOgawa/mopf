#include "../vector.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace mo;

//----------------------------------------
void test_distance(){
    cout << "-----------------------------\n"
         << "run test distance()\n";

    vector<unsigned char> v1{1,2,3};
    vector<unsigned char> v2{2,3,4};

    double eps = 1.0e-3;
    double d = distance(v1, v2) - sqrt(3);
    if(d < eps){
        cout << "[PASS] \n";
    }else{
        cout << "[ERROR] it returns " << d << ", but should be 0.\n";
    }
}


//----------------------------------------
void test_norm(){
    cout << "-----------------------------\n"
         << "run test norm()\n";

    vector<double> v1{1,2};
    double nrm = norm(v1);

    double eps = 1.0e-3;
    double nrm_direct = sqrt(1*1 + 2*2);
    if(nrm - nrm_direct < eps){
        cout << "[PASS] \n";
    }else{
        cout << "[ERROR] \n";
    }

}


//----------------------------------------
void test_cosnorm(){
    cout << "-----------------------------\n"
         << "run test cosnorm()\n";
    double eps = 1.0e-3;

    cout << "test1: \n";
    vector<double> v1{0,1};
    double nrm = cosnorm(v1,v1);
    double nrm_direct = 0;
    if(nrm - nrm_direct < eps){
        cout << "v1=" << v1 << ", cosnorm(v1,v1)=" << nrm << "\n"
             << "[PASS] \n";
    }else{
        cout << "[ERROR] \n";
    }

    cout << "test2: \n";
    vector<double> v2{100,0};
    nrm = cosnorm(v1,v2);
    nrm_direct = 1.0;
    if(nrm - nrm_direct < eps){
        cout << "v1=" << v1 << ", v2=" << v2 << ", cosnorm(v1,v2)=" << nrm << "\n"
             << "[PASS] \n";
    }else{
        cout << "[ERROR] \n";
    }

}

//----------------------------------------

int main()try{
    cout << "============================\n"
         << "start linear_algebra_test.\n";

    test_distance();
    test_norm();
    test_cosnorm();

    return 0;
}catch(runtime_error& e){
    cerr << "runtime error: " << e.what() << endl;
}catch(...){
cerr << "unknown error!\n";
}
