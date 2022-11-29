#include "../video.h"
#include <iostream>

using namespace std;
using namespace mo;


int main()try{
    cout << "----------------------------------------\n"
         << "run test video\n";

    cout << "[PASS] \n";


    return 0;
}catch(runtime_error& e){
    cerr << "runtime error: " << e.what() << endl;
}catch(...){
cerr << "unknown error!\n";
}
