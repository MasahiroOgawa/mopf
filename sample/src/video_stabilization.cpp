#include "../../video/src/videostabilizer.h"

int main(int argc, char **argv) {
  mo::VideoStabilizer vs(argv[1]);
  vs.run();
  return 0;
}
