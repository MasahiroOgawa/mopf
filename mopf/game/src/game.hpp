#ifndef GAME_H
#define GAME_H

#include "../../image/src/image.hpp"
#include "../../linear_algebra/src/matrix.hpp"
#include <opencv2/core.hpp>
#include <random>

namespace mo {
namespace game {

class Character {
public:
  Character(const std::string &image_name);
  void update_position(const int bgimg_w, const int bgimg_h,
                       std::normal_distribution<double> &distribution,
                       std::default_random_engine &generator,
                       const int dt = 10);
  void update_shape(const double time);
  const Image &img() { return character_img_; }
  const Matrix &affine_mat() { return affine_mat_; }

private:
  static constexpr double size_change_ratio_{0.2}; // times.
  static constexpr double skew_change_ratio_{0.2}; // times.

  Image character_img_;
  Matrix affine_mat_{(Matrix(2, 3) << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0)};
  double vx_{0.1}; // [pix / msec]
  double vy_{0.1};
  //  static constexpr _{};
};

class Aquarium {
public:
  Aquarium(const std::string &background_name);
  void load_characters(const std::vector<std::string> &character_imgnames);
  void run();

private:
  Image background_img_;
  Image composite_img_;
  std::vector<Character> characters_{};
};

} // namespace game
} // namespace mo

#endif // GAME_H
