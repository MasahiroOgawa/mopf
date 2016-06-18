#ifndef MATRIX_H
#define MATRIX_H
#include <opencv2/core.hpp>

namespace mo {

using Matrix = cv::Mat_<double>;

void hconcat(const Matrix& A, const Matrix& B, Matrix& C);
Matrix diag(const Matrix& D);
void log(const Matrix& S, Matrix& D);
void add(const Matrix& S, const double& val, Matrix& D);

} //namespace mo
#endif // MATRIX_H
