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

#ifndef KLAB_CONJUGATEGRADIENTSYSTEMSOLVERUNITTEST_H
#define KLAB_CONJUGATEGRADIENTSYSTEMSOLVERUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KConjugateGradientSystemSolverUnitTest : public Test::Suite
{
public:
    
    KConjugateGradientSystemSolverUnitTest();
    virtual ~KConjugateGradientSystemSolverUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testToleranceConstructor();
    void    testToleranceIterationLimitConstructor(); 
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Getters/Setters tests.
    void    testSetTolerance();
    void    testSetIterationLimit();
    void    testTolerance();
    void    testIterationLimit();
    void    testResidual();
    void    testCountIterations();

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

    KConjugateGradientSystemSolverUnitTest(const KConjugateGradientSystemSolverUnitTest& test);
    KConjugateGradientSystemSolverUnitTest& operator=(const KConjugateGradientSystemSolverUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
