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

#include "DownSamplingOperatorUnitTest.h"
#include "../include/DownSamplingOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KDownSamplingOperatorUnitTest::KDownSamplingOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KDownSamplingOperatorUnitTest::testNIndicesConstructor)
    TEST_ADD(KDownSamplingOperatorUnitTest::testMaskConstructor)
    TEST_ADD(KDownSamplingOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KDownSamplingOperatorUnitTest::testApply)
    TEST_ADD(KDownSamplingOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KDownSamplingOperatorUnitTest::testColumn)
    TEST_ADD(KDownSamplingOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KDownSamplingOperatorUnitTest::~KDownSamplingOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KDownSamplingOperatorUnitTest::testNIndicesConstructor()
{
    try
    {
        std::vector<klab::UInt32> indices(2);
        indices[0] = 1;
        indices[1] = 4;

        TDownSamplingOperator<klab::DoubleReal> op(8, indices);
        TEST_ASSERT(op.m()==2 && op.n()==8)
        TEST_ASSERT(op.indices().size() == 2)
        TEST_ASSERT(op.indices()[0] == 1)
        TEST_ASSERT(op.indices()[1] == 4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDownSamplingOperatorUnitTest::testMaskConstructor()
{
    try
    {
        klab::KBitArray bits(8);
        bits.setBit(0, false);
        bits.setBit(1, true);
        bits.setBit(2, false);
        bits.setBit(3, false);
        bits.setBit(4, true);
        bits.setBit(5, true);
        bits.setBit(6, false);
        bits.setBit(7, true);

        TDownSamplingOperator<klab::DoubleReal> op(bits);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.indices().size() == 4)
        TEST_ASSERT(op.indices()[0] == 1)
        TEST_ASSERT(op.indices()[1] == 4)
        TEST_ASSERT(op.indices()[2] == 5)
        TEST_ASSERT(op.indices()[3] == 7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDownSamplingOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::KBitArray bits(8);
        bits.setBit(0, false);
        bits.setBit(1, true);
        bits.setBit(2, false);
        bits.setBit(3, false);
        bits.setBit(4, true);
        bits.setBit(5, true);
        bits.setBit(6, false);
        bits.setBit(7, true);

        TDownSamplingOperator<klab::DoubleReal> op(bits);
        TDownSamplingOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(op2.indices().size() == 4)
        TEST_ASSERT(op2.indices()[0] == 1)
        TEST_ASSERT(op2.indices()[1] == 4)
        TEST_ASSERT(op2.indices()[2] == 5)
        TEST_ASSERT(op2.indices()[3] == 7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDownSamplingOperatorUnitTest::testApply()
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

        klab::KBitArray bits(8);
        bits.setBit(0, false);
        bits.setBit(1, true);
        bits.setBit(2, false);
        bits.setBit(3, false);
        bits.setBit(4, true);
        bits.setBit(5, true);
        bits.setBit(6, false);
        bits.setBit(7, true);

        TDownSamplingOperator<klab::DoubleReal> op(bits);

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], 2.0))
        TEST_ASSERT(klab::Equals(y[1], 5.0))
        TEST_ASSERT(klab::Equals(y[2], 6.0))
        TEST_ASSERT(klab::Equals(y[3], 8.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDownSamplingOperatorUnitTest::testApplyAdjoint()
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

        klab::KBitArray bits(8);
        bits.setBit(0, false);
        bits.setBit(1, true);
        bits.setBit(2, false);
        bits.setBit(3, false);
        bits.setBit(4, true);
        bits.setBit(5, true);
        bits.setBit(6, false);
        bits.setBit(7, true);

        TDownSamplingOperator<klab::DoubleReal> op(bits);

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], 2.0))
        TEST_ASSERT(klab::Equals(y[1], 5.0))
        TEST_ASSERT(klab::Equals(y[2], 6.0))
        TEST_ASSERT(klab::Equals(y[3], 8.0))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], 0.0))
        TEST_ASSERT(klab::Equals(xr[1], 2.0))
        TEST_ASSERT(klab::Equals(xr[2], 0.0))
        TEST_ASSERT(klab::Equals(xr[3], 0.0))
        TEST_ASSERT(klab::Equals(xr[4], 5.0))
        TEST_ASSERT(klab::Equals(xr[5], 6.0))
        TEST_ASSERT(klab::Equals(xr[6], 0.0))
        TEST_ASSERT(klab::Equals(xr[7], 8.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDownSamplingOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        klab::KBitArray bits(8);
        bits.setBit(0, false);
        bits.setBit(1, true);
        bits.setBit(2, false);
        bits.setBit(3, false);
        bits.setBit(4, true);
        bits.setBit(5, true);
        bits.setBit(6, false);
        bits.setBit(7, true);

        TDownSamplingOperator<klab::DoubleReal> op(bits);

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

void KDownSamplingOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        klab::KBitArray bits(8);
        bits.setBit(0, false);
        bits.setBit(1, true);
        bits.setBit(2, false);
        bits.setBit(3, false);
        bits.setBit(4, true);
        bits.setBit(5, true);
        bits.setBit(6, false);
        bits.setBit(7, true);

        TDownSamplingOperator<klab::DoubleReal> op(bits);

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
