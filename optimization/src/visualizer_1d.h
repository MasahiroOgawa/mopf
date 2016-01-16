#ifndef VISUALIZER_1D_H
#define VISUALIZER_1D_H
#include <opencv2/core.hpp>

class Visualizer_1d
{
public:
    Visualizer_1d(const int img_w=255, const int img_h=255);
    void show();

    ////////////////////
    /// \brief record
    /// \param x : variable
    /// \param y : output value of f(x)
    ////////////////////
    void record(const double& x, const double& y);

private:
    cv::Mat img_;
    int img_w_;
    int img_h_;
    std::vector<cv::Point2d> pts_;
};

#endif // VISUALIZER_1D_H
