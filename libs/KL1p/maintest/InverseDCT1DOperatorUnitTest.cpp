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

#include "InverseDCT1DOperatorUnitTest.h"
#include "../include/InverseDCT1DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KInverseDCT1DOperatorUnitTest::KInverseDCT1DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KInverseDCT1DOperatorUnitTest::testNConstructor)  
    TEST_ADD(KInverseDCT1DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KInverseDCT1DOperatorUnitTest::testApply)
    TEST_ADD(KInverseDCT1DOperatorUnitTest::testApply_Complex)
    TEST_ADD(KInverseDCT1DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KInverseDCT1DOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KInverseDCT1DOperatorUnitTest::~KInverseDCT1DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KInverseDCT1DOperatorUnitTest::testNConstructor()
{
    try
    {
        TInverseDCT1DOperator<klab::DoubleReal> op1(128);
        TEST_ASSERT(op1.m()==128 && op1.n()==128)

        TInverseDCT1DOperator<std::complex<klab::DoubleReal> > op2(128);
        TEST_ASSERT(op2.m()==128 && op2.n()==128)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseDCT1DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TInverseDCT1DOperator<klab::DoubleReal> op1(128);
        TInverseDCT1DOperator<klab::DoubleReal> op1Copy(op1);
        TEST_ASSERT(op1Copy.m()==128 && op1Copy.n()==128)

        TInverseDCT1DOperator<std::complex<klab::DoubleReal> > op2(128);
        TInverseDCT1DOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.m()==128 && op2Copy.n()==128)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseDCT1DOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;

        x[0] =  1.0;
        x[1] =  2.0;
        x[2] =  3.0;
        x[3] =  4.0;
        x[4] =  5.0;
        x[5] =  6.0;
        x[6] =  7.0;
        x[7] =  8.0;


        TInverseDCT1DOperator<klab::DoubleReal> op(8);
        op.apply(x, y);

        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0],  9.9373281477360287, precision))
        TEST_ASSERT(klab::Equals(y[1], -8.7971145826327763, precision))
        TEST_ASSERT(klab::Equals(y[2],  3.7504887403404803, precision))
        TEST_ASSERT(klab::Equals(y[3], -2.9486733972134638, precision))
        TEST_ASSERT(klab::Equals(y[4],  1.7408914602432604, precision))
        TEST_ASSERT(klab::Equals(y[5], -1.2598094346029336, precision))
        TEST_ASSERT(klab::Equals(y[6],  0.64958102740284773, precision))
        TEST_ASSERT(klab::Equals(y[7], -0.24426483652725395, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseDCT1DOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(8);
        arma::Col<std::complex<klab::DoubleReal> > y;

        x[0] = std::complex<klab::DoubleReal>( 1.0, 0.0);
        x[1] = std::complex<klab::DoubleReal>( 2.0, 0.0);
        x[2] = std::complex<klab::DoubleReal>( 3.0, 0.0);
        x[3] = std::complex<klab::DoubleReal>( 4.0, 0.0);
        x[4] = std::complex<klab::DoubleReal>( 5.0, 0.0);
        x[5] = std::complex<klab::DoubleReal>( 6.0, 0.0);
        x[6] = std::complex<klab::DoubleReal>( 7.0, 0.0);
        x[7] = std::complex<klab::DoubleReal>( 8.0, 0.0);


        TInverseDCT1DOperator<std::complex<klab::DoubleReal> > op(8);
        op.apply(x, y);

        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>( 9.9373281477360287, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(-8.7971145826327763, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>( 3.7504887403404803, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(-2.9486733972134638, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[4], std::complex<klab::DoubleReal>( 1.7408914602432604, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[5], std::complex<klab::DoubleReal>(-1.2598094346029336, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[6], std::complex<klab::DoubleReal>( 0.64958102740284773, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[7], std::complex<klab::DoubleReal>(-0.24426483652725395, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseDCT1DOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> xr;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;


        klab::TFCT1D<klab::DoubleReal> fct;
        arma::Mat<klab::DoubleReal> fctMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fct.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fctMatrix(i, j) = col[i];
        }       

        arma::Col<klab::DoubleReal> xt = arma::trans(fctMatrix) * x;

        TInverseDCT1DOperator<klab::DoubleReal> op(8);
        op.applyAdjoint(x, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseDCT1DOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(8);
        arma::Col<std::complex<klab::DoubleReal> > xr;

        x[0] = std::complex<klab::DoubleReal>(1.0, -8.0);
        x[1] = std::complex<klab::DoubleReal>(2.0, -7.0);
        x[2] = std::complex<klab::DoubleReal>(3.0, -6.0);
        x[3] = std::complex<klab::DoubleReal>(4.0, -5.0);
        x[4] = std::complex<klab::DoubleReal>(5.0, -4.0);
        x[5] = std::complex<klab::DoubleReal>(6.0, -3.0);
        x[6] = std::complex<klab::DoubleReal>(7.0, -2.0);
        x[7] = std::complex<klab::DoubleReal>(8.0, -1.0);
        

        klab::TFCT1D<std::complex<klab::DoubleReal> > fct;
        arma::Mat<std::complex<klab::DoubleReal> > fctMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(8);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(0.0);
            base[j] = 1.0;

            fct.invert(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fctMatrix(i, j) = col[i];
        }       
       
        arma::Col<std::complex<klab::DoubleReal> > xt = arma::trans(fctMatrix) * x;

        TInverseDCT1DOperator<std::complex<klab::DoubleReal> > op(8);
        op.applyAdjoint(x, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision)) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
