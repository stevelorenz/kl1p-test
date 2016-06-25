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

#include "ThresholdedCountFilter1DUnitTest.h"
#include "../include/ThresholdedCountFilter1D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KThresholdedCountFilter1DUnitTest::KThresholdedCountFilter1DUnitTest() : Test::Suite()
{
    TEST_ADD(KThresholdedCountFilter1DUnitTest::testCountConstructor)  
    TEST_ADD(KThresholdedCountFilter1DUnitTest::testCountValueConstructor)  
    TEST_ADD(KThresholdedCountFilter1DUnitTest::testCopyConstructor)
    TEST_ADD(KThresholdedCountFilter1DUnitTest::testAffectationOperator)

    TEST_ADD(KThresholdedCountFilter1DUnitTest::testCount)
    TEST_ADD(KThresholdedCountFilter1DUnitTest::testValue)
    TEST_ADD(KThresholdedCountFilter1DUnitTest::testApply_InOut)
    TEST_ADD(KThresholdedCountFilter1DUnitTest::testApply_In_Out)
}

// ---------------------------------------------------------------------------------------------------- //

KThresholdedCountFilter1DUnitTest::~KThresholdedCountFilter1DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter1DUnitTest::testCountConstructor()
{
    try
    {
        TThresholdedCountFilter1D<klab::Real> filter(123);
        TEST_ASSERT(filter.count() == 123)
        TEST_ASSERT(klab::Equals(filter.value(), 0.0f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter1DUnitTest::testCountValueConstructor()
{
    try
    {
        TThresholdedCountFilter1D<klab::Real> filter(123, 1.23f);
        TEST_ASSERT(filter.count() == 123)
        TEST_ASSERT(klab::Equals(filter.value(), 1.23f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter1DUnitTest::testCopyConstructor()
{
    try
    {
        TThresholdedCountFilter1D<klab::Real> filter(123, 1.23f);
        TEST_ASSERT(filter.count() == 123)
        TEST_ASSERT(klab::Equals(filter.value(), 1.23f))

        TThresholdedCountFilter1D<klab::Real> filter2(filter);
        TEST_ASSERT(filter2.count() == 123) 
        TEST_ASSERT(klab::Equals(filter2.value(), 1.23f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter1DUnitTest::testAffectationOperator()
{
    try
    {
        TThresholdedCountFilter1D<klab::Real> filter(123, 1.23f);
        TEST_ASSERT(filter.count() == 123)
        TEST_ASSERT(klab::Equals(filter.value(), 1.23f))

        TThresholdedCountFilter1D<klab::Real> filter2(456, 4.56f);
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

void KThresholdedCountFilter1DUnitTest::testCount()
{
    try
    {
        TThresholdedCountFilter1D<klab::Real> filter(123);
        TEST_ASSERT(filter.count() == 123)   
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter1DUnitTest::testValue()
{
    try
    {
        TThresholdedCountFilter1D<klab::Real> filter(123, 1.23f);
        TEST_ASSERT(klab::Equals(filter.value(), 1.23f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter1DUnitTest::testApply_InOut()
{
    try
    {
        arma::Col<klab::DoubleReal> f(32);
        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));   

        klab::DoubleReal precision = 1e-10;


        arma::Col<klab::DoubleReal> fs(f);
        TThresholdedCountFilter1D<klab::DoubleReal> filter(10);
        filter.apply(fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], f[4], precision))  
        TEST_ASSERT(klab::Equals(fs[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[7], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], f[10], precision))  
        TEST_ASSERT(klab::Equals(fs[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[15], f[15], precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[18], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[19], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[20], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[25], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[26], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[27], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], f[29], precision))  
        TEST_ASSERT(klab::Equals(fs[30], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[31], 0.0, precision))


        fs = f;
        TThresholdedCountFilter1D<klab::DoubleReal, TThresholdedCountFilter1DReverseComparator<klab::DoubleReal> > filter2(10);
        filter2.apply(fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], f[0], precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[3], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[4], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fs[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fs[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[9], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[10], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fs[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fs[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[15], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[16], 0.0, precision))   
        TEST_ASSERT(klab::Equals(fs[17], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fs[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fs[20], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[21], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[22], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fs[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fs[27], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[28], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[29], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[30], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[31], f[31], precision))


        fs = f;
        TThresholdedCountFilter1D<klab::DoubleReal, TAbsoluteThresholdedCountFilter1DComparator<klab::DoubleReal> > filter3(10);
        filter3.apply(fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fs[3], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[4], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fs[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[7], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fs[9], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[10], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fs[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fs[15], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[16], 0.0, precision))   
        TEST_ASSERT(klab::Equals(fs[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fs[18], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[19], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fs[21], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[22], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fs[25], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[26], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fs[28], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[29], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fs[31], 0.0, precision))


        fs = f;
        TThresholdedCountFilter1D<klab::DoubleReal, TAbsoluteThresholdedCountFilter1DReverseComparator<klab::DoubleReal> > filter4(10);
        filter4.apply(fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], f[0], precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fs[7], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[15], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[18], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fs[20], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[21], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fs[26], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[27], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[30], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[31], f[31], precision))


        fs = f;
        TThresholdedCountFilter1D<klab::DoubleReal> filter5(10, 56.234);
        filter5.apply(fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], 56.234, precision))  
        TEST_ASSERT(klab::Equals(fs[1], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[2], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], f[4], precision))  
        TEST_ASSERT(klab::Equals(fs[5], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[6], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[7], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[8], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], f[10], precision))  
        TEST_ASSERT(klab::Equals(fs[11], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[12], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[13], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[14], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[15], f[15], precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[18], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[19], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[20], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[24], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[25], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[26], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[27], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], f[29], precision))  
        TEST_ASSERT(klab::Equals(fs[30], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[31], 56.234, precision))


        // Limit cases.
        fs = f;
        TThresholdedCountFilter1D<klab::DoubleReal> filter10(0);
        filter10.apply(fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[3], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[4], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[7], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[9], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[10], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[15], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[16], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[17], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[18], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[19], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[20], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[21], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[22], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[25], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[26], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[27], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[28], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[29], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[30], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[31], 0.0, precision))


        fs = f;
        TThresholdedCountFilter1D<klab::DoubleReal> filter11(32);
        filter11.apply(fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], f[0], precision))  
        TEST_ASSERT(klab::Equals(fs[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fs[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], f[4], precision))  
        TEST_ASSERT(klab::Equals(fs[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fs[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fs[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fs[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], f[10], precision))  
        TEST_ASSERT(klab::Equals(fs[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fs[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fs[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fs[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fs[15], f[15], precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fs[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fs[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fs[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fs[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fs[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fs[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fs[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fs[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], f[29], precision))  
        TEST_ASSERT(klab::Equals(fs[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fs[31], f[31], precision))


        fs = f;
        TThresholdedCountFilter1D<klab::DoubleReal> filter12(33);
        filter12.apply(fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], f[0], precision))  
        TEST_ASSERT(klab::Equals(fs[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fs[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], f[4], precision))  
        TEST_ASSERT(klab::Equals(fs[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fs[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fs[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fs[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], f[10], precision))  
        TEST_ASSERT(klab::Equals(fs[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fs[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fs[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fs[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fs[15], f[15], precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fs[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fs[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fs[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fs[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fs[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fs[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fs[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fs[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], f[29], precision))  
        TEST_ASSERT(klab::Equals(fs[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fs[31], f[31], precision))


        fs.set_size(0);
        TThresholdedCountFilter1D<klab::DoubleReal> filter13(1);
        filter13.apply(fs);
        TEST_ASSERT(fs.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThresholdedCountFilter1DUnitTest::testApply_In_Out()
{
    try
    {
        arma::Col<klab::DoubleReal> f(32);
        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));   

        klab::DoubleReal precision = 1e-10;


        arma::Col<klab::DoubleReal> fs;
        TThresholdedCountFilter1D<klab::DoubleReal> filter(10);
        filter.apply(f, fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], f[4], precision))  
        TEST_ASSERT(klab::Equals(fs[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[7], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], f[10], precision))  
        TEST_ASSERT(klab::Equals(fs[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[15], f[15], precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[18], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[19], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[20], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[25], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[26], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[27], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], f[29], precision))  
        TEST_ASSERT(klab::Equals(fs[30], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[31], 0.0, precision))


        TThresholdedCountFilter1D<klab::DoubleReal, TThresholdedCountFilter1DReverseComparator<klab::DoubleReal> > filter2(10);
        filter2.apply(f, fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], f[0], precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[3], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[4], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fs[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fs[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[9], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[10], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fs[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fs[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[15], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[16], 0.0, precision))   
        TEST_ASSERT(klab::Equals(fs[17], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fs[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fs[20], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[21], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[22], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fs[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fs[27], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[28], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[29], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[30], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[31], f[31], precision))


        TThresholdedCountFilter1D<klab::DoubleReal, TAbsoluteThresholdedCountFilter1DComparator<klab::DoubleReal> > filter3(10);
        filter3.apply(f, fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fs[3], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[4], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fs[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[7], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fs[9], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[10], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fs[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fs[15], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[16], 0.0, precision))   
        TEST_ASSERT(klab::Equals(fs[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fs[18], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[19], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fs[21], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[22], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fs[25], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[26], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fs[28], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[29], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fs[31], 0.0, precision))


        TThresholdedCountFilter1D<klab::DoubleReal, TAbsoluteThresholdedCountFilter1DReverseComparator<klab::DoubleReal> > filter4(10);
        filter4.apply(f, fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], f[0], precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fs[7], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[15], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[18], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fs[20], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[21], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fs[26], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[27], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[30], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[31], f[31], precision))


        TThresholdedCountFilter1D<klab::DoubleReal> filter5(10, 56.234);
        filter5.apply(f, fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], 56.234, precision))  
        TEST_ASSERT(klab::Equals(fs[1], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[2], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], f[4], precision))  
        TEST_ASSERT(klab::Equals(fs[5], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[6], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[7], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[8], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], f[10], precision))  
        TEST_ASSERT(klab::Equals(fs[11], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[12], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[13], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[14], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[15], f[15], precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[18], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[19], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[20], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[24], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[25], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[26], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[27], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], f[29], precision))  
        TEST_ASSERT(klab::Equals(fs[30], 56.234, precision))
        TEST_ASSERT(klab::Equals(fs[31], 56.234, precision))


        // Limit cases.
        TThresholdedCountFilter1D<klab::DoubleReal> filter10(0);
        filter10.apply(f, fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], 0.0, precision))  
        TEST_ASSERT(klab::Equals(fs[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[3], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[4], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[7], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[9], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[10], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[11], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[12], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[13], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[14], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[15], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[16], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[17], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[18], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[19], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[20], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[21], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[22], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[23], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[24], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[25], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[26], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[27], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[28], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[29], 0.0, precision)) 
        TEST_ASSERT(klab::Equals(fs[30], 0.0, precision))
        TEST_ASSERT(klab::Equals(fs[31], 0.0, precision))


        TThresholdedCountFilter1D<klab::DoubleReal> filter11(32);
        filter11.apply(f, fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], f[0], precision))  
        TEST_ASSERT(klab::Equals(fs[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fs[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], f[4], precision))  
        TEST_ASSERT(klab::Equals(fs[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fs[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fs[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fs[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], f[10], precision))  
        TEST_ASSERT(klab::Equals(fs[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fs[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fs[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fs[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fs[15], f[15], precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fs[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fs[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fs[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fs[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fs[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fs[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fs[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fs[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], f[29], precision))  
        TEST_ASSERT(klab::Equals(fs[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fs[31], f[31], precision))


        fs.fill(0.0);
        TThresholdedCountFilter1D<klab::DoubleReal> filter12(33);
        filter12.apply(f, fs);

        TEST_ASSERT(fs.n_rows == 32)
        TEST_ASSERT(klab::Equals(fs[0], f[0], precision))  
        TEST_ASSERT(klab::Equals(fs[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fs[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fs[3], f[3], precision))  
        TEST_ASSERT(klab::Equals(fs[4], f[4], precision))  
        TEST_ASSERT(klab::Equals(fs[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fs[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fs[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fs[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fs[9], f[9], precision)) 
        TEST_ASSERT(klab::Equals(fs[10], f[10], precision))  
        TEST_ASSERT(klab::Equals(fs[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fs[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fs[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fs[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fs[15], f[15], precision))  
        TEST_ASSERT(klab::Equals(fs[16], f[16], precision))   
        TEST_ASSERT(klab::Equals(fs[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fs[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fs[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fs[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fs[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fs[22], f[22], precision)) 
        TEST_ASSERT(klab::Equals(fs[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fs[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fs[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fs[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fs[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fs[28], f[28], precision)) 
        TEST_ASSERT(klab::Equals(fs[29], f[29], precision))  
        TEST_ASSERT(klab::Equals(fs[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fs[31], f[31], precision))


        TThresholdedCountFilter1D<klab::DoubleReal> filter13(1);
        filter13.apply(arma::Col<klab::DoubleReal>(), fs);
        TEST_ASSERT(fs.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
