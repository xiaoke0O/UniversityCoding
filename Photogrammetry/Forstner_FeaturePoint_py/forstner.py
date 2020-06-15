import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import sys


# 灰度处理
def rgb2gray(rgb):
    return np.uint8(np.dot(rgb[..., :3], [0.2989, 0.5870, 0.1140]))


# 利用大津法获取阈值
def otsuthresh(src):
    Grayscale = 256
    graynum = np.zeros(Grayscale, dtype=int)
    for i in src:
        for j in i:
            graynum[j] += 1
    mu, scale = 0, 1. / src.size
    for i in range(Grayscale):
        mu = mu + i * graynum[i]
    mu = mu * scale
    mu1, q1 = 0, 0
    max_sigma, max_val = 0, 0
    for i in range(Grayscale):
        p_i = graynum[i] * scale
        mu1 *= q1
        q1 += p_i
        q2 = 1. - q1
        if min(q1, q2) < sys.float_info.epsilon or max(q1, q2) > 1 - sys.float_info.epsilon:
            continue

        mu1 = (mu1 + i * p_i) / q1
        mu2 = (mu - q1 * mu1) / q2
        sigma = q1 * q2 * (mu1 - mu2) * (mu1 - mu2)
        if sigma > max_sigma:
            max_sigma = sigma
            max_val = i
    thresh = max_val
    return thresh


# 得到二值图像
def getBinary(src):
    if np.ndim(src) < 3:
        image_gray = src.copy()
    else:
        image_gray = rgb2gray(src)
    thresh = otsuthresh(image_gray)
    imgx = image_gray.shape[0]
    imgy = image_gray.shape[1]
    Binaryimg = np.zeros([imgx, imgy], dtype=np.bool)
    for x in range(image_gray.shape[0]):
        for y in range(image_gray.shape[1]):
            if image_gray[x, y] > thresh:
                Binaryimg[x, y] = 1
    return Binaryimg


# 初步选点
def getPrimaryPoints(BinaryImage):
    imgx, imgy = BinaryImage.shape
    PrimaryResult = np.zeros([imgx, imgy], dtype=np.uint8)
    for i in range(1, imgx - 1):
        for j in range(1, imgy - 1):
            dg1 = BinaryImage[i, j] ^ BinaryImage[i + 1, j]
            dg2 = BinaryImage[i, j] ^ BinaryImage[i, j + 1]
            dg3 = BinaryImage[i, j] ^ BinaryImage[i - 1, j]
            dg4 = BinaryImage[i, j] ^ BinaryImage[i, j - 1]
            dg = np.sort([dg1, dg2, dg3, dg4])
            if dg[2] == 1:
                PrimaryResult[i, j] = 255
    return PrimaryResult


# 以初选点为中心计算协方差与误差椭圆
def getCovMatrix(PrimaryPionts, BinaryImage):
    imgx, imgy = PrimaryPionts.shape
    FurtherResult = PrimaryPionts.copy()
    WeightMatrix = np.zeros([imgx, imgy])
    Tq = 0.6
    for i in range(1, imgx - 1):
        for j in range(1, imgy - 1):
            if PrimaryPionts[i, j] == 255:
                gu2, gv2, guv = 0.0, 0.0, 0.0
                for ii in range(i - 1, i + 1):
                    for jj in range(j - 1, j + 1):
                        gu2 += BinaryImage[ii + 1, jj + 1] ^ BinaryImage[ii, jj]
                        gv2 += BinaryImage[ii, jj + 1] ^ BinaryImage[ii + 1, jj]
                        guv += (int(BinaryImage[ii + 1, jj + 1]) - int(BinaryImage[ii, jj])) * (
                                    int(BinaryImage[ii, jj + 1]) - int(BinaryImage[ii + 1, jj]))
                DetN = gu2 * gv2 - guv ** 2
                trN = gu2 + gv2
                q = 4 * DetN / (trN ** 2)
                if q > Tq:
                    WeightMatrix[i, j] = DetN / trN
                else:
                    FurtherResult[i, j] = 0
    return FurtherResult, WeightMatrix


def getResult(FutherImage, WeightMatrix):
    imgx, imgy = FutherImage.shape
    FinallResult = FutherImage.copy()
    vmsize = 5
    wradius = 2
    for i in range(wradius, imgx - wradius):
        for j in range(wradius, imgy - wradius):
            if (FutherImage[i, j] == 255):
                temp = WeightMatrix[i - wradius:i + wradius + 1, j - wradius:j + wradius + 1]
                tempiv = temp.reshape(1, 25)
                tempsort = np.fliplr(np.sort(tempiv))
                # print(tempsort)
                # print('&&&&&&&&&&&&&&&')
                if (WeightMatrix[i, j] == tempsort[0, 0]) and (WeightMatrix[i, j] != tempsort[0, 1]):
                    pass
                else:
                    FinallResult[i, j] = 0
    return FinallResult


# def Forstner(image):


if __name__ == '__main__':
    print('Hello')
    img = np.asarray(Image.open('../Assets/Galleria_Vittorio_Emanuele_II.png'))
    print('图像已加载')
    img_bw = getBinary(img)
    print('已转化为二值图像')
    Primary = getPrimaryPoints(img_bw)
    print('已完成初步选点')
    Further, Weight = getCovMatrix(Primary, img_bw)
    Finall = getResult(Further, Weight)
    print('已完成最终筛选')
    title = ['Original Image', 'BINARY', 'Primary', 'Further', 'Finall', 'overlay']
    image = [img, img_bw, Primary, Further, Finall]
    for i in range(6):
        if i == 5:
            plt.subplot(2, 3, 6), plt.imshow(image[0], 'gray')
            plt.spy(image[4], markersize=1, marker='x', color='r')
            plt.title(title[5])
            break
        plt.subplot(2, 3, i + 1), plt.imshow(image[i], 'gray')
        plt.title(title[i])

    plt.show()