#include "visualization.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> //for arrowedLine()
#include <iostream> //for debug

namespace mo {

//-----------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Color& col){
    return os << "{r,g,b}={" << static_cast<unsigned>(col.red) << ',' <<
                 static_cast<unsigned>(col.green) << ',' <<
                 static_cast<unsigned>(col.blue) << "}";
}


//-----------------------------------------------------------------
void show(const std::string& winname, const Image& img, const int waitms){
    cv::imshow(winname, img);
    cv::waitKey(waitms);
}


//-----------------------------------------------------------------
void arrow(const Point& pt_sta, const Point& pt_end, Image& img, const Color& color){
    //for debug
    std::cout << "{r,g,b}={" << static_cast<double>(color.red) << ',' <<
                 static_cast<double>(color.green) << ',' <<
                 static_cast<double>(color.blue) << "}";
    cv::arrowedLine(img, pt_sta, pt_end, cv::Scalar{0,255,0});

//    cv::arrowedLine(img, pt_sta, pt_end,
//                    cv::Scalar(static_cast<double>(color.blue),
//                               static_cast<double>(color.green),
//                               static_cast<double>(color.red)));
}

}
