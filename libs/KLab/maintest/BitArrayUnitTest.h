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

#ifndef KLAB_BITARRAYUNITTEST_H
#define KLAB_BITARRAYUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KBitArrayUnitTest : public Test::Suite
{
public:
    
    KBitArrayUnitTest();
    virtual ~KBitArrayUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();
    void    testSizeConstructor();
    void    testSizeValueConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Operators tests.
    void    testBracketOperator();
    void    testEqualOperator();
    void    testNotEqualOperator();
    void    testLowerOperator();
    void    testLowerOrEqualOperator();
    void    testGreaterOrEqualOperator();
    void    testGreaterOperator();

    // Methods tests.
    void    testResize();
    void    testFill();
    void    testClear();
    void    testSize();
    void    testPush();
    void    testPop();
    void    testSetBit();
    void    testSet();
    void    testReset();
    void    testBit();


private:

    KBitArrayUnitTest(const KBitArrayUnitTest& test);
    KBitArrayUnitTest&  operator=(const KBitArrayUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
