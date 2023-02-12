#include "videostitcher.hpp"

namespace mo {

VideoStitcher::VideoStitcher() {}

void VideoStitcher::run(const Image &img) {
  if (is_initial_img_) {
    prev_img_ = img;
    is_initial_img_ = false;
    return;
  }
  cur_img_ = img;

  extract_features();
  match_features();
  register_goodfeatures();
  comb_imgs();
}

void VideoStitcher::show() { sift_.show(); }

void VideoStitcher::extract_features() {}

void VideoStitcher::match_features() { sift_.match(prev_img_, cur_img_); }

void VideoStitcher::register_goodfeatures() {}

void VideoStitcher::comb_imgs() {}

} // namespace mo
