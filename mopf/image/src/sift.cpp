#include "sift.hpp"
#include "../../visualization/src/visualization.hpp"

namespace mo {

Sift::Sift() { sift_ = cv::SIFT::create(); }

void Sift::detect(const Image_gray &img) {
  in_img_ = img;

  sift_->detectAndCompute(in_img_, cv::noArray(), keypoints_, descriptors_);
  return;
}

void Sift::match(const Image_gray &img1, const Image_gray &img2) { return; }

int Sift::show() {
  cv::drawKeypoints(in_img_, keypoints_, result_img_);
  return mo::show("SIFT result", result_img_, 0);
}

} // namespace mo
