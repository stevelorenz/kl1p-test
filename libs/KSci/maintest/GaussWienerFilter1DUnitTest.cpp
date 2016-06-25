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

#include "GaussWienerFilter1DUnitTest.h"
#include "../include/GaussWienerFilter1D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KGaussWienerFilter1DUnitTest::KGaussWienerFilter1DUnitTest() : Test::Suite()
{
    TEST_ADD(KGaussWienerFilter1DUnitTest::testSizeConstructor)  
    TEST_ADD(KGaussWienerFilter1DUnitTest::testSizeGammaConstructor)  
    TEST_ADD(KGaussWienerFilter1DUnitTest::testSizeGammaSigmaConstructor)  
    TEST_ADD(KGaussWienerFilter1DUnitTest::testSizeGammaSigmaCConstructor)  
    TEST_ADD(KGaussWienerFilter1DUnitTest::testCopyConstructor)
    TEST_ADD(KGaussWienerFilter1DUnitTest::testAffectationOperator)

    TEST_ADD(KGaussWienerFilter1DUnitTest::testSize)
    TEST_ADD(KGaussWienerFilter1DUnitTest::testGamma)
    TEST_ADD(KGaussWienerFilter1DUnitTest::testSigma)
    TEST_ADD(KGaussWienerFilter1DUnitTest::testC)
    TEST_ADD(KGaussWienerFilter1DUnitTest::testApply_InOut)
    TEST_ADD(KGaussWienerFilter1DUnitTest::testApply_In_Out)
}

// ---------------------------------------------------------------------------------------------------- //

