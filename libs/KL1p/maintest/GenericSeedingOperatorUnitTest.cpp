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

#include "GenericSeedingOperatorUnitTest.h"
#include "../include/GenericSeedingOperator.h"
#include "../include/WalshHadamard1DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KGenericSeedingOperatorUnitTest::KGenericSeedingOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KGenericSeedingOperatorUnitTest::testConstructor) 
    TEST_ADD(KGenericSeedingOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KGenericSeedingOperatorUnitTest::testCountSeededBlocks)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testM0)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testMb)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testDiagonalVariance)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testLowerVariance)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testUpperVariance)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testBlock)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testInBlock)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testApply)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testColumn)
    TEST_ADD(KGenericSeedingOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KGenericSeedingOperatorUnitTest::~KGenericSeedingOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGenericSeedingOperatorUnitTest::testConstructor()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0)) 


        // Limit cases.
        TGenericSeedingOperator<klab::DoubleReal> op0(0, 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)    
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.countSeededBlocks() == 0)  
        TEST_ASSERT(op0.m0() == 8)   
        TEST_ASSERT(op0.mb() == 6)  
        TEST_ASSERT(klab::Equals(op0.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op0.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op0.upperVariance(), 10.0)) 

        TGenericSeedingOperator<klab::DoubleReal> op01(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 0, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op0.m()==0 && op0.n()==0)    
        TEST_ASSERT(op0.countBlockRows()==0 && op0.countBlockColumns()==0)
        TEST_ASSERT(op0.countSeededBlocks() == 0)  
        TEST_ASSERT(op0.m0() == 8)   
        TEST_ASSERT(op0.mb() == 6)  
        TEST_ASSERT(klab::Equals(op0.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op0.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op0.upperVariance(), 10.0)) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KGenericSeedingOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0)) 

        TGenericSeedingOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==26 && opCopy.n()==64)    
        TEST_ASSERT(opCopy.countBlockRows()==4 && opCopy.countBlockColumns()==4)
        TEST_ASSERT(opCopy.countSeededBlocks() == 4)  
        TEST_ASSERT(opCopy.m0() == 8)   
        TEST_ASSERT(opCopy.mb() == 6)  
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

void KGenericSeedingOperatorUnitTest::testCountSeededBlocks()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
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

void KGenericSeedingOperatorUnitTest::testM0()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
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

void KGenericSeedingOperatorUnitTest::testMb()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
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

void KGenericSeedingOperatorUnitTest::testDiagonalVariance()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
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

void KGenericSeedingOperatorUnitTest::testLowerVariance()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
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

void KGenericSeedingOperatorUnitTest::testUpperVariance()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
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

void KGenericSeedingOperatorUnitTest::testCountBlockRows()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
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

void KGenericSeedingOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
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

