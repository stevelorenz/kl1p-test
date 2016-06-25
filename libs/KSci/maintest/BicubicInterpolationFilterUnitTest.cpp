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

#include "BicubicInterpolationFilterUnitTest.h"
#include "../include/BicubicInterpolationFilter.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KBicubicInterpolationFilterUnitTest::KBicubicInterpolationFilterUnitTest() : Test::Suite()
{
    TEST_ADD(KBicubicInterpolationFilterUnitTest::testDefaultConstructor) 
    TEST_ADD(KBicubicInterpolationFilterUnitTest::testCopyConstructor)
    TEST_ADD(KBicubicInterpolationFilterUnitTest::testAffectationOperator)

    TEST_ADD(KBicubicInterpolationFilterUnitTest::testInterpolate_BetweenValues)
    TEST_ADD(KBicubicInterpolationFilterUnitTest::testInterpolate_MuBetweenValues)
}

// ---------------------------------------------------------------------------------------------------- //

KBicubicInterpolationFilterUnitTest::~KBicubicInterpolationFilterUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KBicubicInterpolationFilterUnitTest::testDefaultConstructor()
{
    try
    {
        TBicubicInterpolationFilter<klab::DoubleReal> filter;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBicubicInterpolationFilterUnitTest::testCopyConstructor()
{
    try
    {
        TBicubicInterpolationFilter<klab::DoubleReal> filter1;
        TEST_ASSERT(true)

        TBicubicInterpolationFilter<klab::DoubleReal> filter2(filter1);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBicubicInterpolationFilterUnitTest::testAffectationOperator()
{
    try
    {
        TBicubicInterpolationFilter<klab::DoubleReal> filter1;
        TEST_ASSERT(true)

        TBicubicInterpolationFilter<klab::DoubleReal> filter2;
        filter2 = filter1;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBicubicInterpolationFilterUnitTest::testInterpolate_BetweenValues()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TBicubicInterpolationFilter<klab::DoubleReal> filter;

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0), 7.5, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0), -0.0703125, precision))   


        // Limit cases.
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), 0.0, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0), 1.125, precision)) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBicubicInterpolationFilterUnitTest::testInterpolate_MuBetweenValues()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TBicubicInterpolationFilter<klab::DoubleReal> filter;

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 0.5, 0.5), 7.5, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 0.1, 0.8), 8.3, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 0.8, 0.1), 6.2, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 0.5, 0.5), -0.0703125, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 0.1, 0.8), -1.3885759999999999, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 0.8, 0.1), 1.883924, precision)) 

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 0.0, 0.0), 5.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 0.0, 1.0), 9.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 1.0, 0.0), 6.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 1.0, 1.0), 10.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 0.0, 0.0), 3.0, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 0.0, 1.0), -2.0, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 1.0, 0.0), 2.0, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 1.0, 1.0), -3.0, precision))  

        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, -0.5, 0.5), 6.4375, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 0.5, -0.5), 3.25, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, -0.5, -0.5), 2.1875, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, -0.5, 1.5), 10.6875, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 1.5, 0.5), 8.5625, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 0.5, 1.5), 11.75, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 1.5, 1.5), 12.8125, precision))         
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, -0.5, 0.5), 1.265625, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 0.5, -0.5), 2.3125, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, -0.5, -0.5), 2.3125, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, -0.5, 1.5), -1.8125, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 1.5, 0.5), -1.328125, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 0.5, 1.5), -1.75, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -2.0, -1.0, 0.0, -1.0, 1.5, 1.5), -2.3125, precision)) 


        // Limit cases.
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.5), 0.0, precision))  
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.8), 0.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.8, 0.1), 0.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.5), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.1, 0.8), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 0.1), 1.0, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.5, 0.5), 1.125, precision)) 
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.1, 0.8), 0.591, precision))
        TEST_ASSERT(klab::Equals(filter.interpolate(0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.0, 0.5, 1.5, 0.0, 0.8, 0.1), 1.452, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
