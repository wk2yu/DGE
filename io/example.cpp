#include <opencv2/opencv.hpp>
#include <iostream>

class myCamera
{
public:
    myCamera();
    ~myCamera();
    bool read(cv::Mat &frame);

private:
    cv::VideoCapture cap_;
    bool is_open_;
};

myCamera::myCamera()
{
#ifdef _WIN32
    cap_.open(0);
#else
    cap_.open(0);
#endif
    is_open_ = cap_.isOpened();
    if (!is_open_)
    {
        std::cerr << "camera open failed!" << std::endl;
    }
}

myCamera::~myCamera()
{
    if (is_open_)
    {
        cap_.release();
    }
}

bool myCamera::read(cv::Mat &frame)
{
    if (!is_open_)
        return false;
    return cap_.read(frame);
}

int main()
{
    myCamera cam;
    cv::Mat frame;
    while (true)
    {
        if (!cam.read(frame))
            break;
        cv::imshow("io camera", frame);
        int key = cv::waitKey(30);
        if (key == 27)
            break;
    }
    cv::destroyAllWindows();
    return 0;
}
