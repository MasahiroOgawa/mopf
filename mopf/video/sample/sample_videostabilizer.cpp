#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <mopf/image/src/image.h>
#include <mopf/video/src/video.hpp>
#include <mopf/video/src/videostabilizer.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

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
  int img_w = int(cap.get(cv::CAP_PROP_FRAME_WIDTH));
  int img_h = int(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
  int fps = cap.get(cv::CAP_PROP_FPS);
  mo::Image image;

  // prepare for output
  cv::VideoWriter out(out_videoname,
                      cv::VideoWriter::fourcc('M', 'P', '4', 'V'), fps,
                      cv::Size(2 * img_w, img_h));

  // prepare for processing
  mo::VideoStabilizer vstab;
  vstab.init(img_w, img_h, fps);

  // image loop
  while (1) {
    cap >> image;
    if (image.empty())
      break;
    vstab.run(image);
  }

  // post process
  cap.release();
  out.release();
  cv::destroyAllWindows();
  return 0;
}

void enlargeImage(mo::Image &frame_stabilized, float k) {
  mo::Matrix T = cv::getRotationMatrix2D(
      cv::Point2f(frame_stabilized.cols / 2, frame_stabilized.rows / 2), 0, k);
  cv::warpAffine(frame_stabilized, frame_stabilized, T,
                 frame_stabilized.size());
}
