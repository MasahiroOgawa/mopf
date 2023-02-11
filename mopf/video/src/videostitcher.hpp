#ifndef VIDEOSTITCHER_HPP
#define VIDEOSTITCHER_HPP
#include "../../image/src/image.hpp"

namespace mo {

class VideoStitcher {
public:
  VideoStitcher();
  void run(const mo::Image &img);
  void show();
  mo::Image result_img() const { return result_img_; }

private:
  void extract_features();
  void match_features();
  void register_goodfeatures();
  void comb_imgs();

  mo::Image result_img_;
};

} // namespace mo

#endif // VIDEOSTITCHER_HPP
