#include "mnistdatahandler.h"


using namespace std;

namespace mo {

//---------------------------------------
void MnistDataHandler::read(const std::string& datadir){
    std::cout << "[INFO] try to read mnist data from " << datadir << " @" << __func__ << "\n";

    mnist::MNIST_dataset<std::vector, std::vector<unsigned char>, unsigned char> mnist_dataset = mnist::read_dataset(datadir);

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
void MnistDataHandler::show_traindata(){
    std::cout << "q: stop display.\n";

    const std::vector<std::vector<unsigned char>>& train_data = this->dataset_.train_data;
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
char MnistDataHandler::show(const std::vector<unsigned char>& datum, const std::string& winname){
    Image_gray img(28, 28, const_cast<unsigned char*>(datum.data()));
    return mo::show(winname, img, 0);
}

//---------------------------------------
const Matrix& MnistDataHandler::X()const{
    return Matrix();
}

//---------------------------------------
const Matrix& MnistDataHandler::B()const{
    return Matrix();
}

} // namespace mo
