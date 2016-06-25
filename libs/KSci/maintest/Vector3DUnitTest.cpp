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

#include "Vector3DUnitTest.h"
#include "../include/Vector3D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KVector3DUnitTest::KVector3DUnitTest() : Test::Suite()
{
    TEST_ADD(KVector3DUnitTest::testDefaultConstructor)
    TEST_ADD(KVector3DUnitTest::testXYZConstructor)
    TEST_ADD(KVector3DUnitTest::testVector2DConstructor)
    TEST_ADD(KVector3DUnitTest::testCopyConstructor)
    TEST_ADD(KVector3DUnitTest::testVector2DAffectationOperator)
    TEST_ADD(KVector3DUnitTest::testAffectationOperator)

    TEST_ADD(KVector3DUnitTest::testClear)
    TEST_ADD(KVector3DUnitTest::testSet)
    TEST_ADD(KVector3DUnitTest::testSetX)
    TEST_ADD(KVector3DUnitTest::testSetY)
    TEST_ADD(KVector3DUnitTest::testSetZ)
    TEST_ADD(KVector3DUnitTest::testX)
    TEST_ADD(KVector3DUnitTest::testY)
    TEST_ADD(KVector3DUnitTest::testZ)

    TEST_ADD(KVector3DUnitTest::testEquals)
    TEST_ADD(KVector3DUnitTest::testCompareVector3DOnX)
    TEST_ADD(KVector3DUnitTest::testCompareVector3DOnY)
    TEST_ADD(KVector3DUnitTest::testCompareVector3DOnZ)
}

// ---------------------------------------------------------------------------------------------------- //

