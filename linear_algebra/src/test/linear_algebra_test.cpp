#include "../vector.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace mo;


//----------------------------------------

//----------------------------------------

int main()try{
    double eps = 1.0e-3;

    cout << "----------------------------------------\n"
         << "run test distance()\n";
    vector<unsigned char> v1{1,2,3};
    vector<unsigned char> v2{2,3,4};

    double d = distance(v1, v2) - sqrt(3);
    if(d < eps){
        cout << "[PASS] \n";
    }else{
        cout << "[ERROR] it returns " << d << ", but should be 0.\n";
    }

    return 0;
}catch(runtime_error& e){
    cerr << "runtime error: " << e.what() << endl;
}catch(...){
cerr << "unknown error!\n";
}
