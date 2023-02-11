#include "sift.hpp"
#include "../../visualization/src/visualization.hpp"

namespace mo {

Sift::Sift() { sift_ = cv::SIFT::create(); }

void Sift::detect(const Image_gray &img) {
  in_img_ = img;
  return;
}

void Sift::match(const Image_gray &img1, const Image_gray &img2) { return; }

int Sift::show() { return mo::show("result", in_img_, 0); }

} // namespace mo
