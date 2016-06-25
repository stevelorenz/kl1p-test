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

#ifndef KLAB_SINGLETONUNITTEST_H
#define KLAB_SINGLETONUNITTEST_H

#include <cpptest.h>
#include "../include/TypeUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KSingletonUnitTest : public Test::Suite
{
public:
    
    KSingletonUnitTest();
    virtual ~KSingletonUnitTest();
    
    
protected:

    // Static methods tests.
    void    testInstance();


private:

    KSingletonUnitTest(const KSingletonUnitTest& test);
    KSingletonUnitTest&     operator=(const KSingletonUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

class KTestSingletonClass
{
public:

    KTestSingletonClass();
    KTestSingletonClass(klab::UInt32 value01, klab::UInt32 value02);
    KTestSingletonClass(const KTestSingletonClass& copy);
    virtual ~KTestSingletonClass();

    KTestSingletonClass&    operator=(const KTestSingletonClass& copy);

    void                    setValue01(klab::UInt32 value01);
    void                    setValue02(klab::UInt32 value02);

    klab::UInt32            value01() const;
    klab::UInt32            value02() const;


private:

    klab::UInt32    _value01;
    klab::UInt32    _value02;
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
