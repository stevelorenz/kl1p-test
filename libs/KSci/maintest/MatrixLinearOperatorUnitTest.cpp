// KSci - A portable C++ numerical analysis library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KSci C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#include "MatrixLinearOperatorUnitTest.h"
#include "../include/MatrixLinearOperator.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KMatrixLinearOperatorUnitTest::KMatrixLinearOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KMatrixLinearOperatorUnitTest::testApply)  
	TEST_ADD(KMatrixLinearOperatorUnitTest::testApplyAdjoint)  
}

// ---------------------------------------------------------------------------------------------------- //

KMatrixLinearOperatorUnitTest::~KMatrixLinearOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixLinearOperatorUnitTest::testApply()
{
    try
    {
        arma::Col<klab::Real> x2(2);
        arma::Col<klab::Real> x3(3);
        arma::Col<klab::Real> y2(2);
        arma::Col<klab::Real> y3(3);

        x2[0] = 1.0f;
        x2[1] = 2.0f;

        x3[0] = 1.0f;
        x3[1] = 2.0f;
        x3[2] = 3.0f;

        y2[0] = 0.0f;
        y2[1] = 0.0f;

        y3[0] = 0.0f;
        y3[1] = 0.0f;
        y3[2] = 0.0f;

        arma::Mat<klab::Real> mat2_2(2, 2);
        arma::Mat<klab::Real> mat2_3(2, 3);
        arma::Mat<klab::Real> mat3_2(3, 2);
        arma::Mat<klab::Real> mat3_3(3, 3);

        mat2_3(0, 0) = 1.0f;
        mat2_3(0, 1) = 2.0f;
        mat2_3(0, 2) = 3.0f;
        mat2_3(1, 0) = 4.0f;
        mat2_3(1, 1) = 5.0f;
        mat2_3(1, 2) = 6.0f;

        mat3_2(0, 0) = 1.0f;
        mat3_2(0, 1) = 2.0f;
        mat3_2(1, 0) = 4.0f;
        mat3_2(1, 1) = 5.0f;
        mat3_2(2, 0) = 7.0f;
        mat3_2(2, 1) = 8.0f;

        mat3_3(0, 0) = 1.0f;
        mat3_3(0, 1) = 2.0f;
        mat3_3(0, 2) = 3.0f;
        mat3_3(1, 0) = 4.0f;
        mat3_3(1, 1) = 5.0f;
        mat3_3(1, 2) = 6.0f;
        mat3_3(2, 0) = 7.0f;
        mat3_3(2, 1) = 8.0f;
        mat3_3(2, 2) = 9.0f;

        
        // Tests : y = A * x;
        TMatrixLinearOperator<klab::Real> t1(mat2_3);
        t1.apply(x3, y2);
        TEST_ASSERT(y2[0] == 14.0)
        TEST_ASSERT(y2[1] == 32.0)

        TMatrixLinearOperator<klab::Real> t2(mat3_2);
        t2.apply(x2, y3);
        TEST_ASSERT(y3[0] == 5.0)
        TEST_ASSERT(y3[1] == 14.0)
        TEST_ASSERT(y3[2] == 23.0)

        TMatrixLinearOperator<klab::Real> t3(mat3_3);
        t3.apply(x3, y3);
        TEST_ASSERT(y3[0] == 14.0)
        TEST_ASSERT(y3[1] == 32.0)
        TEST_ASSERT(y3[2] == 50.0)


        // Limit cases.
        try													{TMatrixLinearOperator<klab::Real> t(mat3_3); t.apply(x2, y3); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLinearOperatorException&)	{TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {TMatrixLinearOperator<klab::Real> t(mat3_3); t.apply(x2, y2); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLinearOperatorException&)	{TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMatrixLinearOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        arma::Col<klab::Real> x2(2);
        arma::Col<klab::Real> x3(3);
        arma::Col<klab::Real> y2(2);
        arma::Col<klab::Real> y3(3);
        arma::Col<klab::Real> xr2(2);
        arma::Col<klab::Real> xr3(3);

        x2[0] = 1.0f;
        x2[1] = 2.0f;

        x3[0] = 1.0f;
        x3[1] = 2.0f;
        x3[2] = 3.0f;

        y2[0] = 0.0f;
        y2[1] = 0.0f;

        y3[0] = 0.0f;
        y3[1] = 0.0f;
        y3[2] = 0.0f;

        arma::Mat<klab::Real> mat2_2(2, 2);
        arma::Mat<klab::Real> mat2_3(2, 3);
        arma::Mat<klab::Real> mat3_2(3, 2);
        arma::Mat<klab::Real> mat3_3(3, 3);

        mat2_3(0, 0) = 1.0f;
        mat2_3(0, 1) = 2.0f;
        mat2_3(0, 2) = 3.0f;
        mat2_3(1, 0) = 4.0f;
        mat2_3(1, 1) = 5.0f;
        mat2_3(1, 2) = 6.0f;

        mat3_2(0, 0) = 1.0f;
        mat3_2(0, 1) = 2.0f;
        mat3_2(1, 0) = 4.0f;
        mat3_2(1, 1) = 5.0f;
        mat3_2(2, 0) = 7.0f;
        mat3_2(2, 1) = 8.0f;

        mat3_3(0, 0) = 1.0f;
        mat3_3(0, 1) = 2.0f;
        mat3_3(0, 2) = 3.0f;
        mat3_3(1, 0) = 4.0f;
        mat3_3(1, 1) = 5.0f;
        mat3_3(1, 2) = 6.0f;
        mat3_3(2, 0) = 7.0f;
        mat3_3(2, 1) = 8.0f;
        mat3_3(2, 2) = 9.0f;

        
        // Tests : y = A * x;
        TMatrixLinearOperator<klab::Real> t1(mat2_3);
        t1.apply(x3, y2);
        t1.applyAdjoint(y2, xr3);
        TEST_ASSERT(xr3[0] == 142.0)
        TEST_ASSERT(xr3[1] == 188.0)
        TEST_ASSERT(xr3[2] == 234.0)

        TMatrixLinearOperator<klab::Real> t2(mat3_2);
        t2.apply(x2, y3);
        t2.applyAdjoint(y3, xr2);
        TEST_ASSERT(xr2[0] == 222.0)
        TEST_ASSERT(xr2[1] == 264.0)

        TMatrixLinearOperator<klab::Real> t3(mat3_3);
        t3.apply(x3, y3);
        t3.applyAdjoint(y3, xr3);
        TEST_ASSERT(xr3[0] == 492.0)
        TEST_ASSERT(xr3[1] == 588.0)
        TEST_ASSERT(xr3[2] == 684.0)


        // Limit cases.
        try													{TMatrixLinearOperator<klab::Real> t(mat3_3); t.applyAdjoint(y2, xr3); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLinearOperatorException&)	{TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {TMatrixLinearOperator<klab::Real> t(mat3_3); t.applyAdjoint(y2, xr2); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLinearOperatorException&)	{TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
