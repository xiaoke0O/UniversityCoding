#include<iostream>
#include<opencv2/opencv.hpp>
#include "ImgMatch.h"

int main(){

        cv::Mat image=cv::imread("../Assets/airport.bmp");
        cv::Mat templateImage=cv::imread("../Assets/template.bmp");
        //创建对象
        ImgMatch ImgMatching;
        //输入模板影像
        ImgMatching.getTemplateImage(templateImage);
        //输入待匹配影像
        ImgMatching.getImage(image);
        //指定搜索区域,若不指定即在全图范围内匹配。左上角横坐标，右上角纵坐标，向左长度，向下长度。
        //（0，0）在图像的左上角
        ImgMatching.getCornerPoint(250,250,80,80);
        //进行匹配。0为不显示搜索窗口滑动动画，1为显示
        //由于动画停顿的原因，当搜索区域较小时才建议打开，不然过程将异常漫长
        //当然如果你在大搜索区域的情况下开启了动画演示，可以按ESC键停止程序
        ImgMatching.MatchingImage(0);
        return 0;
}


