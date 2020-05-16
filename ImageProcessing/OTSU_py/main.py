import OTSU
import cv2 as cv

# 注意：
# cv::imread()默认读进来的不管是RGB还是灰度图，结果都是三通道的
# 其中灰度图读进来也是三通道，并且RGB值相等
# 要想读进来的灰度图是单通道的，需要加IMREAD_GRAYSCALE

img = cv.imread("Assets/lena_gray.bmp",cv.IMREAD_GRAYSCALE)
if  img is None:
    print("image opening failed!")
    exit(-1)

# 灰度处理
print(img.shape)
if img.ndim > 2:
    print("Converting to grayscale image")
    img=cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    print("Convert Done")
#与OpenCV对比
mythresh=OTSU.otsuthresh(img)
opencvthresh, dst1 = cv.threshold(img, 0, 255, cv.THRESH_OTSU)

print("Mythresh {0}\nOpenCVthresh {1}".format(mythresh,opencvthresh))