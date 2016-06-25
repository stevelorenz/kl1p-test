// KLab - A portable C++ collection of classes for general purpose.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KLab C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#include "IndexedContainerElementUnitTest.h"
#include "../include/IndexedContainerElement.h"
#include "../include/FuncUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KIndexedContainerElementUnitTest::KIndexedContainerElementUnitTest() : Test::Suite()
{
    TEST_ADD(KIndexedContainerElementUnitTest::testDefaultConstructor)
    TEST_ADD(KIndexedContainerElementUnitTest::testValueConstructor)
    TEST_ADD(KIndexedContainerElementUnitTest::testCopyConstructor)
    TEST_ADD(KIndexedContainerElementUnitTest::testAffectationOperator)

    TEST_ADD(KIndexedContainerElementUnitTest::testLowerOperator)

    TEST_ADD(KIndexedContainerElementUnitTest::testSetIndex)
    TEST_ADD(KIndexedContainerElementUnitTest::testSetValue)
    TEST_ADD(KIndexedContainerElementUnitTest::testIndex)
    TEST_ADD(KIndexedContainerElementUnitTest::testValue)
}

// ---------------------------------------------------------------------------------------------------- //

KIndexedContainerElementUnitTest::~KIndexedContainerElementUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KIndexedContainerElementUnitTest::testDefaultConstructor()
{
    try
    {
        TIndexedContainerElement<klab::DoubleReal, 1> element1;
        TEST_ASSERT(element1.index<1>() == 0)
        TEST_ASSERT(klab::Equals(element1.value(), 0.0))

        TIndexedContainerElement<klab::DoubleReal, 2> element2;
        TEST_ASSERT(element2.index<1>() == 0)
        TEST_ASSERT(element2.index<2>() == 0)
        TEST_ASSERT(klab::Equals(element2.value(), 0.0))

        TIndexedContainerElement<klab::DoubleReal, 3> element3;
        TEST_ASSERT(element3.index<1>() == 0)
        TEST_ASSERT(element3.index<2>() == 0)
        TEST_ASSERT(element3.index<3>() == 0)
        TEST_ASSERT(klab::Equals(element3.value(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIndexedContainerElementUnitTest::testValueConstructor()
{
    try
    {
        TIndexedContainerElement<klab::DoubleReal, 1> element1(1.234);
        TEST_ASSERT(element1.index<1>() == 0)
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 2> element2(1.234);
        TEST_ASSERT(element2.index<1>() == 0)
        TEST_ASSERT(element2.index<2>() == 0)
        TEST_ASSERT(klab::Equals(element2.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 3> element3(1.234);
        TEST_ASSERT(element3.index<1>() == 0)
        TEST_ASSERT(element3.index<2>() == 0)
        TEST_ASSERT(element3.index<3>() == 0)
        TEST_ASSERT(klab::Equals(element3.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIndexedContainerElementUnitTest::testCopyConstructor()
{
    try
    {
        TIndexedContainerElement<klab::DoubleReal, 1> element1(1.234);
        element1.setIndex<1>(123);
        TEST_ASSERT(element1.index<1>() == 123)
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 1> element1_bis(element1);
        TEST_ASSERT(element1_bis.index<1>() == 123)
        TEST_ASSERT(klab::Equals(element1_bis.value(), 1.234))


        TIndexedContainerElement<klab::DoubleReal, 2> element2(1.234);
        element2.setIndex<1>(123);
        element2.setIndex<2>(456);
        TEST_ASSERT(element2.index<1>() == 123)
        TEST_ASSERT(element2.index<2>() == 456)
        TEST_ASSERT(klab::Equals(element2.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 2> element2_bis(element2);
        TEST_ASSERT(element2_bis.index<1>() == 123)
        TEST_ASSERT(element2_bis.index<2>() == 456)
        TEST_ASSERT(klab::Equals(element2_bis.value(), 1.234))


        TIndexedContainerElement<klab::DoubleReal, 3> element3(1.234);
        element3.setIndex<1>(123);
        element3.setIndex<2>(456);
        element3.setIndex<3>(789);
        TEST_ASSERT(element3.index<1>() == 123)
        TEST_ASSERT(element3.index<2>() == 456)
        TEST_ASSERT(element3.index<3>() == 789)
        TEST_ASSERT(klab::Equals(element3.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 3> element3_bis(element3);
        TEST_ASSERT(element3_bis.index<1>() == 123)
        TEST_ASSERT(element3_bis.index<2>() == 456)
        TEST_ASSERT(element3_bis.index<3>() == 789)
        TEST_ASSERT(klab::Equals(element3_bis.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIndexedContainerElementUnitTest::testAffectationOperator()
{
    try
    {
        TIndexedContainerElement<klab::DoubleReal, 1> element1(1.234);
        element1.setIndex<1>(123);
        TEST_ASSERT(element1.index<1>() == 123)
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 1> element1_bis;
        element1_bis = element1;
        TEST_ASSERT(element1_bis.index<1>() == 123)
        TEST_ASSERT(klab::Equals(element1_bis.value(), 1.234))


        TIndexedContainerElement<klab::DoubleReal, 2> element2(1.234);
        element2.setIndex<1>(123);
        element2.setIndex<2>(456);
        TEST_ASSERT(element2.index<1>() == 123)
        TEST_ASSERT(element2.index<2>() == 456)
        TEST_ASSERT(klab::Equals(element2.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 2> element2_bis;
        element2_bis = element2;
        TEST_ASSERT(element2_bis.index<1>() == 123)
        TEST_ASSERT(element2_bis.index<2>() == 456)
        TEST_ASSERT(klab::Equals(element2_bis.value(), 1.234))


        TIndexedContainerElement<klab::DoubleReal, 3> element3(1.234);
        element3.setIndex<1>(123);
        element3.setIndex<2>(456);
        element3.setIndex<3>(789);
        TEST_ASSERT(element3.index<1>() == 123)
        TEST_ASSERT(element3.index<2>() == 456)
        TEST_ASSERT(element3.index<3>() == 789)
        TEST_ASSERT(klab::Equals(element3.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 3> element3_bis;
        element3_bis = element3;
        TEST_ASSERT(element3_bis.index<1>() == 123)
        TEST_ASSERT(element3_bis.index<2>() == 456)
        TEST_ASSERT(element3_bis.index<3>() == 789)
        TEST_ASSERT(klab::Equals(element3_bis.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIndexedContainerElementUnitTest::testLowerOperator()
{
    try
    {
        TIndexedContainerElement<klab::DoubleReal, 1> element1_left(1.234);
        TIndexedContainerElement<klab::DoubleReal, 1> element1_right(4.567);
        TEST_ASSERT(element1_left < element1_right)
        TEST_ASSERT((element1_right < element1_left) == false)

        TIndexedContainerElement<klab::DoubleReal, 2> element2_left(1.234);
        TIndexedContainerElement<klab::DoubleReal, 2> element2_right(4.567);
        TEST_ASSERT(element2_left < element2_right)
        TEST_ASSERT((element2_right < element2_left) == false)

        TIndexedContainerElement<klab::DoubleReal, 3> element3_left(1.234);
        TIndexedContainerElement<klab::DoubleReal, 3> element3_right(4.567);
        TEST_ASSERT(element3_left < element3_right)
        TEST_ASSERT((element3_right < element3_left) == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIndexedContainerElementUnitTest::testSetIndex()
{
    try
    {
        TIndexedContainerElement<klab::DoubleReal, 1> element1(1.234);
        element1.setIndex<1>(123);
        TEST_ASSERT(element1.index<1>() == 123)

        TIndexedContainerElement<klab::DoubleReal, 2> element2(1.234);
        element2.setIndex<1>(123);
        element2.setIndex<2>(456);
        TEST_ASSERT(element2.index<1>() == 123)
        TEST_ASSERT(element2.index<2>() == 456)

        TIndexedContainerElement<klab::DoubleReal, 3> element3(1.234);
        element3.setIndex<1>(123);
        element3.setIndex<2>(456);
        element3.setIndex<3>(789);
        TEST_ASSERT(element3.index<1>() == 123)
        TEST_ASSERT(element3.index<2>() == 456)
        TEST_ASSERT(element3.index<3>() == 789)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIndexedContainerElementUnitTest::testSetValue()
{
    try
    {
        TIndexedContainerElement<klab::DoubleReal, 1> element1;
        element1.setValue(1.234);
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 2> element2;
        element2.setValue(1.234);
        TEST_ASSERT(klab::Equals(element2.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 3> element3;
        element3.setValue(1.234);
        TEST_ASSERT(klab::Equals(element3.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIndexedContainerElementUnitTest::testIndex()
{
    try
    {
        TIndexedContainerElement<klab::DoubleReal, 1> element1(1.234);
        element1.setIndex<1>(123);
        TEST_ASSERT(element1.index<1>() == 123)

        TIndexedContainerElement<klab::DoubleReal, 2> element2(1.234);
        element2.setIndex<1>(123);
        element2.setIndex<2>(456);
        TEST_ASSERT(element2.index<1>() == 123)
        TEST_ASSERT(element2.index<2>() == 456)

        TIndexedContainerElement<klab::DoubleReal, 3> element3(1.234);
        element3.setIndex<1>(123);
        element3.setIndex<2>(456);
        element3.setIndex<3>(789);
        TEST_ASSERT(element3.index<1>() == 123)
        TEST_ASSERT(element3.index<2>() == 456)
        TEST_ASSERT(element3.index<3>() == 789)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KIndexedContainerElementUnitTest::testValue()
{
    try
    {
        TIndexedContainerElement<klab::DoubleReal, 1> element1(1.234);
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 2> element2(1.234);
        TEST_ASSERT(klab::Equals(element2.value(), 1.234))

        TIndexedContainerElement<klab::DoubleReal, 3> element3(1.234);
        TEST_ASSERT(klab::Equals(element3.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
