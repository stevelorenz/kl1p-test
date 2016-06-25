#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
# About  : Plot Success Mean in Contourf for OMP and CoSaMP
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-03-30
"""

import csv

import numpy as np
import matplotlib.pyplot as plt

# get csv data
succ_array_omp_10db = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_10db/SuccessMean_OMP_10db.csv", "r"), delimiter=','))).astype('float')
succ_array_omp_20db = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/SuccessMean_OMP_20db.csv", "r"), delimiter=','))).astype('float')

succ_array_cosamp_10db = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_10db/SuccessMean_CoSaMP_10db.csv", "r"), delimiter=','))).astype('float')
succ_array_cosamp_20db = np.array(list(csv.reader(open("../../../test_results/sensing_matrix_kl1p/pc/snr_20db/SuccessMean_CoSaMP_20db.csv", "r"), delimiter=','))).astype('float')

# get array parameters

row_num = len(succ_array_omp_10db)
col_num = len(succ_array_omp_10db[1])

# --- use contourf plot ---

plt.suptitle("Success Rate OMP CoSaMP")

# adjust subplots
plt.subplots_adjust(hspace=0.35, wspace=0.3)

# set colorbar
cb = np.linspace(0, 1, 5, endpoint=True)

# subplot 1: OMP 10db
# -----------------------------------------------------------------------------
ax1 = plt.subplot(2, 2, 1)
plt.title("OMP SNR=10db", fontsize=10)
plt.xlabel("k", fontsize=10)
plt.ylabel("m", rotation=0, fontsize=10)
ct1 = plt.contourf(succ_array_omp_10db, origin='lower')

# subplot 2: OMP 20db
# -----------------------------------------------------------------------------
ax2 = plt.subplot(2, 2, 2)
plt.xlabel("k", fontsize=10)
plt.ylabel("m", rotation=0, fontsize=10)
plt.title("OMP SNR=20db", fontsize=10)
ct2 = plt.contourf(succ_array_omp_20db, origin='lower')
cbar = plt.colorbar(ticks=cb)

# subplot 3: CoSaMP 10db
# -----------------------------------------------------------------------------
ax3 = plt.subplot(2, 2, 3)
plt.title("CoSaMP SNR=10db", fontsize=10)
plt.xlabel("k", fontsize=10)
plt.ylabel("m", rotation=0, fontsize=10)
ct3 = plt.contourf(succ_array_cosamp_10db, origin='lower')

# subplot 4: CoSaMP 20db
# -----------------------------------------------------------------------------
ax4 = plt.subplot(2, 2, 4)
plt.title("CoSaMP SNR=20db", fontsize=10)
plt.xlabel("k", fontsize=10)
plt.ylabel("m", rotation=0, fontsize=10)
ct4 = plt.contourf(succ_array_cosamp_20db, origin='lower')

# save picture
plt.savefig('succ_omp_cosamp.png', dpi=300)
