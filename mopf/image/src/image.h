#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/core.hpp>

namespace mo {

////////////////////////
/// \brief Rect
////////////////////////
using Rect = cv::Rect;

////////////////////////
/// \brief The Color struct
////////////////////////
struct Color {
  unsigned char red;
  unsigned char green;
  unsigned char blue;

  Color(const unsigned char r, const unsigned char g, const unsigned char b)
      : red{r}, green{g}, blue{b} {}
  cv::Vec3b pixval() const { return cv::Vec3b{blue, green, red}; }
};

std::ostream &operator<<(std::ostream &os, const Color &col);

////////////////////////
/// \brief Image
////////////////////////
template <typename T> using Image_ = cv::Mat_<T>;
using Image = Image_<cv::Vec3b>;          // color image
using Image_gray = Image_<unsigned char>; // gray

///
/// \brief ToGray
/// \param color
/// \param gray
/// Convert color image to gray image.
void ToGray(const Image &color, Image_gray &gray);

} // namespace mo
#endif // IMAGE_H
