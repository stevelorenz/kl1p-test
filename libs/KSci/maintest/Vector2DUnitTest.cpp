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

#include "Vector2DUnitTest.h"
#include "../include/Vector2D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KVector2DUnitTest::KVector2DUnitTest() : Test::Suite()
{
    TEST_ADD(KVector2DUnitTest::testDefaultConstructor) 
    TEST_ADD(KVector2DUnitTest::testXYConstructor)
    TEST_ADD(KVector2DUnitTest::testCopyConstructor)
    TEST_ADD(KVector2DUnitTest::testAffectationOperator)

    TEST_ADD(KVector2DUnitTest::testClear)
    TEST_ADD(KVector2DUnitTest::testSet)
    TEST_ADD(KVector2DUnitTest::testSetX)
    TEST_ADD(KVector2DUnitTest::testSetY)
    TEST_ADD(KVector2DUnitTest::testX)
    TEST_ADD(KVector2DUnitTest::testY)

    TEST_ADD(KVector2DUnitTest::testEquals)
    TEST_ADD(KVector2DUnitTest::testCompareVector2DOnX)
    TEST_ADD(KVector2DUnitTest::testCompareVector2DOnY)
}

// ---------------------------------------------------------------------------------------------------- //

KVector2DUnitTest::~KVector2DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testDefaultConstructor()
{
    try
    {
        TVector2D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testXYConstructor()
{
    try
    {
        TVector2D<klab::DoubleReal> v(1.23, 2.34);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 2.34))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testCopyConstructor()
{
    try
    {
        TVector2D<klab::DoubleReal> v1(1.23, 2.34);
        TEST_ASSERT(klab::Equals(v1.x(), 1.23) && klab::Equals(v1.y(), 2.34))

        TVector2D<klab::DoubleReal> v2(v1);
        TEST_ASSERT(klab::Equals(v2.x(), 1.23) && klab::Equals(v2.y(), 2.34))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testAffectationOperator()
{
    try
    {
        TVector2D<klab::DoubleReal> v1(1.23, 2.34);
        TEST_ASSERT(klab::Equals(v1.x(), 1.23) && klab::Equals(v1.y(), 2.34))

        TVector2D<klab::DoubleReal> v2;
        v2 = v1;
        TEST_ASSERT(klab::Equals(v2.x(), 1.23) && klab::Equals(v2.y(), 2.34))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testClear()
{
    try
    {
        TVector2D<klab::DoubleReal> v(1.23, 2.34);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 2.34))

        v.clear();
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testSet()
{
    try
    {
        TVector2D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0))

        v.set(1.23, 2.34);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 2.34))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testSetX()
{
    try
    {
        TVector2D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0))

        v.setX(1.23);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testSetY()
{
    try
    {
        TVector2D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0))

        v.setY(2.34);
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 2.34))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testX()
{
    try
    {
        TVector2D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0))

        v.setX(1.23);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testY()
{
    try
    {
        TVector2D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0))

        v.setY(2.34);
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 2.34))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testEquals()
{
    try
    {
        TVector2D<klab::DoubleReal> vect1(1.2, 2.3);
        TVector2D<klab::DoubleReal> vect2(1.2, 2.3);
        TVector2D<klab::DoubleReal> vect3(2.3, 3.4);
        TVector2D<klab::DoubleReal> vect4(1.2, 2.5);
        TVector2D<klab::DoubleReal> vect5(1.5, 2.3);

        TEST_ASSERT(klab::Equals(vect1, vect2) && klab::Equals(vect2, vect1) && klab::Equals(vect1, vect2, 1e-6) && klab::Equals(vect2, vect1, 1e-6))
        TEST_ASSERT(klab::Equals(vect1, vect3)==false && klab::Equals(vect3, vect1)==false && klab::Equals(vect1, vect3, 1e-6)==false && klab::Equals(vect3, vect1, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect1, vect4)==false && klab::Equals(vect4, vect1)==false && klab::Equals(vect1, vect4, 1e-6)==false && klab::Equals(vect4, vect1, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect1, vect5)==false && klab::Equals(vect5, vect1)==false && klab::Equals(vect1, vect5, 1e-6)==false && klab::Equals(vect5, vect1, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect2, vect3)==false && klab::Equals(vect3, vect2)==false && klab::Equals(vect2, vect3, 1e-6)==false && klab::Equals(vect3, vect2, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect2, vect4)==false && klab::Equals(vect4, vect2)==false && klab::Equals(vect2, vect4, 1e-6)==false && klab::Equals(vect4, vect2, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect2, vect5)==false && klab::Equals(vect5, vect2)==false && klab::Equals(vect2, vect5, 1e-6)==false && klab::Equals(vect5, vect2, 1e-6)==false)


        // Limit cases.
        TEST_ASSERT(klab::Equals(vect1, vect1) && klab::Equals(vect1, vect1, 1e-6))
        TEST_ASSERT(klab::Equals(vect2, vect2) && klab::Equals(vect1, vect1, 1e-6))
        TEST_ASSERT(klab::Equals(vect3, vect3) && klab::Equals(vect1, vect1, 1e-6))
        TEST_ASSERT(klab::Equals(vect4, vect4) && klab::Equals(vect1, vect1, 1e-6))
        TEST_ASSERT(klab::Equals(vect5, vect5) && klab::Equals(vect1, vect1, 1e-6))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testCompareVector2DOnX()
{
    try
    {
        TVector2D<klab::DoubleReal> vect1(1.2, 2.3);
        TVector2D<klab::DoubleReal> vect2(2.3, 3.4);

        TEST_ASSERT(klab::CompareVector2DOnX_LessThan(vect1, vect2) && klab::CompareVector2DOnX_GreaterThan(vect1, vect2)==false)
        TEST_ASSERT(klab::CompareVector2DOnX_LessThan(vect2, vect1)==false && klab::CompareVector2DOnX_GreaterThan(vect2, vect1))


        // Limit cases.
        TEST_ASSERT(klab::CompareVector2DOnX_LessThan(vect1, vect1)==false && klab::CompareVector2DOnX_GreaterThan(vect1, vect1)==false)
        TEST_ASSERT(klab::CompareVector2DOnX_LessThan(vect2, vect2)==false && klab::CompareVector2DOnX_GreaterThan(vect2, vect2)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector2DUnitTest::testCompareVector2DOnY()
{
    try
    {
        TVector2D<klab::DoubleReal> vect1(1.2, 2.3);
        TVector2D<klab::DoubleReal> vect2(2.3, 3.4);

        TEST_ASSERT(klab::CompareVector2DOnY_LessThan(vect1, vect2) && klab::CompareVector2DOnY_GreaterThan(vect1, vect2)==false)
        TEST_ASSERT(klab::CompareVector2DOnY_LessThan(vect2, vect1)==false && klab::CompareVector2DOnY_GreaterThan(vect2, vect1))


        // Limit cases.
        TEST_ASSERT(klab::CompareVector2DOnY_LessThan(vect1, vect1)==false && klab::CompareVector2DOnY_GreaterThan(vect1, vect1)==false)
        TEST_ASSERT(klab::CompareVector2DOnY_LessThan(vect2, vect2)==false && klab::CompareVector2DOnY_GreaterThan(vect2, vect2)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
