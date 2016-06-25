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

#include "BlockTridiagonalOperatorUnitTest.h"
#include "../include/BlockTridiagonalOperator.h"
#include "../include/MatrixOperator.h"
#include "../include/JointOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KBlockTridiagonalOperatorUnitTest::KBlockTridiagonalOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testOperatorArrayConstructor)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testBlock)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testInBlock)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testApply)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testColumn)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testApplyBlockVariance)
    TEST_ADD(KBlockTridiagonalOperatorUnitTest::testApplyBlockVarianceAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KBlockTridiagonalOperatorUnitTest::~KBlockTridiagonalOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //
 
void KBlockTridiagonalOperatorUnitTest::testOperatorArrayConstructor()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);
        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==2 && op.block(0, 0)->n()==3) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==2 && op.block(0, 1)->n()==4) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()        && op.block(0, 2)->m()==2 && op.block(0, 2)->n()==5) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()        && op.block(0, 3)->m()==2 && op.block(0, 3)->n()==6)
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==3 && op.block(1, 0)->n()==3) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==3 && op.block(1, 1)->n()==4) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==3 && op.block(1, 2)->n()==5) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()        && op.block(1, 3)->m()==3 && op.block(1, 3)->n()==6) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()        && op.block(2, 0)->m()==4 && op.block(2, 0)->n()==3) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==4 && op.block(2, 1)->n()==4) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==4 && op.block(2, 2)->n()==5) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==4 && op.block(2, 3)->n()==6)
        TEST_ASSERT(op.block(3, 0)!=0 && op.block(3, 0)->isZero()        && op.block(3, 0)->m()==5 && op.block(3, 0)->n()==3) 
        TEST_ASSERT(op.block(3, 1)!=0 && op.block(3, 1)->isZero()        && op.block(3, 1)->m()==5 && op.block(3, 1)->n()==4) 
        TEST_ASSERT(op.block(3, 2)!=0 && op.block(3, 2)->isZero()==false && op.block(3, 2)->m()==5 && op.block(3, 2)->n()==5) 
        TEST_ASSERT(op.block(3, 3)!=0 && op.block(3, 3)->isZero()==false && op.block(3, 3)->m()==5 && op.block(3, 3)->n()==6)


        m = 0;
        n = 0;
        blockRows = 0;
        blockCols = 0;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_02(diagonal, lower, upper, m, n, blockRows, blockCols);
        TBlockTridiagonalOperator<klab::DoubleReal> op2(diagonal, lower, upper);
        TEST_ASSERT(op2.m()==m && op2.n()==n)    
        TEST_ASSERT(op2.countBlockRows()==blockRows && op2.countBlockColumns()==blockCols)
        TEST_ASSERT(op2.block(0, 0)!=0 && op2.block(0, 0)->isZero()==false && op2.block(0, 0)->m()==2 && op2.block(0, 0)->n()==3) 
        TEST_ASSERT(op2.block(0, 1)!=0 && op2.block(0, 1)->isZero()        && op2.block(0, 1)->m()==2 && op2.block(0, 1)->n()==4) 
        TEST_ASSERT(op2.block(0, 2)!=0 && op2.block(0, 2)->isZero()        && op2.block(0, 2)->m()==2 && op2.block(0, 2)->n()==5) 
        TEST_ASSERT(op2.block(0, 3)!=0 && op2.block(0, 3)->isZero()        && op2.block(0, 3)->m()==2 && op2.block(0, 3)->n()==6)
        TEST_ASSERT(op2.block(1, 0)!=0 && op2.block(1, 0)->isZero()        && op2.block(1, 0)->m()==3 && op2.block(1, 0)->n()==3) 
        TEST_ASSERT(op2.block(1, 1)!=0 && op2.block(1, 1)->isZero()==false && op2.block(1, 1)->m()==3 && op2.block(1, 1)->n()==4) 
        TEST_ASSERT(op2.block(1, 2)!=0 && op2.block(1, 2)->isZero()==false && op2.block(1, 2)->m()==3 && op2.block(1, 2)->n()==5) 
        TEST_ASSERT(op2.block(1, 3)!=0 && op2.block(1, 3)->isZero()        && op2.block(1, 3)->m()==3 && op2.block(1, 3)->n()==6) 
        TEST_ASSERT(op2.block(2, 0)!=0 && op2.block(2, 0)->isZero()        && op2.block(2, 0)->m()==4 && op2.block(2, 0)->n()==3) 
        TEST_ASSERT(op2.block(2, 1)!=0 && op2.block(2, 1)->isZero()==false && op2.block(2, 1)->m()==4 && op2.block(2, 1)->n()==4) 
        TEST_ASSERT(op2.block(2, 2)!=0 && op2.block(2, 2)->isZero()==false && op2.block(2, 2)->m()==4 && op2.block(2, 2)->n()==5) 
        TEST_ASSERT(op2.block(2, 3)!=0 && op2.block(2, 3)->isZero()==false && op2.block(2, 3)->m()==4 && op2.block(2, 3)->n()==6)
        TEST_ASSERT(op2.block(3, 0)!=0 && op2.block(3, 0)->isZero()        && op2.block(3, 0)->m()==5 && op2.block(3, 0)->n()==3) 
        TEST_ASSERT(op2.block(3, 1)!=0 && op2.block(3, 1)->isZero()        && op2.block(3, 1)->m()==5 && op2.block(3, 1)->n()==4) 
        TEST_ASSERT(op2.block(3, 2)!=0 && op2.block(3, 2)->isZero()        && op2.block(3, 2)->m()==5 && op2.block(3, 2)->n()==5) 
        TEST_ASSERT(op2.block(3, 3)!=0 && op2.block(3, 3)->isZero()==false && op2.block(3, 3)->m()==5 && op2.block(3, 3)->n()==6)


        // Limit cases.
        TBlockTridiagonalOperator<klab::DoubleReal>::TOperatorArray operator0;
        TBlockTridiagonalOperator<klab::DoubleReal> op0(operator0, operator0, operator0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KBlockTridiagonalOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);
        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==2 && op.block(0, 0)->n()==3) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==2 && op.block(0, 1)->n()==4) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()        && op.block(0, 2)->m()==2 && op.block(0, 2)->n()==5) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()        && op.block(0, 3)->m()==2 && op.block(0, 3)->n()==6)
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==3 && op.block(1, 0)->n()==3) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==3 && op.block(1, 1)->n()==4) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==3 && op.block(1, 2)->n()==5) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()        && op.block(1, 3)->m()==3 && op.block(1, 3)->n()==6) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()        && op.block(2, 0)->m()==4 && op.block(2, 0)->n()==3) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==4 && op.block(2, 1)->n()==4) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==4 && op.block(2, 2)->n()==5) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==4 && op.block(2, 3)->n()==6)
        TEST_ASSERT(op.block(3, 0)!=0 && op.block(3, 0)->isZero()        && op.block(3, 0)->m()==5 && op.block(3, 0)->n()==3) 
        TEST_ASSERT(op.block(3, 1)!=0 && op.block(3, 1)->isZero()        && op.block(3, 1)->m()==5 && op.block(3, 1)->n()==4) 
        TEST_ASSERT(op.block(3, 2)!=0 && op.block(3, 2)->isZero()==false && op.block(3, 2)->m()==5 && op.block(3, 2)->n()==5) 
        TEST_ASSERT(op.block(3, 3)!=0 && op.block(3, 3)->isZero()==false && op.block(3, 3)->m()==5 && op.block(3, 3)->n()==6)

        TBlockTridiagonalOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==m && opCopy.n()==n)    
        TEST_ASSERT(opCopy.countBlockRows()==blockRows && opCopy.countBlockColumns()==blockCols)
        TEST_ASSERT(opCopy.block(0, 0)!=0 && opCopy.block(0, 0)->isZero()==false && opCopy.block(0, 0)->m()==2 && opCopy.block(0, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(0, 1)!=0 && opCopy.block(0, 1)->isZero()==false && opCopy.block(0, 1)->m()==2 && opCopy.block(0, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(0, 2)!=0 && opCopy.block(0, 2)->isZero()        && opCopy.block(0, 2)->m()==2 && opCopy.block(0, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(0, 3)!=0 && opCopy.block(0, 3)->isZero()        && opCopy.block(0, 3)->m()==2 && opCopy.block(0, 3)->n()==6)
        TEST_ASSERT(opCopy.block(1, 0)!=0 && opCopy.block(1, 0)->isZero()==false && opCopy.block(1, 0)->m()==3 && opCopy.block(1, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(1, 1)!=0 && opCopy.block(1, 1)->isZero()==false && opCopy.block(1, 1)->m()==3 && opCopy.block(1, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(1, 2)!=0 && opCopy.block(1, 2)->isZero()==false && opCopy.block(1, 2)->m()==3 && opCopy.block(1, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(1, 3)!=0 && opCopy.block(1, 3)->isZero()        && opCopy.block(1, 3)->m()==3 && opCopy.block(1, 3)->n()==6) 
        TEST_ASSERT(opCopy.block(2, 0)!=0 && opCopy.block(2, 0)->isZero()        && opCopy.block(2, 0)->m()==4 && opCopy.block(2, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(2, 1)!=0 && opCopy.block(2, 1)->isZero()==false && opCopy.block(2, 1)->m()==4 && opCopy.block(2, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(2, 2)!=0 && opCopy.block(2, 2)->isZero()==false && opCopy.block(2, 2)->m()==4 && opCopy.block(2, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(2, 3)!=0 && opCopy.block(2, 3)->isZero()==false && opCopy.block(2, 3)->m()==4 && opCopy.block(2, 3)->n()==6)
        TEST_ASSERT(opCopy.block(3, 0)!=0 && opCopy.block(3, 0)->isZero()        && opCopy.block(3, 0)->m()==5 && opCopy.block(3, 0)->n()==3) 
        TEST_ASSERT(opCopy.block(3, 1)!=0 && opCopy.block(3, 1)->isZero()        && opCopy.block(3, 1)->m()==5 && opCopy.block(3, 1)->n()==4) 
        TEST_ASSERT(opCopy.block(3, 2)!=0 && opCopy.block(3, 2)->isZero()==false && opCopy.block(3, 2)->m()==5 && opCopy.block(3, 2)->n()==5) 
        TEST_ASSERT(opCopy.block(3, 3)!=0 && opCopy.block(3, 3)->isZero()==false && opCopy.block(3, 3)->m()==5 && opCopy.block(3, 3)->n()==6)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockTridiagonalOperatorUnitTest::testCountBlockRows()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);
        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockTridiagonalOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);
        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockTridiagonalOperatorUnitTest::testBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);
        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==2 && op.block(0, 0)->n()==3) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==2 && op.block(0, 1)->n()==4) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()        && op.block(0, 2)->m()==2 && op.block(0, 2)->n()==5) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()        && op.block(0, 3)->m()==2 && op.block(0, 3)->n()==6)
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==3 && op.block(1, 0)->n()==3) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==3 && op.block(1, 1)->n()==4) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==3 && op.block(1, 2)->n()==5) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()        && op.block(1, 3)->m()==3 && op.block(1, 3)->n()==6) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()        && op.block(2, 0)->m()==4 && op.block(2, 0)->n()==3) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==4 && op.block(2, 1)->n()==4) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==4 && op.block(2, 2)->n()==5) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==4 && op.block(2, 3)->n()==6)
        TEST_ASSERT(op.block(3, 0)!=0 && op.block(3, 0)->isZero()        && op.block(3, 0)->m()==5 && op.block(3, 0)->n()==3) 
        TEST_ASSERT(op.block(3, 1)!=0 && op.block(3, 1)->isZero()        && op.block(3, 1)->m()==5 && op.block(3, 1)->n()==4) 
        TEST_ASSERT(op.block(3, 2)!=0 && op.block(3, 2)->isZero()==false && op.block(3, 2)->m()==5 && op.block(3, 2)->n()==5) 
        TEST_ASSERT(op.block(3, 3)!=0 && op.block(3, 3)->isZero()==false && op.block(3, 3)->m()==5 && op.block(3, 3)->n()==6)


        // Limit cases.
        TBlockTridiagonalOperator<klab::DoubleReal>::TOperatorArray operator0;
        TBlockTridiagonalOperator<klab::DoubleReal> op0(operator0, operator0, operator0);
        try                                     {op0.block(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(4, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(3, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.block(4, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockTridiagonalOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);
        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)
        TEST_ASSERT(op.isZeroBlock(0, 0)==false) 
        TEST_ASSERT(op.isZeroBlock(0, 1)==false)
        TEST_ASSERT(op.isZeroBlock(0, 2))
        TEST_ASSERT(op.isZeroBlock(0, 3))
        TEST_ASSERT(op.isZeroBlock(1, 0)==false) 
        TEST_ASSERT(op.isZeroBlock(1, 1)==false)
        TEST_ASSERT(op.isZeroBlock(1, 2)==false)
        TEST_ASSERT(op.isZeroBlock(1, 3))
        TEST_ASSERT(op.isZeroBlock(2, 0))
        TEST_ASSERT(op.isZeroBlock(2, 1)==false)
        TEST_ASSERT(op.isZeroBlock(2, 2)==false)
        TEST_ASSERT(op.isZeroBlock(2, 3)==false)
        TEST_ASSERT(op.isZeroBlock(3, 0))
        TEST_ASSERT(op.isZeroBlock(3, 1))
        TEST_ASSERT(op.isZeroBlock(3, 2)==false)
        TEST_ASSERT(op.isZeroBlock(3, 3)==false)


        // Limit cases.
        TBlockTridiagonalOperator<klab::DoubleReal>::TOperatorArray operator0;
        TBlockTridiagonalOperator<klab::DoubleReal> op0(operator0, operator0, operator0);
        try                                     {op0.isZeroBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(4, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(3, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.isZeroBlock(4, 4); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockTridiagonalOperatorUnitTest::testInBlock()
{
    try
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);
        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)    
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        klab::TSmartPointer<TOperator<klab::DoubleReal> > result = op.inBlock(0, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==2 && result->n()==3) 

        result = op.inBlock(0, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==2 && result->n()==3)

        result = op.inBlock(0, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==2 && result->n()==3)

        result = op.inBlock(1, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==2 && result->n()==3) 

        result = op.inBlock(1, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==2 && result->n()==3)

        result = op.inBlock(1, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==2 && result->n()==3)

        result = op.inBlock(1, 3);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==2 && result->n()==4)

        result = op.inBlock(1, 7);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==2 && result->n()==5)

        result = op.inBlock(1, 12);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==2 && result->n()==6)

        result = op.inBlock(1, 17);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==2 && result->n()==6)

        result = op.inBlock(2, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(2, 3);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(2, 7);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==5)

        result = op.inBlock(2, 12);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==6)

        result = op.inBlock(2, 17);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==6)

        result = op.inBlock(4, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==3)

        result = op.inBlock(4, 3);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(4, 7);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==5)

        result = op.inBlock(4, 12);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==6)

        result = op.inBlock(4, 17);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==6)

        result = op.inBlock(5, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==4 && result->n()==3)

        result = op.inBlock(5, 3);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==4)

        result = op.inBlock(5, 7);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5)

        result = op.inBlock(5, 12);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==6)

        result = op.inBlock(5, 17);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==6)

        result = op.inBlock(8, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==4 && result->n()==3)

        result = op.inBlock(8, 3);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==4)

        result = op.inBlock(8, 7);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5)

        result = op.inBlock(8, 12);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==6)

        result = op.inBlock(8, 17);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==6)

        result = op.inBlock(9, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==5 && result->n()==3)

        result = op.inBlock(9, 3);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==5 && result->n()==4)

        result = op.inBlock(9, 7);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==5)

        result = op.inBlock(9, 12);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==6)

        result = op.inBlock(9, 17);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==6)

        result = op.inBlock(13, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==5 && result->n()==3)

        result = op.inBlock(13, 3);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==5 && result->n()==4)

        result = op.inBlock(13, 7);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==5)

        result = op.inBlock(13, 12);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==6)

        result = op.inBlock(13, 17);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==5 && result->n()==6)


        // Limit cases.
        TBlockTridiagonalOperator<klab::DoubleReal>::TOperatorArray operator0;
        TBlockTridiagonalOperator<klab::DoubleReal> op0(operator0, operator0, operator0);
        try                                     {op0.inBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(14, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(2, 18); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(14, 18); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockTridiagonalOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);

        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        operators.push_back(diagonal[0]);
        operators.push_back(upper[0]);
        operators.push_back(0);
        operators.push_back(0);
        operators.push_back(lower[0]);
        operators.push_back(diagonal[1]);
        operators.push_back(upper[1]);
        operators.push_back(0);
        operators.push_back(0);
        operators.push_back(lower[1]);
        operators.push_back(diagonal[2]);
        operators.push_back(upper[2]);
        operators.push_back(0);
        operators.push_back(0);
        operators.push_back(lower[2]);
        operators.push_back(diagonal[3]);

        arma::Col<klab::DoubleReal> x(n);
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
        x[12] = 13.0;
        x[13] = 14.0;
        x[14] = 15.0;
        x[15] = 16.0;
        x[16] = 17.0;
        x[17] = 18.0;


        TJointOperator<klab::DoubleReal> opJoint(blockRows, blockCols, operators);
        TEST_ASSERT(opJoint.m()==m && opJoint.n()==n)

        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)

        opJoint.apply(x, y0);
        op.apply(x, y);
        TEST_ASSERT(y0.n_rows == m)
        TEST_ASSERT(y.n_rows == m)
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

void KBlockTridiagonalOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-9; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);

        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > operators;
        operators.push_back(diagonal[0]);
        operators.push_back(upper[0]);
        operators.push_back(0);
        operators.push_back(0);
        operators.push_back(lower[0]);
        operators.push_back(diagonal[1]);
        operators.push_back(upper[1]);
        operators.push_back(0);
        operators.push_back(0);
        operators.push_back(lower[1]);
        operators.push_back(diagonal[2]);
        operators.push_back(upper[2]);
        operators.push_back(0);
        operators.push_back(0);
        operators.push_back(lower[2]);
        operators.push_back(diagonal[3]);

        arma::Col<klab::DoubleReal> x(n);
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
        x[12] = 13.0;
        x[13] = 14.0;
        x[14] = 15.0;
        x[15] = 16.0;
        x[16] = 17.0;
        x[17] = 18.0;


        TJointOperator<klab::DoubleReal> opJoint(blockRows, blockCols, operators);
        TEST_ASSERT(opJoint.m()==m && opJoint.n()==n)

        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)
        
        op.apply(x, y);
        opJoint.applyAdjoint(y, xr0);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr0.n_rows == n)
        TEST_ASSERT(xr.n_rows == n)
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
        TEST_ASSERT(klab::Equals(xr[12], xr0[12], precision))
        TEST_ASSERT(klab::Equals(xr[13], xr0[13], precision))
        TEST_ASSERT(klab::Equals(xr[14], xr0[14], precision))
        TEST_ASSERT(klab::Equals(xr[15], xr0[15], precision))
        TEST_ASSERT(klab::Equals(xr[16], xr0[16], precision))
        TEST_ASSERT(klab::Equals(xr[17], xr0[17], precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(m-1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(m+1), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockTridiagonalOperatorUnitTest::testColumn()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);

        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
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

void KBlockTridiagonalOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);

        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
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

void KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > >& diagonal, std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > >& lower, std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > >& upper, klab::UInt32& m, klab::UInt32& n, klab::UInt32& blockRows, klab::UInt32& blockCols)
{
    arma::Mat<klab::DoubleReal> matrix00(2, 3);
    arma::Mat<klab::DoubleReal> matrix11(3, 4);
    arma::Mat<klab::DoubleReal> matrix22(4, 5);
    arma::Mat<klab::DoubleReal> matrix33(5, 6);
    arma::Mat<klab::DoubleReal> matrix10(3, 3);
    arma::Mat<klab::DoubleReal> matrix21(4, 4);
    arma::Mat<klab::DoubleReal> matrix32(5, 5);
    arma::Mat<klab::DoubleReal> matrix01(2, 4);
    arma::Mat<klab::DoubleReal> matrix12(3, 5);
    arma::Mat<klab::DoubleReal> matrix23(4, 6);

    matrix00(0, 0) = 0.1;
    matrix00(0, 1) = 2.0;
    matrix00(0, 2) = 0.3;
    matrix00(1, 0) = 4.0;
    matrix00(1, 1) = 0.5;
    matrix00(1, 2) = 6.0;

    matrix11(0, 0) = 12.0;
    matrix11(0, 1) = 11.0;
    matrix11(0, 2) = 10.0;
    matrix11(0, 3) = 9.0;
    matrix11(1, 0) = 8.0;
    matrix11(1, 1) = 7.0;
    matrix11(1, 2) = 6.0;
    matrix11(1, 3) = 5.0;
    matrix11(2, 0) = 4.0;
    matrix11(2, 1) = 3.0;
    matrix11(2, 2) = 2.0;
    matrix11(2, 3) = 1.0;

    matrix22(0, 0) = 1.0;
    matrix22(0, 1) = 2.0;
    matrix22(0, 2) = 3.0;
    matrix22(0, 3) = 4.0;
    matrix22(0, 4) = 5.0;
    matrix22(1, 0) = 6.0;
    matrix22(1, 1) = 7.0;
    matrix22(1, 2) = 8.0;
    matrix22(1, 3) = 9.0;
    matrix22(1, 4) = 10.0;
    matrix22(2, 0) = 11.0;
    matrix22(2, 1) = 12.0;
    matrix22(2, 2) = 13.0;
    matrix22(2, 3) = 14.0;
    matrix22(2, 4) = 15.0;
    matrix22(3, 0) = 16.0;
    matrix22(3, 1) = 17.0;
    matrix22(3, 2) = 18.0;
    matrix22(3, 3) = 19.0;
    matrix22(3, 4) = 20.0;

    matrix33(0, 0) = 0.0;
    matrix33(0, 1) = 0.1;
    matrix33(0, 2) = 0.2;
    matrix33(0, 3) = 0.3;
    matrix33(0, 4) = 0.4;
    matrix33(0, 5) = 0.5;
    matrix33(1, 0) = 1.0;
    matrix33(1, 1) = 1.1;
    matrix33(1, 2) = 1.2;
    matrix33(1, 3) = 1.3;
    matrix33(1, 4) = 1.4;
    matrix33(1, 5) = 1.5;
    matrix33(2, 0) = 2.0;
    matrix33(2, 1) = 2.1;
    matrix33(2, 2) = 2.2;
    matrix33(2, 3) = 2.3;
    matrix33(2, 4) = 2.4;
    matrix33(2, 5) = 2.5;
    matrix33(3, 0) = 3.0;
    matrix33(3, 1) = 3.1;
    matrix33(3, 2) = 3.2;
    matrix33(3, 3) = 3.3;
    matrix33(3, 4) = 3.4;
    matrix33(3, 5) = 3.5;
    matrix33(4, 0) = 4.0;
    matrix33(4, 1) = 4.1;
    matrix33(4, 2) = 4.2;
    matrix33(4, 3) = 4.3;
    matrix33(4, 4) = 4.4;
    matrix33(4, 5) = 4.5;

    matrix10(0, 0) = 0.1;
    matrix10(0, 1) = 2.0;
    matrix10(0, 2) = 0.3;
    matrix10(1, 0) = 4.0;
    matrix10(1, 1) = 0.5;
    matrix10(1, 2) = 6.0;
    matrix10(2, 0) = 7.0;
    matrix10(2, 1) = 0.8;
    matrix10(2, 2) = 9.0;

    matrix21(0, 0) = 1.0;
    matrix21(0, 1) = 2.0;
    matrix21(0, 2) = 3.0;
    matrix21(0, 3) = 4.0;
    matrix21(1, 0) = 5.0;
    matrix21(1, 1) = 6.0;
    matrix21(1, 2) = 7.0;
    matrix21(1, 3) = 8.0;
    matrix21(2, 0) = 9.0;
    matrix21(2, 1) = 10.0;
    matrix21(2, 2) = 11.0;
    matrix21(2, 3) = 12.0;
    matrix21(3, 0) = 13.0;
    matrix21(3, 1) = 14.0;
    matrix21(3, 2) = 15.0;
    matrix21(3, 3) = 16.0;

    matrix32(0, 0) = 25.0;
    matrix32(0, 1) = 24.0;
    matrix32(0, 2) = 23.0;
    matrix32(0, 3) = 22.0;
    matrix32(0, 4) = 21.0;
    matrix32(1, 0) = 20.0;
    matrix32(1, 1) = 19.0;
    matrix32(1, 2) = 18.0;
    matrix32(1, 3) = 17.0;
    matrix32(1, 4) = 16.0;
    matrix32(2, 0) = 15.0;
    matrix32(2, 1) = 14.0;
    matrix32(2, 2) = 13.0;
    matrix32(2, 3) = 12.0;
    matrix32(2, 4) = 11.0;
    matrix32(3, 0) = 10.0;
    matrix32(3, 1) = 9.0;
    matrix32(3, 2) = 8.0;
    matrix32(3, 3) = 7.0;
    matrix32(3, 4) = 6.0;
    matrix32(4, 0) = 5.0;
    matrix32(4, 1) = 4.0;
    matrix32(4, 2) = 3.0;
    matrix32(4, 3) = 2.0;
    matrix32(4, 4) = 1.0;

    matrix01(0, 0) = 8.0;
    matrix01(0, 1) = 7.0;
    matrix01(0, 2) = 6.0;
    matrix01(0, 3) = 5.0;
    matrix01(1, 0) = 4.0;
    matrix01(1, 1) = 3.0;
    matrix01(1, 2) = 2.0;
    matrix01(1, 3) = 1.0;

    matrix12(0, 0) = 0.0;
    matrix12(0, 1) = 0.1;
    matrix12(0, 2) = 2.0;
    matrix12(0, 3) = 0.3;
    matrix12(0, 4) = 4.0;
    matrix12(1, 0) = 0.5;
    matrix12(1, 1) = 6.0;
    matrix12(1, 2) = 0.7;
    matrix12(1, 3) = 9.0;
    matrix12(1, 4) = 0.9;
    matrix12(2, 0) = 10.0;
    matrix12(2, 1) = 0.11;
    matrix12(2, 2) = 12.0;
    matrix12(2, 3) = 0.13;
    matrix12(2, 4) = 14.0;

    matrix23(0, 0) = 1.0;
    matrix23(0, 1) = 2.0;
    matrix23(0, 2) = 3.0;
    matrix23(0, 3) = 4.0;
    matrix23(0, 4) = 5.0;
    matrix23(0, 5) = 6.0;
    matrix23(1, 0) = 7.0;
    matrix23(1, 1) = 8.0;
    matrix23(1, 2) = 9.0;
    matrix23(1, 3) = 10.0;
    matrix23(1, 4) = 11.0;
    matrix23(1, 5) = 12.0;
    matrix23(2, 0) = 13.0;
    matrix23(2, 1) = 14.0;
    matrix23(2, 2) = 15.0;
    matrix23(2, 3) = 16.0;
    matrix23(2, 4) = 17.0;
    matrix23(2, 5) = 18.0;
    matrix23(3, 0) = 19.0;
    matrix23(3, 1) = 20.0;
    matrix23(3, 2) = 21.0;
    matrix23(3, 3) = 22.0;
    matrix23(3, 4) = 23.0;
    matrix23(3, 5) = 24.0;


    diagonal.clear();
    diagonal.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix00));
    diagonal.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix11));
    diagonal.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix22));
    diagonal.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix33));

    lower.clear();
    lower.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix10));
    lower.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix21));
    lower.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix32));

    upper.clear();
    upper.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix01));
    upper.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix12));
    upper.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix23));

    m = diagonal[0]->m() + diagonal[1]->m() + diagonal[2]->m() + diagonal[3]->m();
    n = diagonal[0]->n() + diagonal[1]->n() + diagonal[2]->n() + diagonal[3]->n();

    blockRows = 4;
    blockCols = 4;
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_02(std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > >& diagonal, std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > >& lower, std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > >& upper, klab::UInt32& m, klab::UInt32& n, klab::UInt32& blockRows, klab::UInt32& blockCols)
{
    arma::Mat<klab::DoubleReal> matrix00(2, 3);
    arma::Mat<klab::DoubleReal> matrix11(3, 4);
    arma::Mat<klab::DoubleReal> matrix22(4, 5);
    arma::Mat<klab::DoubleReal> matrix33(5, 6);
    arma::Mat<klab::DoubleReal> matrix21(4, 4);
    arma::Mat<klab::DoubleReal> matrix12(3, 5);
    arma::Mat<klab::DoubleReal> matrix23(4, 6);

    matrix00(0, 0) = 0.1;
    matrix00(0, 1) = 2.0;
    matrix00(0, 2) = 0.3;
    matrix00(1, 0) = 4.0;
    matrix00(1, 1) = 0.5;
    matrix00(1, 2) = 6.0;

    matrix11(0, 0) = 12.0;
    matrix11(0, 1) = 11.0;
    matrix11(0, 2) = 10.0;
    matrix11(0, 3) = 9.0;
    matrix11(1, 0) = 8.0;
    matrix11(1, 1) = 7.0;
    matrix11(1, 2) = 6.0;
    matrix11(1, 3) = 5.0;
    matrix11(2, 0) = 4.0;
    matrix11(2, 1) = 3.0;
    matrix11(2, 2) = 2.0;
    matrix11(2, 3) = 1.0;

    matrix22(0, 0) = 1.0;
    matrix22(0, 1) = 2.0;
    matrix22(0, 2) = 3.0;
    matrix22(0, 3) = 4.0;
    matrix22(0, 4) = 5.0;
    matrix22(1, 0) = 6.0;
    matrix22(1, 1) = 7.0;
    matrix22(1, 2) = 8.0;
    matrix22(1, 3) = 9.0;
    matrix22(1, 4) = 10.0;
    matrix22(2, 0) = 11.0;
    matrix22(2, 1) = 12.0;
    matrix22(2, 2) = 13.0;
    matrix22(2, 3) = 14.0;
    matrix22(2, 4) = 15.0;
    matrix22(3, 0) = 16.0;
    matrix22(3, 1) = 17.0;
    matrix22(3, 2) = 18.0;
    matrix22(3, 3) = 19.0;
    matrix22(3, 4) = 20.0;

    matrix33(0, 0) = 0.0;
    matrix33(0, 1) = 0.1;
    matrix33(0, 2) = 0.2;
    matrix33(0, 3) = 0.3;
    matrix33(0, 4) = 0.4;
    matrix33(0, 5) = 0.5;
    matrix33(1, 0) = 1.0;
    matrix33(1, 1) = 1.1;
    matrix33(1, 2) = 1.2;
    matrix33(1, 3) = 1.3;
    matrix33(1, 4) = 1.4;
    matrix33(1, 5) = 1.5;
    matrix33(2, 0) = 2.0;
    matrix33(2, 1) = 2.1;
    matrix33(2, 2) = 2.2;
    matrix33(2, 3) = 2.3;
    matrix33(2, 4) = 2.4;
    matrix33(2, 5) = 2.5;
    matrix33(3, 0) = 3.0;
    matrix33(3, 1) = 3.1;
    matrix33(3, 2) = 3.2;
    matrix33(3, 3) = 3.3;
    matrix33(3, 4) = 3.4;
    matrix33(3, 5) = 3.5;
    matrix33(4, 0) = 4.0;
    matrix33(4, 1) = 4.1;
    matrix33(4, 2) = 4.2;
    matrix33(4, 3) = 4.3;
    matrix33(4, 4) = 4.4;
    matrix33(4, 5) = 4.5;

    matrix21(0, 0) = 1.0;
    matrix21(0, 1) = 2.0;
    matrix21(0, 2) = 3.0;
    matrix21(0, 3) = 4.0;
    matrix21(1, 0) = 5.0;
    matrix21(1, 1) = 6.0;
    matrix21(1, 2) = 7.0;
    matrix21(1, 3) = 8.0;
    matrix21(2, 0) = 9.0;
    matrix21(2, 1) = 10.0;
    matrix21(2, 2) = 11.0;
    matrix21(2, 3) = 12.0;
    matrix21(3, 0) = 13.0;
    matrix21(3, 1) = 14.0;
    matrix21(3, 2) = 15.0;
    matrix21(3, 3) = 16.0;

    matrix12(0, 0) = 0.0;
    matrix12(0, 1) = 0.1;
    matrix12(0, 2) = 2.0;
    matrix12(0, 3) = 0.3;
    matrix12(0, 4) = 4.0;
    matrix12(1, 0) = 0.5;
    matrix12(1, 1) = 6.0;
    matrix12(1, 2) = 0.7;
    matrix12(1, 3) = 9.0;
    matrix12(1, 4) = 0.9;
    matrix12(2, 0) = 10.0;
    matrix12(2, 1) = 0.11;
    matrix12(2, 2) = 12.0;
    matrix12(2, 3) = 0.13;
    matrix12(2, 4) = 14.0;

    matrix23(0, 0) = 1.0;
    matrix23(0, 1) = 2.0;
    matrix23(0, 2) = 3.0;
    matrix23(0, 3) = 4.0;
    matrix23(0, 4) = 5.0;
    matrix23(0, 5) = 6.0;
    matrix23(1, 0) = 7.0;
    matrix23(1, 1) = 8.0;
    matrix23(1, 2) = 9.0;
    matrix23(1, 3) = 10.0;
    matrix23(1, 4) = 11.0;
    matrix23(1, 5) = 12.0;
    matrix23(2, 0) = 13.0;
    matrix23(2, 1) = 14.0;
    matrix23(2, 2) = 15.0;
    matrix23(2, 3) = 16.0;
    matrix23(2, 4) = 17.0;
    matrix23(2, 5) = 18.0;
    matrix23(3, 0) = 19.0;
    matrix23(3, 1) = 20.0;
    matrix23(3, 2) = 21.0;
    matrix23(3, 3) = 22.0;
    matrix23(3, 4) = 23.0;
    matrix23(3, 5) = 24.0;


    diagonal.clear();
    diagonal.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix00));
    diagonal.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix11));
    diagonal.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix22));
    diagonal.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix33));

    lower.clear();
    lower.push_back(0);
    lower.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix21));

    upper.clear();
    upper.push_back(0);
    upper.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix12));
    upper.push_back(new kl1p::TMatrixOperator<klab::DoubleReal>(matrix23));

    m = diagonal[0]->m() + diagonal[1]->m() + diagonal[2]->m() + diagonal[3]->m();
    n = diagonal[0]->n() + diagonal[1]->n() + diagonal[2]->n() + diagonal[3]->n();

    blockRows = 4;
    blockCols = 4;
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockTridiagonalOperatorUnitTest::testApplyBlockVariance()
{
    try
    {
        klab::DoubleReal precision = 1e-12; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);

        arma::Col<klab::DoubleReal> x(blockCols);
        arma::Col<klab::DoubleReal> y;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;


        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        op.applyBlockVariance(x, y);
        TEST_ASSERT(y.n_rows==blockRows)
        TEST_ASSERT(klab::Equals(y[0], x[0]*op.block(0, 0)->variance() + x[1]*op.block(0, 1)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[1], x[0]*op.block(1, 0)->variance() + x[1]*op.block(1, 1)->variance() + x[2]*op.block(1, 2)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[2], x[1]*op.block(2, 1)->variance() + x[2]*op.block(2, 2)->variance() + x[3]*op.block(2, 3)->variance(), precision))
        TEST_ASSERT(klab::Equals(y[3], x[2]*op.block(3, 2)->variance() + x[3]*op.block(3, 3)->variance(), precision))
        

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

void KBlockTridiagonalOperatorUnitTest::testApplyBlockVarianceAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-9; 

        klab::UInt32 m = 0;
        klab::UInt32 n = 0;
        klab::UInt32 blockRows = 0;
        klab::UInt32 blockCols = 0;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > diagonal;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > lower;
        std::vector<klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > > upper;
        KBlockTridiagonalOperatorUnitTest::GenerateTestOperators_01(diagonal, lower, upper, m, n, blockRows, blockCols);

        arma::Col<klab::DoubleReal> x(blockCols);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;


        TBlockTridiagonalOperator<klab::DoubleReal> op(diagonal, lower, upper);
        TEST_ASSERT(op.m()==m && op.n()==n)
        TEST_ASSERT(op.countBlockRows()==blockRows && op.countBlockColumns()==blockCols)

        op.applyBlockVariance(x, y);
        op.applyBlockVarianceAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows==blockCols)
        TEST_ASSERT(klab::Equals(xr[0], y[0]*op.block(0, 0)->variance() + y[1]*op.block(1, 0)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[1], y[0]*op.block(0, 1)->variance() + y[1]*op.block(1, 1)->variance() + y[2]*op.block(2, 1)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[2], y[1]*op.block(1, 2)->variance() + y[2]*op.block(2, 2)->variance() + y[3]*op.block(3, 2)->variance(), precision))
        TEST_ASSERT(klab::Equals(xr[3], y[2]*op.block(2, 3)->variance() + y[3]*op.block(3, 3)->variance(), precision))
        

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
