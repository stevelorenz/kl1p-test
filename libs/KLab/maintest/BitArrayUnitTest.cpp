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

#include "BitArrayUnitTest.h"
#include "../include/BitArray.h"
#include "../include/FuncUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KBitArrayUnitTest::KBitArrayUnitTest() : Test::Suite()
{
    TEST_ADD(KBitArrayUnitTest::testDefaultConstructor)
    TEST_ADD(KBitArrayUnitTest::testSizeConstructor)
    TEST_ADD(KBitArrayUnitTest::testSizeValueConstructor)
    TEST_ADD(KBitArrayUnitTest::testCopyConstructor)
    TEST_ADD(KBitArrayUnitTest::testAffectationOperator)

    TEST_ADD(KBitArrayUnitTest::testBracketOperator)
    TEST_ADD(KBitArrayUnitTest::testEqualOperator)
    TEST_ADD(KBitArrayUnitTest::testNotEqualOperator)
    TEST_ADD(KBitArrayUnitTest::testLowerOperator)
    TEST_ADD(KBitArrayUnitTest::testLowerOrEqualOperator)
    TEST_ADD(KBitArrayUnitTest::testGreaterOrEqualOperator)
    TEST_ADD(KBitArrayUnitTest::testGreaterOperator)

    TEST_ADD(KBitArrayUnitTest::testResize)
    TEST_ADD(KBitArrayUnitTest::testFill)
    TEST_ADD(KBitArrayUnitTest::testClear)
    TEST_ADD(KBitArrayUnitTest::testSize)
    TEST_ADD(KBitArrayUnitTest::testPush)
    TEST_ADD(KBitArrayUnitTest::testPop)
    TEST_ADD(KBitArrayUnitTest::testSetBit)
    TEST_ADD(KBitArrayUnitTest::testSet)
    TEST_ADD(KBitArrayUnitTest::testReset)
    TEST_ADD(KBitArrayUnitTest::testBit)
}

// ---------------------------------------------------------------------------------------------------- //

