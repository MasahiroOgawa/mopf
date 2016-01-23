#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "../../linear_algebra/src/matrix.h"

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
};

std::ostream& operator<<(std::ostream& os, const Color& col);


/////////////////////////
/// \brief show
/// \param winname
/// \param img
/// \param waitms
/////////////////////////
void show(const std::string& winname, const Matrix& img, const int waitms=0);


/////////////////////////
/// \brief arrow
/// \param pt_sta
/// \param pt_end
/// \param img
/// \param color
//////////////////////////
void arrow(const Point& pt_sta, const Point& pt_end, Matrix& img, const Color& color);

} //namespace mo

#endif // VISUALIZATION_H

