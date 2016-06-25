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

#include "ProxyBlockOperatorUnitTest.h"
#include "../include/BlockDiagonalOperator.h"
#include "../include/MatrixOperator.h"
#include "BlockOperatorUnitTest.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KProxyBlockOperatorUnitTest::KProxyBlockOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KProxyBlockOperatorUnitTest::testOpConstructor)  
    TEST_ADD(KProxyBlockOperatorUnitTest::testNOpConstructor)  
    TEST_ADD(KProxyBlockOperatorUnitTest::testMNOpConstructor)  
    TEST_ADD(KProxyBlockOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KProxyBlockOperatorUnitTest::testOp)
    TEST_ADD(KProxyBlockOperatorUnitTest::testIsZero)    
    TEST_ADD(KProxyBlockOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KProxyBlockOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KProxyBlockOperatorUnitTest::testBlock)
    TEST_ADD(KProxyBlockOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KProxyBlockOperatorUnitTest::testInBlock)
    TEST_ADD(KProxyBlockOperatorUnitTest::testApplyBlockVariance)
    TEST_ADD(KProxyBlockOperatorUnitTest::testApplyBlockVarianceAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KProxyBlockOperatorUnitTest::~KProxyBlockOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testOpConstructor()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testNOpConstructor()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(16, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==16)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
  
void KProxyBlockOperatorUnitTest::testMNOpConstructor()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, 32, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
  
void KProxyBlockOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, 32, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))

        TTestProxyBlockOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==16 && opCopy.n()==32)
        TEST_ASSERT(opCopy.countBlockRows()==1 && opCopy.countBlockColumns()==1)
        TEST_ASSERT(opCopy.op() != 0)
        TEST_ASSERT(opCopy.isZero() == false)
        TEST_ASSERT(opCopy.block(0, 0)!=0 && opCopy.block(0, 0)->isZero()==false && opCopy.block(0, 0)->m()==4 && opCopy.block(0, 0)->n()==8)
        TEST_ASSERT(opCopy.isZeroBlock(0, 0) == false)
        TEST_ASSERT(opCopy.inBlock(1, 1) == opCopy.block(0, 0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testOp()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, 32, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testIsZero() 
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, 32, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
   
void KProxyBlockOperatorUnitTest::testCountBlockRows()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, 32, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, 32, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testBlock()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, 32, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, 32, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testInBlock()
{
    try
    {
        TTestProxyBlockOperator<klab::DoubleReal> op(16, 32, new TBlockDiagonalOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8))));
        TEST_ASSERT(op.m()==16 && op.n()==32)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==8)
        TEST_ASSERT(op.isZeroBlock(0, 0) == false)
        TEST_ASSERT(op.inBlock(1, 1) == op.block(0, 0))


        // Limit cases.
        TTestProxyBlockOperator<klab::DoubleReal> op0(16, 32, 0);
        TEST_ASSERT(op0.m()==16 && op0.n()==32)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testApplyBlockVariance()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Col<klab::DoubleReal> x(4);
        arma::Col<klab::DoubleReal> y;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;


        TTestProxyBlockOperator<klab::DoubleReal> op(new TTestBlockOperator<klab::DoubleReal>());
        TEST_ASSERT(op.m()==12 && op.n()==18)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)

        op.applyBlockVariance(x, y);
        TEST_ASSERT(y.n_rows==3)
        TEST_ASSERT(klab::Equals(y[0], x[0]*op.block(0, 0)->variance() + x[1]*op.block(0, 1)->variance() + x[2]*op.block(0, 2)->variance() + x[3]*op.block(0, 3)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[1], x[0]*op.block(1, 0)->variance() + x[1]*op.block(1, 1)->variance() + x[2]*op.block(1, 2)->variance() + x[3]*op.block(1, 3)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[2], x[0]*op.block(2, 0)->variance() + x[1]*op.block(2, 1)->variance() + x[2]*op.block(2, 2)->variance() + x[3]*op.block(2, 3)->variance(), precision))
        

        // Limit cases.
        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(3), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(5), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KProxyBlockOperatorUnitTest::testApplyBlockVarianceAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-9; 

        arma::Col<klab::DoubleReal> x(4);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;


        TTestProxyBlockOperator<klab::DoubleReal> op(new TTestBlockOperator<klab::DoubleReal>());
        TEST_ASSERT(op.m()==12 && op.n()==18)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)

        op.applyBlockVariance(x, y);
        op.applyBlockVarianceAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows==4)
        TEST_ASSERT(klab::Equals(xr[0], y[0]*op.block(0, 0)->variance() + y[1]*op.block(1, 0)->variance() + y[2]*op.block(2, 0)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[1], y[0]*op.block(0, 1)->variance() + y[1]*op.block(1, 1)->variance() + y[2]*op.block(2, 1)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[2], y[0]*op.block(0, 2)->variance() + y[1]*op.block(1, 2)->variance() + y[2]*op.block(2, 2)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[3], y[0]*op.block(0, 3)->variance() + y[1]*op.block(1, 3)->variance() + y[2]*op.block(2, 3)->variance(), precision))
        

        // Limit cases.
        try                                         {op.applyBlockVarianceAdjoint(arma::Col<klab::DoubleReal>(2), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyBlockVarianceAdjoint(arma::Col<klab::DoubleReal>(4), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
