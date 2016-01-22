#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "../../linear_algebra/src/matrix.h"

namespace mo {

using Point = cv::Point2d;
void show(const std::string& winname, const Matrix& img, const int waitms=0);

} //namespace mo

#endif // VISUALIZATION_H

