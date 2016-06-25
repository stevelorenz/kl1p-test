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

#include "ScalarOperatorUnitTest.h"
#include "../include/ScalarOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KScalarOperatorUnitTest::KScalarOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KScalarOperatorUnitTest::testNConstructor)  
    TEST_ADD(KScalarOperatorUnitTest::testNValueConstructor)  
    TEST_ADD(KScalarOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KScalarOperatorUnitTest::testValue)
    TEST_ADD(KScalarOperatorUnitTest::testApply)
    TEST_ADD(KScalarOperatorUnitTest::testApply_Complex)
    TEST_ADD(KScalarOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KScalarOperatorUnitTest::testApplyAdjoint_Complex)
    TEST_ADD(KScalarOperatorUnitTest::testColumn)
    TEST_ADD(KScalarOperatorUnitTest::testColumn_Complex)
    TEST_ADD(KScalarOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KScalarOperatorUnitTest::testColumnAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KScalarOperatorUnitTest::~KScalarOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testNConstructor()
{
    try
    {
        TScalarOperator<klab::DoubleReal> op(16);
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(klab::Equals(op.value(), 1.0))

        TScalarOperator<std::complex<klab::DoubleReal> > cop(16);
        TEST_ASSERT(cop.m()==16 && cop.n()==16)
        TEST_ASSERT(klab::Equals(cop.value(), std::complex<klab::DoubleReal>(1.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testNValueConstructor()
{
    try
    {
        TScalarOperator<klab::DoubleReal> op(16, 1.2345);
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(klab::Equals(op.value(), 1.2345))

        TScalarOperator<std::complex<klab::DoubleReal> > cop(16, std::complex<klab::DoubleReal>(1.2345, -9.8765));
        TEST_ASSERT(cop.m()==16 && cop.n()==16)
        TEST_ASSERT(klab::Equals(cop.value(), std::complex<klab::DoubleReal>(1.2345, -9.8765)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TScalarOperator<klab::DoubleReal> op(16, 1.2345);
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(klab::Equals(op.value(), 1.2345))

        TScalarOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.m()==16 && op2.n()==16)
        TEST_ASSERT(klab::Equals(op2.value(), 1.2345))


        TScalarOperator<std::complex<klab::DoubleReal> > cop(16, std::complex<klab::DoubleReal>(1.2345, -9.8765));
        TEST_ASSERT(cop.m()==16 && cop.n()==16)
        TEST_ASSERT(klab::Equals(cop.value(), std::complex<klab::DoubleReal>(1.2345, -9.8765)))

        TScalarOperator<std::complex<klab::DoubleReal> > cop2(cop);
        TEST_ASSERT(cop2.m()==16 && cop2.n()==16)
        TEST_ASSERT(klab::Equals(cop2.value(), std::complex<klab::DoubleReal>(1.2345, -9.8765)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testValue()
{
    try
    {
        TScalarOperator<klab::DoubleReal> op(16, 1.2345);
        TEST_ASSERT(klab::Equals(op.value(), 1.2345))

        TScalarOperator<std::complex<klab::DoubleReal> > cop(16, std::complex<klab::DoubleReal>(1.2345, -9.8765));
        TEST_ASSERT(klab::Equals(cop.value(), std::complex<klab::DoubleReal>(1.2345, -9.8765)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testApply()
{
    try
    {
        klab::UInt32 n = 16;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;

        x[0]  =  1.0;
        x[1]  = -2.0;
        x[2]  =  3.0;
        x[3]  = -4.0;
        x[4]  =  5.0;
        x[5]  =  6.0;
        x[6]  = -7.0;
        x[7]  = -8.0;
        x[8]  = -9.0;
        x[9]  =  10.0;
        x[10] = -11.0;
        x[11] =  12.0;
        x[12] =  13.0;
        x[13] =  14.0;
        x[14] = -15.0;
        x[15] = -16.0;

        TScalarOperator<klab::DoubleReal> op(n, 2.5);
        op.apply(x, y);

        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],   2.5, precision))
        TEST_ASSERT(klab::Equals(y[1],  -5.0, precision))
        TEST_ASSERT(klab::Equals(y[2],   7.5, precision))
        TEST_ASSERT(klab::Equals(y[3],  -10.0, precision))
        TEST_ASSERT(klab::Equals(y[4],   12.5, precision))
        TEST_ASSERT(klab::Equals(y[5],   15.0, precision))
        TEST_ASSERT(klab::Equals(y[6],  -17.5, precision))
        TEST_ASSERT(klab::Equals(y[7],  -20.0, precision))
        TEST_ASSERT(klab::Equals(y[8],  -22.5, precision))
        TEST_ASSERT(klab::Equals(y[9],   25.0, precision))
        TEST_ASSERT(klab::Equals(y[10], -27.5, precision))
        TEST_ASSERT(klab::Equals(y[11],  30.0, precision))
        TEST_ASSERT(klab::Equals(y[12],  32.5, precision))
        TEST_ASSERT(klab::Equals(y[13],  35.0, precision))
        TEST_ASSERT(klab::Equals(y[14], -37.5, precision))
        TEST_ASSERT(klab::Equals(y[15], -40.0, precision))


        // Limit cases.
        TScalarOperator<klab::DoubleReal> op0(n, 0.0);
        op0.apply(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[1],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[2],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[3],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[4],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[5],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[6],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[7],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[8],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[9],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[10], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[15], 0.0, precision))

        TScalarOperator<klab::DoubleReal> op1(n, 1.0);
        op1.apply(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  x[0], precision))
        TEST_ASSERT(klab::Equals(y[1],  x[1], precision))
        TEST_ASSERT(klab::Equals(y[2],  x[2], precision))
        TEST_ASSERT(klab::Equals(y[3],  x[3], precision))
        TEST_ASSERT(klab::Equals(y[4],  x[4], precision))
        TEST_ASSERT(klab::Equals(y[5],  x[5], precision))
        TEST_ASSERT(klab::Equals(y[6],  x[6], precision))
        TEST_ASSERT(klab::Equals(y[7],  x[7], precision))
        TEST_ASSERT(klab::Equals(y[8],  x[8], precision))
        TEST_ASSERT(klab::Equals(y[9],  x[9], precision))
        TEST_ASSERT(klab::Equals(y[10], x[10], precision))
        TEST_ASSERT(klab::Equals(y[11], x[11], precision))
        TEST_ASSERT(klab::Equals(y[12], x[12], precision))
        TEST_ASSERT(klab::Equals(y[13], x[13], precision))
        TEST_ASSERT(klab::Equals(y[14], x[14], precision))
        TEST_ASSERT(klab::Equals(y[15], x[15], precision))

        TScalarOperator<klab::DoubleReal> opm1(n, -1.0);
        opm1.apply(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  -x[0], precision))
        TEST_ASSERT(klab::Equals(y[1],  -x[1], precision))
        TEST_ASSERT(klab::Equals(y[2],  -x[2], precision))
        TEST_ASSERT(klab::Equals(y[3],  -x[3], precision))
        TEST_ASSERT(klab::Equals(y[4],  -x[4], precision))
        TEST_ASSERT(klab::Equals(y[5],  -x[5], precision))
        TEST_ASSERT(klab::Equals(y[6],  -x[6], precision))
        TEST_ASSERT(klab::Equals(y[7],  -x[7], precision))
        TEST_ASSERT(klab::Equals(y[8],  -x[8], precision))
        TEST_ASSERT(klab::Equals(y[9],  -x[9], precision))
        TEST_ASSERT(klab::Equals(y[10], -x[10], precision))
        TEST_ASSERT(klab::Equals(y[11], -x[11], precision))
        TEST_ASSERT(klab::Equals(y[12], -x[12], precision))
        TEST_ASSERT(klab::Equals(y[13], -x[13], precision))
        TEST_ASSERT(klab::Equals(y[14], -x[14], precision))
        TEST_ASSERT(klab::Equals(y[15], -x[15], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::UInt32 n = 16;
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;

        x[0]  =  1.0;
        x[1]  = -2.0;
        x[2]  =  3.0;
        x[3]  = -4.0;
        x[4]  =  5.0;
        x[5]  =  6.0;
        x[6]  = -7.0;
        x[7]  = -8.0;
        x[8]  = -9.0;
        x[9]  =  10.0;
        x[10] = -11.0;
        x[11] =  12.0;
        x[12] =  13.0;
        x[13] =  14.0;
        x[14] = -15.0;
        x[15] = -16.0;

        TScalarOperator<std::complex<klab::DoubleReal> > op(n, std::complex<klab::DoubleReal>(2.5, -3.0));
        op.apply(x, y);

        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  std::complex<klab::DoubleReal>( 2.5,  -3.0), precision))
        TEST_ASSERT(klab::Equals(y[1],  std::complex<klab::DoubleReal>(-5.0,   6.0), precision))
        TEST_ASSERT(klab::Equals(y[2],  std::complex<klab::DoubleReal>( 7.5,  -9.0), precision))
        TEST_ASSERT(klab::Equals(y[3],  std::complex<klab::DoubleReal>(-10.0,  12.0), precision))
        TEST_ASSERT(klab::Equals(y[4],  std::complex<klab::DoubleReal>( 12.5, -15.0), precision))
        TEST_ASSERT(klab::Equals(y[5],  std::complex<klab::DoubleReal>( 15.0, -18.0), precision))
        TEST_ASSERT(klab::Equals(y[6],  std::complex<klab::DoubleReal>(-17.5,  21.0), precision))
        TEST_ASSERT(klab::Equals(y[7],  std::complex<klab::DoubleReal>(-20.0,  24.0), precision))
        TEST_ASSERT(klab::Equals(y[8],  std::complex<klab::DoubleReal>(-22.5,  27.0), precision))
        TEST_ASSERT(klab::Equals(y[9],  std::complex<klab::DoubleReal>( 25.0, -30.0), precision))
        TEST_ASSERT(klab::Equals(y[10], std::complex<klab::DoubleReal>(-27.5,  33.0), precision))
        TEST_ASSERT(klab::Equals(y[11], std::complex<klab::DoubleReal>( 30.0, -36.0), precision))
        TEST_ASSERT(klab::Equals(y[12], std::complex<klab::DoubleReal>( 32.5, -39.0), precision))
        TEST_ASSERT(klab::Equals(y[13], std::complex<klab::DoubleReal>( 35.0, -42.0), precision))
        TEST_ASSERT(klab::Equals(y[14], std::complex<klab::DoubleReal>(-37.5,  45.0), precision))
        TEST_ASSERT(klab::Equals(y[15], std::complex<klab::DoubleReal>(-40.0,  48.0), precision))


        // Limit cases.
        TScalarOperator<std::complex<klab::DoubleReal> > op0(n, std::complex<klab::DoubleReal>(0.0, 0.0));
        op0.apply(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[1],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[2],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[3],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[4],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[5],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[6],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[7],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[8],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[9],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[10], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[11], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[12], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[13], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[14], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[15], std::complex<klab::DoubleReal>(0.0, 0.0), precision))

        TScalarOperator<std::complex<klab::DoubleReal> > op1(n, std::complex<klab::DoubleReal>(1.0, 0.0));
        op1.apply(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  x[0], precision))
        TEST_ASSERT(klab::Equals(y[1],  x[1], precision))
        TEST_ASSERT(klab::Equals(y[2],  x[2], precision))
        TEST_ASSERT(klab::Equals(y[3],  x[3], precision))
        TEST_ASSERT(klab::Equals(y[4],  x[4], precision))
        TEST_ASSERT(klab::Equals(y[5],  x[5], precision))
        TEST_ASSERT(klab::Equals(y[6],  x[6], precision))
        TEST_ASSERT(klab::Equals(y[7],  x[7], precision))
        TEST_ASSERT(klab::Equals(y[8],  x[8], precision))
        TEST_ASSERT(klab::Equals(y[9],  x[9], precision))
        TEST_ASSERT(klab::Equals(y[10], x[10], precision))
        TEST_ASSERT(klab::Equals(y[11], x[11], precision))
        TEST_ASSERT(klab::Equals(y[12], x[12], precision))
        TEST_ASSERT(klab::Equals(y[13], x[13], precision))
        TEST_ASSERT(klab::Equals(y[14], x[14], precision))
        TEST_ASSERT(klab::Equals(y[15], x[15], precision))

        TScalarOperator<std::complex<klab::DoubleReal> > opm1(n, std::complex<klab::DoubleReal>(-1.0, 0.0));
        opm1.apply(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  -x[0], precision))
        TEST_ASSERT(klab::Equals(y[1],  -x[1], precision))
        TEST_ASSERT(klab::Equals(y[2],  -x[2], precision))
        TEST_ASSERT(klab::Equals(y[3],  -x[3], precision))
        TEST_ASSERT(klab::Equals(y[4],  -x[4], precision))
        TEST_ASSERT(klab::Equals(y[5],  -x[5], precision))
        TEST_ASSERT(klab::Equals(y[6],  -x[6], precision))
        TEST_ASSERT(klab::Equals(y[7],  -x[7], precision))
        TEST_ASSERT(klab::Equals(y[8],  -x[8], precision))
        TEST_ASSERT(klab::Equals(y[9],  -x[9], precision))
        TEST_ASSERT(klab::Equals(y[10], -x[10], precision))
        TEST_ASSERT(klab::Equals(y[11], -x[11], precision))
        TEST_ASSERT(klab::Equals(y[12], -x[12], precision))
        TEST_ASSERT(klab::Equals(y[13], -x[13], precision))
        TEST_ASSERT(klab::Equals(y[14], -x[14], precision))
        TEST_ASSERT(klab::Equals(y[15], -x[15], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::UInt32 n = 16;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;

        x[0]  =  1.0;
        x[1]  = -2.0;
        x[2]  =  3.0;
        x[3]  = -4.0;
        x[4]  =  5.0;
        x[5]  =  6.0;
        x[6]  = -7.0;
        x[7]  = -8.0;
        x[8]  = -9.0;
        x[9]  =  10.0;
        x[10] = -11.0;
        x[11] =  12.0;
        x[12] =  13.0;
        x[13] =  14.0;
        x[14] = -15.0;
        x[15] = -16.0;

        TScalarOperator<klab::DoubleReal> op(n, 2.5);
        op.applyAdjoint(x, y);

        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],   2.5, precision))
        TEST_ASSERT(klab::Equals(y[1],  -5.0, precision))
        TEST_ASSERT(klab::Equals(y[2],   7.5, precision))
        TEST_ASSERT(klab::Equals(y[3],  -10.0, precision))
        TEST_ASSERT(klab::Equals(y[4],   12.5, precision))
        TEST_ASSERT(klab::Equals(y[5],   15.0, precision))
        TEST_ASSERT(klab::Equals(y[6],  -17.5, precision))
        TEST_ASSERT(klab::Equals(y[7],  -20.0, precision))
        TEST_ASSERT(klab::Equals(y[8],  -22.5, precision))
        TEST_ASSERT(klab::Equals(y[9],   25.0, precision))
        TEST_ASSERT(klab::Equals(y[10], -27.5, precision))
        TEST_ASSERT(klab::Equals(y[11],  30.0, precision))
        TEST_ASSERT(klab::Equals(y[12],  32.5, precision))
        TEST_ASSERT(klab::Equals(y[13],  35.0, precision))
        TEST_ASSERT(klab::Equals(y[14], -37.5, precision))
        TEST_ASSERT(klab::Equals(y[15], -40.0, precision))


        // Limit cases.
        TScalarOperator<klab::DoubleReal> op0(n, 0.0);
        op0.applyAdjoint(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[1],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[2],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[3],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[4],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[5],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[6],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[7],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[8],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[9],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[10], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[15], 0.0, precision))

        TScalarOperator<klab::DoubleReal> op1(n, 1.0);
        op1.applyAdjoint(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  x[0], precision))
        TEST_ASSERT(klab::Equals(y[1],  x[1], precision))
        TEST_ASSERT(klab::Equals(y[2],  x[2], precision))
        TEST_ASSERT(klab::Equals(y[3],  x[3], precision))
        TEST_ASSERT(klab::Equals(y[4],  x[4], precision))
        TEST_ASSERT(klab::Equals(y[5],  x[5], precision))
        TEST_ASSERT(klab::Equals(y[6],  x[6], precision))
        TEST_ASSERT(klab::Equals(y[7],  x[7], precision))
        TEST_ASSERT(klab::Equals(y[8],  x[8], precision))
        TEST_ASSERT(klab::Equals(y[9],  x[9], precision))
        TEST_ASSERT(klab::Equals(y[10], x[10], precision))
        TEST_ASSERT(klab::Equals(y[11], x[11], precision))
        TEST_ASSERT(klab::Equals(y[12], x[12], precision))
        TEST_ASSERT(klab::Equals(y[13], x[13], precision))
        TEST_ASSERT(klab::Equals(y[14], x[14], precision))
        TEST_ASSERT(klab::Equals(y[15], x[15], precision))

        TScalarOperator<klab::DoubleReal> opm1(n, -1.0);
        opm1.applyAdjoint(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  -x[0], precision))
        TEST_ASSERT(klab::Equals(y[1],  -x[1], precision))
        TEST_ASSERT(klab::Equals(y[2],  -x[2], precision))
        TEST_ASSERT(klab::Equals(y[3],  -x[3], precision))
        TEST_ASSERT(klab::Equals(y[4],  -x[4], precision))
        TEST_ASSERT(klab::Equals(y[5],  -x[5], precision))
        TEST_ASSERT(klab::Equals(y[6],  -x[6], precision))
        TEST_ASSERT(klab::Equals(y[7],  -x[7], precision))
        TEST_ASSERT(klab::Equals(y[8],  -x[8], precision))
        TEST_ASSERT(klab::Equals(y[9],  -x[9], precision))
        TEST_ASSERT(klab::Equals(y[10], -x[10], precision))
        TEST_ASSERT(klab::Equals(y[11], -x[11], precision))
        TEST_ASSERT(klab::Equals(y[12], -x[12], precision))
        TEST_ASSERT(klab::Equals(y[13], -x[13], precision))
        TEST_ASSERT(klab::Equals(y[14], -x[14], precision))
        TEST_ASSERT(klab::Equals(y[15], -x[15], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::UInt32 n = 16;
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;

        x[0]  =  1.0;
        x[1]  = -2.0;
        x[2]  =  3.0;
        x[3]  = -4.0;
        x[4]  =  5.0;
        x[5]  =  6.0;
        x[6]  = -7.0;
        x[7]  = -8.0;
        x[8]  = -9.0;
        x[9]  =  10.0;
        x[10] = -11.0;
        x[11] =  12.0;
        x[12] =  13.0;
        x[13] =  14.0;
        x[14] = -15.0;
        x[15] = -16.0;

        TScalarOperator<std::complex<klab::DoubleReal> > op(n, std::complex<klab::DoubleReal>(2.5, -3.0));
        op.applyAdjoint(x, y);

        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  std::complex<klab::DoubleReal>( 2.5,   3.0), precision))
        TEST_ASSERT(klab::Equals(y[1],  std::complex<klab::DoubleReal>(-5.0,  -6.0), precision))
        TEST_ASSERT(klab::Equals(y[2],  std::complex<klab::DoubleReal>( 7.5,   9.0), precision))
        TEST_ASSERT(klab::Equals(y[3],  std::complex<klab::DoubleReal>(-10.0, -12.0), precision))
        TEST_ASSERT(klab::Equals(y[4],  std::complex<klab::DoubleReal>( 12.5,  15.0), precision))
        TEST_ASSERT(klab::Equals(y[5],  std::complex<klab::DoubleReal>( 15.0,  18.0), precision))
        TEST_ASSERT(klab::Equals(y[6],  std::complex<klab::DoubleReal>(-17.5, -21.0), precision))
        TEST_ASSERT(klab::Equals(y[7],  std::complex<klab::DoubleReal>(-20.0, -24.0), precision))
        TEST_ASSERT(klab::Equals(y[8],  std::complex<klab::DoubleReal>(-22.5, -27.0), precision))
        TEST_ASSERT(klab::Equals(y[9],  std::complex<klab::DoubleReal>( 25.0,  30.0), precision))
        TEST_ASSERT(klab::Equals(y[10], std::complex<klab::DoubleReal>(-27.5, -33.0), precision))
        TEST_ASSERT(klab::Equals(y[11], std::complex<klab::DoubleReal>( 30.0,  36.0), precision))
        TEST_ASSERT(klab::Equals(y[12], std::complex<klab::DoubleReal>( 32.5,  39.0), precision))
        TEST_ASSERT(klab::Equals(y[13], std::complex<klab::DoubleReal>( 35.0,  42.0), precision))
        TEST_ASSERT(klab::Equals(y[14], std::complex<klab::DoubleReal>(-37.5, -45.0), precision))
        TEST_ASSERT(klab::Equals(y[15], std::complex<klab::DoubleReal>(-40.0, -48.0), precision))


        // Limit cases.
        TScalarOperator<std::complex<klab::DoubleReal> > op0(n, std::complex<klab::DoubleReal>(0.0, 0.0));
        op0.applyAdjoint(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[1],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[2],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[3],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[4],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[5],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[6],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[7],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[8],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[9],  std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[10], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[11], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[12], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[13], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[14], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[15], std::complex<klab::DoubleReal>(0.0, 0.0), precision))

        TScalarOperator<std::complex<klab::DoubleReal> > op1(n, std::complex<klab::DoubleReal>(1.0, 0.0));
        op1.applyAdjoint(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  x[0], precision))
        TEST_ASSERT(klab::Equals(y[1],  x[1], precision))
        TEST_ASSERT(klab::Equals(y[2],  x[2], precision))
        TEST_ASSERT(klab::Equals(y[3],  x[3], precision))
        TEST_ASSERT(klab::Equals(y[4],  x[4], precision))
        TEST_ASSERT(klab::Equals(y[5],  x[5], precision))
        TEST_ASSERT(klab::Equals(y[6],  x[6], precision))
        TEST_ASSERT(klab::Equals(y[7],  x[7], precision))
        TEST_ASSERT(klab::Equals(y[8],  x[8], precision))
        TEST_ASSERT(klab::Equals(y[9],  x[9], precision))
        TEST_ASSERT(klab::Equals(y[10], x[10], precision))
        TEST_ASSERT(klab::Equals(y[11], x[11], precision))
        TEST_ASSERT(klab::Equals(y[12], x[12], precision))
        TEST_ASSERT(klab::Equals(y[13], x[13], precision))
        TEST_ASSERT(klab::Equals(y[14], x[14], precision))
        TEST_ASSERT(klab::Equals(y[15], x[15], precision))

        TScalarOperator<std::complex<klab::DoubleReal> > opm1(n, std::complex<klab::DoubleReal>(-1.0, 0.0));
        opm1.applyAdjoint(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  -x[0], precision))
        TEST_ASSERT(klab::Equals(y[1],  -x[1], precision))
        TEST_ASSERT(klab::Equals(y[2],  -x[2], precision))
        TEST_ASSERT(klab::Equals(y[3],  -x[3], precision))
        TEST_ASSERT(klab::Equals(y[4],  -x[4], precision))
        TEST_ASSERT(klab::Equals(y[5],  -x[5], precision))
        TEST_ASSERT(klab::Equals(y[6],  -x[6], precision))
        TEST_ASSERT(klab::Equals(y[7],  -x[7], precision))
        TEST_ASSERT(klab::Equals(y[8],  -x[8], precision))
        TEST_ASSERT(klab::Equals(y[9],  -x[9], precision))
        TEST_ASSERT(klab::Equals(y[10], -x[10], precision))
        TEST_ASSERT(klab::Equals(y[11], -x[11], precision))
        TEST_ASSERT(klab::Equals(y[12], -x[12], precision))
        TEST_ASSERT(klab::Equals(y[13], -x[13], precision))
        TEST_ASSERT(klab::Equals(y[14], -x[14], precision))
        TEST_ASSERT(klab::Equals(y[15], -x[15], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        TScalarOperator<klab::DoubleReal> op(n, 1.2345);

        arma::Mat<klab::DoubleReal> A(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col(n);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.apply(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<klab::DoubleReal> B(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> out;
            op.column(i, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                B(j, i) = out[j];
        }


        bool equals = true;
        for(klab::UInt32 i=0; i<m && equals; ++i)
        {
            for(klab::UInt32 j=0; j<n && equals; ++j)
                equals = klab::Equals(A(i, j), B(i, j), precision);
        }

        TEST_ASSERT(equals)


        // Limit cases.
        arma::Col<klab::DoubleReal> out;

        try                                     {op.column(n, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.column(n+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testColumn_Complex()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        TScalarOperator<std::complex<klab::DoubleReal> > op(n, std::complex<klab::DoubleReal>(1.2345, -9.8765));

        arma::Mat<std::complex<klab::DoubleReal> > A(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col(n);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<std::complex<klab::DoubleReal> > out;
            op.apply(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<std::complex<klab::DoubleReal> > B(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > out;
            op.column(i, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                B(j, i) = out[j];
        }


        bool equals = true;
        for(klab::UInt32 i=0; i<m && equals; ++i)
        {
            for(klab::UInt32 j=0; j<n && equals; ++j)
                equals = klab::Equals(A(i, j), B(i, j), precision);
        }

        TEST_ASSERT(equals)


        // Limit cases.
        arma::Col<std::complex<klab::DoubleReal> > out;

        try                                     {op.column(n, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.column(n+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        TScalarOperator<klab::DoubleReal> op(n, 1.2345);

        arma::Mat<klab::DoubleReal> A(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> col(m);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.applyAdjoint(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<klab::DoubleReal> B(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> out;
            op.columnAdjoint(i, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                B(j, i) = out[j];
        }


        bool equals = true;
        for(klab::UInt32 i=0; i<n && equals; ++i)
        {
            for(klab::UInt32 j=0; j<m && equals; ++j)
                equals = klab::Equals(A(i, j), B(i, j), precision);
        }

        TEST_ASSERT(equals)


        // Limit cases.
        arma::Col<klab::DoubleReal> out;

        try                                     {op.columnAdjoint(m, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.columnAdjoint(m+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalarOperatorUnitTest::testColumnAdjoint_Complex()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        TScalarOperator<std::complex<klab::DoubleReal> > op(n, std::complex<klab::DoubleReal>(1.2345, -9.8765));

        arma::Mat<std::complex<klab::DoubleReal> > A(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col(m);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<std::complex<klab::DoubleReal> > out;
            op.applyAdjoint(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<std::complex<klab::DoubleReal> > B(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > out;
            op.columnAdjoint(i, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                B(j, i) = out[j];
        }


        bool equals = true;
        for(klab::UInt32 i=0; i<n && equals; ++i)
        {
            for(klab::UInt32 j=0; j<m && equals; ++j)
                equals = klab::Equals(A(i, j), B(i, j), precision);
        }

        TEST_ASSERT(equals)


        // Limit cases.
        arma::Col<std::complex<klab::DoubleReal> > out;

        try                                     {op.columnAdjoint(m, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.columnAdjoint(m+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
