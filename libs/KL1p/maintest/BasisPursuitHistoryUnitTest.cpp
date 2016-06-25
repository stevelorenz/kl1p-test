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

#include "BasisPursuitHistoryUnitTest.h"
#include "../include/History.h"
#include "../include/BasisPursuitHistoryElement.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KBasisPursuitHistoryUnitTest::KBasisPursuitHistoryUnitTest() : Test::Suite()
{
    TEST_ADD(KBasisPursuitHistoryUnitTest::testDefaultConstructor)  
    TEST_ADD(KBasisPursuitHistoryUnitTest::testCopyConstructor)
    TEST_ADD(KBasisPursuitHistoryUnitTest::testAffectationOperator)

    TEST_ADD(KBasisPursuitHistoryUnitTest::testBracketOperator)

    TEST_ADD(KBasisPursuitHistoryUnitTest::testClear)
    TEST_ADD(KBasisPursuitHistoryUnitTest::testPush)
    TEST_ADD(KBasisPursuitHistoryUnitTest::testSize)
    TEST_ADD(KBasisPursuitHistoryUnitTest::testElement)
}

// ---------------------------------------------------------------------------------------------------- //

KBasisPursuitHistoryUnitTest::~KBasisPursuitHistoryUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitHistoryUnitTest::testDefaultConstructor()
{
    try
    {
        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitHistoryUnitTest::testCopyConstructor()
{
    try
    {
        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history;
        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(1.2345, 123.456));
        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(2.3456, 456.789));
        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(3.4567, 258.369));

        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history2(history);

        TEST_ASSERT(history2.size() == 3)
        TEST_ASSERT(klab::Equals(history2[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history2[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history2[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history2[1].dualityGap(), 456.789))
        TEST_ASSERT(klab::Equals(history2[2].residualNorm(), 3.4567))
        TEST_ASSERT(klab::Equals(history2[2].dualityGap(), 258.369))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitHistoryUnitTest::testAffectationOperator()
{
    try
    {
        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history;
        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(1.2345, 123.456));
        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(2.3456, 456.789));
        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(3.4567, 258.369));

        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history2;
        history2 = history;

        TEST_ASSERT(history2.size() == 3)
        TEST_ASSERT(klab::Equals(history2[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history2[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history2[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history2[1].dualityGap(), 456.789))
        TEST_ASSERT(klab::Equals(history2[2].residualNorm(), 3.4567))
        TEST_ASSERT(klab::Equals(history2[2].dualityGap(), 258.369))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitHistoryUnitTest::testBracketOperator()
{
    try
    {
        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(1.2345, 123.456));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(2.3456, 456.789));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[1].dualityGap(), 456.789))

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(3.4567, 258.369));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[1].dualityGap(), 456.789))
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
        TEST_ASSERT(klab::Equals(history[2].dualityGap(), 258.369))


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

void KBasisPursuitHistoryUnitTest::testClear()
{
    try
    {
        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(1.2345, 123.456));
        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(2.3456, 456.789));
        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(3.4567, 258.369));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[1].dualityGap(), 456.789))
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
        TEST_ASSERT(klab::Equals(history[2].dualityGap(), 258.369))

        history.clear();
        TEST_ASSERT(history.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitHistoryUnitTest::testPush()
{
    try
    {
        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(1.2345, 123.456));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(2.3456, 456.789));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[1].dualityGap(), 456.789))

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(3.4567, 258.369));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[1].dualityGap(), 456.789))
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
        TEST_ASSERT(klab::Equals(history[2].dualityGap(), 258.369))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitHistoryUnitTest::testSize()
{
    try
    {
        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(1.2345, 123.456));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(2.3456, 456.789));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[1].dualityGap(), 456.789))

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(3.4567, 258.369));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[1].dualityGap(), 456.789))
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
        TEST_ASSERT(klab::Equals(history[2].dualityGap(), 258.369))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitHistoryUnitTest::testElement()
{
    try
    {
        THistory<TBasisPursuitHistoryElement<klab::DoubleReal> > history;
        TEST_ASSERT(history.size() == 0)

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(1.2345, 123.456));
        TEST_ASSERT(history.size() == 1)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(2.3456, 456.789));
        TEST_ASSERT(history.size() == 2)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[1].dualityGap(), 456.789))

        history.push(TBasisPursuitHistoryElement<klab::DoubleReal>(3.4567, 258.369));
        TEST_ASSERT(history.size() == 3)
        TEST_ASSERT(klab::Equals(history[0].residualNorm(), 1.2345))
        TEST_ASSERT(klab::Equals(history[0].dualityGap(), 123.456))
        TEST_ASSERT(klab::Equals(history[1].residualNorm(), 2.3456))
        TEST_ASSERT(klab::Equals(history[1].dualityGap(), 456.789))
        TEST_ASSERT(klab::Equals(history[2].residualNorm(), 3.4567))
        TEST_ASSERT(klab::Equals(history[2].dualityGap(), 258.369))


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
