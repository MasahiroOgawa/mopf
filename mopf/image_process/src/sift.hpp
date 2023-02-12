#ifndef SIFT_HPP
#define SIFT_HPP

#include "../../../mopf/image/src/image.hpp"
#include <opencv2/xfeatures2d.hpp>
#include <vector>

namespace mo {

class Sift {
public:
  Sift();
  void detect(const mo::Image_gray &img);
  void match(const mo::Image_gray &img1, const mo::Image_gray &img2);
  int show(int waitms = 0);

private:
  void reset() { keypoints_.clear(); }
  void filter_matches();

  // consts
  static constexpr int num_keep_bestmatch_{2};
  static constexpr float thre_Lowe_ratio_{0.7};

  // variables
  cv::Ptr<cv::SIFT> sift_{};
  mo::Image_gray in_img_{};
  std::vector<cv::KeyPoint> keypoints_{};
  cv::Mat descriptors_{}; ///< histogram of each 3 channel Mat[row,col,octave]
  mo::Image result_img_{};

  // match case
  cv::Ptr<cv::DescriptorMatcher> matcher_{};
  std::vector<std::vector<cv::DMatch>>
      raw_matches_{}; ///< raw matches, that keeps 1,2,...,num_keep_bestmatch_
                      ///< best matches.
  std::vector<cv::DMatch>
      filtered_matches_{}; ///< only keep filtered best matches.
  mo::Image_gray in_img2_{};
  std::vector<cv::KeyPoint> keypoints2_{};
  cv::Mat descriptors2_{};
};

} // namespace mo

#endif // SIFT_HPP
