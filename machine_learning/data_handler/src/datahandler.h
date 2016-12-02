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
    virtual char show(const Datum& datum, const std::string& winname) = 0;
    virtual void show_traindata() = 0;
    const Matrix& train_datamat() const {return train_datamat_;}
    const Matrix& train_labelmat() const {return train_labelmat_;}
    virtual ~DataHandler(){} // Because DataHandler has virtual funcs, it needs virtual destructor to call derived class's destructor.

    const std::vector<Datum>& train_data() const {return dataset_.train_data;}
    const std::vector<Datum>& test_data() const {return dataset_.test_data;}
    const std::vector<Label>& train_labels() const {return dataset_.train_labels;}
    const std::vector<Label>& test_labels() const {return dataset_.test_labels;}
    const size_t train_datanum() const {return dataset_.train_data.size();}
    const size_t train_datadim() const {return dataset_.train_data[0].size();}

protected:
    Dataset<Datum, Label> dataset_;
    Matrix train_datamat_; //< train_datamat_ = [x1,x2,...,xN]. s.t. xi=[,,,]^T. this is duplicated with Dataset, but needed for Neuralnet because of its datahandling method.
    Matrix train_labelmat_; //< train_labelmat_ = [x1,x2,...,xN]. s.t. xi=[,,,]^T
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
