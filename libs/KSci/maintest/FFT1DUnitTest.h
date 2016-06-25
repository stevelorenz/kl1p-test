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

#ifndef KLAB_FFT1DUNITTEST_H
#define KLAB_FFT1DUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KFFT1DUnitTest : public Test::Suite
{
public:
    
    KFFT1DUnitTest();
    virtual ~KFFT1DUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testShiftConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testSetShift();
    void    testShift();
    void    testTransform();
    void    testTransform_Real();
    void    testTransform_02();   
    void    testTransform_02_Real();    
    void    testInvert();
    void    testInvert_Real();
    void    testInvert_02();
    void    testInvert_02_Real();


private:

    KFFT1DUnitTest(const KFFT1DUnitTest& test);
    KFFT1DUnitTest&     operator=(const KFFT1DUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
