#include "videostabilizer.hpp"
#include "../../image/src/imageprocess.hpp"
#include "../../linear_algebra/src/linear_transformation.hpp"
#include "../../video/src/video.hpp"
#include "../../visualization/src/visualization.hpp"

namespace mo {

VideoStabilizer::VideoStabilizer() {}

void VideoStabilizer::run(const mo::Image &image) {
  curr_img_ = image;

  // read gray image
  if (is_initial_frame_) {
    mo::ToGray(curr_img_, prev_gray_);

    // assume input image size is fixed.
    curr_img_.copyTo(dst_img_);

    is_initial_frame_ = false;
    return;
  }
  mo::ToGray(curr_img_, curr_gray_);

  calcFlow();

  compPrev2CurrFrameTransforms();

  curr_gray_.copyTo(prev_gray_);

  comp_stabcam_transform();

  mo::warpAffine(curr_img_, stabcam_transform_, dst_img_);
}

void VideoStabilizer::show() {
  mo::hconcat(curr_img_, dst_img_, comb_img_);
  mo::show("Before and After", comb_img_, 10);
}

void VideoStabilizer::calcFlow() {
  mo::goodFeaturesToTrack(prev_gray_, prev_pts_);

  mo::pyramidLK(prev_gray_, curr_gray_, prev_pts_, curr_pts_, statuses_);

  // Filter out invalid points
  auto prev_it = prev_pts_.begin();
  auto curr_it = curr_pts_.begin();
  for (auto status : statuses_) {
    if (status) {
      prev_it++;
      curr_it++;
    } else {
      prev_it = prev_pts_.erase(prev_it);
      curr_it = curr_pts_.erase(curr_it);
    }
  }
}

void VideoStabilizer::compPrev2CurrFrameTransforms() {
  mo::Transform2D transform;
  mo::estimate2DTransform(prev_pts_, curr_pts_, transform);

  // In case no transform is found, just use the previous transform.
  if (!transform.T().empty())
    prev2currframe_transform_ = transform;
}

void VideoStabilizer::comp_stabcam_transform() {
  cam_trajectory_.x += prev2currframe_transform_.dx();
  cam_trajectory_.y += prev2currframe_transform_.dy();
  cam_trajectory_.a += prev2currframe_transform_.da();

  // Calculate stabilizing camera transformations
  double dx = prev2currframe_transform_.dx() - cam_trajectory_.x;
  double dy = prev2currframe_transform_.dy() - cam_trajectory_.y;
  double da = prev2currframe_transform_.da() - cam_trajectory_.a;
  stabcam_transform_ = Transform2D(dx, dy, da);
}

} // namespace mo
