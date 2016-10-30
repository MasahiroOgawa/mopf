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
    const vector<vector<unsigned char>>& train_data = pdh_->train_data();

    for(int i=0; i<train_data.size(); ++i){
        double dist = distance(datum, train_data[i]);
        dist_idx.insert( pair<double, int>(dist, i) );
    }
    //count_majority_class()
    //return class
    return 0;
}

} // namespace mo

