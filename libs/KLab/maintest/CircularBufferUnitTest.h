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

#ifndef KLAB_CIRCULARBUFFERUNITTEST_H
#define KLAB_CIRCULARBUFFERUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KCircularBufferUnitTest : public Test::Suite
{
public:
    
    KCircularBufferUnitTest();
    virtual ~KCircularBufferUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();
    void    testCapacityConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Operators tests.
    void    testBracketOperator();
    void    testBracketOperator_Const();

    // Methods tests.
    void    testPush();
    void    testPush_Array();
    void    testPush_Vector();
    void    testPop();
    void    testClear();
    void    testReserve();
    void    testResize();
    void    testCapacity();
    void    testSize();
    void    testAt();
    void    testAt_Const();
    void    testFront();
    void    testFront_Const();
    void    testBack();
    void    testBack_Const();


private:

    KCircularBufferUnitTest(const KCircularBufferUnitTest& test);
    KCircularBufferUnitTest&    operator=(const KCircularBufferUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
