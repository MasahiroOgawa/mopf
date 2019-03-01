#ifndef PARAM_H
#define PARAM_H
#include <string>
#include <vector>

namespace mo {
namespace game {

class Param {
public:
  Param(const std::string &prm_fname);
  std::vector<std::string> character_fnames;
  std::string background_fname;
};

void read_strs(std::istream &ist, std::vector<std::string> &strs,
               const char delim);

} // namespace game
} // namespace mo

#endif // PARAM_H
