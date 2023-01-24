#ifndef VIDEO_HPP
#define VIDEO_HPP
#include "../../image/src/image.h"
#include "../../linear_algebra/src/vector.h" // for Point
#include <opencv2/videoio.hpp>               // for cv::VideoCapture

namespace mo {

///
///
///
using VideoCapture = cv::VideoCapture;

using VideoWriter = cv::VideoWriter;

void pyramidLK(const mo::Image_gray &prev_img, const mo::Image_gray &curr_img,
               const std::vector<mo::Point2f> &prev_pts,
               std::vector<mo::Point2f> &curr_pts,
               std::vector<unsigned char> &statuses);

} // namespace mo
#endif // VIDEO_HPP
