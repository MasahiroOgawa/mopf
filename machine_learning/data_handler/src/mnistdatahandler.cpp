#include "mnistdatahandler.h"
#include "../../../image/src/image.h"
#include "../../../visualization/src/visualization.h"

using namespace std;

namespace mo {

MnistDataHandler::MnistDataHandler()
{

}

//---------------------------------------
void MnistDataHandler::read(const std::string& datadir){
    dataset_ = (datadir.empty()) ?
                mnist::read_dataset("git/my/mopf/data/mnist") : mnist::read_dataset(datadir);
}

//---------------------------------------
void MnistDataHandler::show_traindata(){
    for(vector<uint8_t> tr_img : dataset_.training_images){
        Image_gray img(28, 28, tr_img.data());
        show("train image", img, 0);
    }
}
} // namespace mo
