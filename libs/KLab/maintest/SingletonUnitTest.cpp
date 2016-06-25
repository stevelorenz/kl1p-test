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

#include "SingletonUnitTest.h"
#include "../include/Singleton.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KSingletonUnitTest::KSingletonUnitTest() : Test::Suite()
{
    TEST_ADD(KSingletonUnitTest::testInstance)
}

// ---------------------------------------------------------------------------------------------------- //

KSingletonUnitTest::~KSingletonUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSingletonUnitTest::testInstance()
{
    try
    {
        TEST_ASSERT(klab::TSingleton<KTestSingletonClass>::Instance().value01() == 0)
        TEST_ASSERT(klab::TSingleton<KTestSingletonClass>::Instance().value02() == 0)

        klab::TSingleton<KTestSingletonClass>::Instance().setValue01(123);
        TEST_ASSERT(klab::TSingleton<KTestSingletonClass>::Instance().value01() == 123)
        TEST_ASSERT(klab::TSingleton<KTestSingletonClass>::Instance().value02() == 0)

        klab::TSingleton<KTestSingletonClass>::Instance().setValue02(456);
        TEST_ASSERT(klab::TSingleton<KTestSingletonClass>::Instance().value01() == 123)
        TEST_ASSERT(klab::TSingleton<KTestSingletonClass>::Instance().value02() == 456)

        klab::TSingleton<KTestSingletonClass>::Instance().setValue01(741);
        klab::TSingleton<KTestSingletonClass>::Instance().setValue02(963);
        TEST_ASSERT(klab::TSingleton<KTestSingletonClass>::Instance().value01() == 741)
        TEST_ASSERT(klab::TSingleton<KTestSingletonClass>::Instance().value02() == 963)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

KTestSingletonClass::KTestSingletonClass() :
_value01(0), _value02(0)
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSingletonClass::KTestSingletonClass(klab::UInt32 value01, klab::UInt32 value02) :
_value01(value01), _value02(value02)
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSingletonClass::KTestSingletonClass(const KTestSingletonClass& copy) :
_value01(copy._value01), _value02(copy._value02)
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSingletonClass::~KTestSingletonClass()
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSingletonClass& KTestSingletonClass::operator=(const KTestSingletonClass& copy)
{
    if(this != &copy)
    {
        _value01 = copy._value01;
        _value02 = copy._value02;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

void KTestSingletonClass::setValue01(klab::UInt32 value01)
{
    _value01 = value01;
}

// ---------------------------------------------------------------------------------------------------- //

void KTestSingletonClass::setValue02(klab::UInt32 value02)
{
    _value02 = value02;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KTestSingletonClass::value01() const
{
    return _value01;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KTestSingletonClass::value02() const
{
    return _value02;
}

// ---------------------------------------------------------------------------------------------------- //
