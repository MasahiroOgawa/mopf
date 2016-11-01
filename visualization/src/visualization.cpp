#include "visualization.h"
#include <opencv2/highgui.hpp>
using namespace std;

namespace mo {

//-----------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Color& col){
    return os << "{r,g,b}={" << static_cast<unsigned>(col.red) << ',' <<
                 static_cast<unsigned>(col.green) << ',' <<
                 static_cast<unsigned>(col.blue) << "}";
}


//-----------------------------------------------------------------
int show(const std::string& winname, const Image& img, const int waitms){
    cv::imshow(winname, img);
    return cv::waitKey(waitms);
}


//-----------------------------------------------------------------
int show(const std::string& winname, const Image_gray& img, const int waitms){
    cv::imshow(winname, img);
    return cv::waitKey(waitms);
}


//-----------------------------------------------------------------
void line(const Point& pt_sta, const Point& pt_end, Image& img, const Color& color){
    cv::line(img, pt_sta, pt_end, color.pixval());
}


//-----------------------------------------------------------------
void arrow(const Point& pt_sta, const Point& pt_end, Image& img, const Color& color){
    cv::arrowedLine(img, pt_sta, pt_end, color.pixval());
}

//-----------------------------------------------------------------
void point(const Point& pt, Image& img, const Color& color, const int radius){
    cv::circle(img, pt, radius, color.pixval(), -1); //-1 means filled color.
}

//-----------------------------------------------------------------
void text(const std::string& text, Image& img, const Point& org, const double& scale, const Color& color){
    cv::putText(img, text, org, cv::FONT_HERSHEY_SIMPLEX, scale, color.pixval());
}

//-----------------------------------------------------------------
void colorbar(Image& img, const ColormapTypes colormaptype){
    for(int u=0; u<img.rows; ++u){
        unsigned char* Mu = img.ptr(u);
        for(int v=0; v<img.cols*3; v+=3){
            for(int c=0; c<3; ++c){ //color channel
                Mu[v+c] = 255 - u*255/img.rows;
            }
        }
    }

    cv::applyColorMap(img, img, colormaptype);
}


} //namespace mo
