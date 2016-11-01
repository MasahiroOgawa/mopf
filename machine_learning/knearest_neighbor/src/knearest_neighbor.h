#ifndef KNEARESTNEIGHBOR_H
#define KNEARESTNEIGHBOR_H
#include "../../data_handler/src/datahandler.h"
#include "../../data_handler/src/mnistdatahandler.h"
#include <memory> // for unique_ptr

#include <map>
#include "../../../linear_algebra/src/vector.h"

namespace mo {
class KNearestNeighbor
{
public:
    KNearestNeighbor(const DataType dt = DataType::mnist, const std::string& datadir = "", const bool show_result = true);
    void init(const DataType dt = DataType::mnist, const std::string& datadir = "", const bool show_result = true);
    void eval();
    template<typename Datum = std::vector<unsigned char>, typename Label = unsigned char>
    const Label classify(const Datum& datum);
    template<typename Datum = std::vector<unsigned char>> std::vector<Datum>& test_data(){return pdh_->test_data();}

private:
    std::unique_ptr<DataHandler<>> pdh_;
    bool show_result_;
};


//------------------
template<typename Datum, typename Label>
const Label KNearestNeighbor::classify(const Datum& datum){
    std::cout << "start " << __func__ << std::endl;

    std::map<double, int> dist_idx;
    const std::vector<Datum>& train_data = pdh_->train_data();

    for(int i=0; i<train_data.size(); ++i){
        double dist = distance(datum, train_data[i]);

        //debug
        std::cout << "dis to train_data[" << i << "] = " << dist << std::endl;

        dist_idx.insert( std::pair<double, int>(dist, i) );
    }
    //count_majority_class()
    //return class
    return 0;
}

} // namespace mo

#endif // KNEARESTNEIGHBOR_H
