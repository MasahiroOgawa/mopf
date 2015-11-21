#ifndef HILL_CLIMBING_H
#define HILL_CLIMBING_H
#include "../../linear_algebra/src/matrix.h"

namespace mo {

/////////////////
/// \brief The Hill_climbing class
/// based on "これなら分かる最適化数学　金谷健一" p.81
/////////////////
class Hill_climbing
{
public:
    Hill_climbing(const double& h0, const double& eps, const double& delta);
    void compute();


    /////////////////////
    /// \brief x
    /// return the final result; maximal point x of f()
    /// \return
    /////////////////////
    Matrix x()const{return x_;}


    ////////////////////
    /// \brief linear_search
    /// find a maximal for 1-dim funtion f(x)
    /// \param x0
    /// \return
    ////////////////////
    double linear_search(double (*f)(const double&), double(*df)(const double&), const double& x0);

private:
    double h0_;
    double eps_;
    double delta_;
    Matrix x_; //vector of current point
};

} //namespace mo

#endif // HILL_CLIMBING_H
