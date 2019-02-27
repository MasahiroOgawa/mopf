#include "param.h"
#include <fstream>

using namespace std;

namespace mo {
namespace game {

Param::Param(const std::string &prm_fname) {
  // read param
  ifstream fi(prm_fname);
  if (!fi)
    throw runtime_error("input parameter file could not open.");

  constexpr streamsize max_strlen(1024);
  string str;
  while (fi >> str) {
    if (str == "character_filename:")
      fi >> character_fname;
    else if (str == "background_filename:")
      fi >> background_fname;

    fi.ignore(
        max_strlen,
        '\n'); // read until reaching the max_strlen or the end of the line.
  }
}

} // namespace game
} // namespace mo
