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

#include "WalshHadamard1DOperatorUnitTest.h"
#include "../include/WalshHadamard1DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KWalshHadamard1DOperatorUnitTest::KWalshHadamard1DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KWalshHadamard1DOperatorUnitTest::testNConstructor)  
    TEST_ADD(KWalshHadamard1DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KWalshHadamard1DOperatorUnitTest::testApply)
    TEST_ADD(KWalshHadamard1DOperatorUnitTest::testApply_Complex)
    TEST_ADD(KWalshHadamard1DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KWalshHadamard1DOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KWalshHadamard1DOperatorUnitTest::~KWalshHadamard1DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KWalshHadamard1DOperatorUnitTest::testNConstructor()
{
    try
    {
        TWalshHadamard1DOperator<klab::DoubleReal> op1(16);
        TEST_ASSERT(op1.m()==16 && op1.n()==16)

        TWalshHadamard1DOperator<std::complex<klab::DoubleReal> > op2(16);
        TEST_ASSERT(op2.m()==16 && op2.n()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWalshHadamard1DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TWalshHadamard1DOperator<klab::DoubleReal> op1(16);
        TWalshHadamard1DOperator<klab::DoubleReal> op1Copy(op1);
        TEST_ASSERT(op1Copy.m()==16 && op1Copy.n()==16)

        TWalshHadamard1DOperator<std::complex<klab::DoubleReal> > op2(16);
        TWalshHadamard1DOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.m()==16 && op2Copy.n()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWalshHadamard1DOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;


        TWalshHadamard1DOperator<klab::DoubleReal> op(8);
        op.apply(x, y);

        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0],  36.0, precision))
        TEST_ASSERT(klab::Equals(y[1], -4.0, precision))
        TEST_ASSERT(klab::Equals(y[2], -8.0, precision))
        TEST_ASSERT(klab::Equals(y[3],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[4], -16.0, precision))
        TEST_ASSERT(klab::Equals(y[5],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[6],  0.0, precision))
        TEST_ASSERT(klab::Equals(y[7],  0.0, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWalshHadamard1DOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(8);
        arma::Col<std::complex<klab::DoubleReal> > y;

        x[0] = std::complex<klab::DoubleReal>(1.0, 0.0);
        x[1] = std::complex<klab::DoubleReal>(2.0, 0.0);
        x[2] = std::complex<klab::DoubleReal>(3.0, 0.0);
        x[3] = std::complex<klab::DoubleReal>(4.0, 0.0);
        x[4] = std::complex<klab::DoubleReal>(5.0, 0.0);
        x[5] = std::complex<klab::DoubleReal>(6.0, 0.0);
        x[6] = std::complex<klab::DoubleReal>(7.0, 0.0);
        x[7] = std::complex<klab::DoubleReal>(8.0, 0.0);


        TWalshHadamard1DOperator<std::complex<klab::DoubleReal> > op(8);
        op.apply(x, y);

        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>( 36.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(-4.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(-8.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>( 0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[4], std::complex<klab::DoubleReal>(-16.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[5], std::complex<klab::DoubleReal>( 0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[6], std::complex<klab::DoubleReal>( 0.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[7], std::complex<klab::DoubleReal>( 0.0, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWalshHadamard1DOperatorUnitTest::testApplyAdjoint()
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


        klab::TFWHT1D<klab::DoubleReal> fwht;
        arma::Mat<klab::DoubleReal> fwhtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwht.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwhtMatrix(i, j) = col[i];
        }       

        arma::Col<klab::DoubleReal> xt = arma::trans(fwhtMatrix) * x;

        TWalshHadamard1DOperator<klab::DoubleReal> op(8);
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

void KWalshHadamard1DOperatorUnitTest::testApplyAdjoint_Complex()
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
        

        klab::TFWHT1D<std::complex<klab::DoubleReal> > fwht;
        arma::Mat<std::complex<klab::DoubleReal> > fwhtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(8);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(0.0);
            base[j] = 1.0;

            fwht.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwhtMatrix(i, j) = col[i];
        }       
       
        arma::Col<std::complex<klab::DoubleReal> > xt = arma::trans(fwhtMatrix) * x;

        TWalshHadamard1DOperator<std::complex<klab::DoubleReal> > op(8);
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
