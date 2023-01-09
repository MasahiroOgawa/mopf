#ifndef UTIL_H
#define UTIL_H
#include <opencv2/core.hpp>

namespace Util
{
  void delete_col(const int col, cv::Mat& M);
  void delete_row(const int row, cv::Mat& M);


  ////////////////////////
  /// \brief is_valid
  /// return false if input Mat has at least 1 Nan value, other wise it returns true.
  /// \param M
  /// \return
  ////////////////////////
  bool is_valid(const cv::Mat_<double>& M);


  /////////////////////////
  /// \brief minmax_eachrow
  /// output matrix Minmax = (min of row0, max of row0; min of row1, max of row1, ...)
  /// \param M
  /// \param Minmax
  /////////////////////////
  void minmax_eachrow(const cv::Mat_<double>& M, cv::Mat_<double>& Minmax); //It cannot be used template because M.ptr<T> is not allowed.

} //namespace Util

#endif // UTIL_H
