#ifndef SIFT_HPP
#define SIFT_HPP

#include "../../../mopf/image/src/image.h"
#include <opencv2/xfeatures2d.hpp>
#include <vector>


class Sift
{
public:
    Sift();
    void detect(const mo::Image_gray& img);
    int show();

private:
    void reset(){keypoints_.clear();}

    std::vector<cv::KeyPoint> keypoints_{};
    cv::Ptr<cv::SIFT> sift_{};
    cv::Mat descriptor_{}; ///< histogram of each 3 channel Mat[row,col,octave
};

#endif // SIFT_HPP
