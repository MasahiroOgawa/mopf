#include "datahandler.h"
#include "daviddatahandler.h"
#include "irisdatahandler.h"
#include <memory> //for unique_ptr
using namespace std;


/**
 * @brief DataHandler::DataHandler
 */
DataHandler::DataHandler()
{
}



DataHandler* create_handler(const DataHandler::DataType data_type){
  DataHandler* pdh;
  switch (data_type) {
  case DataHandler::David:
    pdh = new DavidDataHandler();
    break;
  case DataHandler::Iris:
    pdh = new IrisDataHandler();
    break;
  default:
    throw runtime_error("no such data type.");
  }
  return pdh;
}
