#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include "../include/rotate.h"

int main()
{
    std::cout << "开始执行!" << std::endl;

    cv::Mat src = cv::imread("../Assets/boy_2.bmp");

    if (src.empty())
    {
        std::cout << "图像读取失败!" << std::endl;
        exit(-1);
    }

    std::cout << "原始图像尺寸：" << src.size() << std::endl;

    cv::Mat ByOpenCV, ByMySelf;

    OpenCVRotate(src, ByOpenCV, 45.0);
    std::cout << "OpenCV旋转后的尺寸：" << ByOpenCV.size() << std::endl;
    cv::imwrite("Rotated_By_OpenCV.jpg", ByOpenCV);                         //将结果输出到文件

    MyRotate(src, ByMySelf, 45.0);                                          //速度比OpenCV慢多了
    std::cout << "MySelf旋转后的尺寸：" << ByMySelf.size() << std::endl;
    cv::imwrite("Rotated_By_MySelf.jpg", ByMySelf);                         //将结果输出到文件
    
    return 0;
}
