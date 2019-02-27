#ifndef PARAM_H
#define PARAM_H
#include <string>

namespace mo {
namespace game {

class Param {
public:
  Param(const std::string &prm_fname);
  std::string character_fname;
  std::string background_fname;
};

} //namespace game
} //namespace mo

#endif // PARAM_H
