#include "../../analysis/src/analysis.h" //for sgn()
#include "hill_climbing.h"

namespace mo {

template<typename F1, typename F2> double Hill_climbing::linear_search(F1 f, F2 df, const double& x0){
    //init variables
    double step = step0_;
    double x = x0;
    if(opt_vis_){
        linsearch_vis_.clear();
        linsearch_vis_.record(x,f(x),df(x)); //record initial point.
        linsearch_vis_.show_optimization(); //we have to call this because comp_minmax assume input points was initially size 1.
    }

    //search until |df(x)/dx| ~ 0
    double dfx = df(x);
    while(fabs(dfx) > thre_df_){
        int loop_count{0};
        //init x_next
        step = sgn(dfx) * fabs(step);
        double x_next = x + step;

        if(f(x) < f(x_next)){ //in case f(x_next) does not yet reached the neighborhood of maximal
            while(f(x) < f(x_next)){ //loop until over maximal
                step *= 2.0;
                x = x_next;
                x_next = x + step;
                check_loopcount(++loop_count);
            }
            step /= 2.0;
        }else{ //in case f(x_next) over the neighborhood of maximal
            while(f(x) >= f(x_next)){ //loop until it finds
                step /= 2.0;
                x_next -= step;
                check_loopcount(++loop_count);
            }
            x = x_next;
            step *= 2.0;
        }

        if(opt_vis_){
            linsearch_vis_.record(x,f(x),df(x));
            linsearch_vis_.show_optimization(); //note: until minx!=maxx && miny!=maxy, it will not display image.
        }

        //update
        dfx = df(x);
    }

    return x;
}

} //namespace mo
