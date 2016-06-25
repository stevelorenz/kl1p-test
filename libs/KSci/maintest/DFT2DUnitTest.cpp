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

#include "DFT2DUnitTest.h"
#include "../include/DFT2D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KDFT2DUnitTest::KDFT2DUnitTest() : Test::Suite()
{
    TEST_ADD(KDFT2DUnitTest::testDefaultConstructor)  
    TEST_ADD(KDFT2DUnitTest::testShiftConstructor)
    TEST_ADD(KDFT2DUnitTest::testCopyConstructor)
    TEST_ADD(KDFT2DUnitTest::testAffectationOperator)
    TEST_ADD(KDFT2DUnitTest::testSetShift)
    TEST_ADD(KDFT2DUnitTest::testShift)
    TEST_ADD(KDFT2DUnitTest::testTransform)
    TEST_ADD(KDFT2DUnitTest::testTransform_02)
    TEST_ADD(KDFT2DUnitTest::testTransform_03)
    TEST_ADD(KDFT2DUnitTest::testTransform_04)
    TEST_ADD(KDFT2DUnitTest::testInvert) 
    TEST_ADD(KDFT2DUnitTest::testInvert_Real) 
    TEST_ADD(KDFT2DUnitTest::testInvert_02)
    TEST_ADD(KDFT2DUnitTest::testInvert_02_Real)
    TEST_ADD(KDFT2DUnitTest::testInvert_03)
    TEST_ADD(KDFT2DUnitTest::testInvert_03_Real)
    TEST_ADD(KDFT2DUnitTest::testInvert_04)
    TEST_ADD(KDFT2DUnitTest::testInvert_04_Real)
}

// ---------------------------------------------------------------------------------------------------- //

