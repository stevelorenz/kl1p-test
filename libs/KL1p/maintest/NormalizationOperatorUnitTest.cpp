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

#include "NormalizationOperatorUnitTest.h"
#include "../include/NormalizationOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KNormalizationOperatorUnitTest::KNormalizationOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KNormalizationOperatorUnitTest::testOpConstructor)  
    TEST_ADD(KNormalizationOperatorUnitTest::testOpScaleConstructor) 
    TEST_ADD(KNormalizationOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KNormalizationOperatorUnitTest::testSetScale)    
    TEST_ADD(KNormalizationOperatorUnitTest::testOp)
    TEST_ADD(KNormalizationOperatorUnitTest::testScale)
    TEST_ADD(KNormalizationOperatorUnitTest::testApply)
    TEST_ADD(KNormalizationOperatorUnitTest::testApply_Complex)
    TEST_ADD(KNormalizationOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KNormalizationOperatorUnitTest::testApplyAdjoint_Complex)
    TEST_ADD(KNormalizationOperatorUnitTest::testColumn)
    TEST_ADD(KNormalizationOperatorUnitTest::testColumn_Complex)
    TEST_ADD(KNormalizationOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KNormalizationOperatorUnitTest::testColumnAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KNormalizationOperatorUnitTest::~KNormalizationOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KNormalizationOperatorUnitTest::testOpConstructor()
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

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr2 = new TMatrixOperator<std::complex<klab::DoubleReal> >(B);


        TNormalizationOperator<klab::DoubleReal> op(optr);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.op() == optr)
        TEST_ASSERT(klab::Equals(op.scale(), 0.0813250060790444, precision))

        TNormalizationOperator<std::complex<klab::DoubleReal> > op2(optr2);
        TEST_ASSERT(op2.m()==m && op2.n()==n)
        TEST_ASSERT(op2.op() == optr2)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.0366145645969789, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalizationOperatorUnitTest::testOpScaleConstructor()
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

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr2 = new TMatrixOperator<std::complex<klab::DoubleReal> >(B);


        TNormalizationOperator<klab::DoubleReal> op(optr, 0.5);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.op() == optr)
        TEST_ASSERT(klab::Equals(op.scale(), 0.0406625030395222, precision))

        TNormalizationOperator<std::complex<klab::DoubleReal> > op2(optr2, 0.5);
        TEST_ASSERT(op2.m()==m && op2.n()==n)
        TEST_ASSERT(op2.op() == optr2)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.01830728229848945, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
} 

// ---------------------------------------------------------------------------------------------------- //

void KNormalizationOperatorUnitTest::testCopyConstructor()
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

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr2 = new TMatrixOperator<std::complex<klab::DoubleReal> >(B);


        TNormalizationOperator<klab::DoubleReal> op(optr, 0.5);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.op() == optr)
        TEST_ASSERT(klab::Equals(op.scale(), 0.0406625030395222, precision))

        TNormalizationOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==m && opCopy.n()==n)
        TEST_ASSERT(opCopy.op() == optr)
        TEST_ASSERT(klab::Equals(opCopy.scale(), 0.0406625030395222, precision))


        TNormalizationOperator<std::complex<klab::DoubleReal> > op2(optr2, 0.5);
        TEST_ASSERT(op2.m()==m && op2.n()==n)
        TEST_ASSERT(op2.op() == optr2)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.01830728229848945, 0.0), precision))

        TNormalizationOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.m()==m && op2Copy.n()==n)
        TEST_ASSERT(op2Copy.op() == optr2)
        TEST_ASSERT(klab::Equals(op2Copy.scale(), std::complex<klab::DoubleReal>(0.01830728229848945, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalizationOperatorUnitTest::testSetScale()
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

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr2 = new TMatrixOperator<std::complex<klab::DoubleReal> >(B);


        TNormalizationOperator<klab::DoubleReal> op(optr);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.op() == optr)
        TEST_ASSERT(klab::Equals(op.scale(), 0.0813250060790444, precision))

        op.setScale(0.5);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.op() == optr)
        TEST_ASSERT(klab::Equals(op.scale(), 0.0406625030395222, precision))


        TNormalizationOperator<std::complex<klab::DoubleReal> > op2(optr2);
        TEST_ASSERT(op2.m()==m && op2.n()==n)
        TEST_ASSERT(op2.op() == optr2)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.0366145645969789, 0.0), precision))

        op2.setScale(0.5);
        TEST_ASSERT(op2.m()==m && op2.n()==n)
        TEST_ASSERT(op2.op() == optr2)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.01830728229848945, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalizationOperatorUnitTest::testOp()
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

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr2 = new TMatrixOperator<std::complex<klab::DoubleReal> >(B);


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

