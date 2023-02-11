#include "../visualization.hpp"
#include <iostream>

using namespace std;
using namespace mo;

int main() try {
  cout << "----------------------------------------\n"
       << "run test visualization\n";
  Color bg_color{0, 0, 128};
  Image img(256, 256, bg_color.pixval());
  Color arrow_color(255, 0, 0);
  cout << "back ground color=" << bg_color << endl
       << "arrow_color=" << arrow_color << endl;
  arrow(mo::Point2i(10, 20), mo::Point2i(100, 200), img, arrow_color);
  show("test win", img);

  cout << "[PASS] \n";

  return 0;
} catch (runtime_error &e) {
  cerr << "runtime error: " << e.what() << endl;
} catch (...) {
  cerr << "unknown error!\n";
}
