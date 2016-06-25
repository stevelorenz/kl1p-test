// KLab - A portable C++ collection of classes for general purpose.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KLab C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_RGBCOLORUNITTEST_H
#define KLAB_RGBCOLORUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KRGBColorUnitTest : public Test::Suite
{
public:
    
    KRGBColorUnitTest();
    virtual ~KRGBColorUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();
    void    testRGBConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Operators tests.
    void    testEqualOperator();
    void    testNotEqualOperator();

    // Getters/Setters tests.
    void    testSet();
    void    testSetRed();
    void    testSetGreen();
    void    testSetBlue();
    void    testRed();
    void    testGreen();
    void    testBlue();

    // Methods tests.
    void    testIsEqual();


private:

    KRGBColorUnitTest(const KRGBColorUnitTest& test);
    KRGBColorUnitTest&      operator=(const KRGBColorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
