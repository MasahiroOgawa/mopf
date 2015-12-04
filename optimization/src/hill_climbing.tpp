#include "../../analysis/src/analysis.h" //for sgn()
#include "hill_climbing.h"

namespace mo {

template<typename F1, typename F2> double Hill_climbing::linear_search(F1 f, F2 df, const double& x0){
    double h = h0_;
    double x = x0;

    //search until |df(x)| ~ 0
    while(fabs(df(x)) > eps_){
        int loop_count{0};
        //init x_next
        h = sgn(df(x)) * fabs(h);
        double x_next = x + h;

        if(f(x) < f(x_next)){ //in case f(x_next) does not yet reached the neighborhood of maximal
            while(f(x) < f(x_next)){ //loop until over maximal
                h *= 2.0;
                x = x_next;
                x_next = x + h;
                check_loopcount(++loop_count);
            }
            h /= 2.0;
        }else{ //in case f(x_next) over the neighborhood of maximal
            while(f(x) >= f(x_next)){ //loop until it finds
                h /= 2.0;
                x_next -= h;
                check_loopcount(++loop_count);
            }
            x = x_next;
            h *= 2.0;
        }
    }

    return x;
}

} //namespace mo
