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

#include "GaussianFilter2DUnitTest.h"
#include "../include/GaussianFilter2D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KGaussianFilter2DUnitTest::KGaussianFilter2DUnitTest() : Test::Suite()
{
    TEST_ADD(KGaussianFilter2DUnitTest::testMNConstructor)  
    TEST_ADD(KGaussianFilter2DUnitTest::testMNSigmaConstructor)  
    TEST_ADD(KGaussianFilter2DUnitTest::testMNSigmaIcJcConstructor)  
    TEST_ADD(KGaussianFilter2DUnitTest::testCopyConstructor)
    TEST_ADD(KGaussianFilter2DUnitTest::testAffectationOperator)

    TEST_ADD(KGaussianFilter2DUnitTest::testM)
    TEST_ADD(KGaussianFilter2DUnitTest::testN)
    TEST_ADD(KGaussianFilter2DUnitTest::testSigma)
    TEST_ADD(KGaussianFilter2DUnitTest::testIc)
    TEST_ADD(KGaussianFilter2DUnitTest::testJc)
    TEST_ADD(KGaussianFilter2DUnitTest::testApply_InOut)
    TEST_ADD(KGaussianFilter2DUnitTest::testApply_In_Out)
}

// ---------------------------------------------------------------------------------------------------- //

KGaussianFilter2DUnitTest::~KGaussianFilter2DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter2DUnitTest::testMNConstructor()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(8, 7);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
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

void KGaussianFilter2DUnitTest::testMNSigmaConstructor()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(8, 7, 4.0);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
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

void KGaussianFilter2DUnitTest::testMNSigmaIcJcConstructor()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(8, 7, 4.0, 1, 2);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
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

void KGaussianFilter2DUnitTest::testCopyConstructor()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(8, 7, 4.0, 1, 2);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.ic() == 1)
        TEST_ASSERT(filter.jc() == 2)

        TGaussianFilter2D<klab::DoubleReal> filter2(filter);
        TEST_ASSERT(filter2.m() == 8)
        TEST_ASSERT(filter2.n() == 7)
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

void KGaussianFilter2DUnitTest::testAffectationOperator()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(8, 7, 4.0, 1, 2);
        TEST_ASSERT(filter.m() == 8)
        TEST_ASSERT(filter.n() == 7)
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
        TEST_ASSERT(filter.ic() == 1)
        TEST_ASSERT(filter.jc() == 2)

        TGaussianFilter2D<klab::DoubleReal> filter2(1, 1);
        filter2 = filter;
        TEST_ASSERT(filter2.m() == 8)
        TEST_ASSERT(filter2.n() == 7)
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

