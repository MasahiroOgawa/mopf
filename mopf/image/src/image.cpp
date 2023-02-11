#include "image.hpp"
#include <opencv2/imgproc.hpp>
using namespace std;

namespace mo {

void ToGray(const Image &color, Image_gray &gray) {
  cv::cvtColor(color, gray, cv::COLOR_BGR2GRAY);
}

} // namespace mo
