#ifndef KNEARESTNEIGHBOR_H
#define KNEARESTNEIGHBOR_H
#include "../../data_handler/src/datahandler.h"
#include "../../data_handler/src/mnistdatahandler.h"
#include <memory> // for unique_ptr
#include <map>
#include "../../../linear_algebra/src/vector.h" // for distance()
#include <ctime> // for clock_t

namespace mo {

template<typename Datum = std::vector<unsigned char>, typename Label = unsigned char>
class KNearestNeighbor
{
public:
    KNearestNeighbor(const int k, const std::string& datadir, const DataType dt = DataType::mnist
            , const bool show_result = true, const DistanceType disttp = DistanceType::l2);
    void eval();
    const Label classify(const Datum& datum);

private:
    int k_;
    std::unique_ptr<DataHandler<>> pdh_;
    bool show_result_;
    DistanceType disttp_;

    const Label count_majority_label(const std::map<double, Label>& dist_label);
};

//------------------
template<typename Datum, typename Label>
KNearestNeighbor<Datum, Label>::KNearestNeighbor(const int k, const std::string& datadir, const DataType dt
                                                 , const bool show_result, const DistanceType disttp):
    k_ {k}, show_result_ {show_result}, pdh_{create_handler(dt)}, disttp_{disttp}
{
    pdh_->read(datadir);
    if(show_result_) pdh_->show_traindata();

    std::cout << "[INFO] init k=" << k << ", datadir=" << datadir << ", data type=" << static_cast<int>(dt)
              << ", show result=" << show_result << ", distance type=" << static_cast<int>(disttp) << "\n";
}

//------------------
template<typename Datum, typename Label>
const Label KNearestNeighbor<Datum, Label>::classify(const Datum& datum){
    std::map<double, Label> dist_label;
    const std::vector<Datum>& train_data = pdh_->train_data();
    const std::vector<Label>& train_labels = pdh_->train_labels();
    assert(train_data.size() == train_labels.size());

    for(int i=0; i<train_data.size(); ++i){
        double dist = distance(datum, train_data[i], disttp_);
        dist_label.insert( std::pair<double, Label>(dist, train_labels[i]) );
    }

    //todo: add reject option
    if(show_result_){
        std::cout << "min normalized dist= " << dist_label.begin()->first / pdh_->train_data()[0].size();
    }

    return count_majority_label(dist_label);
}

//-------------------
template<typename Datum, typename Label>
const Label KNearestNeighbor<Datum, Label>::count_majority_label(const std::map<double, Label>& dist_label)try{
    assert(k_ < dist_label.size());

    std::map<Label, int> label_occurences;
    auto it = dist_label.begin();
    for(int i=0; i<k_; ++i){
        ++label_occurences[it->second];
        ++it;
    }

    auto it2 = std::max_element(label_occurences.begin(), label_occurences.end(),
                                [](const std::pair<Label,int>& p1, const std::pair<Label,int>& p2){return p1.second < p2.second;});

    return it2->first;


}catch(...){
throw;
}

//--------------------
template<typename Datum, typename Label>
void KNearestNeighbor<Datum, Label>::eval(){
    std::cout << "[INFO] enter " << __func__ << '\n';
    assert(pdh_->test_data().size() == pdh_->test_labels().size());

    int num_correct=0;
    int num_testdata = pdh_->test_data().size();
    for(int i=0; i<num_testdata; ++i){
        if(show_result_){
            std::cout << "test " << i << ": ";
        }

        clock_t beg = clock();
        Label lbl = classify(pdh_->test_data()[i]);
        clock_t end = clock();

        if(lbl == pdh_->test_labels()[i]) ++num_correct;

        if(show_result_){
            std::cout << ", computed label= " << static_cast<int>(lbl)
                      << ", true label= " << static_cast<int>(pdh_->test_labels()[i])
                      << ", computation time=" << float(end - beg)/CLOCKS_PER_SEC << "[s]\n" << std::flush;

            char ch = pdh_->show(pdh_->test_data()[i], "test image");
            switch (ch) {
            case 'p':
            case 'b':
                i-=2;
                break;
            case 'q':
                destroy_window("test image");
                show_result_ = false;
                break;
            default:
                break;
            }
        }
    }

    std::cout << "correct classification= " << num_correct * 100.0 / num_testdata << '\n';
}


} // namespace mo

#endif // KNEARESTNEIGHBOR_H
