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

#ifndef KLAB_ARRAYELEMENTUNITTEST_H
#define KLAB_ARRAYELEMENTUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KArrayElementUnitTest : public Test::Suite
{
public:
    
    KArrayElementUnitTest();
    virtual ~KArrayElementUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();
    void    testIndexConstructor();
    void    testIndexValueConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Operators tests.
    void    testLowerOperator();

    // Methods tests.
    void    testSetIndex();
    void    testSetI();
    void    testSetValue();
    void    testIndex();
    void    testI();
    void    testValue();


private:

    KArrayElementUnitTest(const KArrayElementUnitTest& test);
    KArrayElementUnitTest&  operator=(const KArrayElementUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
