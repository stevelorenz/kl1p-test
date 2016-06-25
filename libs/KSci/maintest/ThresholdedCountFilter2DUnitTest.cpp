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

#include "ThresholdedCountFilter2DUnitTest.h"
#include "../include/ThresholdedCountFilter2D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KThresholdedCountFilter2DUnitTest::KThresholdedCountFilter2DUnitTest() : Test::Suite()
{
    TEST_ADD(KThresholdedCountFilter2DUnitTest::testCountConstructor)  
    TEST_ADD(KThresholdedCountFilter2DUnitTest::testCountValueConstructor)  
    TEST_ADD(KThresholdedCountFilter2DUnitTest::testCopyConstructor)
    TEST_ADD(KThresholdedCountFilter2DUnitTest::testAffectationOperator)

    TEST_ADD(KThresholdedCountFilter2DUnitTest::testCount)
    TEST_ADD(KThresholdedCountFilter2DUnitTest::testValue)
    TEST_ADD(KThresholdedCountFilter2DUnitTest::testApply_InOut)
    TEST_ADD(KThresholdedCountFilter2DUnitTest::testApply_In_Out)
}

// ---------------------------------------------------------------------------------------------------- //

KThresholdedCountFilter2DUnitTest::~KThresholdedCountFilter2DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter2DUnitTest::testCountConstructor()
{
    try
    {
        TThresholdedCountFilter2D<klab::Real> filter(123);
        TEST_ASSERT(filter.count() == 123)
        TEST_ASSERT(klab::Equals(filter.value(), 0.0f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter2DUnitTest::testCountValueConstructor()
{
    try
    {
        TThresholdedCountFilter2D<klab::Real> filter(123, 1.23f);
        TEST_ASSERT(filter.count() == 123)
        TEST_ASSERT(klab::Equals(filter.value(), 1.23f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter2DUnitTest::testCopyConstructor()
{
    try
    {
        TThresholdedCountFilter2D<klab::Real> filter(123, 1.23f);
        TEST_ASSERT(filter.count() == 123)
        TEST_ASSERT(klab::Equals(filter.value(), 1.23f))

        TThresholdedCountFilter2D<klab::Real> filter2(filter);
        TEST_ASSERT(filter2.count() == 123)   
        TEST_ASSERT(klab::Equals(filter2.value(), 1.23f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter2DUnitTest::testAffectationOperator()
{
    try
    {
        TThresholdedCountFilter2D<klab::Real> filter(123, 1.23f);
        TEST_ASSERT(filter.count() == 123)
        TEST_ASSERT(klab::Equals(filter.value(), 1.23f))

        TThresholdedCountFilter2D<klab::Real> filter2(456, 4.56f);
        TEST_ASSERT(filter2.count() == 456)  
        TEST_ASSERT(klab::Equals(filter2.value(), 4.56f))

        filter2 = filter;
        TEST_ASSERT(filter2.count() == 123) 
        TEST_ASSERT(klab::Equals(filter2.value(), 1.23f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter2DUnitTest::testCount()
{
    try
    {
        TThresholdedCountFilter2D<klab::Real> filter(123);
        TEST_ASSERT(filter.count() == 123)   
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter2DUnitTest::testValue()
{
    try
    {
        TThresholdedCountFilter2D<klab::Real> filter(123, 1.23f);
        TEST_ASSERT(klab::Equals(filter.value(), 1.23f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter2DUnitTest::testApply_InOut()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(8, 8);

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = -129.0;
        f(0, 3) = 139.0;
        f(0, 4) = -127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = -108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = -124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = -141.0;
        f(2, 4) = -171.0;
        f(2, 5) = -184.0;
        f(2, 6) = 110.0;
        f(2, 7) = -141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = -85.0;
        f(3, 4) = -161.0;
        f(3, 5) = -122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = -107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = -153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = -98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = -87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = -81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = -151.0;
        f(6, 5) = 138.0;
        f(6, 6) = -144.0;
        f(6, 7) = 135.0;
        f(7, 0) = -126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = -175.0;
        f(7, 6) = 125.0;
        f(7, 7) = -93.0;

        klab::DoubleReal precision = 1e-10;


        arma::Mat<klab::DoubleReal> fs(f);
        TThresholdedCountFilter2D<klab::DoubleReal> filter(10);
        filter.apply(fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        fs = f;
        TThresholdedCountFilter2D<klab::DoubleReal, TThresholdedCountFilter2DReverseComparator<klab::DoubleReal> > filter2(10);
        filter2.apply(fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        fs = f;
        TThresholdedCountFilter2D<klab::DoubleReal, TAbsoluteThresholdedCountFilter2DComparator<klab::DoubleReal> > filter3(10);
        filter3.apply(fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        fs = f;
        TThresholdedCountFilter2D<klab::DoubleReal, TAbsoluteThresholdedCountFilter2DReverseComparator<klab::DoubleReal> > filter4(10);
        filter4.apply(fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        fs = f;
        TThresholdedCountFilter2D<klab::DoubleReal> filter5(10, 56.234);
        filter5.apply(fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 56.234, precision))


        // Limit cases.
        fs = f;
        TThresholdedCountFilter2D<klab::DoubleReal> filter10(0);
        filter10.apply(fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        fs = f;
        TThresholdedCountFilter2D<klab::DoubleReal> filter11(64);
        filter11.apply(fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), f(7, 7), precision))


        fs = f;
        TThresholdedCountFilter2D<klab::DoubleReal> filter12(65);
        filter12.apply(fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), f(7, 7), precision))


        fs.set_size(0, 0);
        TThresholdedCountFilter2D<klab::DoubleReal> filter13(1);
        filter13.apply(fs);
        TEST_ASSERT(fs.n_rows==0 && fs.n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter2DUnitTest::testApply_In_Out()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(8, 8);

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = -129.0;
        f(0, 3) = 139.0;
        f(0, 4) = -127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = -108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = -124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = -141.0;
        f(2, 4) = -171.0;
        f(2, 5) = -184.0;
        f(2, 6) = 110.0;
        f(2, 7) = -141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = -85.0;
        f(3, 4) = -161.0;
        f(3, 5) = -122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = -107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = -153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = -98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = -87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = -81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = -151.0;
        f(6, 5) = 138.0;
        f(6, 6) = -144.0;
        f(6, 7) = 135.0;
        f(7, 0) = -126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = -175.0;
        f(7, 6) = 125.0;
        f(7, 7) = -93.0;

        klab::DoubleReal precision = 1e-10;

        arma::Mat<klab::DoubleReal> fs;
        TThresholdedCountFilter2D<klab::DoubleReal> filter(10);
        filter.apply(f, fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        TThresholdedCountFilter2D<klab::DoubleReal, TThresholdedCountFilter2DReverseComparator<klab::DoubleReal> > filter2(10);
        filter2.apply(f, fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        TThresholdedCountFilter2D<klab::DoubleReal, TAbsoluteThresholdedCountFilter2DComparator<klab::DoubleReal> > filter3(10);
        filter3.apply(f, fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        TThresholdedCountFilter2D<klab::DoubleReal, TAbsoluteThresholdedCountFilter2DReverseComparator<klab::DoubleReal> > filter4(10);
        filter4.apply(f, fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        TThresholdedCountFilter2D<klab::DoubleReal> filter5(10, 56.234);
        filter5.apply(f, fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 56.234, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 56.234, precision))


        // Limit cases.
        TThresholdedCountFilter2D<klab::DoubleReal> filter10(0);
        filter10.apply(f, fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), 0.0, precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), 0.0, precision))


        TThresholdedCountFilter2D<klab::DoubleReal> filter11(64);
        filter11.apply(f, fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), f(7, 7), precision))


        fs.fill(0.0);
        TThresholdedCountFilter2D<klab::DoubleReal> filter12(65);
        filter12.apply(f, fs);

        TEST_ASSERT(fs.n_rows==8 && fs.n_cols==8)
        TEST_ASSERT(klab::Equals(fs(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fs(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fs(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fs(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fs(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fs(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fs(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fs(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fs(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fs(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fs(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fs(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fs(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fs(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fs(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fs(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fs(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fs(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fs(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fs(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fs(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fs(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fs(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fs(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fs(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fs(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fs(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fs(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fs(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fs(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fs(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fs(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fs(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fs(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fs(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fs(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fs(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fs(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fs(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fs(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fs(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fs(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fs(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fs(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fs(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fs(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fs(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fs(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fs(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fs(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fs(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fs(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fs(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fs(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fs(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fs(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fs(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fs(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fs(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fs(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fs(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fs(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fs(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fs(7, 7), f(7, 7), precision))


        TThresholdedCountFilter2D<klab::DoubleReal> filter13(1);
        filter13.apply(arma::Mat<klab::DoubleReal>(), fs);
        TEST_ASSERT(fs.n_rows==0 && fs.n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
