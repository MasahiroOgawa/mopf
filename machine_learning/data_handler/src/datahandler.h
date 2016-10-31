#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <string>
#include <memory> //unique_ptr
#include <vector>
#include "../../../linear_algebra/src/vector.h"
#include "mnistdatahandler.h"

namespace mo {
enum class DataType{mnist};

template<typename Datum = std::vector<unsigned char>, typename Label = unsigned char>
struct Dataset{
    std::vector<Datum> train_data;
    std::vector<Datum> test_data;
    std::vector<Label> train_labels;
    std::vector<Label> test_labels;
};

template<typename Datum = std::vector<unsigned char>, typename Label = unsigned char>
class DataHandler
{
public:
    DataHandler();
    virtual void read(const std::string& datadir = "") = 0; // pure virtual function; must be implemented in derived classes.
    virtual void show_traindata() = 0;
    virtual ~DataHandler(){} // Because DataHandler has virtual func, need virtual destructor to call derived class's destructor.
    std::vector<Datum> train_data(){return dataset_.train_data;}
    std::vector<Datum> test_data(){return dataset_.test_data;}
private:
    Dataset<Datum, Label> dataset_; //currently support only the same type MNIST_dataset
};


template<typename Datum = std::vector<unsigned char>, typename Label = unsigned char>
std::unique_ptr<DataHandler<Datum, Label>>
create_handler(const DataType data_type){
  switch (data_type) {
  case DataType::mnist:
    return std::unique_ptr<DataHandler<Datum, Label>>{new MnistDataHandler<Datum, Label>()};
    break;
  default:
    throw std::logic_error("no such data type.");
  }
}

} // namespace mo

#endif // DATAHANDLER_H
