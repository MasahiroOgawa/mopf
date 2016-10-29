#include "knearestneighbor.h"

using namespace std;

namespace mo {
KNearestNeighbor::KNearestNeighbor()
{

}

//------------------
void KNearestNeighbor::init(const DataType dt, const std::string& datadir, const bool show_result){
    show_result_ = show_result;
    pdh_ = create_handler(dt);
    pdh_->read(datadir);
    if(show_result_) pdh_->show_traindata();
}

//------------------
void KNearestNeighbor::eval(){

}

//------------------
void KNearestNeighbor::classify(const std::vector<double>& datum){

}

} // namespace mo

