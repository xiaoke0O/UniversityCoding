//
// Created by kk on 2020/4/27.
//

#include "ImgMatch.h"
#include <iostream>

/*构造函数*/
ImgMatch::ImgMatch() {
        std::cout << "对象已创建,开始执行程序" << std::endl;
}

/*执行匹配函数*/
void ImgMatch::MatchingImage(bool Animation) {
        //画出搜索区域
        ShowImage(*originImage, cv::Rect2i(leftup, cv::Size2i(Swidth, Sheight)), cv::Scalar(255, 0, 0));
        cv::putText(*originImage, "SearchArea", leftup, cv::FONT_HERSHEY_TRIPLEX, 0.5, cv::Scalar(255, 0, 0));
        //获取匹配窗口大小
        int targetWidth = templateImage->cols;
        int targetHeight = templateImage->rows;
        //在搜索区域内进行模板匹配
        for (int i = 0; i < Swidth - targetWidth; ++i) {
                for (int j = 0; j < Sheight - targetHeight; ++j) {
                        //先把原图像复制一下，在复制品上操作
                        cv::Mat newImage;
                        originImage->copyTo(newImage);
                        //新的搜索窗口位置
                        cv::Point2i newleftup(leftup.x + i, leftup.y + j);
                        cv::Point2i newrightdown(newleftup.x + targetWidth, newleftup.y + targetHeight);
                        //在搜索图像上裁剪出与目标窗口一样大小的图像
                        cv::Rect rect(newleftup, newrightdown);
                        cv::Mat searchcut = newImage(rect);
                        //计算目标窗口与搜索窗口的相关系数并存储到CCORR向量
                        float theCCORR = getCorrelation(*templateImage, searchcut);
                        CCORR.push_back(theCCORR);
                        if (Animation) {
                                //窗口滑动动画，按ESC键终止
                                ShowImage(newImage, rect, cv::Scalar(0, 255, 0));
                                if (cv::waitKey(1) == 27) {
                                        std::cout << "人为终止" << std::endl;
                                        exit(-1);
                                }
                        }
                }

        }
        MarkResult();
}

void ImgMatch::ShowImage(cv::Mat Image, cv::Rect2i rect, const cv::Scalar &color) {
        cv::rectangle(Image, rect, color);
        cv::imshow("origin", Image);
}

float ImgMatch::getCorrelation(cv::Mat &targetImage, cv::Mat &searchImage) {
        //将目标图像转为灰度
        cv::Mat targetGray;
        cv::cvtColor(targetImage, targetGray, cv::COLOR_BGR2GRAY);
        //将搜索图像转为灰度
        cv::Mat searchGray;
        cv::cvtColor(searchImage, searchGray, cv::COLOR_BGR2GRAY);
        //计算相关系数参数值
        /*这里有个坑，直接灰度化的图像是8bit的，所以变量也是8位无符号整型，直接平方的话像素值都会变成255
        所以对于参与运算的矩阵要是int型。只是相乘与平方有影响，求和没影响*/
        cv::Mat_<int> targetcopy;
        targetGray.copyTo(targetcopy);
        cv::Mat_<int> searchcopy;
        searchGray.copyTo(searchcopy);

        float sggp = cv::sum(targetcopy.mul(searchcopy))[0];
        float sgg = cv::sum(targetcopy.mul(targetcopy))[0];
        float sgpgp = cv::sum(searchcopy.mul(searchcopy))[0];
        float sg = cv::sum(targetcopy)[0];
        float sgp = cv::sum(searchcopy)[0];
        int N = targetcopy.cols * targetcopy.rows;
        float a = sggp - sg * sgp / (N * 1.0);
        float b = sgg - sg * sg / (N * 1.0);
        float c = sgpgp - sgp * sgp / (N * 1.0);
        float P = a / sqrt(b * c);

        return P;
}
/*标记出结果(目标位置)*/
void ImgMatch::MarkResult() {
        std::vector<float>::iterator result;
        result = std::max_element(CCORR.begin(), CCORR.end());
        int max_location = std::distance(CCORR.begin(), result);
        cv::Point2i markLeft;
        markLeft.x = leftup.x + max_location / (Sheight - templateImage->cols);
        markLeft.y = leftup.y + max_location % (Sheight - templateImage->rows);
        cv::Rect2i rect(markLeft, cv::Size2i(templateImage->cols, templateImage->rows));
        ShowImage(*originImage, rect, cv::Scalar(0, 255, 0));
        cv::waitKey(0);
}