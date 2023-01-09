#include "video.hpp"
#include <opencv2/video/tracking.hpp>

namespace mo {
void pyramidLK(const Image_gray &prev_img, const Image_gray &curr_img,
               const std::vector<Point2f> &prev_pts,
               std::vector<Point2f> &curr_pts,
               std::vector<unsigned char> &statuses) {
  std::vector<float>
      errs{}; // currently, we don't use errors, so slow away this.
  cv::calcOpticalFlowPyrLK(prev_img, curr_img, prev_pts, curr_pts, statuses,
                           errs);
}

} // namespace mo
