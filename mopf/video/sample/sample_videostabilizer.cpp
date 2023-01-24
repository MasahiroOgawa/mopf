#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <mopf/image/src/image.h>
#include <mopf/video/src/video.hpp>
#include <mopf/video/src/videostabilizer.hpp>

int main(int argc, char **argv) {
  // treat arguments
  if (argc < 2) {
    std::cout << "Usage: " << argv[0]
              << " input_video_filename [output_video_filename]\n";
    return 1;
  }
  std::string in_videoname = argv[1];
  std::string out_videoname = (argc > 2) ? argv[2] : "out.mp4";

  // prepare for input
  mo::VideoCapture cap(in_videoname);
  if (!cap.isOpened()) {
    std::cerr << "[ERROR] Unable to open " << in_videoname << std::endl;
    return -1;
  }
  int img_w = int(cap.get(cv::CAP_PROP_FRAME_WIDTH));
  int img_h = int(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
  int fps = cap.get(cv::CAP_PROP_FPS);
  mo::Image image;

  // prepare for output
  mo::VideoWriter out(out_videoname,
                      mo::VideoWriter::fourcc('M', 'P', '4', 'V'), fps,
                      cv::Size(2 * img_w, img_h));

  // prepare for processing
  mo::VideoStabilizer vstab;

  // image loop
  while (1) {
    cap >> image;
    if (image.empty())
      break;
    vstab.run(image);
    vstab.show();
  }

  // post process
  cap.release();
  out.release();
  return 0;
}
