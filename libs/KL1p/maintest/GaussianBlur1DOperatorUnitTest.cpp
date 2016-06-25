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

#include "GaussianBlur1DOperatorUnitTest.h"
#include "../include/GaussianBlur1DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KGaussianBlur1DOperatorUnitTest::KGaussianBlur1DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testSizeConstructor)  
    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testSizeSigmaConstructor)  
    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testSizeSigmaCConstructor)  
    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testSigma)
    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testC)
    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testApply)
    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testApply_Complex)
    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KGaussianBlur1DOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KGaussianBlur1DOperatorUnitTest::~KGaussianBlur1DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur1DOperatorUnitTest::testSizeConstructor()
{
    try
    {
        TGaussianBlur1DOperator<klab::DoubleReal> op(32);
        TEST_ASSERT(op.n()==32 && op.sigma()==1.0 && op.c()==16)

        TGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32);
        TEST_ASSERT(op2.n()==32 && op2.sigma()==1.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur1DOperatorUnitTest::testSizeSigmaConstructor()
{
    try
    {
        TGaussianBlur1DOperator<klab::DoubleReal> op(32, 4.0);
        TEST_ASSERT(op.n()==32 && op.sigma()==4.0 && op.c()==16)

        TGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 4.0);
        TEST_ASSERT(op2.n()==32 && op2.sigma()==4.0 && op2.c()==16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur1DOperatorUnitTest::testSizeSigmaCConstructor()
{
    try
    {
        TGaussianBlur1DOperator<klab::DoubleReal> op(32, 4.0, 8);
        TEST_ASSERT(op.n()==32 && op.sigma()==4.0 && op.c()==8)

        TGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 4.0, 8);
        TEST_ASSERT(op2.n()==32 && op2.sigma()==4.0 && op2.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur1DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TGaussianBlur1DOperator<klab::DoubleReal> op(32, 4.0, 8);
        TEST_ASSERT(op.n()==32 && op.sigma()==4.0 && op.c()==8)

        TGaussianBlur1DOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.n()==32 && opCopy.sigma()==4.0 && opCopy.c()==8)


        TGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 4.0, 8);
        TEST_ASSERT(op2.n()==32 && op2.sigma()==4.0 && op2.c()==8)

        TGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.n()==32 && op2Copy.sigma()==4.0 && op2Copy.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur1DOperatorUnitTest::testSigma()
{
    try
    {
        TGaussianBlur1DOperator<klab::DoubleReal> op(32, 4.0, 8);
        TEST_ASSERT(op.sigma()==4.0)

        TGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 4.0, 8);
        TEST_ASSERT(op2.sigma()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur1DOperatorUnitTest::testC()
{
    try
    {
        TGaussianBlur1DOperator<klab::DoubleReal> op(32, 4.0, 8);
        TEST_ASSERT(op.c()==8)

        TGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op2(32, 4.0, 8);
        TEST_ASSERT(op2.c()==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur1DOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        TGaussianBlur1DOperator<klab::DoubleReal> op(32, 4.0, 16);
        op.apply(x, xr);

        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(xr[0], 11.987088584307381, precision))
        TEST_ASSERT(klab::Equals(xr[1], 5.6209108025747447, precision))
        TEST_ASSERT(klab::Equals(xr[2], 3.7016819679625508, precision))
        TEST_ASSERT(klab::Equals(xr[3], 4.076498180887878, precision))
        TEST_ASSERT(klab::Equals(xr[4], 5.0048666715024019, precision))
        TEST_ASSERT(klab::Equals(xr[5], 5.9999656837765016, precision))
        TEST_ASSERT(klab::Equals(xr[6], 7.0001639259013047, precision))
        TEST_ASSERT(klab::Equals(xr[7], 7.9998604305190026, precision))
        TEST_ASSERT(klab::Equals(xr[8], 9.0001226782851909, precision))
        TEST_ASSERT(klab::Equals(xr[9], 9.9998904421344061, precision))
        TEST_ASSERT(klab::Equals(xr[10], 11.000099484058079, precision))
        TEST_ASSERT(klab::Equals(xr[11], 11.999908144013975, precision))
        TEST_ASSERT(klab::Equals(xr[12], 13.000086220200695, precision))
        TEST_ASSERT(klab::Equals(xr[13], 13.999917751124849, precision))
        TEST_ASSERT(klab::Equals(xr[14], 15.000079717069877, precision))
        TEST_ASSERT(klab::Equals(xr[15], 15.999921515279336, precision))
        TEST_ASSERT(klab::Equals(xr[16], 17.000078484720667, precision))
        TEST_ASSERT(klab::Equals(xr[17], 17.999920282930123, precision))
        TEST_ASSERT(klab::Equals(xr[18], 19.000082248875152, precision))
        TEST_ASSERT(klab::Equals(xr[19], 19.999913779799304, precision))
        TEST_ASSERT(klab::Equals(xr[20], 21.000091855986028, precision))
        TEST_ASSERT(klab::Equals(xr[21], 21.999900515941921, precision))
        TEST_ASSERT(klab::Equals(xr[22], 23.000109557865596, precision))
        TEST_ASSERT(klab::Equals(xr[23], 23.999877321714809, precision))
        TEST_ASSERT(klab::Equals(xr[24], 25.000139569480996, precision))
        TEST_ASSERT(klab::Equals(xr[25], 25.999836074098695, precision))
        TEST_ASSERT(klab::Equals(xr[26], 27.000034316223495, precision))
        TEST_ASSERT(klab::Equals(xr[27], 27.995133328497598, precision))
        TEST_ASSERT(klab::Equals(xr[28], 28.923501819112122, precision))
        TEST_ASSERT(klab::Equals(xr[29], 29.29831803203745, precision))
        TEST_ASSERT(klab::Equals(xr[30], 27.379089197425252, precision))
        TEST_ASSERT(klab::Equals(xr[31], 21.012911415692617, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur1DOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(32);
        arma::Col<std::complex<klab::DoubleReal> > xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1);

        TGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op(32, 4.0, 16);
        op.apply(x, xr);

        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[0]), std::complex<klab::DoubleReal>(11.987088584307381), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[1]), std::complex<klab::DoubleReal>(5.6209108025747447), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[2]), std::complex<klab::DoubleReal>(3.7016819679625508), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[3]), std::complex<klab::DoubleReal>(4.076498180887878), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[4]), std::complex<klab::DoubleReal>(5.0048666715024019), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[5]), std::complex<klab::DoubleReal>(5.9999656837765016), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[6]), std::complex<klab::DoubleReal>(7.0001639259013047), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[7]), std::complex<klab::DoubleReal>(7.9998604305190026), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[8]), std::complex<klab::DoubleReal>(9.0001226782851909), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[9]), std::complex<klab::DoubleReal>(9.9998904421344061), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[10]), std::complex<klab::DoubleReal>(11.000099484058079), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[11]), std::complex<klab::DoubleReal>(11.999908144013975), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[12]), std::complex<klab::DoubleReal>(13.000086220200695), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[13]), std::complex<klab::DoubleReal>(13.999917751124849), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[14]), std::complex<klab::DoubleReal>(15.000079717069877), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[15]), std::complex<klab::DoubleReal>(15.999921515279336), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[16]), std::complex<klab::DoubleReal>(17.000078484720667), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[17]), std::complex<klab::DoubleReal>(17.999920282930123), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[18]), std::complex<klab::DoubleReal>(19.000082248875152), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[19]), std::complex<klab::DoubleReal>(19.999913779799304), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[20]), std::complex<klab::DoubleReal>(21.000091855986028), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[21]), std::complex<klab::DoubleReal>(21.999900515941921), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[22]), std::complex<klab::DoubleReal>(23.000109557865596), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[23]), std::complex<klab::DoubleReal>(23.999877321714809), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[24]), std::complex<klab::DoubleReal>(25.000139569480996), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[25]), std::complex<klab::DoubleReal>(25.999836074098695), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[26]), std::complex<klab::DoubleReal>(27.000034316223495), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[27]), std::complex<klab::DoubleReal>(27.995133328497598), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[28]), std::complex<klab::DoubleReal>(28.923501819112122), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[29]), std::complex<klab::DoubleReal>(29.29831803203745), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[30]), std::complex<klab::DoubleReal>(27.379089197425252), precision))
        TEST_ASSERT(klab::Equals(std::complex<klab::DoubleReal>(xr[31]), std::complex<klab::DoubleReal>(21.012911415692617), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussianBlur1DOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(32);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1); 
        
        TGaussianBlur1DOperator<klab::DoubleReal> op(32, 4.0, 16);
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

void KGaussianBlur1DOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(32);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        for(klab::UInt32 i=0; i<32; ++i)
            x[i] = static_cast<klab::DoubleReal>(i+1); 
        
        TGaussianBlur1DOperator<std::complex<klab::DoubleReal> > op(32, 4.0, 16);
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
