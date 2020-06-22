#include "game.h"
#include "../../visualization/src/visualization.h"
#include "param.h"
#include <fstream>
#include <random>

using namespace std;

namespace mo {
namespace game {
//-----------------------------------------------------------------

Aquarium::Aquarium(const std::string &background_name) {
  background_img_ = imread(background_name);
}

void Aquarium::load_characters(
    const std::vector<std::string> &character_imgnames) {
  for (auto character_imgname : character_imgnames)
    characters_.push_back(Character(character_imgname));
}

void Aquarium::run() {
  static constexpr int dt{1000}; // msec
  double time{0.0};              // msec
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0.0, 0.1);

  while (1) {
    background_img_.copyTo(composite_img_);

    // movement on x,y
    for (auto character : characters_) {
      character.update_position(composite_img_.cols, composite_img_.rows,
                                distribution, generator, dt);
      character.update_shape(time);

      warpAffine(character.img(), composite_img_, character.affine_mat());
    }

    if (show("aquarium", composite_img_, dt) == 'q')
      break;
    time += dt;
  }
} // namespace game

//-----------------------------------------------------------------
Character::Character(const string &image_name) {
  character_img_ = imread(image_name);
}

void Character::update_position(const int bgimg_w, const int bgimg_h,
                                std::normal_distribution<double> &distribution,
                                std::default_random_engine &generator,
                                const int dt) {
  // get an alias
  double &posx = affine_mat_.at<double>(0, 2);
  double &posy = affine_mat_.at<double>(1, 2);

  // add normal distribution to the velocity.
  //  vx_ += distribution(generator);
  //  vy_ += distribution(generator);

  // let it stay inside background image.
  if ((posx > bgimg_w - character_img_.cols && vx_ > 0) ||
      (posx < 0 && vx_ < 0))
    vx_ *= -1;
  if ((posy > bgimg_h - character_img_.rows && vy_ > 0) ||
      (posy < 0 && vy_ < 0))
    vy_ *= -1;

  // integrate velocity to position.
  posx += vx_ * dt;
  posy += vy_ * dt;
}

void Character::update_shape(const double time) {
  affine_mat_.at<double>(0, 0) = 1 + size_change_ratio_ * sin(time * 0.001);
  affine_mat_.at<double>(1, 1) = 1 + size_change_ratio_ * sin(time * 0.001);
}

} // namespace game
} // namespace mo
