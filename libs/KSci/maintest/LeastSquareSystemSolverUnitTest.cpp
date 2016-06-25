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

#include "LeastSquareSystemSolverUnitTest.h"
#include "../include/LeastSquareSystemSolver.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KLeastSquareSystemSolverUnitTest::KLeastSquareSystemSolverUnitTest() : Test::Suite()
{
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testDefaultConstructor)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testIterationLimitConstructor)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testIterationLimitCondLimitConstructor)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testIterationLimitCondLimitAToleranceBToleranceConstructor)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testCopyConstructor)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testAffectationOperator)

    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSetATolerance)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSetBTolerance)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSetCondLimit)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSetIterationLimit)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testATolerance)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testBTolerance)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testCondLimit)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testIterationLimit)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testCountIterations)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testANorm)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testACond)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testArNorm)
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testXNorm)

    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSolve)  
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSolve_Errors)  
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSolve_Matrix)  
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSolve_Matrix_Errors) 
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSolve_Complex)  
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSolve_ErrorsComplex)  
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSolve_MatrixComplex)  
    TEST_ADD(KLeastSquareSystemSolverUnitTest::testSolve_Matrix_ErrorsComplex)  
}

// ---------------------------------------------------------------------------------------------------- //

KLeastSquareSystemSolverUnitTest::~KLeastSquareSystemSolverUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testDefaultConstructor()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.aTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)
        TEST_ASSERT(solver.bTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)
        TEST_ASSERT(solver.condLimit() == 100000000.0f)
        TEST_ASSERT(solver.iterationLimit() == 0)
        TEST_ASSERT(solver.countIterations() == 0)
        TEST_ASSERT(solver.aNorm() == 0.0f)
        TEST_ASSERT(solver.aCond() == 0.0f)
        TEST_ASSERT(solver.rNorm() == 0.0f)
        TEST_ASSERT(solver.arNorm() == 0.0f)
        TEST_ASSERT(solver.xNorm() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testIterationLimitConstructor()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver(123);
        TEST_ASSERT(solver.aTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)
        TEST_ASSERT(solver.bTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)
        TEST_ASSERT(solver.condLimit() == 100000000.0f)
        TEST_ASSERT(solver.iterationLimit() == 123)
        TEST_ASSERT(solver.countIterations() == 0)
        TEST_ASSERT(solver.aNorm() == 0.0f)
        TEST_ASSERT(solver.aCond() == 0.0f)
        TEST_ASSERT(solver.rNorm() == 0.0f)
        TEST_ASSERT(solver.arNorm() == 0.0f)
        TEST_ASSERT(solver.xNorm() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testIterationLimitCondLimitConstructor()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver(123, 456.789f);
        TEST_ASSERT(solver.aTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)
        TEST_ASSERT(solver.bTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)
        TEST_ASSERT(solver.condLimit() == 456.789f)
        TEST_ASSERT(solver.iterationLimit() == 123)
        TEST_ASSERT(solver.countIterations() == 0)
        TEST_ASSERT(solver.aNorm() == 0.0f)
        TEST_ASSERT(solver.aCond() == 0.0f)
        TEST_ASSERT(solver.rNorm() == 0.0f)
        TEST_ASSERT(solver.arNorm() == 0.0f)
        TEST_ASSERT(solver.xNorm() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testIterationLimitCondLimitAToleranceBToleranceConstructor()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver(123, 456.789f, 0.1011f, 0.1213f);
        TEST_ASSERT(solver.aTolerance() == 0.1011f)
        TEST_ASSERT(solver.bTolerance() == 0.1213f)
        TEST_ASSERT(solver.condLimit() == 456.789f)
        TEST_ASSERT(solver.iterationLimit() == 123)
        TEST_ASSERT(solver.countIterations() == 0)
        TEST_ASSERT(solver.aNorm() == 0.0f)
        TEST_ASSERT(solver.aCond() == 0.0f)
        TEST_ASSERT(solver.rNorm() == 0.0f)
        TEST_ASSERT(solver.arNorm() == 0.0f)
        TEST_ASSERT(solver.xNorm() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testCopyConstructor()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver(123, 456.789f, 0.1011f, 0.1213f);
        TEST_ASSERT(solver.aTolerance() == 0.1011f)
        TEST_ASSERT(solver.bTolerance() == 0.1213f)
        TEST_ASSERT(solver.condLimit() == 456.789f)
        TEST_ASSERT(solver.iterationLimit() == 123)
        TEST_ASSERT(solver.countIterations() == 0)
        TEST_ASSERT(solver.aNorm() == 0.0f)
        TEST_ASSERT(solver.aCond() == 0.0f)
        TEST_ASSERT(solver.rNorm() == 0.0f)
        TEST_ASSERT(solver.arNorm() == 0.0f)
        TEST_ASSERT(solver.xNorm() == 0.0f)

        TLeastSquareSystemSolver<klab::Real> solver2(solver);
        TEST_ASSERT(solver2.aTolerance() == 0.1011f)
        TEST_ASSERT(solver2.bTolerance() == 0.1213f)
        TEST_ASSERT(solver2.condLimit() == 456.789f)
        TEST_ASSERT(solver2.iterationLimit() == 123)
        TEST_ASSERT(solver2.countIterations() == 0)
        TEST_ASSERT(solver2.aNorm() == 0.0f)
        TEST_ASSERT(solver2.aCond() == 0.0f)
        TEST_ASSERT(solver2.rNorm() == 0.0f)
        TEST_ASSERT(solver2.arNorm() == 0.0f)
        TEST_ASSERT(solver2.xNorm() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testAffectationOperator()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver(123, 456.789f, 0.1011f, 0.1213f);
        TEST_ASSERT(solver.aTolerance() == 0.1011f)
        TEST_ASSERT(solver.bTolerance() == 0.1213f)
        TEST_ASSERT(solver.condLimit() == 456.789f)
        TEST_ASSERT(solver.iterationLimit() == 123)
        TEST_ASSERT(solver.countIterations() == 0)
        TEST_ASSERT(solver.aNorm() == 0.0f)
        TEST_ASSERT(solver.aCond() == 0.0f)
        TEST_ASSERT(solver.rNorm() == 0.0f)
        TEST_ASSERT(solver.arNorm() == 0.0f)
        TEST_ASSERT(solver.xNorm() == 0.0f)

        TLeastSquareSystemSolver<klab::Real> solver2;
        solver2 = solver;
        TEST_ASSERT(solver2.aTolerance() == 0.1011f)
        TEST_ASSERT(solver2.bTolerance() == 0.1213f)
        TEST_ASSERT(solver2.condLimit() == 456.789f)
        TEST_ASSERT(solver2.iterationLimit() == 123)
        TEST_ASSERT(solver2.countIterations() == 0)
        TEST_ASSERT(solver2.aNorm() == 0.0f)
        TEST_ASSERT(solver2.aCond() == 0.0f)
        TEST_ASSERT(solver2.rNorm() == 0.0f)
        TEST_ASSERT(solver2.arNorm() == 0.0f)
        TEST_ASSERT(solver2.xNorm() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSetATolerance()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.aTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)

        solver.setATolerance(0.1234f);
        TEST_ASSERT(solver.aTolerance() == 0.1234f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSetBTolerance()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.bTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)

        solver.setBTolerance(0.1234f);
        TEST_ASSERT(solver.bTolerance() == 0.1234f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSetCondLimit()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.condLimit() == 100000000.0f)

        solver.setCondLimit(123.456f);
        TEST_ASSERT(solver.condLimit() == 123.456f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSetIterationLimit()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.iterationLimit() == 0)

        solver.setIterationLimit(123);
        TEST_ASSERT(solver.iterationLimit() == 123)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testATolerance()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.aTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)

        solver.setATolerance(0.1234f);
        TEST_ASSERT(solver.aTolerance() == 0.1234f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testBTolerance()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.bTolerance() == klab::TTypeInfo<klab::Real>::EPSILON)

        solver.setBTolerance(0.1234f);
        TEST_ASSERT(solver.bTolerance() == 0.1234f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testCondLimit()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.condLimit() == 100000000.0f)

        solver.setCondLimit(123.456f);
        TEST_ASSERT(solver.condLimit() == 123.456f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testIterationLimit()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.iterationLimit() == 0)

        solver.setIterationLimit(123);
        TEST_ASSERT(solver.iterationLimit() == 123)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testCountIterations()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.countIterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testANorm()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.aNorm() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testACond()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.aCond() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testArNorm()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.arNorm() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testXNorm()
{
    try
    {
        TLeastSquareSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.xNorm() == 0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSolve()
{
    try
    {
        arma::Mat<klab::Real> A(6, 3);
        arma::Col<klab::Real> b(6);
        arma::Col<klab::Real> x;

        A(0, 0) = 1.0f;
        A(0, 1) = 0.2f;
        A(0, 2) = 0.1f;
        A(1, 0) = 1.0f;
        A(1, 1) = 0.5f;
        A(1, 2) = 0.3f;
        A(2, 0) = 1.0f;
        A(2, 1) = 0.6f;
        A(2, 2) = 0.4f;
        A(3, 0) = 1.0f;
        A(3, 1) = 0.8f;
        A(3, 2) = 0.9f;
        A(4, 0) = 1.0f;
        A(4, 1) = 1.0f;
        A(4, 2) = 1.1f;
        A(5, 0) = 1.0f;
        A(5, 1) = 1.1f;
        A(5, 2) = 1.4f;

        b[0]    = 0.17f;
        b[1]    = 0.26f;
        b[2]    = 0.28f;
        b[3]    = 0.23f;
        b[4]    = 0.27f;
        b[5]    = 0.34f;

        TLeastSquareSystemSolver<klab::Real> solver; 
        TEST_ASSERT(solver.aTolerance() >= 0.0)
        TEST_ASSERT(solver.bTolerance() >= 0.0)
        TEST_ASSERT(solver.condLimit() >= 0.0)
        TEST_ASSERT(solver.iterationLimit() >= 0)

        TMatrixLinearOperator<klab::Real> op(A);
        solver.solve<TMatrixLinearOperator<klab::Real> >(op, b, x);
        TEST_ASSERT(x.n_rows == 3);
        TEST_ASSERT(klab::Equals(x[0],  0.120303f))
        TEST_ASSERT(klab::Equals(x[1],  0.328389f))
        TEST_ASSERT(klab::Equals(x[2], -0.131202f))
        
        TEST_ASSERT(solver.countIterations() > 0)
        TEST_ASSERT(solver.aNorm() > 0.0)
        TEST_ASSERT(solver.aCond() > 0.0)
        TEST_ASSERT(solver.rNorm() > 0.0)
        TEST_ASSERT(solver.arNorm() > 0.0)
        TEST_ASSERT(solver.xNorm() > 0.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSolve_Errors()
{
    try
    {
        arma::Mat<klab::Real> A2_3(2, 3);
        arma::Mat<klab::Real> A3_2(3, 2);
        arma::Mat<klab::Real> A3_3(3, 3);
        arma::Col<klab::Real> b0;
        arma::Col<klab::Real> b2(2);
        arma::Col<klab::Real> b3(3);        
        arma::Col<klab::Real> x;

        TLeastSquareSystemSolver<klab::Real> solver; 


        // KNullOperatorLeastSquareException
        try                                             {solver.solve<TMatrixLinearOperator<klab::Real> >(klab::TMatrixLinearOperator<klab::Real>(arma::Mat<klab::Real>(0, 3)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)} 

        try                                             {solver.solve<TMatrixLinearOperator<klab::Real> >(klab::TMatrixLinearOperator<klab::Real>(arma::Mat<klab::Real>(3, 0)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)} 

        try                                             {solver.solve<TMatrixLinearOperator<klab::Real> >(klab::TMatrixLinearOperator<klab::Real>(arma::Mat<klab::Real>(0, 0)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}


        // KIncompatibleSizeLeastSquareException
        try                                             {solver.solve<TMatrixLinearOperator<klab::Real> >(klab::TMatrixLinearOperator<klab::Real>(A3_2), b0, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}

        try                                             {solver.solve<TMatrixLinearOperator<klab::Real> >(klab::TMatrixLinearOperator<klab::Real>(A3_2), b2, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}

        try                                             {solver.solve<TMatrixLinearOperator<klab::Real> >(klab::TMatrixLinearOperator<klab::Real>(A2_3), b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSolve_Matrix()
{
    try
    {
        arma::Mat<klab::Real> A(6, 3);
        arma::Col<klab::Real> b(6);
        arma::Col<klab::Real> x;

        A(0, 0) = 1.0f;
        A(0, 1) = 0.2f;
        A(0, 2) = 0.1f;
        A(1, 0) = 1.0f;
        A(1, 1) = 0.5f;
        A(1, 2) = 0.3f;
        A(2, 0) = 1.0f;
        A(2, 1) = 0.6f;
        A(2, 2) = 0.4f;
        A(3, 0) = 1.0f;
        A(3, 1) = 0.8f;
        A(3, 2) = 0.9f;
        A(4, 0) = 1.0f;
        A(4, 1) = 1.0f;
        A(4, 2) = 1.1f;
        A(5, 0) = 1.0f;
        A(5, 1) = 1.1f;
        A(5, 2) = 1.4f;

        b[0]    = 0.17f;
        b[1]    = 0.26f;
        b[2]    = 0.28f;
        b[3]    = 0.23f;
        b[4]    = 0.27f;
        b[5]    = 0.34f;
        
        TLeastSquareSystemSolver<klab::Real> solver; 
        TEST_ASSERT(solver.aTolerance() >= 0.0)
        TEST_ASSERT(solver.bTolerance() >= 0.0)
        TEST_ASSERT(solver.condLimit() >= 0.0)
        TEST_ASSERT(solver.iterationLimit() >= 0)

        solver.solve(A, b, x);

        TEST_ASSERT(x.n_rows == 3);
        TEST_ASSERT(klab::Equals(x[0],  0.120303f))
        TEST_ASSERT(klab::Equals(x[1],  0.328389f))
        TEST_ASSERT(klab::Equals(x[2], -0.131202f))

        TEST_ASSERT(solver.countIterations() > 0);
        TEST_ASSERT(solver.aNorm() > 0.0)
        TEST_ASSERT(solver.aCond() > 0.0)
        TEST_ASSERT(solver.rNorm() > 0.0)
        TEST_ASSERT(solver.arNorm() > 0.0)
        TEST_ASSERT(solver.xNorm() > 0.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSolve_Matrix_Errors()
{
    try
    {
        arma::Mat<klab::Real> A2_3(2, 3);
        arma::Mat<klab::Real> A3_2(3, 2);
        arma::Mat<klab::Real> A3_3(3, 3);
        arma::Col<klab::Real> b0;
        arma::Col<klab::Real> b2(2);
        arma::Col<klab::Real> b3(3);
        arma::Col<klab::Real> x;

        TLeastSquareSystemSolver<klab::Real> solver; 


        // KNullOperatorLeastSquareException
        try                                             {solver.solve(arma::Mat<klab::Real>(0, 3), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)} 

        try                                             {solver.solve(arma::Mat<klab::Real>(3, 0), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)} 

        try                                             {solver.solve(arma::Mat<klab::Real>(0, 0), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}


        // KIncompatibleSizeLeastSquareException
        try                                             {solver.solve(A3_2, b0, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}

        try                                             {solver.solve(A3_2, b2, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}

        try                                             {solver.solve(A2_3, b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSolve_Complex()
{
    try
    {
        arma::Mat<std::complex<klab::Real> > A(6, 3);
        arma::Col<std::complex<klab::Real> > b(6);
        arma::Col<std::complex<klab::Real> > x;

        A(0, 0) = 1.0f;
        A(0, 1) = 0.2f;
        A(0, 2) = 0.1f;
        A(1, 0) = 1.0f;
        A(1, 1) = 0.5f;
        A(1, 2) = 0.3f;
        A(2, 0) = 1.0f;
        A(2, 1) = 0.6f;
        A(2, 2) = 0.4f;
        A(3, 0) = 1.0f;
        A(3, 1) = 0.8f;
        A(3, 2) = 0.9f;
        A(4, 0) = 1.0f;
        A(4, 1) = 1.0f;
        A(4, 2) = 1.1f;
        A(5, 0) = 1.0f;
        A(5, 1) = 1.1f;
        A(5, 2) = 1.4f;

        b[0]    = 0.17f;
        b[1]    = 0.26f;
        b[2]    = 0.28f;
        b[3]    = 0.23f;
        b[4]    = 0.27f;
        b[5]    = 0.34f;

        TLeastSquareSystemSolver<klab::Real, std::complex<klab::Real> > solver; 
        TEST_ASSERT(solver.aTolerance() >= 0.0)
        TEST_ASSERT(solver.bTolerance() >= 0.0)
        TEST_ASSERT(solver.condLimit() >= 0.0)
        TEST_ASSERT(solver.iterationLimit() >= 0)

        klab::TMatrixLinearOperator<std::complex<klab::Real> > op(A);
        solver.solve<TMatrixLinearOperator<std::complex<klab::Real> > >(op, b, x);
        TEST_ASSERT(x.n_rows == 3);
        TEST_ASSERT(klab::Equals(x[0], std::complex<klab::Real>( 0.120303f, 0.0f)))
        TEST_ASSERT(klab::Equals(x[1], std::complex<klab::Real>( 0.328389f, 0.0f)))
        TEST_ASSERT(klab::Equals(x[2], std::complex<klab::Real>(-0.131202f, 0.0f)))
        
        TEST_ASSERT(solver.countIterations() > 0)
        TEST_ASSERT(solver.aNorm() > 0.0)
        TEST_ASSERT(solver.aCond() > 0.0)
        TEST_ASSERT(solver.rNorm() > 0.0)
        TEST_ASSERT(solver.arNorm() > 0.0)
        TEST_ASSERT(solver.xNorm() > 0.0)

        arma::Mat<std::complex<klab::DoubleReal> > A2(12, 2);
        arma::Col<std::complex<klab::DoubleReal> > b2(12);
        arma::Col<std::complex<klab::DoubleReal> > x2;

        A2(0, 0) = std::complex<klab::DoubleReal>( 0.0625,              0.0);
        A2(1, 0) = std::complex<klab::DoubleReal>( 0.0441941738241592, -0.0441941738241592);
        A2(2, 0) = std::complex<klab::DoubleReal>( 0.0,                -0.0625);
        A2(3, 0) = std::complex<klab::DoubleReal>(-0.0625,              0.0);
        A2(4, 0) = std::complex<klab::DoubleReal>(-0.0441941738241592,  0.0441941738241592);
        A2(5, 0) = std::complex<klab::DoubleReal>( 0.0,                 0.0625);
        A2(6, 0) = std::complex<klab::DoubleReal>( 0.0625,              0.0);
        A2(7, 0) = std::complex<klab::DoubleReal>( 0.0441941738241592, -0.0441941738241592);
        A2(8, 0) = std::complex<klab::DoubleReal>( 0.0,                -0.0625);
        A2(9, 0) = std::complex<klab::DoubleReal>(-0.0625,              0.0);
        A2(10,0) = std::complex<klab::DoubleReal>(-0.0441941738241592,  0.0441941738241592);
        A2(11,0) = std::complex<klab::DoubleReal>( 0.0,                 0.0625);
        A2(0, 1) = std::complex<klab::DoubleReal>( 0.0625,              0.0);
        A2(1, 1) = std::complex<klab::DoubleReal>( 0.0441941738241592,  0.0441941738241592);
        A2(2, 1) = std::complex<klab::DoubleReal>( 0.0,                 0.0625);
        A2(3, 1) = std::complex<klab::DoubleReal>(-0.0625,              0.0);
        A2(4, 1) = std::complex<klab::DoubleReal>(-0.0441941738241592, -0.0441941738241592);
        A2(5, 1) = std::complex<klab::DoubleReal>( 0.0,                -0.0625);
        A2(6, 1) = std::complex<klab::DoubleReal>( 0.0625,              0.0);
        A2(7, 1) = std::complex<klab::DoubleReal>( 0.0441941738241592,  0.0441941738241592);
        A2(8, 1) = std::complex<klab::DoubleReal>( 0.0,                 0.0625);
        A2(9, 1) = std::complex<klab::DoubleReal>(-0.0625,              0.0);
        A2(10,1) = std::complex<klab::DoubleReal>(-0.0441941738241592, -0.0441941738241592);
        A2(11,1) = std::complex<klab::DoubleReal>( 0.0,                -0.0625);

        b2[0] = std::complex<klab::DoubleReal>( 2.82842712474619, 0.0);
        b2[1] = std::complex<klab::DoubleReal>( 4.0,              0.0);
        b2[2] = std::complex<klab::DoubleReal>( 2.82842712474619, 0.0);
        b2[3] = std::complex<klab::DoubleReal>(-4.82842712474619, 0.0);
        b2[4] = std::complex<klab::DoubleReal>(-6.0,              0.0);
        b2[5] = std::complex<klab::DoubleReal>(-4.82842712474619, 0.0);
        b2[6] = std::complex<klab::DoubleReal>( 0.828427124746189,0.0);
        b2[7] = std::complex<klab::DoubleReal>( 2.0,              0.0);
        b2[8] = std::complex<klab::DoubleReal>( 0.828427124746193,0.0);
        b2[9] = std::complex<klab::DoubleReal>(-2.82842712474619, 0.0);
        b2[10]= std::complex<klab::DoubleReal>(-4.0,              0.0);
        b2[11]= std::complex<klab::DoubleReal>(-2.82842712474619, 0.0);

        TLeastSquareSystemSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > solver2; 
        TEST_ASSERT(solver2.aTolerance() >= 0.0)
        TEST_ASSERT(solver2.bTolerance() >= 0.0)
        TEST_ASSERT(solver2.condLimit() >= 0.0)
        TEST_ASSERT(solver2.iterationLimit() >= 0)

        klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> > op2(A2);
        solver2.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(op2, b2, x2);
        TEST_ASSERT(x2.n_rows == 2)
        TEST_ASSERT(klab::Equals(x2[0], std::complex<klab::DoubleReal>(22.6274169979695,  22.6274169979695), 1e-12))
        TEST_ASSERT(klab::Equals(x2[1], std::complex<klab::DoubleReal>(22.6274169979695, -22.6274169979695), 1e-12))
        
        TEST_ASSERT(solver2.countIterations() > 0)
        TEST_ASSERT(solver2.aNorm() > 0.0)
        TEST_ASSERT(solver2.aCond() > 0.0)
        TEST_ASSERT(solver2.rNorm() > 0.0)
        TEST_ASSERT(solver2.arNorm() > 0.0)
        TEST_ASSERT(solver2.xNorm() > 0.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSolve_ErrorsComplex()
{
    try
    {
        arma::Mat<std::complex<klab::Real> > A2_3(2, 3);
        arma::Mat<std::complex<klab::Real> > A3_2(3, 2);
        arma::Mat<std::complex<klab::Real> > A3_3(3, 3);
        arma::Col<std::complex<klab::Real> > b0;
        arma::Col<std::complex<klab::Real> > b2(2);
        arma::Col<std::complex<klab::Real> > b3(3);        
        arma::Col<std::complex<klab::Real> > x;

        b2[0] = std::complex<klab::Real>(1.0, 0.0);
        b2[1] = std::complex<klab::Real>(2.0, 0.0);

        TLeastSquareSystemSolver<klab::Real, std::complex<klab::Real> > solver; 


        // KNullOperatorLeastSquareException
        try                                             {solver.solve<TMatrixLinearOperator<std::complex<klab::Real> > >(klab::TMatrixLinearOperator<std::complex<klab::Real> >(arma::Mat<std::complex<klab::Real> >(0, 3)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)} 

        try                                             {solver.solve<TMatrixLinearOperator<std::complex<klab::Real> > >(klab::TMatrixLinearOperator<std::complex<klab::Real> >(arma::Mat<std::complex<klab::Real> >(3, 0)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)} 

        try                                             {solver.solve<TMatrixLinearOperator<std::complex<klab::Real> > >(klab::TMatrixLinearOperator<std::complex<klab::Real> >(arma::Mat<std::complex<klab::Real> >(0, 0)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}


        // KIncompatibleSizeLeastSquareException
        try                                             {solver.solve<TMatrixLinearOperator<std::complex<klab::Real> > >(klab::TMatrixLinearOperator<std::complex<klab::Real> >(A3_2), b0, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}

        try                                             {solver.solve<TMatrixLinearOperator<std::complex<klab::Real> > >(klab::TMatrixLinearOperator<std::complex<klab::Real> >(A3_2), b2, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}

        try                                             {solver.solve<TMatrixLinearOperator<std::complex<klab::Real> > >(klab::TMatrixLinearOperator<std::complex<klab::Real> >(A2_3), b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSolve_MatrixComplex()
{
    try
    {
        arma::Mat<std::complex<klab::Real> > A(6, 3);
        arma::Col<std::complex<klab::Real> > b(6);
        arma::Col<std::complex<klab::Real> > x;

        A(0, 0) = 1.0f;
        A(0, 1) = 0.2f;
        A(0, 2) = 0.1f;
        A(1, 0) = 1.0f;
        A(1, 1) = 0.5f;
        A(1, 2) = 0.3f;
        A(2, 0) = 1.0f;
        A(2, 1) = 0.6f;
        A(2, 2) = 0.4f;
        A(3, 0) = 1.0f;
        A(3, 1) = 0.8f;
        A(3, 2) = 0.9f;
        A(4, 0) = 1.0f;
        A(4, 1) = 1.0f;
        A(4, 2) = 1.1f;
        A(5, 0) = 1.0f;
        A(5, 1) = 1.1f;
        A(5, 2) = 1.4f;

        b[0]    = 0.17f;
        b[1]    = 0.26f;
        b[2]    = 0.28f;
        b[3]    = 0.23f;
        b[4]    = 0.27f;
        b[5]    = 0.34f;
        
        TLeastSquareSystemSolver<klab::Real, std::complex<klab::Real> > solver; 
        TEST_ASSERT(solver.aTolerance() >= 0.0)
        TEST_ASSERT(solver.bTolerance() >= 0.0)
        TEST_ASSERT(solver.condLimit() >= 0.0)
        TEST_ASSERT(solver.iterationLimit() >= 0)

        solver.solve(A, b, x);

        TEST_ASSERT(x.n_rows == 3)
        TEST_ASSERT(klab::Equals(x[0], std::complex<klab::Real>(0.120303f, 0.0f)))
        TEST_ASSERT(klab::Equals(x[1], std::complex<klab::Real>(0.328389f, 0.0f)))
        TEST_ASSERT(klab::Equals(x[2], std::complex<klab::Real>(-0.131202f, 0.0f)))

        TEST_ASSERT(solver.countIterations() > 0)
        TEST_ASSERT(solver.aNorm() > 0.0)
        TEST_ASSERT(solver.aCond() > 0.0)
        TEST_ASSERT(solver.rNorm() > 0.0)
        TEST_ASSERT(solver.arNorm() > 0.0)
        TEST_ASSERT(solver.xNorm() > 0.0)


        arma::Mat<std::complex<klab::DoubleReal> > A2(12, 2);
        arma::Col<std::complex<klab::DoubleReal> > b2(12);
        arma::Col<std::complex<klab::DoubleReal> > x2;

        A2(0, 0) = std::complex<klab::DoubleReal>( 0.0625,              0.0);
        A2(1, 0) = std::complex<klab::DoubleReal>( 0.0441941738241592, -0.0441941738241592);
        A2(2, 0) = std::complex<klab::DoubleReal>( 0.0,                -0.0625);
        A2(3, 0) = std::complex<klab::DoubleReal>(-0.0625,              0.0);
        A2(4, 0) = std::complex<klab::DoubleReal>(-0.0441941738241592,  0.0441941738241592);
        A2(5, 0) = std::complex<klab::DoubleReal>( 0.0,                 0.0625);
        A2(6, 0) = std::complex<klab::DoubleReal>( 0.0625,              0.0);
        A2(7, 0) = std::complex<klab::DoubleReal>( 0.0441941738241592, -0.0441941738241592);
        A2(8, 0) = std::complex<klab::DoubleReal>( 0.0,                -0.0625);
        A2(9, 0) = std::complex<klab::DoubleReal>(-0.0625,              0.0);
        A2(10,0) = std::complex<klab::DoubleReal>(-0.0441941738241592,  0.0441941738241592);
        A2(11,0) = std::complex<klab::DoubleReal>( 0.0,                 0.0625);
        A2(0, 1) = std::complex<klab::DoubleReal>( 0.0625,              0.0);
        A2(1, 1) = std::complex<klab::DoubleReal>( 0.0441941738241592,  0.0441941738241592);
        A2(2, 1) = std::complex<klab::DoubleReal>( 0.0,                 0.0625);
        A2(3, 1) = std::complex<klab::DoubleReal>(-0.0625,              0.0);
        A2(4, 1) = std::complex<klab::DoubleReal>(-0.0441941738241592, -0.0441941738241592);
        A2(5, 1) = std::complex<klab::DoubleReal>( 0.0,                -0.0625);
        A2(6, 1) = std::complex<klab::DoubleReal>( 0.0625,              0.0);
        A2(7, 1) = std::complex<klab::DoubleReal>( 0.0441941738241592,  0.0441941738241592);
        A2(8, 1) = std::complex<klab::DoubleReal>( 0.0,                 0.0625);
        A2(9, 1) = std::complex<klab::DoubleReal>(-0.0625,              0.0);
        A2(10,1) = std::complex<klab::DoubleReal>(-0.0441941738241592, -0.0441941738241592);
        A2(11,1) = std::complex<klab::DoubleReal>( 0.0,                -0.0625);

        b2[0] = std::complex<klab::DoubleReal>( 2.82842712474619, 0.0);
        b2[1] = std::complex<klab::DoubleReal>( 4.0,              0.0);
        b2[2] = std::complex<klab::DoubleReal>( 2.82842712474619, 0.0);
        b2[3] = std::complex<klab::DoubleReal>(-4.82842712474619, 0.0);
        b2[4] = std::complex<klab::DoubleReal>(-6.0,              0.0);
        b2[5] = std::complex<klab::DoubleReal>(-4.82842712474619, 0.0);
        b2[6] = std::complex<klab::DoubleReal>( 0.828427124746189,0.0);
        b2[7] = std::complex<klab::DoubleReal>( 2.0,              0.0);
        b2[8] = std::complex<klab::DoubleReal>( 0.828427124746193,0.0);
        b2[9] = std::complex<klab::DoubleReal>(-2.82842712474619, 0.0);
        b2[10]= std::complex<klab::DoubleReal>(-4.0,              0.0);
        b2[11]= std::complex<klab::DoubleReal>(-2.82842712474619, 0.0);

        TLeastSquareSystemSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > solver2; 
        TEST_ASSERT(solver2.aTolerance() >= 0.0)
        TEST_ASSERT(solver2.bTolerance() >= 0.0)
        TEST_ASSERT(solver2.condLimit() >= 0.0)
        TEST_ASSERT(solver2.iterationLimit() >= 0)

        solver2.solve(A2, b2, x2);
        TEST_ASSERT(x2.n_rows == 2)
        TEST_ASSERT(klab::Equals(x2[0], std::complex<klab::DoubleReal>(22.6274169979695,  22.6274169979695), 1e-12))
        TEST_ASSERT(klab::Equals(x2[1], std::complex<klab::DoubleReal>(22.6274169979695, -22.6274169979695), 1e-12))
        
        TEST_ASSERT(solver2.countIterations() > 0)
        TEST_ASSERT(solver2.aNorm() > 0.0)
        TEST_ASSERT(solver2.aCond() > 0.0)
        TEST_ASSERT(solver2.rNorm() > 0.0)
        TEST_ASSERT(solver2.arNorm() > 0.0)
        TEST_ASSERT(solver2.xNorm() > 0.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLeastSquareSystemSolverUnitTest::testSolve_Matrix_ErrorsComplex()
{
    try
    {
        arma::Mat<std::complex<klab::Real> > A2_3(2, 3);
        arma::Mat<std::complex<klab::Real> > A3_2(3, 2);
        arma::Mat<std::complex<klab::Real> > A3_3(3, 3);
        arma::Col<std::complex<klab::Real> > b0;
        arma::Col<std::complex<klab::Real> > b2(2);
        arma::Col<std::complex<klab::Real> > b3(3);
        arma::Col<std::complex<klab::Real> > x;

        TLeastSquareSystemSolver<klab::Real, std::complex<klab::Real> > solver; 


        // KNullOperatorLeastSquareException
        try                                             {solver.solve(arma::Mat<std::complex<klab::Real> >(0, 3), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)} 

        try                                             {solver.solve(arma::Mat<std::complex<klab::Real> >(3, 0), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)} 

        try                                             {solver.solve(arma::Mat<std::complex<klab::Real> >(0, 0), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorLeastSquareException&)       {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}


        // KIncompatibleSizeLeastSquareException
        try                                             {solver.solve(A3_2, b0, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}

        try                                             {solver.solve(A3_2, b2, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}

        try                                             {solver.solve(A2_3, b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeLeastSquareException&)   {TEST_ASSERT(true)}
        catch(...)                                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
