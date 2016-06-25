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

#include "GaussWienerFilter2DUnitTest.h"
#include "../include/GaussWienerFilter2D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KGaussWienerFilter2DUnitTest::KGaussWienerFilter2DUnitTest() : Test::Suite()
{
    TEST_ADD(KGaussWienerFilter2DUnitTest::testMNConstructor)
    TEST_ADD(KGaussWienerFilter2DUnitTest::testMNGammaConstructor)  
    TEST_ADD(KGaussWienerFilter2DUnitTest::testMNGammaSigmaConstructor)  
    TEST_ADD(KGaussWienerFilter2DUnitTest::testMNGammaSigmaIcJcConstructor)  
    TEST_ADD(KGaussWienerFilter2DUnitTest::testCopyConstructor)
    TEST_ADD(KGaussWienerFilter2DUnitTest::testAffectationOperator)

    TEST_ADD(KGaussWienerFilter2DUnitTest::testM)
    TEST_ADD(KGaussWienerFilter2DUnitTest::testN)
    TEST_ADD(KGaussWienerFilter2DUnitTest::testGamma)
    TEST_ADD(KGaussWienerFilter2DUnitTest::testSigma)
    TEST_ADD(KGaussWienerFilter2DUnitTest::testIc)
    TEST_ADD(KGaussWienerFilter2DUnitTest::testJc)
    TEST_ADD(KGaussWienerFilter2DUnitTest::testApply_InOut)
    TEST_ADD(KGaussWienerFilter2DUnitTest::testApply_In_Out)
}

// ---------------------------------------------------------------------------------------------------- //

