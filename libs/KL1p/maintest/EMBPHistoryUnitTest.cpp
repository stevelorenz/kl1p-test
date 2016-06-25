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

#include "EMBPHistoryUnitTest.h"
#include "../include/History.h"
#include "../include/EMBPHistoryElement.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KEMBPHistoryUnitTest::KEMBPHistoryUnitTest() : Test::Suite()
{
    TEST_ADD(KEMBPHistoryUnitTest::testDefaultConstructor)  
    TEST_ADD(KEMBPHistoryUnitTest::testCopyConstructor)
    TEST_ADD(KEMBPHistoryUnitTest::testAffectationOperator)

    TEST_ADD(KEMBPHistoryUnitTest::testBracketOperator)

    TEST_ADD(KEMBPHistoryUnitTest::testClear)
    TEST_ADD(KEMBPHistoryUnitTest::testPush)
    TEST_ADD(KEMBPHistoryUnitTest::testSize)
    TEST_ADD(KEMBPHistoryUnitTest::testElement)
}

// ---------------------------------------------------------------------------------------------------- //

KEMBPHistoryUnitTest::~KEMBPHistoryUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPHistoryUnitTest::testDefaultConstructor()
{
    try
    {
        THistory<TEMBPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPHistoryUnitTest::testCopyConstructor()
{
    try
    {
        THistory<TEMBPHistoryElement<klab::DoubleReal> > history;
        history.push(TEMBPHistoryElement<klab::DoubleReal>(1.2345));
        history.push(TEMBPHistoryElement<klab::DoubleReal>(2.3456));
        history.push(TEMBPHistoryElement<klab::DoubleReal>(3.4567));

        THistory<TEMBPHistoryElement<klab::DoubleReal> > history2(history);

        TEST_ASSERT(history2.size() == 3)
        TEST_ASSERT(klab::Equals(history2[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history2[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history2[2].residualNorm(), 3.4567))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPHistoryUnitTest::testAffectationOperator()
{
    try
    {
        THistory<TEMBPHistoryElement<klab::DoubleReal> > history;
        history.push(TEMBPHistoryElement<klab::DoubleReal>(1.2345));
        history.push(TEMBPHistoryElement<klab::DoubleReal>(2.3456));
        history.push(TEMBPHistoryElement<klab::DoubleReal>(3.4567));

        THistory<TEMBPHistoryElement<klab::DoubleReal> > history2;
        history2 = history;

        TEST_ASSERT(history2.size() == 3)
        TEST_ASSERT(klab::Equals(history2[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history2[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history2[2].residualNorm(), 3.4567))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPHistoryUnitTest::testBracketOperator()
{
    try
    {
        THistory<TEMBPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TEMBPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))


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

void KEMBPHistoryUnitTest::testClear()
{
    try
    {
        THistory<TEMBPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TEMBPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))

        history.clear();
        TEST_ASSERT(history.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPHistoryUnitTest::testPush()
{
    try
    {
        THistory<TEMBPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TEMBPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPHistoryUnitTest::testSize()
{
    try
    {
        THistory<TEMBPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TEMBPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPHistoryUnitTest::testElement()
{
    try
    {
        THistory<TEMBPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TEMBPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history.element(0).residualNorm(), 1.2345))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history.element(0).residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history.element(1).residualNorm(), 2.3456))

        history.push(TEMBPHistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history.element(0).residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history.element(1).residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history.element(2).residualNorm(), 3.4567))


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
