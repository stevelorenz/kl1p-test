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

#include "RandomUnitTest.h"
#include "../include/Random.h"
#include "../include/FuncUtil.h"
#include <map>

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KRandomUnitTest::KRandomUnitTest() : Test::Suite()
{
    TEST_ADD(KRandomUnitTest::testDefaultConstructor)
    TEST_ADD(KRandomUnitTest::testSeedConstructor)
    TEST_ADD(KRandomUnitTest::testCopyConstructor)
    TEST_ADD(KRandomUnitTest::testAffectationOperator)

    TEST_ADD(KRandomUnitTest::testSetSeed)
    TEST_ADD(KRandomUnitTest::testResetSeed)
    TEST_ADD(KRandomUnitTest::testSeed)
    TEST_ADD(KRandomUnitTest::testGenerateBool)
    TEST_ADD(KRandomUnitTest::testGenerateUInt8)
    TEST_ADD(KRandomUnitTest::testGenerateInt8)
    TEST_ADD(KRandomUnitTest::testGenerateUInt16)
    TEST_ADD(KRandomUnitTest::testGenerateInt16)
    TEST_ADD(KRandomUnitTest::testGenerateUInt32)
    TEST_ADD(KRandomUnitTest::testGenerateInt32)
    TEST_ADD(KRandomUnitTest::testGenerateUInt64)
    TEST_ADD(KRandomUnitTest::testGenerateInt64)
    TEST_ADD(KRandomUnitTest::testGenerateReal)
    TEST_ADD(KRandomUnitTest::testGenerateDoubleReal)
    TEST_ADD(KRandomUnitTest::testGenerate)
    TEST_ADD(KRandomUnitTest::testGenerateBitArray)

    TEST_ADD(KRandomUnitTest::testInstance)
}

// ---------------------------------------------------------------------------------------------------- //

