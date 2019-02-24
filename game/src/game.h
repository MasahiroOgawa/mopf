#ifndef GAME_H
#define GAME_H

#include "../../image/src/image.h"
#include "../../linear_algebra/src/matrix.h"
#include <opencv2/core.hpp>

namespace mo {
namespace game {

class Character {
public:
  void load(const std::string &image_name);
  void update_position(const int bgimg_w, const int bgimg_h);
  void update_shape(const double time);
  const Image &img() { return character_img_; }
  const Matrix &affine_mat() { return affine_mat_; }

private:
  static constexpr double size_change_ratio_{0.2}; // times.
  static constexpr double skew_change_ratio_{0.2}; // times.
  static constexpr double dt_{10};                 // msec

  Image character_img_;
  Matrix affine_mat_{(Matrix(2, 3) << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0)};
  double vx_{0.0}; // [pix / msec]
  double vy_{0.0};
};

class Aquarium {
public:
  Aquarium(const std::string &background_name);
  void load_characters(const std::string &character_imgname);
  void run();

private:
  Image background_img_;
  Image composite_img_;
  Character character_;
};

class Param {
public:
  Param(const std::string &prm_fname);
  std::string character_fname;
  std::string background_fname;
};

} // namespace game
} // namespace mo

#endif // GAME_H
