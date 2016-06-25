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

#include "CubicInterpolationFilterUnitTest.h"
#include "../include/CubicInterpolationFilter.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KCubicInterpolationFilterUnitTest::KCubicInterpolationFilterUnitTest() : Test::Suite()
{
    TEST_ADD(KCubicInterpolationFilterUnitTest::testDefaultConstructor) 
    TEST_ADD(KCubicInterpolationFilterUnitTest::testCopyConstructor)
    TEST_ADD(KCubicInterpolationFilterUnitTest::testAffectationOperator)

    TEST_ADD(KCubicInterpolationFilterUnitTest::testInterpolate_BetweenValues)
    TEST_ADD(KCubicInterpolationFilterUnitTest::testInterpolate_MuBetweenValues)
    TEST_ADD(KCubicInterpolationFilterUnitTest::testInterpolate_BetweenPoints)
    TEST_ADD(KCubicInterpolationFilterUnitTest::testInterpolate_PointsArray)
    TEST_ADD(KCubicInterpolationFilterUnitTest::testFindLeftNearestControlPointIndex)
}

// ---------------------------------------------------------------------------------------------------- //

KCubicInterpolationFilterUnitTest::~KCubicInterpolationFilterUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KCubicInterpolationFilterUnitTest::testDefaultConstructor()
{
    try
    {
        TCubicInterpolationFilter<klab::DoubleReal> filter;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCubicInterpolationFilterUnitTest::testCopyConstructor()
{
    try
    {
        TCubicInterpolationFilter<klab::DoubleReal> filter1;
        TEST_ASSERT(true)

        TCubicInterpolationFilter<klab::DoubleReal> filter2(filter1);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCubicInterpolationFilterUnitTest::testAffectationOperator()
{
    try
    {
        TCubicInterpolationFilter<klab::DoubleReal> filter1;
        TEST_ASSERT(true)

        TCubicInterpolationFilter<klab::DoubleReal> filter2;
        filter2 = filter1;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCubicInterpolationFilterUnitTest::testInterpolate_BetweenValues()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TCubicInterpolationFilter<klab::DoubleReal> filter;

        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5), 0.65625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0), -0.0625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567), 370.61612499999995, precision))


        // Limit cases.
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(10.0, 10.0, 10.0, 10.0), 10.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCubicInterpolationFilterUnitTest::testInterpolate_MuBetweenValues()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TCubicInterpolationFilter<klab::DoubleReal> filter;

        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5, 0.5), 0.65625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0, 0.5), -0.0625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567, 0.5), 370.61612499999995, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5, 0.1), 0.14725, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0, 0.1), -0.91249999999999998, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567, 0.1), 156.09318900000002, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5, 0.8), 0.91199999999999992, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0, 0.8), 0.68, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567, 0.8), 522.64340800000002, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5, 0.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0, 0.0), -1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567, 0.0), 123.456, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5, 1.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0, 1.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567, 1.0), 567.789, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5, 2.0), 0.5, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0, 2.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567, 2.0), 234.567, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5, -1.0), -2.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0, -1.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567, -1.0), 56.78, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5, 1.5), 0.8125, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0, 1.5), 1.125, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567, 1.5), 428.9488125, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-2.0, 0.0, 1.0, 0.5, -0.5), -1.0625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, -1.0, 1.0, 1.0, -0.5), -0.625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(56.78, 123.456, 567.789, 234.567, -0.5), 62.3471875, precision))


        // Limit cases.
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.5), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(10.0, 10.0, 10.0, 10.0, 0.5), 10.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.1), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(10.0, 10.0, 10.0, 10.0, 0.1), 10.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.8), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(10.0, 10.0, 10.0, 10.0, 0.8), 10.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCubicInterpolationFilterUnitTest::testInterpolate_BetweenPoints()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TCubicInterpolationFilter<klab::DoubleReal> filter;
		
		TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 0.5), 0.65625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), TVector2D<klab::DoubleReal>(3.0, 1.0), 1.5), -0.0625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-4.0, 56.78), TVector2D<klab::DoubleReal>(-2.0, 123.456), TVector2D<klab::DoubleReal>(0.0, 567.789), TVector2D<klab::DoubleReal>(2.0, 234.567), -1.0), 370.61612499999995, precision))
		
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 0.1), 0.14725, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), TVector2D<klab::DoubleReal>(3.0, 1.0), 1.1), -0.91249999999999998, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-4.0, 56.78), TVector2D<klab::DoubleReal>(-2.0, 123.456), TVector2D<klab::DoubleReal>(0.0, 567.789), TVector2D<klab::DoubleReal>(2.0, 234.567), -1.8), 156.09318900000002, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 0.8), 0.91199999999999992, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), TVector2D<klab::DoubleReal>(3.0, 1.0), 1.8), 0.68, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-4.0, 56.78), TVector2D<klab::DoubleReal>(-2.0, 123.456), TVector2D<klab::DoubleReal>(0.0, 567.789), TVector2D<klab::DoubleReal>(2.0, 234.567), -0.4), 522.64340800000002, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 0.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), TVector2D<klab::DoubleReal>(3.0, 1.0), 1.0), -1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-4.0, 56.78), TVector2D<klab::DoubleReal>(-2.0, 123.456), TVector2D<klab::DoubleReal>(0.0, 567.789), TVector2D<klab::DoubleReal>(2.0, 234.567), -2.0), 123.456, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 1.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), TVector2D<klab::DoubleReal>(3.0, 1.0), 2.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-4.0, 56.78), TVector2D<klab::DoubleReal>(-2.0, 123.456), TVector2D<klab::DoubleReal>(0.0, 567.789), TVector2D<klab::DoubleReal>(2.0, 234.567), 0.0), 567.789, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 2.0), 0.5, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), TVector2D<klab::DoubleReal>(3.0, 1.0), 3.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-4.0, 56.78), TVector2D<klab::DoubleReal>(-2.0, 123.456), TVector2D<klab::DoubleReal>(0.0, 567.789), TVector2D<klab::DoubleReal>(2.0, 234.567), 2.0), 234.567, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), -1.0), -2.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), TVector2D<klab::DoubleReal>(3.0, 1.0), 0.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-4.0, 56.78), TVector2D<klab::DoubleReal>(-2.0, 123.456), TVector2D<klab::DoubleReal>(0.0, 567.789), TVector2D<klab::DoubleReal>(2.0, 234.567), -4.0), 56.78, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 1.5), 0.8125, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), TVector2D<klab::DoubleReal>(3.0, 1.0), 2.5), 1.125, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-4.0, 56.78), TVector2D<klab::DoubleReal>(-2.0, 123.456), TVector2D<klab::DoubleReal>(0.0, 567.789), TVector2D<klab::DoubleReal>(2.0, 234.567), 1.0), 428.9488125, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), -0.5), -1.0625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), TVector2D<klab::DoubleReal>(3.0, 1.0), 0.5), -0.625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-4.0, 56.78), TVector2D<klab::DoubleReal>(-2.0, 123.456), TVector2D<klab::DoubleReal>(0.0, 567.789), TVector2D<klab::DoubleReal>(2.0, 234.567), -3.0), 62.3471875, precision))


        // Limit cases.
		TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, 0.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 0.0), TVector2D<klab::DoubleReal>(2.0, 0.0), 0.5), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-10.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), TVector2D<klab::DoubleReal>(20.0, 1.0), 5.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.1, 0.0), TVector2D<klab::DoubleReal>(0.5, 0.0), TVector2D<klab::DoubleReal>(0.7, 0.0), TVector2D<klab::DoubleReal>(8.0, 0.0), 1.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 1.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 1.0), 1.0), 1.0, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 1.0), 0.5),    1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(1.0, 1.0), 0.5), -1.0, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(2.0, 0.5), TVector2D<klab::DoubleReal>(1.0, 1.0), 0.5), 0.65625, precision))        
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(2.0, 0.5), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 0.0), 0.5), 0.65625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(2.0, 0.5), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(-1.0, -2.0), 0.5), 0.65625, precision))        
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 0.5), 0.65625, precision))    
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 0.5), 0.65625, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(-1.0, -2.0), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(2.0, 0.5), 0.5), 0.65625, precision))        
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(2.0, 0.5), TVector2D<klab::DoubleReal>(1.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(-1.0, -2.0), 0.5), 0.65625, precision))        
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCubicInterpolationFilterUnitTest::testInterpolate_PointsArray()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        std::vector<TVector2D<klab::DoubleReal> > controlPoints(8);
        controlPoints[0] = TVector2D<klab::DoubleReal>(-2.0, 5.0);
        controlPoints[1] = TVector2D<klab::DoubleReal>(-1.8, 8.5);
        controlPoints[2] = TVector2D<klab::DoubleReal>(-1.0, 13.2);
        controlPoints[3] = TVector2D<klab::DoubleReal>(-0.3, 12.8);
        controlPoints[4] = TVector2D<klab::DoubleReal>(0.1, 3.4);
        controlPoints[5] = TVector2D<klab::DoubleReal>(0.7, -0.7);
        controlPoints[6] = TVector2D<klab::DoubleReal>(2.0, 0.2);
        controlPoints[7] = TVector2D<klab::DoubleReal>(5.0, 0.8);

        TCubicInterpolationFilter<klab::DoubleReal> filter;        

        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -2.0),  5.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -1.8),  8.5, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -1.0),  13.2, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -0.3),  12.8, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.1),  3.4, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.7), -0.7, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  2.0),  0.2, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  5.0),  0.8, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -3.0),  5.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -1.9),  6.45625, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -1.5),  10.398730468749999, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -0.8),  13.719825072886296, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -0.5),  13.718950437317783, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.0),  5.5882812500000032, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.2),  2.3520833333333329, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.5),  0.099999999999999645, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  1.0), -0.82753755120619021, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  1.5), -0.35188893946290356, precision))    
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  2.5),  0.32430555555555557, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  3.0),  0.44444444444444448, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  4.0),  0.65555555555555556, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  6.0),  0.8, precision)) 


        // Limit cases.
        std::vector<TVector2D<klab::DoubleReal> > controlPoints0;
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints0,  0.0),  0.0, precision)); 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints0, -1.0),  0.0, precision));
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints0,  1.0),  0.0, precision));

        std::vector<TVector2D<klab::DoubleReal> > controlPoints01(1);
        controlPoints01[0] = TVector2D<klab::DoubleReal>(0.0, 1.0);
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints01,  0.0),  1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints01, -1.0),  1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints01,  1.0),  1.0, precision)) 
		
		std::vector<TVector2D<klab::DoubleReal> > controlPoints02(2);
        controlPoints02[0] = TVector2D<klab::DoubleReal>(-1.0, 1.0);
		controlPoints02[1] = TVector2D<klab::DoubleReal>(1.0, 2.0);
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints02,  0.0),  1.5, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints02, -1.0),  1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints02,  1.0),  2.0, precision)) 
		
		std::vector<TVector2D<klab::DoubleReal> > controlPoints03(3);
        controlPoints03[0] = TVector2D<klab::DoubleReal>(-1.0, 1.0);
		controlPoints03[1] = TVector2D<klab::DoubleReal>(0.0, 2.0);
		controlPoints03[2] = TVector2D<klab::DoubleReal>(1.0, 0.5);
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints03,  0.0),  2.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints03, -1.0),  1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints03,  1.0),  0.5, precision)) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCubicInterpolationFilterUnitTest::testFindLeftNearestControlPointIndex()
{
    try
    {
        std::vector<TVector2D<klab::DoubleReal> > controlPoints(8);
        controlPoints[0] = TVector2D<klab::DoubleReal>(-2.0, 5.0);
        controlPoints[1] = TVector2D<klab::DoubleReal>(-1.8, 8.5);
        controlPoints[2] = TVector2D<klab::DoubleReal>(-1.0, 13.2);
        controlPoints[3] = TVector2D<klab::DoubleReal>(-0.3, 12.8);
        controlPoints[4] = TVector2D<klab::DoubleReal>(0.1, 3.4);
        controlPoints[5] = TVector2D<klab::DoubleReal>(0.7, -0.7);
        controlPoints[6] = TVector2D<klab::DoubleReal>(2.0, 0.2);
        controlPoints[7] = TVector2D<klab::DoubleReal>(5.0, 0.8);

        TCubicInterpolationFilter<klab::DoubleReal> filter;   

        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints, -2.0) == 0)
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints, -1.8) == 1)
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints, -1.0) == 2)
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints, -0.3) == 3)
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  0.1) == 4)
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  0.7) == 5)
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  2.0) == 6)
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  5.0) == 7)

        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints, -3.0) == -1) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints, -1.9) == 0) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints, -1.5) == 1) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints, -0.8) == 2) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints, -0.5) == 2) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  0.0) == 3) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  0.2) == 4) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  0.5) == 4) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  1.0) == 5) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  1.5) == 5) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  2.5) == 6) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  3.0) == 6) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  4.0) == 6) 
        TEST_ASSERT(filter.FindLeftNearestControlPointIndex(controlPoints,  6.0) == 7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
