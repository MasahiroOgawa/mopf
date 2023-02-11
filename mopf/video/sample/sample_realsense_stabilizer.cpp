#include "mopf/video/src/video.hpp"
#include "mopf/video/src/videostabilizer.hpp"
#include "mopf/visualization/src/visualization.hpp"

int main() {
  mo::Image in_img;
  mo::VideoCapture cap(cv::CAP_INTELPERC);
  mo::VideoStabilizer vstab;

  while (1) {
    cap.grab();
    cap.retrieve(in_img, cv::CAP_INTELPERC_IMAGE);

    vstab.run(in_img);
    vstab.show();
  }

  cap.release();
  return 0;
}
