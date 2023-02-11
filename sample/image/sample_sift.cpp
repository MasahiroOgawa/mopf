#include <mopf/image/src/sift.hpp>
#include <mopf/visualization/src/visualization.hpp>
using namespace std;

int main(int argc, char **argv) try {
  // read image
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " image_filename\n";
    return -1;
  }
  string imgname = argv[1];
  mo::Image_gray in_img = mo::imread_gray(imgname);
  if (in_img.empty()) {
    cerr << "[ERROR] fail to read " << imgname << endl;
    return -1;
  }

  // run SIFT
  mo::Sift sift;
  sift.detect(in_img);
  sift.show();

  return 0;
} catch (runtime_error &e) {
  cerr << "[ERROR] " << e.what() << endl;
} catch (...) {
  cerr << "[ERROR] Unkown error occureed!";
}