void KGenericSeedingOperatorUnitTest::testBlock()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0)) 
        TEST_ASSERT(op.block(0, 0)!=0 && op.block(0, 0)->isZero()==false && op.block(0, 0)->m()==8 && op.block(0, 0)->n()==16 && klab::Equals(op.block(0, 0)->variance(), 1.0)) 
        TEST_ASSERT(op.block(0, 1)!=0 && op.block(0, 1)->isZero()==false && op.block(0, 1)->m()==8 && op.block(0, 1)->n()==16 && klab::Equals(op.block(0, 1)->variance(), 10.0)) 
        TEST_ASSERT(op.block(0, 2)!=0 && op.block(0, 2)->isZero()        && op.block(0, 2)->m()==8 && op.block(0, 2)->n()==16 && klab::Equals(op.block(0, 2)->variance(), 0.0)) 
        TEST_ASSERT(op.block(0, 3)!=0 && op.block(0, 3)->isZero()        && op.block(0, 3)->m()==8 && op.block(0, 3)->n()==16 && klab::Equals(op.block(0, 3)->variance(), 0.0))
        TEST_ASSERT(op.block(1, 0)!=0 && op.block(1, 0)->isZero()==false && op.block(1, 0)->m()==6 && op.block(1, 0)->n()==16 && klab::Equals(op.block(1, 0)->variance(), 0.1)) 
        TEST_ASSERT(op.block(1, 1)!=0 && op.block(1, 1)->isZero()==false && op.block(1, 1)->m()==6 && op.block(1, 1)->n()==16 && klab::Equals(op.block(1, 1)->variance(), 1.0)) 
        TEST_ASSERT(op.block(1, 2)!=0 && op.block(1, 2)->isZero()==false && op.block(1, 2)->m()==6 && op.block(1, 2)->n()==16 && klab::Equals(op.block(1, 2)->variance(), 10.0)) 
        TEST_ASSERT(op.block(1, 3)!=0 && op.block(1, 3)->isZero()        && op.block(1, 3)->m()==6 && op.block(1, 3)->n()==16 && klab::Equals(op.block(1, 3)->variance(), 0.0)) 
        TEST_ASSERT(op.block(2, 0)!=0 && op.block(2, 0)->isZero()        && op.block(2, 0)->m()==6 && op.block(2, 0)->n()==16 && klab::Equals(op.block(2, 0)->variance(), 0.0)) 
        TEST_ASSERT(op.block(2, 1)!=0 && op.block(2, 1)->isZero()==false && op.block(2, 1)->m()==6 && op.block(2, 1)->n()==16 && klab::Equals(op.block(2, 1)->variance(), 0.1)) 
        TEST_ASSERT(op.block(2, 2)!=0 && op.block(2, 2)->isZero()==false && op.block(2, 2)->m()==6 && op.block(2, 2)->n()==16 && klab::Equals(op.block(2, 2)->variance(), 1.0)) 
        TEST_ASSERT(op.block(2, 3)!=0 && op.block(2, 3)->isZero()==false && op.block(2, 3)->m()==6 && op.block(2, 3)->n()==16 && klab::Equals(op.block(2, 3)->variance(), 10.0))
        TEST_ASSERT(op.block(3, 0)!=0 && op.block(3, 0)->isZero()        && op.block(3, 0)->m()==6 && op.block(3, 0)->n()==16 && klab::Equals(op.block(3, 0)->variance(), 0.0)) 
        TEST_ASSERT(op.block(3, 1)!=0 && op.block(3, 1)->isZero()        && op.block(3, 1)->m()==6 && op.block(3, 1)->n()==16 && klab::Equals(op.block(3, 1)->variance(), 0.0)) 
        TEST_ASSERT(op.block(3, 2)!=0 && op.block(3, 2)->isZero()==false && op.block(3, 2)->m()==6 && op.block(3, 2)->n()==16 && klab::Equals(op.block(3, 2)->variance(), 0.1)) 
        TEST_ASSERT(op.block(3, 3)!=0 && op.block(3, 3)->isZero()==false && op.block(3, 3)->m()==6 && op.block(3, 3)->n()==16 && klab::Equals(op.block(3, 3)->variance(), 1.0))


        // Limit cases.
        TGenericSeedingOperator<klab::DoubleReal> op0(0, 4, 8, 6, 1.0, 0.1, 10.0);
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

void KGenericSeedingOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
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
        TGenericSeedingOperator<klab::DoubleReal> op0(0, 4, 8, 6, 1.0, 0.1, 10.0);
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

