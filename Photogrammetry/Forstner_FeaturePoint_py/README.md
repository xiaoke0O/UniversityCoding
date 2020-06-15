# Forstner特征提取程序--Python/MALIAB版

**MATLAB**版本来自老师课件，并有些许小小更改

**Python** 版参照MATLAB，并自己实现了如RGB2GRAY、OTSU算法（大津算法）获取最佳二值化阈值等函数

## 处理结果

> 点击图片查看大图

<img src="https://www.superbed.cn/item/5e7700df5c560911298d5019.png" style="zoom:150%;" />


<center>MATLAB处理结果</center>

![Matlab版本](https://pic.downk.cc/item/5e76111c9d7d586a540e2728.png)

<center>Python处理结果</center>

<img src="https://www.superbed.cn/item/5e76ffac5c560911298c4435.png" alt="Python版本" style="zoom:150%;" />

<center>MATLAB处理结果</center>

<img src="https://www.superbed.cn/item/5e76fb615c5609112988da6d.png" alt="Matlab版本" style="zoom:150%;" />

## 目前存在的问题

1. ~~两个版本的结果不一致。二值化后的结果是一致的，初步选点结果不一致，以至于以后的结果均不一致。**尚不知问题所在**~~
2. ~~Python版本的最后一图，即叠加显示图，不能自定义点样式，故显示效果不佳。尚不知更佳方法~~
3. 大量使用嵌套for循环（最深的嵌套有4层），严重拖慢运行速度。后期会用C和指针重写，遍历效率应该有提高

## 流程

1. 读取图像
2. 二值化处理getBinary
3. 用差分算子初步提取getPrimaryPoints
4. 以初选点为中心，按照Forstner算子计算协方差矩阵与权值，并与阈值比较，进一步筛选getCovMatrix
5. 以第4步的进一步筛选结果为基础，按照权值获取极大值，即为特征点getResult
6. 画出全部子图，并将最终结果叠加显示

## 遇到的坑

### MATLAB

1. 二值化。老师给的二值化函数`im2bw`在新版中已经不推荐使用，官方推荐的是`imbinarize`,默认阈值为自动调用otsu算法计算所得。`imbinarize`具体用法
2. 显示效果。默认的6张子图显示比较小，需要手工调整间距和图像大小。当然可以在代码中预先设定。

### Python

> 为了避免造成使用了OpenCV特征点提取的嫌疑，没有用OpenCV模块

1. 图像读取。除了OpenCV，我知道的两种读取图像的方法是matplotlib中的Image子模块和PIL库

   1. matplotlib.Image模块只能读取png格式，除非安装Pillow库，就是后面要讲的PIL库。

   2. matplotlib.Image模块读取的图像数据类型默认是float32，但是这在for循环遍历像元统计直方图的时候是个麻烦

      ```python
      # 直方图统计算法
      Grayscale = 256
          graynum = np.zeros(Grayscale, dtype=int)
          for i in src:
              for j in i:
                  graynum[j] += 1
      ```

      可以看到，如果读进来的的`src`是float32,显然不行，因为`j`必须是int。如果对src强制类型转换，无疑加大工作量。故不可取。更多解决方法可看这篇[stackoverflow解答](https://stackoverflow.com/questions/46013594/matplotlib-reads-jpg-into-int8-and-png-into-normalized-float)
   3. PIL.Image模块读进来的图像是uint8，但是他的数据类型是自己的Image格式，同样无法用numpy的方式索引，解决方法是以PIL.Image模块读进来的内容为基础，新建numpy数组`im = np.asarray(Image.open("house.png"))`

2. 二值化。matplotlib.Image模块，没有二值化函数。PIL.Image模块，有二值化函数但是不能自定义阈值。解决方法是自己实现了一个用otsu算法的二值化函数

3. 像素计算。起初为了减小资源占用，将二值化保存成了bool型，但是Python不支持bool型用减法，遂改用逻辑异或（xor）运算，符号是^，但这样作在后来的计算权矩阵的计算结果会出错，牵涉数据类型和运算问题，导致不会出结果。解决方法是统一使用uint8数据类型。

4. 函数参数传递问题。numpy数组的传递是引用传递，而非值传递。什么意思呢，请看下面代码

	```python
	import numpy as np

	def Demo(inputs):
	    outputs=inputs
	    outputs[2,2]=0
	    return outputs

	if __name__=='__main__':
	    inputarray=np.ones([4,4],dtype=int)
	    print('*****input原始值********')
	    print(inputarray)
	    print('*****output值********')
	    outputarray=Demo(inputarray)
	    print(outputarray)
	    print('*****input现在值********')
	    print(inputarray)
	    print('******input也变了*******')
	```
	输出结果

	```txt
	*****input原始值********
	[[1 1 1 1]
	 [1 1 1 1]
	 [1 1 1 1]
	 [1 1 1 1]]
	*****output值********
	[[1 1 1 1]
	 [1 1 1 1]
	 [1 1 0 1]
	 [1 1 1 1]]
	*****input现在值********
	[[1 1 1 1]
	 [1 1 1 1]
	 [1 1 0 1]
	 [1 1 1 1]]
	******input也变了*******
	```
	
	可以看到，在Demo函数中改变output的值，input的值也发生了变化！！
	
	我们的目的是什么，是把input的值赋给output然后对output进行操作，再输出output。pythoin对于numpy数组作为参数，使用的是引用传递，类似于C中的指针概念。当我们调用Demo函数的时候，传进来的是inputs的指针，第二行我们将outputs指针指向inputs。下面的对outputs的操作，实际是对inputs的操作。所以最后inputs和outputs的结果是一样的。
	
	```python
	def Demo(inputs):
	    outputs=inputs
	    outputs[2,2]=0
	    return outputs
	```
	
	解决方法就是不用`outputs=inputs`，改用`outputs=inputs.copy()`
	
5. 数组索引。Matlab的索引是从闭区间。如`for i=1:5`，那么`i=1,2,3,4,5`。Python中是左闭右开。

6. 一维数组索引时要分别规定行列号。如`a=[1,2,3,4,5]`，表示第二个数要用`a[0,1]`，而不能用`a[1]`

7. matplotlib画图颜色的指定。在matlab中`plot(a,'r+')`会将点画成红色的+型。Python中需要分别指定颜色和形状。（起码在spy函数中是这样）
