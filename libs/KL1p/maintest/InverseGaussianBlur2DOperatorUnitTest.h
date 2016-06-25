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

#ifndef KL1P_INVERSEGAUSSIANBLUR2DOPERATORUNITTEST_H
#define KL1P_INVERSEGAUSSIANBLUR2DOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KInverseGaussianBlur2DOperatorUnitTest : public Test::Suite
{
public:
    
    KInverseGaussianBlur2DOperatorUnitTest();
    virtual ~KInverseGaussianBlur2DOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testHeightWidthConstructor(); 
    void    testHeightWidthGammaConstructor(); 
    void    testHeightWidthGammaSigmaConstructor(); 
    void    testHeightWidthGammaSigmaIcJcConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testWidth();
    void    testHeight();
    void    testGamma();
    void    testSigma();
    void    testIc();
    void    testJc();
    void    testApply();
    void    testApply_Complex();
    void    testApplyAdjoint();
    void    testApplyAdjoint_Complex();


private:

    KInverseGaussianBlur2DOperatorUnitTest(const KInverseGaussianBlur2DOperatorUnitTest& test);
    KInverseGaussianBlur2DOperatorUnitTest&     operator=(const KInverseGaussianBlur2DOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
