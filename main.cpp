// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// --------------------------------------------------------------------------------------
// About  : Main function for cs-algorithms testing
// Date   : 2016-01-22 09:10:38
// Author : Xiang,Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>

#include "Constants.h"
#include "CreatSignal.h"
#include "TestCSAlgorithm.h"
#include "DataProc.h"
#include "MatrixIO.h"

using namespace kl1p;
using std::string;

// Init parameters
klab::UInt32 n = 250;	     // Size of the original signal x0.
klab::UInt32 m_min = 1;	     // Number of cs-measurements minimum
klab::UInt32 m_max = 125;	 // Number of cs-measurements maximum
klab::UInt32 k_min = 1;      // Sparsity of the signal x0 (number of non-zero elements) minimum
klab::UInt32 k_max = 30;     // Sparsity of the signal x0 (number of non-zero elements) maximum
klab::UInt64 seed = 0;	     // Seed used for random number generation (0 if regenerate random numbers on each launch).
klab::UInt32 i = 1;          // number of simulation for each round
klab::UInt32 flag = 1;       // Flag for using different Algorithms, default: OMP
                             // 1 -> OMP, 2 -> ROMP
klab::UInt32 noise_flag;     // Flag for adding noise
klab::DoubleReal snr = 0;    // SNR for testing with AWGN

// Main function
// -------------------------------------------------------------------------------------- //

