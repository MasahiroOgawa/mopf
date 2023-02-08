#include "sift.hpp"

Sift::Sift()
{
    sift_ = cv::SIFT::create();
}
