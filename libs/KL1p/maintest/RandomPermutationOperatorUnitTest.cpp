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

#include "RandomPermutationOperatorUnitTest.h"
#include "../include/RandomPermutationOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KRandomPermutationOperatorUnitTest::KRandomPermutationOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KRandomPermutationOperatorUnitTest::testSizeConstructor)  
    TEST_ADD(KRandomPermutationOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KRandomPermutationOperatorUnitTest::testApply)
    TEST_ADD(KRandomPermutationOperatorUnitTest::testApplyAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KRandomPermutationOperatorUnitTest::~KRandomPermutationOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRandomPermutationOperatorUnitTest::testSizeConstructor()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        TRandomPermutationOperator<klab::DoubleReal> op(8);
        TEST_ASSERT(op.indices().size() == 8)
        TEST_ASSERT(op.indices()[0] == 1)
        TEST_ASSERT(op.indices()[1] == 0)
        TEST_ASSERT(op.indices()[2] == 3)
        TEST_ASSERT(op.indices()[3] == 2)
        TEST_ASSERT(op.indices()[4] == 5)
        TEST_ASSERT(op.indices()[5] == 7)
        TEST_ASSERT(op.indices()[6] == 4)
        TEST_ASSERT(op.indices()[7] == 6)


        // Limit cases.
        TRandomPermutationOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.indices().size() == 0)    
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomPermutationOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        TRandomPermutationOperator<klab::DoubleReal> op(8);
        TEST_ASSERT(op.indices().size() == 8)
        TEST_ASSERT(op.indices()[0] == 1)
        TEST_ASSERT(op.indices()[1] == 0)
        TEST_ASSERT(op.indices()[2] == 3)
        TEST_ASSERT(op.indices()[3] == 2)
        TEST_ASSERT(op.indices()[4] == 5)
        TEST_ASSERT(op.indices()[5] == 7)
        TEST_ASSERT(op.indices()[6] == 4)
        TEST_ASSERT(op.indices()[7] == 6)


        TRandomPermutationOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.indices().size() == 8)
        TEST_ASSERT(op2.indices()[0] == 1)
        TEST_ASSERT(op2.indices()[1] == 0)
        TEST_ASSERT(op2.indices()[2] == 3)
        TEST_ASSERT(op2.indices()[3] == 2)
        TEST_ASSERT(op2.indices()[4] == 5)
        TEST_ASSERT(op2.indices()[5] == 7)
        TEST_ASSERT(op2.indices()[6] == 4)
        TEST_ASSERT(op2.indices()[7] == 6)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomPermutationOperatorUnitTest::testApply()
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

        TRandomPermutationOperator<klab::DoubleReal> op(8);
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 2.0))
        TEST_ASSERT(klab::Equals(y[1], 1.0))
        TEST_ASSERT(klab::Equals(y[2], 4.0))
        TEST_ASSERT(klab::Equals(y[3], 3.0))
        TEST_ASSERT(klab::Equals(y[4], 6.0))
        TEST_ASSERT(klab::Equals(y[5], 8.0))
        TEST_ASSERT(klab::Equals(y[6], 5.0))
        TEST_ASSERT(klab::Equals(y[7], 7.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomPermutationOperatorUnitTest::testApplyAdjoint()
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

        TRandomPermutationOperator<klab::DoubleReal> op(8);
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 2.0))
        TEST_ASSERT(klab::Equals(y[1], 1.0))
        TEST_ASSERT(klab::Equals(y[2], 4.0))
        TEST_ASSERT(klab::Equals(y[3], 3.0))
        TEST_ASSERT(klab::Equals(y[4], 6.0))
        TEST_ASSERT(klab::Equals(y[5], 8.0))
        TEST_ASSERT(klab::Equals(y[6], 5.0))
        TEST_ASSERT(klab::Equals(y[7], 7.0))

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
