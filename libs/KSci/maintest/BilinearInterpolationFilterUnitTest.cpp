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

#include "BilinearInterpolationFilterUnitTest.h"
#include "../include/BilinearInterpolationFilter.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KBilinearInterpolationFilterUnitTest::KBilinearInterpolationFilterUnitTest() : Test::Suite()
{
    TEST_ADD(KBilinearInterpolationFilterUnitTest::testDefaultConstructor) 
    TEST_ADD(KBilinearInterpolationFilterUnitTest::testCopyConstructor)
    TEST_ADD(KBilinearInterpolationFilterUnitTest::testAffectationOperator)

    TEST_ADD(KBilinearInterpolationFilterUnitTest::testInterpolate_BetweenValues)
    TEST_ADD(KBilinearInterpolationFilterUnitTest::testInterpolate_MuBetweenValues)
}

// ---------------------------------------------------------------------------------------------------- //

KBilinearInterpolationFilterUnitTest::~KBilinearInterpolationFilterUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KBilinearInterpolationFilterUnitTest::testDefaultConstructor()
{
    try
    {
        TBilinearInterpolationFilter<klab::DoubleReal> filter;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBilinearInterpolationFilterUnitTest::testCopyConstructor()
{
    try
    {
        TBilinearInterpolationFilter<klab::DoubleReal> filter1;
        TEST_ASSERT(true)

        TBilinearInterpolationFilter<klab::DoubleReal> filter2(filter1);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBilinearInterpolationFilterUnitTest::testAffectationOperator()
{
    try
    {
        TBilinearInterpolationFilter<klab::DoubleReal> filter1;
        TEST_ASSERT(true)

        TBilinearInterpolationFilter<klab::DoubleReal> filter2;
        filter2 = filter1;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBilinearInterpolationFilterUnitTest::testInterpolate_BetweenValues()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TBilinearInterpolationFilter<klab::DoubleReal> filter;

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0), 1.5, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 1.0, 0.0), 0.5, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, -1.0, 0.0), -0.25, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(123.456, 234.567, 321.098, 432.109), 277.8075, precision))   


        // Limit cases.
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 1.0, 1.0, 1.0), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 0.0, 1.0), 0.5, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBilinearInterpolationFilterUnitTest::testInterpolate_MuBetweenValues()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TBilinearInterpolationFilter<klab::DoubleReal> filter;

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 0.5, 0.5), 1.5, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 1.0, 0.0, 0.5, 0.5), 0.5, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, -1.0, 0.0, 0.5, 0.5), -0.25, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(123.456, 234.567, 321.098, 432.109, 0.5, 0.5), 277.8075, precision)) 

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 0.1, 0.8), 1.7, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 1.0, 0.0, 0.1, 0.8), 0.74, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, -1.0, 0.0, 0.1, 0.8), -0.88, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(123.456, 234.567, 321.098, 432.109, 0.1, 0.8), 292.6727, precision)) 

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 0.8, 0.1), 1.0, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 1.0, 0.0, 0.8, 0.1), 0.74, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(-1.0, 1.0, -1.0, 0.0, 0.8, 0.1), 0.52, precision))   
        TEST_ASSERT(klab::Equals(filter.interpolate(123.456, 234.567, 321.098, 432.109, 0.8, 0.1), 232.1010, precision)) 

        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0, 0.0, 0.0), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0, 0.0, 1.0), 3.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0, 1.0, 0.0), 2.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0, 1.0, 1.0), 4.0, precision)) 

        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0, -0.5,  0.5), 2.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0,  0.5, -0.5), 1.5, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0, -0.5, -0.5), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0, -0.5,  1.5), 3.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0,  1.5,  0.5), 3.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0,  0.5,  1.5), 3.5, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 2.0, 3.0, 4.0,  1.5,  1.5), 4.0, precision)) 


        // Limit cases.
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.5, 0.5), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 1.0, 1.0, 1.0, 0.5, 0.5), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 0.0, 1.0, 0.5, 0.5), 0.5, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.1, 0.8), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 1.0, 1.0, 1.0, 0.1, 0.8), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 0.0, 1.0, 0.1, 0.8), 0.1, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.8, 0.1), 0.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 1.0, 1.0, 1.0, 0.8, 0.1), 1.0, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 0.0, 1.0, 0.8, 0.1), 0.8, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
