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

private:
    mnist::MNIST_dataset<std::vector, Datum, Label> dataset_;
};


//---------------------------------------
template<typename Datum, typename Label> void
MnistDataHandler<Datum,Label>::read(const std::string& datadir){
    dataset_ = (datadir.empty()) ?
                mnist::read_dataset("git/my/mopf/data/mnist") : mnist::read_dataset(datadir);
}

//---------------------------------------
template<typename Datum, typename Label> void
MnistDataHandler<Datum, Label>::show_traindata(){
    for(std::vector<uint8_t> tr_img : dataset_.training_images){
        Image_gray img(28, 28, tr_img.data());
        show("train image", img, 0);
    }
}

} // namespace mo

#endif // MNISTDATAHANDLER_H
