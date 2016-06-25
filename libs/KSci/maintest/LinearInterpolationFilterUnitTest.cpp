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

#include "LinearInterpolationFilterUnitTest.h"
#include "../include/LinearInterpolationFilter.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KLinearInterpolationFilterUnitTest::KLinearInterpolationFilterUnitTest() : Test::Suite()
{
    TEST_ADD(KLinearInterpolationFilterUnitTest::testDefaultConstructor) 
    TEST_ADD(KLinearInterpolationFilterUnitTest::testCopyConstructor)
    TEST_ADD(KLinearInterpolationFilterUnitTest::testAffectationOperator)

    TEST_ADD(KLinearInterpolationFilterUnitTest::testInterpolate_BetweenValues)
    TEST_ADD(KLinearInterpolationFilterUnitTest::testInterpolate_MuBetweenValues)
    TEST_ADD(KLinearInterpolationFilterUnitTest::testInterpolate_BetweenPoints)
    TEST_ADD(KLinearInterpolationFilterUnitTest::testInterpolate_PointsArray)
    TEST_ADD(KLinearInterpolationFilterUnitTest::testFindLeftNearestControlPointIndex)
}

// ---------------------------------------------------------------------------------------------------- //

KLinearInterpolationFilterUnitTest::~KLinearInterpolationFilterUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KLinearInterpolationFilterUnitTest::testDefaultConstructor()
{
    try
    {
        TLinearInterpolationFilter<klab::DoubleReal> filter;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLinearInterpolationFilterUnitTest::testCopyConstructor()
{
    try
    {
        TLinearInterpolationFilter<klab::DoubleReal> filter1;
        TEST_ASSERT(true)

        TLinearInterpolationFilter<klab::DoubleReal> filter2(filter1);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLinearInterpolationFilterUnitTest::testAffectationOperator()
{
    try
    {
        TLinearInterpolationFilter<klab::DoubleReal> filter1;
        TEST_ASSERT(true)

        TLinearInterpolationFilter<klab::DoubleReal> filter2;
        filter2 = filter1;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLinearInterpolationFilterUnitTest::testInterpolate_BetweenValues()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TLinearInterpolationFilter<klab::DoubleReal> filter;

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0), 0.5, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(123.456, 567.789), 345.6225, precision))


        // Limit cases.
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(10.0, 10.0), 10.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLinearInterpolationFilterUnitTest::testInterpolate_MuBetweenValues()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TLinearInterpolationFilter<klab::DoubleReal> filter;

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 0.5), 0.5, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, 0.5), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(123.456, 567.789, 0.5), 345.6225, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 0.1), 0.1, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, 0.1), -0.8, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 0.8), 0.8, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, 0.8), 0.6, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 0.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, 0.0), -1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 1.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, 1.0), 1.0, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 1.5), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, 1.5), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, -0.5), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, -0.5), -1.0, precision))


        // Limit cases.
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.5), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(10.0, 10.0, 0.5), 10.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.1), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(10.0, 10.0, 0.1), 10.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.8), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(10.0, 10.0, 0.8), 10.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLinearInterpolationFilterUnitTest::testInterpolate_BetweenPoints()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TLinearInterpolationFilter<klab::DoubleReal> filter;

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 5.0), 0.5, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-5.0, -1.0), TVector2D<klab::DoubleReal>(1.0, 1.0), -2.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(-1.0, 123.456), TVector2D<klab::DoubleReal>(1.0, 567.789), 0.0), 345.6225, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 1.0), 0.1, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, -1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 1.0), -0.8, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 8.0), 0.8, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, -1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 8.0), 0.6, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 0.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, -1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 0.0), -1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 10.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, -1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 10.0), 1.0, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 15.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, -1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 15.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 1.0), -5.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, -1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), -5.0), -1.0, precision))


        // Limit cases.
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 0.0), 5.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 5.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 0.0), 1.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 1.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 0.0), TVector2D<klab::DoubleReal>(10.0, 0.0), 8.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 1.0), TVector2D<klab::DoubleReal>(10.0, 1.0), 8.0), 1.0, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(0.0, 1.0), TVector2D<klab::DoubleReal>(0.0, 1.0), 0.5),   1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(1.0, 1.0), 0.5), -1.0, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(10.0, 0.0), TVector2D<klab::DoubleReal>(0.0, 1.0), 5.0), 0.5, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(1.0, -1.0), TVector2D<klab::DoubleReal>(-5.0, 1.0), -2.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(TVector2D<klab::DoubleReal>(1.0, 123.456), TVector2D<klab::DoubleReal>(-1.0, 567.789), 0.0), 345.6225, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLinearInterpolationFilterUnitTest::testInterpolate_PointsArray()
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

        TLinearInterpolationFilter<klab::DoubleReal> filter;        

        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -2.0),  5.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -1.8),  8.5, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -1.0),  13.2, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -0.3),  12.8, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.1),  3.4, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.7), -0.7, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  2.0),  0.2, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  5.0),  0.8, precision))

        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -3.0),  5.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -1.9),  6.75, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -1.5),  10.262499999999999, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -0.8),  13.085714285714285, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints, -0.5),  12.914285714285715, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.0),  5.75, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.2),  2.7166666666666668, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  0.5),  0.66666666666666652, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  1.0), -0.49230769230769228, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  1.5), -0.14615384615384608, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  2.5),  0.3, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  3.0),  0.4, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(controlPoints,  4.0),  0.6, precision)) 
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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLinearInterpolationFilterUnitTest::testFindLeftNearestControlPointIndex()
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

        TLinearInterpolationFilter<klab::DoubleReal> filter;   

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
