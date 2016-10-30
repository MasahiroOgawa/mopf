#include "knearest_neighbor.h"
#include <map>

using namespace std;

namespace mo {
KNearestNeighbor::KNearestNeighbor(const DataType dt, const std::string& datadir, const bool show_result):
    show_result_(show_result),pdh_{create_handler(dt)}
{
    pdh_->read(datadir);
    if(show_result_) pdh_->show_traindata();
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
const char KNearestNeighbor::classify(const std::vector<unsigned char>& datum){
    map<double, int> dist_idx;
    for(int i=0; i< pdh_->train_data().size(); ++i){
        //double dist = distance(datum, train_datum);
        dist_idx.insert( pair<double, int>(0.0,i) );
    }
    //count_majority_class()
    //return class
    return 0;
}

} // namespace mo

