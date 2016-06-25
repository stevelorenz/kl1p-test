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

#include "SL0HistoryUnitTest.h"
#include "../include/History.h"
#include "../include/SL0HistoryElement.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KSL0HistoryUnitTest::KSL0HistoryUnitTest() : Test::Suite()
{
    TEST_ADD(KSL0HistoryUnitTest::testDefaultConstructor)  
    TEST_ADD(KSL0HistoryUnitTest::testCopyConstructor)
    TEST_ADD(KSL0HistoryUnitTest::testAffectationOperator)

    TEST_ADD(KSL0HistoryUnitTest::testBracketOperator)

    TEST_ADD(KSL0HistoryUnitTest::testClear)
    TEST_ADD(KSL0HistoryUnitTest::testPush)
    TEST_ADD(KSL0HistoryUnitTest::testSize)
    TEST_ADD(KSL0HistoryUnitTest::testElement)
}

// ---------------------------------------------------------------------------------------------------- //

KSL0HistoryUnitTest::~KSL0HistoryUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSL0HistoryUnitTest::testDefaultConstructor()
{
    try
    {
        THistory<TSL0HistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0HistoryUnitTest::testCopyConstructor()
{
    try
    {
        THistory<TSL0HistoryElement<klab::DoubleReal> > history;
        history.push(TSL0HistoryElement<klab::DoubleReal>(1.2345));
        history.push(TSL0HistoryElement<klab::DoubleReal>(2.3456));
        history.push(TSL0HistoryElement<klab::DoubleReal>(3.4567));

        THistory<TSL0HistoryElement<klab::DoubleReal> > history2(history);

        TEST_ASSERT(history2.size() == 3)
        TEST_ASSERT(klab::Equals(history2[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history2[1].sigma(), 2.3456))
        TEST_ASSERT(klab::Equals(history2[2].sigma(), 3.4567))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0HistoryUnitTest::testAffectationOperator()
{
    try
    {
        THistory<TSL0HistoryElement<klab::DoubleReal> > history;
        history.push(TSL0HistoryElement<klab::DoubleReal>(1.2345));
        history.push(TSL0HistoryElement<klab::DoubleReal>(2.3456));
        history.push(TSL0HistoryElement<klab::DoubleReal>(3.4567));

        THistory<TSL0HistoryElement<klab::DoubleReal> > history2;
        history2 = history;

        TEST_ASSERT(history2.size() == 3)
        TEST_ASSERT(klab::Equals(history2[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history2[1].sigma(), 2.3456))
        TEST_ASSERT(klab::Equals(history2[2].sigma(), 3.4567))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0HistoryUnitTest::testBracketOperator()
{
    try
    {
        THistory<TSL0HistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TSL0HistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))

        history.push(TSL0HistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].sigma(), 2.3456))

        history.push(TSL0HistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].sigma(), 2.3456))
        TEST_ASSERT(klab::Equals(history[2].sigma(), 3.4567))


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

void KSL0HistoryUnitTest::testClear()
{
    try
    {
        THistory<TSL0HistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TSL0HistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))

        history.push(TSL0HistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].sigma(), 2.3456))

        history.push(TSL0HistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].sigma(), 2.3456))
        TEST_ASSERT(klab::Equals(history[2].sigma(), 3.4567))

        history.clear();
        TEST_ASSERT(history.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0HistoryUnitTest::testPush()
{
    try
    {
        THistory<TSL0HistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TSL0HistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))

        history.push(TSL0HistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].sigma(), 2.3456))

        history.push(TSL0HistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].sigma(), 2.3456))
        TEST_ASSERT(klab::Equals(history[2].sigma(), 3.4567))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0HistoryUnitTest::testSize()
{
    try
    {
        THistory<TSL0HistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TSL0HistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))

        history.push(TSL0HistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].sigma(), 2.3456))

        history.push(TSL0HistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].sigma(), 2.3456))
        TEST_ASSERT(klab::Equals(history[2].sigma(), 3.4567))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0HistoryUnitTest::testElement()
{
    try
    {
        THistory<TSL0HistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TSL0HistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history.element(0).sigma(), 1.2345))

        history.push(TSL0HistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history.element(0).sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history.element(1).sigma(), 2.3456))

        history.push(TSL0HistoryElement<klab::DoubleReal>(3.4567));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history.element(0).sigma(), 1.2345))
        TEST_ASSERT(klab::Equals(history.element(1).sigma(), 2.3456))
        TEST_ASSERT(klab::Equals(history.element(2).sigma(), 3.4567))

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
