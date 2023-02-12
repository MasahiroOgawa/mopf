#ifndef VIDEOSTITCHER_HPP
#define VIDEOSTITCHER_HPP
#include "../../../mopf/image_process/src/sift.hpp"
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

  // variables
  mo::Image_gray prev_img_{};
  mo::Image_gray cur_img_{};
  mo::Sift sift_{};
  mo::Image result_img_{};
};

} // namespace mo

#endif // VIDEOSTITCHER_HPP
