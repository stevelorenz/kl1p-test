// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KL1p C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#include "Gaussian2DDiagonalOperatorUnitTest.h"
#include "../include/Gaussian2DDiagonalOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KGaussian2DDiagonalOperatorUnitTest::KGaussian2DDiagonalOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testHeightWidthConstructor)  
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testHeightWidthSigmaConstructor)  
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testHeightWidthSigmaIcJcConstructor)  
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testWidth)
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testHeight)
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testSigma)
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testIc)
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testJc)
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testApply)
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testApply_Complex)
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KGaussian2DDiagonalOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KGaussian2DDiagonalOperatorUnitTest::~KGaussian2DDiagonalOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testHeightWidthConstructor()
{
    try
    {
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.sigma()==1.0 && op.ic()==2 && op.jc()==4)

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.sigma()==1.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testHeightWidthSigmaConstructor()
{
    try
    {
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 4.0);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.sigma()==4.0 && op.ic()==2 && op.jc()==4)

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.sigma()==4.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testHeightWidthSigmaIcJcConstructor()
{
    try
    {
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.sigma()==4.0 && op.ic()==-1 && op.jc()==7)

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.sigma()==4.0 && op2.ic()==-1 && op2.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.sigma()==4.0 && op.ic()==-1 && op.jc()==7)

        TGaussian2DDiagonalOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==32 && opCopy.n()==32)
        TEST_ASSERT(opCopy.height()==4 && opCopy.width()==8 && opCopy.sigma()==4.0 && opCopy.ic()==-1 && opCopy.jc()==7)


        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.sigma()==4.0 && op2.ic()==-1 && op2.jc()==7)

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.m()==32 && op2Copy.n()==32)
        TEST_ASSERT(op2Copy.height()==4 && op2Copy.width()==8 && op2Copy.sigma()==4.0 && op2Copy.ic()==-1 && op2Copy.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testWidth()
{
    try
    {
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.height()==4)

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.height()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testHeight()
{
    try
    {
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.width()==8)

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testSigma()
{
    try
    {
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.sigma()==4.0)

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.sigma()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testIc()
{
    try
    {
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.ic()==-1)

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.ic()==-1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testJc()
{
    try
    {
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.jc()==7)

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> a(8, 8);
        arma::Mat<klab::DoubleReal> ar;

        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                a(i, j) = static_cast<klab::DoubleReal>(i+1) * static_cast<klab::DoubleReal>(j+1);
        }

        a.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(a);
        arma::Col<klab::DoubleReal> xr;

        TGaussian2DDiagonalOperator<klab::DoubleReal> op(8, 8, 4.0, 4, 4);
        op.apply(x, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(ar(0, 0), 0.36787944117144233, precision))
        TEST_ASSERT(klab::Equals(ar(0, 1), 0.91566672354322853, precision))
        TEST_ASSERT(klab::Equals(ar(0, 2), 1.6057842855569708, precision))
        TEST_ASSERT(klab::Equals(ar(0, 3), 2.351478692489386, precision))
        TEST_ASSERT(klab::Equals(ar(0, 4), 3.0326532985631669, precision))
        TEST_ASSERT(klab::Equals(ar(0, 5), 3.527218038734079, precision))
        TEST_ASSERT(klab::Equals(ar(0, 6), 3.746829999632932, precision))
        TEST_ASSERT(klab::Equals(ar(0, 7), 3.6626668941729141, precision))
        TEST_ASSERT(klab::Equals(ar(1, 0), 0.91566672354322853, precision))
        TEST_ASSERT(klab::Equals(ar(1, 1), 2.279131298923692, precision))
        TEST_ASSERT(klab::Equals(ar(1, 2), 3.9968616642209271, precision))
        TEST_ASSERT(klab::Equals(ar(1, 3), 5.8529250315731343, precision))
        TEST_ASSERT(klab::Equals(ar(1, 4), 7.5483960198900739, precision))
        TEST_ASSERT(klab::Equals(ar(1, 5), 8.7793875473597005, precision))
        TEST_ASSERT(klab::Equals(ar(1, 6), 9.3260105498488297, precision))
        TEST_ASSERT(klab::Equals(ar(1, 7), 9.1165251956947682, precision))
        TEST_ASSERT(klab::Equals(ar(2, 0), 1.6057842855569708, precision))
        TEST_ASSERT(klab::Equals(ar(2, 1), 3.9968616642209271, precision))
        TEST_ASSERT(klab::Equals(ar(2, 2), 7.0092070476426436, precision))
        TEST_ASSERT(klab::Equals(ar(2, 3), 10.264143927689069, precision))
        TEST_ASSERT(klab::Equals(ar(2, 4), 13.237453538768932, precision))
        TEST_ASSERT(klab::Equals(ar(2, 5), 15.396215891533606, precision))
        TEST_ASSERT(klab::Equals(ar(2, 6), 16.354816444499502, precision))
        TEST_ASSERT(klab::Equals(ar(2, 7), 15.987446656883709, precision))
        TEST_ASSERT(klab::Equals(ar(3, 0), 2.351478692489386, precision))
        TEST_ASSERT(klab::Equals(ar(3, 1), 5.8529250315731343, precision))
        TEST_ASSERT(klab::Equals(ar(3, 2), 10.264143927689069, precision))
        TEST_ASSERT(klab::Equals(ar(3, 3), 15.030609005015613, precision))
        TEST_ASSERT(klab::Equals(ar(3, 4), 19.384664689526883, precision))
        TEST_ASSERT(klab::Equals(ar(3, 5), 22.545913507523419, precision))
        TEST_ASSERT(klab::Equals(ar(3, 6), 23.94966916460783, precision))
        TEST_ASSERT(klab::Equals(ar(3, 7), 23.411700126292537, precision))
        TEST_ASSERT(klab::Equals(ar(4, 0), 3.0326532985631669, precision))
        TEST_ASSERT(klab::Equals(ar(4, 1), 7.5483960198900739, precision))
        TEST_ASSERT(klab::Equals(ar(4, 2), 13.237453538768932, precision))
        TEST_ASSERT(klab::Equals(ar(4, 3), 19.384664689526883, precision))
        TEST_ASSERT(klab::Equals(ar(4, 4), 25.0, precision))
        TEST_ASSERT(klab::Equals(ar(4, 5), 29.076997034290322, precision))
        TEST_ASSERT(klab::Equals(ar(4, 6), 30.88739159046084, precision))
        TEST_ASSERT(klab::Equals(ar(4, 7), 30.193584079560296, precision))
        TEST_ASSERT(klab::Equals(ar(5, 0), 3.527218038734079, precision))
        TEST_ASSERT(klab::Equals(ar(5, 1), 8.7793875473597005, precision))
        TEST_ASSERT(klab::Equals(ar(5, 2), 15.396215891533606, precision))
        TEST_ASSERT(klab::Equals(ar(5, 3), 22.545913507523419, precision))
        TEST_ASSERT(klab::Equals(ar(5, 4), 29.076997034290322, precision))
        TEST_ASSERT(klab::Equals(ar(5, 5), 33.818870261285127, precision))
        TEST_ASSERT(klab::Equals(ar(5, 6), 35.924503746911746, precision))
        TEST_ASSERT(klab::Equals(ar(5, 7), 35.117550189438802, precision))
        TEST_ASSERT(klab::Equals(ar(6, 0), 3.746829999632932, precision))
        TEST_ASSERT(klab::Equals(ar(6, 1), 9.3260105498488297, precision))
        TEST_ASSERT(klab::Equals(ar(6, 2), 16.354816444499502, precision))
        TEST_ASSERT(klab::Equals(ar(6, 3), 23.94966916460783, precision))
        TEST_ASSERT(klab::Equals(ar(6, 4), 30.88739159046084, precision))
        TEST_ASSERT(klab::Equals(ar(6, 5), 35.924503746911746, precision))
        TEST_ASSERT(klab::Equals(ar(6, 6), 38.161238370498836, precision))
        TEST_ASSERT(klab::Equals(ar(6, 7), 37.304042199395319, precision))
        TEST_ASSERT(klab::Equals(ar(7, 0), 3.6626668941729141, precision))
        TEST_ASSERT(klab::Equals(ar(7, 1), 9.1165251956947682, precision))
        TEST_ASSERT(klab::Equals(ar(7, 2), 15.987446656883709, precision))
        TEST_ASSERT(klab::Equals(ar(7, 3), 23.411700126292537, precision))
        TEST_ASSERT(klab::Equals(ar(7, 4), 30.193584079560296, precision))
        TEST_ASSERT(klab::Equals(ar(7, 5), 35.117550189438802, precision))
        TEST_ASSERT(klab::Equals(ar(7, 6), 37.304042199395319, precision))
        TEST_ASSERT(klab::Equals(ar(7, 7), 36.466100782779073, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > a(8, 8);
        arma::Mat<std::complex<klab::DoubleReal> > ar;

        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                a(i, j) = static_cast<klab::DoubleReal>(i+1) * static_cast<klab::DoubleReal>(j+1);
        }

        a.reshape(64, 1);
        arma::Col<std::complex<klab::DoubleReal> > x(a);
        arma::Col<std::complex<klab::DoubleReal> > xr;

        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op(8, 8, 4.0, 4, 4);
        op.apply(x, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 0)), std::complex<klab::DoubleReal>(0.36787944117144233), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 1)), std::complex<klab::DoubleReal>(0.91566672354322853), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 2)), std::complex<klab::DoubleReal>(1.6057842855569708), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 3)), std::complex<klab::DoubleReal>(2.351478692489386), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 4)), std::complex<klab::DoubleReal>(3.0326532985631669), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 5)), std::complex<klab::DoubleReal>(3.527218038734079), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 6)), std::complex<klab::DoubleReal>(3.746829999632932), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 7)), std::complex<klab::DoubleReal>(3.6626668941729141), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 0)), std::complex<klab::DoubleReal>(0.91566672354322853), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 1)), std::complex<klab::DoubleReal>(2.279131298923692), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 2)), std::complex<klab::DoubleReal>(3.9968616642209271), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 3)), std::complex<klab::DoubleReal>(5.8529250315731343), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 4)), std::complex<klab::DoubleReal>(7.5483960198900739), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 5)), std::complex<klab::DoubleReal>(8.7793875473597005), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 6)), std::complex<klab::DoubleReal>(9.3260105498488297), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 7)), std::complex<klab::DoubleReal>(9.1165251956947682), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 0)), std::complex<klab::DoubleReal>(1.6057842855569708), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 1)), std::complex<klab::DoubleReal>(3.9968616642209271), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 2)), std::complex<klab::DoubleReal>(7.0092070476426436), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 3)), std::complex<klab::DoubleReal>(10.264143927689069), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 4)), std::complex<klab::DoubleReal>(13.237453538768932), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 5)), std::complex<klab::DoubleReal>(15.396215891533606), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 6)), std::complex<klab::DoubleReal>(16.354816444499502), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 7)), std::complex<klab::DoubleReal>(15.987446656883709), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 0)), std::complex<klab::DoubleReal>(2.351478692489386), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 1)), std::complex<klab::DoubleReal>(5.8529250315731343), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 2)), std::complex<klab::DoubleReal>(10.264143927689069), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 3)), std::complex<klab::DoubleReal>(15.030609005015613), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 4)), std::complex<klab::DoubleReal>(19.384664689526883), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 5)), std::complex<klab::DoubleReal>(22.545913507523419), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 6)), std::complex<klab::DoubleReal>(23.94966916460783), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 7)), std::complex<klab::DoubleReal>(23.411700126292537), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 0)), std::complex<klab::DoubleReal>(3.0326532985631669), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 1)), std::complex<klab::DoubleReal>(7.5483960198900739), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 2)), std::complex<klab::DoubleReal>(13.237453538768932), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 3)), std::complex<klab::DoubleReal>(19.384664689526883), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 4)), std::complex<klab::DoubleReal>(25.0), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 5)), std::complex<klab::DoubleReal>(29.076997034290322), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 6)), std::complex<klab::DoubleReal>(30.88739159046084), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 7)), std::complex<klab::DoubleReal>(30.193584079560296), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 0)), std::complex<klab::DoubleReal>(3.527218038734079), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 1)), std::complex<klab::DoubleReal>(8.7793875473597005), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 2)), std::complex<klab::DoubleReal>(15.396215891533606), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 3)), std::complex<klab::DoubleReal>(22.545913507523419), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 4)), std::complex<klab::DoubleReal>(29.076997034290322), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 5)), std::complex<klab::DoubleReal>(33.818870261285127), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 6)), std::complex<klab::DoubleReal>(35.924503746911746), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 7)), std::complex<klab::DoubleReal>(35.117550189438802), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 0)), std::complex<klab::DoubleReal>(3.746829999632932), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 1)), std::complex<klab::DoubleReal>(9.3260105498488297), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 2)), std::complex<klab::DoubleReal>(16.354816444499502), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 3)), std::complex<klab::DoubleReal>(23.94966916460783), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 4)), std::complex<klab::DoubleReal>(30.88739159046084), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 5)), std::complex<klab::DoubleReal>(35.924503746911746), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 6)), std::complex<klab::DoubleReal>(38.161238370498836), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 7)), std::complex<klab::DoubleReal>(37.304042199395319), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 0)), std::complex<klab::DoubleReal>(3.6626668941729141), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 1)), std::complex<klab::DoubleReal>(9.1165251956947682), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 2)), std::complex<klab::DoubleReal>(15.987446656883709), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 3)), std::complex<klab::DoubleReal>(23.411700126292537), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 4)), std::complex<klab::DoubleReal>(30.193584079560296), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 5)), std::complex<klab::DoubleReal>(35.117550189438802), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 6)), std::complex<klab::DoubleReal>(37.304042199395319), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 7)), std::complex<klab::DoubleReal>(36.466100782779073), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> a(8, 8);
        arma::Mat<klab::DoubleReal> at;
        arma::Mat<klab::DoubleReal> ar;

        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                a(i, j) = static_cast<klab::DoubleReal>(i+1) * static_cast<klab::DoubleReal>(j+1);
        }
        
        TGaussian2DDiagonalOperator<klab::DoubleReal> op(8, 8, 4.0, 4, 4);
        arma::Mat<klab::DoubleReal> opMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            op.apply(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                opMatrix(i, j) = col[i];
        }       

        a.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(a);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(opMatrix) * y;
        at = xt;
        at.reshape(8, 8);

        op.applyAdjoint(y, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(ar(0, 0), at(0, 0), precision))
        TEST_ASSERT(klab::Equals(ar(0, 1), at(0, 1), precision))
        TEST_ASSERT(klab::Equals(ar(0, 2), at(0, 2), precision))
        TEST_ASSERT(klab::Equals(ar(0, 3), at(0, 3), precision))
        TEST_ASSERT(klab::Equals(ar(0, 4), at(0, 4), precision))
        TEST_ASSERT(klab::Equals(ar(0, 5), at(0, 5), precision))
        TEST_ASSERT(klab::Equals(ar(0, 6), at(0, 6), precision))
        TEST_ASSERT(klab::Equals(ar(0, 7), at(0, 7), precision))
        TEST_ASSERT(klab::Equals(ar(1, 0), at(1, 0), precision))
        TEST_ASSERT(klab::Equals(ar(1, 1), at(1, 1), precision))
        TEST_ASSERT(klab::Equals(ar(1, 2), at(1, 2), precision))
        TEST_ASSERT(klab::Equals(ar(1, 3), at(1, 3), precision))
        TEST_ASSERT(klab::Equals(ar(1, 4), at(1, 4), precision))
        TEST_ASSERT(klab::Equals(ar(1, 5), at(1, 5), precision))
        TEST_ASSERT(klab::Equals(ar(1, 6), at(1, 6), precision))
        TEST_ASSERT(klab::Equals(ar(1, 7), at(1, 7), precision))
        TEST_ASSERT(klab::Equals(ar(2, 0), at(2, 0), precision))
        TEST_ASSERT(klab::Equals(ar(2, 1), at(2, 1), precision))
        TEST_ASSERT(klab::Equals(ar(2, 2), at(2, 2), precision))
        TEST_ASSERT(klab::Equals(ar(2, 3), at(2, 3), precision))
        TEST_ASSERT(klab::Equals(ar(2, 4), at(2, 4), precision))
        TEST_ASSERT(klab::Equals(ar(2, 5), at(2, 5), precision))
        TEST_ASSERT(klab::Equals(ar(2, 6), at(2, 6), precision))
        TEST_ASSERT(klab::Equals(ar(2, 7), at(2, 7), precision))
        TEST_ASSERT(klab::Equals(ar(3, 0), at(3, 0), precision))
        TEST_ASSERT(klab::Equals(ar(3, 1), at(3, 1), precision))
        TEST_ASSERT(klab::Equals(ar(3, 2), at(3, 2), precision))
        TEST_ASSERT(klab::Equals(ar(3, 3), at(3, 3), precision))
        TEST_ASSERT(klab::Equals(ar(3, 4), at(3, 4), precision))
        TEST_ASSERT(klab::Equals(ar(3, 5), at(3, 5), precision))
        TEST_ASSERT(klab::Equals(ar(3, 6), at(3, 6), precision))
        TEST_ASSERT(klab::Equals(ar(3, 7), at(3, 7), precision))
        TEST_ASSERT(klab::Equals(ar(4, 0), at(4, 0), precision))
        TEST_ASSERT(klab::Equals(ar(4, 1), at(4, 1), precision))
        TEST_ASSERT(klab::Equals(ar(4, 2), at(4, 2), precision))
        TEST_ASSERT(klab::Equals(ar(4, 3), at(4, 3), precision))
        TEST_ASSERT(klab::Equals(ar(4, 4), at(4, 4), precision))
        TEST_ASSERT(klab::Equals(ar(4, 5), at(4, 5), precision))
        TEST_ASSERT(klab::Equals(ar(4, 6), at(4, 6), precision))
        TEST_ASSERT(klab::Equals(ar(4, 7), at(4, 7), precision))
        TEST_ASSERT(klab::Equals(ar(5, 0), at(5, 0), precision))
        TEST_ASSERT(klab::Equals(ar(5, 1), at(5, 1), precision))
        TEST_ASSERT(klab::Equals(ar(5, 2), at(5, 2), precision))
        TEST_ASSERT(klab::Equals(ar(5, 3), at(5, 3), precision))
        TEST_ASSERT(klab::Equals(ar(5, 4), at(5, 4), precision))
        TEST_ASSERT(klab::Equals(ar(5, 5), at(5, 5), precision))
        TEST_ASSERT(klab::Equals(ar(5, 6), at(5, 6), precision))
        TEST_ASSERT(klab::Equals(ar(5, 7), at(5, 7), precision))
        TEST_ASSERT(klab::Equals(ar(6, 0), at(6, 0), precision))
        TEST_ASSERT(klab::Equals(ar(6, 1), at(6, 1), precision))
        TEST_ASSERT(klab::Equals(ar(6, 2), at(6, 2), precision))
        TEST_ASSERT(klab::Equals(ar(6, 3), at(6, 3), precision))
        TEST_ASSERT(klab::Equals(ar(6, 4), at(6, 4), precision))
        TEST_ASSERT(klab::Equals(ar(6, 5), at(6, 5), precision))
        TEST_ASSERT(klab::Equals(ar(6, 6), at(6, 6), precision))
        TEST_ASSERT(klab::Equals(ar(6, 7), at(6, 7), precision))
        TEST_ASSERT(klab::Equals(ar(7, 0), at(7, 0), precision))
        TEST_ASSERT(klab::Equals(ar(7, 1), at(7, 1), precision))
        TEST_ASSERT(klab::Equals(ar(7, 2), at(7, 2), precision))
        TEST_ASSERT(klab::Equals(ar(7, 3), at(7, 3), precision))
        TEST_ASSERT(klab::Equals(ar(7, 4), at(7, 4), precision))
        TEST_ASSERT(klab::Equals(ar(7, 5), at(7, 5), precision))
        TEST_ASSERT(klab::Equals(ar(7, 6), at(7, 6), precision))
        TEST_ASSERT(klab::Equals(ar(7, 7), at(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian2DDiagonalOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > a(8, 8);
        arma::Mat<std::complex<klab::DoubleReal> > at;
        arma::Mat<std::complex<klab::DoubleReal> > ar;

        for(klab::UInt32 i=0; i<8; ++i)
        {
            for(klab::UInt32 j=0; j<8; ++j)
                a(i, j) = static_cast<klab::DoubleReal>(i+1) * static_cast<klab::DoubleReal>(j+1);
        }
        
        TGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op(8, 8, 4.0, 4, 4);
        arma::Mat<std::complex<klab::DoubleReal> > opMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(64);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(0.0);
            base[j] = 1.0;

            op.apply(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                opMatrix(i, j) = col[i];
        }       

        a.reshape(64, 1);
        arma::Col<std::complex<klab::DoubleReal> > x(a);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        op.apply(x, y);
        arma::Col<std::complex<klab::DoubleReal> > xt = arma::trans(opMatrix) * y;
        at = xt;
        at.reshape(8, 8);

        op.applyAdjoint(y, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(ar(0, 0), at(0, 0), precision))
        TEST_ASSERT(klab::Equals(ar(0, 1), at(0, 1), precision))
        TEST_ASSERT(klab::Equals(ar(0, 2), at(0, 2), precision))
        TEST_ASSERT(klab::Equals(ar(0, 3), at(0, 3), precision))
        TEST_ASSERT(klab::Equals(ar(0, 4), at(0, 4), precision))
        TEST_ASSERT(klab::Equals(ar(0, 5), at(0, 5), precision))
        TEST_ASSERT(klab::Equals(ar(0, 6), at(0, 6), precision))
        TEST_ASSERT(klab::Equals(ar(0, 7), at(0, 7), precision))
        TEST_ASSERT(klab::Equals(ar(1, 0), at(1, 0), precision))
        TEST_ASSERT(klab::Equals(ar(1, 1), at(1, 1), precision))
        TEST_ASSERT(klab::Equals(ar(1, 2), at(1, 2), precision))
        TEST_ASSERT(klab::Equals(ar(1, 3), at(1, 3), precision))
        TEST_ASSERT(klab::Equals(ar(1, 4), at(1, 4), precision))
        TEST_ASSERT(klab::Equals(ar(1, 5), at(1, 5), precision))
        TEST_ASSERT(klab::Equals(ar(1, 6), at(1, 6), precision))
        TEST_ASSERT(klab::Equals(ar(1, 7), at(1, 7), precision))
        TEST_ASSERT(klab::Equals(ar(2, 0), at(2, 0), precision))
        TEST_ASSERT(klab::Equals(ar(2, 1), at(2, 1), precision))
        TEST_ASSERT(klab::Equals(ar(2, 2), at(2, 2), precision))
        TEST_ASSERT(klab::Equals(ar(2, 3), at(2, 3), precision))
        TEST_ASSERT(klab::Equals(ar(2, 4), at(2, 4), precision))
        TEST_ASSERT(klab::Equals(ar(2, 5), at(2, 5), precision))
        TEST_ASSERT(klab::Equals(ar(2, 6), at(2, 6), precision))
        TEST_ASSERT(klab::Equals(ar(2, 7), at(2, 7), precision))
        TEST_ASSERT(klab::Equals(ar(3, 0), at(3, 0), precision))
        TEST_ASSERT(klab::Equals(ar(3, 1), at(3, 1), precision))
        TEST_ASSERT(klab::Equals(ar(3, 2), at(3, 2), precision))
        TEST_ASSERT(klab::Equals(ar(3, 3), at(3, 3), precision))
        TEST_ASSERT(klab::Equals(ar(3, 4), at(3, 4), precision))
        TEST_ASSERT(klab::Equals(ar(3, 5), at(3, 5), precision))
        TEST_ASSERT(klab::Equals(ar(3, 6), at(3, 6), precision))
        TEST_ASSERT(klab::Equals(ar(3, 7), at(3, 7), precision))
        TEST_ASSERT(klab::Equals(ar(4, 0), at(4, 0), precision))
        TEST_ASSERT(klab::Equals(ar(4, 1), at(4, 1), precision))
        TEST_ASSERT(klab::Equals(ar(4, 2), at(4, 2), precision))
        TEST_ASSERT(klab::Equals(ar(4, 3), at(4, 3), precision))
        TEST_ASSERT(klab::Equals(ar(4, 4), at(4, 4), precision))
        TEST_ASSERT(klab::Equals(ar(4, 5), at(4, 5), precision))
        TEST_ASSERT(klab::Equals(ar(4, 6), at(4, 6), precision))
        TEST_ASSERT(klab::Equals(ar(4, 7), at(4, 7), precision))
        TEST_ASSERT(klab::Equals(ar(5, 0), at(5, 0), precision))
        TEST_ASSERT(klab::Equals(ar(5, 1), at(5, 1), precision))
        TEST_ASSERT(klab::Equals(ar(5, 2), at(5, 2), precision))
        TEST_ASSERT(klab::Equals(ar(5, 3), at(5, 3), precision))
        TEST_ASSERT(klab::Equals(ar(5, 4), at(5, 4), precision))
        TEST_ASSERT(klab::Equals(ar(5, 5), at(5, 5), precision))
        TEST_ASSERT(klab::Equals(ar(5, 6), at(5, 6), precision))
        TEST_ASSERT(klab::Equals(ar(5, 7), at(5, 7), precision))
        TEST_ASSERT(klab::Equals(ar(6, 0), at(6, 0), precision))
        TEST_ASSERT(klab::Equals(ar(6, 1), at(6, 1), precision))
        TEST_ASSERT(klab::Equals(ar(6, 2), at(6, 2), precision))
        TEST_ASSERT(klab::Equals(ar(6, 3), at(6, 3), precision))
        TEST_ASSERT(klab::Equals(ar(6, 4), at(6, 4), precision))
        TEST_ASSERT(klab::Equals(ar(6, 5), at(6, 5), precision))
        TEST_ASSERT(klab::Equals(ar(6, 6), at(6, 6), precision))
        TEST_ASSERT(klab::Equals(ar(6, 7), at(6, 7), precision))
        TEST_ASSERT(klab::Equals(ar(7, 0), at(7, 0), precision))
        TEST_ASSERT(klab::Equals(ar(7, 1), at(7, 1), precision))
        TEST_ASSERT(klab::Equals(ar(7, 2), at(7, 2), precision))
        TEST_ASSERT(klab::Equals(ar(7, 3), at(7, 3), precision))
        TEST_ASSERT(klab::Equals(ar(7, 4), at(7, 4), precision))
        TEST_ASSERT(klab::Equals(ar(7, 5), at(7, 5), precision))
        TEST_ASSERT(klab::Equals(ar(7, 6), at(7, 6), precision))
        TEST_ASSERT(klab::Equals(ar(7, 7), at(7, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

