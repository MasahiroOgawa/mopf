#include "videostitcher.hpp"

namespace mo {

VideoStitcher::VideoStitcher() {}

void VideoStitcher::run(const Image &img) {
  extract_features();
  match_features();
  register_goodfeatures();
  comb_imgs();
}

void VideoStitcher::show() {}

void VideoStitcher::extract_features() {}

void VideoStitcher::match_features() {}

void VideoStitcher::register_goodfeatures() {}

void VideoStitcher::comb_imgs() {}

} // namespace mo
