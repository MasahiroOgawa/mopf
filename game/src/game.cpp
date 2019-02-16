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
//-----------------------------------------------------------------

Aquarium::Aquarium(const std::string &background_name) {
  background_image_ = imread(background_name);
}

void Aquarium::load_character(const string &image_name) {
  character_.load_image(image_name);
}

void Aquarium::run() {
  show("aquarium", background_image_);
  character_.swim();
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
