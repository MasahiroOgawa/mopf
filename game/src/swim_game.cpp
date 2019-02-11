#include "game.h"
#include <iostream>

using namespace std;
using namespace mo;
using namespace game;

int main(int argc, char *argv[]) {
  // read param
  if (argc != 2)
    throw runtime_error("Usage: argv[0] <parameter filename>");
  string prm_fname(argv[1]);
  Param prm(prm_fname);

  Character chara;
  chara.load_image(prm.image_fname);
  chara.swim();
}
