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

#include "AdditionOperatorUnitTest.h"
#include "../include/AdditionOperator.h"
#include "../include/MatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KAdditionOperatorUnitTest::KAdditionOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KAdditionOperatorUnitTest::testLeftRightConstructor)  
    TEST_ADD(KAdditionOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KAdditionOperatorUnitTest::testAdditionOperator)

    TEST_ADD(KAdditionOperatorUnitTest::testLeft)
    TEST_ADD(KAdditionOperatorUnitTest::testRight)
    TEST_ADD(KAdditionOperatorUnitTest::testApply)
    TEST_ADD(KAdditionOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KAdditionOperatorUnitTest::testColumn)
    TEST_ADD(KAdditionOperatorUnitTest::testColumnAdjoint)
}

// ---------------------------------------------------------------------------------------------------- //

KAdditionOperatorUnitTest::~KAdditionOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KAdditionOperatorUnitTest::testLeftRightConstructor()
{
    try
    {
        TMatrixOperator<klab::DoubleReal>* left  = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));
        TMatrixOperator<klab::DoubleReal>* right = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));

        TAdditionOperator<klab::DoubleReal> op(left, right);
        TEST_ASSERT(op.left().get()==left && op.right().get()==right)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdditionOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TMatrixOperator<klab::DoubleReal>* left  = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));
        TMatrixOperator<klab::DoubleReal>* right = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));

        TAdditionOperator<klab::DoubleReal> op(left, right);
        TEST_ASSERT(op.left().get()==left && op.right().get()==right)

        TAdditionOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.left().get()==left && op2.right().get()==right)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdditionOperatorUnitTest::testAdditionOperator()
{
    try
    {
        klab::TSmartPointer<TMatrixOperator<klab::DoubleReal> > left  = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));
        klab::TSmartPointer<TOperator<klab::DoubleReal> >       right = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));

        klab::TSmartPointer<TOperator<klab::DoubleReal> > op = (klab::static_pointer_cast<TOperator<klab::DoubleReal> >(left) + right);
        TEST_ASSERT(op != 0)
        TEST_ASSERT(klab::dynamic_pointer_cast<TAdditionOperator<klab::DoubleReal> >(op)->left() == left)
        TEST_ASSERT(klab::dynamic_pointer_cast<TAdditionOperator<klab::DoubleReal> >(op)->right() == right)


        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > cleft  = new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(0, 0));
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > cright = new TMatrixOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(0, 0));

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > cop = (cleft + cright);
        TEST_ASSERT(cop != 0)
        TEST_ASSERT(klab::dynamic_pointer_cast<TAdditionOperator<std::complex<klab::DoubleReal> > >(cop)->left() == cleft)
        TEST_ASSERT(klab::dynamic_pointer_cast<TAdditionOperator<std::complex<klab::DoubleReal> > >(cop)->right() == cright)


        arma::Mat<klab::DoubleReal> mat1(2, 3);
        arma::Mat<klab::DoubleReal> mat2(2, 3);
        arma::Mat<klab::DoubleReal> mat3(2, 3);

        mat1(0, 0) = 1.0;
        mat1(0, 1) = 2.0;
        mat1(0, 2) = 3.0;
        mat1(1, 0) = 4.0;
        mat1(1, 1) = 5.0;
        mat1(1, 2) = 6.0;

        mat2(0, 0) = 6.0;
        mat2(0, 1) = 5.0;
        mat2(0, 2) = 4.0;
        mat2(1, 0) = 3.0;
        mat2(1, 1) = 2.0;
        mat2(1, 2) = 1.0;

        mat3(0, 0) =  1.0;
        mat3(0, 1) = -1.0;
        mat3(0, 2) =  2.0;
        mat3(1, 0) = -2.0;
        mat3(1, 1) =  3.0;
        mat3(1, 2) = -3.0;

        arma::Col<klab::DoubleReal> in(3);
        in[0] = 1.0;
        in[1] = 2.0;
        in[2] = 3.0;

        arma::Col<klab::DoubleReal> result = (mat3 + mat2 + mat1) * in;


        klab::TSmartPointer<TOperator<klab::DoubleReal> > matOp1 = new TMatrixOperator<klab::DoubleReal>(mat1);
        klab::TSmartPointer<TOperator<klab::DoubleReal> > matOp2 = new TMatrixOperator<klab::DoubleReal>(mat2);
        klab::TSmartPointer<TOperator<klab::DoubleReal> > matOp3 = new TMatrixOperator<klab::DoubleReal>(mat3);

        klab::TSmartPointer<TOperator<klab::DoubleReal> > resultOp = matOp3 + matOp2 + matOp1;
        TEST_ASSERT(resultOp != 0)

        arma::Col<klab::DoubleReal> out;
        resultOp->apply(in, out);
        TEST_ASSERT(out.n_rows == 2)
        TEST_ASSERT(klab::Equals(out[0], result[0]))
        TEST_ASSERT(klab::Equals(out[1], result[1]))


        out.fill(0.0);
        resultOp = (matOp3 + matOp2) + matOp1;
        TEST_ASSERT(resultOp != 0)

        resultOp->apply(in, out);
        TEST_ASSERT(out.n_rows == 2)
        TEST_ASSERT(klab::Equals(out[0], result[0]))
        TEST_ASSERT(klab::Equals(out[1], result[1]))


        out.fill(0.0);
        resultOp = matOp3 + (matOp2 + matOp1);
        TEST_ASSERT(resultOp != 0)

        resultOp->apply(in, out);
        TEST_ASSERT(out.n_rows == 2)
        TEST_ASSERT(klab::Equals(out[0], result[0]))
        TEST_ASSERT(klab::Equals(out[1], result[1]))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdditionOperatorUnitTest::testLeft()
{
    try
    {
        TMatrixOperator<klab::DoubleReal>* left  = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));
        TMatrixOperator<klab::DoubleReal>* right = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));

        TAdditionOperator<klab::DoubleReal> op(0, 0);
        TEST_ASSERT(op.left().get()==0 && op.right().get()==0)

        TAdditionOperator<klab::DoubleReal> op2(left, right);
        TEST_ASSERT(op2.left().get()==left && op2.right().get()==right)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdditionOperatorUnitTest::testRight()
{
    try
    {
        TMatrixOperator<klab::DoubleReal>* left  = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));
        TMatrixOperator<klab::DoubleReal>* right = new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0));

        TAdditionOperator<klab::DoubleReal> op(0, 0);
        TEST_ASSERT(op.left().get()==0 && op.right().get()==0)

        TAdditionOperator<klab::DoubleReal> op2(left, right);
        TEST_ASSERT(op2.left().get()==left && op2.right().get()==right)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdditionOperatorUnitTest::testApply()
{
    try
    {
        klab::DoubleReal precision = 1e-6;

        arma::Mat<klab::DoubleReal> matrix1(4, 8);
        arma::Mat<klab::DoubleReal> matrix2(4, 8);
        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(0, 2) = 3.0;
        matrix1(0, 3) = 4.0;
        matrix1(0, 4) = 5.0;
        matrix1(0, 5) = 6.0;
        matrix1(0, 6) = 7.0;
        matrix1(0, 7) = 8.0;
        matrix1(1, 0) = 9.0;
        matrix1(1, 1) = 10.0;
        matrix1(1, 2) = 11.0;
        matrix1(1, 3) = 12.0;
        matrix1(1, 4) = 13.0;
        matrix1(1, 5) = 14.0;
        matrix1(1, 6) = 15.0;
        matrix1(1, 7) = 16.0;
        matrix1(2, 0) = 17.0;
        matrix1(2, 1) = 18.0;
        matrix1(2, 2) = 19.0;
        matrix1(2, 3) = 20.0;
        matrix1(2, 4) = 21.0;
        matrix1(2, 5) = 22.0;
        matrix1(2, 6) = 23.0;
        matrix1(2, 7) = 24.0;
        matrix1(3, 0) = 25.0;
        matrix1(3, 1) = 26.0;
        matrix1(3, 2) = 27.0;
        matrix1(3, 3) = 28.0;
        matrix1(3, 4) = 29.0;
        matrix1(3, 5) = 30.0;
        matrix1(3, 6) = 31.0;
        matrix1(3, 7) = 32.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;
        matrix2(0, 5) = 2.7;
        matrix2(0, 6) = 2.6;
        matrix2(0, 7) = 2.5;
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;
        matrix2(1, 5) = 1.9;
        matrix2(1, 6) = 1.8;
        matrix2(1, 7) = 1.7;
        matrix2(2, 0) = 1.6;
        matrix2(2, 1) = 1.5;
        matrix2(2, 2) = 1.4;
        matrix2(2, 3) = 1.3;
        matrix2(2, 4) = 1.2;
        matrix2(2, 5) = 1.1;
        matrix2(2, 6) = 1.0;
        matrix2(2, 7) = 0.9;
        matrix2(3, 0) = 0.8;
        matrix2(3, 1) = 0.7;
        matrix2(3, 2) = 0.6;
        matrix2(3, 3) = 0.5;
        matrix2(3, 4) = 0.4;
        matrix2(3, 5) = 0.3;
        matrix2(3, 6) = 0.2;
        matrix2(3, 7) = 0.1;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;

 
        TAdditionOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2));
        TEST_ASSERT(op.left().get()>0 && op.right().get()>0)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], 302.4, precision))
        TEST_ASSERT(klab::Equals(y[1], 561.6, precision))
        TEST_ASSERT(klab::Equals(y[2], 820.8, precision))
        TEST_ASSERT(klab::Equals(y[3], 1080.0, precision))


        // Limit cases.
        try
        {
            TAdditionOperator<klab::DoubleReal> op0(0, 0);
            op0.apply(x, y);
            TEST_ASSERT(false)
        }
        catch(KNullOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
            op0.apply(x, y);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 8)));
            op0.apply(x, y);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 7)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
            op0.apply(x, y);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 7)));
            op0.apply(x, y);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 7)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
            op0.apply(x, y);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 7)));
            op0.apply(x, y);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdditionOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-6;

        arma::Mat<klab::DoubleReal> matrix1(4, 8);
        arma::Mat<klab::DoubleReal> matrix2(4, 8);
        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(0, 2) = 3.0;
        matrix1(0, 3) = 4.0;
        matrix1(0, 4) = 5.0;
        matrix1(0, 5) = 6.0;
        matrix1(0, 6) = 7.0;
        matrix1(0, 7) = 8.0;
        matrix1(1, 0) = 9.0;
        matrix1(1, 1) = 10.0;
        matrix1(1, 2) = 11.0;
        matrix1(1, 3) = 12.0;
        matrix1(1, 4) = 13.0;
        matrix1(1, 5) = 14.0;
        matrix1(1, 6) = 15.0;
        matrix1(1, 7) = 16.0;
        matrix1(2, 0) = 17.0;
        matrix1(2, 1) = 18.0;
        matrix1(2, 2) = 19.0;
        matrix1(2, 3) = 20.0;
        matrix1(2, 4) = 21.0;
        matrix1(2, 5) = 22.0;
        matrix1(2, 6) = 23.0;
        matrix1(2, 7) = 24.0;
        matrix1(3, 0) = 25.0;
        matrix1(3, 1) = 26.0;
        matrix1(3, 2) = 27.0;
        matrix1(3, 3) = 28.0;
        matrix1(3, 4) = 29.0;
        matrix1(3, 5) = 30.0;
        matrix1(3, 6) = 31.0;
        matrix1(3, 7) = 32.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;
        matrix2(0, 5) = 2.7;
        matrix2(0, 6) = 2.6;
        matrix2(0, 7) = 2.5;
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;
        matrix2(1, 5) = 1.9;
        matrix2(1, 6) = 1.8;
        matrix2(1, 7) = 1.7;
        matrix2(2, 0) = 1.6;
        matrix2(2, 1) = 1.5;
        matrix2(2, 2) = 1.4;
        matrix2(2, 3) = 1.3;
        matrix2(2, 4) = 1.2;
        matrix2(2, 5) = 1.1;
        matrix2(2, 6) = 1.0;
        matrix2(2, 7) = 0.9;
        matrix2(3, 0) = 0.8;
        matrix2(3, 1) = 0.7;
        matrix2(3, 2) = 0.6;
        matrix2(3, 3) = 0.5;
        matrix2(3, 4) = 0.4;
        matrix2(3, 5) = 0.3;
        matrix2(3, 6) = 0.2;
        matrix2(3, 7) = 0.1;

        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;

 
        TAdditionOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2));
        TEST_ASSERT(op.left().get()>0 && op.right().get()>0)

        op.apply(x, y);
        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], 50803.2, precision))
        TEST_ASSERT(klab::Equals(xr[1], 53291.52, precision))
        TEST_ASSERT(klab::Equals(xr[2], 55779.84, precision))
        TEST_ASSERT(klab::Equals(xr[3], 58268.16, precision))
        TEST_ASSERT(klab::Equals(xr[4], 60756.48, precision))
        TEST_ASSERT(klab::Equals(xr[5], 63244.8, precision))
        TEST_ASSERT(klab::Equals(xr[6], 65733.12, precision))
        TEST_ASSERT(klab::Equals(xr[7], 68221.44, precision))


        // Limit cases.
        try
        {
            TAdditionOperator<klab::DoubleReal> op0(0, 0);
            op0.applyAdjoint(y, xr);
            TEST_ASSERT(false)
        }
        catch(KNullOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
            op0.applyAdjoint(y, xr);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 8)));
            op0.applyAdjoint(y, xr);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 7)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
            op0.applyAdjoint(y, xr);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 7)));
            op0.applyAdjoint(y, xr);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 7)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)));
            op0.applyAdjoint(y, xr);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TAdditionOperator<klab::DoubleReal> op0(new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(4, 8)), new TMatrixOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 7)));
            op0.applyAdjoint(y, xr);
            TEST_ASSERT(false)
        }
        catch(KIncompatibleSizeOperatorException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KAdditionOperatorUnitTest::testColumn()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-6; 

        arma::Mat<klab::DoubleReal> matrix1(m, n);
        arma::Mat<klab::DoubleReal> matrix2(m, n);

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(0, 2) = 3.0;
        matrix1(0, 3) = 4.0;
        matrix1(0, 4) = 5.0;
        matrix1(0, 5) = 6.0;
        matrix1(0, 6) = 7.0;
        matrix1(0, 7) = 8.0;
        matrix1(1, 0) = 9.0;
        matrix1(1, 1) = 10.0;
        matrix1(1, 2) = 11.0;
        matrix1(1, 3) = 12.0;
        matrix1(1, 4) = 13.0;
        matrix1(1, 5) = 14.0;
        matrix1(1, 6) = 15.0;
        matrix1(1, 7) = 16.0;
        matrix1(2, 0) = 17.0;
        matrix1(2, 1) = 18.0;
        matrix1(2, 2) = 19.0;
        matrix1(2, 3) = 20.0;
        matrix1(2, 4) = 21.0;
        matrix1(2, 5) = 22.0;
        matrix1(2, 6) = 23.0;
        matrix1(2, 7) = 24.0;
        matrix1(3, 0) = 25.0;
        matrix1(3, 1) = 26.0;
        matrix1(3, 2) = 27.0;
        matrix1(3, 3) = 28.0;
        matrix1(3, 4) = 29.0;
        matrix1(3, 5) = 30.0;
        matrix1(3, 6) = 31.0;
        matrix1(3, 7) = 32.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;
        matrix2(0, 5) = 2.7;
        matrix2(0, 6) = 2.6;
        matrix2(0, 7) = 2.5;
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;
        matrix2(1, 5) = 1.9;
        matrix2(1, 6) = 1.8;
        matrix2(1, 7) = 1.7;
        matrix2(2, 0) = 1.6;
        matrix2(2, 1) = 1.5;
        matrix2(2, 2) = 1.4;
        matrix2(2, 3) = 1.3;
        matrix2(2, 4) = 1.2;
        matrix2(2, 5) = 1.1;
        matrix2(2, 6) = 1.0;
        matrix2(2, 7) = 0.9;
        matrix2(3, 0) = 0.8;
        matrix2(3, 1) = 0.7;
        matrix2(3, 2) = 0.6;
        matrix2(3, 3) = 0.5;
        matrix2(3, 4) = 0.4;
        matrix2(3, 5) = 0.3;
        matrix2(3, 6) = 0.2;
        matrix2(3, 7) = 0.1;

        TAdditionOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2));

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


        TAdditionOperator<klab::DoubleReal> op0(0, 0);
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

