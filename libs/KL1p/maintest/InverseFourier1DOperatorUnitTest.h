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

#ifndef KL1P_INVERSEFOURIER1DOPERATORUNITTEST_H
#define KL1P_INVERSEFOURIER1DOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KInverseFourier1DOperatorUnitTest : public Test::Suite
{
public:
    
    KInverseFourier1DOperatorUnitTest();
    virtual ~KInverseFourier1DOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testNConstructor(); 
    void    testNShiftConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testIsShift();
    void    testApply();
    void    testApplyAdjoint();
    void    testApplyAdjoint_Real();
    void    testApplyAdjoint_Real_02();


private:

    KInverseFourier1DOperatorUnitTest(const KInverseFourier1DOperatorUnitTest& test);
    KInverseFourier1DOperatorUnitTest&  operator=(const KInverseFourier1DOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
