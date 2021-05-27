#include "../string_util.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace mo;

int main() try {
  if (is_number("0") != true)
    throw runtime_error("0 is a number!");
  if (is_number("8") != true)
    throw runtime_error("8 is a number!");
  if (is_number("a") != false)
    throw runtime_error("a is not a number!");

  cout << "[PASS]" << endl;
} catch (exception &e) {
  cerr << "[ERROR] " << e.what() << endl;
}