KGaussWienerFilter2DUnitTest::~KGaussWienerFilter2DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testMNConstructor()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.0))
        TEST_ASSERT(klab::Equals(filter.sigma(), 1.0))
        TEST_ASSERT(filter.ic() == 4)
        TEST_ASSERT(filter.jc() == 3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testMNGammaConstructor()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 1.0))
        TEST_ASSERT(filter.ic() == 4)
        TEST_ASSERT(filter.jc() == 3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testMNGammaSigmaConstructor()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4, 4.0);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.ic() == 4)
        TEST_ASSERT(filter.jc() == 3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testMNGammaSigmaIcJcConstructor()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4, 4.0, 1, 2);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.ic() == 1)
        TEST_ASSERT(filter.jc() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testCopyConstructor()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4, 4.0, 1, 2);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.ic() == 1)
        TEST_ASSERT(filter.jc() == 2)

        TGaussWienerFilter2D<klab::DoubleReal> filter2(filter);
        TEST_ASSERT(filter2.m() == 8)
        TEST_ASSERT(filter2.n() == 7)
        TEST_ASSERT(klab::Equals(filter2.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter2.sigma(), 4.0))
        TEST_ASSERT(filter2.ic() == 1)
        TEST_ASSERT(filter2.jc() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testAffectationOperator()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4, 4.0, 1, 2);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.ic() == 1)
        TEST_ASSERT(filter.jc() == 2)

        TGaussWienerFilter2D<klab::DoubleReal> filter2(1, 1, 0.4);
        filter2 = filter;
        TEST_ASSERT(filter2.m() == 8)
        TEST_ASSERT(filter2.n() == 7)
        TEST_ASSERT(klab::Equals(filter2.gamma(), 0.4))
        TEST_ASSERT(klab::Equals(filter2.sigma(), 4.0))
        TEST_ASSERT(filter2.ic() == 1)
        TEST_ASSERT(filter2.jc() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testM()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4);
        TEST_ASSERT(filter.m() == 8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testN()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(7, 8, 0.4);
        TEST_ASSERT(filter.n() == 8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testGamma()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4, 4.0);
        TEST_ASSERT(klab::Equals(filter.gamma(), 0.4))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testSigma()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4, 4.0);
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testIc()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4, 4.0, 5, 6);
        TEST_ASSERT(filter.ic() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testJc()
{
    try
    {
        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 7, 0.4, 4.0, 5, 6);
        TEST_ASSERT(filter.jc() == 6)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testApply_InOut()
{
    try
    {
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        klab::DoubleReal precision = 1e-12;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 8, 0.4, 4.0, 4, 4);

        arma::Mat<klab::DoubleReal> x(8, 8);
        x.fill(1.0);

        filter.apply(x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        TEST_ASSERT(klab::Equals(x(0, 0), 0.6871944605393091, precision))
        TEST_ASSERT(klab::Equals(x(0, 1), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x(0, 2), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(x(0, 3), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(x(0, 4), 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x(0, 5), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(x(0, 6), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(x(0, 7), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x(1, 0), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x(1, 1), 0.7862842540342283, precision))
        TEST_ASSERT(klab::Equals(x(1, 2), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(1, 3), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(1, 4), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x(1, 5), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(1, 6), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(1, 7), 0.7862842540342283, precision))
        TEST_ASSERT(klab::Equals(x(2, 0), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(x(2, 1), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(2, 2), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(x(2, 3), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(2, 4), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(2, 5), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(2, 6), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(x(2, 7), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(3, 0), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(x(3, 1), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(3, 2), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(3, 3), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(x(3, 4), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x(3, 5), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(x(3, 6), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(3, 7), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(4, 0), 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x(4, 1), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x(4, 2), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(4, 3), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x(4, 4), 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(x(4, 5), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x(4, 6), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(4, 7), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x(5, 0), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(x(5, 1), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(5, 2), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(5, 3), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(x(5, 4), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x(5, 5), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(x(5, 6), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(5, 7), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(6, 0), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(x(6, 1), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(6, 2), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(x(6, 3), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(6, 4), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(6, 5), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(6, 6), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(x(6, 7), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(7, 0), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x(7, 1), 0.7862842540342283, precision))
        TEST_ASSERT(klab::Equals(x(7, 2), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(7, 3), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(7, 4), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x(7, 5), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(7, 6), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(7, 7), 0.7862842540342283, precision))


        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = static_cast<klab::DoubleReal>(i+1) * static_cast<klab::DoubleReal>(j+1);
        }

        filter.apply(x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        TEST_ASSERT(klab::Equals(x(0, 0), 0.6871944605393091, precision))
        TEST_ASSERT(klab::Equals(x(0, 1), 1.5020499007120285, precision))
        TEST_ASSERT(klab::Equals(x(0, 2), 2.33907220007961, precision))
        TEST_ASSERT(klab::Equals(x(0, 3), 3.1538463753231976, precision))
        TEST_ASSERT(klab::Equals(x(0, 4), 3.9493872813376636, precision))
        TEST_ASSERT(klab::Equals(x(0, 5), 4.7307695629847961, precision))
        TEST_ASSERT(klab::Equals(x(0, 6), 5.4578351335190902, precision))
        TEST_ASSERT(klab::Equals(x(0, 7), 6.0081996028481139, precision))
        TEST_ASSERT(klab::Equals(x(1, 0), 1.5020499007120285, precision))
        TEST_ASSERT(klab::Equals(x(1, 1), 3.1451370161369132, precision))
        TEST_ASSERT(klab::Equals(x(1, 2), 4.7370363335876569, precision))
        TEST_ASSERT(klab::Equals(x(1, 3), 6.258063096690929, precision))
        TEST_ASSERT(klab::Equals(x(1, 4), 7.7835942516144883, precision))
        TEST_ASSERT(klab::Equals(x(1, 5), 9.3870946450363935, precision))
        TEST_ASSERT(klab::Equals(x(1, 6), 11.053084778371201, precision))
        TEST_ASSERT(klab::Equals(x(1, 7), 12.580548064547653, precision))
        TEST_ASSERT(klab::Equals(x(2, 0), 2.33907220007961, precision))
        TEST_ASSERT(klab::Equals(x(2, 1), 4.7370363335876569, precision))
        TEST_ASSERT(klab::Equals(x(2, 2), 6.9637293012453156, precision))
        TEST_ASSERT(klab::Equals(x(2, 3), 9.0703447929960035, precision))
        TEST_ASSERT(klab::Equals(x(2, 4), 11.22959343840806, precision))
        TEST_ASSERT(klab::Equals(x(2, 5), 13.605517189494003, precision))
        TEST_ASSERT(klab::Equals(x(2, 6), 16.248701702905734, precision))
        TEST_ASSERT(klab::Equals(x(2, 7), 18.948145334350627, precision))
        TEST_ASSERT(klab::Equals(x(3, 0), 3.1538463753231976, precision))
        TEST_ASSERT(klab::Equals(x(3, 1), 6.258063096690929, precision))
        TEST_ASSERT(klab::Equals(x(3, 2), 9.0703447929960035, precision))
        TEST_ASSERT(klab::Equals(x(3, 3), 11.719801408272149, precision))
        TEST_ASSERT(klab::Equals(x(3, 4), 14.472506822360558, precision))
        TEST_ASSERT(klab::Equals(x(3, 5), 17.579702112408224, precision))
        TEST_ASSERT(klab::Equals(x(3, 6), 21.164137850324007, precision))
        TEST_ASSERT(klab::Equals(x(3, 7), 25.032252386763716, precision))
        TEST_ASSERT(klab::Equals(x(4, 0), 3.9493872813376636, precision))
        TEST_ASSERT(klab::Equals(x(4, 1), 7.7835942516144883, precision))
        TEST_ASSERT(klab::Equals(x(4, 2), 11.22959343840806, precision))
        TEST_ASSERT(klab::Equals(x(4, 3), 14.472506822360558, precision))
        TEST_ASSERT(klab::Equals(x(4, 4), 17.857142857142858, precision))
        TEST_ASSERT(klab::Equals(x(4, 5), 21.708760233540836, precision))
        TEST_ASSERT(klab::Equals(x(4, 6), 26.202384689618807, precision))
        TEST_ASSERT(klab::Equals(x(4, 7), 31.134377006457953, precision))
        TEST_ASSERT(klab::Equals(x(5, 0), 4.7307695629847961, precision))
        TEST_ASSERT(klab::Equals(x(5, 1), 9.3870946450363935, precision))
        TEST_ASSERT(klab::Equals(x(5, 2), 13.605517189494003, precision))
        TEST_ASSERT(klab::Equals(x(5, 3), 17.579702112408224, precision))
        TEST_ASSERT(klab::Equals(x(5, 4), 21.708760233540836, precision))
        TEST_ASSERT(klab::Equals(x(5, 5), 26.369553168612335, precision))
        TEST_ASSERT(klab::Equals(x(5, 6), 31.746206775486009, precision))
        TEST_ASSERT(klab::Equals(x(5, 7), 37.548378580145574, precision))
        TEST_ASSERT(klab::Equals(x(6, 0), 5.4578351335190902, precision))
        TEST_ASSERT(klab::Equals(x(6, 1), 11.053084778371201, precision))
        TEST_ASSERT(klab::Equals(x(6, 2), 16.248701702905734, precision))
        TEST_ASSERT(klab::Equals(x(6, 3), 21.164137850324007, precision))
        TEST_ASSERT(klab::Equals(x(6, 4), 26.202384689618807, precision))
        TEST_ASSERT(klab::Equals(x(6, 5), 31.746206775486009, precision))
        TEST_ASSERT(klab::Equals(x(6, 6), 37.913637306780046, precision))
        TEST_ASSERT(klab::Equals(x(6, 7), 44.212339113484802, precision))
        TEST_ASSERT(klab::Equals(x(7, 0), 6.0081996028481139, precision))
        TEST_ASSERT(klab::Equals(x(7, 1), 12.580548064547653, precision))
        TEST_ASSERT(klab::Equals(x(7, 2), 18.948145334350627, precision))
        TEST_ASSERT(klab::Equals(x(7, 3), 25.032252386763716, precision))
        TEST_ASSERT(klab::Equals(x(7, 4), 31.134377006457953, precision))
        TEST_ASSERT(klab::Equals(x(7, 5), 37.548378580145574, precision))
        TEST_ASSERT(klab::Equals(x(7, 6), 44.212339113484802, precision))
        TEST_ASSERT(klab::Equals(x(7, 7), 50.322192258190611, precision))


        // Limit cases.
        try                                 {TGaussWienerFilter2D<klab::DoubleReal> filter0(8, 8, 0.4, 0.0, 4, 4); filter0.apply(x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TGaussWienerFilter2D<klab::DoubleReal> filter00(0, 8, 0.4, 1.0, 0, 0);
        filter00.apply(x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(x(i, j), 0.0));
        }

        TGaussWienerFilter2D<klab::DoubleReal> filter000(8, 0, 0.4, 1.0, 0, 0);
        filter000.apply(x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(x(i, j), 0.0));
        }

        TGaussWienerFilter2D<klab::DoubleReal> filter0000(0, 0, 0.4, 1.0, 0, 0);
        filter0000.apply(x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(x(i, j), 0.0));
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussWienerFilter2DUnitTest::testApply_In_Out()
{
    try
    {
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        klab::DoubleReal precision = 1e-12;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        TGaussWienerFilter2D<klab::DoubleReal> filter(8, 8, 0.4, 4.0, 4, 4);

        arma::Mat<klab::DoubleReal> x(8, 8);
        arma::Mat<klab::DoubleReal> xr;
        x.fill(1.0);

        filter.apply(x, xr);
        TEST_ASSERT(xr.n_rows==8 && xr.n_cols==8)
        TEST_ASSERT(klab::Equals(xr(0, 0), 0.6871944605393091, precision))
        TEST_ASSERT(klab::Equals(xr(0, 1), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(xr(0, 2), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(xr(0, 3), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(xr(0, 4), 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(xr(0, 5), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(xr(0, 6), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(xr(0, 7), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(xr(1, 0), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(xr(1, 1), 0.7862842540342283, precision))
        TEST_ASSERT(klab::Equals(xr(1, 2), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(xr(1, 3), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(xr(1, 4), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(xr(1, 5), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(xr(1, 6), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(xr(1, 7), 0.7862842540342283, precision))
        TEST_ASSERT(klab::Equals(xr(2, 0), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(xr(2, 1), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(xr(2, 2), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(xr(2, 3), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(xr(2, 4), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(xr(2, 5), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(xr(2, 6), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(xr(2, 7), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(xr(3, 0), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(xr(3, 1), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(xr(3, 2), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(xr(3, 3), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(xr(3, 4), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(xr(3, 5), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(xr(3, 6), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(xr(3, 7), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(xr(4, 0), 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(xr(4, 1), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(xr(4, 2), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(xr(4, 3), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(xr(4, 4), 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(xr(4, 5), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(xr(4, 6), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(xr(4, 7), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(xr(5, 0), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(xr(5, 1), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(xr(5, 2), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(xr(5, 3), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(xr(5, 4), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(xr(5, 5), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(xr(5, 6), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(xr(5, 7), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(xr(6, 0), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(xr(6, 1), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(xr(6, 2), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(xr(6, 3), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(xr(6, 4), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(xr(6, 5), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(xr(6, 6), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(xr(6, 7), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(xr(7, 0), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(xr(7, 1), 0.7862842540342283, precision))
        TEST_ASSERT(klab::Equals(xr(7, 2), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(xr(7, 3), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(xr(7, 4), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(xr(7, 5), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(xr(7, 6), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(xr(7, 7), 0.7862842540342283, precision))


        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = static_cast<klab::DoubleReal>(i+1) * static_cast<klab::DoubleReal>(j+1);
        }

        filter.apply(x, xr);
        TEST_ASSERT(xr.n_rows==8 && xr.n_cols==8)
        TEST_ASSERT(klab::Equals(xr(0, 0), 0.6871944605393091, precision))
        TEST_ASSERT(klab::Equals(xr(0, 1), 1.5020499007120285, precision))
        TEST_ASSERT(klab::Equals(xr(0, 2), 2.33907220007961, precision))
        TEST_ASSERT(klab::Equals(xr(0, 3), 3.1538463753231976, precision))
        TEST_ASSERT(klab::Equals(xr(0, 4), 3.9493872813376636, precision))
        TEST_ASSERT(klab::Equals(xr(0, 5), 4.7307695629847961, precision))
        TEST_ASSERT(klab::Equals(xr(0, 6), 5.4578351335190902, precision))
        TEST_ASSERT(klab::Equals(xr(0, 7), 6.0081996028481139, precision))
        TEST_ASSERT(klab::Equals(xr(1, 0), 1.5020499007120285, precision))
        TEST_ASSERT(klab::Equals(xr(1, 1), 3.1451370161369132, precision))
        TEST_ASSERT(klab::Equals(xr(1, 2), 4.7370363335876569, precision))
        TEST_ASSERT(klab::Equals(xr(1, 3), 6.258063096690929, precision))
        TEST_ASSERT(klab::Equals(xr(1, 4), 7.7835942516144883, precision))
        TEST_ASSERT(klab::Equals(xr(1, 5), 9.3870946450363935, precision))
        TEST_ASSERT(klab::Equals(xr(1, 6), 11.053084778371201, precision))
        TEST_ASSERT(klab::Equals(xr(1, 7), 12.580548064547653, precision))
        TEST_ASSERT(klab::Equals(xr(2, 0), 2.33907220007961, precision))
        TEST_ASSERT(klab::Equals(xr(2, 1), 4.7370363335876569, precision))
        TEST_ASSERT(klab::Equals(xr(2, 2), 6.9637293012453156, precision))
        TEST_ASSERT(klab::Equals(xr(2, 3), 9.0703447929960035, precision))
        TEST_ASSERT(klab::Equals(xr(2, 4), 11.22959343840806, precision))
        TEST_ASSERT(klab::Equals(xr(2, 5), 13.605517189494003, precision))
        TEST_ASSERT(klab::Equals(xr(2, 6), 16.248701702905734, precision))
        TEST_ASSERT(klab::Equals(xr(2, 7), 18.948145334350627, precision))
        TEST_ASSERT(klab::Equals(xr(3, 0), 3.1538463753231976, precision))
        TEST_ASSERT(klab::Equals(xr(3, 1), 6.258063096690929, precision))
        TEST_ASSERT(klab::Equals(xr(3, 2), 9.0703447929960035, precision))
        TEST_ASSERT(klab::Equals(xr(3, 3), 11.719801408272149, precision))
        TEST_ASSERT(klab::Equals(xr(3, 4), 14.472506822360558, precision))
        TEST_ASSERT(klab::Equals(xr(3, 5), 17.579702112408224, precision))
        TEST_ASSERT(klab::Equals(xr(3, 6), 21.164137850324007, precision))
        TEST_ASSERT(klab::Equals(xr(3, 7), 25.032252386763716, precision))
        TEST_ASSERT(klab::Equals(xr(4, 0), 3.9493872813376636, precision))
        TEST_ASSERT(klab::Equals(xr(4, 1), 7.7835942516144883, precision))
        TEST_ASSERT(klab::Equals(xr(4, 2), 11.22959343840806, precision))
        TEST_ASSERT(klab::Equals(xr(4, 3), 14.472506822360558, precision))
        TEST_ASSERT(klab::Equals(xr(4, 4), 17.857142857142858, precision))
        TEST_ASSERT(klab::Equals(xr(4, 5), 21.708760233540836, precision))
        TEST_ASSERT(klab::Equals(xr(4, 6), 26.202384689618807, precision))
        TEST_ASSERT(klab::Equals(xr(4, 7), 31.134377006457953, precision))
        TEST_ASSERT(klab::Equals(xr(5, 0), 4.7307695629847961, precision))
        TEST_ASSERT(klab::Equals(xr(5, 1), 9.3870946450363935, precision))
        TEST_ASSERT(klab::Equals(xr(5, 2), 13.605517189494003, precision))
        TEST_ASSERT(klab::Equals(xr(5, 3), 17.579702112408224, precision))
        TEST_ASSERT(klab::Equals(xr(5, 4), 21.708760233540836, precision))
        TEST_ASSERT(klab::Equals(xr(5, 5), 26.369553168612335, precision))
        TEST_ASSERT(klab::Equals(xr(5, 6), 31.746206775486009, precision))
        TEST_ASSERT(klab::Equals(xr(5, 7), 37.548378580145574, precision))
        TEST_ASSERT(klab::Equals(xr(6, 0), 5.4578351335190902, precision))
        TEST_ASSERT(klab::Equals(xr(6, 1), 11.053084778371201, precision))
        TEST_ASSERT(klab::Equals(xr(6, 2), 16.248701702905734, precision))
        TEST_ASSERT(klab::Equals(xr(6, 3), 21.164137850324007, precision))
        TEST_ASSERT(klab::Equals(xr(6, 4), 26.202384689618807, precision))
        TEST_ASSERT(klab::Equals(xr(6, 5), 31.746206775486009, precision))
        TEST_ASSERT(klab::Equals(xr(6, 6), 37.913637306780046, precision))
        TEST_ASSERT(klab::Equals(xr(6, 7), 44.212339113484802, precision))
        TEST_ASSERT(klab::Equals(xr(7, 0), 6.0081996028481139, precision))
        TEST_ASSERT(klab::Equals(xr(7, 1), 12.580548064547653, precision))
        TEST_ASSERT(klab::Equals(xr(7, 2), 18.948145334350627, precision))
        TEST_ASSERT(klab::Equals(xr(7, 3), 25.032252386763716, precision))
        TEST_ASSERT(klab::Equals(xr(7, 4), 31.134377006457953, precision))
        TEST_ASSERT(klab::Equals(xr(7, 5), 37.548378580145574, precision))
        TEST_ASSERT(klab::Equals(xr(7, 6), 44.212339113484802, precision))
        TEST_ASSERT(klab::Equals(xr(7, 7), 50.322192258190611, precision))


        // Limit cases.
        try                                 {TGaussWienerFilter2D<klab::DoubleReal> filter0(8, 8, 0.4, 0.0, 4, 4); filter0.apply(x, xr); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TGaussWienerFilter2D<klab::DoubleReal> filter00(0, 8, 0.4, 1.0, 0, 0);
        filter00.apply(x, xr);
        TEST_ASSERT(xr.n_rows==8 && xr.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(xr(i, j), 0.0));
        }

        TGaussWienerFilter2D<klab::DoubleReal> filter000(8, 0, 0.4, 1.0, 0, 0);
        filter000.apply(x, xr);
        TEST_ASSERT(xr.n_rows==8 && xr.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(xr(i, j), 0.0));
        }

        TGaussWienerFilter2D<klab::DoubleReal> filter0000(0, 0, 0.4, 1.0, 0, 0);
        filter0000.apply(x, xr);
        TEST_ASSERT(xr.n_rows==8 && xr.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(xr(i, j), 0.0));
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
