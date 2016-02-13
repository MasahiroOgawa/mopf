#include "visualizer_1d.h"
#include <iostream>
#define DEBUG_
using namespace std;

namespace mo {

//-----------------------------------------------------------------
Visualizer_1d::Visualizer_1d(const double& thre_df, const int img_w, const int img_h):
    thre_df_{thre_df}, img_w_{img_w}, img_h_{img_h}
{
    Color color{128,128,128};
    img_ = Image(img_h_, img_w_, color.pixval());
}


//-----------------------------------------------------------------
void Visualizer_1d::show_optimization(){
    comp_minmax();
    draw_axis();
    draw_arrow();
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

#ifdef DEBUG_
    cout << "pts= ";
    for(auto p : pts_){
        cout << p << ' ';
    }
    cout << endl;

    cout << "min_x=" << min_x_ << ", min_y_=" << min_y_ <<
            ", max_x=" << max_x_ << ", max_y=" << max_y_ << endl;
#endif
}


//-----------------------------------------------------------------
void Visualizer_1d::draw_axis(){

}

//-----------------------------------------------------------------
void Visualizer_1d::draw_arrow()try{
    for(int i=1; i<pts_.size(); ++i){
        arrow(map_to_display(pts_[i-1]), map_to_display(pts_[i]), img_);
    }
}catch(runtime_error& e){
    cout << e.what() << endl;
    return;
}


//-----------------------------------------------------------------
Point Visualizer_1d::map_to_display(const Point& pt){
    const double w_margin{img_w_/10.0};
    const double h_margin{img_h_/10.0};
    if(min_x_==max_x_ || min_y_==max_y_) throw runtime_error("min==max @Visualizer_1d::map_to_display()");
    double w_scale = (img_w_ - 2 * w_margin) / (max_x_ - min_x_);
    double h_scale = (img_h_ - 2 * h_margin) / (max_y_ - min_y_);

    return Point((pt.x - min_x_) * w_scale + w_margin, (pt.y - min_y_) * h_scale + h_margin);
}

} //namespace mo
