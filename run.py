#!/usr/bin/python3
# -*- coding: utf-8 -*-
# #########################################################
# About  : Run CS Test using cpp programm csTest
# Author : Xiang,Zuo
# E-Mail : xianglinks@gmail.com
# Date   : 2016-01-31 17:20:14
# #########################################################

import os
import sys
from os import mkdir
from os.path import isdir

# testing cs-algorithms list
algorithms = ['OMP', 'ROMP', 'CoSaMP', 'Subspace-Pursuit', 'SL0', 'AMP', 'EMBP', 'Basis-Pursuit']


# main fuction
# ---------------------------------------------------------------------------------------
def main():
    try:
        # check if results dir exits
        results_root_dir = './tmp_results'
        if isdir(results_root_dir):
            print('the test results will be saved in %s' % results_root_dir)
        else:
            mkdir(results_root_dir)
            print('the test results will be saved in %s' % results_root_dir)
        print('------------------------------------------------------')

        print('cs-algorithms testing programm started.')

        # get parameters from cli
        n = int(input("input n: "))
        m_min = int(input("input m_min: "))
        m_max = int(input("input m_max: "))
        k_min = int(input("input k_min: "))
        k_max = int(input("input k_max: "))
        num_rounds = int(input("input num_rounds: "))
        noise_flag = int(input("add noise or not(0 for not, 1 for yes): "))
        if(noise_flag == 0):
            snr = 0  # value is irrelevant
            print("testing without noise")
        if(noise_flag == 1):
            snr = float(input('input SNR(dB) for testing with AWGN: '))

        # choose cs-algorithms for testing
        print('--------------------------------------------')
        print('cs-algorithms list: ')
        for i in range(len(algorithms)):
            print('[%d] ' %(i + 1) + algorithms[i])
        print('--------------------------------------------')

        algo_num_list = input('choose testing cs-algorithms(number splitted with space) type 0 for all algorithms: ')
        algo_num_list = algo_num_list.split(' ')
        algo_num_list = list(map(int, algo_num_list))

        # print signal infos
        print('--------------------------------------------')
        print('length of original signal is %d' % n)
        print('number of measurements is from %d to %d' % (m_min, m_max))
        print('sparcity of signal is from %d to %d' % (k_min, k_max))
        print('number of rounds is  %d' % num_rounds)
        print('SNR for testing with AWGN is %.2fdB' % snr)
        print('--------------------------------------------')

        if algo_num_list[0] == 0:
            # testing all algorithms
            for i in range(len(algo_num_list)):
                testCSAlgorithm(i + 1, n, m_min, m_max, k_min, k_max, num_rounds, noise_flag, snr)
        else:
            for algo_num in algo_num_list:
                testCSAlgorithm(algo_num, n, m_min, m_max, k_min, k_max, num_rounds, noise_flag, snr)

    except KeyboardInterrupt:
        print("get keyboardInterrupt! exit ...")
        sys.exit(0)
# ---------------------------------------------------------------------------------------


##
# @brief testCSAlgorithm
#
# @param algo_num
# @param n
# @param m_min
# @param m_max
# @param k_min
# @param k_max
# @param num_rounds
#
# @return
def testCSAlgorithm(algo_num, n, m_min, m_max, k_min, k_max, num_rounds, noise_flag, snr):

    # init basic file paths
    src_file_path = ["./csv_matrix/MSEMean_", "./csv_matrix/MSEStd_", "./csv_matrix/RunTimeMean_", "./csv_matrix/RunTimeStd_",
                     "./csv_matrix/SuccessMean_", "./csv_matrix/SuccessStd_"]

    dst_file_path = ["./tmp_results/MSEMean_", "./tmp_results/MSEStd_", "./tmp_results/RunTimeMean_", "./tmp_results/RunTimeStd_",
                     "./tmp_results/SuccessMean_", "./tmp_results/SuccessStd_"]

    src_file = [None] * len(src_file_path)
    dst_file = [None] * len(src_file_path)

    # get src and dst files
    algo_name = algorithms[algo_num - 1]

    for i in range(len(src_file_path)):
        src_file_path[i] += algo_name + '.csv'

    for i in range(len(dst_file_path)):
        dst_file_path[i] += algo_name + '.csv'

    # clean dst_file for new test
    for file_path in dst_file_path:
        with open(file_path, 'w+') as file:
            file.write('')
            file.close()
    #  choose = input("Do you want to clear file(y/n)? ")
    #  if choose == 'y':

    # --- run test programm ---
    for m in range(m_min, m_max + 1, 1):
        exec = "./test-cs %d %d %d %d %d %d %d %d %d" %(n, m, m, k_min, k_max, num_rounds, algo_num, noise_flag, snr)
        #  print(exec)
        os.system(exec)
        print("end test with m=%d" % m)

        # file operations
        for j in range(len(src_file_path)):
            # get file pointer
            src_file[j] = open(src_file_path[j], 'r')
            dst_file[j] = open(dst_file_path[j], 'a')

            # write new data in results file
            read_lines = src_file[j].readlines()
            write_line = read_lines[m - 1]
            dst_file[j].write(write_line)

    for i in range(len(src_file)):
        src_file[i].close()
        dst_file[i].close()

if __name__ == '__main__':
    main()