KDFT2DUnitTest::~KDFT2DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testDefaultConstructor()
{
    try
    {
        TDFT2D<klab::Real> dft;
        TEST_ASSERT(dft.shift() == false)

        TDFT2D<std::complex<klab::Real> > dftc;
        TEST_ASSERT(dftc.shift() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testShiftConstructor()
{
    try
    {
        TDFT2D<klab::Real> dft1(true);
        TEST_ASSERT(dft1.shift() == true)

        TDFT2D<klab::Real> dft2(false);
        TEST_ASSERT(dft2.shift() == false)


        TDFT2D<std::complex<klab::Real> > dft1c(true);
        TEST_ASSERT(dft1c.shift() == true)

        TDFT2D<std::complex<klab::Real> > dft2c(false);
        TEST_ASSERT(dft2c.shift() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testCopyConstructor()
{
    try
    {
        TDFT2D<klab::Real> dft1;
        TEST_ASSERT(dft1.shift() == false)

        TDFT2D<klab::Real> dft2(dft1);
        TEST_ASSERT(dft2.shift() == false)

        TDFT2D<klab::Real> dft3(true);
        TEST_ASSERT(dft3.shift() == true)

        TDFT2D<klab::Real> dft4(dft3);
        TEST_ASSERT(dft4.shift() == true)


        TDFT2D<std::complex<klab::Real> > dft1c;
        TEST_ASSERT(dft1c.shift() == false)

        TDFT2D<std::complex<klab::Real> > dft2c(dft1c);
        TEST_ASSERT(dft2c.shift() == false)

        TDFT2D<std::complex<klab::Real> > dft3c(true);
        TEST_ASSERT(dft3c.shift() == true)

        TDFT2D<std::complex<klab::Real> > dft4c(dft3c);
        TEST_ASSERT(dft4c.shift() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testAffectationOperator()
{
    try
    {
        TDFT2D<klab::Real> dft1;
        TEST_ASSERT(dft1.shift() == false)

        TDFT2D<klab::Real> dft2;
        dft2 = dft1;
        TEST_ASSERT(dft2.shift() == false)

        TDFT2D<klab::Real> dft3(true);
        TEST_ASSERT(dft3.shift() == true)

        TDFT2D<klab::Real> dft4;
        dft4 = dft3;
        TEST_ASSERT(dft4.shift() == true)


        TDFT2D<std::complex<klab::Real> > dft1c;
        TEST_ASSERT(dft1c.shift() == false)

        TDFT2D<std::complex<klab::Real> > dft2c;
        dft2c = dft1c;
        TEST_ASSERT(dft2c.shift() == false)

        TDFT2D<std::complex<klab::Real> > dft3c(true);
        TEST_ASSERT(dft3c.shift() == true)

        TDFT2D<std::complex<klab::Real> > dft4c;
        dft4c = dft3c;
        TEST_ASSERT(dft4c.shift() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testSetShift()
{
    try
    {
        TDFT2D<klab::Real> dft;
        TEST_ASSERT(dft.shift() == false)

        dft.setShift(true);
        TEST_ASSERT(dft.shift() == true)

        dft.setShift(false);
        TEST_ASSERT(dft.shift() == false)


        TDFT2D<std::complex<klab::Real> > dftc;
        TEST_ASSERT(dftc.shift() == false)

        dftc.setShift(true);
        TEST_ASSERT(dftc.shift() == true)

        dftc.setShift(false);
        TEST_ASSERT(dftc.shift() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testShift()
{
    try
    {
        TDFT2D<klab::Real> dft;
        TEST_ASSERT(dft.shift() == false)

        dft.setShift(true);
        TEST_ASSERT(dft.shift() == true)

        dft.setShift(false);
        TEST_ASSERT(dft.shift() == false)


        TDFT2D<std::complex<klab::Real> > dftc;
        TEST_ASSERT(dftc.shift() == false)

        dftc.setShift(true);
        TEST_ASSERT(dftc.shift() == true)

        dftc.setShift(false);
        TEST_ASSERT(dftc.shift() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testTransform()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(8, 8);
        arma::Mat<std::complex<klab::DoubleReal> > F;

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

        klab::DoubleReal precision = 1e-5;

        TDFT2D<std::complex<klab::DoubleReal> > dft;
        dft.transform(f, F);

        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(7952.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(-320.873629022557, 513.86352775479031), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(415.0, 105), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(-127.12637097744299, 75.863527754790312), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(194.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(-127.12637097744299, -75.863527754790312), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(415.0, -105), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(-320.873629022557, -513.86352775479031), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(104.50609665440986, -283.87362902255705), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(-541.93102422918764, -10.159379566434069), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(-93.87867965644034, -258.30003589374985), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(404.42135623730962, -120.29646455628168), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(132.40559159102156, 94.736544032709403), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(289.94112549695433, 68.870057685088824), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(-15.067496474397281, 161.93250352560278), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(13.828427124746156, 241.55129855222074), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(-33.0, -115.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(20.138564286262735, -85.856385079853908), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(116, 154.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(-64.57211383239202, -94.417784899841308), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(39.0, -33), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(131.86143571373725, 223.85638507985391), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(-182.0, -10.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(188.57211383239201, 48.417784899841301), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(63.49390334559012, 90.126370977442974), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(121.5786437626905, -18.296464556281634), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(-140.93250352560273, -36.067496474397274), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(-78.068975770812457, 97.84062043356596), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(71.594408408978438, -127.26345596729058), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(8.1715728752537728, -12.448701447779307), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(-98.12132034355966, -20.300035893749865), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(222.05887450304579, -15.129942314911219), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(170, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(22.422835533724644, 27.121320343559642), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(-97.0, -33.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(77.577164466275349, -22.878679656440358), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(-16.0, 0), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(77.577164466275349, 22.878679656440358), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(-97.0, 33.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(22.422835533724644, -27.121320343559642), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(63.49390334559012, -90.126370977442974), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(222.05887450304579, 15.129942314911219), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(-98.12132034355966, 20.300035893749865), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(8.1715728752537728, 12.448701447779307), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(71.594408408978438, 127.26345596729058), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(-78.068975770812457, -97.84062043356596), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(-140.93250352560273, 36.067496474397274), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(121.5786437626905, 18.296464556281634), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(-33.0, 115.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(188.57211383239201, -48.417784899841301), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(-182, 10.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(131.86143571373725, -223.85638507985391), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(39.0, 33.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(-64.57211383239202, 94.417784899841308), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(116, -154), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(20.138564286262735, 85.856385079853908), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(104.50609665440986, 283.87362902255705), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(13.828427124746156, -241.55129855222074), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(-15.067496474397281, -161.93250352560278), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(289.94112549695433, -68.870057685088824), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(132.40559159102156, -94.736544032709403), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(404.42135623730962, 120.29646455628168), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(-93.87867965644034, 258.30003589374985), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(-541.93102422918764, 10.159379566434069), precision))


        F.fill(0.0);

        TDFT2D<std::complex<klab::DoubleReal> > dft2(true);
        dft2.transform(f, F);

        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(-16.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(77.577164466275349, 22.878679656440358), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(-97.0, 33.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(22.422835533724644, -27.121320343559642), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(170.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(22.422835533724644, 27.121320343559642), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(-97.0, -33.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(77.577164466275349, -22.878679656440358), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(71.594408408978438, 127.26345596729058), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(-78.068975770812457, -97.84062043356596), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(-140.93250352560273, 36.067496474397274), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(121.5786437626905, 18.296464556281634), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(63.49390334559012, -90.126370977442974), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(222.05887450304579, 15.129942314911219), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(-98.12132034355966, 20.300035893749865), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(8.1715728752537728, 12.448701447779307), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(39.0, 33.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(-64.57211383239202, 94.417784899841308), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(116.0, -154.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(20.138564286262735, 85.856385079853908), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(-33.0, 115.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(188.57211383239201, -48.417784899841301), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(-182.0, 10.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(131.86143571373725, -223.85638507985391), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(132.40559159102156, -94.736544032709403), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(404.42135623730962, 120.29646455628168), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(-93.87867965644034, 258.30003589374985), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(-541.93102422918764, 10.159379566434069), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(104.50609665440986, 283.87362902255705), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(13.828427124746156, -241.55129855222074), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(-15.067496474397281, -161.93250352560278), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(289.94112549695433, -68.870057685088824), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(194.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(-127.12637097744299, -75.863527754790312), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(415.0, -105.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(-320.873629022557, -513.86352775479031), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(7952.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(-320.873629022557, 513.86352775479031), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(415.0, 105.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(-127.12637097744299, 75.863527754790312), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(132.40559159102156, 94.736544032709403), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(289.94112549695433, 68.870057685088824), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(-15.067496474397281, 161.93250352560278), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(13.828427124746156, 241.55129855222074), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(104.50609665440986, -283.87362902255705), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(-541.93102422918764, -10.159379566434069), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(-93.87867965644034, -258.30003589374985), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(404.42135623730962, -120.29646455628168), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(39.0, -33.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(131.86143571373725, 223.85638507985391), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(-182.0, -10.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(188.57211383239201, 48.417784899841301), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(-33.0, -115.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(20.138564286262735, -85.856385079853908), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(116.0, 154.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(-64.57211383239202, -94.417784899841308), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(71.594408408978438, -127.26345596729058), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(8.1715728752537728, -12.448701447779307), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(-98.12132034355966, -20.300035893749865), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(222.05887450304579, -15.129942314911219), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(63.49390334559012, 90.126370977442974), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(121.5786437626905, -18.296464556281634), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(-140.93250352560273, -36.067496474397274), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(-78.068975770812457, 97.84062043356596), precision))


        // Limit cases.
        arma::Mat<std::complex<klab::DoubleReal> > f0;
        arma::Mat<std::complex<klab::DoubleReal> > F0;

        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==0)

        TDFT2D<std::complex<klab::DoubleReal> > dft0;
        dft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==0)

        TDFT2D<std::complex<klab::DoubleReal> > dft00(true);
        dft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==0)


        f0.set_size(32, 0);
        f0.fill(0.0);
        dft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows==32 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==32 && F0.n_cols==0)
        dft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows==32 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==32 && F0.n_cols==0)

        f0.set_size(0, 32);
        f0.fill(0.0);
        dft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==32)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==32)
        dft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==32)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==32)


        f0.set_size(8, 8);
        f0.fill(0.0);
        dft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows==8 && f0.n_cols==8)
        TEST_ASSERT(F0.n_rows==8 && F0.n_cols==8)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<8 && areAllZeros; ++i)
        {
            for(klab::UInt32 j=0; j<8 && areAllZeros; ++j)
                areAllZeros = (F0(i, j)==0.0?true:false);
        }
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(8, 8);
        f0.fill(0.0);
        dft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows==8 && f0.n_cols==8)
        TEST_ASSERT(F0.n_rows==8 && F0.n_cols==8)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<8 && areAllZeros; ++i)
        {
            for(klab::UInt32 j=0; j<8 && areAllZeros; ++j)
                areAllZeros = (F0(i, j)==0.0?true:false);
        }
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testTransform_02()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(9, 8);
        arma::Mat<std::complex<klab::DoubleReal> > F;

        f(0, 0) = 152.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 136.0;
        f(0, 4) = 125.0;
        f(0, 5) = 145.0;
        f(0, 6) = 162.0;
        f(0, 7) = 93.0;
        f(1, 0) = 130.0;
        f(1, 1) = 107.0;
        f(1, 2) = 120.0;
        f(1, 3) = 164.0;
        f(1, 4) = 173.0;
        f(1, 5) = 129.0;
        f(1, 6) = 122.0;
        f(1, 7) = 77.0;
        f(2, 0) = 122.0;
        f(2, 1) = 112.0;
        f(2, 2) = 127.0;
        f(2, 3) = 161.0;
        f(2, 4) = 184.0;
        f(2, 5) = 181.0;
        f(2, 6) = 116.0;
        f(2, 7) = 128.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 128.0;
        f(3, 3) = 91.0;
        f(3, 4) = 158.0;
        f(3, 5) = 151.0;
        f(3, 6) = 94.0;
        f(3, 7) = 158.0;
        f(4, 0) = 125.0;
        f(4, 1) = 113.0;
        f(4, 2) = 80.0;
        f(4, 3) = 103.0;
        f(4, 4) = 157.0;
        f(4, 5) = 100.0;
        f(4, 6) = 112.0;
        f(4, 7) = 156.0;
        f(5, 0) = 118.0;
        f(5, 1) = 101.0;
        f(5, 2) = 79.0;
        f(5, 3) = 116.0;
        f(5, 4) = 152.0;
        f(5, 5) = 97.0;
        f(5, 6) = 135.0;
        f(5, 7) = 187.0;
        f(6, 0) = 115.0;
        f(6, 1) = 96.0;
        f(6, 2) = 91.0;
        f(6, 3) = 79.0;
        f(6, 4) = 136.0;
        f(6, 5) = 88.0;
        f(6, 6) = 144.0;
        f(6, 7) = 185.0;
        f(7, 0) = 121.0;
        f(7, 1) = 77.0;
        f(7, 2) = 82.0;
        f(7, 3) = 82.0;
        f(7, 4) = 155.0;
        f(7, 5) = 153.0;
        f(7, 6) = 145.0;
        f(7, 7) = 125.0;
        f(8, 0) = 126.0;
        f(8, 1) = 72.0;
        f(8, 2) = 69.0;
        f(8, 3) = 109.0;
        f(8, 4) = 148.0;
        f(8, 5) = 174.0;
        f(8, 6) = 122.0;
        f(8, 7) = 92.0;

        klab::DoubleReal precision = 1e-5;

        TDFT2D<std::complex<klab::DoubleReal> > dft;
        dft.transform(f, F);

        TEST_ASSERT(F.n_rows==9 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(8945.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(-360.89444430272835, 582.1686142824235), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(467.0, 120.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(-143.10555569727165, 88.168614282423562), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(217.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(-143.10555569727165, -88.168614282423562), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(467.0, -120.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(-360.89444430272835, -582.1686142824235), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(101.60887820272717, -321.67636783418061), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(-609.57819030094788, 18.865900326029674), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(-114.26905175865969, -287.70172424044677), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(447.80318850640106, -158.08740329998597), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(153.70560128302947, 98.69537291477809), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(328.2701177552118, 63.171238914003183), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(-7.6032020951675108, 183.74600428042999), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(27.73128049177933, 272.24774661576191), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(-56.036022377026377, -122.51318145129005), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(13.653897203461, -90.717505404985445), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(155.76995626378152, 155.03394583242817), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(-81.560218859209812, -103.52671189097497), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(40.433220146636351, -43.004597451409126), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(179.54780990302939, 239.68029039136098), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(-199.56545076100747, 3.8369767014121692), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(213.81621895769615, 46.095318936214539), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(41, 103.92304845413263), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(156.64307947320287, -60.097853292251642), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(-160.24871130596426, -4.2679491924311233), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(-94.769097384012269, 116.63428770515961), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(61, -145.4922678357857), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(18.624869719228229, -46.490603975868261), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(-111.75128869403572, 7.7320508075688767), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(273.50114819158114, -41.222744973279489), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(179.4271441742992, -29.467520216201248), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(20.777536128783613, 43.906339592189966), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(-98.678889981604556, -6.0708809917468898), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(84.004609875911541, -31.516858303153601), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(9.8611785703341752, -22.188464643934697), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(-5.7907244570108318, 9.5866524400830535), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(-56.653361667342352, 24.678359618392321), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(17.32447479489468, -22.719175799180444), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(179.4271441742992, 29.467520216201248), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(17.32447479489468, 22.719175799180444), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(-56.653361667342352, -24.678359618392321), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(-5.7907244570108318, -9.5866524400830535), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(9.8611785703341752, 22.188464643934697), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(84.004609875911541, 31.516858303153601), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(-98.678889981604556, 6.0708809917468898), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(20.777536128783613, -43.906339592189966), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(41, -103.92304845413263), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(273.50114819158114, 41.222744973279489), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(-111.75128869403572, -7.7320508075688767), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(18.624869719228229, 46.490603975868261), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(61, 145.4922678357857), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(-94.769097384012269, -116.63428770515961), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(-160.24871130596426, 4.2679491924311233), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(156.64307947320287, 60.097853292251642), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(-56.036022377026377, 122.51318145129005), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(213.81621895769615, -46.095318936214539), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(-199.56545076100747, -3.8369767014121692), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(179.54780990302939, -239.68029039136098), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(40.433220146636351, 43.004597451409126), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(-81.560218859209812, 103.52671189097497), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(155.76995626378152, -155.03394583242817), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(13.653897203461, 90.717505404985445), precision))
        TEST_ASSERT(klab::Equals(F(8, 0), std::complex<klab::DoubleReal>(101.60887820272717, 321.67636783418061), precision))
        TEST_ASSERT(klab::Equals(F(8, 1), std::complex<klab::DoubleReal>(27.73128049177933, -272.24774661576191), precision))
        TEST_ASSERT(klab::Equals(F(8, 2), std::complex<klab::DoubleReal>(-7.6032020951675108, -183.74600428042999), precision))
        TEST_ASSERT(klab::Equals(F(8, 3), std::complex<klab::DoubleReal>(328.2701177552118, -63.171238914003183), precision))
        TEST_ASSERT(klab::Equals(F(8, 4), std::complex<klab::DoubleReal>(153.70560128302947, -98.69537291477809), precision))
        TEST_ASSERT(klab::Equals(F(8, 5), std::complex<klab::DoubleReal>(447.80318850640106, 158.08740329998597), precision))
        TEST_ASSERT(klab::Equals(F(8, 6), std::complex<klab::DoubleReal>(-114.26905175865969, 287.70172424044677), precision))
        TEST_ASSERT(klab::Equals(F(8, 7), std::complex<klab::DoubleReal>(-609.57819030094788, -18.865900326029674), precision))


        F.fill(0.0);

        TDFT2D<std::complex<klab::DoubleReal> > dft2(true);
        dft2.transform(f, F);

        TEST_ASSERT(F.n_rows==9 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(9.8611785703341752, 22.188464643934697), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(84.004609875911541, 31.516858303153601), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(-98.678889981604556, 6.0708809917468898), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(20.777536128783613, -43.906339592189966), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(179.4271441742992, 29.467520216201248), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(17.32447479489468, 22.719175799180444), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(-56.653361667342352, -24.678359618392321), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(-5.7907244570108318, -9.5866524400830535), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(61.0, 145.4922678357857), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(-94.769097384012269, -116.63428770515961), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(-160.24871130596426, 4.2679491924311233), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(156.64307947320287, 60.097853292251642), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(41.0, -103.92304845413263), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(273.50114819158114, 41.222744973279489), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(-111.75128869403572, -7.7320508075688767), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(18.624869719228229, 46.490603975868261), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(40.433220146636351, 43.004597451409126), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(-81.560218859209812, 103.52671189097497), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(155.76995626378152, -155.03394583242817), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(13.653897203461, 90.717505404985445), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(-56.036022377026377, 122.51318145129005), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(213.81621895769615, -46.095318936214539), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(-199.56545076100747, -3.8369767014121692), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(179.54780990302939, -239.68029039136098), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(153.70560128302947, -98.69537291477809), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(447.80318850640106, 158.08740329998597), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(-114.26905175865969, 287.70172424044677), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(-609.57819030094788, -18.865900326029674), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(101.60887820272717, 321.67636783418061), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(27.73128049177933, -272.24774661576191), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(-7.6032020951675108, -183.74600428042999), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(328.2701177552118, -63.171238914003183), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(217.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(-143.10555569727165, -88.168614282423562), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(467.0, -120.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(-360.89444430272835, -582.1686142824235), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(8945.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(-360.89444430272835, 582.1686142824235), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(467.0, 120.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(-143.10555569727165, 88.168614282423562), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(153.70560128302947, 98.69537291477809), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(328.2701177552118, 63.171238914003183), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(-7.6032020951675108, 183.74600428042999), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(27.73128049177933, 272.24774661576191), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(101.60887820272717, -321.67636783418061), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(-609.57819030094788, 18.865900326029674), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(-114.26905175865969, -287.70172424044677), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(447.80318850640106, -158.08740329998597), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(40.433220146636351, -43.004597451409126), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(179.54780990302939, 239.68029039136098), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(-199.56545076100747, 3.8369767014121692), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(213.81621895769615, 46.095318936214539), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(-56.036022377026377, -122.51318145129005), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(13.653897203461, -90.717505404985445), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(155.76995626378152, 155.03394583242817), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(-81.560218859209812, -103.52671189097497), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(61.0, -145.4922678357857), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(18.624869719228229, -46.490603975868261), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(-111.75128869403572, 7.7320508075688767), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(273.50114819158114, -41.222744973279489), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(41.0, 103.92304845413263), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(156.64307947320287, -60.097853292251642), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(-160.24871130596426, -4.2679491924311233), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(-94.769097384012269, 116.63428770515961), precision))
        TEST_ASSERT(klab::Equals(F(8, 0), std::complex<klab::DoubleReal>(9.8611785703341752, -22.188464643934697), precision))
        TEST_ASSERT(klab::Equals(F(8, 1), std::complex<klab::DoubleReal>(-5.7907244570108318, 9.5866524400830535), precision))
        TEST_ASSERT(klab::Equals(F(8, 2), std::complex<klab::DoubleReal>(-56.653361667342352, 24.678359618392321), precision))
        TEST_ASSERT(klab::Equals(F(8, 3), std::complex<klab::DoubleReal>(17.32447479489468, -22.719175799180444), precision))
        TEST_ASSERT(klab::Equals(F(8, 4), std::complex<klab::DoubleReal>(179.4271441742992, -29.467520216201248), precision))
        TEST_ASSERT(klab::Equals(F(8, 5), std::complex<klab::DoubleReal>(20.777536128783613, 43.906339592189966), precision))
        TEST_ASSERT(klab::Equals(F(8, 6), std::complex<klab::DoubleReal>(-98.678889981604556, -6.0708809917468898), precision))
        TEST_ASSERT(klab::Equals(F(8, 7), std::complex<klab::DoubleReal>(84.004609875911541, -31.516858303153601), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testTransform_03()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(8, 9);
        arma::Mat<std::complex<klab::DoubleReal> > F;

        f(0, 0) = 155.0;
        f(0, 1) = 110.0;
        f(0, 2) = 125.0;
        f(0, 3) = 134.0;
        f(0, 4) = 138.0;
        f(0, 5) = 124.0;
        f(0, 6) = 153.0;
        f(0, 7) = 156.0;
        f(0, 8) = 84.0;
        f(1, 0) = 128.0;
        f(1, 1) = 108.0;
        f(1, 2) = 116.0;
        f(1, 3) = 141.0;
        f(1, 4) = 193.0;
        f(1, 5) = 158.0;
        f(1, 6) = 135.0;
        f(1, 7) = 108.0;
        f(1, 8) = 86.0;
        f(2, 0) = 126.0;
        f(2, 1) = 111.0;
        f(2, 2) = 130.0;
        f(2, 3) = 137.0;
        f(2, 4) = 150.0;
        f(2, 5) = 185.0;
        f(2, 6) = 173.0;
        f(2, 7) = 97.0;
        f(2, 8) = 149.0;
        f(3, 0) = 128.0;
        f(3, 1) = 112.0;
        f(3, 2) = 121.0;
        f(3, 3) = 77.0;
        f(3, 4) = 119.0;
        f(3, 5) = 173.0;
        f(3, 6) = 91.0;
        f(3, 7) = 112.0;
        f(3, 8) = 158.0;
        f(4, 0) = 119.0;
        f(4, 1) = 114.0;
        f(4, 2) = 78.0;
        f(4, 3) = 91.0;
        f(4, 4) = 145.0;
        f(4, 5) = 144.0;
        f(4, 6) = 83.0;
        f(4, 7) = 141.0;
        f(4, 8) = 171.0;
        f(5, 0) = 114.0;
        f(5, 1) = 103.0;
        f(5, 2) = 95.0;
        f(5, 3) = 75.0;
        f(5, 4) = 129.0;
        f(5, 5) = 119.0;
        f(5, 6) = 93.0;
        f(5, 7) = 152.0;
        f(5, 8) = 199.0;
        f(6, 0) = 122.0;
        f(6, 1) = 85.0;
        f(6, 2) = 88.0;
        f(6, 3) = 66.0;
        f(6, 4) = 117.0;
        f(6, 5) = 161.0;
        f(6, 6) = 127.0;
        f(6, 7) = 152.0;
        f(6, 8) = 131.0;
        f(7, 0) = 129.0;
        f(7, 1) = 78.0;
        f(7, 2) = 68.0;
        f(7, 3) = 85.0;
        f(7, 4) = 134.0;
        f(7, 5) = 165.0;
        f(7, 6) = 163.0;
        f(7, 7) = 122.0;
        f(7, 8) = 90.0;

        klab::DoubleReal precision = 1e-5;

        TDFT2D<std::complex<klab::DoubleReal> > dft;
        dft.transform(f, F);

        TEST_ASSERT(F.n_rows==8 && F.n_cols==9)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(8949.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(-332.81921764012145, 593.6089180104193), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(491.5220594323302, 67.702629372635784), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(-207.0, 114.31535329954589), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(168.29715820779123, 24.885868169119391), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(168.29715820779123, -24.885868169119391), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(-207.0, -114.31535329954589), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(491.5220594323302, -67.702629372635784), precision))
        TEST_ASSERT(klab::Equals(F(0, 8), std::complex<klab::DoubleReal>(-332.81921764012145, -593.6089180104193), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(119.16295090390227, -315.77312395916863), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(-611.96450834999723, 18.381666635380924), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(-141.72577216617736, -263.00793582906306), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(474.23421402133113, -243.77587317335971), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(201.44453535914795, 120.44203629487259), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(137.05581757016864, 19.570567692228849), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(284.23086481737414, 109.57486304658309), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(-45.182562457885055, 170.43036740334105), precision))
        TEST_ASSERT(klab::Equals(F(1, 8), std::complex<klab::DoubleReal>(2.2038757623195693, 265.42593849035882), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(-42.0, -127.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(13.7686475130334, -94.901082334318147), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(138.98575875719237, 162.15797410395635), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(-105.19099764656376, -137.86533479473209), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(120.33834918851534, 4.8139103657097095), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(-2.949945698077606, 85.871796263362882), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(99.190997646563758, 225.86533479473209), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(-200.95309360981403, -46.347382207776676), precision))
        TEST_ASSERT(klab::Equals(F(2, 8), std::complex<klab::DoubleReal>(212.81028384915049, 62.40478380906594), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(66.837049096097729, 102.22687604083131), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(140.44674975160183, -19.659553226959332), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(-158.07230609357828, -26.947788431350983), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(-68.794929422884323, 152.72361136217489), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(-15.072994585370026, -115.51020959343981), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(107.84577432760213, -128.10561421190533), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(18.329850584179109, 21.075378511048427), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(-116.00386576487686, -29.545551412997046), precision))
        TEST_ASSERT(klab::Equals(F(3, 8), std::complex<klab::DoubleReal>(253.02525664704478, -2.9886424362282042), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(195.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(24.195258415618071, 31.274236033661083), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(-113.8681051074592, -25.030111605726503), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(93, -20.784609690826528), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(2.6728466918411229, -45.912042793974329), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(2.6728466918411229, 45.912042793974329), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(93, 20.784609690826528), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(-113.8681051074592, 25.030111605726503), precision))
        TEST_ASSERT(klab::Equals(F(4, 8), std::complex<klab::DoubleReal>(24.195258415618071, -31.274236033661083), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(66.837049096097729, -102.22687604083131), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(253.02525664704478, 2.9886424362282042), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(-116.00386576487686, 29.545551412997046), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(18.329850584179109, -21.075378511048427), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(107.84577432760213, 128.10561421190533), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(-15.072994585370026, 115.51020959343981), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(-68.794929422884323, -152.72361136217489), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(-158.07230609357828, 26.947788431350983), precision))
        TEST_ASSERT(klab::Equals(F(5, 8), std::complex<klab::DoubleReal>(140.44674975160183, 19.659553226959332), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(-42.0, 127.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(212.81028384915049, -62.40478380906594), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(-200.95309360981403, 46.347382207776676), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(99.190997646563758, -225.86533479473209), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(-2.949945698077606, -85.871796263362882), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(120.33834918851534, -4.8139103657097095), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(-105.19099764656376, 137.86533479473209), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(138.98575875719237, -162.15797410395635), precision))
        TEST_ASSERT(klab::Equals(F(6, 8), std::complex<klab::DoubleReal>(13.7686475130334, 94.901082334318147), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(119.16295090390227, 315.77312395916863), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(2.2038757623195693, -265.42593849035882), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(-45.182562457885055, -170.43036740334105), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(284.23086481737414, -109.57486304658309), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(137.05581757016864, -19.570567692228849), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(201.44453535914795, -120.44203629487259), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(474.23421402133113, 243.77587317335971), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(-141.72577216617736, 263.00793582906306), precision))
        TEST_ASSERT(klab::Equals(F(7, 8), std::complex<klab::DoubleReal>(-611.96450834999723, -18.381666635380924), precision))


        F.fill(0.0);

        TDFT2D<std::complex<klab::DoubleReal> > dft2(true);
        dft2.transform(f, F);

        TEST_ASSERT(F.n_rows==8 && F.n_cols==9)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(2.6728466918411229, 45.912042793974329), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(93, 20.784609690826528), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(-113.8681051074592, 25.030111605726503), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(24.195258415618071, -31.274236033661083), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(195.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(24.195258415618071, 31.274236033661083), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(-113.8681051074592, -25.030111605726503), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(93.0, -20.784609690826528), precision))
        TEST_ASSERT(klab::Equals(F(0, 8), std::complex<klab::DoubleReal>(2.6728466918411229, -45.912042793974329), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(-15.072994585370026, 115.51020959343981), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(-68.794929422884323, -152.72361136217489), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(-158.07230609357828, 26.947788431350983), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(140.44674975160183, 19.659553226959332), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(66.837049096097729, -102.22687604083131), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(253.02525664704478, 2.9886424362282042), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(-116.00386576487686, 29.545551412997046), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(18.329850584179109, -21.075378511048427), precision))
        TEST_ASSERT(klab::Equals(F(1, 8), std::complex<klab::DoubleReal>(107.84577432760213, 128.10561421190533), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(120.33834918851534, -4.8139103657097095), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(-105.19099764656376, 137.86533479473209), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(138.98575875719237, -162.15797410395635), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(13.7686475130334, 94.901082334318147), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(-42.0, 127.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(212.81028384915049, -62.40478380906594), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(-200.95309360981403, 46.347382207776676), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(99.190997646563758, -225.86533479473209), precision))
        TEST_ASSERT(klab::Equals(F(2, 8), std::complex<klab::DoubleReal>(-2.949945698077606, -85.871796263362882), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(201.44453535914795, -120.44203629487259), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(474.23421402133113, 243.77587317335971), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(-141.72577216617736, 263.00793582906306), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(-611.96450834999723, -18.381666635380924), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(119.16295090390227, 315.77312395916863), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(2.2038757623195693, -265.42593849035882), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(-45.182562457885055, -170.43036740334105), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(284.23086481737414, -109.57486304658309), precision))
        TEST_ASSERT(klab::Equals(F(3, 8), std::complex<klab::DoubleReal>(137.05581757016864, -19.570567692228849), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(168.29715820779123, -24.885868169119391), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(-207.0, -114.31535329954589), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(491.5220594323302, -67.702629372635784), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(-332.81921764012145, -593.6089180104193), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(8949.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(-332.81921764012145, 593.6089180104193), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(491.5220594323302, 67.702629372635784), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(-207.0, 114.31535329954589), precision))
        TEST_ASSERT(klab::Equals(F(4, 8), std::complex<klab::DoubleReal>(168.29715820779123, 24.885868169119391), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(137.05581757016864, 19.570567692228849), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(284.23086481737414, 109.57486304658309), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(-45.182562457885055, 170.43036740334105), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(2.2038757623195693, 265.42593849035882), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(119.16295090390227, -315.77312395916863), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(-611.96450834999723, 18.381666635380924), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(-141.72577216617736, -263.00793582906306), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(474.23421402133113, -243.77587317335971), precision))
        TEST_ASSERT(klab::Equals(F(5, 8), std::complex<klab::DoubleReal>(201.44453535914795, 120.44203629487259), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(-2.949945698077606, 85.871796263362882), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(99.190997646563758, 225.86533479473209), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(-200.95309360981403, -46.347382207776676), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(212.81028384915049, 62.40478380906594), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(-42.0, -127.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(13.7686475130334, -94.901082334318147), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(138.98575875719237, 162.15797410395635), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(-105.19099764656376, -137.86533479473209), precision))
        TEST_ASSERT(klab::Equals(F(6, 8), std::complex<klab::DoubleReal>(120.33834918851534, 4.8139103657097095), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(107.84577432760213, -128.10561421190533), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(18.329850584179109, 21.075378511048427), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(-116.00386576487686, -29.545551412997046), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(253.02525664704478, -2.9886424362282042), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(66.837049096097729, 102.22687604083131), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(140.44674975160183, -19.659553226959332), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(-158.07230609357828, -26.947788431350983), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(-68.794929422884323, 152.72361136217489), precision))
        TEST_ASSERT(klab::Equals(F(7, 8), std::complex<klab::DoubleReal>(-15.072994585370026, -115.51020959343981), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testTransform_04()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(9, 9);
        arma::Mat<std::complex<klab::DoubleReal> > F;

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

        klab::DoubleReal precision = 1e-5;

        TDFT2D<std::complex<klab::DoubleReal> > dft;
        dft.transform(f, F);

        TEST_ASSERT(F.n_rows==9 && F.n_cols==9)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(10066.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(-374.3423341787049, 667.89088823953989), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(552.2717149955887, 76.515784489223876), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(-230.0, 124.70765814495915), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(189.57061918311629, 24.368958340419823), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(189.57061918311629, -24.368958340419823), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(-230.0, -124.70765814495915), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(552.2717149955887, -76.515784489223876), precision))
        TEST_ASSERT(klab::Equals(F(0, 8), std::complex<klab::DoubleReal>(-374.3423341787049, -667.89088823953989), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(117.87997508542273, -363.43183697248298), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(-687.42912491197262, 53.538429927932057), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(-171.9624054303477, -293.08836157392977), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(523.26775279990397, -299.65112220697637), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(231.76718612458581, 126.13275214685747), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(150.95660101976142, 16.452226880972532), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(326.02035550828754, 109.64397618890843), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(-44.608811491595972, 194.82799327456391), precision))
        TEST_ASSERT(klab::Equals(F(1, 8), std::complex<klab::DoubleReal>(12.705039040453642, 307.18293287357869), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(-63.808930259743768, -136.41397733285621), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(5.8585074197023062, -103.24580941040561), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(183.19051259818983, 162.11721275999128), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(-132.73068054383364, -149.73381106297671), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(147.83795938851387, -4.0160701359317912), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(-0.066075038557087851, 97.518896117417285), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(141.61393425590839, 253.65689803279901), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(-226.3150784795757, -35.748752874213835), precision))
        TEST_ASSERT(klab::Equals(F(2, 8), std::complex<klab::DoubleReal>(240.95318830307971, 59.323871613405814), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(47.5, 125.57368354874359), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(177.21137573372769, -71.760445211762089), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(-187.73908703530759, 15.132655596564057), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(-78.499999999999986, 182.73136019851654), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(-25.79469065278721, -135.53594608405268), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(86.962563124764159, -163.84958289572609), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(42.999999999999986, -6.9282032302755141), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(-143.91668508094045, 2.048370598902828), precision))
        TEST_ASSERT(klab::Equals(F(3, 8), std::complex<klab::DoubleReal>(310.77652391054346, -33.14840749557009), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(202.428955174321, -24.995532861644872), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(26.674886530153039, 48.183170678639023), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(-107.3151084394637, 7.6076980649342989), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(77.618312944187622, -31.259127314720729), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(-49.261387686217113, -49.903866060493037), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(65.110039439122119, 23.397060053025122), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(0.21032503554607729, -7.3643947506135259), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(-72.220374427665519, 24.123786863914404), precision))
        TEST_ASSERT(klab::Equals(F(4, 8), std::complex<klab::DoubleReal>(19.624446041833814, -25.294930135753141), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(202.428955174321, 24.995532861644872), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(19.624446041833814, 25.294930135753141), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(-72.220374427665519, -24.123786863914404), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(0.21032503554607729, 7.3643947506135259), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(65.110039439122119, -23.397060053025122), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(-49.261387686217113, 49.903866060493037), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(77.618312944187622, 31.259127314720729), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(-107.3151084394637, -7.6076980649342989), precision))
        TEST_ASSERT(klab::Equals(F(5, 8), std::complex<klab::DoubleReal>(26.674886530153039, -48.183170678639023), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(47.5, -125.57368354874359), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(310.77652391054346, 33.14840749557009), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(-143.91668508094045, -2.048370598902828), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(42.999999999999986, 6.9282032302755141), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(86.962563124764159, 163.84958289572609), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(-25.79469065278721, 135.53594608405268), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(-78.499999999999986, -182.73136019851654), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(-187.73908703530759, -15.132655596564057), precision))
        TEST_ASSERT(klab::Equals(F(6, 8), std::complex<klab::DoubleReal>(177.21137573372769, 71.760445211762089), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(-63.808930259743768, 136.41397733285621), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(240.95318830307971, -59.323871613405814), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(-226.3150784795757, 35.748752874213835), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(141.61393425590839, -253.65689803279901), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(-0.066075038557087851, -97.518896117417285), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(147.83795938851387, 4.0160701359317912), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(-132.73068054383364, 149.73381106297671), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(183.19051259818983, -162.11721275999128), precision))
        TEST_ASSERT(klab::Equals(F(7, 8), std::complex<klab::DoubleReal>(5.8585074197023062, 103.24580941040561), precision))
        TEST_ASSERT(klab::Equals(F(8, 0), std::complex<klab::DoubleReal>(117.87997508542273, 363.43183697248298), precision))
        TEST_ASSERT(klab::Equals(F(8, 1), std::complex<klab::DoubleReal>(12.705039040453642, -307.18293287357869), precision))
        TEST_ASSERT(klab::Equals(F(8, 2), std::complex<klab::DoubleReal>(-44.608811491595972, -194.82799327456391), precision))
        TEST_ASSERT(klab::Equals(F(8, 3), std::complex<klab::DoubleReal>(326.02035550828754, -109.64397618890843), precision))
        TEST_ASSERT(klab::Equals(F(8, 4), std::complex<klab::DoubleReal>(150.95660101976142, -16.452226880972532), precision))
        TEST_ASSERT(klab::Equals(F(8, 5), std::complex<klab::DoubleReal>(231.76718612458581, -126.13275214685747), precision))
        TEST_ASSERT(klab::Equals(F(8, 6), std::complex<klab::DoubleReal>(523.26775279990397, 299.65112220697637), precision))
        TEST_ASSERT(klab::Equals(F(8, 7), std::complex<klab::DoubleReal>(-171.9624054303477, 293.08836157392977), precision))
        TEST_ASSERT(klab::Equals(F(8, 8), std::complex<klab::DoubleReal>(-687.42912491197262, -53.538429927932057), precision))


        F.fill(0.0);

        TDFT2D<std::complex<klab::DoubleReal> > dft2(true);
        dft2.transform(f, F);

        TEST_ASSERT(F.n_rows==9 && F.n_cols==9)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(-49.261387686217113, 49.903866060493037), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(77.618312944187622, 31.259127314720729), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(-107.3151084394637, -7.6076980649342989), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(26.674886530153039, -48.183170678639023), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(202.428955174321, 24.995532861644872), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(19.624446041833814, 25.294930135753141), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(-72.220374427665519, -24.123786863914404), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(0.21032503554607729, 7.3643947506135259), precision))
        TEST_ASSERT(klab::Equals(F(0, 8), std::complex<klab::DoubleReal>(65.110039439122119, -23.397060053025122), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(-25.79469065278721, 135.53594608405268), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(-78.499999999999986, -182.73136019851654), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(-187.73908703530759, -15.132655596564057), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(177.21137573372769, 71.760445211762089), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(47.5, -125.57368354874359), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(310.77652391054346, 33.14840749557009), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(-143.91668508094045, -2.048370598902828), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(42.999999999999986, 6.9282032302755141), precision))
        TEST_ASSERT(klab::Equals(F(1, 8), std::complex<klab::DoubleReal>(86.962563124764159, 163.84958289572609), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(147.83795938851387, 4.0160701359317912), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(-132.73068054383364, 149.73381106297671), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(183.19051259818983, -162.11721275999128), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(5.8585074197023062, 103.24580941040561), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(-63.808930259743768, 136.41397733285621), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(240.95318830307971, -59.323871613405814), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(-226.3150784795757, 35.748752874213835), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(141.61393425590839, -253.65689803279901), precision))
        TEST_ASSERT(klab::Equals(F(2, 8), std::complex<klab::DoubleReal>(-0.066075038557087851, -97.518896117417285), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(231.76718612458581, -126.13275214685747), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(523.26775279990397, 299.65112220697637), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(-171.9624054303477, 293.08836157392977), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(-687.42912491197262, -53.538429927932057), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(117.87997508542273, 363.43183697248298), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(12.705039040453642, -307.18293287357869), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(-44.608811491595972, -194.82799327456391), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(326.02035550828754, -109.64397618890843), precision))
        TEST_ASSERT(klab::Equals(F(3, 8), std::complex<klab::DoubleReal>(150.95660101976142, -16.452226880972532), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(189.57061918311629, -24.368958340419823), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(-230.0, -124.70765814495915), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(552.2717149955887, -76.515784489223876), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(-374.3423341787049, -667.89088823953989), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(10066.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(-374.3423341787049, 667.89088823953989), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(552.2717149955887, 76.515784489223876), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(-230.0, 124.70765814495915), precision))
        TEST_ASSERT(klab::Equals(F(4, 8), std::complex<klab::DoubleReal>(189.57061918311629, 24.368958340419823), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(150.95660101976142, 16.452226880972532), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(326.02035550828754, 109.64397618890843), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(-44.608811491595972, 194.82799327456391), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(12.705039040453642, 307.18293287357869), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(117.87997508542273, -363.43183697248298), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(-687.42912491197262, 53.538429927932057), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(-171.9624054303477, -293.08836157392977), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(523.26775279990397, -299.65112220697637), precision))
        TEST_ASSERT(klab::Equals(F(5, 8), std::complex<klab::DoubleReal>(231.76718612458581, 126.13275214685747), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(-0.066075038557087851, 97.518896117417285), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(141.61393425590839, 253.65689803279901), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(-226.3150784795757, -35.748752874213835), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(240.95318830307971, 59.323871613405814), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(-63.808930259743768, -136.41397733285621), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(5.8585074197023062, -103.24580941040561), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(183.19051259818983, 162.11721275999128), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(-132.73068054383364, -149.73381106297671), precision))
        TEST_ASSERT(klab::Equals(F(6, 8), std::complex<klab::DoubleReal>(147.83795938851387, -4.0160701359317912), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(86.962563124764159, -163.84958289572609), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(42.999999999999986, -6.9282032302755141), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(-143.91668508094045, 2.048370598902828), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(310.77652391054346, -33.14840749557009), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(47.5, 125.57368354874359), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(177.21137573372769, -71.760445211762089), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(-187.73908703530759, 15.132655596564057), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(-78.499999999999986, 182.73136019851654), precision))
        TEST_ASSERT(klab::Equals(F(7, 8), std::complex<klab::DoubleReal>(-25.79469065278721, -135.53594608405268), precision))
        TEST_ASSERT(klab::Equals(F(8, 0), std::complex<klab::DoubleReal>(65.110039439122119, 23.397060053025122), precision))
        TEST_ASSERT(klab::Equals(F(8, 1), std::complex<klab::DoubleReal>(0.21032503554607729, -7.3643947506135259), precision))
        TEST_ASSERT(klab::Equals(F(8, 2), std::complex<klab::DoubleReal>(-72.220374427665519, 24.123786863914404), precision))
        TEST_ASSERT(klab::Equals(F(8, 3), std::complex<klab::DoubleReal>(19.624446041833814, -25.294930135753141), precision))
        TEST_ASSERT(klab::Equals(F(8, 4), std::complex<klab::DoubleReal>(202.428955174321, -24.995532861644872), precision))
        TEST_ASSERT(klab::Equals(F(8, 5), std::complex<klab::DoubleReal>(26.674886530153039, 48.183170678639023), precision))
        TEST_ASSERT(klab::Equals(F(8, 6), std::complex<klab::DoubleReal>(-107.3151084394637, 7.6076980649342989), precision))
        TEST_ASSERT(klab::Equals(F(8, 7), std::complex<klab::DoubleReal>(77.618312944187622, -31.259127314720729), precision))
        TEST_ASSERT(klab::Equals(F(8, 8), std::complex<klab::DoubleReal>(-49.261387686217113, -49.903866060493037), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testInvert()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(8, 8);
        arma::Mat<std::complex<klab::DoubleReal> > F;
        arma::Mat<std::complex<klab::DoubleReal> > fR;

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


        klab::DoubleReal precision = 1e-5;

        TDFT2D<std::complex<klab::DoubleReal> > dft;
        dft.transform(f, F);
        dft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        F.fill(0.0);
        fR.fill(0.0);

        TDFT2D<std::complex<klab::DoubleReal> > dft2(true);
        dft2.transform(f, F);
        dft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        // Limit cases.
        arma::Mat<std::complex<klab::DoubleReal> > f0;
        arma::Mat<std::complex<klab::DoubleReal> > F0;
        arma::Mat<std::complex<klab::DoubleReal> > fR0;

        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==0)

        TDFT2D<std::complex<klab::DoubleReal> > dft0;
        dft0.transform(f0, F0);
        dft0.invert(F0, f0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==0)

        TDFT2D<std::complex<klab::DoubleReal> > dft00(true);
        dft00.transform(f0, F0);
        dft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==0)


        f0.set_size(32, 0);
        f0.fill(0.0);
        dft0.transform(f0, F0);
        dft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==32 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==32 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==32 && fR0.n_cols==0)
        dft00.transform(f0, F0);
        dft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==32 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==32 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==32 && fR0.n_cols==0)

        f0.set_size(0, 32);
        f0.fill(0.0);
        dft0.transform(f0, F0);
        dft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==32)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==32)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==32)
        dft00.transform(f0, F0);
        dft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==32)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==32)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==32)


        f0.set_size(8, 8);
        f0.fill(0.0);
        dft0.transform(f0, F0);
        dft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==8 && f0.n_cols==8)
        TEST_ASSERT(F0.n_rows==8 && F0.n_cols==8)
        TEST_ASSERT(fR0.n_rows==8 && fR0.n_cols==8)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<8 && areAllZeros; ++i)
        {
            for(klab::UInt32 j=0; j<8 && areAllZeros; ++j)
                areAllZeros = (fR0(i, j)==0.0?true:false);
        }
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(8, 8);
        f0.fill(0.0);
        dft00.transform(f0, F0);
        dft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==8 && f0.n_cols==8)
        TEST_ASSERT(F0.n_rows==8 && F0.n_cols==8)
        TEST_ASSERT(fR0.n_rows==8 && fR0.n_cols==8)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<8 && areAllZeros; ++i)
        {
            for(klab::UInt32 j=0; j<8 && areAllZeros; ++j)
                areAllZeros = (fR0(i, j)==0.0?true:false);
        }
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testInvert_Real()
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


        klab::DoubleReal precision = 1e-5;

        TDFT2D<klab::DoubleReal> dft;
        dft.transform(f, F);
        dft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        F.fill(0.0);
        fR.fill(0.0);

        TDFT2D<klab::DoubleReal> dft2(true);
        dft2.transform(f, F);
        dft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))


        // Limit cases.
        arma::Mat<klab::DoubleReal> f0;
        arma::Mat<klab::DoubleReal> F0;
        arma::Mat<klab::DoubleReal> fR0;

        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==0)

        TDFT2D<klab::DoubleReal> dft0;
        dft0.transform(f0, F0);
        dft0.invert(F0, f0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==0)

        TDFT2D<klab::DoubleReal> dft00(true);
        dft00.transform(f0, F0);
        dft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==0)


        f0.set_size(32, 0);
        f0.fill(0.0);
        dft0.transform(f0, F0);
        dft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==32 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==32 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==32 && fR0.n_cols==0)
        dft00.transform(f0, F0);
        dft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==32 && f0.n_cols==0)
        TEST_ASSERT(F0.n_rows==32 && F0.n_cols==0)
        TEST_ASSERT(fR0.n_rows==32 && fR0.n_cols==0)

        f0.set_size(0, 32);
        f0.fill(0.0);
        dft0.transform(f0, F0);
        dft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==32)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==32)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==32)
        dft00.transform(f0, F0);
        dft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==0 && f0.n_cols==32)
        TEST_ASSERT(F0.n_rows==0 && F0.n_cols==32)
        TEST_ASSERT(fR0.n_rows==0 && fR0.n_cols==32)


        f0.set_size(8, 8);
        f0.fill(0.0);
        dft0.transform(f0, F0);
        dft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==8 && f0.n_cols==8)
        TEST_ASSERT(F0.n_rows==8 && F0.n_cols==8)
        TEST_ASSERT(fR0.n_rows==8 && fR0.n_cols==8)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<8 && areAllZeros; ++i)
        {
            for(klab::UInt32 j=0; j<8 && areAllZeros; ++j)
                areAllZeros = (fR0(i, j)==0.0?true:false);
        }
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(8, 8);
        f0.fill(0.0);
        dft00.transform(f0, F0);
        dft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows==8 && f0.n_cols==8)
        TEST_ASSERT(F0.n_rows==8 && F0.n_cols==8)
        TEST_ASSERT(fR0.n_rows==8 && fR0.n_cols==8)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<8 && areAllZeros; ++i)
        {
            for(klab::UInt32 j=0; j<8 && areAllZeros; ++j)
                areAllZeros = (fR0(i, j)==0.0?true:false);
        }
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testInvert_02()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(9, 8);
        arma::Mat<std::complex<klab::DoubleReal> > F;
        arma::Mat<std::complex<klab::DoubleReal> > fR;

        f(0, 0) = 152.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 136.0;
        f(0, 4) = 125.0;
        f(0, 5) = 145.0;
        f(0, 6) = 162.0;
        f(0, 7) = 93.0;
        f(1, 0) = 130.0;
        f(1, 1) = 107.0;
        f(1, 2) = 120.0;
        f(1, 3) = 164.0;
        f(1, 4) = 173.0;
        f(1, 5) = 129.0;
        f(1, 6) = 122.0;
        f(1, 7) = 77.0;
        f(2, 0) = 122.0;
        f(2, 1) = 112.0;
        f(2, 2) = 127.0;
        f(2, 3) = 161.0;
        f(2, 4) = 184.0;
        f(2, 5) = 181.0;
        f(2, 6) = 116.0;
        f(2, 7) = 128.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 128.0;
        f(3, 3) = 91.0;
        f(3, 4) = 158.0;
        f(3, 5) = 151.0;
        f(3, 6) = 94.0;
        f(3, 7) = 158.0;
        f(4, 0) = 125.0;
        f(4, 1) = 113.0;
        f(4, 2) = 80.0;
        f(4, 3) = 103.0;
        f(4, 4) = 157.0;
        f(4, 5) = 100.0;
        f(4, 6) = 112.0;
        f(4, 7) = 156.0;
        f(5, 0) = 118.0;
        f(5, 1) = 101.0;
        f(5, 2) = 79.0;
        f(5, 3) = 116.0;
        f(5, 4) = 152.0;
        f(5, 5) = 97.0;
        f(5, 6) = 135.0;
        f(5, 7) = 187.0;
        f(6, 0) = 115.0;
        f(6, 1) = 96.0;
        f(6, 2) = 91.0;
        f(6, 3) = 79.0;
        f(6, 4) = 136.0;
        f(6, 5) = 88.0;
        f(6, 6) = 144.0;
        f(6, 7) = 185.0;
        f(7, 0) = 121.0;
        f(7, 1) = 77.0;
        f(7, 2) = 82.0;
        f(7, 3) = 82.0;
        f(7, 4) = 155.0;
        f(7, 5) = 153.0;
        f(7, 6) = 145.0;
        f(7, 7) = 125.0;
        f(8, 0) = 126.0;
        f(8, 1) = 72.0;
        f(8, 2) = 69.0;
        f(8, 3) = 109.0;
        f(8, 4) = 148.0;
        f(8, 5) = 174.0;
        f(8, 6) = 122.0;
        f(8, 7) = 92.0;


        klab::DoubleReal precision = 1e-5;

        TDFT2D<std::complex<klab::DoubleReal> > dft;
        dft.transform(f, F);
        dft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(8, 0), f(8, 0), precision))
        TEST_ASSERT(klab::Equals(fR(8, 1), f(8, 1), precision))
        TEST_ASSERT(klab::Equals(fR(8, 2), f(8, 2), precision))
        TEST_ASSERT(klab::Equals(fR(8, 3), f(8, 3), precision))
        TEST_ASSERT(klab::Equals(fR(8, 4), f(8, 4), precision))
        TEST_ASSERT(klab::Equals(fR(8, 5), f(8, 5), precision))
        TEST_ASSERT(klab::Equals(fR(8, 6), f(8, 6), precision))
        TEST_ASSERT(klab::Equals(fR(8, 7), f(8, 7), precision))



        F.fill(0.0);
        fR.fill(0.0);

        TDFT2D<std::complex<klab::DoubleReal> > dft2(true);
        dft2.transform(f, F);
        dft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(8, 0), f(8, 0), precision))
        TEST_ASSERT(klab::Equals(fR(8, 1), f(8, 1), precision))
        TEST_ASSERT(klab::Equals(fR(8, 2), f(8, 2), precision))
        TEST_ASSERT(klab::Equals(fR(8, 3), f(8, 3), precision))
        TEST_ASSERT(klab::Equals(fR(8, 4), f(8, 4), precision))
        TEST_ASSERT(klab::Equals(fR(8, 5), f(8, 5), precision))
        TEST_ASSERT(klab::Equals(fR(8, 6), f(8, 6), precision))
        TEST_ASSERT(klab::Equals(fR(8, 7), f(8, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}


// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testInvert_02_Real()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(9, 8);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;

        f(0, 0) = 152.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 136.0;
        f(0, 4) = 125.0;
        f(0, 5) = 145.0;
        f(0, 6) = 162.0;
        f(0, 7) = 93.0;
        f(1, 0) = 130.0;
        f(1, 1) = 107.0;
        f(1, 2) = 120.0;
        f(1, 3) = 164.0;
        f(1, 4) = 173.0;
        f(1, 5) = 129.0;
        f(1, 6) = 122.0;
        f(1, 7) = 77.0;
        f(2, 0) = 122.0;
        f(2, 1) = 112.0;
        f(2, 2) = 127.0;
        f(2, 3) = 161.0;
        f(2, 4) = 184.0;
        f(2, 5) = 181.0;
        f(2, 6) = 116.0;
        f(2, 7) = 128.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 128.0;
        f(3, 3) = 91.0;
        f(3, 4) = 158.0;
        f(3, 5) = 151.0;
        f(3, 6) = 94.0;
        f(3, 7) = 158.0;
        f(4, 0) = 125.0;
        f(4, 1) = 113.0;
        f(4, 2) = 80.0;
        f(4, 3) = 103.0;
        f(4, 4) = 157.0;
        f(4, 5) = 100.0;
        f(4, 6) = 112.0;
        f(4, 7) = 156.0;
        f(5, 0) = 118.0;
        f(5, 1) = 101.0;
        f(5, 2) = 79.0;
        f(5, 3) = 116.0;
        f(5, 4) = 152.0;
        f(5, 5) = 97.0;
        f(5, 6) = 135.0;
        f(5, 7) = 187.0;
        f(6, 0) = 115.0;
        f(6, 1) = 96.0;
        f(6, 2) = 91.0;
        f(6, 3) = 79.0;
        f(6, 4) = 136.0;
        f(6, 5) = 88.0;
        f(6, 6) = 144.0;
        f(6, 7) = 185.0;
        f(7, 0) = 121.0;
        f(7, 1) = 77.0;
        f(7, 2) = 82.0;
        f(7, 3) = 82.0;
        f(7, 4) = 155.0;
        f(7, 5) = 153.0;
        f(7, 6) = 145.0;
        f(7, 7) = 125.0;
        f(8, 0) = 126.0;
        f(8, 1) = 72.0;
        f(8, 2) = 69.0;
        f(8, 3) = 109.0;
        f(8, 4) = 148.0;
        f(8, 5) = 174.0;
        f(8, 6) = 122.0;
        f(8, 7) = 92.0;


        klab::DoubleReal precision = 1e-5;

        TDFT2D<klab::DoubleReal> dft;
        dft.transform(f, F);
        dft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(8, 0), f(8, 0), precision))
        TEST_ASSERT(klab::Equals(fR(8, 1), f(8, 1), precision))
        TEST_ASSERT(klab::Equals(fR(8, 2), f(8, 2), precision))
        TEST_ASSERT(klab::Equals(fR(8, 3), f(8, 3), precision))
        TEST_ASSERT(klab::Equals(fR(8, 4), f(8, 4), precision))
        TEST_ASSERT(klab::Equals(fR(8, 5), f(8, 5), precision))
        TEST_ASSERT(klab::Equals(fR(8, 6), f(8, 6), precision))
        TEST_ASSERT(klab::Equals(fR(8, 7), f(8, 7), precision))



        F.fill(0.0);
        fR.fill(0.0);

        TDFT2D<klab::DoubleReal> dft2(true);
        dft2.transform(f, F);
        dft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==8)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(8, 0), f(8, 0), precision))
        TEST_ASSERT(klab::Equals(fR(8, 1), f(8, 1), precision))
        TEST_ASSERT(klab::Equals(fR(8, 2), f(8, 2), precision))
        TEST_ASSERT(klab::Equals(fR(8, 3), f(8, 3), precision))
        TEST_ASSERT(klab::Equals(fR(8, 4), f(8, 4), precision))
        TEST_ASSERT(klab::Equals(fR(8, 5), f(8, 5), precision))
        TEST_ASSERT(klab::Equals(fR(8, 6), f(8, 6), precision))
        TEST_ASSERT(klab::Equals(fR(8, 7), f(8, 7), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testInvert_03()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(8, 9);
        arma::Mat<std::complex<klab::DoubleReal> > F;
        arma::Mat<std::complex<klab::DoubleReal> > fR;

        f(0, 0) = 155.0;
        f(0, 1) = 110.0;
        f(0, 2) = 125.0;
        f(0, 3) = 134.0;
        f(0, 4) = 138.0;
        f(0, 5) = 124.0;
        f(0, 6) = 153.0;
        f(0, 7) = 156.0;
        f(0, 8) = 84.0;
        f(1, 0) = 128.0;
        f(1, 1) = 108.0;
        f(1, 2) = 116.0;
        f(1, 3) = 141.0;
        f(1, 4) = 193.0;
        f(1, 5) = 158.0;
        f(1, 6) = 135.0;
        f(1, 7) = 108.0;
        f(1, 8) = 86.0;
        f(2, 0) = 126.0;
        f(2, 1) = 111.0;
        f(2, 2) = 130.0;
        f(2, 3) = 137.0;
        f(2, 4) = 150.0;
        f(2, 5) = 185.0;
        f(2, 6) = 173.0;
        f(2, 7) = 97.0;
        f(2, 8) = 149.0;
        f(3, 0) = 128.0;
        f(3, 1) = 112.0;
        f(3, 2) = 121.0;
        f(3, 3) = 77.0;
        f(3, 4) = 119.0;
        f(3, 5) = 173.0;
        f(3, 6) = 91.0;
        f(3, 7) = 112.0;
        f(3, 8) = 158.0;
        f(4, 0) = 119.0;
        f(4, 1) = 114.0;
        f(4, 2) = 78.0;
        f(4, 3) = 91.0;
        f(4, 4) = 145.0;
        f(4, 5) = 144.0;
        f(4, 6) = 83.0;
        f(4, 7) = 141.0;
        f(4, 8) = 171.0;
        f(5, 0) = 114.0;
        f(5, 1) = 103.0;
        f(5, 2) = 95.0;
        f(5, 3) = 75.0;
        f(5, 4) = 129.0;
        f(5, 5) = 119.0;
        f(5, 6) = 93.0;
        f(5, 7) = 152.0;
        f(5, 8) = 199.0;
        f(6, 0) = 122.0;
        f(6, 1) = 85.0;
        f(6, 2) = 88.0;
        f(6, 3) = 66.0;
        f(6, 4) = 117.0;
        f(6, 5) = 161.0;
        f(6, 6) = 127.0;
        f(6, 7) = 152.0;
        f(6, 8) = 131.0;
        f(7, 0) = 129.0;
        f(7, 1) = 78.0;
        f(7, 2) = 68.0;
        f(7, 3) = 85.0;
        f(7, 4) = 134.0;
        f(7, 5) = 165.0;
        f(7, 6) = 163.0;
        f(7, 7) = 122.0;
        f(7, 8) = 90.0;


        klab::DoubleReal precision = 1e-5;

        TDFT2D<std::complex<klab::DoubleReal> > dft;
        dft.transform(f, F);
        dft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(0, 8), f(0, 8), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 8), f(1, 8), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 8), f(2, 8), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 8), f(3, 8), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 8), f(4, 8), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 8), f(5, 8), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 8), f(6, 8), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 8), f(7, 8), precision))


        F.fill(0.0);
        fR.fill(0.0);

        TDFT2D<std::complex<klab::DoubleReal> > dft2(true);
        dft2.transform(f, F);
        dft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(0, 8), f(0, 8), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 8), f(1, 8), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 8), f(2, 8), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 8), f(3, 8), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 8), f(4, 8), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 8), f(5, 8), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 8), f(6, 8), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 8), f(7, 8), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}


// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testInvert_03_Real()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(8, 9);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fR;

        f(0, 0) = 155.0;
        f(0, 1) = 110.0;
        f(0, 2) = 125.0;
        f(0, 3) = 134.0;
        f(0, 4) = 138.0;
        f(0, 5) = 124.0;
        f(0, 6) = 153.0;
        f(0, 7) = 156.0;
        f(0, 8) = 84.0;
        f(1, 0) = 128.0;
        f(1, 1) = 108.0;
        f(1, 2) = 116.0;
        f(1, 3) = 141.0;
        f(1, 4) = 193.0;
        f(1, 5) = 158.0;
        f(1, 6) = 135.0;
        f(1, 7) = 108.0;
        f(1, 8) = 86.0;
        f(2, 0) = 126.0;
        f(2, 1) = 111.0;
        f(2, 2) = 130.0;
        f(2, 3) = 137.0;
        f(2, 4) = 150.0;
        f(2, 5) = 185.0;
        f(2, 6) = 173.0;
        f(2, 7) = 97.0;
        f(2, 8) = 149.0;
        f(3, 0) = 128.0;
        f(3, 1) = 112.0;
        f(3, 2) = 121.0;
        f(3, 3) = 77.0;
        f(3, 4) = 119.0;
        f(3, 5) = 173.0;
        f(3, 6) = 91.0;
        f(3, 7) = 112.0;
        f(3, 8) = 158.0;
        f(4, 0) = 119.0;
        f(4, 1) = 114.0;
        f(4, 2) = 78.0;
        f(4, 3) = 91.0;
        f(4, 4) = 145.0;
        f(4, 5) = 144.0;
        f(4, 6) = 83.0;
        f(4, 7) = 141.0;
        f(4, 8) = 171.0;
        f(5, 0) = 114.0;
        f(5, 1) = 103.0;
        f(5, 2) = 95.0;
        f(5, 3) = 75.0;
        f(5, 4) = 129.0;
        f(5, 5) = 119.0;
        f(5, 6) = 93.0;
        f(5, 7) = 152.0;
        f(5, 8) = 199.0;
        f(6, 0) = 122.0;
        f(6, 1) = 85.0;
        f(6, 2) = 88.0;
        f(6, 3) = 66.0;
        f(6, 4) = 117.0;
        f(6, 5) = 161.0;
        f(6, 6) = 127.0;
        f(6, 7) = 152.0;
        f(6, 8) = 131.0;
        f(7, 0) = 129.0;
        f(7, 1) = 78.0;
        f(7, 2) = 68.0;
        f(7, 3) = 85.0;
        f(7, 4) = 134.0;
        f(7, 5) = 165.0;
        f(7, 6) = 163.0;
        f(7, 7) = 122.0;
        f(7, 8) = 90.0;


        klab::DoubleReal precision = 1e-5;

        TDFT2D<klab::DoubleReal> dft;
        dft.transform(f, F);
        dft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(0, 8), f(0, 8), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 8), f(1, 8), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 8), f(2, 8), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 8), f(3, 8), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 8), f(4, 8), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 8), f(5, 8), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 8), f(6, 8), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 8), f(7, 8), precision))


        F.fill(0.0);
        fR.fill(0.0);

        TDFT2D<klab::DoubleReal> dft2(true);
        dft2.transform(f, F);
        dft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==8 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(0, 8), f(0, 8), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 8), f(1, 8), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 8), f(2, 8), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 8), f(3, 8), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 8), f(4, 8), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 8), f(5, 8), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 8), f(6, 8), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 8), f(7, 8), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testInvert_04()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > f(9, 9);
        arma::Mat<std::complex<klab::DoubleReal> > F;
        arma::Mat<std::complex<klab::DoubleReal> > fR;

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


        klab::DoubleReal precision = 1e-5;

        TDFT2D<std::complex<klab::DoubleReal> > dft;
        dft.transform(f, F);
        dft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(0, 8), f(0, 8), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 8), f(1, 8), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 8), f(2, 8), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 8), f(3, 8), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 8), f(4, 8), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 8), f(5, 8), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 8), f(6, 8), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 8), f(7, 8), precision))
        TEST_ASSERT(klab::Equals(fR(8, 0), f(8, 0), precision))
        TEST_ASSERT(klab::Equals(fR(8, 1), f(8, 1), precision))
        TEST_ASSERT(klab::Equals(fR(8, 2), f(8, 2), precision))
        TEST_ASSERT(klab::Equals(fR(8, 3), f(8, 3), precision))
        TEST_ASSERT(klab::Equals(fR(8, 4), f(8, 4), precision))
        TEST_ASSERT(klab::Equals(fR(8, 5), f(8, 5), precision))
        TEST_ASSERT(klab::Equals(fR(8, 6), f(8, 6), precision))
        TEST_ASSERT(klab::Equals(fR(8, 7), f(8, 7), precision))
        TEST_ASSERT(klab::Equals(fR(8, 8), f(8, 8), precision))


        F.fill(0.0);
        fR.fill(0.0);

        TDFT2D<std::complex<klab::DoubleReal> > dft2(true);
        dft2.transform(f, F);
        dft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(0, 8), f(0, 8), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 8), f(1, 8), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 8), f(2, 8), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 8), f(3, 8), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 8), f(4, 8), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 8), f(5, 8), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 8), f(6, 8), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 8), f(7, 8), precision))
        TEST_ASSERT(klab::Equals(fR(8, 0), f(8, 0), precision))
        TEST_ASSERT(klab::Equals(fR(8, 1), f(8, 1), precision))
        TEST_ASSERT(klab::Equals(fR(8, 2), f(8, 2), precision))
        TEST_ASSERT(klab::Equals(fR(8, 3), f(8, 3), precision))
        TEST_ASSERT(klab::Equals(fR(8, 4), f(8, 4), precision))
        TEST_ASSERT(klab::Equals(fR(8, 5), f(8, 5), precision))
        TEST_ASSERT(klab::Equals(fR(8, 6), f(8, 6), precision))
        TEST_ASSERT(klab::Equals(fR(8, 7), f(8, 7), precision))
        TEST_ASSERT(klab::Equals(fR(8, 8), f(8, 8), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDFT2DUnitTest::testInvert_04_Real()
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


        klab::DoubleReal precision = 1e-5;

        TDFT2D<klab::DoubleReal> dft;
        dft.transform(f, F);
        dft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(0, 8), f(0, 8), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 8), f(1, 8), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 8), f(2, 8), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 8), f(3, 8), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 8), f(4, 8), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 8), f(5, 8), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 8), f(6, 8), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 8), f(7, 8), precision))
        TEST_ASSERT(klab::Equals(fR(8, 0), f(8, 0), precision))
        TEST_ASSERT(klab::Equals(fR(8, 1), f(8, 1), precision))
        TEST_ASSERT(klab::Equals(fR(8, 2), f(8, 2), precision))
        TEST_ASSERT(klab::Equals(fR(8, 3), f(8, 3), precision))
        TEST_ASSERT(klab::Equals(fR(8, 4), f(8, 4), precision))
        TEST_ASSERT(klab::Equals(fR(8, 5), f(8, 5), precision))
        TEST_ASSERT(klab::Equals(fR(8, 6), f(8, 6), precision))
        TEST_ASSERT(klab::Equals(fR(8, 7), f(8, 7), precision))
        TEST_ASSERT(klab::Equals(fR(8, 8), f(8, 8), precision))


        F.fill(0.0);
        fR.fill(0.0);

        TDFT2D<klab::DoubleReal> dft2(true);
        dft2.transform(f, F);
        dft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==9 && fR.n_cols==9)
        TEST_ASSERT(klab::Equals(fR(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fR(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fR(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fR(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fR(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fR(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fR(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fR(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fR(0, 8), f(0, 8), precision))
        TEST_ASSERT(klab::Equals(fR(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fR(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fR(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fR(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fR(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fR(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fR(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fR(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fR(1, 8), f(1, 8), precision))
        TEST_ASSERT(klab::Equals(fR(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fR(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fR(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fR(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fR(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fR(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fR(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fR(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fR(2, 8), f(2, 8), precision))
        TEST_ASSERT(klab::Equals(fR(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fR(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fR(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fR(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fR(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fR(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fR(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fR(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fR(3, 8), f(3, 8), precision))
        TEST_ASSERT(klab::Equals(fR(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fR(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fR(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fR(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fR(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fR(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fR(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fR(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fR(4, 8), f(4, 8), precision))
        TEST_ASSERT(klab::Equals(fR(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fR(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fR(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fR(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fR(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fR(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fR(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fR(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fR(5, 8), f(5, 8), precision))
        TEST_ASSERT(klab::Equals(fR(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fR(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fR(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fR(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fR(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fR(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fR(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fR(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fR(6, 8), f(6, 8), precision))
        TEST_ASSERT(klab::Equals(fR(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fR(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fR(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fR(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fR(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fR(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fR(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fR(7, 7), f(7, 7), precision))
        TEST_ASSERT(klab::Equals(fR(7, 8), f(7, 8), precision))
        TEST_ASSERT(klab::Equals(fR(8, 0), f(8, 0), precision))
        TEST_ASSERT(klab::Equals(fR(8, 1), f(8, 1), precision))
        TEST_ASSERT(klab::Equals(fR(8, 2), f(8, 2), precision))
        TEST_ASSERT(klab::Equals(fR(8, 3), f(8, 3), precision))
        TEST_ASSERT(klab::Equals(fR(8, 4), f(8, 4), precision))
        TEST_ASSERT(klab::Equals(fR(8, 5), f(8, 5), precision))
        TEST_ASSERT(klab::Equals(fR(8, 6), f(8, 6), precision))
        TEST_ASSERT(klab::Equals(fR(8, 7), f(8, 7), precision))
        TEST_ASSERT(klab::Equals(fR(8, 8), f(8, 8), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
