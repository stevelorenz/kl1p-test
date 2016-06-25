// KSci - A portable C++ numerical analysis library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KSci C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#include "SignalUtilUnitTest.h"
#include "../include/SignalUtil.h"
#include "../include/Fourier.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KSignalUtilUnitTest::KSignalUtilUnitTest() : Test::Suite()
{
    TEST_ADD(KSignalUtilUnitTest::testSquaredError_Vector)
    TEST_ADD(KSignalUtilUnitTest::testSquaredError_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testRootSquaredError_Vector)
    TEST_ADD(KSignalUtilUnitTest::testRootSquaredError_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testSqrtSquaredError_Vector)
    TEST_ADD(KSignalUtilUnitTest::testSqrtSquaredError_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testMeanSquaredError_Vector)
    TEST_ADD(KSignalUtilUnitTest::testMeanSquaredError_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testRootMeanSquaredError_Vector)
    TEST_ADD(KSignalUtilUnitTest::testRootMeanSquaredError_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testSNR_Vector)
    TEST_ADD(KSignalUtilUnitTest::testSNR_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testPSNR_Vector)
    TEST_ADD(KSignalUtilUnitTest::testPSNR_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testSparsify_Vector)
    TEST_ADD(KSignalUtilUnitTest::testSparsify_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testConvolve_Vector)
    TEST_ADD(KSignalUtilUnitTest::testConvolve_Vector_Complex)
    TEST_ADD(KSignalUtilUnitTest::testConvolve_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testConvolve_Matrix_Complex)
    TEST_ADD(KSignalUtilUnitTest::testCrossCorrelate_Vector)
    TEST_ADD(KSignalUtilUnitTest::testCrossCorrelate_Vector_Complex)
    TEST_ADD(KSignalUtilUnitTest::testCrossCorrelate_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testCrossCorrelate_Matrix_Complex)
    TEST_ADD(KSignalUtilUnitTest::testCorrelation_Vector)
    TEST_ADD(KSignalUtilUnitTest::testCorrelation_Vector_Complex)
    TEST_ADD(KSignalUtilUnitTest::testCorrelation_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testCorrelation_Matrix_Complex)
    TEST_ADD(KSignalUtilUnitTest::testDownsample_Vector)
    TEST_ADD(KSignalUtilUnitTest::testDownsample_Matrix)
    TEST_ADD(KSignalUtilUnitTest::testUpsample_Vector)
    TEST_ADD(KSignalUtilUnitTest::testUpsample_Matrix)
}

// ---------------------------------------------------------------------------------------------------- //

