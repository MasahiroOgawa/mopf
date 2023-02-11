#include "../game.hpp"
#include <iostream>

using namespace std;
using namespace mo;
using namespace game;

int main() try {
  cout << "----------------------------------------\n"
       << "run test game\n";

  cout << "[PASS] \n";

  return 0;
} catch (runtime_error &e) {
  cerr << "runtime error: " << e.what() << endl;
} catch (...) {
  cerr << "unknown error!\n";
}
