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

#include "GridElementUnitTest.h"
#include "../include/GridElement.h"
#include "../include/FuncUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KGridElementUnitTest::KGridElementUnitTest() : Test::Suite()
{
    TEST_ADD(KGridElementUnitTest::testDefaultConstructor)
    TEST_ADD(KGridElementUnitTest::testIndexesValueConstructor)
    TEST_ADD(KGridElementUnitTest::testIndexesValueConstructor)
    TEST_ADD(KGridElementUnitTest::testCopyConstructor)
    TEST_ADD(KGridElementUnitTest::testAffectationOperator)

    TEST_ADD(KGridElementUnitTest::testLowerOperator)

    TEST_ADD(KGridElementUnitTest::testSetIndex)
    TEST_ADD(KGridElementUnitTest::testSetI)
    TEST_ADD(KGridElementUnitTest::testSetJ)
    TEST_ADD(KGridElementUnitTest::testSetValue)
    TEST_ADD(KGridElementUnitTest::testIndex)
    TEST_ADD(KGridElementUnitTest::testI)
    TEST_ADD(KGridElementUnitTest::testJ)
    TEST_ADD(KGridElementUnitTest::testValue)
}

// ---------------------------------------------------------------------------------------------------- //

KGridElementUnitTest::~KGridElementUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testDefaultConstructor()
{
    try
    {
        TGridElement<klab::DoubleReal> element1;
        TEST_ASSERT(element1.i() == 0)
        TEST_ASSERT(element1.j() == 0)
        TEST_ASSERT(klab::Equals(element1.value(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testIndexesConstructor()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(123, 456);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 456)
        TEST_ASSERT(klab::Equals(element1.value(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testIndexesValueConstructor()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(123, 456, 1.234);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 456)
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testCopyConstructor()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(123, 456, 1.234);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 456)
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))

        TGridElement<klab::DoubleReal> element1_bis(element1);
        TEST_ASSERT(element1_bis.i() == 123)
        TEST_ASSERT(element1_bis.j() == 456)
        TEST_ASSERT(klab::Equals(element1_bis.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testAffectationOperator()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(123, 456, 1.234);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 456)
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))

        TGridElement<klab::DoubleReal> element1_bis;
        element1_bis = element1;
        TEST_ASSERT(element1_bis.i() == 123)
        TEST_ASSERT(element1_bis.j() == 456)
        TEST_ASSERT(klab::Equals(element1_bis.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testLowerOperator()
{
    try
    {
        TGridElement<klab::DoubleReal> element1_left(789, 456, 1.234);
        TGridElement<klab::DoubleReal> element1_right(147, 123, 4.567);
        TEST_ASSERT(element1_left < element1_right)
        TEST_ASSERT((element1_right < element1_left) == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testSetIndex()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(0, 0, 1.234);
        element1.setIndex<1>(123);
        element1.setIndex<2>(456);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 456)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testSetI()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(0, 0, 1.234);
        element1.setI(123);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 0)

        element1.setJ(456);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 456)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testSetJ()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(0, 0, 1.234);
        element1.setI(123);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 0)

        element1.setJ(456);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 456)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testSetValue()
{
    try
    {
        TGridElement<klab::DoubleReal> element1;
        element1.setValue(1.234);
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testIndex()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(0, 0);
        element1.setI(123);
        element1.setJ(456);
        TEST_ASSERT(element1.index<1>() == 123)
        TEST_ASSERT(element1.index<2>() == 456)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testI()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(0, 0, 1.234);
        element1.setI(123);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 0)

        element1.setJ(456);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 456)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testJ()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(0, 0, 1.234);
        element1.setI(123);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 0)

        element1.setJ(456);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(element1.j() == 456)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGridElementUnitTest::testValue()
{
    try
    {
        TGridElement<klab::DoubleReal> element1(0, 0, 1.234);
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