void KGaussianFilter2DUnitTest::testM()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(8, 7);
        TEST_ASSERT(filter.m() == 8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter2DUnitTest::testN()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(7, 8);
        TEST_ASSERT(filter.n() == 8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter2DUnitTest::testSigma()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(8, 7, 4.0);
        TEST_ASSERT(klab::Equals(filter.sigma(), 4.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter2DUnitTest::testIc()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(8, 7, 4.0, 5, 6);
        TEST_ASSERT(filter.ic() == 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter2DUnitTest::testJc()
{
    try
    {
        TGaussianFilter2D<klab::DoubleReal> filter(8, 7, 4.0, 5, 6);
        TEST_ASSERT(filter.jc() == 6)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianFilter2DUnitTest::testApply_InOut()
{
    try
    {
        klab::DoubleReal precision = 1e-16;

        TGaussianFilter2D<klab::DoubleReal> filter(8, 8, 4.0, 4, 4);

        arma::Mat<klab::DoubleReal> x(8, 8);
        x.fill(1.0);

        filter.apply(x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        TEST_ASSERT(klab::Equals(x(0, 0), 0.36787944117144233, precision))
        TEST_ASSERT(klab::Equals(x(0, 1), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x(0, 2), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(x(0, 3), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(x(0, 4), 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x(0, 5), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(x(0, 6), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(x(0, 7), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x(1, 0), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x(1, 1), 0.56978282473092301, precision))
        TEST_ASSERT(klab::Equals(x(1, 2), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(1, 3), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(1, 4), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x(1, 5), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(1, 6), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(1, 7), 0.56978282473092301, precision))
        TEST_ASSERT(klab::Equals(x(2, 0), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(x(2, 1), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(2, 2), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(x(2, 3), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(2, 4), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(2, 5), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(2, 6), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(x(2, 7), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(3, 0), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(x(3, 1), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(3, 2), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(3, 3), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(x(3, 4), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x(3, 5), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(x(3, 6), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(3, 7), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(4, 0), 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x(4, 1), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x(4, 2), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(4, 3), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x(4, 4), 1.0, precision))
        TEST_ASSERT(klab::Equals(x(4, 5), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x(4, 6), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(4, 7), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x(5, 0), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(x(5, 1), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(5, 2), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(5, 3), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(x(5, 4), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x(5, 5), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(x(5, 6), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(5, 7), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(6, 0), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(x(6, 1), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(6, 2), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(x(6, 3), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(6, 4), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(6, 5), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(6, 6), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(x(6, 7), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(7, 0), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x(7, 1), 0.56978282473092301, precision))
        TEST_ASSERT(klab::Equals(x(7, 2), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(7, 3), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(7, 4), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x(7, 5), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(7, 6), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(7, 7), 0.56978282473092301, precision))


        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = static_cast<klab::DoubleReal>(i+1) * static_cast<klab::DoubleReal>(j+1);
        }

        filter.apply(x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        TEST_ASSERT(klab::Equals(x(0, 0), 0.36787944117144233, precision))
        TEST_ASSERT(klab::Equals(x(0, 1), 0.91566672354322853, precision))
        TEST_ASSERT(klab::Equals(x(0, 2), 1.6057842855569708, precision))
        TEST_ASSERT(klab::Equals(x(0, 3), 2.351478692489386, precision))
        TEST_ASSERT(klab::Equals(x(0, 4), 3.0326532985631669, precision))
        TEST_ASSERT(klab::Equals(x(0, 5), 3.527218038734079, precision))
        TEST_ASSERT(klab::Equals(x(0, 6), 3.746829999632932, precision))
        TEST_ASSERT(klab::Equals(x(0, 7), 3.6626668941729141, precision))
        TEST_ASSERT(klab::Equals(x(1, 0), 0.91566672354322853, precision))
        TEST_ASSERT(klab::Equals(x(1, 1), 2.279131298923692, precision))
        TEST_ASSERT(klab::Equals(x(1, 2), 3.9968616642209271, precision))
        TEST_ASSERT(klab::Equals(x(1, 3), 5.8529250315731343, precision))
        TEST_ASSERT(klab::Equals(x(1, 4), 7.5483960198900739, precision))
        TEST_ASSERT(klab::Equals(x(1, 5), 8.7793875473597005, precision))
        TEST_ASSERT(klab::Equals(x(1, 6), 9.3260105498488297, precision))
        TEST_ASSERT(klab::Equals(x(1, 7), 9.1165251956947682, precision))
        TEST_ASSERT(klab::Equals(x(2, 0), 1.6057842855569708, precision))
        TEST_ASSERT(klab::Equals(x(2, 1), 3.9968616642209271, precision))
        TEST_ASSERT(klab::Equals(x(2, 2), 7.0092070476426436, precision))
        TEST_ASSERT(klab::Equals(x(2, 3), 10.264143927689069, precision))
        TEST_ASSERT(klab::Equals(x(2, 4), 13.237453538768932, precision))
        TEST_ASSERT(klab::Equals(x(2, 5), 15.396215891533606, precision))
        TEST_ASSERT(klab::Equals(x(2, 6), 16.354816444499502, precision))
        TEST_ASSERT(klab::Equals(x(2, 7), 15.987446656883709, precision))
        TEST_ASSERT(klab::Equals(x(3, 0), 2.351478692489386, precision))
        TEST_ASSERT(klab::Equals(x(3, 1), 5.8529250315731343, precision))
        TEST_ASSERT(klab::Equals(x(3, 2), 10.264143927689069, precision))
        TEST_ASSERT(klab::Equals(x(3, 3), 15.030609005015613, precision))
        TEST_ASSERT(klab::Equals(x(3, 4), 19.384664689526883, precision))
        TEST_ASSERT(klab::Equals(x(3, 5), 22.545913507523419, precision))
        TEST_ASSERT(klab::Equals(x(3, 6), 23.94966916460783, precision))
        TEST_ASSERT(klab::Equals(x(3, 7), 23.411700126292537, precision))
        TEST_ASSERT(klab::Equals(x(4, 0), 3.0326532985631669, precision))
        TEST_ASSERT(klab::Equals(x(4, 1), 7.5483960198900739, precision))
        TEST_ASSERT(klab::Equals(x(4, 2), 13.237453538768932, precision))
        TEST_ASSERT(klab::Equals(x(4, 3), 19.384664689526883, precision))
        TEST_ASSERT(klab::Equals(x(4, 4), 25.0, precision))
        TEST_ASSERT(klab::Equals(x(4, 5), 29.076997034290322, precision))
        TEST_ASSERT(klab::Equals(x(4, 6), 30.88739159046084, precision))
        TEST_ASSERT(klab::Equals(x(4, 7), 30.193584079560296, precision))
        TEST_ASSERT(klab::Equals(x(5, 0), 3.527218038734079, precision))
        TEST_ASSERT(klab::Equals(x(5, 1), 8.7793875473597005, precision))
        TEST_ASSERT(klab::Equals(x(5, 2), 15.396215891533606, precision))
        TEST_ASSERT(klab::Equals(x(5, 3), 22.545913507523419, precision))
        TEST_ASSERT(klab::Equals(x(5, 4), 29.076997034290322, precision))
        TEST_ASSERT(klab::Equals(x(5, 5), 33.818870261285127, precision))
        TEST_ASSERT(klab::Equals(x(5, 6), 35.924503746911746, precision))
        TEST_ASSERT(klab::Equals(x(5, 7), 35.117550189438802, precision))
        TEST_ASSERT(klab::Equals(x(6, 0), 3.746829999632932, precision))
        TEST_ASSERT(klab::Equals(x(6, 1), 9.3260105498488297, precision))
        TEST_ASSERT(klab::Equals(x(6, 2), 16.354816444499502, precision))
        TEST_ASSERT(klab::Equals(x(6, 3), 23.94966916460783, precision))
        TEST_ASSERT(klab::Equals(x(6, 4), 30.88739159046084, precision))
        TEST_ASSERT(klab::Equals(x(6, 5), 35.924503746911746, precision))
        TEST_ASSERT(klab::Equals(x(6, 6), 38.161238370498836, precision))
        TEST_ASSERT(klab::Equals(x(6, 7), 37.304042199395319, precision))
        TEST_ASSERT(klab::Equals(x(7, 0), 3.6626668941729141, precision))
        TEST_ASSERT(klab::Equals(x(7, 1), 9.1165251956947682, precision))
        TEST_ASSERT(klab::Equals(x(7, 2), 15.987446656883709, precision))
        TEST_ASSERT(klab::Equals(x(7, 3), 23.411700126292537, precision))
        TEST_ASSERT(klab::Equals(x(7, 4), 30.193584079560296, precision))
        TEST_ASSERT(klab::Equals(x(7, 5), 35.117550189438802, precision))
        TEST_ASSERT(klab::Equals(x(7, 6), 37.304042199395319, precision))
        TEST_ASSERT(klab::Equals(x(7, 7), 36.466100782779073, precision))


        // Limit cases.
        try                                 {TGaussianFilter2D<klab::DoubleReal> filter0(8, 8, 0.0, 4, 4); filter.apply(x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TGaussianFilter2D<klab::DoubleReal> filter00(0, 8, 1.0, 0, 4); 
        filter00.apply(x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(x(i, j), 0.0));
        }

        TGaussianFilter2D<klab::DoubleReal> filter000(8, 0, 1.0, 4, 0); 
        filter000.apply(x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(x(i, j), 0.0));
        }

        TGaussianFilter2D<klab::DoubleReal> filter0000(0, 0, 1.0, 0, 0); 
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

void KGaussianFilter2DUnitTest::testApply_In_Out()
{
    try
    {
        klab::DoubleReal precision = 1e-16;

        TGaussianFilter2D<klab::DoubleReal> filter(8, 8, 4.0, 4, 4);

        arma::Mat<klab::DoubleReal> x(8, 8);
        arma::Mat<klab::DoubleReal> xr;
        x.fill(1.0);

        filter.apply(x, xr);
        TEST_ASSERT(xr.n_rows==8 && xr.n_cols==8)
        TEST_ASSERT(klab::Equals(xr(0, 0), 0.36787944117144233, precision))
        TEST_ASSERT(klab::Equals(xr(0, 1), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(xr(0, 2), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(xr(0, 3), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(xr(0, 4), 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(xr(0, 5), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(xr(0, 6), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(xr(0, 7), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(xr(1, 0), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(xr(1, 1), 0.56978282473092301, precision))
        TEST_ASSERT(klab::Equals(xr(1, 2), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(xr(1, 3), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(xr(1, 4), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(xr(1, 5), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(xr(1, 6), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(xr(1, 7), 0.56978282473092301, precision))
        TEST_ASSERT(klab::Equals(xr(2, 0), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(xr(2, 1), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(xr(2, 2), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(xr(2, 3), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(xr(2, 4), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(xr(2, 5), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(xr(2, 6), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(xr(2, 7), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(xr(3, 0), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(xr(3, 1), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(xr(3, 2), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(xr(3, 3), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(xr(3, 4), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(xr(3, 5), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(xr(3, 6), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(xr(3, 7), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(xr(4, 0), 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(xr(4, 1), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(xr(4, 2), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(xr(4, 3), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(xr(4, 4), 1.0, precision))
        TEST_ASSERT(klab::Equals(xr(4, 5), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(xr(4, 6), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(xr(4, 7), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(xr(5, 0), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(xr(5, 1), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(xr(5, 2), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(xr(5, 3), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(xr(5, 4), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(xr(5, 5), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(xr(5, 6), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(xr(5, 7), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(xr(6, 0), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(xr(6, 1), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(xr(6, 2), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(xr(6, 3), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(xr(6, 4), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(xr(6, 5), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(xr(6, 6), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(xr(6, 7), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(xr(7, 0), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(xr(7, 1), 0.56978282473092301, precision))
        TEST_ASSERT(klab::Equals(xr(7, 2), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(xr(7, 3), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(xr(7, 4), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(xr(7, 5), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(xr(7, 6), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(xr(7, 7), 0.56978282473092301, precision))


        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                x(i, j) = static_cast<klab::DoubleReal>(i+1) * static_cast<klab::DoubleReal>(j+1);
        }

        filter.apply(x, xr);
        TEST_ASSERT(xr.n_rows==8 && xr.n_cols==8)
        TEST_ASSERT(klab::Equals(xr(0, 0), 0.36787944117144233, precision))
        TEST_ASSERT(klab::Equals(xr(0, 1), 0.91566672354322853, precision))
        TEST_ASSERT(klab::Equals(xr(0, 2), 1.6057842855569708, precision))
        TEST_ASSERT(klab::Equals(xr(0, 3), 2.351478692489386, precision))
        TEST_ASSERT(klab::Equals(xr(0, 4), 3.0326532985631669, precision))
        TEST_ASSERT(klab::Equals(xr(0, 5), 3.527218038734079, precision))
        TEST_ASSERT(klab::Equals(xr(0, 6), 3.746829999632932, precision))
        TEST_ASSERT(klab::Equals(xr(0, 7), 3.6626668941729141, precision))
        TEST_ASSERT(klab::Equals(xr(1, 0), 0.91566672354322853, precision))
        TEST_ASSERT(klab::Equals(xr(1, 1), 2.279131298923692, precision))
        TEST_ASSERT(klab::Equals(xr(1, 2), 3.9968616642209271, precision))
        TEST_ASSERT(klab::Equals(xr(1, 3), 5.8529250315731343, precision))
        TEST_ASSERT(klab::Equals(xr(1, 4), 7.5483960198900739, precision))
        TEST_ASSERT(klab::Equals(xr(1, 5), 8.7793875473597005, precision))
        TEST_ASSERT(klab::Equals(xr(1, 6), 9.3260105498488297, precision))
        TEST_ASSERT(klab::Equals(xr(1, 7), 9.1165251956947682, precision))
        TEST_ASSERT(klab::Equals(xr(2, 0), 1.6057842855569708, precision))
        TEST_ASSERT(klab::Equals(xr(2, 1), 3.9968616642209271, precision))
        TEST_ASSERT(klab::Equals(xr(2, 2), 7.0092070476426436, precision))
        TEST_ASSERT(klab::Equals(xr(2, 3), 10.264143927689069, precision))
        TEST_ASSERT(klab::Equals(xr(2, 4), 13.237453538768932, precision))
        TEST_ASSERT(klab::Equals(xr(2, 5), 15.396215891533606, precision))
        TEST_ASSERT(klab::Equals(xr(2, 6), 16.354816444499502, precision))
        TEST_ASSERT(klab::Equals(xr(2, 7), 15.987446656883709, precision))
        TEST_ASSERT(klab::Equals(xr(3, 0), 2.351478692489386, precision))
        TEST_ASSERT(klab::Equals(xr(3, 1), 5.8529250315731343, precision))
        TEST_ASSERT(klab::Equals(xr(3, 2), 10.264143927689069, precision))
        TEST_ASSERT(klab::Equals(xr(3, 3), 15.030609005015613, precision))
        TEST_ASSERT(klab::Equals(xr(3, 4), 19.384664689526883, precision))
        TEST_ASSERT(klab::Equals(xr(3, 5), 22.545913507523419, precision))
        TEST_ASSERT(klab::Equals(xr(3, 6), 23.94966916460783, precision))
        TEST_ASSERT(klab::Equals(xr(3, 7), 23.411700126292537, precision))
        TEST_ASSERT(klab::Equals(xr(4, 0), 3.0326532985631669, precision))
        TEST_ASSERT(klab::Equals(xr(4, 1), 7.5483960198900739, precision))
        TEST_ASSERT(klab::Equals(xr(4, 2), 13.237453538768932, precision))
        TEST_ASSERT(klab::Equals(xr(4, 3), 19.384664689526883, precision))
        TEST_ASSERT(klab::Equals(xr(4, 4), 25.0, precision))
        TEST_ASSERT(klab::Equals(xr(4, 5), 29.076997034290322, precision))
        TEST_ASSERT(klab::Equals(xr(4, 6), 30.88739159046084, precision))
        TEST_ASSERT(klab::Equals(xr(4, 7), 30.193584079560296, precision))
        TEST_ASSERT(klab::Equals(xr(5, 0), 3.527218038734079, precision))
        TEST_ASSERT(klab::Equals(xr(5, 1), 8.7793875473597005, precision))
        TEST_ASSERT(klab::Equals(xr(5, 2), 15.396215891533606, precision))
        TEST_ASSERT(klab::Equals(xr(5, 3), 22.545913507523419, precision))
        TEST_ASSERT(klab::Equals(xr(5, 4), 29.076997034290322, precision))
        TEST_ASSERT(klab::Equals(xr(5, 5), 33.818870261285127, precision))
        TEST_ASSERT(klab::Equals(xr(5, 6), 35.924503746911746, precision))
        TEST_ASSERT(klab::Equals(xr(5, 7), 35.117550189438802, precision))
        TEST_ASSERT(klab::Equals(xr(6, 0), 3.746829999632932, precision))
        TEST_ASSERT(klab::Equals(xr(6, 1), 9.3260105498488297, precision))
        TEST_ASSERT(klab::Equals(xr(6, 2), 16.354816444499502, precision))
        TEST_ASSERT(klab::Equals(xr(6, 3), 23.94966916460783, precision))
        TEST_ASSERT(klab::Equals(xr(6, 4), 30.88739159046084, precision))
        TEST_ASSERT(klab::Equals(xr(6, 5), 35.924503746911746, precision))
        TEST_ASSERT(klab::Equals(xr(6, 6), 38.161238370498836, precision))
        TEST_ASSERT(klab::Equals(xr(6, 7), 37.304042199395319, precision))
        TEST_ASSERT(klab::Equals(xr(7, 0), 3.6626668941729141, precision))
        TEST_ASSERT(klab::Equals(xr(7, 1), 9.1165251956947682, precision))
        TEST_ASSERT(klab::Equals(xr(7, 2), 15.987446656883709, precision))
        TEST_ASSERT(klab::Equals(xr(7, 3), 23.411700126292537, precision))
        TEST_ASSERT(klab::Equals(xr(7, 4), 30.193584079560296, precision))
        TEST_ASSERT(klab::Equals(xr(7, 5), 35.117550189438802, precision))
        TEST_ASSERT(klab::Equals(xr(7, 6), 37.304042199395319, precision))
        TEST_ASSERT(klab::Equals(xr(7, 7), 36.466100782779073, precision))


        // Limit cases.
        try                                 {TGaussianFilter2D<klab::DoubleReal> filter0(8, 8, 0.0, 4, 4); filter.apply(x, xr); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TGaussianFilter2D<klab::DoubleReal> filter00(0, 8, 1.0, 0, 4); 
        filter00.apply(x, xr);
        TEST_ASSERT(xr.n_rows==8 && xr.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(xr(i, j), 0.0));
        }

        TGaussianFilter2D<klab::DoubleReal> filter000(8, 0, 1.0, 4, 0); 
        filter000.apply(x, xr);
        TEST_ASSERT(xr.n_rows==8 && xr.n_cols==8)
        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                TEST_ASSERT(klab::Equals(xr(i, j), 0.0));
        }

        TGaussianFilter2D<klab::DoubleReal> filter0000(0, 0, 1.0, 0, 0); 
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
