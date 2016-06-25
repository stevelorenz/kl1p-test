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

#include "OMPHistoryUnitTest.h"
#include "../include/History.h"
#include "../include/OMPHistoryElement.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KOMPHistoryUnitTest::KOMPHistoryUnitTest() : Test::Suite()
{
    TEST_ADD(KOMPHistoryUnitTest::testDefaultConstructor)  
    TEST_ADD(KOMPHistoryUnitTest::testCopyConstructor)
    TEST_ADD(KOMPHistoryUnitTest::testAffectationOperator)

    TEST_ADD(KOMPHistoryUnitTest::testBracketOperator)

    TEST_ADD(KOMPHistoryUnitTest::testClear)
    TEST_ADD(KOMPHistoryUnitTest::testPush)
    TEST_ADD(KOMPHistoryUnitTest::testSize)
    TEST_ADD(KOMPHistoryUnitTest::testElement)
}

// ---------------------------------------------------------------------------------------------------- //

KOMPHistoryUnitTest::~KOMPHistoryUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KOMPHistoryUnitTest::testDefaultConstructor()
{
    try
    {
        THistory<TOMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOMPHistoryUnitTest::testCopyConstructor()
{
    try
    {
        THistory<TOMPHistoryElement<klab::DoubleReal> > history;
        history.push(TOMPHistoryElement<klab::DoubleReal>(1.2345, 123));
        history.push(TOMPHistoryElement<klab::DoubleReal>(2.3456, 456));
        history.push(TOMPHistoryElement<klab::DoubleReal>(3.4567, 258));

        THistory<TOMPHistoryElement<klab::DoubleReal> > history2(history);

        TEST_ASSERT(history2.size() == 3)
        TEST_ASSERT(klab::Equals(history2[0].residualNorm(), 1.2345))
        TEST_ASSERT(history2[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history2[1].residualNorm(), 2.3456))
        TEST_ASSERT(history2[1].sparsity() == 456)
        TEST_ASSERT(klab::Equals(history2[2].residualNorm(), 3.4567))
        TEST_ASSERT(history2[2].sparsity() == 258)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOMPHistoryUnitTest::testAffectationOperator()
{
    try
    {
        THistory<TOMPHistoryElement<klab::DoubleReal> > history;
        history.push(TOMPHistoryElement<klab::DoubleReal>(1.2345, 123));
        history.push(TOMPHistoryElement<klab::DoubleReal>(2.3456, 456));
        history.push(TOMPHistoryElement<klab::DoubleReal>(3.4567, 258));

        THistory<TOMPHistoryElement<klab::DoubleReal> > history2;
        history2 = history;

        TEST_ASSERT(history2.size() == 3)
        TEST_ASSERT(klab::Equals(history2[0].residualNorm(), 1.2345))
        TEST_ASSERT(history2[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history2[1].residualNorm(), 2.3456))
        TEST_ASSERT(history2[1].sparsity() == 456)
        TEST_ASSERT(klab::Equals(history2[2].residualNorm(), 3.4567))
        TEST_ASSERT(history2[2].sparsity() == 258)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOMPHistoryUnitTest::testBracketOperator()
{
    try
    {
        THistory<TOMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TOMPHistoryElement<klab::DoubleReal>(1.2345, 123));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)

        history.push(TOMPHistoryElement<klab::DoubleReal>(2.3456, 456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(history[1].sparsity() == 456)

        history.push(TOMPHistoryElement<klab::DoubleReal>(3.4567, 258));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(history[1].sparsity() == 456)
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
        TEST_ASSERT(history[2].sparsity() == 258)


        // Limit cases.
        try                                 {history[3]; TEST_ASSERT(false)}
        catch(KOutOfBoundHistoryException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOMPHistoryUnitTest::testClear()
{
    try
    {
        THistory<TOMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TOMPHistoryElement<klab::DoubleReal>(1.2345, 123));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)

        history.push(TOMPHistoryElement<klab::DoubleReal>(2.3456, 456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(history[1].sparsity() == 456)

        history.push(TOMPHistoryElement<klab::DoubleReal>(3.4567, 258));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(history[1].sparsity() == 456)
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
        TEST_ASSERT(history[2].sparsity() == 258)

        history.clear();
        TEST_ASSERT(history.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOMPHistoryUnitTest::testPush()
{
    try
    {
        THistory<TOMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TOMPHistoryElement<klab::DoubleReal>(1.2345, 123));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)

        history.push(TOMPHistoryElement<klab::DoubleReal>(2.3456, 456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(history[1].sparsity() == 456)

        history.push(TOMPHistoryElement<klab::DoubleReal>(3.4567, 258));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(history[1].sparsity() == 456)
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
        TEST_ASSERT(history[2].sparsity() == 258)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOMPHistoryUnitTest::testSize()
{
    try
    {
        THistory<TOMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TOMPHistoryElement<klab::DoubleReal>(1.2345, 123));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)

        history.push(TOMPHistoryElement<klab::DoubleReal>(2.3456, 456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(history[1].sparsity() == 456)

        history.push(TOMPHistoryElement<klab::DoubleReal>(3.4567, 258));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(history[0].sparsity() == 123)
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(history[1].sparsity() == 456)
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
        TEST_ASSERT(history[2].sparsity() == 258)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOMPHistoryUnitTest::testElement()
{
    try
    {
        THistory<TOMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TOMPHistoryElement<klab::DoubleReal>(1.2345, 123));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history.element(0).residualNorm(), 1.2345))
        TEST_ASSERT(history.element(0).sparsity() == 123)

        history.push(TOMPHistoryElement<klab::DoubleReal>(2.3456, 456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history.element(0).residualNorm(), 1.2345))
        TEST_ASSERT(history.element(0).sparsity() == 123)
        TEST_ASSERT(klab::Equals(history.element(1).residualNorm(), 2.3456))
        TEST_ASSERT(history.element(1).sparsity() == 456)

        history.push(TOMPHistoryElement<klab::DoubleReal>(3.4567, 258));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history.element(0).residualNorm(), 1.2345))
        TEST_ASSERT(history.element(0).sparsity() == 123)
        TEST_ASSERT(klab::Equals(history.element(1).residualNorm(), 2.3456))
        TEST_ASSERT(history.element(1).sparsity() == 456)
        TEST_ASSERT(klab::Equals(history.element(2).residualNorm(), 3.4567))
        TEST_ASSERT(history.element(2).sparsity() == 258)


        // Limit cases.
        try                                 {history.element(3); TEST_ASSERT(false)}
        catch(KOutOfBoundHistoryException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
