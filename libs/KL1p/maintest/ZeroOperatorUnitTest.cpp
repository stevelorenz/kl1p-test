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

#include "ZeroOperatorUnitTest.h"
#include "../include/ZeroOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KZeroOperatorUnitTest::KZeroOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KZeroOperatorUnitTest::testMNConstructor)   
    TEST_ADD(KZeroOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KZeroOperatorUnitTest::testIsZero)
    TEST_ADD(KZeroOperatorUnitTest::testSum)
    TEST_ADD(KZeroOperatorUnitTest::testNormFrobenius)
    TEST_ADD(KZeroOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KZeroOperatorUnitTest::testMean)
    TEST_ADD(KZeroOperatorUnitTest::testVariance)
    TEST_ADD(KZeroOperatorUnitTest::testApply)
    TEST_ADD(KZeroOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KZeroOperatorUnitTest::testColumn)
    TEST_ADD(KZeroOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KZeroOperatorUnitTest::~KZeroOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testMNConstructor()
{
    try
    {
        TZeroOperator<klab::DoubleReal> op0(0, 0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.isZero())

        TZeroOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TZeroOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.isZero())

        TZeroOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==16 && opCopy.n()==32)
        TEST_ASSERT(opCopy.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testIsZero()
{
    try
    {
        TZeroOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testSum()
{
    try
    {
        TZeroOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(klab::Equals(op.sum(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testNormFrobenius()
{
    try
    {
        TZeroOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(klab::Equals(op.normFrobenius(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testSquaredNormFrobenius()
{
    try
    {
        TZeroOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testMean()
{
    try
    {
        TZeroOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(klab::Equals(op.mean(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testVariance()
{
    try
    {
        TZeroOperator<klab::DoubleReal> op(16, 32);
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(klab::Equals(op.variance(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testApply()
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

        TZeroOperator<klab::DoubleReal> op(4, 8);
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], 0.0))
        TEST_ASSERT(klab::Equals(y[1], 0.0))
        TEST_ASSERT(klab::Equals(y[2], 0.0))
        TEST_ASSERT(klab::Equals(y[3], 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testApplyAdjoint()
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

        TZeroOperator<klab::DoubleReal> op(4, 8);
        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], 0.0))
        TEST_ASSERT(klab::Equals(xr[1], 0.0))
        TEST_ASSERT(klab::Equals(xr[2], 0.0))
        TEST_ASSERT(klab::Equals(xr[3], 0.0))
        TEST_ASSERT(klab::Equals(xr[4], 0.0))
        TEST_ASSERT(klab::Equals(xr[5], 0.0))
        TEST_ASSERT(klab::Equals(xr[6], 0.0))
        TEST_ASSERT(klab::Equals(xr[7], 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KZeroOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        TZeroOperator<std::complex<klab::DoubleReal> > op(m, n);

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

void KZeroOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        TZeroOperator<klab::DoubleReal> op(m, n);

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
