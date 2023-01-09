#include "usbcam.h"
#include "../../video/src/video.hpp"
#include "../../visualization/src/visualization.h"

namespace mo {
bool Usbcam::show_loop() {
  VideoCapture cap(0); // open the default camera
  if (!cap.isOpened()) // check if we succeeded
    return false;

  Image frame;
  int waitms{5};
  for (;;) {
    cap >> frame; // get a new frame from camera
    if (show("frame", frame, waitms) == 'q')
      break;
  }
  return true;
}

} // namespace mo
