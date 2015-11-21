#include "matrix.h"


namespace mo {

void hconcat(const Matrix& A, const Matrix& B, Matrix& C){
    cv::hconcat(A,B,C);
}

Matrix diag(const Matrix& D){
    return cv::Mat::diag(D);
}

void log(const Matrix& S, Matrix& D){
    cv::log(S, D);
}

void add(const Matrix& S, const double& val, Matrix& D){
    cv::add(S,val,D);
}

}
