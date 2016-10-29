#include "datahandler.h"

using namespace std;

namespace mo {
DataHandler::DataHandler(const Datatype dt) : dt_(dt)
{

}

//------------------
void DataHandler::init(const Datatype dt){
    dt_ = dt;
}

//------------------
void DataHandler::read(){
    switch (dt_) {
    case Datatype::mnist:
        mnist_data_ = mnist::read_dataset_mopf();
        break;
    default:
        throw logic_error("no such Datatype.");
    }
}

} // namespace mo
