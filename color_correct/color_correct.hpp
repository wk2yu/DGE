#ifndef COLOR_CORRECT_HPP
#define COLOR_CORRECT_HPP
#include <opencv2/opencv.hpp>

class ColorCorrect
{
public:
    cv::Mat run(const cv::Mat &src);
};

#endif
