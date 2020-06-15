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
    rotm.at<double>(0, 2) += (bbox.width  / 2.0 - center.x);
    rotm.at<double>(1, 2) += (bbox.height / 2.0 - center.y);
    // std::cout<<"修正后Opencv旋转矩阵"<<rotm<<std::endl;
    cv::warpAffine(img, dst, rotm, bbox.size(), cv::INTER_LINEAR, 0, cv::Scalar(255, 255, 255));
}

/*自制的旋转操作*/
void MyRotate(cv::Mat &img, cv::Mat &dst, double degree)
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
    /*修正旋转矩阵（修正平移变换）*/
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
    cv::Mat A = RotateMat(cv::Rect(0, 0, 2, 2)).t();                      //反算的旋转矩阵（数值上等于原旋转矩阵的转置）
    cv::Mat B = RotateMat(cv::Rect(2, 0, 1, 2));                          //反算的平移矩阵（数值上等于原平移矩阵的负数）
    /**在目标图像上遍历，寻找反算的原图像像素值*/
    for (int i = 0; i < nW; i++)
    {
        for (int j = 0; j < nH; j++)
        {
            cv::Mat dstPoint = (cv::Mat_<float>(2, 1) << i, j);
            cv::Mat T;
            /*反算原图像位置*/
            T = A.t() * (dstPoint - B);
            /*四邻域点
            0————-->x
            | A——B
            | |    |
            | D——C
            |
            y  */
            cv::Point2f pointDone(T.at<float>(0, 0), T.at<float>(1, 0));
            cv::Point2i pointDoneA(int(pointDone.x), int(pointDone.y));
            cv::Point2i pointDoneB = pointDoneA + cv::Point2i(1, 0);
            cv::Point2i pointDoneC = pointDoneA + cv::Point2i(1, 1);
            cv::Point2i pointDoneD = pointDoneA + cv::Point2i(0, 1);

            /*小数部分，以分配权重*/
            float u = pointDone.x - pointDoneA.x;
            float v = pointDone.y - pointDoneA.y;

            cv::Vec3b pixelValues;
            /*确定反算点的像素值*/
            if (pointDoneA.x >= 0 && pointDoneA.y >= 0 && pointDoneC.x <= w && pointDoneC.y <= h)
            {
                if (pointDone.x - pointDoneA.x < 0.001 && pointDone.y - pointDoneA.y < 0.001)
                {
                    pixelValues = img.at<cv::Vec3b>(pointDoneA);        //若反算的点是整数点，则直接赋值
                }
                else
                {
                    /*四邻域像素值*/
                    cv::Vec3b pixelPointA = img.at<cv::Vec3b>(pointDoneA);
                    cv::Vec3b pixelPointB = img.at<cv::Vec3b>(pointDoneB);
                    cv::Vec3b pixelPointC = img.at<cv::Vec3b>(pointDoneC);
                    cv::Vec3b pixelPointD = img.at<cv::Vec3b>(pointDoneD);
                    /*邻域加权像素值*/
                    pixelValues = (1 - u) * (1 - v) * pixelPointA + (1 - u) * v * pixelPointB + u * v * pixelPointC + u * (1 - v) * pixelPointD;
                }
            }
            else
            {
                pixelValues = cv::Vec3b(255, 255, 0);                    //若反算的点不在原图像上，则赋值为255（背景色）
            }
            dst.at<cv::Vec3b>(cv::Point(i, j)) = pixelValues;           //找到的点赋值
        }
    }
}