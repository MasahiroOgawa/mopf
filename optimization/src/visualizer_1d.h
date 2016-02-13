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
    /// \param dfx: differential value df(x)
    ////////////////////
    void record(const double& x, const double& y, const double& dfx);


    ////////////////////
    /// \brief clear
    ////////////////////
    void clear();

private:
    ////////////////////
    /// \brief comp_minmax
    /// check only newly added point is min or max
    ////////////////////
    void comp_minmax();


    ////////////////////
    /// \brief draw_axis
    ////////////////////
    void draw_axis();


    ////////////////////
    /// \brief draw_arrow
    ////////////////////
    void draw_arrow();


    ////////////////////
    /// \brief draw_pts
    ////////////////////
    void draw_pts();


    ////////////////////
    /// \brief map_to_display
    /// map input point into display image "img_" by scaling and translate it.
    /// \param pt
    /// \return
    ////////////////////
    Point map_to_display(const Point& pt);


    ////////////////////
    /// \brief clear_img
    ////////////////////
    void clear_img();

    Image img_;
    int img_w_;
    int img_h_;
    std::vector<Point> pts_;
    std::vector<double> dfxs_;
    double min_x_; //to define draw area
    double min_y_;
    double max_x_;
    double max_y_;
    Color bg_color_;
};

} //namespace mo

#endif // VISUALIZER_1D_H
