#include "irisdatahandler.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace mo {

IrisDataHandler::IrisDataHandler()
{

    cls_map_["Iris-setosa"] = (Matrix(3,1) << 1, 0, 0);
    cls_map_["Iris-versicolor"] = (Matrix(3,1) << 0, 1, 0);
    cls_map_["Iris-virginica"] = (Matrix(3,1) << 0, 0, 1);
}


/**
 * @brief IrisDataHandler::read
 * @param filename
 */
void IrisDataHandler::read(const std::string& datadir)
try{
    string filename = datadir + "/iris.data";
    ifstream fi(filename.c_str());
    if(!fi){
        string errmsg="cannot open: "+filename;
        throw(runtime_error(errmsg));
    }

    string line;
    string cell;
    Matrix Xt;
    unsigned datadim_ = 4;
    while(getline(fi, line)){ //read lines
        stringstream lstream(line);
        if(line.empty()) break; //in case reading empty line.
        Matrix x;
        for(unsigned i=0;i<datadim_;++i){ //read feature cells
            getline(lstream, cell, ',');
            x.push_back(stod(cell));
        }
        Xt.push_back(Matrix(x.t()));

        getline(lstream, cell, ','); //read instruction signal
        Matrix b_vec = cls_map_.find(cell)->second;
        if(train_labelmat_.empty()) train_labelmat_ = b_vec;
        else cv::hconcat(train_labelmat_, b_vec, train_labelmat_);
    }

    train_datamat_ = Xt.t();
}catch(invalid_argument &e){
    cerr << "invalid argument in DataHandler::read()\n";
    throw;
}


//-----------------------------------------
void IrisDataHandler::show_traindata(){
    cout << "train data matrix = " << train_datamat() << endl;
    cout << "train label matrix = " << train_labelmat() << endl;
}


} // namespace mo
