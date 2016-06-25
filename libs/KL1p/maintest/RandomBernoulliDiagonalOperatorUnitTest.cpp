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

#include "RandomBernoulliDiagonalOperatorUnitTest.h"
#include "../include/RandomBernoulliDiagonalOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KRandomBernoulliDiagonalOperatorUnitTest::KRandomBernoulliDiagonalOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KRandomBernoulliDiagonalOperatorUnitTest::testSizeConstructor)  
    TEST_ADD(KRandomBernoulliDiagonalOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KRandomBernoulliDiagonalOperatorUnitTest::testApply)
    TEST_ADD(KRandomBernoulliDiagonalOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KRandomBernoulliDiagonalOperatorUnitTest::testColumn)
    TEST_ADD(KRandomBernoulliDiagonalOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KRandomBernoulliDiagonalOperatorUnitTest::~KRandomBernoulliDiagonalOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRandomBernoulliDiagonalOperatorUnitTest::testSizeConstructor()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        TRandomBernoulliDiagonalOperator<klab::DoubleReal> op(8);
        TEST_ASSERT(op.diagonal().size() == 8)
        TEST_ASSERT(op.diagonal()[0] == -1.0)
        TEST_ASSERT(op.diagonal()[1] == -1.0)
        TEST_ASSERT(op.diagonal()[2] == 1.0)
        TEST_ASSERT(op.diagonal()[3] == -1.0)
        TEST_ASSERT(op.diagonal()[4] == 1.0)
        TEST_ASSERT(op.diagonal()[5] == 1.0)
        TEST_ASSERT(op.diagonal()[6] == -1.0)
        TEST_ASSERT(op.diagonal()[7] == 1.0)


        // Limit cases.
        TRandomBernoulliDiagonalOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.diagonal().size() == 0)             
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomBernoulliDiagonalOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        TRandomBernoulliDiagonalOperator<klab::DoubleReal> op(8);
        TEST_ASSERT(op.diagonal().size() == 8)
        TEST_ASSERT(op.diagonal()[0] == -1.0)
        TEST_ASSERT(op.diagonal()[1] == -1.0)
        TEST_ASSERT(op.diagonal()[2] == 1.0)
        TEST_ASSERT(op.diagonal()[3] == -1.0)
        TEST_ASSERT(op.diagonal()[4] == 1.0)
        TEST_ASSERT(op.diagonal()[5] == 1.0)
        TEST_ASSERT(op.diagonal()[6] == -1.0)
        TEST_ASSERT(op.diagonal()[7] == 1.0)


        TRandomBernoulliDiagonalOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.diagonal().size() == 8)
        TEST_ASSERT(op2.diagonal()[0] == -1.0)
        TEST_ASSERT(op2.diagonal()[1] == -1.0)
        TEST_ASSERT(op2.diagonal()[2] == 1.0)
        TEST_ASSERT(op2.diagonal()[3] == -1.0)
        TEST_ASSERT(op2.diagonal()[4] == 1.0)
        TEST_ASSERT(op2.diagonal()[5] == 1.0)
        TEST_ASSERT(op2.diagonal()[6] == -1.0)
        TEST_ASSERT(op2.diagonal()[7] == 1.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomBernoulliDiagonalOperatorUnitTest::testApply()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

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

        TRandomBernoulliDiagonalOperator<klab::DoubleReal> op(8);
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], -1.0))
        TEST_ASSERT(klab::Equals(y[1], -2.0))
        TEST_ASSERT(klab::Equals(y[2],  3.0))
        TEST_ASSERT(klab::Equals(y[3], -4.0))
        TEST_ASSERT(klab::Equals(y[4],  5.0))
        TEST_ASSERT(klab::Equals(y[5],  6.0))
        TEST_ASSERT(klab::Equals(y[6], -7.0))
        TEST_ASSERT(klab::Equals(y[7],  8.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomBernoulliDiagonalOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

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

        TRandomBernoulliDiagonalOperator<klab::DoubleReal> op(8);
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], -1.0))
        TEST_ASSERT(klab::Equals(y[1], -2.0))
        TEST_ASSERT(klab::Equals(y[2],  3.0))
        TEST_ASSERT(klab::Equals(y[3], -4.0))
        TEST_ASSERT(klab::Equals(y[4],  5.0))
        TEST_ASSERT(klab::Equals(y[5],  6.0))
        TEST_ASSERT(klab::Equals(y[6], -7.0))
        TEST_ASSERT(klab::Equals(y[7],  8.0))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
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

void KRandomBernoulliDiagonalOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12; 

        TRandomBernoulliDiagonalOperator<std::complex<klab::DoubleReal> > op(n);

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

void KRandomBernoulliDiagonalOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12; 

        TRandomBernoulliDiagonalOperator<klab::DoubleReal> op(n);

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
