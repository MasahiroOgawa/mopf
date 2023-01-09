#include "../datahandler.h"
#include "../mnistdatahandler.h"

using namespace std;
using namespace mo;

int main()try{
    unique_ptr<DataHandler<vector<unsigned char>, unsigned char>> pdh{create_imgdata_handler(DataType::mnist)};
    pdh->read("~/git/my/mopf/data/mnist");
    pdh->show_traindata();

    return 0;
}catch(runtime_error& e){
    cerr << "runtime error: " << e.what() << endl;
}catch(logic_error& e){
    cerr << "logic error: " << e.what() << endl;
}catch(...){
cerr << "unknown error occured.\n";
}
