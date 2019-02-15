#include "game.h"
#include "../../visualization/src/visualization.h"
#include <fstream>
using namespace std;

namespace mo {
namespace game {
//-----------------------------------------------------------------
void Character::load_image(const std::string &image_name) {
  image = imread(image_name);
}

void Character::swim() { show("water tank", image); }

Param::Param(const std::string &prm_fname) {
  // read param
  ifstream fi(prm_fname);
  if (!fi)
    throw runtime_error("input parameter file could not open.");

  constexpr streamsize max_strlen(1024);
  string str;
  while (fi >> str) {
    if (str == "image_filename:")
      fi >> image_fname;

    fi.ignore(
        max_strlen,
        '\n'); // read until reaching the max_strlen or the end of the line.
  }
}

} // namespace game
} // namespace mo
