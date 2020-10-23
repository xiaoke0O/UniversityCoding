# UniversityCoding

## 介绍
大学阶段的编程作业，一般为专业课作业。以及自己做的一些DIY设备


## TODO
 
1. 完善各个README



## 使用平台介绍

| 语言    | IDE               | 编译器    | 编译方式   | 备注                 | 代码风格     |
| ------- | ----------------- | --------- | ---------- | -------------------- | ------------ |
| C++     | CLion、VSCode| g++       | CMake      | 主要用来开发产品     | 尽量写成类   |
| Python  | PyCharm           | python3.x | 直接运行   | 主要用来学习新算法   | 类或函数分离 |
| Fortran | CodeBlocks        | gfortran  | CodeBlocks | 扩展知识，算大型矩阵 | 模块封装     |
| IDL     |                   | IDL 8.3   | 直接运行   | ENVI相关             | 函数分离     |

## 使用说明

分为master分支与develop分支，查看代码请在master(默认)分支（develop存在为未完成项目）

在当前页面每一个文件夹为一大类，子文件夹为不同的项目，命名规则：*<u>项目名_语言</u>*

下边是一个项目的例子

```shell
ImageProcessing
├── OTSU_CPP
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── OTSU.cpp
│   ├── OTSU.h
│   └── README.md
├── Other
```

最好在原平台运行（平台参见上表）。若有问题可直接Issues或发邮件lengfeng1453@hotmail.com。

没有限制，可随意复制使用，主代码都在每一个文件夹中。

## 项目树

> 长期更新，最近一次更新2020-06-20

- Photogrammetry（摄影测量）
  - CCORR_ImageMatching_CPP（基于相关系数法的影像匹配）
  - Forstner_FeaturePoint_py（基于Forstner算子的特征点提取算法）
- ImageProcessing（图像处理）
  - OTSU_CPP（大津算法）
  - Rotate_cpp（图像旋转）