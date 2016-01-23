#include "visualization.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> //for arrowedLine()

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
    cv::arrowedLine(img, pt_sta, pt_end, color.pixval());
}

}
