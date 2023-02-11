#include "../series.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace mo;

void test_fibonacci() {
  cout << "-----------------------------\n"
       << "run " << __func__ << endl;
  for (int i = 0; i < 91; ++i)
    cout << "fibonacci(" << i << ")= " << fibonacci(i) << endl;

  cout << "[PASS] \n";
}

int main() try {
  cout << "============================\n"
       << "start lalgebra_test.\n";

  test_fibonacci();

  return 0;
} catch (exception &e) {
  cerr << "[ERROR] " << e.what() << endl;
} catch (...) {
  cerr << "unknown error!\n";
}
