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

#include "OperatorUnitTest.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KOperatorUnitTest::KOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KOperatorUnitTest::testDefaultConstructor)  
    TEST_ADD(KOperatorUnitTest::testNConstructor)  
    TEST_ADD(KOperatorUnitTest::testMNConstructor)  
    TEST_ADD(KOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KOperatorUnitTest::testCountRows)
    TEST_ADD(KOperatorUnitTest::testCountColumns)
    TEST_ADD(KOperatorUnitTest::testM)
    TEST_ADD(KOperatorUnitTest::testN)
    TEST_ADD(KOperatorUnitTest::testIsZero)
    TEST_ADD(KOperatorUnitTest::testSum)
    TEST_ADD(KOperatorUnitTest::testNormFrobenius)
    TEST_ADD(KOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KOperatorUnitTest::testMean)
    TEST_ADD(KOperatorUnitTest::testVariance)
    TEST_ADD(KOperatorUnitTest::testStandardDeviation)
    TEST_ADD(KOperatorUnitTest::testApply)
    TEST_ADD(KOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KOperatorUnitTest::testColumn)
    TEST_ADD(KOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KOperatorUnitTest::testToMatrix)
    TEST_ADD(KOperatorUnitTest::testToMatrixAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KOperatorUnitTest::~KOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testDefaultConstructor()
{
    try
    {
        TTestOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==0 && op.n()==0)
        TEST_ASSERT(op.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testNConstructor()
{
    try
    {
        TTestOperator<klab::DoubleReal> op(16);
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(op.isZero() == false)


        // Limit cases.
        TTestOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testMNConstructor()
{
    try
    {
        TTestOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)


        // Limit cases.
        TTestOperator<klab::DoubleReal> op00(0, 0);
        TEST_ASSERT(op00.m()==0 && op00.n()==0)
        TEST_ASSERT(op00.isZero())

        TTestOperator<klab::DoubleReal> op0n(0, 32);
        TEST_ASSERT(op0n.m()==0 && op0n.n()==32)
        TEST_ASSERT(op0n.isZero())

        TTestOperator<klab::DoubleReal> opn0(16, 0);
        TEST_ASSERT(opn0.m()==16 && opn0.n()==0)
        TEST_ASSERT(opn0.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TTestOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==0 && op.n()==0)
        TEST_ASSERT(op.isZero())

        TTestOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.m()==0 && op2.n()==0)
        TEST_ASSERT(op2.isZero())


        TTestOperator<klab::DoubleReal> op3(16, 32);
        TEST_ASSERT(op3.m()==16 && op3.n()==32)
        TEST_ASSERT(op3.isZero() == false)

        TTestOperator<klab::DoubleReal> op4(op3);
        TEST_ASSERT(op4.m()==16 && op4.n()==32)
        TEST_ASSERT(op4.isZero() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testCountRows()
{
    try
    {
        TTestOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.countRows()==16 && op.countColumns()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testCountColumns()
{
    try
    {
        TTestOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.countRows()==16 && op.countColumns()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testM()
{
    try
    {
        TTestOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testN()
{
    try
    {
        TTestOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testIsZero()
{
    try
    {
        TTestOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.isZero() == false)

        TTestOperator<klab::DoubleReal> op00(0, 0);
        TEST_ASSERT(op00.isZero())

        TTestOperator<klab::DoubleReal> op0n(0, 32);
        TEST_ASSERT(op0n.isZero())

        TTestOperator<klab::DoubleReal> opn0(16, 0);
        TEST_ASSERT(opn0.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testSum()
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

        TMatrixOperator<klab::DoubleReal> opA(A);
        klab::DoubleReal sum = opA.sum();
        TEST_ASSERT(klab::Equals(sum, 25.8, precision)) 


        arma::Mat<std::complex<klab::DoubleReal> > B(m, n);
        B(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        B(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        B(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        B(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        B(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        B(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        B(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        B(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        B(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        B(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        B(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        B(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        B(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        B(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        B(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        B(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        B(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        B(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        B(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        B(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        B(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        B(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        B(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        B(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        B(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        B(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        B(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        B(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        B(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        B(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        B(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        B(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        TMatrixOperator<std::complex<klab::DoubleReal> > opB(B);
        std::complex<klab::DoubleReal> csum = opB.sum();
        TEST_ASSERT(klab::Equals(csum, std::complex<klab::DoubleReal>(25.8, 60.0), precision))  


        // Limit cases.
        TMatrixOperator<klab::DoubleReal> op0(arma::Mat<klab::DoubleReal>(0, 0));
        TEST_ASSERT(klab::Equals(op0.sum(), 0.0))

        TMatrixOperator<std::complex<klab::DoubleReal> > cop0(arma::Mat<std::complex<klab::DoubleReal> >(0, 0));
        TEST_ASSERT(klab::Equals(cop0.sum(), std::complex<klab::DoubleReal>(0.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testNormFrobenius()
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

        TMatrixOperator<klab::DoubleReal> opA(A);
        klab::DoubleReal norm = opA.normFrobenius();
        TEST_ASSERT(klab::Equals(norm, 12.29634091915152, precision))


        arma::Mat<std::complex<klab::DoubleReal> > B(m, n);
        B(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        B(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        B(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        B(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        B(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        B(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        B(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        B(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        B(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        B(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        B(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        B(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        B(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        B(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        B(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        B(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        B(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        B(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        B(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        B(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        B(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        B(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        B(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        B(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        B(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        B(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        B(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        B(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        B(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        B(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        B(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        B(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        TMatrixOperator<std::complex<klab::DoubleReal> > opB(B);
        std::complex<klab::DoubleReal> cnorm = opB.normFrobenius();
        TEST_ASSERT(klab::Equals(cnorm, std::complex<klab::DoubleReal>(27.3115360241785, 0.0), precision))


        // Limit cases.
        TMatrixOperator<klab::DoubleReal> op0(arma::Mat<klab::DoubleReal>(0, 0));
        TEST_ASSERT(klab::Equals(op0.normFrobenius(), 0.0))

        TMatrixOperator<std::complex<klab::DoubleReal> > cop0(arma::Mat<std::complex<klab::DoubleReal> >(0, 0));
        TEST_ASSERT(klab::Equals(cop0.normFrobenius(), std::complex<klab::DoubleReal>(0.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testSquaredNormFrobenius()
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

        TMatrixOperator<klab::DoubleReal> opA(A);
        klab::DoubleReal norm = opA.squaredNormFrobenius();
        TEST_ASSERT(klab::Equals(norm, 151.2, precision))


        arma::Mat<std::complex<klab::DoubleReal> > B(m, n);
        B(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        B(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        B(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        B(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        B(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        B(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        B(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        B(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        B(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        B(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        B(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        B(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        B(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        B(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        B(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        B(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        B(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        B(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        B(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        B(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        B(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        B(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        B(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        B(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        B(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        B(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        B(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        B(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        B(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        B(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        B(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        B(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        TMatrixOperator<std::complex<klab::DoubleReal> > opB(B);
        std::complex<klab::DoubleReal> cnorm = opB.squaredNormFrobenius();
        TEST_ASSERT(klab::Equals(cnorm, std::complex<klab::DoubleReal>(745.92, 0.0), precision))


        // Limit cases.
        TMatrixOperator<klab::DoubleReal> op0(arma::Mat<klab::DoubleReal>(0, 0));
        TEST_ASSERT(klab::Equals(op0.squaredNormFrobenius(), 0.0))

        TMatrixOperator<std::complex<klab::DoubleReal> > cop0(arma::Mat<std::complex<klab::DoubleReal> >(0, 0));
        TEST_ASSERT(klab::Equals(cop0.squaredNormFrobenius(), std::complex<klab::DoubleReal>(0.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testMean()
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

        TMatrixOperator<klab::DoubleReal> opA(A);
        klab::DoubleReal mean = opA.mean();
        TEST_ASSERT(klab::Equals(mean, 0.80625, precision)) 


        arma::Mat<std::complex<klab::DoubleReal> > B(m, n);
        B(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        B(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        B(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        B(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        B(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        B(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        B(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        B(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        B(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        B(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        B(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        B(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        B(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        B(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        B(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        B(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        B(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        B(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        B(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        B(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        B(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        B(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        B(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        B(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        B(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        B(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        B(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        B(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        B(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        B(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        B(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        B(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        TMatrixOperator<std::complex<klab::DoubleReal> > opB(B);
        std::complex<klab::DoubleReal> cmean = opB.mean();
        TEST_ASSERT(klab::Equals(cmean, std::complex<klab::DoubleReal>(0.80625, 1.875), precision))   


        // Limit cases.
        TMatrixOperator<klab::DoubleReal> op0(arma::Mat<klab::DoubleReal>(0, 0));
        TEST_ASSERT(klab::Equals(op0.mean(), 0.0))

        TMatrixOperator<std::complex<klab::DoubleReal> > cop0(arma::Mat<std::complex<klab::DoubleReal> >(0, 0));
        TEST_ASSERT(klab::Equals(cop0.mean(), std::complex<klab::DoubleReal>(0.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testVariance()
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

        TMatrixOperator<klab::DoubleReal> opA(A);
        klab::DoubleReal variance = opA.variance();
        TEST_ASSERT(klab::Equals(variance, 4.0749609375, precision))


        arma::Mat<std::complex<klab::DoubleReal> > B(m, n);
        B(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        B(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        B(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        B(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        B(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        B(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        B(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        B(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        B(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        B(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        B(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        B(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        B(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        B(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        B(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        B(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        B(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        B(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        B(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        B(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        B(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        B(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        B(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        B(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        B(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        B(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        B(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        B(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        B(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        B(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        B(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        B(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        TMatrixOperator<std::complex<klab::DoubleReal> > opB(B);
        std::complex<klab::DoubleReal> cvariance = opB.variance();
        TEST_ASSERT(klab::Equals(cvariance, std::complex<klab::DoubleReal>(19.1443359375, 0.0), precision))   


        // Limit cases.
        TMatrixOperator<klab::DoubleReal> op0(arma::Mat<klab::DoubleReal>(0, 0));
        TEST_ASSERT(klab::Equals(op0.variance(), 0.0))

        TMatrixOperator<std::complex<klab::DoubleReal> > cop0(arma::Mat<std::complex<klab::DoubleReal> >(0, 0));
        TEST_ASSERT(klab::Equals(cop0.variance(), std::complex<klab::DoubleReal>(0.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testStandardDeviation()
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

        TMatrixOperator<klab::DoubleReal> opA(A);
        klab::DoubleReal deviation = opA.standardDeviation();
        TEST_ASSERT(klab::Equals(deviation, 2.01865324845551421, precision))


        arma::Mat<std::complex<klab::DoubleReal> > B(m, n);
        B(0, 0) = std::complex<klab::DoubleReal>( 0.0,  0.0);
        B(0, 1) = std::complex<klab::DoubleReal>( 0.1,  1.0);
        B(0, 2) = std::complex<klab::DoubleReal>(-0.2, -2.0);
        B(0, 3) = std::complex<klab::DoubleReal>( 0.3,  3.0);
        B(0, 4) = std::complex<klab::DoubleReal>( 0.4,  4.0);
        B(0, 5) = std::complex<klab::DoubleReal>( 0.5,  5.0);
        B(0, 6) = std::complex<klab::DoubleReal>( 0.6,  6.0);
        B(0, 7) = std::complex<klab::DoubleReal>( 0.7,  7.0);
        B(1, 0) = std::complex<klab::DoubleReal>( 1.0,  0.1);
        B(1, 1) = std::complex<klab::DoubleReal>( 1.1,  1.1);
        B(1, 2) = std::complex<klab::DoubleReal>( 1.2,  2.1);
        B(1, 3) = std::complex<klab::DoubleReal>(-1.3, -3.1);
        B(1, 4) = std::complex<klab::DoubleReal>(-1.4, -4.1);
        B(1, 5) = std::complex<klab::DoubleReal>( 1.5,  5.1);
        B(1, 6) = std::complex<klab::DoubleReal>( 1.6,  6.1);
        B(1, 7) = std::complex<klab::DoubleReal>( 1.7,  7.1);
        B(2, 0) = std::complex<klab::DoubleReal>( 2.0,  0.2);
        B(2, 1) = std::complex<klab::DoubleReal>( 2.1,  1.2);
        B(2, 2) = std::complex<klab::DoubleReal>( 2.2,  2.2);
        B(2, 3) = std::complex<klab::DoubleReal>(-2.3, -3.2);
        B(2, 4) = std::complex<klab::DoubleReal>( 2.4,  4.2);
        B(2, 5) = std::complex<klab::DoubleReal>(-2.5, -5.2);
        B(2, 6) = std::complex<klab::DoubleReal>( 2.6,  6.2);
        B(2, 7) = std::complex<klab::DoubleReal>(-2.7, -7.2);
        B(3, 0) = std::complex<klab::DoubleReal>(-3.0, -0.3);
        B(3, 1) = std::complex<klab::DoubleReal>( 3.1,  1.3);
        B(3, 2) = std::complex<klab::DoubleReal>( 3.2,  2.3);
        B(3, 3) = std::complex<klab::DoubleReal>(-3.3, -3.3);
        B(3, 4) = std::complex<klab::DoubleReal>( 3.4,  4.3);
        B(3, 5) = std::complex<klab::DoubleReal>( 3.5,  5.3);
        B(3, 6) = std::complex<klab::DoubleReal>( 3.6,  6.3);
        B(3, 7) = std::complex<klab::DoubleReal>( 3.7,  7.3);

        TMatrixOperator<std::complex<klab::DoubleReal> > opB(B);
        std::complex<klab::DoubleReal> cdeviation = opB.standardDeviation();
        TEST_ASSERT(klab::Equals(cdeviation, std::complex<klab::DoubleReal>(4.3754240865886365, 0.0), precision))   


        // Limit cases.
        TMatrixOperator<klab::DoubleReal> op0(arma::Mat<klab::DoubleReal>(0, 0));
        TEST_ASSERT(klab::Equals(op0.standardDeviation(), 0.0))

        TMatrixOperator<std::complex<klab::DoubleReal> > cop0(arma::Mat<std::complex<klab::DoubleReal> >(0, 0));
        TEST_ASSERT(klab::Equals(cop0.standardDeviation(), std::complex<klab::DoubleReal>(0.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testApply()
{
    try
    {
        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;


        TTestOperator<klab::DoubleReal> op;
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 1.0))
        TEST_ASSERT(klab::Equals(y[1], 2.0))
        TEST_ASSERT(klab::Equals(y[2], 3.0))
        TEST_ASSERT(klab::Equals(y[3], 4.0))
        TEST_ASSERT(klab::Equals(y[4], 5.0))
        TEST_ASSERT(klab::Equals(y[5], 6.0))
        TEST_ASSERT(klab::Equals(y[6], 7.0))
        TEST_ASSERT(klab::Equals(y[7], 8.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;


        TTestOperator<klab::DoubleReal> op;
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 1.0))
        TEST_ASSERT(klab::Equals(y[1], 2.0))
        TEST_ASSERT(klab::Equals(y[2], 3.0))
        TEST_ASSERT(klab::Equals(y[3], 4.0))
        TEST_ASSERT(klab::Equals(y[4], 5.0))
        TEST_ASSERT(klab::Equals(y[5], 6.0))
        TEST_ASSERT(klab::Equals(y[6], 7.0))
        TEST_ASSERT(klab::Equals(y[7], 8.0))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], 1.0))
        TEST_ASSERT(klab::Equals(xr[1], 2.0))
        TEST_ASSERT(klab::Equals(xr[2], 3.0))
        TEST_ASSERT(klab::Equals(xr[3], 4.0))
        TEST_ASSERT(klab::Equals(xr[4], 5.0))
        TEST_ASSERT(klab::Equals(xr[5], 6.0))
        TEST_ASSERT(klab::Equals(xr[6], 7.0))
        TEST_ASSERT(klab::Equals(xr[7], 8.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        TTestOperator<klab::DoubleReal> op(m, n);

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

void KOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        TTestOperator<klab::DoubleReal> op(m, n);

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

void KOperatorUnitTest::testToMatrix()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        TTestOperator<klab::DoubleReal> op(m, n);

        arma::Mat<klab::DoubleReal> A;
        op.toMatrix(A);
        TEST_ASSERT(A.n_rows==m && A.n_cols==n)

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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorUnitTest::testToMatrixAdjoint()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        TTestOperator<klab::DoubleReal> op(m, n);

        arma::Mat<klab::DoubleReal> A;
        op.toMatrixAdjoint(A);
        TEST_ASSERT(A.n_rows==n && A.n_cols==m)

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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
