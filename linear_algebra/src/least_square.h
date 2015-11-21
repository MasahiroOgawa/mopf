#ifndef LEAST_SQUARE_H
#define LEAST_SQUARE_H
#include "matrix.h"

namespace mo {

/**
 * @brief polynomial_curvefit
 * @param x
 * @param y
 * @param c
 * @param degree : degree of polynomial
 * @param weight : weight for each x data. default is 1,...,1
 * solve WXc=y s.t. W=diag(weight), X=(1,x,x^2,...,x^degree), x:input data, y:corresponding output data, c:coefficients for c0 + c1*x + ... + cdeg*x^deg = y.
 */
void polynomial_curvefit(const Matrix& x, const Matrix& y, Matrix& c,
                         const int& degree = 1, const std::vector<double>& weight = {1});

}

#endif // LEAST_SQUARE_H