KBitArrayUnitTest::~KBitArrayUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testDefaultConstructor()
{
    try
    {
        KBitArray bits;
        TEST_ASSERT(bits.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testSizeConstructor()
{
    try
    {
        KBitArray bits(16);
        TEST_ASSERT(bits.size() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testSizeValueConstructor()
{
    try
    {
        KBitArray bits(16, false);
        TEST_ASSERT(bits.size() == 16)
        TEST_ASSERT(bits[0]  == false)
        TEST_ASSERT(bits[1]  == false)
        TEST_ASSERT(bits[2]  == false)
        TEST_ASSERT(bits[3]  == false)
        TEST_ASSERT(bits[4]  == false)
        TEST_ASSERT(bits[5]  == false)
        TEST_ASSERT(bits[6]  == false)
        TEST_ASSERT(bits[7]  == false)
        TEST_ASSERT(bits[8]  == false)
        TEST_ASSERT(bits[9]  == false)
        TEST_ASSERT(bits[10] == false)
        TEST_ASSERT(bits[11] == false)
        TEST_ASSERT(bits[12] == false)
        TEST_ASSERT(bits[13] == false)
        TEST_ASSERT(bits[14] == false)
        TEST_ASSERT(bits[15] == false)

        KBitArray bits2(16, true);
        TEST_ASSERT(bits2.size() == 16)
        TEST_ASSERT(bits2[0]  == true)
        TEST_ASSERT(bits2[1]  == true)
        TEST_ASSERT(bits2[2]  == true)
        TEST_ASSERT(bits2[3]  == true)
        TEST_ASSERT(bits2[4]  == true)
        TEST_ASSERT(bits2[5]  == true)
        TEST_ASSERT(bits2[6]  == true)
        TEST_ASSERT(bits2[7]  == true)
        TEST_ASSERT(bits2[8]  == true)
        TEST_ASSERT(bits2[9]  == true)
        TEST_ASSERT(bits2[10] == true)
        TEST_ASSERT(bits2[11] == true)
        TEST_ASSERT(bits2[12] == true)
        TEST_ASSERT(bits2[13] == true)
        TEST_ASSERT(bits2[14] == true)
        TEST_ASSERT(bits2[15] == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testCopyConstructor()
{
    try
    {
        KBitArray bits(16, true);
        TEST_ASSERT(bits.size() == 16)
        TEST_ASSERT(bits[0]  == true)
        TEST_ASSERT(bits[1]  == true)
        TEST_ASSERT(bits[2]  == true)
        TEST_ASSERT(bits[3]  == true)
        TEST_ASSERT(bits[4]  == true)
        TEST_ASSERT(bits[5]  == true)
        TEST_ASSERT(bits[6]  == true)
        TEST_ASSERT(bits[7]  == true)
        TEST_ASSERT(bits[8]  == true)
        TEST_ASSERT(bits[9]  == true)
        TEST_ASSERT(bits[10] == true)
        TEST_ASSERT(bits[11] == true)
        TEST_ASSERT(bits[12] == true)
        TEST_ASSERT(bits[13] == true)
        TEST_ASSERT(bits[14] == true)
        TEST_ASSERT(bits[15] == true)

        KBitArray bits2(bits);
        TEST_ASSERT(bits2.size() == 16)
        TEST_ASSERT(bits2[0]  == true)
        TEST_ASSERT(bits2[1]  == true)
        TEST_ASSERT(bits2[2]  == true)
        TEST_ASSERT(bits2[3]  == true)
        TEST_ASSERT(bits2[4]  == true)
        TEST_ASSERT(bits2[5]  == true)
        TEST_ASSERT(bits2[6]  == true)
        TEST_ASSERT(bits2[7]  == true)
        TEST_ASSERT(bits2[8]  == true)
        TEST_ASSERT(bits2[9]  == true)
        TEST_ASSERT(bits2[10] == true)
        TEST_ASSERT(bits2[11] == true)
        TEST_ASSERT(bits2[12] == true)
        TEST_ASSERT(bits2[13] == true)
        TEST_ASSERT(bits2[14] == true)
        TEST_ASSERT(bits2[15] == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testAffectationOperator()
{
    try
    {
        KBitArray bits(16, true);
        TEST_ASSERT(bits.size() == 16)
        TEST_ASSERT(bits[0]  == true)
        TEST_ASSERT(bits[1]  == true)
        TEST_ASSERT(bits[2]  == true)
        TEST_ASSERT(bits[3]  == true)
        TEST_ASSERT(bits[4]  == true)
        TEST_ASSERT(bits[5]  == true)
        TEST_ASSERT(bits[6]  == true)
        TEST_ASSERT(bits[7]  == true)
        TEST_ASSERT(bits[8]  == true)
        TEST_ASSERT(bits[9]  == true)
        TEST_ASSERT(bits[10] == true)
        TEST_ASSERT(bits[11] == true)
        TEST_ASSERT(bits[12] == true)
        TEST_ASSERT(bits[13] == true)
        TEST_ASSERT(bits[14] == true)
        TEST_ASSERT(bits[15] == true)

        KBitArray bits2;
        bits2 = bits;
        TEST_ASSERT(bits2.size() == 16)
        TEST_ASSERT(bits2[0]  == true)
        TEST_ASSERT(bits2[1]  == true)
        TEST_ASSERT(bits2[2]  == true)
        TEST_ASSERT(bits2[3]  == true)
        TEST_ASSERT(bits2[4]  == true)
        TEST_ASSERT(bits2[5]  == true)
        TEST_ASSERT(bits2[6]  == true)
        TEST_ASSERT(bits2[7]  == true)
        TEST_ASSERT(bits2[8]  == true)
        TEST_ASSERT(bits2[9]  == true)
        TEST_ASSERT(bits2[10] == true)
        TEST_ASSERT(bits2[11] == true)
        TEST_ASSERT(bits2[12] == true)
        TEST_ASSERT(bits2[13] == true)
        TEST_ASSERT(bits2[14] == true)
        TEST_ASSERT(bits2[15] == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testBracketOperator()
{
    try
    {
        KBitArray bits(16);
        for(klab::UInt32 i=0; i<16; ++i)
            bits.setBit(i, (i%2)==0);

        TEST_ASSERT(bits.size() == 16)
        TEST_ASSERT(bits[0]  == true)
        TEST_ASSERT(bits[1]  == false)
        TEST_ASSERT(bits[2]  == true)
        TEST_ASSERT(bits[3]  == false)
        TEST_ASSERT(bits[4]  == true)
        TEST_ASSERT(bits[5]  == false)
        TEST_ASSERT(bits[6]  == true)
        TEST_ASSERT(bits[7]  == false)
        TEST_ASSERT(bits[8]  == true)
        TEST_ASSERT(bits[9]  == false)
        TEST_ASSERT(bits[10] == true)
        TEST_ASSERT(bits[11] == false)
        TEST_ASSERT(bits[12] == true)
        TEST_ASSERT(bits[13] == false)
        TEST_ASSERT(bits[14] == true)
        TEST_ASSERT(bits[15] == false)

        TEST_ASSERT(bits[16] == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testEqualOperator()
{
    try
    {
        KBitArray bits(16);
        KBitArray bits2(16);
        KBitArray bits3;
        KBitArray bits4;

        for(klab::UInt32 i=0; i<16; ++i)
        {
            bits.setBit(i, (i%2)==0);
            bits2.setBit(i, (i%2)==0);
        }

        bits3 = bits;
        bits4 = bits;
        bits4.set(5);


        TEST_ASSERT(bits==bits2 && bits2==bits)
        TEST_ASSERT(bits==bits3 && bits3==bits)
        TEST_ASSERT(bits2==bits3 && bits3==bits2)
        TEST_ASSERT((bits==bits4)==false && (bits4==bits)==false)
        TEST_ASSERT((bits2==bits4)==false && (bits4==bits2)==false)
        TEST_ASSERT((bits3==bits4)==false && (bits4==bits3)==false)
        TEST_ASSERT(bits==bits && bits2==bits2 && bits3==bits3 && bits4==bits4)


        // Limit cases.
        KBitArray empty;
        KBitArray empty2(16, false);
        TEST_ASSERT(empty==KBitArray() && KBitArray()==empty)
        TEST_ASSERT(empty2==KBitArray() && KBitArray()==empty2)
        TEST_ASSERT(empty2==empty && empty==empty2)
        TEST_ASSERT((bits==KBitArray())==false && (KBitArray()==bits)==false)
        TEST_ASSERT((bits==empty)==false && (empty==bits)==false)
        TEST_ASSERT((bits==empty2)==false && (empty2==bits)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testNotEqualOperator()
{
    try
    {
        KBitArray bits(16);
        KBitArray bits2(16);
        KBitArray bits3;
        KBitArray bits4;

        for(klab::UInt32 i=0; i<16; ++i)
        {
            bits.setBit(i, (i%2)==0);
            bits2.setBit(i, (i%2)==0);
        }

        bits3 = bits;
        bits4 = bits;
        bits4.set(5);


        TEST_ASSERT((bits!=bits2)==false && (bits2!=bits)==false)
        TEST_ASSERT((bits!=bits3)==false && (bits3!=bits)==false)
        TEST_ASSERT((bits2!=bits3)==false && (bits3!=bits2)==false)
        TEST_ASSERT(bits!=bits4 && bits4!=bits)
        TEST_ASSERT(bits2!=bits4 && bits4!=bits2)
        TEST_ASSERT(bits3!=bits4 && bits4!=bits3)
        TEST_ASSERT((bits!=bits)==false && (bits2!=bits2)==false && (bits3!=bits3)==false && (bits4!=bits4)==false)


        // Limit cases.
        KBitArray empty;
        KBitArray empty2(16, false);
        TEST_ASSERT((empty!=KBitArray())==false && (KBitArray()!=empty)==false)
        TEST_ASSERT((empty2!=KBitArray())==false && (KBitArray()!=empty2)==false)
        TEST_ASSERT((empty2!=empty)==false && (empty!=empty2)==false)
        TEST_ASSERT(bits!=KBitArray() && KBitArray()!=bits)
        TEST_ASSERT(bits!=empty && empty!=bits)
        TEST_ASSERT(bits!=empty2 && empty2!=bits)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testLowerOperator()
{
    try
    {
        KBitArray bits(4);
        bits.setBit(0, true);
        bits.setBit(1, false);
        bits.setBit(2, true);
        bits.setBit(3, false);

        KBitArray bits2(4);
        bits2.setBit(0, true);
        bits2.setBit(1, false);
        bits2.setBit(2, true);
        bits2.setBit(3, true);

        KBitArray bits3(3);
        bits3.setBit(0, false);
        bits3.setBit(1, true);
        bits3.setBit(2, false);

        KBitArray bits4(bits);


        TEST_ASSERT(bits<bits2 && (bits2<bits)==false)
        TEST_ASSERT((bits<bits3)==false && bits3<bits)
        TEST_ASSERT((bits<bits4)==false && (bits4<bits)==false)
        TEST_ASSERT((bits2<bits3)==false && bits3<bits2)
        TEST_ASSERT((bits2<bits4)==false && bits4<bits2)
        TEST_ASSERT(bits3<bits4 && (bits4<bits3)==false)
        TEST_ASSERT((bits<bits)==false && (bits2<bits2)==false && (bits3<bits3)==false && (bits4<bits4)==false)


        // Limit cases.
        KBitArray empty;
        KBitArray empty2(16, false);
        TEST_ASSERT((empty<KBitArray())==false && (KBitArray()<empty)==false)
        TEST_ASSERT((empty2<KBitArray())==false && (KBitArray()<empty2)==false)
        TEST_ASSERT((empty2<empty)==false && (empty<empty2)==false)
        TEST_ASSERT((bits<KBitArray())==false && KBitArray()<bits)
        TEST_ASSERT((bits<empty)==false && empty<bits)
        TEST_ASSERT((bits<empty2)==false && empty2<bits)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testLowerOrEqualOperator()
{
    try
    {
        KBitArray bits(4);
        bits.setBit(0, true);
        bits.setBit(1, false);
        bits.setBit(2, true);
        bits.setBit(3, false);

        KBitArray bits2(4);
        bits2.setBit(0, true);
        bits2.setBit(1, false);
        bits2.setBit(2, true);
        bits2.setBit(3, true);

        KBitArray bits3(3);
        bits3.setBit(0, false);
        bits3.setBit(1, true);
        bits3.setBit(2, false);

        KBitArray bits4(bits);


        TEST_ASSERT(bits<=bits2 && (bits2<=bits)==false)
        TEST_ASSERT((bits<=bits3)==false && bits3<=bits)
        TEST_ASSERT(bits<=bits4 && bits4<=bits)
        TEST_ASSERT((bits2<=bits3)==false && bits3<=bits2)
        TEST_ASSERT((bits2<=bits4)==false && bits4<=bits2)
        TEST_ASSERT(bits3<=bits4 && (bits4<=bits3)==false)
        TEST_ASSERT(bits<=bits && bits2<=bits2 && bits3<=bits3 && bits4<=bits4)


        // Limit cases.
        KBitArray empty;
        KBitArray empty2(16, false);
        TEST_ASSERT(empty<=KBitArray() && KBitArray()<=empty)
        TEST_ASSERT(empty2<=KBitArray() && KBitArray()<=empty2)
        TEST_ASSERT(empty2<=empty && empty<=empty2)
        TEST_ASSERT((bits<=KBitArray())==false && KBitArray()<=bits)
        TEST_ASSERT((bits<=empty)==false && empty<=bits)
        TEST_ASSERT((bits<=empty2)==false && empty2<=bits)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testGreaterOrEqualOperator()
{
    try
    {
        KBitArray bits(4);
        bits.setBit(0, true);
        bits.setBit(1, false);
        bits.setBit(2, true);
        bits.setBit(3, false);

        KBitArray bits2(4);
        bits2.setBit(0, true);
        bits2.setBit(1, false);
        bits2.setBit(2, true);
        bits2.setBit(3, true);

        KBitArray bits3(3);
        bits3.setBit(0, false);
        bits3.setBit(1, true);
        bits3.setBit(2, false);

        KBitArray bits4(bits);


        TEST_ASSERT((bits>=bits2)==false && bits2>=bits)
        TEST_ASSERT(bits>=bits3 && (bits3>=bits)==false)
        TEST_ASSERT(bits>=bits4 && bits4>=bits)
        TEST_ASSERT(bits2>=bits3 && (bits3>=bits2)==false)
        TEST_ASSERT(bits2>=bits4 && (bits4>=bits2)==false)
        TEST_ASSERT((bits3>=bits4)==false && bits4>=bits3)
        TEST_ASSERT(bits>=bits && bits2>=bits2 && bits3>=bits3 && bits4>=bits4)


        // Limit cases.
        KBitArray empty;
        KBitArray empty2(16, false);
        TEST_ASSERT(empty>=KBitArray() && KBitArray()>=empty)
        TEST_ASSERT(empty2>=KBitArray() && KBitArray()>=empty2)
        TEST_ASSERT(empty2>=empty && empty>=empty2)
        TEST_ASSERT(bits>=KBitArray() && (KBitArray()>=bits)==false)
        TEST_ASSERT(bits>=empty && (empty>=bits)==false)
        TEST_ASSERT(bits>=empty2 && (empty2>=bits)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testGreaterOperator()
{
    try
    {
        KBitArray bits(4);
        bits.setBit(0, true);
        bits.setBit(1, false);
        bits.setBit(2, true);
        bits.setBit(3, false);

        KBitArray bits2(4);
        bits2.setBit(0, true);
        bits2.setBit(1, false);
        bits2.setBit(2, true);
        bits2.setBit(3, true);

        KBitArray bits3(3);
        bits3.setBit(0, false);
        bits3.setBit(1, true);
        bits3.setBit(2, false);

        KBitArray bits4(bits);


        TEST_ASSERT((bits>bits2)==false && bits2>bits)
        TEST_ASSERT(bits>bits3 && (bits3>bits)==false)
        TEST_ASSERT((bits>bits4)==false && (bits4>bits)==false)
        TEST_ASSERT(bits2>bits3 && (bits3>bits2)==false)
        TEST_ASSERT(bits2>bits4 && (bits4>bits2)==false)
        TEST_ASSERT((bits3>bits4)==false && bits4>bits3)
        TEST_ASSERT((bits>bits)==false && (bits2>bits2)==false && (bits3>bits3)==false && (bits4>bits4)==false)


        // Limit cases.
        KBitArray empty;
        KBitArray empty2(16, false);
        TEST_ASSERT((empty>KBitArray())==false && (KBitArray()>empty)==false)
        TEST_ASSERT((empty2>KBitArray())==false && (KBitArray()>empty2)==false)
        TEST_ASSERT((empty2>empty)==false && (empty>empty2)==false)
        TEST_ASSERT(bits>KBitArray() && (KBitArray()>bits)==false)
        TEST_ASSERT(bits>empty && (empty>bits)==false)
        TEST_ASSERT(bits>empty2 && (empty2>bits)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testResize()
{
    try
    {
        KBitArray bits;
        TEST_ASSERT(bits.size() == 0)

        bits.resize(8);
        TEST_ASSERT(bits.size() == 8)

        bits.set(0);
        bits.reset(1);
        bits.set(2);
        bits.reset(3);
        bits.set(4);
        bits.reset(5);
        bits.set(6);
        bits.reset(7);
        TEST_ASSERT(bits[0]  == true)
        TEST_ASSERT(bits[1]  == false)
        TEST_ASSERT(bits[2]  == true)
        TEST_ASSERT(bits[3]  == false)
        TEST_ASSERT(bits[4]  == true)
        TEST_ASSERT(bits[5]  == false)
        TEST_ASSERT(bits[6]  == true)
        TEST_ASSERT(bits[7]  == false)

        bits.resize(4);
        TEST_ASSERT(bits.size() == 4)
        TEST_ASSERT(bits[0]  == true)
        TEST_ASSERT(bits[1]  == false)
        TEST_ASSERT(bits[2]  == true)
        TEST_ASSERT(bits[3]  == false)
        TEST_ASSERT(bits[4]  == false)
        TEST_ASSERT(bits[5]  == false)
        TEST_ASSERT(bits[6]  == false)
        TEST_ASSERT(bits[7]  == false)

        bits.resize(0);
        TEST_ASSERT(bits.size() == 0)
        TEST_ASSERT(bits[0]  == false)
        TEST_ASSERT(bits[1]  == false)
        TEST_ASSERT(bits[2]  == false)
        TEST_ASSERT(bits[3]  == false)
        TEST_ASSERT(bits[4]  == false)
        TEST_ASSERT(bits[5]  == false)
        TEST_ASSERT(bits[6]  == false)
        TEST_ASSERT(bits[7]  == false)


        KBitArray bits2(16);
        TEST_ASSERT(bits2.size() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testFill()
{
    try
    {
        KBitArray bits(8);
        TEST_ASSERT(bits.size() == 8)

        bits.fill(true);
        TEST_ASSERT(bits[0]  == true)
        TEST_ASSERT(bits[1]  == true)
        TEST_ASSERT(bits[2]  == true)
        TEST_ASSERT(bits[3]  == true)
        TEST_ASSERT(bits[4]  == true)
        TEST_ASSERT(bits[5]  == true)
        TEST_ASSERT(bits[6]  == true)
        TEST_ASSERT(bits[7]  == true)

        bits.fill(false);
        TEST_ASSERT(bits[0]  == false)
        TEST_ASSERT(bits[1]  == false)
        TEST_ASSERT(bits[2]  == false)
        TEST_ASSERT(bits[3]  == false)
        TEST_ASSERT(bits[4]  == false)
        TEST_ASSERT(bits[5]  == false)
        TEST_ASSERT(bits[6]  == false)
        TEST_ASSERT(bits[7]  == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testClear()
{
    try
    {
        KBitArray bits(8);
        TEST_ASSERT(bits.size() == 8)

        bits.fill(true);
        TEST_ASSERT(bits[0]  == true)
        TEST_ASSERT(bits[1]  == true)
        TEST_ASSERT(bits[2]  == true)
        TEST_ASSERT(bits[3]  == true)
        TEST_ASSERT(bits[4]  == true)
        TEST_ASSERT(bits[5]  == true)
        TEST_ASSERT(bits[6]  == true)
        TEST_ASSERT(bits[7]  == true)

        bits.clear();
        TEST_ASSERT(bits.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testSize()
{
    try
    {
        KBitArray bits;
        TEST_ASSERT(bits.size() == 0)

        bits.resize(8);
        TEST_ASSERT(bits.size() == 8)

        bits.resize(4);
        TEST_ASSERT(bits.size() == 4)

        bits.resize(0);
        TEST_ASSERT(bits.size() == 0)

        KBitArray bits2(16);
        TEST_ASSERT(bits2.size() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testPush()
{
    try
    {
        KBitArray bits;
        TEST_ASSERT(bits.size() == 0)

        bits.push(true);
        TEST_ASSERT(bits.size() == 1)
        TEST_ASSERT(bits[0] == true)

        bits.push(false);
        TEST_ASSERT(bits.size() == 2)
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)

        bits.push(true);
        TEST_ASSERT(bits.size() == 3)
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testPop()
{
    try
    {
        KBitArray bits;
        TEST_ASSERT(bits.size() == 0)

        bits.push(true);
        TEST_ASSERT(bits.size() == 1)
        TEST_ASSERT(bits[0] == true)

        bits.push(false);
        TEST_ASSERT(bits.size() == 2)
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)

        TEST_ASSERT(bits.pop() == false)
        TEST_ASSERT(bits.size() == 1)
        TEST_ASSERT(bits[0] == true)

        bits.push(false);
        TEST_ASSERT(bits.size() == 2)
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)

        bits.push(true);
        TEST_ASSERT(bits.size() == 3)
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true)

        TEST_ASSERT(bits.pop() == true)
        TEST_ASSERT(bits.size() == 2)
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)

        TEST_ASSERT(bits.pop() == false)
        TEST_ASSERT(bits.size() == 1)
        TEST_ASSERT(bits[0] == true)

        TEST_ASSERT(bits.pop() == true)
        TEST_ASSERT(bits.size() == 0)

        bits.pop();
        TEST_ASSERT(bits.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testSetBit()
{
    try
    {
        KBitArray bits(3);
        TEST_ASSERT(bits[0] == false)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false)

        bits.setBit(0, true);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false)

        bits.setBit(1, false);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false)

        bits.setBit(2, true);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true)

        bits.setBit(3, true);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true)     
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testSet()
{
    try
    {
        KBitArray bits(3);
        TEST_ASSERT(bits[0] == false)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false)

        bits.set(0);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false)

        bits.reset(1);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false)

        bits.set(2);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true)

        bits.set(3);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true) 

        bits.reset(3);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true) 

        bits.reset();
        TEST_ASSERT(bits[0] == false)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false) 

        bits.set();
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == true)
        TEST_ASSERT(bits[2] == true) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testReset()
{
    try
    {
        KBitArray bits(3);
        TEST_ASSERT(bits[0] == false)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false)

        bits.set(0);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false)

        bits.reset(1);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false)

        bits.set(2);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true)

        bits.set(3);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true) 

        bits.reset(3);
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == true)

        bits.reset();
        TEST_ASSERT(bits[0] == false)
        TEST_ASSERT(bits[1] == false)
        TEST_ASSERT(bits[2] == false) 

        bits.set();
        TEST_ASSERT(bits[0] == true)
        TEST_ASSERT(bits[1] == true)
        TEST_ASSERT(bits[2] == true) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArrayUnitTest::testBit()
{
    try
    {
        KBitArray bits(3);
        TEST_ASSERT(bits.bit(0) == false)
        TEST_ASSERT(bits.bit(1) == false)
        TEST_ASSERT(bits.bit(2) == false)

        bits.set(0);
        TEST_ASSERT(bits.bit(0) == true)
        TEST_ASSERT(bits.bit(1) == false)
        TEST_ASSERT(bits.bit(2) == false)

        bits.reset(1);
        TEST_ASSERT(bits.bit(0) == true)
        TEST_ASSERT(bits.bit(1) == false)
        TEST_ASSERT(bits.bit(2) == false)

        bits.set(2);
        TEST_ASSERT(bits.bit(0) == true)
        TEST_ASSERT(bits.bit(1) == false)
        TEST_ASSERT(bits.bit(2) == true)

        bits.set(3);
        TEST_ASSERT(bits.bit(0) == true)
        TEST_ASSERT(bits.bit(1) == false)
        TEST_ASSERT(bits.bit(2) == true) 

        bits.reset(3);
        TEST_ASSERT(bits.bit(0) == true)
        TEST_ASSERT(bits.bit(1) == false)
        TEST_ASSERT(bits.bit(2) == true) 

        TEST_ASSERT(bits.bit(3) == false) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
