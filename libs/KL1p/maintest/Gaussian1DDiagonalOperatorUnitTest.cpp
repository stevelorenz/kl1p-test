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

#include "Gaussian1DDiagonalOperatorUnitTest.h"
#include "../include/Gaussian1DDiagonalOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KGaussian1DDiagonalOperatorUnitTest::KGaussian1DDiagonalOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testSizeConstructor)  
    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testSizeSigmaConstructor)  
    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testSizeSigmaCConstructor)  
    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testSigma)
    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testC)
    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testApply)
    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testApply_Complex)
    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KGaussian1DDiagonalOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KGaussian1DDiagonalOperatorUnitTest::~KGaussian1DDiagonalOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian1DDiagonalOperatorUnitTest::testSizeConstructor()
{
    try
    {
        TGaussian1DDiagonalOperator<klab::DoubleReal> op(32);
        TEST_ASSERT(op.n()==32 && op.sigma()==1.0 && op.c()==16)

        TGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32);
        TEST_ASSERT(op2.n()==32 && op2.sigma()==1.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian1DDiagonalOperatorUnitTest::testSizeSigmaConstructor()
{
    try
    {
        TGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 4.0);
        TEST_ASSERT(op.n()==32 && op.sigma()==4.0 && op.c()==16)

        TGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 4.0);
        TEST_ASSERT(op2.n()==32 && op2.sigma()==4.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian1DDiagonalOperatorUnitTest::testSizeSigmaCConstructor()
{
    try
    {
        TGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 4.0, 8);
        TEST_ASSERT(op.n()==32 && op.sigma()==4.0 && op.c()==8)

        TGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 4.0, 8);
        TEST_ASSERT(op2.n()==32 && op2.sigma()==4.0 && op2.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian1DDiagonalOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 4.0, 8);
        TEST_ASSERT(op.n()==32 && op.sigma()==4.0 && op.c()==8)

        TGaussian1DDiagonalOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.n()==32 && opCopy.sigma()==4.0 && opCopy.c()==8)


        TGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 4.0, 8);
        TEST_ASSERT(op2.n()==32 && op2.sigma()==4.0 && op2.c()==8)

        TGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.n()==32 && op2Copy.sigma()==4.0 && op2Copy.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian1DDiagonalOperatorUnitTest::testSigma()
{
    try
    {
        TGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 4.0, 8);
        TEST_ASSERT(op.sigma()==4.0)

        TGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 4.0, 8);
        TEST_ASSERT(op2.sigma()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian1DDiagonalOperatorUnitTest::testC()
{
    try
    {
        TGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 4.0, 8);
        TEST_ASSERT(op.c()==8)

        TGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op2(32, 4.0, 8);
        TEST_ASSERT(op2.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian1DDiagonalOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        TGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 4.0, 16);
        op.apply(x, xr);

        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(xr[0], 0.00033546262790251185, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0017676526138700999, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.0065624733545486553, precision))
        TEST_ASSERT(klab::Equals(xr[3], 0.020344276924050803, precision))
        TEST_ASSERT(klab::Equals(xr[4], 0.055544982691211532, precision))
        TEST_ASSERT(klab::Equals(xr[5], 0.13676508530167408, precision))
        TEST_ASSERT(klab::Equals(xr[6], 0.30755853536385191, precision))
        TEST_ASSERT(klab::Equals(xr[7], 0.63647606974582149, precision))
        TEST_ASSERT(klab::Equals(xr[8], 1.2180175491295144, precision))
        TEST_ASSERT(klab::Equals(xr[9], 2.1626516682988730, precision))
        TEST_ASSERT(klab::Equals(xr[10], 3.5711771409418471, precision))
        TEST_ASSERT(klab::Equals(xr[11], 5.4940003412593708, precision))
        TEST_ASSERT(klab::Equals(xr[12], 7.8848985762642343, precision))
        TEST_ASSERT(klab::Equals(xr[13], 10.567754427846102, precision))
        TEST_ASSERT(klab::Equals(xr[14], 13.237453538768932, precision))
        TEST_ASSERT(klab::Equals(xr[15], 15.507731751621506, precision))
        TEST_ASSERT(klab::Equals(xr[16], 17.0, precision))
        TEST_ASSERT(klab::Equals(xr[17], 17.446198220574196, precision))
        TEST_ASSERT(klab::Equals(xr[18], 16.767441149107313, precision))
        TEST_ASSERT(klab::Equals(xr[19], 15.096792039780148, precision))
        TEST_ASSERT(klab::Equals(xr[20], 12.737143853965302, precision))
        TEST_ASSERT(klab::Equals(xr[21], 10.072333958975515, precision))
        TEST_ASSERT(klab::Equals(xr[22], 7.467006749242044, precision))
        TEST_ASSERT(klab::Equals(xr[23], 5.1903640039172956, precision))
        TEST_ASSERT(klab::Equals(xr[24], 3.3833820809153177, precision))
        TEST_ASSERT(klab::Equals(xr[25], 2.0685472266739198, precision))
        TEST_ASSERT(klab::Equals(xr[26], 1.1862972078320004, precision))
        TEST_ASSERT(klab::Equals(xr[27], 0.63823706474114561, precision))
        TEST_ASSERT(klab::Equals(xr[28], 0.32216089960902689, precision))
        TEST_ASSERT(klab::Equals(xr[29], 0.15258207693038101, precision))
        TEST_ASSERT(klab::Equals(xr[30], 0.067812224663669443, precision))
        TEST_ASSERT(klab::Equals(xr[31], 0.028282441821921599, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian1DDiagonalOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(32);
        arma::Col<std::complex<klab::DoubleReal> > xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        TGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op(32, 4.0, 16);
        op.apply(x, xr);

        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[0]), std::complex<klab::DoubleReal>(0.00033546262790251185), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[1]), std::complex<klab::DoubleReal>(0.0017676526138700999), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[2]), std::complex<klab::DoubleReal>(0.0065624733545486553), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[3]), std::complex<klab::DoubleReal>(0.020344276924050803), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[4]), std::complex<klab::DoubleReal>(0.055544982691211532), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[5]), std::complex<klab::DoubleReal>(0.13676508530167408), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[6]), std::complex<klab::DoubleReal>(0.30755853536385191), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[7]), std::complex<klab::DoubleReal>(0.63647606974582149), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[8]), std::complex<klab::DoubleReal>(1.2180175491295144), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[9]), std::complex<klab::DoubleReal>(2.1626516682988730), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[10]), std::complex<klab::DoubleReal>(3.5711771409418471), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[11]), std::complex<klab::DoubleReal>(5.4940003412593708), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[12]), std::complex<klab::DoubleReal>(7.8848985762642343), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[13]), std::complex<klab::DoubleReal>(10.567754427846102), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[14]), std::complex<klab::DoubleReal>(13.237453538768932), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[15]), std::complex<klab::DoubleReal>(15.507731751621506), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[16]), std::complex<klab::DoubleReal>(17.0), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[17]), std::complex<klab::DoubleReal>(17.446198220574196), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[18]), std::complex<klab::DoubleReal>(16.767441149107313), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[19]), std::complex<klab::DoubleReal>(15.096792039780148), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[20]), std::complex<klab::DoubleReal>(12.737143853965302), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[21]), std::complex<klab::DoubleReal>(10.072333958975515), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[22]), std::complex<klab::DoubleReal>(7.467006749242044), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[23]), std::complex<klab::DoubleReal>(5.1903640039172956), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[24]), std::complex<klab::DoubleReal>(3.3833820809153177), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[25]), std::complex<klab::DoubleReal>(2.0685472266739198), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[26]), std::complex<klab::DoubleReal>(1.1862972078320004), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[27]), std::complex<klab::DoubleReal>(0.63823706474114561), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[28]), std::complex<klab::DoubleReal>(0.32216089960902689), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[29]), std::complex<klab::DoubleReal>(0.15258207693038101), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[30]), std::complex<klab::DoubleReal>(0.067812224663669443), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[31]), std::complex<klab::DoubleReal>(0.028282441821921599), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussian1DDiagonalOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1); 
        
        TGaussian1DDiagonalOperator<klab::DoubleReal> op(32, 4.0, 16);
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

void KGaussian1DDiagonalOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(32);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1); 
        
        TGaussian1DDiagonalOperator<std::complex<klab::DoubleReal> > op(32, 4.0, 16);
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

