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

#ifndef KLAB_VECTOR3DUNITTEST_H
#define KLAB_VECTOR3DUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KVector3DUnitTest : public Test::Suite
{
public:
    
    KVector3DUnitTest();
    virtual ~KVector3DUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testXYZConstructor();
    void    testVector2DConstructor();
    void    testCopyConstructor();
    void    testVector2DAffectationOperator();
    void    testAffectationOperator();

    // Methods tests.
    void    testClear();
    void    testSet();
    void    testSetX();
    void    testSetY();
    void    testSetZ();
    void    testX();
    void    testY();
    void    testZ();

    // Functions tests.
    void    testEquals();
    void    testCompareVector3DOnX();
    void    testCompareVector3DOnY();
    void    testCompareVector3DOnZ();


private:

    KVector3DUnitTest(const KVector3DUnitTest& test);
    KVector3DUnitTest&  operator=(const KVector3DUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
