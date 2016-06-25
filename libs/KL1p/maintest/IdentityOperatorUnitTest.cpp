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

#include "IdentityOperatorUnitTest.h"
#include "../include/IdentityOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KIdentityOperatorUnitTest::KIdentityOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KIdentityOperatorUnitTest::testNConstructor)   
    TEST_ADD(KIdentityOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KIdentityOperatorUnitTest::testApply)
    TEST_ADD(KIdentityOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KIdentityOperatorUnitTest::testColumn)
    TEST_ADD(KIdentityOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KIdentityOperatorUnitTest::~KIdentityOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KIdentityOperatorUnitTest::testNConstructor()
{
    try
    {
        TIdentityOperator<klab::DoubleReal> op(32);
        TEST_ASSERT(op.m()==32 && op.n()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIdentityOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TIdentityOperator<klab::DoubleReal> op(32);
        TEST_ASSERT(op.m()==32 && op.n()==32)

        TIdentityOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(op.m()==32 && op.n()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIdentityOperatorUnitTest::testApply()
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

        TEST_ASSERT(x.n_rows == 8)
        TEST_ASSERT(klab::Equals(x[0], 1.0))
        TEST_ASSERT(klab::Equals(x[1], 2.0))
        TEST_ASSERT(klab::Equals(x[2], 3.0))
        TEST_ASSERT(klab::Equals(x[3], 4.0))
        TEST_ASSERT(klab::Equals(x[4], 5.0))
        TEST_ASSERT(klab::Equals(x[5], 6.0))
        TEST_ASSERT(klab::Equals(x[6], 7.0))
        TEST_ASSERT(klab::Equals(x[7], 8.0))


        TIdentityOperator<klab::DoubleReal> op(8);
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

void KIdentityOperatorUnitTest::testApplyAdjoint()
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

        TEST_ASSERT(x.n_rows == 8)
        TEST_ASSERT(klab::Equals(x[0], 1.0))
        TEST_ASSERT(klab::Equals(x[1], 2.0))
        TEST_ASSERT(klab::Equals(x[2], 3.0))
        TEST_ASSERT(klab::Equals(x[3], 4.0))
        TEST_ASSERT(klab::Equals(x[4], 5.0))
        TEST_ASSERT(klab::Equals(x[5], 6.0))
        TEST_ASSERT(klab::Equals(x[6], 7.0))
        TEST_ASSERT(klab::Equals(x[7], 8.0))


        TIdentityOperator<klab::DoubleReal> op(8);
        op.applyAdjoint(x, y);
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

void KIdentityOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        TIdentityOperator<std::complex<klab::DoubleReal> > op(n);

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

void KIdentityOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        TIdentityOperator<klab::DoubleReal> op(n);

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
