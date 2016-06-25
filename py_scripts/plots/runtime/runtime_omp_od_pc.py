#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
# About  : Runtime on Odroid divided by on PC for OMP surface plot
# Author : Xiang, Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-03-31
"""

import csv

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

# get csv data
runtime_omp_pc= np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/without_noise/RunTimeMean_OMP.csv", "r"), delimiter=','))).astype('float')
runtime_omp_od= np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/odroid/RunTimeMean_OMP_odroid.csv", "r"), delimiter=','))).astype('float')

# odroid only up to k=60 getested
runtime_omp_pc = runtime_omp_pc[:, 0:60]

# x and y axis
X = np.arange(1, 61, 1)
Y = np.arange(1, 126, 1)

Y, X = np.meshgrid(X, Y)  # creat a base grid

# z axis
Z = np.divide(runtime_omp_od, runtime_omp_pc)
#  Z = runtime_omp_od - runtime_omp_pc

# --- plot runtime using surface ---
fig = plt.figure()
ax = fig.gca(projection='3d')         # set the 3d axes
plt.gca().invert_xaxis()              # invert x axis

surf = ax.plot_surface(X, Y, Z,
                alpha=0.8,            # transparency of the surface
                cmap=cm.coolwarm)         # colour map

# fig settings
plt.title("OMP-Odroid divided by PC", y=1.08)
ax.set_xlabel("m")
ax.set_ylabel("k")
ax.set_zlabel("runtime(ms)")
ax.set_zlim(0, 10)
ax.view_init(elev=25, azim=-58)           # elevation and angle
ax.dist=8.5
# add colorbar
fig.colorbar(surf, shrink=0.8, orientation="horizontal")

# save picture
plt.savefig('runtime_omp_od_pc.png', dpi=300)
