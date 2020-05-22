#include <string>
#include <cmath>
#include <Eigen/Geometry>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/eigen.hpp>

/*OpenCV的旋转操作*/
void OpenCVRotate(cv::Mat &img, cv::Mat &dst, double degree)
{
    cv::Point2f center(img.cols / 2, img.rows / 2);
    cv::Mat rotm = cv::getRotationMatrix2D(center, degree, 1.0);
    cv::Rect bbox = cv::RotatedRect(center, img.size(), degree).boundingRect();
    rotm.at<double>(0, 2) += (bbox.width / 2.0 - center.x);
    rotm.at<double>(1, 2) += (bbox.height / 2.0 - center.y);
    cv::warpAffine(img, dst, rotm, bbox.size(), cv::INTER_LINEAR);
}
/*自制的旋转操作*/
void MyRotate(cv::Mat &img, cv::Mat &dst, double degree, std::string method)
{
    /*源文件参数
    @w 图像宽度（列数）
    @h 图像高度（行数）*/
    int w = img.cols;
    int h = img.rows;
    /*确定旋转矩阵*/
    degree *= asin(1) / 90.0;
    float alpha = std::cos(degree);
    float Beta = std::sin(degree);
    int x = img.size().width / 2;
    int y = img.size().height / 2;
    Eigen::Matrix<float, 2, 3> RotMat;
    RotMat << alpha, Beta, (1 - alpha) * x - Beta * y, -Beta, alpha, Beta * x + (1 - alpha) * y;
    /*TODO:计算旋转后的图片尺寸*/
    int nW = int(w * alpha + h * Beta);
    int nH = int(w * Beta + h * alpha);
    /*TODO:修正旋转矩阵*/
    RotMat[0, 2] += nW / 2 - x;
    RotMat[1, 2] += nH / 2 - y;
    /*TODO:计算旋转后的坐标位置（仿射变换）*/
}