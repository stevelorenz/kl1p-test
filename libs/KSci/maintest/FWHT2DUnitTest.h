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

#ifndef KLAB_FWHT2DUNITTEST_H
#define KLAB_FWHT2DUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KFWHT2DUnitTest : public Test::Suite
{
public:
    
    KFWHT2DUnitTest();
    virtual ~KFWHT2DUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testTransform();
    void    testTransform_02();
    void    testTransform_03();
    void    testInvert();
    void    testInvert_02();
    void    testInvert_03();


private:

    KFWHT2DUnitTest(const KFWHT2DUnitTest& test);
    KFWHT2DUnitTest&     operator=(const KFWHT2DUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
