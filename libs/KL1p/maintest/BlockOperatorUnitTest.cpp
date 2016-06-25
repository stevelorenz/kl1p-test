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

#include "BlockOperatorUnitTest.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KBlockOperatorUnitTest::KBlockOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KBlockOperatorUnitTest::testDefaultConstructor) 
    TEST_ADD(KBlockOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KBlockOperatorUnitTest::testIsZero)
    TEST_ADD(KBlockOperatorUnitTest::testSum)
    TEST_ADD(KBlockOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KBlockOperatorUnitTest::testCountBlockRows)
    TEST_ADD(KBlockOperatorUnitTest::testCountBlockColumns)
    TEST_ADD(KBlockOperatorUnitTest::testBlock)
    TEST_ADD(KBlockOperatorUnitTest::testIsZeroBlock)
    TEST_ADD(KBlockOperatorUnitTest::testInBlock)
    TEST_ADD(KBlockOperatorUnitTest::testApply)
    TEST_ADD(KBlockOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KBlockOperatorUnitTest::testColumn)
    TEST_ADD(KBlockOperatorUnitTest::testColumnAdjoint)
    TEST_ADD(KBlockOperatorUnitTest::testApplyBlockVariance)
    TEST_ADD(KBlockOperatorUnitTest::testApplyBlockVarianceAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KBlockOperatorUnitTest::~KBlockOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KBlockOperatorUnitTest::testDefaultConstructor()
{
    try
    {
        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)
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
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KBlockOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)
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

        TTestBlockOperator<klab::DoubleReal> opCopy(op);
        TEST_ASSERT(opCopy.m()==12 && opCopy.n()==18)    
        TEST_ASSERT(opCopy.countBlockRows()==3 && opCopy.countBlockColumns()==4)
        TEST_ASSERT(opCopy.block(0, 0)!=0 && opCopy.block(0, 0)->isZero()==false) 
        TEST_ASSERT(opCopy.block(0, 1)!=0 && opCopy.block(0, 1)->isZero()==false) 
        TEST_ASSERT(opCopy.block(0, 2)!=0 && opCopy.block(0, 2)->isZero()==false) 
        TEST_ASSERT(opCopy.block(0, 3)!=0 && opCopy.block(0, 3)->isZero()==false)
        TEST_ASSERT(opCopy.block(1, 0)!=0 && opCopy.block(1, 0)->isZero()==false) 
        TEST_ASSERT(opCopy.block(1, 1)!=0 && opCopy.block(1, 1)->isZero()==false) 
        TEST_ASSERT(opCopy.block(1, 2)!=0 && opCopy.block(1, 2)->isZero()==false) 
        TEST_ASSERT(opCopy.block(1, 3)!=0 && opCopy.block(1, 3)->isZero()==false) 
        TEST_ASSERT(opCopy.block(2, 0)!=0 && opCopy.block(2, 0)->isZero()==false) 
        TEST_ASSERT(opCopy.block(2, 1)!=0 && opCopy.block(2, 1)->isZero()==false) 
        TEST_ASSERT(opCopy.block(2, 2)!=0 && opCopy.block(2, 2)->isZero()==false) 
        TEST_ASSERT(opCopy.block(2, 3)!=0 && opCopy.block(2, 3)->isZero()==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockOperatorUnitTest::testIsZero()
{
    try
    {
        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)
        TEST_ASSERT(op.isZero() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockOperatorUnitTest::testSum()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)

        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.countBlockRows(); ++i)
        {
            for(klab::UInt32 j=0; j<op.countBlockColumns(); ++j)
            {
                klab::TSmartPointer<TOperator<klab::DoubleReal> > block = op.block(i, j);
                if(block != 0)
                    sum += block->sum();
            }
        }

        TEST_ASSERT(klab::Equals(op.sum(), sum, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockOperatorUnitTest::testSquaredNormFrobenius()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)

        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.countBlockRows(); ++i)
        {
            for(klab::UInt32 j=0; j<op.countBlockColumns(); ++j)
            {
                klab::TSmartPointer<TOperator<klab::DoubleReal> > block = op.block(i, j);
                if(block != 0)
                    sum += block->squaredNormFrobenius();
            }
        }

        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), sum, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockOperatorUnitTest::testCountBlockRows()
{
    try
    {
        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockOperatorUnitTest::testCountBlockColumns()
{
    try
    {
        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockOperatorUnitTest::testBlock()
{
    try
    {
        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)
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

void KBlockOperatorUnitTest::testIsZeroBlock()
{
    try
    {
        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)
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

void KBlockOperatorUnitTest::testInBlock()
{
    try
    {
        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)    
        TEST_ASSERT(op.countBlockRows()==3 && op.countBlockColumns()==4)

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

void KBlockOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(18);
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


        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 12)
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
        try                                         {op.apply(arma::Col<klab::DoubleReal>(17), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<klab::DoubleReal>(19), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-9;

        arma::Col<klab::DoubleReal> x(18);
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


        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 18)
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
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(11), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(13), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBlockOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 12;
        klab::UInt32 n = 18;
        klab::DoubleReal precision = 1e-12; 


        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)

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

void KBlockOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 12;
        klab::UInt32 n = 18;
        klab::DoubleReal precision = 1e-12; 


        TTestBlockOperator<klab::DoubleReal> op;
        TEST_ASSERT(op.m()==12 && op.n()==18)

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

void KBlockOperatorUnitTest::testApplyBlockVariance()
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


        TTestBlockOperator<klab::DoubleReal> op;
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

void KBlockOperatorUnitTest::testApplyBlockVarianceAdjoint()
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


        TTestBlockOperator<klab::DoubleReal> op;
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
