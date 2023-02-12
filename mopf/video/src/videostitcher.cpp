#include "videostitcher.hpp"

namespace mo {

VideoStitcher::VideoStitcher() {}

void VideoStitcher::run(const Image &img) {
  if (prev_img_.empty()) {
    mo::ToGray(img, prev_img_);
    return;
  }
  mo::ToGray(img, cur_img_);

  extract_features();
  match_features();
  register_goodfeatures();
  comb_imgs();
  prev_img_ = cur_img_;
}

void VideoStitcher::show() {
  if (!cur_img_.empty())
    sift_.show();
}

void VideoStitcher::extract_features() {}

void VideoStitcher::match_features() { sift_.match(prev_img_, cur_img_); }

void VideoStitcher::register_goodfeatures() {}

void VideoStitcher::comb_imgs() {}

} // namespace mo
