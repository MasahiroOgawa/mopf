#include "datahandler.h"
#include "mnistdatahandler.h"

using namespace std;

namespace mo {
DataHandler::DataHandler()
{

}


//-----------------------------------------
std::unique_ptr<DataHandler> create_handler(const DataType data_type){
    unique_ptr<DataHandler> pdh;
  switch (data_type) {
  case DataType::mnist:
    pdh = unique_ptr<DataHandler>{new MnistDataHandler()};
    break;
  default:
    throw logic_error("no such data type.");
  }
  return pdh;
}

} // namespace mo
