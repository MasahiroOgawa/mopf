#include "linear_transformation.hpp"
#include <opencv2/calib3d.hpp>

namespace mo {

Transform2D::Transform2D(const double dx, const double dy, const double da)
    : dx_(dx), dy_(dy), da_(da) {
  T_.at<double>(0, 0) = cos(da_);
  T_.at<double>(0, 1) = -sin(da_);
  T_.at<double>(1, 0) = sin(da_);
  T_.at<double>(1, 1) = cos(da_);
  T_.at<double>(0, 2) = dx_;
  T_.at<double>(1, 2) = dy_;
}

Transform2D::Transform2D(const Matrix &T) : T_(T) {
  if (T.empty())
    return;
  dx_ = T.at<double>(0, 2);
  dy_ = T.at<double>(1, 2);
  da_ = std::atan2(T.at<double>(1, 0), T.at<double>(0, 0));
}

void estimate2DTransform(const std::vector<Point2f> &pts_from,
                         const std::vector<Point2f> &pts_to,
                         Transform2D &transform) {
  mo::Matrix T = cv::estimateAffine2D(pts_from, pts_to);
  transform = Transform2D(T);
}
} // namespace mo
