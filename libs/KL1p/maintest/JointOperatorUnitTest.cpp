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

#include "JointOperatorUnitTest.h"
#include "../include/JointOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KJointOperatorUnitTest::KJointOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KJointOperatorUnitTest::testOpConstructor) 
    TEST_ADD(KJointOperatorUnitTest::testOpArrayConstructor) 
    TEST_ADD(KJointOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KJointOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KJointOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KJointOperatorUnitTest::testBlock)
    TEST_ADD(KJointOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KJointOperatorUnitTest::testInBlock)
    TEST_ADD(KJointOperatorUnitTest::testApply)
    TEST_ADD(KJointOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KJointOperatorUnitTest::testColumn)
    TEST_ADD(KJointOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KJointOperatorUnitTest::testApplyBlockVariance)
    TEST_ADD(KJointOperatorUnitTest::testApplyBlockVarianceAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KJointOperatorUnitTest::~KJointOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testOpConstructor()
{
    try
    {
        TJointOperator<klab::DoubleReal> op(new kl1p::TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 4))); 
        TEST_ASSERT(op.m()==3 && op.n()==4)    
        TEST_ASSERT(op.countBlockRows()==1 && op.countBlockColumns()==1)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==3 && op.block(0, 0)->n()==4) 


        // Limit cases.
        TJointOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)    
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testOpArrayConstructor()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);
        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators); 
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==3 && op.block(0, 0)->n()==3) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==3 && op.block(0, 1)->n()==4) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()==false && op.block(0, 2)->m()==3 && op.block(0, 2)->n()==5) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()==false && op.block(0, 3)->m()==3 && op.block(0, 3)->n()==6)
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==4 && op.block(1, 0)->n()==3) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==4 && op.block(1, 1)->n()==4) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==4 && op.block(1, 2)->n()==5) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()==false && op.block(1, 3)->m()==4 && op.block(1, 3)->n()==6) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()==false && op.block(2, 0)->m()==5 && op.block(2, 0)->n()==3) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==5 && op.block(2, 1)->n()==4) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==5 && op.block(2, 2)->n()==5) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==5 && op.block(2, 3)->n()==6)


        m = 0;
        n = 0;
        blockRows = 0;
        blockCols = 0;
        KJointOperatorUnitTest::GenerateTestOperators_02(operators, m, n, blockRows, blockCols);
        TJointOperator<klab::DoubleReal> op2(blockRows, blockCols, operators); 
        TEST_ASSERT(op2.m()==m && op2.n()==n)    
        TEST_ASSERT(op2.countBlockRows()==2 && op2.countBlockColumns()==3)
        TEST_ASSERT(op2.block(0, 0)!=0 && op2.block(0, 0)->isZero()==false && op2.block(0, 0)->m()==3 && op2.block(0, 0)->n()==3) 
        TEST_ASSERT(op2.block(0, 1)!=0 && op2.block(0, 1)->isZero()==false && op2.block(0, 1)->m()==3 && op2.block(0, 1)->n()==4)       
        TEST_ASSERT(op2.block(0, 2)!=0 && op2.block(0, 2)->isZero()==false && op2.block(0, 2)->m()==3 && op2.block(0, 2)->n()==6)        
        TEST_ASSERT(op2.block(1, 0)!=0 && op2.block(1, 0)->isZero()==false && op2.block(1, 0)->m()==5 && op2.block(1, 0)->n()==3) 
        TEST_ASSERT(op2.block(1, 1)!=0 && op2.block(1, 1)->isZero()==false && op2.block(1, 1)->m()==5 && op2.block(1, 1)->n()==4)         
        TEST_ASSERT(op2.block(1, 2)!=0 && op2.block(1, 2)->isZero()==false && op2.block(1, 2)->m()==5 && op2.block(1, 2)->n()==6)


        // Limit cases.
        TJointOperator<klab::DoubleReal> op00(0, 0, TJointOperator<klab::DoubleReal>::TOperatorArray());
        TEST_ASSERT(op00.m()==0 && op00.n()==0)    
        TEST_ASSERT(op00.countBlockRows()==0 && op00.countBlockColumns()==0)

        TJointOperator<klab::DoubleReal> op01(0, 1, TJointOperator<klab::DoubleReal>::TOperatorArray());
        TEST_ASSERT(op01.m()==0 && op01.n()==0)    
        TEST_ASSERT(op01.countBlockRows()==0 && op01.countBlockColumns()==0)

        TJointOperator<klab::DoubleReal> op02(1, 0, TJointOperator<klab::DoubleReal>::TOperatorArray());
        TEST_ASSERT(op02.m()==0 && op02.n()==0)    
        TEST_ASSERT(op02.countBlockRows()==0 && op02.countBlockColumns()==0)

        TJointOperator<klab::DoubleReal> op03(1, 1, TJointOperator<klab::DoubleReal>::TOperatorArray());
        TEST_ASSERT(op03.m()==0 && op03.n()==0)    
        TEST_ASSERT(op03.countBlockRows()==0 && op03.countBlockColumns()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KJointOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators); 
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==3 && op.block(0, 0)->n()==3) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==3 && op.block(0, 1)->n()==4) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()==false && op.block(0, 2)->m()==3 && op.block(0, 2)->n()==5) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()==false && op.block(0, 3)->m()==3 && op.block(0, 3)->n()==6)
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==4 && op.block(1, 0)->n()==3) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==4 && op.block(1, 1)->n()==4) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==4 && op.block(1, 2)->n()==5) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()==false && op.block(1, 3)->m()==4 && op.block(1, 3)->n()==6) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()==false && op.block(2, 0)->m()==5 && op.block(2, 0)->n()==3) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==5 && op.block(2, 1)->n()==4) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==5 && op.block(2, 2)->n()==5) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==5 && op.block(2, 3)->n()==6)

        TJointOperator<klab::DoubleReal> opCopy(op); 
        TEST_ASSERT(opCopy.m()==m && opCopy.n()==n)    
        TEST_ASSERT(opCopy.countBlockRows()==blockRows && opCopy.countBlockColumns()==blockCols)
        TEST_ASSERT(opCopy.block(0, 0)!=0 && opCopy.block(0, 0)->isZero()==false && opCopy.block(0, 0)->m()==3 && opCopy.block(0, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(0, 1)!=0 && opCopy.block(0, 1)->isZero()==false && opCopy.block(0, 1)->m()==3 && opCopy.block(0, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(0, 2)!=0 && opCopy.block(0, 2)->isZero()==false && opCopy.block(0, 2)->m()==3 && opCopy.block(0, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(0, 3)!=0 && opCopy.block(0, 3)->isZero()==false && opCopy.block(0, 3)->m()==3 && opCopy.block(0, 3)->n()==6)
        TEST_ASSERT(opCopy.block(1, 0)!=0 && opCopy.block(1, 0)->isZero()==false && opCopy.block(1, 0)->m()==4 && opCopy.block(1, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(1, 1)!=0 && opCopy.block(1, 1)->isZero()==false && opCopy.block(1, 1)->m()==4 && opCopy.block(1, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(1, 2)!=0 && opCopy.block(1, 2)->isZero()==false && opCopy.block(1, 2)->m()==4 && opCopy.block(1, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(1, 3)!=0 && opCopy.block(1, 3)->isZero()==false && opCopy.block(1, 3)->m()==4 && opCopy.block(1, 3)->n()==6) 
        TEST_ASSERT(opCopy.block(2, 0)!=0 && opCopy.block(2, 0)->isZero()==false && opCopy.block(2, 0)->m()==5 && opCopy.block(2, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(2, 1)!=0 && opCopy.block(2, 1)->isZero()==false && opCopy.block(2, 1)->m()==5 && opCopy.block(2, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(2, 2)!=0 && opCopy.block(2, 2)->isZero()==false && opCopy.block(2, 2)->m()==5 && opCopy.block(2, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(2, 3)!=0 && opCopy.block(2, 3)->isZero()==false && opCopy.block(2, 3)->m()==5 && opCopy.block(2, 3)->n()==6)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testCountBlockRows()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators); 
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators); 
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators); 
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()==false) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()==false)
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()==false) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()==false) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false)


        // Limit cases.
        TJointOperator<klab::DoubleReal> op0(0);
        try                                     {op0.block(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(3, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(2, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(3, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators); 
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.isZeroBlock(0, 0)==false) 
        TEST_ASSERT(op.isZeroBlock(0, 1)==false) 
        TEST_ASSERT(op.isZeroBlock(0, 2)==false) 
        TEST_ASSERT(op.isZeroBlock(0, 3)==false)
        TEST_ASSERT(op.isZeroBlock(1, 0)==false) 
        TEST_ASSERT(op.isZeroBlock(1, 1)==false) 
        TEST_ASSERT(op.isZeroBlock(1, 2)==false) 
        TEST_ASSERT(op.isZeroBlock(1, 3)==false) 
        TEST_ASSERT(op.isZeroBlock(2, 0)==false) 
        TEST_ASSERT(op.isZeroBlock(2, 1)==false) 
        TEST_ASSERT(op.isZeroBlock(2, 2)==false) 
        TEST_ASSERT(op.isZeroBlock(2, 3)==false)


        // Limit cases.
        TJointOperator<klab::DoubleReal> op0(0);
        try                                     {op0.isZeroBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(3, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(2, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(3, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testInBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators); 
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        klab::TSmartPointer<TOperator<klab::DoubleReal> > result = op.inBlock(0, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3) 

        result = op.inBlock(0, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(1, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(1, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(1, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(1, 3);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(1, 7);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==5)

        result = op.inBlock(1, 12);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==6)

        result = op.inBlock(1, 17);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==6)

        result = op.inBlock(4, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==3)

        result = op.inBlock(4, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==3)

        result = op.inBlock(4, 3);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==4)

        result = op.inBlock(4, 7);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5)

        result = op.inBlock(4, 12);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==6)

        result = op.inBlock(4, 17);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==6)

        result = op.inBlock(9, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==3)

        result = op.inBlock(9, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==3)

        result = op.inBlock(9, 3);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==4)

        result = op.inBlock(9, 7);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==5)

        result = op.inBlock(9, 12);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==6)

        result = op.inBlock(9, 17);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==6)

        result = op.inBlock(11, 17);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==6)


        // Limit cases.
        TJointOperator<klab::DoubleReal> op0(0);
        try                                     {op0.inBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(12, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(2, 18); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(12, 18); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-9; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

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
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;
        x[12] = 13.0;
        x[13] = 14.0;
        x[14] = 15.0;
        x[15] = 16.0;
        x[16] = 17.0;
        x[17] = 18.0;


        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators);
        TEST_ASSERT(op.m()==m && op.n()==n)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == m)
        TEST_ASSERT(klab::Equals(y[0], -7.8, precision))
        TEST_ASSERT(klab::Equals(y[1],  401.6, precision))
        TEST_ASSERT(klab::Equals(y[2],  242.4, precision))
        TEST_ASSERT(klab::Equals(y[3],  79.7, precision))
        TEST_ASSERT(klab::Equals(y[4],  521.13, precision))
        TEST_ASSERT(klab::Equals(y[5],  663.05, precision))
        TEST_ASSERT(klab::Equals(y[6],  1278.41, precision))
        TEST_ASSERT(klab::Equals(y[7],  1823.8, precision))
        TEST_ASSERT(klab::Equals(y[8],  776.2, precision))
        TEST_ASSERT(klab::Equals(y[9],  177.4, precision))
        TEST_ASSERT(klab::Equals(y[10], 1000.4, precision))
        TEST_ASSERT(klab::Equals(y[11], 242.8, precision))


        // Limit cases.
        try                                         {op.apply(arma::Col<klab::DoubleReal>(n-1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<klab::DoubleReal>(n+1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-9; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

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
        x[8] = 9.0;
        x[9] = 10.0;
        x[10] = 11.0;
        x[11] = 12.0;
        x[12] = 13.0;
        x[13] = 14.0;
        x[14] = 15.0;
        x[15] = 16.0;
        x[16] = 17.0;
        x[17] = 18.0;


        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators);
        TEST_ASSERT(op.m()==m && op.n()==n)

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == n)
        TEST_ASSERT(klab::Equals(xr[0],  25079.068, precision))
        TEST_ASSERT(klab::Equals(xr[1],  20159.729, precision))
        TEST_ASSERT(klab::Equals(xr[2],  33884.21, precision))
        TEST_ASSERT(klab::Equals(xr[3],  3256.826, precision))
        TEST_ASSERT(klab::Equals(xr[4],  12068.596, precision))
        TEST_ASSERT(klab::Equals(xr[5],  4412.186, precision))
        TEST_ASSERT(klab::Equals(xr[6],  12103.576, precision))
        TEST_ASSERT(klab::Equals(xr[7], -13659.33, precision))
        TEST_ASSERT(klab::Equals(xr[8],  45816.04, precision))
        TEST_ASSERT(klab::Equals(xr[9],  31118.43, precision))
        TEST_ASSERT(klab::Equals(xr[10], 30639.26, precision))
        TEST_ASSERT(klab::Equals(xr[11], 106.43, precision))
        TEST_ASSERT(klab::Equals(xr[12],-28706.5666, precision))
        TEST_ASSERT(klab::Equals(xr[13], 120951.86, precision))
        TEST_ASSERT(klab::Equals(xr[14], 50103.7184, precision))
        TEST_ASSERT(klab::Equals(xr[15], 100994.28, precision))
        TEST_ASSERT(klab::Equals(xr[16], 44572.1129, precision))
        TEST_ASSERT(klab::Equals(xr[17], 102357.74, precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(m-1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(m+1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testColumn()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators);
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

void KJointOperatorUnitTest::testColumnAdjoint()
{
    try
    {       
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators);
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

void KJointOperatorUnitTest::GenerateTestOperators_01(std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > >& operators, klab::UInt32& m, klab::UInt32& n, klab::UInt32& blockRows, klab::UInt32& blockCols)
{
    arma::Mat<klab::DoubleReal> matrix00(3, 3);
    arma::Mat<klab::DoubleReal> matrix01(3, 4);
    arma::Mat<klab::DoubleReal> matrix02(3, 5);
    arma::Mat<klab::DoubleReal> matrix03(3, 6);
    arma::Mat<klab::DoubleReal> matrix10(4, 3);
    arma::Mat<klab::DoubleReal> matrix11(4, 4);
    arma::Mat<klab::DoubleReal> matrix12(4, 5);
    arma::Mat<klab::DoubleReal> matrix13(4, 6);
    arma::Mat<klab::DoubleReal> matrix20(5, 3);
    arma::Mat<klab::DoubleReal> matrix21(5, 4);
    arma::Mat<klab::DoubleReal> matrix22(5, 5);
    arma::Mat<klab::DoubleReal> matrix23(5, 6);

    matrix00(0, 0) = klab::DoubleReal(1.0);
    matrix00(0, 1) = klab::DoubleReal(-2.0);
    matrix00(0, 2) = klab::DoubleReal(3.0);
    matrix00(1, 0) = klab::DoubleReal(4.0);
    matrix00(1, 1) = klab::DoubleReal(-5.0);
    matrix00(1, 2) = klab::DoubleReal(6.0);
    matrix00(2, 0) = klab::DoubleReal(7.0);
    matrix00(2, 1) = klab::DoubleReal(-8.0);
    matrix00(2, 2) = klab::DoubleReal(9.0);

    matrix01(0, 0) = klab::DoubleReal(-12.0);
    matrix01(0, 1) = klab::DoubleReal(11.0);
    matrix01(0, 2) = klab::DoubleReal(10.0);
    matrix01(0, 3) = klab::DoubleReal(-9.0);
    matrix01(1, 0) = klab::DoubleReal(-8.0);
    matrix01(1, 1) = klab::DoubleReal(7.0);
    matrix01(1, 2) = klab::DoubleReal(6.0);
    matrix01(1, 3) = klab::DoubleReal(5.0);
    matrix01(2, 0) = klab::DoubleReal(4.0);
    matrix01(2, 1) = klab::DoubleReal(3.0);
    matrix01(2, 2) = klab::DoubleReal(-2.0);
    matrix01(2, 3) = klab::DoubleReal(1.0);

    matrix02(0, 0) = klab::DoubleReal(0.0);
    matrix02(0, 1) = klab::DoubleReal(0.1);
    matrix02(0, 2) = klab::DoubleReal(0.2);
    matrix02(0, 3) = klab::DoubleReal(-0.3);
    matrix02(0, 4) = klab::DoubleReal(0.4);
    matrix02(1, 0) = klab::DoubleReal(1.0);
    matrix02(1, 1) = klab::DoubleReal(1.1);
    matrix02(1, 2) = klab::DoubleReal(1.2);
    matrix02(1, 3) = klab::DoubleReal(1.3);
    matrix02(1, 4) = klab::DoubleReal(1.4);
    matrix02(2, 0) = klab::DoubleReal(-2.0);
    matrix02(2, 1) = klab::DoubleReal(2.1);
    matrix02(2, 2) = klab::DoubleReal(2.2);
    matrix02(2, 3) = klab::DoubleReal(2.3);
    matrix02(2, 4) = klab::DoubleReal(2.4);

    matrix03(0, 0) = klab::DoubleReal(1.0);
    matrix03(0, 1) = klab::DoubleReal(1.2);
    matrix03(0, 2) = klab::DoubleReal(-1.4);
    matrix03(0, 3) = klab::DoubleReal(-1.6);
    matrix03(0, 4) = klab::DoubleReal(1.8);
    matrix03(0, 5) = klab::DoubleReal(-2.0);
    matrix03(1, 0) = klab::DoubleReal(2.2);
    matrix03(1, 1) = klab::DoubleReal(2.4);
    matrix03(1, 2) = klab::DoubleReal(2.6);
    matrix03(1, 3) = klab::DoubleReal(2.8);
    matrix03(1, 4) = klab::DoubleReal(3.0);
    matrix03(1, 5) = klab::DoubleReal(3.2);
    matrix03(2, 0) = klab::DoubleReal(-3.4);
    matrix03(2, 1) = klab::DoubleReal(3.6);
    matrix03(2, 2) = klab::DoubleReal(3.8);
    matrix03(2, 3) = klab::DoubleReal(4.0);
    matrix03(2, 4) = klab::DoubleReal(4.2);
    matrix03(2, 5) = klab::DoubleReal(-4.4);

    matrix10(0, 0) = klab::DoubleReal(3.2);
    matrix10(0, 1) = klab::DoubleReal(3.1);
    matrix10(0, 2) = klab::DoubleReal(3.0);
    matrix10(1, 0) = klab::DoubleReal(2.2);
    matrix10(1, 1) = klab::DoubleReal(2.1);
    matrix10(1, 2) = klab::DoubleReal(2.0);
    matrix10(2, 0) = klab::DoubleReal(1.2);
    matrix10(2, 1) = klab::DoubleReal(-1.1);
    matrix10(2, 2) = klab::DoubleReal(1.0);
    matrix10(3, 0) = klab::DoubleReal(0.2);
    matrix10(3, 1) = klab::DoubleReal(0.1);
    matrix10(3, 2) = klab::DoubleReal(0.0);

    matrix11(0, 0) = klab::DoubleReal(0.0);
    matrix11(0, 1) = klab::DoubleReal(1.0);
    matrix11(0, 2) = klab::DoubleReal(2.0);
    matrix11(0, 3) = klab::DoubleReal(-3.0);
    matrix11(1, 0) = klab::DoubleReal(0.1);
    matrix11(1, 1) = klab::DoubleReal(1.1);
    matrix11(1, 2) = klab::DoubleReal(2.1);
    matrix11(1, 3) = klab::DoubleReal(3.1);
    matrix11(2, 0) = klab::DoubleReal(-0.2);
    matrix11(2, 1) = klab::DoubleReal(1.2);
    matrix11(2, 2) = klab::DoubleReal(2.2);
    matrix11(2, 3) = klab::DoubleReal(-3.2);
    matrix11(3, 0) = klab::DoubleReal(0.3);
    matrix11(3, 1) = klab::DoubleReal(1.3);
    matrix11(3, 2) = klab::DoubleReal(2.3);
    matrix11(3, 3) = klab::DoubleReal(3.3);

    matrix12(0, 0) = klab::DoubleReal(-1.0);
    matrix12(0, 1) = klab::DoubleReal(2.0);
    matrix12(0, 2) = klab::DoubleReal(-3.0);
    matrix12(0, 3) = klab::DoubleReal(-4.0);
    matrix12(0, 4) = klab::DoubleReal(5.0);
    matrix12(1, 0) = klab::DoubleReal(6.0);
    matrix12(1, 1) = klab::DoubleReal(7.0);
    matrix12(1, 2) = klab::DoubleReal(8.0);
    matrix12(1, 3) = klab::DoubleReal(9.0);
    matrix12(1, 4) = klab::DoubleReal(10.0);
    matrix12(2, 0) = klab::DoubleReal(11.0);
    matrix12(2, 1) = klab::DoubleReal(12.0);
    matrix12(2, 2) = klab::DoubleReal(-13.0);
    matrix12(2, 3) = klab::DoubleReal(14.0);
    matrix12(2, 4) = klab::DoubleReal(15.0);
    matrix12(3, 0) = klab::DoubleReal(-16.0);
    matrix12(3, 1) = klab::DoubleReal(17.0);
    matrix12(3, 2) = klab::DoubleReal(18.0);
    matrix12(3, 3) = klab::DoubleReal(19.0);
    matrix12(3, 4) = klab::DoubleReal(-20.0);

    matrix13(0, 0) = klab::DoubleReal(0.1);
    matrix13(0, 1) = klab::DoubleReal(2.0);
    matrix13(0, 2) = klab::DoubleReal(0.3);
    matrix13(0, 3) = klab::DoubleReal(-4.0);
    matrix13(0, 4) = klab::DoubleReal(-0.5);
    matrix13(0, 5) = klab::DoubleReal(6.0);
    matrix13(1, 0) = klab::DoubleReal(-0.7);
    matrix13(1, 1) = klab::DoubleReal(8.0);
    matrix13(1, 2) = klab::DoubleReal(0.9);
    matrix13(1, 3) = klab::DoubleReal(10.0);
    matrix13(1, 4) = klab::DoubleReal(-0.11);
    matrix13(1, 5) = klab::DoubleReal(-12.0);
    matrix13(2, 0) = klab::DoubleReal(0.13);
    matrix13(2, 1) = klab::DoubleReal(14.0);
    matrix13(2, 2) = klab::DoubleReal(0.15);
    matrix13(2, 3) = klab::DoubleReal(-16.0);
    matrix13(2, 4) = klab::DoubleReal(-0.17);
    matrix13(2, 5) = klab::DoubleReal(18.0);
    matrix13(3, 0) = klab::DoubleReal(0.19);
    matrix13(3, 1) = klab::DoubleReal(20.0);
    matrix13(3, 2) = klab::DoubleReal(-0.21);
    matrix13(3, 3) = klab::DoubleReal(22.0);
    matrix13(3, 4) = klab::DoubleReal(-0.23);
    matrix13(3, 5) = klab::DoubleReal(24.0);

    matrix20(0, 0) = klab::DoubleReal(1.0);
    matrix20(0, 1) = klab::DoubleReal(2.0);
    matrix20(0, 2) = klab::DoubleReal(3.0);
    matrix20(1, 0) = klab::DoubleReal(4.0);
    matrix20(1, 1) = klab::DoubleReal(5.0);
    matrix20(1, 2) = klab::DoubleReal(6.0);
    matrix20(2, 0) = klab::DoubleReal(7.0);
    matrix20(2, 1) = klab::DoubleReal(8.0);
    matrix20(2, 2) = klab::DoubleReal(9.0);
    matrix20(3, 0) = klab::DoubleReal(10.0);
    matrix20(3, 1) = klab::DoubleReal(11.0);
    matrix20(3, 2) = klab::DoubleReal(12.0);
    matrix20(4, 0) = klab::DoubleReal(13.0);
    matrix20(4, 1) = klab::DoubleReal(14.0);
    matrix20(4, 2) = klab::DoubleReal(15.0);

    matrix21(0, 0) = klab::DoubleReal(0.0);
    matrix21(0, 1) = klab::DoubleReal(0.1);
    matrix21(0, 2) = klab::DoubleReal(-0.2);
    matrix21(0, 3) = klab::DoubleReal(0.3);
    matrix21(1, 0) = klab::DoubleReal(1.0);
    matrix21(1, 1) = klab::DoubleReal(1.1);
    matrix21(1, 2) = klab::DoubleReal(-1.2);
    matrix21(1, 3) = klab::DoubleReal(1.3);
    matrix21(2, 0) = klab::DoubleReal(2.0);
    matrix21(2, 1) = klab::DoubleReal(2.1);
    matrix21(2, 2) = klab::DoubleReal(2.2);
    matrix21(2, 3) = klab::DoubleReal(2.3);
    matrix21(3, 0) = klab::DoubleReal(3.0);
    matrix21(3, 1) = klab::DoubleReal(3.1);
    matrix21(3, 2) = klab::DoubleReal(-3.2);
    matrix21(3, 3) = klab::DoubleReal(3.3);
    matrix21(4, 0) = klab::DoubleReal(4.0);
    matrix21(4, 1) = klab::DoubleReal(4.1);
    matrix21(4, 2) = klab::DoubleReal(4.2);
    matrix21(4, 3) = klab::DoubleReal(4.3);

    matrix22(0, 0) = klab::DoubleReal(-4.4);
    matrix22(0, 1) = klab::DoubleReal(4.3);
    matrix22(0, 2) = klab::DoubleReal(4.2);
    matrix22(0, 3) = klab::DoubleReal(-4.1);
    matrix22(0, 4) = klab::DoubleReal(4.0);
    matrix22(1, 0) = klab::DoubleReal(3.4);
    matrix22(1, 1) = klab::DoubleReal(3.3);
    matrix22(1, 2) = klab::DoubleReal(3.2);
    matrix22(1, 3) = klab::DoubleReal(-3.1);
    matrix22(1, 4) = klab::DoubleReal(3.0);
    matrix22(2, 0) = klab::DoubleReal(2.4);
    matrix22(2, 1) = klab::DoubleReal(-2.3);
    matrix22(2, 2) = klab::DoubleReal(2.2);
    matrix22(2, 3) = klab::DoubleReal(2.1);
    matrix22(2, 4) = klab::DoubleReal(2.0);
    matrix22(3, 0) = klab::DoubleReal(1.4);
    matrix22(3, 1) = klab::DoubleReal(1.3);
    matrix22(3, 2) = klab::DoubleReal(1.2);
    matrix22(3, 3) = klab::DoubleReal(1.1);
    matrix22(3, 4) = klab::DoubleReal(-1.0);
    matrix22(4, 0) = klab::DoubleReal(0.4);
    matrix22(4, 1) = klab::DoubleReal(0.3);
    matrix22(4, 2) = klab::DoubleReal(0.2);
    matrix22(4, 3) = klab::DoubleReal(0.1);
    matrix22(4, 4) = klab::DoubleReal(0.0);

    matrix23(0, 0) = klab::DoubleReal(-30.0);
    matrix23(0, 1) = klab::DoubleReal(29.0);
    matrix23(0, 2) = klab::DoubleReal(28.0);
    matrix23(0, 3) = klab::DoubleReal(27.0);
    matrix23(0, 4) = klab::DoubleReal(26.0);
    matrix23(0, 5) = klab::DoubleReal(25.0);
    matrix23(1, 0) = klab::DoubleReal(24.0);
    matrix23(1, 1) = klab::DoubleReal(23.0);
    matrix23(1, 2) = klab::DoubleReal(-22.0);
    matrix23(1, 3) = klab::DoubleReal(21.0);
    matrix23(1, 4) = klab::DoubleReal(-20.0);
    matrix23(1, 5) = klab::DoubleReal(19.0);
    matrix23(2, 0) = klab::DoubleReal(-18.0);
    matrix23(2, 1) = klab::DoubleReal(-17.0);
    matrix23(2, 2) = klab::DoubleReal(16.0);
    matrix23(2, 3) = klab::DoubleReal(15.0);
    matrix23(2, 4) = klab::DoubleReal(14.0);
    matrix23(2, 5) = klab::DoubleReal(-13.0);
    matrix23(3, 0) = klab::DoubleReal(12.0);
    matrix23(3, 1) = klab::DoubleReal(11.0);
    matrix23(3, 2) = klab::DoubleReal(10.0);
    matrix23(3, 3) = klab::DoubleReal(9.0);
    matrix23(3, 4) = klab::DoubleReal(8.0);
    matrix23(3, 5) = klab::DoubleReal(7.0);
    matrix23(4, 0) = klab::DoubleReal(-6.0);
    matrix23(4, 1) = klab::DoubleReal(5.0);
    matrix23(4, 2) = klab::DoubleReal(4.0);
    matrix23(4, 3) = klab::DoubleReal(-3.0);
    matrix23(4, 4) = klab::DoubleReal(2.0);
    matrix23(4, 5) = klab::DoubleReal(1.0);


    operators.clear();
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix00));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix01));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix02));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix03));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix10));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix11));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix12));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix13));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix20));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix21));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix22));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix23));

    m = klab::Max(operators[0]->m()+operators[4]->m()+operators[8]->m(), klab::Max(operators[1]->m()+operators[5]->m()+operators[9]->m(), klab::Max(operators[2]->m()+operators[6]->m()+operators[10]->m(), operators[3]->m()+operators[7]->m()+operators[11]->m())));
    n = klab::Max(operators[0]->n()+operators[1]->n()+operators[2]->n()+operators[3]->n(), klab::Max(operators[4]->n()+operators[5]->n()+operators[6]->n()+operators[7]->n(), operators[8]->n()+operators[9]->n()+operators[10]->n()+operators[11]->n()));

    blockRows = 3;
    blockCols = 4;
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::GenerateTestOperators_02(std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > >& operators, klab::UInt32& m, klab::UInt32& n, klab::UInt32& blockRows, klab::UInt32& blockCols)
{
    arma::Mat<klab::DoubleReal> matrix00(3, 3);
    arma::Mat<klab::DoubleReal> matrix01(3, 4);
    arma::Mat<klab::DoubleReal> matrix03(3, 6);
    arma::Mat<klab::DoubleReal> matrix20(5, 3);
    arma::Mat<klab::DoubleReal> matrix21(5, 4);
    arma::Mat<klab::DoubleReal> matrix23(5, 6);

    matrix00(0, 0) = klab::DoubleReal(1.0);
    matrix00(0, 1) = klab::DoubleReal(-2.0);
    matrix00(0, 2) = klab::DoubleReal(3.0);
    matrix00(1, 0) = klab::DoubleReal(4.0);
    matrix00(1, 1) = klab::DoubleReal(-5.0);
    matrix00(1, 2) = klab::DoubleReal(6.0);
    matrix00(2, 0) = klab::DoubleReal(7.0);
    matrix00(2, 1) = klab::DoubleReal(-8.0);
    matrix00(2, 2) = klab::DoubleReal(9.0);

    matrix01(0, 0) = klab::DoubleReal(-12.0);
    matrix01(0, 1) = klab::DoubleReal(11.0);
    matrix01(0, 2) = klab::DoubleReal(10.0);
    matrix01(0, 3) = klab::DoubleReal(-9.0);
    matrix01(1, 0) = klab::DoubleReal(-8.0);
    matrix01(1, 1) = klab::DoubleReal(7.0);
    matrix01(1, 2) = klab::DoubleReal(6.0);
    matrix01(1, 3) = klab::DoubleReal(5.0);
    matrix01(2, 0) = klab::DoubleReal(4.0);
    matrix01(2, 1) = klab::DoubleReal(3.0);
    matrix01(2, 2) = klab::DoubleReal(-2.0);
    matrix01(2, 3) = klab::DoubleReal(1.0);

    matrix03(0, 0) = klab::DoubleReal(1.0);
    matrix03(0, 1) = klab::DoubleReal(1.2);
    matrix03(0, 2) = klab::DoubleReal(-1.4);
    matrix03(0, 3) = klab::DoubleReal(-1.6);
    matrix03(0, 4) = klab::DoubleReal(1.8);
    matrix03(0, 5) = klab::DoubleReal(-2.0);
    matrix03(1, 0) = klab::DoubleReal(2.2);
    matrix03(1, 1) = klab::DoubleReal(2.4);
    matrix03(1, 2) = klab::DoubleReal(2.6);
    matrix03(1, 3) = klab::DoubleReal(2.8);
    matrix03(1, 4) = klab::DoubleReal(3.0);
    matrix03(1, 5) = klab::DoubleReal(3.2);
    matrix03(2, 0) = klab::DoubleReal(-3.4);
    matrix03(2, 1) = klab::DoubleReal(3.6);
    matrix03(2, 2) = klab::DoubleReal(3.8);
    matrix03(2, 3) = klab::DoubleReal(4.0);
    matrix03(2, 4) = klab::DoubleReal(4.2);
    matrix03(2, 5) = klab::DoubleReal(-4.4);

    matrix20(0, 0) = klab::DoubleReal(1.0);
    matrix20(0, 1) = klab::DoubleReal(2.0);
    matrix20(0, 2) = klab::DoubleReal(3.0);
    matrix20(1, 0) = klab::DoubleReal(4.0);
    matrix20(1, 1) = klab::DoubleReal(5.0);
    matrix20(1, 2) = klab::DoubleReal(6.0);
    matrix20(2, 0) = klab::DoubleReal(7.0);
    matrix20(2, 1) = klab::DoubleReal(8.0);
    matrix20(2, 2) = klab::DoubleReal(9.0);
    matrix20(3, 0) = klab::DoubleReal(10.0);
    matrix20(3, 1) = klab::DoubleReal(11.0);
    matrix20(3, 2) = klab::DoubleReal(12.0);
    matrix20(4, 0) = klab::DoubleReal(13.0);
    matrix20(4, 1) = klab::DoubleReal(14.0);
    matrix20(4, 2) = klab::DoubleReal(15.0);

    matrix21(0, 0) = klab::DoubleReal(0.0);
    matrix21(0, 1) = klab::DoubleReal(0.1);
    matrix21(0, 2) = klab::DoubleReal(-0.2);
    matrix21(0, 3) = klab::DoubleReal(0.3);
    matrix21(1, 0) = klab::DoubleReal(1.0);
    matrix21(1, 1) = klab::DoubleReal(1.1);
    matrix21(1, 2) = klab::DoubleReal(-1.2);
    matrix21(1, 3) = klab::DoubleReal(1.3);
    matrix21(2, 0) = klab::DoubleReal(2.0);
    matrix21(2, 1) = klab::DoubleReal(2.1);
    matrix21(2, 2) = klab::DoubleReal(2.2);
    matrix21(2, 3) = klab::DoubleReal(2.3);
    matrix21(3, 0) = klab::DoubleReal(3.0);
    matrix21(3, 1) = klab::DoubleReal(3.1);
    matrix21(3, 2) = klab::DoubleReal(-3.2);
    matrix21(3, 3) = klab::DoubleReal(3.3);
    matrix21(4, 0) = klab::DoubleReal(4.0);
    matrix21(4, 1) = klab::DoubleReal(4.1);
    matrix21(4, 2) = klab::DoubleReal(4.2);
    matrix21(4, 3) = klab::DoubleReal(4.3);

    matrix23(0, 0) = klab::DoubleReal(-30.0);
    matrix23(0, 1) = klab::DoubleReal(29.0);
    matrix23(0, 2) = klab::DoubleReal(28.0);
    matrix23(0, 3) = klab::DoubleReal(27.0);
    matrix23(0, 4) = klab::DoubleReal(26.0);
    matrix23(0, 5) = klab::DoubleReal(25.0);
    matrix23(1, 0) = klab::DoubleReal(24.0);
    matrix23(1, 1) = klab::DoubleReal(23.0);
    matrix23(1, 2) = klab::DoubleReal(-22.0);
    matrix23(1, 3) = klab::DoubleReal(21.0);
    matrix23(1, 4) = klab::DoubleReal(-20.0);
    matrix23(1, 5) = klab::DoubleReal(19.0);
    matrix23(2, 0) = klab::DoubleReal(-18.0);
    matrix23(2, 1) = klab::DoubleReal(-17.0);
    matrix23(2, 2) = klab::DoubleReal(16.0);
    matrix23(2, 3) = klab::DoubleReal(15.0);
    matrix23(2, 4) = klab::DoubleReal(14.0);
    matrix23(2, 5) = klab::DoubleReal(-13.0);
    matrix23(3, 0) = klab::DoubleReal(12.0);
    matrix23(3, 1) = klab::DoubleReal(11.0);
    matrix23(3, 2) = klab::DoubleReal(10.0);
    matrix23(3, 3) = klab::DoubleReal(9.0);
    matrix23(3, 4) = klab::DoubleReal(8.0);
    matrix23(3, 5) = klab::DoubleReal(7.0);
    matrix23(4, 0) = klab::DoubleReal(-6.0);
    matrix23(4, 1) = klab::DoubleReal(5.0);
    matrix23(4, 2) = klab::DoubleReal(4.0);
    matrix23(4, 3) = klab::DoubleReal(-3.0);
    matrix23(4, 4) = klab::DoubleReal(2.0);
    matrix23(4, 5) = klab::DoubleReal(1.0);


    operators.clear();
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix00));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix01));
    operators.push_back(0);
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix03));
    operators.push_back(0);
    operators.push_back(0);
    operators.push_back(0);
    operators.push_back(0);
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix20));
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix21));
    operators.push_back(0);
    operators.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix23));

    m = klab::Max(operators[0]->m()+operators[8]->m(), klab::Max(operators[1]->m()+operators[9]->m(), operators[3]->m()+operators[11]->m()));
    n = klab::Max(operators[0]->n()+operators[1]->n()+operators[3]->n(), operators[8]->n()+operators[9]->n()+operators[11]->n());

    blockRows = 3;
    blockCols = 4;
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testApplyBlockVariance()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        arma::Col<klab::DoubleReal> x(4);
        arma::Col<klab::DoubleReal> y;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;


        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        op.applyBlockVariance(x, y);
        TEST_ASSERT(y.n_rows==blockRows)
        TEST_ASSERT(klab::Equals(y[0], x[0]*op.block(0, 0)->variance() + x[1]*op.block(0, 1)->variance() + x[2]*op.block(0, 2)->variance() + x[3]*op.block(0, 3)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[1], x[0]*op.block(1, 0)->variance() + x[1]*op.block(1, 1)->variance() + x[2]*op.block(1, 2)->variance() + x[3]*op.block(1, 3)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[2], x[0]*op.block(2, 0)->variance() + x[1]*op.block(2, 1)->variance() + x[2]*op.block(2, 2)->variance() + x[3]*op.block(2, 3)->variance(), precision))
        

        // Limit cases.
        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(blockCols-1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyBlockVariance(arma::Col<klab::DoubleReal>(blockCols+1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KJointOperatorUnitTest::testApplyBlockVarianceAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-9; 

        arma::Col<klab::DoubleReal> x(4);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;


        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TJointOperator<klab::DoubleReal> op(blockRows, blockCols, operators);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        op.applyBlockVariance(x, y);
        op.applyBlockVarianceAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows==blockCols)
        TEST_ASSERT(klab::Equals(xr[0], y[0]*op.block(0, 0)->variance() + y[1]*op.block(1, 0)->variance() + y[2]*op.block(2, 0)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[1], y[0]*op.block(0, 1)->variance() + y[1]*op.block(1, 1)->variance() + y[2]*op.block(2, 1)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[2], y[0]*op.block(0, 2)->variance() + y[1]*op.block(1, 2)->variance() + y[2]*op.block(2, 2)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[3], y[0]*op.block(0, 3)->variance() + y[1]*op.block(1, 3)->variance() + y[2]*op.block(2, 3)->variance(), precision))
        

        // Limit cases.
        try                                         {op.applyBlockVarianceAdjoint(arma::Col<klab::DoubleReal>(blockRows-1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyBlockVarianceAdjoint(arma::Col<klab::DoubleReal>(blockRows+1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
