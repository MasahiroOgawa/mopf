#ifndef VIDEOSTABILIZER_HPP
#define VIDEOSTABILIZER_HPP
#include "../../image/src/image.h"
#include "../../image/src/imageprocess.hpp"
#include "../../linear_algebra/src/linear_transformation.hpp" // for Transform2D
#include "../../linear_algebra/src/vector.h"                  // for Point
#include <vector>

namespace mo {

class VideoStabilizer {
public:
  VideoStabilizer();
  void run(const mo::Image &image);
  void show();
  const mo::Image &comb_img() {
    if (comb_img_.empty())
      mo::hconcat(curr_img_, dst_img_, comb_img_);
    return comb_img_;
  }
  const mo::Image &dst_img() const { return dst_img_; }

  struct Trajectory {
    double x;
    double y;
    double a; // angle
  };

private:
  // functions
  void calcFlow();
  void compPrev2CurrFrameTransforms();
  void comp_stabcam_transform();

  // variables
  std::string in_videoname_{};
  std::string out_videoname_{};
  bool is_initial_frame_{true};
  mo::Image curr_img_{};
  mo::Image_gray curr_gray_{};
  mo::Image prev_img_{};
  mo::Image_gray prev_gray_{};
  mo::Transform2D
      prev2currframe_transform_; ///< interframe small transformations between
                                 ///< previous frame to cuurent. If we apply
                                 ///< this to camera, this can also be fixing
                                 ///< camera transformation.
  std::vector<mo::Point2f> prev_pts_;
  std::vector<mo::Point2f> curr_pts_;
  std::vector<unsigned char>
      statuses_{}; ///< point status. used for extracting valid points.
  Trajectory cam_trajectory_{0, 0, 0}; ///< camera trajectory computed from
                                       ///< cummurative transformations.
  Transform2D stabcam_transform_;
  mo::Image dst_img_{};
  mo::Image comb_img_{};
};

} // namespace mo
#endif // VIDEOSTABILIZER_H
