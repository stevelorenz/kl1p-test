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

#include "ScopedMutexUnitTest.h"
#include "../include/Mutex.h"
#include "../include/ScopedMutex.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KScopedMutexUnitTest::KScopedMutexUnitTest() : Test::Suite(),
_mutex(),
_concurrent(false), _lastID(0)
{
    TEST_ADD(KScopedMutexUnitTest::testMutexConstructor)

    TEST_ADD(KScopedMutexUnitTest::testSynchronization)
}

// ---------------------------------------------------------------------------------------------------- //

KScopedMutexUnitTest::~KScopedMutexUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

bool KScopedMutexUnitTest::unprotectedAccess(klab::UInt32 id)
{
    _lastID = id;

    klab::Sleep(20);

    if(_lastID != id)
        _concurrent = true;

    return !_concurrent;
}

// ---------------------------------------------------------------------------------------------------- //

bool KScopedMutexUnitTest::protectedAccess(klab::UInt32 id)
{
    TScopedMutex<KMutex> mutex(_mutex);

    _lastID = id;

    klab::Sleep(20);

    if(_lastID != id)
        _concurrent = true;

    return !_concurrent;
}

// ---------------------------------------------------------------------------------------------------- //

void KScopedMutexUnitTest::testMutexConstructor()
{
    try
    {
        TMutex<> m1;
        const TMutex<> m2;


        TScopedMutex<TMutex<> > mutex1(m1);
        TEST_ASSERT(true)

        TScopedMutex<TMutex<> > mutex2(m2);
        TEST_ASSERT(true)

        KScopedMutex mutex3(m1);
        TEST_ASSERT(true)

        KScopedMutex mutex4(m2);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KScopedMutexUnitTest::testSynchronization()
{
    try
    {
        _concurrent = false;

        KRunnableScopedMutexTestClass runnable01(*this, 1);
        KRunnableScopedMutexTestClass runnable02(*this, 2);

        TThread<KRunnableScopedMutexTestClass, &KRunnableScopedMutexTestClass::run> thread1(runnable01);
        TThread<KRunnableScopedMutexTestClass, &KRunnableScopedMutexTestClass::run> thread2(runnable02);

        thread1.start();
        thread2.start();
		TEST_ASSERT(thread1.isStarted() && thread2.isStarted())

        klab::Sleep(100);

        TEST_ASSERT(thread1.isStarted() && thread2.isStarted())
        TEST_ASSERT(_concurrent == false)

        thread1.stop();
        thread2.stop();
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

KRunnableScopedMutexTestClass::KRunnableScopedMutexTestClass(KScopedMutexUnitTest& test, klab::UInt32 id) : 
_test(test), _id(id)
{}

// ---------------------------------------------------------------------------------------------------- //

KRunnableScopedMutexTestClass::~KRunnableScopedMutexTestClass()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableScopedMutexTestClass::run(const IThreadStatus& status)
{
    while(status.checkThreadState() && _test.protectedAccess(_id))
        klab::Sleep(2);           
}

// ---------------------------------------------------------------------------------------------------- //
