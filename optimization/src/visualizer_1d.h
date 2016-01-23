#ifndef VISUALIZER_1D_H
#define VISUALIZER_1D_H
#include "../../linear_algebra/src/matrix.h"
#include "../../visualization/src/visualization.h"

namespace mo {

class Visualizer_1d
{
public:
    Visualizer_1d(const int img_w=255, const int img_h=255);
    void show_optimization();

    ////////////////////
    /// \brief record
    /// \param x : variable
    /// \param y : output value of f(x)
    ////////////////////
    void record(const double& x, const double& y);

private:
    ////////////////////
    /// \brief comp_minmax
    /// check only newly added point is min or max
    ////////////////////
    void comp_minmax();

    ////////////////////
    /// \brief draw_arrow
    ////////////////////
    void draw_arrow();

    Matrix img_;
    int img_w_;
    int img_h_;
    std::vector<Point> pts_;
    double min_x_; //to define draw area
    double min_y_;
    double max_x_;
    double max_y_;
};

} //namespace mo

#endif // VISUALIZER_1D_H
