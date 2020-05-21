#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include "rotate.h"

int main()
{
    std::cout << "开始执行!" << std::endl;

    cv::Mat src = cv::imread("../Assets/boy_2.bmp");
    if (src.empty())
    {
        std::cout << "图像读取失败!" << std::endl;
        exit(-1);
    }
    std::cout<<src.size().width<<std::endl;
    cv::Mat ByOpenCV,ByMySelf;
    // OpenCVRotate(src, ByOpenCV, 45.0);
    // cv::imwrite("Rotated_By_OpenCV.jpg", ByOpenCV);
    MyRotate(src,ByMySelf,30.0,"LINE");
    // cv::imwrite("Rotated_By_MySelf.jpg",ByMySelf);
    return 0;
}
