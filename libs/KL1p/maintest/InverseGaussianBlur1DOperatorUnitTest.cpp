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

#include "InverseGaussianBlur1DOperatorUnitTest.h"
#include "../include/InverseGaussianBlur1DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KInverseGaussianBlur1DOperatorUnitTest::KInverseGaussianBlur1DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testSizeConstructor)  
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testSizeGammaConstructor)  
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testSizeGammaSigmaConstructor)  
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testSizeGammaSigmaCConstructor)  
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testGamma)
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testSigma)
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testC)
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testApply)
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testApply_Complex)
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KInverseGaussianBlur1DOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KInverseGaussianBlur1DOperatorUnitTest::~KInverseGaussianBlur1DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testSizeConstructor()
{
    try
    {
        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.0 && op.sigma()==1.0 && op.c()==16)

        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32);
        TEST_ASSERT(op2.n()==32 && op2.gamma()==0.0 && op2.sigma()==1.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testSizeGammaConstructor()
{
    try
    {
        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32, 0.4);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.4 && op.sigma()==1.0 && op.c()==16)

        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 0.4);
        TEST_ASSERT(op2.n()==32 && op2.gamma()==0.4 && op2.sigma()==1.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testSizeGammaSigmaConstructor()
{
    try
    {
        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32, 0.4, 4.0);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.4 && op.sigma()==4.0 && op.c()==16)

        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0);
        TEST_ASSERT(op2.n()==32 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testSizeGammaSigmaCConstructor()
{
    try
    {
        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.4 && op.sigma()==4.0 && op.c()==8)

        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.n()==32 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.n()==32 && op.gamma()==0.4 && op.sigma()==4.0 && op.c()==8)

        TInverseGaussianBlur1DOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.n()==32 && opCopy.gamma()==0.4 && opCopy.sigma()==4.0 && opCopy.c()==8)


        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.n()==32 && op2.gamma()==0.4 && op2.sigma()==4.0 && op2.c()==8)

        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.n()==32 && op2Copy.gamma()==0.4 && op2Copy.sigma()==4.0 && op2Copy.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testGamma()
{
    try
    {
        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.gamma()==0.4)

        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.gamma()==0.4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testSigma()
{
    try
    {
        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.sigma()==4.0)

        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.sigma()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testC()
{
    try
    {
        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32, 0.4, 4.0, 8);
        TEST_ASSERT(op.c()==8)

        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 0.4, 4.0, 8);
        TEST_ASSERT(op2.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32, 0.4, 4.0, 16);
        op.apply(x, xr);

        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(xr[0], 6.1336292961307421, precision))
        TEST_ASSERT(klab::Equals(xr[1], -0.29656688500371864, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.27417548315833784, precision))
        TEST_ASSERT(klab::Equals(xr[3], 2.5498837621217207, precision))
        TEST_ASSERT(klab::Equals(xr[4], 3.8106635284524142, precision))
        TEST_ASSERT(klab::Equals(xr[5], 4.4232168318025025, precision))
        TEST_ASSERT(klab::Equals(xr[6], 5.0065132048829017, precision))
        TEST_ASSERT(klab::Equals(xr[7], 5.6911788640164858, precision))
        TEST_ASSERT(klab::Equals(xr[8], 6.4195914889533672, precision))
        TEST_ASSERT(klab::Equals(xr[9], 7.1433851997942188, precision))
        TEST_ASSERT(klab::Equals(xr[10], 7.8593680355420412, precision))
        TEST_ASSERT(klab::Equals(xr[11], 8.5717621977628955, precision))
        TEST_ASSERT(klab::Equals(xr[12], 9.2857733598847343, precision))
        TEST_ASSERT(klab::Equals(xr[13], 9.9996374058370474, precision))
        TEST_ASSERT(klab::Equals(xr[14], 10.714455775364186, precision))
        TEST_ASSERT(klab::Equals(xr[15], 11.428382046708077, precision))
        TEST_ASSERT(klab::Equals(xr[16], 12.143046524720496, precision))
        TEST_ASSERT(klab::Equals(xr[17], 12.856972796064385, precision))
        TEST_ASSERT(klab::Equals(xr[18], 13.571791165591527, precision))
        TEST_ASSERT(klab::Equals(xr[19], 14.28565521154384, precision))
        TEST_ASSERT(klab::Equals(xr[20], 14.999666373665681, precision))
        TEST_ASSERT(klab::Equals(xr[21], 15.712060535886531, precision))
        TEST_ASSERT(klab::Equals(xr[22], 16.428043371634356, precision))
        TEST_ASSERT(klab::Equals(xr[23], 17.151837082475208, precision))
        TEST_ASSERT(klab::Equals(xr[24], 17.880249707412091, precision))
        TEST_ASSERT(klab::Equals(xr[25], 18.564915366545669, precision))
        TEST_ASSERT(klab::Equals(xr[26], 19.14821173962607, precision))
        TEST_ASSERT(klab::Equals(xr[27], 19.760765042976153, precision))
        TEST_ASSERT(klab::Equals(xr[28], 21.021544809306853, precision))
        TEST_ASSERT(klab::Equals(xr[29], 23.297253088270235, precision))
        TEST_ASSERT(klab::Equals(xr[30], 23.86799545643229, precision))
        TEST_ASSERT(klab::Equals(xr[31], 17.437799275297827, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(32);
        arma::Col<std::complex<klab::DoubleReal> > xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op(32, 0.4, 4.0, 16);
        op.apply(x, xr);

        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[0]), std::complex<klab::DoubleReal>(6.1336292961307421), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[1]), std::complex<klab::DoubleReal>(-0.29656688500371864), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[2]), std::complex<klab::DoubleReal>(0.27417548315833784), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[3]), std::complex<klab::DoubleReal>(2.5498837621217207), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[4]), std::complex<klab::DoubleReal>(3.8106635284524142), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[5]), std::complex<klab::DoubleReal>(4.4232168318025025), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[6]), std::complex<klab::DoubleReal>(5.0065132048829017), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[7]), std::complex<klab::DoubleReal>(5.6911788640164858), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[8]), std::complex<klab::DoubleReal>(6.4195914889533672), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[9]), std::complex<klab::DoubleReal>(7.1433851997942188), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[10]), std::complex<klab::DoubleReal>(7.8593680355420412), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[11]), std::complex<klab::DoubleReal>(8.5717621977628955), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[12]), std::complex<klab::DoubleReal>(9.2857733598847343), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[13]), std::complex<klab::DoubleReal>(9.9996374058370474), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[14]), std::complex<klab::DoubleReal>(10.714455775364186), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[15]), std::complex<klab::DoubleReal>(11.428382046708077), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[16]), std::complex<klab::DoubleReal>(12.143046524720496), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[17]), std::complex<klab::DoubleReal>(12.856972796064385), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[18]), std::complex<klab::DoubleReal>(13.571791165591527), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[19]), std::complex<klab::DoubleReal>(14.28565521154384), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[20]), std::complex<klab::DoubleReal>(14.999666373665681), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[21]), std::complex<klab::DoubleReal>(15.712060535886531), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[22]), std::complex<klab::DoubleReal>(16.428043371634356), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[23]), std::complex<klab::DoubleReal>(17.151837082475208), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[24]), std::complex<klab::DoubleReal>(17.880249707412091), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[25]), std::complex<klab::DoubleReal>(18.564915366545669), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[26]), std::complex<klab::DoubleReal>(19.14821173962607), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[27]), std::complex<klab::DoubleReal>(19.760765042976153), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[28]), std::complex<klab::DoubleReal>(21.021544809306853), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[29]), std::complex<klab::DoubleReal>(23.297253088270235), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[30]), std::complex<klab::DoubleReal>(23.86799545643229), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[31]), std::complex<klab::DoubleReal>(17.437799275297827), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KInverseGaussianBlur1DOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1); 
        
        TInverseGaussianBlur1DOperator<klab::DoubleReal> op(32, 0.4, 4.0, 16);
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

void KInverseGaussianBlur1DOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(32);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1); 
        
        TInverseGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op(32, 0.4, 4.0, 16);
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
