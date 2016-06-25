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

#include "DiagonalOperatorUnitTest.h"
#include "../include/DiagonalOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KDiagonalOperatorUnitTest::KDiagonalOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KDiagonalOperatorUnitTest::testDiagonalConstructor)  
    TEST_ADD(KDiagonalOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KDiagonalOperatorUnitTest::testDiagonal)
    TEST_ADD(KDiagonalOperatorUnitTest::testApply)
    TEST_ADD(KDiagonalOperatorUnitTest::testApply_Complex)
    TEST_ADD(KDiagonalOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KDiagonalOperatorUnitTest::testApplyAdjoint_Complex)
    TEST_ADD(KDiagonalOperatorUnitTest::testColumn)
    TEST_ADD(KDiagonalOperatorUnitTest::testColumn_Complex)
    TEST_ADD(KDiagonalOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KDiagonalOperatorUnitTest::testColumnAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KDiagonalOperatorUnitTest::~KDiagonalOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KDiagonalOperatorUnitTest::testDiagonalConstructor()
{
    try
    {
        arma::Col<klab::DoubleReal> diag(8);
        diag[0] = 1.0;
        diag[1] = 2.0;
        diag[2] = 3.0;
        diag[3] = 4.0;
        diag[4] = 5.0;
        diag[5] = 6.0;
        diag[6] = 7.0;
        diag[7] = 8.0;

        arma::Col<std::complex<klab::DoubleReal> > cdiag(8);
        cdiag[0] = std::complex<klab::DoubleReal>(1.0, 8.0);
        cdiag[1] = std::complex<klab::DoubleReal>(2.0, 7.0);
        cdiag[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        cdiag[3] = std::complex<klab::DoubleReal>(4.0, 5.0);
        cdiag[4] = std::complex<klab::DoubleReal>(5.0, 4.0);
        cdiag[5] = std::complex<klab::DoubleReal>(6.0, 3.0);
        cdiag[6] = std::complex<klab::DoubleReal>(7.0, 2.0);
        cdiag[7] = std::complex<klab::DoubleReal>(8.0, 1.0);


        TDiagonalOperator<klab::DoubleReal> op(diag);
        TEST_ASSERT(op.diagonal().n_rows == 8)
        TEST_ASSERT(klab::Equals(op.diagonal()[0], 1.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[1], 2.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[2], 3.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[3], 4.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[4], 5.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[5], 6.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[6], 7.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[7], 8.0))

        TDiagonalOperator<std::complex<klab::DoubleReal> > cop(cdiag);
        TEST_ASSERT(cop.diagonal().n_rows == 8)
        TEST_ASSERT(klab::Equals(cop.diagonal()[0], std::complex<klab::DoubleReal>(1.0, 8.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[1], std::complex<klab::DoubleReal>(2.0, 7.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[2], std::complex<klab::DoubleReal>(3.0, 6.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[3], std::complex<klab::DoubleReal>(4.0, 5.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[4], std::complex<klab::DoubleReal>(5.0, 4.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[5], std::complex<klab::DoubleReal>(6.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[6], std::complex<klab::DoubleReal>(7.0, 2.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[7], std::complex<klab::DoubleReal>(8.0, 1.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDiagonalOperatorUnitTest::testCopyConstructor()
{
    try
    {
        arma::Col<klab::DoubleReal> diag(8);
        diag[0] = 1.0;
        diag[1] = 2.0;
        diag[2] = 3.0;
        diag[3] = 4.0;
        diag[4] = 5.0;
        diag[5] = 6.0;
        diag[6] = 7.0;
        diag[7] = 8.0;

        arma::Col<std::complex<klab::DoubleReal> > cdiag(8);
        cdiag[0] = std::complex<klab::DoubleReal>(1.0, 8.0);
        cdiag[1] = std::complex<klab::DoubleReal>(2.0, 7.0);
        cdiag[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        cdiag[3] = std::complex<klab::DoubleReal>(4.0, 5.0);
        cdiag[4] = std::complex<klab::DoubleReal>(5.0, 4.0);
        cdiag[5] = std::complex<klab::DoubleReal>(6.0, 3.0);
        cdiag[6] = std::complex<klab::DoubleReal>(7.0, 2.0);
        cdiag[7] = std::complex<klab::DoubleReal>(8.0, 1.0);


        TDiagonalOperator<klab::DoubleReal> op(diag);
        TEST_ASSERT(op.diagonal().n_rows == 8)
        TEST_ASSERT(klab::Equals(op.diagonal()[0], 1.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[1], 2.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[2], 3.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[3], 4.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[4], 5.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[5], 6.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[6], 7.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[7], 8.0))

        TDiagonalOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.diagonal().n_rows == 8)
        TEST_ASSERT(klab::Equals(op2.diagonal()[0], 1.0))
        TEST_ASSERT(klab::Equals(op2.diagonal()[1], 2.0))
        TEST_ASSERT(klab::Equals(op2.diagonal()[2], 3.0))
        TEST_ASSERT(klab::Equals(op2.diagonal()[3], 4.0))
        TEST_ASSERT(klab::Equals(op2.diagonal()[4], 5.0))
        TEST_ASSERT(klab::Equals(op2.diagonal()[5], 6.0))
        TEST_ASSERT(klab::Equals(op2.diagonal()[6], 7.0))
        TEST_ASSERT(klab::Equals(op2.diagonal()[7], 8.0))


        TDiagonalOperator<std::complex<klab::DoubleReal> > cop(cdiag);
        TEST_ASSERT(cop.diagonal().n_rows == 8)
        TEST_ASSERT(klab::Equals(cop.diagonal()[0], std::complex<klab::DoubleReal>(1.0, 8.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[1], std::complex<klab::DoubleReal>(2.0, 7.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[2], std::complex<klab::DoubleReal>(3.0, 6.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[3], std::complex<klab::DoubleReal>(4.0, 5.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[4], std::complex<klab::DoubleReal>(5.0, 4.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[5], std::complex<klab::DoubleReal>(6.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[6], std::complex<klab::DoubleReal>(7.0, 2.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[7], std::complex<klab::DoubleReal>(8.0, 1.0)))

        TDiagonalOperator<std::complex<klab::DoubleReal> > cop2(cop);
        TEST_ASSERT(cop2.diagonal().n_rows == 8)
        TEST_ASSERT(klab::Equals(cop2.diagonal()[0], std::complex<klab::DoubleReal>(1.0, 8.0)))
        TEST_ASSERT(klab::Equals(cop2.diagonal()[1], std::complex<klab::DoubleReal>(2.0, 7.0)))
        TEST_ASSERT(klab::Equals(cop2.diagonal()[2], std::complex<klab::DoubleReal>(3.0, 6.0)))
        TEST_ASSERT(klab::Equals(cop2.diagonal()[3], std::complex<klab::DoubleReal>(4.0, 5.0)))
        TEST_ASSERT(klab::Equals(cop2.diagonal()[4], std::complex<klab::DoubleReal>(5.0, 4.0)))
        TEST_ASSERT(klab::Equals(cop2.diagonal()[5], std::complex<klab::DoubleReal>(6.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop2.diagonal()[6], std::complex<klab::DoubleReal>(7.0, 2.0)))
        TEST_ASSERT(klab::Equals(cop2.diagonal()[7], std::complex<klab::DoubleReal>(8.0, 1.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDiagonalOperatorUnitTest::testDiagonal()
{
    try
    {
        arma::Col<klab::DoubleReal> diag(8);
        diag[0] = 1.0;
        diag[1] = 2.0;
        diag[2] = 3.0;
        diag[3] = 4.0;
        diag[4] = 5.0;
        diag[5] = 6.0;
        diag[6] = 7.0;
        diag[7] = 8.0;

        arma::Col<std::complex<klab::DoubleReal> > cdiag(8);
        cdiag[0] = std::complex<klab::DoubleReal>(1.0, 8.0);
        cdiag[1] = std::complex<klab::DoubleReal>(2.0, 7.0);
        cdiag[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        cdiag[3] = std::complex<klab::DoubleReal>(4.0, 5.0);
        cdiag[4] = std::complex<klab::DoubleReal>(5.0, 4.0);
        cdiag[5] = std::complex<klab::DoubleReal>(6.0, 3.0);
        cdiag[6] = std::complex<klab::DoubleReal>(7.0, 2.0);
        cdiag[7] = std::complex<klab::DoubleReal>(8.0, 1.0);


        TDiagonalOperator<klab::DoubleReal> op(diag);
        TEST_ASSERT(op.diagonal().n_rows == 8)
        TEST_ASSERT(klab::Equals(op.diagonal()[0], 1.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[1], 2.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[2], 3.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[3], 4.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[4], 5.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[5], 6.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[6], 7.0))
        TEST_ASSERT(klab::Equals(op.diagonal()[7], 8.0))

        TDiagonalOperator<std::complex<klab::DoubleReal> > cop(cdiag);
        TEST_ASSERT(cop.diagonal().n_rows == 8)
        TEST_ASSERT(klab::Equals(cop.diagonal()[0], std::complex<klab::DoubleReal>(1.0, 8.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[1], std::complex<klab::DoubleReal>(2.0, 7.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[2], std::complex<klab::DoubleReal>(3.0, 6.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[3], std::complex<klab::DoubleReal>(4.0, 5.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[4], std::complex<klab::DoubleReal>(5.0, 4.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[5], std::complex<klab::DoubleReal>(6.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[6], std::complex<klab::DoubleReal>(7.0, 2.0)))
        TEST_ASSERT(klab::Equals(cop.diagonal()[7], std::complex<klab::DoubleReal>(8.0, 1.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDiagonalOperatorUnitTest::testApply()
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

        arma::Col<klab::DoubleReal> diag(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag[i] = static_cast<klab::DoubleReal>(n-i);


        TDiagonalOperator<klab::DoubleReal> op(diag);
        op.apply(x, y);

        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],   16.0, precision))
        TEST_ASSERT(klab::Equals(y[1],  -30.0, precision))
        TEST_ASSERT(klab::Equals(y[2],   42.0, precision))
        TEST_ASSERT(klab::Equals(y[3],  -52.0, precision))
        TEST_ASSERT(klab::Equals(y[4],   60.0, precision))
        TEST_ASSERT(klab::Equals(y[5],   66.0, precision))
        TEST_ASSERT(klab::Equals(y[6],  -70.0, precision))
        TEST_ASSERT(klab::Equals(y[7],  -72.0, precision))
        TEST_ASSERT(klab::Equals(y[8],  -72.0, precision))
        TEST_ASSERT(klab::Equals(y[9],   70.0, precision))
        TEST_ASSERT(klab::Equals(y[10], -66.0, precision))
        TEST_ASSERT(klab::Equals(y[11],  60.0, precision))
        TEST_ASSERT(klab::Equals(y[12],  52.0, precision))
        TEST_ASSERT(klab::Equals(y[13],  42.0, precision))
        TEST_ASSERT(klab::Equals(y[14], -30.0, precision))
        TEST_ASSERT(klab::Equals(y[15], -16.0, precision))


        // Limit cases.
        try                                         {op.apply(arma::Col<klab::DoubleReal>(15), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}


        arma::Col<klab::DoubleReal> diag0(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag0[i] = 0.0;

        TDiagonalOperator<klab::DoubleReal> op0(diag0);
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

        arma::Col<klab::DoubleReal> diag1(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag1[i] = 1.0;

        TDiagonalOperator<klab::DoubleReal> op1(diag1);
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

        arma::Col<klab::DoubleReal> diagm1(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diagm1[i] = -1.0;

        TDiagonalOperator<klab::DoubleReal> opm1(diagm1);
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

void KDiagonalOperatorUnitTest::testApply_Complex()
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

        arma::Col<std::complex<klab::DoubleReal> > diag(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag[i] = std::complex<klab::DoubleReal>(static_cast<klab::DoubleReal>(n-i), static_cast<klab::DoubleReal>(i));


        TDiagonalOperator<std::complex<klab::DoubleReal> > op(diag);
        op.apply(x, y);

        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  std::complex<klab::DoubleReal>( 16.0,  0.0), precision))
        TEST_ASSERT(klab::Equals(y[1],  std::complex<klab::DoubleReal>(-30.0, -2.0), precision))
        TEST_ASSERT(klab::Equals(y[2],  std::complex<klab::DoubleReal>( 42.0,  6.0), precision))
        TEST_ASSERT(klab::Equals(y[3],  std::complex<klab::DoubleReal>(-52.0, -12.0), precision))
        TEST_ASSERT(klab::Equals(y[4],  std::complex<klab::DoubleReal>( 60.0,  20.0), precision))
        TEST_ASSERT(klab::Equals(y[5],  std::complex<klab::DoubleReal>( 66.0,  30.0), precision))
        TEST_ASSERT(klab::Equals(y[6],  std::complex<klab::DoubleReal>(-70.0, -42.0), precision))
        TEST_ASSERT(klab::Equals(y[7],  std::complex<klab::DoubleReal>(-72.0, -56.0), precision))
        TEST_ASSERT(klab::Equals(y[8],  std::complex<klab::DoubleReal>(-72.0, -72.0), precision))
        TEST_ASSERT(klab::Equals(y[9],  std::complex<klab::DoubleReal>( 70.0,  90.0), precision))
        TEST_ASSERT(klab::Equals(y[10], std::complex<klab::DoubleReal>(-66.0, -110.0), precision))
        TEST_ASSERT(klab::Equals(y[11], std::complex<klab::DoubleReal>( 60.0,  132.0), precision))
        TEST_ASSERT(klab::Equals(y[12], std::complex<klab::DoubleReal>( 52.0,  156.0), precision))
        TEST_ASSERT(klab::Equals(y[13], std::complex<klab::DoubleReal>( 42.0,  182.0), precision))
        TEST_ASSERT(klab::Equals(y[14], std::complex<klab::DoubleReal>(-30.0, -210.0), precision))
        TEST_ASSERT(klab::Equals(y[15], std::complex<klab::DoubleReal>(-16.0, -240.0), precision))


        // Limit cases.
        try                                         {op.apply(arma::Col<std::complex<klab::DoubleReal> >(15), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}


        arma::Col<std::complex<klab::DoubleReal> > diag0(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag0[i] = std::complex<klab::DoubleReal>(0.0, 0.0);

        TDiagonalOperator<std::complex<klab::DoubleReal> > op0(diag0);
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

        arma::Col<std::complex<klab::DoubleReal> > diag1(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag1[i] = std::complex<klab::DoubleReal>(1.0, 0.0);

        TDiagonalOperator<std::complex<klab::DoubleReal> > op1(diag1);
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

        arma::Col<std::complex<klab::DoubleReal> > diagm1(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diagm1[i] = std::complex<klab::DoubleReal>(-1.0, 0.0);

        TDiagonalOperator<std::complex<klab::DoubleReal> > opm1(diagm1);
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

void KDiagonalOperatorUnitTest::testApplyAdjoint()
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

        arma::Col<klab::DoubleReal> diag(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag[i] = static_cast<klab::DoubleReal>(n-i);


        TDiagonalOperator<klab::DoubleReal> op(diag);
        op.applyAdjoint(x, y);

        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],   16.0, precision))
        TEST_ASSERT(klab::Equals(y[1],  -30.0, precision))
        TEST_ASSERT(klab::Equals(y[2],   42.0, precision))
        TEST_ASSERT(klab::Equals(y[3],  -52.0, precision))
        TEST_ASSERT(klab::Equals(y[4],   60.0, precision))
        TEST_ASSERT(klab::Equals(y[5],   66.0, precision))
        TEST_ASSERT(klab::Equals(y[6],  -70.0, precision))
        TEST_ASSERT(klab::Equals(y[7],  -72.0, precision))
        TEST_ASSERT(klab::Equals(y[8],  -72.0, precision))
        TEST_ASSERT(klab::Equals(y[9],   70.0, precision))
        TEST_ASSERT(klab::Equals(y[10], -66.0, precision))
        TEST_ASSERT(klab::Equals(y[11],  60.0, precision))
        TEST_ASSERT(klab::Equals(y[12],  52.0, precision))
        TEST_ASSERT(klab::Equals(y[13],  42.0, precision))
        TEST_ASSERT(klab::Equals(y[14], -30.0, precision))
        TEST_ASSERT(klab::Equals(y[15], -16.0, precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(15), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}


        arma::Col<klab::DoubleReal> diag0(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag0[i] = 0.0;

        TDiagonalOperator<klab::DoubleReal> op0(diag0);
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

        arma::Col<klab::DoubleReal> diag1(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag1[i] = 1.0;

        TDiagonalOperator<klab::DoubleReal> op1(diag1);
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

        arma::Col<klab::DoubleReal> diagm1(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diagm1[i] = -1.0;

        TDiagonalOperator<klab::DoubleReal> opm1(diagm1);
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

void KDiagonalOperatorUnitTest::testApplyAdjoint_Complex()
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

        arma::Col<std::complex<klab::DoubleReal> > diag(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag[i] = std::complex<klab::DoubleReal>(static_cast<klab::DoubleReal>(n-i), static_cast<klab::DoubleReal>(i));


        TDiagonalOperator<std::complex<klab::DoubleReal> > op(diag);
        op.applyAdjoint(x, y);

        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  std::complex<klab::DoubleReal>( 16.0, -0.0), precision))
        TEST_ASSERT(klab::Equals(y[1],  std::complex<klab::DoubleReal>(-30.0,  2.0), precision))
        TEST_ASSERT(klab::Equals(y[2],  std::complex<klab::DoubleReal>( 42.0, -6.0), precision))
        TEST_ASSERT(klab::Equals(y[3],  std::complex<klab::DoubleReal>(-52.0,  12.0), precision))
        TEST_ASSERT(klab::Equals(y[4],  std::complex<klab::DoubleReal>( 60.0, -20.0), precision))
        TEST_ASSERT(klab::Equals(y[5],  std::complex<klab::DoubleReal>( 66.0, -30.0), precision))
        TEST_ASSERT(klab::Equals(y[6],  std::complex<klab::DoubleReal>(-70.0,  42.0), precision))
        TEST_ASSERT(klab::Equals(y[7],  std::complex<klab::DoubleReal>(-72.0,  56.0), precision))
        TEST_ASSERT(klab::Equals(y[8],  std::complex<klab::DoubleReal>(-72.0,  72.0), precision))
        TEST_ASSERT(klab::Equals(y[9],  std::complex<klab::DoubleReal>( 70.0, -90.0), precision))
        TEST_ASSERT(klab::Equals(y[10], std::complex<klab::DoubleReal>(-66.0,  110.0), precision))
        TEST_ASSERT(klab::Equals(y[11], std::complex<klab::DoubleReal>( 60.0, -132.0), precision))
        TEST_ASSERT(klab::Equals(y[12], std::complex<klab::DoubleReal>( 52.0, -156.0), precision))
        TEST_ASSERT(klab::Equals(y[13], std::complex<klab::DoubleReal>( 42.0, -182.0), precision))
        TEST_ASSERT(klab::Equals(y[14], std::complex<klab::DoubleReal>(-30.0,  210.0), precision))
        TEST_ASSERT(klab::Equals(y[15], std::complex<klab::DoubleReal>(-16.0,  240.0), precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<std::complex<klab::DoubleReal> >(15), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}


        arma::Col<std::complex<klab::DoubleReal> > diag0(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag0[i] = std::complex<klab::DoubleReal>(0.0, 0.0);

        TDiagonalOperator<std::complex<klab::DoubleReal> > op0(diag0);
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

        arma::Col<std::complex<klab::DoubleReal> > diag1(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diag1[i] = std::complex<klab::DoubleReal>(1.0, 0.0);

        TDiagonalOperator<std::complex<klab::DoubleReal> > op1(diag1);
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

        arma::Col<std::complex<klab::DoubleReal> > diagm1(n);
        for(klab::UInt32 i=0; i<n; ++i)
            diagm1[i] = std::complex<klab::DoubleReal>(-1.0, 0.0);

        TDiagonalOperator<std::complex<klab::DoubleReal> > opm1(diagm1);
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

void KDiagonalOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 


        arma::Col<klab::DoubleReal> diag(n);
        diag[0] = 1.0;
        diag[1] = 2.0;
        diag[2] = 3.0;
        diag[3] = 4.0;
        diag[4] = 5.0;
        diag[5] = 6.0;
        diag[6] = 7.0;
        diag[7] = 8.0;


        TDiagonalOperator<klab::DoubleReal> op(diag);

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

void KDiagonalOperatorUnitTest::testColumn_Complex()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 


        arma::Col<std::complex<klab::DoubleReal> > cdiag(n);
        cdiag[0] = std::complex<klab::DoubleReal>(1.0, 8.0);
        cdiag[1] = std::complex<klab::DoubleReal>(2.0, 7.0);
        cdiag[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        cdiag[3] = std::complex<klab::DoubleReal>(4.0, 5.0);
        cdiag[4] = std::complex<klab::DoubleReal>(5.0, 4.0);
        cdiag[5] = std::complex<klab::DoubleReal>(6.0, 3.0);
        cdiag[6] = std::complex<klab::DoubleReal>(7.0, 2.0);
        cdiag[7] = std::complex<klab::DoubleReal>(8.0, 1.0);


        TDiagonalOperator<std::complex<klab::DoubleReal> > op(cdiag);

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

void KDiagonalOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 


        arma::Col<klab::DoubleReal> diag(n);
        diag[0] = 1.0;
        diag[1] = 2.0;
        diag[2] = 3.0;
        diag[3] = 4.0;
        diag[4] = 5.0;
        diag[5] = 6.0;
        diag[6] = 7.0;
        diag[7] = 8.0;


        TDiagonalOperator<klab::DoubleReal> op(diag);

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

void KDiagonalOperatorUnitTest::testColumnAdjoint_Complex()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12;


        arma::Col<std::complex<klab::DoubleReal> > cdiag(n);
        cdiag[0] = std::complex<klab::DoubleReal>(1.0, 8.0);
        cdiag[1] = std::complex<klab::DoubleReal>(2.0, 7.0);
        cdiag[2] = std::complex<klab::DoubleReal>(3.0, 6.0);
        cdiag[3] = std::complex<klab::DoubleReal>(4.0, 5.0);
        cdiag[4] = std::complex<klab::DoubleReal>(5.0, 4.0);
        cdiag[5] = std::complex<klab::DoubleReal>(6.0, 3.0);
        cdiag[6] = std::complex<klab::DoubleReal>(7.0, 2.0);
        cdiag[7] = std::complex<klab::DoubleReal>(8.0, 1.0);


        TDiagonalOperator<std::complex<klab::DoubleReal> > op(cdiag);

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
