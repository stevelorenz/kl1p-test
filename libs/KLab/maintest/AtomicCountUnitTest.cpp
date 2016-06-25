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

#include "AtomicCountUnitTest.h"
#include "../include/AtomicCount.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KAtomicCountUnitTest::KAtomicCountUnitTest() : Test::Suite()
{
    TEST_ADD(KAtomicCountUnitTest::testDefaultConstructor)
    TEST_ADD(KAtomicCountUnitTest::testValueConstructor)

    TEST_ADD(KAtomicCountUnitTest::testIncrementOperator)
    TEST_ADD(KAtomicCountUnitTest::testDecrementOperator)
    TEST_ADD(KAtomicCountUnitTest::testCastOperator)
}

// ---------------------------------------------------------------------------------------------------- //

KAtomicCountUnitTest::~KAtomicCountUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KAtomicCountUnitTest::testDefaultConstructor()
{
    try
    {
        TAtomicCount<klab::UInt32> count1;
        TEST_ASSERT(count1 == 0)

        KAtomicUInt8Count count2;
        TEST_ASSERT(count2 == 0)

        KAtomicInt8Count count3;
        TEST_ASSERT(count3 == 0)

        KAtomicUInt16Count count4;
        TEST_ASSERT(count4 == 0)

        KAtomicInt16Count count5;
        TEST_ASSERT(count5 == 0)

        KAtomicUInt32Count count6;
        TEST_ASSERT(count6 == 0)

        KAtomicInt32Count count7;
        TEST_ASSERT(count7 == 0)

        KAtomicUInt64Count count8;
        TEST_ASSERT(count8 == 0)

        KAtomicInt64Count count9;
        TEST_ASSERT(count9 == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAtomicCountUnitTest::testValueConstructor()
{
    try
    {
        TAtomicCount<klab::UInt32> count1(123);
        TEST_ASSERT(count1 == 123)

        KAtomicUInt8Count count2(123);
        TEST_ASSERT(count2 == 123)

        KAtomicInt8Count count3(123);
        TEST_ASSERT(count3 == 123)

        KAtomicUInt16Count count4(123);
        TEST_ASSERT(count4 == 123)

        KAtomicInt16Count count5(123);
        TEST_ASSERT(count5 == 123)

        KAtomicUInt32Count count6(123);
        TEST_ASSERT(count6 == 123)

        KAtomicInt32Count count7(123);
        TEST_ASSERT(count7 == 123)

        KAtomicUInt64Count count8(123);
        TEST_ASSERT(count8 == 123)

        KAtomicInt64Count count9(123);
        TEST_ASSERT(count9 == 123)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAtomicCountUnitTest::testIncrementOperator()
{
    try
    {
        TAtomicCount<klab::UInt32> count1;
        TEST_ASSERT(count1 == 0)

        ++count1;
        TEST_ASSERT(count1 == 1)

        ++count1;
        TEST_ASSERT(count1 == 2)

        count1++;
        TEST_ASSERT(count1 == 3)

        --count1;
        TEST_ASSERT(count1 == 2)

        --count1;
        TEST_ASSERT(count1 == 1)

        count1--;
        TEST_ASSERT(count1 == 0)


        TAtomicCount<klab::Int64> count2;
        TEST_ASSERT(count2 == 0)

        ++count2;
        TEST_ASSERT(count2 == 1)

        ++count2;
        TEST_ASSERT(count2 == 2)

        count2++;
        TEST_ASSERT(count2 == 3)

        --count2;
        TEST_ASSERT(count2 == 2)

        --count2;
        TEST_ASSERT(count2 == 1)

        count2--;
        TEST_ASSERT(count2 == 0)

        --count2;
        TEST_ASSERT(count2 == -1)

        count2++;
        TEST_ASSERT(count2 == 0)


        KAtomicInt8Count count3;
        TEST_ASSERT(count3 == 0)

        ++count3;
        TEST_ASSERT(count3 == 1)

        ++count3;
        TEST_ASSERT(count3 == 2)

        count3++;
        TEST_ASSERT(count3 == 3)

        --count3;
        TEST_ASSERT(count3 == 2)

        --count3;
        TEST_ASSERT(count3 == 1)

        count3--;
        TEST_ASSERT(count3 == 0)

        count3--;
        TEST_ASSERT(count3 == -1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAtomicCountUnitTest::testDecrementOperator()
{
    try
    {
        TAtomicCount<klab::UInt32> count1;
        TEST_ASSERT(count1 == 0)

        ++count1;
        TEST_ASSERT(count1 == 1)

        ++count1;
        TEST_ASSERT(count1 == 2)

        count1++;
        TEST_ASSERT(count1 == 3)

        --count1;
        TEST_ASSERT(count1 == 2)

        --count1;
        TEST_ASSERT(count1 == 1)

        count1--;
        TEST_ASSERT(count1 == 0)


        TAtomicCount<klab::Int64> count2;
        TEST_ASSERT(count2 == 0)

        ++count2;
        TEST_ASSERT(count2 == 1)

        ++count2;
        TEST_ASSERT(count2 == 2)

        count2++;
        TEST_ASSERT(count2 == 3)

        --count2;
        TEST_ASSERT(count2 == 2)

        --count2;
        TEST_ASSERT(count2 == 1)

        count2--;
        TEST_ASSERT(count2 == 0)

        --count2;
        TEST_ASSERT(count2 == -1)

        count2++;
        TEST_ASSERT(count2 == 0)


        KAtomicInt8Count count3;
        TEST_ASSERT(count3 == 0)

        ++count3;
        TEST_ASSERT(count3 == 1)

        ++count3;
        TEST_ASSERT(count3 == 2)

        count3++;
        TEST_ASSERT(count3 == 3)

        --count3;
        TEST_ASSERT(count3 == 2)

        --count3;
        TEST_ASSERT(count3 == 1)

        count3--;
        TEST_ASSERT(count3 == 0)

        count3--;
        TEST_ASSERT(count3 == -1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAtomicCountUnitTest::testCastOperator()
{
    try
    {
        TAtomicCount<klab::UInt32> count1(123);
        TEST_ASSERT(count1 == 123)

        KAtomicUInt8Count count2(123);
        TEST_ASSERT(count2 == 123)

        KAtomicInt8Count count3(123);
        TEST_ASSERT(count3 == 123)

        KAtomicUInt16Count count4(123);
        TEST_ASSERT(count4 == 123)

        KAtomicInt16Count count5(123);
        TEST_ASSERT(count5 == 123)

        KAtomicUInt32Count count6(123);
        TEST_ASSERT(count6 == 123)

        KAtomicInt32Count count7(123);
        TEST_ASSERT(count7 == 123)

        KAtomicUInt64Count count8(123);
        TEST_ASSERT(count8 == 123)

        KAtomicInt64Count count9(123);
        TEST_ASSERT(count9 == 123)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
