#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
# About  : Evaluate the simularity of two matrix
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-03-14 16:20
"""

import csv

import numpy as np
from scipy.stats.mstats import kruskalwallis

# get csv data
mean_array_amp = np.array(list(csv.reader(open("../../test_results/sensing_matrix_kl1p/pc/snr_10db/SuccessMean_AMP_10db.csv", "r"), delimiter=','))).astype('float')
mean_array_bp = np.array(list(csv.reader(open("../../test_results/sensing_matrix_kl1p/pc/snr_10db/SuccessMean_Basis-Pursuit_10db.csv", "r"), delimiter=','))).astype('float')

mean_array_omp = np.array(list(csv.reader(open("../../test_results/sensing_matrix_kl1p/pc/snr_10db/SuccessMean_OMP_10db.csv", "r"), delimiter=','))).astype('float')
mean_array_cosamp = np.array(list(csv.reader(open("../../test_results/sensing_matrix_kl1p/pc/snr_10db/SuccessMean_CoSaMP_10db.csv", "r"), delimiter=','))).astype('float')

row_num = len(mean_array_amp)
col_num = len(mean_array_amp[0])

num_elements = row_num * col_num

# reshape the data
mean_vector_amp = np.reshape(mean_array_amp, (1, num_elements))
mean_vector_bp = np.reshape(mean_array_bp, (1, num_elements))

mean_vector_omp = np.reshape(mean_array_omp, (1, num_elements))
mean_vector_cosamp = np.reshape(mean_array_cosamp, (1, num_elements))

# plot the sse between two vectors
# -------------------------------------------------------------------
#  diff_array = np.square(mean_vector_amp - mean_vector_bp)
#  diff_vector = diff_array[0]

#  x_axis = np.arange(1, num_elements + 1, 1)
#  y_axis = diff_vector

#  plt.plot(x_axis, y_axis, color='black', label='', lw=1, ls='-',
#  marker='o', markerfacecolor='None', markeredgewidth=1, markeredgecolor='black', markevery=10)
#  plt.show()

# -------------------------------------------------------------------

# use some criterion for the simularity of two vectors
# -------------------------------------------------------------------
# 1.caculate the square differenz between two vectors
sq_diff_ab = np.square(mean_vector_amp - mean_vector_bp)
sse_ab = np.sum(sq_diff_ab)
norm_ab = np.sqrt(sse_ab)
print('the L2-Norm is %.2f' % norm_ab)

# 2.threshold and ratio
counter = 0
threshold = 0.01
print('the threshold is %.2f%%' % (threshold * 100))
for i in range(num_elements):
    diff = np.abs(mean_vector_amp[0][i] - mean_vector_bp[0][i])
    if diff <= threshold:
        counter += 1
ratio = float(counter) / num_elements
print('the ratio is %.2f%%' % (ratio * 100))

# 3.caculate the correlation between two vectors
cocoef_matrix = np.corrcoef(mean_array_amp, mean_array_bp)
cocoef = cocoef_matrix[0, 1]
print('the correlation coefficient is %0.3f' % cocoef)

# 4.kruskalwallis test for median difference between two distribution
H, pvalue = kruskalwallis(mean_vector_amp[0], mean_vector_bp[0])
print('the p-value is %.2f' % pvalue)

if pvalue > 0.05:
    print("accept null hypothesis: no significant difference between two groups")
# -------------------------------------------------------------------
