#include "param.hpp"
#include <fstream>
#include <sstream> // for istringstream

using namespace std;

namespace mo {
namespace game {

Param::Param(const std::string &prm_fname) {
  // read param
  ifstream fi(prm_fname);
  if (!fi)
    throw runtime_error("input parameter file could not open.");

  constexpr streamsize max_strlen(1024);
  string str;
  while (fi >> str) {
    if (str == "character_filename:")
      read_strs(fi, character_fnames, '#');
    else if (str == "background_filename:")
      fi >> background_fname;

    fi.ignore(
        max_strlen,
        '\n'); // read until reaching the max_strlen or the end of the line.
  }
}

void read_strs(istream &ist, std::vector<string> &strs, const char delim) {
  string line;
  getline(ist, line, delim); // read until delim
  istringstream iss(line);
  string str;
  while (iss >> str)
    strs.push_back(str);
}
} // namespace game
} // namespace mo
