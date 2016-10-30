#include "vector.h"
using namespace std;

namespace mo {

double distance(const std::vector<unsigned char>& v1, const std::vector<unsigned char>& v2){
    if(v1.size() != v2.size()){
        stringstream errmsg;
        errmsg << "v1.size:" << v1.size() << " must be equal with v2.size:" << v2.size()
               << " @distance()";
        throw runtime_error(errmsg.str());
    }

    double dist{0};
    for(size_t i=0; i<v1.size(); ++i){
        dist += (v1[i] - v2[i]) * (v1[i] - v2[i]);
    }

    return sqrt(dist);
}

} // namespace mo

