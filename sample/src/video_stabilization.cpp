#include "../../video/src/videostabilizer.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " video_file_name\n";
    return 1;
  }
  mo::VideoStabilizer vs(argv[1]);
  vs.run();
  return 0;
}
