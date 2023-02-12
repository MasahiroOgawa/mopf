#ifndef IMAGEPROCESS_HPP
#define IMAGEPROCESS_HPP
#include "../../linear_algebra/src/linear_transformation.hpp"
#include "../../linear_algebra/src/matrix.hpp"
#include "../../linear_algebra/src/vector.hpp"
#include "../../image/src/image.hpp"

namespace mo {

void goodFeaturesToTrack(const mo::Image_gray &image,
                         std::vector<mo::Point2f> &corners,
                         const int max_corners = 200,
                         const double quality_level = 0.01,
                         const double minDistance = 30);

void hconcat(const Image &l_img, const Image &r_img, Image &concat_img);

void warpAffine(const mo::Image &in_img, const mo::Transform2D &transform,
                mo::Image &dst_img);

} // namespace mo
#endif // IMAGEPROCESS_HPP
