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

#include "ProxyOperatorUnitTest.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KProxyOperatorUnitTest::KProxyOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KProxyOperatorUnitTest::testOpConstructor)  
    TEST_ADD(KProxyOperatorUnitTest::testNOpConstructor)  
    TEST_ADD(KProxyOperatorUnitTest::testMNOpConstructor)  
    TEST_ADD(KProxyOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KProxyOperatorUnitTest::testOp)
    TEST_ADD(KProxyOperatorUnitTest::testIsZero)    
}

// ---------------------------------------------------------------------------------------------------- //

KProxyOperatorUnitTest::~KProxyOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KProxyOperatorUnitTest::testOpConstructor()
{
    try
    {
        TTestProxyOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)


        // Limit cases.
        TTestProxyOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyOperatorUnitTest::testNOpConstructor()
{
    try
    {
        TTestProxyOperator<klab::DoubleReal> op(16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)


        // Limit cases.
        TTestProxyOperator<klab::DoubleReal> op0(16, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==16)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
  
void KProxyOperatorUnitTest::testMNOpConstructor()
{
    try
    {
        TTestProxyOperator<klab::DoubleReal> op(16, 32, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)


        // Limit cases.
        TTestProxyOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
  
void KProxyOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TTestProxyOperator<klab::DoubleReal> op(16, 32, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)

        TTestProxyOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==16 && opCopy.n()==32)
        TEST_ASSERT(opCopy.op() != 0)
        TEST_ASSERT(opCopy.isZero() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyOperatorUnitTest::testOp()
{
    try
    {
        TTestProxyOperator<klab::DoubleReal> op(16, 32, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)

        TTestProxyOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyOperatorUnitTest::testIsZero() 
{
    try
    {
        TTestProxyOperator<klab::DoubleReal> op(16, 32, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)

        TTestProxyOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
   