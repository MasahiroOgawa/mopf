#include "sift.hpp"
#include "../../../mopf/visualization/src/visualization.hpp"

namespace mo {

Sift::Sift() {
  sift_ = cv::SIFT::create();
  matcher_ = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
}

void Sift::detect(const Image_gray &img) {
  in_img_ = img;

  sift_->detectAndCompute(in_img_, cv::noArray(), keypoints_, descriptors_);
  return;
}

void Sift::match(const Image_gray &img1, const Image_gray &img2) {
  // init
  keypoints_.clear();
  keypoints2_.clear();
  descriptors_.release();
  descriptors2_.release();
  raw_matches_.clear();
  filtered_matches_.clear();

  in_img_ = img1;
  in_img2_ = img2;

  sift_->detectAndCompute(in_img_, cv::noArray(), keypoints_, descriptors_);
  sift_->detectAndCompute(in_img2_, cv::noArray(), keypoints2_, descriptors2_);

  matcher_->knnMatch(descriptors_, descriptors2_, raw_matches_,
                     num_keep_bestmatch_);
  filter_matches();

  return;
}

void Sift::filter_matches() {
  for (const auto &raw_match : raw_matches_) {
    if (raw_match[0].distance < thre_Lowe_ratio_ * raw_match[1].distance) {
      filtered_matches_.push_back(raw_match[0]);
    }
  }
}

int Sift::show(int waitms) {
  if (filtered_matches_.empty()) {
    cv::drawKeypoints(in_img_, keypoints_, result_img_);
  } else {
    cv::drawMatches(in_img_, keypoints_, in_img2_, keypoints2_,
                    filtered_matches_, result_img_, cv::Scalar::all(-1),
                    cv::Scalar::all(-1), std::vector<char>(),
                    cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
  }

  return mo::show("SIFT", result_img_, waitms);
}

} // namespace mo
