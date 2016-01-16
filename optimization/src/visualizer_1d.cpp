#include "visualizer_1d.h"
#include <opencv2/highgui.hpp>

Visualizer_1d::Visualizer_1d(const int img_w, const int img_h):
    img_w_{img_w}, img_h_{img_h}
{
    img_ = cv::Mat(img_h_, img_w_, CV_8UC3);
}


void Visualizer_1d::show(){
    cv::imshow("1D optimization", img_);
    cv::waitKey(0);
}

