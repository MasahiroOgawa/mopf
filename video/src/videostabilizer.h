#ifndef VIDEOSTABILIZER_H
#define VIDEOSTABILIZER_H
#include <opencv2/core.hpp>
#include <vector>

namespace mo {

class VideoStabilizer {
public:
  VideoStabilizer(const std::string &in_videoname,
                  const std::string &out_videoname = "out.mp4");
  void run();
  struct Transform {
    double dx;
    double dy;
    double da; // angle

    void getTransform(cv::Mat &T) {
      T.at<double>(0, 0) = cos(da);
      T.at<double>(0, 1) = -sin(da);
      T.at<double>(1, 0) = sin(da);
      T.at<double>(1, 1) = cos(da);
      T.at<double>(0, 2) = dx;
      T.at<double>(1, 2) = dy;
    }
  };

  struct Trajectory {
    double x;
    double y;
    double a; // angle
  };

private:
  // functions
  std::vector<Trajectory> cumsum(std::vector<Transform> &transforms);
  /// upscale k% fixing the center.
  void enlargeImage(cv::Mat &frame_stabilized, float k = 1.05);

  // variables
  std::string in_videoname_;
  std::string out_videoname_;
};

} // namespace mo
#endif // VIDEOSTABILIZER_H
