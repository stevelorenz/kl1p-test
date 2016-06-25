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

#include "TemplateUtilUnitTest.h"
#include "../include/FuncUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

klab::Int32 KTemplateUtilUnitTest::TestValue = 0;

// ---------------------------------------------------------------------------------------------------- //

KTemplateUtilUnitTest::KTemplateUtilUnitTest() : Test::Suite()
{
    TEST_ADD(KTemplateUtilUnitTest::testNOP)
    TEST_ADD(KTemplateUtilUnitTest::testINC)
    TEST_ADD(KTemplateUtilUnitTest::testDEC)
    TEST_ADD(KTemplateUtilUnitTest::testTYPEIF)
    TEST_ADD(KTemplateUtilUnitTest::testVALUEIF)
    TEST_ADD(KTemplateUtilUnitTest::testIF)
    TEST_ADD(KTemplateUtilUnitTest::testLOOP)
    TEST_ADD(KTemplateUtilUnitTest::testFILLARRAY)
    TEST_ADD(KTemplateUtilUnitTest::testCOPYARRAY)
    TEST_ADD(KTemplateUtilUnitTest::testMIN)
    TEST_ADD(KTemplateUtilUnitTest::testMAX)
    TEST_ADD(KTemplateUtilUnitTest::testPOWER)
    TEST_ADD(KTemplateUtilUnitTest::testSTATIC_ASSERT)
}

// ---------------------------------------------------------------------------------------------------- //

