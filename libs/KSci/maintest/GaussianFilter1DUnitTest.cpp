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

#include "GaussianFilter1DUnitTest.h"
#include "../include/GaussianFilter1D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KGaussianFilter1DUnitTest::KGaussianFilter1DUnitTest() : Test::Suite()
{
    TEST_ADD(KGaussianFilter1DUnitTest::testSizeConstructor)  
    TEST_ADD(KGaussianFilter1DUnitTest::testSizeSigmaConstructor)  
    TEST_ADD(KGaussianFilter1DUnitTest::testSizeSigmaCConstructor)  
    TEST_ADD(KGaussianFilter1DUnitTest::testCopyConstructor)
    TEST_ADD(KGaussianFilter1DUnitTest::testAffectationOperator)

    TEST_ADD(KGaussianFilter1DUnitTest::testSize)
    TEST_ADD(KGaussianFilter1DUnitTest::testSigma)
    TEST_ADD(KGaussianFilter1DUnitTest::testC)
    TEST_ADD(KGaussianFilter1DUnitTest::testApply_InOut)
    TEST_ADD(KGaussianFilter1DUnitTest::testApply_In_Out)
}

// ---------------------------------------------------------------------------------------------------- //

KGaussianFilter1DUnitTest::~KGaussianFilter1DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testSizeConstructor()
{
    try
    {
        TGaussianFilter1D<klab::DoubleReal> filter(32);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.sigma(), 1.0))
        TEST_ASSERT(filter.c() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testSizeSigmaConstructor()
{
    try
    {
        TGaussianFilter1D<klab::DoubleReal> filter(32, 4.0);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.c() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testSizeSigmaCConstructor()
{
    try
    {
        TGaussianFilter1D<klab::DoubleReal> filter(32, 4.0, 5);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.c() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testCopyConstructor()
{
    try
    {
        TGaussianFilter1D<klab::DoubleReal> filter(32, 4.0, 5);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.c() == 5)

        TGaussianFilter1D<klab::DoubleReal> filter2(filter);
        TEST_ASSERT(filter2.size() == 32)
        TEST_ASSERT(klab::Equals(filter2.sigma(), 4.0))
        TEST_ASSERT(filter2.c() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testAffectationOperator()
{
    try
    {
        TGaussianFilter1D<klab::DoubleReal> filter(32, 4.0, 5);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.c() == 5)

        TGaussianFilter1D<klab::DoubleReal> filter2(8);
        filter2 = filter;
        TEST_ASSERT(filter2.size() == 32)
        TEST_ASSERT(klab::Equals(filter2.sigma(), 4.0))
        TEST_ASSERT(filter2.c() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testSize()
{
    try
    {
        TGaussianFilter1D<klab::DoubleReal> filter(32);
        TEST_ASSERT(filter.size() == 32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testSigma()
{
    try
    {
        TGaussianFilter1D<klab::DoubleReal> filter(32, 4.0);
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testC()
{
    try
    {
        TGaussianFilter1D<klab::DoubleReal> filter(32, 4.0, 5);
        TEST_ASSERT(filter.c() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testApply_InOut()
{
    try
    {
        klab::DoubleReal precision = 1e-16;

        TGaussianFilter1D<klab::DoubleReal> filter(32, 4.0, 16);

        arma::Col<klab::DoubleReal> x(32);
        x.fill(1.0);

        filter.apply(x);
        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.00033546262790251185, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.00088382630693504996, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x[16], 1.0, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.00088382630693504996, precision)) 


        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        filter.apply(x);
        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.00033546262790251185, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.0017676526138700999, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.0065624733545486553, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.020344276924050803, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.055544982691211532, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.13676508530167408, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.30755853536385191, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.63647606974582149, precision))
        TEST_ASSERT(klab::Equals(x[8], 1.2180175491295144, precision))
        TEST_ASSERT(klab::Equals(x[9], 2.1626516682988730, precision))
        TEST_ASSERT(klab::Equals(x[10], 3.5711771409418471, precision))
        TEST_ASSERT(klab::Equals(x[11], 5.4940003412593708, precision))
        TEST_ASSERT(klab::Equals(x[12], 7.8848985762642343, precision))
        TEST_ASSERT(klab::Equals(x[13], 10.567754427846102, precision))
        TEST_ASSERT(klab::Equals(x[14], 13.237453538768932, precision))
        TEST_ASSERT(klab::Equals(x[15], 15.507731751621506, precision))
        TEST_ASSERT(klab::Equals(x[16], 17.0, precision))
        TEST_ASSERT(klab::Equals(x[17], 17.446198220574196, precision))
        TEST_ASSERT(klab::Equals(x[18], 16.767441149107313, precision))
        TEST_ASSERT(klab::Equals(x[19], 15.096792039780148, precision))
        TEST_ASSERT(klab::Equals(x[20], 12.737143853965302, precision))
        TEST_ASSERT(klab::Equals(x[21], 10.072333958975515, precision))
        TEST_ASSERT(klab::Equals(x[22], 7.467006749242044, precision))
        TEST_ASSERT(klab::Equals(x[23], 5.1903640039172956, precision))
        TEST_ASSERT(klab::Equals(x[24], 3.3833820809153177, precision))
        TEST_ASSERT(klab::Equals(x[25], 2.0685472266739198, precision))
        TEST_ASSERT(klab::Equals(x[26], 1.1862972078320004, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.63823706474114561, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.32216089960902689, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.15258207693038101, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.067812224663669443, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.028282441821921599, precision))


        // Limit cases.
        try                                 {TGaussianFilter1D<klab::DoubleReal> filter0(32, 0.0, 16); filter.apply(x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TGaussianFilter1D<klab::DoubleReal> filter00(0, 1.0, 0); 
        filter00.apply(x);
        TEST_ASSERT(x.n_rows == 32)
        for(klab::UInt32 i=0; i<32; ++i)
            TEST_ASSERT(klab::Equals(x[i], 0.0));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter1DUnitTest::testApply_In_Out()
{
    try
    {
        klab::DoubleReal precision = 1e-16;

        TGaussianFilter1D<klab::DoubleReal> filter(32, 4.0, 16);

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> xr;
        x.fill(1.0);

        filter.apply(x, xr);
        TEST_ASSERT(xr.n_rows == 32)
        TEST_ASSERT(klab::Equals(xr[0], 0.00033546262790251185, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.00088382630693504996, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(xr[3], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(xr[4], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(xr[5], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(xr[6], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(xr[7], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(xr[8], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(xr[9], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(xr[10], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(xr[11], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(xr[12], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(xr[13], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(xr[14], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(xr[15], 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(xr[16], 1.0, precision))
        TEST_ASSERT(klab::Equals(xr[17], 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(xr[18], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(xr[19], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(xr[20], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(xr[21], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(xr[22], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(xr[23], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(xr[24], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(xr[25], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(xr[26], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(xr[27], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(xr[28], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(xr[29], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(xr[30], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(xr[31], 0.00088382630693504996, precision)) 


        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        filter.apply(x, xr);
        TEST_ASSERT(xr.n_rows == 32)
        TEST_ASSERT(klab::Equals(xr[0], 0.00033546262790251185, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0017676526138700999, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.0065624733545486553, precision))
        TEST_ASSERT(klab::Equals(xr[3], 0.020344276924050803, precision))
        TEST_ASSERT(klab::Equals(xr[4], 0.055544982691211532, precision))
        TEST_ASSERT(klab::Equals(xr[5], 0.13676508530167408, precision))
        TEST_ASSERT(klab::Equals(xr[6], 0.30755853536385191, precision))
        TEST_ASSERT(klab::Equals(xr[7], 0.63647606974582149, precision))
        TEST_ASSERT(klab::Equals(xr[8], 1.2180175491295144, precision))
        TEST_ASSERT(klab::Equals(xr[9], 2.1626516682988730, precision))
        TEST_ASSERT(klab::Equals(xr[10], 3.5711771409418471, precision))
        TEST_ASSERT(klab::Equals(xr[11], 5.4940003412593708, precision))
        TEST_ASSERT(klab::Equals(xr[12], 7.8848985762642343, precision))
        TEST_ASSERT(klab::Equals(xr[13], 10.567754427846102, precision))
        TEST_ASSERT(klab::Equals(xr[14], 13.237453538768932, precision))
        TEST_ASSERT(klab::Equals(xr[15], 15.507731751621506, precision))
        TEST_ASSERT(klab::Equals(xr[16], 17.0, precision))
        TEST_ASSERT(klab::Equals(xr[17], 17.446198220574196, precision))
        TEST_ASSERT(klab::Equals(xr[18], 16.767441149107313, precision))
        TEST_ASSERT(klab::Equals(xr[19], 15.096792039780148, precision))
        TEST_ASSERT(klab::Equals(xr[20], 12.737143853965302, precision))
        TEST_ASSERT(klab::Equals(xr[21], 10.072333958975515, precision))
        TEST_ASSERT(klab::Equals(xr[22], 7.467006749242044, precision))
        TEST_ASSERT(klab::Equals(xr[23], 5.1903640039172956, precision))
        TEST_ASSERT(klab::Equals(xr[24], 3.3833820809153177, precision))
        TEST_ASSERT(klab::Equals(xr[25], 2.0685472266739198, precision))
        TEST_ASSERT(klab::Equals(xr[26], 1.1862972078320004, precision))
        TEST_ASSERT(klab::Equals(xr[27], 0.63823706474114561, precision))
        TEST_ASSERT(klab::Equals(xr[28], 0.32216089960902689, precision))
        TEST_ASSERT(klab::Equals(xr[29], 0.15258207693038101, precision))
        TEST_ASSERT(klab::Equals(xr[30], 0.067812224663669443, precision))
        TEST_ASSERT(klab::Equals(xr[31], 0.028282441821921599, precision))


        // Limit cases.
        try                                 {TGaussianFilter1D<klab::DoubleReal> filter0(32, 0.0, 16); filter.apply(x, xr); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TGaussianFilter1D<klab::DoubleReal> filter00(0, 1.0, 0); 
        filter00.apply(x, xr);
        TEST_ASSERT(x.n_rows == 32)
        for(klab::UInt32 i=0; i<32; ++i)
            TEST_ASSERT(klab::Equals(xr[i], 0.0));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
