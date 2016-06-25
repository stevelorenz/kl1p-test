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

#include "AdjointBlockOperatorUnitTest.h"
#include "JointOperatorUnitTest.h"
#include "../include/AdjointBlockOperator.h"
#include "../include/JointOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KAdjointBlockOperatorUnitTest::KAdjointBlockOperatorUnitTest() : Test::Suite()
{ 
    TEST_ADD(KAdjointBlockOperatorUnitTest::testOpConstructor)  
    TEST_ADD(KAdjointBlockOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KAdjointBlockOperatorUnitTest::testOp)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testIsZero)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testSum)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testNormFrobenius)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testMean)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testVariance)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testBlock)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testInBlock)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testApply)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testColumn)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testApplyBlockVariance)
    TEST_ADD(KAdjointBlockOperatorUnitTest::testApplyBlockVarianceAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KAdjointBlockOperatorUnitTest::~KAdjointBlockOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testOpConstructor()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)    
        TEST_ASSERT(op.countBlockRows()==blockCols && op.countBlockColumns()==blockRows)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==3 && op.block(0, 0)->n()==3) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==3 && op.block(0, 1)->n()==4) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()==false && op.block(0, 2)->m()==3 && op.block(0, 2)->n()==5) 
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==4 && op.block(1, 0)->n()==3) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==4 && op.block(1, 1)->n()==4) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==4 && op.block(1, 2)->n()==5) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()==false && op.block(2, 0)->m()==5 && op.block(2, 0)->n()==3) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==5 && op.block(2, 1)->n()==4) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==5 && op.block(2, 2)->n()==5) 
        TEST_ASSERT(op.block(3, 0)!=0 && op.block(3, 0)->isZero()==false && op.block(3, 0)->m()==6 && op.block(3, 0)->n()==3) 
        TEST_ASSERT(op.block(3, 1)!=0 && op.block(3, 1)->isZero()==false && op.block(3, 1)->m()==6 && op.block(3, 1)->n()==4) 
        TEST_ASSERT(op.block(3, 2)!=0 && op.block(3, 2)->isZero()==false && op.block(3, 2)->m()==6 && op.block(3, 2)->n()==5) 


        // Limit cases.
        TAdjointBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)    
        TEST_ASSERT(op.countBlockRows()==blockCols && op.countBlockColumns()==blockRows)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==3 && op.block(0, 0)->n()==3) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==3 && op.block(0, 1)->n()==4) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()==false && op.block(0, 2)->m()==3 && op.block(0, 2)->n()==5) 
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==4 && op.block(1, 0)->n()==3) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==4 && op.block(1, 1)->n()==4) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==4 && op.block(1, 2)->n()==5) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()==false && op.block(2, 0)->m()==5 && op.block(2, 0)->n()==3) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==5 && op.block(2, 1)->n()==4) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==5 && op.block(2, 2)->n()==5) 
        TEST_ASSERT(op.block(3, 0)!=0 && op.block(3, 0)->isZero()==false && op.block(3, 0)->m()==6 && op.block(3, 0)->n()==3) 
        TEST_ASSERT(op.block(3, 1)!=0 && op.block(3, 1)->isZero()==false && op.block(3, 1)->m()==6 && op.block(3, 1)->n()==4) 
        TEST_ASSERT(op.block(3, 2)!=0 && op.block(3, 2)->isZero()==false && op.block(3, 2)->m()==6 && op.block(3, 2)->n()==5) 

        TAdjointBlockOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==n && opCopy.n()==m)    
        TEST_ASSERT(opCopy.countBlockRows()==blockCols && opCopy.countBlockColumns()==blockRows)
        TEST_ASSERT(opCopy.op() == op.op())
        TEST_ASSERT(opCopy.block(0, 0)!=0 && opCopy.block(0, 0)->isZero()==false && opCopy.block(0, 0)->m()==3 && opCopy.block(0, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(0, 1)!=0 && opCopy.block(0, 1)->isZero()==false && opCopy.block(0, 1)->m()==3 && opCopy.block(0, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(0, 2)!=0 && opCopy.block(0, 2)->isZero()==false && opCopy.block(0, 2)->m()==3 && opCopy.block(0, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(1, 0)!=0 && opCopy.block(1, 0)->isZero()==false && opCopy.block(1, 0)->m()==4 && opCopy.block(1, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(1, 1)!=0 && opCopy.block(1, 1)->isZero()==false && opCopy.block(1, 1)->m()==4 && opCopy.block(1, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(1, 2)!=0 && opCopy.block(1, 2)->isZero()==false && opCopy.block(1, 2)->m()==4 && opCopy.block(1, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(2, 0)!=0 && opCopy.block(2, 0)->isZero()==false && opCopy.block(2, 0)->m()==5 && opCopy.block(2, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(2, 1)!=0 && opCopy.block(2, 1)->isZero()==false && opCopy.block(2, 1)->m()==5 && opCopy.block(2, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(2, 2)!=0 && opCopy.block(2, 2)->isZero()==false && opCopy.block(2, 2)->m()==5 && opCopy.block(2, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(3, 0)!=0 && opCopy.block(3, 0)->isZero()==false && opCopy.block(3, 0)->m()==6 && opCopy.block(3, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(3, 1)!=0 && opCopy.block(3, 1)->isZero()==false && opCopy.block(3, 1)->m()==6 && opCopy.block(3, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(3, 2)!=0 && opCopy.block(3, 2)->isZero()==false && opCopy.block(3, 2)->m()==6 && opCopy.block(3, 2)->n()==5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testOp()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)    
        TEST_ASSERT(op.countBlockRows()==blockCols && op.countBlockColumns()==blockRows)
        TEST_ASSERT(op.op() != 0)


        // Limit cases.
        TAdjointBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testIsZero()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)    
        TEST_ASSERT(op.countBlockRows()==blockCols && op.countBlockColumns()==blockRows)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZero() == false)


        // Limit cases.
        TAdjointBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
        TEST_ASSERT(op0.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testSum()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        klab::TSmartPointer<TBlockOperator<klab::DoubleReal> > opJoint = new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators);
        TAdjointBlockOperator<klab::DoubleReal> op(opJoint); 
        TEST_ASSERT(klab::Equals(op.sum(), opJoint->sum()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testNormFrobenius()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        klab::TSmartPointer<TBlockOperator<klab::DoubleReal> > opJoint = new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators);
        TAdjointBlockOperator<klab::DoubleReal> op(opJoint); 
        TEST_ASSERT(klab::Equals(op.normFrobenius(), opJoint->normFrobenius(), 1e-6))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testSquaredNormFrobenius()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        klab::TSmartPointer<TBlockOperator<klab::DoubleReal> > opJoint = new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators);
        TAdjointBlockOperator<klab::DoubleReal> op(opJoint); 
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), opJoint->squaredNormFrobenius()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testMean()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        klab::TSmartPointer<TBlockOperator<klab::DoubleReal> > opJoint = new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators);
        TAdjointBlockOperator<klab::DoubleReal> op(opJoint); 
        TEST_ASSERT(klab::Equals(op.mean(), opJoint->mean()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testVariance()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        klab::TSmartPointer<TBlockOperator<klab::DoubleReal> > opJoint = new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators);
        TAdjointBlockOperator<klab::DoubleReal> op(opJoint); 
        TEST_ASSERT(klab::Equals(op.variance(), opJoint->variance(), 1e-6))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testCountBlockRows()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)    
        TEST_ASSERT(op.countBlockRows()==blockCols && op.countBlockColumns()==blockRows)
        TEST_ASSERT(op.op() != 0)


        // Limit cases.
        TAdjointBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)    
        TEST_ASSERT(op.countBlockRows()==blockCols && op.countBlockColumns()==blockRows)
        TEST_ASSERT(op.op() != 0)


        // Limit cases.
        TAdjointBlockOperator<klab::DoubleReal> op0(0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.op() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)    
        TEST_ASSERT(op.countBlockRows()==blockCols && op.countBlockColumns()==blockRows)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==3 && op.block(0, 0)->n()==3) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==3 && op.block(0, 1)->n()==4) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()==false && op.block(0, 2)->m()==3 && op.block(0, 2)->n()==5) 
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==4 && op.block(1, 0)->n()==3) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==4 && op.block(1, 1)->n()==4) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==4 && op.block(1, 2)->n()==5) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()==false && op.block(2, 0)->m()==5 && op.block(2, 0)->n()==3) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==5 && op.block(2, 1)->n()==4) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==5 && op.block(2, 2)->n()==5) 
        TEST_ASSERT(op.block(3, 0)!=0 && op.block(3, 0)->isZero()==false && op.block(3, 0)->m()==6 && op.block(3, 0)->n()==3) 
        TEST_ASSERT(op.block(3, 1)!=0 && op.block(3, 1)->isZero()==false && op.block(3, 1)->m()==6 && op.block(3, 1)->n()==4) 
        TEST_ASSERT(op.block(3, 2)!=0 && op.block(3, 2)->isZero()==false && op.block(3, 2)->m()==6 && op.block(3, 2)->n()==5) 


        // Limit cases.
        TAdjointBlockOperator<klab::DoubleReal> op0(0); 
        try                                     {op0.block(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(3, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(4, 2); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(4, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)    
        TEST_ASSERT(op.countBlockRows()==blockCols && op.countBlockColumns()==blockRows)
        TEST_ASSERT(op.op() != 0)
        TEST_ASSERT(op.isZeroBlock(0, 0)==false)
        TEST_ASSERT(op.isZeroBlock(0, 1)==false)
        TEST_ASSERT(op.isZeroBlock(0, 2)==false)
        TEST_ASSERT(op.isZeroBlock(1, 0)==false)
        TEST_ASSERT(op.isZeroBlock(1, 1)==false)
        TEST_ASSERT(op.isZeroBlock(1, 2)==false) 
        TEST_ASSERT(op.isZeroBlock(2, 0)==false)
        TEST_ASSERT(op.isZeroBlock(2, 1)==false)
        TEST_ASSERT(op.isZeroBlock(2, 2)==false)
        TEST_ASSERT(op.isZeroBlock(3, 0)==false)
        TEST_ASSERT(op.isZeroBlock(3, 1)==false)
        TEST_ASSERT(op.isZeroBlock(3, 2)==false)


        // Limit cases.
        TAdjointBlockOperator<klab::DoubleReal> op0(0); 
        try                                     {op0.isZeroBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(3, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(4, 2); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(4, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testInBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, m, n, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)    
        TEST_ASSERT(op.countBlockRows()==blockCols && op.countBlockColumns()==blockRows)
        TEST_ASSERT(op.op() != 0)

        klab::TSmartPointer<TOperator<klab::DoubleReal> > result = op.inBlock(0, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3) 

        result = op.inBlock(1, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(0, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(1, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(2, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(3, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==3)

        result = op.inBlock(7, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==3)

        result = op.inBlock(12, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==3)

        result = op.inBlock(17, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==3)

        result = op.inBlock(0, 4);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(2, 4);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(3, 4);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==4)

        result = op.inBlock(7, 4);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==4)

        result = op.inBlock(12, 4);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==4)

        result = op.inBlock(17, 4);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==4)

        result = op.inBlock(0, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==5)

        result = op.inBlock(2, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==5)

        result = op.inBlock(3, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5)

        result = op.inBlock(7, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==5)

        result = op.inBlock(12, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==5)

        result = op.inBlock(17, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==5)

        result = op.inBlock(17, 11);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==5)


        // Limit cases.
        TAdjointBlockOperator<klab::DoubleReal> op0(0);
        try                                     {op0.inBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(3, 12); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(18, 2); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(18, 12); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testApply()
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

        arma::Col<klab::DoubleReal> x(m);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> y0;

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


        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)

        TJointOperator<klab::DoubleReal> opJoint(blockRows, blockCols, operators);
        TEST_ASSERT(opJoint.m()==m && opJoint.n()==n)

        opJoint.applyAdjoint(x, y0);
        op.apply(x, y);
        TEST_ASSERT(y.n_rows == n)
        TEST_ASSERT(klab::Equals(y[0],  y0[0], precision))
        TEST_ASSERT(klab::Equals(y[1],  y0[1], precision))
        TEST_ASSERT(klab::Equals(y[2],  y0[2], precision))
        TEST_ASSERT(klab::Equals(y[3],  y0[3], precision))
        TEST_ASSERT(klab::Equals(y[4],  y0[4], precision))
        TEST_ASSERT(klab::Equals(y[5],  y0[5], precision))
        TEST_ASSERT(klab::Equals(y[6],  y0[6], precision))
        TEST_ASSERT(klab::Equals(y[7],  y0[7], precision))
        TEST_ASSERT(klab::Equals(y[8],  y0[8], precision))
        TEST_ASSERT(klab::Equals(y[9],  y0[9], precision))
        TEST_ASSERT(klab::Equals(y[10], y0[10], precision))
        TEST_ASSERT(klab::Equals(y[11], y0[11], precision))
        TEST_ASSERT(klab::Equals(y[12], y0[12], precision))
        TEST_ASSERT(klab::Equals(y[13], y0[13], precision))
        TEST_ASSERT(klab::Equals(y[14], y0[14], precision))
        TEST_ASSERT(klab::Equals(y[15], y0[15], precision))
        TEST_ASSERT(klab::Equals(y[16], y0[16], precision))
        TEST_ASSERT(klab::Equals(y[17], y0[17], precision))


        // Limit cases.
        try                                         {op.apply(arma::Col<klab::DoubleReal>(m-1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<klab::DoubleReal>(m+1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testApplyAdjoint()
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

        arma::Col<klab::DoubleReal> x(m);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        arma::Col<klab::DoubleReal> xr0;

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


        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
        TEST_ASSERT(op.m()==n && op.n()==m)

        TJointOperator<klab::DoubleReal> opJoint(blockRows, blockCols, operators);
        TEST_ASSERT(opJoint.m()==m && opJoint.n()==n)
        
        op.apply(x, y);
        opJoint.apply(y, xr0);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == m)
        TEST_ASSERT(klab::Equals(xr[0],  xr0[0], precision))
        TEST_ASSERT(klab::Equals(xr[1],  xr0[1], precision))
        TEST_ASSERT(klab::Equals(xr[2],  xr0[2], precision))
        TEST_ASSERT(klab::Equals(xr[3],  xr0[3], precision))
        TEST_ASSERT(klab::Equals(xr[4],  xr0[4], precision))
        TEST_ASSERT(klab::Equals(xr[5],  xr0[5], precision))
        TEST_ASSERT(klab::Equals(xr[6],  xr0[6], precision))
        TEST_ASSERT(klab::Equals(xr[7],  xr0[7], precision))
        TEST_ASSERT(klab::Equals(xr[8],  xr0[8], precision))
        TEST_ASSERT(klab::Equals(xr[9],  xr0[9], precision))
        TEST_ASSERT(klab::Equals(xr[10], xr0[10], precision))
        TEST_ASSERT(klab::Equals(xr[11], xr0[11], precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(n-1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(n+1), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdjointBlockOperatorUnitTest::testColumn()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, n, m, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
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

void KAdjointBlockOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, n, m, blockRows, blockCols);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockRows, blockCols, operators)); 
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

void KAdjointBlockOperatorUnitTest::testApplyBlockVariance()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        arma::Col<klab::DoubleReal> x(3);
        arma::Col<klab::DoubleReal> y;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;


        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, n, m, blockCols, blockRows);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockCols, blockRows, operators)); 
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        op.applyBlockVariance(x, y);
        TEST_ASSERT(y.n_rows==blockRows)
        TEST_ASSERT(klab::Equals(y[0], x[0]*op.block(0, 0)->variance() + x[1]*op.block(0, 1)->variance() + x[2]*op.block(0, 2)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[1], x[0]*op.block(1, 0)->variance() + x[1]*op.block(1, 1)->variance() + x[2]*op.block(1, 2)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[2], x[0]*op.block(2, 0)->variance() + x[1]*op.block(2, 1)->variance() + x[2]*op.block(2, 2)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[3], x[0]*op.block(3, 0)->variance() + x[1]*op.block(3, 1)->variance() + x[2]*op.block(3, 2)->variance(), precision))        
        

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

void KAdjointBlockOperatorUnitTest::testApplyBlockVarianceAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-9; 

        arma::Col<klab::DoubleReal> x(3);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;


        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        KJointOperatorUnitTest::GenerateTestOperators_01(operators, n, m, blockCols, blockRows);

        TAdjointBlockOperator<klab::DoubleReal> op(new TJointOperator<klab::DoubleReal>(blockCols, blockRows, operators));
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        op.applyBlockVariance(x, y);
        op.applyBlockVarianceAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows==blockCols)
        TEST_ASSERT(klab::Equals(xr[0], y[0]*op.block(0, 0)->variance() + y[1]*op.block(1, 0)->variance() + y[2]*op.block(2, 0)->variance() + y[3]*op.block(3, 0)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[1], y[0]*op.block(0, 1)->variance() + y[1]*op.block(1, 1)->variance() + y[2]*op.block(2, 1)->variance() + y[3]*op.block(3, 1)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[2], y[0]*op.block(0, 2)->variance() + y[1]*op.block(1, 2)->variance() + y[2]*op.block(2, 2)->variance() + y[3]*op.block(3, 2)->variance(), precision))
        

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