KTemplateUtilUnitTest::~KTemplateUtilUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testNOP()
{
    try
    {
        klab::NOP::Do();
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testVALUE()
{
    try
    {
        TEST_ASSERT(klab::VALUE<-1>::RESULT == -1)
        TEST_ASSERT(klab::VALUE<0>::RESULT  == 0)
        TEST_ASSERT(klab::VALUE<1>::RESULT  == 1)
        TEST_ASSERT(klab::VALUE<2>::RESULT  == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testINC()
{
    try
    {
        TEST_ASSERT(klab::INC<-1>::RESULT == 0)
        TEST_ASSERT(klab::INC<0>::RESULT  == 1)
        TEST_ASSERT(klab::INC<1>::RESULT  == 2)
        TEST_ASSERT(klab::INC<2>::RESULT  == 3)

        TEST_ASSERT(klab::INC<klab::INC<10>::RESULT>::RESULT == 12)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testDEC()
{
    try
    {
        TEST_ASSERT(klab::DEC<-1>::RESULT == -2)
        TEST_ASSERT(klab::DEC<0>::RESULT  == -1)
        TEST_ASSERT(klab::DEC<1>::RESULT  == 0)
        TEST_ASSERT(klab::DEC<2>::RESULT  == 1)
        TEST_ASSERT(klab::DEC<klab::DEC<10>::RESULT>::RESULT == 8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testTYPEIF()
{
    try
    {
        klab::TYPEIF<1==1, klab::UInt8, klab::UInt32>::RESULT a = 0;
        klab::TYPEIF<1!=1, klab::UInt8, klab::UInt32>::RESULT b = 0;
        TEST_ASSERT(sizeof(a) == 1)
        TEST_ASSERT(sizeof(b) == 4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testVALUEIF()
{
    try
    {
        klab::Int32 i1 = klab::VALUEIF<1==1, klab::VALUE<10>, klab::VALUE<-10> >::RESULT;
        klab::Int32 i2 = klab::VALUEIF<1!=1, klab::VALUE<10>, klab::VALUE<-10> >::RESULT;
        TEST_ASSERT(i1 == 10)
        TEST_ASSERT(i2 == -10)

        klab::Int32 i3 = klab::VALUEIF<1==1, klab::INC<0>, klab::DEC<0> >::RESULT;
        klab::Int32 i4 = klab::VALUEIF<1!=1, klab::INC<0>, klab::DEC<0> >::RESULT;
        TEST_ASSERT(i3 == 1)
        TEST_ASSERT(i4 == -1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testIF()
{
    try
    {
        KTemplateUtilUnitTest::TestValue = 0;
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 0)

        klab::IF<1==1, KTemplateUtilUnitTest_IncrementTestValue<0>, KTemplateUtilUnitTest_DecrementTestValue<0> >::Do();
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 1)

        klab::IF<1==1, KTemplateUtilUnitTest_IncrementTestValue<0>, KTemplateUtilUnitTest_DecrementTestValue<0> >::Do();
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 2)

        klab::IF<1!=1, KTemplateUtilUnitTest_IncrementTestValue<0>, KTemplateUtilUnitTest_DecrementTestValue<0> >::Do();
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 1)

        klab::IF<1!=1, KTemplateUtilUnitTest_IncrementTestValue<0>, KTemplateUtilUnitTest_DecrementTestValue<0> >::Do();
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 0)

        klab::IF<1==1, KTemplateUtilUnitTest_IncrementTestValue<0> >::Do();
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 1)

        klab::IF<1!=1, KTemplateUtilUnitTest_IncrementTestValue<0> >::Do();
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 1)        
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testLOOP()
{
    try
    {
        KTemplateUtilUnitTest::TestValue = 0;
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 0)

        klab::LOOP<5, KTemplateUtilUnitTest_IncrementTestValue>::Do();
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 5)

        klab::LOOP<2, KTemplateUtilUnitTest_IncrementTestValue>::Do();
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == 7)

        klab::LOOP<10, KTemplateUtilUnitTest_DecrementTestValue>::Do();
        TEST_ASSERT(KTemplateUtilUnitTest::TestValue == -3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testFILLARRAY()
{
    try
    {
        klab::Int32 array1[3]      = {10, -20, 30};
        klab::DoubleReal array2[5] = {1.2, 2.3, 3.4, 4.5, 5.6};
    
        TEST_ASSERT(array1[0] == 10)
        TEST_ASSERT(array1[1] == -20)
        TEST_ASSERT(array1[2] == 30)
        TEST_ASSERT(klab::Equals(array2[0], 1.2))
        TEST_ASSERT(klab::Equals(array2[1], 2.3))
        TEST_ASSERT(klab::Equals(array2[2], 3.4))
        TEST_ASSERT(klab::Equals(array2[3], 4.5))
        TEST_ASSERT(klab::Equals(array2[4], 5.6))

        klab::FILLARRAY<klab::Int32, 3>::Do(array1, 0);
        TEST_ASSERT(array1[0] == 0)
        TEST_ASSERT(array1[1] == 0)
        TEST_ASSERT(array1[2] == 0)

        klab::FILLARRAY<klab::DoubleReal, 5>::Do(array2, 1.0);
        TEST_ASSERT(klab::Equals(array2[0], 1.0))
        TEST_ASSERT(klab::Equals(array2[1], 1.0))
        TEST_ASSERT(klab::Equals(array2[2], 1.0))
        TEST_ASSERT(klab::Equals(array2[3], 1.0))
        TEST_ASSERT(klab::Equals(array2[4], 1.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testCOPYARRAY()
{
    try
    {
        klab::Int32 array1[3]      = {10, -20, 30};
        klab::Int32 array2[3]      = {0, 0, 0};
        klab::DoubleReal array3[5] = {1.2, 2.3, 3.4, 4.5, 5.6};
        klab::DoubleReal array4[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    
        TEST_ASSERT(array1[0] == 10)
        TEST_ASSERT(array1[1] == -20)
        TEST_ASSERT(array1[2] == 30)
        TEST_ASSERT(array2[0] == 0)
        TEST_ASSERT(array2[1] == 0)
        TEST_ASSERT(array2[2] == 0)
        TEST_ASSERT(klab::Equals(array3[0], 1.2))
        TEST_ASSERT(klab::Equals(array3[1], 2.3))
        TEST_ASSERT(klab::Equals(array3[2], 3.4))
        TEST_ASSERT(klab::Equals(array3[3], 4.5))
        TEST_ASSERT(klab::Equals(array3[4], 5.6))
        TEST_ASSERT(klab::Equals(array4[0], 0.0))
        TEST_ASSERT(klab::Equals(array4[1], 0.0))
        TEST_ASSERT(klab::Equals(array4[2], 0.0))
        TEST_ASSERT(klab::Equals(array4[3], 0.0))
        TEST_ASSERT(klab::Equals(array4[4], 0.0))

        klab::COPYARRAY<klab::Int32, 3>::Do(array1, array2);
        TEST_ASSERT(array1[0] == 10)
        TEST_ASSERT(array1[1] == -20)
        TEST_ASSERT(array1[2] == 30)
        TEST_ASSERT(array2[0] == 10)
        TEST_ASSERT(array2[1] == -20)
        TEST_ASSERT(array2[2] == 30)

        klab::COPYARRAY<klab::DoubleReal, 5>::Do(array3, array4);
        TEST_ASSERT(klab::Equals(array3[0], 1.2))
        TEST_ASSERT(klab::Equals(array3[1], 2.3))
        TEST_ASSERT(klab::Equals(array3[2], 3.4))
        TEST_ASSERT(klab::Equals(array3[3], 4.5))
        TEST_ASSERT(klab::Equals(array3[4], 5.6))
        TEST_ASSERT(klab::Equals(array4[0], 1.2))
        TEST_ASSERT(klab::Equals(array4[1], 2.3))
        TEST_ASSERT(klab::Equals(array4[2], 3.4))
        TEST_ASSERT(klab::Equals(array4[3], 4.5))
        TEST_ASSERT(klab::Equals(array4[4], 5.6))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testMIN()
{
    try
    {
        klab::UInt32 result = MIN<klab::UInt32, 1, 2>::RESULT;
        TEST_ASSERT(result == 1)

        result = MIN<klab::UInt32, 1, 1>::RESULT;
        TEST_ASSERT(result == 1)

        result = MIN<klab::UInt32, 2, 1>::RESULT;
        TEST_ASSERT(result == 1)

        result = MIN<klab::UInt32, 2, 2>::RESULT;
        TEST_ASSERT(result == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testMAX()
{
    try
    {
        klab::UInt32 result = MAX<klab::UInt32, 1, 2>::RESULT;
        TEST_ASSERT(result == 2)

        result = MAX<klab::UInt32, 1, 1>::RESULT;
        TEST_ASSERT(result == 1)

        result = MAX<klab::UInt32, 2, 1>::RESULT;
        TEST_ASSERT(result == 2)

        result = MAX<klab::UInt32, 2, 2>::RESULT;
        TEST_ASSERT(result == 2)   
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testPOWER()
{
    try
    {
        klab::UInt32 result = klab::POWER<2, 0>::RESULT;
        TEST_ASSERT(result == 1)

        result = klab::POWER<2, 2>::RESULT;
        TEST_ASSERT(result == 4)

        result = klab::POWER<3, 2>::RESULT;
        TEST_ASSERT(result == 9) 

        result = klab::POWER<2, 8>::RESULT;
        TEST_ASSERT(result == 256)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTemplateUtilUnitTest::testSTATIC_ASSERT()
{
    try
    {
        klab::STATIC_ASSERT<true>();
        //klab::STATIC_ASSERT<false>();

        klab::STATIC_ASSERT<(1>0)>();
        //klab::STATIC_ASSERT<(1<0)>();


        KLAB_STATIC_ASSERT(true);
        //KLAB_STATIC_ASSERT(false);

        KLAB_STATIC_ASSERT(1>0);
        //KLAB_STATIC_ASSERT(1<0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
