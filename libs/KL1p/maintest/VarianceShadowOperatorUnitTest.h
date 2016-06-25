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

#ifndef KL1P_VARIANCESHADOWOPERATORUNITTEST_H
#define KL1P_VARIANCESHADOWOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KVarianceShadowOperatorUnitTest : public Test::Suite
{
public:
    
    KVarianceShadowOperatorUnitTest();
    virtual ~KVarianceShadowOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testOpConstructor(); 
    void    testOpVarianceConstructor(); 
    void    testOpVarianceMeanConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testOp();
    void    testIsZero();
    void    testSum();
    void    testNormFrobenius();
    void    testSquaredNormFrobenius();
    void    testMean();
    void    testVariance();
    void    testApply();
    void    testApply_Complex();
    void    testApplyAdjoint();
    void    testApplyAdjoint_Complex();
    void    testColumn();
    void    testColumn_Complex();
    void    testColumnAdjoint();
    void    testColumnAdjoint_Complex();


private:

    KVarianceShadowOperatorUnitTest(const KVarianceShadowOperatorUnitTest& test);
    KVarianceShadowOperatorUnitTest&    operator=(const KVarianceShadowOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
