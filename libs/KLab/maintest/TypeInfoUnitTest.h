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

#ifndef KLAB_TYPEINFOUNITTEST_H
#define KLAB_TYPEINFOUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KTypeInfoUnitTest : public Test::Suite
{
public:
    
    KTypeInfoUnitTest();
    virtual ~KTypeInfoUnitTest();
    
    
protected:

    // Tests.
    void    testUInt8TypeInfo();
    void    testInt8TypeInfo();
    void    testUInt16TypeInfo();
    void    testInt16TypeInfo();
    void    testUInt32TypeInfo();
    void    testInt32TypeInfo();
    void    testUInt64TypeInfo();
    void    testInt64TypeInfo();
    void    testRealTypeInfo();
    void    testDoubleRealTypeInfo();
    void    testComplexRealTypeInfo();
    void    testComplexDoubleRealTypeInfo();


private:

    KTypeInfoUnitTest(const KTypeInfoUnitTest& test);
    KTypeInfoUnitTest&      operator=(const KTypeInfoUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
