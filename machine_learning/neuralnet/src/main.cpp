#include <stdexcept>
#include "../../data_handler/src/datahandler.h"
#include "../../data_handler/src/daviddatahandler.h"
#include "../../data_handler/src/irisdatahandler.h"
#include "neuralnethandler.h"
#include <memory> //for unique_ptr
using namespace std;
using namespace mo;

int main(int argc, char** argv)
try{
  //read param
  if(argc!=2) throw runtime_error("Usage: Neuralnet <parameter filename>");
  ifstream prm_file(argv[1]);
  if (!prm_file) throw runtime_error("input parameter file could not open.");
  Param prm;
  read_param(prm_file,prm);

  //read data
  unique_ptr<DataHandler<>> pdh{create_handler(static_cast<DataType>(prm.data.data_type))};
  pdh->read(prm.data.datafname);

  //learn
  NeuralnetHandler nns(prm.nn, prm.vis);
  nns.learn(pdh->X(), pdh->B());

  return 0;
}catch(runtime_error& e){
  cerr << "runtime error: " << e.what() << endl;
}catch(logic_error& e){
  cerr << "logic error: " << e.what() << endl;
}catch(...){
cerr << "unknown error occured.\n";
}
