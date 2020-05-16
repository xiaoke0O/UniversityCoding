import sys
import numpy as np


def otsuthresh(src):
    if src.ndim > 2:
        raise Exception('输入图像不是灰度图像')

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