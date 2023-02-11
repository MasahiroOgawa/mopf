#ifndef SIFT_HPP
#define SIFT_HPP

#include "image.hpp"
#include <opencv2/xfeatures2d.hpp>
#include <vector>

namespace mo {

class Sift {
public:
  Sift();
  void detect(const mo::Image_gray &img);
  void match(const mo::Image_gray &img1, const mo::Image_gray &img2);
  int show();

private:
  void reset() { keypoints_.clear(); }

  mo::Image_gray in_img_{};
  std::vector<cv::KeyPoint> keypoints_{};
  cv::Ptr<cv::SIFT> sift_{};
  cv::Mat descriptor_{}; ///< histogram of each 3 channel Mat[row,col,octave]
};

} // namespace mo

#endif // SIFT_HPP
