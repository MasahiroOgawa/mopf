#ifndef LINEAR_TRANSFORMATION_HPP
#define LINEAR_TRANSFORMATION_HPP
#include "matrix.hpp"
#include "vector.hpp"
#include <vector>

namespace mo {
class Transform2D {
public:
  Transform2D() {}
  Transform2D(const double dx, const double dy, const double da);
  Transform2D(const mo::Matrix &T);

  // getter
  double dx() const { return dx_; }
  double dy() const { return dy_; }
  double da() const { return da_; }
  mo::Matrix T() const { return T_; }

private:
  double dx_{0.0};
  double dy_{0.0};
  double da_{0.0};                        ///< angle
  mo::Matrix T_{mo::Matrix::zeros(2, 3)}; ///< =(R|t) 2x3 matrix.
};

void estimate2DTransform(const std::vector<Point2f> &pts_from,
                         const std::vector<Point2f> &pts_to,
                         Transform2D &transform);

} // namespace mo

#endif // LINEAR_TRANSFORMATION_HPP
