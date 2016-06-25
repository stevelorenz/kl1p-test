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

#include "RandomDownSamplingOperatorUnitTest.h"
#include "../include/RandomDownSamplingOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KRandomDownSamplingOperatorUnitTest::KRandomDownSamplingOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KRandomDownSamplingOperatorUnitTest::testMNConstructor)  
    TEST_ADD(KRandomDownSamplingOperatorUnitTest::testMNIndexConstructor)  
    TEST_ADD(KRandomDownSamplingOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KRandomDownSamplingOperatorUnitTest::testApply)
    TEST_ADD(KRandomDownSamplingOperatorUnitTest::testApplyAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KRandomDownSamplingOperatorUnitTest::~KRandomDownSamplingOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRandomDownSamplingOperatorUnitTest::testMNConstructor()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        TRandomDownSamplingOperator<klab::DoubleReal> op(2, 8);
        TEST_ASSERT(op.m()==2 && op.n()==8)
        TEST_ASSERT(op.indices().size() == 2)
        TEST_ASSERT(op.indices()[0] == 0)
        TEST_ASSERT(op.indices()[1] == 6)

        TRandomDownSamplingOperator<klab::DoubleReal> op2(8, 8);
        TEST_ASSERT(op2.m()==8 && op2.n()==8)
        TEST_ASSERT(op2.indices().size() == 8)
        TEST_ASSERT(op2.indices()[0] == 0)
        TEST_ASSERT(op2.indices()[1] == 1)
        TEST_ASSERT(op2.indices()[2] == 2)
        TEST_ASSERT(op2.indices()[3] == 3)   
        TEST_ASSERT(op2.indices()[4] == 4)
        TEST_ASSERT(op2.indices()[5] == 5)
        TEST_ASSERT(op2.indices()[6] == 6)
        TEST_ASSERT(op2.indices()[7] == 7) 


        // Limit cases.
        TRandomDownSamplingOperator<klab::DoubleReal> op0(0, 0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.indices().size() == 0)

        TRandomDownSamplingOperator<klab::DoubleReal> op01(8, 0);
        TEST_ASSERT(op01.m()==0 && op01.n()==0)
        TEST_ASSERT(op01.indices().size() == 0)

        TRandomDownSamplingOperator<klab::DoubleReal> op02(0, 8);
        TEST_ASSERT(op02.m()==0 && op02.n()==8)
        TEST_ASSERT(op02.indices().size() == 0)

        TRandomDownSamplingOperator<klab::DoubleReal> op03(12, 8);
        TEST_ASSERT(op03.m()==8 && op03.n()==8)
        TEST_ASSERT(op03.indices().size() == 8)
        TEST_ASSERT(op03.indices()[0] == 0)
        TEST_ASSERT(op03.indices()[1] == 1)
        TEST_ASSERT(op03.indices()[2] == 2)
        TEST_ASSERT(op03.indices()[3] == 3)   
        TEST_ASSERT(op03.indices()[4] == 4)
        TEST_ASSERT(op03.indices()[5] == 5)
        TEST_ASSERT(op03.indices()[6] == 6)
        TEST_ASSERT(op03.indices()[7] == 7) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomDownSamplingOperatorUnitTest::testMNIndexConstructor()
{
    try
    {
        klab::KRandom::Instance().setSeed(54321);

        TRandomDownSamplingOperator<klab::DoubleReal> op(2, 8, 3);
        TEST_ASSERT(op.m()==2 && op.n()==8)
        TEST_ASSERT(op.indices().size() == 2)
        TEST_ASSERT(op.indices()[0] == 3)
        TEST_ASSERT(op.indices()[1] == 6)

        TRandomDownSamplingOperator<klab::DoubleReal> op2(2, 8, 0);
        TEST_ASSERT(op2.m()==2 && op2.n()==8)
        TEST_ASSERT(op2.indices().size() == 2)
        TEST_ASSERT(op2.indices()[0] == 0)
        TEST_ASSERT(op2.indices()[1] == 7)


        // Limit cases.
        TRandomDownSamplingOperator<klab::DoubleReal> op0(2, 8, 8);
        TEST_ASSERT(op0.m()==2 && op0.n()==8)
        TEST_ASSERT(op0.indices().size() == 2)
        TEST_ASSERT(op0.indices()[0] == 1)
        TEST_ASSERT(op0.indices()[1] == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomDownSamplingOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        TRandomDownSamplingOperator<klab::DoubleReal> op(2, 8);
        TEST_ASSERT(op.m()==2 && op.n()==8)
        TEST_ASSERT(op.indices().size() == 2)
        TEST_ASSERT(op.indices()[0] == 0)
        TEST_ASSERT(op.indices()[1] == 6)


        TRandomDownSamplingOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.m()==2 && op2.n()==8)
        TEST_ASSERT(op2.indices().size() == 2)
        TEST_ASSERT(op2.indices()[0] == 0)
        TEST_ASSERT(op2.indices()[1] == 6)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomDownSamplingOperatorUnitTest::testApply()
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

        TRandomDownSamplingOperator<klab::DoubleReal> op(2, 8);
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 2)
        TEST_ASSERT(klab::Equals(y[0], 1.0))
        TEST_ASSERT(klab::Equals(y[1], 7.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomDownSamplingOperatorUnitTest::testApplyAdjoint()
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

        TRandomDownSamplingOperator<klab::DoubleReal> op(2, 8);
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 2)
        TEST_ASSERT(klab::Equals(y[0], 1.0))
        TEST_ASSERT(klab::Equals(y[1], 7.0))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], 1.0))
        TEST_ASSERT(klab::Equals(xr[1], 0.0))
        TEST_ASSERT(klab::Equals(xr[2], 0.0))
        TEST_ASSERT(klab::Equals(xr[3], 0.0))
        TEST_ASSERT(klab::Equals(xr[4], 0.0))
        TEST_ASSERT(klab::Equals(xr[5], 0.0))
        TEST_ASSERT(klab::Equals(xr[6], 7.0))
        TEST_ASSERT(klab::Equals(xr[7], 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