void KGenericSeedingOperatorUnitTest::testInBlock()
{
    try
    {
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    
        TEST_ASSERT(op.countBlockRows()==4 && op.countBlockColumns()==4)
        TEST_ASSERT(op.countSeededBlocks() == 4)  
        TEST_ASSERT(op.m0() == 8)   
        TEST_ASSERT(op.mb() == 6)  
        TEST_ASSERT(klab::Equals(op.diagonalVariance(), 1.0))  
        TEST_ASSERT(klab::Equals(op.lowerVariance(), 0.1))  
        TEST_ASSERT(klab::Equals(op.upperVariance(), 10.0)) 

        klab::TSmartPointer<TOperator<klab::DoubleReal> > result = op.inBlock(0, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==16) 

        result = op.inBlock(0, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==16)

        result = op.inBlock(0, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==16)

        result = op.inBlock(1, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==16) 

        result = op.inBlock(1, 1);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==16)

        result = op.inBlock(1, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==16)

        result = op.inBlock(1, 15);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==16)

        result = op.inBlock(1, 31);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==8 && result->n()==16)

        result = op.inBlock(1, 47);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==8 && result->n()==16)

        result = op.inBlock(1, 63);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==8 && result->n()==16)

        result = op.inBlock(8, 0);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(8, 2);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(8, 15);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(8, 31);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(8, 47);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(8, 63);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(14, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(14, 2);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(14, 15);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(14, 31);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(14, 47);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(14, 63);
        TEST_ASSERT(result!=0 && result->isZero()==false  && result->m()==6 && result->n()==16)

        result = op.inBlock(20, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(20, 2);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(20, 15);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(20, 31);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(20, 47);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(20, 63);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(25, 0);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(25, 2);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(25, 15);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(25, 31);
        TEST_ASSERT(result!=0 && result->isZero() && result->m()==6 && result->n()==16)

        result = op.inBlock(25, 47);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)

        result = op.inBlock(25, 63);
        TEST_ASSERT(result!=0 && result->isZero()==false && result->m()==6 && result->n()==16)       


        // Limit cases.
        TGenericSeedingOperator<klab::DoubleReal> op0(0, 4, 8, 6, 1.0, 0.1, 10.0);
        try                                     {op0.inBlock(0, 0); TEST_ASSERT(false)}
        catch(KNullOperatorException&)          {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(26, 3); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(2, 64); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {op.inBlock(26, 64); TEST_ASSERT(false)}
        catch(KOutOfBoundOperatorException&)    {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGenericSeedingOperatorUnitTest::testApply()
{
    try
    {
        klab::KRandom::Instance().setSeed(12345);
        klab::DoubleReal precision = 1e-12; 

        arma::Col<klab::DoubleReal> x(64);
        arma::Col<klab::DoubleReal> y;

        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            x[i] = klab::DoubleReal(i+1);        


        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 26)
        TEST_ASSERT(klab::Equals(y[0],  -65.570108523704349, precision))
        TEST_ASSERT(klab::Equals(y[1],  -207.08754896942926, precision))
        TEST_ASSERT(klab::Equals(y[2],   27.298221281347036, precision))
        TEST_ASSERT(klab::Equals(y[3],   10.32455532033676, precision))
        TEST_ASSERT(klab::Equals(y[4],   30.0, precision))
        TEST_ASSERT(klab::Equals(y[5],   148.64911064067351, precision))
        TEST_ASSERT(klab::Equals(y[6],  -18.271887242357316, precision))
        TEST_ASSERT(klab::Equals(y[7],  -18.0, precision))
        TEST_ASSERT(klab::Equals(y[8],   32.066620434559368, precision))
        TEST_ASSERT(klab::Equals(y[9],   2046.5234682570765, precision))
        TEST_ASSERT(klab::Equals(y[10],  392.0, precision))
        TEST_ASSERT(klab::Equals(y[11], -95.808685548781966, precision))
        TEST_ASSERT(klab::Equals(y[12],  0.54647723677454607, precision))
        TEST_ASSERT(klab::Equals(y[13], -113.50078533708506, precision))
        TEST_ASSERT(klab::Equals(y[14], -27.725410005582766, precision))
        TEST_ASSERT(klab::Equals(y[15],  6.5631323454143864, precision))
        TEST_ASSERT(klab::Equals(y[16], -82.441141080815655, precision))
        TEST_ASSERT(klab::Equals(y[17],  68.493809158795102, precision))
        TEST_ASSERT(klab::Equals(y[18],  2859.7586490484846, precision))
        TEST_ASSERT(klab::Equals(y[19],  86.937652991670674, precision))
        TEST_ASSERT(klab::Equals(y[20], -0.41053361559588986, precision))
        TEST_ASSERT(klab::Equals(y[21],  3.042989147629565, precision))
        TEST_ASSERT(klab::Equals(y[22], -9.264911064067352, precision))
        TEST_ASSERT(klab::Equals(y[23], -23.14562255152854, precision))
        TEST_ASSERT(klab::Equals(y[24],  23.264911064067352, precision))
        TEST_ASSERT(klab::Equals(y[25], -11.794733192202056, precision))


        // Limit cases.
        try                                         {op.apply(arma::Col<klab::DoubleReal>(63), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<klab::DoubleReal>(65), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGenericSeedingOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::KRandom::Instance().setSeed(12345);
        klab::DoubleReal precision = 1e-12; 

        arma::Col<klab::DoubleReal> x(64);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            x[i] = klab::DoubleReal(i+1);    


        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
        TEST_ASSERT(op.m()==26 && op.n()==64)    

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 64)
        TEST_ASSERT(klab::Equals(xr[0],  -1038.6452758107239, precision))
        TEST_ASSERT(klab::Equals(xr[1],   673.75273742614036, precision))
        TEST_ASSERT(klab::Equals(xr[2],  -696.12626469082898, precision))
        TEST_ASSERT(klab::Equals(xr[3],   875.88228216163134, precision))
        TEST_ASSERT(klab::Equals(xr[4],   518.01067231191792, precision))
        TEST_ASSERT(klab::Equals(xr[5],   619.89309316987112, precision))
        TEST_ASSERT(klab::Equals(xr[6],  -476.10177871865312, precision))
        TEST_ASSERT(klab::Equals(xr[7],   1023.0401476992479, precision))
        TEST_ASSERT(klab::Equals(xr[8],  -473.57024722002643, precision))
        TEST_ASSERT(klab::Equals(xr[9],  -680.19459449588021, precision))
        TEST_ASSERT(klab::Equals(xr[10], -623.95601747080264, precision))
        TEST_ASSERT(klab::Equals(xr[11],  1164.8172324012421, precision))
        TEST_ASSERT(klab::Equals(xr[12], -358.84056378821356, precision))
        TEST_ASSERT(klab::Equals(xr[13],  822.2982212813472, precision))
        TEST_ASSERT(klab::Equals(xr[14], -508.40697617829017, precision))
        TEST_ASSERT(klab::Equals(xr[15],  1051.7752366351806, precision))
        TEST_ASSERT(klab::Equals(xr[16], -142.80408971527913, precision))
        TEST_ASSERT(klab::Equals(xr[17], -3306.8816111873375, precision))
        TEST_ASSERT(klab::Equals(xr[18],  326.20801457448715, precision))
        TEST_ASSERT(klab::Equals(xr[19], -854.14994099238811, precision))
        TEST_ASSERT(klab::Equals(xr[20],  2894.2125879006762, precision))
        TEST_ASSERT(klab::Equals(xr[21], -3163.0686747196396, precision))
        TEST_ASSERT(klab::Equals(xr[22], -57.681611187336557, precision))
        TEST_ASSERT(klab::Equals(xr[23],  1841.1879632321779, precision))
        TEST_ASSERT(klab::Equals(xr[24],  1780.6623920229588, precision))
        TEST_ASSERT(klab::Equals(xr[25],  3742.6393380286318, precision))
        TEST_ASSERT(klab::Equals(xr[26], -1878.003347566606, precision))
        TEST_ASSERT(klab::Equals(xr[27], -261.45130362207499, precision))
        TEST_ASSERT(klab::Equals(xr[28],  866.94245869587371, precision))
        TEST_ASSERT(klab::Equals(xr[29], -650.8337938281893, precision))
        TEST_ASSERT(klab::Equals(xr[30],  2747.7667573046647, precision))
        TEST_ASSERT(klab::Equals(xr[31],  2387.2548610593817, precision))
        TEST_ASSERT(klab::Equals(xr[32],  9879.8783986646213, precision))
        TEST_ASSERT(klab::Equals(xr[33],  1705.8178358535943, precision))
        TEST_ASSERT(klab::Equals(xr[34],  9893.6788147535863, precision))
        TEST_ASSERT(klab::Equals(xr[35],  2441.0969766668854, precision))
        TEST_ASSERT(klab::Equals(xr[36],  2001.9268681431818, precision))
        TEST_ASSERT(klab::Equals(xr[37],  10536.926077327445, precision))
        TEST_ASSERT(klab::Equals(xr[38],  10420.369782464, precision))
        TEST_ASSERT(klab::Equals(xr[39],  7677.2739190201228, precision))
        TEST_ASSERT(klab::Equals(xr[40],  2911.931996254657, precision))
        TEST_ASSERT(klab::Equals(xr[41],  2345.5003954078697, precision))
        TEST_ASSERT(klab::Equals(xr[42],  11308.55911015208, precision))
        TEST_ASSERT(klab::Equals(xr[43],  5259.0030963337131, precision))
        TEST_ASSERT(klab::Equals(xr[44],  5628.8644499604734, precision))
        TEST_ASSERT(klab::Equals(xr[45],  10500.331066742599, precision))
        TEST_ASSERT(klab::Equals(xr[46],  2138.2183906388823, precision))
        TEST_ASSERT(klab::Equals(xr[47],  8897.4299364909275, precision))
        TEST_ASSERT(klab::Equals(xr[48],  8781.1816355208703, precision))
        TEST_ASSERT(klab::Equals(xr[49],  8692.1165857604792, precision))
        TEST_ASSERT(klab::Equals(xr[50],  8593.1762300167484, precision))
        TEST_ASSERT(klab::Equals(xr[51],  8744.5325248801946, precision))
        TEST_ASSERT(klab::Equals(xr[52],  9358.374520646259, precision))
        TEST_ASSERT(klab::Equals(xr[53],  8902.6572188968548, precision))
        TEST_ASSERT(klab::Equals(xr[54],  9207.2622083120095, precision))
        TEST_ASSERT(klab::Equals(xr[55],  9000.9763687130726, precision))
        TEST_ASSERT(klab::Equals(xr[56],  9197.1150150863104, precision))
        TEST_ASSERT(klab::Equals(xr[57],  8246.9291061392105, precision))
        TEST_ASSERT(klab::Equals(xr[58],  9341.0708938607913, precision))
        TEST_ASSERT(klab::Equals(xr[59],  8357.0096789303516, precision))
        TEST_ASSERT(klab::Equals(xr[60],  9313.6920997883044, precision))
        TEST_ASSERT(klab::Equals(xr[61],  9277.7308155097035, precision))
        TEST_ASSERT(klab::Equals(xr[62],  9704.8656270529937, precision))
        TEST_ASSERT(klab::Equals(xr[63],  9974.9237006350941, precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(25), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(27), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGenericSeedingOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 26;
        klab::UInt32 n = 64;
        klab::DoubleReal precision = 1e-12; 
        
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
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

void KGenericSeedingOperatorUnitTest::testColumnAdjoint()
{
    try
    {       
        klab::UInt32 m = 26;
        klab::UInt32 n = 64;
        klab::DoubleReal precision = 1e-12; 
        
        TGenericSeedingOperator<klab::DoubleReal> op(new TWalshHadamard1DOperator<klab::DoubleReal>(16), 4, 8, 6, 1.0, 0.1, 10.0);
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
