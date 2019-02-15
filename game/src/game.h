#ifndef GAME_H
#define GAME_H

#include "../../image/src/image.h"
#include <opencv2/core.hpp>

namespace mo {
namespace game {

class Character {
public:
  void load_image(const std::string &image_name);
  void swim();

private:
  Image image;
};

class Param {
public:
  Param(const std::string &prm_fname);
  std::string image_fname;
};

} // namespace game
} // namespace mo

#endif // GAME_H
