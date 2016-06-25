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

#ifndef KLAB_COMPLEXUNITTEST_H
#define KLAB_COMPLEXUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KComplexUnitTest : public Test::Suite
{
public:
    
    KComplexUnitTest();
    virtual ~KComplexUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor();
    void    testValueConstructor();
    void    testRealImaginaryConstructor();
    void    testStdComplexConstructor();
    void    testCopyConstructor();
    void    testValueAffectationOperator();
    void    testStdComplexAffectationOperator();
    void    testAffectationOperator();

    // Operators tests.
    void    testEqualOperator();
    void    testNotEqualOperator();
    void    testAddAndAffectOperator();
    void    testSubstractAndAffectOperator();
    void    testMultiplyAndAffectOperator();
    void    testDivideAndAffectOperator();
    void    testAddOperator();
    void    testSubstractOperator();
    void    testMultiplyOperator();
    void    testDivideOperator();
    void    testSignOperator();

    // Methods tests.
    void    testSet();
    void    testSetPolar();
    void    testSetReal();
    void    testSetImaginary();
    void    testReal();
    void    testImaginary();
    void    testConjugue();
    void    testConjugate();
    void    testAbsolute();
    void    testModulus();
    void    testArgument();
    void    testNorm();
    void    testEquals();

    // Casts tests.
    void    testStdComplexCastOperator();

    // Functions tests.
    void    testAbs();
    void    testConj();
    void    testEqualsFunction();
    void    testCos();
    void    testCosH();
    void    testSin();
    void    testSinH();
    void    testTan();
    void    testTanH();
    void    testSqrt();
    void    testExp();
    void    testLog();
    void    testLog10();
    void    testPow();
    void    testOstreamOperator();

    // Other tests.
    void    testTypeInfoConstants();


private:

    KComplexUnitTest(const KComplexUnitTest& test);
    KComplexUnitTest&   operator=(const KComplexUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
