#include "datahandler.h"
#include "mnistdatahandler.h"

using namespace std;

namespace mo {

//-----------------------------------------
std::unique_ptr<DataHandler<>>
create_handler(const DataType data_type){
  switch (data_type) {
  case DataType::mnist:
      return std::unique_ptr<DataHandler<>>{new MnistDataHandler<>()};
    break;
  default:
    throw std::logic_error("no such data type.");
  }
}

} // namespace mo
