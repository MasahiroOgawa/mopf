#ifndef KNEARESTNEIGHBOR_H
#define KNEARESTNEIGHBOR_H
#include "../../data_handler/src/datahandler.h"
#include "../../data_handler/src/mnistdatahandler.h"
#include <memory> // for unique_ptr
#include <map>
#include "../../../linear_algebra/src/vector.h" // for distance()

namespace mo {

template<typename Datum = std::vector<unsigned char>, typename Label = unsigned char>
class KNearestNeighbor
{
public:
    KNearestNeighbor(const int k, const DataType dt = DataType::mnist, const std::string& datadir = "", const bool show_result = true)
    {init(k,dt,datadir,show_result);}
    void init(const int k, const DataType dt = DataType::mnist, const std::string& datadir = "", const bool show_result = true);
    void eval();
    const Label classify(const Datum& datum);
    std::vector<Datum>& test_data(){return pdh_->test_data();}

private:
    int k_;
    std::unique_ptr<DataHandler<>> pdh_;
    bool show_result_;

    const Label count_majority_label(const std::map<double, Label>& dist_label);
};


//------------------
template<typename Datum, typename Label>
void KNearestNeighbor<Datum, Label>::init(const int k, const DataType dt, const std::string& datadir, const bool show_result){
    k_ = k;
    show_result_ = show_result;
    pdh_ = create_handler(dt);
    pdh_->read(datadir);
    if(show_result_) pdh_->show_traindata();
}

//------------------
template<typename Datum, typename Label>
const Label KNearestNeighbor<Datum, Label>::classify(const Datum& datum){
    std::map<double, Label> dist_label;
    const std::vector<Datum>& train_data = pdh_->train_data();
    const std::vector<Label>& train_labels = pdh_->train_labels();
    assert(train_data.size() == train_labels.size());

    for(int i=0; i<train_data.size(); ++i){
        double dist = distance(datum, train_data[i]);
        dist_label.insert( std::pair<double, Label>(dist, train_labels[i]) );
    }

    return count_majority_label(dist_label);
}

//-------------------
template<typename Datum, typename Label>
const Label KNearestNeighbor<Datum, Label>::count_majority_label(const std::map<double, Label>& dist_label)try{
    assert(k_ < dist_label.size());

    //cut k
    //map label as first index
    std::map<Label, int> label_occurences;
    auto it = dist_label.begin();

    for(int i=0; i<k_; ++i){
        ++label_occurences[it->second];
        ++it;
    }

    //count max label
//    auto

    //return
}catch(...){
throw;
}

} // namespace mo

#endif // KNEARESTNEIGHBOR_H
