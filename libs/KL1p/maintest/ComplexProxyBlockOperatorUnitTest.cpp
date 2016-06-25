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

#include "ComplexProxyBlockOperatorUnitTest.h"
#include "../include/ComplexProxyBlockOperator.h"
#include "../include/MatrixOperator.h"
#include "../include/JointOperator.h"
#include "../include/BlockDiagonalOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KComplexProxyBlockOperatorUnitTest::KComplexProxyBlockOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testOpConstructor)  
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testOp)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testIsZero)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testSum)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testNormFrobenius)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testMean)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testVariance)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testBlock)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testInBlock)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testApply)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testColumn)  
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testColumnAdjoint) 
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testApplyBlockVariance)
    TEST_ADD(KComplexProxyBlockOperatorUnitTest::testApplyBlockVarianceAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KComplexProxyBlockOperatorUnitTest::~KComplexProxyBlockOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testOpConstructor()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==6 && op.block(0, 0)->n()==6) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==6 && op.block(0, 1)->n()==8) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()==false && op.block(0, 2)->m()==6 && op.block(0, 2)->n()==10) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()==false && op.block(0, 3)->m()==6 && op.block(0, 3)->n()==12)
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==8 && op.block(1, 0)->n()==6) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==8 && op.block(1, 1)->n()==8) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==8 && op.block(1, 2)->n()==10) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()==false && op.block(1, 3)->m()==8 && op.block(1, 3)->n()==12) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()==false && op.block(2, 0)->m()==10 && op.block(2, 0)->n()==6) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==10 && op.block(2, 1)->n()==8) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==10 && op.block(2, 2)->n()==10) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==10 && op.block(2, 3)->n()==12)


        // Limit cases.
        TComplexProxyBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==6 && op.block(0, 0)->n()==6) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==6 && op.block(0, 1)->n()==8) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()==false && op.block(0, 2)->m()==6 && op.block(0, 2)->n()==10) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()==false && op.block(0, 3)->m()==6 && op.block(0, 3)->n()==12)
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==8 && op.block(1, 0)->n()==6) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==8 && op.block(1, 1)->n()==8) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==8 && op.block(1, 2)->n()==10) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()==false && op.block(1, 3)->m()==8 && op.block(1, 3)->n()==12) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()==false && op.block(2, 0)->m()==10 && op.block(2, 0)->n()==6) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==10 && op.block(2, 1)->n()==8) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==10 && op.block(2, 2)->n()==10) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==10 && op.block(2, 3)->n()==12)


        TComplexProxyBlockOperator<klab::DoubleReal> opCopy(op); 
        TEST_ASSERT(opCopy.m()==m<<1 && opCopy.n()==n<<1)    
        TEST_ASSERT(opCopy.countBlockRows()==blockRows && opCopy.countBlockColumns()==blockCols)
        TEST_ASSERT(opCopy.op() != 0)
        TEST_ASSERT(opCopy.block(0, 0)!=0 && opCopy.block(0, 0)->isZero()==false && opCopy.block(0, 0)->m()==6 && opCopy.block(0, 0)->n()==6) 
        TEST_ASSERT(opCopy.block(0, 1)!=0 && opCopy.block(0, 1)->isZero()==false && opCopy.block(0, 1)->m()==6 && opCopy.block(0, 1)->n()==8) 
        TEST_ASSERT(opCopy.block(0, 2)!=0 && opCopy.block(0, 2)->isZero()==false && opCopy.block(0, 2)->m()==6 && opCopy.block(0, 2)->n()==10) 
        TEST_ASSERT(opCopy.block(0, 3)!=0 && opCopy.block(0, 3)->isZero()==false && opCopy.block(0, 3)->m()==6 && opCopy.block(0, 3)->n()==12)
        TEST_ASSERT(opCopy.block(1, 0)!=0 && opCopy.block(1, 0)->isZero()==false && opCopy.block(1, 0)->m()==8 && opCopy.block(1, 0)->n()==6) 
        TEST_ASSERT(opCopy.block(1, 1)!=0 && opCopy.block(1, 1)->isZero()==false && opCopy.block(1, 1)->m()==8 && opCopy.block(1, 1)->n()==8) 
        TEST_ASSERT(opCopy.block(1, 2)!=0 && opCopy.block(1, 2)->isZero()==false && opCopy.block(1, 2)->m()==8 && opCopy.block(1, 2)->n()==10) 
        TEST_ASSERT(opCopy.block(1, 3)!=0 && opCopy.block(1, 3)->isZero()==false && opCopy.block(1, 3)->m()==8 && opCopy.block(1, 3)->n()==12) 
        TEST_ASSERT(opCopy.block(2, 0)!=0 && opCopy.block(2, 0)->isZero()==false && opCopy.block(2, 0)->m()==10 && opCopy.block(2, 0)->n()==6) 
        TEST_ASSERT(opCopy.block(2, 1)!=0 && opCopy.block(2, 1)->isZero()==false && opCopy.block(2, 1)->m()==10 && opCopy.block(2, 1)->n()==8) 
        TEST_ASSERT(opCopy.block(2, 2)!=0 && opCopy.block(2, 2)->isZero()==false && opCopy.block(2, 2)->m()==10 && opCopy.block(2, 2)->n()==10) 
        TEST_ASSERT(opCopy.block(2, 3)!=0 && opCopy.block(2, 3)->isZero()==false && opCopy.block(2, 3)->m()==10 && opCopy.block(2, 3)->n()==12)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testOp()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.op() != 0)


        // Limit cases.
        TComplexProxyBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testIsZero()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)


        // Limit cases.
        TComplexProxyBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testSum()
{
    try
    {
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
        klab::TSmartPointer<TBlockOperator<std::complex<klab::DoubleReal> > > copBlock = new TBlockDiagonalOperator<std::complex<klab::DoubleReal> >(copMat);
        TComplexProxyBlockOperator<klab::DoubleReal> op(copBlock);
        TEST_ASSERT(klab::Equals(op.sum(), std::norm(copBlock->sum())))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testNormFrobenius()
{
    try
    {
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
        klab::TSmartPointer<TBlockOperator<std::complex<klab::DoubleReal> > > copBlock = new TBlockDiagonalOperator<std::complex<klab::DoubleReal> >(copMat);
        TComplexProxyBlockOperator<klab::DoubleReal> op(copBlock);
        TEST_ASSERT(klab::Equals(op.normFrobenius(), copBlock->normFrobenius().real()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testSquaredNormFrobenius()
{
    try
    {
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
        klab::TSmartPointer<TBlockOperator<std::complex<klab::DoubleReal> > > copBlock = new TBlockDiagonalOperator<std::complex<klab::DoubleReal> >(copMat);
        TComplexProxyBlockOperator<klab::DoubleReal> op(copBlock);
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), copBlock->squaredNormFrobenius().real()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testMean()
{
    try
    {
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
        klab::TSmartPointer<TBlockOperator<std::complex<klab::DoubleReal> > > copBlock = new TBlockDiagonalOperator<std::complex<klab::DoubleReal> >(copMat);
        TComplexProxyBlockOperator<klab::DoubleReal> op(copBlock);
        TEST_ASSERT(klab::Equals(op.mean(), std::norm(copBlock->mean())))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testVariance()
{
    try
    {
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
        klab::TSmartPointer<TBlockOperator<std::complex<klab::DoubleReal> > > copBlock = new TBlockDiagonalOperator<std::complex<klab::DoubleReal> >(copMat);
        TComplexProxyBlockOperator<klab::DoubleReal> op(copBlock);
        TEST_ASSERT(klab::Equals(op.variance(), copBlock->variance().real()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testCountBlockRows()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)


        // Limit cases.
        TComplexProxyBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)


        // Limit cases.
        TComplexProxyBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==6 && op.block(0, 0)->n()==6) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==6 && op.block(0, 1)->n()==8) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()==false && op.block(0, 2)->m()==6 && op.block(0, 2)->n()==10) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()==false && op.block(0, 3)->m()==6 && op.block(0, 3)->n()==12)
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==8 && op.block(1, 0)->n()==6) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==8 && op.block(1, 1)->n()==8) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==8 && op.block(1, 2)->n()==10) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()==false && op.block(1, 3)->m()==8 && op.block(1, 3)->n()==12) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()==false && op.block(2, 0)->m()==10 && op.block(2, 0)->n()==6) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==10 && op.block(2, 1)->n()==8) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==10 && op.block(2, 2)->n()==10) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==10 && op.block(2, 3)->n()==12)


        // Limit cases.
        TComplexProxyBlockOperator<klab::DoubleReal> op0(0); 
        try                                     {op0.block(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(3, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(4, 2); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(4, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZeroBlock(0, 0)==false) 
        TEST_ASSERT(op.isZeroBlock(0, 1)==false) 
        TEST_ASSERT(op.isZeroBlock(0, 2)==false) 
        TEST_ASSERT(op.isZeroBlock(0, 3)==false)
        TEST_ASSERT(op.isZeroBlock(1, 0)==false) 
        TEST_ASSERT(op.isZeroBlock(1, 1)==false) 
        TEST_ASSERT(op.isZeroBlock(1, 2)==false) 
        TEST_ASSERT(op.isZeroBlock(1, 3)==false) 
        TEST_ASSERT(op.isZeroBlock(2, 0)==false) 
        TEST_ASSERT(op.isZeroBlock(2, 1)==false) 
        TEST_ASSERT(op.isZeroBlock(2, 2)==false) 
        TEST_ASSERT(op.isZeroBlock(2, 3)==false)


        // Limit cases.
        TComplexProxyBlockOperator<klab::DoubleReal> op0(0); 
        try                                     {op0.isZeroBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(3, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(4, 2); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(4, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testInBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.op() != 0)

        klab::TSmartPointer<TOperator<klab::DoubleReal> > result = op.inBlock(0, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==6) 

        result = op.inBlock(0, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==6)

        result = op.inBlock(1, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==6)

        result = op.inBlock(1, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==6)

        result = op.inBlock(2, 4);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==6)

        result = op.inBlock(2, 6);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==8)

        result = op.inBlock(2, 14);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==10)

        result = op.inBlock(2, 24);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==12)

        result = op.inBlock(2, 35);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==12)

        result = op.inBlock(8, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==6)

        result = op.inBlock(8, 4);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==6)

        result = op.inBlock(8, 6);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==8)

        result = op.inBlock(8, 14);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==10)

        result = op.inBlock(8, 24);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==12)

        result = op.inBlock(8, 35);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==12)

        result = op.inBlock(18, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==10 && result->n()==6)

        result = op.inBlock(18, 4);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==10 && result->n()==6)

        result = op.inBlock(18, 6);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==10 && result->n()==8)

        result = op.inBlock(18, 14);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==10 && result->n()==10)

        result = op.inBlock(18, 24);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==10 && result->n()==12)

        result = op.inBlock(18, 35);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==10 && result->n()==12)

        result = op.inBlock(23, 35);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==10 && result->n()==12)


        // Limit cases.
        TJointOperator<klab::DoubleReal> op0(0);
        try                                     {op0.inBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(24, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(2, 36); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(24, 36); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);        

        arma::Col<klab::DoubleReal> x(n<<1);
        arma::Col<std::complex<klab::DoubleReal> > xc(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<std::complex<klab::DoubleReal> > yc;

        xc[0]  = std::complex<klab::DoubleReal>(1.0,   18.0);
        xc[1]  = std::complex<klab::DoubleReal>(2.0,  -17.0);
        xc[2]  = std::complex<klab::DoubleReal>(3.0,   16.0);
        xc[3]  = std::complex<klab::DoubleReal>(4.0,   15.0);
        xc[4]  = std::complex<klab::DoubleReal>(5.0,  -14.0);
        xc[5]  = std::complex<klab::DoubleReal>(6.0,   13.0);
        xc[6]  = std::complex<klab::DoubleReal>(7.0,   12.0);
        xc[7]  = std::complex<klab::DoubleReal>(8.0,  -11.0);
        xc[8]  = std::complex<klab::DoubleReal>(9.0,   10.0);
        xc[9]  = std::complex<klab::DoubleReal>(10.0,  9.0);
        xc[10] = std::complex<klab::DoubleReal>(11.0, -8.0);
        xc[11] = std::complex<klab::DoubleReal>(12.0,  7.0);
        xc[12] = std::complex<klab::DoubleReal>(13.0,  6.0);
        xc[13] = std::complex<klab::DoubleReal>(14.0, -5.0);
        xc[14] = std::complex<klab::DoubleReal>(15.0,  4.0);
        xc[15] = std::complex<klab::DoubleReal>(16.0,  3.0);
        xc[16] = std::complex<klab::DoubleReal>(17.0, -2.0);
        xc[17] = std::complex<klab::DoubleReal>(18.0,  1.0);

        x[0]  = xc[0].real();
        x[1]  = xc[1].real();
        x[2]  = xc[2].real();
        x[3]  = xc[0].imag();
        x[4]  = xc[1].imag();
        x[5]  = xc[2].imag();
        x[6]  = xc[3].real();
        x[7]  = xc[4].real();
        x[8]  = xc[5].real();
        x[9]  = xc[6].real();
        x[10] = xc[3].imag();
        x[11] = xc[4].imag();
        x[12] = xc[5].imag();
        x[13] = xc[6].imag();
        x[14] = xc[7].real();
        x[15] = xc[8].real();
        x[16] = xc[9].real();
        x[17] = xc[10].real();
        x[18] = xc[11].real();
        x[19] = xc[7].imag();
        x[20] = xc[8].imag();
        x[21] = xc[9].imag();
        x[22] = xc[10].imag();
        x[23] = xc[11].imag();
        x[24] = xc[12].real();
        x[25] = xc[13].real();
        x[26] = xc[14].real();
        x[27] = xc[15].real();
        x[28] = xc[16].real();
        x[29] = xc[17].real();
        x[30] = xc[12].imag();
        x[31] = xc[13].imag();
        x[32] = xc[14].imag();
        x[33] = xc[15].imag();
        x[34] = xc[16].imag();
        x[35] = xc[17].imag();


        klab::TSmartPointer<TJointOperator<std::complex<klab::DoubleReal> > > opJoint =  new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators);
        TComplexProxyBlockOperator<klab::DoubleReal> op(opJoint); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)

        opJoint->apply(xc, yc);
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m<<1)
        TEST_ASSERT(klab::Equals(y[0],  yc[0].real(), precision))
        TEST_ASSERT(klab::Equals(y[1],  yc[1].real(), precision))
        TEST_ASSERT(klab::Equals(y[2],  yc[2].real(), precision))
        TEST_ASSERT(klab::Equals(y[3],  yc[0].imag(), precision))
        TEST_ASSERT(klab::Equals(y[4],  yc[1].imag(), precision))
        TEST_ASSERT(klab::Equals(y[5],  yc[2].imag(), precision))
        TEST_ASSERT(klab::Equals(y[6],  yc[3].real(), precision))
        TEST_ASSERT(klab::Equals(y[7],  yc[4].real(), precision))
        TEST_ASSERT(klab::Equals(y[8],  yc[5].real(), precision))
        TEST_ASSERT(klab::Equals(y[9],  yc[6].real(), precision))
        TEST_ASSERT(klab::Equals(y[10], yc[3].imag(), precision))
        TEST_ASSERT(klab::Equals(y[11], yc[4].imag(), precision))
        TEST_ASSERT(klab::Equals(y[12], yc[5].imag(), precision))
        TEST_ASSERT(klab::Equals(y[13], yc[6].imag(), precision))
        TEST_ASSERT(klab::Equals(y[14], yc[7].real(), precision))
        TEST_ASSERT(klab::Equals(y[15], yc[8].real(), precision))
        TEST_ASSERT(klab::Equals(y[16], yc[9].real(), precision))
        TEST_ASSERT(klab::Equals(y[17], yc[10].real(), precision))
        TEST_ASSERT(klab::Equals(y[18], yc[11].real(), precision))               
        TEST_ASSERT(klab::Equals(y[19], yc[7].imag(), precision))
        TEST_ASSERT(klab::Equals(y[20], yc[8].imag(), precision))
        TEST_ASSERT(klab::Equals(y[21], yc[9].imag(), precision))
        TEST_ASSERT(klab::Equals(y[22], yc[10].imag(), precision))
        TEST_ASSERT(klab::Equals(y[23], yc[11].imag(), precision))


        // Limit cases.
        try                                         {op.apply(arma::Col<klab::DoubleReal>((n<<1)-1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<klab::DoubleReal>((n<<1)+1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);  

        arma::Col<klab::DoubleReal> x(n<<1);
        arma::Col<std::complex<klab::DoubleReal> > xc(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<std::complex<klab::DoubleReal> > yc;
        arma::Col<klab::DoubleReal> xr;
        arma::Col<std::complex<klab::DoubleReal> > xrc;

        xc[0]  = std::complex<klab::DoubleReal>(1.0,   18.0);
        xc[1]  = std::complex<klab::DoubleReal>(2.0,  -17.0);
        xc[2]  = std::complex<klab::DoubleReal>(3.0,   16.0);
        xc[3]  = std::complex<klab::DoubleReal>(4.0,   15.0);
        xc[4]  = std::complex<klab::DoubleReal>(5.0,  -14.0);
        xc[5]  = std::complex<klab::DoubleReal>(6.0,   13.0);
        xc[6]  = std::complex<klab::DoubleReal>(7.0,   12.0);
        xc[7]  = std::complex<klab::DoubleReal>(8.0,  -11.0);
        xc[8]  = std::complex<klab::DoubleReal>(9.0,   10.0);
        xc[9]  = std::complex<klab::DoubleReal>(10.0,  9.0);
        xc[10] = std::complex<klab::DoubleReal>(11.0, -8.0);
        xc[11] = std::complex<klab::DoubleReal>(12.0,  7.0);
        xc[12] = std::complex<klab::DoubleReal>(13.0,  6.0);
        xc[13] = std::complex<klab::DoubleReal>(14.0, -5.0);
        xc[14] = std::complex<klab::DoubleReal>(15.0,  4.0);
        xc[15] = std::complex<klab::DoubleReal>(16.0,  3.0);
        xc[16] = std::complex<klab::DoubleReal>(17.0, -2.0);
        xc[17] = std::complex<klab::DoubleReal>(18.0,  1.0);

        x[0]  = xc[0].real();
        x[1]  = xc[1].real();
        x[2]  = xc[2].real();
        x[3]  = xc[0].imag();
        x[4]  = xc[1].imag();
        x[5]  = xc[2].imag();
        x[6]  = xc[3].real();
        x[7]  = xc[4].real();
        x[8]  = xc[5].real();
        x[9]  = xc[6].real();
        x[10] = xc[3].imag();
        x[11] = xc[4].imag();
        x[12] = xc[5].imag();
        x[13] = xc[6].imag();
        x[14] = xc[7].real();
        x[15] = xc[8].real();
        x[16] = xc[9].real();
        x[17] = xc[10].real();
        x[18] = xc[11].real();
        x[19] = xc[7].imag();
        x[20] = xc[8].imag();
        x[21] = xc[9].imag();
        x[22] = xc[10].imag();
        x[23] = xc[11].imag();
        x[24] = xc[12].real();
        x[25] = xc[13].real();
        x[26] = xc[14].real();
        x[27] = xc[15].real();
        x[28] = xc[16].real();
        x[29] = xc[17].real();
        x[30] = xc[12].imag();
        x[31] = xc[13].imag();
        x[32] = xc[14].imag();
        x[33] = xc[15].imag();
        x[34] = xc[16].imag();
        x[35] = xc[17].imag();


        klab::TSmartPointer<TJointOperator<std::complex<klab::DoubleReal> > > opJoint =  new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators);
        TComplexProxyBlockOperator<klab::DoubleReal> op(opJoint); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1)

        opJoint->apply(xc, yc);
        opJoint->applyAdjoint(yc, xrc);

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n<<1)
        TEST_ASSERT(klab::Equals(xr[0],  xrc[0].real(), precision))
        TEST_ASSERT(klab::Equals(xr[1],  xrc[1].real(), precision))
        TEST_ASSERT(klab::Equals(xr[2],  xrc[2].real(), precision))
        TEST_ASSERT(klab::Equals(xr[3],  xrc[0].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[4],  xrc[1].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[5],  xrc[2].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[6],  xrc[3].real(), precision))
        TEST_ASSERT(klab::Equals(xr[7],  xrc[4].real(), precision))
        TEST_ASSERT(klab::Equals(xr[8],  xrc[5].real(), precision))
        TEST_ASSERT(klab::Equals(xr[9],  xrc[6].real(), precision))
        TEST_ASSERT(klab::Equals(xr[10], xrc[3].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[11], xrc[4].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[12], xrc[5].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[13], xrc[6].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[14], xrc[7].real(), precision))
        TEST_ASSERT(klab::Equals(xr[15], xrc[8].real(), precision))
        TEST_ASSERT(klab::Equals(xr[16], xrc[9].real(), precision))
        TEST_ASSERT(klab::Equals(xr[17], xrc[10].real(), precision))
        TEST_ASSERT(klab::Equals(xr[18], xrc[11].real(), precision))
        TEST_ASSERT(klab::Equals(xr[19], xrc[7].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[20], xrc[8].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[21], xrc[9].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[22], xrc[10].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[23], xrc[11].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[24], xrc[12].real(), precision))
        TEST_ASSERT(klab::Equals(xr[25], xrc[13].real(), precision))
        TEST_ASSERT(klab::Equals(xr[26], xrc[14].real(), precision))
        TEST_ASSERT(klab::Equals(xr[27], xrc[15].real(), precision))
        TEST_ASSERT(klab::Equals(xr[28], xrc[16].real(), precision))
        TEST_ASSERT(klab::Equals(xr[29], xrc[17].real(), precision))
        TEST_ASSERT(klab::Equals(xr[30], xrc[12].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[31], xrc[13].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[32], xrc[14].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[33], xrc[15].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[34], xrc[16].imag(), precision))
        TEST_ASSERT(klab::Equals(xr[35], xrc[17].imag(), precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>((m<<1)-1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>((m<<1)+1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testColumn()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);
        m <<= 1;
        n <<= 1;

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m && op.n()==n)

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

void KComplexProxyBlockOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);
        m <<= 1;
        n <<= 1;

        TComplexProxyBlockOperator<klab::DoubleReal> op(new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==m && op.n()==n)

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

void KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > >& operators, klab::UInt32& m, klab::UInt32& n, klab::UInt32& blockRows, klab::UInt32& blockCols)
{
    arma::Mat<std::complex<klab::DoubleReal> > matrix00(3, 3);
    arma::Mat<std::complex<klab::DoubleReal> > matrix01(3, 4);
    arma::Mat<std::complex<klab::DoubleReal> > matrix02(3, 5);
    arma::Mat<std::complex<klab::DoubleReal> > matrix03(3, 6);
    arma::Mat<std::complex<klab::DoubleReal> > matrix10(4, 3);
    arma::Mat<std::complex<klab::DoubleReal> > matrix11(4, 4);
    arma::Mat<std::complex<klab::DoubleReal> > matrix12(4, 5);
    arma::Mat<std::complex<klab::DoubleReal> > matrix13(4, 6);
    arma::Mat<std::complex<klab::DoubleReal> > matrix20(5, 3);
    arma::Mat<std::complex<klab::DoubleReal> > matrix21(5, 4);
    arma::Mat<std::complex<klab::DoubleReal> > matrix22(5, 5);
    arma::Mat<std::complex<klab::DoubleReal> > matrix23(5, 6);

    matrix00(0, 0) = std::complex<klab::DoubleReal>(1.0, 9.0);  
    matrix00(0, 1) = std::complex<klab::DoubleReal>(-2.0, -8.0);
    matrix00(0, 2) = std::complex<klab::DoubleReal>(3.0, 7.0);
    matrix00(1, 0) = std::complex<klab::DoubleReal>(4.0, 6.0);
    matrix00(1, 1) = std::complex<klab::DoubleReal>(-5.0, 5.0);
    matrix00(1, 2) = std::complex<klab::DoubleReal>(6.0, 4.0);
    matrix00(2, 0) = std::complex<klab::DoubleReal>(7.0, 3.0);
    matrix00(2, 1) = std::complex<klab::DoubleReal>(-8.0, -2.0);
    matrix00(2, 2) = std::complex<klab::DoubleReal>(9.0, 1.0);

    matrix01(0, 0) = std::complex<klab::DoubleReal>(-12.0, 1.0);
    matrix01(0, 1) = std::complex<klab::DoubleReal>(11.0, -2.0);
    matrix01(0, 2) = std::complex<klab::DoubleReal>(10.0, 3.0);
    matrix01(0, 3) = std::complex<klab::DoubleReal>(-9.0, 4.0);
    matrix01(1, 0) = std::complex<klab::DoubleReal>(-8.0, 5.0);
    matrix01(1, 1) = std::complex<klab::DoubleReal>(7.0, 6.0);
    matrix01(1, 2) = std::complex<klab::DoubleReal>(6.0, 7.0);
    matrix01(1, 3) = std::complex<klab::DoubleReal>(5.0, -8.0);
    matrix01(2, 0) = std::complex<klab::DoubleReal>(4.0, -9.0);
    matrix01(2, 1) = std::complex<klab::DoubleReal>(3.0, 10.0);
    matrix01(2, 2) = std::complex<klab::DoubleReal>(-2.0, 11.0);
    matrix01(2, 3) = std::complex<klab::DoubleReal>(1.0, -12.0);

    matrix02(0, 0) = std::complex<klab::DoubleReal>(0.0, 2.4);
    matrix02(0, 1) = std::complex<klab::DoubleReal>(0.1, 2.3);
    matrix02(0, 2) = std::complex<klab::DoubleReal>(0.2, 2.2);
    matrix02(0, 3) = std::complex<klab::DoubleReal>(-0.3, 2.4);
    matrix02(0, 4) = std::complex<klab::DoubleReal>(0.4, -2.0);
    matrix02(1, 0) = std::complex<klab::DoubleReal>(1.0, 1.4);
    matrix02(1, 1) = std::complex<klab::DoubleReal>(1.1, 1.3);
    matrix02(1, 2) = std::complex<klab::DoubleReal>(1.2, 1.2);
    matrix02(1, 3) = std::complex<klab::DoubleReal>(1.3, 1.1);
    matrix02(1, 4) = std::complex<klab::DoubleReal>(1.4, 1.0);
    matrix02(2, 0) = std::complex<klab::DoubleReal>(-2.0, 0.4);
    matrix02(2, 1) = std::complex<klab::DoubleReal>(2.1, -0.3);
    matrix02(2, 2) = std::complex<klab::DoubleReal>(2.2, 0.2);
    matrix02(2, 3) = std::complex<klab::DoubleReal>(2.3, 0.1);
    matrix02(2, 4) = std::complex<klab::DoubleReal>(2.4, 0.0);

    matrix03(0, 0) = std::complex<klab::DoubleReal>(1.0, -4.4);
    matrix03(0, 1) = std::complex<klab::DoubleReal>(1.2, 4.2);
    matrix03(0, 2) = std::complex<klab::DoubleReal>(-1.4, 4.0);
    matrix03(0, 3) = std::complex<klab::DoubleReal>(-1.6, 3.8);
    matrix03(0, 4) = std::complex<klab::DoubleReal>(1.8, 3.6);
    matrix03(0, 5) = std::complex<klab::DoubleReal>(-2.0, -3.4);
    matrix03(1, 0) = std::complex<klab::DoubleReal>(2.2, 3.2);
    matrix03(1, 1) = std::complex<klab::DoubleReal>(2.4, 3.0);
    matrix03(1, 2) = std::complex<klab::DoubleReal>(2.6, 2.8);
    matrix03(1, 3) = std::complex<klab::DoubleReal>(2.8, 2.6);
    matrix03(1, 4) = std::complex<klab::DoubleReal>(3.0, 2.4);
    matrix03(1, 5) = std::complex<klab::DoubleReal>(3.2, 2.2);
    matrix03(2, 0) = std::complex<klab::DoubleReal>(-3.4, -2.0);
    matrix03(2, 1) = std::complex<klab::DoubleReal>(3.6, 1.8);
    matrix03(2, 2) = std::complex<klab::DoubleReal>(3.8, -1.6);
    matrix03(2, 3) = std::complex<klab::DoubleReal>(4.0, -1.4);
    matrix03(2, 4) = std::complex<klab::DoubleReal>(4.2, 1.2);
    matrix03(2, 5) = std::complex<klab::DoubleReal>(-4.4, 1.0);

    matrix10(0, 0) = std::complex<klab::DoubleReal>(3.2, 0.0);
    matrix10(0, 1) = std::complex<klab::DoubleReal>(3.1, 0.1);
    matrix10(0, 2) = std::complex<klab::DoubleReal>(3.0, 0.2);
    matrix10(1, 0) = std::complex<klab::DoubleReal>(2.2, 1.0);
    matrix10(1, 1) = std::complex<klab::DoubleReal>(2.1, -1.1);
    matrix10(1, 2) = std::complex<klab::DoubleReal>(2.0, 1.2);
    matrix10(2, 0) = std::complex<klab::DoubleReal>(1.2, 2.0);
    matrix10(2, 1) = std::complex<klab::DoubleReal>(-1.1, 2.1);
    matrix10(2, 2) = std::complex<klab::DoubleReal>(1.0, 2.2);
    matrix10(3, 0) = std::complex<klab::DoubleReal>(0.2, 3.0);
    matrix10(3, 1) = std::complex<klab::DoubleReal>(0.1, 3.1);
    matrix10(3, 2) = std::complex<klab::DoubleReal>(0.0, 3.2);

    matrix11(0, 0) = std::complex<klab::DoubleReal>(0.0, 3.3);
    matrix11(0, 1) = std::complex<klab::DoubleReal>(1.0, 2.3);
    matrix11(0, 2) = std::complex<klab::DoubleReal>(2.0, 1.3);
    matrix11(0, 3) = std::complex<klab::DoubleReal>(-3.0, 0.3);
    matrix11(1, 0) = std::complex<klab::DoubleReal>(0.1, -3.2);
    matrix11(1, 1) = std::complex<klab::DoubleReal>(1.1, 2.2);
    matrix11(1, 2) = std::complex<klab::DoubleReal>(2.1, 1.2);
    matrix11(1, 3) = std::complex<klab::DoubleReal>(3.1, -0.2);
    matrix11(2, 0) = std::complex<klab::DoubleReal>(-0.2, 3.1);
    matrix11(2, 1) = std::complex<klab::DoubleReal>(1.2, 2.1);
    matrix11(2, 2) = std::complex<klab::DoubleReal>(2.2, 1.1);
    matrix11(2, 3) = std::complex<klab::DoubleReal>(-3.2, 0.1);
    matrix11(3, 0) = std::complex<klab::DoubleReal>(0.3, -3.0);
    matrix11(3, 1) = std::complex<klab::DoubleReal>(1.3, 2.0);
    matrix11(3, 2) = std::complex<klab::DoubleReal>(2.3, 1.0);
    matrix11(3, 3) = std::complex<klab::DoubleReal>(3.3, 0.0);

    matrix12(0, 0) = std::complex<klab::DoubleReal>(-1.0, -20.0);
    matrix12(0, 1) = std::complex<klab::DoubleReal>(2.0, 19.0);
    matrix12(0, 2) = std::complex<klab::DoubleReal>(-3.0, 18.0);
    matrix12(0, 3) = std::complex<klab::DoubleReal>(-4.0, 17.0);
    matrix12(0, 4) = std::complex<klab::DoubleReal>(5.0, -16.0);
    matrix12(1, 0) = std::complex<klab::DoubleReal>(6.0, 15.0);
    matrix12(1, 1) = std::complex<klab::DoubleReal>(7.0, 14.0);
    matrix12(1, 2) = std::complex<klab::DoubleReal>(8.0, -13.0);
    matrix12(1, 3) = std::complex<klab::DoubleReal>(9.0, 12.0);
    matrix12(1, 4) = std::complex<klab::DoubleReal>(10.0, 11.0);
    matrix12(2, 0) = std::complex<klab::DoubleReal>(11.0, 10.0);
    matrix12(2, 1) = std::complex<klab::DoubleReal>(12.0, 9.0);
    matrix12(2, 2) = std::complex<klab::DoubleReal>(-13.0, 8.0);
    matrix12(2, 3) = std::complex<klab::DoubleReal>(14.0, 7.0);
    matrix12(2, 4) = std::complex<klab::DoubleReal>(15.0, 6.0);
    matrix12(3, 0) = std::complex<klab::DoubleReal>(-16.0, 5.0);
    matrix12(3, 1) = std::complex<klab::DoubleReal>(17.0, -4.0);
    matrix12(3, 2) = std::complex<klab::DoubleReal>(18.0, -3.0);
    matrix12(3, 3) = std::complex<klab::DoubleReal>(19.0, 2.0);
    matrix12(3, 4) = std::complex<klab::DoubleReal>(-20.0, -1.0);

    matrix13(0, 0) = std::complex<klab::DoubleReal>(0.1, 24.0);
    matrix13(0, 1) = std::complex<klab::DoubleReal>(2.0, -0.23);
    matrix13(0, 2) = std::complex<klab::DoubleReal>(0.3, 22.0);
    matrix13(0, 3) = std::complex<klab::DoubleReal>(-4.0, -0.21);
    matrix13(0, 4) = std::complex<klab::DoubleReal>(-0.5, 20.0);
    matrix13(0, 5) = std::complex<klab::DoubleReal>(6.0, 0.19);
    matrix13(1, 0) = std::complex<klab::DoubleReal>(-0.7, 18.0);
    matrix13(1, 1) = std::complex<klab::DoubleReal>(8.0, -0.17);
    matrix13(1, 2) = std::complex<klab::DoubleReal>(0.9, -16.0);
    matrix13(1, 3) = std::complex<klab::DoubleReal>(10.0, 0.15);
    matrix13(1, 4) = std::complex<klab::DoubleReal>(-0.11, 14.0);
    matrix13(1, 5) = std::complex<klab::DoubleReal>(-12.0, 0.13);
    matrix13(2, 0) = std::complex<klab::DoubleReal>(0.13, -12.0);
    matrix13(2, 1) = std::complex<klab::DoubleReal>(14.0, -0.11);
    matrix13(2, 2) = std::complex<klab::DoubleReal>(0.15, 10.0);
    matrix13(2, 3) = std::complex<klab::DoubleReal>(-16.0, 0.9);
    matrix13(2, 4) = std::complex<klab::DoubleReal>(-0.17, 8.0);
    matrix13(2, 5) = std::complex<klab::DoubleReal>(18.0, -0.7);
    matrix13(3, 0) = std::complex<klab::DoubleReal>(0.19, 6.0);
    matrix13(3, 1) = std::complex<klab::DoubleReal>(20.0, -0.5);
    matrix13(3, 2) = std::complex<klab::DoubleReal>(-0.21, -4.0);
    matrix13(3, 3) = std::complex<klab::DoubleReal>(22.0, 0.3);
    matrix13(3, 4) = std::complex<klab::DoubleReal>(-0.23, 2.0);
    matrix13(3, 5) = std::complex<klab::DoubleReal>(24.0, 0.1);

    matrix20(0, 0) = std::complex<klab::DoubleReal>(1.0, 15.0);
    matrix20(0, 1) = std::complex<klab::DoubleReal>(2.0, 14.0);
    matrix20(0, 2) = std::complex<klab::DoubleReal>(3.0, 13.0);
    matrix20(1, 0) = std::complex<klab::DoubleReal>(4.0, 12.0);
    matrix20(1, 1) = std::complex<klab::DoubleReal>(5.0, 11.0);
    matrix20(1, 2) = std::complex<klab::DoubleReal>(6.0, 10.0);
    matrix20(2, 0) = std::complex<klab::DoubleReal>(7.0, 9.0);
    matrix20(2, 1) = std::complex<klab::DoubleReal>(8.0, 8.0);
    matrix20(2, 2) = std::complex<klab::DoubleReal>(9.0, 7.0);
    matrix20(3, 0) = std::complex<klab::DoubleReal>(10.0, 6.0);
    matrix20(3, 1) = std::complex<klab::DoubleReal>(11.0, 5.0);
    matrix20(3, 2) = std::complex<klab::DoubleReal>(12.0, 4.0);
    matrix20(4, 0) = std::complex<klab::DoubleReal>(13.0, 3.0);
    matrix20(4, 1) = std::complex<klab::DoubleReal>(14.0, 2.0);
    matrix20(4, 2) = std::complex<klab::DoubleReal>(15.0, 1.0);

    matrix21(0, 0) = std::complex<klab::DoubleReal>(0.0, 4.3);
    matrix21(0, 1) = std::complex<klab::DoubleReal>(0.1, 4.2);
    matrix21(0, 2) = std::complex<klab::DoubleReal>(-0.2, 4.1);
    matrix21(0, 3) = std::complex<klab::DoubleReal>(0.3, 4.0);
    matrix21(1, 0) = std::complex<klab::DoubleReal>(1.0, 3.3);
    matrix21(1, 1) = std::complex<klab::DoubleReal>(1.1, -3.2);
    matrix21(1, 2) = std::complex<klab::DoubleReal>(-1.2, 3.1);
    matrix21(1, 3) = std::complex<klab::DoubleReal>(1.3, 3.0);
    matrix21(2, 0) = std::complex<klab::DoubleReal>(2.0, 2.3);
    matrix21(2, 1) = std::complex<klab::DoubleReal>(2.1, 2.2);
    matrix21(2, 2) = std::complex<klab::DoubleReal>(2.2, 2.1);
    matrix21(2, 3) = std::complex<klab::DoubleReal>(2.3, 2.0);
    matrix21(3, 0) = std::complex<klab::DoubleReal>(3.0, 1.3);
    matrix21(3, 1) = std::complex<klab::DoubleReal>(3.1, -1.2);
    matrix21(3, 2) = std::complex<klab::DoubleReal>(-3.2, 1.1);
    matrix21(3, 3) = std::complex<klab::DoubleReal>(3.3, 1.0);
    matrix21(4, 0) = std::complex<klab::DoubleReal>(4.0, 0.3);
    matrix21(4, 1) = std::complex<klab::DoubleReal>(4.1, -0.2);
    matrix21(4, 2) = std::complex<klab::DoubleReal>(4.2, 0.1);
    matrix21(4, 3) = std::complex<klab::DoubleReal>(4.3, 0.0);

    matrix22(0, 0) = std::complex<klab::DoubleReal>(-4.4, 0.0);
    matrix22(0, 1) = std::complex<klab::DoubleReal>(4.3, 0.1);
    matrix22(0, 2) = std::complex<klab::DoubleReal>(4.2, 0.2);
    matrix22(0, 3) = std::complex<klab::DoubleReal>(-4.1, 0.3);
    matrix22(0, 4) = std::complex<klab::DoubleReal>(4.0, 0.4);
    matrix22(1, 0) = std::complex<klab::DoubleReal>(3.4, -1.0);
    matrix22(1, 1) = std::complex<klab::DoubleReal>(3.3, 1.1);
    matrix22(1, 2) = std::complex<klab::DoubleReal>(3.2, 1.2);
    matrix22(1, 3) = std::complex<klab::DoubleReal>(-3.1, 1.3);
    matrix22(1, 4) = std::complex<klab::DoubleReal>(3.0, 1.4);
    matrix22(2, 0) = std::complex<klab::DoubleReal>(2.4, 2.0);
    matrix22(2, 1) = std::complex<klab::DoubleReal>(-2.3, 2.1);
    matrix22(2, 2) = std::complex<klab::DoubleReal>(2.2, 2.2);
    matrix22(2, 3) = std::complex<klab::DoubleReal>(2.1, -2.3);
    matrix22(2, 4) = std::complex<klab::DoubleReal>(2.0, 2.4);
    matrix22(3, 0) = std::complex<klab::DoubleReal>(1.4, 3.0);
    matrix22(3, 1) = std::complex<klab::DoubleReal>(1.3, -3.1);
    matrix22(3, 2) = std::complex<klab::DoubleReal>(1.2, 3.2);
    matrix22(3, 3) = std::complex<klab::DoubleReal>(1.1, 3.3);
    matrix22(3, 4) = std::complex<klab::DoubleReal>(-1.0, 3.4);
    matrix22(4, 0) = std::complex<klab::DoubleReal>(0.4, 4.0);
    matrix22(4, 1) = std::complex<klab::DoubleReal>(0.3, -4.1);
    matrix22(4, 2) = std::complex<klab::DoubleReal>(0.2, 4.2);
    matrix22(4, 3) = std::complex<klab::DoubleReal>(0.1, 4.3);
    matrix22(4, 4) = std::complex<klab::DoubleReal>(0.0, -4.4);

    matrix23(0, 0) = std::complex<klab::DoubleReal>(-30.0, 1.0);
    matrix23(0, 1) = std::complex<klab::DoubleReal>(29.0, 2.0);
    matrix23(0, 2) = std::complex<klab::DoubleReal>(28.0, -3.0);
    matrix23(0, 3) = std::complex<klab::DoubleReal>(27.0, 4.0);
    matrix23(0, 4) = std::complex<klab::DoubleReal>(26.0, 5.0);
    matrix23(0, 5) = std::complex<klab::DoubleReal>(25.0, -6.0);
    matrix23(1, 0) = std::complex<klab::DoubleReal>(24.0, 7.0);
    matrix23(1, 1) = std::complex<klab::DoubleReal>(23.0, 8.0);
    matrix23(1, 2) = std::complex<klab::DoubleReal>(-22.0, 9.0);
    matrix23(1, 3) = std::complex<klab::DoubleReal>(21.0, 10.0);
    matrix23(1, 4) = std::complex<klab::DoubleReal>(-20.0, 11.0);
    matrix23(1, 5) = std::complex<klab::DoubleReal>(19.0, 12.0);
    matrix23(2, 0) = std::complex<klab::DoubleReal>(-18.0, -13.0);
    matrix23(2, 1) = std::complex<klab::DoubleReal>(-17.0, 14.0);
    matrix23(2, 2) = std::complex<klab::DoubleReal>(16.0, 15.0);
    matrix23(2, 3) = std::complex<klab::DoubleReal>(15.0, 16.0);
    matrix23(2, 4) = std::complex<klab::DoubleReal>(14.0, -17.0);
    matrix23(2, 5) = std::complex<klab::DoubleReal>(-13.0, -18.0);
    matrix23(3, 0) = std::complex<klab::DoubleReal>(12.0, 19.0);
    matrix23(3, 1) = std::complex<klab::DoubleReal>(11.0, -20.0);
    matrix23(3, 2) = std::complex<klab::DoubleReal>(10.0, 21.0);
    matrix23(3, 3) = std::complex<klab::DoubleReal>(9.0, -22.0);
    matrix23(3, 4) = std::complex<klab::DoubleReal>(8.0, 23.0);
    matrix23(3, 5) = std::complex<klab::DoubleReal>(7.0, 24.0);
    matrix23(4, 0) = std::complex<klab::DoubleReal>(-6.0, 25.0);
    matrix23(4, 1) = std::complex<klab::DoubleReal>(5.0, 26.0);
    matrix23(4, 2) = std::complex<klab::DoubleReal>(4.0, 27.0);
    matrix23(4, 3) = std::complex<klab::DoubleReal>(-3.0, 28.0);
    matrix23(4, 4) = std::complex<klab::DoubleReal>(2.0, 29.0);
    matrix23(4, 5) = std::complex<klab::DoubleReal>(1.0, -30.0);


    operators.clear();
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix00));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix01));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix02));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix03));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix10));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix11));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix12));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix13));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix20));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix21));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix22));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix23));

    m = klab::Max(operators[0]->m()+operators[4]->m()+operators[8]->m(), klab::Max(operators[1]->m()+operators[5]->m()+operators[9]->m(), klab::Max(operators[2]->m()+operators[6]->m()+operators[10]->m(), operators[3]->m()+operators[7]->m()+operators[11]->m())));
    n = klab::Max(operators[0]->n()+operators[1]->n()+operators[2]->n()+operators[3]->n(), klab::Max(operators[4]->n()+operators[5]->n()+operators[6]->n()+operators[7]->n(), operators[8]->n()+operators[9]->n()+operators[10]->n()+operators[11]->n()));

    blockRows = 3;
    blockCols = 4;
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_02(std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > >& operators, klab::UInt32& m, klab::UInt32& n, klab::UInt32& blockRows, klab::UInt32& blockCols)
{
    arma::Mat<std::complex<klab::DoubleReal> > matrix00(3, 3);
    arma::Mat<std::complex<klab::DoubleReal> > matrix01(3, 4);
    arma::Mat<std::complex<klab::DoubleReal> > matrix03(3, 6);
    arma::Mat<std::complex<klab::DoubleReal> > matrix20(5, 3);
    arma::Mat<std::complex<klab::DoubleReal> > matrix21(5, 4);
    arma::Mat<std::complex<klab::DoubleReal> > matrix23(5, 6);

    matrix00(0, 0) = std::complex<klab::DoubleReal>(1.0, 9.0);  
    matrix00(0, 1) = std::complex<klab::DoubleReal>(-2.0, -8.0);
    matrix00(0, 2) = std::complex<klab::DoubleReal>(3.0, 7.0);
    matrix00(1, 0) = std::complex<klab::DoubleReal>(4.0, 6.0);
    matrix00(1, 1) = std::complex<klab::DoubleReal>(-5.0, 5.0);
    matrix00(1, 2) = std::complex<klab::DoubleReal>(6.0, 4.0);
    matrix00(2, 0) = std::complex<klab::DoubleReal>(7.0, 3.0);
    matrix00(2, 1) = std::complex<klab::DoubleReal>(-8.0, -2.0);
    matrix00(2, 2) = std::complex<klab::DoubleReal>(9.0, 1.0);

    matrix01(0, 0) = std::complex<klab::DoubleReal>(-12.0, 1.0);
    matrix01(0, 1) = std::complex<klab::DoubleReal>(11.0, -2.0);
    matrix01(0, 2) = std::complex<klab::DoubleReal>(10.0, 3.0);
    matrix01(0, 3) = std::complex<klab::DoubleReal>(-9.0, 4.0);
    matrix01(1, 0) = std::complex<klab::DoubleReal>(-8.0, 5.0);
    matrix01(1, 1) = std::complex<klab::DoubleReal>(7.0, 6.0);
    matrix01(1, 2) = std::complex<klab::DoubleReal>(6.0, 7.0);
    matrix01(1, 3) = std::complex<klab::DoubleReal>(5.0, -8.0);
    matrix01(2, 0) = std::complex<klab::DoubleReal>(4.0, -9.0);
    matrix01(2, 1) = std::complex<klab::DoubleReal>(3.0, 10.0);
    matrix01(2, 2) = std::complex<klab::DoubleReal>(-2.0, 11.0);
    matrix01(2, 3) = std::complex<klab::DoubleReal>(1.0, -12.0);

    matrix03(0, 0) = std::complex<klab::DoubleReal>(1.0, -4.4);
    matrix03(0, 1) = std::complex<klab::DoubleReal>(1.2, 4.2);
    matrix03(0, 2) = std::complex<klab::DoubleReal>(-1.4, 4.0);
    matrix03(0, 3) = std::complex<klab::DoubleReal>(-1.6, 3.8);
    matrix03(0, 4) = std::complex<klab::DoubleReal>(1.8, 3.6);
    matrix03(0, 5) = std::complex<klab::DoubleReal>(-2.0, -3.4);
    matrix03(1, 0) = std::complex<klab::DoubleReal>(2.2, 3.2);
    matrix03(1, 1) = std::complex<klab::DoubleReal>(2.4, 3.0);
    matrix03(1, 2) = std::complex<klab::DoubleReal>(2.6, 2.8);
    matrix03(1, 3) = std::complex<klab::DoubleReal>(2.8, 2.6);
    matrix03(1, 4) = std::complex<klab::DoubleReal>(3.0, 2.4);
    matrix03(1, 5) = std::complex<klab::DoubleReal>(3.2, 2.2);
    matrix03(2, 0) = std::complex<klab::DoubleReal>(-3.4, -2.0);
    matrix03(2, 1) = std::complex<klab::DoubleReal>(3.6, 1.8);
    matrix03(2, 2) = std::complex<klab::DoubleReal>(3.8, -1.6);
    matrix03(2, 3) = std::complex<klab::DoubleReal>(4.0, -1.4);
    matrix03(2, 4) = std::complex<klab::DoubleReal>(4.2, 1.2);
    matrix03(2, 5) = std::complex<klab::DoubleReal>(-4.4, 1.0);

    matrix20(0, 0) = std::complex<klab::DoubleReal>(1.0, 15.0);
    matrix20(0, 1) = std::complex<klab::DoubleReal>(2.0, 14.0);
    matrix20(0, 2) = std::complex<klab::DoubleReal>(3.0, 13.0);
    matrix20(1, 0) = std::complex<klab::DoubleReal>(4.0, 12.0);
    matrix20(1, 1) = std::complex<klab::DoubleReal>(5.0, 11.0);
    matrix20(1, 2) = std::complex<klab::DoubleReal>(6.0, 10.0);
    matrix20(2, 0) = std::complex<klab::DoubleReal>(7.0, 9.0);
    matrix20(2, 1) = std::complex<klab::DoubleReal>(8.0, 8.0);
    matrix20(2, 2) = std::complex<klab::DoubleReal>(9.0, 7.0);
    matrix20(3, 0) = std::complex<klab::DoubleReal>(10.0, 6.0);
    matrix20(3, 1) = std::complex<klab::DoubleReal>(11.0, 5.0);
    matrix20(3, 2) = std::complex<klab::DoubleReal>(12.0, 4.0);
    matrix20(4, 0) = std::complex<klab::DoubleReal>(13.0, 3.0);
    matrix20(4, 1) = std::complex<klab::DoubleReal>(14.0, 2.0);
    matrix20(4, 2) = std::complex<klab::DoubleReal>(15.0, 1.0);

    matrix21(0, 0) = std::complex<klab::DoubleReal>(0.0, 4.3);
    matrix21(0, 1) = std::complex<klab::DoubleReal>(0.1, 4.2);
    matrix21(0, 2) = std::complex<klab::DoubleReal>(-0.2, 4.1);
    matrix21(0, 3) = std::complex<klab::DoubleReal>(0.3, 4.0);
    matrix21(1, 0) = std::complex<klab::DoubleReal>(1.0, 3.3);
    matrix21(1, 1) = std::complex<klab::DoubleReal>(1.1, -3.2);
    matrix21(1, 2) = std::complex<klab::DoubleReal>(-1.2, 3.1);
    matrix21(1, 3) = std::complex<klab::DoubleReal>(1.3, 3.0);
    matrix21(2, 0) = std::complex<klab::DoubleReal>(2.0, 2.3);
    matrix21(2, 1) = std::complex<klab::DoubleReal>(2.1, 2.2);
    matrix21(2, 2) = std::complex<klab::DoubleReal>(2.2, 2.1);
    matrix21(2, 3) = std::complex<klab::DoubleReal>(2.3, 2.0);
    matrix21(3, 0) = std::complex<klab::DoubleReal>(3.0, 1.3);
    matrix21(3, 1) = std::complex<klab::DoubleReal>(3.1, -1.2);
    matrix21(3, 2) = std::complex<klab::DoubleReal>(-3.2, 1.1);
    matrix21(3, 3) = std::complex<klab::DoubleReal>(3.3, 1.0);
    matrix21(4, 0) = std::complex<klab::DoubleReal>(4.0, 0.3);
    matrix21(4, 1) = std::complex<klab::DoubleReal>(4.1, -0.2);
    matrix21(4, 2) = std::complex<klab::DoubleReal>(4.2, 0.1);
    matrix21(4, 3) = std::complex<klab::DoubleReal>(4.3, 0.0);

    matrix23(0, 0) = std::complex<klab::DoubleReal>(-30.0, 1.0);
    matrix23(0, 1) = std::complex<klab::DoubleReal>(29.0, 2.0);
    matrix23(0, 2) = std::complex<klab::DoubleReal>(28.0, -3.0);
    matrix23(0, 3) = std::complex<klab::DoubleReal>(27.0, 4.0);
    matrix23(0, 4) = std::complex<klab::DoubleReal>(26.0, 5.0);
    matrix23(0, 5) = std::complex<klab::DoubleReal>(25.0, -6.0);
    matrix23(1, 0) = std::complex<klab::DoubleReal>(24.0, 7.0);
    matrix23(1, 1) = std::complex<klab::DoubleReal>(23.0, 8.0);
    matrix23(1, 2) = std::complex<klab::DoubleReal>(-22.0, 9.0);
    matrix23(1, 3) = std::complex<klab::DoubleReal>(21.0, 10.0);
    matrix23(1, 4) = std::complex<klab::DoubleReal>(-20.0, 11.0);
    matrix23(1, 5) = std::complex<klab::DoubleReal>(19.0, 12.0);
    matrix23(2, 0) = std::complex<klab::DoubleReal>(-18.0, -13.0);
    matrix23(2, 1) = std::complex<klab::DoubleReal>(-17.0, 14.0);
    matrix23(2, 2) = std::complex<klab::DoubleReal>(16.0, 15.0);
    matrix23(2, 3) = std::complex<klab::DoubleReal>(15.0, 16.0);
    matrix23(2, 4) = std::complex<klab::DoubleReal>(14.0, -17.0);
    matrix23(2, 5) = std::complex<klab::DoubleReal>(-13.0, -18.0);
    matrix23(3, 0) = std::complex<klab::DoubleReal>(12.0, 19.0);
    matrix23(3, 1) = std::complex<klab::DoubleReal>(11.0, -20.0);
    matrix23(3, 2) = std::complex<klab::DoubleReal>(10.0, 21.0);
    matrix23(3, 3) = std::complex<klab::DoubleReal>(9.0, -22.0);
    matrix23(3, 4) = std::complex<klab::DoubleReal>(8.0, 23.0);
    matrix23(3, 5) = std::complex<klab::DoubleReal>(7.0, 24.0);
    matrix23(4, 0) = std::complex<klab::DoubleReal>(-6.0, 25.0);
    matrix23(4, 1) = std::complex<klab::DoubleReal>(5.0, 26.0);
    matrix23(4, 2) = std::complex<klab::DoubleReal>(4.0, 27.0);
    matrix23(4, 3) = std::complex<klab::DoubleReal>(-3.0, 28.0);
    matrix23(4, 4) = std::complex<klab::DoubleReal>(2.0, 29.0);
    matrix23(4, 5) = std::complex<klab::DoubleReal>(1.0, -30.0);


    operators.clear();
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix00));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix01));
    operators.push_back(0);
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix03));
    operators.push_back(0);
    operators.push_back(0);
    operators.push_back(0);
    operators.push_back(0);
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix20));
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix21));
    operators.push_back(0);
    operators.push_back(new kl1p::TMatrixOperator<std::complex<klab::DoubleReal> >(matrix23));

    m = klab::Max(operators[0]->m()+operators[8]->m(), klab::Max(operators[1]->m()+operators[9]->m(), operators[3]->m()+operators[11]->m()));
    n = klab::Max(operators[0]->n()+operators[1]->n()+operators[3]->n(), operators[8]->n()+operators[9]->n()+operators[11]->n());

    blockRows = 3;
    blockCols = 4;
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testApplyBlockVariance()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);        

        arma::Col<klab::DoubleReal> x(blockCols);
        arma::Col<std::complex<klab::DoubleReal> > xc(blockCols);
        arma::Col<klab::DoubleReal> y;
        arma::Col<std::complex<klab::DoubleReal> > yc;

        xc[0]  = std::complex<klab::DoubleReal>(1.0, 0.0);
        xc[1]  = std::complex<klab::DoubleReal>(2.0, 0.0);
        xc[2]  = std::complex<klab::DoubleReal>(3.0, 0.0);
        xc[3]  = std::complex<klab::DoubleReal>(4.0, 0.0);

        x[0]  = xc[0].real();
        x[1]  = xc[1].real();
        x[2]  = xc[2].real();
        x[3]  = xc[3].real();


        klab::TSmartPointer<TJointOperator<std::complex<klab::DoubleReal> > > opJoint =  new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators);
        TComplexProxyBlockOperator<klab::DoubleReal> op(opJoint); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1) 
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        opJoint->applyBlockVariance(xc, yc);
        op.applyBlockVariance(x, y);
        TEST_ASSERT(y.n_rows==blockRows)
        TEST_ASSERT(klab::Equals(y[0], yc[0].real(), precision))
        TEST_ASSERT(klab::Equals(y[1], yc[1].real(), precision))
        TEST_ASSERT(klab::Equals(y[2], yc[2].real(), precision))       
        

        // Limit cases.
        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(blockCols-1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(blockCols+1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexProxyBlockOperatorUnitTest::testApplyBlockVarianceAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-9; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > > operators;
        KComplexProxyBlockOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);        

        arma::Col<klab::DoubleReal> x(blockCols);
        arma::Col<std::complex<klab::DoubleReal> > xc(blockCols);
        arma::Col<klab::DoubleReal> y;
        arma::Col<std::complex<klab::DoubleReal> > yc;
        arma::Col<klab::DoubleReal> xr;
        arma::Col<std::complex<klab::DoubleReal> > xrc;

        xc[0]  = std::complex<klab::DoubleReal>(1.0, 0.0);
        xc[1]  = std::complex<klab::DoubleReal>(2.0, 0.0);
        xc[2]  = std::complex<klab::DoubleReal>(3.0, 0.0);
        xc[3]  = std::complex<klab::DoubleReal>(4.0, 0.0);

        x[0]  = xc[0].real();
        x[1]  = xc[1].real();
        x[2]  = xc[2].real();
        x[3]  = xc[3].real();


        klab::TSmartPointer<TJointOperator<std::complex<klab::DoubleReal> > > opJoint =  new TJointOperator<std::complex<klab::DoubleReal> >(blockRows, blockCols, operators);
        TComplexProxyBlockOperator<klab::DoubleReal> op(opJoint); 
        TEST_ASSERT(op.m()==m<<1 && op.n()==n<<1) 
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        opJoint->applyBlockVariance(xc, yc);
        opJoint->applyBlockVarianceAdjoint(yc, xrc);
        op.applyBlockVariance(x, y);
        op.applyBlockVarianceAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows==blockCols)
        TEST_ASSERT(klab::Equals(xr[0], xrc[0].real(), precision))
        TEST_ASSERT(klab::Equals(xr[1], xrc[1].real(), precision))
        TEST_ASSERT(klab::Equals(xr[2], xrc[2].real(), precision))  
        TEST_ASSERT(klab::Equals(xr[3], xrc[3].real(), precision))  
        

        // Limit cases.
        try                                         {op.applyBlockVarianceAdjoint(arma::Col<klab::DoubleReal>(blockRows-1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyBlockVarianceAdjoint(arma::Col<klab::DoubleReal>(blockRows+1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
