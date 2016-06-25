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

#include "ScalingOperatorUnitTest.h"
#include "../include/ScalingOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KScalingOperatorUnitTest::KScalingOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KScalingOperatorUnitTest::testOpConstructor)  
    TEST_ADD(KScalingOperatorUnitTest::testOpScaleConstructor) 
    TEST_ADD(KScalingOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KScalingOperatorUnitTest::testSetScale)
    TEST_ADD(KScalingOperatorUnitTest::testOp)
    TEST_ADD(KScalingOperatorUnitTest::testScale)
    TEST_ADD(KScalingOperatorUnitTest::testApply)
    TEST_ADD(KScalingOperatorUnitTest::testApply_Complex)
    TEST_ADD(KScalingOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KScalingOperatorUnitTest::testApplyAdjoint_Complex)
    TEST_ADD(KScalingOperatorUnitTest::testColumn)
    TEST_ADD(KScalingOperatorUnitTest::testColumn_Complex)
    TEST_ADD(KScalingOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KScalingOperatorUnitTest::testColumnAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KScalingOperatorUnitTest::~KScalingOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testOpConstructor()
{
    try
    {
        TScalingOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(klab::Equals(op.scale(), 1.0))

        TScalingOperator<std::complex<klab::DoubleReal> > op2(new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(4, 8)));
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(1.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testOpScaleConstructor()
{
    try
    {
        TScalingOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0.5);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(klab::Equals(op.scale(), 0.5))

        TScalingOperator<std::complex<klab::DoubleReal> > op2(new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(4, 8)), std::complex<klab::DoubleReal>(0.5, 2.0));
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.5, 2.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
} 

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TScalingOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0.5);
        TScalingOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==4 && opCopy.n()==8)
        TEST_ASSERT(klab::Equals(opCopy.scale(), 0.5))

        TScalingOperator<std::complex<klab::DoubleReal> > op2(new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(4, 8)), std::complex<klab::DoubleReal>(0.5, 2.0));
        TScalingOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.m()==4 && op2Copy.n()==8)
        TEST_ASSERT(klab::Equals(op2Copy.scale(), std::complex<klab::DoubleReal>(0.5, 2.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testSetScale()
{
    try
    {
        TScalingOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(klab::Equals(op.scale(), 1.0))

        op.setScale(0.5);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(klab::Equals(op.scale(), 0.5))


        TScalingOperator<std::complex<klab::DoubleReal> > op2(new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(4, 8)));
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(1.0, 0.0)))

        op2.setScale(std::complex<klab::DoubleReal>(0.5, 2.0));
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.5, 2.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testOp()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr2 = new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(4, 8));

        TScalingOperator<klab::DoubleReal> op(optr);
        TEST_ASSERT(op.op() == optr)

        TScalingOperator<std::complex<klab::DoubleReal> > op2(optr2);
        TEST_ASSERT(op2.op() == optr2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testScale()
{
    try
    {
        TScalingOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(klab::Equals(op.scale(), 1.0))

        op.setScale(0.5);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(klab::Equals(op.scale(), 0.5))


        TScalingOperator<std::complex<klab::DoubleReal> > op2(new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(4, 8)));
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(1.0, 0.0)))

        op2.setScale(std::complex<klab::DoubleReal>(0.5, 2.0));
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.5, 2.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testApply()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> A(m, n);
        A(0, 0) =  0.0;
        A(0, 1) =  0.1;
        A(0, 2) = -0.2;
        A(0, 3) =  0.3;
        A(0, 4) =  0.4;
        A(0, 5) =  0.5;
        A(0, 6) =  0.6;
        A(0, 7) =  0.7;
        A(1, 0) =  1.0;
        A(1, 1) =  1.1;
        A(1, 2) =  1.2;
        A(1, 3) = -1.3;
        A(1, 4) = -1.4;
        A(1, 5) =  1.5;
        A(1, 6) =  1.6;
        A(1, 7) =  1.7;
        A(2, 0) =  2.0;
        A(2, 1) =  2.1;
        A(2, 2) =  2.2;
        A(2, 3) = -2.3;
        A(2, 4) =  2.4;
        A(2, 5) = -2.5;
        A(2, 6) =  2.6;
        A(2, 7) = -2.7;
        A(3, 0) = -3.0;
        A(3, 1) =  3.1;
        A(3, 2) =  3.2;
        A(3, 3) = -3.3;
        A(3, 4) =  3.4;
        A(3, 5) =  3.5;
        A(3, 6) =  3.6;
        A(3, 7) =  3.7;

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);
        TScalingOperator<klab::DoubleReal> op(optr, 0.5);

        arma::Col<klab::DoubleReal> x(n);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        arma::Col<klab::DoubleReal> y;
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0],  7.8, precision))
        TEST_ASSERT(klab::Equals(y[1],  14.2, precision))
        TEST_ASSERT(klab::Equals(y[2], -1.4, precision))
        TEST_ASSERT(klab::Equals(y[3],  46.2, precision))

        
        // Limit cases.
        TScalingOperator<klab::DoubleReal> op0(optr, 0.0);
        op0.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > A(m, n);
        A(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        A(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        A(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        A(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        A(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        A(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        A(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        A(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        A(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        A(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        A(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        A(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        A(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        A(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        A(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        A(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        A(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        A(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        A(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        A(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        A(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        A(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        A(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        A(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        A(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        A(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        A(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        A(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        A(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        A(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        A(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        A(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr = new TMatrixOperator<std::complex<klab::DoubleReal> >(A);
        TScalingOperator<std::complex<klab::DoubleReal> > op(optr, 0.5);

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = std::complex<klab::DoubleReal>(static_cast<klab::DoubleReal>(i+1), static_cast<klab::DoubleReal>(n-i));

        arma::Col<std::complex<klab::DoubleReal> > y;
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(-22.2, 81.0), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>( 2.3,  63.0), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(-8.2,  4.5), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>( 17.7, 93.6), precision))

        
        // Limit cases.
        TScalingOperator<std::complex<klab::DoubleReal> > op0(optr, std::complex<klab::DoubleReal>(0.0, 0.0));
        op0.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> A(m, n);
        A(0, 0) =  0.0;
        A(0, 1) =  0.1;
        A(0, 2) = -0.2;
        A(0, 3) =  0.3;
        A(0, 4) =  0.4;
        A(0, 5) =  0.5;
        A(0, 6) =  0.6;
        A(0, 7) =  0.7;
        A(1, 0) =  1.0;
        A(1, 1) =  1.1;
        A(1, 2) =  1.2;
        A(1, 3) = -1.3;
        A(1, 4) = -1.4;
        A(1, 5) =  1.5;
        A(1, 6) =  1.6;
        A(1, 7) =  1.7;
        A(2, 0) =  2.0;
        A(2, 1) =  2.1;
        A(2, 2) =  2.2;
        A(2, 3) = -2.3;
        A(2, 4) =  2.4;
        A(2, 5) = -2.5;
        A(2, 6) =  2.6;
        A(2, 7) = -2.7;
        A(3, 0) = -3.0;
        A(3, 1) =  3.1;
        A(3, 2) =  3.2;
        A(3, 3) = -3.3;
        A(3, 4) =  3.4;
        A(3, 5) =  3.5;
        A(3, 6) =  3.6;
        A(3, 7) =  3.7;

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);
        TScalingOperator<klab::DoubleReal> op(optr, 0.5);

        arma::Col<klab::DoubleReal> x(n);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        arma::Col<klab::DoubleReal> y;
        op.apply(x, y);

        arma::Col<klab::DoubleReal> xr;
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], -63.6, precision))
        TEST_ASSERT(klab::Equals(xr[1],  78.34, precision))
        TEST_ASSERT(klab::Equals(xr[2],  80.12, precision))
        TEST_ASSERT(klab::Equals(xr[3], -82.68, precision))
        TEST_ASSERT(klab::Equals(xr[4],  68.48, precision))
        TEST_ASSERT(klab::Equals(xr[5],  95.2, precision))
        TEST_ASSERT(klab::Equals(xr[6],  95.04, precision))
        TEST_ASSERT(klab::Equals(xr[7],  102.16, precision))

        
        // Limit cases.
        TScalingOperator<klab::DoubleReal> op0(optr, 0.0);
        op0.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > A(m, n);
        A(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        A(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        A(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        A(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        A(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        A(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        A(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        A(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        A(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        A(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        A(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        A(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        A(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        A(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        A(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        A(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        A(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        A(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        A(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        A(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        A(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        A(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        A(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        A(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        A(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        A(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        A(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        A(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        A(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        A(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        A(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        A(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr = new TMatrixOperator<std::complex<klab::DoubleReal> >(A);
        TScalingOperator<std::complex<klab::DoubleReal> > op(optr, 0.5);

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = std::complex<klab::DoubleReal>(static_cast<klab::DoubleReal>(i+1), static_cast<klab::DoubleReal>(n-i));

        arma::Col<std::complex<klab::DoubleReal> > y;
        op.apply(x, y);

        arma::Col<std::complex<klab::DoubleReal> > xr;
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], std::complex<klab::DoubleReal>(-44.04, -101.04), precision))
        TEST_ASSERT(klab::Equals(xr[1], std::complex<klab::DoubleReal>( 157.67,  191.755), precision))
        TEST_ASSERT(klab::Equals(xr[2], std::complex<klab::DoubleReal>( 120.64,  148.46), precision))
        TEST_ASSERT(klab::Equals(xr[3], std::complex<klab::DoubleReal>(-162.39, -135.465), precision))
        TEST_ASSERT(klab::Equals(xr[4], std::complex<klab::DoubleReal>( 257.74,  164.90), precision))
        TEST_ASSERT(klab::Equals(xr[5], std::complex<klab::DoubleReal>( 636.89,  207.085), precision))
        TEST_ASSERT(klab::Equals(xr[6], std::complex<klab::DoubleReal>( 760.32,  278.28), precision))
        TEST_ASSERT(klab::Equals(xr[7], std::complex<klab::DoubleReal>( 870.59,  224.395), precision))

        
        // Limit cases.
        TScalingOperator<std::complex<klab::DoubleReal> > op0(optr, std::complex<klab::DoubleReal>(0.0, 0.0));
        op0.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xr[1], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xr[2], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xr[3], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xr[4], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xr[5], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xr[6], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(xr[7], std::complex<klab::DoubleReal>(0.0, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> A(m, n);
        A(0, 0) =  0.0;
        A(0, 1) =  0.1;
        A(0, 2) = -0.2;
        A(0, 3) =  0.3;
        A(0, 4) =  0.4;
        A(0, 5) =  0.5;
        A(0, 6) =  0.6;
        A(0, 7) =  0.7;
        A(1, 0) =  1.0;
        A(1, 1) =  1.1;
        A(1, 2) =  1.2;
        A(1, 3) = -1.3;
        A(1, 4) = -1.4;
        A(1, 5) =  1.5;
        A(1, 6) =  1.6;
        A(1, 7) =  1.7;
        A(2, 0) =  2.0;
        A(2, 1) =  2.1;
        A(2, 2) =  2.2;
        A(2, 3) = -2.3;
        A(2, 4) =  2.4;
        A(2, 5) = -2.5;
        A(2, 6) =  2.6;
        A(2, 7) = -2.7;
        A(3, 0) = -3.0;
        A(3, 1) =  3.1;
        A(3, 2) =  3.2;
        A(3, 3) = -3.3;
        A(3, 4) =  3.4;
        A(3, 5) =  3.5;
        A(3, 6) =  3.6;
        A(3, 7) =  3.7;

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);

        TScalingOperator<klab::DoubleReal> op(optr, 0.5);

        arma::Mat<klab::DoubleReal> A2(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col(n);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.apply(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A2(j, i) = out[j];
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
                equals = klab::Equals(A2(i, j), B(i, j), precision);
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


        TScalingOperator<klab::DoubleReal> op0(0);
        try                                     {op0.column(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testColumn_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > A(m, n);
        A(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        A(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        A(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        A(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        A(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        A(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        A(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        A(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        A(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        A(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        A(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        A(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        A(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        A(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        A(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        A(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        A(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        A(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        A(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        A(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        A(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        A(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        A(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        A(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        A(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        A(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        A(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        A(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        A(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        A(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        A(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        A(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr = new TMatrixOperator<std::complex<klab::DoubleReal> >(A);

        TScalingOperator<std::complex<klab::DoubleReal> > op(optr, 0.5);

        arma::Mat<std::complex<klab::DoubleReal> > A2(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col(n);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<std::complex<klab::DoubleReal> > out;
            op.apply(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A2(j, i) = out[j];
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
                equals = klab::Equals(A2(i, j), B(i, j), precision);
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


        TScalingOperator<std::complex<klab::DoubleReal> > op0(0);
        try                                     {op0.column(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> A(m, n);
        A(0, 0) =  0.0;
        A(0, 1) =  0.1;
        A(0, 2) = -0.2;
        A(0, 3) =  0.3;
        A(0, 4) =  0.4;
        A(0, 5) =  0.5;
        A(0, 6) =  0.6;
        A(0, 7) =  0.7;
        A(1, 0) =  1.0;
        A(1, 1) =  1.1;
        A(1, 2) =  1.2;
        A(1, 3) = -1.3;
        A(1, 4) = -1.4;
        A(1, 5) =  1.5;
        A(1, 6) =  1.6;
        A(1, 7) =  1.7;
        A(2, 0) =  2.0;
        A(2, 1) =  2.1;
        A(2, 2) =  2.2;
        A(2, 3) = -2.3;
        A(2, 4) =  2.4;
        A(2, 5) = -2.5;
        A(2, 6) =  2.6;
        A(2, 7) = -2.7;
        A(3, 0) = -3.0;
        A(3, 1) =  3.1;
        A(3, 2) =  3.2;
        A(3, 3) = -3.3;
        A(3, 4) =  3.4;
        A(3, 5) =  3.5;
        A(3, 6) =  3.6;
        A(3, 7) =  3.7;

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);

        TScalingOperator<klab::DoubleReal> op(optr, 0.5);

        arma::Mat<klab::DoubleReal> A2(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> col(m);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.applyAdjoint(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A2(j, i) = out[j];
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
                equals = klab::Equals(A2(i, j), B(i, j), precision);
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


        TScalingOperator<klab::DoubleReal> op0(0);
        try                                     {op0.columnAdjoint(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScalingOperatorUnitTest::testColumnAdjoint_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > A(m, n);
        A(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        A(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        A(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        A(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        A(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        A(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        A(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        A(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        A(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        A(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        A(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        A(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        A(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        A(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        A(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        A(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        A(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        A(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        A(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        A(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        A(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        A(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        A(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        A(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        A(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        A(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        A(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        A(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        A(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        A(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        A(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        A(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr = new TMatrixOperator<std::complex<klab::DoubleReal> >(A);

        TScalingOperator<std::complex<klab::DoubleReal> > op(optr, 0.5);

        arma::Mat<std::complex<klab::DoubleReal> > A2(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col(m);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<std::complex<klab::DoubleReal> > out;
            op.applyAdjoint(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A2(j, i) = out[j];
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
                equals = klab::Equals(A2(i, j), B(i, j), precision);
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


        TScalingOperator<std::complex<klab::DoubleReal> > op0(0);
        try                                     {op0.columnAdjoint(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
