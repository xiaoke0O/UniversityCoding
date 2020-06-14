#include <cmath>
#include <string>
#include <iostream>
#include <opencv2/imgproc.hpp>

/*OpenCV的旋转操作*/
void OpenCVRotate(cv::Mat &img, cv::Mat &dst, double degree)
{
    cv::Point2f center(img.cols / 2.0, img.rows / 2.0);
    cv::Mat rotm = cv::getRotationMatrix2D(center, degree, 1.0);

    cv::Rect bbox = cv::RotatedRect(center, img.size(), degree).boundingRect();
    rotm.at<double>(0, 2) += (bbox.width / 2.0 - center.x);
    rotm.at<double>(1, 2) += (bbox.height / 2.0 - center.y);
    // std::cout<<"修正后Opencv旋转矩阵"<<rotm<<std::endl;
    cv::warpAffine(img, dst, rotm, bbox.size(), cv::INTER_LINEAR);
}

/*自制的旋转操作*/
void MyRotate(cv::Mat &img, cv::Mat &dst, double degree, std::string method)
{
    /*源文件参数
    @w 图像宽度（列数）
    @h 图像高度（行数）
    @d 图像维度（通道数）*/
    int w = img.cols;
    int h = img.rows;
    int d = img.dims;
    /*确定旋转矩阵*/
    degree *= asin(1) / 90.0;
    float alpha = std::cos(degree);
    float Beta = std::sin(degree);
    int center_x = (w / 2.0);
    int center_y = (h / 2.0);
    cv::Mat RotateMat;
    RotateMat = (cv::Mat_<float>(2, 3) << alpha, Beta, (1 - alpha) * center_x - Beta * center_y,
                 -Beta, alpha, Beta * center_x + (1 - alpha) * center_y);

    /*计算旋转后的图片尺寸*/
    int nW = std::ceil(w * alpha + h * Beta);
    int nH = std::ceil(w * Beta + h * alpha);
    dst = cv::Mat::zeros(nH, nW, CV_8UC3);
    /*修正旋转矩阵*/
    RotateMat.at<float>(0, 2) += nW / 2.0 - center_x;
    RotateMat.at<float>(1, 2) += nH / 2.0 - center_y;

    // std::cout<<"修正后My旋转矩阵"<<RotateMat<<std::endl;
    /*计算旋转后的坐标位置（仿射变换）（正算，但是会出现空洞）*/

    // for (int i = 0; i < w; i++)
    // {
    //     for (int j = 0; j < h; j++)
    //     {
    //         cv::Mat T;
    //         cv::Mat OriginPoint = (cv::Mat_<float>(3, 1) << i, j, 1);
    //         T = RotateMat * OriginPoint;
    //         cv::Point2i PointDone;
    //         /*TODO:先简单的把旋转后的点取整*/
    //         PointDone.x =std::round(T.at<float>(0, 0));
    //         PointDone.y = std::round(T.at<float>(1, 0));
    //         // std::cout<<PointDone<<std::endl;
    //         dst.at<cv::Vec3b>(PointDone) = img.at<cv::Vec3b>(cv::Point(i, j));
    //     }
    // }

    /*由旋转后的点反算其在原图的坐标，有则取之，无则重采样*/
    cv::Mat A = RotateMat(cv::Rect(0, 0, 2, 2));
    cv::Mat B = RotateMat(cv::Rect(2, 0, 1, 2));

    for (int i = 0; i < nW; i++)
    {
        for (int j = 0; j < nH; j++)
        {

            cv::Mat dstPoint = (cv::Mat_<float>(2, 1) << i, j);
            cv::Mat T;
            T = A.t() * (dstPoint - B);
            cv::Point2i PointDone;
            PointDone.x = std::round(T.at<float>(0, 0));
            PointDone.y = std::round(T.at<float>(1, 0));

            // std::cout << "Heaaaaaaaaaaaa" << std::endl;

            if (PointDone.x >= 0 && PointDone.y >= 0 && PointDone.x <= w && PointDone.y <= h)
            {
                dst.at<cv::Vec3b>(cv::Point(i, j)) = img.at<cv::Vec3b>(PointDone);
            }
            else
            {
                dst.at<cv::Vec3b>(cv::Point(i, j)) = cv::Vec3b(0, 0, 0);
            }
        }
    }
}