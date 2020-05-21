#include <string>
#include <cmath>
#include <Eigen/Geometry>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/eigen.hpp>

void OpenCVRotate(cv::Mat &img, cv::Mat &dst, double degree)
{
    cv::Point2f center(img.cols / 2, img.rows / 2);
    cv::Mat rotm = cv::getRotationMatrix2D(center, degree, 1.0);
    cv::Rect bbox = cv::RotatedRect(center, img.size(), degree).boundingRect();
    rotm.at<double>(0, 2) += (bbox.width / 2.0 - center.x);
    rotm.at<double>(1, 2) += (bbox.height / 2.0 - center.y);
    cv::warpAffine(img, dst, rotm, bbox.size(), cv::INTER_LINEAR);
}

void MyRotate(cv::Mat &img, cv::Mat &dst, double degree, std::string method)
{
    degree *= asin(1) / 90.0;
    float alpha = std::cos(degree);
    float Beta = std::sin(degree);
    int x=img.size().width/2;
    int y=img.size().height/2;
    Eigen::Matrix<float, 2,3> A;


}