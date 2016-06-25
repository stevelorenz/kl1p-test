#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
# About  : Plot MSE results with SNR=20db
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-03-13
"""

import csv

import numpy as np
import matplotlib.pyplot as plt

# get csv data snr_20db
mean_array_omp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/MSEMean_OMP_20db.csv", "r"), delimiter=','))).astype('float')
std_array_omp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/MSEStd_OMP_20db.csv", "r"), delimiter=','))).astype('float')

# get csv data
mean_array_cosamp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/MSEMean_CoSaMP_20db.csv", "r"), delimiter=','))).astype('float')
std_array_cosamp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/MSEStd_CoSaMP_20db.csv", "r"), delimiter=','))).astype('float')

# get csv data
mean_array_amp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/MSEMean_AMP_20db.csv", "r"), delimiter=','))).astype('float')
std_array_amp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/MSEStd_AMP_20db.csv", "r"), delimiter=','))).astype('float')

# get csv data
mean_array_bp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/MSEMean_Basis-Pursuit_20db.csv", "r"), delimiter=','))).astype('float')
std_array_bp = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/MSEStd_Basis-Pursuit_20db.csv", "r"), delimiter=','))).astype('float')

# get array parameters
row_num = len(mean_array_omp)
col_num = len(mean_array_omp[1])

print(row_num, col_num)

plt.suptitle("MSE with SNR=20db")

# adjust subplots
plt.subplots_adjust(hspace=0.35, wspace=0.3)

# subplot 1: OMP 20db
# -----------------------------------------------------------------------------
ax1 = plt.subplot(2, 2, 1)
plt.title("OMP", fontsize=10)
plt.xlabel("m", fontsize=10)
plt.ylabel("MSE", fontsize=10)
plt.ylim(0, 0.5)
plt.grid()

k_10 = mean_array_omp[:, 9]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_10
plt.plot(x_axis, y_axis, color='green', label='k=10', lw=1, ls='-')

k_30 = mean_array_omp[:, 29]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_30
plt.plot(x_axis, y_axis, color='blue', label='k=30', lw=1, ls='-')

k_60 = mean_array_omp[:, 59]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_60
plt.plot(x_axis, y_axis, color='black', label='k=60', lw=1, ls='-')

handles, labels = ax1.get_legend_handles_labels()
ax1.legend(handles, labels, fontsize=8)
# -----------------------------------------------------------------------------

# subplot 2: CoSaMP 20db
# -----------------------------------------------------------------------------
ax2 = plt.subplot(2, 2, 2)
plt.title("CoSaMP", fontsize=10)
plt.xlabel("m", fontsize=10)
plt.ylabel("MSE", fontsize=10)
plt.ylim(0, 0.5)
plt.grid()

k_10 = mean_array_cosamp[:, 9]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_10
plt.plot(x_axis, y_axis, color='green', label='k=10', lw=1, ls='-')

k_30 = mean_array_cosamp[:, 29]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_30
plt.plot(x_axis, y_axis, color='blue', label='k=30', lw=1, ls='-')

k_60 = mean_array_cosamp[:, 59]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_60
plt.plot(x_axis, y_axis, color='black', label='k=60', lw=1, ls='-')

handles, labels = ax2.get_legend_handles_labels()
ax2.legend(handles, labels, fontsize=8)
# -----------------------------------------------------------------------------

# subplot 3 AMP 20db
# -----------------------------------------------------------------------------
ax3 = plt.subplot(2, 2, 3)
plt.title("AMP", fontsize=10)
plt.xlabel("m", fontsize=10)
plt.ylabel("MSE", fontsize=10)
plt.ylim(0, 0.5)
plt.grid()

k_10 = mean_array_amp[:, 9]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_10
plt.plot(x_axis, y_axis, color='green', label='k=10', lw=1, ls='-')

k_30 = mean_array_amp[:, 29]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_30
plt.plot(x_axis, y_axis, color='blue', label='k=30', lw=1, ls='-')

k_60 = mean_array_amp[:, 59]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_60
plt.plot(x_axis, y_axis, color='black', label='k=60', lw=1, ls='-')

handles, labels = ax3.get_legend_handles_labels()
ax3.legend(handles, labels, fontsize=8)
# -----------------------------------------------------------------------------

# subplot 4 BP 20db
# -----------------------------------------------------------------------------
ax4 = plt.subplot(2, 2, 4)
plt.title("BP", fontsize=10)
plt.xlabel("m", fontsize=10)
plt.ylabel("MSE", fontsize=10)
plt.ylim(0, 0.5)
plt.grid()

k_10 = mean_array_bp[:, 9]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_10
plt.plot(x_axis, y_axis, color='green', label='k=10', lw=1, ls='-')

k_30 = mean_array_bp[:, 29]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_30
plt.plot(x_axis, y_axis, color='blue', label='k=30', lw=1, ls='-')

k_60 = mean_array_bp[:, 59]
x_axis = np.arange(1, row_num + 1, 1)
y_axis = k_60
plt.plot(x_axis, y_axis, color='black', label='k=60', lw=1, ls='-')

handles, labels = ax4.get_legend_handles_labels()
ax4.legend(handles, labels, fontsize=8)
# -----------------------------------------------------------------------------

# save picture
plt.savefig('mse_20db.png', dpi=300)
