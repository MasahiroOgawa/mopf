#include "../game.h"
#include <iostream>

using namespace std;
using namespace mo;
using namespace game;

int main(int argc, char *argv[]) try {
  // read param
  if (argc != 2)
    throw runtime_error("Usage: argv[0] <parameter filename>");
  string prm_fname(argv[1]);
  Param prm(prm_fname);

  Aquarium aquarium(prm.background_fname);
  aquarium.load_character(prm.character_fname);
  aquarium.run();

} catch (runtime_error &e) {
  cerr << "runtime error: " << e.what() << endl;
} catch (...) {
  cerr << "unknown error!\n";
}
