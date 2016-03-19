#include "visualizer_1d.h"
#include <iostream>
#define DEBUG_
using namespace std;

namespace mo {

//-----------------------------------------------------------------
Visualizer_1d::Visualizer_1d(const int img_w, const int img_h):
    img_w_{img_w}, img_h_{img_h}, bg_color_(Color(128,128,128))
{
    img_ = Image(img_h_, img_w_, bg_color_.pixval());
}


//-----------------------------------------------------------------
void Visualizer_1d::show_optimization(){
    comp_minmax();
    if(min_x_==max_x_ || min_y_==max_y_) return; //display nothing.
    clear_img(); //after computing min & max, we have to rescale points. So we need to clear image.
    draw_axis();
    draw_arrow();
    draw_pts();
    draw_colorbar();
    int waitms=0;
    show("1D optimization", img_, waitms);
}


//-----------------------------------------------------------------

void Visualizer_1d::record(const double& x, const double& y, const double& dfx){
    pts_.push_back(Point(x,y));
    dfxs_.push_back(dfx);
}


//-----------------------------------------------------------------
void Visualizer_1d::clear(){
    pts_.clear();
    dfxs_.clear();
    clear_img();
}

//-----------------------------------------------------------------
void Visualizer_1d::clear_img(){
    img_ = Image(img_h_, img_w_, bg_color_.pixval());
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
    //x axis
    arrow(map_to_display(Point(min_x_,min_y_)), map_to_display(Point(max_x_,min_y_)), img_, Color(0,0,0));
    text("x", img_,  map_to_display(Point(max_x_,min_y_)), 1.0, Color{0,0,0});

    //y axis
    arrow(map_to_display(Point(0,min_y_)), map_to_display(Point(0,max_y_)), img_, Color(0,0,0));
    text("f(x)", img_,  map_to_display(Point(0,max_y_)), 1.0, Color{0,0,0});
}


//-----------------------------------------------------------------
void Visualizer_1d::draw_arrow(){
    for(int i=1; i<pts_.size(); ++i){
        arrow(map_to_display(pts_[i-1]), map_to_display(pts_[i]), img_);
    }
}


//-----------------------------------------------------------------
void Visualizer_1d::draw_pts(){
    for(int i=0; i<pts_.size(); ++i){
        double red = tanh(abs(dfxs_[i])) * 255;
        double blue = 255-red;
        point(map_to_display(pts_[i]), img_, Color(red,0,blue), 3);
    }
}


//-----------------------------------------------------------------
void Visualizer_1d::draw_colorbar(){
    text("df(x)", img_, Point(img_w_*90/100,img_h_/20), 0.5, Color{0,0,0});
    //from here 2016 3/16
    //draw color bar df(x)
    Image roi = img_(Rect{img_w_*90/100, img_h_/10, img_w_/100, img_h_/10});
    colorbar(roi, ColormapTypes::COLORMAP_HOT);
}


//-----------------------------------------------------------------
Point Visualizer_1d::map_to_display(const Point& pt){
    const double w_margin{img_w_/10.0};
    const double h_margin{img_h_/10.0};
    if(min_x_==max_x_ || min_y_==max_y_) throw runtime_error("min==max @Visualizer_1d::map_to_display()");
    double w_scale = (img_w_ - 2 * w_margin) / (max_x_ - min_x_);
    double h_scale = (img_h_ - 2 * h_margin) / (max_y_ - min_y_);

    return Point((pt.x - min_x_) * w_scale + w_margin, (max_y_ - pt.y) * h_scale + h_margin); //note: y direction is inverse in image coordinate.
}



} //namespace mo
