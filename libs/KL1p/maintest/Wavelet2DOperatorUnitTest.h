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

#ifndef KL1P_WAVELET2DOPERATORUNITTEST_H
#define KL1P_WAVELET2DOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KWavelet2DOperatorUnitTest : public Test::Suite
{
public:
    
    KWavelet2DOperatorUnitTest();
    virtual ~KWavelet2DOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testHeightWidthConstructor(); 
    void    testHeightWidthFilterConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testWidth();
    void    testHeight();
    void    testFilter();
    void    testApply();
    void    testApply_Haar();
    void    testApply_Daubechies2();
    void    testApply_Daubechies4();
    void    testApply_Daubechies6();
    void    testApply_Daubechies8();
    void    testApply_Daubechies10();
    void    testApply_Daubechies9_7();
    void    testApply_Delegate();
    void    testApply_Name();
    void    testApply_Custom();
    void    testApplyAdjoint();
    void    testApplyAdjoint_Haar();
    void    testApplyAdjoint_Daubechies2();
    void    testApplyAdjoint_Daubechies4();
    void    testApplyAdjoint_Daubechies6();
    void    testApplyAdjoint_Daubechies8();
    void    testApplyAdjoint_Daubechies10();
    void    testApplyAdjoint_Daubechies9_7();
    void    testApplyAdjoint_Delegate();
    void    testApplyAdjoint_Name();
    void    testApplyAdjoint_Custom();


private:

    KWavelet2DOperatorUnitTest(const KWavelet2DOperatorUnitTest& test);
    KWavelet2DOperatorUnitTest&     operator=(const KWavelet2DOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
