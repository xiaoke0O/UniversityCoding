import numpy as np
from math import sin, cos

# 左像的外方位元素
varphi1 = -0.005785603
omega1 = 0.0003784083
kappa1 = -0.01880947
Xs1 = 432438.565
Ys1 = 3894841.049
Zs1 = 1274.012

# 右像的外方位元素
varphi2 = -0.006604103
omega2 = 0.0005394704
kappa2 = 0.0007619388
Xs2 = 432847.537
Ys2 = 3894836.718
Zs2 = 1272.414

# 摄影基线的三个分量
Bx = Xs2 - Xs1
By = Ys2 - Ys1
Bz = Zs2 - Zs1
focal_length = 70.5  # mm

# 同名像点在左像的坐标
Left_image_coordinate = np.array([29.214000, -47.640000, -focal_length])
# 同名像点在右像的坐标
Right_image_coordinate = np.array([3.936000, -47.910000, -focal_length])

# 左像片的旋转矩阵
Left_Rotate = np.zeros((3, 3))
Left_Rotate[0, 0] = cos(varphi1) * cos(kappa1) - sin(varphi1) * sin(omega1) * sin(kappa1)
Left_Rotate[0, 1] = (-1.0) * cos(varphi1) * sin(kappa1) - sin(varphi1) * sin(omega1) * cos(kappa1)
Left_Rotate[0, 2] = (-1.0) * sin(varphi1) * cos(omega1)
Left_Rotate[1, 0] = cos(omega1) * sin(kappa1)
Left_Rotate[1, 1] = cos(omega1) * cos(kappa1)
Left_Rotate[1, 2] = (-1.0) * sin(omega1)
Left_Rotate[2, 0] = sin(varphi1) * cos(kappa1) + cos(varphi1) * sin(omega1) * sin(kappa1)
Left_Rotate[2, 1] = (-1.0) * sin(varphi1) * sin(kappa1) + cos(varphi1) * sin(omega1) * cos(kappa1)
Left_Rotate[2, 2] = cos(varphi1) * cos(omega1)

# 右像片的旋转矩阵
Right_Rotate = np.zeros((3, 3))
Right_Rotate[0, 0] = cos(varphi2) * cos(kappa2) - sin(varphi2) * sin(omega2) * sin(kappa2)
Right_Rotate[0, 1] = (-1.0) * cos(varphi2) * sin(kappa2) - sin(varphi2) * sin(omega2) * cos(kappa2)
Right_Rotate[0, 2] = (-1.0) * sin(varphi2) * cos(omega2)
Right_Rotate[1, 0] = cos(omega2) * sin(kappa2)
Right_Rotate[1, 1] = cos(omega2) * cos(kappa2)
Right_Rotate[1, 2] = (-1.0) * sin(omega2)
Right_Rotate[2, 0] = sin(varphi2) * cos(kappa2) + sin(varphi2) * sin(omega2) * sin(kappa2)
Right_Rotate[2, 1] = (-1.0) * sin(varphi2) * sin(kappa2) + cos(varphi2) * sin(omega2) * cos(kappa2)
Right_Rotate[2, 2] = cos(varphi2) * cos(omega2)

# 同名像点的像空间辅助坐标
Left_aux_coordinate = Left_Rotate * Left_image_coordinate
Right_aux_coordinate = Right_Rotate * Right_image_coordinate

# 计算投影系数Left_N Right_N
X1 = Left_aux_coordinate[0, 0]
Y1 = Left_aux_coordinate[1, 0]
Z1 = Left_aux_coordinate[2, 0]

X2 = Right_aux_coordinate[0, 0]
Y2 = Right_aux_coordinate[1, 0]
Z2 = Right_aux_coordinate[2, 0]

Left_N = (Bx * Z2 - Bz * X2) / (X1 * Z2 - X2 * Z1)
Right_N = (Bx * Z1 - Bz * X1) / (X1 * Z2 - X2 * Z1)

# 计算地面点的左像像辅系坐标
delta_X = Left_N * X1
delta_Y = (Left_N * Y1 + Right_N * Y2 + By) / 2.0
delta_Z = Left_N * Z1
print("地面点的左像像辅系坐标\n{0:.3f},{1:.3f},{2:.3f}\n".format(delta_X, delta_Y, delta_Z))
# 地面点的地面坐标
ground_X = Xs1 + delta_X
ground_Y = Ys1 + delta_Y
ground_Z = Zs1 + delta_Z
print("地面点的地面坐标\n{0:.3f},{1:.3f},{2:.3f}\n".format(ground_X, ground_Y, ground_Z))