KGaussWienerFilter1DUnitTest::~KGaussWienerFilter1DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testSizeConstructor()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.0))
        TEST_ASSERT(klab::Equals(filter.sigma(), 1.0))
        TEST_ASSERT(filter.c() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testSizeGammaConstructor()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 1.0))
        TEST_ASSERT(filter.c() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testSizeGammaSigmaConstructor()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4, 4.0);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.c() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testSizeGammaSigmaCConstructor()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4, 4.0, 5);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.c() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testCopyConstructor()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4, 4.0, 5);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.c() == 5)

        TGaussWienerFilter1D<klab::DoubleReal> filter2(filter);
        TEST_ASSERT(filter2.size() == 32)
        TEST_ASSERT(klab::Equals(filter2.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter2.sigma(), 4.0))
        TEST_ASSERT(filter2.c() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testAffectationOperator()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4, 4.0, 5);
        TEST_ASSERT(filter.size() == 32)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.c() == 5)

        TGaussWienerFilter1D<klab::DoubleReal> filter2(8, 0.4);
        filter2 = filter;
        TEST_ASSERT(filter2.size() == 32)
        TEST_ASSERT(klab::Equals(filter2.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter2.sigma(), 4.0))
        TEST_ASSERT(filter2.c() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testSize()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4);
        TEST_ASSERT(filter.size() == 32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testGamma()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4, 4.0);
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testSigma()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4, 4.0);
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testC()
{
    try
    {
        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4, 4.0, 5);
        TEST_ASSERT(filter.c() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter1DUnitTest::testApply_InOut()
{
    try
    {
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        klab::DoubleReal precision = 1e-12;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4, 4.0, 16);

        arma::Col<klab::DoubleReal> x(32);
        x.fill(1.0);

        filter.apply(x);
        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.00083865633381043688, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.0022095614523461545, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.0054686623749786072, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.012714350837277439, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.027763925494091006, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.056911527736694015, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.19580037023510777, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.48406308739795989, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x[16], 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.48406308739795989, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.19580037023510777, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.056911527736694015, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.027763925494091006, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.012714350837277439, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.0054686623749786072, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.0022095614523461545, precision))  


        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        filter.apply(x);
        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.00083865633381043688, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.0044191229046923091, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.016405987124935822, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.050857403349109757, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.13881962747045504, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.34146916642016412, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.7652033634147315, precision))
        TEST_ASSERT(klab::Equals(x[7], 1.5664029618808621, precision))
        TEST_ASSERT(klab::Equals(x[8], 2.9117188933342484, precision))
        TEST_ASSERT(klab::Equals(x[9], 4.8406308739795989, precision))
        TEST_ASSERT(klab::Equals(x[10], 7.0660518801502636, precision))
        TEST_ASSERT(klab::Equals(x[11], 9.01229940427217, precision))
        TEST_ASSERT(klab::Equals(x[12], 10.268406931477925, precision))
        TEST_ASSERT(klab::Equals(x[13], 10.897031952260283, precision))
        TEST_ASSERT(klab::Equals(x[14], 11.22959343840806, precision))
        TEST_ASSERT(klab::Equals(x[15], 11.578005457888446, precision))
        TEST_ASSERT(klab::Equals(x[16], 12.142857142857142, precision))
        TEST_ASSERT(klab::Equals(x[17], 13.025256140124503, precision))
        TEST_ASSERT(klab::Equals(x[18], 14.22415168865021, precision))
        TEST_ASSERT(klab::Equals(x[19], 15.567188503228977, precision))
        TEST_ASSERT(klab::Equals(x[20], 16.587426581618185, precision))
        TEST_ASSERT(klab::Equals(x[21], 16.522548907832313, precision))
        TEST_ASSERT(klab::Equals(x[22], 14.77447211304146, precision))
        TEST_ASSERT(klab::Equals(x[23], 11.617514097551037, precision))
        TEST_ASSERT(klab::Equals(x[24], 8.0881080370395786, precision))
        TEST_ASSERT(klab::Equals(x[25], 5.0908096261128017, precision))
        TEST_ASSERT(klab::Equals(x[26], 2.9514986874568212, precision))
        TEST_ASSERT(klab::Equals(x[27], 1.5935227766274322, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.80515383932863915, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.3814305251183232, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.16952853362433681, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.070705966475076945, precision))


        // Limit cases.
        try                                 {TGaussWienerFilter1D<klab::DoubleReal> filter0(32, 0.4, 0.0, 16); filter0.apply(x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TGaussWienerFilter1D<klab::DoubleReal> filter00(0, 0.4, 1.0, 0);
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

void KGaussWienerFilter1DUnitTest::testApply_In_Out()
{
    try
    {
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        klab::DoubleReal precision = 1e-9;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        TGaussWienerFilter1D<klab::DoubleReal> filter(32, 0.4, 4.0, 16);

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> xr;
        x.fill(1.0);

        filter.apply(x, xr);
        TEST_ASSERT(xr.n_rows == 32)
        TEST_ASSERT(klab::Equals(xr[0], 0.00083865633381043688, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0022095614523461545, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.0054686623749786072, precision))
        TEST_ASSERT(klab::Equals(xr[3], 0.012714350837277439, precision))
        TEST_ASSERT(klab::Equals(xr[4], 0.027763925494091006, precision))
        TEST_ASSERT(klab::Equals(xr[5], 0.056911527736694015, precision))
        TEST_ASSERT(klab::Equals(xr[6], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(xr[7], 0.19580037023510777, precision))
        TEST_ASSERT(klab::Equals(xr[8], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(xr[9], 0.48406308739795989, precision))
        TEST_ASSERT(klab::Equals(xr[10], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(xr[11], 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(xr[12], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(xr[13], 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(xr[14], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(xr[15], 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(xr[16], 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(xr[17], 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(xr[18], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(xr[19], 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(xr[20], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(xr[21], 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(xr[22], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(xr[23], 0.48406308739795989, precision))
        TEST_ASSERT(klab::Equals(xr[24], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(xr[25], 0.19580037023510777, precision))
        TEST_ASSERT(klab::Equals(xr[26], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(xr[27], 0.056911527736694015, precision))
        TEST_ASSERT(klab::Equals(xr[28], 0.027763925494091006, precision))
        TEST_ASSERT(klab::Equals(xr[29], 0.012714350837277439, precision))
        TEST_ASSERT(klab::Equals(xr[30], 0.0054686623749786072, precision))
        TEST_ASSERT(klab::Equals(xr[31], 0.0022095614523461545, precision))  


        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        filter.apply(x, xr);
        TEST_ASSERT(xr.n_rows == 32)
        TEST_ASSERT(klab::Equals(xr[0], 0.00083865633381043688, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0044191229046923091, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.016405987124935822, precision))
        TEST_ASSERT(klab::Equals(xr[3], 0.050857403349109757, precision))
        TEST_ASSERT(klab::Equals(xr[4], 0.13881962747045504, precision))
        TEST_ASSERT(klab::Equals(xr[5], 0.34146916642016412, precision))
        TEST_ASSERT(klab::Equals(xr[6], 0.7652033634147315, precision))
        TEST_ASSERT(klab::Equals(xr[7], 1.5664029618808621, precision))
        TEST_ASSERT(klab::Equals(xr[8], 2.9117188933342484, precision))
        TEST_ASSERT(klab::Equals(xr[9], 4.8406308739795989, precision))
        TEST_ASSERT(klab::Equals(xr[10], 7.0660518801502636, precision))
        TEST_ASSERT(klab::Equals(xr[11], 9.01229940427217, precision))
        TEST_ASSERT(klab::Equals(xr[12], 10.268406931477925, precision))
        TEST_ASSERT(klab::Equals(xr[13], 10.897031952260283, precision))
        TEST_ASSERT(klab::Equals(xr[14], 11.22959343840806, precision))
        TEST_ASSERT(klab::Equals(xr[15], 11.578005457888446, precision))
        TEST_ASSERT(klab::Equals(xr[16], 12.142857142857142, precision))
        TEST_ASSERT(klab::Equals(xr[17], 13.025256140124503, precision))
        TEST_ASSERT(klab::Equals(xr[18], 14.22415168865021, precision))
        TEST_ASSERT(klab::Equals(xr[19], 15.567188503228977, precision))
        TEST_ASSERT(klab::Equals(xr[20], 16.587426581618185, precision))
        TEST_ASSERT(klab::Equals(xr[21], 16.522548907832313, precision))
        TEST_ASSERT(klab::Equals(xr[22], 14.77447211304146, precision))
        TEST_ASSERT(klab::Equals(xr[23], 11.617514097551037, precision))
        TEST_ASSERT(klab::Equals(xr[24], 8.0881080370395786, precision))
        TEST_ASSERT(klab::Equals(xr[25], 5.0908096261128017, precision))
        TEST_ASSERT(klab::Equals(xr[26], 2.9514986874568212, precision))
        TEST_ASSERT(klab::Equals(xr[27], 1.5935227766274322, precision))
        TEST_ASSERT(klab::Equals(xr[28], 0.80515383932863915, precision))
        TEST_ASSERT(klab::Equals(xr[29], 0.3814305251183232, precision))
        TEST_ASSERT(klab::Equals(xr[30], 0.16952853362433681, precision))
        TEST_ASSERT(klab::Equals(xr[31], 0.070705966475076945, precision))


        // Limit cases.
        try                                 {TGaussWienerFilter1D<klab::DoubleReal> filter0(32, 0.4, 0.0, 16); filter0.apply(x, xr); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TGaussWienerFilter1D<klab::DoubleReal> filter00(0, 0.4, 1.0, 0);
        filter00.apply(x, xr);
        TEST_ASSERT(xr.n_rows == 32)
        for(klab::UInt32 i=0; i<32; ++i)
            TEST_ASSERT(klab::Equals(xr[i], 0.0));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
