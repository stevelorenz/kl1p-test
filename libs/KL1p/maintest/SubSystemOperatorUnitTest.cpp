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

#include "SubSystemOperatorUnitTest.h"
#include "../include/SubSystemOperator.h"
#include "../include/MatrixOperator.h"
#include "../include/DownSamplingOperator.h"
#include "../include/Fourier1DOperator.h"
#include "../include/InverseFourier1DOperator.h"
#include "../include/MultiplicationOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KSubSystemOperatorUnitTest::KSubSystemOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KSubSystemOperatorUnitTest::testOpConstructor)
    TEST_ADD(KSubSystemOperatorUnitTest::testOpIndexesConstructor)
    TEST_ADD(KSubSystemOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KSubSystemOperatorUnitTest::testOp)
    TEST_ADD(KSubSystemOperatorUnitTest::testIndexes)
    TEST_ADD(KSubSystemOperatorUnitTest::testApply)
    TEST_ADD(KSubSystemOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KSubSystemOperatorUnitTest::testColumn)
    TEST_ADD(KSubSystemOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KSubSystemOperatorUnitTest::~KSubSystemOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSubSystemOperatorUnitTest::testOpConstructor()
{
    try
    {
        TSubSystemOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.op().get()>0 && op.n()==8 && op.indexes().size()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubSystemOperatorUnitTest::testOpIndexesConstructor()
{
    try
    {
        std::vector<klab::UInt32> indexes;
        indexes.push_back(9);
        indexes.push_back(2);
        indexes.push_back(3);

        TSubSystemOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), indexes);
        TEST_ASSERT(op.op().get()>0 && op.n()==3 && op.indexes().size()==3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubSystemOperatorUnitTest::testCopyConstructor()
{
    try
    {
        std::vector<klab::UInt32> indexes;
        indexes.push_back(9);
        indexes.push_back(2);
        indexes.push_back(3);

        TSubSystemOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), indexes);
        TEST_ASSERT(op.op().get()>0 && op.n()==3 && op.indexes().size()==3)

        TSubSystemOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.op().get()>0 && op2.n()==3 && op2.indexes().size()==3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubSystemOperatorUnitTest::testOp()
{
    try
    {
        TSubSystemOperator<klab::DoubleReal> op(0);
        TEST_ASSERT(op.op().get()==0 && op.n()==0 && op.indexes().size()==0)

        TSubSystemOperator<klab::DoubleReal> op2(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op2.op().get()>0 && op2.n()==8 && op2.indexes().size()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubSystemOperatorUnitTest::testIndexes()
{
    try
    {
        std::vector<klab::UInt32> indexes;
        indexes.push_back(9);
        indexes.push_back(2);
        indexes.push_back(3);

        TSubSystemOperator<klab::DoubleReal> op(0, indexes);
        TEST_ASSERT(op.op().get()==0 && op.n()==3 && op.indexes().size()==3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubSystemOperatorUnitTest::testApply()
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

        TDownSamplingOperator<std::complex<klab::DoubleReal> >* opBitMask      = new TDownSamplingOperator<std::complex<klab::DoubleReal> >(bits);
        TInverseFourier1DOperator<std::complex<klab::DoubleReal> >* opInverseFourier = new TInverseFourier1DOperator<std::complex<klab::DoubleReal> >(16, true);   
        TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal> >* phi = new TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal> >(opBitMask, opInverseFourier);

        std::vector<klab::UInt32> indexes;
        indexes.push_back(6);
        indexes.push_back(10);

        TSubSystemOperator<std::complex<klab::DoubleReal> > op(phi, indexes);
        op.apply(x, y);

        TEST_ASSERT(y.n_rows == 12)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>( 2.82842712474619,  0.0), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>( 4.0,               0.0), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>( 2.82842712474619,  0.0), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(-2.82842712474619,  0.0), precision))
        TEST_ASSERT(klab::Equals(y[4], std::complex<klab::DoubleReal>(-4.0,               0.0), precision))
        TEST_ASSERT(klab::Equals(y[5], std::complex<klab::DoubleReal>(-2.82842712474619,  0.0), precision))
        TEST_ASSERT(klab::Equals(y[6], std::complex<klab::DoubleReal>( 2.82842712474619,  0.0), precision))
        TEST_ASSERT(klab::Equals(y[7], std::complex<klab::DoubleReal>( 4.0,               0.0), precision))
        TEST_ASSERT(klab::Equals(y[8], std::complex<klab::DoubleReal>( 2.82842712474619,  0.0), precision))
        TEST_ASSERT(klab::Equals(y[9], std::complex<klab::DoubleReal>(-2.82842712474619,  0.0), precision))
        TEST_ASSERT(klab::Equals(y[10],std::complex<klab::DoubleReal>(-4.0,               0.0), precision))
        TEST_ASSERT(klab::Equals(y[11],std::complex<klab::DoubleReal>(-2.82842712474619,  0.0), precision))


        // Limit cases.
        TSubSystemOperator<std::complex<klab::DoubleReal> > op0(0);
        try                             {op0.apply(x, y); TEST_ASSERT(false)}
        catch(KNullOperatorException)   {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubSystemOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > x(12);
        x[0] = std::complex<klab::DoubleReal>( 2.82842712474619,  0.0);
        x[1] = std::complex<klab::DoubleReal>( 4.0,               0.0);
        x[2] = std::complex<klab::DoubleReal>( 2.82842712474619,  0.0);
        x[3] = std::complex<klab::DoubleReal>(-2.82842712474619,  0.0);
        x[4] = std::complex<klab::DoubleReal>(-4.0,               0.0);
        x[5] = std::complex<klab::DoubleReal>(-2.82842712474619,  0.0);
        x[6] = std::complex<klab::DoubleReal>( 2.82842712474619,  0.0);
        x[7] = std::complex<klab::DoubleReal>( 4.0,               0.0);
        x[8] = std::complex<klab::DoubleReal>( 2.82842712474619,  0.0);
        x[9] = std::complex<klab::DoubleReal>(-2.82842712474619,  0.0);
        x[10]= std::complex<klab::DoubleReal>(-4.0,               0.0);
        x[11]= std::complex<klab::DoubleReal>(-2.82842712474619,  0.0);

        arma::Col<std::complex<klab::DoubleReal> > y;


        KBitArray bits(16);
        for(klab::UInt32 i=0; i<16; ++i)
            bits.setBit(i, ((i+1)%4==0 ? false : true));

        TDownSamplingOperator<std::complex<klab::DoubleReal> >* opBitMask      = new TDownSamplingOperator<std::complex<klab::DoubleReal> >(bits);
        TInverseFourier1DOperator<std::complex<klab::DoubleReal> >* opInverseFourier = new TInverseFourier1DOperator<std::complex<klab::DoubleReal> >(16, true);   
        TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal> >* phi = new TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal> >(opBitMask, opInverseFourier);

        std::vector<klab::UInt32> indexes;
        indexes.push_back(6);
        indexes.push_back(10);

        TSubSystemOperator<std::complex<klab::DoubleReal> > op(phi, indexes);
        op.applyAdjoint(x, y);

        TEST_ASSERT(y.n_rows == 2)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(1.4142135623731,  1.4142135623731), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(1.414213562373,  -1.4142135623731), precision))


        // Limit cases.
        TSubSystemOperator<std::complex<klab::DoubleReal> > op0(0);
        try                             {op0.applyAdjoint(x, y); TEST_ASSERT(false)}
        catch(KNullOperatorException)   {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubSystemOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 2;

        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, 8);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        std::vector<klab::UInt32> indexes;
        indexes.push_back(3);
        indexes.push_back(5);

        TSubSystemOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), indexes);

        arma::Mat<klab::DoubleReal> A(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col(n);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.apply(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<klab::DoubleReal> B(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> out;
            op.column(i, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                B(j, i) = out[j];
        }


        bool equals = true;
        for(klab::UInt32 i=0; i<m && equals; ++i)
        {
            for(klab::UInt32 j=0; j<n && equals; ++j)
                equals = klab::Equals(A(i, j), B(i, j), precision);
        }

        TEST_ASSERT(equals)


        // Limit cases.
        arma::Col<klab::DoubleReal> out;

        try                                     {op.column(n, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.column(n+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        TSubSystemOperator<klab::DoubleReal> op0(0, indexes);
        try                                     {op0.column(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubSystemOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 2;

        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, 8);
        matrix(0, 0) = 1.0;
        matrix(0, 1) = 2.0;
        matrix(0, 2) = 3.0;
        matrix(0, 3) = 4.0;
        matrix(0, 4) = 5.0;
        matrix(0, 5) = 6.0;
        matrix(0, 6) = 7.0;
        matrix(0, 7) = 8.0;
        matrix(1, 0) = 9.0;
        matrix(1, 1) = 10.0;
        matrix(1, 2) = 11.0;
        matrix(1, 3) = 12.0;
        matrix(1, 4) = 13.0;
        matrix(1, 5) = 14.0;
        matrix(1, 6) = 15.0;
        matrix(1, 7) = 16.0;
        matrix(2, 0) = 17.0;
        matrix(2, 1) = 18.0;
        matrix(2, 2) = 19.0;
        matrix(2, 3) = 20.0;
        matrix(2, 4) = 21.0;
        matrix(2, 5) = 22.0;
        matrix(2, 6) = 23.0;
        matrix(2, 7) = 24.0;
        matrix(3, 0) = 25.0;
        matrix(3, 1) = 26.0;
        matrix(3, 2) = 27.0;
        matrix(3, 3) = 28.0;
        matrix(3, 4) = 29.0;
        matrix(3, 5) = 30.0;
        matrix(3, 6) = 31.0;
        matrix(3, 7) = 32.0;

        std::vector<klab::UInt32> indexes;
        indexes.push_back(3);
        indexes.push_back(5);

        TSubSystemOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix), indexes);

        arma::Mat<klab::DoubleReal> A(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> col(m);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<klab::DoubleReal> out;
            op.applyAdjoint(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<klab::DoubleReal> B(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<klab::DoubleReal> out;
            op.columnAdjoint(i, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                B(j, i) = out[j];
        }


        bool equals = true;
        for(klab::UInt32 i=0; i<n && equals; ++i)
        {
            for(klab::UInt32 j=0; j<m && equals; ++j)
                equals = klab::Equals(A(i, j), B(i, j), precision);
        }

        TEST_ASSERT(equals)


        // Limit cases.
        arma::Col<klab::DoubleReal> out;

        try                                     {op.columnAdjoint(m, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.columnAdjoint(m+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        TSubSystemOperator<klab::DoubleReal> op0(0, indexes);
        try                                     {op0.columnAdjoint(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
