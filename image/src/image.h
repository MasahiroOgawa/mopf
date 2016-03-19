#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/core.hpp>

namespace mo {

////////////////////////
/// \brief Point
////////////////////////
using Point = cv::Point2d;


////////////////////////
/// \brief Rect
////////////////////////
using Rect = cv::Rect;


////////////////////////
/// \brief The Color struct
////////////////////////
struct Color{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    Color(const unsigned char r, const unsigned char g, const unsigned char b):red{r},green{g},blue{b}{}
    cv::Vec3b pixval()const{return cv::Vec3b{blue,green,red};}
};

std::ostream& operator<<(std::ostream& os, const Color& col);


////////////////////////
/// \brief Image
////////////////////////
using Image = cv::Mat_<cv::Vec3b>; //color image
using Image_gray = cv::Mat_<unsigned char>; //gray image

} // namespace mo
#endif // IMAGE_H
