import matplotlib.image as mpimg  # 读取图像的库
import matplotlib.pyplot as plt  # 画图的库
import numpy as np  # 创建向量的库

# 读取灰度图像
lena = mpimg.imread('test_image/lena_grey.bmp')
# 以灰度图像展示
plt.imshow(lena, cmap='Greys_r')
# 关闭数轴
plt.axis("off")
# 新建画布，画直方图
plt.figure()
# 创建x轴和y轴，x周分度值为1
data = np.zeros((256, 2), dtype=int)
data[..., 0] = np.arange(256)
# 统计每个像素值的结果
for i in lena:
    for j in i:
        data[j, 1] += 1
# 打印统计结果
print(data)
# 画直方图
plt.bar(data[..., 0], data[..., 1], color='g')

plt.show()