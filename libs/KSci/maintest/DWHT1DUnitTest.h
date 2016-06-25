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

#ifndef KLAB_DWHT1DUNITTEST_H
#define KLAB_DWHT1DUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KDWHT1DUnitTest : public Test::Suite
{
public:
    
    KDWHT1DUnitTest();
    virtual ~KDWHT1DUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testTransform();
    void    testInvert();

    // Functionnal tests.
    void    testWalshHadamardMatrix();


private:

    KDWHT1DUnitTest(const KDWHT1DUnitTest& test);
    KDWHT1DUnitTest&     operator=(const KDWHT1DUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
