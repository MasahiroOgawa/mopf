#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

struct Transform {
  double dx;
  double dy;
  double da; // angle

  void getTransform(cv::Mat &T) {
    T.at<double>(0, 0) = cos(da);
    T.at<double>(0, 1) = -sin(da);
    T.at<double>(1, 0) = sin(da);
    T.at<double>(1, 1) = cos(da);
    T.at<double>(0, 2) = dx;
    T.at<double>(1, 2) = dy;
  }
};

struct Trajectory {
  double x;
  double y;
  double a; // angle
};

std::vector<Trajectory> cumsum(std::vector<Transform> &transforms) {
  std::vector<Trajectory> trajectory;
  // Accumulate frame to frame transform
  double a = 0;
  double x = 0;
  double y = 0;

  for (size_t t = 0; t < transforms.size(); ++t) {
    x += transforms[t].dx;
    y += transforms[t].dy;
    a += transforms[t].da;

    trajectory.push_back(Trajectory{x, y, a});
  }

  return trajectory;
}

// upscale 4% fixing the center.
void enlargeImage(cv::Mat &frame_stabilized) {
  cv::Mat T = cv::getRotationMatrix2D(
      cv::Point2f(frame_stabilized.cols / 2, frame_stabilized.rows / 2), 0,
      1.04);
  cv::warpAffine(frame_stabilized, frame_stabilized, T,
                 frame_stabilized.size());
}

int main(int argc, char **argv) {
  // preparation
  cv::VideoCapture cap(argv[1]);
  int n_frames = int(cap.get(cv::CAP_PROP_FRAME_COUNT));
  int w = int(cap.get(cv::CAP_PROP_FRAME_WIDTH));
  int h = int(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
  double fps = cap.get(cv::CAP_PROP_FPS);
  cv::VideoWriter out("out.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
                      fps, cv::Size(2 * w, h));
  cv::Mat curr, curr_gray;
  cv::Mat prev, prev_gray;
  std::vector<Transform> transforms;
  cv::Mat last_T;

  // Read first frame
  cap >> prev;
  cv::cvtColor(prev, prev_gray, cv::COLOR_BGR2GRAY);

  // get trajectory frame loop
  for (int i = 1; i < n_frames - 1; i++) {
    std::vector<cv::Point2f> prev_pts, curr_pts;
    cv::goodFeaturesToTrack(prev_gray, prev_pts, 200, 0.01, 30);

    // Read next frame
    bool success = cap.read(curr);
    if (!success)
      break;
    cv::cvtColor(curr, curr_gray, cv::COLOR_BGR2GRAY);

    // Calculate optical flow
    std::vector<uchar> status;
    std::vector<float> err;
    cv::calcOpticalFlowPyrLK(prev_gray, curr_gray, prev_pts, curr_pts, status,
                             err);

    // Filter only valid points
    auto prev_it = prev_pts.begin();
    auto curr_it = curr_pts.begin();
    for (size_t k = 0; k < status.size(); k++) {
      if (status[k]) {
        prev_it++;
        curr_it++;
      } else {
        prev_it = prev_pts.erase(prev_it);
        curr_it = curr_pts.erase(curr_it);
      }
    }

    cv::Mat T = cv::estimateRigidTransform(prev_pts, curr_pts, false);
    // In case no transform is found, just use the last known good transform.
    if (T.data == NULL)
      last_T.copyTo(T);

    double dx = T.at<double>(0, 2);
    double dy = T.at<double>(1, 2);
    double da = std::atan2(T.at<double>(1, 0), T.at<double>(0, 0));
    transforms.push_back(Transform{dx, dy, da});

    T.copyTo(last_T);
    curr_gray.copyTo(prev_gray);

    std::cout << "Frame =" << i << " ,  Tracked points = " << prev_pts.size()
              << std::endl;
  }

  // Compute trajectory using cumulative sum of transformations
  std::vector<Trajectory> trajectory = cumsum(transforms);

  std::vector<Transform> transforms_smooth;

  for (size_t i = 0; i < transforms.size(); i++) {
    // Calculate newer transformation array
    double dx = transforms[i].dx - trajectory[i].x;
    double dy = transforms[i].dy - trajectory[i].y;
    double da = transforms[i].da - trajectory[i].a;

    transforms_smooth.push_back(Transform{dx, dy, da});
  }

  cap.set(cv::CAP_PROP_POS_FRAMES, 0);
  cv::Mat T(2, 3, CV_64F);
  cv::Mat frame, frame_stabilized, frame_out;

  // create stabilized video loop
  for (int t = 0; t < n_frames - 1; ++t) {
    bool success = cap.read(frame);
    if (!success)
      break;

    transforms_smooth[t].getTransform(T);
    cv::warpAffine(frame, frame_stabilized, T, frame.size());

    // Scale image to remove black border artifact
    enlargeImage(frame_stabilized);

    // Draw the original and stablised
    cv::hconcat(frame, frame_stabilized, frame_out);
    out.write(frame_out);

    cv::imshow("Before and After", frame_out);
    cv::waitKey(10);
  }

  cap.release();
  out.release();
  cv::destroyAllWindows();

  return 0;
}
