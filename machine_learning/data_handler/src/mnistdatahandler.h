#ifndef MNISTDATAHANDLER_H
#define MNISTDATAHANDLER_H
#include "datahandler.h"
#include "../../../ext/mnist/src/mnist_reader.hpp"
#include "../../../image/src/image.h"
#include "../../../visualization/src/visualization.h"

namespace mo{

template<typename Datum , typename Label>
class MnistDataHandler : public DataHandler<Datum, Label>
{
public:
    MnistDataHandler(){}

    //////////////////
    /// \brief read
    /// \param datadir
    //////////////////
    void read(const std::string& datadir);

    //////////////////
    /// \brief show
    /// \param datum
    /// \return pushed key on the window
    //////////////////
    char show(const Datum& datum, const std::string& winname="mnist image");

    void show_traindata();
    const Matrix& train_datamat()const;
    const Matrix& train_labelmat()const;
};


//---------------------------------------
template<typename Datum , typename Label>
void MnistDataHandler<Datum,Label>::read(const std::string& datadir){
    std::cout << "[INFO] try to read mnist data from " << datadir << " @" << __func__ << "\n";

    mnist::MNIST_dataset<std::vector, Datum, Label> mnist_dataset = mnist::read_dataset<std::vector, std::vector, typename Datum::value_type, Label>(datadir);

    this->dataset_.train_data = std::move(mnist_dataset.training_images); // we need this-> to make it dependent name(template arguments).
    this->dataset_.test_data = std::move(mnist_dataset.test_images);
    this->dataset_.train_labels = std::move(mnist_dataset.training_labels);
    this->dataset_.test_labels = std::move(mnist_dataset.test_labels);

    //print out info
    size_t num_traindata = this->dataset_.train_data.size();
    size_t num_testdata = this->dataset_.test_data.size();
    size_t num_trainlbl = this->dataset_.train_labels.size();
    size_t num_testlbl = this->dataset_.test_labels.size();
    std::cout << "[INFO] read " << "#train data=" << num_traindata << ", #train labels=" << num_trainlbl
              << ", #test data=" << num_testdata << ", #test labels=" << num_testlbl << "\n";
    if(num_traindata != num_trainlbl){
        std::string errmsg = "#train_data != #train_labels @";
        errmsg += __func__;
        throw(std::logic_error(errmsg));
    }
    if(this->dataset_.test_data.size() != this->dataset_.test_labels.size()){
        std::string errmsg = "#test_data != #test_labels @";
        errmsg += __func__;
        throw(std::logic_error(errmsg));
    }
}

//---------------------------------------
template<typename Datum , typename Label>
char MnistDataHandler<Datum, Label>::show(const Datum& datum, const std::string& winname){
    std::cout << "datum" << std::endl;
    return '0';
}

//---------------------------------------
// template specialization for image data.
// to avoid being called primary, this must be placed in header file.
// in this case, it needs inline specifier. then it has the same address in every translation unit.
// otherwise it cause compile error of multiple definition.
template<>
inline char MnistDataHandler<std::vector<unsigned char>, unsigned char>::show(const std::vector<unsigned char>& datum, const std::string& winname){
    Image_gray img(28, 28, const_cast<unsigned char*>(datum.data()));
    return mo::show(winname, img, 0);
}

//---------------------------------------
template<typename Datum , typename Label>
void MnistDataHandler<Datum, Label>::show_traindata(){
    std::cout << "q: stop display.\n";

    const auto& train_data = this->train_data();
    for(auto tr_img : train_data){
        char ch = this->show(tr_img,"train image");
        if(ch=='q'){
            destroy_window("train image");
            break;
        }
    }

    return;
}

//---------------------------------------
template<typename Datum , typename Label>
const Matrix& MnistDataHandler<Datum, Label>::train_datamat()const{
    return Matrix();
}

//---------------------------------------
template<typename Datum , typename Label>
const Matrix& MnistDataHandler<Datum, Label>::train_labelmat()const{
    return Matrix();
}


} // namespace mo

#endif // MNISTDATAHANDLER_H
