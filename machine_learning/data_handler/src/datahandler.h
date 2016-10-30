#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <string>
#include <memory> //unique_ptr
#include <vector>
#include "../../../linear_algebra/src/vector.h"

namespace mo {
enum class DataType{mnist};

template<typename Datum, typename Label> struct Dataset{
    std::vector<Datum> train_data;
    std::vector<Datum> test_data;
    std::vector<Label> train_labels;
    std::vector<Label> test_labels;
};

class DataHandler
{
public:
    DataHandler();
    virtual void read(const std::string& datadir = "") = 0; // pure virtual function; must be implemented in derived classes.
    virtual void show_traindata() = 0;
    virtual ~DataHandler(){} // Because DataHandler has virtual func, need virtual destructor to call derived class's destructor.
    std::vector<std::vector<unsigned char>> train_data(){return dataset_.train_data;}
private:
    Dataset<std::vector<unsigned char>, unsigned char> dataset_; //currently support only the same type MNIST_dataset
};

std::unique_ptr<DataHandler> create_handler(const DataType data_type);

} // namespace mo

#endif // DATAHANDLER_H
