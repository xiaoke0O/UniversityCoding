#include <opencv2/imgproc.hpp>
cv::Mat OpenCVRotate(cv::Mat &img, double degree)
{
    cv::Point2f center(img.cols / 2, img.rows / 2);
    cv::Mat rotm = cv::getRotationMatrix2D(center, degree, 1.0);
    cv::Rect bbox = cv::RotatedRect(center, img.size(), degree).boundingRect();
    rotm.at<double>(0, 2) += (bbox.width / 2.0 - center.x);
    rotm.at<double>(1, 2) += (bbox.height / 2.0 - center.y);

    cv::Mat dst;
    cv::warpAffine(img, dst, rotm, bbox.size(), cv::INTER_LINEAR);
    return dst;
}