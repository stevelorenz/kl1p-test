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

#ifndef KL1P_FOURIER2DOPERATORUNITTEST_H
#define KL1P_FOURIER2DOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KFourier2DOperatorUnitTest : public Test::Suite
{
public:
    
    KFourier2DOperatorUnitTest();
    virtual ~KFourier2DOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testHeightWidthShiftConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testWidth();
    void    testHeight();
    void    testIsShift();
    void    testApply();
    void    testApplyAdjoint();
    void    testApplyAdjoint_Real();    


private:

    KFourier2DOperatorUnitTest(const KFourier2DOperatorUnitTest& test);
    KFourier2DOperatorUnitTest&     operator=(const KFourier2DOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
