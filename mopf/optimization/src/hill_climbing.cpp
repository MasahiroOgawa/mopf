#include "hill_climbing.hpp"
#include "../../analysis/src/analysis.hpp" //for sgn()
#include <cmath>                           //for fabs()
#include <iostream>
using namespace std;

namespace mo {

Hill_climbing::Hill_climbing(const double &step0, const double &thre_df,
                             const double &thre_dx, const int &max_loopcount,
                             bool opt_vis)
    : step0_{step0}, thre_df_{thre_df}, thre_dx_{thre_dx},
      max_loopcount_{max_loopcount}, viswin_w_{512}, viswin_h_{512},
      linsearch_vis_{viswin_w_, viswin_h_}, opt_vis_{opt_vis} {}

void Hill_climbing::compute(double (*f)(const Matrix &),
                            Matrix (*df)(const Matrix &), const Matrix &x0) {
  // initialize
  int loop_count{0};
  x_ = x0;
  Matrix dx =
      (thre_dx_ + 1.0) *
      Matrix::ones(x_.size()); // any value is OK if it is larger than thre_dx_.

  while (norm(dx) > thre_dx_) {
    auto F = [f, df, this](const double &t) { return f(x_ + t * df(x_)); };
    auto dF = [df, this](const double &t) {
      cv::Mat_<double> Dfdf(df(x_ + t * df(x_)).t() * df(x_));
      return Dfdf.at<double>(0, 0);
    };

    double t = linear_search(
        F, dF,
        0.0); // 0.0 means t=0.0, so starting from the corresting point of x_.
    dx = t * df(x_);
    x_ += dx;
    check_loopcount(
        ++loop_count); // to do: we have to change this to finish condition.
  }
}

void Hill_climbing::check_loopcount(const int loop_count) {
  if (loop_count > max_loopcount_) {
    std::string errmsg =
        "@Hill_climbing::check_loopcount(): loop count=" +
        std::to_string(loop_count) +
        " is over max_loopcount=" + std::to_string(max_loopcount_);
    throw std::overflow_error(errmsg);
  }
}

} // namespace mo
