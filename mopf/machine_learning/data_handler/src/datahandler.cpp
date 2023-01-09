#include "datahandler.h"
#include "mnistdatahandler.h"
#include "daviddatahandler.h"
#include "irisdatahandler.h"

using namespace std;

namespace mo {

std::unique_ptr<DataHandler<std::vector<unsigned char>, unsigned char>> create_imgdata_handler(const DataType data_type){
    switch (data_type) {
    case DataType::mnist:
        return unique_ptr<DataHandler<vector<unsigned char>, unsigned char>>{ new MnistDataHandler<vector<unsigned char>, unsigned char>() };
    default:
        throw std::logic_error("no such data type. @DataHandler::create_imgdata_handler()");
    }
}

//------------------------------
std::unique_ptr<DataHandler<std::vector<double>, double>> create_vecdata_handler(const DataType data_type){
    switch (data_type) {
    case DataType::david:
        return unique_ptr<DataHandler<vector<double>, double>>{ new DavidDataHandler() };
    case DataType::iris:
        return unique_ptr<DataHandler<vector<double>, double>>{ new IrisDataHandler() };
    case DataType::mnist:
        return unique_ptr<DataHandler<vector<double>, double>>{ new MnistDataHandler<vector<double>, double>() };
    default:
        throw std::logic_error("no such data type. @DataHandler::create_vecdata_handler()");
    }
}

} // namespace mo
