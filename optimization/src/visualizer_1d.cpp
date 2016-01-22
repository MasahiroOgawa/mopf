#include "visualizer_1d.h"

namespace mo {

//-----------------------------------------------------------------
Visualizer_1d::Visualizer_1d(const int img_w, const int img_h):
    img_w_{img_w}, img_h_{img_h}
{
    img_ = Matrix(img_h_, img_w_, CV_8UC3);
}


//-----------------------------------------------------------------
void Visualizer_1d::show_optimization(){
    comp_minmax();
    show("1D optimization", img_);
}


//-----------------------------------------------------------------

void Visualizer_1d::record(const double& x, const double& y){
    pts_.push_back(Point(x,y));
}


//-----------------------------------------------------------------
void Visualizer_1d::comp_minmax(){
    if(pts_.size()==1){
        min_x_ = pts_[0].x;
        min_y_ = pts_[0].y;
        max_x_ = pts_[0].x;
        max_y_ = pts_[0].y;
    }else{
        if(pts_.back().x < min_x_) min_x_ = pts_.back().x;
        else if(pts_.back().x > max_x_) max_x_ = pts_.back().x;

        if(pts_.back().y < min_y_) min_y_ = pts_.back().y;
        else if(pts_.back().y > max_y_) max_y_ = pts_.back().y;
    }
    //from here. 2016/1/20 check correctness.
}

} //namespace mo
