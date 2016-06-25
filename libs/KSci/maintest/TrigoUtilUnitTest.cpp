// KSci - A portable C++ numerical analysis library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KSci C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#include "TrigoUtilUnitTest.h"
#include "../include/TrigoUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KTrigoUtilUnitTest::KTrigoUtilUnitTest() : Test::Suite()
{
    TEST_ADD(KTrigoUtilUnitTest::testCos)
    TEST_ADD(KTrigoUtilUnitTest::testCosH)
    TEST_ADD(KTrigoUtilUnitTest::testACos)
    TEST_ADD(KTrigoUtilUnitTest::testSin)
    TEST_ADD(KTrigoUtilUnitTest::testSinH)
    TEST_ADD(KTrigoUtilUnitTest::testASin)
    TEST_ADD(KTrigoUtilUnitTest::testTan)
    TEST_ADD(KTrigoUtilUnitTest::testTanH)        
    TEST_ADD(KTrigoUtilUnitTest::testATan)
    TEST_ADD(KTrigoUtilUnitTest::testATan2)
}

// ---------------------------------------------------------------------------------------------------- //

KTrigoUtilUnitTest::~KTrigoUtilUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testCos()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Cos(0.0), 1.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Cos(klab::PI_4), 0.7071067811865476, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Cos(klab::PI_2), 0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Cos(3.0*klab::PI_4), -0.7071067811865476, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Cos(klab::PI), -1.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Cos(5.0*klab::PI_4), -0.7071067811865476, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Cos(3.0*klab::PI_2), 0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Cos(7.0*klab::PI_4), 0.7071067811865476, 1e-14));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testCosH()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::CosH(-5.0), 74.209948524787848, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(-4.0), 27.308232836016487, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(-3.0), 10.067661995777765, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(-2.0), 3.7621956910836314, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(-1.0), 1.5430806348152439, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(0.0),  1.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(1.0),  1.5430806348152439, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(2.0),  3.7621956910836314, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(3.0),  10.067661995777765, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(4.0),  27.308232836016487, 1e-14));
        TEST_ASSERT(klab::Equals(klab::CosH(5.0),  74.209948524787848, 1e-14));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testACos()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::ACos(-1.0), klab::PI, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ACos(-0.7071067811865476), 3*klab::PI_4, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ACos(0.0), klab::PI_2, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ACos(0.7071067811865476), klab::PI_4, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ACos(1.0), 0.0, 1e-14));


        // Limit cases.
        try
        {
            klab::DoubleReal value = klab::ACos(-1.1);
            TEST_ASSERT(false)
        }
        catch(klab::KACosMathsException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            klab::DoubleReal value = klab::ACos(1.1);
            TEST_ASSERT(false)
        }
        catch(klab::KACosMathsException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testSin()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Sin(0.0), 0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Sin(klab::PI_4), 0.7071067811865476, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Sin(klab::PI_2), 1.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Sin(3.0*klab::PI_4), 0.7071067811865476, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Sin(klab::PI), 0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Sin(5.0*klab::PI_4), -0.7071067811865476, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Sin(3.0*klab::PI_2), -1.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Sin(7.0*klab::PI_4), -0.7071067811865476, 1e-14));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testSinH()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::SinH(-5.0), -74.203210577788752, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(-4.0), -27.28991719712775, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(-3.0), -10.017874927409903, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(-2.0), -3.626860407847019, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(-1.0), -1.1752011936438014, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(0.0),  0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(1.0),  1.1752011936438014, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(2.0),  3.626860407847019, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(3.0),  10.017874927409903, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(4.0),  27.28991719712775, 1e-14));
        TEST_ASSERT(klab::Equals(klab::SinH(5.0),  74.203210577788752, 1e-14));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testASin()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::ASin(-1.0), -klab::PI_2, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ASin(-0.7071067811865476), -klab::PI_4, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ASin(0.0), 0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ASin(0.7071067811865476), klab::PI_4, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ASin(1.0), klab::PI_2, 1e-14));


        // Limit cases.
        try
        {
            klab::DoubleReal value = klab::ASin(-1.1);
            TEST_ASSERT(false)
        }
        catch(klab::KASinMathsException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            klab::DoubleReal value = klab::ASin(1.1);
            TEST_ASSERT(false)
        }
        catch(klab::KASinMathsException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testTan()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Tan(0.0), 0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Tan(klab::PI_4), 0.99999999999999989, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Tan(3.0*klab::PI_4), -1.0000000000000002, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Tan(klab::PI), 0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Tan(5.0*klab::PI_4), 0.99999999999999967, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Tan(7.0*klab::PI_4), -1.0000000000000004, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Tan(-klab::PI_2), -16331239353195370.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::Tan(klab::PI_2), 16331239353195370.0, 1e-14));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testTanH()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::TanH(-5.0), -0.99990920426259511, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(-4.0), -0.99932929973906703, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(-3.0), -0.99505475368673046, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(-2.0), -0.9640275800758169, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(-1.0), -0.76159415595576485, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(0.0),  0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(1.0),  0.76159415595576485, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(2.0),  0.9640275800758169, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(3.0),  0.99505475368673046, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(4.0),  0.99932929973906703, 1e-14));
        TEST_ASSERT(klab::Equals(klab::TanH(5.0),  0.99990920426259511, 1e-14));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testATan()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::ATan(-5.0), -1.3734007669450159, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(-4.0), -1.3258176636680326, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(-3.0), -1.2490457723982544, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(-2.0), -1.1071487177940904, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(-1.0), -0.78539816339744828, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(0.0),  0.0, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(1.0),  0.78539816339744828, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(2.0),  1.1071487177940904, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(3.0),  1.2490457723982544, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(4.0),  1.3258176636680326, 1e-14));
        TEST_ASSERT(klab::Equals(klab::ATan(5.0),  1.3734007669450159, 1e-14));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTrigoUtilUnitTest::testATan2()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::ATan2(3.0, 4.0), 0.64350110879328437, 1e-14));


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::ATan2(0.0, 0.0), 0.0, 1e-14));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
