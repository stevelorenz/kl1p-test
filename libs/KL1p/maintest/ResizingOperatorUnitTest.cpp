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

#include "ResizingOperatorUnitTest.h"
#include "../include/ResizingOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KResizingOperatorUnitTest::KResizingOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KResizingOperatorUnitTest::testMNOpConstructor) 
    TEST_ADD(KResizingOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KResizingOperatorUnitTest::testOp)
    TEST_ADD(KResizingOperatorUnitTest::testApply)
    TEST_ADD(KResizingOperatorUnitTest::testApply_02)
    TEST_ADD(KResizingOperatorUnitTest::testApply_03)
    TEST_ADD(KResizingOperatorUnitTest::testApply_04)
    TEST_ADD(KResizingOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KResizingOperatorUnitTest::testApplyAdjoint_02)
    TEST_ADD(KResizingOperatorUnitTest::testApplyAdjoint_03)
    TEST_ADD(KResizingOperatorUnitTest::testApplyAdjoint_04)
    TEST_ADD(KResizingOperatorUnitTest::testColumn)
    TEST_ADD(KResizingOperatorUnitTest::testColumn_02)
    TEST_ADD(KResizingOperatorUnitTest::testColumn_03)
    TEST_ADD(KResizingOperatorUnitTest::testColumn_04)
    TEST_ADD(KResizingOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KResizingOperatorUnitTest::testColumnAdjoint_02)
    TEST_ADD(KResizingOperatorUnitTest::testColumnAdjoint_03)
    TEST_ADD(KResizingOperatorUnitTest::testColumnAdjoint_04)
}

// ---------------------------------------------------------------------------------------------------- //