void KNormalizationOperatorUnitTest::testScale()
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

        klab::TSmartPointer<TOperator<klab::DoubleReal> > optr  = new TMatrixOperator<klab::DoubleReal>(A);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > optr2 = new TMatrixOperator<std::complex<klab::DoubleReal> >(B);


        TNormalizationOperator<klab::DoubleReal> op(optr);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.op() == optr)
        TEST_ASSERT(klab::Equals(op.scale(), 0.0813250060790444, precision))

        op.setScale(0.5);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.op() == optr)
        TEST_ASSERT(klab::Equals(op.scale(), 0.0406625030395222, precision))


        TNormalizationOperator<std::complex<klab::DoubleReal> > op2(optr2);
        TEST_ASSERT(op2.m()==m && op2.n()==n)
        TEST_ASSERT(op2.op() == optr2)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.0366145645969789, 0.0), precision))

        op2.setScale(0.5);
        TEST_ASSERT(op2.m()==m && op2.n()==n)
        TEST_ASSERT(op2.op() == optr2)
        TEST_ASSERT(klab::Equals(op2.scale(), std::complex<klab::DoubleReal>(0.01830728229848945, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalizationOperatorUnitTest::testApply()
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
        TNormalizationOperator<klab::DoubleReal> op(optr, 0.5);

        arma::Col<klab::DoubleReal> x(n);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        arma::Col<klab::DoubleReal> y;
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0],  0.6343350474165466, precision))
        TEST_ASSERT(klab::Equals(y[1],  1.154815086322431, precision))
        TEST_ASSERT(klab::Equals(y[2], -0.1138550085106621, precision))
        TEST_ASSERT(klab::Equals(y[3],  3.757215280851852, precision))

        
        // Limit cases.
        TNormalizationOperator<klab::DoubleReal> op0(optr, 0.0);
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

void KNormalizationOperatorUnitTest::testApply_Complex()
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
        TNormalizationOperator<std::complex<klab::DoubleReal> > op(optr, 0.5);

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = std::complex<klab::DoubleReal>(static_cast<klab::DoubleReal>(i+1), static_cast<klab::DoubleReal>(n-i));

        arma::Col<std::complex<klab::DoubleReal> > y;
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(-0.8128433340529317,   2.965779732355291), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>( 0.08421349857305144,  2.30671756960967), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(-0.300239429695227,    0.164765540686405), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>( 0.6480777933665265,   3.427123246277225), precision))

        
        // Limit cases.
        TNormalizationOperator<std::complex<klab::DoubleReal> > op0(optr, std::complex<klab::DoubleReal>(0.0, 0.0));
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

void KNormalizationOperatorUnitTest::testApplyAdjoint()
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
        TNormalizationOperator<klab::DoubleReal> op(optr, 0.5);

        arma::Col<klab::DoubleReal> x(n);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        arma::Col<klab::DoubleReal> y;
        op.apply(x, y);

        arma::Col<klab::DoubleReal> xr;
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], -0.4206349206349206, precision))
        TEST_ASSERT(klab::Equals(xr[1],  0.5181216931216931, precision))
        TEST_ASSERT(klab::Equals(xr[2],  0.5298941798941799, precision))
        TEST_ASSERT(klab::Equals(xr[3], -0.5468253968253967, precision))
        TEST_ASSERT(klab::Equals(xr[4],  0.4529100529100529, precision))
        TEST_ASSERT(klab::Equals(xr[5],  0.6296296296296295, precision))
        TEST_ASSERT(klab::Equals(xr[6],  0.6285714285714286, precision))
        TEST_ASSERT(klab::Equals(xr[7],  0.6756613756613756, precision))

        
        // Limit cases.
        TNormalizationOperator<klab::DoubleReal> op0(optr, 0.0);
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

void KNormalizationOperatorUnitTest::testApplyAdjoint_Complex()
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
        TNormalizationOperator<std::complex<klab::DoubleReal> > op(optr, 0.5);

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = std::complex<klab::DoubleReal>(static_cast<klab::DoubleReal>(i+1), static_cast<klab::DoubleReal>(n-i));

        arma::Col<std::complex<klab::DoubleReal> > y;
        op.apply(x, y);

        arma::Col<std::complex<klab::DoubleReal> > xr;
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], std::complex<klab::DoubleReal>(-0.05904118404118405, -0.1354568854568855), precision))
        TEST_ASSERT(klab::Equals(xr[1], std::complex<klab::DoubleReal>( 0.2113765551265552,   0.257071803946804), precision))
        TEST_ASSERT(klab::Equals(xr[2], std::complex<klab::DoubleReal>( 0.161733161733118,    0.1990293865293866), precision))
        TEST_ASSERT(klab::Equals(xr[3], std::complex<klab::DoubleReal>(-0.2177043114543115,  -0.1816079472329473), precision))
        TEST_ASSERT(klab::Equals(xr[4], std::complex<klab::DoubleReal>( 0.3455330330330331,   0.2210692835692836), precision))
        TEST_ASSERT(klab::Equals(xr[5], std::complex<klab::DoubleReal>( 0.85383151008151004,  0.27762360574860573), precision))
        TEST_ASSERT(klab::Equals(xr[6], std::complex<klab::DoubleReal>( 1.01930501930502,     0.3730694980694982), precision))
        TEST_ASSERT(klab::Equals(xr[7], std::complex<klab::DoubleReal>( 1.167135885885886,    0.3008298477048478), precision))

        
        // Limit cases.
        TNormalizationOperator<std::complex<klab::DoubleReal> > op0(optr, std::complex<klab::DoubleReal>(0.0, 0.0));
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

void KNormalizationOperatorUnitTest::testColumn()
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

        TNormalizationOperator<klab::DoubleReal> op(optr, 0.5);

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

void KNormalizationOperatorUnitTest::testColumn_Complex()
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

        TNormalizationOperator<std::complex<klab::DoubleReal> > op(optr, 0.5);

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

void KNormalizationOperatorUnitTest::testColumnAdjoint()
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

        TNormalizationOperator<klab::DoubleReal> op(optr, 0.5);

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

void KNormalizationOperatorUnitTest::testColumnAdjoint_Complex()
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

        TNormalizationOperator<std::complex<klab::DoubleReal> > op(optr, 0.5);

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
