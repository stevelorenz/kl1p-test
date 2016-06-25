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

#include "Interpolator1DUnitTest.h"
#include "../include/Interpolator1D.h"
#include "../include/LinearInterpolationFilter.h"
#include "../include/CubicInterpolationFilter.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KInterpolator1DUnitTest::KInterpolator1DUnitTest() : Test::Suite()
{
    TEST_ADD(KInterpolator1DUnitTest::testDefaultConstructor) 
    TEST_ADD(KInterpolator1DUnitTest::testControlPointsVectorConstructor)
    TEST_ADD(KInterpolator1DUnitTest::testCopyConstructor)
    TEST_ADD(KInterpolator1DUnitTest::testAffectationOperator)

    TEST_ADD(KInterpolator1DUnitTest::testInsert)
    TEST_ADD(KInterpolator1DUnitTest::testClear)
    TEST_ADD(KInterpolator1DUnitTest::testCountControlPoints)
    TEST_ADD(KInterpolator1DUnitTest::testControlPoint)
    TEST_ADD(KInterpolator1DUnitTest::testInterpolate_OnePoint)
    TEST_ADD(KInterpolator1DUnitTest::testInterpolate_ManyPoints)
}

// ---------------------------------------------------------------------------------------------------- //

KInterpolator1DUnitTest::~KInterpolator1DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testDefaultConstructor()
{
    try
    {
        TInterpolator1D<klab::DoubleReal> interpolator1;
        TEST_ASSERT(interpolator1.countControlPoints() == 0)

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2;
        TEST_ASSERT(interpolator2.countControlPoints() == 0)

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3;
        TEST_ASSERT(interpolator3.countControlPoints() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testControlPointsVectorConstructor()
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

        TInterpolator1D<klab::DoubleReal> interpolator1(controlPoints);
        TEST_ASSERT(interpolator1.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2(controlPoints);
        TEST_ASSERT(interpolator2.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3(controlPoints);
        TEST_ASSERT(interpolator3.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testCopyConstructor()
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

        TInterpolator1D<klab::DoubleReal> interpolator1(controlPoints);
        TEST_ASSERT(interpolator1.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2(controlPoints);
        TEST_ASSERT(interpolator2.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3(controlPoints);
        TEST_ASSERT(interpolator3.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))


        TInterpolator1D<klab::DoubleReal> interpolator1b(interpolator1);
        TEST_ASSERT(interpolator1b.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2b(interpolator2);
        TEST_ASSERT(interpolator2b.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3b(interpolator3);
        TEST_ASSERT(interpolator3b.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testAffectationOperator()
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

        TInterpolator1D<klab::DoubleReal> interpolator1(controlPoints);
        TEST_ASSERT(interpolator1.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2(controlPoints);
        TEST_ASSERT(interpolator2.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3(controlPoints);
        TEST_ASSERT(interpolator3.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))


        TInterpolator1D<klab::DoubleReal> interpolator1b;
        interpolator1b = interpolator1;
        TEST_ASSERT(interpolator1b.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1b.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2b;
        interpolator2b = interpolator2;
        TEST_ASSERT(interpolator2b.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2b.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3b;
        interpolator3b = interpolator3;
        TEST_ASSERT(interpolator3b.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3b.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testInsert()
{
    try
    {
        TInterpolator1D<klab::DoubleReal> interpolator1;
        TEST_ASSERT(interpolator1.countControlPoints() == 0)

        interpolator1.insert(TVector2D<klab::DoubleReal>(-1.0, 13.2));
        TEST_ASSERT(interpolator1.countControlPoints() == 1)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-1.0, 13.2)))

        interpolator1.insert(TVector2D<klab::DoubleReal>(-1.8, 8.5));
        TEST_ASSERT(interpolator1.countControlPoints() == 2)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.0, 13.2)))

        interpolator1.insert(TVector2D<klab::DoubleReal>(0.1, 3.4));
        TEST_ASSERT(interpolator1.countControlPoints() == 3)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(0.1, 3.4)))

        interpolator1.insert(TVector2D<klab::DoubleReal>(-0.3, 12.8));
        TEST_ASSERT(interpolator1.countControlPoints() == 4)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(0.1, 3.4)))

        interpolator1.insert(TVector2D<klab::DoubleReal>(-2.0, 5.0));
        TEST_ASSERT(interpolator1.countControlPoints() == 5)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))

        interpolator1.insert(TVector2D<klab::DoubleReal>(5.0, 0.8));
        TEST_ASSERT(interpolator1.countControlPoints() == 6)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        interpolator1.insert(TVector2D<klab::DoubleReal>(2.0, 0.2));
        TEST_ASSERT(interpolator1.countControlPoints() == 7)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        interpolator1.insert(TVector2D<klab::DoubleReal>(0.7, -0.7));
        TEST_ASSERT(interpolator1.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testClear()
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

        TInterpolator1D<klab::DoubleReal> interpolator1(controlPoints);
        TEST_ASSERT(interpolator1.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2(controlPoints);
        TEST_ASSERT(interpolator2.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3(controlPoints);
        TEST_ASSERT(interpolator3.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))


        interpolator1.clear();
        TEST_ASSERT(interpolator1.countControlPoints() == 0)

        interpolator2.clear();
        TEST_ASSERT(interpolator2.countControlPoints() == 0)

        interpolator3.clear();
        TEST_ASSERT(interpolator3.countControlPoints() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testCountControlPoints()
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

        TInterpolator1D<klab::DoubleReal> interpolator1(controlPoints);
        TEST_ASSERT(interpolator1.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2(controlPoints);
        TEST_ASSERT(interpolator2.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3(controlPoints);
        TEST_ASSERT(interpolator3.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testControlPoint()
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

        TInterpolator1D<klab::DoubleReal> interpolator1(controlPoints);
        TEST_ASSERT(interpolator1.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2(controlPoints);
        TEST_ASSERT(interpolator2.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3(controlPoints);
        TEST_ASSERT(interpolator3.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testInterpolate_OnePoint()
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

        TInterpolator1D<klab::DoubleReal> interpolator1(controlPoints);
        TEST_ASSERT(interpolator1.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2(controlPoints);
        TEST_ASSERT(interpolator2.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3(controlPoints);
        TEST_ASSERT(interpolator3.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))


        TEST_ASSERT(klab::Equals(interpolator1.interpolate(-2.0),  5.0, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(-1.8),  8.5, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(-1.0),  13.2, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(-0.3),  12.8, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(0.1),  3.4, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(0.7), -0.7, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(2.0),  0.2, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(5.0),  0.8, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(-3.0),  5.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(-1.9),  6.75, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(-1.5),  10.262499999999999, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(-0.8),  13.085714285714285, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate(-0.5),  12.914285714285715, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate( 0.0),  5.75, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate( 0.2),  2.7166666666666668, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate( 0.5),  0.66666666666666652, precision))
        TEST_ASSERT(klab::Equals(interpolator1.interpolate( 1.0), -0.49230769230769228, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate( 1.5), -0.14615384615384608, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate( 2.5),  0.3, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate( 3.0),  0.4, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate( 4.0),  0.6, precision)) 
        TEST_ASSERT(klab::Equals(interpolator1.interpolate( 6.0),  0.8, precision)) 

        TEST_ASSERT(klab::Equals(interpolator2.interpolate(-2.0),  5.0, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(-1.8),  8.5, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(-1.0),  13.2, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(-0.3),  12.8, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(0.1),  3.4, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(0.7), -0.7, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(2.0),  0.2, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(5.0),  0.8, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(-3.0),  5.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(-1.9),  6.75, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(-1.5),  10.262499999999999, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(-0.8),  13.085714285714285, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate(-0.5),  12.914285714285715, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate( 0.0),  5.75, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate( 0.2),  2.7166666666666668, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate( 0.5),  0.66666666666666652, precision))
        TEST_ASSERT(klab::Equals(interpolator2.interpolate( 1.0), -0.49230769230769228, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate( 1.5), -0.14615384615384608, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate( 2.5),  0.3, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate( 3.0),  0.4, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate( 4.0),  0.6, precision)) 
        TEST_ASSERT(klab::Equals(interpolator2.interpolate( 6.0),  0.8, precision)) 

        TEST_ASSERT(klab::Equals(interpolator3.interpolate(-2.0),  5.0, precision))
        TEST_ASSERT(klab::Equals(interpolator3.interpolate(-1.8),  8.5, precision))
        TEST_ASSERT(klab::Equals(interpolator3.interpolate(-1.0),  13.2, precision))
        TEST_ASSERT(klab::Equals(interpolator3.interpolate(-0.3),  12.8, precision))
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 0.1),  3.4, precision))
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 0.7), -0.7, precision))
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 2.0),  0.2, precision))
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 5.0),  0.8, precision))
        TEST_ASSERT(klab::Equals(interpolator3.interpolate(-3.0),  5.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator3.interpolate(-1.9),  6.45625, precision)) 
        TEST_ASSERT(klab::Equals(interpolator3.interpolate(-1.5),  10.398730468749999, precision))  
        TEST_ASSERT(klab::Equals(interpolator3.interpolate(-0.8),  13.719825072886296, precision))  
        TEST_ASSERT(klab::Equals(interpolator3.interpolate(-0.5),  13.718950437317783, precision)) 
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 0.0),  5.5882812500000032, precision))  
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 0.2),  2.3520833333333329, precision))  
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 0.5),  0.099999999999999645, precision)) 
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 1.0), -0.82753755120619021, precision)) 
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 1.5), -0.35188893946290356, precision))    
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 2.5),  0.32430555555555557, precision)) 
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 3.0),  0.44444444444444448, precision)) 
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 4.0),  0.65555555555555556, precision)) 
        TEST_ASSERT(klab::Equals(interpolator3.interpolate( 6.0),  0.8, precision)) 


        // Limit cases.
        TInterpolator1D<klab::DoubleReal> interpolator0;
        TEST_ASSERT(klab::Equals(interpolator0.interpolate( 0.0), 0.0, precision)); 
        TEST_ASSERT(klab::Equals(interpolator0.interpolate(-1.0), 0.0, precision));
        TEST_ASSERT(klab::Equals(interpolator0.interpolate( 1.0), 0.0, precision));

        std::vector<TVector2D<klab::DoubleReal> > controlPoints01(1);
        controlPoints01[0] = TVector2D<klab::DoubleReal>(0.0, 1.0);
        TInterpolator1D<klab::DoubleReal> interpolator01(controlPoints01);
        TEST_ASSERT(klab::Equals(interpolator01.interpolate( 0.0), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator01.interpolate(-1.0), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator01.interpolate( 1.0), 1.0, precision)) 

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator0b;
        TEST_ASSERT(klab::Equals(interpolator0b.interpolate( 0.0), 0.0, precision)); 
        TEST_ASSERT(klab::Equals(interpolator0b.interpolate(-1.0), 0.0, precision));
        TEST_ASSERT(klab::Equals(interpolator0b.interpolate( 1.0), 0.0, precision));

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator01b(controlPoints01);
        TEST_ASSERT(klab::Equals(interpolator01b.interpolate( 0.0), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator01b.interpolate(-1.0), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator01b.interpolate( 1.0), 1.0, precision))

        std::vector<TVector2D<klab::DoubleReal> > controlPoints02(2);
        controlPoints02[0] = TVector2D<klab::DoubleReal>(-1.0, 1.0);
		controlPoints02[1] = TVector2D<klab::DoubleReal>(1.0, 2.0);
        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator02(controlPoints02);
        TEST_ASSERT(klab::Equals(interpolator02.interpolate( 0.0), 1.5, precision)) 
        TEST_ASSERT(klab::Equals(interpolator02.interpolate(-1.0), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator02.interpolate( 1.0), 2.0, precision)) 
		
		std::vector<TVector2D<klab::DoubleReal> > controlPoints03(3);
        controlPoints03[0] = TVector2D<klab::DoubleReal>(-1.0, 1.0);
		controlPoints03[1] = TVector2D<klab::DoubleReal>(0.0, 2.0);
		controlPoints03[2] = TVector2D<klab::DoubleReal>(1.0, 0.5);
        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator03(controlPoints03);
        TEST_ASSERT(klab::Equals(interpolator03.interpolate( 0.0), 2.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator03.interpolate(-1.0), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(interpolator03.interpolate( 1.0), 0.5, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInterpolator1DUnitTest::testInterpolate_ManyPoints()
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

        std::vector<klab::DoubleReal> in(22);
        std::vector<klab::DoubleReal> out;
        in[0] = -2.0;
        in[1] = -1.8;
        in[2] = -1.0;
        in[3] = -0.3;
        in[4] =  0.1;
        in[5] =  0.7;
        in[6] =  2.0;
        in[7] =  5.0;
        in[8] = -3.0;
        in[9] = -1.9;
        in[10]= -1.5; 
        in[11]= -0.8;
        in[12]= -0.5;
        in[13]=  0.0;
        in[14]=  0.2;
        in[15]=  0.5;
        in[16]=  1.0; 
        in[17]=  1.5;    
        in[18]=  2.5;
        in[19]=  3.0;
        in[20]=  4.0;
        in[21]=  6.0;


        TInterpolator1D<klab::DoubleReal> interpolator1(controlPoints);
        TEST_ASSERT(interpolator1.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator1.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TLinearInterpolationFilter<klab::DoubleReal> > interpolator2(controlPoints);
        TEST_ASSERT(interpolator2.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator2.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))

        TInterpolator1D<klab::DoubleReal, TCubicInterpolationFilter<klab::DoubleReal> > interpolator3(controlPoints);
        TEST_ASSERT(interpolator3.countControlPoints() == 8)
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(0), TVector2D<klab::DoubleReal>(-2.0, 5.0)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(1), TVector2D<klab::DoubleReal>(-1.8, 8.5)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(2), TVector2D<klab::DoubleReal>(-1.0, 13.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(3), TVector2D<klab::DoubleReal>(-0.3, 12.8)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(4), TVector2D<klab::DoubleReal>(0.1, 3.4)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(5), TVector2D<klab::DoubleReal>(0.7, -0.7)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(6), TVector2D<klab::DoubleReal>(2.0, 0.2)))
        TEST_ASSERT(klab::Equals(interpolator3.controlPoint(7), TVector2D<klab::DoubleReal>(5.0, 0.8)))


        interpolator1.interpolate(in, out);
        TEST_ASSERT(out.size() == 22)
        TEST_ASSERT(klab::Equals(out[0],  5.0, precision))
        TEST_ASSERT(klab::Equals(out[1],  8.5, precision))
        TEST_ASSERT(klab::Equals(out[2],  13.2, precision))
        TEST_ASSERT(klab::Equals(out[3],  12.8, precision))
        TEST_ASSERT(klab::Equals(out[4],  3.4, precision))
        TEST_ASSERT(klab::Equals(out[5], -0.7, precision))
        TEST_ASSERT(klab::Equals(out[6],  0.2, precision))
        TEST_ASSERT(klab::Equals(out[7],  0.8, precision))
        TEST_ASSERT(klab::Equals(out[8],  5.0, precision)) 
        TEST_ASSERT(klab::Equals(out[9],  6.75, precision)) 
        TEST_ASSERT(klab::Equals(out[10], 10.262499999999999, precision)) 
        TEST_ASSERT(klab::Equals(out[11], 13.085714285714285, precision)) 
        TEST_ASSERT(klab::Equals(out[12], 12.914285714285715, precision)) 
        TEST_ASSERT(klab::Equals(out[13], 5.75, precision))
        TEST_ASSERT(klab::Equals(out[14], 2.7166666666666668, precision)) 
        TEST_ASSERT(klab::Equals(out[15], 0.66666666666666652, precision))
        TEST_ASSERT(klab::Equals(out[16],-0.49230769230769228, precision)) 
        TEST_ASSERT(klab::Equals(out[17],-0.14615384615384608, precision)) 
        TEST_ASSERT(klab::Equals(out[18], 0.3, precision)) 
        TEST_ASSERT(klab::Equals(out[19], 0.4, precision)) 
        TEST_ASSERT(klab::Equals(out[20], 0.6, precision)) 
        TEST_ASSERT(klab::Equals(out[21], 0.8, precision)) 

        out.clear();
        interpolator2.interpolate(in, out);
        TEST_ASSERT(out.size() == 22)
        TEST_ASSERT(klab::Equals(out[0],  5.0, precision))
        TEST_ASSERT(klab::Equals(out[1],  8.5, precision))
        TEST_ASSERT(klab::Equals(out[2],  13.2, precision))
        TEST_ASSERT(klab::Equals(out[3],  12.8, precision))
        TEST_ASSERT(klab::Equals(out[4],  3.4, precision))
        TEST_ASSERT(klab::Equals(out[5], -0.7, precision))
        TEST_ASSERT(klab::Equals(out[6],  0.2, precision))
        TEST_ASSERT(klab::Equals(out[7],  0.8, precision))
        TEST_ASSERT(klab::Equals(out[8],  5.0, precision)) 
        TEST_ASSERT(klab::Equals(out[9],  6.75, precision)) 
        TEST_ASSERT(klab::Equals(out[10], 10.262499999999999, precision)) 
        TEST_ASSERT(klab::Equals(out[11], 13.085714285714285, precision)) 
        TEST_ASSERT(klab::Equals(out[12], 12.914285714285715, precision)) 
        TEST_ASSERT(klab::Equals(out[13], 5.75, precision))
        TEST_ASSERT(klab::Equals(out[14], 2.7166666666666668, precision)) 
        TEST_ASSERT(klab::Equals(out[15], 0.66666666666666652, precision))
        TEST_ASSERT(klab::Equals(out[16],-0.49230769230769228, precision)) 
        TEST_ASSERT(klab::Equals(out[17],-0.14615384615384608, precision)) 
        TEST_ASSERT(klab::Equals(out[18], 0.3, precision)) 
        TEST_ASSERT(klab::Equals(out[19], 0.4, precision)) 
        TEST_ASSERT(klab::Equals(out[20], 0.6, precision)) 
        TEST_ASSERT(klab::Equals(out[21], 0.8, precision)) 

        out.clear();
        interpolator3.interpolate(in, out);
        TEST_ASSERT(out.size() == 22)
        TEST_ASSERT(klab::Equals(out[0],  5.0, precision))
        TEST_ASSERT(klab::Equals(out[1],  8.5, precision))
        TEST_ASSERT(klab::Equals(out[2],  13.2, precision))
        TEST_ASSERT(klab::Equals(out[3],  12.8, precision))
        TEST_ASSERT(klab::Equals(out[4],  3.4, precision))
        TEST_ASSERT(klab::Equals(out[5], -0.7, precision))
        TEST_ASSERT(klab::Equals(out[6],  0.2, precision))
        TEST_ASSERT(klab::Equals(out[7],  0.8, precision))
        TEST_ASSERT(klab::Equals(out[8],  5.0, precision)) 
        TEST_ASSERT(klab::Equals(out[9],  6.45625, precision)) 
        TEST_ASSERT(klab::Equals(out[10], 10.398730468749999, precision))  
        TEST_ASSERT(klab::Equals(out[11], 13.719825072886296, precision))  
        TEST_ASSERT(klab::Equals(out[12], 13.718950437317783, precision)) 
        TEST_ASSERT(klab::Equals(out[13], 5.5882812500000032, precision))  
        TEST_ASSERT(klab::Equals(out[14], 2.3520833333333329, precision))  
        TEST_ASSERT(klab::Equals(out[15], 0.099999999999999645, precision)) 
        TEST_ASSERT(klab::Equals(out[16],-0.82753755120619021, precision)) 
        TEST_ASSERT(klab::Equals(out[17],-0.35188893946290356, precision))    
        TEST_ASSERT(klab::Equals(out[18], 0.32430555555555557, precision)) 
        TEST_ASSERT(klab::Equals(out[19], 0.44444444444444448, precision)) 
        TEST_ASSERT(klab::Equals(out[20], 0.65555555555555556, precision)) 
        TEST_ASSERT(klab::Equals(out[21], 0.8, precision)) 


        // Limit cases.
        interpolator1.interpolate(std::vector<klab::DoubleReal>(), out);
        TEST_ASSERT(out.size() == 0)

        interpolator2.interpolate(std::vector<klab::DoubleReal>(), out);
        TEST_ASSERT(out.size() == 0)

        interpolator3.interpolate(std::vector<klab::DoubleReal>(), out);
        TEST_ASSERT(out.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
