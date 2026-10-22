#ifndef ARMOR_DETECT_HPP
#define ARMOR_DETECT_HPP
#include <opencv2/opencv.hpp>
#include <vector>

struct LightBlob
{
    cv::RotatedRect rect;
};

class ArmorDetect
{
public:
    std::vector<std::vector<cv::Point>> detect(cv::Mat &src);
private:
    std::vector<LightBlob> getLightBlobs(const cv::Mat &src);
    bool checkPair(const LightBlob &a, const LightBlob &b);
};

#endif
