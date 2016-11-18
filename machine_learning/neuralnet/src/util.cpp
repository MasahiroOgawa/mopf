#include "util.h"
#include <stdexcept>

using namespace std;

namespace Util{

  /**
 * @brief Util::delete_col
 * delete the column (0 starting index) in mat M.
 * output M is continuous.
 * @param col
 * @param M
 */
  void delete_col(const int col, cv::Mat& M){
    cv::Mat newM;
    if(col<0 || col>M.cols-1)
      throw range_error("0 starting index col="+to_string(col)+" is outside of M's cols="+to_string(M.cols)+" @Util::delete_col()");
    else if(col==0){ //separate this case because hconcat output error.
      newM = M.colRange(1, M.cols);
    }else{
      newM = M.colRange(0,col);
      if(col != M.cols-1){
        cv::Mat newM_tail = M.colRange(col+1, M.cols);
        cv::hconcat(newM, newM_tail, newM);
      }
    }
    M = newM.clone(); //to make ouput M continuous.
#ifdef DEBUG_
    cout << "M = " << M
         << "\nnewM= " << newM << endl;
#endif
  }


  void delete_row(const int row, cv::Mat& M){
    cv::Mat newM;
    if(row<0 || row>M.rows-1)
      throw range_error("0 starting index row="+to_string(row)+" is outside of M's rows="+to_string(M.rows)+" @Util::delete_row()");
    else if(row==0){ //separate this case because vconcat output error.
      newM = M.rowRange(1, M.rows);
    }else{
      newM = M.rowRange(0,row);
      if(row != M.rows-1){
        cv::Mat newM_tail = M.rowRange(row+1, M.rows);
        cv::vconcat(newM, newM_tail, newM);
      }
    }
    M = newM.clone(); //to make ouput M continuous.
  }


  bool is_valid(const cv::Mat_<double>& M){
    for(int r=0; r<M.rows; ++r){
      const double* Mr = M.ptr<double>(r);
      for(int c=0; c<M.cols; ++c){
        if(Mr[c] * 0.0 != 0.0) return false;
      }
    }
    return true;
  }

//-----------------------------------------------------
  void minmax_eachrow(const cv::Mat_<double>& M, cv::Mat_<double>& Minmax){
    for(int i=0; i<M.rows; ++i){
      const double* Mi = M.ptr<double>(i);
      double minval = Mi[0];
      double maxval = Mi[0];
      for(int j=1; j<M.cols; ++j){
        if(Mi[j] < minval)
          minval = Mi[j];
        else if(Mi[j] > maxval)
          maxval = Mi[j];
      }
      cv::Mat Minmax_i = (cv::Mat_<double>(1,2) << minval,maxval);
      Minmax.push_back(Minmax_i);
    }
  }

} //namespace Util
