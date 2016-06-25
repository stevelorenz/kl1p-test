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

#include "GaussianBlur2DOperatorUnitTest.h"
#include "../include/GaussianBlur2DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KGaussianBlur2DOperatorUnitTest::KGaussianBlur2DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testHeightWidthConstructor)  
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testHeightWidthSigmaConstructor)  
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testHeightWidthSigmaIcJcConstructor)  
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testWidth)
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testHeight)
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testSigma)
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testIc)
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testJc)
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testApply)
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testApply_Complex)
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KGaussianBlur2DOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KGaussianBlur2DOperatorUnitTest::~KGaussianBlur2DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testHeightWidthConstructor()
{
    try
    {
        TGaussianBlur2DOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.sigma()==1.0 && op.ic()==2 && op.jc()==4)

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.sigma()==1.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testHeightWidthSigmaConstructor()
{
    try
    {
        TGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 4.0);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.sigma()==4.0 && op.ic()==2 && op.jc()==4)

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.sigma()==4.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testHeightWidthSigmaIcJcConstructor()
{
    try
    {
        TGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.sigma()==4.0 && op.ic()==-1 && op.jc()==7)

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.sigma()==4.0 && op2.ic()==-1 && op2.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.sigma()==4.0 && op.ic()==-1 && op.jc()==7)

        TGaussianBlur2DOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==32 && opCopy.n()==32)
        TEST_ASSERT(opCopy.height()==4 && opCopy.width()==8 && opCopy.sigma()==4.0 && opCopy.ic()==-1 && opCopy.jc()==7)


        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.sigma()==4.0 && op2.ic()==-1 && op2.jc()==7)

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.m()==32 && op2Copy.n()==32)
        TEST_ASSERT(op2Copy.height()==4 && op2Copy.width()==8 && op2Copy.sigma()==4.0 && op2Copy.ic()==-1 && op2Copy.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testWidth()
{
    try
    {
        TGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.height()==4)

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.height()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testHeight()
{
    try
    {
        TGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.width()==8)

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testSigma()
{
    try
    {
        TGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.sigma()==4.0)

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.sigma()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testIc()
{
    try
    {
        TGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.ic()==-1)

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.ic()==-1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testJc()
{
    try
    {
        TGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op.jc()==7)

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 4.0, -1, 7);
        TEST_ASSERT(op2.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testApply()
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

        TGaussianBlur2DOperator<klab::DoubleReal> op(8, 8, 4.0, 4, 4);
        op.apply(x, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(ar(0, 0), 2.5286245080803447, precision))
        TEST_ASSERT(klab::Equals(ar(0, 1), 3.0109728573750965, precision))
        TEST_ASSERT(klab::Equals(ar(0, 2), 4.8531203252446558, precision))
        TEST_ASSERT(klab::Equals(ar(0, 3), 6.2997395453662595, precision))
        TEST_ASSERT(klab::Equals(ar(0, 4), 8.0117448344773621, precision))
        TEST_ASSERT(klab::Equals(ar(0, 5), 9.4583640545989685, precision))
        TEST_ASSERT(klab::Equals(ar(0, 6), 11.300511522468526, precision))
        TEST_ASSERT(klab::Equals(ar(0, 7), 11.78285987176328, precision))
        TEST_ASSERT(klab::Equals(ar(1, 0), 3.0109728573750969, precision))
        TEST_ASSERT(klab::Equals(ar(1, 1), 3.5853316769171677, precision))
        TEST_ASSERT(klab::Equals(ar(1, 2), 5.7788784084753324, precision))
        TEST_ASSERT(klab::Equals(ar(1, 3), 7.5014478104661482, precision))
        TEST_ASSERT(klab::Equals(ar(1, 4), 9.5400270620409522, precision))
        TEST_ASSERT(klab::Equals(ar(1, 5), 11.26259646403177, precision))
        TEST_ASSERT(klab::Equals(ar(1, 6), 13.456143195589934, precision))
        TEST_ASSERT(klab::Equals(ar(1, 7), 14.030502015132006, precision))
        TEST_ASSERT(klab::Equals(ar(2, 0), 4.8531203252446575, precision))
        TEST_ASSERT(klab::Equals(ar(2, 1), 5.7788784084753342, precision))
        TEST_ASSERT(klab::Equals(ar(2, 2), 9.3144619994146005, precision))
        TEST_ASSERT(klab::Equals(ar(2, 3), 12.090918969449888, precision))
        TEST_ASSERT(klab::Equals(ar(2, 4), 15.376724212166234, precision))
        TEST_ASSERT(klab::Equals(ar(2, 5), 18.153181182201521, precision))
        TEST_ASSERT(klab::Equals(ar(2, 6), 21.688764773140786, precision))
        TEST_ASSERT(klab::Equals(ar(2, 7), 22.614522856371465, precision))
        TEST_ASSERT(klab::Equals(ar(3, 0), 6.2997395453662683, precision))
        TEST_ASSERT(klab::Equals(ar(3, 1), 7.5014478104661517, precision))
        TEST_ASSERT(klab::Equals(ar(3, 2), 12.090918969449895, precision))
        TEST_ASSERT(klab::Equals(ar(3, 3), 15.6949828701852, precision))
        TEST_ASSERT(klab::Equals(ar(3, 4), 19.96022169359485, precision))
        TEST_ASSERT(klab::Equals(ar(3, 5), 23.564285594330158, precision))
        TEST_ASSERT(klab::Equals(ar(3, 6), 28.1537567533139, precision))
        TEST_ASSERT(klab::Equals(ar(3, 7), 29.355465018413788, precision))
        TEST_ASSERT(klab::Equals(ar(4, 0), 8.0117448344773656, precision))
        TEST_ASSERT(klab::Equals(ar(4, 1), 9.5400270620409557, precision))
        TEST_ASSERT(klab::Equals(ar(4, 2), 15.376724212166231, precision))
        TEST_ASSERT(klab::Equals(ar(4, 3), 19.960221693594839, precision))
        TEST_ASSERT(klab::Equals(ar(4, 4), 25.384573742625111, precision))
        TEST_ASSERT(klab::Equals(ar(4, 5), 29.968071224053723, precision))
        TEST_ASSERT(klab::Equals(ar(4, 6), 35.804768374178998, precision))
        TEST_ASSERT(klab::Equals(ar(4, 7), 37.333050601742592, precision))
        TEST_ASSERT(klab::Equals(ar(5, 0), 9.4583640545989667, precision))
        TEST_ASSERT(klab::Equals(ar(5, 1), 11.262596464031768, precision))
        TEST_ASSERT(klab::Equals(ar(5, 2), 18.153181182201521, precision))
        TEST_ASSERT(klab::Equals(ar(5, 3), 23.564285594330158, precision))
        TEST_ASSERT(klab::Equals(ar(5, 4), 29.968071224053723, precision))
        TEST_ASSERT(klab::Equals(ar(5, 5), 35.37917563618236, precision))
        TEST_ASSERT(klab::Equals(ar(5, 6), 42.269760354352115, precision))
        TEST_ASSERT(klab::Equals(ar(5, 7), 44.073992763784915, precision))
        TEST_ASSERT(klab::Equals(ar(6, 0), 11.300511522468526, precision))
        TEST_ASSERT(klab::Equals(ar(6, 1), 13.456143195589924, precision))
        TEST_ASSERT(klab::Equals(ar(6, 2), 21.688764773140779, precision))
        TEST_ASSERT(klab::Equals(ar(6, 3), 28.153756753313885, precision))
        TEST_ASSERT(klab::Equals(ar(6, 4), 35.804768374178998, precision))
        TEST_ASSERT(klab::Equals(ar(6, 5), 42.269760354352108, precision))
        TEST_ASSERT(klab::Equals(ar(6, 6), 50.50238193190296, precision))
        TEST_ASSERT(klab::Equals(ar(6, 7), 52.658013605024365, precision))
        TEST_ASSERT(klab::Equals(ar(7, 0), 11.782859871763284, precision))
        TEST_ASSERT(klab::Equals(ar(7, 1), 14.030502015132011, precision))
        TEST_ASSERT(klab::Equals(ar(7, 2), 22.614522856371465, precision))
        TEST_ASSERT(klab::Equals(ar(7, 3), 29.355465018413785, precision))
        TEST_ASSERT(klab::Equals(ar(7, 4), 37.333050601742592, precision))
        TEST_ASSERT(klab::Equals(ar(7, 5), 44.073992763784915, precision))
        TEST_ASSERT(klab::Equals(ar(7, 6), 52.658013605024365, precision))
        TEST_ASSERT(klab::Equals(ar(7, 7), 54.905655748393102, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testApply_Complex()
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

        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op(8, 8, 4.0, 4, 4);
        op.apply(x, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 0)), std::complex<klab::DoubleReal>(2.5286245080803447), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 1)), std::complex<klab::DoubleReal>(3.0109728573750965), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 2)), std::complex<klab::DoubleReal>(4.8531203252446558), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 3)), std::complex<klab::DoubleReal>(6.2997395453662595), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 4)), std::complex<klab::DoubleReal>(8.0117448344773621), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 5)), std::complex<klab::DoubleReal>(9.4583640545989685), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 6)), std::complex<klab::DoubleReal>(11.300511522468526), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 7)), std::complex<klab::DoubleReal>(11.78285987176328), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 0)), std::complex<klab::DoubleReal>(3.0109728573750969), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 1)), std::complex<klab::DoubleReal>(3.5853316769171677), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 2)), std::complex<klab::DoubleReal>(5.7788784084753324), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 3)), std::complex<klab::DoubleReal>(7.5014478104661482), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 4)), std::complex<klab::DoubleReal>(9.5400270620409522), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 5)), std::complex<klab::DoubleReal>(11.26259646403177), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 6)), std::complex<klab::DoubleReal>(13.456143195589934), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 7)), std::complex<klab::DoubleReal>(14.030502015132006), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 0)), std::complex<klab::DoubleReal>(4.8531203252446575), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 1)), std::complex<klab::DoubleReal>(5.7788784084753342), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 2)), std::complex<klab::DoubleReal>(9.3144619994146005), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 3)), std::complex<klab::DoubleReal>(12.090918969449888), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 4)), std::complex<klab::DoubleReal>(15.376724212166234), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 5)), std::complex<klab::DoubleReal>(18.153181182201521), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 6)), std::complex<klab::DoubleReal>(21.688764773140786), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 7)), std::complex<klab::DoubleReal>(22.614522856371465), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 0)), std::complex<klab::DoubleReal>(6.2997395453662683), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 1)), std::complex<klab::DoubleReal>(7.5014478104661517), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 2)), std::complex<klab::DoubleReal>(12.090918969449895), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 3)), std::complex<klab::DoubleReal>(15.6949828701852), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 4)), std::complex<klab::DoubleReal>(19.96022169359485), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 5)), std::complex<klab::DoubleReal>(23.564285594330158), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 6)), std::complex<klab::DoubleReal>(28.1537567533139), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 7)), std::complex<klab::DoubleReal>(29.355465018413788), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 0)), std::complex<klab::DoubleReal>(8.0117448344773656), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 1)), std::complex<klab::DoubleReal>(9.5400270620409557), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 2)), std::complex<klab::DoubleReal>(15.376724212166231), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 3)), std::complex<klab::DoubleReal>(19.960221693594839), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 4)), std::complex<klab::DoubleReal>(25.384573742625111), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 5)), std::complex<klab::DoubleReal>(29.968071224053723), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 6)), std::complex<klab::DoubleReal>(35.804768374178998), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 7)), std::complex<klab::DoubleReal>(37.333050601742592), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 0)), std::complex<klab::DoubleReal>(9.4583640545989667), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 1)), std::complex<klab::DoubleReal>(11.262596464031768), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 2)), std::complex<klab::DoubleReal>(18.153181182201521), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 3)), std::complex<klab::DoubleReal>(23.564285594330158), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 4)), std::complex<klab::DoubleReal>(29.968071224053723), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 5)), std::complex<klab::DoubleReal>(35.37917563618236), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 6)), std::complex<klab::DoubleReal>(42.269760354352115), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 7)), std::complex<klab::DoubleReal>(44.073992763784915), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 0)), std::complex<klab::DoubleReal>(11.300511522468526), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 1)), std::complex<klab::DoubleReal>(13.456143195589924), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 2)), std::complex<klab::DoubleReal>(21.688764773140779), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 3)), std::complex<klab::DoubleReal>(28.153756753313885), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 4)), std::complex<klab::DoubleReal>(35.804768374178998), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 5)), std::complex<klab::DoubleReal>(42.269760354352108), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 6)), std::complex<klab::DoubleReal>(50.50238193190296), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 7)), std::complex<klab::DoubleReal>(52.658013605024365), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 0)), std::complex<klab::DoubleReal>(11.782859871763284), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 1)), std::complex<klab::DoubleReal>(14.030502015132011), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 2)), std::complex<klab::DoubleReal>(22.614522856371465), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 3)), std::complex<klab::DoubleReal>(29.355465018413785), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 4)), std::complex<klab::DoubleReal>(37.333050601742592), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 5)), std::complex<klab::DoubleReal>(44.073992763784915), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 6)), std::complex<klab::DoubleReal>(52.658013605024365), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 7)), std::complex<klab::DoubleReal>(54.905655748393102), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur2DOperatorUnitTest::testApplyAdjoint()
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
        
        TGaussianBlur2DOperator<klab::DoubleReal> op(8, 8, 4.0, 4, 4);
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

void KGaussianBlur2DOperatorUnitTest::testApplyAdjoint_Complex()
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
        
        TGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op(8, 8, 4.0, 4, 4);
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

