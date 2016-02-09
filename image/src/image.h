#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/core.hpp>

namespace mo {

////////////////////////
/// \brief Point
////////////////////////
using Point = cv::Point2d;


////////////////////////
/// \brief The Color struct
////////////////////////
struct Color{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    Color(const unsigned char r, const unsigned char g, const unsigned char b):red{r},green{g},blue{b}{}
    cv::Scalar pixval()const{return cv::Scalar{blue/255.0,green/255.0,red/255.0};}
};

std::ostream& operator<<(std::ostream& os, const Color& col);


////////////////////////
/// \brief Image
////////////////////////
using Image = cv::Mat_<cv::Scalar>; //color image
using Image_gray = cv::Mat_<unsigned char>; //gray image

} // namespace mo
#endif // IMAGE_H
