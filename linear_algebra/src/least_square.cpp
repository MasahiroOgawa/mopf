#include "least_square.h"
#include <sstream>
#include <iostream>
using namespace std;

namespace mo {

void polynomial_curvefit(const Matrix& x, const Matrix& y, Matrix& c, const int& degree, const std::vector<double>& weight){
    if(x.rows != y.rows){
        ostringstream errmsg;
        errmsg << "the number of x.rows = " << x.rows << " and y.rows = " << y.rows << " must be the same @least_squarefit";
        throw runtime_error(errmsg.str());
    }
    Matrix X;
    hconcat(Matrix::ones(x.rows, 1), x, X);
    if(degree < 1) throw runtime_error("degree of polynomial must be larger than 1. @mo::polynomial_curvefit()");
    Matrix xpow_n; //if we define "xpow_n = x", and if the content of x is stl vector, we happeningly change the contents of x, though the pointer will not be changed.
    x.copyTo(xpow_n); //so we copy x to another Matrix xpow_n.
    for(int i=1; i<degree; ++i){
        xpow_n = xpow_n.mul(x);
        hconcat(X, xpow_n, X);
    }

    //compute weight matrix W and H.
    vector<double> w{1};
    if(weight==w){
        for(int i=1; i<x.rows; ++i) w.push_back(i);
    }else if(weight.size() != x.rows){
        throw runtime_error("weight size must be the same with input data x's size. @polynomial_curvefit()");
    }else
        w = weight;
    Matrix W = diag(Matrix(w));
    Matrix H = W.t() * W;

    c = (X.t() * H * X).inv() * X.t() * H * y;
}

} //namespace mo
