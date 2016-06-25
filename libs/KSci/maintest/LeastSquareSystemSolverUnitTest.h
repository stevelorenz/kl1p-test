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

#ifndef KLAB_LEASTSQUARESYSTEMSOLVERUNITTEST_H
#define KLAB_LEASTSQUARESYSTEMSOLVERUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KLeastSquareSystemSolverUnitTest : public Test::Suite
{
public:
    
    KLeastSquareSystemSolverUnitTest();
    virtual ~KLeastSquareSystemSolverUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testIterationLimitConstructor(); 
    void    testIterationLimitCondLimitConstructor(); 
    void    testIterationLimitCondLimitAToleranceBToleranceConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Getters/Setters tests.
    void    testSetATolerance();
    void    testSetBTolerance();
    void    testSetCondLimit();
    void    testSetIterationLimit();
    void    testATolerance();
    void    testBTolerance();
    void    testCondLimit();
    void    testIterationLimit();
    void    testCountIterations();
    void    testANorm();
    void    testACond();
    void    testArNorm();
    void    testXNorm();

    // Methods tests.
    void    testSolve();
    void    testSolve_Errors();
    void    testSolve_Matrix();
    void    testSolve_Matrix_Errors();
    void    testSolve_Complex();
    void    testSolve_ErrorsComplex();
    void    testSolve_MatrixComplex();
    void    testSolve_Matrix_ErrorsComplex();


private:

    KLeastSquareSystemSolverUnitTest(const KLeastSquareSystemSolverUnitTest& test);
    KLeastSquareSystemSolverUnitTest&   operator=(const KLeastSquareSystemSolverUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
