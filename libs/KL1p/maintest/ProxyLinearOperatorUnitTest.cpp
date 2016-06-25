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

#include "ProxyLinearOperatorUnitTest.h"
#include "../include/ProxyLinearOperator.h"
#include "../include/MatrixOperator.h"
#include "../include/DownSamplingOperator.h"
#include "../include/Fourier1DOperator.h"
#include "../include/InverseFourier1DOperator.h"
#include "../include/MultiplicationOperator.h"
#include "../include/SubSystemOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KProxyLinearOperatorUnitTest::KProxyLinearOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KProxyLinearOperatorUnitTest::testOpConstructor)
    TEST_ADD(KProxyLinearOperatorUnitTest::testCopyConstructor)
    TEST_ADD(KProxyLinearOperatorUnitTest::testAffectationOperator)

    TEST_ADD(KProxyLinearOperatorUnitTest::testApply)
    TEST_ADD(KProxyLinearOperatorUnitTest::testApply_Complex)
    TEST_ADD(KProxyLinearOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KProxyLinearOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KProxyLinearOperatorUnitTest::~KProxyLinearOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KProxyLinearOperatorUnitTest::testOpConstructor()
{
    try
    {
        TProxyLinearOperator<klab::DoubleReal> op1(new TSubSystemOperator<klab::DoubleReal>(0));
        TEST_ASSERT(true)

        TProxyLinearOperator<std::complex<klab::DoubleReal> > op2(new TSubSystemOperator<std::complex<klab::DoubleReal> >(0));
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyLinearOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TProxyLinearOperator<klab::DoubleReal> op1(new TSubSystemOperator<klab::DoubleReal>(0));
        TProxyLinearOperator<klab::DoubleReal> op2(op1);
        TEST_ASSERT(true)

        TProxyLinearOperator<std::complex<klab::DoubleReal> > op3(new TSubSystemOperator<std::complex<klab::DoubleReal> >(0));
        TProxyLinearOperator<std::complex<klab::DoubleReal> > op4(op3);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyLinearOperatorUnitTest::testAffectationOperator()
{
    try
    {
        TProxyLinearOperator<klab::DoubleReal> op1(new TSubSystemOperator<klab::DoubleReal>(0));
        TProxyLinearOperator<klab::DoubleReal> op2(0);
        op2 = op1;
        TEST_ASSERT(true)

        TProxyLinearOperator<std::complex<klab::DoubleReal> > op3(new TSubSystemOperator<std::complex<klab::DoubleReal> >(0));
        TProxyLinearOperator<std::complex<klab::DoubleReal> > op4(0);
        op4 = op3;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyLinearOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(2);
        x[0] =  22.6274169979695;
        x[1] = -22.6274169979695;

        arma::Col<klab::DoubleReal> y;


        KBitArray bits(16);
        for(klab::UInt32 i=0; i<16; ++i)
            bits.setBit(i, ((i+1)%4==0 ? false : true));

        klab::TSmartPointer<TOperator<klab::DoubleReal> > opBitMask = new TDownSamplingOperator<klab::DoubleReal>(bits);
        klab::TSmartPointer<TOperator<klab::DoubleReal> > opInverseFourier = new TInverseFourier1DOperator<klab::DoubleReal>(16, true);   
        klab::TSmartPointer<TOperator<klab::DoubleReal> > phi = opBitMask * opInverseFourier;

        std::vector<klab::UInt32> indexes;
        indexes.push_back(6);
        indexes.push_back(10);

        TProxyLinearOperator<klab::DoubleReal> cgOp(new TSubSystemOperator<klab::DoubleReal>(phi, indexes));
        cgOp.apply(x, y);

        TEST_ASSERT(y.n_rows == 12)
        TEST_ASSERT(klab::Equals(y[0],  2.8284271247461876, precision))
        TEST_ASSERT(klab::Equals(y[1],  0.0,                precision))
        TEST_ASSERT(klab::Equals(y[2],  2.8284271247461872, precision))
        TEST_ASSERT(klab::Equals(y[3], -2.8284271247461876, precision))
        TEST_ASSERT(klab::Equals(y[4],  0.0,                precision))
        TEST_ASSERT(klab::Equals(y[5], -2.8284271247461872, precision))
        TEST_ASSERT(klab::Equals(y[6],  2.8284271247461876, precision))
        TEST_ASSERT(klab::Equals(y[7],  0.0,                precision))
        TEST_ASSERT(klab::Equals(y[8],  2.8284271247461872, precision))
        TEST_ASSERT(klab::Equals(y[9], -2.8284271247461876, precision))
        TEST_ASSERT(klab::Equals(y[10], 0.0,                precision))
        TEST_ASSERT(klab::Equals(y[11],-2.8284271247461872, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyLinearOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(2);
        x[0] = std::complex<klab::DoubleReal>(22.6274169979695,  22.6274169979695);
        x[1] = std::complex<klab::DoubleReal>(22.6274169979695, -22.6274169979695);

        arma::Col<std::complex<klab::DoubleReal> > y;


        KBitArray bits(16);
        for(klab::UInt32 i=0; i<16; ++i)
            bits.setBit(i, ((i+1)%4==0 ? false : true));

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > opBitMask = new TDownSamplingOperator<std::complex<klab::DoubleReal> >(bits);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > opInverseFourier = new TInverseFourier1DOperator<std::complex<klab::DoubleReal> >(16, true);   
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > phi = opBitMask * opInverseFourier;

        std::vector<klab::UInt32> indexes;
        indexes.push_back(6);
        indexes.push_back(10);

        TProxyLinearOperator<std::complex<klab::DoubleReal> > cgOp(new TSubSystemOperator<std::complex<klab::DoubleReal> >(phi, indexes));
        cgOp.apply(x, y);

        TEST_ASSERT(y.n_rows == 12)
        TEST_ASSERT(klab::Equals(y[0],  std::complex<klab::DoubleReal>( 2.82842712474619, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[1],  std::complex<klab::DoubleReal>( 4.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[2],  std::complex<klab::DoubleReal>( 2.82842712474619, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[3],  std::complex<klab::DoubleReal>(-2.82842712474619, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[4],  std::complex<klab::DoubleReal>(-4.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[5],  std::complex<klab::DoubleReal>(-2.82842712474619, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[6],  std::complex<klab::DoubleReal>( 2.82842712474619, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[7],  std::complex<klab::DoubleReal>( 4.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[8],  std::complex<klab::DoubleReal>( 2.82842712474619, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[9],  std::complex<klab::DoubleReal>(-2.82842712474619, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[10], std::complex<klab::DoubleReal>(-4.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(y[11], std::complex<klab::DoubleReal>(-2.82842712474619, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyLinearOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(2);
        x[0] =  22.6274169979695;
        x[1] = -22.6274169979695;

        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;


        KBitArray bits(16);
        for(klab::UInt32 i=0; i<16; ++i)
            bits.setBit(i, ((i+1)%4==0 ? false : true));

        klab::TSmartPointer<TOperator<klab::DoubleReal> > opBitMask = new TDownSamplingOperator<klab::DoubleReal>(bits);
        klab::TSmartPointer<TOperator<klab::DoubleReal> > opInverseFourier = new TInverseFourier1DOperator<klab::DoubleReal>(16, true);   
        klab::TSmartPointer<TOperator<klab::DoubleReal> > phi = opBitMask * opInverseFourier;

        std::vector<klab::UInt32> indexes;
        indexes.push_back(6);
        indexes.push_back(10);

        TProxyLinearOperator<klab::DoubleReal> cgOp(new TSubSystemOperator<klab::DoubleReal>(phi, indexes));
        cgOp.apply(x, y);
        cgOp.applyAdjoint(y, xr);

        TEST_ASSERT(xr.n_rows == 2)
        TEST_ASSERT(klab::Equals(xr[0],  1.4142135623730936, precision))
        TEST_ASSERT(klab::Equals(xr[1], -1.4142135623730936, precision))        
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyLinearOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(2);
        x[0] = std::complex<klab::DoubleReal>(22.6274169979695,  22.6274169979695);
        x[1] = std::complex<klab::DoubleReal>(22.6274169979695, -22.6274169979695);

        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;


        KBitArray bits(16);
        for(klab::UInt32 i=0; i<16; ++i)
            bits.setBit(i, ((i+1)%4==0 ? false : true));

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > opBitMask = new TDownSamplingOperator<std::complex<klab::DoubleReal> >(bits);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > opInverseFourier = new TInverseFourier1DOperator<std::complex<klab::DoubleReal> >(16, true);   
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > phi = opBitMask * opInverseFourier;

        std::vector<klab::UInt32> indexes;
        indexes.push_back(6);
        indexes.push_back(10);

        TProxyLinearOperator<std::complex<klab::DoubleReal> > cgOp(new TSubSystemOperator<std::complex<klab::DoubleReal> >(phi, indexes));
        cgOp.apply(x, y);
        cgOp.applyAdjoint(y, xr);

        TEST_ASSERT(xr.n_rows == 2)
        TEST_ASSERT(klab::Equals(xr[0],  std::complex<klab::DoubleReal>(1.4142135623730940,  1.4142135623730934), precision))
        TEST_ASSERT(klab::Equals(xr[1],  std::complex<klab::DoubleReal>(1.4142135623730936, -1.4142135623730936), precision))        
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
