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

#include "OperatorTest.h"
#include "../include/MatrixOperator.h"
#include "../include/AdjointOperator.h"
#include "../include/DiagonalOperator.h"
#include "../include/MultiplicationOperator.h"
#include "../include/Fourier1DOperator.h"
#include "../include/InverseFourier1DOperator.h"
#include "../include/Fourier2DOperator.h"
#include "../include/InverseFourier2DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KOperatorTest::KOperatorTest() : Test::Suite()
{
    TEST_ADD(KOperatorTest::testElementWiseSquareMatrixOperator)  
    TEST_ADD(KOperatorTest::testTransposedElementWiseSquareMatrixOperator)  
    TEST_ADD(KOperatorTest::testFourierMean) 
    TEST_ADD(KOperatorTest::testFourierVariance) 
}

// ---------------------------------------------------------------------------------------------------- //

KOperatorTest::~KOperatorTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorTest::testElementWiseSquareMatrixOperator()
{
    try
    {
        klab::UInt32 m = 16;    
        klab::UInt32 n = 64;   

        klab::DoubleReal precision = 1e-12;


        arma::Mat<klab::DoubleReal> A(m, n);
        arma::Mat<klab::DoubleReal> A2(m, n);
        arma::Mat<klab::DoubleReal> AxT(n, m);
        arma::Col<klab::DoubleReal> x(n);

        klab::KRandom::Instance().setSeed(12345);

        for(klab::UInt32 i=0; i<n; ++i)
            x[i] = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                klab::DoubleReal value = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);

                A(i, j)  = value;
                A2(i, j) = value * value;
                AxT(j, i) = x[j] * value;
            }
        }           

        arma::Col<klab::DoubleReal> result  = A2 * x;
        arma::Mat<klab::DoubleReal> mat = A * AxT;

        TEST_ASSERT(mat.n_rows==mat.n_cols && mat.n_rows==result.n_rows)

        bool equals = true;
        for(klab::UInt32 i=0; i<m && equals; ++i)
            equals = klab::Equals(mat(i, i), result[i], precision);

        TEST_ASSERT(equals)


        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > op   = new TMatrixOperator<klab::DoubleReal>(A);
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > opT  = new TAdjointOperator<klab::DoubleReal>(op);
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > xOp  = new TDiagonalOperator<klab::DoubleReal>(x);
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > sqOp = op * xOp * opT;
        
        arma::Col<klab::DoubleReal> xr(m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> col(m);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> colr;
            sqOp->apply(col, colr);

            xr[i] = colr[i];
        }

        TEST_ASSERT(xr.n_rows == result.n_rows)

        equals = true;
        for(klab::UInt32 i=0; i<m && equals; ++i)
            equals = klab::Equals(xr[i], result[i], precision);

        TEST_ASSERT(equals)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorTest::testTransposedElementWiseSquareMatrixOperator()
{
    try
    {
        klab::UInt32 m = 16;    
        klab::UInt32 n = 64;   

        klab::DoubleReal precision = 1e-12;


        arma::Mat<klab::DoubleReal> A(m, n);
        arma::Mat<klab::DoubleReal> A2(m, n);
        arma::Mat<klab::DoubleReal> Ax(m, n);
        arma::Col<klab::DoubleReal> x(m);

        klab::KRandom::Instance().setSeed(12345);

        for(klab::UInt32 i=0; i<m; ++i)
            x[i] = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                klab::DoubleReal value = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);

                A(i, j)  = value;
                A2(i, j) = value * value;
                Ax(i, j) = x[i] * value;
            }
        }           

        arma::Col<klab::DoubleReal> result  = arma::trans(A2) * x;
        arma::Mat<klab::DoubleReal> mat = arma::trans(A) * Ax;

        TEST_ASSERT(mat.n_rows==mat.n_cols && mat.n_rows==result.n_rows)

        bool equals = true;
        for(klab::UInt32 i=0; i<m && equals; ++i)
            equals = klab::Equals(mat(i, i), result[i], precision);

        TEST_ASSERT(equals)


        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > op   = new TMatrixOperator<klab::DoubleReal>(A);
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > opT  = new TAdjointOperator<klab::DoubleReal>(op);
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > xOp  = new TDiagonalOperator<klab::DoubleReal>(x);
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > sqOp = opT * xOp * op;
        
        arma::Col<klab::DoubleReal> xr(n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col(n);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> colr;
            sqOp->apply(col, colr);

            xr[i] = colr[i];
        }

        TEST_ASSERT(xr.n_rows == result.n_rows)

        equals = true;
        for(klab::UInt32 i=0; i<n && equals; ++i)
            equals = klab::Equals(xr[i], result[i], precision);

        TEST_ASSERT(equals)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorTest::testFourierMean()
{
    try
    {
        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_01(8);
        TEST_ASSERT(klab::Equals(opF1D_01.mean(), std::complex<klab::DoubleReal>(0.125, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_02(16);
        TEST_ASSERT(klab::Equals(opF1D_02.mean(), std::complex<klab::DoubleReal>(0.0625, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_03(32);
        TEST_ASSERT(klab::Equals(opF1D_03.mean(), std::complex<klab::DoubleReal>(0.03125, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_04(64);
        TEST_ASSERT(klab::Equals(opF1D_04.mean(), std::complex<klab::DoubleReal>(0.015625, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_05(128);
        TEST_ASSERT(klab::Equals(opF1D_05.mean(), std::complex<klab::DoubleReal>(0.0078125, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_06(256);
        TEST_ASSERT(klab::Equals(opF1D_06.mean(), std::complex<klab::DoubleReal>(0.00390625, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_07(512);
        TEST_ASSERT(klab::Equals(opF1D_07.mean(), std::complex<klab::DoubleReal>(0.001953125, 0.0)))


        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_01(8);
        TEST_ASSERT(klab::Equals(opIF1D_01.mean(), std::complex<klab::DoubleReal>(0.015625, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_02(16);
        TEST_ASSERT(klab::Equals(opIF1D_02.mean(), std::complex<klab::DoubleReal>(0.00390625, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_03(32);
        TEST_ASSERT(klab::Equals(opIF1D_03.mean(), std::complex<klab::DoubleReal>(0.0009765625, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_04(64);
        TEST_ASSERT(klab::Equals(opIF1D_04.mean(), std::complex<klab::DoubleReal>(0.000244140625, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_05(128);
        TEST_ASSERT(klab::Equals(opIF1D_05.mean(), std::complex<klab::DoubleReal>(0.00006103515625, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_06(256);
        TEST_ASSERT(klab::Equals(opIF1D_06.mean(), std::complex<klab::DoubleReal>(0.0000152587890625, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_07(512);
        TEST_ASSERT(klab::Equals(opIF1D_07.mean(), std::complex<klab::DoubleReal>(0.000003814697265625, 0.0)))


        TFourier2DOperator<std::complex<klab::DoubleReal> > opF2D_01(8, 8);
        TEST_ASSERT(klab::Equals(opF2D_01.mean(), std::complex<klab::DoubleReal>(0.015625, 0.0)))

        TFourier2DOperator<std::complex<klab::DoubleReal> > opF2D_02(16, 16);
        TEST_ASSERT(klab::Equals(opF2D_02.mean(), std::complex<klab::DoubleReal>(0.00390625, 0.0)))

        //TFourier2DOperator<std::complex<klab::DoubleReal> > opF2D_03(32, 32);
        //TEST_ASSERT(klab::Equals(opF2D_03.mean(), std::complex<klab::DoubleReal>(0.0009765625, 0.0)))


        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > opIF2D_01(8, 8);
        TEST_ASSERT(klab::Equals(opIF2D_01.mean(), std::complex<klab::DoubleReal>(0.000244140625, 0.0)))

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > opIF2D_02(16, 16);
        TEST_ASSERT(klab::Equals(opIF2D_02.mean(), std::complex<klab::DoubleReal>(1.5258789062500000e-005, 0.0)))

        //TInverseFourier2DOperator<std::complex<klab::DoubleReal> > opIF2D_03(32, 32);
        //TEST_ASSERT(klab::Equals(opIF2D_03.mean(), std::complex<klab::DoubleReal>(9.5367431640625000e-007, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KOperatorTest::testFourierVariance()
{
    try
    {
        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_01(8);
        TEST_ASSERT(klab::Equals(opF1D_01.variance(), std::complex<klab::DoubleReal>(0.984375, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_02(16);
        TEST_ASSERT(klab::Equals(opF1D_02.variance(), std::complex<klab::DoubleReal>(0.99609375, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_03(32);
        TEST_ASSERT(klab::Equals(opF1D_03.variance(), std::complex<klab::DoubleReal>(0.9990234375, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_04(64);
        TEST_ASSERT(klab::Equals(opF1D_04.variance(), std::complex<klab::DoubleReal>(0.999755859375, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_05(128);
        TEST_ASSERT(klab::Equals(opF1D_05.variance(), std::complex<klab::DoubleReal>(0.99993896484375, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_06(256);
        TEST_ASSERT(klab::Equals(opF1D_06.variance(), std::complex<klab::DoubleReal>(0.9999847412109375, 0.0)))

        TFourier1DOperator<std::complex<klab::DoubleReal> > opF1D_07(512);
        TEST_ASSERT(klab::Equals(opF1D_07.variance(), std::complex<klab::DoubleReal>(0.99999618530273438, 0.0)))


        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_01(8);
        TEST_ASSERT(klab::Equals(opIF1D_01.variance(), std::complex<klab::DoubleReal>(0.015380859375, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_02(16);
        TEST_ASSERT(klab::Equals(opIF1D_02.variance(), std::complex<klab::DoubleReal>(0.0038909912109375, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_03(32);
        TEST_ASSERT(klab::Equals(opIF1D_03.variance(), std::complex<klab::DoubleReal>(0.00097560882568359375, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_04(64);
        TEST_ASSERT(klab::Equals(opIF1D_04.variance(), std::complex<klab::DoubleReal>(0.00024408102035522461, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_05(128);
        TEST_ASSERT(klab::Equals(opIF1D_05.variance(), std::complex<klab::DoubleReal>(6.1031430959701538e-005, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_06(256);
        TEST_ASSERT(klab::Equals(opIF1D_06.variance(), std::complex<klab::DoubleReal>(1.5258556231856346e-005, 0.0)))

        TInverseFourier1DOperator<std::complex<klab::DoubleReal> > opIF1D_07(512);
        TEST_ASSERT(klab::Equals(opIF1D_07.variance(), std::complex<klab::DoubleReal>(3.8146827137097716e-006, 0.0)))


        TFourier2DOperator<std::complex<klab::DoubleReal> > opF2D_01(8, 8);
        TEST_ASSERT(klab::Equals(opF2D_01.variance(), std::complex<klab::DoubleReal>(0.999755859375, 0.0)))

        TFourier2DOperator<std::complex<klab::DoubleReal> > opF2D_02(16, 16);
        TEST_ASSERT(klab::Equals(opF2D_02.variance(), std::complex<klab::DoubleReal>(0.9999847412109375, 0.0)))

        //TFourier2DOperator<std::complex<klab::DoubleReal> > opF2D_03(32, 32);
        //TEST_ASSERT(klab::Equals(opF2D_03.variance(), std::complex<klab::DoubleReal>(0.99999904632568359, 0.0)))


        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > opIF2D_01(8, 8);
        TEST_ASSERT(klab::Equals(opIF2D_01.variance(), std::complex<klab::DoubleReal>(0.00024408102035522461, 0.0)))

        TInverseFourier2DOperator<std::complex<klab::DoubleReal> > opIF2D_02(16, 16);
        TEST_ASSERT(klab::Equals(opIF2D_02.variance(), std::complex<klab::DoubleReal>(1.5258556231856346e-005, 0.0)))

        //TInverseFourier2DOperator<std::complex<klab::DoubleReal> > opIF2D_03(32, 32);
        //TEST_ASSERT(klab::Equals(opIF2D_03.variance(), std::complex<klab::DoubleReal>(9.5367340691154823e-007, 0.0)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
