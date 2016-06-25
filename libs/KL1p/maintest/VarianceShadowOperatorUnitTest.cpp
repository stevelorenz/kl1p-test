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

#include "VarianceShadowOperatorUnitTest.h"
#include "../include/VarianceShadowOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KVarianceShadowOperatorUnitTest::KVarianceShadowOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KVarianceShadowOperatorUnitTest::testOpConstructor)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testOpVarianceConstructor)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testOpVarianceMeanConstructor)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KVarianceShadowOperatorUnitTest::testOp)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testIsZero)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testSum)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testNormFrobenius)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testMean)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testVariance)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testApply)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testApply_Complex)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testApplyAdjoint_Complex)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testColumn)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testColumn_Complex)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KVarianceShadowOperatorUnitTest::testColumnAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KVarianceShadowOperatorUnitTest::~KVarianceShadowOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testOpConstructor()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 0.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), 0.0))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 0.0))
        TEST_ASSERT(klab::Equals(op.mean(), 0.0))
        TEST_ASSERT(klab::Equals(op.variance(), 0.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(0.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(0.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(0.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(0.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(0.0, 0.0)))


        // Limit cases.
        TVarianceShadowOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.isZero())
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testOpVarianceConstructor()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 0.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(32.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 32.0))
        TEST_ASSERT(klab::Equals(op.mean(), 0.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0);
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(0.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(32.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(32.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(0.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))


        // Limit cases.
        TVarianceShadowOperator<klab::DoubleReal> op0(0, 1.0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.isZero())
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testOpVarianceMeanConstructor()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 64.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(op.mean(), 2.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))


        // Limit cases.
        TVarianceShadowOperator<klab::DoubleReal> op0(0, 1.0, 2.0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.isZero())
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testCopyConstructor()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 64.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(op.mean(), 2.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))

        TVarianceShadowOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==4 && opCopy.n()==8)
        TEST_ASSERT(opCopy.isZero() == false)
        TEST_ASSERT(opCopy.op() == op.op())
        TEST_ASSERT(klab::Equals(opCopy.sum(), 64.0))
        TEST_ASSERT(klab::Equals(opCopy.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(opCopy.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(opCopy.mean(), 2.0))
        TEST_ASSERT(klab::Equals(opCopy.variance(), 1.0))


        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))

        TVarianceShadowOperator<std::complex<klab::DoubleReal> > copCopy(cop);
        TEST_ASSERT(copCopy.m()==4 && copCopy.n()==8)
        TEST_ASSERT(copCopy.isZero() == false)
        TEST_ASSERT(copCopy.op() == cop.op())
        TEST_ASSERT(klab::Equals(copCopy.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(copCopy.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(copCopy.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(copCopy.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(copCopy.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))

    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testOp()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 64.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(op.mean(), 2.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testIsZero()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 64.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(op.mean(), 2.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testSum()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 64.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(op.mean(), 2.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testNormFrobenius()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 64.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(op.mean(), 2.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testSquaredNormFrobenius()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 64.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(op.mean(), 2.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testMean()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 64.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(op.mean(), 2.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testVariance()
{
    try
    {
        arma::Mat<klab::DoubleReal> matrix(4, 8);
        matrix.fill(0.0);

        arma::Mat<std::complex<klab::DoubleReal> > cmatrix(4, 8);
        cmatrix.fill(0.0);


        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(klab::Equals(op.sum(), 64.0))
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(160.0)))
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 160.0))
        TEST_ASSERT(klab::Equals(op.mean(), 2.0))
        TEST_ASSERT(klab::Equals(op.variance(), 1.0))
        
        TVarianceShadowOperator<std::complex<klab::DoubleReal> > cop(new TMatrixOperator<std::complex<klab::DoubleReal> >(cmatrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.isZero() == false)
        TEST_ASSERT(cop.op() != 0)
        TEST_ASSERT(klab::Equals(cop.sum(), std::complex<klab::DoubleReal>(64.0, 96.0)))
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(448.0), 0.0)))
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), std::complex<klab::DoubleReal>(448.0, 0.0)))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(2.0, 3.0)))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(1.0, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testApply()
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

        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)

        op.apply(x, y);
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

void KVarianceShadowOperatorUnitTest::testApply_Complex()
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

        TVarianceShadowOperator<std::complex<klab::DoubleReal> > op(new TMatrixOperator<std::complex<klab::DoubleReal> >(matrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(op.m()==4 && op.n()==8)

        op.apply(x, y);
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

void KVarianceShadowOperatorUnitTest::testApplyAdjoint()
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

        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)

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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testApplyAdjoint_Complex()
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

        TVarianceShadowOperator<std::complex<klab::DoubleReal> > op(new TMatrixOperator<std::complex<klab::DoubleReal> >(matrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(op.m()==4 && op.n()==8)

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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVarianceShadowOperatorUnitTest::testColumn()
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

        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)

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

void KVarianceShadowOperatorUnitTest::testColumn_Complex()
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

        TVarianceShadowOperator<std::complex<klab::DoubleReal> > op(new TMatrixOperator<std::complex<klab::DoubleReal> >(matrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(op.m()==4 && op.n()==8)

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

void KVarianceShadowOperatorUnitTest::testColumnAdjoint()
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

        TVarianceShadowOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)

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

void KVarianceShadowOperatorUnitTest::testColumnAdjoint_Complex()
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

        TVarianceShadowOperator<std::complex<klab::DoubleReal> > op(new TMatrixOperator<std::complex<klab::DoubleReal> >(matrix), 1.0, std::complex<klab::DoubleReal>(2.0, 3.0));
        TEST_ASSERT(op.m()==4 && op.n()==8)

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
