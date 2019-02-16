#include "game.h"
#include "../../visualization/src/visualization.h"
#include <fstream>
using namespace std;

namespace mo {
namespace game {
//-----------------------------------------------------------------

Aquarium::Aquarium(const std::string &background_name) {
  background_img_ = imread(background_name);
}

void Aquarium::load_character(const string &image_name) {
  character_img_ = imread(image_name);
}

void Aquarium::run() {
  Matrix affine_mat = (Matrix(2, 3) << 1.0, 0.0, 10.0, 0.0, 1.0, 10.0);

  warpAffine(character_img_, background_img_, affine_mat);
  show("aquarium", background_img_);
}

//-----------------------------------------------------------------

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