KResizingOperatorUnitTest::~KResizingOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testMNOpConstructor()
{
    try
    {
        TResizingOperator<klab::DoubleReal> op(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)));
        TEST_ASSERT(op.m()==8 && op.n()==16)
        TEST_ASSERT(op.op()!=0 && op.op()->m()==4 && op.op()->n()==6)  

        // Limit cases.
        TResizingOperator<klab::DoubleReal> op0(8, 16, 0);
        TEST_ASSERT(op0.m()==8 && op0.n()==16)
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KResizingOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TResizingOperator<klab::DoubleReal> op(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)));
        TEST_ASSERT(op.m()==8 && op.n()==16)
        TEST_ASSERT(op.op()!=0 && op.op()->m()==4 && op.op()->n()==6)

        TResizingOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==8 && opCopy.n()==16)
        TEST_ASSERT(opCopy.op()!=0 && opCopy.op()==op.op() && opCopy.op()->m()==4 && opCopy.op()->n()==6)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testOp()
{
    try
    {
        TResizingOperator<klab::DoubleReal> op(8, 16, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)));
        TEST_ASSERT(op.m()==8 && op.n()==16)
        TEST_ASSERT(op.op()!=0 && op.op()->m()==4 && op.op()->n()==6)    
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testApply()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x8(8);
        arma::Col<klab::DoubleReal> x12(12);
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

        x8[0] = 1.0;
        x8[1] = 2.0;
        x8[2] = 3.0;
        x8[3] = 4.0;
        x8[4] = 5.0;
        x8[5] = 6.0;
        x8[6] = 7.0;
        x8[7] = 8.0;

        x12[0] = 1.0;
        x12[1] = 2.0;
        x12[2] = 3.0;
        x12[3] = 4.0;
        x12[4] = 5.0;
        x12[5] = 6.0;
        x12[6] = 7.0;
        x12[7] = 8.0;
        x12[8] = 9.0;
        x12[9] = 10.0;
        x12[10] = 11.0;
        x12[11] = 12.0;

        TResizingOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op.m()==8 && op.n()==12)
        op.apply(x12, y);
        TEST_ASSERT(y.n_rows == 8)        
        TEST_ASSERT(klab::Equals(y[0], 204.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 492.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 780.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 1068.0, precision))
        TEST_ASSERT(klab::Equals(y[4], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[7], 0.0, precision))


        TResizingOperator<klab::DoubleReal> op1(4, 8, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        op1.apply(x8, y);
        TEST_ASSERT(y.n_rows == 4)        
        TEST_ASSERT(klab::Equals(y[0], 204.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 492.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 780.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 1068.0, precision))

        TResizingOperator<klab::DoubleReal> op2(4, 12, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op2.m()==4 && op2.n()==12)
        op2.apply(x12, y);
        TEST_ASSERT(y.n_rows == 4)        
        TEST_ASSERT(klab::Equals(y[0], 204.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 492.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 780.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 1068.0, precision))

        TResizingOperator<klab::DoubleReal> op3(8, 8, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op3.m()==8 && op3.n()==8)
        op3.apply(x8, y);
        TEST_ASSERT(y.n_rows == 8)        
        TEST_ASSERT(klab::Equals(y[0], 204.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 492.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 780.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 1068.0, precision))
        TEST_ASSERT(klab::Equals(y[4], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[7], 0.0, precision))


        // Limit cases.     
        TResizingOperator<klab::DoubleReal> op01(4, 8, 0);
        try                             {op01.apply(x8, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        TResizingOperator<klab::DoubleReal> op02(8, 12, 0);
        try                             {op02.apply(x12, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testApply_02()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x6(6);
        arma::Col<klab::DoubleReal> x7(7);
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

        x6[0] = 1.0;
        x6[1] = 2.0;
        x6[2] = 3.0;
        x6[3] = 4.0;
        x6[4] = 5.0;
        x6[5] = 6.0;

        x7[0] = 1.0;
        x7[1] = 2.0;
        x7[2] = 3.0;
        x7[3] = 4.0;
        x7[4] = 5.0;
        x7[5] = 6.0;
        x7[6] = 7.0;


        TResizingOperator<klab::DoubleReal> op(8, 6, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op.m()==8 && op.n()==6)
        op.apply(x6, y);
        TEST_ASSERT(y.n_rows == 8)        
        TEST_ASSERT(klab::Equals(y[0], 91.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 259.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 427.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 595.0, precision))
        TEST_ASSERT(klab::Equals(y[4], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[7], 0.0, precision))


        TResizingOperator<klab::DoubleReal> op1(4, 6, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op1.m()==4 && op1.n()==6)
        op1.apply(x6, y);
        TEST_ASSERT(y.n_rows == 4)        
        TEST_ASSERT(klab::Equals(y[0], 91.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 259.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 427.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 595.0, precision))

        TResizingOperator<klab::DoubleReal> op2(4, 7, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op2.m()==4 && op2.n()==7)
        op2.apply(x7, y);
        TEST_ASSERT(y.n_rows == 4)        
        TEST_ASSERT(klab::Equals(y[0], 140.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 364.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 588.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 812.0, precision))

        TResizingOperator<klab::DoubleReal> op3(8, 7, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op3.m()==8 && op3.n()==7)
        op3.apply(x7, y);
        TEST_ASSERT(y.n_rows == 8)        
        TEST_ASSERT(klab::Equals(y[0], 140.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 364.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 588.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 812.0, precision))
        TEST_ASSERT(klab::Equals(y[4], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[5], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[6], 0.0, precision))
        TEST_ASSERT(klab::Equals(y[7], 0.0, precision))


        // Limit cases.     
        TResizingOperator<klab::DoubleReal> op01(4, 6, 0);
        try                             {op01.apply(x6, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        TResizingOperator<klab::DoubleReal> op02(8, 7, 0);
        try                             {op02.apply(x7, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testApply_03()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x8(8);
        arma::Col<klab::DoubleReal> x12(12);
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

        x8[0] = 1.0;
        x8[1] = 2.0;
        x8[2] = 3.0;
        x8[3] = 4.0;
        x8[4] = 5.0;
        x8[5] = 6.0;
        x8[6] = 7.0;
        x8[7] = 8.0;

        x12[0] = 1.0;
        x12[1] = 2.0;
        x12[2] = 3.0;
        x12[3] = 4.0;
        x12[4] = 5.0;
        x12[5] = 6.0;
        x12[6] = 7.0;
        x12[7] = 8.0;
        x12[8] = 9.0;
        x12[9] = 10.0;
        x12[10] = 11.0;
        x12[11] = 12.0;

        TResizingOperator<klab::DoubleReal> op(2, 12, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op.m()==2 && op.n()==12)
        op.apply(x12, y);
        TEST_ASSERT(y.n_rows == 2)        
        TEST_ASSERT(klab::Equals(y[0], 204.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 492.0, precision))


        TResizingOperator<klab::DoubleReal> op1(2, 8, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op1.m()==2 && op1.n()==8)
        op1.apply(x8, y);
        TEST_ASSERT(y.n_rows == 2)        
        TEST_ASSERT(klab::Equals(y[0], 204.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 492.0, precision))

        TResizingOperator<klab::DoubleReal> op2(3, 12, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op2.m()==3 && op2.n()==12)
        op2.apply(x12, y);
        TEST_ASSERT(y.n_rows == 3)        
        TEST_ASSERT(klab::Equals(y[0], 204.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 492.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 780.0, precision))

        TResizingOperator<klab::DoubleReal> op3(3, 8, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op3.m()==3 && op3.n()==8)
        op3.apply(x8, y);
        TEST_ASSERT(y.n_rows == 3)        
        TEST_ASSERT(klab::Equals(y[0], 204.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 492.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 780.0, precision))


        // Limit cases.     
        TResizingOperator<klab::DoubleReal> op01(2, 8, 0);
        try                             {op01.apply(x8, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        TResizingOperator<klab::DoubleReal> op02(3, 12, 0);
        try                             {op02.apply(x12, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testApply_04()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x6(6);
        arma::Col<klab::DoubleReal> x7(7);
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

        x6[0] = 1.0;
        x6[1] = 2.0;
        x6[2] = 3.0;
        x6[3] = 4.0;
        x6[4] = 5.0;
        x6[5] = 6.0;

        x7[0] = 1.0;
        x7[1] = 2.0;
        x7[2] = 3.0;
        x7[3] = 4.0;
        x7[4] = 5.0;
        x7[5] = 6.0;
        x7[6] = 7.0;


        TResizingOperator<klab::DoubleReal> op(2, 6, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op.m()==2 && op.n()==6)
        op.apply(x6, y);
        TEST_ASSERT(y.n_rows == 2)        
        TEST_ASSERT(klab::Equals(y[0], 91.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 259.0, precision))

        TResizingOperator<klab::DoubleReal> op1(2, 6, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op1.m()==2 && op1.n()==6)
        op1.apply(x6, y);
        TEST_ASSERT(y.n_rows == 2)        
        TEST_ASSERT(klab::Equals(y[0], 91.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 259.0, precision))

        TResizingOperator<klab::DoubleReal> op2(3, 7, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op2.m()==3 && op2.n()==7)
        op2.apply(x7, y);
        TEST_ASSERT(y.n_rows == 3)        
        TEST_ASSERT(klab::Equals(y[0], 140.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 364.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 588.0, precision))

        TResizingOperator<klab::DoubleReal> op3(3, 7, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op3.m()==3 && op3.n()==7)
        op3.apply(x7, y);
        TEST_ASSERT(y.n_rows == 3)        
        TEST_ASSERT(klab::Equals(y[0], 140.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 364.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 588.0, precision))


        // Limit cases.     
        TResizingOperator<klab::DoubleReal> op01(2, 6, 0);
        try                             {op01.apply(x6, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        TResizingOperator<klab::DoubleReal> op02(3, 7, 0);
        try                             {op02.apply(x7, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x8(8);
        arma::Col<klab::DoubleReal> x12(12);
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

        x8[0] = 1.0;
        x8[1] = 2.0;
        x8[2] = 3.0;
        x8[3] = 4.0;
        x8[4] = 5.0;
        x8[5] = 6.0;
        x8[6] = 7.0;
        x8[7] = 8.0;

        x12[0] = 1.0;
        x12[1] = 2.0;
        x12[2] = 3.0;
        x12[3] = 4.0;
        x12[4] = 5.0;
        x12[5] = 6.0;
        x12[6] = 7.0;
        x12[7] = 8.0;
        x12[8] = 9.0;
        x12[9] = 10.0;
        x12[10] = 11.0;
        x12[11] = 12.0;

        TResizingOperator<klab::DoubleReal> op(8, 12, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op.m()==8 && op.n()==12)
        op.apply(x12, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 12)        
        TEST_ASSERT(klab::Equals(xr[0], 44592.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 47136.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 49680.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 52224.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 54768.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 57312.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 59856.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 62400.0, precision))
        TEST_ASSERT(klab::Equals(xr[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[9], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[10], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[11], 0.0, precision))

        TResizingOperator<klab::DoubleReal> op1(4, 8, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        op1.apply(x8, y);
        op1.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)        
        TEST_ASSERT(klab::Equals(xr[0], 44592.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 47136.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 49680.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 52224.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 54768.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 57312.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 59856.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 62400.0, precision))

        TResizingOperator<klab::DoubleReal> op2(4, 12, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op2.m()==4 && op2.n()==12)
        op2.apply(x12, y);
        op2.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 12)        
        TEST_ASSERT(klab::Equals(xr[0], 44592.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 47136.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 49680.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 52224.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 54768.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 57312.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 59856.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 62400.0, precision))
        TEST_ASSERT(klab::Equals(xr[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[9], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[10], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[11], 0.0, precision))

        TResizingOperator<klab::DoubleReal> op3(8, 8, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op3.m()==8 && op3.n()==8)
        op3.apply(x8, y);
        op3.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)        
        TEST_ASSERT(klab::Equals(xr[0], 44592.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 47136.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 49680.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 52224.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 54768.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 57312.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 59856.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 62400.0, precision))


        // Limit cases.     
        TResizingOperator<klab::DoubleReal> op01(4, 8, 0);
        try                             {op01.applyAdjoint(arma::Col<klab::DoubleReal>(4), xr); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        TResizingOperator<klab::DoubleReal> op02(8, 12, 0);
        try                             {op02.applyAdjoint(arma::Col<klab::DoubleReal>(8), xr); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testApplyAdjoint_02()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x6(6);
        arma::Col<klab::DoubleReal> x7(7);
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

        x6[0] = 1.0;
        x6[1] = 2.0;
        x6[2] = 3.0;
        x6[3] = 4.0;
        x6[4] = 5.0;
        x6[5] = 6.0;

        x7[0] = 1.0;
        x7[1] = 2.0;
        x7[2] = 3.0;
        x7[3] = 4.0;
        x7[4] = 5.0;
        x7[5] = 6.0;
        x7[6] = 7.0;


        TResizingOperator<klab::DoubleReal> op(8, 6, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op.m()==8 && op.n()==6)
        op.apply(x6, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 6)        
        TEST_ASSERT(klab::Equals(xr[0], 24556.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 25928.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 27300.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 28672.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 30044.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 31416.0, precision))

        TResizingOperator<klab::DoubleReal> op1(4, 6, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op1.m()==4 && op1.n()==6)
        op1.apply(x6, y);
        op1.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 6)        
        TEST_ASSERT(klab::Equals(xr[0], 24556.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 25928.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 27300.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 28672.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 30044.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 31416.0, precision))

        TResizingOperator<klab::DoubleReal> op2(4, 7, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op2.m()==4 && op2.n()==7)
        op2.apply(x7, y);
        op2.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 7)        
        TEST_ASSERT(klab::Equals(xr[0], 33712.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 35616.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 37520.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 39424.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 41328.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 43232.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 45136.0, precision))

        TResizingOperator<klab::DoubleReal> op3(8, 7, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op3.m()==8 && op3.n()==7)
        op3.apply(x7, y);
        op3.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 7)        
        TEST_ASSERT(klab::Equals(xr[0], 33712.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 35616.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 37520.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 39424.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 41328.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 43232.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 45136.0, precision))


        // Limit cases.     
        TResizingOperator<klab::DoubleReal> op01(4, 6, 0);
        try                             {op01.applyAdjoint(arma::Col<klab::DoubleReal>(4), y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        TResizingOperator<klab::DoubleReal> op02(8, 7, 0);
        try                             {op02.applyAdjoint(arma::Col<klab::DoubleReal>(8), y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testApplyAdjoint_03()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x8(8);
        arma::Col<klab::DoubleReal> x12(12);
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

        x8[0] = 1.0;
        x8[1] = 2.0;
        x8[2] = 3.0;
        x8[3] = 4.0;
        x8[4] = 5.0;
        x8[5] = 6.0;
        x8[6] = 7.0;
        x8[7] = 8.0;

        x12[0] = 1.0;
        x12[1] = 2.0;
        x12[2] = 3.0;
        x12[3] = 4.0;
        x12[4] = 5.0;
        x12[5] = 6.0;
        x12[6] = 7.0;
        x12[7] = 8.0;
        x12[8] = 9.0;
        x12[9] = 10.0;
        x12[10] = 11.0;
        x12[11] = 12.0;

        TResizingOperator<klab::DoubleReal> op(2, 12, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op.m()==2 && op.n()==12)
        op.apply(x12, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 12)        
        TEST_ASSERT(klab::Equals(xr[0], 4632.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 5328.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 6024.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 6720.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 7416.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 8112.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 8808.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 9504.0, precision))
        TEST_ASSERT(klab::Equals(xr[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[9], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[10], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[11], 0.0, precision))

        TResizingOperator<klab::DoubleReal> op1(2, 8, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op1.m()==2 && op1.n()==8)
        op1.apply(x8, y);
        op1.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)        
        TEST_ASSERT(klab::Equals(xr[0], 4632.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 5328.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 6024.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 6720.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 7416.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 8112.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 8808.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 9504.0, precision))

        TResizingOperator<klab::DoubleReal> op2(3, 12, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op2.m()==3 && op2.n()==12)
        op2.apply(x12, y);
        op2.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 12)        
        TEST_ASSERT(klab::Equals(xr[0], 17892.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 19368.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 20844.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 22320.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 23796.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 25272.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 26748.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 28224.0, precision))
        TEST_ASSERT(klab::Equals(xr[8], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[9], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[10], 0.0, precision))
        TEST_ASSERT(klab::Equals(xr[11], 0.0, precision))

        TResizingOperator<klab::DoubleReal> op3(3, 8, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op3.m()==3 && op3.n()==8)
        op3.apply(x8, y);
        op3.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)        
        TEST_ASSERT(klab::Equals(xr[0], 17892.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 19368.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 20844.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 22320.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 23796.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 25272.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 26748.0, precision))
        TEST_ASSERT(klab::Equals(xr[7], 28224.0, precision))


        // Limit cases.     
        TResizingOperator<klab::DoubleReal> op01(2, 8, 0);
        try                             {op01.applyAdjoint(arma::Col<klab::DoubleReal>(2), xr); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        TResizingOperator<klab::DoubleReal> op02(3, 12, 0);
        try                             {op02.applyAdjoint(arma::Col<klab::DoubleReal>(3), xr); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testApplyAdjoint_04()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix(m, n);
        arma::Col<klab::DoubleReal> x6(6);
        arma::Col<klab::DoubleReal> x7(7);
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

        x6[0] = 1.0;
        x6[1] = 2.0;
        x6[2] = 3.0;
        x6[3] = 4.0;
        x6[4] = 5.0;
        x6[5] = 6.0;

        x7[0] = 1.0;
        x7[1] = 2.0;
        x7[2] = 3.0;
        x7[3] = 4.0;
        x7[4] = 5.0;
        x7[5] = 6.0;
        x7[6] = 7.0;


        TResizingOperator<klab::DoubleReal> op(2, 6, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op.m()==2 && op.n()==6)
        op.apply(x6, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 6) 
        TEST_ASSERT(klab::Equals(xr[0], 2422.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 2772.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 3122.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 3472.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 3822.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 4172.0, precision))               

        TResizingOperator<klab::DoubleReal> op1(3, 6, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op1.m()==3 && op1.n()==6)
        op1.apply(x6, y);
        op1.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 6)  
        TEST_ASSERT(klab::Equals(xr[0], 9681.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 10458.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 11235.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 12012.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 12789.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 13566.0, precision))

        TResizingOperator<klab::DoubleReal> op2(2, 7, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op2.m()==2 && op2.n()==7)
        op2.apply(x7, y);
        op2.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 7)        
        TEST_ASSERT(klab::Equals(xr[0], 3416.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 3920.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 4424.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 4928.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 5432.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 5936.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 6440.0, precision))

        TResizingOperator<klab::DoubleReal> op3(3, 7, new TMatrixOperator<klab::DoubleReal>(matrix));
        TEST_ASSERT(op3.m()==3 && op3.n()==7)
        op3.apply(x7, y);
        op3.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 7)        
        TEST_ASSERT(klab::Equals(xr[0], 13412.0, precision))
        TEST_ASSERT(klab::Equals(xr[1], 14504.0, precision))
        TEST_ASSERT(klab::Equals(xr[2], 15596.0, precision))
        TEST_ASSERT(klab::Equals(xr[3], 16688.0, precision))
        TEST_ASSERT(klab::Equals(xr[4], 17780.0, precision))
        TEST_ASSERT(klab::Equals(xr[5], 18872.0, precision))
        TEST_ASSERT(klab::Equals(xr[6], 19964.0, precision))


        // Limit cases.     
        TResizingOperator<klab::DoubleReal> op01(2, 6, 0);
        try                             {op01.applyAdjoint(arma::Col<klab::DoubleReal>(2), y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        TResizingOperator<klab::DoubleReal> op02(3, 7, 0);
        try                             {op02.applyAdjoint(arma::Col<klab::DoubleReal>(3), y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KResizingOperatorUnitTest::testColumn()
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


        TResizingOperator<klab::DoubleReal> op(m, n, new TMatrixOperator<klab::DoubleReal>(matrix));

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

        TResizingOperator<klab::DoubleReal> op0(m, n, 0);
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

void KResizingOperatorUnitTest::testColumn_02()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 6;
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


        TResizingOperator<klab::DoubleReal> op(m, n, new TMatrixOperator<klab::DoubleReal>(matrix));

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

        TResizingOperator<klab::DoubleReal> op0(m, n, 0);
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

void KResizingOperatorUnitTest::testColumn_03()
{
    try
    {
        klab::UInt32 m = 2;
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


        TResizingOperator<klab::DoubleReal> op(m, n, new TMatrixOperator<klab::DoubleReal>(matrix));

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

        TResizingOperator<klab::DoubleReal> op0(m, n, 0);
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

void KResizingOperatorUnitTest::testColumn_04()
{
    try
    {
        klab::UInt32 m = 2;
        klab::UInt32 n = 6;
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


        TResizingOperator<klab::DoubleReal> op(m, n, new TMatrixOperator<klab::DoubleReal>(matrix));

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

        TResizingOperator<klab::DoubleReal> op0(m, n, 0);
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

void KResizingOperatorUnitTest::testColumnAdjoint()
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


        TResizingOperator<klab::DoubleReal> op(m, n, new TMatrixOperator<klab::DoubleReal>(matrix));

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


        TResizingOperator<klab::DoubleReal> op0(m, n, 0);
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

void KResizingOperatorUnitTest::testColumnAdjoint_02()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 6;
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


        TResizingOperator<klab::DoubleReal> op(m, n, new TMatrixOperator<klab::DoubleReal>(matrix));

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


        TResizingOperator<klab::DoubleReal> op0(m, n, 0);
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

void KResizingOperatorUnitTest::testColumnAdjoint_03()
{
    try
    {
        klab::UInt32 m = 2;
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


        TResizingOperator<klab::DoubleReal> op(m, n, new TMatrixOperator<klab::DoubleReal>(matrix));

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


        TResizingOperator<klab::DoubleReal> op0(m, n, 0);
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

void KResizingOperatorUnitTest::testColumnAdjoint_04()
{
    try
    {
        klab::UInt32 m = 2;
        klab::UInt32 n = 6;
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


        TResizingOperator<klab::DoubleReal> op(m, n, new TMatrixOperator<klab::DoubleReal>(matrix));

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


        TResizingOperator<klab::DoubleReal> op0(m, n, 0);
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
