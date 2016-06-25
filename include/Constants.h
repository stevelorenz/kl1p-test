#ifndef CONSTANTS_H
#define CONSTANTS_H
// --------------------------------------------------------------------------------------
// About  : Definitions of Constants
// Date   : 2016-01-25 14:07:20
// Author : Xiang,Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------

/* Initialize Constants */

#include <cmath>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <KL1pInclude.h>

// --- Array of algorithms ---
string algorithms [] = {"OMP", "ROMP", "CoSaMP", "Subspace-Pursuit", "SL0", "AMP", "EMBP", "Basis-Pursuit"};

// --- Some constant value ---

klab::DoubleReal tolerance = 1e-6;
// threshold for differing a value from zero
klab::DoubleReal epsilon = 5e-8;

// --- File path for sensing matrix and statistish results ---

// sensing matrix
string sensingMatrixOriginalFile("./rsc/sensingMatrixKL1P.csv");
string sensingMatrixResizedFile("./rsc/sensingMatrixResized.csv");

// results dir and files
const char* MatrixRootDir = "./csv_matrix";

string RunTimeMeanMatrixFile("./csv_matrix/RunTimeMean_");
string RunTimeStdMatrixFile("./csv_matrix/RunTimeStd_");

string MSEMeanMatrixFile("./csv_matrix/MSEMean_");
string MSEStdMatrixFile("./csv_matrix/MSEStd_");

string SuccessMeanMatrixFile("./csv_matrix/SuccessMean_");
string SuccessStdMatrixFile("./csv_matrix/SuccessStd_");

string CSVEndName(".csv");

// --------------------------------------------------------------------------------------

#endif /* CONSTANTS_H */
