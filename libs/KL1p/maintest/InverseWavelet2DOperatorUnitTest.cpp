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

#include "InverseWavelet2DOperatorUnitTest.h"
#include "../include/Wavelet2DOperator.h"
#include "../include/InverseWavelet2DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KInverseWavelet2DOperatorUnitTest::KInverseWavelet2DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testHeightWidthConstructor)  
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testHeightWidthFilterConstructor)  
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testWidth)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testHeight)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testFilter)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Haar)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Daubechies2)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Daubechies4)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Daubechies6)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Daubechies8)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Daubechies10)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Daubechies9_7)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Delegate)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Name)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApply_Custom)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Haar)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies2)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies4)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies6)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies8)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies10)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies9_7)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Delegate)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Name)
    TEST_ADD(KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Custom)
}

// ---------------------------------------------------------------------------------------------------- //

KInverseWavelet2DOperatorUnitTest::~KInverseWavelet2DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testHeightWidthConstructor()
{
    try
    {
        TInverseWavelet2DOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.filter().waveLength()==0 && op.height()==4 && op.width()==8)

        TInverseWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(4, 8);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.filter().waveLength()==2 && op2.height()==4 && op2.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testHeightWidthFilterConstructor()
{
    try
    {
        THaarWaveletFilter<klab::DoubleReal> filter;

        TInverseWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(4, 8, filter);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.filter().waveLength()==2 && op.height()==4 && op.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        THaarWaveletFilter<klab::DoubleReal> filter;

        TInverseWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(4, 8, filter);
        TInverseWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(op);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.filter().waveLength()==2 && op2.height()==4 && op2.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testWidth()
{
    try
    {
        TInverseWavelet2DOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.height()==4 && op.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testHeight()
{
    try
    {
        TInverseWavelet2DOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.height()==4 && op.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testFilter()
{
    try
    {
        TInverseWavelet2DOperator<klab::DoubleReal> op(0, 0);
        TEST_ASSERT(op.filter().waveLength() == 0)

        TInverseWavelet2DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(0, 0);
        TEST_ASSERT(op2.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8, 8);
        TInverseWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > iop(8, 8);

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Haar()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8, 8);
        TInverseWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > iop(8, 8);

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Daubechies2()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2> > op(8, 8);
        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2> > iop(8, 8);

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Daubechies4()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > op(8, 8);
        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > iop(8, 8);

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Daubechies6()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6> > op(8, 8);
        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6> > iop(8, 8);

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Daubechies8()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > op(8, 8);
        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > iop(8, 8);

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Daubechies10()
{
    try
    {
        klab::DoubleReal precision = 1e-11;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10> > op(8, 8);
        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10> > iop(8, 8);

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Daubechies9_7()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > op(8, 8);
        TInverseWavelet2DOperator<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > iop(8, 8);

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Delegate()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal> > op(8, 8, new THaarWaveletFilter<klab::DoubleReal>());
        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal> > iop(8, 8, new THaarWaveletFilter<klab::DoubleReal>());
        TEST_ASSERT(op.filter().waveLength() == 2)
        TEST_ASSERT(iop.filter().waveLength() == 2)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        op.filter().setFilter(new TDaubechiesWaveletFilter<klab::DoubleReal, 4>());
        iop.filter().setFilter(new TDaubechiesWaveletFilter<klab::DoubleReal, 4>());
        TEST_ASSERT(op.filter().waveLength() == 4)
        TEST_ASSERT(iop.filter().waveLength() == 4)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        klab::TSmartPointer<TDaubechiesWaveletFilter<klab::DoubleReal, 8> > daubechies8 = new TDaubechiesWaveletFilter<klab::DoubleReal, 8>();
        op.filter().setFilter(daubechies8);
        iop.filter().setFilter(daubechies8);
        TEST_ASSERT(op.filter().waveLength() == 8)
        TEST_ASSERT(iop.filter().waveLength() == 8)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Name()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > op(8, 8, "Haar");
        TInverseWavelet2DOperator<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > iop(8, 8, "Haar");
        TEST_ASSERT(op.filter().waveLength() == 2)
        TEST_ASSERT(iop.filter().waveLength() == 2)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        op.filter().set("Daubechies2");
        iop.filter().set("Daubechies2");
        TEST_ASSERT(op.filter().waveLength() == 2)
        TEST_ASSERT(iop.filter().waveLength() == 2)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        op.filter().set("Daubechies4");
        iop.filter().set("Daubechies4");
        TEST_ASSERT(op.filter().waveLength() == 4)
        TEST_ASSERT(iop.filter().waveLength() == 4)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        op.filter().set("Daubechies6");
        iop.filter().set("Daubechies6");
        TEST_ASSERT(op.filter().waveLength() == 6)
        TEST_ASSERT(iop.filter().waveLength() == 6)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        op.filter().set("Daubechies8");
        iop.filter().set("Daubechies8");
        TEST_ASSERT(op.filter().waveLength() == 8)
        TEST_ASSERT(iop.filter().waveLength() == 8)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        precision = 1e-11;
        op.filter().set("Daubechies10");
        iop.filter().set("Daubechies10");
        TEST_ASSERT(op.filter().waveLength() == 10)
        TEST_ASSERT(iop.filter().waveLength() == 10)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        precision = 1e-12;
        op.filter().set("Daubechies9.7");
        iop.filter().set("Daubechies9.7");
        TEST_ASSERT(op.filter().waveLength() == 9)
        TEST_ASSERT(iop.filter().waveLength() == 9)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApply_Custom()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> fR;

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

        TWavelet2DOperator<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > op(8, 8, TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));
        TInverseWavelet2DOperator<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > iop(8, 8, TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));
        TEST_ASSERT(op.filter().waveLength() == 2)
        TEST_ASSERT(iop.filter().waveLength() == 2)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


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
        iop.filter().set(db4ScalingCoefficients, db4WaveletCoefficients);
        TEST_ASSERT(op.filter().waveLength() == 4)
        TEST_ASSERT(iop.filter().waveLength() == 4)

        op.apply(x, y);
        iop.apply(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8, 8);

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Haar()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8, 8);

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies2()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2> > op(8, 8);

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies4()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > op(8, 8);

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies6()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6> > op(8, 8);

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies8()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > op(8, 8);

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies10()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10> > op(8, 8);

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Daubechies9_7()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > op(8, 8);

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Delegate()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal> > op(8, 8, klab::TDelegateWaveletFilter<klab::DoubleReal>(new klab::THaarWaveletFilter<klab::DoubleReal>()));

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Name()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > op(8, 8, "Daubechies4");

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

void KInverseWavelet2DOperatorUnitTest::testApplyAdjoint_Custom()
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
            fwt.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fwtMatrix(i, j) = outMatrix[i];
        } 

        TInverseWavelet2DOperator<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > op(8, 8, klab::TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));

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
