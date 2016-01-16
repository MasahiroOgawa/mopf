#ifndef HILL_CLIMBING_H
#define HILL_CLIMBING_H
#include "../../linear_algebra/src/matrix.h"
#include <functional> //for std::function
#include "visualizer_1d.h"

namespace mo {

/////////////////
/// \brief The Hill_climbing class
/// based on "これなら分かる最適化数学　金谷健一" p.81
/////////////////
class Hill_climbing
{
public:
    /////////////////////
    /// \brief Hill_climbing
    /// \param step0 : initial step value. x(1)=x(0)+step0.
    /// \param thre_df : linear search's tolerance. It will judge convergence if |f'(x)| < thre_df.
    /// \param thre_dx : multi dimentional hill climbing's convergence threshold. It will judge convergence if |dx| < thre_dx.
    /// \param max_loopcount
    /// \param opt_vis :
    /////////////////////
    Hill_climbing(const double& step0, const double& thre_df, const double& thre_dx, const int& max_loopcount=1e+8, bool opt_vis=true);


    /////////////////////
    /// \brief compute
    /// compute hill climbing for multi variate function f(x); x is vector.
    /// \param x0
    /////////////////////
    void compute(double (*f)(const Matrix&), Matrix (*df)(const Matrix&), const Matrix& x0);


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
    template<typename F1, typename F2> double linear_search(F1 f, F2 df, const double& x0);

private:
    /////////////////////
    /// \brief check_loopcount
    /// check the loop count and if it is over max_loopcount_, this will throw overflow_error.
    /// \param loop_count
    /////////////////////
    void check_loopcount(const int loop_count);

    double step0_;
    double thre_df_;
    double thre_dx_;
    int max_loopcount_;
    Matrix x_; //vector of current point
    Visualizer_1d linsearch_vis_;
    bool opt_vis_;
};

} //namespace mo

#include "hill_climbing.tpp"

#endif // HILL_CLIMBING_H
