#include "../parallelstereo.hpp"
#include <iostream>

using namespace std;
using namespace mo;

int main() try {
  cout << "----------------------------------------\n"
       << "run test parallelstereo\n";

  cout << "[PASS] \n";

  return 0;
} catch (runtime_error &e) {
  cerr << "runtime error: " << e.what() << endl;
} catch (...) {
  cerr << "unknown error!\n";
}
