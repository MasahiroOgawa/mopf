#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "../../image/src/image.h"

namespace mo {
namespace game {

class Character {
public:
  void load_image(const std::string &image_name);
  void swim();

private:
  cv::Mat image;
};

class Param {
public:
  Param(const std::string &prm_fname);
  std::string image_fname;
};

} // namespace game
} // namespace mo

#endif // VISUALIZATION_H