KSignalUtilUnitTest::~KSignalUtilUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testSquaredError_Vector()
{
    try
    {
        klab::UInt32 n = 32;

        arma::Col<klab::DoubleReal> x0(n);

        klab::DoubleReal invN = 1.0 / n;
        for(klab::UInt32 i=1; i<=n; ++i)
            x0[i-1] = 4.0 * klab::Sin(4.0 * klab::PI * i * invN);

        klab::DoubleReal precision = 1e-6;


        arma::Col<klab::DoubleReal> x = x0;
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 0.0, precision))


        x[0]  = -x0[0];
        x[14] = -x0[14];
        x[15] = -x0[15];
        x[20] = -x0[20];
        x[27] = -x0[27];
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 137.372583, precision))


        x.set_size(n+1);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = x0[i];
        x[n] = 1.23;
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 1.5129, precision))


        x.set_size(n-2);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n-2; ++i)
            x[i] = x0[i];
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 2.34314575, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, arma::Col<klab::DoubleReal>()), 256.0, precision))
        TEST_ASSERT(klab::Equals(klab::SquaredError(arma::Col<klab::DoubleReal>(), x), 256.0, precision))
        TEST_ASSERT(klab::Equals(klab::SquaredError(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testSquaredError_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> x0(8, 8);

        x0(0, 0) = 150.0;
        x0(0, 1) = 111.0;
        x0(0, 2) = 129.0;
        x0(0, 3) = 139.0;
        x0(0, 4) = 127.0;
        x0(0, 5) = 143.0;
        x0(0, 6) = 160.0;
        x0(0, 7) = 90.0;
        x0(1, 0) = 127.0;
        x0(1, 1) = 108.0;
        x0(1, 2) = 120.0;
        x0(1, 3) = 167.0;
        x0(1, 4) = 182.0;
        x0(1, 5) = 136.0;
        x0(1, 6) = 118.0;
        x0(1, 7) = 85.0;
        x0(2, 0) = 124.0;
        x0(2, 1) = 114.0;
        x0(2, 2) = 132.0;
        x0(2, 3) = 141.0;
        x0(2, 4) = 171.0;
        x0(2, 5) = 184.0;
        x0(2, 6) = 110.0;
        x0(2, 7) = 141.0;
        x0(3, 0) = 127.0;
        x0(3, 1) = 115.0;
        x0(3, 2) = 107.0;
        x0(3, 3) = 85.0;
        x0(3, 4) = 161.0;
        x0(3, 5) = 122.0;
        x0(3, 6) = 97.0;
        x0(3, 7) = 157.0;
        x0(4, 0) = 121.0;
        x0(4, 1) = 107.0;
        x0(4, 2) = 73.0;
        x0(4, 3) = 118.0;
        x0(4, 4) = 153.0;
        x0(4, 5) = 97.0;
        x0(4, 6) = 126.0;
        x0(4, 7) = 170.0;
        x0(5, 0) = 115.0;
        x0(5, 1) = 98.0;
        x0(5, 2) = 90.0;
        x0(5, 3) = 91.0;
        x0(5, 4) = 140.0;
        x0(5, 5) = 87.0;
        x0(5, 6) = 144.0;
        x0(5, 7) = 195.0;
        x0(6, 0) = 120.0;
        x0(6, 1) = 81.0;
        x0(6, 2) = 84.0;
        x0(6, 3) = 77.0;
        x0(6, 4) = 151.0;
        x0(6, 5) = 138.0;
        x0(6, 6) = 144.0;
        x0(6, 7) = 135.0;
        x0(7, 0) = 126.0;
        x0(7, 1) = 71.0;
        x0(7, 2) = 70.0;
        x0(7, 3) = 108.0;
        x0(7, 4) = 149.0;
        x0(7, 5) = 175.0;
        x0(7, 6) = 125.0;
        x0(7, 7) = 93.0;

        klab::DoubleReal precision = 1e-10;


        // M0=M and N0=N
        arma::Mat<klab::DoubleReal> x(x0);
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 0.0, precision))

        x(0, 1) = -x0(0, 1);
        x(1, 3) = -x0(1, 3);
        x(3, 3) = -x0(3, 3);
        x(3, 4) = -x0(3, 4);
        x(3, 7) = -x0(3, 7);
        x(4, 0) = -x0(4, 0);
        x(4, 1) = -x0(4, 1);
        x(5, 3) = -x0(5, 3);
        x(6, 3) = -x0(6, 3);
        x(7, 6) = -x0(7, 6);
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 615720.0, precision))
        

        // M0<M and N0<N
        x.set_size(9, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<9; ++i)
            x(i, 8) = 20.0 * (i+1);
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 195600.0, precision))


        // M0<M and N0=N
        x.set_size(9, 8);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 81600.0, precision))
        

        // M0<M and N0>N
        x.set_size(9, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<7; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 209654.0, precision))
        

        // M0=M and N0<N
        x.set_size(8, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<8; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 81600.0, precision))
        

        // M0=M and N0>N
        x.set_size(8, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 153654.0, precision))
        

        // M0>M and N0<N
        x.set_size(7, 9);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<7; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 170581.0, precision))


        // M0>M and N0=N
        x.set_size(7, 8);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 114581.0, precision))


        // M0>M and N0>N
        x.set_size(7, 7);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, x), 259586.0, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::SquaredError(x0, arma::Mat<klab::DoubleReal>()), 1044968.0, precision))
        TEST_ASSERT(klab::Equals(klab::SquaredError(arma::Mat<klab::DoubleReal>(), x), 1044968.0, precision))
        TEST_ASSERT(klab::Equals(klab::SquaredError(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testRootSquaredError_Vector()
{
    try
    {
        klab::UInt32 n = 32;

        arma::Col<klab::DoubleReal> x0(n);

        klab::DoubleReal invN = 1.0 / n;
        for(klab::UInt32 i=1; i<=n; ++i)
            x0[i-1] = 4.0 * klab::Sin(4.0 * klab::PI * i * invN);

        klab::DoubleReal precision = 1e-6;


        arma::Col<klab::DoubleReal> x = x0;
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 0.0, precision))


        x[0]  = -x0[0];
        x[14] = -x0[14];
        x[15] = -x0[15];
        x[20] = -x0[20];
        x[27] = -x0[27];
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 21.51397118, precision))


        x.set_size(n+1);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = x0[i];
        x[n] = 1.23;
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 1.23, precision))


        x.set_size(n-2);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n-2; ++i)
            x[i] = x0[i];
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 1.53073373, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, arma::Col<klab::DoubleReal>()), 80.43743187, precision))
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(arma::Col<klab::DoubleReal>(), x), 80.43743187, precision))
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testRootSquaredError_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> x0(8, 8);

        x0(0, 0) = 150.0;
        x0(0, 1) = 111.0;
        x0(0, 2) = 129.0;
        x0(0, 3) = 139.0;
        x0(0, 4) = 127.0;
        x0(0, 5) = 143.0;
        x0(0, 6) = 160.0;
        x0(0, 7) = 90.0;
        x0(1, 0) = 127.0;
        x0(1, 1) = 108.0;
        x0(1, 2) = 120.0;
        x0(1, 3) = 167.0;
        x0(1, 4) = 182.0;
        x0(1, 5) = 136.0;
        x0(1, 6) = 118.0;
        x0(1, 7) = 85.0;
        x0(2, 0) = 124.0;
        x0(2, 1) = 114.0;
        x0(2, 2) = 132.0;
        x0(2, 3) = 141.0;
        x0(2, 4) = 171.0;
        x0(2, 5) = 184.0;
        x0(2, 6) = 110.0;
        x0(2, 7) = 141.0;
        x0(3, 0) = 127.0;
        x0(3, 1) = 115.0;
        x0(3, 2) = 107.0;
        x0(3, 3) = 85.0;
        x0(3, 4) = 161.0;
        x0(3, 5) = 122.0;
        x0(3, 6) = 97.0;
        x0(3, 7) = 157.0;
        x0(4, 0) = 121.0;
        x0(4, 1) = 107.0;
        x0(4, 2) = 73.0;
        x0(4, 3) = 118.0;
        x0(4, 4) = 153.0;
        x0(4, 5) = 97.0;
        x0(4, 6) = 126.0;
        x0(4, 7) = 170.0;
        x0(5, 0) = 115.0;
        x0(5, 1) = 98.0;
        x0(5, 2) = 90.0;
        x0(5, 3) = 91.0;
        x0(5, 4) = 140.0;
        x0(5, 5) = 87.0;
        x0(5, 6) = 144.0;
        x0(5, 7) = 195.0;
        x0(6, 0) = 120.0;
        x0(6, 1) = 81.0;
        x0(6, 2) = 84.0;
        x0(6, 3) = 77.0;
        x0(6, 4) = 151.0;
        x0(6, 5) = 138.0;
        x0(6, 6) = 144.0;
        x0(6, 7) = 135.0;
        x0(7, 0) = 126.0;
        x0(7, 1) = 71.0;
        x0(7, 2) = 70.0;
        x0(7, 3) = 108.0;
        x0(7, 4) = 149.0;
        x0(7, 5) = 175.0;
        x0(7, 6) = 125.0;
        x0(7, 7) = 93.0;

        klab::DoubleReal precision = 1e-10;


        // M0=M and N0=N
        arma::Mat<klab::DoubleReal> x(x0);
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 0.0, precision))

        x(0, 1) = -x0(0, 1);
        x(1, 3) = -x0(1, 3);
        x(3, 3) = -x0(3, 3);
        x(3, 4) = -x0(3, 4);
        x(3, 7) = -x0(3, 7);
        x(4, 0) = -x0(4, 0);
        x(4, 1) = -x0(4, 1);
        x(5, 3) = -x0(5, 3);
        x(6, 3) = -x0(6, 3);
        x(7, 6) = -x0(7, 6);
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 2404.0, precision))
        

        // M0<M and N0<N
        x.set_size(9, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<9; ++i)
            x(i, 8) = 20.0 * (i+1);
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 1620.0, precision))


        // M0<M and N0=N
        x.set_size(9, 8);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 720.0, precision))
        

        // M0<M and N0>N
        x.set_size(9, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<7; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 1626.0, precision))
        

        // M0=M and N0<N
        x.set_size(8, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<8; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 720.0, precision))
        

        // M0=M and N0>N
        x.set_size(8, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 1066.0, precision))
        

        // M0>M and N0<N
        x.set_size(7, 9);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<7; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 1477.0, precision))


        // M0>M and N0=N
        x.set_size(7, 8);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 917.0, precision))


        // M0>M and N0>N
        x.set_size(7, 7);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, x), 1890.0, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(x0, arma::Mat<klab::DoubleReal>()), 7952.0, precision))
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(arma::Mat<klab::DoubleReal>(), x), 7952.0, precision))
        TEST_ASSERT(klab::Equals(klab::RootSquaredError(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testSqrtSquaredError_Vector()
{
    try
    {
        klab::UInt32 n = 32;

        arma::Col<klab::DoubleReal> x0(n);

        klab::DoubleReal invN = 1.0 / n;
        for(klab::UInt32 i=1; i<=n; ++i)
            x0[i-1] = 4.0 * klab::Sin(4.0 * klab::PI * i * invN);

        klab::DoubleReal precision = 1e-6;


        arma::Col<klab::DoubleReal> x = x0;
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 0.0, precision))


        x[0]  = -x0[0];
        x[14] = -x0[14];
        x[15] = -x0[15];
        x[20] = -x0[20];
        x[27] = -x0[27];
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 11.72060506, precision))


        x.set_size(n+1);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = x0[i];
        x[n] = 1.23;
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 1.23, precision))


        x.set_size(n-2);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n-2; ++i)
            x[i] = x0[i];
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 1.53073373, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, arma::Col<klab::DoubleReal>()), 16.0, precision))
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(arma::Col<klab::DoubleReal>(), x), 16.0, precision))
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testSqrtSquaredError_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> x0(8, 8);

        x0(0, 0) = 150.0;
        x0(0, 1) = 111.0;
        x0(0, 2) = 129.0;
        x0(0, 3) = 139.0;
        x0(0, 4) = 127.0;
        x0(0, 5) = 143.0;
        x0(0, 6) = 160.0;
        x0(0, 7) = 90.0;
        x0(1, 0) = 127.0;
        x0(1, 1) = 108.0;
        x0(1, 2) = 120.0;
        x0(1, 3) = 167.0;
        x0(1, 4) = 182.0;
        x0(1, 5) = 136.0;
        x0(1, 6) = 118.0;
        x0(1, 7) = 85.0;
        x0(2, 0) = 124.0;
        x0(2, 1) = 114.0;
        x0(2, 2) = 132.0;
        x0(2, 3) = 141.0;
        x0(2, 4) = 171.0;
        x0(2, 5) = 184.0;
        x0(2, 6) = 110.0;
        x0(2, 7) = 141.0;
        x0(3, 0) = 127.0;
        x0(3, 1) = 115.0;
        x0(3, 2) = 107.0;
        x0(3, 3) = 85.0;
        x0(3, 4) = 161.0;
        x0(3, 5) = 122.0;
        x0(3, 6) = 97.0;
        x0(3, 7) = 157.0;
        x0(4, 0) = 121.0;
        x0(4, 1) = 107.0;
        x0(4, 2) = 73.0;
        x0(4, 3) = 118.0;
        x0(4, 4) = 153.0;
        x0(4, 5) = 97.0;
        x0(4, 6) = 126.0;
        x0(4, 7) = 170.0;
        x0(5, 0) = 115.0;
        x0(5, 1) = 98.0;
        x0(5, 2) = 90.0;
        x0(5, 3) = 91.0;
        x0(5, 4) = 140.0;
        x0(5, 5) = 87.0;
        x0(5, 6) = 144.0;
        x0(5, 7) = 195.0;
        x0(6, 0) = 120.0;
        x0(6, 1) = 81.0;
        x0(6, 2) = 84.0;
        x0(6, 3) = 77.0;
        x0(6, 4) = 151.0;
        x0(6, 5) = 138.0;
        x0(6, 6) = 144.0;
        x0(6, 7) = 135.0;
        x0(7, 0) = 126.0;
        x0(7, 1) = 71.0;
        x0(7, 2) = 70.0;
        x0(7, 3) = 108.0;
        x0(7, 4) = 149.0;
        x0(7, 5) = 175.0;
        x0(7, 6) = 125.0;
        x0(7, 7) = 93.0;

        klab::DoubleReal precision = 1e-6;


        // M0=M and N0=N
        arma::Mat<klab::DoubleReal> x(x0);
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 0.0, precision))

        x(0, 1) = -x0(0, 1);
        x(1, 3) = -x0(1, 3);
        x(3, 3) = -x0(3, 3);
        x(3, 4) = -x0(3, 4);
        x(3, 7) = -x0(3, 7);
        x(4, 0) = -x0(4, 0);
        x(4, 1) = -x0(4, 1);
        x(5, 3) = -x0(5, 3);
        x(6, 3) = -x0(6, 3);
        x(7, 6) = -x0(7, 6);
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 784.678278, precision))
        

        // M0<M and N0<N
        x.set_size(9, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<9; ++i)
            x(i, 8) = 20.0 * (i+1);
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 442.2668877, precision))


        // M0<M and N0=N
        x.set_size(9, 8);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 285.6571371, precision))
        

        // M0<M and N0>N
        x.set_size(9, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<7; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 457.8798969, precision))
        

        // M0=M and N0<N
        x.set_size(8, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<8; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 285.6571371, precision))
        

        // M0=M and N0>N
        x.set_size(8, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 391.9872447, precision))
        

        // M0>M and N0<N
        x.set_size(7, 9);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<7; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 413.0145276, precision))


        // M0>M and N0=N
        x.set_size(7, 8);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 338.4981536, precision))


        // M0>M and N0>N
        x.set_size(7, 7);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, x), 509.4958292, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(x0, arma::Mat<klab::DoubleReal>()), 1022.236763, precision))
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(arma::Mat<klab::DoubleReal>(), x), 1022.236763, precision))
        TEST_ASSERT(klab::Equals(klab::SqrtSquaredError(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testMeanSquaredError_Vector()
{
    try
    {
        klab::UInt32 n = 32;

        arma::Col<klab::DoubleReal> x0(n);

        klab::DoubleReal invN = 1.0 / n;
        for(klab::UInt32 i=1; i<=n; ++i)
            x0[i-1] = 4.0 * klab::Sin(4.0 * klab::PI * i * invN);

        klab::DoubleReal precision = 1e-6;


        arma::Col<klab::DoubleReal> x = x0;
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 0.0, precision))


        x[0]  = -x0[0];
        x[14] = -x0[14];
        x[15] = -x0[15];
        x[20] = -x0[20];
        x[27] = -x0[27];
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 4.29289322, precision))


        x.set_size(n+1);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = x0[i];
        x[n] = 1.23;
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 0.04584545, precision))


        x.set_size(n-2);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n-2; ++i)
            x[i] = x0[i];
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 0.07322330, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, arma::Col<klab::DoubleReal>()), 8.0, precision))
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(arma::Col<klab::DoubleReal>(), x), 8.0, precision))
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testMeanSquaredError_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> x0(8, 8);

        x0(0, 0) = 150.0;
        x0(0, 1) = 111.0;
        x0(0, 2) = 129.0;
        x0(0, 3) = 139.0;
        x0(0, 4) = 127.0;
        x0(0, 5) = 143.0;
        x0(0, 6) = 160.0;
        x0(0, 7) = 90.0;
        x0(1, 0) = 127.0;
        x0(1, 1) = 108.0;
        x0(1, 2) = 120.0;
        x0(1, 3) = 167.0;
        x0(1, 4) = 182.0;
        x0(1, 5) = 136.0;
        x0(1, 6) = 118.0;
        x0(1, 7) = 85.0;
        x0(2, 0) = 124.0;
        x0(2, 1) = 114.0;
        x0(2, 2) = 132.0;
        x0(2, 3) = 141.0;
        x0(2, 4) = 171.0;
        x0(2, 5) = 184.0;
        x0(2, 6) = 110.0;
        x0(2, 7) = 141.0;
        x0(3, 0) = 127.0;
        x0(3, 1) = 115.0;
        x0(3, 2) = 107.0;
        x0(3, 3) = 85.0;
        x0(3, 4) = 161.0;
        x0(3, 5) = 122.0;
        x0(3, 6) = 97.0;
        x0(3, 7) = 157.0;
        x0(4, 0) = 121.0;
        x0(4, 1) = 107.0;
        x0(4, 2) = 73.0;
        x0(4, 3) = 118.0;
        x0(4, 4) = 153.0;
        x0(4, 5) = 97.0;
        x0(4, 6) = 126.0;
        x0(4, 7) = 170.0;
        x0(5, 0) = 115.0;
        x0(5, 1) = 98.0;
        x0(5, 2) = 90.0;
        x0(5, 3) = 91.0;
        x0(5, 4) = 140.0;
        x0(5, 5) = 87.0;
        x0(5, 6) = 144.0;
        x0(5, 7) = 195.0;
        x0(6, 0) = 120.0;
        x0(6, 1) = 81.0;
        x0(6, 2) = 84.0;
        x0(6, 3) = 77.0;
        x0(6, 4) = 151.0;
        x0(6, 5) = 138.0;
        x0(6, 6) = 144.0;
        x0(6, 7) = 135.0;
        x0(7, 0) = 126.0;
        x0(7, 1) = 71.0;
        x0(7, 2) = 70.0;
        x0(7, 3) = 108.0;
        x0(7, 4) = 149.0;
        x0(7, 5) = 175.0;
        x0(7, 6) = 125.0;
        x0(7, 7) = 93.0;

        klab::DoubleReal precision = 1e-6;


        // M0=M and N0=N
        arma::Mat<klab::DoubleReal> x(x0);
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 0.0, precision))

        x(0, 1) = -x0(0, 1);
        x(1, 3) = -x0(1, 3);
        x(3, 3) = -x0(3, 3);
        x(3, 4) = -x0(3, 4);
        x(3, 7) = -x0(3, 7);
        x(4, 0) = -x0(4, 0);
        x(4, 1) = -x0(4, 1);
        x(5, 3) = -x0(5, 3);
        x(6, 3) = -x0(6, 3);
        x(7, 6) = -x0(7, 6);
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 9620.625, precision))
        

        // M0<M and N0<N
        x.set_size(9, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<9; ++i)
            x(i, 8) = 20.0 * (i+1);
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 2414.814815, precision))


        // M0<M and N0=N
        x.set_size(9, 8);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 1133.333333, precision))
        

        // M0<M and N0>N
        x.set_size(9, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<7; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 2911.861111, precision))
        

        // M0=M and N0<N
        x.set_size(8, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<8; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 1133.333333, precision))
        

        // M0=M and N0>N
        x.set_size(8, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 2400.84375, precision))
        

        // M0>M and N0<N
        x.set_size(7, 9);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<7; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 2369.180556, precision))


        // M0>M and N0=N
        x.set_size(7, 8);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 1790.328125, precision))


        // M0>M and N0>N
        x.set_size(7, 7);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, x), 4056.03125, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(x0, arma::Mat<klab::DoubleReal>()), 16327.625, precision))
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(arma::Mat<klab::DoubleReal>(), x), 16327.625, precision))
        TEST_ASSERT(klab::Equals(klab::MeanSquaredError(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testRootMeanSquaredError_Vector()
{
    try
    {
        klab::UInt32 n = 32;

        arma::Col<klab::DoubleReal> x0(n);

        klab::DoubleReal invN = 1.0 / n;
        for(klab::UInt32 i=1; i<=n; ++i)
            x0[i-1] = 4.0 * klab::Sin(4.0 * klab::PI * i * invN);

        klab::DoubleReal precision = 1e-6;


        arma::Col<klab::DoubleReal> x = x0;
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 0.0, precision))


        x[0]  = -x0[0];
        x[14] = -x0[14];
        x[15] = -x0[15];
        x[20] = -x0[20];
        x[27] = -x0[27];
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 0.67231160, precision))


        x.set_size(n+1);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = x0[i];
        x[n] = 1.23;
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 0.03727273, precision))


        x.set_size(n-2);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n-2; ++i)
            x[i] = x0[i];
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 0.04783543, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, arma::Col<klab::DoubleReal>()), 2.51366975, precision))
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(arma::Col<klab::DoubleReal>(), x), 2.51366975, precision))
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testRootMeanSquaredError_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> x0(8, 8);

        x0(0, 0) = 150.0;
        x0(0, 1) = 111.0;
        x0(0, 2) = 129.0;
        x0(0, 3) = 139.0;
        x0(0, 4) = 127.0;
        x0(0, 5) = 143.0;
        x0(0, 6) = 160.0;
        x0(0, 7) = 90.0;
        x0(1, 0) = 127.0;
        x0(1, 1) = 108.0;
        x0(1, 2) = 120.0;
        x0(1, 3) = 167.0;
        x0(1, 4) = 182.0;
        x0(1, 5) = 136.0;
        x0(1, 6) = 118.0;
        x0(1, 7) = 85.0;
        x0(2, 0) = 124.0;
        x0(2, 1) = 114.0;
        x0(2, 2) = 132.0;
        x0(2, 3) = 141.0;
        x0(2, 4) = 171.0;
        x0(2, 5) = 184.0;
        x0(2, 6) = 110.0;
        x0(2, 7) = 141.0;
        x0(3, 0) = 127.0;
        x0(3, 1) = 115.0;
        x0(3, 2) = 107.0;
        x0(3, 3) = 85.0;
        x0(3, 4) = 161.0;
        x0(3, 5) = 122.0;
        x0(3, 6) = 97.0;
        x0(3, 7) = 157.0;
        x0(4, 0) = 121.0;
        x0(4, 1) = 107.0;
        x0(4, 2) = 73.0;
        x0(4, 3) = 118.0;
        x0(4, 4) = 153.0;
        x0(4, 5) = 97.0;
        x0(4, 6) = 126.0;
        x0(4, 7) = 170.0;
        x0(5, 0) = 115.0;
        x0(5, 1) = 98.0;
        x0(5, 2) = 90.0;
        x0(5, 3) = 91.0;
        x0(5, 4) = 140.0;
        x0(5, 5) = 87.0;
        x0(5, 6) = 144.0;
        x0(5, 7) = 195.0;
        x0(6, 0) = 120.0;
        x0(6, 1) = 81.0;
        x0(6, 2) = 84.0;
        x0(6, 3) = 77.0;
        x0(6, 4) = 151.0;
        x0(6, 5) = 138.0;
        x0(6, 6) = 144.0;
        x0(6, 7) = 135.0;
        x0(7, 0) = 126.0;
        x0(7, 1) = 71.0;
        x0(7, 2) = 70.0;
        x0(7, 3) = 108.0;
        x0(7, 4) = 149.0;
        x0(7, 5) = 175.0;
        x0(7, 6) = 125.0;
        x0(7, 7) = 93.0;

        klab::DoubleReal precision = 1e-6;


        // M0=M and N0=N
        arma::Mat<klab::DoubleReal> x(x0);
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 0.0, precision))

        x(0, 1) = -x0(0, 1);
        x(1, 3) = -x0(1, 3);
        x(3, 3) = -x0(3, 3);
        x(3, 4) = -x0(3, 4);
        x(3, 7) = -x0(3, 7);
        x(4, 0) = -x0(4, 0);
        x(4, 1) = -x0(4, 1);
        x(5, 3) = -x0(5, 3);
        x(6, 3) = -x0(6, 3);
        x(7, 6) = -x0(7, 6);
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 37.5625, precision))
        

        // M0<M and N0<N
        x.set_size(9, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<9; ++i)
            x(i, 8) = 20.0 * (i+1);
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 20.0, precision))


        // M0<M and N0=N
        x.set_size(9, 8);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 10.0, precision))
        

        // M0<M and N0>N
        x.set_size(9, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<7; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 22.58333333, precision))
        

        // M0=M and N0<N
        x.set_size(8, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<8; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 10.0, precision))
        

        // M0=M and N0>N
        x.set_size(8, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 16.65625, precision))
        

        // M0>M and N0<N
        x.set_size(7, 9);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<7; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 20.51388889, precision))


        // M0>M and N0=N
        x.set_size(7, 8);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 14.328125, precision))


        // M0>M and N0>N
        x.set_size(7, 7);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, x), 29.53125, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(x0, arma::Mat<klab::DoubleReal>()), 124.25, precision))
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(arma::Mat<klab::DoubleReal>(), x), 124.25, precision))
        TEST_ASSERT(klab::Equals(klab::RootMeanSquaredError(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>()), 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testSNR_Vector()
{
    try
    {
        klab::UInt32 n = 32;

        arma::Col<klab::DoubleReal> x0(n);

        klab::DoubleReal invN = 1.0 / n;
        for(klab::UInt32 i=1; i<=n; ++i)
            x0[i-1] = 4.0 * klab::Sin(4.0 * klab::PI * i * invN);

        klab::DoubleReal precision = 1e-6;


        arma::Col<klab::DoubleReal> x = x0;
        TEST_ASSERT(klab::SNR(x0, x) == klab::DOUBLEREAL_INFINITY)


        x[0]  = -x0[0];
        x[14] = -x0[14];
        x[15] = -x0[15];
        x[20] = -x0[20];
        x[27] = -x0[27];
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 2.70339901, precision))


        x.set_size(n+1);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = x0[i];
        x[n] = 1.23;
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 22.28429742, precision))


        x.set_size(n-2);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n-2; ++i)
            x[i] = x0[i];
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 20.38440661, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::SNR(x0, arma::Col<klab::DoubleReal>()), 0.0, precision))
        TEST_ASSERT(klab::Equals(klab::SNR(arma::Col<klab::DoubleReal>(), x), 0.0, precision))
        TEST_ASSERT(klab::SNR(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>()) == klab::DOUBLEREAL_INFINITY)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testSNR_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> x0(8, 8);

        x0(0, 0) = 150.0;
        x0(0, 1) = 111.0;
        x0(0, 2) = 129.0;
        x0(0, 3) = 139.0;
        x0(0, 4) = 127.0;
        x0(0, 5) = 143.0;
        x0(0, 6) = 160.0;
        x0(0, 7) = 90.0;
        x0(1, 0) = 127.0;
        x0(1, 1) = 108.0;
        x0(1, 2) = 120.0;
        x0(1, 3) = 167.0;
        x0(1, 4) = 182.0;
        x0(1, 5) = 136.0;
        x0(1, 6) = 118.0;
        x0(1, 7) = 85.0;
        x0(2, 0) = 124.0;
        x0(2, 1) = 114.0;
        x0(2, 2) = 132.0;
        x0(2, 3) = 141.0;
        x0(2, 4) = 171.0;
        x0(2, 5) = 184.0;
        x0(2, 6) = 110.0;
        x0(2, 7) = 141.0;
        x0(3, 0) = 127.0;
        x0(3, 1) = 115.0;
        x0(3, 2) = 107.0;
        x0(3, 3) = 85.0;
        x0(3, 4) = 161.0;
        x0(3, 5) = 122.0;
        x0(3, 6) = 97.0;
        x0(3, 7) = 157.0;
        x0(4, 0) = 121.0;
        x0(4, 1) = 107.0;
        x0(4, 2) = 73.0;
        x0(4, 3) = 118.0;
        x0(4, 4) = 153.0;
        x0(4, 5) = 97.0;
        x0(4, 6) = 126.0;
        x0(4, 7) = 170.0;
        x0(5, 0) = 115.0;
        x0(5, 1) = 98.0;
        x0(5, 2) = 90.0;
        x0(5, 3) = 91.0;
        x0(5, 4) = 140.0;
        x0(5, 5) = 87.0;
        x0(5, 6) = 144.0;
        x0(5, 7) = 195.0;
        x0(6, 0) = 120.0;
        x0(6, 1) = 81.0;
        x0(6, 2) = 84.0;
        x0(6, 3) = 77.0;
        x0(6, 4) = 151.0;
        x0(6, 5) = 138.0;
        x0(6, 6) = 144.0;
        x0(6, 7) = 135.0;
        x0(7, 0) = 126.0;
        x0(7, 1) = 71.0;
        x0(7, 2) = 70.0;
        x0(7, 3) = 108.0;
        x0(7, 4) = 149.0;
        x0(7, 5) = 175.0;
        x0(7, 6) = 125.0;
        x0(7, 7) = 93.0;

        klab::DoubleReal precision = 1e-6;


        // M0=M and N0=N
        arma::Mat<klab::DoubleReal> x(x0);
        TEST_ASSERT(klab::SNR(x0, x)  == klab::DOUBLEREAL_INFINITY)

        x(0, 1) = -x0(0, 1);
        x(1, 3) = -x0(1, 3);
        x(3, 3) = -x0(3, 3);
        x(3, 4) = -x0(3, 4);
        x(3, 7) = -x0(3, 7);
        x(4, 0) = -x0(4, 0);
        x(4, 1) = -x0(4, 1);
        x(5, 3) = -x0(5, 3);
        x(6, 3) = -x0(6, 3);
        x(7, 6) = -x0(7, 6);
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 2.297197306, precision))
        

        // M0<M and N0<N
        x.set_size(9, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<9; ++i)
            x(i, 8) = 20.0 * (i+1);
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 7.277341408, precision))


        // M0<M and N0=N
        x.set_size(9, 8);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 11.07412833, precision))
        

        // M0<M and N0>N
        x.set_size(9, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<7; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 6.975998385, precision))
        

        // M0=M and N0<N
        x.set_size(8, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<8; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 11.07412833, precision))
        

        // M0=M and N0>N
        x.set_size(8, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 8.325591208, precision))
        

        // M0>M and N0<N
        x.set_size(7, 9);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<7; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 7.871723352, precision))


        // M0>M and N0=N
        x.set_size(7, 8);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 9.599903831, precision))


        // M0>M and N0>N
        x.set_size(7, 7);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::SNR(x0, x), 6.048217249, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::SNR(x0, arma::Mat<klab::DoubleReal>()), 0.0, precision))
        TEST_ASSERT(klab::Equals(klab::SNR(arma::Mat<klab::DoubleReal>(), x), 0.0, precision))
        TEST_ASSERT(klab::SNR(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>()) == klab::DOUBLEREAL_INFINITY)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testPSNR_Vector()
{
    try
    {
        klab::UInt32 n = 32;

        arma::Col<klab::DoubleReal> x0(n);

        klab::DoubleReal invN = 1.0 / n;
        for(klab::UInt32 i=1; i<=n; ++i)
            x0[i-1] = 4.0 * klab::Sin(4.0 * klab::PI * i * invN);

        klab::DoubleReal precision = 1e-6;


        arma::Col<klab::DoubleReal> x = x0;
        TEST_ASSERT(klab::PSNR(x0, x) == klab::DOUBLEREAL_INFINITY)


        x[0]  = -x0[0];
        x[14] = -x0[14];
        x[15] = -x0[15];
        x[20] = -x0[20];
        x[27] = -x0[27];
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 5.713698967, precision))     


        x.set_size(n+1);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = x0[i];
        x[n] = 1.23;
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 25.428237, precision))   


        x.set_size(n-2);
        x.fill(0.0);
        for(klab::UInt32 i=0; i<n-2; ++i)
            x[i] = x0[i];
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 23.39470657, precision))    


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, arma::Col<klab::DoubleReal>()), 3.010299957, precision))    
        TEST_ASSERT(klab::Equals(klab::PSNR(arma::Col<klab::DoubleReal>(), x), 3.010299957, precision))     
        TEST_ASSERT(klab::PSNR(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>()) == klab::DOUBLEREAL_INFINITY)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testPSNR_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> x0(8, 8);

        x0(0, 0) = 150.0;
        x0(0, 1) = 111.0;
        x0(0, 2) = 129.0;
        x0(0, 3) = 139.0;
        x0(0, 4) = 127.0;
        x0(0, 5) = 143.0;
        x0(0, 6) = 160.0;
        x0(0, 7) = 90.0;
        x0(1, 0) = 127.0;
        x0(1, 1) = 108.0;
        x0(1, 2) = 120.0;
        x0(1, 3) = 167.0;
        x0(1, 4) = 182.0;
        x0(1, 5) = 136.0;
        x0(1, 6) = 118.0;
        x0(1, 7) = 85.0;
        x0(2, 0) = 124.0;
        x0(2, 1) = 114.0;
        x0(2, 2) = 132.0;
        x0(2, 3) = 141.0;
        x0(2, 4) = 171.0;
        x0(2, 5) = 184.0;
        x0(2, 6) = 110.0;
        x0(2, 7) = 141.0;
        x0(3, 0) = 127.0;
        x0(3, 1) = 115.0;
        x0(3, 2) = 107.0;
        x0(3, 3) = 85.0;
        x0(3, 4) = 161.0;
        x0(3, 5) = 122.0;
        x0(3, 6) = 97.0;
        x0(3, 7) = 157.0;
        x0(4, 0) = 121.0;
        x0(4, 1) = 107.0;
        x0(4, 2) = 73.0;
        x0(4, 3) = 118.0;
        x0(4, 4) = 153.0;
        x0(4, 5) = 97.0;
        x0(4, 6) = 126.0;
        x0(4, 7) = 170.0;
        x0(5, 0) = 115.0;
        x0(5, 1) = 98.0;
        x0(5, 2) = 90.0;
        x0(5, 3) = 91.0;
        x0(5, 4) = 140.0;
        x0(5, 5) = 87.0;
        x0(5, 6) = 144.0;
        x0(5, 7) = 195.0;
        x0(6, 0) = 120.0;
        x0(6, 1) = 81.0;
        x0(6, 2) = 84.0;
        x0(6, 3) = 77.0;
        x0(6, 4) = 151.0;
        x0(6, 5) = 138.0;
        x0(6, 6) = 144.0;
        x0(6, 7) = 135.0;
        x0(7, 0) = 126.0;
        x0(7, 1) = 71.0;
        x0(7, 2) = 70.0;
        x0(7, 3) = 108.0;
        x0(7, 4) = 149.0;
        x0(7, 5) = 175.0;
        x0(7, 6) = 125.0;
        x0(7, 7) = 93.0;

        klab::DoubleReal precision = 1e-6;


        // M0=M and N0=N
        arma::Mat<klab::DoubleReal> x(x0);
        TEST_ASSERT(klab::PSNR(x0, x)  == klab::DOUBLEREAL_INFINITY)

        x(0, 1) = -x0(0, 1);
        x(1, 3) = -x0(1, 3);
        x(3, 3) = -x0(3, 3);
        x(3, 4) = -x0(3, 4);
        x(3, 7) = -x0(3, 7);
        x(4, 0) = -x0(4, 0);
        x(4, 1) = -x0(4, 1);
        x(5, 3) = -x0(5, 3);
        x(6, 3) = -x0(6, 3);
        x(7, 6) = -x0(7, 6);
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 5.96865936, precision))
        

        // M0<M and N0<N
        x.set_size(9, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<9; ++i)
            x(i, 8) = 20.0 * (i+1);
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 11.97185391, precision))


        // M0<M and N0=N
        x.set_size(9, 8);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<8; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 15.2571156, precision))
        

        // M0<M and N0>N
        x.set_size(9, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 j=0; j<7; ++j)
            x(8, j) = 20.0 * (j+1);
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 11.15898566, precision))
        

        // M0=M and N0<N
        x.set_size(8, 9);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<8; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 15.2571156, precision))
        

        // M0=M and N0>N
        x.set_size(8, 7);
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 11.99705326, precision))
        

        // M0>M and N0<N
        x.set_size(7, 9);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        for(klab::UInt32 i=0; i<7; ++i)
            x(i, 8) = 20.0 * (i+1);
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 12.05471063, precision))


        // M0>M and N0=N
        x.set_size(7, 8);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 13.27136588, precision))


        // M0>M and N0>N
        x.set_size(7, 7);
        for(klab::UInt32 i=0; i<7; ++i)
        {
            for(klab::UInt32 j=0; j<7; ++j)
                x(i, j) = x0(i, j);
        }
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 9.719679303, precision))


        // Limit cases.
        x = x0;
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, arma::Mat<klab::DoubleReal>()), 3.671462054, precision))
        TEST_ASSERT(klab::Equals(klab::PSNR(arma::Mat<klab::DoubleReal>(), x), 3.671462054, precision))
        TEST_ASSERT(klab::PSNR(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>()) == klab::DOUBLEREAL_INFINITY)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testSparsify_Vector()
{
    try
    {
        klab::UInt32 n = 32;

        arma::Col<klab::DoubleReal> x0(n);
        
        klab::DoubleReal invN = 1.0 / n;
        for(klab::UInt32 i=1; i<=n; ++i)
        {
            x0[i-1] = 4.0 * klab::Sin(4.0 * klab::PI * i * invN);
            if(klab::Equals(x0[i-1], 0.0))
                x0[i-1] = 1.0;
        }

        klab::DoubleReal precision = 1e-6;


        arma::Col<klab::DoubleReal> x;
        klab::Sparsify(x0, 0.25, x);
        TEST_ASSERT(x.n_rows == n)        
        klab::UInt32 count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == static_cast<klab::UInt32>(0.25 * n))


        x = x0;
        klab::Sparsify(x, 0.25);
        TEST_ASSERT(x.n_rows == n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == static_cast<klab::UInt32>(0.25 * n))
    

        arma::Col<klab::DoubleReal> x00(n);
        for(klab::UInt32 i=1; i<=n; ++i)
        {
            x00[i-1] = 4.0 * klab::Sin(4.0 * klab::PI * i * invN);
            x00[i-1] -= ((i*invN-0.3 < 0)?-1.0:1.0) + ((0.72-i*invN < 0)?-1.0:1.0);
        }
        arma::Col<std::complex<klab::DoubleReal> > xc00(n);
        arma::Col<std::complex<klab::DoubleReal> > X0;
        arma::Col<std::complex<klab::DoubleReal> > xx;
        for(klab::UInt32 i=0; i<n; ++i)
            xc00[i] = x00[i];
        TFFT1D<std::complex<klab::DoubleReal> > fft;
        fft.transform(xc00, X0);
        klab::Sparsify(X0, 0.15);   
        fft.invert(X0, xx);
        x.set_size(n);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = xx[i].real();
        TEST_ASSERT(klab::Equals(klab::SNR(x00, x), 14.14970975, precision))    


        // Limit cases.
        arma::Col<klab::DoubleReal> x10;
        klab::Sparsify(x10, 0.25);
        TEST_ASSERT(x10.n_rows == 0)

        klab::Sparsify(arma::Col<klab::DoubleReal>(), 0.25, x10);
        TEST_ASSERT(x10.n_rows == 0)


        x = x0;
        klab::Sparsify(x, 0.0);
        TEST_ASSERT(x.n_rows == n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == 0)


        x = x0;
        klab::Sparsify(x, -0.5);
        TEST_ASSERT(x.n_rows == n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == 0)


        x = x0;
        klab::Sparsify(x, 1.0);
        TEST_ASSERT(x.n_rows == n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == n)


        x = x0;
        klab::Sparsify(x, 1.8);
        TEST_ASSERT(x.n_rows == n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == n)

        
        x.set_size(0);
        klab::Sparsify(x0, 0.0, x);
        TEST_ASSERT(x.n_rows == n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == 0)


        x.set_size(0);
        klab::Sparsify(x0, -0.5, x);
        TEST_ASSERT(x.n_rows == n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == 0)


        x.set_size(0);
        klab::Sparsify(x0, 1.0, x);
        TEST_ASSERT(x.n_rows == n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == n)


        x.set_size(0);
        klab::Sparsify(x0, 1.8, x);
        TEST_ASSERT(x.n_rows == n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            count += (klab::Equals(x[i], 0.0)==false?1:0);
        TEST_ASSERT(count == n)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testSparsify_Matrix()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        arma::Mat<klab::DoubleReal> x0(m, n);

        x0(0, 0) = 150.0;
        x0(0, 1) = 111.0;
        x0(0, 2) = 129.0;
        x0(0, 3) = 139.0;
        x0(0, 4) = 127.0;
        x0(0, 5) = 143.0;
        x0(0, 6) = 160.0;
        x0(0, 7) = 90.0;
        x0(1, 0) = 127.0;
        x0(1, 1) = 108.0;
        x0(1, 2) = 120.0;
        x0(1, 3) = 167.0;
        x0(1, 4) = 182.0;
        x0(1, 5) = 136.0;
        x0(1, 6) = 118.0;
        x0(1, 7) = 85.0;
        x0(2, 0) = 124.0;
        x0(2, 1) = 114.0;
        x0(2, 2) = 132.0;
        x0(2, 3) = 141.0;
        x0(2, 4) = 171.0;
        x0(2, 5) = 184.0;
        x0(2, 6) = 110.0;
        x0(2, 7) = 141.0;
        x0(3, 0) = 127.0;
        x0(3, 1) = 115.0;
        x0(3, 2) = 107.0;
        x0(3, 3) = 85.0;
        x0(3, 4) = 161.0;
        x0(3, 5) = 122.0;
        x0(3, 6) = 97.0;
        x0(3, 7) = 157.0;
        x0(4, 0) = 121.0;
        x0(4, 1) = 107.0;
        x0(4, 2) = 73.0;
        x0(4, 3) = 118.0;
        x0(4, 4) = 153.0;
        x0(4, 5) = 97.0;
        x0(4, 6) = 126.0;
        x0(4, 7) = 170.0;
        x0(5, 0) = 115.0;
        x0(5, 1) = 98.0;
        x0(5, 2) = 90.0;
        x0(5, 3) = 91.0;
        x0(5, 4) = 140.0;
        x0(5, 5) = 87.0;
        x0(5, 6) = 144.0;
        x0(5, 7) = 195.0;
        x0(6, 0) = 120.0;
        x0(6, 1) = 81.0;
        x0(6, 2) = 84.0;
        x0(6, 3) = 77.0;
        x0(6, 4) = 151.0;
        x0(6, 5) = 138.0;
        x0(6, 6) = 144.0;
        x0(6, 7) = 135.0;
        x0(7, 0) = 126.0;
        x0(7, 1) = 71.0;
        x0(7, 2) = 70.0;
        x0(7, 3) = 108.0;
        x0(7, 4) = 149.0;
        x0(7, 5) = 175.0;
        x0(7, 6) = 125.0;
        x0(7, 7) = 93.0;

        klab::DoubleReal precision = 1e-6;


        arma::Mat<klab::DoubleReal> x;
        klab::Sparsify(x0, 0.25, x);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)        
        klab::UInt32 count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == static_cast<klab::UInt32>(0.25 * m*n))


        x = x0;
        klab::Sparsify(x, 0.25);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)    
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == static_cast<klab::UInt32>(0.25 * m*n))


        arma::Mat<std::complex<klab::DoubleReal> > xc0(m, n);
        arma::Mat<std::complex<klab::DoubleReal> > X0;
        arma::Mat<std::complex<klab::DoubleReal> > xc;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                xc0(i, j) = x0(i, j);
        }
        TFFT2D<std::complex<klab::DoubleReal> > fft;
        fft.transform(xc0, X0);
        klab::Sparsify(X0, 0.15);   
        fft.invert(X0, xc);
        x.set_size(m, n);
        for(klab::UInt32 i=0; i<xc.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<xc.n_cols; ++j)
                x(i, j) = xc(i, j).real();
        }
        TEST_ASSERT(klab::Equals(klab::PSNR(x0, x), 19.88451406, precision))    


        // Limit cases.
        arma::Mat<klab::DoubleReal> x10;
        klab::Sparsify(x10, 0.25);
        TEST_ASSERT(x10.n_rows==0 && x10.n_cols==0)

        klab::Sparsify(arma::Mat<klab::DoubleReal>(), 0.25, x10);
        TEST_ASSERT(x10.n_rows==0 && x10.n_cols==0)


        x = x0;
        klab::Sparsify(x, 0.0);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == 0)


        x = x0;
        klab::Sparsify(x, -0.5);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == 0)


        x = x0;
        klab::Sparsify(x, 1.0);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)         
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == m*n)


        x = x0;
        klab::Sparsify(x, 1.8);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)       
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == m*n)

        
        x.set_size(0);
        klab::Sparsify(x0, 0.0, x);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)        
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == 0)


        x.set_size(0);
        klab::Sparsify(x0, -0.5, x);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)         
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == 0)


        x.set_size(0);
        klab::Sparsify(x0, 1.0, x);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)       
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == m*n)


        x.set_size(0);
        klab::Sparsify(x0, 1.8, x);
        TEST_ASSERT(x.n_rows==m && x.n_cols==n)       
        count = 0;
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<x.n_cols; ++j)
                count += (klab::Equals(x(i, j), 0.0)==false?1:0);
        }
        TEST_ASSERT(count == m*n)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testConvolve_Vector()
{
    try
    {
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(n);        
        arma::Col<klab::DoubleReal> xo;
        arma::Col<klab::DoubleReal> f1(4);
        arma::Col<klab::DoubleReal> f2(5);

        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = klab::DoubleReal(i+1);

        f1[0] = 1.0;
        f1[1] = 2.0;
        f1[2] = 3.0;
        f1[3] = 4.0;

        f2[0] = 5.0;
        f2[1] = 4.0;
        f2[2] = 3.0;
        f2[3] = 2.0;
        f2[4] = 1.0;


        klab::Convolve(x, f1, xo);
        TEST_ASSERT(xo.n_rows == (x.n_rows+f1.n_rows-1))
        TEST_ASSERT(klab::Equals(xo[0], 1.0, precision))
        TEST_ASSERT(klab::Equals(xo[1], 4.0, precision))
        TEST_ASSERT(klab::Equals(xo[2], 10.0, precision))
        TEST_ASSERT(klab::Equals(xo[3], 20.0, precision))
        TEST_ASSERT(klab::Equals(xo[4], 30.0, precision))
        TEST_ASSERT(klab::Equals(xo[5], 40.0, precision))
        TEST_ASSERT(klab::Equals(xo[6], 50.0, precision))
        TEST_ASSERT(klab::Equals(xo[7], 60.0, precision))
        TEST_ASSERT(klab::Equals(xo[8], 61.0, precision))
        TEST_ASSERT(klab::Equals(xo[9], 52.0, precision))
        TEST_ASSERT(klab::Equals(xo[10], 32.0, precision))

        klab::Convolve(x, f2, xo);
        TEST_ASSERT(xo.n_rows == (x.n_rows+f2.n_rows-1))
        TEST_ASSERT(klab::Equals(xo[0], 5.0, precision))
        TEST_ASSERT(klab::Equals(xo[1], 14.0, precision))
        TEST_ASSERT(klab::Equals(xo[2], 26.0, precision))
        TEST_ASSERT(klab::Equals(xo[3], 40.0, precision))
        TEST_ASSERT(klab::Equals(xo[4], 55.0, precision))
        TEST_ASSERT(klab::Equals(xo[5], 70.0, precision))
        TEST_ASSERT(klab::Equals(xo[6], 85.0, precision))
        TEST_ASSERT(klab::Equals(xo[7], 100.0, precision))
        TEST_ASSERT(klab::Equals(xo[8], 70.0, precision))
        TEST_ASSERT(klab::Equals(xo[9], 44.0, precision))
        TEST_ASSERT(klab::Equals(xo[10], 23.0, precision))
        TEST_ASSERT(klab::Equals(xo[11], 8.0, precision))


        // Limit cases.
        klab::Convolve(arma::Col<klab::DoubleReal>(), f1, xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::Convolve(x, arma::Col<klab::DoubleReal>(), xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::Convolve(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>(), xo);
        TEST_ASSERT(xo.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testConvolve_Vector_Complex()
{
    try
    {
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(n);        
        arma::Col<std::complex<klab::DoubleReal> > xo;
        arma::Col<std::complex<klab::DoubleReal> > f1(4);
        arma::Col<std::complex<klab::DoubleReal> > f2(5);

        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = std::complex<klab::DoubleReal>(klab::DoubleReal(i+1), klab::DoubleReal(n-i));

        f1[0] = std::complex<klab::DoubleReal>(1.0, 8.0);
        f1[1] = std::complex<klab::DoubleReal>(2.0, 7.0);
        f1[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        f1[3] = std::complex<klab::DoubleReal>(4.0, 5.0);

        f2[0] = std::complex<klab::DoubleReal>(5.0, 8.0);
        f2[1] = std::complex<klab::DoubleReal>(4.0, 7.0);
        f2[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        f2[3] = std::complex<klab::DoubleReal>(2.0, 5.0);
        f2[4] = std::complex<klab::DoubleReal>(1.0, 4.0);


        klab::Convolve(x, f1, xo);
        TEST_ASSERT(xo.n_rows == (x.n_rows+f1.n_rows-1))
        TEST_ASSERT(klab::Equals(xo[0], std::complex<klab::DoubleReal>(-63.0, 16.0), precision))
        TEST_ASSERT(klab::Equals(xo[1], std::complex<klab::DoubleReal>(-108.0, 46.0), precision))
        TEST_ASSERT(klab::Equals(xo[2], std::complex<klab::DoubleReal>(-135.0, 88.0), precision))
        TEST_ASSERT(klab::Equals(xo[3], std::complex<klab::DoubleReal>(-144.0, 140.0), precision))
        TEST_ASSERT(klab::Equals(xo[4], std::complex<klab::DoubleReal>(-108.0, 156.0), precision))
        TEST_ASSERT(klab::Equals(xo[5], std::complex<klab::DoubleReal>(-72.0, 172.0), precision))
        TEST_ASSERT(klab::Equals(xo[6], std::complex<klab::DoubleReal>(-36.0, 188.0), precision))
        TEST_ASSERT(klab::Equals(xo[7], std::complex<klab::DoubleReal>( 0.0, 204.0), precision))
        TEST_ASSERT(klab::Equals(xo[8], std::complex<klab::DoubleReal>( 27.0, 148.0), precision))
        TEST_ASSERT(klab::Equals(xo[9], std::complex<klab::DoubleReal>( 36.0, 94.0), precision))
        TEST_ASSERT(klab::Equals(xo[10], std::complex<klab::DoubleReal>(27.0, 44.0), precision))

        klab::Convolve(x, f2, xo);
        TEST_ASSERT(xo.n_rows == (x.n_rows+f2.n_rows-1))
        TEST_ASSERT(klab::Equals(xo[0], std::complex<klab::DoubleReal>(-59.0, 48.0), precision))
        TEST_ASSERT(klab::Equals(xo[1], std::complex<klab::DoubleReal>(-98.0, 90.0), precision))
        TEST_ASSERT(klab::Equals(xo[2], std::complex<klab::DoubleReal>(-119.0, 126.0), precision))
        TEST_ASSERT(klab::Equals(xo[3], std::complex<klab::DoubleReal>(-124.0, 156.0), precision))
        TEST_ASSERT(klab::Equals(xo[4], std::complex<klab::DoubleReal>(-115.0, 180.0), precision))
        TEST_ASSERT(klab::Equals(xo[5], std::complex<klab::DoubleReal>(-70.0, 195.0), precision))
        TEST_ASSERT(klab::Equals(xo[6], std::complex<klab::DoubleReal>(-25.0, 210.0), precision))
        TEST_ASSERT(klab::Equals(xo[7], std::complex<klab::DoubleReal>(20.0, 225.0), precision))
        TEST_ASSERT(klab::Equals(xo[8], std::complex<klab::DoubleReal>(20.0, 168.0), precision))
        TEST_ASSERT(klab::Equals(xo[9], std::complex<klab::DoubleReal>(16.0, 117.0), precision))
        TEST_ASSERT(klab::Equals(xo[10], std::complex<klab::DoubleReal>(10.0, 72.0), precision))
        TEST_ASSERT(klab::Equals(xo[11], std::complex<klab::DoubleReal>(4.0, 33.0), precision))


        // Limit cases.
        klab::Convolve(arma::Col<std::complex<klab::DoubleReal> >(), f1, xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::Convolve(x, arma::Col<std::complex<klab::DoubleReal> >(), xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::Convolve(arma::Col<std::complex<klab::DoubleReal> >(), arma::Col<std::complex<klab::DoubleReal> >(), xo);
        TEST_ASSERT(xo.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testConvolve_Matrix()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-11;
         
        arma::Mat<klab::DoubleReal> x(m, n);
        arma::Mat<klab::DoubleReal> xo;
        arma::Mat<klab::DoubleReal> f1(2, 4);
        arma::Mat<klab::DoubleReal> f2(3, 5);
         
        x( 0, 0) = 0.0;
        x( 0, 1) = 1.0;
        x( 0, 2) = 2.0;
        x( 0, 3) = 3.0;
        x( 0, 4) = 4.0;
        x( 0, 5) = 5.0;
        x( 0, 6) = 6.0;
        x( 0, 7) = 7.0;
        x( 1, 0) = 8.0;
        x( 1, 1) = 9.0;
        x( 1, 2) = 10.0;
        x( 1, 3) = 11.0;
        x( 1, 4) = 12.0;
        x( 1, 5) = 13.0;
        x( 1, 6) = 14.0;
        x( 1, 7) = 15.0;
        x( 2, 0) = 16.0;
        x( 2, 1) = 17.0;
        x( 2, 2) = 18.0;
        x( 2, 3) = 19.0;
        x( 2, 4) = 20.0;
        x( 2, 5) = 21.0;
        x( 2, 6) = 22.0;
        x( 2, 7) = 23.0;
        x( 3, 0) = 24.0;
        x( 3, 1) = 25.0;
        x( 3, 2) = 26.0;
        x( 3, 3) = 27.0;
        x( 3, 4) = 28.0;
        x( 3, 5) = 29.0;
        x( 3, 6) = 30.0;
        x( 3, 7) = 31.0;
         
        f1( 0, 0) = 0.0;
        f1( 0, 1) = 1.0;
        f1( 0, 2) = 2.0;
        f1( 0, 3) = 3.0;
        f1( 1, 0) = 4.0;
        f1( 1, 1) = 5.0;
        f1( 1, 2) = 6.0;
        f1( 1, 3) = 7.0;
         
        f2( 0, 0) = 32.0;
        f2( 0, 1) = 31.0;
        f2( 0, 2) = 30.0;
        f2( 0, 3) = 29.0;
        f2( 0, 4) = 28.0;
        f2( 1, 0) = 27.0;
        f2( 1, 1) = 26.0;
        f2( 1, 2) = 25.0;
        f2( 1, 3) = 24.0;
        f2( 1, 4) = 23.0;
        f2( 2, 0) = 22.0;
        f2( 2, 1) = 21.0;
        f2( 2, 2) = 20.0;
        f2( 2, 3) = 19.0;
        f2( 2, 4) = 18.0;
         
        klab::Convolve(x, f1, xo);
        TEST_ASSERT(xo.n_rows==5 && xo.n_cols==11)
        TEST_ASSERT(klab::Equals(xo(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 2), 1.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 3), 4.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 4), 10.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 5), 16.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 6), 22.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 7), 28.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 8), 34.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 9), 32.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 10), 21.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 1), 12.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 2), 38.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 3), 80.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 4), 108.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 5), 136.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 6), 164.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 7), 192.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 8), 188.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 9), 156.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 10), 94.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 0), 32.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 1), 92.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 2), 182.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 3), 304.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 4), 332.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 5), 360.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 6), 388.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 7), 416.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 8), 380.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 9), 300.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 10), 174.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 0), 64.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 1), 172.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 2), 326.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 3), 528.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 4), 556.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 5), 584.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 6), 612.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 7), 640.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 8), 572.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 9), 444.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 10), 254.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 0), 96.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 1), 220.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 2), 373.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 3), 556.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 4), 578.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 5), 600.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 6), 622.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 7), 644.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 8), 538.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 9), 396.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 10), 217.0, precision))
         
        klab::Convolve(x, f2, xo);
        TEST_ASSERT(xo.n_rows==6 && xo.n_cols==12)
        TEST_ASSERT(klab::Equals(xo(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 1), 32.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 2), 95.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 3), 188.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 4), 310.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 5), 460.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 6), 610.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 7), 760.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 8), 654.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 9), 524.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 10), 371.0, precision))
        TEST_ASSERT(klab::Equals(xo(0, 11), 196.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 0), 256.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 1), 563.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 2), 919.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 3), 1322.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 4), 1770.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 5), 2045.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 6), 2320.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 7), 2595.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 8), 2142.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 9), 1654.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 10), 1133.0, precision))
        TEST_ASSERT(klab::Equals(xo(1, 11), 581.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 0), 728.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 1), 1513.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 2), 2352.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 3), 3242.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 4), 4180.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 5), 4555.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 6), 4930.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 7), 5305.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 8), 4304.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 9), 3270.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 10), 2206.0, precision))
        TEST_ASSERT(klab::Equals(xo(2, 11), 1115.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 0), 1376.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 1), 2785.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 2), 4224.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 3), 5690.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 4), 7180.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 5), 7555.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 6), 7930.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 7), 8305.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 8), 6656.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 9), 4998.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 10), 3334.0, precision))
        TEST_ASSERT(klab::Equals(xo(3, 11), 1667.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 0), 1000.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 1), 2009.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 2), 3025.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 3), 4046.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 4), 5070.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 5), 5295.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 6), 5520.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 7), 5745.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 8), 4578.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 9), 3418.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 10), 2267.0, precision))
        TEST_ASSERT(klab::Equals(xo(4, 11), 1127.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 0), 528.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 1), 1054.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 2), 1577.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 3), 2096.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 4), 2610.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 5), 2710.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 6), 2810.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 7), 2910.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 8), 2306.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 9), 1712.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 10), 1129.0, precision))
        TEST_ASSERT(klab::Equals(xo(5, 11), 558.0, precision))
         
        // Limit cases.
        klab::Convolve(arma::Mat<klab::DoubleReal>(), f1, xo);
        TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
         
        klab::Convolve(x, arma::Mat<klab::DoubleReal>(), xo);
        TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
         
        klab::Convolve(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>(), xo);
        TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testConvolve_Matrix_Complex()
{
    try
    {
        klab::UInt32 m = 4;
		klab::UInt32 n = 8;
		klab::DoubleReal precision = 1e-10;
		 
		arma::Mat<std::complex<klab::DoubleReal> > x(m, n);
		arma::Mat<std::complex<klab::DoubleReal> > xo;
		arma::Mat<std::complex<klab::DoubleReal> > f1(2, 4);
		arma::Mat<std::complex<klab::DoubleReal> > f2(3, 5);
		 
		x( 0, 0) = std::complex<klab::DoubleReal>(0.0, 32.0);
		x( 0, 1) = std::complex<klab::DoubleReal>(1.0, 31.0);
		x( 0, 2) = std::complex<klab::DoubleReal>(2.0, 30.0);
		x( 0, 3) = std::complex<klab::DoubleReal>(3.0, 29.0);
		x( 0, 4) = std::complex<klab::DoubleReal>(4.0, 28.0);
		x( 0, 5) = std::complex<klab::DoubleReal>(5.0, 27.0);
		x( 0, 6) = std::complex<klab::DoubleReal>(6.0, 26.0);
		x( 0, 7) = std::complex<klab::DoubleReal>(7.0, 25.0);
		x( 1, 0) = std::complex<klab::DoubleReal>(8.0, 24.0);
		x( 1, 1) = std::complex<klab::DoubleReal>(9.0, 23.0);
		x( 1, 2) = std::complex<klab::DoubleReal>(10.0, 22.0);
		x( 1, 3) = std::complex<klab::DoubleReal>(11.0, 21.0);
		x( 1, 4) = std::complex<klab::DoubleReal>(12.0, 20.0);
		x( 1, 5) = std::complex<klab::DoubleReal>(13.0, 19.0);
		x( 1, 6) = std::complex<klab::DoubleReal>(14.0, 18.0);
		x( 1, 7) = std::complex<klab::DoubleReal>(15.0, 17.0);
		x( 2, 0) = std::complex<klab::DoubleReal>(16.0, 16.0);
		x( 2, 1) = std::complex<klab::DoubleReal>(17.0, 15.0);
		x( 2, 2) = std::complex<klab::DoubleReal>(18.0, 14.0);
		x( 2, 3) = std::complex<klab::DoubleReal>(19.0, 13.0);
		x( 2, 4) = std::complex<klab::DoubleReal>(20.0, 12.0);
		x( 2, 5) = std::complex<klab::DoubleReal>(21.0, 11.0);
		x( 2, 6) = std::complex<klab::DoubleReal>(22.0, 10.0);
		x( 2, 7) = std::complex<klab::DoubleReal>(23.0, 9.0);
		x( 3, 0) = std::complex<klab::DoubleReal>(24.0, 8.0);
		x( 3, 1) = std::complex<klab::DoubleReal>(25.0, 7.0);
		x( 3, 2) = std::complex<klab::DoubleReal>(26.0, 6.0);
		x( 3, 3) = std::complex<klab::DoubleReal>(27.0, 5.0);
		x( 3, 4) = std::complex<klab::DoubleReal>(28.0, 4.0);
		x( 3, 5) = std::complex<klab::DoubleReal>(29.0, 3.0);
		x( 3, 6) = std::complex<klab::DoubleReal>(30.0, 2.0);
		x( 3, 7) = std::complex<klab::DoubleReal>(31.0, 1.0);
		 
		f1( 0, 0) = std::complex<klab::DoubleReal>(0.0, 32.0);
		f1( 0, 1) = std::complex<klab::DoubleReal>(1.0, 31.0);
		f1( 0, 2) = std::complex<klab::DoubleReal>(2.0, 30.0);
		f1( 0, 3) = std::complex<klab::DoubleReal>(3.0, 29.0);
		f1( 1, 0) = std::complex<klab::DoubleReal>(4.0, 28.0);
		f1( 1, 1) = std::complex<klab::DoubleReal>(5.0, 27.0);
		f1( 1, 2) = std::complex<klab::DoubleReal>(6.0, 26.0);
		f1( 1, 3) = std::complex<klab::DoubleReal>(7.0, 25.0);
		 
		f2( 0, 0) = std::complex<klab::DoubleReal>(32.0, 0.0);
		f2( 0, 1) = std::complex<klab::DoubleReal>(31.0, 1.0);
		f2( 0, 2) = std::complex<klab::DoubleReal>(30.0, 2.0);
		f2( 0, 3) = std::complex<klab::DoubleReal>(29.0, 3.0);
		f2( 0, 4) = std::complex<klab::DoubleReal>(28.0, 4.0);
		f2( 1, 0) = std::complex<klab::DoubleReal>(27.0, 5.0);
		f2( 1, 1) = std::complex<klab::DoubleReal>(26.0, 6.0);
		f2( 1, 2) = std::complex<klab::DoubleReal>(25.0, 7.0);
		f2( 1, 3) = std::complex<klab::DoubleReal>(24.0, 8.0);
		f2( 1, 4) = std::complex<klab::DoubleReal>(23.0, 9.0);
		f2( 2, 0) = std::complex<klab::DoubleReal>(22.0, 10.0);
		f2( 2, 1) = std::complex<klab::DoubleReal>(21.0, 11.0);
		f2( 2, 2) = std::complex<klab::DoubleReal>(20.0, 12.0);
		f2( 2, 3) = std::complex<klab::DoubleReal>(19.0, 13.0);
		f2( 2, 4) = std::complex<klab::DoubleReal>(18.0, 14.0);
		 
		klab::Convolve(x, f1, xo);
		TEST_ASSERT(xo.n_rows==5 && xo.n_cols==11)
		TEST_ASSERT(klab::Equals(xo(0, 0), std::complex<klab::DoubleReal>(-1024.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), std::complex<klab::DoubleReal>(-1984.0, 64.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), std::complex<klab::DoubleReal>(-2880.0, 190.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), std::complex<klab::DoubleReal>(-3712.0, 376.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), std::complex<klab::DoubleReal>(-3584.0, 492.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), std::complex<klab::DoubleReal>(-3456.0, 608.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), std::complex<klab::DoubleReal>(-3328.0, 724.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), std::complex<klab::DoubleReal>(-3200.0, 840.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), std::complex<klab::DoubleReal>(-2304.0, 700.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), std::complex<klab::DoubleReal>(-1472.0, 512.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), std::complex<klab::DoubleReal>(-704.0, 278.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), std::complex<klab::DoubleReal>(-1664.0, 384.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), std::complex<klab::DoubleReal>(-3200.0, 872.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), std::complex<klab::DoubleReal>(-4608.0, 1460.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), std::complex<klab::DoubleReal>(-5888.0, 2144.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), std::complex<klab::DoubleReal>(-5632.0, 2344.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), std::complex<klab::DoubleReal>(-5376.0, 2544.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), std::complex<klab::DoubleReal>(-5120.0, 2744.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), std::complex<klab::DoubleReal>(-4864.0, 2944.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), std::complex<klab::DoubleReal>(-3456.0, 2312.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), std::complex<klab::DoubleReal>(-2176.0, 1608.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), std::complex<klab::DoubleReal>(-1024.0, 836.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), std::complex<klab::DoubleReal>(-1152.0, 832.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), std::complex<klab::DoubleReal>(-2176.0, 1736.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), std::complex<klab::DoubleReal>(-3072.0, 2708.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), std::complex<klab::DoubleReal>(-3840.0, 3744.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), std::complex<klab::DoubleReal>(-3584.0, 3944.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), std::complex<klab::DoubleReal>(-3328.0, 4144.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), std::complex<klab::DoubleReal>(-3072.0, 4344.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), std::complex<klab::DoubleReal>(-2816.0, 4544.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), std::complex<klab::DoubleReal>(-1920.0, 3464.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), std::complex<klab::DoubleReal>(-1152.0, 2344.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), std::complex<klab::DoubleReal>(-512.0, 1188.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), std::complex<klab::DoubleReal>(-640.0, 1280.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), std::complex<klab::DoubleReal>(-1152.0, 2600.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), std::complex<klab::DoubleReal>(-1536.0, 3956.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), std::complex<klab::DoubleReal>(-1792.0, 5344.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), std::complex<klab::DoubleReal>(-1536.0, 5544.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), std::complex<klab::DoubleReal>(-1280.0, 5744.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), std::complex<klab::DoubleReal>(-1024.0, 5944.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), std::complex<klab::DoubleReal>(-768.0, 6144.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), std::complex<klab::DoubleReal>(-384.0, 4616.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), std::complex<klab::DoubleReal>(-128.0, 3080.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), std::complex<klab::DoubleReal>(0.0, 1540.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), std::complex<klab::DoubleReal>(-128.0, 704.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), std::complex<klab::DoubleReal>(-192.0, 1416.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), std::complex<klab::DoubleReal>(-192.0, 2134.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), std::complex<klab::DoubleReal>(-128.0, 2856.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), std::complex<klab::DoubleReal>(0.0, 2940.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), std::complex<klab::DoubleReal>(128.0, 3024.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), std::complex<klab::DoubleReal>(256.0, 3108.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), std::complex<klab::DoubleReal>(384.0, 3192.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), std::complex<klab::DoubleReal>(384.0, 2380.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), std::complex<klab::DoubleReal>(320.0, 1576.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), std::complex<klab::DoubleReal>(192.0, 782.0), precision))
		 
		klab::Convolve(x, f2, xo);
		TEST_ASSERT(xo.n_rows==6 && xo.n_cols==12)
		TEST_ASSERT(klab::Equals(xo(0, 0), std::complex<klab::DoubleReal>(0.0, 1024.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), std::complex<klab::DoubleReal>(0.0, 1984.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), std::complex<klab::DoubleReal>(0.0, 2882.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), std::complex<klab::DoubleReal>(0.0, 3720.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), std::complex<klab::DoubleReal>(0.0, 4500.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), std::complex<klab::DoubleReal>(160.0, 4360.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), std::complex<klab::DoubleReal>(320.0, 4220.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), std::complex<klab::DoubleReal>(480.0, 4080.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), std::complex<klab::DoubleReal>(384.0, 3172.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), std::complex<klab::DoubleReal>(288.0, 2312.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), std::complex<klab::DoubleReal>(192.0, 1498.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), std::complex<klab::DoubleReal>(96.0, 728.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), std::complex<klab::DoubleReal>(96.0, 1632.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), std::complex<klab::DoubleReal>(192.0, 3162.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), std::complex<klab::DoubleReal>(288.0, 4594.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), std::complex<klab::DoubleReal>(384.0, 5932.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), std::complex<klab::DoubleReal>(480.0, 7180.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), std::complex<klab::DoubleReal>(800.0, 6950.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), std::complex<klab::DoubleReal>(1120.0, 6720.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), std::complex<klab::DoubleReal>(1440.0, 6490.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), std::complex<klab::DoubleReal>(1152.0, 5060.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), std::complex<klab::DoubleReal>(864.0, 3700.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), std::complex<klab::DoubleReal>(576.0, 2406.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), std::complex<klab::DoubleReal>(288.0, 1174.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), std::complex<klab::DoubleReal>(288.0, 1904.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), std::complex<klab::DoubleReal>(576.0, 3694.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), std::complex<klab::DoubleReal>(864.0, 5376.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), std::complex<klab::DoubleReal>(1152.0, 6956.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), std::complex<klab::DoubleReal>(1440.0, 8440.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), std::complex<klab::DoubleReal>(1920.0, 8170.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), std::complex<klab::DoubleReal>(2400.0, 7900.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), std::complex<klab::DoubleReal>(2880.0, 7630.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), std::complex<klab::DoubleReal>(2304.0, 5984.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), std::complex<klab::DoubleReal>(1728.0, 4404.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), std::complex<klab::DoubleReal>(1152.0, 2884.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), std::complex<klab::DoubleReal>(576.0, 1418.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), std::complex<klab::DoubleReal>(1056.0, 1376.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), std::complex<klab::DoubleReal>(2112.0, 2686.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), std::complex<klab::DoubleReal>(3168.0, 3936.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), std::complex<klab::DoubleReal>(4224.0, 5132.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), std::complex<klab::DoubleReal>(5280.0, 6280.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), std::complex<klab::DoubleReal>(5760.0, 6010.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), std::complex<klab::DoubleReal>(6240.0, 5740.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), std::complex<klab::DoubleReal>(6720.0, 5470.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), std::complex<klab::DoubleReal>(5376.0, 4352.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), std::complex<klab::DoubleReal>(4032.0, 3252.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), std::complex<klab::DoubleReal>(2688.0, 2164.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), std::complex<klab::DoubleReal>(1344.0, 1082.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), std::complex<klab::DoubleReal>(800.0, 848.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), std::complex<klab::DoubleReal>(1600.0, 1678.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), std::complex<klab::DoubleReal>(2400.0, 2494.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), std::complex<klab::DoubleReal>(3200.0, 3300.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), std::complex<klab::DoubleReal>(4000.0, 4100.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), std::complex<klab::DoubleReal>(4320.0, 3970.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), std::complex<klab::DoubleReal>(4640.0, 3840.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), std::complex<klab::DoubleReal>(4960.0, 3710.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), std::complex<klab::DoubleReal>(3968.0, 3004.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), std::complex<klab::DoubleReal>(2976.0, 2284.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), std::complex<klab::DoubleReal>(1984.0, 1546.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), std::complex<klab::DoubleReal>(992.0, 786.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), std::complex<klab::DoubleReal>(448.0, 416.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), std::complex<klab::DoubleReal>(896.0, 836.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), std::complex<klab::DoubleReal>(1344.0, 1262.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), std::complex<klab::DoubleReal>(1792.0, 1696.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), std::complex<klab::DoubleReal>(2240.0, 2140.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), std::complex<klab::DoubleReal>(2400.0, 2100.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), std::complex<klab::DoubleReal>(2560.0, 2060.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), std::complex<klab::DoubleReal>(2720.0, 2020.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), std::complex<klab::DoubleReal>(2176.0, 1660.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), std::complex<klab::DoubleReal>(1632.0, 1280.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), std::complex<klab::DoubleReal>(1088.0, 878.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), std::complex<klab::DoubleReal>(544.0, 452.0), precision))
		 
		// Limit cases.
		klab::Convolve(arma::Mat<std::complex<klab::DoubleReal> >(), f1, xo);
		TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
		 
		klab::Convolve(x, arma::Mat<std::complex<klab::DoubleReal> >(), xo);
		TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
		 
		klab::Convolve(arma::Mat<std::complex<klab::DoubleReal> >(), arma::Mat<std::complex<klab::DoubleReal> >(), xo);
		TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)   
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testCrossCorrelate_Vector()
{
    try
    {
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(n);        
        arma::Col<klab::DoubleReal> xo;
        arma::Col<klab::DoubleReal> f1(4);
        arma::Col<klab::DoubleReal> f2(5);

        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = klab::DoubleReal(i+1);

        f1[0] = 1.0;
        f1[1] = 2.0;
        f1[2] = 3.0;
        f1[3] = 4.0;

        f2[0] = 5.0;
        f2[1] = 4.0;
        f2[2] = 3.0;
        f2[3] = 2.0;
        f2[4] = 1.0;


        klab::CrossCorrelate(x, f1, xo);
        TEST_ASSERT(xo.n_rows == 15)      
        TEST_ASSERT(klab::Equals(xo[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[3], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[4], 4.0, precision))
        TEST_ASSERT(klab::Equals(xo[5], 11.0, precision))
        TEST_ASSERT(klab::Equals(xo[6], 20.0, precision))   
        TEST_ASSERT(klab::Equals(xo[7], 30.0, precision))
        TEST_ASSERT(klab::Equals(xo[8], 40.0, precision))
        TEST_ASSERT(klab::Equals(xo[9], 50.0, precision))
        TEST_ASSERT(klab::Equals(xo[10], 60.0, precision))
        TEST_ASSERT(klab::Equals(xo[11], 70.0, precision))
        TEST_ASSERT(klab::Equals(xo[12], 44.0, precision))
        TEST_ASSERT(klab::Equals(xo[13], 23.0, precision))
        TEST_ASSERT(klab::Equals(xo[14], 8.0, precision))

        klab::CrossCorrelate(f1, x, xo);
        TEST_ASSERT(xo.n_rows == 15)
        TEST_ASSERT(klab::Equals(xo[0], 8.0, precision))
        TEST_ASSERT(klab::Equals(xo[1], 23.0, precision))
        TEST_ASSERT(klab::Equals(xo[2], 44.0, precision))
        TEST_ASSERT(klab::Equals(xo[3], 70.0, precision))
        TEST_ASSERT(klab::Equals(xo[4], 60.0, precision))
        TEST_ASSERT(klab::Equals(xo[5], 50.0, precision))
        TEST_ASSERT(klab::Equals(xo[6], 40.0, precision)) 
        TEST_ASSERT(klab::Equals(xo[7], 30.0, precision))
        TEST_ASSERT(klab::Equals(xo[8], 20.0, precision))
        TEST_ASSERT(klab::Equals(xo[9], 11.0, precision))
        TEST_ASSERT(klab::Equals(xo[10], 4.0, precision))
        TEST_ASSERT(klab::Equals(xo[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[14], 0.0, precision))

        klab::CrossCorrelate(x, f2, xo);
        TEST_ASSERT(xo.n_rows == 15)       
        TEST_ASSERT(klab::Equals(xo[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[3], 1.0, precision))
        TEST_ASSERT(klab::Equals(xo[4], 4.0, precision))
        TEST_ASSERT(klab::Equals(xo[5], 10.0, precision))
        TEST_ASSERT(klab::Equals(xo[6], 20.0, precision)) 
        TEST_ASSERT(klab::Equals(xo[7], 35.0, precision))
        TEST_ASSERT(klab::Equals(xo[8], 50.0, precision))
        TEST_ASSERT(klab::Equals(xo[9], 65.0, precision))
        TEST_ASSERT(klab::Equals(xo[10], 80.0, precision))
        TEST_ASSERT(klab::Equals(xo[11], 86.0, precision))
        TEST_ASSERT(klab::Equals(xo[12], 82.0, precision))
        TEST_ASSERT(klab::Equals(xo[13], 67.0, precision))
        TEST_ASSERT(klab::Equals(xo[14], 40.0, precision))

        klab::CrossCorrelate(f2, x, xo);
        TEST_ASSERT(xo.n_rows == 15)    
        TEST_ASSERT(klab::Equals(xo[0], 40.0, precision))
        TEST_ASSERT(klab::Equals(xo[1], 67.0, precision))
        TEST_ASSERT(klab::Equals(xo[2], 82.0, precision))
        TEST_ASSERT(klab::Equals(xo[3], 86.0, precision))
        TEST_ASSERT(klab::Equals(xo[4], 80.0, precision))
        TEST_ASSERT(klab::Equals(xo[5], 65.0, precision))
        TEST_ASSERT(klab::Equals(xo[6], 50.0, precision))
        TEST_ASSERT(klab::Equals(xo[7], 35.0, precision))
        TEST_ASSERT(klab::Equals(xo[8], 20.0, precision))
        TEST_ASSERT(klab::Equals(xo[9], 10.0, precision))
        TEST_ASSERT(klab::Equals(xo[10], 4.0, precision))
        TEST_ASSERT(klab::Equals(xo[11], 1.0, precision))
        TEST_ASSERT(klab::Equals(xo[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(xo[14], 0.0, precision))


        // Limit cases.
        klab::CrossCorrelate(x, x, xo);
        TEST_ASSERT(xo.n_rows == 15)
        TEST_ASSERT(klab::Equals(xo[0], 8.0, precision))
        TEST_ASSERT(klab::Equals(xo[1], 23.0, precision))
        TEST_ASSERT(klab::Equals(xo[2], 44.0, precision))
        TEST_ASSERT(klab::Equals(xo[3], 70.0, precision))
        TEST_ASSERT(klab::Equals(xo[4], 100.0, precision))
        TEST_ASSERT(klab::Equals(xo[5], 133.0, precision))
        TEST_ASSERT(klab::Equals(xo[6], 168.0, precision))
        TEST_ASSERT(klab::Equals(xo[7], 204.0, precision))
        TEST_ASSERT(klab::Equals(xo[8], 168.0, precision))
        TEST_ASSERT(klab::Equals(xo[9], 133.0, precision))
        TEST_ASSERT(klab::Equals(xo[10], 100.0, precision))
        TEST_ASSERT(klab::Equals(xo[11], 70.0, precision))
        TEST_ASSERT(klab::Equals(xo[12], 44.0, precision))
        TEST_ASSERT(klab::Equals(xo[13], 23.0, precision))
        TEST_ASSERT(klab::Equals(xo[14], 8.0, precision))                

        klab::CrossCorrelate(arma::Col<klab::DoubleReal>(), f1, xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::CrossCorrelate(x, arma::Col<klab::DoubleReal>(), xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::CrossCorrelate(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>(), xo);
        TEST_ASSERT(xo.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testCrossCorrelate_Vector_Complex()
{
    try
    {
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-11;

        arma::Col<std::complex<klab::DoubleReal> > x(n);        
        arma::Col<std::complex<klab::DoubleReal> > xo;
        arma::Col<std::complex<klab::DoubleReal> > f1(4);
        arma::Col<std::complex<klab::DoubleReal> > f2(5);

        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = std::complex<klab::DoubleReal>(klab::DoubleReal(i+1), klab::DoubleReal(n-i));

        f1[0] = std::complex<klab::DoubleReal>(1.0, 8.0);
        f1[1] = std::complex<klab::DoubleReal>(2.0, 7.0);
        f1[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        f1[3] = std::complex<klab::DoubleReal>(4.0, 5.0);

        f2[0] = std::complex<klab::DoubleReal>(5.0, 8.0);
        f2[1] = std::complex<klab::DoubleReal>(4.0, 7.0);
        f2[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        f2[3] = std::complex<klab::DoubleReal>(2.0, 5.0);
        f2[4] = std::complex<klab::DoubleReal>(1.0, 4.0);


        klab::CrossCorrelate(x, f1, xo);
        TEST_ASSERT(xo.n_rows == 15)      
        TEST_ASSERT(klab::Equals(xo[0], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[1], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[2], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[3], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[4], std::complex<klab::DoubleReal>(44.0, 27.0), precision))
        TEST_ASSERT(klab::Equals(xo[5], std::complex<klab::DoubleReal>(94.0, 36.0), precision))
        TEST_ASSERT(klab::Equals(xo[6], std::complex<klab::DoubleReal>(148.0, 27.0), precision))   
        TEST_ASSERT(klab::Equals(xo[7], std::complex<klab::DoubleReal>(204.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[8], std::complex<klab::DoubleReal>(188.0, -36.0), precision))
        TEST_ASSERT(klab::Equals(xo[9], std::complex<klab::DoubleReal>(172.0, -72.0), precision))
        TEST_ASSERT(klab::Equals(xo[10], std::complex<klab::DoubleReal>(156.0, -108.0), precision))
        TEST_ASSERT(klab::Equals(xo[11], std::complex<klab::DoubleReal>(140.0, -144.0), precision))
        TEST_ASSERT(klab::Equals(xo[12], std::complex<klab::DoubleReal>(88.0, -135.0), precision))
        TEST_ASSERT(klab::Equals(xo[13], std::complex<klab::DoubleReal>(46.0, -108.0), precision))
        TEST_ASSERT(klab::Equals(xo[14], std::complex<klab::DoubleReal>(16.0, -63.0), precision))

        klab::CrossCorrelate(f1, x, xo);
        TEST_ASSERT(xo.n_rows == 15)
        TEST_ASSERT(klab::Equals(xo[0], std::complex<klab::DoubleReal>(16.0, 63.0), precision))
        TEST_ASSERT(klab::Equals(xo[1], std::complex<klab::DoubleReal>(46.0, 108.0), precision))
        TEST_ASSERT(klab::Equals(xo[2], std::complex<klab::DoubleReal>(88.0, 135.0), precision))
        TEST_ASSERT(klab::Equals(xo[3], std::complex<klab::DoubleReal>(140.0, 144.0), precision))
        TEST_ASSERT(klab::Equals(xo[4], std::complex<klab::DoubleReal>(156.0, 108.0), precision))
        TEST_ASSERT(klab::Equals(xo[5], std::complex<klab::DoubleReal>(172.0, 72.0), precision))
        TEST_ASSERT(klab::Equals(xo[6], std::complex<klab::DoubleReal>(188.0, 36.0), precision)) 
        TEST_ASSERT(klab::Equals(xo[7], std::complex<klab::DoubleReal>(204.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[8], std::complex<klab::DoubleReal>(148.0, -27.0), precision))
        TEST_ASSERT(klab::Equals(xo[9], std::complex<klab::DoubleReal>(94.0, -36.0), precision))
        TEST_ASSERT(klab::Equals(xo[10], std::complex<klab::DoubleReal>(44.0, -27.0), precision))
        TEST_ASSERT(klab::Equals(xo[11], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[12], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[13], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[14], std::complex<klab::DoubleReal>(0.0, 0.0), precision))

        klab::CrossCorrelate(x, f2, xo);
        TEST_ASSERT(xo.n_rows == 15)       
        TEST_ASSERT(klab::Equals(xo[0], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[1], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[2], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[3], std::complex<klab::DoubleReal>(33.0, 4.0), precision))
        TEST_ASSERT(klab::Equals(xo[4], std::complex<klab::DoubleReal>(72.0, 10.0), precision))
        TEST_ASSERT(klab::Equals(xo[5], std::complex<klab::DoubleReal>(117.0, 16.0), precision))
        TEST_ASSERT(klab::Equals(xo[6], std::complex<klab::DoubleReal>(168.0, 20.0), precision)) 
        TEST_ASSERT(klab::Equals(xo[7], std::complex<klab::DoubleReal>(225.0, 20.0), precision))
        TEST_ASSERT(klab::Equals(xo[8], std::complex<klab::DoubleReal>(210.0, -25.0), precision))
        TEST_ASSERT(klab::Equals(xo[9], std::complex<klab::DoubleReal>(195.0, -70.0), precision))
        TEST_ASSERT(klab::Equals(xo[10], std::complex<klab::DoubleReal>(180.0, -115.0), precision))
        TEST_ASSERT(klab::Equals(xo[11], std::complex<klab::DoubleReal>(156.0, -124.0), precision))
        TEST_ASSERT(klab::Equals(xo[12], std::complex<klab::DoubleReal>(126.0, -119.0), precision))
        TEST_ASSERT(klab::Equals(xo[13], std::complex<klab::DoubleReal>(90.0, -98.0), precision))
        TEST_ASSERT(klab::Equals(xo[14], std::complex<klab::DoubleReal>(48.0, -59.0), precision))

        klab::CrossCorrelate(f2, x, xo);
        TEST_ASSERT(xo.n_rows == 15)    
        TEST_ASSERT(klab::Equals(xo[0], std::complex<klab::DoubleReal>(48.0, 59.0), precision))
        TEST_ASSERT(klab::Equals(xo[1], std::complex<klab::DoubleReal>(90.0, 98.0), precision))
        TEST_ASSERT(klab::Equals(xo[2], std::complex<klab::DoubleReal>(126.0, 119.0), precision))
        TEST_ASSERT(klab::Equals(xo[3], std::complex<klab::DoubleReal>(156.0, 124.0), precision))
        TEST_ASSERT(klab::Equals(xo[4], std::complex<klab::DoubleReal>(180.0, 115.0), precision))
        TEST_ASSERT(klab::Equals(xo[5], std::complex<klab::DoubleReal>(195.0, 70.0), precision))
        TEST_ASSERT(klab::Equals(xo[6], std::complex<klab::DoubleReal>(210.0, 25.0), precision))
        TEST_ASSERT(klab::Equals(xo[7], std::complex<klab::DoubleReal>(225.0, -20.0), precision))
        TEST_ASSERT(klab::Equals(xo[8], std::complex<klab::DoubleReal>(168.0, -20.0), precision))
        TEST_ASSERT(klab::Equals(xo[9], std::complex<klab::DoubleReal>(117.0, -16.0), precision))
        TEST_ASSERT(klab::Equals(xo[10], std::complex<klab::DoubleReal>(72.0, -10.0), precision))
        TEST_ASSERT(klab::Equals(xo[11], std::complex<klab::DoubleReal>(33.0, -4.0), precision))
        TEST_ASSERT(klab::Equals(xo[12], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[13], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[14], std::complex<klab::DoubleReal>(0.0, 0.0), precision))


        // Limit cases.
        klab::CrossCorrelate(x, x, xo);
        TEST_ASSERT(xo.n_rows == 15)
        TEST_ASSERT(klab::Equals(xo[0], std::complex<klab::DoubleReal>(16.0, 63.0), precision))
        TEST_ASSERT(klab::Equals(xo[1], std::complex<klab::DoubleReal>(46.0, 108.0), precision))
        TEST_ASSERT(klab::Equals(xo[2], std::complex<klab::DoubleReal>(88.0, 135.0), precision))
        TEST_ASSERT(klab::Equals(xo[3], std::complex<klab::DoubleReal>(140.0, 144.0), precision))
        TEST_ASSERT(klab::Equals(xo[4], std::complex<klab::DoubleReal>(200.0, 135.0), precision))
        TEST_ASSERT(klab::Equals(xo[5], std::complex<klab::DoubleReal>(266.0, 108.0), precision))
        TEST_ASSERT(klab::Equals(xo[6], std::complex<klab::DoubleReal>(336.0, 63.0), precision))
        TEST_ASSERT(klab::Equals(xo[7], std::complex<klab::DoubleReal>(408.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xo[8], std::complex<klab::DoubleReal>(336.0, -63.0), precision))
        TEST_ASSERT(klab::Equals(xo[9], std::complex<klab::DoubleReal>(266.0, -108.0), precision))
        TEST_ASSERT(klab::Equals(xo[10], std::complex<klab::DoubleReal>(200.0, -135.0), precision))
        TEST_ASSERT(klab::Equals(xo[11], std::complex<klab::DoubleReal>(140.0, -144.0), precision))
        TEST_ASSERT(klab::Equals(xo[12], std::complex<klab::DoubleReal>(88.0, -135.0), precision))
        TEST_ASSERT(klab::Equals(xo[13], std::complex<klab::DoubleReal>(46.0, -108.0), precision))
        TEST_ASSERT(klab::Equals(xo[14], std::complex<klab::DoubleReal>(16.0, -63.0), precision))                

        klab::CrossCorrelate(arma::Col<std::complex<klab::DoubleReal> >(), f1, xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::CrossCorrelate(x, arma::Col<std::complex<klab::DoubleReal> >(), xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::CrossCorrelate(arma::Col<std::complex<klab::DoubleReal> >(), arma::Col<std::complex<klab::DoubleReal> >(), xo);
        TEST_ASSERT(xo.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testCrossCorrelate_Matrix()
{
    try
    {
        klab::UInt32 m = 4;
		klab::UInt32 n = 8;
		klab::DoubleReal precision = 1e-10;
		 
		arma::Mat<klab::DoubleReal> x(m, n);
		arma::Mat<klab::DoubleReal> xo;
		arma::Mat<klab::DoubleReal> f1(2, 4);
		arma::Mat<klab::DoubleReal> f2(3, 5);
		 
		x( 0, 0) = 0.0;
		x( 0, 1) = 1.0;
		x( 0, 2) = 2.0;
		x( 0, 3) = 3.0;
		x( 0, 4) = 4.0;
		x( 0, 5) = 5.0;
		x( 0, 6) = 6.0;
		x( 0, 7) = 7.0;
		x( 1, 0) = 8.0;
		x( 1, 1) = 9.0;
		x( 1, 2) = 10.0;
		x( 1, 3) = 11.0;
		x( 1, 4) = 12.0;
		x( 1, 5) = 13.0;
		x( 1, 6) = 14.0;
		x( 1, 7) = 15.0;
		x( 2, 0) = 16.0;
		x( 2, 1) = 17.0;
		x( 2, 2) = 18.0;
		x( 2, 3) = 19.0;
		x( 2, 4) = 20.0;
		x( 2, 5) = 21.0;
		x( 2, 6) = 22.0;
		x( 2, 7) = 23.0;
		x( 3, 0) = 24.0;
		x( 3, 1) = 25.0;
		x( 3, 2) = 26.0;
		x( 3, 3) = 27.0;
		x( 3, 4) = 28.0;
		x( 3, 5) = 29.0;
		x( 3, 6) = 30.0;
		x( 3, 7) = 31.0;
		 
		f1( 0, 0) = 0.0;
		f1( 0, 1) = 1.0;
		f1( 0, 2) = 2.0;
		f1( 0, 3) = 3.0;
		f1( 1, 0) = 4.0;
		f1( 1, 1) = 5.0;
		f1( 1, 2) = 6.0;
		f1( 1, 3) = 7.0;
		 
		f2( 0, 0) = 32.0;
		f2( 0, 1) = 31.0;
		f2( 0, 2) = 30.0;
		f2( 0, 3) = 29.0;
		f2( 0, 4) = 28.0;
		f2( 1, 0) = 27.0;
		f2( 1, 1) = 26.0;
		f2( 1, 2) = 25.0;
		f2( 1, 3) = 24.0;
		f2( 1, 4) = 23.0;
		f2( 2, 0) = 22.0;
		f2( 2, 1) = 21.0;
		f2( 2, 2) = 20.0;
		f2( 2, 3) = 19.0;
		f2( 2, 4) = 18.0;
		 
		klab::CrossCorrelate(x, f1, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), 7.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), 20.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), 38.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), 60.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), 82.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), 104.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), 126.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), 92.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), 59.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), 28.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), 56.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), 114.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), 172.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), 228.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), 256.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), 284.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), 312.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), 340.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), 232.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), 138.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), 60.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), 136.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), 258.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), 364.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), 452.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), 480.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), 508.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), 536.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), 564.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), 376.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), 218.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), 92.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), 216.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), 402.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), 556.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), 676.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), 704.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), 732.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), 760.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), 788.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), 520.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), 298.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), 124.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), 72.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), 123.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), 152.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), 158.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), 164.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), 170.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), 176.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), 182.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), 92.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), 31.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), 0.0, precision))
		 
		klab::CrossCorrelate(f1, x, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), 31.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), 92.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), 182.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), 176.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), 170.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), 164.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), 158.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), 152.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), 123.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), 72.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), 124.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), 298.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), 520.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), 788.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), 760.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), 732.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), 704.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), 676.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), 556.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), 402.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), 216.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), 92.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), 218.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), 376.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), 564.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), 536.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), 508.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), 480.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), 452.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), 364.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), 258.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), 136.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), 60.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), 138.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), 232.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), 340.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), 312.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), 284.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), 256.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), 228.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), 172.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), 114.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), 56.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), 28.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), 59.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), 92.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), 126.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), 104.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), 82.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), 60.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), 38.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), 20.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), 7.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), 0.0, precision))
		 
		klab::CrossCorrelate(x, f2, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), 18.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), 55.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), 112.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), 190.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), 290.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), 390.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), 490.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), 446.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), 376.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), 279.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), 154.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), 144.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), 337.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), 581.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), 878.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), 1230.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), 1455.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), 1680.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), 1905.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), 1658.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), 1346.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), 967.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), 519.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), 472.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), 1037.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), 1698.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), 2458.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), 3320.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), 3695.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), 4070.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), 4445.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), 3796.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), 3030.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), 2144.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), 1135.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), 1024.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), 2165.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), 3426.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), 4810.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), 6320.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), 6695.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), 7070.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), 7445.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), 6244.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), 4902.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), 3416.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), 1783.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), 1000.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), 2091.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), 3275.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), 4554.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), 5930.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), 6205.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), 6480.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), 6755.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), 5622.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), 4382.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), 3033.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), 1573.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), 672.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), 1396.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), 2173.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), 3004.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), 3890.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), 4040.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), 4190.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), 4340.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), 3594.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), 2788.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), 1921.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), 992.0, precision))
		 
		klab::CrossCorrelate(f2, x, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), 992.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), 1921.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), 2788.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), 3594.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), 4340.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), 4190.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), 4040.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), 3890.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), 3004.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), 2173.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), 1396.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), 672.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), 1573.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), 3033.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), 4382.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), 5622.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), 6755.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), 6480.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), 6205.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), 5930.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), 4554.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), 3275.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), 2091.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), 1000.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), 1783.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), 3416.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), 4902.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), 6244.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), 7445.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), 7070.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), 6695.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), 6320.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), 4810.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), 3426.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), 2165.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), 1024.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), 1135.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), 2144.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), 3030.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), 3796.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), 4445.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), 4070.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), 3695.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), 3320.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), 2458.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), 1698.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), 1037.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), 472.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), 519.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), 967.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), 1346.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), 1658.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), 1905.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), 1680.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), 1455.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), 1230.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), 878.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), 581.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), 337.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), 144.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), 154.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), 279.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), 376.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), 446.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), 490.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), 390.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), 290.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), 190.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), 112.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), 55.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), 18.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), 0.0, precision))
		 
		// Limit cases.
		klab::CrossCorrelate(x, x, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), 0.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), 31.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), 92.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), 182.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), 300.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), 445.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), 616.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), 812.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), 784.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), 733.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), 660.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), 566.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), 452.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), 319.0, precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), 168.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), 248.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), 542.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), 880.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), 1260.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), 1680.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), 2138.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), 2632.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), 3160.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), 2856.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), 2522.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), 2160.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), 1772.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), 1360.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), 926.0, precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), 472.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), 680.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), 1405.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), 2172.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), 2978.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), 3820.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), 4695.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), 5600.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), 6532.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), 5768.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), 4983.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), 4180.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), 3362.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), 2532.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), 1693.0, precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), 848.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), 1232.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), 2492.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), 3776.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), 5080.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), 6400.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), 7732.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), 9072.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), 10416.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), 9072.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), 7732.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), 6400.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), 5080.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), 3776.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), 2492.0, precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), 1232.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), 848.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), 1693.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), 2532.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), 3362.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), 4180.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), 4983.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), 5768.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), 6532.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), 5600.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), 4695.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), 3820.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), 2978.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), 2172.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), 1405.0, precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), 680.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), 472.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), 926.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), 1360.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), 1772.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), 2160.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), 2522.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), 2856.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), 3160.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), 2632.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), 2138.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), 1680.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), 1260.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), 880.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), 542.0, precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), 248.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), 168.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), 319.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), 452.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), 566.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), 660.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), 733.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), 784.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), 812.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), 616.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), 445.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), 300.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), 182.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), 92.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), 31.0, precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), 0.0, precision))
		 
		klab::CrossCorrelate(arma::Mat<klab::DoubleReal>(), f1, xo);
		TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
		 
		klab::CrossCorrelate(x, arma::Mat<klab::DoubleReal>(), xo);
		TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
		 
		klab::CrossCorrelate(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>(), xo);
		TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testCrossCorrelate_Matrix_Complex()
{
    try
    {
        klab::UInt32 m = 4;
		klab::UInt32 n = 8;
		klab::DoubleReal precision = 1e-10;
		 
		arma::Mat<std::complex<klab::DoubleReal> > x(m, n);
		arma::Mat<std::complex<klab::DoubleReal> > xo;
		arma::Mat<std::complex<klab::DoubleReal> > f1(2, 4);
		arma::Mat<std::complex<klab::DoubleReal> > f2(3, 5);
		 
		x( 0, 0) = std::complex<klab::DoubleReal>(0.0, 32.0);
		x( 0, 1) = std::complex<klab::DoubleReal>(1.0, 31.0);
		x( 0, 2) = std::complex<klab::DoubleReal>(2.0, 30.0);
		x( 0, 3) = std::complex<klab::DoubleReal>(3.0, 29.0);
		x( 0, 4) = std::complex<klab::DoubleReal>(4.0, 28.0);
		x( 0, 5) = std::complex<klab::DoubleReal>(5.0, 27.0);
		x( 0, 6) = std::complex<klab::DoubleReal>(6.0, 26.0);
		x( 0, 7) = std::complex<klab::DoubleReal>(7.0, 25.0);
		x( 1, 0) = std::complex<klab::DoubleReal>(8.0, 24.0);
		x( 1, 1) = std::complex<klab::DoubleReal>(9.0, 23.0);
		x( 1, 2) = std::complex<klab::DoubleReal>(10.0, 22.0);
		x( 1, 3) = std::complex<klab::DoubleReal>(11.0, 21.0);
		x( 1, 4) = std::complex<klab::DoubleReal>(12.0, 20.0);
		x( 1, 5) = std::complex<klab::DoubleReal>(13.0, 19.0);
		x( 1, 6) = std::complex<klab::DoubleReal>(14.0, 18.0);
		x( 1, 7) = std::complex<klab::DoubleReal>(15.0, 17.0);
		x( 2, 0) = std::complex<klab::DoubleReal>(16.0, 16.0);
		x( 2, 1) = std::complex<klab::DoubleReal>(17.0, 15.0);
		x( 2, 2) = std::complex<klab::DoubleReal>(18.0, 14.0);
		x( 2, 3) = std::complex<klab::DoubleReal>(19.0, 13.0);
		x( 2, 4) = std::complex<klab::DoubleReal>(20.0, 12.0);
		x( 2, 5) = std::complex<klab::DoubleReal>(21.0, 11.0);
		x( 2, 6) = std::complex<klab::DoubleReal>(22.0, 10.0);
		x( 2, 7) = std::complex<klab::DoubleReal>(23.0, 9.0);
		x( 3, 0) = std::complex<klab::DoubleReal>(24.0, 8.0);
		x( 3, 1) = std::complex<klab::DoubleReal>(25.0, 7.0);
		x( 3, 2) = std::complex<klab::DoubleReal>(26.0, 6.0);
		x( 3, 3) = std::complex<klab::DoubleReal>(27.0, 5.0);
		x( 3, 4) = std::complex<klab::DoubleReal>(28.0, 4.0);
		x( 3, 5) = std::complex<klab::DoubleReal>(29.0, 3.0);
		x( 3, 6) = std::complex<klab::DoubleReal>(30.0, 2.0);
		x( 3, 7) = std::complex<klab::DoubleReal>(31.0, 1.0);
		 
		f1( 0, 0) = std::complex<klab::DoubleReal>(0.0, 32.0);
		f1( 0, 1) = std::complex<klab::DoubleReal>(1.0, 31.0);
		f1( 0, 2) = std::complex<klab::DoubleReal>(2.0, 30.0);
		f1( 0, 3) = std::complex<klab::DoubleReal>(3.0, 29.0);
		f1( 1, 0) = std::complex<klab::DoubleReal>(4.0, 28.0);
		f1( 1, 1) = std::complex<klab::DoubleReal>(5.0, 27.0);
		f1( 1, 2) = std::complex<klab::DoubleReal>(6.0, 26.0);
		f1( 1, 3) = std::complex<klab::DoubleReal>(7.0, 25.0);
		 
		f2( 0, 0) = std::complex<klab::DoubleReal>(32.0, 0.0);
		f2( 0, 1) = std::complex<klab::DoubleReal>(31.0, 1.0);
		f2( 0, 2) = std::complex<klab::DoubleReal>(30.0, 2.0);
		f2( 0, 3) = std::complex<klab::DoubleReal>(29.0, 3.0);
		f2( 0, 4) = std::complex<klab::DoubleReal>(28.0, 4.0);
		f2( 1, 0) = std::complex<klab::DoubleReal>(27.0, 5.0);
		f2( 1, 1) = std::complex<klab::DoubleReal>(26.0, 6.0);
		f2( 1, 2) = std::complex<klab::DoubleReal>(25.0, 7.0);
		f2( 1, 3) = std::complex<klab::DoubleReal>(24.0, 8.0);
		f2( 1, 4) = std::complex<klab::DoubleReal>(23.0, 9.0);
		f2( 2, 0) = std::complex<klab::DoubleReal>(22.0, 10.0);
		f2( 2, 1) = std::complex<klab::DoubleReal>(21.0, 11.0);
		f2( 2, 2) = std::complex<klab::DoubleReal>(20.0, 12.0);
		f2( 2, 3) = std::complex<klab::DoubleReal>(19.0, 13.0);
		f2( 2, 4) = std::complex<klab::DoubleReal>(18.0, 14.0);
		 
		klab::CrossCorrelate(x, f1, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), std::complex<klab::DoubleReal>(800.0, 224.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), std::complex<klab::DoubleReal>(1614.0, 384.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), std::complex<klab::DoubleReal>(2440.0, 480.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), std::complex<klab::DoubleReal>(3276.0, 512.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), std::complex<klab::DoubleReal>(3192.0, 384.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), std::complex<klab::DoubleReal>(3108.0, 256.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), std::complex<klab::DoubleReal>(3024.0, 128.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), std::complex<klab::DoubleReal>(2940.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), std::complex<klab::DoubleReal>(2200.0, -96.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), std::complex<klab::DoubleReal>(1462.0, -128.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), std::complex<klab::DoubleReal>(728.0, -96.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), std::complex<klab::DoubleReal>(1584.0, 64.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), std::complex<klab::DoubleReal>(3172.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), std::complex<klab::DoubleReal>(4760.0, -192.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), std::complex<klab::DoubleReal>(6344.0, -512.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), std::complex<klab::DoubleReal>(6144.0, -768.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), std::complex<klab::DoubleReal>(5944.0, -1024.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), std::complex<klab::DoubleReal>(5744.0, -1280.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), std::complex<klab::DoubleReal>(5544.0, -1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), std::complex<klab::DoubleReal>(4112.0, -1344.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), std::complex<klab::DoubleReal>(2708.0, -1024.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), std::complex<klab::DoubleReal>(1336.0, -576.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), std::complex<klab::DoubleReal>(1232.0, -448.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), std::complex<klab::DoubleReal>(2436.0, -1024.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), std::complex<klab::DoubleReal>(3608.0, -1728.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), std::complex<klab::DoubleReal>(4744.0, -2560.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), std::complex<klab::DoubleReal>(4544.0, -2816.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), std::complex<klab::DoubleReal>(4344.0, -3072.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), std::complex<klab::DoubleReal>(4144.0, -3328.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), std::complex<klab::DoubleReal>(3944.0, -3584.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), std::complex<klab::DoubleReal>(2864.0, -2880.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), std::complex<klab::DoubleReal>(1844.0, -2048.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), std::complex<klab::DoubleReal>(888.0, -1088.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), std::complex<klab::DoubleReal>(880.0, -960.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), std::complex<klab::DoubleReal>(1700.0, -2048.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), std::complex<klab::DoubleReal>(2456.0, -3264.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), std::complex<klab::DoubleReal>(3144.0, -4608.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), std::complex<klab::DoubleReal>(2944.0, -4864.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), std::complex<klab::DoubleReal>(2744.0, -5120.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), std::complex<klab::DoubleReal>(2544.0, -5376.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), std::complex<klab::DoubleReal>(2344.0, -5632.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), std::complex<klab::DoubleReal>(1616.0, -4416.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), std::complex<klab::DoubleReal>(980.0, -3072.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), std::complex<klab::DoubleReal>(440.0, -1600.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), std::complex<klab::DoubleReal>(304.0, -672.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), std::complex<klab::DoubleReal>(566.0, -1408.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), std::complex<klab::DoubleReal>(784.0, -2208.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), std::complex<klab::DoubleReal>(956.0, -3072.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), std::complex<klab::DoubleReal>(840.0, -3200.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), std::complex<klab::DoubleReal>(724.0, -3328.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), std::complex<klab::DoubleReal>(608.0, -3456.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), std::complex<klab::DoubleReal>(492.0, -3584.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), std::complex<klab::DoubleReal>(280.0, -2784.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), std::complex<klab::DoubleReal>(126.0, -1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), std::complex<klab::DoubleReal>(32.0, -992.0), precision))
		 
		klab::CrossCorrelate(f1, x, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), std::complex<klab::DoubleReal>(32.0, 992.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), std::complex<klab::DoubleReal>(126.0, 1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), std::complex<klab::DoubleReal>(280.0, 2784.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), std::complex<klab::DoubleReal>(492.0, 3584.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), std::complex<klab::DoubleReal>(608.0, 3456.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), std::complex<klab::DoubleReal>(724.0, 3328.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), std::complex<klab::DoubleReal>(840.0, 3200.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), std::complex<klab::DoubleReal>(956.0, 3072.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), std::complex<klab::DoubleReal>(784.0, 2208.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), std::complex<klab::DoubleReal>(566.0, 1408.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), std::complex<klab::DoubleReal>(304.0, 672.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), std::complex<klab::DoubleReal>(440.0, 1600.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), std::complex<klab::DoubleReal>(980.0, 3072.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), std::complex<klab::DoubleReal>(1616.0, 4416.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), std::complex<klab::DoubleReal>(2344.0, 5632.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), std::complex<klab::DoubleReal>(2544.0, 5376.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), std::complex<klab::DoubleReal>(2744.0, 5120.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), std::complex<klab::DoubleReal>(2944.0, 4864.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), std::complex<klab::DoubleReal>(3144.0, 4608.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), std::complex<klab::DoubleReal>(2456.0, 3264.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), std::complex<klab::DoubleReal>(1700.0, 2048.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), std::complex<klab::DoubleReal>(880.0, 960.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), std::complex<klab::DoubleReal>(888.0, 1088.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), std::complex<klab::DoubleReal>(1844.0, 2048.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), std::complex<klab::DoubleReal>(2864.0, 2880.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), std::complex<klab::DoubleReal>(3944.0, 3584.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), std::complex<klab::DoubleReal>(4144.0, 3328.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), std::complex<klab::DoubleReal>(4344.0, 3072.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), std::complex<klab::DoubleReal>(4544.0, 2816.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), std::complex<klab::DoubleReal>(4744.0, 2560.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), std::complex<klab::DoubleReal>(3608.0, 1728.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), std::complex<klab::DoubleReal>(2436.0, 1024.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), std::complex<klab::DoubleReal>(1232.0, 448.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), std::complex<klab::DoubleReal>(1336.0, 576.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), std::complex<klab::DoubleReal>(2708.0, 1024.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), std::complex<klab::DoubleReal>(4112.0, 1344.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), std::complex<klab::DoubleReal>(5544.0, 1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), std::complex<klab::DoubleReal>(5744.0, 1280.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), std::complex<klab::DoubleReal>(5944.0, 1024.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), std::complex<klab::DoubleReal>(6144.0, 768.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), std::complex<klab::DoubleReal>(6344.0, 512.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), std::complex<klab::DoubleReal>(4760.0, 192.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), std::complex<klab::DoubleReal>(3172.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), std::complex<klab::DoubleReal>(1584.0, -64.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), std::complex<klab::DoubleReal>(728.0, 96.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), std::complex<klab::DoubleReal>(1462.0, 128.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), std::complex<klab::DoubleReal>(2200.0, 96.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), std::complex<klab::DoubleReal>(2940.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), std::complex<klab::DoubleReal>(3024.0, -128.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), std::complex<klab::DoubleReal>(3108.0, -256.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), std::complex<klab::DoubleReal>(3192.0, -384.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), std::complex<klab::DoubleReal>(3276.0, -512.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), std::complex<klab::DoubleReal>(2440.0, -480.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), std::complex<klab::DoubleReal>(1614.0, -384.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), std::complex<klab::DoubleReal>(800.0, -224.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		 
		klab::CrossCorrelate(x, f2, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), std::complex<klab::DoubleReal>(448.0, 576.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), std::complex<klab::DoubleReal>(868.0, 1152.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), std::complex<klab::DoubleReal>(1262.0, 1728.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), std::complex<klab::DoubleReal>(1632.0, 2304.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), std::complex<klab::DoubleReal>(1980.0, 2880.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), std::complex<klab::DoubleReal>(2020.0, 2720.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), std::complex<klab::DoubleReal>(2060.0, 2560.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), std::complex<klab::DoubleReal>(2100.0, 2400.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), std::complex<klab::DoubleReal>(1660.0, 1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), std::complex<klab::DoubleReal>(1232.0, 1440.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), std::complex<klab::DoubleReal>(814.0, 960.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), std::complex<klab::DoubleReal>(404.0, 480.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), std::complex<klab::DoubleReal>(768.0, 1056.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), std::complex<klab::DoubleReal>(1506.0, 2112.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), std::complex<klab::DoubleReal>(2218.0, 3168.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), std::complex<klab::DoubleReal>(2908.0, 4224.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), std::complex<klab::DoubleReal>(3580.0, 5280.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), std::complex<klab::DoubleReal>(3710.0, 4960.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), std::complex<klab::DoubleReal>(3840.0, 4640.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), std::complex<klab::DoubleReal>(3970.0, 4320.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), std::complex<klab::DoubleReal>(3188.0, 3456.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), std::complex<klab::DoubleReal>(2404.0, 2592.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), std::complex<klab::DoubleReal>(1614.0, 1728.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), std::complex<klab::DoubleReal>(814.0, 864.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), std::complex<klab::DoubleReal>(1040.0, 1440.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), std::complex<klab::DoubleReal>(2074.0, 2880.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), std::complex<klab::DoubleReal>(3108.0, 4320.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), std::complex<klab::DoubleReal>(4148.0, 5760.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), std::complex<klab::DoubleReal>(5200.0, 7200.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), std::complex<klab::DoubleReal>(5470.0, 6720.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), std::complex<klab::DoubleReal>(5740.0, 6240.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), std::complex<klab::DoubleReal>(6010.0, 5760.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), std::complex<klab::DoubleReal>(4904.0, 4608.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), std::complex<klab::DoubleReal>(3756.0, 3456.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), std::complex<klab::DoubleReal>(2560.0, 2304.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), std::complex<klab::DoubleReal>(1310.0, 1152.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), std::complex<klab::DoubleReal>(1376.0, 672.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), std::complex<klab::DoubleReal>(2794.0, 1344.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), std::complex<klab::DoubleReal>(4260.0, 2016.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), std::complex<klab::DoubleReal>(5780.0, 2688.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), std::complex<klab::DoubleReal>(7360.0, 3360.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), std::complex<klab::DoubleReal>(7630.0, 2880.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), std::complex<klab::DoubleReal>(7900.0, 2400.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), std::complex<klab::DoubleReal>(8170.0, 1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), std::complex<klab::DoubleReal>(6728.0, 1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), std::complex<klab::DoubleReal>(5196.0, 1152.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), std::complex<klab::DoubleReal>(3568.0, 768.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), std::complex<klab::DoubleReal>(1838.0, 384.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), std::complex<klab::DoubleReal>(1136.0, 352.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), std::complex<klab::DoubleReal>(2326.0, 704.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), std::complex<klab::DoubleReal>(3574.0, 1056.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), std::complex<klab::DoubleReal>(4884.0, 1408.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), std::complex<klab::DoubleReal>(6260.0, 1760.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), std::complex<klab::DoubleReal>(6490.0, 1440.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), std::complex<klab::DoubleReal>(6720.0, 1120.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), std::complex<klab::DoubleReal>(6950.0, 800.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), std::complex<klab::DoubleReal>(5740.0, 640.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), std::complex<klab::DoubleReal>(4444.0, 480.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), std::complex<klab::DoubleReal>(3058.0, 320.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), std::complex<klab::DoubleReal>(1578.0, 160.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), std::complex<klab::DoubleReal>(704.0, 128.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), std::complex<klab::DoubleReal>(1448.0, 256.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), std::complex<klab::DoubleReal>(2234.0, 384.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), std::complex<klab::DoubleReal>(3064.0, 512.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), std::complex<klab::DoubleReal>(3940.0, 640.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), std::complex<klab::DoubleReal>(4080.0, 480.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), std::complex<klab::DoubleReal>(4220.0, 320.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), std::complex<klab::DoubleReal>(4360.0, 160.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), std::complex<klab::DoubleReal>(3604.0, 128.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), std::complex<klab::DoubleReal>(2792.0, 96.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), std::complex<klab::DoubleReal>(1922.0, 64.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), std::complex<klab::DoubleReal>(992.0, 32.0), precision))
		 
		klab::CrossCorrelate(f2, x, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), std::complex<klab::DoubleReal>(992.0, -32.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), std::complex<klab::DoubleReal>(1922.0, -64.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), std::complex<klab::DoubleReal>(2792.0, -96.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), std::complex<klab::DoubleReal>(3604.0, -128.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), std::complex<klab::DoubleReal>(4360.0, -160.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), std::complex<klab::DoubleReal>(4220.0, -320.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), std::complex<klab::DoubleReal>(4080.0, -480.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), std::complex<klab::DoubleReal>(3940.0, -640.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), std::complex<klab::DoubleReal>(3064.0, -512.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), std::complex<klab::DoubleReal>(2234.0, -384.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), std::complex<klab::DoubleReal>(1448.0, -256.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), std::complex<klab::DoubleReal>(704.0, -128.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), std::complex<klab::DoubleReal>(1578.0, -160.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), std::complex<klab::DoubleReal>(3058.0, -320.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), std::complex<klab::DoubleReal>(4444.0, -480.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), std::complex<klab::DoubleReal>(5740.0, -640.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), std::complex<klab::DoubleReal>(6950.0, -800.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), std::complex<klab::DoubleReal>(6720.0, -1120.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), std::complex<klab::DoubleReal>(6490.0, -1440.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), std::complex<klab::DoubleReal>(6260.0, -1760.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), std::complex<klab::DoubleReal>(4884.0, -1408.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), std::complex<klab::DoubleReal>(3574.0, -1056.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), std::complex<klab::DoubleReal>(2326.0, -704.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), std::complex<klab::DoubleReal>(1136.0, -352.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), std::complex<klab::DoubleReal>(1838.0, -384.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), std::complex<klab::DoubleReal>(3568.0, -768.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), std::complex<klab::DoubleReal>(5196.0, -1152.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), std::complex<klab::DoubleReal>(6728.0, -1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), std::complex<klab::DoubleReal>(8170.0, -1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), std::complex<klab::DoubleReal>(7900.0, -2400.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), std::complex<klab::DoubleReal>(7630.0, -2880.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), std::complex<klab::DoubleReal>(7360.0, -3360.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), std::complex<klab::DoubleReal>(5780.0, -2688.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), std::complex<klab::DoubleReal>(4260.0, -2016.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), std::complex<klab::DoubleReal>(2794.0, -1344.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), std::complex<klab::DoubleReal>(1376.0, -672.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), std::complex<klab::DoubleReal>(1310.0, -1152.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), std::complex<klab::DoubleReal>(2560.0, -2304.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), std::complex<klab::DoubleReal>(3756.0, -3456.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), std::complex<klab::DoubleReal>(4904.0, -4608.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), std::complex<klab::DoubleReal>(6010.0, -5760.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), std::complex<klab::DoubleReal>(5740.0, -6240.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), std::complex<klab::DoubleReal>(5470.0, -6720.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), std::complex<klab::DoubleReal>(5200.0, -7200.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), std::complex<klab::DoubleReal>(4148.0, -5760.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), std::complex<klab::DoubleReal>(3108.0, -4320.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), std::complex<klab::DoubleReal>(2074.0, -2880.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), std::complex<klab::DoubleReal>(1040.0, -1440.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), std::complex<klab::DoubleReal>(814.0, -864.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), std::complex<klab::DoubleReal>(1614.0, -1728.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), std::complex<klab::DoubleReal>(2404.0, -2592.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), std::complex<klab::DoubleReal>(3188.0, -3456.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), std::complex<klab::DoubleReal>(3970.0, -4320.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), std::complex<klab::DoubleReal>(3840.0, -4640.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), std::complex<klab::DoubleReal>(3710.0, -4960.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), std::complex<klab::DoubleReal>(3580.0, -5280.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), std::complex<klab::DoubleReal>(2908.0, -4224.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), std::complex<klab::DoubleReal>(2218.0, -3168.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), std::complex<klab::DoubleReal>(1506.0, -2112.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), std::complex<klab::DoubleReal>(768.0, -1056.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), std::complex<klab::DoubleReal>(404.0, -480.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), std::complex<klab::DoubleReal>(814.0, -960.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), std::complex<klab::DoubleReal>(1232.0, -1440.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), std::complex<klab::DoubleReal>(1660.0, -1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), std::complex<klab::DoubleReal>(2100.0, -2400.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), std::complex<klab::DoubleReal>(2060.0, -2560.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), std::complex<klab::DoubleReal>(2020.0, -2720.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), std::complex<klab::DoubleReal>(1980.0, -2880.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), std::complex<klab::DoubleReal>(1632.0, -2304.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), std::complex<klab::DoubleReal>(1262.0, -1728.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), std::complex<klab::DoubleReal>(868.0, -1152.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), std::complex<klab::DoubleReal>(448.0, -576.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		 
		// Limit cases.
		klab::CrossCorrelate(x, x, xo);
		TEST_ASSERT(xo.n_rows==7 && xo.n_cols==15)
		TEST_ASSERT(klab::Equals(xo(0, 0), std::complex<klab::DoubleReal>(32.0, 992.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 1), std::complex<klab::DoubleReal>(126.0, 1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 2), std::complex<klab::DoubleReal>(280.0, 2784.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 3), std::complex<klab::DoubleReal>(492.0, 3584.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 4), std::complex<klab::DoubleReal>(760.0, 4320.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 5), std::complex<klab::DoubleReal>(1082.0, 4992.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 6), std::complex<klab::DoubleReal>(1456.0, 5600.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 7), std::complex<klab::DoubleReal>(1880.0, 6144.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 8), std::complex<klab::DoubleReal>(1792.0, 5152.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 9), std::complex<klab::DoubleReal>(1658.0, 4224.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 10), std::complex<klab::DoubleReal>(1480.0, 3360.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 11), std::complex<klab::DoubleReal>(1260.0, 2560.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 12), std::complex<klab::DoubleReal>(1000.0, 1824.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 13), std::complex<klab::DoubleReal>(702.0, 1152.0), precision))
		TEST_ASSERT(klab::Equals(xo(0, 14), std::complex<klab::DoubleReal>(368.0, 544.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 0), std::complex<klab::DoubleReal>(560.0, 1472.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 1), std::complex<klab::DoubleReal>(1212.0, 2816.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 2), std::complex<klab::DoubleReal>(1952.0, 4032.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 3), std::complex<klab::DoubleReal>(2776.0, 5120.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 4), std::complex<klab::DoubleReal>(3680.0, 6080.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 5), std::complex<klab::DoubleReal>(4660.0, 6912.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 6), std::complex<klab::DoubleReal>(5712.0, 7616.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 7), std::complex<klab::DoubleReal>(6832.0, 8192.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 8), std::complex<klab::DoubleReal>(6160.0, 6720.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 9), std::complex<klab::DoubleReal>(5428.0, 5376.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 10), std::complex<klab::DoubleReal>(4640.0, 4160.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 11), std::complex<klab::DoubleReal>(3800.0, 3072.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 12), std::complex<klab::DoubleReal>(2912.0, 2112.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 13), std::complex<klab::DoubleReal>(1980.0, 1280.0), precision))
		TEST_ASSERT(klab::Equals(xo(1, 14), std::complex<klab::DoubleReal>(1008.0, 576.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 0), std::complex<klab::DoubleReal>(1456.0, 1440.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 1), std::complex<klab::DoubleReal>(3002.0, 2688.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 2), std::complex<klab::DoubleReal>(4632.0, 3744.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 3), std::complex<klab::DoubleReal>(6340.0, 4608.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 4), std::complex<klab::DoubleReal>(8120.0, 5280.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 5), std::complex<klab::DoubleReal>(9966.0, 5760.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 6), std::complex<klab::DoubleReal>(11872.0, 6048.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 7), std::complex<klab::DoubleReal>(13832.0, 6144.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 8), std::complex<klab::DoubleReal>(12208.0, 4704.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 9), std::complex<klab::DoubleReal>(10542.0, 3456.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 10), std::complex<klab::DoubleReal>(8840.0, 2400.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 11), std::complex<klab::DoubleReal>(7108.0, 1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 12), std::complex<klab::DoubleReal>(5352.0, 864.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 13), std::complex<klab::DoubleReal>(3578.0, 384.0), precision))
		TEST_ASSERT(klab::Equals(xo(2, 14), std::complex<klab::DoubleReal>(1792.0, 96.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 0), std::complex<klab::DoubleReal>(2592.0, 896.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 1), std::complex<klab::DoubleReal>(5240.0, 1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 2), std::complex<klab::DoubleReal>(7936.0, 1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 3), std::complex<klab::DoubleReal>(10672.0, 2048.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 4), std::complex<klab::DoubleReal>(13440.0, 1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 5), std::complex<klab::DoubleReal>(16232.0, 1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 6), std::complex<klab::DoubleReal>(19040.0, 896.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 7), std::complex<klab::DoubleReal>(21856.0, 0.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 8), std::complex<klab::DoubleReal>(19040.0, -896.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 9), std::complex<klab::DoubleReal>(16232.0, -1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 10), std::complex<klab::DoubleReal>(13440.0, -1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 11), std::complex<klab::DoubleReal>(10672.0, -2048.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 12), std::complex<klab::DoubleReal>(7936.0, -1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 13), std::complex<klab::DoubleReal>(5240.0, -1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(3, 14), std::complex<klab::DoubleReal>(2592.0, -896.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 0), std::complex<klab::DoubleReal>(1792.0, -96.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 1), std::complex<klab::DoubleReal>(3578.0, -384.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 2), std::complex<klab::DoubleReal>(5352.0, -864.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 3), std::complex<klab::DoubleReal>(7108.0, -1536.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 4), std::complex<klab::DoubleReal>(8840.0, -2400.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 5), std::complex<klab::DoubleReal>(10542.0, -3456.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 6), std::complex<klab::DoubleReal>(12208.0, -4704.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 7), std::complex<klab::DoubleReal>(13832.0, -6144.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 8), std::complex<klab::DoubleReal>(11872.0, -6048.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 9), std::complex<klab::DoubleReal>(9966.0, -5760.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 10), std::complex<klab::DoubleReal>(8120.0, -5280.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 11), std::complex<klab::DoubleReal>(6340.0, -4608.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 12), std::complex<klab::DoubleReal>(4632.0, -3744.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 13), std::complex<klab::DoubleReal>(3002.0, -2688.0), precision))
		TEST_ASSERT(klab::Equals(xo(4, 14), std::complex<klab::DoubleReal>(1456.0, -1440.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 0), std::complex<klab::DoubleReal>(1008.0, -576.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 1), std::complex<klab::DoubleReal>(1980.0, -1280.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 2), std::complex<klab::DoubleReal>(2912.0, -2112.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 3), std::complex<klab::DoubleReal>(3800.0, -3072.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 4), std::complex<klab::DoubleReal>(4640.0, -4160.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 5), std::complex<klab::DoubleReal>(5428.0, -5376.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 6), std::complex<klab::DoubleReal>(6160.0, -6720.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 7), std::complex<klab::DoubleReal>(6832.0, -8192.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 8), std::complex<klab::DoubleReal>(5712.0, -7616.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 9), std::complex<klab::DoubleReal>(4660.0, -6912.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 10), std::complex<klab::DoubleReal>(3680.0, -6080.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 11), std::complex<klab::DoubleReal>(2776.0, -5120.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 12), std::complex<klab::DoubleReal>(1952.0, -4032.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 13), std::complex<klab::DoubleReal>(1212.0, -2816.0), precision))
		TEST_ASSERT(klab::Equals(xo(5, 14), std::complex<klab::DoubleReal>(560.0, -1472.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 0), std::complex<klab::DoubleReal>(368.0, -544.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 1), std::complex<klab::DoubleReal>(702.0, -1152.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 2), std::complex<klab::DoubleReal>(1000.0, -1824.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 3), std::complex<klab::DoubleReal>(1260.0, -2560.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 4), std::complex<klab::DoubleReal>(1480.0, -3360.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 5), std::complex<klab::DoubleReal>(1658.0, -4224.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 6), std::complex<klab::DoubleReal>(1792.0, -5152.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 7), std::complex<klab::DoubleReal>(1880.0, -6144.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 8), std::complex<klab::DoubleReal>(1456.0, -5600.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 9), std::complex<klab::DoubleReal>(1082.0, -4992.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 10), std::complex<klab::DoubleReal>(760.0, -4320.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 11), std::complex<klab::DoubleReal>(492.0, -3584.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 12), std::complex<klab::DoubleReal>(280.0, -2784.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 13), std::complex<klab::DoubleReal>(126.0, -1920.0), precision))
		TEST_ASSERT(klab::Equals(xo(6, 14), std::complex<klab::DoubleReal>(32.0, -992.0), precision))
		 
		klab::CrossCorrelate(arma::Mat<std::complex<klab::DoubleReal> >(), f1, xo);
		TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
		 
		klab::CrossCorrelate(x, arma::Mat<std::complex<klab::DoubleReal> >(), xo);
		TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
		 
		klab::CrossCorrelate(arma::Mat<std::complex<klab::DoubleReal> >(), arma::Mat<std::complex<klab::DoubleReal> >(), xo);
		TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testCorrelation_Vector()
{
    try
    {
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(n);        
        arma::Col<klab::DoubleReal> f1(4);
        arma::Col<klab::DoubleReal> f2(5);

        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = klab::DoubleReal(i+1);

        f1[0] = 1.0;
        f1[1] = 2.0;
        f1[2] = 3.0;
        f1[3] = 4.0;

        f2[0] = 5.0;
        f2[1] = 4.0;
        f2[2] = 3.0;
        f2[3] = 2.0;
        f2[4] = 1.0;


        klab::DoubleReal result = klab::Correlation(x, f1);
        TEST_ASSERT(klab::Equals(result, -0.5532833351724882, precision))   

        result = klab::Correlation(f1, x);
        TEST_ASSERT(klab::Equals(result, -0.5532833351724882, precision))  

        result = klab::Correlation(x, f2);
        TEST_ASSERT(klab::Equals(result, -0.9673518784288834, precision))  

        result = klab::Correlation(f2, x);
        TEST_ASSERT(klab::Equals(result, -0.9673518784288834, precision)) 

        result = klab::Correlation(f1, f2);
        TEST_ASSERT(klab::Equals(result, 0.0, precision))  

        result = klab::Correlation(f2, f1);
        TEST_ASSERT(klab::Equals(result, 0.0, precision))  

        result = klab::Correlation(x, x);
		TEST_ASSERT(klab::Equals(result, 1.0, precision))

        result = klab::Correlation(f1, f1);
		TEST_ASSERT(klab::Equals(result, 1.0, precision))

        result = klab::Correlation(f2, f2);
		TEST_ASSERT(klab::Equals(result, 1.0, precision))


        arma::Col<klab::DoubleReal> u(n);
        arma::Col<klab::DoubleReal> v(n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            u[i] = 4.5;
            v[i] = 4.5;
        }
        result = klab::Correlation(u, v);
		TEST_ASSERT(klab::Equals(result, 1.0, precision))

        for(klab::UInt32 i=0; i<n; ++i)
            v[i] = 5.0;
        result = klab::Correlation(u, v);
		TEST_ASSERT(klab::Equals(result, 0.0, precision))


        // Limit cases.      
        result = klab::Correlation(arma::Col<klab::DoubleReal>(), f1);
		TEST_ASSERT(klab::Equals(result, 0.0, precision))
		 
		result = klab::Correlation(x, arma::Col<klab::DoubleReal>());
		TEST_ASSERT(klab::Equals(result, 0.0, precision))
		 
		result = klab::Correlation(arma::Col<klab::DoubleReal>(), arma::Col<klab::DoubleReal>());
		TEST_ASSERT(klab::Equals(result, 0.0, precision))        
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testCorrelation_Vector_Complex()
{
    try
    {
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-10;

        arma::Col<std::complex<klab::DoubleReal> > x(n);        
        arma::Col<std::complex<klab::DoubleReal> > f1(4);
        arma::Col<std::complex<klab::DoubleReal> > f2(5);

        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = std::complex<klab::DoubleReal>(klab::DoubleReal(i+1), klab::DoubleReal(n-i));

        f1[0] = std::complex<klab::DoubleReal>(1.0, 8.0);
        f1[1] = std::complex<klab::DoubleReal>(2.0, 7.0);
        f1[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        f1[3] = std::complex<klab::DoubleReal>(4.0, 5.0);

        f2[0] = std::complex<klab::DoubleReal>(5.0, 8.0);
        f2[1] = std::complex<klab::DoubleReal>(4.0, 7.0);
        f2[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        f2[3] = std::complex<klab::DoubleReal>(2.0, 5.0);
        f2[4] = std::complex<klab::DoubleReal>(1.0, 4.0);


        std::complex<klab::DoubleReal> result = klab::Correlation(x, f1);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.4430143138127601, -0.759453109393303), precision))   

        result = klab::Correlation(f1, x);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.4430143138127601, 0.759453109393303), precision))  

        result = klab::Correlation(x, f2);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.240294942858501, -0.9344803331338614), precision))  

        result = klab::Correlation(f2, x);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.240294942858501, 0.9344803331338614), precision)) 

        result = klab::Correlation(f1, f2);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.5761659596980318, -0.5761659596980318), precision))  

        result = klab::Correlation(f2, f1);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.5761659596980318, 0.5761659596980318), precision))  

        result = klab::Correlation(x, x);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(1.0, 0.0), precision))

        result = klab::Correlation(f1, f1);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(1.0, 0.0), precision))

        result = klab::Correlation(f2, f2);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(1.0, 0.0), precision))


        arma::Col<std::complex<klab::DoubleReal> > u(n);
        arma::Col<std::complex<klab::DoubleReal> > v(n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            u[i] = std::complex<klab::DoubleReal>(4.5, -3.2);
            v[i] = std::complex<klab::DoubleReal>(4.5, -3.2);
        }
        result = klab::Correlation(u, v);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(1.0, 0.0), precision))

        for(klab::UInt32 i=0; i<n; ++i)
            v[i] = std::complex<klab::DoubleReal>(5.0, -4.0);
        result = klab::Correlation(u, v);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.0, 0.0), precision))


        // Limit cases.      
        result = klab::Correlation(arma::Col<std::complex<klab::DoubleReal> >(), f1);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		 
		result = klab::Correlation(x, arma::Col<std::complex<klab::DoubleReal> >());
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		 
		result = klab::Correlation(arma::Col<std::complex<klab::DoubleReal> >(), arma::Col<std::complex<klab::DoubleReal> >());
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.0, 0.0), precision)) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testCorrelation_Matrix()
{
    try
    {
        klab::UInt32 m = 4;
		klab::UInt32 n = 8;
		klab::DoubleReal precision = 1e-12;
		 
		arma::Mat<klab::DoubleReal> x(m, n);
		arma::Mat<klab::DoubleReal> xo;
		arma::Mat<klab::DoubleReal> f1(2, 4);
		arma::Mat<klab::DoubleReal> f2(3, 5);
		 
		x( 0, 0) = 0.0;
		x( 0, 1) = 1.0;
		x( 0, 2) = 2.0;
		x( 0, 3) = 3.0;
		x( 0, 4) = 4.0;
		x( 0, 5) = 5.0;
		x( 0, 6) = 6.0;
		x( 0, 7) = 7.0;
		x( 1, 0) = 8.0;
		x( 1, 1) = 9.0;
		x( 1, 2) = 10.0;
		x( 1, 3) = 11.0;
		x( 1, 4) = 12.0;
		x( 1, 5) = 13.0;
		x( 1, 6) = 14.0;
		x( 1, 7) = 15.0;
		x( 2, 0) = 16.0;
		x( 2, 1) = 17.0;
		x( 2, 2) = 18.0;
		x( 2, 3) = 19.0;
		x( 2, 4) = 20.0;
		x( 2, 5) = 21.0;
		x( 2, 6) = 22.0;
		x( 2, 7) = 23.0;
		x( 3, 0) = 24.0;
		x( 3, 1) = 25.0;
		x( 3, 2) = 26.0;
		x( 3, 3) = 27.0;
		x( 3, 4) = 28.0;
		x( 3, 5) = 29.0;
		x( 3, 6) = 30.0;
		x( 3, 7) = 31.0;
		 
		f1( 0, 0) = 0.0;
		f1( 0, 1) = 1.0;
		f1( 0, 2) = 2.0;
		f1( 0, 3) = 3.0;
		f1( 1, 0) = 4.0;
		f1( 1, 1) = 5.0;
		f1( 1, 2) = 6.0;
		f1( 1, 3) = 7.0;
		 
		f2( 0, 0) = 32.0;
		f2( 0, 1) = 31.0;
		f2( 0, 2) = 30.0;
		f2( 0, 3) = 29.0;
		f2( 0, 4) = 28.0;
		f2( 1, 0) = 27.0;
		f2( 1, 1) = 26.0;
		f2( 1, 2) = 25.0;
		f2( 1, 3) = 24.0;
		f2( 1, 4) = 23.0;
		f2( 2, 0) = 22.0;
		f2( 2, 1) = 21.0;
		f2( 2, 2) = 20.0;
		f2( 2, 3) = 19.0;
		f2( 2, 4) = 18.0;


        klab::DoubleReal result = klab::Correlation(x, f1);
        TEST_ASSERT(klab::Equals(result, -0.3669898435089587, precision))   

        result = klab::Correlation(f1, x);
        TEST_ASSERT(klab::Equals(result, -0.3669898435089587, precision))  

        result = klab::Correlation(x, f2);
        TEST_ASSERT(klab::Equals(result, -0.6579619233956483, precision))  

        result = klab::Correlation(f2, x);
        TEST_ASSERT(klab::Equals(result, -0.6579619233956483, precision)) 

        result = klab::Correlation(f1, f2);
        TEST_ASSERT(klab::Equals(result, 0.2169289860210435, precision))  

        result = klab::Correlation(f2, f1);
        TEST_ASSERT(klab::Equals(result, 0.2169289860210435, precision))  

        result = klab::Correlation(x, x);
		TEST_ASSERT(klab::Equals(result, 1.0, precision))

        result = klab::Correlation(f1, f1);
		TEST_ASSERT(klab::Equals(result, 1.0, precision))

        result = klab::Correlation(f2, f2);
		TEST_ASSERT(klab::Equals(result, 1.0, precision))


        arma::Mat<klab::DoubleReal> u(m, n);
        arma::Mat<klab::DoubleReal> v(m, n);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                u(i, j) = 4.5;
                v(i, j) = 4.5;
            }
        }
        result = klab::Correlation(u, v);
		TEST_ASSERT(klab::Equals(result, 1.0, precision))

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
                v(i, j) = 5.0;
        }
        result = klab::Correlation(u, v);
		TEST_ASSERT(klab::Equals(result, 0.0, precision))


        // Limit cases.      
        result = klab::Correlation(arma::Mat<klab::DoubleReal>(), f1);
		TEST_ASSERT(klab::Equals(result, 0.0, precision))
		 
		result = klab::Correlation(x, arma::Mat<klab::DoubleReal>());
		TEST_ASSERT(klab::Equals(result, 0.0, precision))
		 
		result = klab::Correlation(arma::Mat<klab::DoubleReal>(), arma::Mat<klab::DoubleReal>());
		TEST_ASSERT(klab::Equals(result, 0.0, precision))   
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testCorrelation_Matrix_Complex()
{
    try
    {
        klab::UInt32 m = 4;
		klab::UInt32 n = 8;
		klab::DoubleReal precision = 1e-12;
		 
		arma::Mat<std::complex<klab::DoubleReal> > x(m, n);
		arma::Mat<std::complex<klab::DoubleReal> > xo;
		arma::Mat<std::complex<klab::DoubleReal> > f1(2, 4);
		arma::Mat<std::complex<klab::DoubleReal> > f2(3, 5);
		 
		x( 0, 0) = std::complex<klab::DoubleReal>(0.0, 32.0);
		x( 0, 1) = std::complex<klab::DoubleReal>(1.0, 31.0);
		x( 0, 2) = std::complex<klab::DoubleReal>(2.0, 30.0);
		x( 0, 3) = std::complex<klab::DoubleReal>(3.0, 29.0);
		x( 0, 4) = std::complex<klab::DoubleReal>(4.0, 28.0);
		x( 0, 5) = std::complex<klab::DoubleReal>(5.0, 27.0);
		x( 0, 6) = std::complex<klab::DoubleReal>(6.0, 26.0);
		x( 0, 7) = std::complex<klab::DoubleReal>(7.0, 25.0);
		x( 1, 0) = std::complex<klab::DoubleReal>(8.0, 24.0);
		x( 1, 1) = std::complex<klab::DoubleReal>(9.0, 23.0);
		x( 1, 2) = std::complex<klab::DoubleReal>(10.0, 22.0);
		x( 1, 3) = std::complex<klab::DoubleReal>(11.0, 21.0);
		x( 1, 4) = std::complex<klab::DoubleReal>(12.0, 20.0);
		x( 1, 5) = std::complex<klab::DoubleReal>(13.0, 19.0);
		x( 1, 6) = std::complex<klab::DoubleReal>(14.0, 18.0);
		x( 1, 7) = std::complex<klab::DoubleReal>(15.0, 17.0);
		x( 2, 0) = std::complex<klab::DoubleReal>(16.0, 16.0);
		x( 2, 1) = std::complex<klab::DoubleReal>(17.0, 15.0);
		x( 2, 2) = std::complex<klab::DoubleReal>(18.0, 14.0);
		x( 2, 3) = std::complex<klab::DoubleReal>(19.0, 13.0);
		x( 2, 4) = std::complex<klab::DoubleReal>(20.0, 12.0);
		x( 2, 5) = std::complex<klab::DoubleReal>(21.0, 11.0);
		x( 2, 6) = std::complex<klab::DoubleReal>(22.0, 10.0);
		x( 2, 7) = std::complex<klab::DoubleReal>(23.0, 9.0);
		x( 3, 0) = std::complex<klab::DoubleReal>(24.0, 8.0);
		x( 3, 1) = std::complex<klab::DoubleReal>(25.0, 7.0);
		x( 3, 2) = std::complex<klab::DoubleReal>(26.0, 6.0);
		x( 3, 3) = std::complex<klab::DoubleReal>(27.0, 5.0);
		x( 3, 4) = std::complex<klab::DoubleReal>(28.0, 4.0);
		x( 3, 5) = std::complex<klab::DoubleReal>(29.0, 3.0);
		x( 3, 6) = std::complex<klab::DoubleReal>(30.0, 2.0);
		x( 3, 7) = std::complex<klab::DoubleReal>(31.0, 1.0);
		 
		f1( 0, 0) = std::complex<klab::DoubleReal>(0.0, 32.0);
		f1( 0, 1) = std::complex<klab::DoubleReal>(1.0, 31.0);
		f1( 0, 2) = std::complex<klab::DoubleReal>(2.0, 30.0);
		f1( 0, 3) = std::complex<klab::DoubleReal>(3.0, 29.0);
		f1( 1, 0) = std::complex<klab::DoubleReal>(4.0, 28.0);
		f1( 1, 1) = std::complex<klab::DoubleReal>(5.0, 27.0);
		f1( 1, 2) = std::complex<klab::DoubleReal>(6.0, 26.0);
		f1( 1, 3) = std::complex<klab::DoubleReal>(7.0, 25.0);
		 
		f2( 0, 0) = std::complex<klab::DoubleReal>(32.0, 0.0);
		f2( 0, 1) = std::complex<klab::DoubleReal>(31.0, 1.0);
		f2( 0, 2) = std::complex<klab::DoubleReal>(30.0, 2.0);
		f2( 0, 3) = std::complex<klab::DoubleReal>(29.0, 3.0);
		f2( 0, 4) = std::complex<klab::DoubleReal>(28.0, 4.0);
		f2( 1, 0) = std::complex<klab::DoubleReal>(27.0, 5.0);
		f2( 1, 1) = std::complex<klab::DoubleReal>(26.0, 6.0);
		f2( 1, 2) = std::complex<klab::DoubleReal>(25.0, 7.0);
		f2( 1, 3) = std::complex<klab::DoubleReal>(24.0, 8.0);
		f2( 1, 4) = std::complex<klab::DoubleReal>(23.0, 9.0);
		f2( 2, 0) = std::complex<klab::DoubleReal>(22.0, 10.0);
		f2( 2, 1) = std::complex<klab::DoubleReal>(21.0, 11.0);
		f2( 2, 2) = std::complex<klab::DoubleReal>(20.0, 12.0);
		f2( 2, 3) = std::complex<klab::DoubleReal>(19.0, 13.0);
		f2( 2, 4) = std::complex<klab::DoubleReal>(18.0, 14.0);


        std::complex<klab::DoubleReal> result = klab::Correlation(x, f1);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.40998685967172, -0.488624935176724), precision))   

        result = klab::Correlation(f1, x);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.40998685967172, 0.488624935176724), precision))  

        result = klab::Correlation(x, f2);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(-0.41223417472524104, -0.46409305811285140), precision))  

        result = klab::Correlation(f2, x);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(-0.41223417472524104, 0.46409305811285140), precision)) 

        result = klab::Correlation(f1, f2);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(-0.5260341475980407, -0.5771346076504217), precision))  

        result = klab::Correlation(f2, f1);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(-0.5260341475980407, 0.5771346076504217), precision))  

        result = klab::Correlation(x, x);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(1.0, 0.0), precision))

        result = klab::Correlation(f1, f1);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(1.0, 0.0), precision))

        result = klab::Correlation(f2, f2);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(1.0, 0.0), precision))


        arma::Mat<std::complex<klab::DoubleReal> > u(m, n);
        arma::Mat<std::complex<klab::DoubleReal> > v(m, n);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                u(i, j) = std::complex<klab::DoubleReal>(4.5, -3.2);
                v(i, j) = std::complex<klab::DoubleReal>(4.5, -3.2);
            }
        }
        result = klab::Correlation(u, v);
        TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(1.0, 0.0), precision))

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
                v(i, j) = std::complex<klab::DoubleReal>(5.0, -4.0);
        }
        result = klab::Correlation(u, v);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.0, 0.0), precision))


        // Limit cases.      
        result = klab::Correlation(arma::Mat<std::complex<klab::DoubleReal> >(), f1);
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		 
		result = klab::Correlation(x, arma::Mat<std::complex<klab::DoubleReal> >());
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.0, 0.0), precision))
		 
		result = klab::Correlation(arma::Mat<std::complex<klab::DoubleReal> >(), arma::Mat<std::complex<klab::DoubleReal> >());
		TEST_ASSERT(klab::Equals(result, std::complex<klab::DoubleReal>(0.0, 0.0), precision)) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testDownsample_Vector()
{
    try
    {
        klab::UInt32 n = 8;

        arma::Col<klab::DoubleReal> x(n);        
        arma::Col<klab::DoubleReal> xo;

        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = klab::DoubleReal(i+1);

        klab::Downsample(x, 1, xo);
        TEST_ASSERT(xo.n_rows == 8)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))
        TEST_ASSERT(klab::Equals(xo[1], x[1]))
        TEST_ASSERT(klab::Equals(xo[2], x[2]))
        TEST_ASSERT(klab::Equals(xo[3], x[3]))
        TEST_ASSERT(klab::Equals(xo[4], x[4]))
        TEST_ASSERT(klab::Equals(xo[5], x[5]))
        TEST_ASSERT(klab::Equals(xo[6], x[6]))
        TEST_ASSERT(klab::Equals(xo[7], x[7]))

        klab::Downsample(x, 2, xo);
        TEST_ASSERT(xo.n_rows == 4)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))
        TEST_ASSERT(klab::Equals(xo[1], x[2]))
        TEST_ASSERT(klab::Equals(xo[2], x[4]))
        TEST_ASSERT(klab::Equals(xo[3], x[6]))

        klab::Downsample(x, 3, xo);
        TEST_ASSERT(xo.n_rows == 3)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))
        TEST_ASSERT(klab::Equals(xo[1], x[3]))
        TEST_ASSERT(klab::Equals(xo[2], x[6]))

        klab::Downsample(x, 4, xo);
        TEST_ASSERT(xo.n_rows == 2)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))
        TEST_ASSERT(klab::Equals(xo[1], x[4]))

        klab::Downsample(x, 5, xo);
        TEST_ASSERT(xo.n_rows == 2)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))
        TEST_ASSERT(klab::Equals(xo[1], x[5]))

        klab::Downsample(x, 6, xo);
        TEST_ASSERT(xo.n_rows == 2)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))
        TEST_ASSERT(klab::Equals(xo[1], x[6]))

        klab::Downsample(x, 7, xo);
        TEST_ASSERT(xo.n_rows == 2)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))
        TEST_ASSERT(klab::Equals(xo[1], x[7]))

        klab::Downsample(x, 8, xo);
        TEST_ASSERT(xo.n_rows == 1)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))

        klab::Downsample(x, 16, xo);
        TEST_ASSERT(xo.n_rows == 1)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))


        // Limit cases.
        try                             {klab::Downsample(x, 0, xo); TEST_ASSERT(false)}
        catch(KBadArithmeticException&) {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        klab::Downsample(arma::Col<klab::DoubleReal>(), 1, xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::Downsample(arma::Col<klab::DoubleReal>(), 2, xo);
        TEST_ASSERT(xo.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testDownsample_Matrix()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        arma::Mat<klab::DoubleReal> x(m, n); 
        arma::Mat<klab::DoubleReal> xo;

        x( 0, 0) = 0.0;
        x( 0, 1) = 1.0;
        x( 0, 2) = 2.0;
        x( 0, 3) = 3.0;
        x( 0, 4) = 4.0;
        x( 0, 5) = 5.0;
        x( 0, 6) = 6.0;
        x( 0, 7) = 7.0;
        x( 1, 0) = 8.0;
        x( 1, 1) = 9.0;
        x( 1, 2) = 10.0;
        x( 1, 3) = 11.0;
        x( 1, 4) = 12.0;
        x( 1, 5) = 13.0;
        x( 1, 6) = 14.0;
        x( 1, 7) = 15.0;
        x( 2, 0) = 16.0;
        x( 2, 1) = 17.0;
        x( 2, 2) = 18.0;
        x( 2, 3) = 19.0;
        x( 2, 4) = 20.0;
        x( 2, 5) = 21.0;
        x( 2, 6) = 22.0;
        x( 2, 7) = 23.0;
        x( 3, 0) = 24.0;
        x( 3, 1) = 25.0;
        x( 3, 2) = 26.0;
        x( 3, 3) = 27.0;
        x( 3, 4) = 28.0;
        x( 3, 5) = 29.0;
        x( 3, 6) = 30.0;
        x( 3, 7) = 31.0;

        
        klab::Downsample(x, 1, xo);
        TEST_ASSERT(xo.n_rows==4 && xo.n_cols==8)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))
		TEST_ASSERT(klab::Equals(xo(0, 1), x(0, 1)))
		TEST_ASSERT(klab::Equals(xo(0, 2), x(0, 2)))
		TEST_ASSERT(klab::Equals(xo(0, 3), x(0, 3)))
		TEST_ASSERT(klab::Equals(xo(0, 4), x(0, 4)))
		TEST_ASSERT(klab::Equals(xo(0, 5), x(0, 5)))
		TEST_ASSERT(klab::Equals(xo(0, 6), x(0, 6)))
		TEST_ASSERT(klab::Equals(xo(0, 7), x(0, 7)))
		TEST_ASSERT(klab::Equals(xo(1, 0), x(1, 0)))
		TEST_ASSERT(klab::Equals(xo(1, 1), x(1, 1)))
		TEST_ASSERT(klab::Equals(xo(1, 2), x(1, 2)))
		TEST_ASSERT(klab::Equals(xo(1, 3), x(1, 3)))
		TEST_ASSERT(klab::Equals(xo(1, 4), x(1, 4)))
		TEST_ASSERT(klab::Equals(xo(1, 5), x(1, 5)))
		TEST_ASSERT(klab::Equals(xo(1, 6), x(1, 6)))
		TEST_ASSERT(klab::Equals(xo(1, 7), x(1, 7)))
		TEST_ASSERT(klab::Equals(xo(2, 0), x(2, 0)))
		TEST_ASSERT(klab::Equals(xo(2, 1), x(2, 1)))
		TEST_ASSERT(klab::Equals(xo(2, 2), x(2, 2)))
		TEST_ASSERT(klab::Equals(xo(2, 3), x(2, 3)))
		TEST_ASSERT(klab::Equals(xo(2, 4), x(2, 4)))
		TEST_ASSERT(klab::Equals(xo(2, 5), x(2, 5)))
		TEST_ASSERT(klab::Equals(xo(2, 6), x(2, 6)))
		TEST_ASSERT(klab::Equals(xo(2, 7), x(2, 7)))
		TEST_ASSERT(klab::Equals(xo(3, 0), x(3, 0)))
		TEST_ASSERT(klab::Equals(xo(3, 1), x(3, 1)))
		TEST_ASSERT(klab::Equals(xo(3, 2), x(3, 2)))
		TEST_ASSERT(klab::Equals(xo(3, 3), x(3, 3)))
		TEST_ASSERT(klab::Equals(xo(3, 4), x(3, 4)))
		TEST_ASSERT(klab::Equals(xo(3, 5), x(3, 5)))
		TEST_ASSERT(klab::Equals(xo(3, 6), x(3, 6)))
		TEST_ASSERT(klab::Equals(xo(3, 7), x(3, 7)))

        klab::Downsample(x, 2, xo);
        TEST_ASSERT(xo.n_rows==2 && xo.n_cols==4)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))
		TEST_ASSERT(klab::Equals(xo(0, 1), x(0, 2)))
		TEST_ASSERT(klab::Equals(xo(0, 2), x(0, 4)))
		TEST_ASSERT(klab::Equals(xo(0, 3), x(0, 6)))
		TEST_ASSERT(klab::Equals(xo(1, 0), x(2, 0)))
		TEST_ASSERT(klab::Equals(xo(1, 1), x(2, 2)))
		TEST_ASSERT(klab::Equals(xo(1, 2), x(2, 4)))
		TEST_ASSERT(klab::Equals(xo(1, 3), x(2, 6)))

        klab::Downsample(x, 3, xo);
        TEST_ASSERT(xo.n_rows==2 && xo.n_cols==3)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))
		TEST_ASSERT(klab::Equals(xo(0, 1), x(0, 3)))
		TEST_ASSERT(klab::Equals(xo(0, 2), x(0, 6)))
		TEST_ASSERT(klab::Equals(xo(1, 0), x(3, 0)))
		TEST_ASSERT(klab::Equals(xo(1, 1), x(3, 3)))
		TEST_ASSERT(klab::Equals(xo(1, 2), x(3, 6)))

        klab::Downsample(x, 4, xo);
        TEST_ASSERT(xo.n_rows==1 && xo.n_cols==2)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))
		TEST_ASSERT(klab::Equals(xo(0, 1), x(0, 4)))

        klab::Downsample(x, 5, xo);
        TEST_ASSERT(xo.n_rows==1 && xo.n_cols==2)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))
		TEST_ASSERT(klab::Equals(xo(0, 1), x(0, 5)))

        klab::Downsample(x, 6, xo);
        TEST_ASSERT(xo.n_rows==1 && xo.n_cols==2)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))
		TEST_ASSERT(klab::Equals(xo(0, 1), x(0, 6)))

        klab::Downsample(x, 7, xo);
        TEST_ASSERT(xo.n_rows==1 && xo.n_cols==2)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))
		TEST_ASSERT(klab::Equals(xo(0, 1), x(0, 7)))

        klab::Downsample(x, 8, xo);
        TEST_ASSERT(xo.n_rows==1 && xo.n_cols==1)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))

        klab::Downsample(x, 16, xo);
        TEST_ASSERT(xo.n_rows==1 && xo.n_cols==1)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))


        // Limit cases.
        try                             {klab::Downsample(x, 0, xo); TEST_ASSERT(false)}
        catch(KBadArithmeticException&) {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        klab::Downsample(arma::Mat<klab::DoubleReal>(), 1, xo);
        TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)

        klab::Downsample(arma::Mat<klab::DoubleReal>(), 2, xo);
        TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testUpsample_Vector()
{
    try
    {
        klab::UInt32 n = 8;

        arma::Col<klab::DoubleReal> x(n);        
        arma::Col<klab::DoubleReal> xo;

        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = klab::DoubleReal(i+1);

        klab::Upsample(x, 1, xo);
        TEST_ASSERT(xo.n_rows == 8)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))
        TEST_ASSERT(klab::Equals(xo[1], x[1]))
        TEST_ASSERT(klab::Equals(xo[2], x[2]))
        TEST_ASSERT(klab::Equals(xo[3], x[3]))
        TEST_ASSERT(klab::Equals(xo[4], x[4]))
        TEST_ASSERT(klab::Equals(xo[5], x[5]))
        TEST_ASSERT(klab::Equals(xo[6], x[6]))
        TEST_ASSERT(klab::Equals(xo[7], x[7]))

        klab::Upsample(x, 2, xo);
        TEST_ASSERT(xo.n_rows == 16)
        TEST_ASSERT(klab::Equals(xo[0], x[0]))
        TEST_ASSERT(klab::Equals(xo[1], 0.0))
        TEST_ASSERT(klab::Equals(xo[2], x[1]))
        TEST_ASSERT(klab::Equals(xo[3], 0.0))
        TEST_ASSERT(klab::Equals(xo[4], x[2]))
        TEST_ASSERT(klab::Equals(xo[5], 0.0))
        TEST_ASSERT(klab::Equals(xo[6], x[3]))
        TEST_ASSERT(klab::Equals(xo[7], 0.0))  
        TEST_ASSERT(klab::Equals(xo[8], x[4]))
        TEST_ASSERT(klab::Equals(xo[9], 0.0))
        TEST_ASSERT(klab::Equals(xo[10], x[5]))
        TEST_ASSERT(klab::Equals(xo[11], 0.0))
        TEST_ASSERT(klab::Equals(xo[12], x[6]))
        TEST_ASSERT(klab::Equals(xo[13], 0.0))
        TEST_ASSERT(klab::Equals(xo[14], x[7]))
        TEST_ASSERT(klab::Equals(xo[15], 0.0))   


        // Limit cases.
        try                             {klab::Upsample(x, 0, xo); TEST_ASSERT(false)}
        catch(KBadArithmeticException&) {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        klab::Upsample(arma::Col<klab::DoubleReal>(), 1, xo);
        TEST_ASSERT(xo.n_rows == 0)

        klab::Upsample(arma::Col<klab::DoubleReal>(), 2, xo);
        TEST_ASSERT(xo.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUtilUnitTest::testUpsample_Matrix()
{
    try
    {
       klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        arma::Mat<klab::DoubleReal> x(m, n); 
        arma::Mat<klab::DoubleReal> xo;

        x( 0, 0) = 0.0;
        x( 0, 1) = 1.0;
        x( 0, 2) = 2.0;
        x( 0, 3) = 3.0;
        x( 0, 4) = 4.0;
        x( 0, 5) = 5.0;
        x( 0, 6) = 6.0;
        x( 0, 7) = 7.0;
        x( 1, 0) = 8.0;
        x( 1, 1) = 9.0;
        x( 1, 2) = 10.0;
        x( 1, 3) = 11.0;
        x( 1, 4) = 12.0;
        x( 1, 5) = 13.0;
        x( 1, 6) = 14.0;
        x( 1, 7) = 15.0;
        x( 2, 0) = 16.0;
        x( 2, 1) = 17.0;
        x( 2, 2) = 18.0;
        x( 2, 3) = 19.0;
        x( 2, 4) = 20.0;
        x( 2, 5) = 21.0;
        x( 2, 6) = 22.0;
        x( 2, 7) = 23.0;
        x( 3, 0) = 24.0;
        x( 3, 1) = 25.0;
        x( 3, 2) = 26.0;
        x( 3, 3) = 27.0;
        x( 3, 4) = 28.0;
        x( 3, 5) = 29.0;
        x( 3, 6) = 30.0;
        x( 3, 7) = 31.0;


        klab::Upsample(x, 1, xo);
        TEST_ASSERT(xo.n_rows==4 && xo.n_cols==8)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))
		TEST_ASSERT(klab::Equals(xo(0, 1), x(0, 1)))
		TEST_ASSERT(klab::Equals(xo(0, 2), x(0, 2)))
		TEST_ASSERT(klab::Equals(xo(0, 3), x(0, 3)))
		TEST_ASSERT(klab::Equals(xo(0, 4), x(0, 4)))
		TEST_ASSERT(klab::Equals(xo(0, 5), x(0, 5)))
		TEST_ASSERT(klab::Equals(xo(0, 6), x(0, 6)))
		TEST_ASSERT(klab::Equals(xo(0, 7), x(0, 7)))
		TEST_ASSERT(klab::Equals(xo(1, 0), x(1, 0)))
		TEST_ASSERT(klab::Equals(xo(1, 1), x(1, 1)))
		TEST_ASSERT(klab::Equals(xo(1, 2), x(1, 2)))
		TEST_ASSERT(klab::Equals(xo(1, 3), x(1, 3)))
		TEST_ASSERT(klab::Equals(xo(1, 4), x(1, 4)))
		TEST_ASSERT(klab::Equals(xo(1, 5), x(1, 5)))
		TEST_ASSERT(klab::Equals(xo(1, 6), x(1, 6)))
		TEST_ASSERT(klab::Equals(xo(1, 7), x(1, 7)))
		TEST_ASSERT(klab::Equals(xo(2, 0), x(2, 0)))
		TEST_ASSERT(klab::Equals(xo(2, 1), x(2, 1)))
		TEST_ASSERT(klab::Equals(xo(2, 2), x(2, 2)))
		TEST_ASSERT(klab::Equals(xo(2, 3), x(2, 3)))
		TEST_ASSERT(klab::Equals(xo(2, 4), x(2, 4)))
		TEST_ASSERT(klab::Equals(xo(2, 5), x(2, 5)))
		TEST_ASSERT(klab::Equals(xo(2, 6), x(2, 6)))
		TEST_ASSERT(klab::Equals(xo(2, 7), x(2, 7)))
		TEST_ASSERT(klab::Equals(xo(3, 0), x(3, 0)))
		TEST_ASSERT(klab::Equals(xo(3, 1), x(3, 1)))
		TEST_ASSERT(klab::Equals(xo(3, 2), x(3, 2)))
		TEST_ASSERT(klab::Equals(xo(3, 3), x(3, 3)))
		TEST_ASSERT(klab::Equals(xo(3, 4), x(3, 4)))
		TEST_ASSERT(klab::Equals(xo(3, 5), x(3, 5)))
		TEST_ASSERT(klab::Equals(xo(3, 6), x(3, 6)))
		TEST_ASSERT(klab::Equals(xo(3, 7), x(3, 7)))

        klab::Upsample(x, 2, xo);
        TEST_ASSERT(xo.n_rows==8 && xo.n_cols==16)
        TEST_ASSERT(klab::Equals(xo(0, 0), x(0, 0)))
		TEST_ASSERT(klab::Equals(xo(0, 1), 0.0))
		TEST_ASSERT(klab::Equals(xo(0, 2), x(0, 1)))
		TEST_ASSERT(klab::Equals(xo(0, 3), 0.0))
		TEST_ASSERT(klab::Equals(xo(0, 4), x(0, 2)))
		TEST_ASSERT(klab::Equals(xo(0, 5), 0.0))
		TEST_ASSERT(klab::Equals(xo(0, 6), x(0, 3)))
		TEST_ASSERT(klab::Equals(xo(0, 7), 0.0))
		TEST_ASSERT(klab::Equals(xo(0, 8), x(0, 4)))
		TEST_ASSERT(klab::Equals(xo(0, 9), 0.0))
		TEST_ASSERT(klab::Equals(xo(0, 10), x(0, 5)))
		TEST_ASSERT(klab::Equals(xo(0, 11), 0.0))
		TEST_ASSERT(klab::Equals(xo(0, 12), x(0, 6)))
		TEST_ASSERT(klab::Equals(xo(0, 13), 0.0))
		TEST_ASSERT(klab::Equals(xo(0, 14), x(0, 7)))
		TEST_ASSERT(klab::Equals(xo(0, 15), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 0), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 1), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 2), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 3), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 4), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 5), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 6), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 7), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 8), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 9), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 10), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 11), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 12), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 13), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 14), 0.0))
		TEST_ASSERT(klab::Equals(xo(1, 15), 0.0))
		TEST_ASSERT(klab::Equals(xo(2, 0), x(1, 0)))
		TEST_ASSERT(klab::Equals(xo(2, 1), 0.0))
		TEST_ASSERT(klab::Equals(xo(2, 2), x(1, 1)))
		TEST_ASSERT(klab::Equals(xo(2, 3), 0.0))
		TEST_ASSERT(klab::Equals(xo(2, 4), x(1, 2)))
		TEST_ASSERT(klab::Equals(xo(2, 5), 0.0))
		TEST_ASSERT(klab::Equals(xo(2, 6), x(1, 3)))
		TEST_ASSERT(klab::Equals(xo(2, 7), 0.0))
		TEST_ASSERT(klab::Equals(xo(2, 8), x(1, 4)))
		TEST_ASSERT(klab::Equals(xo(2, 9), 0.0))
		TEST_ASSERT(klab::Equals(xo(2, 10), x(1, 5)))
		TEST_ASSERT(klab::Equals(xo(2, 11), 0.0))
		TEST_ASSERT(klab::Equals(xo(2, 12), x(1, 6)))
		TEST_ASSERT(klab::Equals(xo(2, 13), 0.0))
		TEST_ASSERT(klab::Equals(xo(2, 14), x(1, 7)))
		TEST_ASSERT(klab::Equals(xo(2, 15), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 0), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 1), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 2), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 3), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 4), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 5), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 6), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 7), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 8), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 9), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 10), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 11), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 12), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 13), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 14), 0.0))
		TEST_ASSERT(klab::Equals(xo(3, 15), 0.0))
		TEST_ASSERT(klab::Equals(xo(4, 0), x(2, 0)))
		TEST_ASSERT(klab::Equals(xo(4, 1), 0.0))
		TEST_ASSERT(klab::Equals(xo(4, 2), x(2, 1)))
		TEST_ASSERT(klab::Equals(xo(4, 3), 0.0))
		TEST_ASSERT(klab::Equals(xo(4, 4), x(2, 2)))
		TEST_ASSERT(klab::Equals(xo(4, 5), 0.0))
		TEST_ASSERT(klab::Equals(xo(4, 6), x(2, 3)))
		TEST_ASSERT(klab::Equals(xo(4, 7), 0.0))
		TEST_ASSERT(klab::Equals(xo(4, 8), x(2, 4)))
		TEST_ASSERT(klab::Equals(xo(4, 9), 0.0))
		TEST_ASSERT(klab::Equals(xo(4, 10), x(2, 5)))
		TEST_ASSERT(klab::Equals(xo(4, 11), 0.0))
		TEST_ASSERT(klab::Equals(xo(4, 12), x(2, 6)))
		TEST_ASSERT(klab::Equals(xo(4, 13), 0.0))
		TEST_ASSERT(klab::Equals(xo(4, 14), x(2, 7)))
		TEST_ASSERT(klab::Equals(xo(4, 15), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 0), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 1), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 2), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 3), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 4), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 5), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 6), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 7), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 8), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 9), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 10), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 11), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 12), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 13), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 14), 0.0))
		TEST_ASSERT(klab::Equals(xo(5, 15), 0.0))
		TEST_ASSERT(klab::Equals(xo(6, 0), x(3, 0)))
		TEST_ASSERT(klab::Equals(xo(6, 1), 0.0))
		TEST_ASSERT(klab::Equals(xo(6, 2), x(3, 1)))
		TEST_ASSERT(klab::Equals(xo(6, 3), 0.0))
		TEST_ASSERT(klab::Equals(xo(6, 4), x(3, 2)))
		TEST_ASSERT(klab::Equals(xo(6, 5), 0.0))
		TEST_ASSERT(klab::Equals(xo(6, 6), x(3, 3)))
		TEST_ASSERT(klab::Equals(xo(6, 7), 0.0))
		TEST_ASSERT(klab::Equals(xo(6, 8), x(3, 4)))
		TEST_ASSERT(klab::Equals(xo(6, 9), 0.0))
		TEST_ASSERT(klab::Equals(xo(6, 10), x(3, 5)))
		TEST_ASSERT(klab::Equals(xo(6, 11), 0.0))
		TEST_ASSERT(klab::Equals(xo(6, 12), x(3, 6)))
		TEST_ASSERT(klab::Equals(xo(6, 13), 0.0))
		TEST_ASSERT(klab::Equals(xo(6, 14), x(3, 7)))
		TEST_ASSERT(klab::Equals(xo(6, 15), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 0), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 1), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 2), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 3), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 4), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 5), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 6), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 7), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 8), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 9), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 10), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 11), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 12), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 13), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 14), 0.0))
		TEST_ASSERT(klab::Equals(xo(7, 15), 0.0)) 


        // Limit cases.
        try                             {klab::Upsample(x, 0, xo); TEST_ASSERT(false)}
        catch(KBadArithmeticException&) {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        klab::Upsample(arma::Mat<klab::DoubleReal>(), 1, xo);
        TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)

        klab::Upsample(arma::Mat<klab::DoubleReal>(), 2, xo);
        TEST_ASSERT(xo.n_rows==0 && xo.n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
