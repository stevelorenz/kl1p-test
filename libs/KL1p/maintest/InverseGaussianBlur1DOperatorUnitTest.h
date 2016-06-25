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

#ifndef KL1P_INVERSEGAUSSIANBLUR1DOPERATORUNITTEST_H
#define KL1P_INVERSEGAUSSIANBLUR1DOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KInverseGaussianBlur1DOperatorUnitTest : public Test::Suite
{
public:
    
    KInverseGaussianBlur1DOperatorUnitTest();
    virtual ~KInverseGaussianBlur1DOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testSizeConstructor(); 
    void    testSizeGammaConstructor(); 
    void    testSizeGammaSigmaConstructor(); 
    void    testSizeGammaSigmaCConstructor();
    void    testCopyConstructor();

    // Methods tests.
    void    testGamma();
    void    testSigma();
    void    testC();
    void    testApply();
    void    testApply_Complex();
    void    testApplyAdjoint();
    void    testApplyAdjoint_Complex();


private:

    KInverseGaussianBlur1DOperatorUnitTest(const KInverseGaussianBlur1DOperatorUnitTest& test);
    KInverseGaussianBlur1DOperatorUnitTest& operator=(const KInverseGaussianBlur1DOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
