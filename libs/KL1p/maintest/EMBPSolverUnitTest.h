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

#ifndef KL1P_EMBPSOLVERUNITTEST_H
#define KL1P_EMBPSOLVERUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KEMBPSolverUnitTest : public Test::Suite
{
public:
    
    KEMBPSolverUnitTest();
    virtual ~KEMBPSolverUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor();
    void    testToleranceConstructor(); 
    void    testToleranceIterationLimitConstructor(); 
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testSetTolerance();
    void    testSetIterationLimit();
    void    testSetNoiseVariance();
    void    testSetMessageDamping();
    void    testSetLearningDamping();
    void    testEnableDampingLearning();
    void    testEnableParameterLearning();
    void    testEnableHomogeneous();
    void    testTolerance();
    void    testIterationLimit();
    void    testNoiseVariance();
    void    testMessageDamping();
    void    testLearningDamping();
    void    testIsDampingLearningEnabled();
    void    testIsParameterLearningEnabled();
    void    testIsHomogeneousEnabled();
    void    testResidualNorm();
    void    testRelativeResidualNorm();
    void    testIterations();
    void    testEnableHistory();
    void    testIsHistoryEnabled();
    void    testHistory();
    void    testSolve();
    void    testSolve_02();
    void    testSolve_03();
    void    testSolve_04();
    void    testSolve_05();
    void    testSolve_06();
    void    testSolve_07();
    void    testSolve_08();
    void    testSolve_09();
    void    testSolve_10();
    void    testSolve_11();
    void    testSolve_12();
    void    testSolve_13();
    void    testSolve_14();
    void    testSolve_15();


private:

    KEMBPSolverUnitTest(const KEMBPSolverUnitTest& test);
    KEMBPSolverUnitTest&    operator=(const KEMBPSolverUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
