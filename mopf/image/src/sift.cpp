#include "sift.hpp"

namespace mo {

Sift::Sift() { sift_ = cv::SIFT::create(); }

void Sift::detect(const Image_gray &img) { return; }

void Sift::match(const Image_gray &img1, const Image_gray &img2) { return; }

} // namespace mo
