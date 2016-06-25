// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// --------------------------------------------------------------------------------------
// About  : Functions to operate arma::Col or Mat
// Date   : 2016-01-19 10:34:23
// Author : Xiang, Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#ifndef MATRIXIO_H
#define MATRIXIO_H

#include <iostream>
#include <string>
#include <KL1pInclude.h>

namespace kl1p
{
void WriteColToCSVFile(const arma::Col<klab::DoubleReal>& signal, const std::string& filePath);
void WriteMatrixToCSVFile(const arma::Mat<klab::DoubleReal> writeMatrix, const std::string filePath);
}

// -------------------------------------------------------------------------------------------------------------------- //

/**
 * @brief Write a vector to a CSV file
 *
 * @param signal
 * @param filePath
 */
void kl1p::WriteColToCSVFile(const arma::Col<klab::DoubleReal>& signal, const std::string& filePath)
{
	std::ofstream of(filePath.c_str());
	if(of.is_open())
	{
		for(klab::UInt32 i=0; i<signal.n_rows; ++i)
			of<<signal[i]<<std::endl;

		of.close();
	}
	else
	{
		std::cout<<"ERROR! Unable to open file \""<<filePath<<"\" !"<<std::endl;
	}
}

// -------------------------------------------------------------------------------------------------------------------- //

/**
 * @brief Write a arma::Mat to a CSV File
 *
 * @param writeMatrix
 * @param file_name
 */
void kl1p::WriteMatrixToCSVFile(const arma::Mat<klab::DoubleReal> writeMatrix, const std::string filePath)
{
    // get of stream
	std::ofstream of(filePath.c_str(), std::ofstream::out | std::ofstream::trunc);

	if(of.is_open())
	{
		for(klab::UInt32 i=0; i<writeMatrix.n_rows; i++) {
            for(klab::UInt32 j=0; j<writeMatrix.n_cols; j++) {
                if(j == (writeMatrix.n_cols - 1))
                    of<<writeMatrix.at(i, j);
                else
                    of<<writeMatrix.at(i, j)<<",";
            }
            of<<std::endl;
        }

		of.close();
	}
	else
	{
		std::cout<<"ERROR! Unable to open file \""<<filePath<<"\" !"<<std::endl;
	}
}

// -------------------------------------------------------------------------------------------------------------------- //

#endif /* MATRIXIO_H */


