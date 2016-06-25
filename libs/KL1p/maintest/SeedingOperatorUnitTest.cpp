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

#include "SeedingOperatorUnitTest.h"
#include "../include/SeedingOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KSeedingOperatorUnitTest::KSeedingOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KSeedingOperatorUnitTest::testConstructor) 
    TEST_ADD(KSeedingOperatorUnitTest::testConstructor2) 
    TEST_ADD(KSeedingOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KSeedingOperatorUnitTest::testCountSeededBlocks)
    TEST_ADD(KSeedingOperatorUnitTest::testM0)
    TEST_ADD(KSeedingOperatorUnitTest::testN0)
    TEST_ADD(KSeedingOperatorUnitTest::testMb)
    TEST_ADD(KSeedingOperatorUnitTest::testNb)
    TEST_ADD(KSeedingOperatorUnitTest::testDiagonalVariance)
    TEST_ADD(KSeedingOperatorUnitTest::testLowerVariance)
    TEST_ADD(KSeedingOperatorUnitTest::testUpperVariance)
    TEST_ADD(KSeedingOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KSeedingOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KSeedingOperatorUnitTest::testBlock)
    TEST_ADD(KSeedingOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KSeedingOperatorUnitTest::testInBlock)
    TEST_ADD(KSeedingOperatorUnitTest::testApply)
    TEST_ADD(KSeedingOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KSeedingOperatorUnitTest::testColumn)
    TEST_ADD(KSeedingOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KSeedingOperatorUnitTest::~KSeedingOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testConstructor()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  


        // Limit cases.
        TSeedingOperator<klab::DoubleReal> op0(0, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)    
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.countSeededBlocks() == 0)  
        TEST_ASSERT(op0.m0() == 4)  
        TEST_ASSERT(op0.n0() == 5)  
        TEST_ASSERT(op0.mb() == 3)  
        TEST_ASSERT(op0.nb() == 4)  
        TEST_ASSERT(klab::Equals(op0.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op0.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op0.upperVariance(), 10.0)) 

        TSeedingOperator<klab::DoubleReal> op00(8, 0, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op00.m()==0 && op00.n()==0)    
        TEST_ASSERT(op00.countBlockRows()==0 && op00.countBlockColumns()==0)
        TEST_ASSERT(op00.countSeededBlocks() == 0)  
        TEST_ASSERT(op00.m0() == 0)  
        TEST_ASSERT(op00.n0() == 5)  
        TEST_ASSERT(op00.mb() == 3)  
        TEST_ASSERT(op00.nb() == 4)  
        TEST_ASSERT(klab::Equals(op00.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op00.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op00.upperVariance(), 10.0))

        TSeedingOperator<klab::DoubleReal> op000(8, 4, 0, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op000.m()==0 && op000.n()==0)    
        TEST_ASSERT(op000.countBlockRows()==0 && op000.countBlockColumns()==0)
        TEST_ASSERT(op000.countSeededBlocks() == 0)  
        TEST_ASSERT(op000.m0() == 4)  
        TEST_ASSERT(op000.n0() == 0)  
        TEST_ASSERT(op000.mb() == 3)  
        TEST_ASSERT(op000.nb() == 4)  
        TEST_ASSERT(klab::Equals(op000.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op000.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op000.upperVariance(), 10.0))

        TSeedingOperator<klab::DoubleReal> op0000(8, 0, 0, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op0000.m()==0 && op0000.n()==0)    
        TEST_ASSERT(op0000.countBlockRows()==0 && op0000.countBlockColumns()==0)
        TEST_ASSERT(op0000.countSeededBlocks() == 0)  
        TEST_ASSERT(op0000.m0() == 0)  
        TEST_ASSERT(op0000.n0() == 0)  
        TEST_ASSERT(op0000.mb() == 3)  
        TEST_ASSERT(op0000.nb() == 4)  
        TEST_ASSERT(klab::Equals(op0000.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op0000.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op0000.upperVariance(), 10.0))

        TSeedingOperator<klab::DoubleReal> op1(1, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op1.m()==4 && op1.n()==5)    
        TEST_ASSERT(op1.countBlockRows()==1 && op1.countBlockColumns()==1)
        TEST_ASSERT(op1.countSeededBlocks() == 1)  
        TEST_ASSERT(op1.m0() == 4)  
        TEST_ASSERT(op1.n0() == 5)  
        TEST_ASSERT(op1.mb() == 3)  
        TEST_ASSERT(op1.nb() == 4)  
        TEST_ASSERT(klab::Equals(op1.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op1.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op1.upperVariance(), 10.0))

        TSeedingOperator<klab::DoubleReal> op10(8, 4, 5, 0, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op10.m()==4 && op10.n()==5)    
        TEST_ASSERT(op10.countBlockRows()==1 && op10.countBlockColumns()==1)
        TEST_ASSERT(op10.countSeededBlocks() == 1)  
        TEST_ASSERT(op10.m0() == 4)  
        TEST_ASSERT(op10.n0() == 5)  
        TEST_ASSERT(op10.mb() == 0)  
        TEST_ASSERT(op10.nb() == 4)  
        TEST_ASSERT(klab::Equals(op10.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op10.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op10.upperVariance(), 10.0))

        TSeedingOperator<klab::DoubleReal> op100(8, 4, 5, 3, 0, 1.0, 0.1, 10.0);
        TEST_ASSERT(op100.m()==4 && op100.n()==5)    
        TEST_ASSERT(op100.countBlockRows()==1 && op100.countBlockColumns()==1)
        TEST_ASSERT(op100.countSeededBlocks() == 1)  
        TEST_ASSERT(op100.m0() == 4)  
        TEST_ASSERT(op100.n0() == 5)  
        TEST_ASSERT(op100.mb() == 3)  
        TEST_ASSERT(op100.nb() == 0)  
        TEST_ASSERT(klab::Equals(op100.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op100.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op100.upperVariance(), 10.0))

        TSeedingOperator<klab::DoubleReal> op1000(8, 4, 5, 0, 0, 1.0, 0.1, 10.0);
        TEST_ASSERT(op1000.m()==4 && op1000.n()==5)    
        TEST_ASSERT(op1000.countBlockRows()==1 && op1000.countBlockColumns()==1)
        TEST_ASSERT(op1000.countSeededBlocks() == 1)  
        TEST_ASSERT(op1000.m0() == 4)  
        TEST_ASSERT(op1000.n0() == 5)  
        TEST_ASSERT(op1000.mb() == 0)  
        TEST_ASSERT(op1000.nb() == 0)  
        TEST_ASSERT(klab::Equals(op1000.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op1000.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op1000.upperVariance(), 10.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testConstructor2()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(32, 4, 0.5, 0.25, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==10 && op.n()==32)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 8)  
        TEST_ASSERT(op.mb() == 2)  
        TEST_ASSERT(op.nb() == 8)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  

        TSeedingOperator<klab::DoubleReal> op2(32, 5, 0.5, 0.25, 1.0, 0.1, 10.0);
        TEST_ASSERT(op2.m()==8 && op2.n()==32)    
        TEST_ASSERT(op2.countBlockRows()==5 && op2.countBlockColumns()==5)
        TEST_ASSERT(op2.countSeededBlocks() == 5)  
        TEST_ASSERT(op2.m0() == 4)  
        TEST_ASSERT(op2.n0() == 8)  
        TEST_ASSERT(op2.mb() == 1)  
        TEST_ASSERT(op2.nb() == 6)  
        TEST_ASSERT(klab::Equals(op2.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op2.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op2.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KSeedingOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  

        TSeedingOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==25 && opCopy.n()==33)    
        TEST_ASSERT(opCopy.countBlockRows()==8 && opCopy.countBlockColumns()==8)
        TEST_ASSERT(opCopy.countSeededBlocks() == 8)  
        TEST_ASSERT(opCopy.m0() == 4)  
        TEST_ASSERT(opCopy.n0() == 5)  
        TEST_ASSERT(opCopy.mb() == 3)  
        TEST_ASSERT(opCopy.nb() == 4)  
        TEST_ASSERT(klab::Equals(opCopy.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(opCopy.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(opCopy.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testCountSeededBlocks()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testM0()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testN0()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testMb()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testNb()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testDiagonalVariance()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testLowerVariance()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testUpperVariance()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testCountBlockRows()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)    
        TEST_ASSERT(op.countBlockRows()==8 && op.countBlockColumns()==8)
        TEST_ASSERT(op.countSeededBlocks() == 8)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testBlock()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(4, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==13 && op.n()==17)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==4 && op.block(0, 0)->n()==5 && klab::Equals(op.block(0, 0)->variance(), 1.0)) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==4 && op.block(0, 1)->n()==4 && klab::Equals(op.block(0, 1)->variance(), 10.0)) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()        && op.block(0, 2)->m()==4 && op.block(0, 2)->n()==4 && klab::Equals(op.block(0, 2)->variance(), 0.0)) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()        && op.block(0, 3)->m()==4 && op.block(0, 3)->n()==4 && klab::Equals(op.block(0, 3)->variance(), 0.0))
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==3 && op.block(1, 0)->n()==5 && klab::Equals(op.block(1, 0)->variance(), 0.1)) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==3 && op.block(1, 1)->n()==4 && klab::Equals(op.block(1, 1)->variance(), 1.0)) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==3 && op.block(1, 2)->n()==4 && klab::Equals(op.block(1, 2)->variance(), 10.0)) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()        && op.block(1, 3)->m()==3 && op.block(1, 3)->n()==4 && klab::Equals(op.block(1, 3)->variance(), 0.0)) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()        && op.block(2, 0)->m()==3 && op.block(2, 0)->n()==5 && klab::Equals(op.block(2, 0)->variance(), 0.0)) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==3 && op.block(2, 1)->n()==4 && klab::Equals(op.block(2, 1)->variance(), 0.1)) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==3 && op.block(2, 2)->n()==4 && klab::Equals(op.block(2, 2)->variance(), 1.0)) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==3 && op.block(2, 3)->n()==4 && klab::Equals(op.block(2, 3)->variance(), 10.0))
        TEST_ASSERT(op.block(3, 0)!=0 && op.block(3, 0)->isZero()        && op.block(3, 0)->m()==3 && op.block(3, 0)->n()==5 && klab::Equals(op.block(3, 0)->variance(), 0.0)) 
        TEST_ASSERT(op.block(3, 1)!=0 && op.block(3, 1)->isZero()        && op.block(3, 1)->m()==3 && op.block(3, 1)->n()==4 && klab::Equals(op.block(3, 1)->variance(), 0.0)) 
        TEST_ASSERT(op.block(3, 2)!=0 && op.block(3, 2)->isZero()==false && op.block(3, 2)->m()==3 && op.block(3, 2)->n()==4 && klab::Equals(op.block(3, 2)->variance(), 0.1)) 
        TEST_ASSERT(op.block(3, 3)!=0 && op.block(3, 3)->isZero()==false && op.block(3, 3)->m()==3 && op.block(3, 3)->n()==4 && klab::Equals(op.block(3, 3)->variance(), 1.0))


        // Limit cases.
        TSeedingOperator<klab::DoubleReal> op0(0, 4, 5, 3, 4, 1.0, 0.1, 10.0);
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

void KSeedingOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(4, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==13 && op.n()==17)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  
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
        TSeedingOperator<klab::DoubleReal> op0(0, 4, 5, 3, 4, 1.0, 0.1, 10.0);
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

void KSeedingOperatorUnitTest::testInBlock()
{
    try
    {
        TSeedingOperator<klab::DoubleReal> op(4, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==13 && op.n()==17)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 4)  
        TEST_ASSERT(op.n0() == 5)  
        TEST_ASSERT(op.mb() == 3)  
        TEST_ASSERT(op.nb() == 4)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0))  

        klab::TSmartPointer<TOperator<klab::DoubleReal> > result = op.inBlock(0, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5) 

        result = op.inBlock(0, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5)

        result = op.inBlock(0, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5)

        result = op.inBlock(1, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5) 

        result = op.inBlock(1, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5)

        result = op.inBlock(1, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==5)

        result = op.inBlock(1, 5);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==4 && result->n()==4)

        result = op.inBlock(1, 9);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==4 && result->n()==4)

        result = op.inBlock(1, 13);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==4 && result->n()==4)

        result = op.inBlock(1, 16);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==4 && result->n()==4)

        result = op.inBlock(4, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==5)

        result = op.inBlock(4, 5);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(4, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(4, 13);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==4)

        result = op.inBlock(4, 16);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==4)

        result = op.inBlock(5, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==5)

        result = op.inBlock(5, 5);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(5, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(5, 13);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==4)

        result = op.inBlock(5, 16);
        TEST_ASSERT(result!=0 && result->isZero()  && result->m()==3 && result->n()==4)

        result = op.inBlock(7, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==5)

        result = op.inBlock(7, 5);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(7, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(7, 13);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(7, 16);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(10, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==5)

        result = op.inBlock(10, 5);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==4)

        result = op.inBlock(10, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(10, 13);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(10, 16);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(12, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==5)

        result = op.inBlock(12, 5);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==3 && result->n()==4)

        result = op.inBlock(12, 9);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(12, 13);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)

        result = op.inBlock(12, 16);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==3 && result->n()==4)


        // Limit cases.
        TSeedingOperator<klab::DoubleReal> op0(0, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        try                                     {op0.inBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(13, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(2, 17); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(13, 17); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testApply()
{
    try
    {
        klab::KRandom::Instance().setSeed(12345);
        klab::DoubleReal precision = 1e-9; 

        arma::Col<klab::DoubleReal> x(33);
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
        x[18] = 19.0;
        x[19] = 20.0;
        x[20] = 21.0;
        x[21] = 22.0;
        x[22] = 23.0;
        x[23] = 24.0;
        x[24] = 25.0;
        x[25] = 26.0;
        x[26] = 27.0;
        x[27] = 28.0;
        x[28] = 29.0;
        x[29] = 30.0;
        x[30] = 31.0;
        x[31] = 32.0;
        x[32] = 33.0;


        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 25)

        TEST_ASSERT(klab::Equals(y[0],   8.8720368320549561, precision))
        TEST_ASSERT(klab::Equals(y[1],   0.17407017816392578, precision))
        TEST_ASSERT(klab::Equals(y[2],  -6.0935783182554122, precision))
        TEST_ASSERT(klab::Equals(y[3],  -3.5125190318202812, precision))
        TEST_ASSERT(klab::Equals(y[4],   0.98824427424552574, precision))
        TEST_ASSERT(klab::Equals(y[5],   8.4180374154240241, precision))
        TEST_ASSERT(klab::Equals(y[6],  -12.236079954695107, precision))
        TEST_ASSERT(klab::Equals(y[7],   42.001829499773372, precision))
        TEST_ASSERT(klab::Equals(y[8],  -23.11313788297354, precision))
        TEST_ASSERT(klab::Equals(y[9],   6.8040438696192087, precision))
        TEST_ASSERT(klab::Equals(y[10], -12.671533973697976, precision))
        TEST_ASSERT(klab::Equals(y[11],  8.080980578297261, precision))
        TEST_ASSERT(klab::Equals(y[12],  15.199698348178064, precision))
        TEST_ASSERT(klab::Equals(y[13],  21.606798311160972, precision))
        TEST_ASSERT(klab::Equals(y[14],  42.445116426545511, precision))
        TEST_ASSERT(klab::Equals(y[15], -8.342525117211947, precision))
        TEST_ASSERT(klab::Equals(y[16],  18.996583175745439, precision))
        TEST_ASSERT(klab::Equals(y[17], -27.808285687912935, precision))
        TEST_ASSERT(klab::Equals(y[18],  27.76203308681098, precision))
        TEST_ASSERT(klab::Equals(y[19], -55.6700217698599, precision))
        TEST_ASSERT(klab::Equals(y[20], -46.754059930407436, precision))
        TEST_ASSERT(klab::Equals(y[21], -14.021292215149979, precision))
        TEST_ASSERT(klab::Equals(y[22],  1.9031821614133497, precision))
        TEST_ASSERT(klab::Equals(y[23],  3.8715384457880555, precision))
        TEST_ASSERT(klab::Equals(y[24], -2.0849402039070597, precision))


        // Limit cases.
        try                                         {op.apply(arma::Col<klab::DoubleReal>(32), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<klab::DoubleReal>(34), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::KRandom::Instance().setSeed(12345);
        klab::DoubleReal precision = 1e-9; 

        arma::Col<klab::DoubleReal> x(33);
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
        x[18] = 19.0;
        x[19] = 20.0;
        x[20] = 21.0;
        x[21] = 22.0;
        x[22] = 23.0;
        x[23] = 24.0;
        x[24] = 25.0;
        x[25] = 26.0;
        x[26] = 27.0;
        x[27] = 28.0;
        x[28] = 29.0;
        x[29] = 30.0;
        x[30] = 31.0;
        x[31] = 32.0;
        x[32] = 33.0;


        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==25 && op.n()==33)

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 33)

        TEST_ASSERT(klab::Equals(xr[0],   8.0211484545285021, precision))
        TEST_ASSERT(klab::Equals(xr[1],  -6.1009841374233833, precision))
        TEST_ASSERT(klab::Equals(xr[2],  -0.63867034098961928, precision))
        TEST_ASSERT(klab::Equals(xr[3],  -2.5004375125900342, precision))
        TEST_ASSERT(klab::Equals(xr[4],   0.35478359410629468, precision))
        TEST_ASSERT(klab::Equals(xr[5],   4.0662306502583903, precision))
        TEST_ASSERT(klab::Equals(xr[6],   2.1320031324194479, precision))
        TEST_ASSERT(klab::Equals(xr[7],   0.6467294831251742, precision))
        TEST_ASSERT(klab::Equals(xr[8],   7.7684168588274192, precision))
        TEST_ASSERT(klab::Equals(xr[9],   23.281900256384692, precision))
        TEST_ASSERT(klab::Equals(xr[10],  8.7501891978602089, precision))
        TEST_ASSERT(klab::Equals(xr[11],  10.270031108740961, precision))
        TEST_ASSERT(klab::Equals(xr[12], -0.83617017909650038, precision))
        TEST_ASSERT(klab::Equals(xr[13],  51.947011224742361, precision))
        TEST_ASSERT(klab::Equals(xr[14],  54.882142981731697, precision))
        TEST_ASSERT(klab::Equals(xr[15],  3.6355236013952128, precision))
        TEST_ASSERT(klab::Equals(xr[16],  44.336294639096209, precision))
        TEST_ASSERT(klab::Equals(xr[17],  18.974245079404984, precision))
        TEST_ASSERT(klab::Equals(xr[18], -1.1803647122504266, precision))
        TEST_ASSERT(klab::Equals(xr[19],  9.5233054038444251, precision))
        TEST_ASSERT(klab::Equals(xr[20], -4.7057643553538329, precision))
        TEST_ASSERT(klab::Equals(xr[21],  11.959443859928957, precision))
        TEST_ASSERT(klab::Equals(xr[22],  16.148549340897731, precision))
        TEST_ASSERT(klab::Equals(xr[23],  54.145029717506176, precision))
        TEST_ASSERT(klab::Equals(xr[24],  22.641389162074542, precision))
        TEST_ASSERT(klab::Equals(xr[25],  24.064395204451841, precision))
        TEST_ASSERT(klab::Equals(xr[26],  6.7393932633206326, precision))
        TEST_ASSERT(klab::Equals(xr[27],  79.381028742177975, precision))
        TEST_ASSERT(klab::Equals(xr[28],  12.86975170226037, precision))
        TEST_ASSERT(klab::Equals(xr[29],  38.209627030964604, precision))
        TEST_ASSERT(klab::Equals(xr[30],  21.154998044650551, precision))
        TEST_ASSERT(klab::Equals(xr[31],  86.278710129280327, precision))
        TEST_ASSERT(klab::Equals(xr[32], -26.736658492822791, precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(24), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(26), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSeedingOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 25;
        klab::UInt32 n = 33;
        klab::DoubleReal precision = 1e-12; 
        
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
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

void KSeedingOperatorUnitTest::testColumnAdjoint()
{
    try
    {       
        klab::UInt32 m = 25;
        klab::UInt32 n = 33;
        klab::DoubleReal precision = 1e-12; 
        
        TSeedingOperator<klab::DoubleReal> op(8, 4, 5, 3, 4, 1.0, 0.1, 10.0);
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
