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

#include "ConjugateGradientSystemSolverUnitTest.h"
#include "../include/ConjugateGradientSystemSolver.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KConjugateGradientSystemSolverUnitTest::KConjugateGradientSystemSolverUnitTest() : Test::Suite()
{
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testDefaultConstructor)
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testToleranceConstructor)
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testToleranceIterationLimitConstructor)
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testCopyConstructor)
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testAffectationOperator)

    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSetTolerance)
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSetIterationLimit)
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testTolerance)
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testIterationLimit)
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testResidual)
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testCountIterations)

    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSolve)  
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSolve_Errors)  
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSolve_Matrix)  
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSolve_Matrix_Errors) 
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSolve_Complex)  
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSolve_ErrorsComplex)  
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSolve_MatrixComplex)  
    TEST_ADD(KConjugateGradientSystemSolverUnitTest::testSolve_Matrix_ErrorsComplex)  
}

// ---------------------------------------------------------------------------------------------------- //

KConjugateGradientSystemSolverUnitTest::~KConjugateGradientSystemSolverUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testDefaultConstructor()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.tolerance() == klab::TTypeInfo<klab::Real>::EPSILON)
        TEST_ASSERT(solver.iterationLimit() == 0)
        TEST_ASSERT(klab::Equals(solver.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver.countIterations() == 0)

        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2;
        TEST_ASSERT(solver2.tolerance() == klab::TTypeInfo<klab::Real>::EPSILON)
        TEST_ASSERT(solver2.iterationLimit() == 0)
        TEST_ASSERT(klab::Equals(solver2.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver2.countIterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testToleranceConstructor()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver(1e-2f);
        TEST_ASSERT(klab::Equals(solver.tolerance(), 1e-2f))
        TEST_ASSERT(solver.iterationLimit() == 0)
        TEST_ASSERT(klab::Equals(solver.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver.countIterations() == 0)

        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2(1e-2f);
        TEST_ASSERT(klab::Equals(solver2.tolerance(), 1e-2f))
        TEST_ASSERT(solver2.iterationLimit() == 0)
        TEST_ASSERT(klab::Equals(solver2.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver2.countIterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testToleranceIterationLimitConstructor()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver(1e-2f, 10);
        TEST_ASSERT(klab::Equals(solver.tolerance(), 1e-2f))
        TEST_ASSERT(solver.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solver.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver.countIterations() == 0)

        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2(1e-2f, 10);
        TEST_ASSERT(klab::Equals(solver2.tolerance(), 1e-2f))
        TEST_ASSERT(solver2.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solver2.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver2.countIterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testCopyConstructor()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver(1e-2f, 10);
        TEST_ASSERT(klab::Equals(solver.tolerance(), 1e-2f))
        TEST_ASSERT(solver.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solver.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver.countIterations() == 0)

        TConjugateGradientSystemSolver<klab::Real> solverCopy(solver);
        TEST_ASSERT(klab::Equals(solverCopy.tolerance(), 1e-2f))
        TEST_ASSERT(solverCopy.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solverCopy.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solverCopy.countIterations() == 0)


        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2(1e-2f, 10);
        TEST_ASSERT(klab::Equals(solver2.tolerance(), 1e-2f))
        TEST_ASSERT(solver2.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solver2.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver2.countIterations() == 0)

        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solverCopy2(solver2);
        TEST_ASSERT(klab::Equals(solverCopy2.tolerance(), 1e-2f))
        TEST_ASSERT(solverCopy2.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solverCopy2.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solverCopy2.countIterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testAffectationOperator()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver(1e-2f, 10);
        TEST_ASSERT(klab::Equals(solver.tolerance(), 1e-2f))
        TEST_ASSERT(solver.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solver.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver.countIterations() == 0)

        TConjugateGradientSystemSolver<klab::Real> solverCopy;
        solverCopy = solver;
        TEST_ASSERT(klab::Equals(solverCopy.tolerance(), 1e-2f))
        TEST_ASSERT(solverCopy.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solverCopy.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solverCopy.countIterations() == 0)


        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2(1e-2f, 10);
        TEST_ASSERT(klab::Equals(solver2.tolerance(), 1e-2f))
        TEST_ASSERT(solver2.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solver2.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solver2.countIterations() == 0)

        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solverCopy2;
        solverCopy2 = solver2;
        TEST_ASSERT(klab::Equals(solverCopy2.tolerance(), 1e-2f))
        TEST_ASSERT(solverCopy2.iterationLimit() == 10)
        TEST_ASSERT(klab::Equals(solverCopy2.residual(), klab::TTypeInfo<klab::Real>::ZERO))
        TEST_ASSERT(solverCopy2.countIterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSetTolerance()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.tolerance() == klab::TTypeInfo<klab::Real>::EPSILON)

        solver.setTolerance(1e-2f);
        TEST_ASSERT(klab::Equals(solver.tolerance(), 1e-2f))


        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2;
        TEST_ASSERT(solver2.tolerance() == klab::TTypeInfo<klab::Real>::EPSILON)

        solver2.setTolerance(1e-2f);
        TEST_ASSERT(klab::Equals(solver2.tolerance(), 1e-2f))

    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSetIterationLimit()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.iterationLimit() == 0)

        solver.setIterationLimit(10);
        TEST_ASSERT(solver.iterationLimit() == 10)


        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2;
        TEST_ASSERT(solver2.iterationLimit() == 0)

        solver2.setIterationLimit(10);
        TEST_ASSERT(solver2.iterationLimit() == 10)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testTolerance()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.tolerance() == klab::TTypeInfo<klab::Real>::EPSILON)

        solver.setTolerance(1e-2f);
        TEST_ASSERT(klab::Equals(solver.tolerance(), 1e-2f))


        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2;
        TEST_ASSERT(solver2.tolerance() == klab::TTypeInfo<klab::Real>::EPSILON)

        solver2.setTolerance(1e-2f);
        TEST_ASSERT(klab::Equals(solver2.tolerance(), 1e-2f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testIterationLimit()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.iterationLimit() == 0)

        solver.setIterationLimit(10);
        TEST_ASSERT(solver.iterationLimit() == 10)


        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2;
        TEST_ASSERT(solver2.iterationLimit() == 0)

        solver2.setIterationLimit(10);
        TEST_ASSERT(solver2.iterationLimit() == 10)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testResidual()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver;
        TEST_ASSERT(klab::Equals(solver.residual(), klab::TTypeInfo<klab::Real>::ZERO))

        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2;
        TEST_ASSERT(klab::Equals(solver2.residual(), klab::TTypeInfo<klab::Real>::ZERO))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testCountIterations()
{
    try
    {
        TConjugateGradientSystemSolver<klab::Real> solver;
        TEST_ASSERT(solver.countIterations() == 0)

        TConjugateGradientSystemSolver<klab::Real, std::complex<klab::Real> > solver2;
        TEST_ASSERT(solver2.countIterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSolve()
{
    try
    {
        klab::DoubleReal precision = 1e-6;

        arma::Mat<klab::DoubleReal> a(3, 3);
        arma::Col<klab::DoubleReal> b(3);
        arma::Col<klab::DoubleReal> x0(3);
        arma::Col<klab::DoubleReal> x;
        arma::Col<klab::DoubleReal> x2;
        arma::Col<klab::DoubleReal> x3;
        arma::Col<klab::DoubleReal> x4;

        a(0, 0) = 8.0;
        a(0, 1) = 3.0;
        a(0, 2) = 4.0;
        a(1, 0) = 3.0;
        a(1, 1) = 5.0;
        a(1, 2) = 9.0;
        a(2, 0) = 4.0;
        a(2, 1) = 9.0;
        a(2, 2) = 2.0;

        b[0] = 1.0;
        b[1] = 2.0;
        b[2] = 3.0;

        x0.fill(0.0);


        TConjugateGradientSystemSolver<klab::DoubleReal> solver(1e-6);

        klab::TMatrixLinearOperator<klab::DoubleReal> op(a);
        solver.solve<klab::TMatrixLinearOperator<klab::DoubleReal> >(op, b, x);
        TEST_ASSERT(x.n_rows == 3)
        TEST_ASSERT(klab::Equals(x[0], -0.02222222, precision))
        TEST_ASSERT(klab::Equals(x[1],  0.33333333, precision))
        TEST_ASSERT(klab::Equals(x[2],  0.04444444, precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)

        solver.solve<klab::TMatrixLinearOperator<klab::DoubleReal> >(op, b, x0, x2);
        TEST_ASSERT(x2.n_rows == 3)
        TEST_ASSERT(klab::Equals(x2[0], -0.02222222, precision))
        TEST_ASSERT(klab::Equals(x2[1],  0.33333333, precision))
        TEST_ASSERT(klab::Equals(x2[2],  0.04444444, precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)

        solver.solve(op, b, x3);
        TEST_ASSERT(x3.n_rows == 3)
        TEST_ASSERT(klab::Equals(x3[0], -0.02222222, precision))
        TEST_ASSERT(klab::Equals(x3[1],  0.33333333, precision))
        TEST_ASSERT(klab::Equals(x3[2],  0.04444444, precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)

        solver.solve(op, b, x0, x4);
        TEST_ASSERT(x4.n_rows == 3)
        TEST_ASSERT(klab::Equals(x4[0], -0.02222222, precision))
        TEST_ASSERT(klab::Equals(x4[1],  0.33333333, precision))
        TEST_ASSERT(klab::Equals(x4[2],  0.04444444, precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSolve_Errors()
{
    try
    {
        arma::Mat<klab::DoubleReal> A2_2(2, 2);
        arma::Mat<klab::DoubleReal> A2_3(2, 3);
        arma::Mat<klab::DoubleReal> A3_2(3, 2);
        arma::Mat<klab::DoubleReal> A3_3(3, 3);
        arma::Col<klab::DoubleReal> b0;
        arma::Col<klab::DoubleReal> b2(2);
        arma::Col<klab::DoubleReal> b3(3);
        arma::Col<klab::DoubleReal> x00;
        arma::Col<klab::DoubleReal> x01(1);
        arma::Col<klab::DoubleReal> x02(2);
        arma::Col<klab::DoubleReal> x03(3);
        arma::Col<klab::DoubleReal> x;

        b3.fill(0.0);


        TConjugateGradientSystemSolver<klab::DoubleReal> solver; 


        // KNullOperatorConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 3)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(3, 0)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(arma::Mat<klab::DoubleReal>(0, 0)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(A2_3), b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(A3_2), b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(A3_3), b0, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(A3_3), b2, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(A2_2), b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(A3_3), b3, x00, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(A3_3), b3, x01, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(A3_3), b3, x02, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KZeroNormConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<klab::DoubleReal> >(klab::TMatrixLinearOperator<klab::DoubleReal>(A3_3), b3, x03, x); TEST_ASSERT(false)}
        catch(KZeroNormConjugateGradientException&)         {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSolve_Matrix()
{
    try
    {
        klab::DoubleReal precision = 1e-6;

        arma::Mat<klab::DoubleReal> a(3, 3);
        arma::Col<klab::DoubleReal> b(3);
        arma::Col<klab::DoubleReal> x0(3);
        arma::Col<klab::DoubleReal> x;
        arma::Col<klab::DoubleReal> x2;

        a(0, 0) = 8.0;
        a(0, 1) = 3.0;
        a(0, 2) = 4.0;
        a(1, 0) = 3.0;
        a(1, 1) = 5.0;
        a(1, 2) = 9.0;
        a(2, 0) = 4.0;
        a(2, 1) = 9.0;
        a(2, 2) = 2.0;

        b[0] = 1.0;
        b[1] = 2.0;
        b[2] = 3.0;

        x0.fill(0.0);


        TConjugateGradientSystemSolver<klab::DoubleReal> solver(1e-6);

        solver.solve(a, b, x);
        TEST_ASSERT(x.n_rows == 3)
        TEST_ASSERT(klab::Equals(x[0], -0.02222222, precision))
        TEST_ASSERT(klab::Equals(x[1],  0.33333333, precision))
        TEST_ASSERT(klab::Equals(x[2],  0.04444444, precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)

        solver.solve(a, b, x0, x2);
        TEST_ASSERT(x2.n_rows == 3)
        TEST_ASSERT(klab::Equals(x2[0], -0.02222222, precision))
        TEST_ASSERT(klab::Equals(x2[1],  0.33333333, precision))
        TEST_ASSERT(klab::Equals(x2[2],  0.04444444, precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSolve_Matrix_Errors()
{
    try
    {
        arma::Mat<klab::DoubleReal> A2_2(2, 2);
        arma::Mat<klab::DoubleReal> A2_3(2, 3);
        arma::Mat<klab::DoubleReal> A3_2(3, 2);
        arma::Mat<klab::DoubleReal> A3_3(3, 3);
        arma::Col<klab::DoubleReal> b0;
        arma::Col<klab::DoubleReal> b2(2);
        arma::Col<klab::DoubleReal> b3(3);
        arma::Col<klab::DoubleReal> x00;
        arma::Col<klab::DoubleReal> x01(1);
        arma::Col<klab::DoubleReal> x02(2);
        arma::Col<klab::DoubleReal> x03(3);
        arma::Col<klab::DoubleReal> x;

        b3.fill(0.0);


        TConjugateGradientSystemSolver<klab::DoubleReal> solver; 


        // KNullOperatorConjugateGradientException
        try                                                 {solver.solve(arma::Mat<klab::DoubleReal>(0, 3), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve(arma::Mat<klab::DoubleReal>(3, 0), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve(arma::Mat<klab::DoubleReal>(0, 0), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve(A2_3, b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve(A3_2, b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve(A3_3, b0, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve(A3_3, b2, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve(A2_2, b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve(A3_3, b3, x00, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve(A3_3, b3, x01, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve(A3_3, b3, x02, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KZeroNormSolveConjugateGradientException
        try                                                 {solver.solve(A3_3, b3, x03, x); TEST_ASSERT(false)}
        catch(KZeroNormConjugateGradientException&)         {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSolve_Complex()
{
    try
    {
        klab::DoubleReal precision = 1e-6;

        arma::Mat<std::complex<klab::DoubleReal> > a(3, 3);
        arma::Col<std::complex<klab::DoubleReal> > b(3);
        arma::Col<std::complex<klab::DoubleReal> > x0(3);
        arma::Col<std::complex<klab::DoubleReal> > x;
        arma::Col<std::complex<klab::DoubleReal> > x2;
        arma::Col<std::complex<klab::DoubleReal> > x3;
        arma::Col<std::complex<klab::DoubleReal> > x4;

        a(0, 0) = std::complex<klab::DoubleReal>(1.0,  0.0);
        a(0, 1) = std::complex<klab::DoubleReal>(4.0,  5.0);
        a(0, 2) = std::complex<klab::DoubleReal>(7.0, -8.0);
        a(1, 0) = std::complex<klab::DoubleReal>(4.0, -5.0);
        a(1, 1) = std::complex<klab::DoubleReal>(5.0,  0.0);
        a(1, 2) = std::complex<klab::DoubleReal>(6.0,  7.0);
        a(2, 0) = std::complex<klab::DoubleReal>(7.0,  8.0);
        a(2, 1) = std::complex<klab::DoubleReal>(6.0, -7.0);
        a(2, 2) = std::complex<klab::DoubleReal>(9.0,  0.0);

        b[0] = std::complex<klab::DoubleReal>(77.0, 4.0);
        b[1] = std::complex<klab::DoubleReal>(14.0, 33.0);
        b[2] = std::complex<klab::DoubleReal>( 9.0, 26.0);

        x0.fill(std::complex<klab::DoubleReal>(0.0, 0.0));


        TConjugateGradientSystemSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > solver(1e-6);

        klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> > op(a);
        solver.solve<klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(op, b, x);
        TEST_ASSERT(x.n_rows == 3)
        TEST_ASSERT(klab::Equals(x[0], std::complex<klab::DoubleReal>(1.0,  2.0), precision))
        TEST_ASSERT(klab::Equals(x[1], std::complex<klab::DoubleReal>(2.0, -3.0), precision))
        TEST_ASSERT(klab::Equals(x[2], std::complex<klab::DoubleReal>(3.0,  4.0), precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)

        solver.solve<klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(op, b, x0, x2);
        TEST_ASSERT(x2.n_rows == 3)
        TEST_ASSERT(klab::Equals(x2[0], std::complex<klab::DoubleReal>(1.0,  2.0), precision))
        TEST_ASSERT(klab::Equals(x2[1], std::complex<klab::DoubleReal>(2.0, -3.0), precision))
        TEST_ASSERT(klab::Equals(x2[2], std::complex<klab::DoubleReal>(3.0,  4.0), precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)

        solver.solve(op, b, x3);
        TEST_ASSERT(x3.n_rows == 3)
        TEST_ASSERT(klab::Equals(x3[0], std::complex<klab::DoubleReal>(1.0,  2.0), precision))
        TEST_ASSERT(klab::Equals(x3[1], std::complex<klab::DoubleReal>(2.0, -3.0), precision))
        TEST_ASSERT(klab::Equals(x3[2], std::complex<klab::DoubleReal>(3.0,  4.0), precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)

        solver.solve(op, b, x0, x4);
        TEST_ASSERT(x4.n_rows == 3)
        TEST_ASSERT(klab::Equals(x4[0], std::complex<klab::DoubleReal>(1.0,  2.0), precision))
        TEST_ASSERT(klab::Equals(x4[1], std::complex<klab::DoubleReal>(2.0, -3.0), precision))
        TEST_ASSERT(klab::Equals(x4[2], std::complex<klab::DoubleReal>(3.0,  4.0), precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSolve_ErrorsComplex()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > A2_2(2, 2);
        arma::Mat<std::complex<klab::DoubleReal> > A2_3(2, 3);
        arma::Mat<std::complex<klab::DoubleReal> > A3_2(3, 2);
        arma::Mat<std::complex<klab::DoubleReal> > A3_3(3, 3);
        arma::Col<std::complex<klab::DoubleReal> > b0;
        arma::Col<std::complex<klab::DoubleReal> > b2(2);
        arma::Col<std::complex<klab::DoubleReal> > b3(3);
        arma::Col<std::complex<klab::DoubleReal> > x00;
        arma::Col<std::complex<klab::DoubleReal> > x01(1);
        arma::Col<std::complex<klab::DoubleReal> > x02(2);
        arma::Col<std::complex<klab::DoubleReal> > x03(3);
        arma::Col<std::complex<klab::DoubleReal> > x;

        b3.fill(std::complex<klab::DoubleReal>(0.0, 0.0));


        TConjugateGradientSystemSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > solver; 


        // KNullOperatorConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(0, 3)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(3, 0)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(arma::Mat<std::complex<klab::DoubleReal> >(0, 0)), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(A2_3), b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(A3_2), b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(A3_3), b0, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(A3_3), b2, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(A2_2), b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(A3_3), b3, x00, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(A3_3), b3, x01, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(A3_3), b3, x02, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KZeroNormConjugateGradientException
        try                                                 {solver.solve<TMatrixLinearOperator<std::complex<klab::DoubleReal> > >(klab::TMatrixLinearOperator<std::complex<klab::DoubleReal> >(A3_3), b3, x03, x); TEST_ASSERT(false)}
        catch(KZeroNormConjugateGradientException&)         {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSolve_MatrixComplex()
{
    try
    {
        klab::DoubleReal precision = 1e-6;

        arma::Mat<std::complex<klab::DoubleReal> > a(3, 3);
        arma::Col<std::complex<klab::DoubleReal> > b(3);
        arma::Col<std::complex<klab::DoubleReal> > x0(3);
        arma::Col<std::complex<klab::DoubleReal> > x;
        arma::Col<std::complex<klab::DoubleReal> > x2;

        a(0, 0) = std::complex<klab::DoubleReal>(1.0,  0.0);
        a(0, 1) = std::complex<klab::DoubleReal>(4.0,  5.0);
        a(0, 2) = std::complex<klab::DoubleReal>(7.0, -8.0);
        a(1, 0) = std::complex<klab::DoubleReal>(4.0, -5.0);
        a(1, 1) = std::complex<klab::DoubleReal>(5.0,  0.0);
        a(1, 2) = std::complex<klab::DoubleReal>(6.0,  7.0);
        a(2, 0) = std::complex<klab::DoubleReal>(7.0,  8.0);
        a(2, 1) = std::complex<klab::DoubleReal>(6.0, -7.0);
        a(2, 2) = std::complex<klab::DoubleReal>(9.0,  0.0);

        b[0] = std::complex<klab::DoubleReal>(77.0, 4.0);
        b[1] = std::complex<klab::DoubleReal>(14.0, 33.0);
        b[2] = std::complex<klab::DoubleReal>( 9.0, 26.0);

        x0.fill(std::complex<klab::DoubleReal>(0.0, 0.0));


        TConjugateGradientSystemSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > solver(1e-6);

        solver.solve(a, b, x);
        TEST_ASSERT(x.n_rows == 3)
        TEST_ASSERT(klab::Equals(x[0], std::complex<klab::DoubleReal>(1.0,  2.0), precision))
        TEST_ASSERT(klab::Equals(x[1], std::complex<klab::DoubleReal>(2.0, -3.0), precision))
        TEST_ASSERT(klab::Equals(x[2], std::complex<klab::DoubleReal>(3.0,  4.0), precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)

        solver.solve(a, b, x0, x2);
        TEST_ASSERT(x2.n_rows == 3)
        TEST_ASSERT(klab::Equals(x2[0], std::complex<klab::DoubleReal>(1.0,  2.0), precision))
        TEST_ASSERT(klab::Equals(x2[1], std::complex<klab::DoubleReal>(2.0, -3.0), precision))
        TEST_ASSERT(klab::Equals(x2[2], std::complex<klab::DoubleReal>(3.0,  4.0), precision))
        TEST_ASSERT(solver.countIterations()>0 && solver.countIterations()<=3)
        TEST_ASSERT(solver.residual()>0.0 && solver.residual()!=klab::TTypeInfo<klab::DoubleReal>::MAX)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KConjugateGradientSystemSolverUnitTest::testSolve_Matrix_ErrorsComplex()
{
    try
    {
        arma::Mat<std::complex<klab::DoubleReal> > A2_2(2, 2);
        arma::Mat<std::complex<klab::DoubleReal> > A2_3(2, 3);
        arma::Mat<std::complex<klab::DoubleReal> > A3_2(3, 2);
        arma::Mat<std::complex<klab::DoubleReal> > A3_3(3, 3);
        arma::Col<std::complex<klab::DoubleReal> > b0;
        arma::Col<std::complex<klab::DoubleReal> > b2(2);
        arma::Col<std::complex<klab::DoubleReal> > b3(3);
        arma::Col<std::complex<klab::DoubleReal> > x00;
        arma::Col<std::complex<klab::DoubleReal> > x01(1);
        arma::Col<std::complex<klab::DoubleReal> > x02(2);
        arma::Col<std::complex<klab::DoubleReal> > x03(3);
        arma::Col<std::complex<klab::DoubleReal> > x;

        b3.fill(std::complex<klab::DoubleReal>(0.0, 0.0));


        TConjugateGradientSystemSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > solver; 


        // KNullOperatorConjugateGradientException
        try                                                 {solver.solve(arma::Mat<std::complex<klab::DoubleReal> >(0, 3), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve(arma::Mat<std::complex<klab::DoubleReal> >(3, 0), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve(arma::Mat<std::complex<klab::DoubleReal> >(0, 0), b3, x); TEST_ASSERT(false)}
        catch(KNullOperatorConjugateGradientException&)     {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve(A2_3, b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)} 

        try                                                 {solver.solve(A3_2, b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve(A3_3, b0, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve(A3_3, b2, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve(A2_2, b3, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KIncompatibleSizeConjugateGradientException
        try                                                 {solver.solve(A3_3, b3, x00, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve(A3_3, b3, x01, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {solver.solve(A3_3, b3, x02, x); TEST_ASSERT(false)}
        catch(KIncompatibleSizeConjugateGradientException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}


        // KZeroNormConjugateGradientException
        try                                                 {solver.solve(A3_3, b3, x03, x); TEST_ASSERT(false)}
        catch(KZeroNormConjugateGradientException&)         {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
