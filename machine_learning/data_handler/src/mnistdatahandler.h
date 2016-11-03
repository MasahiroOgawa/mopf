#ifndef MNISTDATAHANDLER_H
#define MNISTDATAHANDLER_H
#include "datahandler.h"
#include "../../../ext/mnist/mnist_reader.hpp"
#include "../../../image/src/image.h"
#include "../../../visualization/src/visualization.h"

namespace mo{

template<typename Datum = std::vector<unsigned char>, typename Label = unsigned char>
class MnistDataHandler : public DataHandler<Datum,Label>
{
public:
    MnistDataHandler(){}
    void read(const std::string& datadir = "");
    void show_traindata();
};


//---------------------------------------
template<typename Datum, typename Label> void
MnistDataHandler<Datum,Label>::read(const std::string& datadir){
    mnist::MNIST_dataset<std::vector, Datum, Label> mnist_dataset = (datadir.empty()) ?
                mnist::read_dataset("git/my/mopf/data/mnist") : mnist::read_dataset(datadir);

    this->dataset_.train_data = std::move(mnist_dataset.training_images); // we need this-> to make it dependent name(template arguments).
    this->dataset_.test_data = std::move(mnist_dataset.test_images);
    this->dataset_.train_labels = std::move(mnist_dataset.training_labels);
    this->dataset_.test_labels = std::move(mnist_dataset.test_labels);

    assert(this->dataset_.train_data.size() == this->dataset_.train_labels.size());
    assert(this->dataset_.test_data.size() == this->dataset_.test_labels.size());
}

//---------------------------------------
template<typename Datum, typename Label> void
MnistDataHandler<Datum, Label>::show_traindata(){
    std::cout << "q: stop display.\n";

    const std::vector<Datum>& train_data = this->dataset_.train_data;
    for(std::vector<unsigned char> tr_img : train_data){
        Image_gray img(28, 28, tr_img.data());
        char ch = show("train image", img, 0);
        if(ch=='q'){
            destroy_window("train image");
            break;
        }
    }
}

} // namespace mo

#endif // MNISTDATAHANDLER_H
