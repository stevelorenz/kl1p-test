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

#include "AdjointOperatorUnitTest.h"
#include "../include/AdjointOperator.h"
#include "../include/MatrixOperator.h"
#include "../include/ZeroOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KAdjointOperatorUnitTest::KAdjointOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KAdjointOperatorUnitTest::testOpConstructor)  
    TEST_ADD(KAdjointOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KAdjointOperatorUnitTest::testOp)
    TEST_ADD(KAdjointOperatorUnitTest::testIsZero)
    TEST_ADD(KAdjointOperatorUnitTest::testSum)
    TEST_ADD(KAdjointOperatorUnitTest::testNormFrobenius)
    TEST_ADD(KAdjointOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KAdjointOperatorUnitTest::testMean)
    TEST_ADD(KAdjointOperatorUnitTest::testVariance)
    TEST_ADD(KAdjointOperatorUnitTest::testApply)
    TEST_ADD(KAdjointOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KAdjointOperatorUnitTest::testColumn)
    TEST_ADD(KAdjointOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KAdjointOperatorUnitTest::~KAdjointOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testOpConstructor()
{
    try
    {
        TAdjointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.op().get() != 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TAdjointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.op().get() != 0)

        TAdjointOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.op().get()!=0 && op2.op().get()==op.op().get())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testOp()
{
    try
    {
        TAdjointOperator<klab::DoubleReal> op(0);
        TEST_ASSERT(op.op() == 0)
        
        TAdjointOperator<klab::DoubleReal> op2(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op2.op() != 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testIsZero()
{
    try
    {
        arma::Mat<klab::DoubleReal> mat(4, 8);
        mat.fill(1.0);

        TAdjointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(mat));
        TEST_ASSERT(op.isZero() == false)

        TAdjointOperator<klab::DoubleReal> op2(new TZeroOperator<klab::DoubleReal>(4, 8));
        TEST_ASSERT(op2.isZero())


        // Limit cases.
        TAdjointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testSum()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        klab::TSmartPointer<TOperator<klab::DoubleReal> > opMat = new TMatrixOperator<klab::DoubleReal>(matrix);
        TAdjointOperator<klab::DoubleReal> op(opMat);
        TEST_ASSERT(klab::Equals(op.sum(), opMat->sum()))


        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TAdjointOperator<std::complex<klab::DoubleReal> > cop(copMat);
        TEST_ASSERT(klab::Equals(cop.sum(), klab::Conj(copMat->sum())))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testNormFrobenius()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        klab::TSmartPointer<TOperator<klab::DoubleReal> > opMat = new TMatrixOperator<klab::DoubleReal>(matrix);
        TAdjointOperator<klab::DoubleReal> op(opMat);
        TEST_ASSERT(klab::Equals(op.normFrobenius(), opMat->normFrobenius(), 1e-6))


        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TAdjointOperator<std::complex<klab::DoubleReal> > cop(copMat);
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), copMat->normFrobenius()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testSquaredNormFrobenius()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        klab::TSmartPointer<TOperator<klab::DoubleReal> > opMat = new TMatrixOperator<klab::DoubleReal>(matrix);
        TAdjointOperator<klab::DoubleReal> op(opMat);
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), opMat->squaredNormFrobenius()))


        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TAdjointOperator<std::complex<klab::DoubleReal> > cop(copMat);
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), copMat->squaredNormFrobenius()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testMean()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        klab::TSmartPointer<TOperator<klab::DoubleReal> > opMat = new TMatrixOperator<klab::DoubleReal>(matrix);
        TAdjointOperator<klab::DoubleReal> op(opMat);
        TEST_ASSERT(klab::Equals(op.mean(), opMat->mean()))


        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TAdjointOperator<std::complex<klab::DoubleReal> > cop(copMat);
        TEST_ASSERT(klab::Equals(cop.mean(), klab::Conj(copMat->mean())))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testVariance()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        klab::TSmartPointer<TOperator<klab::DoubleReal> > opMat = new TMatrixOperator<klab::DoubleReal>(matrix);
        TAdjointOperator<klab::DoubleReal> op(opMat);
        TEST_ASSERT(klab::Equals(op.variance(), opMat->variance()))


        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix(0, 0) = std::complex<klab::DoubleReal>(1.0, 32.0);
        cmatrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        cmatrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        cmatrix(0, 3) = std::complex<klab::DoubleReal>(4.0, 29.0);
        cmatrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        cmatrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        cmatrix(0, 6) = std::complex<klab::DoubleReal>(7.0, 26.0);
        cmatrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        cmatrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        cmatrix(1, 1) = std::complex<klab::DoubleReal>(10.0, 23.0);
        cmatrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        cmatrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        cmatrix(1, 4) = std::complex<klab::DoubleReal>(13.0, 20.0);
        cmatrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        cmatrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        cmatrix(1, 7) = std::complex<klab::DoubleReal>(16.0, 17.0);
        cmatrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        cmatrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        cmatrix(2, 2) = std::complex<klab::DoubleReal>(19.0, 14.0);
        cmatrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        cmatrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        cmatrix(2, 5) = std::complex<klab::DoubleReal>(22.0, 11.0);
        cmatrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        cmatrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        cmatrix(3, 0) = std::complex<klab::DoubleReal>(25.0, 8.0);
        cmatrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        cmatrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        cmatrix(3, 3) = std::complex<klab::DoubleReal>(28.0, 5.0);
        cmatrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        cmatrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        cmatrix(3, 6) = std::complex<klab::DoubleReal>(31.0, 2.0);
        cmatrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > copMat = new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix);
        TAdjointOperator<std::complex<klab::DoubleReal> > cop(copMat);
        TEST_ASSERT(klab::Equals(cop.variance(), copMat->variance()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testApply()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        arma::Col<klab::DoubleReal> x(4);
        arma::Col<klab::DoubleReal> y;

        x[0] = 204.0;
        x[1] = 492.0;
        x[2] = 780.0;
        x[3] = 1068.0;

        TAdjointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix));
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 44592.0))
        TEST_ASSERT(klab::Equals(y[1], 47136.0))
        TEST_ASSERT(klab::Equals(y[2], 49680.0))
        TEST_ASSERT(klab::Equals(y[3], 52224.0))
        TEST_ASSERT(klab::Equals(y[4], 54768.0))
        TEST_ASSERT(klab::Equals(y[5], 57312.0))
        TEST_ASSERT(klab::Equals(y[6], 59856.0))
        TEST_ASSERT(klab::Equals(y[7], 62400.0)) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        arma::Col<klab::DoubleReal> x(4);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        x[0] = 204.0;
        x[1] = 492.0;
        x[2] = 780.0;
        x[3] = 1068.0;

        TAdjointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix));
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 44592.0))
        TEST_ASSERT(klab::Equals(y[1], 47136.0))
        TEST_ASSERT(klab::Equals(y[2], 49680.0))
        TEST_ASSERT(klab::Equals(y[3], 52224.0))
        TEST_ASSERT(klab::Equals(y[4], 54768.0))
        TEST_ASSERT(klab::Equals(y[5], 57312.0))
        TEST_ASSERT(klab::Equals(y[6], 59856.0))
        TEST_ASSERT(klab::Equals(y[7], 62400.0)) 

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 4)
        TEST_ASSERT(klab::Equals(xr[0], 2032704.0))
        TEST_ASSERT(klab::Equals(xr[1], 5456448.0))
        TEST_ASSERT(klab::Equals(xr[2], 8880192.0))
        TEST_ASSERT(klab::Equals(xr[3], 12303936.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        TAdjointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix));

        arma::Mat<klab::DoubleReal> A(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> col(m);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.apply(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<klab::DoubleReal> B(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> out;
            op.column(i, out);

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

        try                                     {op.column(m, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.column(m+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}


        TAdjointOperator<klab::DoubleReal> op0(0);
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

void KAdjointOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        TAdjointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix));

        arma::Mat<klab::DoubleReal> A(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col(n);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.applyAdjoint(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<klab::DoubleReal> B(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> out;
            op.columnAdjoint(i, out);

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

        try                                     {op.columnAdjoint(n, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.columnAdjoint(n+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}


        TAdjointOperator<klab::DoubleReal> op0(0);
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
