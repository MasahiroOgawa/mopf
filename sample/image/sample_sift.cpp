#include <mopf/image/src/sift.hpp>
#include <mopf/visualization/src/visualization.hpp>
using namespace std;

int main(int argc, char **argv) try {
  // read image
  if (argc < 2) {
    cerr << "Usage: " << argv[0]
         << " image_filename [matching_img2_filename]\n";
    return -1;
  }
  string imgname = argv[1];
  mo::Image_gray in_img = mo::imread_gray(imgname);
  if (in_img.empty()) {
    cerr << "[ERROR] fail to read " << imgname << endl;
    return -1;
  }
  // read matching image if exist
  string img2name{};
  mo::Image_gray in_img2{};
  if (argc > 2) {
    img2name = argv[2];
    in_img2 = mo::imread_gray(img2name);
    if (in_img2.empty()) {
      cerr << "[ERROR] fail to read " << img2name << endl;
      return -1;
    }
  }

  // run SIFT
  mo::Sift sift;
  if (in_img2.empty()) {
    sift.detect(in_img);
  } else {
    sift.match(in_img, in_img2);
  }
  sift.show();

  return 0;
} catch (runtime_error &e) {
  cerr << "[ERROR] " << e.what() << endl;
} catch (...) {
  cerr << "[ERROR] Unkown error occureed!";
}
