#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
int main() {
    std::cout << "Hello, World!" << std::endl;
    cv::Mat src=cv::imread("../../Assets/lena.png");
    cv::imshow("lena",src);
    cv::waitKey(0);
    return 0;
}
