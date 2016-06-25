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

#include "InverseWavelet1DOperatorUnitTest.h"
#include "../include/Wavelet1DOperator.h"
#include "../include/InverseWavelet1DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KInverseWavelet1DOperatorUnitTest::KInverseWavelet1DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testNConstructor)  
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testNFilterConstructor)  
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testFilter)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Haar)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Daubechies2)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Daubechies4)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Daubechies6)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Daubechies8)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Daubechies10)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Daubechies9_7)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Delegate)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Name)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApply_Custom)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Haar)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies2)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies4)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies6)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies8)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies10)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies9_7)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Delegate)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Name)
    TEST_ADD(KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Custom)
}

// ---------------------------------------------------------------------------------------------------- //

KInverseWavelet1DOperatorUnitTest::~KInverseWavelet1DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testNConstructor()
{
    try
    {
        TInverseWavelet1DOperator<klab::DoubleReal> op(16);
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(op.filter().waveLength() == 0)

        TInverseWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(16);
        TEST_ASSERT(op2.m()==16 && op2.n()==16)
        TEST_ASSERT(op2.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testNFilterConstructor()
{
    try
    {
        THaarWaveletFilter<klab::DoubleReal> filter;

        TInverseWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(16, filter);
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(op.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        THaarWaveletFilter<klab::DoubleReal> filter;

        TInverseWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(16, filter);
        TInverseWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(op);
        TEST_ASSERT(op2.m()==16 && op2.n()==16)
        TEST_ASSERT(op2.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testFilter()
{
    try
    {
        TInverseWavelet1DOperator<klab::DoubleReal> op(16);
        TEST_ASSERT(op.filter().waveLength() == 0)

        TInverseWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(16);
        TEST_ASSERT(op2.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(n);
        TInverseWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > iop(n);
        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Haar()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(n);
        TInverseWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > iop(n);
        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Daubechies2()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 2> > op(n);
        TInverseWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 2> > iop(n);
        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Daubechies4()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 4> > op(n);
        TInverseWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 4> > iop(n);
        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Daubechies6()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 6> > op(n);
        TInverseWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 6> > iop(n);
        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Daubechies8()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 8> > op(n);
        TInverseWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 8> > iop(n);
        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Daubechies10()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 10> > op(n);
        TInverseWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 10> > iop(n);
        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Daubechies9_7()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-9;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > op(n);
        TInverseWavelet1DOperator<klab::DoubleReal, TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > iop(n);
        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Delegate()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDelegateWaveletFilter<klab::DoubleReal> > op(n, new THaarWaveletFilter<klab::DoubleReal>());
        TInverseWavelet1DOperator<klab::DoubleReal, TDelegateWaveletFilter<klab::DoubleReal> > iop(n, new THaarWaveletFilter<klab::DoubleReal>());
        TEST_ASSERT(iop.filter().waveLength() == 2)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))


        op.filter().setFilter(new TDaubechiesWaveletFilter<klab::DoubleReal, 4>());
        iop.filter().setFilter(new TDaubechiesWaveletFilter<klab::DoubleReal, 4>());
        TEST_ASSERT(iop.filter().waveLength() == 4)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))


        klab::TSmartPointer<TDaubechiesWaveletFilter<klab::DoubleReal, 8> > daubechies8 = new TDaubechiesWaveletFilter<klab::DoubleReal, 8>();
        op.filter().setFilter(daubechies8);
        iop.filter().setFilter(daubechies8);
        TEST_ASSERT(iop.filter().waveLength() == 8)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Name()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TNameWaveletFilter<klab::DoubleReal> > op(n, "Haar");
        TInverseWavelet1DOperator<klab::DoubleReal, TNameWaveletFilter<klab::DoubleReal> > iop(n, "Haar");
        TEST_ASSERT(iop.filter().waveLength() == 2)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))


        op.filter().set("Daubechies2");
        iop.filter().set("Daubechies2");
        TEST_ASSERT(iop.filter().waveLength() == 2)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))


        op.filter().set("Daubechies4");
        iop.filter().set("Daubechies4");
        TEST_ASSERT(iop.filter().waveLength() == 4)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))


        op.filter().set("Daubechies6");
        iop.filter().set("Daubechies6");
        TEST_ASSERT(iop.filter().waveLength() == 6)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
        

        op.filter().set("Daubechies8");
        iop.filter().set("Daubechies8");
        TEST_ASSERT(iop.filter().waveLength() == 8)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))


        op.filter().set("Daubechies10");
        iop.filter().set("Daubechies10");
        TEST_ASSERT(iop.filter().waveLength() == 10)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))


        precision = 1e-9;
        op.filter().set("Daubechies9.7");
        iop.filter().set("Daubechies9.7");
        TEST_ASSERT(iop.filter().waveLength() == 9)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApply_Custom()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        std::vector<klab::DoubleReal> haarWaveletCoefficients(2);
        haarWaveletCoefficients[0] =  0.70710678118654752440084436210485;
        haarWaveletCoefficients[1] = -0.70710678118654752440084436210485;

        std::vector<klab::DoubleReal> haarScalingCoefficients(2);
        haarScalingCoefficients[0] = 0.70710678118654752440084436210485;
        haarScalingCoefficients[1] = 0.70710678118654752440084436210485;

        TWavelet1DOperator<klab::DoubleReal, TCustomWaveletFilter<klab::DoubleReal> > op(n, TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));
        TInverseWavelet1DOperator<klab::DoubleReal, TCustomWaveletFilter<klab::DoubleReal> > iop(n, TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));
        TEST_ASSERT(op.filter().waveLength() == 2)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
        

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
        TEST_ASSERT(iop.filter().waveLength() == 4)

        op.apply(f, F);
        iop.apply(F, fr);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0],  f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1],  f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2],  f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3],  f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4],  f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5],  f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6],  f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7],  f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8],  f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9],  f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Haar()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies2()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies4()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies6()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies8()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies10()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies9_7()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Delegate()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > > fwt(new klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4>());
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > > op(8, new klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4>());

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Name()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > fwt("Daubechies4");
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > op(8, "Daubechies4");

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseWavelet1DOperatorUnitTest::testApplyAdjoint_Custom()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 

        std::vector<klab::DoubleReal> haarWaveletCoefficients(2);
        haarWaveletCoefficients[0] =  0.70710678118654752440084436210485;
        haarWaveletCoefficients[1] = -0.70710678118654752440084436210485;

        std::vector<klab::DoubleReal> haarScalingCoefficients(2);
        haarScalingCoefficients[0] = 0.70710678118654752440084436210485;
        haarScalingCoefficients[1] = 0.70710678118654752440084436210485;
        

        klab::TFWT1D<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > fwt(klab::TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TInverseWavelet1DOperator<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > op(8, klab::TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
