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

#include "MatrixOperatorUnitTest.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KMatrixOperatorUnitTest::KMatrixOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KMatrixOperatorUnitTest::testMatrixConstructor)  
    TEST_ADD(KMatrixOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KMatrixOperatorUnitTest::testMatrix)
	TEST_ADD(KMatrixOperatorUnitTest::testNormalize)
	TEST_ADD(KMatrixOperatorUnitTest::testIsNormalized)
	TEST_ADD(KMatrixOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KMatrixOperatorUnitTest::testApply)
    TEST_ADD(KMatrixOperatorUnitTest::testApply_Complex)
    TEST_ADD(KMatrixOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KMatrixOperatorUnitTest::testApplyAdjoint_Complex)
    TEST_ADD(KMatrixOperatorUnitTest::testColumn)
    TEST_ADD(KMatrixOperatorUnitTest::testColumn_Complex)
    TEST_ADD(KMatrixOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KMatrixOperatorUnitTest::testColumnAdjoint_Complex)
    TEST_ADD(KMatrixOperatorUnitTest::testToMatrix)
    TEST_ADD(KMatrixOperatorUnitTest::testToMatrix_Complex)
    TEST_ADD(KMatrixOperatorUnitTest::testToMatrixAdjoint)
    TEST_ADD(KMatrixOperatorUnitTest::testToMatrixAdjoint_Complex)

    TEST_ADD(KMatrixOperatorUnitTest::testToOperator)
    TEST_ADD(KMatrixOperatorUnitTest::testToOperator_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KMatrixOperatorUnitTest::~KMatrixOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testMatrixConstructor()
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

        TMatrixOperator<klab::DoubleReal> op(matrix);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
		TEST_ASSERT(op.isNormalized() == false)
        TEST_ASSERT(klab::Equals(op.matrix()(0, 0), 1.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 1), 2.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 2), 3.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 3), 4.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 4), 5.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 5), 6.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 6), 7.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 7), 8.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 0), 9.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 1), 10.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 2), 11.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 3), 12.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 4), 13.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 5), 14.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 6), 15.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 7), 16.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 0), 17.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 1), 18.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 2), 19.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 3), 20.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 4), 21.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 5), 22.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 6), 23.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 7), 24.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 0), 25.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 1), 26.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 2), 27.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 3), 28.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 4), 29.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 5), 30.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 6), 31.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 7), 32.0))
		
		TMatrixOperator<klab::DoubleReal> op2(matrix, true);
        TEST_ASSERT(op2.matrix().n_rows==4 && op2.matrix().n_cols==8)
		TEST_ASSERT(op2.isNormalized() == true)
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 0), 0.031686212526224, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 1), 0.060192926542885, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 2), 0.08588975014708, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 3), 0.109108945118, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 4), 0.13014480157384 , 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 5), 0.1492555785315, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 6), 0.16666666666667, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 7), 0.18257418583506, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 0), 0.28517591273602, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 1), 0.30096463271442, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 2), 0.31492908387263, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 3), 0.32732683535399, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 4), 0.33837648409198, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 5), 0.3482630165735, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 6), 0.35714285714286, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 7), 0.36514837167011, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 0), 0.53866561294581, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 1), 0.54173633888596, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 2), 0.54396841759817, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 3), 0.54554472558998, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 4), 0.54660816661012, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 5), 0.54727045461549, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 6), 0.54761904761905, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 7), 0.54772255750517, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 0), 0.7921553131556, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 1), 0.7825080450575, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 2), 0.77300775132372, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 3), 0.76376261582597, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 4), 0.75483984912826, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 5), 0.74627789265749, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 6), 0.73809523809524, 1e-12))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 7), 0.73029674334022, 1e-12))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testCopyConstructor()
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

        TMatrixOperator<klab::DoubleReal> op(matrix);
        TMatrixOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.matrix().n_rows==4 && op2.matrix().n_cols==8)
		TEST_ASSERT(op2.isNormalized() == false)
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 0), 1.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 1), 2.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 2), 3.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 3), 4.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 4), 5.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 5), 6.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 6), 7.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 7), 8.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 0), 9.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 1), 10.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 2), 11.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 3), 12.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 4), 13.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 5), 14.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 6), 15.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 7), 16.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 0), 17.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 1), 18.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 2), 19.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 3), 20.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 4), 21.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 5), 22.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 6), 23.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 7), 24.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 0), 25.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 1), 26.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 2), 27.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 3), 28.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 4), 29.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 5), 30.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 6), 31.0))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 7), 32.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testMatrix()
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

        TMatrixOperator<klab::DoubleReal> op(matrix);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
        TEST_ASSERT(klab::Equals(op.matrix()(0, 0), 1.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 1), 2.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 2), 3.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 3), 4.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 4), 5.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 5), 6.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 6), 7.0))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 7), 8.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 0), 9.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 1), 10.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 2), 11.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 3), 12.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 4), 13.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 5), 14.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 6), 15.0))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 7), 16.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 0), 17.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 1), 18.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 2), 19.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 3), 20.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 4), 21.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 5), 22.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 6), 23.0))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 7), 24.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 0), 25.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 1), 26.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 2), 27.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 3), 28.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 4), 29.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 5), 30.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 6), 31.0))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 7), 32.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testNormalize()
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
		
		TMatrixOperator<klab::DoubleReal> op(matrix);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
		TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 11440.0, 1e-12))	
		TEST_ASSERT(op.isNormalized() == false)
		
		op.normalize();
		TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
		TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 8.0, 1e-12))	
		TEST_ASSERT(op.isNormalized() == true)
        TEST_ASSERT(klab::Equals(op.matrix()(0, 0), 0.031686212526224, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 1), 0.060192926542885, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 2), 0.08588975014708, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 3), 0.109108945118, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 4), 0.13014480157384 , 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 5), 0.1492555785315, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 6), 0.16666666666667, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 7), 0.18257418583506, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 0), 0.28517591273602, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 1), 0.30096463271442, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 2), 0.31492908387263, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 3), 0.32732683535399, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 4), 0.33837648409198, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 5), 0.3482630165735, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 6), 0.35714285714286, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 7), 0.36514837167011, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 0), 0.53866561294581, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 1), 0.54173633888596, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 2), 0.54396841759817, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 3), 0.54554472558998, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 4), 0.54660816661012, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 5), 0.54727045461549, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 6), 0.54761904761905, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 7), 0.54772255750517, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 0), 0.7921553131556, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 1), 0.7825080450575, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 2), 0.77300775132372, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 3), 0.76376261582597, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 4), 0.75483984912826, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 5), 0.74627789265749, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 6), 0.73809523809524, 1e-12))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 7), 0.73029674334022, 1e-12))
	}
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testIsNormalized()
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
		
		TMatrixOperator<klab::DoubleReal> op(matrix);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
		TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 11440.0, 1e-12))	
		TEST_ASSERT(op.isNormalized() == false)
		
		op.normalize();
		TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
		TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 8.0, 1e-12))	
		TEST_ASSERT(op.isNormalized() == true)       
	}
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testSquaredNormFrobenius()
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
		
		TMatrixOperator<klab::DoubleReal> op(matrix);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
		TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 11440.0, 1e-12))	
		TEST_ASSERT(op.isNormalized() == false)
		
		op.normalize();
		TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
		TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 8.0, 1e-12))	
		TEST_ASSERT(op.isNormalized() == true)        
	}
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testApply()
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

        TMatrixOperator<klab::DoubleReal> op(matrix);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], 204.0))
        TEST_ASSERT(klab::Equals(y[1], 492.0))
        TEST_ASSERT(klab::Equals(y[2], 780.0))
        TEST_ASSERT(klab::Equals(y[3], 1068.0))


        // Limit cases.
        arma::Col<klab::DoubleReal> x2(7);
        x2[0] = 1.0;
        x2[1] = 2.0;
        x2[2] = 3.0;
        x2[3] = 4.0;
        x2[4] = 5.0;
        x2[5] = 6.0;
        x2[6] = 7.0;
        try                                         {op.apply(x2, y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}


        arma::Col<klab::DoubleReal> x3(9);
        x3[0] = 1.0;
        x3[1] = 2.0;
        x3[2] = 3.0;
        x3[3] = 4.0;
        x3[4] = 5.0;
        x3[5] = 6.0;
        x3[6] = 7.0;
        x3[7] = 8.0;
        x3[8] = 9.0;
        try                                         {op.apply(x3, y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testApply_Complex()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > matrix(4, 8);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        arma::Col<std::complex<klab::DoubleReal> > x(8);
        arma::Col<std::complex<klab::DoubleReal> > y;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;

        TMatrixOperator<std::complex<klab::DoubleReal> > op(matrix);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(204.0, 324.0)))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(492.0, 132.0)))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(780.0, 192.0)))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(1068.0, 36.0)))


        // Limit cases.
        arma::Col<std::complex<klab::DoubleReal> > x2(7);
        x2[0] = 1.0;
        x2[1] = 2.0;
        x2[2] = 3.0;
        x2[3] = 4.0;
        x2[4] = 5.0;
        x2[5] = 6.0;
        x2[6] = 7.0;
        try                                         {op.apply(x2, y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}


        arma::Col<std::complex<klab::DoubleReal> > x3(9);
        x3[0] = 1.0;
        x3[1] = 2.0;
        x3[2] = 3.0;
        x3[3] = 4.0;
        x3[4] = 5.0;
        x3[5] = 6.0;
        x3[6] = 7.0;
        x3[7] = 8.0;
        x3[8] = 9.0;
        try                                         {op.apply(x3, y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testApplyAdjoint()
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

        TMatrixOperator<klab::DoubleReal> op(matrix);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], 204.0))
        TEST_ASSERT(klab::Equals(y[1], 492.0))
        TEST_ASSERT(klab::Equals(y[2], 780.0))
        TEST_ASSERT(klab::Equals(y[3], 1068.0))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], 44592.0))
        TEST_ASSERT(klab::Equals(xr[1], 47136.0))
        TEST_ASSERT(klab::Equals(xr[2], 49680.0))
        TEST_ASSERT(klab::Equals(xr[3], 52224.0))
        TEST_ASSERT(klab::Equals(xr[4], 54768.0))
        TEST_ASSERT(klab::Equals(xr[5], 57312.0))
        TEST_ASSERT(klab::Equals(xr[6], 59856.0))
        TEST_ASSERT(klab::Equals(xr[7], 62400.0)) 


        // Limit cases.
        arma::Col<klab::DoubleReal> y2(3);
        y2[0] = 1.0;
        y2[1] = 2.0;
        y2[2] = 3.0;
        try                                         {op.applyAdjoint(y2, xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}


        arma::Col<klab::DoubleReal> y3(5);
        y3[0] = 1.0;
        y3[1] = 2.0;
        y3[2] = 3.0;
        y3[3] = 4.0;
        y3[4] = 5.0;
        try                                         {op.applyAdjoint(y3, xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > matrix(4, 8);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        arma::Col<std::complex<klab::DoubleReal> > x(8);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;

        TMatrixOperator<std::complex<klab::DoubleReal> > op(matrix);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(204.0, 324.0)))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(492.0, 132.0)))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(780.0, 192.0)))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(1068.0, 36.0)))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], std::complex<klab::DoubleReal>(40176.000000000000, -3540.0000000000000)))
        TEST_ASSERT(klab::Equals(xr[1], std::complex<klab::DoubleReal>(57276.000000000000, -7824.0000000000000)))
        TEST_ASSERT(klab::Equals(xr[2], std::complex<klab::DoubleReal>(59832.000000000000, -5388.0000000000000)))
        TEST_ASSERT(klab::Equals(xr[3], std::complex<klab::DoubleReal>(47916.000000000000, -1488.0000000000000)))
        TEST_ASSERT(klab::Equals(xr[4], std::complex<klab::DoubleReal>(63648.000000000000, -1092.0000000000000)))
        TEST_ASSERT(klab::Equals(xr[5], std::complex<klab::DoubleReal>(66564.000000000000, -384.00000000000000)))
        TEST_ASSERT(klab::Equals(xr[6], std::complex<klab::DoubleReal>(55656.000000000000, 564.00000000000000)))
        TEST_ASSERT(klab::Equals(xr[7], std::complex<klab::DoubleReal>(70020.000000000000, 5640.0000000000000))) 


        // Limit cases.
        arma::Col<std::complex<klab::DoubleReal> > y2(3);
        y2[0] = 1.0;
        y2[1] = 2.0;
        y2[2] = 3.0;
        try                                         {op.applyAdjoint(y2, xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}


        arma::Col<std::complex<klab::DoubleReal> > y3(5);
        y3[0] = 1.0;
        y3[1] = 2.0;
        y3[2] = 3.0;
        y3[3] = 4.0;
        y3[4] = 5.0;
        try                                         {op.applyAdjoint(y3, xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

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

        klab::DoubleReal precision = 1e-12; 

        TMatrixOperator<klab::DoubleReal> op(matrix);

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

void KMatrixOperatorUnitTest::testColumn_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        arma::Mat<std::complex<klab::DoubleReal> > matrix(m, n);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        klab::DoubleReal precision = 1e-12; 

        TMatrixOperator<std::complex<klab::DoubleReal> > op(matrix);

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

void KMatrixOperatorUnitTest::testColumnAdjoint()
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

        TMatrixOperator<klab::DoubleReal> op(matrix);

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

void KMatrixOperatorUnitTest::testColumnAdjoint_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        arma::Mat<std::complex<klab::DoubleReal> > matrix(m, n);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        TMatrixOperator<std::complex<klab::DoubleReal> > op(matrix);

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

void KMatrixOperatorUnitTest::testToMatrix()
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

        
        TMatrixOperator<klab::DoubleReal> op(matrix);

        arma::Mat<klab::DoubleReal> A;
        op.toMatrix(A);
        TEST_ASSERT(A.n_rows==m && A.n_cols==n)

        arma::Mat<klab::DoubleReal> B(matrix);

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

void KMatrixOperatorUnitTest::testToMatrix_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<std::complex<klab::DoubleReal> > matrix(m, n);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);        

        TMatrixOperator<std::complex<klab::DoubleReal> > op(matrix);

        arma::Mat<std::complex<klab::DoubleReal> > A;
        op.toMatrix(A);
        TEST_ASSERT(A.n_rows==m && A.n_cols==n)

        arma::Mat<std::complex<klab::DoubleReal> > B(matrix);

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

void KMatrixOperatorUnitTest::testToMatrixAdjoint()
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

        TMatrixOperator<klab::DoubleReal> op(matrix);

        arma::Mat<klab::DoubleReal> A;
        op.toMatrixAdjoint(A);
        TEST_ASSERT(A.n_rows==n && A.n_cols==m)

        arma::Mat<klab::DoubleReal> B(arma::trans(matrix));

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

void KMatrixOperatorUnitTest::testToMatrixAdjoint_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<std::complex<klab::DoubleReal> > matrix(m, n);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);

        TMatrixOperator<std::complex<klab::DoubleReal> > op(matrix);

        arma::Mat<std::complex<klab::DoubleReal> > A;
        op.toMatrixAdjoint(A);
        TEST_ASSERT(A.n_rows==n && A.n_cols==m)

        arma::Mat<std::complex<klab::DoubleReal> > B(arma::trans(matrix));

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

void KMatrixOperatorUnitTest::testToOperator()
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

        klab::TSmartPointer<TOperator<klab::DoubleReal> > op = kl1p::ToOperator(matrix);
        TEST_ASSERT(op!=0 && op->m()==4 && op->n()==8)

        op->apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], 204.0))
        TEST_ASSERT(klab::Equals(y[1], 492.0))
        TEST_ASSERT(klab::Equals(y[2], 780.0))
        TEST_ASSERT(klab::Equals(y[3], 1068.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixOperatorUnitTest::testToOperator_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<std::complex<klab::DoubleReal> > matrix(m, n);
        matrix(0, 0) = std::complex<klab::DoubleReal>(1.0, -32.0);
        matrix(0, 1) = std::complex<klab::DoubleReal>(2.0, 31.0);
        matrix(0, 2) = std::complex<klab::DoubleReal>(3.0, 30.0);
        matrix(0, 3) = std::complex<klab::DoubleReal>(4.0, -29.0);
        matrix(0, 4) = std::complex<klab::DoubleReal>(5.0, 28.0);
        matrix(0, 5) = std::complex<klab::DoubleReal>(6.0, 27.0);
        matrix(0, 6) = std::complex<klab::DoubleReal>(7.0, -26.0);
        matrix(0, 7) = std::complex<klab::DoubleReal>(8.0, 25.0);
        matrix(1, 0) = std::complex<klab::DoubleReal>(9.0, 24.0);
        matrix(1, 1) = std::complex<klab::DoubleReal>(10.0, -23.0);
        matrix(1, 2) = std::complex<klab::DoubleReal>(11.0, 22.0);
        matrix(1, 3) = std::complex<klab::DoubleReal>(12.0, 21.0);
        matrix(1, 4) = std::complex<klab::DoubleReal>(13.0, -20.0);
        matrix(1, 5) = std::complex<klab::DoubleReal>(14.0, 19.0);
        matrix(1, 6) = std::complex<klab::DoubleReal>(15.0, 18.0);
        matrix(1, 7) = std::complex<klab::DoubleReal>(16.0, -17.0);
        matrix(2, 0) = std::complex<klab::DoubleReal>(17.0, 16.0);
        matrix(2, 1) = std::complex<klab::DoubleReal>(18.0, 15.0);
        matrix(2, 2) = std::complex<klab::DoubleReal>(19.0, -14.0);
        matrix(2, 3) = std::complex<klab::DoubleReal>(20.0, 13.0);
        matrix(2, 4) = std::complex<klab::DoubleReal>(21.0, 12.0);
        matrix(2, 5) = std::complex<klab::DoubleReal>(22.0, -11.0);
        matrix(2, 6) = std::complex<klab::DoubleReal>(23.0, 10.0);
        matrix(2, 7) = std::complex<klab::DoubleReal>(24.0, 9.0);
        matrix(3, 0) = std::complex<klab::DoubleReal>(25.0, -8.0);
        matrix(3, 1) = std::complex<klab::DoubleReal>(26.0, 7.0);
        matrix(3, 2) = std::complex<klab::DoubleReal>(27.0, 6.0);
        matrix(3, 3) = std::complex<klab::DoubleReal>(28.0, -5.0);
        matrix(3, 4) = std::complex<klab::DoubleReal>(29.0, 4.0);
        matrix(3, 5) = std::complex<klab::DoubleReal>(30.0, 3.0);
        matrix(3, 6) = std::complex<klab::DoubleReal>(31.0, -2.0);
        matrix(3, 7) = std::complex<klab::DoubleReal>(32.0, 1.0);
      
        arma::Col<std::complex<klab::DoubleReal> > x(8);
        arma::Col<std::complex<klab::DoubleReal> > y;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > op = kl1p::ToOperator(matrix);
        TEST_ASSERT(op!=0 && op->m()==4 && op->n()==8)

        op->apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(204.0, 324.0)))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(492.0, 132.0)))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(780.0, 192.0)))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(1068.0, 36.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
