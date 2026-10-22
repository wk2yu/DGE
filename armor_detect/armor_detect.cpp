#include "armor_detect.hpp"
#include <cmath>

std::vector<LightBlob> ArmorDetect::getLightBlobs(const cv::Mat &src)
{
    std::vector<LightBlob> lights;
    cv::Mat gray, binary;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 120, 255, cv::THRESH_BINARY);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (auto &cnt : contours)
    {
        if (cv::contourArea(cnt) < 15)
            continue;
        LightBlob lb;
        lb.rect = cv::minAreaRect(cnt);
        lights.push_back(lb);
    }
    return lights;
}

bool ArmorDetect::checkPair(const LightBlob &a, const LightBlob &b)
{
    cv::Point2f ca = a.rect.center;
    cv::Point2f cb = b.rect.center;
    float dx = fabs(ca.x - cb.x);
    float dy = fabs(ca.y - cb.y);
    if (dx < dy)
        return false;
    float ha = a.rect.size.height;
    float hb = b.rect.size.height;
    if (fabs(ha - hb) > std::max(ha, hb) * 0.45)
        return false;
    return true;
}

std::vector<std::vector<cv::Point>> ArmorDetect::detect(cv::Mat &src)
{
    std::vector<std::vector<cv::Point>> armors;
    auto lights = getLightBlobs(src);
    for (int i = 0; i < lights.size(); i++)
    {
        for (int j = i + 1; j < lights.size(); j++)
        {
            if (checkPair(lights[i], lights[j]))
            {
                cv::Point2f p1[4], p2[4];
                lights[i].rect.points(p1);
                lights[j].rect.points(p2);
                std::vector<cv::Point> armor;
                armor.emplace_back(p1[0]);
                armor.emplace_back(p1[1]);
                armor.emplace_back(p2[3]);
                armor.emplace_back(p2[2]);
                armors.push_back(armor);
            }
        }
    }
    return armors;
}
