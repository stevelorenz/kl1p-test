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

#ifndef KL1P_GAUSSIAN2DDIAGONALOPERATORUNITTEST_H
#define KL1P_GAUSSIAN2DDIAGONALOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KGaussian2DDiagonalOperatorUnitTest : public Test::Suite
{
public:
    
    KGaussian2DDiagonalOperatorUnitTest();
    virtual ~KGaussian2DDiagonalOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testHeightWidthConstructor(); 
    void    testHeightWidthSigmaConstructor(); 
    void    testHeightWidthSigmaIcJcConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testWidth();
    void    testHeight();
    void    testSigma();
    void    testIc();
    void    testJc();
    void    testApply();
    void    testApply_Complex();
    void    testApplyAdjoint();
    void    testApplyAdjoint_Complex();


private:

    KGaussian2DDiagonalOperatorUnitTest(const KGaussian2DDiagonalOperatorUnitTest& test);
    KGaussian2DDiagonalOperatorUnitTest&    operator=(const KGaussian2DDiagonalOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
