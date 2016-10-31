#include "../knearest_neighbor.h"

using namespace std;
using namespace mo;

int main()try{
    cout << "----------------\n"
            "start knearest_neighbor test\n";

    KNearestNeighbor knn;
//    knn.classify();

    return 0;
}catch(runtime_error& e){
  cerr << "runtime error: " << e.what() << endl;
}catch(logic_error& e){
  cerr << "logic error: " << e.what() << endl;
}catch(...){
cerr << "unknown error occured.\n";
}
