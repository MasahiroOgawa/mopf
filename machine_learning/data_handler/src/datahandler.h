#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include <string>
#include <memory> //unique_ptr
#include <vector>
#include "../../../linear_algebra/src/matrix.h"

namespace mo {
enum class DataType{
    david=1,
    iris,
    mnist
};

template<typename Datum, typename Label>
struct Dataset{
    std::vector<Datum> train_data;
    std::vector<Datum> test_data;
    std::vector<Label> train_labels;
    std::vector<Label> test_labels;
};

/////////////////////////////
/// \brief DataHandler
/////////////////////////////
template<typename Datum , typename Label>
class DataHandler
{
public:
    DataHandler(){}
    virtual void read(const std::string& datadir) = 0; // pure virtual function; must be implemented in derived classes.

    virtual const Matrix& train_datamat()const = 0; // for Neuralnet input
    virtual const Matrix& train_labelmat()const = 0;
    virtual ~DataHandler(){} // Because DataHandler has virtual func, need virtual destructor to call derived class's destructor.
    std::vector<Datum>& train_data(){return dataset_.train_data;}
    std::vector<Datum>& test_data(){return dataset_.test_data;}
    std::vector<Label>& train_labels(){return dataset_.train_labels;}
    std::vector<Label>& test_labels(){return dataset_.test_labels;}

    virtual char show(const Datum& datum, const std::string& winname) = 0;
    virtual void show_traindata() = 0;

protected:
    Dataset<Datum, Label> dataset_; //currently support only the same type MNIST_dataset
};


//////////////////////////////
/// \brief create_imgdata_handler
/// \param data_type
/// \return
/// we cannot define tempalete version.
/// because in that case we have to define whole inplementation in .h, and which needs mnisthandler.h,
///  so it cause cross include.
//////////////////////////////
std::unique_ptr<DataHandler<std::vector<unsigned char>, unsigned char>> create_imgdata_handler(const DataType data_type);


//////////////////////////////
/// \brief create_vecdata_handler
/// \param data_type
/// \return
//////////////////////////////
std::unique_ptr<DataHandler<std::vector<double>, double>> create_vecdata_handler(const DataType data_type);

} // namespace mo

#endif // DATAHANDLER_H