void KAdditionOperatorUnitTest::testColumnAdjoint()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;

        klab::DoubleReal precision = 1e-12; 

        arma::Mat<klab::DoubleReal> matrix1(m, n);
        arma::Mat<klab::DoubleReal> matrix2(m, n);

        matrix1(0, 0) = 1.0;
        matrix1(0, 1) = 2.0;
        matrix1(0, 2) = 3.0;
        matrix1(0, 3) = 4.0;
        matrix1(0, 4) = 5.0;
        matrix1(0, 5) = 6.0;
        matrix1(0, 6) = 7.0;
        matrix1(0, 7) = 8.0;
        matrix1(1, 0) = 9.0;
        matrix1(1, 1) = 10.0;
        matrix1(1, 2) = 11.0;
        matrix1(1, 3) = 12.0;
        matrix1(1, 4) = 13.0;
        matrix1(1, 5) = 14.0;
        matrix1(1, 6) = 15.0;
        matrix1(1, 7) = 16.0;
        matrix1(2, 0) = 17.0;
        matrix1(2, 1) = 18.0;
        matrix1(2, 2) = 19.0;
        matrix1(2, 3) = 20.0;
        matrix1(2, 4) = 21.0;
        matrix1(2, 5) = 22.0;
        matrix1(2, 6) = 23.0;
        matrix1(2, 7) = 24.0;
        matrix1(3, 0) = 25.0;
        matrix1(3, 1) = 26.0;
        matrix1(3, 2) = 27.0;
        matrix1(3, 3) = 28.0;
        matrix1(3, 4) = 29.0;
        matrix1(3, 5) = 30.0;
        matrix1(3, 6) = 31.0;
        matrix1(3, 7) = 32.0;

        matrix2(0, 0) = 3.2;
        matrix2(0, 1) = 3.1;
        matrix2(0, 2) = 3.0;
        matrix2(0, 3) = 2.9;
        matrix2(0, 4) = 2.8;
        matrix2(0, 5) = 2.7;
        matrix2(0, 6) = 2.6;
        matrix2(0, 7) = 2.5;
        matrix2(1, 0) = 2.4;
        matrix2(1, 1) = 2.3;
        matrix2(1, 2) = 2.2;
        matrix2(1, 3) = 2.1;
        matrix2(1, 4) = 2.0;
        matrix2(1, 5) = 1.9;
        matrix2(1, 6) = 1.8;
        matrix2(1, 7) = 1.7;
        matrix2(2, 0) = 1.6;
        matrix2(2, 1) = 1.5;
        matrix2(2, 2) = 1.4;
        matrix2(2, 3) = 1.3;
        matrix2(2, 4) = 1.2;
        matrix2(2, 5) = 1.1;
        matrix2(2, 6) = 1.0;
        matrix2(2, 7) = 0.9;
        matrix2(3, 0) = 0.8;
        matrix2(3, 1) = 0.7;
        matrix2(3, 2) = 0.6;
        matrix2(3, 3) = 0.5;
        matrix2(3, 4) = 0.4;
        matrix2(3, 5) = 0.3;
        matrix2(3, 6) = 0.2;
        matrix2(3, 7) = 0.1;

        TAdditionOperator<klab::DoubleReal> op(new TMatrixOperator<klab::DoubleReal>(matrix1), new TMatrixOperator<klab::DoubleReal>(matrix2));

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


        TAdditionOperator<klab::DoubleReal> op0(0, 0);
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
