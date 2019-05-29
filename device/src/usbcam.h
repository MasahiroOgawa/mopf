#ifndef USBCAM_H
#define USBCAM_H
#include <opencv2/videoio.hpp>

namespace mo {
using VideoCapture = cv::VideoCapture;

class Usbcam {
public:
  bool show_loop();

private:
};

} // namespace mo

#endif
