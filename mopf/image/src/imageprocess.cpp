#include "imageprocess.hpp"
#include <opencv2/imgproc.hpp>

namespace mo {

void goodFeaturesToTrack(const Image_gray &image,
                         std::vector<mo::Point2f> &corners,
                         const int max_corners, const double quality_level,
                         const double minDistance) {
  cv::goodFeaturesToTrack(image, corners, max_corners, quality_level,
                          minDistance);
}

void warpAffine(const Image &in_img, const Transform2D &transform,
                Image &dst_img) {
  cv::warpAffine(in_img, dst_img, transform.T(), dst_img.size(),
                 cv::INTER_LINEAR, cv::BORDER_TRANSPARENT);
}

} // namespace mo
