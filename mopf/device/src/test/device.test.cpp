#include "../usbcam.hpp"
#include <iostream>

using namespace std;
using namespace mo;

void test_usbcam() {
  cout << "---------------------------\nrun" << __func__ << endl;

  Usbcam cam;
  if (cam.show_loop())
    cout << "[PASS] \n";
  else
    throw runtime_error("cannot capture!");
}

int main() try {
  cout << "============================\n"
       << "start device_test.\n";

  test_usbcam();

  return 0;
} catch (runtime_error &e) {
  cerr << "runtime error: " << e.what() << endl;
} catch (...) {
  cerr << "unknown error!\n";
}
