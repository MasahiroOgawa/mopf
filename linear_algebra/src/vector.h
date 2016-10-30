#ifndef VECTOR_H
#define VECTOR_H
#include <opencv2/core.hpp>

namespace mo {
template<int n> using Vector = cv::Vec<double,n>; //opencv only support specific dimension vector.


///
/// \brief distance
/// return L2 norm of 2 stl vectors
/// \param v1
/// \param v2
/// \return
///
double distance(const std::vector<unsigned char>& v1, const std::vector<unsigned char>& v2);
}

#endif // VECTOR_H