KVector3DUnitTest::~KVector3DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testDefaultConstructor()
{
    try
    {
        TVector3D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testXYZConstructor()
{
    try
    {
        TVector3D<klab::DoubleReal> v(1.23, 2.34, 3.45);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 2.34) && klab::Equals(v.z(), 3.45))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testVector2DConstructor()
{
    try
    {
        TVector2D<klab::DoubleReal> v2D(1.23, 2.34);
        TEST_ASSERT(klab::Equals(v2D.x(), 1.23) && klab::Equals(v2D.y(), 2.34))

        TVector3D<klab::DoubleReal> v(v2D);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 2.34) && klab::Equals(v.z(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testCopyConstructor()
{
    try
    {
        TVector3D<klab::DoubleReal> v1(1.23, 2.34, 3.45);
        TEST_ASSERT(klab::Equals(v1.x(), 1.23) && klab::Equals(v1.y(), 2.34) && klab::Equals(v1.z(), 3.45))

        TVector3D<klab::DoubleReal> v2(v1);
        TEST_ASSERT(klab::Equals(v2.x(), 1.23) && klab::Equals(v2.y(), 2.34) && klab::Equals(v2.z(), 3.45))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testVector2DAffectationOperator()
{
    try
    {
        TVector2D<klab::DoubleReal> v2D(1.23, 2.34);
        TEST_ASSERT(klab::Equals(v2D.x(), 1.23) && klab::Equals(v2D.y(), 2.34))

        TVector3D<klab::DoubleReal> v;
        v = v2D;
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 2.34) && klab::Equals(v.z(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testAffectationOperator()
{
    try
    {
        TVector3D<klab::DoubleReal> v1(1.23, 2.34, 3.45);
        TEST_ASSERT(klab::Equals(v1.x(), 1.23) && klab::Equals(v1.y(), 2.34) && klab::Equals(v1.z(), 3.45))

        TVector3D<klab::DoubleReal> v2;
        v2 = v1;
        TEST_ASSERT(klab::Equals(v2.x(), 1.23) && klab::Equals(v2.y(), 2.34) && klab::Equals(v2.z(), 3.45))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testClear()
{
    try
    {
        TVector3D<klab::DoubleReal> v(1.23, 2.34, 3.45);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 2.34) && klab::Equals(v.z(), 3.45))

        v.clear();
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testSet()
{
    try
    {
        TVector3D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))

        v.set(1.23, 2.34, 3.45);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 2.34) && klab::Equals(v.z(), 3.45))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testSetX()
{
    try
    {
        TVector3D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))

        v.setX(1.23);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testSetY()
{
    try
    {
        TVector3D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))

        v.setY(2.34);
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 2.34) && klab::Equals(v.z(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testSetZ()
{
    try
    {
        TVector3D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))

        v.setZ(3.45);
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 3.45))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testX()
{
    try
    {
        TVector3D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))

        v.setX(1.23);
        TEST_ASSERT(klab::Equals(v.x(), 1.23) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testY()
{
    try
    {
        TVector3D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))

        v.setY(2.34);
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 2.34) && klab::Equals(v.z(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testZ()
{
    try
    {
        TVector3D<klab::DoubleReal> v;
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 0.0))

        v.setZ(3.45);
        TEST_ASSERT(klab::Equals(v.x(), 0.0) && klab::Equals(v.y(), 0.0) && klab::Equals(v.z(), 3.45))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testEquals()
{
    try
    {
        TVector3D<klab::DoubleReal> vect1(1.2, 2.3, 3.4);
        TVector3D<klab::DoubleReal> vect2(1.2, 2.3, 3.4);
        TVector3D<klab::DoubleReal> vect3(2.3, 3.4, 4.5);
        TVector3D<klab::DoubleReal> vect4(1.2, 2.5, 3.4);
        TVector3D<klab::DoubleReal> vect5(1.5, 2.3, 3.4);
        TVector3D<klab::DoubleReal> vect6(1.2, 2.3, 3.5);

        TEST_ASSERT(klab::Equals(vect1, vect2) && klab::Equals(vect2, vect1) && klab::Equals(vect1, vect2, 1e-6) && klab::Equals(vect2, vect1, 1e-6))
        TEST_ASSERT(klab::Equals(vect1, vect3)==false && klab::Equals(vect3, vect1)==false && klab::Equals(vect1, vect3, 1e-6)==false && klab::Equals(vect3, vect1, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect1, vect4)==false && klab::Equals(vect4, vect1)==false && klab::Equals(vect1, vect4, 1e-6)==false && klab::Equals(vect4, vect1, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect1, vect5)==false && klab::Equals(vect5, vect1)==false && klab::Equals(vect1, vect5, 1e-6)==false && klab::Equals(vect5, vect1, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect1, vect6)==false && klab::Equals(vect6, vect1)==false && klab::Equals(vect1, vect6, 1e-6)==false && klab::Equals(vect6, vect1, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect2, vect3)==false && klab::Equals(vect3, vect2)==false && klab::Equals(vect2, vect3, 1e-6)==false && klab::Equals(vect3, vect2, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect2, vect4)==false && klab::Equals(vect4, vect2)==false && klab::Equals(vect2, vect4, 1e-6)==false && klab::Equals(vect4, vect2, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect2, vect5)==false && klab::Equals(vect5, vect2)==false && klab::Equals(vect2, vect5, 1e-6)==false && klab::Equals(vect5, vect2, 1e-6)==false)
        TEST_ASSERT(klab::Equals(vect2, vect6)==false && klab::Equals(vect6, vect2)==false && klab::Equals(vect2, vect6, 1e-6)==false && klab::Equals(vect6, vect2, 1e-6)==false)


        // Limit cases.
        TEST_ASSERT(klab::Equals(vect1, vect1) && klab::Equals(vect1, vect1, 1e-6))
        TEST_ASSERT(klab::Equals(vect2, vect2) && klab::Equals(vect2, vect2, 1e-6))
        TEST_ASSERT(klab::Equals(vect3, vect3) && klab::Equals(vect3, vect3, 1e-6))
        TEST_ASSERT(klab::Equals(vect4, vect4) && klab::Equals(vect4, vect4, 1e-6))
        TEST_ASSERT(klab::Equals(vect5, vect5) && klab::Equals(vect5, vect5, 1e-6))
        TEST_ASSERT(klab::Equals(vect6, vect6) && klab::Equals(vect6, vect6, 1e-6))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testCompareVector3DOnX()
{
    try
    {
        TVector3D<klab::DoubleReal> vect1(1.2, 2.3, 3.4);
        TVector3D<klab::DoubleReal> vect2(2.3, 3.4, 4.5);

        TEST_ASSERT(klab::CompareVector3DOnX_LessThan(vect1, vect2) && klab::CompareVector3DOnX_GreaterThan(vect1, vect2)==false)
        TEST_ASSERT(klab::CompareVector3DOnX_LessThan(vect2, vect1)==false && klab::CompareVector3DOnX_GreaterThan(vect2, vect1))


        // Limit cases.
        TEST_ASSERT(klab::CompareVector3DOnX_LessThan(vect1, vect1)==false && klab::CompareVector3DOnX_GreaterThan(vect1, vect1)==false)
        TEST_ASSERT(klab::CompareVector3DOnX_LessThan(vect2, vect2)==false && klab::CompareVector3DOnX_GreaterThan(vect2, vect2)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testCompareVector3DOnY()
{
    try
    {
        TVector3D<klab::DoubleReal> vect1(1.2, 2.3, 3.4);
        TVector3D<klab::DoubleReal> vect2(2.3, 3.4, 4.5);

        TEST_ASSERT(klab::CompareVector3DOnY_LessThan(vect1, vect2) && klab::CompareVector3DOnY_GreaterThan(vect1, vect2)==false)
        TEST_ASSERT(klab::CompareVector3DOnY_LessThan(vect2, vect1)==false && klab::CompareVector3DOnY_GreaterThan(vect2, vect1))


        // Limit cases.
        TEST_ASSERT(klab::CompareVector3DOnY_LessThan(vect1, vect1)==false && klab::CompareVector3DOnY_GreaterThan(vect1, vect1)==false)
        TEST_ASSERT(klab::CompareVector3DOnY_LessThan(vect2, vect2)==false && klab::CompareVector3DOnY_GreaterThan(vect2, vect2)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KVector3DUnitTest::testCompareVector3DOnZ()
{
    try
    {
        TVector3D<klab::DoubleReal> vect1(1.2, 2.3, 3.4);
        TVector3D<klab::DoubleReal> vect2(2.3, 3.4, 4.5);

        TEST_ASSERT(klab::CompareVector3DOnZ_LessThan(vect1, vect2) && klab::CompareVector3DOnZ_GreaterThan(vect1, vect2)==false)
        TEST_ASSERT(klab::CompareVector3DOnZ_LessThan(vect2, vect1)==false && klab::CompareVector3DOnZ_GreaterThan(vect2, vect1))


        // Limit cases.
        TEST_ASSERT(klab::CompareVector3DOnZ_LessThan(vect1, vect1)==false && klab::CompareVector3DOnZ_GreaterThan(vect1, vect1)==false)
        TEST_ASSERT(klab::CompareVector3DOnZ_LessThan(vect2, vect2)==false && klab::CompareVector3DOnZ_GreaterThan(vect2, vect2)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
