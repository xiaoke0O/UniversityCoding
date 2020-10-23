import os
import pandas as pd
from numpy import sin, cos, zeros, array, dot, linalg

'''
读取点文件
并判断点文件是否存在，不存在既终止程序
'''
left_points_dir = 'points/left_points.txt'
right_points_dir = 'points/right_points.txt'
if not os.path.exists(left_points_dir) or not os.path.exists(right_points_dir):
    print('file not exit')
    exit()
left_points = pd.read_table(left_points_dir, header=None, sep='\s+')
right_points = pd.read_table(right_points_dir, header=None, sep='\s+')

'''
确定初始值
'''
Bx = left_points.iloc[0, 0] - right_points.iloc[0, 0]
By, Bz = 0, 0
varphi, omega, kappa = 0, 0, 0
focal_length = 24  # mm
'''
大循环
'''
j = 0
right_rotate = zeros([3, 3], dtype=float)
A = zeros([left_points.shape[0], 5], dtype=float)
Q = zeros([left_points.shape[0], 1], dtype=float)
while 1:
    # 右片的旋转矩阵right_rotate
    right_rotate[0, 0] = cos(varphi) * cos(kappa) - sin(varphi) * sin(omega) * sin(kappa)
    right_rotate[0, 1] = -cos(varphi) * sin(kappa) - sin(varphi) * sin(omega) * cos(kappa)
    right_rotate[0, 2] = -sin(varphi) * cos(omega)
    right_rotate[1, 0] = cos(omega) * sin(kappa)
    right_rotate[1, 1] = cos(omega) * cos(kappa)
    right_rotate[1, 2] = -sin(omega)
    right_rotate[2, 0] = sin(varphi) * cos(kappa) + cos(varphi) * sin(omega) * sin(kappa)
    right_rotate[2, 1] = sin(varphi) * sin(kappa) + cos(varphi) * sin(omega) * cos(kappa)
    right_rotate[2, 2] = cos(varphi) * cos(omega)
    '''
    小循环
    计算
    所有左像点的像空系坐标
    所有右像点的像空系坐标
    所有左像点的点投影系数
    所有右像点的点投影系数
    所有上下视差
    计算系数矩阵
    '''
    for i in range(left_points.shape[0]):
        # 左像像空系坐标
        X1 = left_points.iloc[i, 0]
        Y1 = left_points.iloc[i, 1]
        Z1 = -focal_length
        # 右像像空系坐标
        right_space = right_rotate.dot(
            array([[right_points.iloc[i, 0]], [right_points.iloc[i, 1]], [-focal_length]]))
        X2 = right_space[0, 0]
        Y2 = right_space[1, 0]
        Z2 = right_space[2, 0]
        # 左右像点投影系数和Q
        left_N = (Bx * Z2 - Bz * X2) / (X1 * Z2 - X2 * Z1)
        right_N = (Bx * Z1 - Bz * X1) / (X1 * Z2 - X2 * Z1)
        Q[i] = left_N * Y1 - right_N * Y2 - By

        A[i, 0] = X2 * Y2 / focal_length
        A[i, 1] = focal_length + (Y2 ** 2 / focal_length)
        A[i, 2] = X2
        A[i, 3] = 1
        A[i, 4] = Y2 / focal_length
    # 最小二乘法
    ATA = dot(A.transpose(), A)
    ATAT = (linalg.inv(ATA)).dot(A.transpose())
    X = ATAT.dot(Q)

    # if abs(X[0, 0]) < 1E-5 and abs(X[1, 0]) < 1E-5 and abs(X[2, 0]) < 1E-5 and abs(X[3, 0]) < 1E-5 and abs(
    #         X[4, 0]) < 1E-5:
    if abs(X[0, 0]) < 1E-5 and abs(X[1, 0]) < 1E-5 and abs(X[2, 0]) < 1E-5:
        break

    varphi += X[0, 0]
    omega += X[1, 0]
    kappa += X[2, 0]
    By += X[3, 0]
    Bz += X[4, 0]
    j += 1
    print("varphi={0:.4f},omega={1:.4f},kappa={2:.4f}".format(varphi, omega, kappa))

print(j)
print(X)
