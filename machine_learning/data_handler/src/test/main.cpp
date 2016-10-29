#include "../datahandler.h"

using namespace std;
using namespace mo;

int main(){
    string mnist_dir = "git/my/mopf/data/mnist";
    string trainimg = mnist_dir + "/train-images-idx3-ubyte";
    string testimg = mnist_dir + "/t10k-images-idx3-ubyte";
    string trainlabel = mnist_dir + "/train-labels-idx1-ubyte";
    string testlabel = mnist_dir + "/t10k-labels-idx1-ubyte";

    auto dataset = mnist::read_dataset(trainimg, testimg, trainlabel, testlabel);
    for(vector<uint8_t> tr_img : dataset.training_images){
//        for(auto p : tr_img)
//            cout << int(p) << ' ';

        Image_gray img(28, 28, tr_img.data());
//        cout << img << endl;
        show("train image", img, 0);
    }


    return 0;
}