KRandomUnitTest::~KRandomUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testDefaultConstructor()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)


        klab::UInt32 x1 = random.generateUInt32(1, 1000000000);
        klab::UInt32 x2 = random.generateUInt32(1, 1000000000);

        TEST_ASSERT(x1 != x2)       // Probability for the test to failed = 1/1000000000 (1e-9)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testSeedConstructor()
{
    try
    {
        KRandom random1(123456);
        TEST_ASSERT(random1.seed() == 123456)

        KRandom random2(123456);
        TEST_ASSERT(random2.seed() == 123456)

        KRandom random3(654321);
        TEST_ASSERT(random3.seed() == 654321)

        KRandom random4;
        TEST_ASSERT(random4.seed() > 0)


        klab::UInt32 x1 = random1.generateUInt32(1, 1000000000);
        klab::UInt32 x2 = random2.generateUInt32(1, 1000000000);
        klab::UInt32 x3 = random3.generateUInt32(1, 1000000000);
        klab::UInt32 x4 = random4.generateUInt32(1, 1000000000);
        klab::UInt32 x5 = random1.generateUInt32(1, 1000000000);
        klab::UInt32 x6 = random2.generateUInt32(1, 1000000000);

        TEST_ASSERT(x1 == x2)
        TEST_ASSERT(x5 == x6)
        TEST_ASSERT(x1 != x3)       // Probability for the test to failed = 1/1000000000 (1e-9)
        TEST_ASSERT(x1 != x4)       // Probability for the test to failed = 1/1000000000 (1e-9)
        TEST_ASSERT(x3 != x4)       // Probability for the test to failed = 1/1000000000 (1e-9)
        
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testCopyConstructor()
{
    try
    {
        KRandom random1(123456);        
        TEST_ASSERT(random1.seed() == 123456)
        random1.generateUInt32(1, 1000000000);
        random1.generateUInt32(1, 1000000000);

        KRandom random2(random1);        
        TEST_ASSERT(random2.seed() == 123456)

        klab::UInt32 x1 = random1.generateUInt32(1, 1000000000);
        klab::UInt32 x2 = random1.generateUInt32(1, 1000000000);
        klab::UInt32 x3 = random2.generateUInt32(1, 1000000000);
        klab::UInt32 x4 = random2.generateUInt32(1, 1000000000);
        TEST_ASSERT(x1 == x3)
        TEST_ASSERT(x2 == x4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testAffectationOperator()
{
    try
    {
        KRandom random1(123456);        
        TEST_ASSERT(random1.seed() == 123456)
        random1.generateUInt32(1, 1000000000);
        random1.generateUInt32(1, 1000000000);

        KRandom random2;
        random2 = random1;
        TEST_ASSERT(random2.seed() == 123456)

        klab::UInt32 x1 = random1.generateUInt32(1, 1000000000);
        klab::UInt32 x2 = random1.generateUInt32(1, 1000000000);
        klab::UInt32 x3 = random2.generateUInt32(1, 1000000000);
        klab::UInt32 x4 = random2.generateUInt32(1, 1000000000);
        TEST_ASSERT(x1 == x3)
        TEST_ASSERT(x2 == x4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testSetSeed()
{
    try
    {
        KRandom random1(123456);
        klab::UInt32 x1 = random1.generateUInt32(1, 1000000000);
        klab::UInt32 x2 = random1.generateUInt32(1, 1000000000);
        TEST_ASSERT(random1.seed() == 123456)

        KRandom random2;
        klab::UInt32 x3 = random2.generateUInt32(1, 1000000000);
        klab::UInt32 x4 = random2.generateUInt32(1, 1000000000);
        TEST_ASSERT(random2.seed() > 0)
        
        TEST_ASSERT(x1 != x3)   // Probability for the test to failed = 1/1000000000 (1e-9)
        TEST_ASSERT(x2 != x4)   // Probability for the test to failed = 1/1000000000 (1e-9)


        random2.setSeed(123456);
        klab::UInt32 x5 = random2.generateUInt32(1, 1000000000);
        klab::UInt32 x6 = random2.generateUInt32(1, 1000000000);
        TEST_ASSERT(random2.seed() == 123456)

        TEST_ASSERT(x1 == x5)
        TEST_ASSERT(x2 == x6)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testResetSeed()
{
    try
    {
        KRandom random1(123456);
        klab::UInt32 x1 = random1.generateUInt32(1, 1000000000);
        klab::UInt32 x2 = random1.generateUInt32(1, 1000000000);
        TEST_ASSERT(random1.seed() == 123456)

        KRandom random2;
        klab::UInt32 x3 = random2.generateUInt32(1, 1000000000);
        klab::UInt32 x4 = random2.generateUInt32(1, 1000000000);
        TEST_ASSERT(random2.seed() > 0)
        
        TEST_ASSERT(x1 != x3)   // Probability for the test to failed = 1/1000000000 (1e-9)
        TEST_ASSERT(x2 != x4)   // Probability for the test to failed = 1/1000000000 (1e-9)


        random2.setSeed(123456);
        klab::UInt32 x5 = random2.generateUInt32(1, 1000000000);
        klab::UInt32 x6 = random2.generateUInt32(1, 1000000000);
        TEST_ASSERT(random2.seed() == 123456)

        TEST_ASSERT(x1 == x5)
        TEST_ASSERT(x2 == x6)


        random2.resetSeed();
        klab::UInt32 x7 = random2.generateUInt32(1, 1000000000);
        klab::UInt32 x8 = random2.generateUInt32(1, 1000000000);
        TEST_ASSERT(random2.seed() > 0)

        TEST_ASSERT(x1 != x7)   // Probability for the test to failed = 1/1000000000 (1e-9)
        TEST_ASSERT(x2 != x8)   // Probability for the test to failed = 1/1000000000 (1e-9)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testSeed()
{
    try
    {
        KRandom random1(123456);
        TEST_ASSERT(random1.seed() == 123456)

        KRandom random2;
        TEST_ASSERT(random2.seed() > 0)

        random2.setSeed(123456);
        TEST_ASSERT(random2.seed() == 123456)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateBool()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        std::map<bool, klab::UInt32> randMap;
        randMap[false]  = 0;
        randMap[true] = 0;


        for(klab::UInt32 i=0; i<100; ++i)
            randMap[random.generateBool()] += 1;

        TEST_ASSERT(randMap[false] > 0)     // Probability for the test to failed = 1/100
        TEST_ASSERT(randMap[true] > 0)      // Probability for the test to failed = 1/100

        klab::UInt32 sum = randMap[false] + randMap[true];
        TEST_ASSERT(sum == 100)
        

        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        TEST_ASSERT(random.generateBool() == true)
        TEST_ASSERT(random.generateBool() == false)
        TEST_ASSERT(random.generateBool() == true)
        TEST_ASSERT(random.generateBool() == false)
        TEST_ASSERT(random.generateBool() == true)
        TEST_ASSERT(random.generateBool() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateUInt8()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        std::map<klab::UInt8, klab::UInt32> randMap1;
        for(klab::UInt32 i=0; i<=255; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 100 * (256);
        for(klab::UInt32 i=0; i<count; ++i)
            randMap1[random.generateUInt8()] += 1;

        klab::UInt32 sum = 0;
        for(klab::UInt32 i=0; i<=static_cast<klab::UInt32>(klab::TTypeInfo<klab::Int8>::MAX); ++i)
        {
            sum += randMap1[i];
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/100         
        }
        TEST_ASSERT(sum == count)


        std::map<klab::UInt8, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt32 i=0; i<600; ++i)
            randMap2[random.generateUInt8(1, 6)] += 1;

        sum = 0;
        for(klab::UInt32 i=1; i<=6; ++i)
        {
            sum += randMap2[i];
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/100
        }
        TEST_ASSERT(sum == 600)


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::UInt8 x1 = random.generateUInt8(1, 6);
        klab::UInt8 x2 = random.generateUInt8(1, 6);
        klab::UInt8 x3 = random.generateUInt8(1, 6);
        klab::UInt8 x4 = random.generateUInt8(1, 6);
        klab::UInt8 x5 = random.generateUInt8(1, 6);
        klab::UInt8 x6 = random.generateUInt8(1, 6);
        klab::UInt8 x7 = random.generateUInt8(1, 6);
        klab::UInt8 x8 = random.generateUInt8(1, 6);
        klab::UInt8 x9 = random.generateUInt8(1, 6);

        TEST_ASSERT(x1 == 2)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateInt8()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        std::map<klab::Int8, klab::UInt32> randMap1;
        for(klab::Int32 i=-128; i<=127; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 100 * (256);
        for(klab::UInt32 i=0; i<count; ++i)
            randMap1[random.generateInt8()] += 1;

        klab::UInt32 sum = 0;
        for(klab::Int32 i=-128; i<=127; ++i)
        {
            sum += randMap1[i];
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/100         
        }
        TEST_ASSERT(sum == count)


        std::map<klab::Int8, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt32 i=0; i<600; ++i)
            randMap2[random.generateInt8(1, 6)] += 1;

        sum = 0;
        for(klab::UInt32 i=1; i<=6; ++i)
        {
            sum += randMap2[i];
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/100
        }
        TEST_ASSERT(sum == 600)


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::Int8 x1 = random.generateInt8(1, 6);
        klab::Int8 x2 = random.generateInt8(1, 6);
        klab::Int8 x3 = random.generateInt8(1, 6);
        klab::Int8 x4 = random.generateInt8(1, 6);
        klab::Int8 x5 = random.generateInt8(1, 6);
        klab::Int8 x6 = random.generateInt8(1, 6);
        klab::Int8 x7 = random.generateInt8(1, 6);
        klab::Int8 x8 = random.generateInt8(1, 6);
        klab::Int8 x9 = random.generateInt8(1, 6);

        TEST_ASSERT(x1 == 2)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateUInt16()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        std::map<klab::UInt16, klab::UInt32> randMap1;
        for(klab::UInt32 i=0; i<=255; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 100 * (256);
        for(klab::UInt32 i=0; i<count; ++i)
            randMap1[random.generateUInt16(0, 255)] += 1;

        klab::UInt32 sum = 0;
        for(klab::UInt32 i=0; i<=255; ++i)
        {
            sum += randMap1[i];
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/100         
        }
        TEST_ASSERT(sum == count)


        std::map<klab::UInt16, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt32 i=0; i<600; ++i)
            randMap2[random.generateUInt16(1, 6)] += 1;

        sum = 0;
        for(klab::UInt32 i=1; i<=6; ++i)
        {
            sum += randMap2[i];
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/100
        }
        TEST_ASSERT(sum == 600)


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::UInt16 x1 = random.generateUInt16(1, 6);
        klab::UInt16 x2 = random.generateUInt16(1, 6);
        klab::UInt16 x3 = random.generateUInt16(1, 6);
        klab::UInt16 x4 = random.generateUInt16(1, 6);
        klab::UInt16 x5 = random.generateUInt16(1, 6);
        klab::UInt16 x6 = random.generateUInt16(1, 6);
        klab::UInt16 x7 = random.generateUInt16(1, 6);
        klab::UInt16 x8 = random.generateUInt16(1, 6);
        klab::UInt16 x9 = random.generateUInt16(1, 6);

        TEST_ASSERT(x1 == 2)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateInt16()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        std::map<klab::Int16, klab::UInt32> randMap1;
        for(klab::Int32 i=-128; i<=127; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 100 * (256);
        for(klab::UInt32 i=0; i<count; ++i)
            randMap1[random.generateInt16(-128, 127)] += 1;

        klab::UInt32 sum = 0;
        for(klab::Int32 i=-128; i<=127; ++i)
        {
            sum += randMap1[i];
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/100         
        }
        TEST_ASSERT(sum == count)


        std::map<klab::Int16, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt32 i=0; i<600; ++i)
            randMap2[random.generateInt16(1, 6)] += 1;

        sum = 0;
        for(klab::UInt32 i=1; i<=6; ++i)
        {
            sum += randMap2[i];
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/100
        }
        TEST_ASSERT(sum == 600)


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::Int16 x1 = random.generateInt16(1, 6);
        klab::Int16 x2 = random.generateInt16(1, 6);
        klab::Int16 x3 = random.generateInt16(1, 6);
        klab::Int16 x4 = random.generateInt16(1, 6);
        klab::Int16 x5 = random.generateInt16(1, 6);
        klab::Int16 x6 = random.generateInt16(1, 6);
        klab::Int16 x7 = random.generateInt16(1, 6);
        klab::Int16 x8 = random.generateInt16(1, 6);
        klab::Int16 x9 = random.generateInt16(1, 6);

        TEST_ASSERT(x1 == 2)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateUInt32()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        std::map<klab::UInt32, klab::UInt32> randMap1;
        for(klab::UInt32 i=0; i<=255; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 100 * (256);
        for(klab::UInt32 i=0; i<count; ++i)
            randMap1[random.generateUInt32(0, 255)] += 1;

        klab::UInt32 sum = 0;
        for(klab::UInt32 i=0; i<=255; ++i)
        {
            sum += randMap1[i];
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/100         
        }
        TEST_ASSERT(sum == count)


        std::map<klab::UInt32, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt32 i=0; i<600; ++i)
            randMap2[random.generateUInt32(1, 6)] += 1;

        sum = 0;
        for(klab::UInt32 i=1; i<=6; ++i)
        {
            sum += randMap2[i];
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/100
        }
        TEST_ASSERT(sum == 600)


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::UInt32 x1 = random.generateUInt32(1, 6);
        klab::UInt32 x2 = random.generateUInt32(1, 6);
        klab::UInt32 x3 = random.generateUInt32(1, 6);
        klab::UInt32 x4 = random.generateUInt32(1, 6);
        klab::UInt32 x5 = random.generateUInt32(1, 6);
        klab::UInt32 x6 = random.generateUInt32(1, 6);
        klab::UInt32 x7 = random.generateUInt32(1, 6);
        klab::UInt32 x8 = random.generateUInt32(1, 6);
        klab::UInt32 x9 = random.generateUInt32(1, 6);

        TEST_ASSERT(x1 == 2)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateInt32()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        std::map<klab::Int32, klab::UInt32> randMap1;
        for(klab::Int32 i=-128; i<=127; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 100 * (256);
        for(klab::UInt32 i=0; i<count; ++i)
            randMap1[random.generateInt32(-128, 127)] += 1;

        klab::UInt32 sum = 0;
        for(klab::Int32 i=-128; i<=127; ++i)
        {
            sum += randMap1[i];
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/100         
        }
        TEST_ASSERT(sum == count)


        std::map<klab::Int32, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt32 i=0; i<600; ++i)
            randMap2[random.generateInt32(1, 6)] += 1;

        sum = 0;
        for(klab::UInt32 i=1; i<=6; ++i)
        {
            sum += randMap2[i];
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/100
        }
        TEST_ASSERT(sum == 600)


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::Int32 x1 = random.generateInt32(1, 6);
        klab::Int32 x2 = random.generateInt32(1, 6);
        klab::Int32 x3 = random.generateInt32(1, 6);
        klab::Int32 x4 = random.generateInt32(1, 6);
        klab::Int32 x5 = random.generateInt32(1, 6);
        klab::Int32 x6 = random.generateInt32(1, 6);
        klab::Int32 x7 = random.generateInt32(1, 6);
        klab::Int32 x8 = random.generateInt32(1, 6);
        klab::Int32 x9 = random.generateInt32(1, 6);

        TEST_ASSERT(x1 == 2)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateUInt64()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        std::map<klab::UInt64, klab::UInt32> randMap1;
        for(klab::UInt32 i=0; i<=255; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 100 * (256);
        for(klab::UInt32 i=0; i<count; ++i)
            randMap1[random.generateUInt64(0, 255)] += 1;

        klab::UInt32 sum = 0;
        for(klab::UInt64 i=0; i<=255; ++i)
        {
            sum += randMap1[i];
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/100         
        }
        TEST_ASSERT(sum == count)


        std::map<klab::UInt64, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt64 i=0; i<600; ++i)
            randMap2[random.generateUInt64(1, 6)] += 1;

        sum = 0;
        for(klab::UInt32 i=1; i<=6; ++i)
        {
            sum += randMap2[i];
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/100
        }
        TEST_ASSERT(sum == 600)


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::UInt64 x1 = random.generateUInt64(1, 6);
        klab::UInt64 x2 = random.generateUInt64(1, 6);
        klab::UInt64 x3 = random.generateUInt64(1, 6);
        klab::UInt64 x4 = random.generateUInt64(1, 6);
        klab::UInt64 x5 = random.generateUInt64(1, 6);
        klab::UInt64 x6 = random.generateUInt64(1, 6);
        klab::UInt64 x7 = random.generateUInt64(1, 6);
        klab::UInt64 x8 = random.generateUInt64(1, 6);
        klab::UInt64 x9 = random.generateUInt64(1, 6);

        TEST_ASSERT(x1 == 2)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateInt64()
{
    try
    {
        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        std::map<klab::Int64, klab::UInt32> randMap1;
        for(klab::Int32 i=-128; i<=127; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 100 * (256);
        for(klab::UInt32 i=0; i<count; ++i)
            randMap1[random.generateInt64(-128, 127)] += 1;

        klab::UInt32 sum = 0;
        for(klab::Int64 i=-128; i<=127; ++i)
        {
            sum += randMap1[i];
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/100         
        }
        TEST_ASSERT(sum == count)


        std::map<klab::Int64, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt64 i=0; i<600; ++i)
            randMap2[random.generateInt64(1, 6)] += 1;

        sum = 0;
        for(klab::UInt32 i=1; i<=6; ++i)
        {
            sum += randMap2[i];
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/100
        }
        TEST_ASSERT(sum == 600)


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::Int64 x1 = random.generateInt64(1, 6);
        klab::Int64 x2 = random.generateInt64(1, 6);
        klab::Int64 x3 = random.generateInt64(1, 6);
        klab::Int64 x4 = random.generateInt64(1, 6);
        klab::Int64 x5 = random.generateInt64(1, 6);
        klab::Int64 x6 = random.generateInt64(1, 6);
        klab::Int64 x7 = random.generateInt64(1, 6);
        klab::Int64 x8 = random.generateInt64(1, 6);
        klab::Int64 x9 = random.generateInt64(1, 6);

        TEST_ASSERT(x1 == 2)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateReal()
{
    try
    {
        klab::DoubleReal precision = 1e-6;

        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        
        std::map<klab::UInt8, klab::UInt32> randMap1;
        for(klab::UInt8 i=0; i<=10; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 10000;
        for(klab::UInt32 i=0; i<count; ++i)
        {
            klab::Real x = random.generateReal();
            randMap1[static_cast<UInt8>(x*10)] += 1;

            TEST_ASSERT(x>=0.0f && x<=1.0f) 
        }

        for(klab::UInt8 i=0; i<10; ++i)
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/1000 


        std::map<klab::UInt8, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt32 i=0; i<6000; ++i)
        {
            klab::Real x = random.generateReal(1.0f, 6.0f);
            randMap2[static_cast<UInt8>(x)] += 1;

            TEST_ASSERT(x>=1.0f && x<=6.0f) 
        }

        for(klab::UInt32 i=1; i<6; ++i)
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/1000


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::Real x1 = random.generateReal(1.0f, 6.0f);
        klab::Real x2 = random.generateReal(1.0f, 6.0f);
        klab::Real x3 = random.generateReal(1.0f, 6.0f);
        klab::Real x4 = random.generateReal(1.0f, 6.0f);
        klab::Real x5 = random.generateReal(1.0f, 6.0f);
        klab::Real x6 = random.generateReal(1.0f, 6.0f);
        klab::Real x7 = random.generateReal(1.0f, 6.0f);
        klab::Real x8 = random.generateReal(1.0f, 6.0f);
        klab::Real x9 = random.generateReal(1.0f, 6.0f);

        TEST_ASSERT(klab::Equals(x1, 1.1505429f, precision))
        TEST_ASSERT(klab::Equals(x2, 1.6501818f, precision))
        TEST_ASSERT(klab::Equals(x3, 5.7077127f, precision))
        TEST_ASSERT(klab::Equals(x4, 1.7601167f, precision))
        TEST_ASSERT(klab::Equals(x5, 5.8134179f, precision))
        TEST_ASSERT(klab::Equals(x6, 4.6400003f, precision))
        TEST_ASSERT(klab::Equals(x7, 1.1347063f, precision))
        TEST_ASSERT(klab::Equals(x8, 3.3189843f, precision))
        TEST_ASSERT(klab::Equals(x9, 5.6627960f, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateDoubleReal()
{
    try
    {
        klab::DoubleReal precision = 1e-15;

        KRandom random;
        TEST_ASSERT(random.seed() > 0)

        
        std::map<klab::UInt8, klab::UInt32> randMap1;
        for(klab::UInt8 i=0; i<=10; ++i)
            randMap1[i] = 0;

        klab::UInt32 count = 10000;
        for(klab::UInt32 i=0; i<count; ++i)
        {
            klab::DoubleReal x = random.generateDoubleReal();
            randMap1[static_cast<UInt8>(x*10)] += 1;

            TEST_ASSERT(x>=0.0 && x<=1.0) 
        }

        for(klab::UInt8 i=0; i<10; ++i)
            TEST_ASSERT(randMap1[i] > 0)    // Probability for the test to failed = 1/1000 


        std::map<klab::UInt8, klab::UInt32> randMap2;
        for(klab::UInt32 i=1; i<=6; ++i)
            randMap2[i] = 0;

        for(klab::UInt32 i=0; i<6000; ++i)
        {
            klab::DoubleReal x = random.generateDoubleReal(1.0, 6.0);
            randMap2[static_cast<UInt8>(x)] += 1;

            TEST_ASSERT(x>=1.0 && x<=6.0) 
        }

        for(klab::UInt32 i=1; i<6; ++i)
            TEST_ASSERT(randMap2[i] > 0)    // Probability for the test to failed = 1/1000


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        klab::DoubleReal x1 = random.generateDoubleReal(1.0, 6.0);
        klab::DoubleReal x2 = random.generateDoubleReal(1.0, 6.0);
        klab::DoubleReal x3 = random.generateDoubleReal(1.0, 6.0);
        klab::DoubleReal x4 = random.generateDoubleReal(1.0, 6.0);
        klab::DoubleReal x5 = random.generateDoubleReal(1.0, 6.0);
        klab::DoubleReal x6 = random.generateDoubleReal(1.0, 6.0);
        klab::DoubleReal x7 = random.generateDoubleReal(1.0, 6.0);
        klab::DoubleReal x8 = random.generateDoubleReal(1.0, 6.0);
        klab::DoubleReal x9 = random.generateDoubleReal(1.0, 6.0);

        TEST_ASSERT(klab::Equals(x1, 1.0346391043044960, precision))
        TEST_ASSERT(klab::Equals(x2, 1.0002706506406380, precision))
        TEST_ASSERT(klab::Equals(x3, 1.6149117845827043, precision))
        TEST_ASSERT(klab::Equals(x4, 1.2711688228324327, precision))
        TEST_ASSERT(klab::Equals(x5, 4.6825219681052070, precision))
        TEST_ASSERT(klab::Equals(x6, 2.2500192629266529, precision))
        TEST_ASSERT(klab::Equals(x7, 5.8362568766192311, precision))
        TEST_ASSERT(klab::Equals(x8, 4.3991663349603733, precision))
        TEST_ASSERT(klab::Equals(x9, 5.6945531944890497, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerate()
{
    try
    {
        KRandom random(123456);
        TEST_ASSERT(random.seed() == 123456)

        bool x1              = random.generate<bool>(false, true);
        klab::UInt8 x2       = random.generate<klab::UInt8>(1, 6);
        klab::Int8 x3        = random.generate<klab::Int8>(1, 6);
        klab::UInt16 x4      = random.generate<klab::UInt16>(1, 6);
        klab::Int16 x5       = random.generate<klab::Int16>(1, 6);
        klab::UInt32 x6      = random.generate<klab::UInt32>(1, 6);
        klab::Int32 x7       = random.generate<klab::Int32>(1, 6);
        klab::UInt64 x8      = random.generate<klab::UInt64>(1, 6);
        klab::Int64 x9       = random.generate<klab::Int64>(1, 6);
        klab::Real x10       = random.generate<klab::Real>(1.0f, 6.0f);
        klab::DoubleReal x11 = random.generate<klab::DoubleReal>(1.0, 6.0);

        TEST_ASSERT(x1 == true)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
        TEST_ASSERT(klab::Equals(x10, 4.1854053f, 1e-6))
        TEST_ASSERT(klab::Equals(x11, 4.4308009887439477, 1e-15))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testGenerateBitArray()
{
    try
    {
        klab::UInt32         n  = 100;
        klab::UInt32 countTrues = 48;

        KRandom random;
        TEST_ASSERT(random.seed() > 0)


        KBitArray bits1;
        random.generateBitArray(n, bits1);
        TEST_ASSERT(bits1.size() == n)

        std::map<bool, klab::UInt32> randMap;
        randMap[false] = 0;
        randMap[true]  = 0;

        for(klab::UInt32 i=0; i<100; ++i)
            randMap[bits1[i]] += 1;

        TEST_ASSERT(randMap[false] > 0)     // Probability for the test to failed = 1/100
        TEST_ASSERT(randMap[true] > 0)      // Probability for the test to failed = 1/100


        KBitArray bits2;
        random.generateBitArray(n, countTrues, bits2);
        TEST_ASSERT(bits2.size() == n)

        klab::UInt32 count = 0;
        for(klab::UInt32 i=0; i<n; ++i)
            count += (bits2[i]==1 ? 1 : 0);
        TEST_ASSERT(count == countTrues)


        random.setSeed(123456);
        TEST_ASSERT(random.seed() == 123456)

        KBitArray bits3;
        random.generateBitArray(10, bits3);
        TEST_ASSERT(bits3.size() == 10)
        TEST_ASSERT(bits3[0] == true)
        TEST_ASSERT(bits3[1] == false)
        TEST_ASSERT(bits3[2] == true)
        TEST_ASSERT(bits3[3] == false)
        TEST_ASSERT(bits3[4] == true)
        TEST_ASSERT(bits3[5] == false)
        TEST_ASSERT(bits3[6] == false)
        TEST_ASSERT(bits3[7] == true)
        TEST_ASSERT(bits3[8] == false)
        TEST_ASSERT(bits3[9] == true)

        KBitArray bits4;
        random.generateBitArray(10, 4, bits4);
        TEST_ASSERT(bits4.size() == 10)
        TEST_ASSERT(bits4[0] == true)
        TEST_ASSERT(bits4[1] == false)
        TEST_ASSERT(bits4[2] == false)
        TEST_ASSERT(bits4[3] == false)
        TEST_ASSERT(bits4[4] == true)
        TEST_ASSERT(bits4[5] == true)
        TEST_ASSERT(bits4[6] == false)
        TEST_ASSERT(bits4[7] == true)
        TEST_ASSERT(bits4[8] == false)
        TEST_ASSERT(bits4[9] == false)


        // Limit cases.
        KRandom random0;
        KBitArray bits0_1;

        random0.generateBitArray(0, 10, bits0_1);
        TEST_ASSERT(bits0_1.size() == 0)

        random0.generateBitArray(10, 0, bits0_1);
        TEST_ASSERT(bits0_1.size() == 10)
        TEST_ASSERT(bits0_1[0] == false)
        TEST_ASSERT(bits0_1[1] == false)
        TEST_ASSERT(bits0_1[2] == false)
        TEST_ASSERT(bits0_1[3] == false)
        TEST_ASSERT(bits0_1[4] == false)
        TEST_ASSERT(bits0_1[5] == false)
        TEST_ASSERT(bits0_1[6] == false)
        TEST_ASSERT(bits0_1[7] == false)
        TEST_ASSERT(bits0_1[8] == false)
        TEST_ASSERT(bits0_1[9] == false)

        bits0_1.clear();
        random0.generateBitArray(10, 10, bits0_1);
        TEST_ASSERT(bits0_1.size() == 10)
        TEST_ASSERT(bits0_1[0] == true)
        TEST_ASSERT(bits0_1[1] == true)
        TEST_ASSERT(bits0_1[2] == true)
        TEST_ASSERT(bits0_1[3] == true)
        TEST_ASSERT(bits0_1[4] == true)
        TEST_ASSERT(bits0_1[5] == true)
        TEST_ASSERT(bits0_1[6] == true)
        TEST_ASSERT(bits0_1[7] == true)
        TEST_ASSERT(bits0_1[8] == true)
        TEST_ASSERT(bits0_1[9] == true)

        bits0_1.clear();
        random0.generateBitArray(10, 20, bits0_1);
        TEST_ASSERT(bits0_1.size() == 10)
        TEST_ASSERT(bits0_1[0] == true)
        TEST_ASSERT(bits0_1[1] == true)
        TEST_ASSERT(bits0_1[2] == true)
        TEST_ASSERT(bits0_1[3] == true)
        TEST_ASSERT(bits0_1[4] == true)
        TEST_ASSERT(bits0_1[5] == true)
        TEST_ASSERT(bits0_1[6] == true)
        TEST_ASSERT(bits0_1[7] == true)
        TEST_ASSERT(bits0_1[8] == true)
        TEST_ASSERT(bits0_1[9] == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandomUnitTest::testInstance()
{
    try
    {
        KRandom::Instance().setSeed(123456);
        TEST_ASSERT(KRandom::Instance().seed() == 123456)

        bool x1             = KRandom::Instance().generate<bool>(false, true);
        klab::UInt8 x2      = KRandom::Instance().generate<klab::UInt8>(1, 6);
        klab::Int8 x3       = KRandom::Instance().generate<klab::Int8>(1, 6);
        klab::UInt16 x4     = KRandom::Instance().generate<klab::UInt16>(1, 6);
        klab::Int16 x5      = KRandom::Instance().generate<klab::Int16>(1, 6);
        klab::UInt32 x6     = KRandom::Instance().generate<klab::UInt32>(1, 6);
        klab::Int32 x7      = KRandom::Instance().generate<klab::Int32>(1, 6);
        klab::UInt64 x8     = KRandom::Instance().generate<klab::UInt64>(1, 6);
        klab::Int64 x9      = KRandom::Instance().generate<klab::Int64>(1, 6);
        klab::Real x10      = KRandom::Instance().generate<klab::Real>(1.0f, 6.0f);
        klab::DoubleReal x11= KRandom::Instance().generate<klab::DoubleReal>(1.0, 6.0);

        TEST_ASSERT(x1 == true)
        TEST_ASSERT(x2 == 5)
        TEST_ASSERT(x3 == 4)
        TEST_ASSERT(x4 == 3)
        TEST_ASSERT(x5 == 2)
        TEST_ASSERT(x6 == 1)
        TEST_ASSERT(x7 == 3)
        TEST_ASSERT(x8 == 2)
        TEST_ASSERT(x9 == 5)
        TEST_ASSERT(klab::Equals(x10, 4.1854053f, 1e-6))
        TEST_ASSERT(klab::Equals(x11, 4.4308009887439477, 1e-15))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
