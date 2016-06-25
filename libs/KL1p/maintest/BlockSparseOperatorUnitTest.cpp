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

#include "BlockSparseOperatorUnitTest.h"
#include "../include/BlockSparseOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KBlockSparseOperatorUnitTest::KBlockSparseOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KBlockSparseOperatorUnitTest::testMNOpIJConstructor) 
    TEST_ADD(KBlockSparseOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KBlockSparseOperatorUnitTest::testI)
    TEST_ADD(KBlockSparseOperatorUnitTest::testJ)
    TEST_ADD(KBlockSparseOperatorUnitTest::testOp)
    TEST_ADD(KBlockSparseOperatorUnitTest::testApply)
    TEST_ADD(KBlockSparseOperatorUnitTest::testApply_02)
    TEST_ADD(KBlockSparseOperatorUnitTest::testApply_03)
    TEST_ADD(KBlockSparseOperatorUnitTest::testApply_04)
    TEST_ADD(KBlockSparseOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KBlockSparseOperatorUnitTest::testApplyAdjoint_02)
    TEST_ADD(KBlockSparseOperatorUnitTest::testApplyAdjoint_03)
    TEST_ADD(KBlockSparseOperatorUnitTest::testApplyAdjoint_04)
    TEST_ADD(KBlockSparseOperatorUnitTest::testColumn)
    TEST_ADD(KBlockSparseOperatorUnitTest::testColumn_02)
    TEST_ADD(KBlockSparseOperatorUnitTest::testColumn_03)
    TEST_ADD(KBlockSparseOperatorUnitTest::testColumn_04)
    TEST_ADD(KBlockSparseOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KBlockSparseOperatorUnitTest::testColumnAdjoint_02)
    TEST_ADD(KBlockSparseOperatorUnitTest::testColumnAdjoint_03)
    TEST_ADD(KBlockSparseOperatorUnitTest::testColumnAdjoint_04)
}

// ---------------------------------------------------------------------------------------------------- //

