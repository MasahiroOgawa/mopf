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

class Aquarium {
public:
  Aquarium(const std::string &background_name);
  void load_character(const std::string &image_name);
  void run();

private:
  Image background_image_;
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
