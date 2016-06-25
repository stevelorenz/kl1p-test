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

#include "InverseFourier2DOperatorUnitTest.h"
#include "../include/InverseFourier2DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KInverseFourier2DOperatorUnitTest::KInverseFourier2DOperatorUnitTest() : Test::Suite()
{ 
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testHeightWidthShiftConstructor)  
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KInverseFourier2DOperatorUnitTest::testWidth)
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testHeight)
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testIsShift)
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testApply)
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testApplyAdjoint_Real)
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testApplyAdjoint_Real_02)
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testApplyAdjoint_Real_03)
    TEST_ADD(KInverseFourier2DOperatorUnitTest::testApplyAdjoint_Real_04)
}

// ---------------------------------------------------------------------------------------------------- //

KInverseFourier2DOperatorUnitTest::~KInverseFourier2DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testHeightWidthShiftConstructor()
{
    try
    {
        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op(4, 8);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.isShift()==false)

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op2(4, 8, true);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.isShift()==true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op(4, 8, true);
        TEST_ASSERT(op.m()==32 && op.n()==32)
        TEST_ASSERT(op.height()==4 && op.width()==8 && op.isShift()==true)

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op2(op);
        TEST_ASSERT(op2.m()==32 && op2.n()==32)
        TEST_ASSERT(op2.height()==4 && op2.width()==8 && op2.isShift()==true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testWidth()
{
    try
    {
        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op(0, 0);
        TEST_ASSERT(op.height()==0 && op.width()==0)

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op2(4, 8);
        TEST_ASSERT(op2.height()==4 && op2.width()==8)

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op3(7, 5);
        TEST_ASSERT(op3.height()==7 && op3.width()==5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testHeight()
{
    try
    {
        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op(0, 0);
        TEST_ASSERT(op.height()==0 && op.width()==0)

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op2(4, 8);
        TEST_ASSERT(op2.height()==4 && op2.width()==8)

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op3(7, 5);
        TEST_ASSERT(op3.height()==7 && op3.width()==5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}


// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testIsShift()
{
    try
    {
        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op(0, 0);
        TEST_ASSERT(op.isShift() == false)

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op2(0, 0, true);
        TEST_ASSERT(op2.isShift() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testApply()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(8, 8);
        arma::Mat<std::complex<klab::DoubleReal> > F;

        f(0, 0) = std::complex<klab::DoubleReal>(7952.0, 0.0);
        f(0, 1) = std::complex<klab::DoubleReal>(-320.873629022557, 513.86352775479031);
        f(0, 2) = std::complex<klab::DoubleReal>(415.0, 105);
        f(0, 3) = std::complex<klab::DoubleReal>(-127.12637097744299, 75.863527754790312);
        f(0, 4) = std::complex<klab::DoubleReal>(194.0, 0.0);
        f(0, 5) = std::complex<klab::DoubleReal>(-127.12637097744299, -75.863527754790312);
        f(0, 6) = std::complex<klab::DoubleReal>(415.0, -105);
        f(0, 7) = std::complex<klab::DoubleReal>(-320.873629022557, -513.86352775479031);
        f(1, 0) = std::complex<klab::DoubleReal>(104.50609665440986, -283.87362902255705);
        f(1, 1) = std::complex<klab::DoubleReal>(-541.93102422918764, -10.159379566434069);
        f(1, 2) = std::complex<klab::DoubleReal>(-93.87867965644034, -258.30003589374985);
        f(1, 3) = std::complex<klab::DoubleReal>(404.42135623730962, -120.29646455628168);
        f(1, 4) = std::complex<klab::DoubleReal>(132.40559159102156, 94.736544032709403);
        f(1, 5) = std::complex<klab::DoubleReal>(289.94112549695433, 68.870057685088824);
        f(1, 6) = std::complex<klab::DoubleReal>(-15.067496474397281, 161.93250352560278);
        f(1, 7) = std::complex<klab::DoubleReal>(13.828427124746156, 241.55129855222074);
        f(2, 0) = std::complex<klab::DoubleReal>(-33.0, -115.0);
        f(2, 1) = std::complex<klab::DoubleReal>(20.138564286262735, -85.856385079853908);
        f(2, 2) = std::complex<klab::DoubleReal>(116, 154.0);
        f(2, 3) = std::complex<klab::DoubleReal>(-64.57211383239202, -94.417784899841308);
        f(2, 4) = std::complex<klab::DoubleReal>(39.0, -33);
        f(2, 5) = std::complex<klab::DoubleReal>(131.86143571373725, 223.85638507985391);
        f(2, 6) = std::complex<klab::DoubleReal>(-182.0, -10.0);
        f(2, 7) = std::complex<klab::DoubleReal>(188.57211383239201, 48.417784899841301);
        f(3, 0) = std::complex<klab::DoubleReal>(63.49390334559012, 90.126370977442974);
        f(3, 1) = std::complex<klab::DoubleReal>(121.5786437626905, -18.296464556281634);
        f(3, 2) = std::complex<klab::DoubleReal>(-140.93250352560273, -36.067496474397274);
        f(3, 3) = std::complex<klab::DoubleReal>(-78.068975770812457, 97.84062043356596);
        f(3, 4) = std::complex<klab::DoubleReal>(71.594408408978438, -127.26345596729058);
        f(3, 5) = std::complex<klab::DoubleReal>(8.1715728752537728, -12.448701447779307);
        f(3, 6) = std::complex<klab::DoubleReal>(-98.12132034355966, -20.300035893749865);
        f(3, 7) = std::complex<klab::DoubleReal>(222.05887450304579, -15.129942314911219);
        f(4, 0) = std::complex<klab::DoubleReal>(170, 0.0);
        f(4, 1) = std::complex<klab::DoubleReal>(22.422835533724644, 27.121320343559642);
        f(4, 2) = std::complex<klab::DoubleReal>(-97.0, -33.0);
        f(4, 3) = std::complex<klab::DoubleReal>(77.577164466275349, -22.878679656440358);
        f(4, 4) = std::complex<klab::DoubleReal>(-16.0, 0);
        f(4, 5) = std::complex<klab::DoubleReal>(77.577164466275349, 22.878679656440358);
        f(4, 6) = std::complex<klab::DoubleReal>(-97.0, 33.0);
        f(4, 7) = std::complex<klab::DoubleReal>(22.422835533724644, -27.121320343559642);
        f(5, 0) = std::complex<klab::DoubleReal>(63.49390334559012, -90.126370977442974);
        f(5, 1) = std::complex<klab::DoubleReal>(222.05887450304579, 15.129942314911219);
        f(5, 2) = std::complex<klab::DoubleReal>(-98.12132034355966, 20.300035893749865);
        f(5, 3) = std::complex<klab::DoubleReal>(8.1715728752537728, 12.448701447779307);
        f(5, 4) = std::complex<klab::DoubleReal>(71.594408408978438, 127.26345596729058);
        f(5, 5) = std::complex<klab::DoubleReal>(-78.068975770812457, -97.84062043356596);
        f(5, 6) = std::complex<klab::DoubleReal>(-140.93250352560273, 36.067496474397274);
        f(5, 7) = std::complex<klab::DoubleReal>(121.5786437626905, 18.296464556281634);
        f(6, 0) = std::complex<klab::DoubleReal>(-33.0, 115.0);
        f(6, 1) = std::complex<klab::DoubleReal>(188.57211383239201, -48.417784899841301);
        f(6, 2) = std::complex<klab::DoubleReal>(-182, 10.0);
        f(6, 3) = std::complex<klab::DoubleReal>(131.86143571373725, -223.85638507985391);
        f(6, 4) = std::complex<klab::DoubleReal>(39.0, 33.0);
        f(6, 5) = std::complex<klab::DoubleReal>(-64.57211383239202, 94.417784899841308);
        f(6, 6) = std::complex<klab::DoubleReal>(116, -154);
        f(6, 7) = std::complex<klab::DoubleReal>(20.138564286262735, 85.856385079853908);
        f(7, 0) = std::complex<klab::DoubleReal>(104.50609665440986, 283.87362902255705);
        f(7, 1) = std::complex<klab::DoubleReal>(13.828427124746156, -241.55129855222074);
        f(7, 2) = std::complex<klab::DoubleReal>(-15.067496474397281, -161.93250352560278);
        f(7, 3) = std::complex<klab::DoubleReal>(289.94112549695433, -68.870057685088824);
        f(7, 4) = std::complex<klab::DoubleReal>(132.40559159102156, -94.736544032709403);
        f(7, 5) = std::complex<klab::DoubleReal>(404.42135623730962, 120.29646455628168);
        f(7, 6) = std::complex<klab::DoubleReal>(-93.87867965644034, 258.30003589374985);
        f(7, 7) = std::complex<klab::DoubleReal>(-541.93102422918764, 10.159379566434069);        
        
        f.reshape(64, 1);
        arma::Col<std::complex<klab::DoubleReal> > x(f);
        arma::Col<std::complex<klab::DoubleReal> > y;
        f.reshape(8, 8);

        klab::DoubleReal precision = 1e-5;

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(150.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(111.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(129.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(139.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(127.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(143.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(160.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(90.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(127.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(108.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(120.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(167.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(182.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(136.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(118.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(85.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(124.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(114.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(132.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(141.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(171.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(184.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(110.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(141.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(127.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(115.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(107.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(85.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(161.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(122.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(97.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(157.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(121.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(107.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(73.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(118.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(153.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(97.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(126.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(170.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(115.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(98.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(90.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(91.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(140.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(87.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(144.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(195.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(120.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(81.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(84.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(77.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(151.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(138.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(144.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(135.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(126.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(71.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(70.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(108.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(149.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(175.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(125.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(93.0, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(8, 8);
        arma::Mat<std::complex<klab::DoubleReal> > F;
        arma::Mat<std::complex<klab::DoubleReal> > fR;

        f(0, 0) = std::complex<klab::DoubleReal>(7952.0, 0.0);
        f(0, 1) = std::complex<klab::DoubleReal>(-320.873629022557, 513.86352775479031);
        f(0, 2) = std::complex<klab::DoubleReal>(415.0, 105);
        f(0, 3) = std::complex<klab::DoubleReal>(-127.12637097744299, 75.863527754790312);
        f(0, 4) = std::complex<klab::DoubleReal>(194.0, 0.0);
        f(0, 5) = std::complex<klab::DoubleReal>(-127.12637097744299, -75.863527754790312);
        f(0, 6) = std::complex<klab::DoubleReal>(415.0, -105);
        f(0, 7) = std::complex<klab::DoubleReal>(-320.873629022557, -513.86352775479031);
        f(1, 0) = std::complex<klab::DoubleReal>(104.50609665440986, -283.87362902255705);
        f(1, 1) = std::complex<klab::DoubleReal>(-541.93102422918764, -10.159379566434069);
        f(1, 2) = std::complex<klab::DoubleReal>(-93.87867965644034, -258.30003589374985);
        f(1, 3) = std::complex<klab::DoubleReal>(404.42135623730962, -120.29646455628168);
        f(1, 4) = std::complex<klab::DoubleReal>(132.40559159102156, 94.736544032709403);
        f(1, 5) = std::complex<klab::DoubleReal>(289.94112549695433, 68.870057685088824);
        f(1, 6) = std::complex<klab::DoubleReal>(-15.067496474397281, 161.93250352560278);
        f(1, 7) = std::complex<klab::DoubleReal>(13.828427124746156, 241.55129855222074);
        f(2, 0) = std::complex<klab::DoubleReal>(-33.0, -115.0);
        f(2, 1) = std::complex<klab::DoubleReal>(20.138564286262735, -85.856385079853908);
        f(2, 2) = std::complex<klab::DoubleReal>(116, 154.0);
        f(2, 3) = std::complex<klab::DoubleReal>(-64.57211383239202, -94.417784899841308);
        f(2, 4) = std::complex<klab::DoubleReal>(39.0, -33);
        f(2, 5) = std::complex<klab::DoubleReal>(131.86143571373725, 223.85638507985391);
        f(2, 6) = std::complex<klab::DoubleReal>(-182.0, -10.0);
        f(2, 7) = std::complex<klab::DoubleReal>(188.57211383239201, 48.417784899841301);
        f(3, 0) = std::complex<klab::DoubleReal>(63.49390334559012, 90.126370977442974);
        f(3, 1) = std::complex<klab::DoubleReal>(121.5786437626905, -18.296464556281634);
        f(3, 2) = std::complex<klab::DoubleReal>(-140.93250352560273, -36.067496474397274);
        f(3, 3) = std::complex<klab::DoubleReal>(-78.068975770812457, 97.84062043356596);
        f(3, 4) = std::complex<klab::DoubleReal>(71.594408408978438, -127.26345596729058);
        f(3, 5) = std::complex<klab::DoubleReal>(8.1715728752537728, -12.448701447779307);
        f(3, 6) = std::complex<klab::DoubleReal>(-98.12132034355966, -20.300035893749865);
        f(3, 7) = std::complex<klab::DoubleReal>(222.05887450304579, -15.129942314911219);
        f(4, 0) = std::complex<klab::DoubleReal>(170, 0.0);
        f(4, 1) = std::complex<klab::DoubleReal>(22.422835533724644, 27.121320343559642);
        f(4, 2) = std::complex<klab::DoubleReal>(-97.0, -33.0);
        f(4, 3) = std::complex<klab::DoubleReal>(77.577164466275349, -22.878679656440358);
        f(4, 4) = std::complex<klab::DoubleReal>(-16.0, 0);
        f(4, 5) = std::complex<klab::DoubleReal>(77.577164466275349, 22.878679656440358);
        f(4, 6) = std::complex<klab::DoubleReal>(-97.0, 33.0);
        f(4, 7) = std::complex<klab::DoubleReal>(22.422835533724644, -27.121320343559642);
        f(5, 0) = std::complex<klab::DoubleReal>(63.49390334559012, -90.126370977442974);
        f(5, 1) = std::complex<klab::DoubleReal>(222.05887450304579, 15.129942314911219);
        f(5, 2) = std::complex<klab::DoubleReal>(-98.12132034355966, 20.300035893749865);
        f(5, 3) = std::complex<klab::DoubleReal>(8.1715728752537728, 12.448701447779307);
        f(5, 4) = std::complex<klab::DoubleReal>(71.594408408978438, 127.26345596729058);
        f(5, 5) = std::complex<klab::DoubleReal>(-78.068975770812457, -97.84062043356596);
        f(5, 6) = std::complex<klab::DoubleReal>(-140.93250352560273, 36.067496474397274);
        f(5, 7) = std::complex<klab::DoubleReal>(121.5786437626905, 18.296464556281634);
        f(6, 0) = std::complex<klab::DoubleReal>(-33.0, 115.0);
        f(6, 1) = std::complex<klab::DoubleReal>(188.57211383239201, -48.417784899841301);
        f(6, 2) = std::complex<klab::DoubleReal>(-182, 10.0);
        f(6, 3) = std::complex<klab::DoubleReal>(131.86143571373725, -223.85638507985391);
        f(6, 4) = std::complex<klab::DoubleReal>(39.0, 33.0);
        f(6, 5) = std::complex<klab::DoubleReal>(-64.57211383239202, 94.417784899841308);
        f(6, 6) = std::complex<klab::DoubleReal>(116, -154);
        f(6, 7) = std::complex<klab::DoubleReal>(20.138564286262735, 85.856385079853908);
        f(7, 0) = std::complex<klab::DoubleReal>(104.50609665440986, 283.87362902255705);
        f(7, 1) = std::complex<klab::DoubleReal>(13.828427124746156, -241.55129855222074);
        f(7, 2) = std::complex<klab::DoubleReal>(-15.067496474397281, -161.93250352560278);
        f(7, 3) = std::complex<klab::DoubleReal>(289.94112549695433, -68.870057685088824);
        f(7, 4) = std::complex<klab::DoubleReal>(132.40559159102156, -94.736544032709403);
        f(7, 5) = std::complex<klab::DoubleReal>(404.42135623730962, 120.29646455628168);
        f(7, 6) = std::complex<klab::DoubleReal>(-93.87867965644034, 258.30003589374985);
        f(7, 7) = std::complex<klab::DoubleReal>(-541.93102422918764, 10.159379566434069);        
        
        f.reshape(64, 1);
        arma::Col<std::complex<klab::DoubleReal> > x(f);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;
        f.reshape(8, 8);

        klab::DoubleReal precision = 1e-5;
        

        klab::TFFT2D<std::complex<klab::DoubleReal> > fft;
        arma::Mat<std::complex<klab::DoubleReal> > fftMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(64);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<std::complex<klab::DoubleReal> > inMatrix(base);
            arma::Mat<std::complex<klab::DoubleReal> > outMatrix;
            inMatrix.reshape(8, 8);
            fft.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fftMatrix(i, j) = outMatrix[i];
        }  

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > op(8, 8);

        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(y.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(150.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(111.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(129.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(139.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(127.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(143.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(160.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(90.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(127.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(108.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(120.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(167.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(182.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(136.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(118.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(85.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(124.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(114.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(132.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(141.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(171.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(184.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(110.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(141.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(127.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(115.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(107.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(85.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(161.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(122.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(97.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(157.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(121.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(107.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(73.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(118.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(153.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(97.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(126.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(170.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(115.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(98.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(90.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(91.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(140.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(87.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(144.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(195.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(120.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(81.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(84.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(77.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(151.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(138.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(144.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(135.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(126.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(71.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(70.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(108.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(149.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(175.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(125.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(93.0, 0.0), precision))

        arma::Col<std::complex<klab::DoubleReal> > xt = arma::trans(fftMatrix) * y;


        op.applyAdjoint(y, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
        TEST_ASSERT(klab::Equals(xr[8], xt[8], precision))
        TEST_ASSERT(klab::Equals(xr[9], xt[9], precision))
        TEST_ASSERT(klab::Equals(xr[10], xt[10], precision))
        TEST_ASSERT(klab::Equals(xr[11], xt[11], precision))
        TEST_ASSERT(klab::Equals(xr[12], xt[12], precision))
        TEST_ASSERT(klab::Equals(xr[13], xt[13], precision))
        TEST_ASSERT(klab::Equals(xr[14], xt[14], precision))
        TEST_ASSERT(klab::Equals(xr[15], xt[15], precision))
        TEST_ASSERT(klab::Equals(xr[16], xt[16], precision))
        TEST_ASSERT(klab::Equals(xr[17], xt[17], precision))
        TEST_ASSERT(klab::Equals(xr[18], xt[18], precision))
        TEST_ASSERT(klab::Equals(xr[19], xt[19], precision))
        TEST_ASSERT(klab::Equals(xr[20], xt[20], precision))
        TEST_ASSERT(klab::Equals(xr[21], xt[21], precision))
        TEST_ASSERT(klab::Equals(xr[22], xt[22], precision))
        TEST_ASSERT(klab::Equals(xr[23], xt[23], precision))
        TEST_ASSERT(klab::Equals(xr[24], xt[24], precision))
        TEST_ASSERT(klab::Equals(xr[25], xt[25], precision))
        TEST_ASSERT(klab::Equals(xr[26], xt[26], precision))
        TEST_ASSERT(klab::Equals(xr[27], xt[27], precision))
        TEST_ASSERT(klab::Equals(xr[28], xt[28], precision))
        TEST_ASSERT(klab::Equals(xr[29], xt[29], precision))
        TEST_ASSERT(klab::Equals(xr[30], xt[30], precision))
        TEST_ASSERT(klab::Equals(xr[31], xt[31], precision))
        TEST_ASSERT(klab::Equals(xr[32], xt[32], precision))
        TEST_ASSERT(klab::Equals(xr[33], xt[33], precision))
        TEST_ASSERT(klab::Equals(xr[34], xt[34], precision))
        TEST_ASSERT(klab::Equals(xr[35], xt[35], precision))
        TEST_ASSERT(klab::Equals(xr[36], xt[36], precision))
        TEST_ASSERT(klab::Equals(xr[37], xt[37], precision))
        TEST_ASSERT(klab::Equals(xr[38], xt[38], precision))
        TEST_ASSERT(klab::Equals(xr[39], xt[39], precision))
        TEST_ASSERT(klab::Equals(xr[40], xt[40], precision))
        TEST_ASSERT(klab::Equals(xr[41], xt[41], precision))
        TEST_ASSERT(klab::Equals(xr[42], xt[42], precision))
        TEST_ASSERT(klab::Equals(xr[43], xt[43], precision))
        TEST_ASSERT(klab::Equals(xr[44], xt[44], precision))
        TEST_ASSERT(klab::Equals(xr[45], xt[45], precision))
        TEST_ASSERT(klab::Equals(xr[46], xt[46], precision))
        TEST_ASSERT(klab::Equals(xr[47], xt[47], precision))
        TEST_ASSERT(klab::Equals(xr[48], xt[48], precision))
        TEST_ASSERT(klab::Equals(xr[49], xt[49], precision))
        TEST_ASSERT(klab::Equals(xr[50], xt[50], precision))
        TEST_ASSERT(klab::Equals(xr[51], xt[51], precision))
        TEST_ASSERT(klab::Equals(xr[52], xt[52], precision))
        TEST_ASSERT(klab::Equals(xr[53], xt[53], precision))
        TEST_ASSERT(klab::Equals(xr[54], xt[54], precision))
        TEST_ASSERT(klab::Equals(xr[55], xt[55], precision))
        TEST_ASSERT(klab::Equals(xr[56], xt[56], precision))
        TEST_ASSERT(klab::Equals(xr[57], xt[57], precision))
        TEST_ASSERT(klab::Equals(xr[58], xt[58], precision))
        TEST_ASSERT(klab::Equals(xr[59], xt[59], precision))
        TEST_ASSERT(klab::Equals(xr[60], xt[60], precision))
        TEST_ASSERT(klab::Equals(xr[61], xt[61], precision))
        TEST_ASSERT(klab::Equals(xr[62], xt[62], precision))
        TEST_ASSERT(klab::Equals(xr[63], xt[63], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testApplyAdjoint_Real()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(8, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;        
        
        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);

        klab::DoubleReal precision = 1e-5;
        

        klab::TFFT2D<klab::DoubleReal> fft;
        arma::Mat<klab::DoubleReal> fftMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fft.invert(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fftMatrix(i, j) = outMatrix[i];
        }  

        arma::Col<klab::DoubleReal> xt = arma::trans(fftMatrix) * x;

        TInverseFourier2DOperator<klab::DoubleReal> op(8, 8);
        op.applyAdjoint(x, xr);
        fR = xr;
        fR.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
        TEST_ASSERT(klab::Equals(xr[8], xt[8], precision))
        TEST_ASSERT(klab::Equals(xr[9], xt[9], precision))
        TEST_ASSERT(klab::Equals(xr[10], xt[10], precision))
        TEST_ASSERT(klab::Equals(xr[11], xt[11], precision))
        TEST_ASSERT(klab::Equals(xr[12], xt[12], precision))
        TEST_ASSERT(klab::Equals(xr[13], xt[13], precision))
        TEST_ASSERT(klab::Equals(xr[14], xt[14], precision))
        TEST_ASSERT(klab::Equals(xr[15], xt[15], precision))
        TEST_ASSERT(klab::Equals(xr[16], xt[16], precision))
        TEST_ASSERT(klab::Equals(xr[17], xt[17], precision))
        TEST_ASSERT(klab::Equals(xr[18], xt[18], precision))
        TEST_ASSERT(klab::Equals(xr[19], xt[19], precision))
        TEST_ASSERT(klab::Equals(xr[20], xt[20], precision))
        TEST_ASSERT(klab::Equals(xr[21], xt[21], precision))
        TEST_ASSERT(klab::Equals(xr[22], xt[22], precision))
        TEST_ASSERT(klab::Equals(xr[23], xt[23], precision))
        TEST_ASSERT(klab::Equals(xr[24], xt[24], precision))
        TEST_ASSERT(klab::Equals(xr[25], xt[25], precision))
        TEST_ASSERT(klab::Equals(xr[26], xt[26], precision))
        TEST_ASSERT(klab::Equals(xr[27], xt[27], precision))
        TEST_ASSERT(klab::Equals(xr[28], xt[28], precision))
        TEST_ASSERT(klab::Equals(xr[29], xt[29], precision))
        TEST_ASSERT(klab::Equals(xr[30], xt[30], precision))
        TEST_ASSERT(klab::Equals(xr[31], xt[31], precision))
        TEST_ASSERT(klab::Equals(xr[32], xt[32], precision))
        TEST_ASSERT(klab::Equals(xr[33], xt[33], precision))
        TEST_ASSERT(klab::Equals(xr[34], xt[34], precision))
        TEST_ASSERT(klab::Equals(xr[35], xt[35], precision))
        TEST_ASSERT(klab::Equals(xr[36], xt[36], precision))
        TEST_ASSERT(klab::Equals(xr[37], xt[37], precision))
        TEST_ASSERT(klab::Equals(xr[38], xt[38], precision))
        TEST_ASSERT(klab::Equals(xr[39], xt[39], precision))
        TEST_ASSERT(klab::Equals(xr[40], xt[40], precision))
        TEST_ASSERT(klab::Equals(xr[41], xt[41], precision))
        TEST_ASSERT(klab::Equals(xr[42], xt[42], precision))
        TEST_ASSERT(klab::Equals(xr[43], xt[43], precision))
        TEST_ASSERT(klab::Equals(xr[44], xt[44], precision))
        TEST_ASSERT(klab::Equals(xr[45], xt[45], precision))
        TEST_ASSERT(klab::Equals(xr[46], xt[46], precision))
        TEST_ASSERT(klab::Equals(xr[47], xt[47], precision))
        TEST_ASSERT(klab::Equals(xr[48], xt[48], precision))
        TEST_ASSERT(klab::Equals(xr[49], xt[49], precision))
        TEST_ASSERT(klab::Equals(xr[50], xt[50], precision))
        TEST_ASSERT(klab::Equals(xr[51], xt[51], precision))
        TEST_ASSERT(klab::Equals(xr[52], xt[52], precision))
        TEST_ASSERT(klab::Equals(xr[53], xt[53], precision))
        TEST_ASSERT(klab::Equals(xr[54], xt[54], precision))
        TEST_ASSERT(klab::Equals(xr[55], xt[55], precision))
        TEST_ASSERT(klab::Equals(xr[56], xt[56], precision))
        TEST_ASSERT(klab::Equals(xr[57], xt[57], precision))
        TEST_ASSERT(klab::Equals(xr[58], xt[58], precision))
        TEST_ASSERT(klab::Equals(xr[59], xt[59], precision))
        TEST_ASSERT(klab::Equals(xr[60], xt[60], precision))
        TEST_ASSERT(klab::Equals(xr[61], xt[61], precision))
        TEST_ASSERT(klab::Equals(xr[62], xt[62], precision))
        TEST_ASSERT(klab::Equals(xr[63], xt[63], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testApplyAdjoint_Real_02()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(9, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;

        f(0, 0) = 156.0;
        f(0, 1) = 111.0;
        f(0, 2) = 126.0;
        f(0, 3) = 134.0;
        f(0, 4) = 134.0;
        f(0, 5) = 124.0;
        f(0, 6) = 155.0;
        f(0, 7) = 159.0;
        f(1, 0) = 132.0;
        f(1, 1) = 107.0;
        f(1, 2) = 116.0;
        f(1, 3) = 139.0;
        f(1, 4) = 188.0;
        f(1, 5) = 147.0;
        f(1, 6) = 130.0;
        f(1, 7) = 114.0;
        f(2, 0) = 123.0;
        f(2, 1) = 111.0;
        f(2, 2) = 123.0;
        f(2, 3) = 146.0;
        f(2, 4) = 176.0;
        f(2, 5) = 186.0;
        f(2, 6) = 176.0;
        f(2, 7) = 98.0;
        f(3, 0) = 129.0;
        f(3, 1) = 110.0;
        f(3, 2) = 135.0;
        f(3, 3) = 98.0;
        f(3, 4) = 111.0;
        f(3, 5) = 181.0;
        f(3, 6) = 123.0;
        f(3, 7) = 101.0;
        f(4, 0) = 125.0;
        f(4, 1) = 115.0;
        f(4, 2) = 94.0;
        f(4, 3) = 76.0;
        f(4, 4) = 138.0;
        f(4, 5) = 155.0;
        f(4, 6) = 76.0;
        f(4, 7) = 130.0;
        f(5, 0) = 116.0;
        f(5, 1) = 110.0;
        f(5, 2) = 78.0;
        f(5, 3) = 94.0;
        f(5, 4) = 144.0;
        f(5, 5) = 138.0;
        f(5, 6) = 90.0;
        f(5, 7) = 147.0;
        f(6, 0) = 115.0;
        f(6, 1) = 99.0;
        f(6, 2) = 100.0;
        f(6, 3) = 65.0;
        f(6, 4) = 121.0;
        f(6, 5) = 117.0;
        f(6, 6) = 95.0;
        f(6, 7) = 152.0;
        f(7, 0) = 123.0;
        f(7, 1) = 82.0;
        f(7, 2) = 83.0;
        f(7, 3) = 70.0;
        f(7, 4) = 118.0;
        f(7, 5) = 171.0;
        f(7, 6) = 137.0;
        f(7, 7) = 152.0;
        f(8, 0) = 130.0;
        f(8, 1) = 79.0;
        f(8, 2) = 67.0;
        f(8, 3) = 86.0;
        f(8, 4) = 135.0;
        f(8, 5) = 163.0;
        f(8, 6) = 163.0;
        f(8, 7) = 118.0;   
        
        f.reshape(72, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(9, 8);

        klab::DoubleReal precision = 1e-5;
        

        klab::TFFT2D<klab::DoubleReal> fft;
        arma::Mat<klab::DoubleReal> fftMatrix(72, 72);
        for(klab::UInt32 j=0; j<72; ++j)
        {
            arma::Col<klab::DoubleReal> base(72);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(9, 8);
            fft.invert(inMatrix, outMatrix);
            outMatrix.reshape(72, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fftMatrix(i, j) = outMatrix[i];
        }  

        arma::Col<klab::DoubleReal> xt = arma::trans(fftMatrix) * x;

        TInverseFourier2DOperator<klab::DoubleReal> op(9, 8);
        op.applyAdjoint(x, xr);
        fR = xr;
        fR.reshape(9, 8);

        TEST_ASSERT(xr.n_rows==72)
        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
        TEST_ASSERT(klab::Equals(xr[8], xt[8], precision))
        TEST_ASSERT(klab::Equals(xr[9], xt[9], precision))
        TEST_ASSERT(klab::Equals(xr[10], xt[10], precision))
        TEST_ASSERT(klab::Equals(xr[11], xt[11], precision))
        TEST_ASSERT(klab::Equals(xr[12], xt[12], precision))
        TEST_ASSERT(klab::Equals(xr[13], xt[13], precision))
        TEST_ASSERT(klab::Equals(xr[14], xt[14], precision))
        TEST_ASSERT(klab::Equals(xr[15], xt[15], precision))
        TEST_ASSERT(klab::Equals(xr[16], xt[16], precision))
        TEST_ASSERT(klab::Equals(xr[17], xt[17], precision))
        TEST_ASSERT(klab::Equals(xr[18], xt[18], precision))
        TEST_ASSERT(klab::Equals(xr[19], xt[19], precision))
        TEST_ASSERT(klab::Equals(xr[20], xt[20], precision))
        TEST_ASSERT(klab::Equals(xr[21], xt[21], precision))
        TEST_ASSERT(klab::Equals(xr[22], xt[22], precision))
        TEST_ASSERT(klab::Equals(xr[23], xt[23], precision))
        TEST_ASSERT(klab::Equals(xr[24], xt[24], precision))
        TEST_ASSERT(klab::Equals(xr[25], xt[25], precision))
        TEST_ASSERT(klab::Equals(xr[26], xt[26], precision))
        TEST_ASSERT(klab::Equals(xr[27], xt[27], precision))
        TEST_ASSERT(klab::Equals(xr[28], xt[28], precision))
        TEST_ASSERT(klab::Equals(xr[29], xt[29], precision))
        TEST_ASSERT(klab::Equals(xr[30], xt[30], precision))
        TEST_ASSERT(klab::Equals(xr[31], xt[31], precision))
        TEST_ASSERT(klab::Equals(xr[32], xt[32], precision))
        TEST_ASSERT(klab::Equals(xr[33], xt[33], precision))
        TEST_ASSERT(klab::Equals(xr[34], xt[34], precision))
        TEST_ASSERT(klab::Equals(xr[35], xt[35], precision))
        TEST_ASSERT(klab::Equals(xr[36], xt[36], precision))
        TEST_ASSERT(klab::Equals(xr[37], xt[37], precision))
        TEST_ASSERT(klab::Equals(xr[38], xt[38], precision))
        TEST_ASSERT(klab::Equals(xr[39], xt[39], precision))
        TEST_ASSERT(klab::Equals(xr[40], xt[40], precision))
        TEST_ASSERT(klab::Equals(xr[41], xt[41], precision))
        TEST_ASSERT(klab::Equals(xr[42], xt[42], precision))
        TEST_ASSERT(klab::Equals(xr[43], xt[43], precision))
        TEST_ASSERT(klab::Equals(xr[44], xt[44], precision))
        TEST_ASSERT(klab::Equals(xr[45], xt[45], precision))
        TEST_ASSERT(klab::Equals(xr[46], xt[46], precision))
        TEST_ASSERT(klab::Equals(xr[47], xt[47], precision))
        TEST_ASSERT(klab::Equals(xr[48], xt[48], precision))
        TEST_ASSERT(klab::Equals(xr[49], xt[49], precision))
        TEST_ASSERT(klab::Equals(xr[50], xt[50], precision))
        TEST_ASSERT(klab::Equals(xr[51], xt[51], precision))
        TEST_ASSERT(klab::Equals(xr[52], xt[52], precision))
        TEST_ASSERT(klab::Equals(xr[53], xt[53], precision))
        TEST_ASSERT(klab::Equals(xr[54], xt[54], precision))
        TEST_ASSERT(klab::Equals(xr[55], xt[55], precision))
        TEST_ASSERT(klab::Equals(xr[56], xt[56], precision))
        TEST_ASSERT(klab::Equals(xr[57], xt[57], precision))
        TEST_ASSERT(klab::Equals(xr[58], xt[58], precision))
        TEST_ASSERT(klab::Equals(xr[59], xt[59], precision))
        TEST_ASSERT(klab::Equals(xr[60], xt[60], precision))
        TEST_ASSERT(klab::Equals(xr[61], xt[61], precision))
        TEST_ASSERT(klab::Equals(xr[62], xt[62], precision))
        TEST_ASSERT(klab::Equals(xr[63], xt[63], precision))
        TEST_ASSERT(klab::Equals(xr[64], xt[64], precision))
        TEST_ASSERT(klab::Equals(xr[65], xt[65], precision))
        TEST_ASSERT(klab::Equals(xr[66], xt[66], precision))
        TEST_ASSERT(klab::Equals(xr[67], xt[67], precision))
        TEST_ASSERT(klab::Equals(xr[68], xt[68], precision))
        TEST_ASSERT(klab::Equals(xr[69], xt[69], precision))
        TEST_ASSERT(klab::Equals(xr[70], xt[70], precision))
        TEST_ASSERT(klab::Equals(xr[71], xt[71], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testApplyAdjoint_Real_03()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(8, 9);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;

        f(0, 0) = 156.0;
        f(0, 1) = 111.0;
        f(0, 2) = 126.0;
        f(0, 3) = 134.0;
        f(0, 4) = 134.0;
        f(0, 5) = 124.0;
        f(0, 6) = 155.0;
        f(0, 7) = 159.0;
        f(0, 8) = 87.0;
        f(1, 0) = 132.0;
        f(1, 1) = 107.0;
        f(1, 2) = 116.0;
        f(1, 3) = 139.0;
        f(1, 4) = 188.0;
        f(1, 5) = 147.0;
        f(1, 6) = 130.0;
        f(1, 7) = 114.0;
        f(1, 8) = 75.0;
        f(2, 0) = 123.0;
        f(2, 1) = 111.0;
        f(2, 2) = 123.0;
        f(2, 3) = 146.0;
        f(2, 4) = 176.0;
        f(2, 5) = 186.0;
        f(2, 6) = 176.0;
        f(2, 7) = 98.0;
        f(2, 8) = 137.0;
        f(3, 0) = 129.0;
        f(3, 1) = 110.0;
        f(3, 2) = 135.0;
        f(3, 3) = 98.0;
        f(3, 4) = 111.0;
        f(3, 5) = 181.0;
        f(3, 6) = 123.0;
        f(3, 7) = 101.0;
        f(3, 8) = 161.0;
        f(4, 0) = 125.0;
        f(4, 1) = 115.0;
        f(4, 2) = 94.0;
        f(4, 3) = 76.0;
        f(4, 4) = 138.0;
        f(4, 5) = 155.0;
        f(4, 6) = 76.0;
        f(4, 7) = 130.0;
        f(4, 8) = 155.0;
        f(5, 0) = 116.0;
        f(5, 1) = 110.0;
        f(5, 2) = 78.0;
        f(5, 3) = 94.0;
        f(5, 4) = 144.0;
        f(5, 5) = 138.0;
        f(5, 6) = 90.0;
        f(5, 7) = 147.0;
        f(5, 8) = 190.0;
        f(6, 0) = 115.0;
        f(6, 1) = 99.0;
        f(6, 2) = 100.0;
        f(6, 3) = 65.0;
        f(6, 4) = 121.0;
        f(6, 5) = 117.0;
        f(6, 6) = 95.0;
        f(6, 7) = 152.0;
        f(6, 8) = 188.0;
        f(7, 0) = 123.0;
        f(7, 1) = 82.0;
        f(7, 2) = 83.0;
        f(7, 3) = 70.0;
        f(7, 4) = 118.0;
        f(7, 5) = 171.0;
        f(7, 6) = 137.0;
        f(7, 7) = 152.0;
        f(7, 8) = 119.0;     
        
        f.reshape(72, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 9);

        klab::DoubleReal precision = 1e-5;
        

        klab::TFFT2D<klab::DoubleReal> fft;
        arma::Mat<klab::DoubleReal> fftMatrix(72, 72);
        for(klab::UInt32 j=0; j<72; ++j)
        {
            arma::Col<klab::DoubleReal> base(72);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 9);
            fft.invert(inMatrix, outMatrix);
            outMatrix.reshape(72, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fftMatrix(i, j) = outMatrix[i];
        }  

        arma::Col<klab::DoubleReal> xt = arma::trans(fftMatrix) * x;

        TInverseFourier2DOperator<klab::DoubleReal> op(8, 9);
        op.applyAdjoint(x, xr);
        fR = xr;
        fR.reshape(8, 9);

        TEST_ASSERT(xr.n_rows==72)
        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
        TEST_ASSERT(klab::Equals(xr[8], xt[8], precision))
        TEST_ASSERT(klab::Equals(xr[9], xt[9], precision))
        TEST_ASSERT(klab::Equals(xr[10], xt[10], precision))
        TEST_ASSERT(klab::Equals(xr[11], xt[11], precision))
        TEST_ASSERT(klab::Equals(xr[12], xt[12], precision))
        TEST_ASSERT(klab::Equals(xr[13], xt[13], precision))
        TEST_ASSERT(klab::Equals(xr[14], xt[14], precision))
        TEST_ASSERT(klab::Equals(xr[15], xt[15], precision))
        TEST_ASSERT(klab::Equals(xr[16], xt[16], precision))
        TEST_ASSERT(klab::Equals(xr[17], xt[17], precision))
        TEST_ASSERT(klab::Equals(xr[18], xt[18], precision))
        TEST_ASSERT(klab::Equals(xr[19], xt[19], precision))
        TEST_ASSERT(klab::Equals(xr[20], xt[20], precision))
        TEST_ASSERT(klab::Equals(xr[21], xt[21], precision))
        TEST_ASSERT(klab::Equals(xr[22], xt[22], precision))
        TEST_ASSERT(klab::Equals(xr[23], xt[23], precision))
        TEST_ASSERT(klab::Equals(xr[24], xt[24], precision))
        TEST_ASSERT(klab::Equals(xr[25], xt[25], precision))
        TEST_ASSERT(klab::Equals(xr[26], xt[26], precision))
        TEST_ASSERT(klab::Equals(xr[27], xt[27], precision))
        TEST_ASSERT(klab::Equals(xr[28], xt[28], precision))
        TEST_ASSERT(klab::Equals(xr[29], xt[29], precision))
        TEST_ASSERT(klab::Equals(xr[30], xt[30], precision))
        TEST_ASSERT(klab::Equals(xr[31], xt[31], precision))
        TEST_ASSERT(klab::Equals(xr[32], xt[32], precision))
        TEST_ASSERT(klab::Equals(xr[33], xt[33], precision))
        TEST_ASSERT(klab::Equals(xr[34], xt[34], precision))
        TEST_ASSERT(klab::Equals(xr[35], xt[35], precision))
        TEST_ASSERT(klab::Equals(xr[36], xt[36], precision))
        TEST_ASSERT(klab::Equals(xr[37], xt[37], precision))
        TEST_ASSERT(klab::Equals(xr[38], xt[38], precision))
        TEST_ASSERT(klab::Equals(xr[39], xt[39], precision))
        TEST_ASSERT(klab::Equals(xr[40], xt[40], precision))
        TEST_ASSERT(klab::Equals(xr[41], xt[41], precision))
        TEST_ASSERT(klab::Equals(xr[42], xt[42], precision))
        TEST_ASSERT(klab::Equals(xr[43], xt[43], precision))
        TEST_ASSERT(klab::Equals(xr[44], xt[44], precision))
        TEST_ASSERT(klab::Equals(xr[45], xt[45], precision))
        TEST_ASSERT(klab::Equals(xr[46], xt[46], precision))
        TEST_ASSERT(klab::Equals(xr[47], xt[47], precision))
        TEST_ASSERT(klab::Equals(xr[48], xt[48], precision))
        TEST_ASSERT(klab::Equals(xr[49], xt[49], precision))
        TEST_ASSERT(klab::Equals(xr[50], xt[50], precision))
        TEST_ASSERT(klab::Equals(xr[51], xt[51], precision))
        TEST_ASSERT(klab::Equals(xr[52], xt[52], precision))
        TEST_ASSERT(klab::Equals(xr[53], xt[53], precision))
        TEST_ASSERT(klab::Equals(xr[54], xt[54], precision))
        TEST_ASSERT(klab::Equals(xr[55], xt[55], precision))
        TEST_ASSERT(klab::Equals(xr[56], xt[56], precision))
        TEST_ASSERT(klab::Equals(xr[57], xt[57], precision))
        TEST_ASSERT(klab::Equals(xr[58], xt[58], precision))
        TEST_ASSERT(klab::Equals(xr[59], xt[59], precision))
        TEST_ASSERT(klab::Equals(xr[60], xt[60], precision))
        TEST_ASSERT(klab::Equals(xr[61], xt[61], precision))
        TEST_ASSERT(klab::Equals(xr[62], xt[62], precision))
        TEST_ASSERT(klab::Equals(xr[63], xt[63], precision))
        TEST_ASSERT(klab::Equals(xr[64], xt[64], precision))
        TEST_ASSERT(klab::Equals(xr[65], xt[65], precision))
        TEST_ASSERT(klab::Equals(xr[66], xt[66], precision))
        TEST_ASSERT(klab::Equals(xr[67], xt[67], precision))
        TEST_ASSERT(klab::Equals(xr[68], xt[68], precision))
        TEST_ASSERT(klab::Equals(xr[69], xt[69], precision))
        TEST_ASSERT(klab::Equals(xr[70], xt[70], precision))
        TEST_ASSERT(klab::Equals(xr[71], xt[71], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseFourier2DOperatorUnitTest::testApplyAdjoint_Real_04()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(9, 9);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;

        f(0, 0) = 156.0;
        f(0, 1) = 111.0;
        f(0, 2) = 126.0;
        f(0, 3) = 134.0;
        f(0, 4) = 134.0;
        f(0, 5) = 124.0;
        f(0, 6) = 155.0;
        f(0, 7) = 159.0;
        f(0, 8) = 87.0;
        f(1, 0) = 132.0;
        f(1, 1) = 107.0;
        f(1, 2) = 116.0;
        f(1, 3) = 139.0;
        f(1, 4) = 188.0;
        f(1, 5) = 147.0;
        f(1, 6) = 130.0;
        f(1, 7) = 114.0;
        f(1, 8) = 75.0;
        f(2, 0) = 123.0;
        f(2, 1) = 111.0;
        f(2, 2) = 123.0;
        f(2, 3) = 146.0;
        f(2, 4) = 176.0;
        f(2, 5) = 186.0;
        f(2, 6) = 176.0;
        f(2, 7) = 98.0;
        f(2, 8) = 137.0;
        f(3, 0) = 129.0;
        f(3, 1) = 110.0;
        f(3, 2) = 135.0;
        f(3, 3) = 98.0;
        f(3, 4) = 111.0;
        f(3, 5) = 181.0;
        f(3, 6) = 123.0;
        f(3, 7) = 101.0;
        f(3, 8) = 161.0;
        f(4, 0) = 125.0;
        f(4, 1) = 115.0;
        f(4, 2) = 94.0;
        f(4, 3) = 76.0;
        f(4, 4) = 138.0;
        f(4, 5) = 155.0;
        f(4, 6) = 76.0;
        f(4, 7) = 130.0;
        f(4, 8) = 155.0;
        f(5, 0) = 116.0;
        f(5, 1) = 110.0;
        f(5, 2) = 78.0;
        f(5, 3) = 94.0;
        f(5, 4) = 144.0;
        f(5, 5) = 138.0;
        f(5, 6) = 90.0;
        f(5, 7) = 147.0;
        f(5, 8) = 190.0;
        f(6, 0) = 115.0;
        f(6, 1) = 99.0;
        f(6, 2) = 100.0;
        f(6, 3) = 65.0;
        f(6, 4) = 121.0;
        f(6, 5) = 117.0;
        f(6, 6) = 95.0;
        f(6, 7) = 152.0;
        f(6, 8) = 188.0;
        f(7, 0) = 123.0;
        f(7, 1) = 82.0;
        f(7, 2) = 83.0;
        f(7, 3) = 70.0;
        f(7, 4) = 118.0;
        f(7, 5) = 171.0;
        f(7, 6) = 137.0;
        f(7, 7) = 152.0;
        f(7, 8) = 119.0;
        f(8, 0) = 130.0;
        f(8, 1) = 79.0;
        f(8, 2) = 67.0;
        f(8, 3) = 86.0;
        f(8, 4) = 135.0;
        f(8, 5) = 163.0;
        f(8, 6) = 163.0;
        f(8, 7) = 118.0;
        f(8, 8) = 88.0;       
        
        f.reshape(81, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(9, 9);

        klab::DoubleReal precision = 1e-5;
        

        klab::TFFT2D<klab::DoubleReal> fft;
        arma::Mat<klab::DoubleReal> fftMatrix(81, 81);
        for(klab::UInt32 j=0; j<81; ++j)
        {
            arma::Col<klab::DoubleReal> base(81);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(9, 9);
            fft.invert(inMatrix, outMatrix);
            outMatrix.reshape(81, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fftMatrix(i, j) = outMatrix[i];
        }  

        arma::Col<klab::DoubleReal> xt = arma::trans(fftMatrix) * x;

        TInverseFourier2DOperator<klab::DoubleReal> op(9, 9);
        op.applyAdjoint(x, xr);
        fR = xr;
        fR.reshape(9, 9);

        TEST_ASSERT(xr.n_rows==81)
        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
        TEST_ASSERT(klab::Equals(xr[8], xt[8], precision))
        TEST_ASSERT(klab::Equals(xr[9], xt[9], precision))
        TEST_ASSERT(klab::Equals(xr[10], xt[10], precision))
        TEST_ASSERT(klab::Equals(xr[11], xt[11], precision))
        TEST_ASSERT(klab::Equals(xr[12], xt[12], precision))
        TEST_ASSERT(klab::Equals(xr[13], xt[13], precision))
        TEST_ASSERT(klab::Equals(xr[14], xt[14], precision))
        TEST_ASSERT(klab::Equals(xr[15], xt[15], precision))
        TEST_ASSERT(klab::Equals(xr[16], xt[16], precision))
        TEST_ASSERT(klab::Equals(xr[17], xt[17], precision))
        TEST_ASSERT(klab::Equals(xr[18], xt[18], precision))
        TEST_ASSERT(klab::Equals(xr[19], xt[19], precision))
        TEST_ASSERT(klab::Equals(xr[20], xt[20], precision))
        TEST_ASSERT(klab::Equals(xr[21], xt[21], precision))
        TEST_ASSERT(klab::Equals(xr[22], xt[22], precision))
        TEST_ASSERT(klab::Equals(xr[23], xt[23], precision))
        TEST_ASSERT(klab::Equals(xr[24], xt[24], precision))
        TEST_ASSERT(klab::Equals(xr[25], xt[25], precision))
        TEST_ASSERT(klab::Equals(xr[26], xt[26], precision))
        TEST_ASSERT(klab::Equals(xr[27], xt[27], precision))
        TEST_ASSERT(klab::Equals(xr[28], xt[28], precision))
        TEST_ASSERT(klab::Equals(xr[29], xt[29], precision))
        TEST_ASSERT(klab::Equals(xr[30], xt[30], precision))
        TEST_ASSERT(klab::Equals(xr[31], xt[31], precision))
        TEST_ASSERT(klab::Equals(xr[32], xt[32], precision))
        TEST_ASSERT(klab::Equals(xr[33], xt[33], precision))
        TEST_ASSERT(klab::Equals(xr[34], xt[34], precision))
        TEST_ASSERT(klab::Equals(xr[35], xt[35], precision))
        TEST_ASSERT(klab::Equals(xr[36], xt[36], precision))
        TEST_ASSERT(klab::Equals(xr[37], xt[37], precision))
        TEST_ASSERT(klab::Equals(xr[38], xt[38], precision))
        TEST_ASSERT(klab::Equals(xr[39], xt[39], precision))
        TEST_ASSERT(klab::Equals(xr[40], xt[40], precision))
        TEST_ASSERT(klab::Equals(xr[41], xt[41], precision))
        TEST_ASSERT(klab::Equals(xr[42], xt[42], precision))
        TEST_ASSERT(klab::Equals(xr[43], xt[43], precision))
        TEST_ASSERT(klab::Equals(xr[44], xt[44], precision))
        TEST_ASSERT(klab::Equals(xr[45], xt[45], precision))
        TEST_ASSERT(klab::Equals(xr[46], xt[46], precision))
        TEST_ASSERT(klab::Equals(xr[47], xt[47], precision))
        TEST_ASSERT(klab::Equals(xr[48], xt[48], precision))
        TEST_ASSERT(klab::Equals(xr[49], xt[49], precision))
        TEST_ASSERT(klab::Equals(xr[50], xt[50], precision))
        TEST_ASSERT(klab::Equals(xr[51], xt[51], precision))
        TEST_ASSERT(klab::Equals(xr[52], xt[52], precision))
        TEST_ASSERT(klab::Equals(xr[53], xt[53], precision))
        TEST_ASSERT(klab::Equals(xr[54], xt[54], precision))
        TEST_ASSERT(klab::Equals(xr[55], xt[55], precision))
        TEST_ASSERT(klab::Equals(xr[56], xt[56], precision))
        TEST_ASSERT(klab::Equals(xr[57], xt[57], precision))
        TEST_ASSERT(klab::Equals(xr[58], xt[58], precision))
        TEST_ASSERT(klab::Equals(xr[59], xt[59], precision))
        TEST_ASSERT(klab::Equals(xr[60], xt[60], precision))
        TEST_ASSERT(klab::Equals(xr[61], xt[61], precision))
        TEST_ASSERT(klab::Equals(xr[62], xt[62], precision))
        TEST_ASSERT(klab::Equals(xr[63], xt[63], precision))
        TEST_ASSERT(klab::Equals(xr[64], xt[64], precision))
        TEST_ASSERT(klab::Equals(xr[65], xt[65], precision))
        TEST_ASSERT(klab::Equals(xr[66], xt[66], precision))
        TEST_ASSERT(klab::Equals(xr[67], xt[67], precision))
        TEST_ASSERT(klab::Equals(xr[68], xt[68], precision))
        TEST_ASSERT(klab::Equals(xr[69], xt[69], precision))
        TEST_ASSERT(klab::Equals(xr[70], xt[70], precision))
        TEST_ASSERT(klab::Equals(xr[71], xt[71], precision))
        TEST_ASSERT(klab::Equals(xr[72], xt[72], precision))
        TEST_ASSERT(klab::Equals(xr[73], xt[73], precision))
        TEST_ASSERT(klab::Equals(xr[74], xt[74], precision))
        TEST_ASSERT(klab::Equals(xr[75], xt[75], precision))
        TEST_ASSERT(klab::Equals(xr[76], xt[76], precision))
        TEST_ASSERT(klab::Equals(xr[77], xt[77], precision))
        TEST_ASSERT(klab::Equals(xr[78], xt[78], precision))
        TEST_ASSERT(klab::Equals(xr[79], xt[79], precision))
        TEST_ASSERT(klab::Equals(xr[80], xt[80], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
