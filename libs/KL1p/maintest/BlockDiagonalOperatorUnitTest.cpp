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

#include "BlockDiagonalOperatorUnitTest.h"
#include "../include/BlockDiagonalOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KBlockDiagonalOperatorUnitTest::KBlockDiagonalOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testOpConstructor) 
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testOp1Op2Constructor) 
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testOp1Op2Op3Constructor)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testOperatorArrayConstructor)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KBlockDiagonalOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testBlock)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testInBlock)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testApply)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testColumn)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testApplyBlockVariance)
    TEST_ADD(KBlockDiagonalOperatorUnitTest::testApplyBlockVarianceAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KBlockDiagonalOperatorUnitTest::~KBlockDiagonalOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testOpConstructor()
{
    try
    {
        TBlockDiagonalOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  


        // Limit cases.
        TBlockDiagonalOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testOp1Op2Constructor()
{
    try
    {
        TBlockDiagonalOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==8 && op.n()==16)
        TEST_ASSERT(op.countBlockRows()==2 && op.countBlockColumns()==2)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op.block(1, 1)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op2(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 12)));
        TEST_ASSERT(op2.m()==8 && op2.n()==20)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==2)
        TEST_ASSERT(op2.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op2.block(1, 1)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op3(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12)));
        TEST_ASSERT(op3.m()==10 && op3.n()==20)
        TEST_ASSERT(op3.countBlockRows()==2 && op3.countBlockColumns()==2)
        TEST_ASSERT(op3.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op3.block(1, 1)->isZero()==false)


        // Limit cases.
        TBlockDiagonalOperator<klab::DoubleReal> op0(0, 0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TBlockDiagonalOperator<klab::DoubleReal> op01(0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op01.m()==4 && op01.n()==8)
        TEST_ASSERT(op01.countBlockRows()==1 && op01.countBlockColumns()==1)
        TEST_ASSERT(op01.block(0, 0)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op10(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0);
        TEST_ASSERT(op10.m()==4 && op10.n()==8)
        TEST_ASSERT(op10.countBlockRows()==1 && op10.countBlockColumns()==1)
        TEST_ASSERT(op10.block(0, 0)->isZero()==false) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testOp1Op2Op3Constructor()
{
    try
    {
        TBlockDiagonalOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==12 && op.n()==24)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==3)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op.block(1, 1)->isZero()==false) 
        TEST_ASSERT(op.block(2, 2)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op2(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 12)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 3)));
        TEST_ASSERT(op2.m()==12 && op2.n()==23)
        TEST_ASSERT(op2.countBlockRows()==3 && op2.countBlockColumns()==3)
        TEST_ASSERT(op2.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op2.block(1, 1)->isZero()==false) 
        TEST_ASSERT(op2.block(2, 2)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op3(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TEST_ASSERT(op3.m()==15 && op3.n()==26)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==3)
        TEST_ASSERT(op3.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op3.block(1, 1)->isZero()==false)
        TEST_ASSERT(op3.block(2, 2)->isZero()==false)


        // Limit cases.
        TBlockDiagonalOperator<klab::DoubleReal> op000(0, 0, 0);
        TEST_ASSERT(op000.m()==0 && op000.n()==0)
        TEST_ASSERT(op000.countBlockRows()==0 && op000.countBlockColumns()==0)

        TBlockDiagonalOperator<klab::DoubleReal> op001(0, 0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op001.m()==4 && op001.n()==8)
        TEST_ASSERT(op001.countBlockRows()==1 && op001.countBlockColumns()==1)
        TEST_ASSERT(op001.block(0, 0)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op010(0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0);
        TEST_ASSERT(op010.m()==4 && op010.n()==8)
        TEST_ASSERT(op010.countBlockRows()==1 && op010.countBlockColumns()==1)
        TEST_ASSERT(op010.block(0, 0)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op011(0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TEST_ASSERT(op011.m()==9 && op011.n()==14)
        TEST_ASSERT(op011.countBlockRows()==2 && op011.countBlockColumns()==2)
        TEST_ASSERT(op011.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op011.block(1, 1)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op100(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0, 0);
        TEST_ASSERT(op100.m()==4 && op100.n()==8)
        TEST_ASSERT(op100.countBlockRows()==1 && op100.countBlockColumns()==1)
        TEST_ASSERT(op100.block(0, 0)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op101(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TEST_ASSERT(op101.m()==9 && op101.n()==14)
        TEST_ASSERT(op101.countBlockRows()==2 && op101.countBlockColumns()==2)
        TEST_ASSERT(op101.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op101.block(1, 1)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal> op110(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)), 0);
        TEST_ASSERT(op110.m()==9 && op110.n()==14)
        TEST_ASSERT(op110.countBlockRows()==2 && op110.countBlockColumns()==2)
        TEST_ASSERT(op110.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op110.block(1, 1)->isZero()==false) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KBlockDiagonalOperatorUnitTest::testOperatorArrayConstructor()
{
    try
    {
        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators1;
        operators1.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators1.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators1.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TBlockDiagonalOperator<klab::DoubleReal> op(operators1);
        TEST_ASSERT(op.m()==12 && op.n()==24)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==3)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op.block(1, 1)->isZero()==false) 
        TEST_ASSERT(op.block(2, 2)->isZero()==false)

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators2;
        operators2.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators2.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 12)));
        operators2.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 3)));
        TBlockDiagonalOperator<klab::DoubleReal> op2(operators2);
        TEST_ASSERT(op2.m()==12 && op2.n()==23)
        TEST_ASSERT(op2.countBlockRows()==3 && op2.countBlockColumns()==3)
        TEST_ASSERT(op2.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op2.block(1, 1)->isZero()==false) 
        TEST_ASSERT(op2.block(2, 2)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators3;
        operators3.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators3.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12))); 
        operators3.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TBlockDiagonalOperator<klab::DoubleReal> op3(operators3);
        TEST_ASSERT(op3.m()==15 && op3.n()==26)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==3)
        TEST_ASSERT(op3.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op3.block(1, 1)->isZero()==false)
        TEST_ASSERT(op3.block(2, 2)->isZero()==false)


        // Limit cases.
        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators0;
        TBlockDiagonalOperator<klab::DoubleReal> op0(operators0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators000;
        operators000.push_back(0);
        operators000.push_back(0);
        operators000.push_back(0);
        TBlockDiagonalOperator<klab::DoubleReal> op000(operators000);
        TEST_ASSERT(op000.m()==0 && op000.n()==0)
        TEST_ASSERT(op000.countBlockRows()==0 && op000.countBlockColumns()==0)

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators001;
        operators001.push_back(0);
        operators001.push_back(0);
        operators001.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TBlockDiagonalOperator<klab::DoubleReal> op001(operators001);
        TEST_ASSERT(op001.m()==4 && op001.n()==8)
        TEST_ASSERT(op001.countBlockRows()==1 && op001.countBlockColumns()==1)
        TEST_ASSERT(op001.block(0, 0)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators010;
        operators010.push_back(0);
        operators010.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators010.push_back(0);
        TBlockDiagonalOperator<klab::DoubleReal> op010(operators010);
        TEST_ASSERT(op010.m()==4 && op010.n()==8)
        TEST_ASSERT(op010.countBlockRows()==1 && op010.countBlockColumns()==1)
        TEST_ASSERT(op010.block(0, 0)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators011;
        operators011.push_back(0);
        operators011.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators011.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TBlockDiagonalOperator<klab::DoubleReal> op011(operators011);
        TEST_ASSERT(op011.m()==9 && op011.n()==14)
        TEST_ASSERT(op011.countBlockRows()==2 && op011.countBlockColumns()==2)
        TEST_ASSERT(op011.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op011.block(1, 1)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators100;
        operators100.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators100.push_back(0);
        operators100.push_back(0);
        TBlockDiagonalOperator<klab::DoubleReal> op100(operators100);
        TEST_ASSERT(op100.m()==4 && op100.n()==8)
        TEST_ASSERT(op100.countBlockRows()==1 && op100.countBlockColumns()==1)
        TEST_ASSERT(op100.block(0, 0)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators101;
        operators101.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators101.push_back(0);
        operators101.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TBlockDiagonalOperator<klab::DoubleReal> op101(operators101);
        TEST_ASSERT(op101.m()==9 && op101.n()==14)
        TEST_ASSERT(op101.countBlockRows()==2 && op101.countBlockColumns()==2)
        TEST_ASSERT(op101.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op101.block(1, 1)->isZero()==false) 

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators110;
        operators110.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators110.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        operators110.push_back(0);
        TBlockDiagonalOperator<klab::DoubleReal> op110(operators110);
        TEST_ASSERT(op110.m()==9 && op110.n()==14)
        TEST_ASSERT(op110.countBlockRows()==2 && op110.countBlockColumns()==2)
        TEST_ASSERT(op110.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op110.block(1, 1)->isZero()==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KBlockDiagonalOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12))); 
        operators.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TBlockDiagonalOperator<klab::DoubleReal> op(operators);
        TEST_ASSERT(op.m()==15 && op.n()==26)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==3)
        TEST_ASSERT(op.block(0, 0) == operators[0])  
        TEST_ASSERT(op.block(1, 1) == operators[1])
        TEST_ASSERT(op.block(2, 2) == operators[2])

        TBlockDiagonalOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==15 && opCopy.n()==26)
        TEST_ASSERT(opCopy.countBlockRows()==3 && opCopy.countBlockColumns()==3)
        TEST_ASSERT(opCopy.block(0, 0) == operators[0])  
        TEST_ASSERT(opCopy.block(1, 1) == operators[1])
        TEST_ASSERT(opCopy.block(2, 2) == operators[2])
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testCountBlockRows()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TBlockDiagonalOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TBlockDiagonalOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)

        TBlockDiagonalOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==9 && op2.n()==17)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==2)

        TBlockDiagonalOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==15 && op3.n()==27)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==3)

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TBlockDiagonalOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==22 && op4.n()==38)
        TEST_ASSERT(op4.countBlockRows()==4 && op4.countBlockColumns()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TBlockDiagonalOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TBlockDiagonalOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)

        TBlockDiagonalOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==9 && op2.n()==17)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==2)

        TBlockDiagonalOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==15 && op3.n()==27)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==3)

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TBlockDiagonalOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==22 && op4.n()==38)
        TEST_ASSERT(op4.countBlockRows()==4 && op4.countBlockColumns()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testBlock()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TBlockDiagonalOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TBlockDiagonalOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)
        TEST_ASSERT(op1.block(0, 0) == operator1)  

        TBlockDiagonalOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==9 && op2.n()==17)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==2)
        TEST_ASSERT(op2.block(0, 0) == operator1)  
        TEST_ASSERT(op2.block(0, 1)->isZero())  
        TEST_ASSERT(op2.block(1, 0)->isZero())  
        TEST_ASSERT(op2.block(1, 1) == operator2)  

        TBlockDiagonalOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==15 && op3.n()==27)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==3)
        TEST_ASSERT(op3.block(0, 0) == operator1)  
        TEST_ASSERT(op3.block(0, 1)->isZero())  
        TEST_ASSERT(op3.block(0, 2)->isZero())  
        TEST_ASSERT(op3.block(1, 0)->isZero()) 
        TEST_ASSERT(op3.block(1, 1) == operator2)
        TEST_ASSERT(op3.block(1, 2)->isZero())
        TEST_ASSERT(op3.block(2, 0)->isZero()) 
        TEST_ASSERT(op3.block(2, 1)->isZero()) 
        TEST_ASSERT(op3.block(2, 2) == operator3)

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TBlockDiagonalOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==22 && op4.n()==38)
        TEST_ASSERT(op4.countBlockRows()==4 && op4.countBlockColumns()==4)
        TEST_ASSERT(op4.block(0, 0) == operator1)  
        TEST_ASSERT(op4.block(0, 1)->isZero())  
        TEST_ASSERT(op4.block(0, 2)->isZero())
        TEST_ASSERT(op4.block(0, 3)->isZero())
        TEST_ASSERT(op4.block(1, 0)->isZero())
        TEST_ASSERT(op4.block(1, 1) == operator2)
        TEST_ASSERT(op4.block(1, 2)->isZero())
        TEST_ASSERT(op4.block(1, 3)->isZero())
        TEST_ASSERT(op4.block(2, 0)->isZero())
        TEST_ASSERT(op4.block(2, 1)->isZero())
        TEST_ASSERT(op4.block(2, 2) == operator3)
        TEST_ASSERT(op4.block(2, 3)->isZero())
        TEST_ASSERT(op4.block(3, 0)->isZero())
        TEST_ASSERT(op4.block(3, 1)->isZero())
        TEST_ASSERT(op4.block(3, 2)->isZero())
        TEST_ASSERT(op4.block(3, 3) == operator4)


        // Limit cases.
        try                                     {op0.block(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.block(1, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.block(2, 2); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.block(3, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.block(4, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TBlockDiagonalOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TBlockDiagonalOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)
        TEST_ASSERT(op1.isZeroBlock(0, 0) == false)  

        TBlockDiagonalOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==9 && op2.n()==17)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==2)
        TEST_ASSERT(op2.isZeroBlock(0, 0) == false)  
        TEST_ASSERT(op2.isZeroBlock(0, 1))  
        TEST_ASSERT(op2.isZeroBlock(1, 0))  
        TEST_ASSERT(op2.isZeroBlock(1, 1) == false)  

        TBlockDiagonalOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==15 && op3.n()==27)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==3)
        TEST_ASSERT(op3.isZeroBlock(0, 0) == false)  
        TEST_ASSERT(op3.isZeroBlock(0, 1))  
        TEST_ASSERT(op3.isZeroBlock(0, 2))  
        TEST_ASSERT(op3.isZeroBlock(1, 0)) 
        TEST_ASSERT(op3.isZeroBlock(1, 1) == false)
        TEST_ASSERT(op3.isZeroBlock(1, 2))
        TEST_ASSERT(op3.isZeroBlock(2, 0)) 
        TEST_ASSERT(op3.isZeroBlock(2, 1)) 
        TEST_ASSERT(op3.isZeroBlock(2, 2) == false)

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TBlockDiagonalOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==22 && op4.n()==38)
        TEST_ASSERT(op4.countBlockRows()==4 && op4.countBlockColumns()==4)
        TEST_ASSERT(op4.isZeroBlock(0, 0) == false)  
        TEST_ASSERT(op4.isZeroBlock(0, 1))  
        TEST_ASSERT(op4.isZeroBlock(0, 2))
        TEST_ASSERT(op4.isZeroBlock(0, 3))
        TEST_ASSERT(op4.isZeroBlock(1, 0))
        TEST_ASSERT(op4.isZeroBlock(1, 1) == false)
        TEST_ASSERT(op4.isZeroBlock(1, 2))
        TEST_ASSERT(op4.isZeroBlock(1, 3))
        TEST_ASSERT(op4.isZeroBlock(2, 0))
        TEST_ASSERT(op4.isZeroBlock(2, 1))
        TEST_ASSERT(op4.isZeroBlock(2, 2) == false)
        TEST_ASSERT(op4.isZeroBlock(2, 3))
        TEST_ASSERT(op4.isZeroBlock(3, 0))
        TEST_ASSERT(op4.isZeroBlock(3, 1))
        TEST_ASSERT(op4.isZeroBlock(3, 2))
        TEST_ASSERT(op4.isZeroBlock(3, 3) == false)


        // Limit cases.
        try                                     {op0.isZeroBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.isZeroBlock(1, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.isZeroBlock(2, 2); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.isZeroBlock(3, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.isZeroBlock(4, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testInBlock()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TBlockDiagonalOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TBlockDiagonalOperator<klab::DoubleReal> op(operators);
        TEST_ASSERT(op.m()==22 && op.n()==38)
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.inBlock(0, 0) == operator1)
        TEST_ASSERT(op.inBlock(0, 1) == operator1)
        TEST_ASSERT(op.inBlock(1, 0) == operator1)
        TEST_ASSERT(op.inBlock(1, 1) == operator1)
        TEST_ASSERT(op.inBlock(3, 7) == operator1)
        TEST_ASSERT(op.inBlock(4, 8) == operator2)
        TEST_ASSERT(op.inBlock(9, 17) == operator3)
        TEST_ASSERT(op.inBlock(15, 27) == operator4)
        TEST_ASSERT(op.inBlock(21, 37) == operator4)
        TEST_ASSERT(op.inBlock(4, 0)->isZero())
        TEST_ASSERT(op.inBlock(9, 9)->isZero())
        TEST_ASSERT(op.inBlock(0, 8)->isZero())
        TEST_ASSERT(op.inBlock(4, 18)->isZero())


        // Limit cases.
        try                                     {op.inBlock(0, 38); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(22, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(22, 38); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        TBlockDiagonalOperator<klab::DoubleReal> op0(0);
        try                                     {op0.inBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> matrix1(3, 2);
        arma::Mat<klab::DoubleReal> matrix2(2, 5);
        arma::Mat<klab::DoubleReal> matrix3(2, 1);
        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(1, 0) = 3.0;
        matrix1(1, 1) = 4.0;
        matrix1(2, 0) = 5.0;
        matrix1(2, 1) = 6.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;        
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;  

        matrix3(0, 0) = -5.0;
        matrix3(1, 0) =  5.0;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;


        TBlockDiagonalOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 7)
        TEST_ASSERT(klab::Equals(y[0],  5.0, precision))
        TEST_ASSERT(klab::Equals(y[1],  11.0, precision))
        TEST_ASSERT(klab::Equals(y[2],  17.0, precision))
        TEST_ASSERT(klab::Equals(y[3],  74.0, precision))
        TEST_ASSERT(klab::Equals(y[4],  54.0, precision))
        TEST_ASSERT(klab::Equals(y[5], -40.0, precision))
        TEST_ASSERT(klab::Equals(y[6],  40.0, precision))


        // Limit cases.
        TBlockDiagonalOperator<klab::DoubleReal> op0(0);
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

void KBlockDiagonalOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> matrix1(3, 2);
        arma::Mat<klab::DoubleReal> matrix2(2, 5);
        arma::Mat<klab::DoubleReal> matrix3(2, 1);
        arma::Col<klab::DoubleReal> x(7);
        arma::Col<klab::DoubleReal> y;

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(1, 0) = 3.0;
        matrix1(1, 1) = 4.0;
        matrix1(2, 0) = 5.0;
        matrix1(2, 1) = 6.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;        
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;  

        matrix3(0, 0) = -5.0;
        matrix3(1, 0) =  5.0;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;


        TBlockDiagonalOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==8)

        op.applyAdjoint(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 22.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 28.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 24.8, precision))
        TEST_ASSERT(klab::Equals(y[3], 23.9, precision))
        TEST_ASSERT(klab::Equals(y[4], 23.0, precision))
        TEST_ASSERT(klab::Equals(y[5], 22.1, precision))
        TEST_ASSERT(klab::Equals(y[6], 21.2, precision))
        TEST_ASSERT(klab::Equals(y[7],  5.0, precision))


        // Limit cases.
        TBlockDiagonalOperator<klab::DoubleReal> op0(0);
        try                             {op0.applyAdjoint(x, y); TEST_ASSERT(false)}
        catch(KNullOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 7;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix1(3, 2);
        arma::Mat<klab::DoubleReal> matrix2(2, 5);
        arma::Mat<klab::DoubleReal> matrix3(2, 1);

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(1, 0) = 3.0;
        matrix1(1, 1) = 4.0;
        matrix1(2, 0) = 5.0;
        matrix1(2, 1) = 6.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;        
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;  

        matrix3(0, 0) = -5.0;
        matrix3(1, 0) =  5.0;


        TBlockDiagonalOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==8)

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


        TBlockDiagonalOperator<klab::DoubleReal> op0(0);
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

void KBlockDiagonalOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 7;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix1(3, 2);
        arma::Mat<klab::DoubleReal> matrix2(2, 5);
        arma::Mat<klab::DoubleReal> matrix3(2, 1);

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(1, 0) = 3.0;
        matrix1(1, 1) = 4.0;
        matrix1(2, 0) = 5.0;
        matrix1(2, 1) = 6.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;        
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;  

        matrix3(0, 0) = -5.0;
        matrix3(1, 0) =  5.0;


        TBlockDiagonalOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==8)

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


        TBlockDiagonalOperator<klab::DoubleReal> op0(0, 0);
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

void KBlockDiagonalOperatorUnitTest::testApplyBlockVariance()
{
    try
    {
        klab::UInt32 m = 3;
        klab::UInt32 n = 3;
        klab::DoubleReal precision = 1e-12; 

        arma::Col<klab::DoubleReal> x(3);
        arma::Col<klab::DoubleReal> y;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;

        arma::Mat<klab::DoubleReal> matrix1(3, 2);
        arma::Mat<klab::DoubleReal> matrix2(2, 5);
        arma::Mat<klab::DoubleReal> matrix3(2, 1);

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(1, 0) = 3.0;
        matrix1(1, 1) = 4.0;
        matrix1(2, 0) = 5.0;
        matrix1(2, 1) = 6.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;        
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;  

        matrix3(0, 0) = -5.0;
        matrix3(1, 0) =  5.0;


        TBlockDiagonalOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==3)

        op.applyBlockVariance(x, y);
        TEST_ASSERT(y.n_rows==3)
        TEST_ASSERT(klab::Equals(y[0], x[0]*op.block(0, 0)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[1], x[1]*op.block(1, 1)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[2], x[2]*op.block(2, 2)->variance(), precision))
        

        // Limit cases.
        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(2), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(4), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockDiagonalOperatorUnitTest::testApplyBlockVarianceAdjoint()
{
    try
    {
        klab::UInt32 m = 3;
        klab::UInt32 n = 3;
        klab::DoubleReal precision = 1e-12; 

        arma::Col<klab::DoubleReal> x(3);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;

        arma::Mat<klab::DoubleReal> matrix1(3, 2);
        arma::Mat<klab::DoubleReal> matrix2(2, 5);
        arma::Mat<klab::DoubleReal> matrix3(2, 1);

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(1, 0) = 3.0;
        matrix1(1, 1) = 4.0;
        matrix1(2, 0) = 5.0;
        matrix1(2, 1) = 6.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;        
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;  

        matrix3(0, 0) = -5.0;
        matrix3(1, 0) =  5.0;


        TBlockDiagonalOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==3)

        op.applyBlockVariance(x, y);
        op.applyBlockVarianceAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows==3)
        TEST_ASSERT(klab::Equals(xr[0], y[0]*op.block(0, 0)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[1], y[1]*op.block(1, 1)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[2], y[2]*op.block(2, 2)->variance(), precision))
        

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
