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

#ifndef KL1P_SL0SOLVERUNITTEST_H
#define KL1P_SL0SOLVERUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KSL0SolverUnitTest : public Test::Suite
{
public:
    
    KSL0SolverUnitTest();
    virtual ~KSL0SolverUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor();
    void    testToleranceConstructor(); 
    void    testToleranceIterationLimitConstructor(); 
    void    testToleranceIterationLimitSigmaStepFactorConstructor();
    void    testToleranceIterationLimitSigmaStepFactorMu0Constructor();
    void    testToleranceIterationLimitSigmaStepFactorMu0InnerIterationLimitConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testSetTolerance();
    void    testSetIterationLimit();
    void    testSetSigmaStepFactor();
    void    testSetMu0();
    void    testSetInnerIterationLimit();
    void    testTolerance();
    void    testIterationLimit();
    void    testSigmaStepFactor();
    void    testMu0();
    void    testInnerIterationLimit();
    void    testSigma();
    void    testIterations();
    void    testConjugateGradientSolver();
    void    testEnableHistory();
    void    testIsHistoryEnabled();
    void    testHistory();
    void    testSolve();
    void    testSolve_02();
    void    testSolve_03();
    void    testSolve_04();


private:

    KSL0SolverUnitTest(const KSL0SolverUnitTest& test);
    KSL0SolverUnitTest& operator=(const KSL0SolverUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
