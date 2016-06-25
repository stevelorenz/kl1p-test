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

#include "InverseGaussian2DDiagonalOperatorUnitTest.h"
#include "../include/InverseGaussian2DDiagonalOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KInverseGaussian2DDiagonalOperatorUnitTest::KInverseGaussian2DDiagonalOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testHeightWidthConstructor)  
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testHeightWidthGammaConstructor)  
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testHeightWidthGammaSigmaConstructor)  
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testHeightWidthGammaSigmaIcJcConstructor)  
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testWidth)
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testHeight)
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testGamma)
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testSigma)
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testIc)
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testJc)
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testApply)
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testApply_Complex)
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KInverseGaussian2DDiagonalOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KInverseGaussian2DDiagonalOperatorUnitTest::~KInverseGaussian2DDiagonalOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testHeightWidthConstructor()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.0 && op.sigma()==1.0 && op.ic()==2 && op.jc()==4)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.0 && op2.sigma()==1.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testHeightWidthGammaConstructor()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.4 && op.sigma()==1.0 && op.ic()==2 && op.jc()==4)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.4 && op2.sigma()==1.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testHeightWidthGammaSigmaConstructor()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.4 && op.sigma()==4.0 && op.ic()==2 && op.jc()==4)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.ic()==2 && op2.jc()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testHeightWidthGammaSigmaIcJcConstructor()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.4 && op.sigma()==4.0 && op.ic()==-1 && op.jc()==7)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.ic()==-1 && op2.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.gamma()==0.4 && op.sigma()==4.0 && op.ic()==-1 && op.jc()==7)

        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==32 && opCopy.n()==32)
        TEST_ASSERT(opCopy.height()==4 && opCopy.width()==8 && opCopy.gamma()==0.4 && opCopy.sigma()==4.0 && opCopy.ic()==-1 && opCopy.jc()==7)


        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.ic()==-1 && op2.jc()==7)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.m()==32 && op2Copy.n()==32)
        TEST_ASSERT(op2Copy.height()==4 && op2Copy.width()==8 && op2Copy.gamma()==0.4 && op2Copy.sigma()==4.0 && op2Copy.ic()==-1 && op2Copy.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testWidth()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.height()==4)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.height()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testHeight()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.width()==8)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.width()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testGamma()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.gamma()==0.4)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.gamma()==0.4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testSigma()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.sigma()==4.0)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.sigma()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testIc()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.ic()==-1)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.ic()==-1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testJc()
{
    try
    {
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op.jc()==7)

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op2(4, 8, 0.4, 4.0, -1, 7);
        TEST_ASSERT(op2.jc()==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testApply()
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

        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(8, 8, 0.4, 4.0, 4, 4);
        op.apply(x, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(ar(0, 0), 0.6871944605393091, precision))
        TEST_ASSERT(klab::Equals(ar(0, 1), 1.5020499007120285, precision))
        TEST_ASSERT(klab::Equals(ar(0, 2), 2.33907220007961, precision))
        TEST_ASSERT(klab::Equals(ar(0, 3), 3.1538463753231976, precision))
        TEST_ASSERT(klab::Equals(ar(0, 4), 3.9493872813376636, precision))
        TEST_ASSERT(klab::Equals(ar(0, 5), 4.7307695629847961, precision))
        TEST_ASSERT(klab::Equals(ar(0, 6), 5.4578351335190902, precision))
        TEST_ASSERT(klab::Equals(ar(0, 7), 6.0081996028481139, precision))
        TEST_ASSERT(klab::Equals(ar(1, 0), 1.5020499007120285, precision))
        TEST_ASSERT(klab::Equals(ar(1, 1), 3.1451370161369132, precision))
        TEST_ASSERT(klab::Equals(ar(1, 2), 4.7370363335876569, precision))
        TEST_ASSERT(klab::Equals(ar(1, 3), 6.258063096690929, precision))
        TEST_ASSERT(klab::Equals(ar(1, 4), 7.7835942516144883, precision))
        TEST_ASSERT(klab::Equals(ar(1, 5), 9.3870946450363935, precision))
        TEST_ASSERT(klab::Equals(ar(1, 6), 11.053084778371201, precision))
        TEST_ASSERT(klab::Equals(ar(1, 7), 12.580548064547653, precision))
        TEST_ASSERT(klab::Equals(ar(2, 0), 2.33907220007961, precision))
        TEST_ASSERT(klab::Equals(ar(2, 1), 4.7370363335876569, precision))
        TEST_ASSERT(klab::Equals(ar(2, 2), 6.9637293012453156, precision))
        TEST_ASSERT(klab::Equals(ar(2, 3), 9.0703447929960035, precision))
        TEST_ASSERT(klab::Equals(ar(2, 4), 11.22959343840806, precision))
        TEST_ASSERT(klab::Equals(ar(2, 5), 13.605517189494003, precision))
        TEST_ASSERT(klab::Equals(ar(2, 6), 16.248701702905734, precision))
        TEST_ASSERT(klab::Equals(ar(2, 7), 18.948145334350627, precision))
        TEST_ASSERT(klab::Equals(ar(3, 0), 3.1538463753231976, precision))
        TEST_ASSERT(klab::Equals(ar(3, 1), 6.258063096690929, precision))
        TEST_ASSERT(klab::Equals(ar(3, 2), 9.0703447929960035, precision))
        TEST_ASSERT(klab::Equals(ar(3, 3), 11.719801408272149, precision))
        TEST_ASSERT(klab::Equals(ar(3, 4), 14.472506822360558, precision))
        TEST_ASSERT(klab::Equals(ar(3, 5), 17.579702112408224, precision))
        TEST_ASSERT(klab::Equals(ar(3, 6), 21.164137850324007, precision))
        TEST_ASSERT(klab::Equals(ar(3, 7), 25.032252386763716, precision))
        TEST_ASSERT(klab::Equals(ar(4, 0), 3.9493872813376636, precision))
        TEST_ASSERT(klab::Equals(ar(4, 1), 7.7835942516144883, precision))
        TEST_ASSERT(klab::Equals(ar(4, 2), 11.22959343840806, precision))
        TEST_ASSERT(klab::Equals(ar(4, 3), 14.472506822360558, precision))
        TEST_ASSERT(klab::Equals(ar(4, 4), 17.857142857142858, precision))
        TEST_ASSERT(klab::Equals(ar(4, 5), 21.708760233540836, precision))
        TEST_ASSERT(klab::Equals(ar(4, 6), 26.202384689618807, precision))
        TEST_ASSERT(klab::Equals(ar(4, 7), 31.134377006457953, precision))
        TEST_ASSERT(klab::Equals(ar(5, 0), 4.7307695629847961, precision))
        TEST_ASSERT(klab::Equals(ar(5, 1), 9.3870946450363935, precision))
        TEST_ASSERT(klab::Equals(ar(5, 2), 13.605517189494003, precision))
        TEST_ASSERT(klab::Equals(ar(5, 3), 17.579702112408224, precision))
        TEST_ASSERT(klab::Equals(ar(5, 4), 21.708760233540836, precision))
        TEST_ASSERT(klab::Equals(ar(5, 5), 26.369553168612335, precision))
        TEST_ASSERT(klab::Equals(ar(5, 6), 31.746206775486009, precision))
        TEST_ASSERT(klab::Equals(ar(5, 7), 37.548378580145574, precision))
        TEST_ASSERT(klab::Equals(ar(6, 0), 5.4578351335190902, precision))
        TEST_ASSERT(klab::Equals(ar(6, 1), 11.053084778371201, precision))
        TEST_ASSERT(klab::Equals(ar(6, 2), 16.248701702905734, precision))
        TEST_ASSERT(klab::Equals(ar(6, 3), 21.164137850324007, precision))
        TEST_ASSERT(klab::Equals(ar(6, 4), 26.202384689618807, precision))
        TEST_ASSERT(klab::Equals(ar(6, 5), 31.746206775486009, precision))
        TEST_ASSERT(klab::Equals(ar(6, 6), 37.913637306780046, precision))
        TEST_ASSERT(klab::Equals(ar(6, 7), 44.212339113484802, precision))
        TEST_ASSERT(klab::Equals(ar(7, 0), 6.0081996028481139, precision))
        TEST_ASSERT(klab::Equals(ar(7, 1), 12.580548064547653, precision))
        TEST_ASSERT(klab::Equals(ar(7, 2), 18.948145334350627, precision))
        TEST_ASSERT(klab::Equals(ar(7, 3), 25.032252386763716, precision))
        TEST_ASSERT(klab::Equals(ar(7, 4), 31.134377006457953, precision))
        TEST_ASSERT(klab::Equals(ar(7, 5), 37.548378580145574, precision))
        TEST_ASSERT(klab::Equals(ar(7, 6), 44.212339113484802, precision))
        TEST_ASSERT(klab::Equals(ar(7, 7), 50.322192258190611, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testApply_Complex()
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

        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op(8, 8, 0.4, 4.0, 4, 4);
        op.apply(x, xr);
        ar = xr;
        ar.reshape(8, 8);

        TEST_ASSERT(ar.n_rows==8 && ar.n_cols==8)
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 0)), std::complex<klab::DoubleReal>(0.6871944605393091), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 1)), std::complex<klab::DoubleReal>(1.5020499007120285), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 2)), std::complex<klab::DoubleReal>(2.33907220007961), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 3)), std::complex<klab::DoubleReal>(3.1538463753231976), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 4)), std::complex<klab::DoubleReal>(3.9493872813376636), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 5)), std::complex<klab::DoubleReal>(4.7307695629847961), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 6)), std::complex<klab::DoubleReal>(5.4578351335190902), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(0, 7)), std::complex<klab::DoubleReal>(6.0081996028481139), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 0)), std::complex<klab::DoubleReal>(1.5020499007120285), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 1)), std::complex<klab::DoubleReal>(3.1451370161369132), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 2)), std::complex<klab::DoubleReal>(4.7370363335876569), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 3)), std::complex<klab::DoubleReal>(6.258063096690929), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 4)), std::complex<klab::DoubleReal>(7.7835942516144883), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 5)), std::complex<klab::DoubleReal>(9.3870946450363935), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 6)), std::complex<klab::DoubleReal>(11.053084778371201), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(1, 7)), std::complex<klab::DoubleReal>(12.580548064547653), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 0)), std::complex<klab::DoubleReal>(2.33907220007961), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 1)), std::complex<klab::DoubleReal>(4.7370363335876569), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 2)), std::complex<klab::DoubleReal>(6.9637293012453156), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 3)), std::complex<klab::DoubleReal>(9.0703447929960035), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 4)), std::complex<klab::DoubleReal>(11.22959343840806), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 5)), std::complex<klab::DoubleReal>(13.605517189494003), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 6)), std::complex<klab::DoubleReal>(16.248701702905734), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(2, 7)), std::complex<klab::DoubleReal>(18.948145334350627), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 0)), std::complex<klab::DoubleReal>(3.1538463753231976), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 1)), std::complex<klab::DoubleReal>(6.258063096690929), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 2)), std::complex<klab::DoubleReal>(9.0703447929960035), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 3)), std::complex<klab::DoubleReal>(11.719801408272149), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 4)), std::complex<klab::DoubleReal>(14.472506822360558), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 5)), std::complex<klab::DoubleReal>(17.579702112408224), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 6)), std::complex<klab::DoubleReal>(21.164137850324007), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(3, 7)), std::complex<klab::DoubleReal>(25.032252386763716), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 0)), std::complex<klab::DoubleReal>(3.9493872813376636), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 1)), std::complex<klab::DoubleReal>(7.7835942516144883), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 2)), std::complex<klab::DoubleReal>(11.22959343840806), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 3)), std::complex<klab::DoubleReal>(14.472506822360558), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 4)), std::complex<klab::DoubleReal>(17.857142857142858), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 5)), std::complex<klab::DoubleReal>(21.708760233540836), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 6)), std::complex<klab::DoubleReal>(26.202384689618807), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(4, 7)), std::complex<klab::DoubleReal>(31.134377006457953), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 0)), std::complex<klab::DoubleReal>(4.7307695629847961), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 1)), std::complex<klab::DoubleReal>(9.3870946450363935), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 2)), std::complex<klab::DoubleReal>(13.605517189494003), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 3)), std::complex<klab::DoubleReal>(17.579702112408224), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 4)), std::complex<klab::DoubleReal>(21.708760233540836), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 5)), std::complex<klab::DoubleReal>(26.369553168612335), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 6)), std::complex<klab::DoubleReal>(31.746206775486009), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(5, 7)), std::complex<klab::DoubleReal>(37.548378580145574), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 0)), std::complex<klab::DoubleReal>(5.4578351335190902), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 1)), std::complex<klab::DoubleReal>(11.053084778371201), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 2)), std::complex<klab::DoubleReal>(16.248701702905734), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 3)), std::complex<klab::DoubleReal>(21.164137850324007), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 4)), std::complex<klab::DoubleReal>(26.202384689618807), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 5)), std::complex<klab::DoubleReal>(31.746206775486009), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 6)), std::complex<klab::DoubleReal>(37.913637306780046), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(6, 7)), std::complex<klab::DoubleReal>(44.212339113484802), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 0)), std::complex<klab::DoubleReal>(6.0081996028481139), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 1)), std::complex<klab::DoubleReal>(12.580548064547653), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 2)), std::complex<klab::DoubleReal>(18.948145334350627), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 3)), std::complex<klab::DoubleReal>(25.032252386763716), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 4)), std::complex<klab::DoubleReal>(31.134377006457953), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 5)), std::complex<klab::DoubleReal>(37.548378580145574), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 6)), std::complex<klab::DoubleReal>(44.212339113484802), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(ar(7, 7)), std::complex<klab::DoubleReal>(50.322192258190611), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian2DDiagonalOperatorUnitTest::testApplyAdjoint()
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
        
        TInverseGaussian2DDiagonalOperator<klab::DoubleReal> op(8, 8, 0.4, 4.0, 4, 4);
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

void KInverseGaussian2DDiagonalOperatorUnitTest::testApplyAdjoint_Complex()
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
        
        TInverseGaussian2DDiagonalOperator<std::complex<klab::DoubleReal> > op(8, 8, 0.4, 4.0, 4, 4);
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

