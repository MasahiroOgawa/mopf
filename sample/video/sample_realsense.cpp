#include "mopf/video/src/video.hpp"
#include "mopf/visualization/src/visualization.hpp"

int main() {
  mo::Image in_img;
  mo::VideoCapture cap(cv::CAP_INTELPERC);

  while (1) {
    cap.grab();
    cap.retrieve(in_img, cv::CAP_INTELPERC_IMAGE);

    int key = mo::show("realsense", in_img, 10);
    if (key == 'q')
      break;
  }

  return 0;
}
