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

#ifndef KL1P_ROMPSOLVERUNITTEST_H
#define KL1P_ROMPSOLVERUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KROMPSolverUnitTest : public Test::Suite
{
public:
    
    KROMPSolverUnitTest();
    virtual ~KROMPSolverUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor();
    void    testToleranceConstructor(); 
    void    testToleranceIterationLimitConstructor(); 
    void    testToleranceIterationLimitMaxCoeffConstructor(); 
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testSetTolerance();
    void    testSetIterationLimit();
    void    testSetMaxCoeffAddedEachIterations();
    void    testTolerance();
    void    testIterationLimit();
    void    testMaxCoeffAddedEachIterations();
    void    testResidualNorm();
    void    testRelativeResidualNorm();
    void    testIterations();
    void    testSparsity();
    void    testLeastSquareSolver();
    void    testEnableHistory();
    void    testIsHistoryEnabled();
    void    testHistory();
    void    testSolve();
    void    testSolve_02();
    void    testSolve_03();
    void    testSolve_04();


private:

    KROMPSolverUnitTest(const KROMPSolverUnitTest& test);
    KROMPSolverUnitTest&    operator=(const KROMPSolverUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
