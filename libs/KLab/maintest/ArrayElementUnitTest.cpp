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

#include "ArrayElementUnitTest.h"
#include "../include/ArrayElement.h"
#include "../include/FuncUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KArrayElementUnitTest::KArrayElementUnitTest() : Test::Suite()
{
    TEST_ADD(KArrayElementUnitTest::testDefaultConstructor)
    TEST_ADD(KArrayElementUnitTest::testIndexValueConstructor)
    TEST_ADD(KArrayElementUnitTest::testIndexValueConstructor)
    TEST_ADD(KArrayElementUnitTest::testCopyConstructor)
    TEST_ADD(KArrayElementUnitTest::testAffectationOperator)

    TEST_ADD(KArrayElementUnitTest::testLowerOperator)

    TEST_ADD(KArrayElementUnitTest::testSetIndex)
    TEST_ADD(KArrayElementUnitTest::testSetI)
    TEST_ADD(KArrayElementUnitTest::testSetValue)
    TEST_ADD(KArrayElementUnitTest::testIndex)
    TEST_ADD(KArrayElementUnitTest::testI)
    TEST_ADD(KArrayElementUnitTest::testValue)
}

// ---------------------------------------------------------------------------------------------------- //

KArrayElementUnitTest::~KArrayElementUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testDefaultConstructor()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1;
        TEST_ASSERT(element1.i() == 0)
        TEST_ASSERT(klab::Equals(element1.value(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testIndexConstructor()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1(123);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(klab::Equals(element1.value(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testIndexValueConstructor()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1(123, 1.234);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testCopyConstructor()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1(123, 1.234);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))

        TArrayElement<klab::DoubleReal> element1_bis(element1);
        TEST_ASSERT(element1_bis.i() == 123)
        TEST_ASSERT(klab::Equals(element1_bis.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testAffectationOperator()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1(123, 1.234);
        TEST_ASSERT(element1.i() == 123)
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))

        TArrayElement<klab::DoubleReal> element1_bis;
        element1_bis = element1;
        TEST_ASSERT(element1_bis.i() == 123)
        TEST_ASSERT(klab::Equals(element1_bis.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testLowerOperator()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1_left(456, 1.234);
        TArrayElement<klab::DoubleReal> element1_right(123, 4.567);
        TEST_ASSERT(element1_left < element1_right)
        TEST_ASSERT((element1_right < element1_left) == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testSetIndex()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1(0, 1.234);
        element1.setIndex<1>(123);
        TEST_ASSERT(element1.i() == 123)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testSetI()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1(0, 1.234);
        element1.setI(123);
        TEST_ASSERT(element1.i() == 123)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testSetValue()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1;
        element1.setValue(1.234);
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testIndex()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1(0);
        element1.setI(123);
        TEST_ASSERT(element1.index<1>() == 123)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testI()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1(0);
        element1.setI(123);
        TEST_ASSERT(element1.i() == 123)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArrayElementUnitTest::testValue()
{
    try
    {
        TArrayElement<klab::DoubleReal> element1(0, 1.234);
        TEST_ASSERT(klab::Equals(element1.value(), 1.234))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
