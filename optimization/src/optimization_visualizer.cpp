#include "optimization_visualizer.h"
#include <opencv2/highgui.hpp>

Optimization_visualizer::Optimization_visualizer(const int linear_search_img_w, const int linear_search_img_h):
    linear_search_img_w_{linear_search_img_w}, linear_search_img_h_{linear_search_img_h}
{
    linear_search_img_ = cv::Mat(linear_search_img_h_, linear_search_img_w_, CV_8UC3);
}


void Optimization_visualizer::show(){
    cv::imshow("linear search", linear_search_img_);
    cv::waitKey(0);
}

