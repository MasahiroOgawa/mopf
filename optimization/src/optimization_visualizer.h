#ifndef OPTIMIZATION_VISUALIZER_H
#define OPTIMIZATION_VISUALIZER_H
#include <opencv2/core.hpp>


class Optimization_visualizer
{
public:
    Optimization_visualizer(const int linear_search_img_w=255, const int linear_search_img_h=255);
    void show();

private:
    cv::Mat linear_search_img_;
    int linear_search_img_w_;
    int linear_search_img_h_;
};

#endif // OPTIMIZATION_VISUALIZER_H
