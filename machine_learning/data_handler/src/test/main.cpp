#include "../datahandler.h"
#include "../../../../image/src/image.h"
#include "../../../../visualization/src/visualization.h"

using namespace std;
using namespace mo;

int main(){
    auto dataset = mnist::read_dataset_mopf();

    //display
    for(vector<uint8_t> tr_img : dataset.training_images){
        Image_gray img(28, 28, tr_img.data());
        show("train image", img, 0);
    }


    return 0;
}
