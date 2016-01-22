#include "visualization.h"
#include <opencv2/highgui.hpp>

namespace mo {

void show(const std::string& winname, const Matrix& img, const int waitms){
    cv::imshow(winname, img);
    cv::waitKey(waitms);
}

}
