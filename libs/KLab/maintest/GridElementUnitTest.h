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

#ifndef KLAB_GRIDELEMENTUNITTEST_H
#define KLAB_GRIDELEMENTUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KGridElementUnitTest : public Test::Suite
{
public:
    
    KGridElementUnitTest();
    virtual ~KGridElementUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();
    void    testIndexesConstructor();
    void    testIndexesValueConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Operators tests.
    void    testLowerOperator();

    // Methods tests.
    void    testSetIndex();
    void    testSetI();
    void    testSetJ();
    void    testSetValue();
    void    testIndex();
    void    testI();
    void    testJ();
    void    testValue();


private:

    KGridElementUnitTest(const KGridElementUnitTest& test);
    KGridElementUnitTest&   operator=(const KGridElementUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
