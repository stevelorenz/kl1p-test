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

#include "ColumnJointOperatorUnitTest.h"
#include "../include/ColumnJointOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KColumnJointOperatorUnitTest::KColumnJointOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KColumnJointOperatorUnitTest::testOpConstructor) 
    TEST_ADD(KColumnJointOperatorUnitTest::testOp1Op2Constructor) 
    TEST_ADD(KColumnJointOperatorUnitTest::testOp1Op2Op3Constructor)
    TEST_ADD(KColumnJointOperatorUnitTest::testOperatorArrayConstructor)
    TEST_ADD(KColumnJointOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KColumnJointOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KColumnJointOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KColumnJointOperatorUnitTest::testBlock)
    TEST_ADD(KColumnJointOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KColumnJointOperatorUnitTest::testInBlock)
    TEST_ADD(KColumnJointOperatorUnitTest::testApply)
    TEST_ADD(KColumnJointOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KColumnJointOperatorUnitTest::testColumn)
    TEST_ADD(KColumnJointOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KColumnJointOperatorUnitTest::testApplyBlockVariance)
    TEST_ADD(KColumnJointOperatorUnitTest::testApplyBlockVarianceAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KColumnJointOperatorUnitTest::~KColumnJointOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KColumnJointOperatorUnitTest::testOpConstructor()
{
    try
    {
        TColumnJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  


        // Limit cases.
        TColumnJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KColumnJointOperatorUnitTest::testOp1Op2Constructor()
{
    try
    {
        TColumnJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==8 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==2 && op.countBlockColumns()==1)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op.block(1, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op2(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 8)));
        TEST_ASSERT(op2.m()==10 && op2.n()==8)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==1)
        TEST_ASSERT(op2.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op2.block(1, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op3(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12)));
        TEST_ASSERT(op3.m()==10 && op3.n()==12)
        TEST_ASSERT(op3.countBlockRows()==2 && op3.countBlockColumns()==1)
        TEST_ASSERT(op3.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op3.block(1, 0)->isZero()==false)


        // Limit cases.
        TColumnJointOperator<klab::DoubleReal> op0(0, 0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TColumnJointOperator<klab::DoubleReal> op01(0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op01.m()==4 && op01.n()==8)
        TEST_ASSERT(op01.countBlockRows()==1 && op01.countBlockColumns()==1)
        TEST_ASSERT(op01.block(0, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op10(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0);
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

void KColumnJointOperatorUnitTest::testOp1Op2Op3Constructor()
{
    try
    {
        TColumnJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==12 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==1)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op.block(1, 0)->isZero()==false) 
        TEST_ASSERT(op.block(2, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op2(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 12)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 3)));
        TEST_ASSERT(op2.m()==12 && op2.n()==12)
        TEST_ASSERT(op2.countBlockRows()==3 && op2.countBlockColumns()==1)
        TEST_ASSERT(op2.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op2.block(1, 0)->isZero()==false) 
        TEST_ASSERT(op2.block(2, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op3(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TEST_ASSERT(op3.m()==15 && op3.n()==12)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==1)
        TEST_ASSERT(op3.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op3.block(1, 0)->isZero()==false)
        TEST_ASSERT(op3.block(2, 0)->isZero()==false)


        // Limit cases.
        TColumnJointOperator<klab::DoubleReal> op000(0, 0, 0);
        TEST_ASSERT(op000.m()==0 && op000.n()==0)
        TEST_ASSERT(op000.countBlockRows()==0 && op000.countBlockColumns()==0)

        TColumnJointOperator<klab::DoubleReal> op001(0, 0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op001.m()==4 && op001.n()==8)
        TEST_ASSERT(op001.countBlockRows()==1 && op001.countBlockColumns()==1)
        TEST_ASSERT(op001.block(0, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op010(0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0);
        TEST_ASSERT(op010.m()==4 && op010.n()==8)
        TEST_ASSERT(op010.countBlockRows()==1 && op010.countBlockColumns()==1)
        TEST_ASSERT(op010.block(0, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op011(0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TEST_ASSERT(op011.m()==9 && op011.n()==8)
        TEST_ASSERT(op011.countBlockRows()==2 && op011.countBlockColumns()==1)
        TEST_ASSERT(op011.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op011.block(1, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op100(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0, 0);
        TEST_ASSERT(op100.m()==4 && op100.n()==8)
        TEST_ASSERT(op100.countBlockRows()==1 && op100.countBlockColumns()==1)
        TEST_ASSERT(op100.block(0, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op101(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TEST_ASSERT(op101.m()==9 && op101.n()==8)
        TEST_ASSERT(op101.countBlockRows()==2 && op101.countBlockColumns()==1)
        TEST_ASSERT(op101.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op101.block(1, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal> op110(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)), 0);
        TEST_ASSERT(op110.m()==9 && op110.n()==8)
        TEST_ASSERT(op110.countBlockRows()==2 && op110.countBlockColumns()==1)
        TEST_ASSERT(op110.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op110.block(1, 0)->isZero()==false) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KColumnJointOperatorUnitTest::testOperatorArrayConstructor()
{
    try
    {
        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators1;
        operators1.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators1.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators1.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TColumnJointOperator<klab::DoubleReal> op(operators1);
        TEST_ASSERT(op.m()==12 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==1)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op.block(1, 0)->isZero()==false) 
        TEST_ASSERT(op.block(2, 0)->isZero()==false)

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators2;
        operators2.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators2.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 12)));
        operators2.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 3)));
        TColumnJointOperator<klab::DoubleReal> op2(operators2);
        TEST_ASSERT(op2.m()==12 && op2.n()==12)
        TEST_ASSERT(op2.countBlockRows()==3 && op2.countBlockColumns()==1)
        TEST_ASSERT(op2.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op2.block(1, 0)->isZero()==false) 
        TEST_ASSERT(op2.block(2, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators3;
        operators3.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators3.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12))); 
        operators3.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TColumnJointOperator<klab::DoubleReal> op3(operators3);
        TEST_ASSERT(op3.m()==15 && op3.n()==12)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==1)
        TEST_ASSERT(op3.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op3.block(1, 0)->isZero()==false)
        TEST_ASSERT(op3.block(2, 0)->isZero()==false)


        // Limit cases.
        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators0;
        TColumnJointOperator<klab::DoubleReal> op0(operators0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators000;
        operators000.push_back(0);
        operators000.push_back(0);
        operators000.push_back(0);
        TColumnJointOperator<klab::DoubleReal> op000(operators000);
        TEST_ASSERT(op000.m()==0 && op000.n()==0)
        TEST_ASSERT(op000.countBlockRows()==0 && op000.countBlockColumns()==0)

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators001;
        operators001.push_back(0);
        operators001.push_back(0);
        operators001.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TColumnJointOperator<klab::DoubleReal> op001(operators001);
        TEST_ASSERT(op001.m()==4 && op001.n()==8)
        TEST_ASSERT(op001.countBlockRows()==1 && op001.countBlockColumns()==1)
        TEST_ASSERT(op001.block(0, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators010;
        operators010.push_back(0);
        operators010.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators010.push_back(0);
        TColumnJointOperator<klab::DoubleReal> op010(operators010);
        TEST_ASSERT(op010.m()==4 && op010.n()==8)
        TEST_ASSERT(op010.countBlockRows()==1 && op010.countBlockColumns()==1)
        TEST_ASSERT(op010.block(0, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators011;
        operators011.push_back(0);
        operators011.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators011.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TColumnJointOperator<klab::DoubleReal> op011(operators011);
        TEST_ASSERT(op011.m()==9 && op011.n()==8)
        TEST_ASSERT(op011.countBlockRows()==2 && op011.countBlockColumns()==1)
        TEST_ASSERT(op011.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op011.block(1, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators100;
        operators100.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators100.push_back(0);
        operators100.push_back(0);
        TColumnJointOperator<klab::DoubleReal> op100(operators100);
        TEST_ASSERT(op100.m()==4 && op100.n()==8)
        TEST_ASSERT(op100.countBlockRows()==1 && op100.countBlockColumns()==1)
        TEST_ASSERT(op100.block(0, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators101;
        operators101.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators101.push_back(0);
        operators101.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TColumnJointOperator<klab::DoubleReal> op101(operators101);
        TEST_ASSERT(op101.m()==9 && op101.n()==8)
        TEST_ASSERT(op101.countBlockRows()==2 && op101.countBlockColumns()==1)
        TEST_ASSERT(op101.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op101.block(1, 0)->isZero()==false) 

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators110;
        operators110.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators110.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        operators110.push_back(0);
        TColumnJointOperator<klab::DoubleReal> op110(operators110);
        TEST_ASSERT(op110.m()==9 && op110.n()==8)
        TEST_ASSERT(op110.countBlockRows()==2 && op110.countBlockColumns()==1)
        TEST_ASSERT(op110.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op110.block(1, 0)->isZero()==false) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KColumnJointOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 12)));
        operators.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12))); 
        operators.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 12)));
        TColumnJointOperator<klab::DoubleReal> op(operators);
        TEST_ASSERT(op.m()==15 && op.n()==12)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==1)
        TEST_ASSERT(op.block(0, 0) == operators[0])  
        TEST_ASSERT(op.block(1, 0) == operators[1])
        TEST_ASSERT(op.block(2, 0) == operators[2])

        TColumnJointOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==15 && opCopy.n()==12)
        TEST_ASSERT(opCopy.countBlockRows()==3 && opCopy.countBlockColumns()==1)
        TEST_ASSERT(opCopy.block(0, 0) == operators[0])  
        TEST_ASSERT(opCopy.block(1, 0) == operators[1])
        TEST_ASSERT(opCopy.block(2, 0) == operators[2])
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KColumnJointOperatorUnitTest::testCountBlockRows()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TColumnJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TColumnJointOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)

        TColumnJointOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==9 && op2.n()==9)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==1)

        TColumnJointOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==15 && op3.n()==10)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==1)

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TColumnJointOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==22 && op4.n()==11)
        TEST_ASSERT(op4.countBlockRows()==4 && op4.countBlockColumns()==1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KColumnJointOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TColumnJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TColumnJointOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)

        TColumnJointOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==9 && op2.n()==9)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==1)

        TColumnJointOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==15 && op3.n()==10)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==1)

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TColumnJointOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==22 && op4.n()==11)
        TEST_ASSERT(op4.countBlockRows()==4 && op4.countBlockColumns()==1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KColumnJointOperatorUnitTest::testBlock()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 11));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 11));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 11));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TColumnJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TColumnJointOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==11)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)
        TEST_ASSERT(op1.block(0, 0) == operator1)  

        TColumnJointOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==9 && op2.n()==11)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==1)
        TEST_ASSERT(op2.block(0, 0) == operator1)  
        TEST_ASSERT(op2.block(1, 0) == operator2)  

        TColumnJointOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==15 && op3.n()==11)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==1)
        TEST_ASSERT(op3.block(0, 0) == operator1)  
        TEST_ASSERT(op3.block(1, 0) == operator2)
        TEST_ASSERT(op3.block(2, 0) == operator3)

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TColumnJointOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==22 && op4.n()==11)
        TEST_ASSERT(op4.countBlockRows()==4 && op4.countBlockColumns()==1)
        TEST_ASSERT(op4.block(0, 0) == operator1)  
        TEST_ASSERT(op4.block(1, 0) == operator2)
        TEST_ASSERT(op4.block(2, 0) == operator3)
        TEST_ASSERT(op4.block(3, 0) == operator4)


        // Limit cases.
        try                                     {op0.block(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.block(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.block(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.block(2, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.block(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.block(3, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.block(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.block(4, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.block(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KColumnJointOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TColumnJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TColumnJointOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)
        TEST_ASSERT(op1.isZeroBlock(0, 0) == false)  

        TColumnJointOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==9 && op2.n()==9)
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==1)
        TEST_ASSERT(op2.isZeroBlock(0, 0) == false)  
        TEST_ASSERT(op2.isZeroBlock(1, 0) == false)  

        TColumnJointOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==15 && op3.n()==10)
        TEST_ASSERT(op3.countBlockRows()==3 && op3.countBlockColumns()==1)
        TEST_ASSERT(op3.isZeroBlock(0, 0) == false)  
        TEST_ASSERT(op3.isZeroBlock(1, 0) == false)
        TEST_ASSERT(op3.isZeroBlock(2, 0) == false)

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TColumnJointOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==22 && op4.n()==11)
        TEST_ASSERT(op4.countBlockRows()==4 && op4.countBlockColumns()==1)
        TEST_ASSERT(op4.isZeroBlock(0, 0) == false)  
        TEST_ASSERT(op4.isZeroBlock(1, 0) == false)
        TEST_ASSERT(op4.isZeroBlock(2, 0) == false)
        TEST_ASSERT(op4.isZeroBlock(3, 0) == false)


        // Limit cases.
        try                                     {op0.isZeroBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.isZeroBlock(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.isZeroBlock(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.isZeroBlock(2, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.isZeroBlock(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.isZeroBlock(3, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.isZeroBlock(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.isZeroBlock(4, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.isZeroBlock(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KColumnJointOperatorUnitTest::testInBlock()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 11));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 11));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 11));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TColumnJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TColumnJointOperator<klab::DoubleReal> op(operators);
        TEST_ASSERT(op.m()==22 && op.n()==11)
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==1)
        TEST_ASSERT(op.inBlock(0, 0) == operator1)
        TEST_ASSERT(op.inBlock(1, 0) == operator1)
        TEST_ASSERT(op.inBlock(2, 0) == operator1)
        TEST_ASSERT(op.inBlock(3, 0) == operator1)
        TEST_ASSERT(op.inBlock(4, 2) == operator2)
        TEST_ASSERT(op.inBlock(9, 2) == operator3)
        TEST_ASSERT(op.inBlock(15, 2) == operator4)
        TEST_ASSERT(op.inBlock(21, 2) == operator4)


        // Limit cases.
        try                                     {op.inBlock(0, 11); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(22, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(22, 11); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        TColumnJointOperator<klab::DoubleReal> op0(0);
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

void KColumnJointOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> matrix1(3, 2);
        arma::Mat<klab::DoubleReal> matrix2(2, 5);
        arma::Mat<klab::DoubleReal> matrix3(2, 1);
        arma::Col<klab::DoubleReal> x(5);
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


        TColumnJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==5)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 7)
        TEST_ASSERT(klab::Equals(y[0],  5.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 11.0, precision))
        TEST_ASSERT(klab::Equals(y[2], 17.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 44.0, precision))
        TEST_ASSERT(klab::Equals(y[4], 32.0, precision))
        TEST_ASSERT(klab::Equals(y[5], -5.0, precision))
        TEST_ASSERT(klab::Equals(y[6],  5.0, precision))


        // Limit cases.
        TColumnJointOperator<klab::DoubleReal> op0(0);
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

void KColumnJointOperatorUnitTest::testApplyAdjoint()
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


        TColumnJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==5)

        op.applyAdjoint(x, y);
        TEST_ASSERT(y.n_rows == 5)
        TEST_ASSERT(klab::Equals(y[0], 51.8, precision))
        TEST_ASSERT(klab::Equals(y[1], 51.9, precision))
        TEST_ASSERT(klab::Equals(y[2], 23.0, precision))
        TEST_ASSERT(klab::Equals(y[3], 22.1, precision))
        TEST_ASSERT(klab::Equals(y[4], 21.2, precision))


        // Limit cases.
        TColumnJointOperator<klab::DoubleReal> op0(0);
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

void KColumnJointOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 7;
        klab::UInt32 n = 5;
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


        TColumnJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==5)

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


        TColumnJointOperator<klab::DoubleReal> op0(0);
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

void KColumnJointOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 7;
        klab::UInt32 n = 5;
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


        TColumnJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==5)

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


        TColumnJointOperator<klab::DoubleReal> op0(0, 0);
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

void KColumnJointOperatorUnitTest::testApplyBlockVariance()
{
    try
    {
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

        arma::Col<klab::DoubleReal> x(1);
        arma::Col<klab::DoubleReal> y;
        x[0] = 2.0;


        TColumnJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==5)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==1)

        op.applyBlockVariance(x, y);
        TEST_ASSERT(y.n_rows==3)
        TEST_ASSERT(klab::Equals(y[0], x[0]*op.block(0, 0)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[1], x[0]*op.block(1, 0)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[2], x[0]*op.block(2, 0)->variance(), precision))
        

        // Limit cases.
        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(2), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KColumnJointOperatorUnitTest::testApplyBlockVarianceAdjoint()
{
    try
    {
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

        arma::Col<klab::DoubleReal> x(1);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        x[0] = 2.0;


        TColumnJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==7 && op.n()==5)
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==1)

        op.applyBlockVariance(x, y);
        op.applyBlockVarianceAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows==1)
        TEST_ASSERT(klab::Equals(xr[0], y[0]*op.block(0, 0)->variance() + y[1]*op.block(1, 0)->variance() + y[2]*op.block(2, 0)->variance(), precision))
        

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
