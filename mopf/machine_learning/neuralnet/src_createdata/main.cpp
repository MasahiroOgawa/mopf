#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
  //param
  string outfname = "/home/masahiro/git/neuralnet/data/x^2_trainingdata.txt";

  //process
  ofstream fo(outfname);
  fo << "topology: 1 2 1\n";

  for(double x=-5; x<5; x+=0.1){
    fo << "in: " << x << endl;
    fo << "out: " << x*x << endl;
  }

  return 0;
}
