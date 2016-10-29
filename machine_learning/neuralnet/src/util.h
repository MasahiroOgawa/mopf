#ifndef UTIL_H
#define UTIL_H
#include <opencv2/core.hpp>

class Util
{
public:
  Util();
  void delete_col(const int col, cv::Mat& M);
  void delete_row(const int row, cv::Mat& M);


  ////////////////////////
  /// \brief is_valid
  /// return false if input Mat has at least 1 Nan value, other wise it returns true.
  /// \param M
  /// \return
  ////////////////////////
  bool is_valid(const cv::Mat_<double>& M);
};

#endif // UTIL_H
