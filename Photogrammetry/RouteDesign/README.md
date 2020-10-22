# 航线设计

已知值

| 项目                  | 值              |
| --------------------- | --------------- |
| 摄影比例尺            | 1：1000         |
| 地面采样间隔 $D$      | 10cm            |
| 航向重叠度$q_x$       | 0.85            |
| 旁向重叠度 $q_y$      | 0.6             |
| 像元大小 $d$          | 3.92μ           |
| 像幅大小$n_x$ $n_y$   | 6000行 × 4000行 |
| 焦距 $f$              | 15.6mm          |
| 平均高程面 $h_{平均}$ | 90米            |
| 测区长度              | 2073.676米      |
| 测区宽度              | 1389.065米      |

待求值

| 项目                   | 值   |
| ---------------------- | ---- |
| 绝对航高 $H_{绝对}$    |      |
| 调整后航向重叠度 $q_x$ |      |
| 调整后航向重叠度 $q_y$                      |      |
| 摄影基线 $B$           |      |
| 航线间隔              |      |



## 计算（绝对）航高

$$
H_{摄影}=\frac{D}{d}f=\frac{0.1}{0.00000392}\times0.0156=397.859米
$$
$$
H_{绝对}=H_{摄影}+h_{平均}=397.959+90=487.959米
$$



## 调整重叠度

摄区最大高程未知，$\Delta h$未知，假设地面平坦，重叠度保持不变。

## 计算摄影基线与航线间隔

$$
B=(1-q_x)ml_x=(1-q_x)Dn_x=(1-0.85)\times0.1\times6000=90米
$$
$$
航线间隔=(1-q_y)ml_y=(1-q_y)Dn_y=(1-0.6)\times0.1\times4000=160米
$$

## 航线数目

$$
N_2=INT(\frac{测区宽度}{航线间隔}+0.5)+1=INT(\frac{1389.065}{160}+0.5)+1=10
$$



## 每条航线像片数

$$
N_1=INT(\frac{测区长度}{B}+0.5)+3=INT(\frac{2073.676}{90}+0.5)+3=26
$$

## 相片总数

$$
N=N_1\cdot N_2=260
$$