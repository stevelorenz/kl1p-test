// KSci - A portable C++ numerical analysis library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KSci C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_DWT1DUNITTEST_H
#define KLAB_DWT1DUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KDWT1DUnitTest : public Test::Suite
{
public:
    
    KDWT1DUnitTest();
    virtual ~KDWT1DUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testFilterConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testFilter();
    void    testTransform();
    void    testInvert();

    // Functionnal tests.
    void    testHaarWavelet();
    void    testDaubechies2Wavelet();
    void    testDaubechies4Wavelet();
    void    testDaubechies6Wavelet();
    void    testDaubechies8Wavelet();
    void    testDaubechies10Wavelet();
    void    testDaubechies9_7Wavelet();
    void    testDelegateWavelet();
    void    testNameWavelet();
    void    testCustomWavelet();    


private:

    KDWT1DUnitTest(const KDWT1DUnitTest& test);
    KDWT1DUnitTest&     operator=(const KDWT1DUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
