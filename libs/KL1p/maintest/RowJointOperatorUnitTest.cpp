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

#include "RowJointOperatorUnitTest.h"
#include "../include/RowJointOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KRowJointOperatorUnitTest::KRowJointOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KRowJointOperatorUnitTest::testOpConstructor) 
    TEST_ADD(KRowJointOperatorUnitTest::testOp1Op2Constructor) 
    TEST_ADD(KRowJointOperatorUnitTest::testOp1Op2Op3Constructor)
    TEST_ADD(KRowJointOperatorUnitTest::testOperatorArrayConstructor)
    TEST_ADD(KRowJointOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KRowJointOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KRowJointOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KRowJointOperatorUnitTest::testBlock)
    TEST_ADD(KRowJointOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KRowJointOperatorUnitTest::testInBlock)
    TEST_ADD(KRowJointOperatorUnitTest::testApply)
    TEST_ADD(KRowJointOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KRowJointOperatorUnitTest::testColumn)
    TEST_ADD(KRowJointOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KRowJointOperatorUnitTest::testApplyBlockVariance)
    TEST_ADD(KRowJointOperatorUnitTest::testApplyBlockVarianceAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KRowJointOperatorUnitTest::~KRowJointOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRowJointOperatorUnitTest::testOpConstructor()
{
    try
    {
        TRowJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  


        // Limit cases.
        TRowJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRowJointOperatorUnitTest::testOp1Op2Constructor()
{
    try
    {
        TRowJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==4 && op.n()==16)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==2)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op.block(0, 1)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op2(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 8)));
        TEST_ASSERT(op2.m()==6 && op2.n()==16)
        TEST_ASSERT(op2.countBlockRows()==1 && op2.countBlockColumns()==2)
        TEST_ASSERT(op2.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op2.block(0, 1)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op3(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12)));
        TEST_ASSERT(op3.m()==6 && op3.n()==20)
        TEST_ASSERT(op3.countBlockRows()==1 && op3.countBlockColumns()==2)
        TEST_ASSERT(op3.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op3.block(0, 1)->isZero()==false)


        // Limit cases.
        TRowJointOperator<klab::DoubleReal> op0(0, 0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TRowJointOperator<klab::DoubleReal> op01(0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op01.m()==4 && op01.n()==8)
        TEST_ASSERT(op01.countBlockRows()==1 && op01.countBlockColumns()==1)
        TEST_ASSERT(op01.block(0, 0)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op10(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0);
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

void KRowJointOperatorUnitTest::testOp1Op2Op3Constructor()
{
    try
    {
        TRowJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op.m()==4 && op.n()==24)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==3)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op.block(0, 1)->isZero()==false) 
        TEST_ASSERT(op.block(0, 2)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op2(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 12)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 3)));
        TEST_ASSERT(op2.m()==4 && op2.n()==23)
        TEST_ASSERT(op2.countBlockRows()==1 && op2.countBlockColumns()==3)
        TEST_ASSERT(op2.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op2.block(0, 1)->isZero()==false) 
        TEST_ASSERT(op2.block(0, 2)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op3(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TEST_ASSERT(op3.m()==6 && op3.n()==26)
        TEST_ASSERT(op3.countBlockRows()==1 && op3.countBlockColumns()==3)
        TEST_ASSERT(op3.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op3.block(0, 1)->isZero()==false)
        TEST_ASSERT(op3.block(0, 2)->isZero()==false)


        // Limit cases.
        TRowJointOperator<klab::DoubleReal> op000(0, 0, 0);
        TEST_ASSERT(op000.m()==0 && op000.n()==0)
        TEST_ASSERT(op000.countBlockRows()==0 && op000.countBlockColumns()==0)

        TRowJointOperator<klab::DoubleReal> op001(0, 0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TEST_ASSERT(op001.m()==4 && op001.n()==8)
        TEST_ASSERT(op001.countBlockRows()==1 && op001.countBlockColumns()==1)
        TEST_ASSERT(op001.block(0, 0)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op010(0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0);
        TEST_ASSERT(op010.m()==4 && op010.n()==8)
        TEST_ASSERT(op010.countBlockRows()==1 && op010.countBlockColumns()==1)
        TEST_ASSERT(op010.block(0, 0)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op011(0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TEST_ASSERT(op011.m()==5 && op011.n()==14)
        TEST_ASSERT(op011.countBlockRows()==1 && op011.countBlockColumns()==2)
        TEST_ASSERT(op011.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op011.block(0, 1)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op100(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0, 0);
        TEST_ASSERT(op100.m()==4 && op100.n()==8)
        TEST_ASSERT(op100.countBlockRows()==1 && op100.countBlockColumns()==1)
        TEST_ASSERT(op100.block(0, 0)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op101(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), 0, new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TEST_ASSERT(op101.m()==5 && op101.n()==14)
        TEST_ASSERT(op101.countBlockRows()==1 && op101.countBlockColumns()==2)
        TEST_ASSERT(op101.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op101.block(0, 1)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal> op110(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)), 0);
        TEST_ASSERT(op110.m()==5 && op110.n()==14)
        TEST_ASSERT(op110.countBlockRows()==1 && op110.countBlockColumns()==2)
        TEST_ASSERT(op110.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op110.block(0, 1)->isZero()==false) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KRowJointOperatorUnitTest::testOperatorArrayConstructor()
{
    try
    {
        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators1;
        operators1.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators1.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators1.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TRowJointOperator<klab::DoubleReal> op(operators1);
        TEST_ASSERT(op.m()==4 && op.n()==24)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==3)
        TEST_ASSERT(op.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op.block(0, 1)->isZero()==false) 
        TEST_ASSERT(op.block(0, 2)->isZero()==false)

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators2;
        operators2.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators2.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 12)));
        operators2.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 3)));
        TRowJointOperator<klab::DoubleReal> op2(operators2);
        TEST_ASSERT(op2.m()==4 && op2.n()==23)
        TEST_ASSERT(op2.countBlockRows()==1 && op2.countBlockColumns()==3)
        TEST_ASSERT(op2.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op2.block(0, 1)->isZero()==false) 
        TEST_ASSERT(op2.block(0, 2)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators3;
        operators3.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators3.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 12))); 
        operators3.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TRowJointOperator<klab::DoubleReal> op3(operators3);
        TEST_ASSERT(op3.m()==6 && op3.n()==26)
        TEST_ASSERT(op3.countBlockRows()==1 && op3.countBlockColumns()==3)
        TEST_ASSERT(op3.block(0, 0)->isZero()==false)  
        TEST_ASSERT(op3.block(0, 1)->isZero()==false)
        TEST_ASSERT(op3.block(0, 2)->isZero()==false)


        // Limit cases.
        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators0;
        TRowJointOperator<klab::DoubleReal> op0(operators0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators000;
        operators000.push_back(0);
        operators000.push_back(0);
        operators000.push_back(0);
        TRowJointOperator<klab::DoubleReal> op000(operators000);
        TEST_ASSERT(op000.m()==0 && op000.n()==0)
        TEST_ASSERT(op000.countBlockRows()==0 && op000.countBlockColumns()==0)

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators001;
        operators001.push_back(0);
        operators001.push_back(0);
        operators001.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        TRowJointOperator<klab::DoubleReal> op001(operators001);
        TEST_ASSERT(op001.m()==4 && op001.n()==8)
        TEST_ASSERT(op001.countBlockRows()==1 && op001.countBlockColumns()==1)
        TEST_ASSERT(op001.block(0, 0)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators010;
        operators010.push_back(0);
        operators010.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators010.push_back(0);
        TRowJointOperator<klab::DoubleReal> op010(operators010);
        TEST_ASSERT(op010.m()==4 && op010.n()==8)
        TEST_ASSERT(op010.countBlockRows()==1 && op010.countBlockColumns()==1)
        TEST_ASSERT(op010.block(0, 0)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators011;
        operators011.push_back(0);
        operators011.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators011.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TRowJointOperator<klab::DoubleReal> op011(operators011);
        TEST_ASSERT(op011.m()==5 && op011.n()==14)
        TEST_ASSERT(op011.countBlockRows()==1 && op011.countBlockColumns()==2)
        TEST_ASSERT(op011.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op011.block(0, 1)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators100;
        operators100.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators100.push_back(0);
        operators100.push_back(0);
        TRowJointOperator<klab::DoubleReal> op100(operators100);
        TEST_ASSERT(op100.m()==4 && op100.n()==8)
        TEST_ASSERT(op100.countBlockRows()==1 && op100.countBlockColumns()==1)
        TEST_ASSERT(op100.block(0, 0)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators101;
        operators101.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators101.push_back(0);
        operators101.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        TRowJointOperator<klab::DoubleReal> op101(operators101);
        TEST_ASSERT(op101.m()==5 && op101.n()==14)
        TEST_ASSERT(op101.countBlockRows()==1 && op101.countBlockColumns()==2)
        TEST_ASSERT(op101.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op101.block(0, 1)->isZero()==false) 

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators110;
        operators110.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators110.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 6)));
        operators110.push_back(0);
        TRowJointOperator<klab::DoubleReal> op110(operators110);
        TEST_ASSERT(op110.m()==5 && op110.n()==14)
        TEST_ASSERT(op110.countBlockRows()==1 && op110.countBlockColumns()==2)
        TEST_ASSERT(op110.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op110.block(0, 1)->isZero()==false) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KRowJointOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
        operators.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 12))); 
        operators.push_back(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 6)));
        TRowJointOperator<klab::DoubleReal> op(operators);
        TEST_ASSERT(op.m()==4 && op.n()==26)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==3)
        TEST_ASSERT(op.block(0, 0) == operators[0])  
        TEST_ASSERT(op.block(0, 1) == operators[1])
        TEST_ASSERT(op.block(0, 2) == operators[2])

        TRowJointOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==4 && opCopy.n()==26)
        TEST_ASSERT(opCopy.countBlockRows()==1 && opCopy.countBlockColumns()==3)
        TEST_ASSERT(opCopy.block(0, 0) == operators[0])  
        TEST_ASSERT(opCopy.block(0, 1) == operators[1])
        TEST_ASSERT(opCopy.block(0, 2) == operators[2])
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRowJointOperatorUnitTest::testCountBlockRows()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TRowJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TRowJointOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)

        TRowJointOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==5 && op2.n()==17)
        TEST_ASSERT(op2.countBlockRows()==1 && op2.countBlockColumns()==2)

        TRowJointOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==6 && op3.n()==27)
        TEST_ASSERT(op3.countBlockRows()==1 && op3.countBlockColumns()==3)

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TRowJointOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==7 && op4.n()==38)
        TEST_ASSERT(op4.countBlockRows()==1 && op4.countBlockColumns()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRowJointOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TRowJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TRowJointOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)

        TRowJointOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==5 && op2.n()==17)
        TEST_ASSERT(op2.countBlockRows()==1 && op2.countBlockColumns()==2)

        TRowJointOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==6 && op3.n()==27)
        TEST_ASSERT(op3.countBlockRows()==1 && op3.countBlockColumns()==3)

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TRowJointOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==7 && op4.n()==38)
        TEST_ASSERT(op4.countBlockRows()==1 && op4.countBlockColumns()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRowJointOperatorUnitTest::testBlock()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 11));

        TRowJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TRowJointOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)
        TEST_ASSERT(op1.block(0, 0) == operator1)  

        TRowJointOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==4 && op2.n()==17)
        TEST_ASSERT(op2.countBlockRows()==1 && op2.countBlockColumns()==2)
        TEST_ASSERT(op2.block(0, 0) == operator1)  
        TEST_ASSERT(op2.block(0, 1) == operator2)  

        TRowJointOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==4 && op3.n()==27)
        TEST_ASSERT(op3.countBlockRows()==1 && op3.countBlockColumns()==3)
        TEST_ASSERT(op3.block(0, 0) == operator1)  
        TEST_ASSERT(op3.block(0, 1) == operator2)
        TEST_ASSERT(op3.block(0, 2) == operator3)

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TRowJointOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==4 && op4.n()==38)
        TEST_ASSERT(op4.countBlockRows()==1 && op4.countBlockColumns()==4)
        TEST_ASSERT(op4.block(0, 0) == operator1)  
        TEST_ASSERT(op4.block(0, 1) == operator2)
        TEST_ASSERT(op4.block(0, 2) == operator3)
        TEST_ASSERT(op4.block(0, 3) == operator4)


        // Limit cases.
        try                                     {op0.block(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.block(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.block(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.block(0, 2); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.block(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.block(0, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.block(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.block(0, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.block(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRowJointOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(5, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(6, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(7, 11));

        TRowJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)

        TRowJointOperator<klab::DoubleReal> op1(operator1);
        TEST_ASSERT(op1.m()==4 && op1.n()==8)
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)
        TEST_ASSERT(op1.isZeroBlock(0, 0) == false)  

        TRowJointOperator<klab::DoubleReal> op2(operator1, operator2);
        TEST_ASSERT(op2.m()==5 && op2.n()==17)
        TEST_ASSERT(op2.countBlockRows()==1 && op2.countBlockColumns()==2)
        TEST_ASSERT(op2.isZeroBlock(0, 0) == false)  
        TEST_ASSERT(op2.isZeroBlock(0, 1) == false)  

        TRowJointOperator<klab::DoubleReal> op3(operator1, operator2, operator3);
        TEST_ASSERT(op3.m()==6 && op3.n()==27)
        TEST_ASSERT(op3.countBlockRows()==1 && op3.countBlockColumns()==3)
        TEST_ASSERT(op3.isZeroBlock(0, 0) == false)  
        TEST_ASSERT(op3.isZeroBlock(0, 1) == false)
        TEST_ASSERT(op3.isZeroBlock(0, 2) == false)

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TRowJointOperator<klab::DoubleReal> op4(operators);
        TEST_ASSERT(op4.m()==7 && op4.n()==38)
        TEST_ASSERT(op4.countBlockRows()==1 && op4.countBlockColumns()==4)
        TEST_ASSERT(op4.isZeroBlock(0, 0) == false)  
        TEST_ASSERT(op4.isZeroBlock(0, 1) == false)
        TEST_ASSERT(op4.isZeroBlock(0, 2) == false)
        TEST_ASSERT(op4.isZeroBlock(0, 3) == false)


        // Limit cases.
        try                                     {op0.isZeroBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.isZeroBlock(0, 1); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op1.isZeroBlock(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.isZeroBlock(0, 2); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op2.isZeroBlock(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.isZeroBlock(0, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op3.isZeroBlock(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.isZeroBlock(0, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op4.isZeroBlock(1, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRowJointOperatorUnitTest::testInBlock()
{
    try
    {
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator1 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator2 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 9));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator3 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 10));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > operator4 = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 11));

        TRowJointOperator<klab::DoubleReal>::TOperatorArray operators;
        operators.push_back(operator1);
        operators.push_back(operator2); 
        operators.push_back(operator3);
        operators.push_back(operator4);
        TRowJointOperator<klab::DoubleReal> op(operators);
        TEST_ASSERT(op.m()==4 && op.n()==38)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==4)
        TEST_ASSERT(op.inBlock(0, 0) == operator1)
        TEST_ASSERT(op.inBlock(0, 1) == operator1)
        TEST_ASSERT(op.inBlock(0, 2) == operator1)
        TEST_ASSERT(op.inBlock(0, 3) == operator1)
        TEST_ASSERT(op.inBlock(2, 8) == operator2)
        TEST_ASSERT(op.inBlock(2, 17) == operator3)
        TEST_ASSERT(op.inBlock(2, 27) == operator4)
        TEST_ASSERT(op.inBlock(2, 37) == operator4)


        // Limit cases.
        try                                     {op.inBlock(0, 38); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(7, 0); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(7, 38); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        TRowJointOperator<klab::DoubleReal> op0(0);
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

void KRowJointOperatorUnitTest::testApply()
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


        TRowJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==3 && op.n()==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 3)
        TEST_ASSERT(klab::Equals(y[0],  39.0, precision))
        TEST_ASSERT(klab::Equals(y[1],  105.0, precision))
        TEST_ASSERT(klab::Equals(y[2],  17.0, precision))


        // Limit cases.
        TRowJointOperator<klab::DoubleReal> op0(0);
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

void KRowJointOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> matrix1(3, 2);
        arma::Mat<klab::DoubleReal> matrix2(2, 5);
        arma::Mat<klab::DoubleReal> matrix3(2, 1);
        arma::Col<klab::DoubleReal> x(3);
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


        TRowJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==3 && op.n()==8)

        op.applyAdjoint(x, y);
        TEST_ASSERT(y.n_rows == 8)
        TEST_ASSERT(klab::Equals(y[0], 22.0, precision))
        TEST_ASSERT(klab::Equals(y[1], 28.0, precision))
        TEST_ASSERT(klab::Equals(y[2],  8.0, precision))
        TEST_ASSERT(klab::Equals(y[3],  7.7, precision))
        TEST_ASSERT(klab::Equals(y[4],  7.4, precision))
        TEST_ASSERT(klab::Equals(y[5],  7.1, precision))
        TEST_ASSERT(klab::Equals(y[6],  6.8, precision))
        TEST_ASSERT(klab::Equals(y[7],  5.0, precision))


        // Limit cases.
        TRowJointOperator<klab::DoubleReal> op0(0);
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

void KRowJointOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 3;
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


        TRowJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==3 && op.n()==8)

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


        TRowJointOperator<klab::DoubleReal> op0(0);
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

void KRowJointOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 3;
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


        TRowJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==3 && op.n()==8)

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


        TRowJointOperator<klab::DoubleReal> op0(0, 0);
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

void KRowJointOperatorUnitTest::testApplyBlockVariance()
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

        arma::Col<klab::DoubleReal> x(3);
        arma::Col<klab::DoubleReal> y;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;


        TRowJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==3 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==3)

        op.applyBlockVariance(x, y);
        TEST_ASSERT(y.n_rows==1)
        TEST_ASSERT(klab::Equals(y[0], x[0]*op.block(0, 0)->variance() + x[1]*op.block(0, 1)->variance() + x[2]*op.block(0, 2)->variance(), precision))        
        

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

void KRowJointOperatorUnitTest::testApplyBlockVarianceAdjoint()
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

        arma::Col<klab::DoubleReal> x(3);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;


        TRowJointOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2), new TMatrixOperator<klab::DoubleReal>(matrix3));
        TEST_ASSERT(op.m()==3 && op.n()==8)
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==3)

        op.applyBlockVariance(x, y);
        op.applyBlockVarianceAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows==3)
        TEST_ASSERT(klab::Equals(xr[0], y[0]*op.block(0, 0)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[1], y[0]*op.block(0, 1)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[2], y[0]*op.block(0, 2)->variance(), precision))
        

        // Limit cases.
        try                                         {op.applyBlockVarianceAdjoint(arma::Col<klab::DoubleReal>(), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyBlockVarianceAdjoint(arma::Col<klab::DoubleReal>(2), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
