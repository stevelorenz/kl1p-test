// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KL1p C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#include "Wavelet2DOperatorUnitTest.h"
#include "../include/Wavelet2DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KWavelet2DOperatorUnitTest::KWavelet2DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KWavelet2DOperatorUnitTest::testHeightWidthConstructor)  
    TEST_ADD(KWavelet2DOperatorUnitTest::testHeightWidthFilterConstructor)  
    TEST_ADD(KWavelet2DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KWavelet2DOperatorUnitTest::testWidth)
    TEST_ADD(KWavelet2DOperatorUnitTest::testHeight)
    TEST_ADD(KWavelet2DOperatorUnitTest::testFilter)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Haar)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Daubechies2)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Daubechies4)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Daubechies6)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Daubechies8)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Daubechies10)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Daubechies9_7)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Delegate)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Name)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApply_Custom)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Haar)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies2)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies4)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies6)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies8)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies10)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies9_7)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Delegate)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Name)
    TEST_ADD(KWavelet2DOperatorUnitTest::testApplyAdjoint_Custom)
}

// ---------------------------------------------------------------------------------------------------- //

KWavelet2DOperatorUnitTest::~KWavelet2DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testHeightWidthConstructor()
{
    try
    {
        TWavelet2DOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.filter().waveLength()==0 && op.height()==4 && op.width()==8)

        TWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(4, 8);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.filter().waveLength()==2 && op2.height()==4 && op2.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testHeightWidthFilterConstructor()
{
    try
    {
        THaarWaveletFilter<klab::DoubleReal> filter;

        TWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(4, 8, filter);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.filter().waveLength()==2 && op.height()==4 && op.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        THaarWaveletFilter<klab::DoubleReal> filter;

        TWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(4, 8, filter);
        TWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(op);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.filter().waveLength()==2 && op2.height()==4 && op2.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testWidth()
{
    try
    {
        TWavelet2DOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.height()==4 && op.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testHeight()
{
    try
    {
        TWavelet2DOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.height()==4 && op.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testFilter()
{
    try
    {
        TWavelet2DOperator<klab::DoubleReal> op(0, 0);
        TEST_ASSERT(op.filter().waveLength() == 0)

        TWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(0, 0);
        TEST_ASSERT(op2.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 994.00000000000034, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -107.49999999999991, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -10.999999999999968, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 67.000000000000043, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 28.999999999999993, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -28.5, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 15.000000000000002, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 51.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 51.000000000000114, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 60.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -10.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 11.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 6.4999999999999938, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -45.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 26.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -25.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -18.499999999999989, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 0.49999999999998579, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -23.000000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 54.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -47.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 19.000000000000028, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 0.50000000000005684, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 2.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -68.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 47.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -6.499999999999992, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 20.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -9.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -24.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 23.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 10.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 18.5, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -31.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 18.500000000000004, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -1.9999999999999858, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 40.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 36.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -1.5, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -0.99999999999999734, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -15.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -26.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 14.499999999999998, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 7.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 5.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 11.5, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -21.499999999999972, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -1.4999999999999911, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -22.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 1.5000000000000071, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 3.4999999999999964, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 2.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -8.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -17.500000000000028, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 30.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -8.0000000000000036, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 22.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 19.499999999999996, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -11.499999999999993, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Haar()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 994.00000000000034, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -107.49999999999991, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -10.999999999999968, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 67.000000000000043, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 28.999999999999993, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -28.5, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 15.000000000000002, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 51.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 51.000000000000114, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 60.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -10.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 11.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 6.4999999999999938, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -45.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 26.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -25.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -18.499999999999989, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 0.49999999999998579, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -23.000000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 54.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -47.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 19.000000000000028, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 0.50000000000005684, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 2.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -68.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 47.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -6.499999999999992, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 20.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -9.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -24.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 23.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 10.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 18.5, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -31.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 18.500000000000004, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -1.9999999999999858, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 40.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 36.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -1.5, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -0.99999999999999734, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -15.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -26.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 14.499999999999998, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 7.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 5.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 11.5, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -21.499999999999972, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -1.4999999999999911, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -22.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 1.5000000000000071, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 3.4999999999999964, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 2.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -8.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -17.500000000000028, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 30.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -8.0000000000000036, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 22.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 19.499999999999996, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -11.499999999999993, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Daubechies2()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 994.00000000000034, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -107.49999999999991, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -10.999999999999968, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 67.000000000000043, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 28.999999999999993, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -28.5, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 15.000000000000002, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 51.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 51.000000000000114, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 60.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -10.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 11.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 6.4999999999999938, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -45.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 26.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -25.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -18.499999999999989, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 0.49999999999998579, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -23.000000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 54.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -47.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 19.000000000000028, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 0.50000000000005684, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 2.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -68.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 47.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -6.499999999999992, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 20.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -9.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -24.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 23.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 10.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 18.5, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -31.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 18.500000000000004, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -1.9999999999999858, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 40.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 36.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -1.5, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -0.99999999999999734, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -15.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -26.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 14.499999999999998, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 7.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 5.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 11.5, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -21.499999999999972, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -1.4999999999999911, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -22.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 1.5000000000000071, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 3.4999999999999964, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 2.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -8.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -17.500000000000028, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 30.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -8.0000000000000036, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 22.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 19.499999999999996, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -11.499999999999993, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Daubechies4()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999898, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -74.350544142276078, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), 29.783277833725016, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -29.843341500359539, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -19.838457268119896, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 18.637259526419165, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 19.963457268119896, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 31.744782028742804, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 40.141896345772807, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 47.195712325508936, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 47.340968362108292, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -45.163935902179823, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -1.6862976320958274, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 43.074673200287627, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -57.532354476264032, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 4.4902947306350303, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), -34.910254037844368, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 26.283257801676513, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -94.408144111257712, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -0.087078014682679949, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), -18.581243060694845, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 64.044786654946279, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -17.370190528383297, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -15.261937352910234, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 77.116057001341574, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), -32.235539987592716, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 24.383507134730753, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -19.753021718539038, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), -19.975072447521203, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 14.224514426634894, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), 12.186855652982141, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 38.878929277221452, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -0.98686027918559205, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 21.135970832383421, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 40.455127018922155, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 7.2066515603352741, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 2.7320508075688834, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), -22.254400971976246, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -18.533493649053899, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), -7.4967150697963971, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -5.5786024775091363, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 5.3128221735089198, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -8.3519191624432096, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -4.5346960169580655, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -28.582767602107936, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), 6.7379763209582144, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 4.9270008623713331, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 1.4064110867544617, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 1.6806079660838904, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -15.426356515353461, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 2.8653810567665801, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 7.3624183000719086, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 17.803203230275507, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 7.5642603887904984, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 8.3540017247426697, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), -2.4679445662276649, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 26.853765877365262, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 5.1623366001437745, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -12.043906460550971, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 13.887259526419172, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 13.029564371832437, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), -30.776837462515154, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 32.416265877365284, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), 7.141424651018017, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Daubechies6()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999955, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -12.038446380914504, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -63.825617471159084, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -7.6373779449229664, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 9.1727572909519068, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -6.830905229142056, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 39.398751215856677, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), -6.7453905368492757, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 13.123486950183775, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), -23.647189163352738, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -72.114210182915016, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), 76.102411172466716, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 53.052778535868526, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), -53.560809485706415, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -5.7571658251691291, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -7.8648593201415427, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 91.318078018120559, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -21.847304971401698, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 16.551304181783689, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -7.8468077363814395, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 66.233098586605863, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -1.4679230052067485, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -40.867907316305875, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -1.9241806592945694, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -57.383807227577734, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 30.122785584720603, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), -28.516469678998408, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -36.06588681482598, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 16.910446945505356, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 1.6953332782543911, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), 45.831969269487644, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), -10.275993744714677, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -15.727126406538261, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 13.983625236864924, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -6.4714324199154234, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), -0.26621786266790082, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -4.114451151262692, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 19.227653484194139, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), 2.0333566779807608, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), -27.195009599074087, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 2.9742926031028958, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -13.206404217823682, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 19.601973096902881, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -12.273655416162413, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), 7.668702098431222, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -1.8775837908399255, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 10.732363117734369, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 12.539045876263149, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 39.094788134247842, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 3.6116718403186212, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), -12.46169902750367, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 17.981960178574859, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -23.390726037772836, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 36.083899559138267, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), -1.6267759817922123, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 10.936296660853861, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 0.99254050372658753, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -0.40219521703681238, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 33.189783898376938, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 14.378095075532713, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -16.157040273330662, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), -31.465588264444058, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), -10.174725096369036, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), 8.7805827202897007, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Daubechies8()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999977, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 52.445892062981528, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -2.477926877349037, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -107.65574447980721, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -22.090439023383595, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 40.949051155442682, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 1.1759766585946994, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 4.1399654188672885, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), -18.462826354812336, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), -63.148217805973303, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.088405370171337, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -42.100265738661967, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -32.019725870534323, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), -25.196457861209328, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -4.8852935990889916, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 45.891849207788724, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), -27.035733039249564, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -3.4169542491646467, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 26.139388551861003, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -33.616084640691099, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 2.5594076546282598, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -48.626903370728662, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 14.174228098632916, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), 56.814263748089367, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 59.366741967714546, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 10.211872914487415, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), -41.055047116624593, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), 33.823634035361657, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 2.1399206258932093, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 58.907133726931114, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -4.5937464605072496, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 7.6607698905835306, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 0.52270180007242928, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -6.1667108720144057, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 16.367025852969824, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), -16.699517831785791, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -15.770641802955243, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 22.18066369384502, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), 3.3047200600533544, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 12.230578687790809, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 45.434388603947788, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -7.8693021805106014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -9.5192529958855161, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), 21.873129278607436, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), 39.029109740766707, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -13.708330442857314, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 11.298517845496059, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), -12.592733348794265, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 0.1502677481464687, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -11.274037744683085, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 31.177345205003732, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 12.347734088359516, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -36.498195463508956, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -5.767571487373738, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 9.6207093184217403, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), -11.352834008552833, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), -12.739502352702758, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 21.309595726285572, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 1.5344307521975367, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), -1.4482950780085204, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 25.638200715696836, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 4.3091227035921431, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), -20.964774357761929, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -18.956541853858397, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Daubechies10()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999909, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 96.679298632552829, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -116.34965915642296, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 14.112095126508832, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 32.690048905940387, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 5.8943110490242754, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 7.1897804135243311, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), -29.497593700117271, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), -43.550166700487111, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), -21.318454428095308, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -2.5817267428689123, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -43.177493364174268, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -49.268134860930772, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 4.2930057673628816, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 30.048913893701439, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 0.2056608635705881, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 19.981199738985779, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 27.210024072750741, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 9.0926105781637236, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -33.041700608948553, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), -43.608107137149318, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 21.907204796862281, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 41.657042526055449, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), 5.0692232288329642, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 14.958668185581487, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), -33.687462820713883, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 0.73873867656411996, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), 25.908939296496822, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 67.000260068585717, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -2.0141378091892879, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -5.5364414192326201, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 10.968963413159184, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 47.003464806356547, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -21.277813508567505, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 1.6221216961146538, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 19.880868652381682, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -16.049549226975479, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 11.648280690012871, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -2.6955214737537636, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 35.281375863506483, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -0.26598087250654601, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -12.782723347563401, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 29.52028482254714, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), 9.2827486649055828, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), 3.8269492720158604, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), 6.7700804028450401, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -8.4719128852458443, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), -38.451767656156534, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), -1.8524787939320646, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 26.386733232405458, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 7.021589716869066, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -4.993270974349727, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 3.1990625109745316, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -14.763354198569594, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), -27.381164995540978, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 23.327026134048864, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), -8.3291016483029772, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 1.2308112982457544, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 3.6960233531185338, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), -11.143277097722102, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 24.254617250240273, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), -4.0672658767776859, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 14.595605816270654, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -19.022461626894735, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Daubechies9_7()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 988.52515733649886, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 99.209606329473971, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -25.527638359256002, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -97.20431022716771, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -24.502689503711188, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 24.122646242347209, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), -17.669921494891064, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), -69.330862810813983, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), -83.412688967604154, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 2.0803900796313957, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -77.165151878043346, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -14.996582083306246, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -8.6973758773148031, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), -25.12875994013573, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 25.36800734098647, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 37.4903103950709, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 3.502032193061777, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 39.614438513468869, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 4.8641999716942843, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -43.120936991871226, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 9.3123150562466659, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -11.914955295603166, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -57.226856690498209, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), 67.896884134814741, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -29.622194708175943, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 12.642307188344715, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), -3.6936161484881662, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -0.80118962075328271, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), -18.062457993067813, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -27.253826619229734, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -8.0167499959320008, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), -1.6804783342695884, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -7.1599043914803158, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -4.5798938127422524, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 24.112495471400404, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), -27.717428076361031, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 5.4811236401690708, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 9.7960944396117817, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -24.064308501087414, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 1.0445025379719193, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 6.9033041211756769, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -10.413888703641334, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -21.267903974004135, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -13.995288897237105, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -0.56231682623294665, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -30.007811417755189, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -1.512790415097514, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 9.1319274668168529, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), -4.311353748078858, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 12.962048466043502, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), -19.527089649088676, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 12.488186792031746, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 0.022492461281151066, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -3.3559031892651485, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), -16.24128683946487, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 20.610468271748623, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 1.4968924624605549, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -4.6866436834981577, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 24.841048141246816, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), -16.707371898539332, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -3.2366844997012376, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 26.460675596954911, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 27.761347744393067, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -14.265647645766609, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Delegate()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal> > op(8, 8, new THaarWaveletFilter<klab::DoubleReal>());
        TEST_ASSERT(op.filter().waveLength() == 2)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 994.00000000000034, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -107.49999999999991, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -10.999999999999968, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 67.000000000000043, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 28.999999999999993, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -28.5, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 15.000000000000002, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 51.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 51.000000000000114, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 60.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -10.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 11.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 6.4999999999999938, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -45.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 26.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -25.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -18.499999999999989, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 0.49999999999998579, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -23.000000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 54.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -47.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 19.000000000000028, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 0.50000000000005684, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 2.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -68.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 47.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -6.499999999999992, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 20.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -9.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -24.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 23.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 10.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 18.5, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -31.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 18.500000000000004, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -1.9999999999999858, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 40.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 36.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -1.5, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -0.99999999999999734, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -15.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -26.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 14.499999999999998, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 7.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 5.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 11.5, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -21.499999999999972, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -1.4999999999999911, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -22.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 1.5000000000000071, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 3.4999999999999964, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 2.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -8.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -17.500000000000028, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 30.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -8.0000000000000036, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 22.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 19.499999999999996, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -11.499999999999993, precision))


        op.filter().setFilter(new TDaubechiesWaveletFilter<klab::DoubleReal, 4>());
        TEST_ASSERT(op.filter().waveLength() == 4)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999898, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -74.350544142276078, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), 29.783277833725016, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -29.843341500359539, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -19.838457268119896, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 18.637259526419165, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 19.963457268119896, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 31.744782028742804, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 40.141896345772807, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 47.195712325508936, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 47.340968362108292, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -45.163935902179823, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -1.6862976320958274, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 43.074673200287627, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -57.532354476264032, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 4.4902947306350303, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), -34.910254037844368, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 26.283257801676513, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -94.408144111257712, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -0.087078014682679949, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), -18.581243060694845, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 64.044786654946279, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -17.370190528383297, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -15.261937352910234, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 77.116057001341574, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), -32.235539987592716, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 24.383507134730753, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -19.753021718539038, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), -19.975072447521203, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 14.224514426634894, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), 12.186855652982141, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 38.878929277221452, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -0.98686027918559205, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 21.135970832383421, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 40.455127018922155, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 7.2066515603352741, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 2.7320508075688834, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), -22.254400971976246, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -18.533493649053899, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), -7.4967150697963971, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -5.5786024775091363, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 5.3128221735089198, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -8.3519191624432096, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -4.5346960169580655, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -28.582767602107936, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), 6.7379763209582144, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 4.9270008623713331, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 1.4064110867544617, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 1.6806079660838904, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -15.426356515353461, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 2.8653810567665801, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 7.3624183000719086, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 17.803203230275507, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 7.5642603887904984, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 8.3540017247426697, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), -2.4679445662276649, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 26.853765877365262, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 5.1623366001437745, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -12.043906460550971, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 13.887259526419172, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 13.029564371832437, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), -30.776837462515154, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 32.416265877365284, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), 7.141424651018017, precision))


        klab::TSmartPointer<TDaubechiesWaveletFilter<klab::DoubleReal, 8> > daubechies8 = new TDaubechiesWaveletFilter<klab::DoubleReal, 8>();
        op.filter().setFilter(daubechies8);
        TEST_ASSERT(op.filter().waveLength() == 8)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999977, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 52.445892062981528, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -2.477926877349037, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -107.65574447980721, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -22.090439023383595, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 40.949051155442682, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 1.1759766585946994, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 4.1399654188672885, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), -18.462826354812336, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), -63.148217805973303, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.088405370171337, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -42.100265738661967, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -32.019725870534323, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), -25.196457861209328, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -4.8852935990889916, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 45.891849207788724, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), -27.035733039249564, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -3.4169542491646467, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 26.139388551861003, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -33.616084640691099, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 2.5594076546282598, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -48.626903370728662, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 14.174228098632916, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), 56.814263748089367, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 59.366741967714546, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 10.211872914487415, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), -41.055047116624593, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), 33.823634035361657, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 2.1399206258932093, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 58.907133726931114, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -4.5937464605072496, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 7.6607698905835306, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 0.52270180007242928, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -6.1667108720144057, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 16.367025852969824, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), -16.699517831785791, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -15.770641802955243, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 22.18066369384502, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), 3.3047200600533544, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 12.230578687790809, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 45.434388603947788, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -7.8693021805106014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -9.5192529958855161, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), 21.873129278607436, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), 39.029109740766707, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -13.708330442857314, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 11.298517845496059, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), -12.592733348794265, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 0.1502677481464687, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -11.274037744683085, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 31.177345205003732, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 12.347734088359516, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -36.498195463508956, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -5.767571487373738, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 9.6207093184217403, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), -11.352834008552833, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), -12.739502352702758, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 21.309595726285572, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 1.5344307521975367, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), -1.4482950780085204, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 25.638200715696836, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 4.3091227035921431, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), -20.964774357761929, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -18.956541853858397, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Name()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TWavelet2DOperator<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > op(8, 8, "Haar");
        TEST_ASSERT(op.filter().waveLength() == 2)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 994.00000000000034, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -107.49999999999991, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -10.999999999999968, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 67.000000000000043, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 28.999999999999993, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -28.5, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 15.000000000000002, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 51.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 51.000000000000114, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 60.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -10.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 11.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 6.4999999999999938, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -45.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 26.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -25.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -18.499999999999989, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 0.49999999999998579, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -23.000000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 54.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -47.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 19.000000000000028, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 0.50000000000005684, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 2.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -68.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 47.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -6.499999999999992, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 20.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -9.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -24.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 23.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 10.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 18.5, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -31.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 18.500000000000004, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -1.9999999999999858, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 40.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 36.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -1.5, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -0.99999999999999734, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -15.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -26.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 14.499999999999998, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 7.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 5.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 11.5, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -21.499999999999972, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -1.4999999999999911, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -22.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 1.5000000000000071, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 3.4999999999999964, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 2.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -8.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -17.500000000000028, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 30.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -8.0000000000000036, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 22.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 19.499999999999996, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -11.499999999999993, precision))


        op.filter().set("Daubechies2");
        TEST_ASSERT(op.filter().waveLength() == 2)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 994.00000000000034, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -107.49999999999991, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -10.999999999999968, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 67.000000000000043, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 28.999999999999993, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -28.5, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 15.000000000000002, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 51.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 51.000000000000114, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 60.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -10.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 11.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 6.4999999999999938, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -45.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 26.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -25.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -18.499999999999989, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 0.49999999999998579, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -23.000000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 54.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -47.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 19.000000000000028, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 0.50000000000005684, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 2.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -68.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 47.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -6.499999999999992, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 20.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -9.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -24.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 23.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 10.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 18.5, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -31.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 18.500000000000004, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -1.9999999999999858, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 40.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 36.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -1.5, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -0.99999999999999734, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -15.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -26.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 14.499999999999998, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 7.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 5.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 11.5, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -21.499999999999972, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -1.4999999999999911, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -22.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 1.5000000000000071, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 3.4999999999999964, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 2.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -8.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -17.500000000000028, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 30.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -8.0000000000000036, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 22.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 19.499999999999996, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -11.499999999999993, precision))


        op.filter().set("Daubechies4");
        TEST_ASSERT(op.filter().waveLength() == 4)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999898, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -74.350544142276078, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), 29.783277833725016, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -29.843341500359539, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -19.838457268119896, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 18.637259526419165, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 19.963457268119896, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 31.744782028742804, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 40.141896345772807, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 47.195712325508936, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 47.340968362108292, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -45.163935902179823, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -1.6862976320958274, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 43.074673200287627, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -57.532354476264032, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 4.4902947306350303, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), -34.910254037844368, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 26.283257801676513, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -94.408144111257712, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -0.087078014682679949, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), -18.581243060694845, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 64.044786654946279, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -17.370190528383297, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -15.261937352910234, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 77.116057001341574, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), -32.235539987592716, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 24.383507134730753, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -19.753021718539038, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), -19.975072447521203, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 14.224514426634894, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), 12.186855652982141, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 38.878929277221452, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -0.98686027918559205, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 21.135970832383421, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 40.455127018922155, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 7.2066515603352741, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 2.7320508075688834, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), -22.254400971976246, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -18.533493649053899, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), -7.4967150697963971, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -5.5786024775091363, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 5.3128221735089198, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -8.3519191624432096, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -4.5346960169580655, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -28.582767602107936, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), 6.7379763209582144, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 4.9270008623713331, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 1.4064110867544617, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 1.6806079660838904, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -15.426356515353461, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 2.8653810567665801, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 7.3624183000719086, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 17.803203230275507, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 7.5642603887904984, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 8.3540017247426697, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), -2.4679445662276649, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 26.853765877365262, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 5.1623366001437745, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -12.043906460550971, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 13.887259526419172, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 13.029564371832437, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), -30.776837462515154, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 32.416265877365284, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), 7.141424651018017, precision))


        op.filter().set("Daubechies6");
        TEST_ASSERT(op.filter().waveLength() == 6)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999955, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -12.038446380914504, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -63.825617471159084, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -7.6373779449229664, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 9.1727572909519068, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -6.830905229142056, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 39.398751215856677, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), -6.7453905368492757, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 13.123486950183775, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), -23.647189163352738, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -72.114210182915016, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), 76.102411172466716, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 53.052778535868526, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), -53.560809485706415, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -5.7571658251691291, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -7.8648593201415427, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 91.318078018120559, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -21.847304971401698, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 16.551304181783689, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -7.8468077363814395, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 66.233098586605863, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -1.4679230052067485, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -40.867907316305875, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -1.9241806592945694, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -57.383807227577734, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 30.122785584720603, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), -28.516469678998408, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -36.06588681482598, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 16.910446945505356, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 1.6953332782543911, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), 45.831969269487644, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), -10.275993744714677, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -15.727126406538261, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 13.983625236864924, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -6.4714324199154234, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), -0.26621786266790082, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -4.114451151262692, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 19.227653484194139, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), 2.0333566779807608, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), -27.195009599074087, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 2.9742926031028958, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -13.206404217823682, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 19.601973096902881, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -12.273655416162413, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), 7.668702098431222, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -1.8775837908399255, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 10.732363117734369, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 12.539045876263149, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 39.094788134247842, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 3.6116718403186212, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), -12.46169902750367, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 17.981960178574859, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -23.390726037772836, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 36.083899559138267, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), -1.6267759817922123, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 10.936296660853861, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 0.99254050372658753, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -0.40219521703681238, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 33.189783898376938, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 14.378095075532713, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -16.157040273330662, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), -31.465588264444058, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), -10.174725096369036, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), 8.7805827202897007, precision))


        op.filter().set("Daubechies8");
        TEST_ASSERT(op.filter().waveLength() == 8)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999977, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 52.445892062981528, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -2.477926877349037, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -107.65574447980721, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -22.090439023383595, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 40.949051155442682, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 1.1759766585946994, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 4.1399654188672885, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), -18.462826354812336, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), -63.148217805973303, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.088405370171337, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -42.100265738661967, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -32.019725870534323, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), -25.196457861209328, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -4.8852935990889916, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 45.891849207788724, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), -27.035733039249564, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -3.4169542491646467, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 26.139388551861003, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -33.616084640691099, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 2.5594076546282598, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -48.626903370728662, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 14.174228098632916, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), 56.814263748089367, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 59.366741967714546, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 10.211872914487415, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), -41.055047116624593, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), 33.823634035361657, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 2.1399206258932093, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 58.907133726931114, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -4.5937464605072496, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 7.6607698905835306, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 0.52270180007242928, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -6.1667108720144057, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 16.367025852969824, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), -16.699517831785791, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -15.770641802955243, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 22.18066369384502, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), 3.3047200600533544, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 12.230578687790809, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 45.434388603947788, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -7.8693021805106014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -9.5192529958855161, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), 21.873129278607436, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), 39.029109740766707, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -13.708330442857314, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 11.298517845496059, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), -12.592733348794265, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 0.1502677481464687, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -11.274037744683085, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 31.177345205003732, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 12.347734088359516, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -36.498195463508956, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -5.767571487373738, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 9.6207093184217403, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), -11.352834008552833, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), -12.739502352702758, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 21.309595726285572, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 1.5344307521975367, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), -1.4482950780085204, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 25.638200715696836, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 4.3091227035921431, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), -20.964774357761929, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -18.956541853858397, precision))


        op.filter().set("Daubechies10");
        TEST_ASSERT(op.filter().waveLength() == 10)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999909, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 96.679298632552829, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -116.34965915642296, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 14.112095126508832, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 32.690048905940387, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 5.8943110490242754, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 7.1897804135243311, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), -29.497593700117271, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), -43.550166700487111, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), -21.318454428095308, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -2.5817267428689123, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -43.177493364174268, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -49.268134860930772, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 4.2930057673628816, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 30.048913893701439, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 0.2056608635705881, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 19.981199738985779, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 27.210024072750741, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 9.0926105781637236, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -33.041700608948553, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), -43.608107137149318, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 21.907204796862281, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 41.657042526055449, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), 5.0692232288329642, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 14.958668185581487, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), -33.687462820713883, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 0.73873867656411996, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), 25.908939296496822, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 67.000260068585717, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -2.0141378091892879, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -5.5364414192326201, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 10.968963413159184, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 47.003464806356547, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -21.277813508567505, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 1.6221216961146538, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 19.880868652381682, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -16.049549226975479, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 11.648280690012871, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -2.6955214737537636, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 35.281375863506483, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -0.26598087250654601, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -12.782723347563401, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 29.52028482254714, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), 9.2827486649055828, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), 3.8269492720158604, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), 6.7700804028450401, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -8.4719128852458443, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), -38.451767656156534, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), -1.8524787939320646, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 26.386733232405458, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 7.021589716869066, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -4.993270974349727, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 3.1990625109745316, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -14.763354198569594, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), -27.381164995540978, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 23.327026134048864, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), -8.3291016483029772, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 1.2308112982457544, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 3.6960233531185338, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), -11.143277097722102, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 24.254617250240273, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), -4.0672658767776859, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 14.595605816270654, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -19.022461626894735, precision))


        op.filter().set("Daubechies9.7");
        TEST_ASSERT(op.filter().waveLength() == 9)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 988.52515733649886, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 99.209606329473971, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -25.527638359256002, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -97.20431022716771, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -24.502689503711188, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 24.122646242347209, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), -17.669921494891064, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), -69.330862810813983, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), -83.412688967604154, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 2.0803900796313957, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -77.165151878043346, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -14.996582083306246, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -8.6973758773148031, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), -25.12875994013573, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 25.36800734098647, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 37.4903103950709, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 3.502032193061777, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 39.614438513468869, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 4.8641999716942843, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -43.120936991871226, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 9.3123150562466659, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -11.914955295603166, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -57.226856690498209, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), 67.896884134814741, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -29.622194708175943, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 12.642307188344715, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), -3.6936161484881662, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -0.80118962075328271, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), -18.062457993067813, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -27.253826619229734, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -8.0167499959320008, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), -1.6804783342695884, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -7.1599043914803158, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -4.5798938127422524, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 24.112495471400404, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), -27.717428076361031, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 5.4811236401690708, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 9.7960944396117817, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -24.064308501087414, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 1.0445025379719193, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 6.9033041211756769, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -10.413888703641334, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -21.267903974004135, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -13.995288897237105, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -0.56231682623294665, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -30.007811417755189, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -1.512790415097514, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 9.1319274668168529, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), -4.311353748078858, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 12.962048466043502, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), -19.527089649088676, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 12.488186792031746, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 0.022492461281151066, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -3.3559031892651485, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), -16.24128683946487, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 20.610468271748623, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 1.4968924624605549, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -4.6866436834981577, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 24.841048141246816, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), -16.707371898539332, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -3.2366844997012376, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 26.460675596954911, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 27.761347744393067, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -14.265647645766609, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApply_Custom()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        std::vector<klab::DoubleReal> haarWaveletCoefficients(2);
        haarWaveletCoefficients[0] =  0.70710678118654752440084436210485;
        haarWaveletCoefficients[1] = -0.70710678118654752440084436210485;

        std::vector<klab::DoubleReal> haarScalingCoefficients(2);
        haarScalingCoefficients[0] = 0.70710678118654752440084436210485;
        haarScalingCoefficients[1] = 0.70710678118654752440084436210485;

        TWavelet2DOperator<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > op(8, 8, TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));
        TEST_ASSERT(op.filter().waveLength() == 2)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 994.00000000000034, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -107.49999999999991, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -10.999999999999968, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 67.000000000000043, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 28.999999999999993, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -28.5, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 15.000000000000002, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 51.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 51.000000000000114, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 60.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 32.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -10.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 11.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 6.4999999999999938, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -45.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 26.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -25.5, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -18.499999999999989, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 0.49999999999998579, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -23.000000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 54.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -47.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 19.000000000000028, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 0.50000000000005684, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 2.5, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -68.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 47.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -15.500000000000005, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -6.499999999999992, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 20.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 13.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -9.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -24.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 23.499999999999986, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 10.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 18.5, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -31.000000000000014, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 18.500000000000004, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -1.9999999999999858, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 40.500000000000014, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 36.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -1.5, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -0.99999999999999734, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -15.500000000000007, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -26.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 14.499999999999998, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 7.4999999999999716, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 5.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 11.5, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -21.499999999999972, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -1.4999999999999911, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -22.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 1.5000000000000071, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 3.4999999999999964, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 2.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -8.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -17.500000000000028, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 30.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -8.0000000000000036, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 22.5, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 19.499999999999996, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -11.499999999999993, precision))


        std::vector<klab::DoubleReal> db4WaveletCoefficients(4);
        db4WaveletCoefficients[0] = -0.129409522551260340;
        db4WaveletCoefficients[1] = -0.224143868042013390;
        db4WaveletCoefficients[2] =  0.836516303737807720;
        db4WaveletCoefficients[3] = -0.482962913144534100;

        std::vector<klab::DoubleReal> db4ScalingCoefficients(4);
        db4ScalingCoefficients[0] =  0.482962913144534100;
        db4ScalingCoefficients[1] =  0.836516303737807720;
        db4ScalingCoefficients[2] =  0.224143868042013390;
        db4ScalingCoefficients[3] = -0.129409522551260340;
 
        op.filter().set(db4ScalingCoefficients, db4WaveletCoefficients);
        TEST_ASSERT(op.filter().waveLength() == 4)

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.999999999999999, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -74.350544142276078, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), 29.783277833725016, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), -29.843341500359539, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -19.838457268119896, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), 18.637259526419165, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 19.963457268119896, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 31.744782028742804, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 40.141896345772807, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 47.195712325508936, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), 47.340968362108292, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -45.163935902179823, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -1.6862976320958274, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 43.074673200287627, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -57.532354476264032, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 4.4902947306350303, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), -34.910254037844368, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 26.283257801676513, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -94.408144111257712, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -0.087078014682679949, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), -18.581243060694845, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 64.044786654946279, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -17.370190528383297, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -15.261937352910234, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), 77.116057001341574, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), -32.235539987592716, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 24.383507134730753, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -19.753021718539038, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), -19.975072447521203, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 14.224514426634894, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), 12.186855652982141, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 38.878929277221452, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -0.98686027918559205, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 21.135970832383421, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 40.455127018922155, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 7.2066515603352741, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 2.7320508075688834, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), -22.254400971976246, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -18.533493649053899, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), -7.4967150697963971, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -5.5786024775091363, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 5.3128221735089198, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -8.3519191624432096, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -4.5346960169580655, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -28.582767602107936, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), 6.7379763209582144, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 4.9270008623713331, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 1.4064110867544617, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 1.6806079660838904, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -15.426356515353461, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 2.8653810567665801, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 7.3624183000719086, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 17.803203230275507, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 7.5642603887904984, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 8.3540017247426697, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), -2.4679445662276649, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 26.853765877365262, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 5.1623366001437745, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -12.043906460550971, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 13.887259526419172, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 13.029564371832437, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), -30.776837462515154, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 32.416265877365284, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), 7.141424651018017, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8, 8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Haar()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8, 8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies2()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2> > op(8, 8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies4()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > op(8, 8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies6()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6> > op(8, 8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies8()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > op(8, 8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies10()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10> > op(8, 8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies9_7()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > op(8, 8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Delegate()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal> > fwt(klab::TDelegateWaveletFilter<klab::DoubleReal>(new klab::THaarWaveletFilter<klab::DoubleReal>()));
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal> > op(8, 8, klab::TDelegateWaveletFilter<klab::DoubleReal>(new klab::THaarWaveletFilter<klab::DoubleReal>()));

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Name()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        klab::TFWT2D<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > fwt("Daubechies4");
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > op(8, 8, "Daubechies4");

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet2DOperatorUnitTest::testApplyAdjoint_Custom()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;
        arma::Mat<klab::DoubleReal> fT;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);


        std::vector<klab::DoubleReal> haarWaveletCoefficients(2);
        haarWaveletCoefficients[0] =  0.70710678118654752440084436210485;
        haarWaveletCoefficients[1] = -0.70710678118654752440084436210485;

        std::vector<klab::DoubleReal> haarScalingCoefficients(2);
        haarScalingCoefficients[0] = 0.70710678118654752440084436210485;
        haarScalingCoefficients[1] = 0.70710678118654752440084436210485;

        klab::TFWT2D<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > fwt(klab::TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));
        arma::Mat<klab::DoubleReal> fwtMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fwt.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TWavelet2DOperator<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > op(8, 8, klab::TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;
        fT = xt;
        fT.reshape(8, 8);
        TEST_ASSERT(fT.n_rows==8 && fT.n_cols==8)

        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), fT(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), fT(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), fT(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), fT(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), fT(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), fT(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), fT(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), fT(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), fT(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), fT(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), fT(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), fT(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), fT(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), fT(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), fT(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), fT(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), fT(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), fT(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), fT(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), fT(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), fT(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), fT(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), fT(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), fT(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), fT(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), fT(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), fT(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), fT(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), fT(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), fT(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), fT(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), fT(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), fT(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), fT(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), fT(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), fT(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), fT(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), fT(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), fT(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), fT(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), fT(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), fT(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), fT(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), fT(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), fT(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), fT(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), fT(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), fT(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), fT(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), fT(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), fT(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), fT(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), fT(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), fT(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), fT(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), fT(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), fT(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), fT(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), fT(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), fT(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), fT(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), fT(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), fT(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), fT(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
