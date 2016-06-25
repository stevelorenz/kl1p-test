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

#include "RGBColorUnitTest.h"
#include "../include/RGBColor.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KRGBColorUnitTest::KRGBColorUnitTest() : Test::Suite()
{
    TEST_ADD(KRGBColorUnitTest::testDefaultConstructor)
    TEST_ADD(KRGBColorUnitTest::testRGBConstructor)
    TEST_ADD(KRGBColorUnitTest::testCopyConstructor)
    TEST_ADD(KRGBColorUnitTest::testAffectationOperator)

    TEST_ADD(KRGBColorUnitTest::testEqualOperator)
    TEST_ADD(KRGBColorUnitTest::testNotEqualOperator)

    TEST_ADD(KRGBColorUnitTest::testSet)
    TEST_ADD(KRGBColorUnitTest::testSetRed)
    TEST_ADD(KRGBColorUnitTest::testSetGreen)
    TEST_ADD(KRGBColorUnitTest::testSetBlue)
    TEST_ADD(KRGBColorUnitTest::testRed)
    TEST_ADD(KRGBColorUnitTest::testGreen)
    TEST_ADD(KRGBColorUnitTest::testBlue)

    TEST_ADD(KRGBColorUnitTest::testIsEqual)
}

// ---------------------------------------------------------------------------------------------------- //

KRGBColorUnitTest::~KRGBColorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testDefaultConstructor()
{
    try
    {
        TRGBColor<klab::UInt8> color;
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testRGBConstructor()
{
    try
    {
        TRGBColor<klab::UInt8> color(12, 34, 56);
        TEST_ASSERT(color.red()==12 && color.green()==34 && color.blue()==56)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testCopyConstructor()
{
    try
    {
        TRGBColor<klab::UInt8> color(12, 34, 56);
        TEST_ASSERT(color.red()==12 && color.green()==34 && color.blue()==56)

        TRGBColor<klab::UInt8> copyColor(color);
        TEST_ASSERT(copyColor.red()==12 && copyColor.green()==34 && copyColor.blue()==56)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testAffectationOperator()
{
    try
    {
        TRGBColor<klab::UInt8> color(12, 34, 56);
        TEST_ASSERT(color.red()==12 && color.green()==34 && color.blue()==56)

        TRGBColor<klab::UInt8> copyColor;
        copyColor = color;
        TEST_ASSERT(copyColor.red()==12 && copyColor.green()==34 && copyColor.blue()==56)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testEqualOperator()
{
    try
    {
        TRGBColor<klab::UInt8> color(12, 34, 56);
        TEST_ASSERT(color.red()==12 && color.green()==34 && color.blue()==56)

        TRGBColor<klab::UInt8> copyColor;
        copyColor = color;
        TEST_ASSERT(copyColor.red()==12 && copyColor.green()==34 && copyColor.blue()==56)

        TRGBColor<klab::UInt8> color2(12, 34, 57);

        TEST_ASSERT(copyColor==color && color==copyColor)
        TEST_ASSERT((color2==color)==false && (color==color2)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testNotEqualOperator()
{
    try
    {
        TRGBColor<klab::UInt8> color(12, 34, 56);
        TEST_ASSERT(color.red()==12 && color.green()==34 && color.blue()==56)

        TRGBColor<klab::UInt8> copyColor;
        copyColor = color;
        TEST_ASSERT(copyColor.red()==12 && copyColor.green()==34 && copyColor.blue()==56)

        TRGBColor<klab::UInt8> color2(12, 34, 57);

        TEST_ASSERT((copyColor!=color)==false && (color!=copyColor)==false)
        TEST_ASSERT(color2!=color && color!=color2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testSet()
{
    try
    {
        TRGBColor<klab::UInt8> color;
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==0)

        color.set(12, 34, 56);
        TEST_ASSERT(color.red()==12 && color.green()==34 && color.blue()==56)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testSetRed()
{
    try
    {
        TRGBColor<klab::UInt8> color;
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==0)

        color.setRed(12);
        TEST_ASSERT(color.red()==12 && color.green()==0 && color.blue()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testSetGreen()
{
    try
    {
        TRGBColor<klab::UInt8> color;
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==0)

        color.setGreen(12);
        TEST_ASSERT(color.red()==0 && color.green()==12 && color.blue()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testSetBlue()
{
    try
    {
        TRGBColor<klab::UInt8> color;
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==0)

        color.setBlue(12);
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==12)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testRed()
{
    try
    {
        TRGBColor<klab::UInt8> color;
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==0)

        color.setRed(12);
        TEST_ASSERT(color.red()==12 && color.green()==0 && color.blue()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testGreen()
{
    try
    {
        TRGBColor<klab::UInt8> color;
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==0)

        color.setGreen(12);
        TEST_ASSERT(color.red()==0 && color.green()==12 && color.blue()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testBlue()
{
    try
    {
        TRGBColor<klab::UInt8> color;
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==0)

        color.setBlue(12);
        TEST_ASSERT(color.red()==0 && color.green()==0 && color.blue()==12)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRGBColorUnitTest::testIsEqual()
{
    try
    {
        TRGBColor<klab::UInt8> color(12, 34, 56);
        TEST_ASSERT(color.red()==12 && color.green()==34 && color.blue()==56)

        TRGBColor<klab::UInt8> copyColor;
        copyColor = color;
        TEST_ASSERT(copyColor.red()==12 && copyColor.green()==34 && copyColor.blue()==56)

        TRGBColor<klab::UInt8> color2(12, 34, 57);

        TEST_ASSERT(copyColor.isEqual(color) && color.isEqual(copyColor))
        TEST_ASSERT(color2.isEqual(color)==false && color.isEqual(color2)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
