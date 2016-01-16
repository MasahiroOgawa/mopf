#ifndef VISUALIZER_1D_H
#define VISUALIZER_1D_H
#include <opencv2/core.hpp>

class Visualizer_1d
{
public:
    Visualizer_1d(const int img_w=255, const int img_h=255);
    void show();

private:
    cv::Mat img_;
    int img_w_;
    int img_h_;
};

#endif // VISUALIZER_1D_H