int main(int argc, char* argv[])
{
    try {
        // Check if MatrixRootDir exists
        struct stat sb;
        if (stat(MatrixRootDir, &sb) == 0 && S_ISDIR(sb.st_mode)) {
            // if dir exists
            printf("the test results will be saved in %s\n", MatrixRootDir);
        }
        else {
            // mkdir if dir not exists
            const int dir_err = mkdir(MatrixRootDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if (-1 == dir_err) {
                printf("Error creating directory!n");
                exit(1);
            }
            else {
                printf("the test results will be saved in %s\n", MatrixRootDir);
            }
        }

        // Get parameters
        if(argc > 1) {
            n = atoi(argv[1]);
            m_min = atoi(argv[2]);
            m_max = atoi(argv[3]);
            k_min = atoi(argv[4]);
            k_max = atoi(argv[5]);
            i = atoi(argv[6]);
            flag = atoi(argv[7]);
            noise_flag = atoi(argv[8]);
            snr = atoi(argv[9]);
        }

        else {
            std::cout<<"---------------------------------------------"<<std::endl;
            std::cout<<"init parameters: "<<std::endl;
            std::cout<<"length of original signal -> n: "; std::cin>>n;
            std::cout<<"number of measurements -> m_min and m_max(split with space): "; std::cin>>m_min>>m_max;
            std::cout<<"sparsity of signal -> k_min and k_max(split with space): "; std::cin>>k_min>>k_max;
            std::cout<<"rounds for each simulation -> i = "; std::cin>>i;
            std::cout<<"add noise or not(0 for not, 1 for yes) -> noise_flag = "; std::cin>>noise_flag;

            if(noise_flag == 1) {
                std::cout<<"SNR for testing with AWGN -> SNR(dB) = "; std::cin>>snr;
            }
            if(noise_flag == 0) {
                std::cout<<"testing without noise"<<std::endl;
            }

            std::cout<<"cs-algorithms list: "<<std::endl;
            klab::UInt32 numberOfList = sizeof(algorithms) / sizeof(algorithms[0]);
            for(klab::UInt32 index_algo=0; index_algo<numberOfList; index_algo++) {
                std::cout<<"["<<index_algo + 1<<"] "<<algorithms[index_algo] + "  ";
            }
            std::cout<<std::endl<<"choose cs-algorithm to test(type number): "; std::cin>>flag;
        }

        std::cout<<"using cs-algorithm: "<<algorithms[flag-1]<<std::endl;
        std::cout<<"---------------------------------------------"<<std::endl;

        // Init struct and matrix for results
        resultStruct resultArray;

        arma::Mat<klab::DoubleReal> runTimeMeanMat(m_max, k_max);
        arma::Mat<klab::DoubleReal> mseMeanMat(m_max, k_max);
        arma::Mat<klab::DoubleReal> successMeanMat(m_max, k_max);

        arma::Mat<klab::DoubleReal> runTimeStdMat(m_max, k_max);
        arma::Mat<klab::DoubleReal> mseStdMat(m_max, k_max);
        arma::Mat<klab::DoubleReal> successStdMat(m_max, k_max);

        // Get output CSV file names
        RunTimeMeanMatrixFile += algorithms[flag-1] + CSVEndName;
        RunTimeStdMatrixFile += algorithms[flag-1] + CSVEndName;

        MSEMeanMatrixFile += algorithms[flag-1] + CSVEndName;
        MSEStdMatrixFile += algorithms[flag-1] + CSVEndName;

        SuccessMeanMatrixFile += algorithms[flag-1] + CSVEndName;
        SuccessStdMatrixFile += algorithms[flag-1] + CSVEndName;

        // Measure runTime of programm
        klab::DoubleReal programmRuntime = 0;
        klab::KTimer programmTimer;
        programmTimer.start();

        std::cout<<"start cs-algorithm test with following parameters"<<std::endl;

        // Print signal informations
		std::cout<<"================================================="<<std::endl;
		std::cout<<"n = "<<n<<" (signal size)"<<std::endl;
        std::cout<<"m_min = "<<m_min<<", "<<"m_max = "<<m_max<<" (number of measurements)"<<std::endl;
        std::cout<<"k_min = "<<k_min<<", "<<"k_max = "<<k_max<<" (sparsity of signal)"<<std::endl;
        std::cout<<"number of rounds = "<<i<<std::endl;
        if(noise_flag == 1)
            std::cout<<"testing with AWGN SNR = "<<snr<<"dB"<<std::endl;
        else
            std::cout<<"testing without noise"<<std::endl;
		std::cout<<"================================================="<<std::endl;

        // Init loop index
        klab::UInt32 a;
        klab::UInt32 b;

        // Loop for test with different parameters
        for(a=k_min; a<=k_max; a++) {
            for(b=m_min; b<=m_max; b++) {
                // Run test functions
                    // with b -> m and a-> k
                resultArray = kl1p::testCSAlgorithm(flag, i, b, n, a, seed, noise_flag, snr);

                // Save testing results in results matrix
                runTimeMeanMat.at(b-1, a-1) = resultArray.run_time_mean;
                runTimeStdMat.at(b-1, a-1) = resultArray.run_time_std;

                mseMeanMat.at(b-1, a-1) = resultArray.mse_mean;
                mseStdMat.at(b-1, a-1) = resultArray.mse_std;

                successMeanMat.at(b-1, a-1) = resultArray.success_mean;
                successStdMat.at(b-1, a-1) = resultArray.success_std;
            }  // end m loop

            // Write temp-results matrix to CSV file
            kl1p::WriteMatrixToCSVFile(runTimeMeanMat, RunTimeMeanMatrixFile);
            kl1p::WriteMatrixToCSVFile(runTimeStdMat, RunTimeStdMatrixFile);
            kl1p::WriteMatrixToCSVFile(mseMeanMat, MSEMeanMatrixFile);
            kl1p::WriteMatrixToCSVFile(mseStdMat, MSEStdMatrixFile);
            kl1p::WriteMatrixToCSVFile(successMeanMat, SuccessMeanMatrixFile);
            kl1p::WriteMatrixToCSVFile(successStdMat, SuccessStdMatrixFile);

            // Print debug information
            // std::cout<<"test for "<<algorithms[flag - 1]<<" end loop with m="<<b<<", k="<<a<<std::endl;

        }  //end k loop

        // --- After testing loop ---

        // Write final-results matrix to CSV file
        kl1p::WriteMatrixToCSVFile(runTimeMeanMat, RunTimeMeanMatrixFile);
        kl1p::WriteMatrixToCSVFile(runTimeStdMat, RunTimeStdMatrixFile);
        kl1p::WriteMatrixToCSVFile(mseMeanMat, MSEMeanMatrixFile);
        kl1p::WriteMatrixToCSVFile(mseStdMat, MSEStdMatrixFile);
        kl1p::WriteMatrixToCSVFile(successMeanMat, SuccessMeanMatrixFile);
        kl1p::WriteMatrixToCSVFile(successStdMat, SuccessStdMatrixFile);

        // End test programm
        programmTimer.stop();
        programmRuntime = klab::DoubleReal(programmTimer.durationInMilliseconds()) / 1000.0;
        std::cout<<"Tests finished..."<<std::endl;
        std::cout<<"The runtime of test programm is: "<<programmRuntime<<" s"<<std::endl;
    }

    // Catch Exception
	catch(klab::KException& e)
	{
		std::cout<<"ERROR! KLab exception : "<<klab::FormatExceptionToString(e)<<std::endl;
	}
	catch(std::exception& e)
	{
		std::cout<<"ERROR! Standard exception : "<<klab::FormatExceptionToString(e)<<std::endl;
	}
	catch(...)
	{
		std::cout<<"ERROR! Unknown exception !"<<std::endl;
	}
	return 0;
}

// -------------------------------------------------------------------------------------- //
