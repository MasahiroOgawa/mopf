#ifndef KNEARESTNEIGHBOR_H
#define KNEARESTNEIGHBOR_H
#include "../../data_handler/src/datahandler.h"
#include "../../data_handler/src/mnistdatahandler.h"
#include <memory> // for unique_ptr

namespace mo {
class KNearestNeighbor
{
public:
    KNearestNeighbor();
    void init(const DataType dt = DataType::mnist, const std::string& datadir = "", const bool show_result = true);
    void eval();
    void classify(const std::vector<double>& datum);

private:
    std::unique_ptr<DataHandler> pdh_;
    bool show_result_;
};

} // namespace mo

#endif // KNEARESTNEIGHBOR_H
