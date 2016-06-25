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

#ifndef KLAB_VECTOR2DUNITTEST_H
#define KLAB_VECTOR2DUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KVector2DUnitTest : public Test::Suite
{
public:
    
    KVector2DUnitTest();
    virtual ~KVector2DUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor();
    void    testXYConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testClear();
    void    testSet();
    void    testSetX();
    void    testSetY();
    void    testX();
    void    testY();

    // Functions tests.
    void    testEquals();
    void    testCompareVector2DOnX();
    void    testCompareVector2DOnY();


private:

    KVector2DUnitTest(const KVector2DUnitTest& test);
    KVector2DUnitTest&  operator=(const KVector2DUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
