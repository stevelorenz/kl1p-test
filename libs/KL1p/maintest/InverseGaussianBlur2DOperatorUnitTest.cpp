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

#include "InverseGaussianBlur2DOperatorUnitTest.h"
#include "../include/InverseGaussianBlur2DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KInverseGaussianBlur2DOperatorUnitTest::KInverseGaussianBlur2DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testHeightWidthConstructor)  
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testHeightWidthGammaConstructor)  
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testHeightWidthGammaSigmaConstructor)  
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testHeightWidthGammaSigmaIcJcConstructor)  
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testWidth)
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testHeight)    
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testGamma)
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testSigma)
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testIc)
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testJc)
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testApply)
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testApply_Complex)
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KInverseGaussianBlur2DOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KInverseGaussianBlur2DOperatorUnitTest::~KInverseGaussianBlur2DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testHeightWidthConstructor()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.0 && op.sigma()==1.0 && op.ic()==2 && op.jc()==4)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.0 && op2.sigma()==1.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testHeightWidthGammaConstructor()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.4 && op.sigma()==1.0 && op.ic()==2 && op.jc()==4)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.4 && op2.sigma()==1.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testHeightWidthGammaSigmaConstructor()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.4 && op.sigma()==4.0 && op.ic()==2 && op.jc()==4)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testHeightWidthGammaSigmaIcJcConstructor()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.4 && op.sigma()==4.0 && op.ic()==-1 && op.jc()==7)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.ic()==-1 && op2.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.4 && op.sigma()==4.0 && op.ic()==-1 && op.jc()==7)

        TInverseGaussianBlur2DOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==32 && opCopy.n()==32)
        TEST_ASSERT(opCopy.height()==4 && opCopy.width()==8 && opCopy.gamma()==0.4 && opCopy.sigma()==4.0 && opCopy.ic()==-1 && opCopy.jc()==7)


        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.ic()==-1 && op2.jc()==7)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.m()==32 && op2Copy.n()==32)
        TEST_ASSERT(op2Copy.height()==4 && op2Copy.width()==8 && op2Copy.gamma()==0.4 && op2Copy.sigma()==4.0 && op2Copy.ic()==-1 && op2Copy.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testWidth()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.width()==8)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testHeight()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.height()==4)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.height()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testGamma()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.gamma()==0.4)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.gamma()==0.4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testSigma()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.sigma()==4.0)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.sigma()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testIc()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.ic()==-1)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.ic()==-1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testJc()
{
    try
    {
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.jc()==7)

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testApply()
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

        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(8, 8, 0.4, 4.0, 4, 4);
        op.apply(x, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(ar(0, 0), 0.092965653927427061, precision))
        TEST_ASSERT(klab::Equals(ar(0, 1), 1.2357772207267281, precision))
        TEST_ASSERT(klab::Equals(ar(0, 2), 1.6639368613855119, precision))
        TEST_ASSERT(klab::Equals(ar(0, 3), 2.3044733853613275, precision))
        TEST_ASSERT(klab::Equals(ar(0, 4), 2.8140305304460789, precision))
        TEST_ASSERT(klab::Equals(ar(0, 5), 3.4545670544218954, precision))
        TEST_ASSERT(klab::Equals(ar(0, 6), 3.8827266950806791, precision))
        TEST_ASSERT(klab::Equals(ar(0, 7), 5.0255382618799809, precision))
        TEST_ASSERT(klab::Equals(ar(1, 0), 1.2357772207267286, precision))
        TEST_ASSERT(klab::Equals(ar(1, 1), 2.8684085659588128, precision))
        TEST_ASSERT(klab::Equals(ar(1, 2), 4.316858194258538, precision))
        TEST_ASSERT(klab::Equals(ar(1, 3), 5.7360770430166497, precision))
        TEST_ASSERT(klab::Equals(ar(1, 4), 7.1879751350030219, precision))
        TEST_ASSERT(klab::Equals(ar(1, 5), 8.6071939837611335, precision))
        TEST_ASSERT(klab::Equals(ar(1, 6), 10.055643612060857, precision))
        TEST_ASSERT(klab::Equals(ar(1, 7), 11.688274957292947, precision))
        TEST_ASSERT(klab::Equals(ar(2, 0), 1.663936861385511, precision))
        TEST_ASSERT(klab::Equals(ar(2, 1), 4.3168581942585353, precision))
        TEST_ASSERT(klab::Equals(ar(2, 2), 6.4287301502115621, precision))
        TEST_ASSERT(klab::Equals(ar(2, 3), 8.5720330236895972, precision))
        TEST_ASSERT(klab::Equals(ar(2, 4), 10.71863417401195, precision))
        TEST_ASSERT(klab::Equals(ar(2, 5), 12.861937047489988, precision))
        TEST_ASSERT(klab::Equals(ar(2, 6), 14.97380900344301, precision))
        TEST_ASSERT(klab::Equals(ar(2, 7), 17.626730336316037, precision))
        TEST_ASSERT(klab::Equals(ar(3, 0), 2.3044733853613275, precision))
        TEST_ASSERT(klab::Equals(ar(3, 1), 5.7360770430166497, precision))
        TEST_ASSERT(klab::Equals(ar(3, 2), 8.5720330236896007, precision))
        TEST_ASSERT(klab::Equals(ar(3, 3), 11.41692931132749, precision))
        TEST_ASSERT(klab::Equals(ar(3, 4), 14.28598383697738, precision))
        TEST_ASSERT(klab::Equals(ar(3, 5), 17.130880124615274, precision))
        TEST_ASSERT(klab::Equals(ar(3, 6), 19.966836105288223, precision))
        TEST_ASSERT(klab::Equals(ar(3, 7), 23.39843976294355, precision))
        TEST_ASSERT(klab::Equals(ar(4, 0), 2.8140305304460771, precision))
        TEST_ASSERT(klab::Equals(ar(4, 1), 7.1879751350030183, precision))
        TEST_ASSERT(klab::Equals(ar(4, 2), 10.718634174011953, precision))
        TEST_ASSERT(klab::Equals(ar(4, 3), 14.285983836977376, precision))
        TEST_ASSERT(klab::Equals(ar(4, 4), 17.868245871860609, precision))
        TEST_ASSERT(klab::Equals(ar(4, 5), 21.435595534826039, precision))
        TEST_ASSERT(klab::Equals(ar(4, 6), 24.966254573834966, precision))
        TEST_ASSERT(klab::Equals(ar(4, 7), 29.340199178391909, precision))
        TEST_ASSERT(klab::Equals(ar(5, 0), 3.4545670544218936, precision))
        TEST_ASSERT(klab::Equals(ar(5, 1), 8.6071939837611318, precision))
        TEST_ASSERT(klab::Equals(ar(5, 2), 12.861937047489985, precision))
        TEST_ASSERT(klab::Equals(ar(5, 3), 17.130880124615267, precision))
        TEST_ASSERT(klab::Equals(ar(5, 4), 21.435595534826039, precision))
        TEST_ASSERT(klab::Equals(ar(5, 5), 25.704538611951325, precision))
        TEST_ASSERT(klab::Equals(ar(5, 6), 29.959281675680177, precision))
        TEST_ASSERT(klab::Equals(ar(5, 7), 35.111908605019416, precision))
        TEST_ASSERT(klab::Equals(ar(6, 0), 3.8827266950806774, precision))
        TEST_ASSERT(klab::Equals(ar(6, 1), 10.055643612060855, precision))
        TEST_ASSERT(klab::Equals(ar(6, 2), 14.97380900344301, precision))
        TEST_ASSERT(klab::Equals(ar(6, 3), 19.966836105288216, precision))
        TEST_ASSERT(klab::Equals(ar(6, 4), 24.966254573834966, precision))
        TEST_ASSERT(klab::Equals(ar(6, 5), 29.959281675680174, precision))
        TEST_ASSERT(klab::Equals(ar(6, 6), 34.877447067062327, precision))
        TEST_ASSERT(klab::Equals(ar(6, 7), 41.050363984042505, precision))
        TEST_ASSERT(klab::Equals(ar(7, 0), 5.0255382618799835, precision))
        TEST_ASSERT(klab::Equals(ar(7, 1), 11.688274957292943, precision))
        TEST_ASSERT(klab::Equals(ar(7, 2), 17.62673033631604, precision))
        TEST_ASSERT(klab::Equals(ar(7, 3), 23.398439762943543, precision))
        TEST_ASSERT(klab::Equals(ar(7, 4), 29.340199178391916, precision))
        TEST_ASSERT(klab::Equals(ar(7, 5), 35.111908605019423, precision))
        TEST_ASSERT(klab::Equals(ar(7, 6), 41.050363984042505, precision))
        TEST_ASSERT(klab::Equals(ar(7, 7), 47.713100679455479, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testApply_Complex()
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

        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op(8, 8, 0.4, 4.0, 4, 4);
        op.apply(x, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 0)), std::complex<klab::DoubleReal>(0.092965653927427061), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 1)), std::complex<klab::DoubleReal>(1.2357772207267281), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 2)), std::complex<klab::DoubleReal>(1.6639368613855119), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 3)), std::complex<klab::DoubleReal>(2.3044733853613275), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 4)), std::complex<klab::DoubleReal>(2.8140305304460789), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 5)), std::complex<klab::DoubleReal>(3.4545670544218954), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 6)), std::complex<klab::DoubleReal>(3.8827266950806791), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 7)), std::complex<klab::DoubleReal>(5.0255382618799809), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 0)), std::complex<klab::DoubleReal>(1.2357772207267286), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 1)), std::complex<klab::DoubleReal>(2.8684085659588128), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 2)), std::complex<klab::DoubleReal>(4.316858194258538), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 3)), std::complex<klab::DoubleReal>(5.7360770430166497), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 4)), std::complex<klab::DoubleReal>(7.1879751350030219), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 5)), std::complex<klab::DoubleReal>(8.6071939837611335), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 6)), std::complex<klab::DoubleReal>(10.055643612060857), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 7)), std::complex<klab::DoubleReal>(11.688274957292947), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 0)), std::complex<klab::DoubleReal>(1.663936861385511), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 1)), std::complex<klab::DoubleReal>(4.3168581942585353), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 2)), std::complex<klab::DoubleReal>(6.4287301502115621), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 3)), std::complex<klab::DoubleReal>(8.5720330236895972), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 4)), std::complex<klab::DoubleReal>(10.71863417401195), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 5)), std::complex<klab::DoubleReal>(12.861937047489988), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 6)), std::complex<klab::DoubleReal>(14.97380900344301), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 7)), std::complex<klab::DoubleReal>(17.626730336316037), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 0)), std::complex<klab::DoubleReal>(2.3044733853613275), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 1)), std::complex<klab::DoubleReal>(5.7360770430166497), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 2)), std::complex<klab::DoubleReal>(8.5720330236896007), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 3)), std::complex<klab::DoubleReal>(11.41692931132749), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 4)), std::complex<klab::DoubleReal>(14.28598383697738), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 5)), std::complex<klab::DoubleReal>(17.130880124615274), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 6)), std::complex<klab::DoubleReal>(19.966836105288223), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 7)), std::complex<klab::DoubleReal>(23.39843976294355), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 0)), std::complex<klab::DoubleReal>(2.8140305304460771), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 1)), std::complex<klab::DoubleReal>(7.1879751350030183), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 2)), std::complex<klab::DoubleReal>(10.718634174011953), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 3)), std::complex<klab::DoubleReal>(14.285983836977376), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 4)), std::complex<klab::DoubleReal>(17.868245871860609), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 5)), std::complex<klab::DoubleReal>(21.435595534826039), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 6)), std::complex<klab::DoubleReal>(24.966254573834966), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 7)), std::complex<klab::DoubleReal>(29.340199178391909), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 0)), std::complex<klab::DoubleReal>(3.4545670544218936), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 1)), std::complex<klab::DoubleReal>(8.6071939837611318), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 2)), std::complex<klab::DoubleReal>(12.861937047489985), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 3)), std::complex<klab::DoubleReal>(17.130880124615267), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 4)), std::complex<klab::DoubleReal>(21.435595534826039), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 5)), std::complex<klab::DoubleReal>(25.704538611951325), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 6)), std::complex<klab::DoubleReal>(29.959281675680177), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 7)), std::complex<klab::DoubleReal>(35.111908605019416), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 0)), std::complex<klab::DoubleReal>(3.8827266950806774), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 1)), std::complex<klab::DoubleReal>(10.055643612060855), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 2)), std::complex<klab::DoubleReal>(14.97380900344301), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 3)), std::complex<klab::DoubleReal>(19.966836105288216), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 4)), std::complex<klab::DoubleReal>(24.966254573834966), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 5)), std::complex<klab::DoubleReal>(29.959281675680174), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 6)), std::complex<klab::DoubleReal>(34.877447067062327), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 7)), std::complex<klab::DoubleReal>(41.050363984042505), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 0)), std::complex<klab::DoubleReal>(5.0255382618799835), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 1)), std::complex<klab::DoubleReal>(11.688274957292943), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 2)), std::complex<klab::DoubleReal>(17.62673033631604), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 3)), std::complex<klab::DoubleReal>(23.398439762943543), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 4)), std::complex<klab::DoubleReal>(29.340199178391916), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 5)), std::complex<klab::DoubleReal>(35.111908605019423), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 6)), std::complex<klab::DoubleReal>(41.050363984042505), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 7)), std::complex<klab::DoubleReal>(47.713100679455479), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur2DOperatorUnitTest::testApplyAdjoint()
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
        
        TInverseGaussianBlur2DOperator<klab::DoubleReal> op(8, 8, 0.4, 4.0, 4, 4);
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

void KInverseGaussianBlur2DOperatorUnitTest::testApplyAdjoint_Complex()
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
        
        TInverseGaussianBlur2DOperator<std::complex<klab::DoubleReal> > op(8, 8, 0.4, 4.0, 4, 4);
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

