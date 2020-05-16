//
// Created by kk on 2020/4/27.
//

#ifndef IMAGEMATCHING_IMGMATCH_H
#define IMAGEMATCHING_IMGMATCH_H

#include <opencv2/opencv.hpp>

class ImgMatch {
public:
    ImgMatch();//构造函数
    //公有函数为私有成员赋值，并初始化搜索区域位置
    void getImage(cv::Mat &Image) {
            originImage = &Image;
            leftup.x = 0;
            leftup.y = 0;
            Swidth=Image.cols;
            Sheight=Image.rows;
    }
    void getTemplateImage(cv::Mat &Image) { templateImage = &Image; }

    //获取区域角点坐标
    void getCornerPoint(int leftupX, int leftupY, int searchwidth, int searchheight) {
            leftup.x = leftupX;
            leftup.y = leftupY;
            Swidth = searchwidth;
            Sheight = searchheight;
    }
    //公有函数，进行匹配的开关
    void MatchingImage(bool Animation);

private:

    std::vector<float> CCORR;//存储的每一次计算的结果
    cv::Mat *originImage{};//待匹配的大图
    cv::Mat *templateImage{};//模板图像
    cv::Point2i leftup;//搜索区域左上角坐标
    int Swidth, Sheight;//搜索区域的长宽
    //显示图像，集画矩形与imshow
    static void ShowImage(cv::Mat Imag, cv::Rect2i rect, const cv::Scalar &color);
    //计算相关系数
    float getCorrelation(cv::Mat &targetImage, cv::Mat &searchImage);
    //找出相关系数最大的地方并画出结果
    void MarkResult();


};


#endif //IMAGEMATCHING_IMGMATCH_H
