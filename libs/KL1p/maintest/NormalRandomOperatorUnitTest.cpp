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

#include "NormalRandomOperatorUnitTest.h"
#include "../include/NormalRandomOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KNormalRandomOperatorUnitTest::KNormalRandomOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KNormalRandomOperatorUnitTest::testMNConstructor)  
    TEST_ADD(KNormalRandomOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KNormalRandomOperatorUnitTest::testIsZero)
    TEST_ADD(KNormalRandomOperatorUnitTest::testSum)
    TEST_ADD(KNormalRandomOperatorUnitTest::testNormFrobenius)
    TEST_ADD(KNormalRandomOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KNormalRandomOperatorUnitTest::testMean)
    TEST_ADD(KNormalRandomOperatorUnitTest::testVariance)
    TEST_ADD(KNormalRandomOperatorUnitTest::testApply)
    TEST_ADD(KNormalRandomOperatorUnitTest::testApply_Complex)
    TEST_ADD(KNormalRandomOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KNormalRandomOperatorUnitTest::testApplyAdjoint_Complex)
    TEST_ADD(KNormalRandomOperatorUnitTest::testColumn)
    TEST_ADD(KNormalRandomOperatorUnitTest::testColumn_Complex)
    TEST_ADD(KNormalRandomOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KNormalRandomOperatorUnitTest::testColumnAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KNormalRandomOperatorUnitTest::~KNormalRandomOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testMNConstructor()
{
    try
    {
        TNormalRandomOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.mean()==0.0 && op.variance()==1.0)

        TNormalRandomOperator<klab::DoubleReal> op2(4, 8, 1.0, 2.0);
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(op2.mean()==1.0 && op2.variance()==4.0)

        TNormalRandomOperator<std::complex<klab::DoubleReal> > cop(4, 8);
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.mean()==0.0 && cop.variance()==1.0)

        TNormalRandomOperator<std::complex<klab::DoubleReal> > cop2(4, 8, 1.0, 2.0);
        TEST_ASSERT(cop2.m()==4 && cop2.n()==8)
        TEST_ASSERT(cop2.mean()==1.0 && cop2.variance()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TNormalRandomOperator<klab::DoubleReal> op(4, 8, 1.0, 2.0);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.mean()==1.0 && op.variance()==4.0)

        TNormalRandomOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(op2.mean()==1.0 && op2.variance()==4.0)

        TNormalRandomOperator<std::complex<klab::DoubleReal> > cop(4, 8, 1.0, 2.0);
        TEST_ASSERT(cop.m()==4 && cop.n()==8)
        TEST_ASSERT(cop.mean()==1.0 && cop.variance()==4.0)

        TNormalRandomOperator<std::complex<klab::DoubleReal> > cop2(cop);
        TEST_ASSERT(cop2.m()==4 && cop2.n()==8)
        TEST_ASSERT(cop2.mean()==1.0 && cop2.variance()==4.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testIsZero()
{
    try
    {
        TNormalRandomOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)

        TNormalRandomOperator<klab::DoubleReal> op2(4, 8, 0, 0);
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(op2.isZero())

        TNormalRandomOperator<std::complex<klab::DoubleReal> > op3(4, 8, 0, 0);
        TEST_ASSERT(op3.m()==4 && op3.n()==8)
        TEST_ASSERT(op3.isZero())


        // Limit cases.
        TNormalRandomOperator<klab::DoubleReal> op0(0, 8);
        TEST_ASSERT(op0.m()==0 && op0.n()==8)
        TEST_ASSERT(op0.isZero())

        TNormalRandomOperator<klab::DoubleReal> op00(4, 0);
        TEST_ASSERT(op00.m()==4 && op00.n()==0)
        TEST_ASSERT(op00.isZero())

        TNormalRandomOperator<klab::DoubleReal> op000(0, 0);
        TEST_ASSERT(op000.m()==0 && op000.n()==0)
        TEST_ASSERT(op000.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testSum()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);
        klab::DoubleReal precision = 1e-6;        

        TNormalRandomOperator<klab::DoubleReal> op(40, 80, 1.0, 2.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j];
        }
        TEST_ASSERT(klab::Equals(op.sum(), sum, 2e2))


        TNormalRandomOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1.0, 2.0), std::complex<klab::DoubleReal>(3.0, 4.0));
        std::complex<klab::DoubleReal>  csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j];
        }
        TEST_ASSERT(klab::Equals(cop.sum(), csum, 4e2))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testNormFrobenius()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);     

        TNormalRandomOperator<klab::DoubleReal> op(40, 80, 1000.0, 2000.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j] * col[j];
        }
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(sum), 10000.0))


        TNormalRandomOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0));
        std::complex<klab::DoubleReal>  csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j].real()*col[j].real() + col[j].imag()*col[j].imag();
        }
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), klab::Sqrt(csum), 10000.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testSquaredNormFrobenius()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);   

        TNormalRandomOperator<klab::DoubleReal> op(40, 80, 1000.0, 2000.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j] * col[j];
        }
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), sum, 1e10))


        TNormalRandomOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0));
        std::complex<klab::DoubleReal>  csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j].real()*col[j].real() + col[j].imag()*col[j].imag();
        }
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), csum, 1e10))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testMean()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);
        klab::DoubleReal precision = 1e-12;        

        TNormalRandomOperator<klab::DoubleReal> op(40, 80, 1000.0, 2000.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j];
        }
        TEST_ASSERT(klab::Equals(op.mean(), sum/static_cast<klab::DoubleReal>(op.m()*op.n()), 100))
        TEST_ASSERT(klab::Equals(op.mean(), 1000.0, precision))


        TNormalRandomOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0));
        std::complex<klab::DoubleReal>  csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j];
        }
        TEST_ASSERT(klab::Equals(cop.mean(), csum/static_cast<klab::DoubleReal>(cop.m()*cop.n()), 200))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(1000.0, 2000.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testVariance()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);
        klab::DoubleReal precision = 1e-12;        

        TNormalRandomOperator<klab::DoubleReal> op(40, 80, 1000.0, 2000.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j] * col[j];
        }
        TEST_ASSERT(klab::Equals(op.variance(), (sum/static_cast<klab::DoubleReal>(op.m()*op.n())) - op.mean()*op.mean(), 1000000.0))
        TEST_ASSERT(klab::Equals(op.variance(), 4000000.0, precision))


        TNormalRandomOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0));
        std::complex<klab::DoubleReal>  csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j].real()*col[j].real() + col[j].imag()*col[j].imag();
        }
        TEST_ASSERT(klab::Equals(cop.variance(), (csum/static_cast<klab::DoubleReal>(cop.m()*cop.n())) - klab::Conj(cop.mean())*cop.mean(), 10000000.0))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(25000000.0, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testApply()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12;        

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;        

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;


        arma::Mat<klab::DoubleReal> A(m, n);

        klab::KRandom random(klab::KRandom::Instance().seed());
        std::vector<klab::UInt32> seeds(m);
        for(klab::UInt32 i=0; i<m; ++i)
            seeds[i] = random.generateUInt32();

        for(klab::UInt32 i=0; i<m; ++i)
        {
            random.setSeed(seeds[i]);
            for(klab::UInt32 j=0; j<n; ++j)
                A(i, j) = TNormalRandomOperatorSpecialisation<klab::DoubleReal>::GenerateNormalRandomNumber(random, 0.0, 1.0);
        }

        arma::Col<klab::DoubleReal> result = A * x;


        TNormalRandomOperator<klab::DoubleReal> op(m, n);
        TEST_ASSERT(op.m()==m && op.n()==n)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], result[0], precision))
        TEST_ASSERT(klab::Equals(y[1], result[1], precision))
        TEST_ASSERT(klab::Equals(y[2], result[2], precision))
        TEST_ASSERT(klab::Equals(y[3], result[3], precision))

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], result[0], precision))
        TEST_ASSERT(klab::Equals(y[1], result[1], precision))
        TEST_ASSERT(klab::Equals(y[2], result[2], precision))
        TEST_ASSERT(klab::Equals(y[3], result[3], precision))


        // Limit cases.
        try                                             {op.apply(arma::Col<klab::DoubleReal>(), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)      {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
        
        try                                             {op.apply(arma::Col<klab::DoubleReal>(m), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)      {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12;        

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;        

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;


        arma::Mat<std::complex<klab::DoubleReal> > A(m, n);

        klab::KRandom random(klab::KRandom::Instance().seed());
        std::vector<klab::UInt32> seeds(m);
        for(klab::UInt32 i=0; i<m; ++i)
            seeds[i] = random.generateUInt32();

        for(klab::UInt32 i=0; i<m; ++i)
        {
            random.setSeed(seeds[i]);
            for(klab::UInt32 j=0; j<n; ++j)
                A(i, j) = TNormalRandomOperatorSpecialisation<std::complex<klab::DoubleReal> >::GenerateNormalRandomNumber(random, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));
        }

        arma::Col<std::complex<klab::DoubleReal> > result = A * x;


        TNormalRandomOperator<std::complex<klab::DoubleReal> > op(m, n, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));
        TEST_ASSERT(op.m()==m && op.n()==n)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], result[0], precision))
        TEST_ASSERT(klab::Equals(y[1], result[1], precision))
        TEST_ASSERT(klab::Equals(y[2], result[2], precision))
        TEST_ASSERT(klab::Equals(y[3], result[3], precision))

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], result[0], precision))
        TEST_ASSERT(klab::Equals(y[1], result[1], precision))
        TEST_ASSERT(klab::Equals(y[2], result[2], precision))
        TEST_ASSERT(klab::Equals(y[3], result[3], precision))


        // Limit cases.
        try                                             {op.apply(arma::Col<std::complex<klab::DoubleReal> >(), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)      {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
        
        try                                             {op.apply(arma::Col<std::complex<klab::DoubleReal> >(m), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)      {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12;        

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;


        arma::Mat<klab::DoubleReal> A(m, n);

        klab::KRandom random(klab::KRandom::Instance().seed());
        std::vector<klab::UInt32> seeds(m);
        for(klab::UInt32 i=0; i<m; ++i)
            seeds[i] = random.generateUInt32();

        for(klab::UInt32 i=0; i<m; ++i)
        {
            random.setSeed(seeds[i]);
            for(klab::UInt32 j=0; j<n; ++j)
                A(i, j) = TNormalRandomOperatorSpecialisation<klab::DoubleReal>::GenerateNormalRandomNumber(random, 0.0, 1.0);
        }

        arma::Col<klab::DoubleReal> yr     = A * x;
        arma::Col<klab::DoubleReal> result = arma::trans(A) * yr;


        TNormalRandomOperator<klab::DoubleReal> op(m, n);
        TEST_ASSERT(op.m()==m && op.n()==n)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], yr[0], precision))
        TEST_ASSERT(klab::Equals(y[1], yr[1], precision))
        TEST_ASSERT(klab::Equals(y[2], yr[2], precision))
        TEST_ASSERT(klab::Equals(y[3], yr[3], precision))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], result[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], result[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], result[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], result[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], result[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], result[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], result[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], result[7], precision))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], result[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], result[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], result[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], result[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], result[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], result[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], result[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], result[7], precision))


        // Limit cases.
        try                                             {op.applyAdjoint(arma::Col<klab::DoubleReal>(), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)      {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
        
        try                                             {op.applyAdjoint(arma::Col<klab::DoubleReal>(n), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)      {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12;        

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;


        arma::Mat<std::complex<klab::DoubleReal> > A(m, n);

        klab::KRandom random(klab::KRandom::Instance().seed());
        std::vector<klab::UInt32> seeds(m);
        for(klab::UInt32 i=0; i<m; ++i)
            seeds[i] = random.generateUInt32();

        for(klab::UInt32 i=0; i<m; ++i)
        {
            random.setSeed(seeds[i]);
            for(klab::UInt32 j=0; j<n; ++j)
                A(i, j) = TNormalRandomOperatorSpecialisation<std::complex<klab::DoubleReal> >::GenerateNormalRandomNumber(random, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));
        }

        arma::Col<std::complex<klab::DoubleReal> > yr     = A * x;
        arma::Col<std::complex<klab::DoubleReal> > result = arma::trans(A) * yr;


        TNormalRandomOperator<std::complex<klab::DoubleReal> > op(m, n, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));
        TEST_ASSERT(op.m()==m && op.n()==n)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], yr[0], precision))
        TEST_ASSERT(klab::Equals(y[1], yr[1], precision))
        TEST_ASSERT(klab::Equals(y[2], yr[2], precision))
        TEST_ASSERT(klab::Equals(y[3], yr[3], precision))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], result[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], result[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], result[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], result[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], result[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], result[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], result[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], result[7], precision))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0], result[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], result[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], result[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], result[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], result[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], result[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], result[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], result[7], precision))


        // Limit cases.
        try                                             {op.applyAdjoint(arma::Col<std::complex<klab::DoubleReal> >(n), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)      {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
        
        try                                             {op.applyAdjoint(arma::Col<std::complex<klab::DoubleReal> >(), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)      {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12; 

        TNormalRandomOperator<klab::DoubleReal> op(m, n);
        TEST_ASSERT(op.m()==m && op.n()==n)

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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testColumn_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12; 

        TNormalRandomOperator<std::complex<klab::DoubleReal> > op(m, n);
        TEST_ASSERT(op.m()==m && op.n()==n)

        arma::Mat<std::complex<klab::DoubleReal> > A(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col(n);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<std::complex<klab::DoubleReal> > out;
            op.apply(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<std::complex<klab::DoubleReal> > B(m, n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > out;
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
        arma::Col<std::complex<klab::DoubleReal> > out;

        try                                     {op.column(n, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.column(n+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12; 

        TNormalRandomOperator<klab::DoubleReal> op(m, n);
        TEST_ASSERT(op.m()==m && op.n()==n)

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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomOperatorUnitTest::testColumnAdjoint_Complex()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12; 

        TNormalRandomOperator<std::complex<klab::DoubleReal> > op(m, n);
        TEST_ASSERT(op.m()==m && op.n()==n)

        arma::Mat<std::complex<klab::DoubleReal> > A(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col(m);
            col.fill(0.0);
            col[i] = 1.0;

            arma::Col<std::complex<klab::DoubleReal> > out;
            op.applyAdjoint(col, out);

            for(klab::UInt32 j=0; j<out.n_rows; ++j)
                A(j, i) = out[j];
        }

        arma::Mat<std::complex<klab::DoubleReal> > B(n, m);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > out;
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
        arma::Col<std::complex<klab::DoubleReal> > out;

        try                                     {op.columnAdjoint(m, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.columnAdjoint(m+1, out); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
