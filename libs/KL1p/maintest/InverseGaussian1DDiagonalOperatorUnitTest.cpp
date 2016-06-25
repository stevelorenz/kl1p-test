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

#include "InverseGaussian1DDiagonalOperatorUnitTest.h"
#include "../include/InverseGaussian1DDiagonalOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KInverseGaussian1DDiagonalOperatorUnitTest::KInverseGaussian1DDiagonalOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testSizeConstructor)  
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testSizeGammaConstructor)  
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testSizeGammaSigmaConstructor)  
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testSizeGammaSigmaCConstructor)  
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testGamma)
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testSigma)
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testC)
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testApply)
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testApply_Complex)
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KInverseGaussian1DDiagonalOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KInverseGaussian1DDiagonalOperatorUnitTest::~KInverseGaussian1DDiagonalOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testSizeConstructor()
{
    try
    {
        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.0 && op.sigma()==1.0 && op.c()==16)

        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32);
        TEST_ASSERT(op2.n()==32 && op2.gamma()==0.0 && op2.sigma()==1.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testSizeGammaConstructor()
{
    try
    {
        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 0.4);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.4 && op.sigma()==1.0 && op.c()==16)

        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 0.4);
        TEST_ASSERT(op2.n()==32 && op2.gamma()==0.4 && op2.sigma()==1.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testSizeGammaSigmaConstructor()
{
    try
    {
        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 0.4, 4.0);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.4 && op.sigma()==4.0 && op.c()==16)

        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0);
        TEST_ASSERT(op2.n()==32 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testSizeGammaSigmaCConstructor()
{
    try
    {
        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.4 && op.sigma()==4.0 && op.c()==8)

        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.n()==32 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.4 && op.sigma()==4.0 && op.c()==8)

        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.n()==32 && opCopy.gamma()==0.4 && opCopy.sigma()==4.0 && opCopy.c()==8)


        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.n()==32 && op.gamma()==0.4 && op2.sigma()==4.0 && op2.c()==8)

        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.n()==32 && op2Copy.gamma()==0.4 && op2Copy.sigma()==4.0 && op2Copy.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testGamma()
{
    try
    {
        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.gamma()==0.4)

        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.gamma()==0.4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testSigma()
{
    try
    {
        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.sigma()==4.0)

        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.sigma()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testC()
{
    try
    {
        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.c()==8)

        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 0.4, 4.0, 16);
        op.apply(x, xr);

        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(xr[0], 0.00083865633381043688, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0044191229046923091, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.016405987124935822, precision))
        TEST_ASSERT(klab::Equals(xr[3], 0.050857403349109757, precision))
        TEST_ASSERT(klab::Equals(xr[4], 0.13881962747045504, precision))
        TEST_ASSERT(klab::Equals(xr[5], 0.34146916642016412, precision))
        TEST_ASSERT(klab::Equals(xr[6], 0.7652033634147315, precision))
        TEST_ASSERT(klab::Equals(xr[7], 1.5664029618808621, precision))
        TEST_ASSERT(klab::Equals(xr[8], 2.9117188933342484, precision))
        TEST_ASSERT(klab::Equals(xr[9], 4.8406308739795989, precision))
        TEST_ASSERT(klab::Equals(xr[10], 7.0660518801502636, precision))
        TEST_ASSERT(klab::Equals(xr[11], 9.01229940427217, precision))
        TEST_ASSERT(klab::Equals(xr[12], 10.268406931477925, precision))
        TEST_ASSERT(klab::Equals(xr[13], 10.897031952260283, precision))
        TEST_ASSERT(klab::Equals(xr[14], 11.22959343840806, precision))
        TEST_ASSERT(klab::Equals(xr[15], 11.578005457888446, precision))
        TEST_ASSERT(klab::Equals(xr[16], 12.142857142857142, precision))
        TEST_ASSERT(klab::Equals(xr[17], 13.025256140124503, precision))
        TEST_ASSERT(klab::Equals(xr[18], 14.22415168865021, precision))
        TEST_ASSERT(klab::Equals(xr[19], 15.567188503228977, precision))
        TEST_ASSERT(klab::Equals(xr[20], 16.587426581618185, precision))
        TEST_ASSERT(klab::Equals(xr[21], 16.522548907832313, precision))
        TEST_ASSERT(klab::Equals(xr[22], 14.77447211304146, precision))
        TEST_ASSERT(klab::Equals(xr[23], 11.617514097551037, precision))
        TEST_ASSERT(klab::Equals(xr[24], 8.0881080370395786, precision))
        TEST_ASSERT(klab::Equals(xr[25], 5.0908096261128017, precision))
        TEST_ASSERT(klab::Equals(xr[26], 2.9514986874568212, precision))
        TEST_ASSERT(klab::Equals(xr[27], 1.5935227766274322, precision))
        TEST_ASSERT(klab::Equals(xr[28], 0.80515383932863915, precision))
        TEST_ASSERT(klab::Equals(xr[29], 0.3814305251183232, precision))
        TEST_ASSERT(klab::Equals(xr[30], 0.16952853362433681, precision))
        TEST_ASSERT(klab::Equals(xr[31], 0.070705966475076945, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(32);
        arma::Col<std::complex<klab::DoubleReal> > xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op(32, 0.4, 4.0, 16);
        op.apply(x, xr);

        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[0]), std::complex<klab::DoubleReal>(0.00083865633381043688), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[1]), std::complex<klab::DoubleReal>(0.0044191229046923091), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[2]), std::complex<klab::DoubleReal>(0.016405987124935822), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[3]), std::complex<klab::DoubleReal>(0.050857403349109757), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[4]), std::complex<klab::DoubleReal>(0.13881962747045504), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[5]), std::complex<klab::DoubleReal>(0.34146916642016412), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[6]), std::complex<klab::DoubleReal>(0.7652033634147315), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[7]), std::complex<klab::DoubleReal>(1.5664029618808621), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[8]), std::complex<klab::DoubleReal>(2.9117188933342484), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[9]), std::complex<klab::DoubleReal>(4.8406308739795989), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[10]), std::complex<klab::DoubleReal>(7.0660518801502636), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[11]), std::complex<klab::DoubleReal>(9.01229940427217), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[12]), std::complex<klab::DoubleReal>(10.268406931477925), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[13]), std::complex<klab::DoubleReal>(10.897031952260283), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[14]), std::complex<klab::DoubleReal>(11.22959343840806), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[15]), std::complex<klab::DoubleReal>(11.578005457888446), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[16]), std::complex<klab::DoubleReal>(12.142857142857142), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[17]), std::complex<klab::DoubleReal>(13.025256140124503), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[18]), std::complex<klab::DoubleReal>(14.22415168865021), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[19]), std::complex<klab::DoubleReal>(15.567188503228977), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[20]), std::complex<klab::DoubleReal>(16.587426581618185), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[21]), std::complex<klab::DoubleReal>(16.522548907832313), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[22]), std::complex<klab::DoubleReal>(14.77447211304146), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[23]), std::complex<klab::DoubleReal>(11.617514097551037), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[24]), std::complex<klab::DoubleReal>(8.0881080370395786), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[25]), std::complex<klab::DoubleReal>(5.0908096261128017), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[26]), std::complex<klab::DoubleReal>(2.9514986874568212), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[27]), std::complex<klab::DoubleReal>(1.5935227766274322), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[28]), std::complex<klab::DoubleReal>(0.80515383932863915), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[29]), std::complex<klab::DoubleReal>(0.3814305251183232), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[30]), std::complex<klab::DoubleReal>(0.16952853362433681), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[31]), std::complex<klab::DoubleReal>(0.070705966475076945), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1); 
        
        TInverseGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 4.0, 16);
        arma::Mat<klab::DoubleReal> opMatrix(32, 32);
        for(klab::UInt32 j=0; j<32; ++j)
        {
            arma::Col<klab::DoubleReal> base(32);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            op.apply(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                opMatrix(i, j) = col[i];
        }       

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(opMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 32)
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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussian1DDiagonalOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(32);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1); 
        
        TInverseGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op(32, 4.0, 16);
        arma::Mat<std::complex<klab::DoubleReal> > opMatrix(32, 32);
        for(klab::UInt32 j=0; j<32; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(32);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(0.0);
            base[j] = 1.0;

            op.apply(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                opMatrix(i, j) = col[i];
        }       

        op.apply(x, y);
        arma::Col<std::complex<klab::DoubleReal> > xt = arma::trans(opMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 32)
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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

