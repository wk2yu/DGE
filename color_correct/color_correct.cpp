#include "color_correct.hpp"

cv::Mat ColorCorrect::run(const cv::Mat &src)
{
    if (src.empty())
        return cv::Mat();
    cv::Mat img;
    src.convertTo(img, CV_32FC3);
    std::vector<cv::Mat> bgr;
    cv::split(img, bgr);
    cv::Scalar m = cv::mean(src);
    float meanB = m[0];
    float meanG = m[1];
    float meanR = m[2];
    float grayMean = (meanB + meanG + meanR) / 3.0f;
    bgr[0] = bgr[0] * grayMean / meanB;
    bgr[1] = bgr[1] * grayMean / meanG;
    bgr[2] = bgr[2] * grayMean / meanR;
    cv::Mat dst;
    cv::merge(bgr, dst);
    dst.convertTo(dst, CV_8UC3);
    return dst;
}
