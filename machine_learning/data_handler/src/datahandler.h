#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <string>
#include <memory> //unique_ptr
#include <vector>

namespace mo {
enum class DataType{mnist};

template<typename Datum = std::vector<unsigned char>, typename Label = unsigned char>
struct Dataset{
    std::vector<Datum> train_data;
    std::vector<Datum> test_data;
    std::vector<Label> train_labels;
    std::vector<Label> test_labels;
};

/////////////////////////////
/// \brief DataHandler
/////////////////////////////
template<typename Datum = std::vector<unsigned char>, typename Label = unsigned char>
class DataHandler
{
public:
    DataHandler(){}
    virtual void read(const std::string& datadir = "") = 0; // pure virtual function; must be implemented in derived classes.
    virtual void show_traindata() = 0;
    virtual ~DataHandler(){} // Because DataHandler has virtual func, need virtual destructor to call derived class's destructor.
    std::vector<Datum>& train_data(){return dataset_.train_data;}
    std::vector<Datum>& test_data(){return dataset_.test_data;}
    std::vector<Label>& train_labels(){return dataset_.train_labels;}
    std::vector<Label>& test_labels(){return dataset_.test_labels;}
protected:
    Dataset<Datum, Label> dataset_; //currently support only the same type MNIST_dataset
};


//////////////////////////////
/// \brief create_handler
/// \param data_type
/// \return
//////////////////////////////
std::unique_ptr<DataHandler<>> // we cannot define tempalete version.
    // because in that case we have to define whole inplementation in .h, and which needs mnisthandler.h,
    // so it cause cross include.
create_handler(const DataType data_type);

} // namespace mo

#endif // DATAHANDLER_H
