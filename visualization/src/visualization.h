#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "../../image/src/image.h"

namespace mo {

/////////////////////////
/// \brief show
/// \param winname
/// \param img
/// \param waitms
/////////////////////////
void show(const std::string& winname, const Image& img, const int waitms=0);


/////////////////////////
/// \brief arrow
/// \param pt_sta
/// \param pt_end
/// \param img
/// \param color
//////////////////////////
void arrow(const Point& pt_sta, const Point& pt_end, Image& img, const Color& color);

} //namespace mo

#endif // VISUALIZATION_H
