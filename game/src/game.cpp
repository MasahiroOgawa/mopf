#include "game.h"
#include <fstream>
#include <opencv2/highgui.hpp>
using namespace std;

namespace mo {
namespace game {
//-----------------------------------------------------------------
void Character::load_image(const std::string &image_name) {
  image = cv::imread(image_name);
}

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
