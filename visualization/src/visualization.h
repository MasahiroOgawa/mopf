#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "../../image/src/image.h"
#include "../../linear_algebra/src/matrix.h" //for warpaffine.
#include <iostream>
#include <opencv2/imgcodecs.hpp> //for cv::IMREAD_COLOR
#include <opencv2/imgproc.hpp>   //for ColormapTypes, arrowedLine()

namespace mo {
///
/// \brief imread
/// \param filename
/// \param flags
/// \return
///
Image imread(const std::string &filename, int flags = cv::IMREAD_COLOR);

/////////////////////////
/// \brief show
/// \param winname
/// \param img
/// \param waitms
/// \return pressed key as int. same with cv::waitKey's return value
/////////////////////////
int show(const std::string &winname, const Image &img, const int waitms = 0);
int show(const std::string &winname, const Image_gray &img,
         const int waitms = 0);

/////////////////////////
/// \brief destroy_window
/// \param winname
/////////////////////////
void destroy_window(const std::string &winname);

/////////////////////////
/// \brief line
/// draw line in img.
/////////////////////////
void line(const Point &pt_sta, const Point &pt_end, Image &img,
          const Color &color = Color{255, 255, 255});

/////////////////////////
/// \brief arrow
/// draw arrow in img.
/// \param pt_sta
/// \param pt_end
/// \param img
/// \param color
//////////////////////////
void arrow(const Point &pt_sta, const Point &pt_end, Image &img,
           const Color &color = Color{255, 255, 255});

//////////////////////////
/// \brief point
/// draw point in img.
//////////////////////////
void point(const Point &pt, Image &img,
           const Color &color = Color{255, 255, 255}, const int radius = 1);

//////////////////////////
/// \brief text
/// draw text in img.
//////////////////////////
void text(const std::string &text, Image &img, const Point &org,
          const double &scale = 1.0, const Color &color = Color{255, 255, 255});

using ColormapTypes = cv::ColormapTypes;

//////////////////////////
/// \brief colorbar
/// \param img
/// \param colormaptype
//////////////////////////
void colorbar(Image &img, const ColormapTypes colormaptype);

void warpAffine(Image src, Image dst, Matrix M);

} // namespace mo

#endif // VISUALIZATION_H
