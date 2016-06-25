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

#include "CoSaMPHistoryUnitTest.h"
#include "../include/History.h"
#include "../include/CoSaMPHistoryElement.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KCoSaMPHistoryUnitTest::KCoSaMPHistoryUnitTest() : Test::Suite()
{
    TEST_ADD(KCoSaMPHistoryUnitTest::testDefaultConstructor)  
    TEST_ADD(KCoSaMPHistoryUnitTest::testCopyConstructor)
    TEST_ADD(KCoSaMPHistoryUnitTest::testAffectationOperator)

    TEST_ADD(KCoSaMPHistoryUnitTest::testBracketOperator)

    TEST_ADD(KCoSaMPHistoryUnitTest::testClear)
    TEST_ADD(KCoSaMPHistoryUnitTest::testPush)
    TEST_ADD(KCoSaMPHistoryUnitTest::testSize)
    TEST_ADD(KCoSaMPHistoryUnitTest::testElement)
}

// ---------------------------------------------------------------------------------------------------- //

KCoSaMPHistoryUnitTest::~KCoSaMPHistoryUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPHistoryUnitTest::testDefaultConstructor()
{
    try
    {
        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPHistoryUnitTest::testCopyConstructor()
{
    try
    {
        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history;
        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(1.2345));
        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(2.3456));
        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(3.4567));

        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history2(history);

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

void KCoSaMPHistoryUnitTest::testAffectationOperator()
{
    try
    {
        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history;
        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(1.2345));
        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(2.3456));
        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(3.4567));

        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history2;
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

void KCoSaMPHistoryUnitTest::testBracketOperator()
{
    try
    {
        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(3.4567));
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

void KCoSaMPHistoryUnitTest::testClear()
{
    try
    {
        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(3.4567));
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

void KCoSaMPHistoryUnitTest::testPush()
{
    try
    {
        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(3.4567));
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

void KCoSaMPHistoryUnitTest::testSize()
{
    try
    {
        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(3.4567));
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

void KCoSaMPHistoryUnitTest::testElement()
{
    try
    {
        THistory<TCoSaMPHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(1.2345));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history.element(0).residualNorm(), 1.2345))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(2.3456));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history.element(0).residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history.element(1).residualNorm(), 2.3456))

        history.push(TCoSaMPHistoryElement<klab::DoubleReal>(3.4567));
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
