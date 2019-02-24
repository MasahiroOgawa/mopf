#include "game.h"
#include "../../visualization/src/visualization.h"
#include <fstream>
#include <random> //for Character::update_position()

using namespace std;

namespace mo {
namespace game {
//-----------------------------------------------------------------

Aquarium::Aquarium(const std::string &background_name) {
  background_img_ = imread(background_name);
}

void Aquarium::load_characters(const std::string &character_imgname) {
  character_.load(character_imgname);
}

void Aquarium::run() {
  static constexpr int dt{10}; // msec
  double time{0.0};            // msec

  while (1) {
    background_img_.copyTo(composite_img_);

    // movement on x,y
    character_.update_position(composite_img_.cols, composite_img_.rows);
    character_.update_shape(time);

    warpAffine(character_.img(), composite_img_, character_.affine_mat());

    if (show("aquarium", composite_img_, dt) == 'q')
      break;
    time += dt;
  }
}

//-----------------------------------------------------------------
void Character::load(const string &image_name) {
  character_img_ = imread(image_name);
}

void Character::update_position(const int bgimg_w, const int bgimg_h) {
  double &posx = affine_mat_.at<double>(0, 2); // alias
  double &posy = affine_mat_.at<double>(1, 2); // alias
  if (posx > bgimg_w - character_img_.cols && vx_ > 0 || posx < 0 && vx_ < 0)
    vx_ *= -1;
  if (posy > bgimg_h - character_img_.rows && vy_ > 0 || posy < 0 && vy_ < 0)
    vy_ *= -1;

  static std::default_random_engine generator;
  normal_distribution<double> distribution(0.0, 0.01);
  vx_ += distribution(generator);
  vy_ += distribution(generator);

  posx += vx_ * dt_;
  posy += vy_ * dt_;
}

void Character::update_shape(const double time) {
  affine_mat_.at<double>(0, 0) = 1 + size_change_ratio_ * sin(time * 0.001);
  affine_mat_.at<double>(1, 1) = 1 + size_change_ratio_ * sin(time * 0.001);
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