KBlockSparseOperatorUnitTest::~KBlockSparseOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testMNOpIJConstructor()
{
    try
    {
        TBlockSparseOperator<klab::DoubleReal> op(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)));
        TEST_ASSERT(op.m()==8 && op.n()==16)
        TEST_ASSERT(op.i()==0 && op.j()==0)
        TEST_ASSERT(op.op()!=0 && op.op()->m()==4 && op.op()->n()==6)  

        TBlockSparseOperator<klab::DoubleReal> op2(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 2, 3);
        TEST_ASSERT(op2.m()==8 && op2.n()==16)
        TEST_ASSERT(op2.i()==2 && op2.j()==3)
        TEST_ASSERT(op2.op()!=0 && op2.op()->m()==4 && op2.op()->n()==6)  


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op0(8, 16, 0);
        TEST_ASSERT(op0.m()==8 && op0.n()==16)
        TEST_ASSERT(op0.i()==0 && op0.j()==0)
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KBlockSparseOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TBlockSparseOperator<klab::DoubleReal> op(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 2, 3);
        TEST_ASSERT(op.m()==8 && op.n()==16)
        TEST_ASSERT(op.i()==2 && op.j()==3)
        TEST_ASSERT(op.op()!=0 && op.op()->m()==4 && op.op()->n()==6)

        TBlockSparseOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==8 && opCopy.n()==16)
        TEST_ASSERT(opCopy.i()==2 && opCopy.j()==3)
        TEST_ASSERT(opCopy.op()!=0 && opCopy.op()==op.op() && opCopy.op()->m()==4 && opCopy.op()->n()==6)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testI()
{
    try
    {
        TBlockSparseOperator<klab::DoubleReal> op(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)));
        TEST_ASSERT(op.m()==8 && op.n()==16)
        TEST_ASSERT(op.i()==0 && op.j()==0)

        TBlockSparseOperator<klab::DoubleReal> op2(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 2, 3);
        TEST_ASSERT(op2.m()==8 && op2.n()==16)
        TEST_ASSERT(op2.i()==2 && op2.j()==3)  


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op3(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 8, 3);
        TEST_ASSERT(op3.m()==8 && op3.n()==16)
        TEST_ASSERT(op3.i()==8 && op3.j()==3)

        TBlockSparseOperator<klab::DoubleReal> op4(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 2, 16);
        TEST_ASSERT(op4.m()==8 && op4.n()==16)
        TEST_ASSERT(op4.i()==2 && op4.j()==16)

        TBlockSparseOperator<klab::DoubleReal> op5(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 8, 16);
        TEST_ASSERT(op5.m()==8 && op5.n()==16)
        TEST_ASSERT(op5.i()==8 && op5.j()==16)

        TBlockSparseOperator<klab::DoubleReal> op6(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 14)), 2, 3);
        TEST_ASSERT(op6.m()==8 && op6.n()==16)
        TEST_ASSERT(op6.i()==2 && op6.j()==3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testJ()
{
    try
    {
        TBlockSparseOperator<klab::DoubleReal> op(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)));
        TEST_ASSERT(op.m()==8 && op.n()==16)
        TEST_ASSERT(op.i()==0 && op.j()==0)

        TBlockSparseOperator<klab::DoubleReal> op2(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 2, 3);
        TEST_ASSERT(op2.m()==8 && op2.n()==16)
        TEST_ASSERT(op2.i()==2 && op2.j()==3)  


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op3(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 8, 3);
        TEST_ASSERT(op3.m()==8 && op3.n()==16)
        TEST_ASSERT(op3.i()==8 && op3.j()==3)

        TBlockSparseOperator<klab::DoubleReal> op4(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 2, 16);
        TEST_ASSERT(op4.m()==8 && op4.n()==16)
        TEST_ASSERT(op4.i()==2 && op4.j()==16)

        TBlockSparseOperator<klab::DoubleReal> op5(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 8, 16);
        TEST_ASSERT(op5.m()==8 && op5.n()==16)
        TEST_ASSERT(op5.i()==8 && op5.j()==16)

        TBlockSparseOperator<klab::DoubleReal> op6(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 14)), 2, 3);
        TEST_ASSERT(op6.m()==8 && op6.n()==16)
        TEST_ASSERT(op6.i()==2 && op6.j()==3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testOp()
{
    try
    {
        TBlockSparseOperator<klab::DoubleReal> op(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)));
        TEST_ASSERT(op.m()==8 && op.n()==16)
        TEST_ASSERT(op.i()==0 && op.j()==0)
        TEST_ASSERT(op.op()!=0 && op.op()->m()==4 && op.op()->n()==6)  

        TBlockSparseOperator<klab::DoubleReal> op2(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)), 2, 3);
        TEST_ASSERT(op2.m()==8 && op2.n()==16)
        TEST_ASSERT(op2.i()==2 && op2.j()==3)
        TEST_ASSERT(op2.op()!=0 && op2.op()->m()==4 && op2.op()->n()==6)  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testApply()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x(12);
        arma::Col<klab::DoubleReal> y;

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

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;

        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 3, 2);
        TEST_ASSERT(op.m()==8 && op.n()==12)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 276.0, precision))
        TEST_ASSERT(klab::Equals(y[4], 692.0, precision))
        TEST_ASSERT(klab::Equals(y[5], 1108.0, precision))
        TEST_ASSERT(klab::Equals(y[6], 1524.0, precision))
        TEST_ASSERT(klab::Equals(y[7], 0.0, precision))


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 3, 2);
        try                             {op0.apply(x, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testApply_02()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x(12);
        arma::Col<klab::DoubleReal> y;

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

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;

        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 6, 2);
        TEST_ASSERT(op.m()==8 && op.n()==12)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[4], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[6], 276.0, precision))
        TEST_ASSERT(klab::Equals(y[7], 692.0, precision))


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 6, 2);
        try                             {op0.apply(x, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testApply_03()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x(12);
        arma::Col<klab::DoubleReal> y;

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

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;

        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 3, 5);
        TEST_ASSERT(op.m()==8 && op.n()==12)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 280.0, precision))
        TEST_ASSERT(klab::Equals(y[4], 784.0, precision))
        TEST_ASSERT(klab::Equals(y[5], 1288.0, precision))
        TEST_ASSERT(klab::Equals(y[6], 1792.0, precision))
        TEST_ASSERT(klab::Equals(y[7], 0.0, precision))


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 3, 5);
        try                             {op0.apply(x, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testApply_04()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x(12);
        arma::Col<klab::DoubleReal> y;

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

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;

        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 6, 5);
        TEST_ASSERT(op.m()==8 && op.n()==12)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[4], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[6], 280.0, precision))
        TEST_ASSERT(klab::Equals(y[7], 784.0, precision))


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 6, 5);
        try                             {op0.apply(x, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x(12);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

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

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;

        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 3, 2);
        TEST_ASSERT(op.m()==8 && op.n()==12)

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 12)
        TEST_ASSERT(klab::Equals(xr[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 63440.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 67040.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 70640.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 74240.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 77840.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 81440.0, precision))
        TEST_ASSERT(klab::Equals(xr[8], 85040.0, precision))
        TEST_ASSERT(klab::Equals(xr[9], 88640.0, precision))
        TEST_ASSERT(klab::Equals(xr[10], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[11], 0.0, precision))


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 3, 2);
        try                             {op0.applyAdjoint(y, xr); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testApplyAdjoint_02()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x(12);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

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

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;

        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 6, 2);
        TEST_ASSERT(op.m()==8 && op.n()==12)

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 12)
        TEST_ASSERT(klab::Equals(xr[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 6504.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 7472.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 8440.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 9408.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 10376.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 11344.0, precision))
        TEST_ASSERT(klab::Equals(xr[8], 12312.0, precision))
        TEST_ASSERT(klab::Equals(xr[9], 13280.0, precision))
        TEST_ASSERT(klab::Equals(xr[10], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[11], 0.0, precision))


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 6, 2);
        try                             {op0.applyAdjoint(y, xr); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testApplyAdjoint_03()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x(12);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

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

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;

        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 3, 5);
        TEST_ASSERT(op.m()==8 && op.n()==12)

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 12)
        TEST_ASSERT(klab::Equals(xr[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 74032.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 78176.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 82320.0, precision))
        TEST_ASSERT(klab::Equals(xr[8], 86464.0, precision))
        TEST_ASSERT(klab::Equals(xr[9], 90608.0, precision))
        TEST_ASSERT(klab::Equals(xr[10], 94752.0, precision))
        TEST_ASSERT(klab::Equals(xr[11], 98896.0, precision))


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 3, 5);
        try                             {op0.applyAdjoint(y, xr); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testApplyAdjoint_04()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x(12);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

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

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;

        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 6, 5);
        TEST_ASSERT(op.m()==8 && op.n()==12)

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 12)
        TEST_ASSERT(klab::Equals(xr[0], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 7336.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 8400.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 9464.0, precision))
        TEST_ASSERT(klab::Equals(xr[8], 10528.0, precision))
        TEST_ASSERT(klab::Equals(xr[9], 11592.0, precision))
        TEST_ASSERT(klab::Equals(xr[10], 12656.0, precision))
        TEST_ASSERT(klab::Equals(xr[11], 13720.0, precision))


        // Limit cases.
        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 6, 5);
        try                             {op0.applyAdjoint(y, xr); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 12;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(4, 8);
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


        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 3, 2);

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

        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 3, 2);
        try                             {op0.column(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testColumn_02()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 12;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(4, 8);
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


        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 6, 2);

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

        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 6, 2);
        try                             {op0.column(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testColumn_03()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 12;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(4, 8);
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


        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 3, 5);

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

        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 3, 5);
        try                             {op0.column(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testColumn_04()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 12;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(4, 8);
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


        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 6, 5);

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

        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 6, 5);
        try                             {op0.column(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}
// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 12;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(4, 8);
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


        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 3, 2);

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


        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 3, 2);
        try                             {op0.columnAdjoint(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testColumnAdjoint_02()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 12;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(4, 8);
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


        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 6, 2);

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


        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 6, 2);
        try                             {op0.columnAdjoint(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testColumnAdjoint_03()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 12;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(4, 8);
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


        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 3, 5);

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


        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 3, 5);
        try                             {op0.columnAdjoint(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockSparseOperatorUnitTest::testColumnAdjoint_04()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 12;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(4, 8);
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


        TBlockSparseOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix), 6, 5);

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


        TBlockSparseOperator<klab::DoubleReal> op0(8, 12, 0, 6, 5);
        try                             {op0.columnAdjoint(0, out); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
