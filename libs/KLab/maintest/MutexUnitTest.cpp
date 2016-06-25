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

#include "MutexUnitTest.h"
#include "../include/Mutex.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KMutexUnitTest::KMutexUnitTest() : Test::Suite(),
_mutex(),
_concurrent(false), _lastID(0)
{
    TEST_ADD(KMutexUnitTest::testDefaultConstructor)

    TEST_ADD(KMutexUnitTest::testLock)
    TEST_ADD(KMutexUnitTest::testTryToLock)
    TEST_ADD(KMutexUnitTest::testUnlock)

    TEST_ADD(KMutexUnitTest::testSynchronization)
}

// ---------------------------------------------------------------------------------------------------- //

KMutexUnitTest::~KMutexUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

bool KMutexUnitTest::unprotectedAccess(klab::UInt32 id)
{
    _lastID = id;

    klab::Sleep(20);

    if(_lastID != id)
        _concurrent = true;

    return !_concurrent;
}

// ---------------------------------------------------------------------------------------------------- //

bool KMutexUnitTest::protectedAccess(klab::UInt32 id)
{
    _mutex.lock();

    _lastID = id;

    klab::Sleep(20);

    if(_lastID != id)
        _concurrent = true;

    _mutex.unlock();

    return !_concurrent;
}

// ---------------------------------------------------------------------------------------------------- //

void KMutexUnitTest::testDefaultConstructor()
{
    try
    {
        TMutex<> mutex1;
        TEST_ASSERT(true)

        KMutex mutex2;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMutexUnitTest::testLock()
{
    try
    {
        TMutex<> mutex1;
        TEST_ASSERT(true)

        mutex1.lock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.lock();
        TEST_ASSERT(true)

        mutex1.tryToLock();
        TEST_ASSERT(true)

        mutex1.lock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)


        KMutex mutex2;
        TEST_ASSERT(true)

        mutex2.lock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.lock();
        TEST_ASSERT(true)

        mutex2.tryToLock();
        TEST_ASSERT(true)

        mutex2.lock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMutexUnitTest::testTryToLock()
{
    try
    {
        TMutex<> mutex1;
        TEST_ASSERT(true)

        mutex1.tryToLock();
        TEST_ASSERT(true)

        mutex1.lock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.lock();
        TEST_ASSERT(true)

        mutex1.tryToLock();
        TEST_ASSERT(true)

        mutex1.lock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)


        KMutex mutex2;
        TEST_ASSERT(true)

        mutex2.tryToLock();
        TEST_ASSERT(true)

        mutex2.lock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.lock();
        TEST_ASSERT(true)

        mutex2.tryToLock();
        TEST_ASSERT(true)

        mutex2.lock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMutexUnitTest::testUnlock()
{
    try
    {
        TMutex<> mutex1;
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.lock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.lock();
        TEST_ASSERT(true)

        mutex1.tryToLock();
        TEST_ASSERT(true)

        mutex1.lock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)

        mutex1.unlock();
        TEST_ASSERT(true)


        KMutex mutex2;
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.lock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.lock();
        TEST_ASSERT(true)

        mutex2.tryToLock();
        TEST_ASSERT(true)

        mutex2.lock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)

        mutex2.unlock();
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMutexUnitTest::testSynchronization()
{
    try
    {
        _concurrent = false;

        KRunnableMutexTestClass runnable01(*this, 1);
        KRunnableMutexTestClass runnable02(*this, 2);

        TThread<KRunnableMutexTestClass, &KRunnableMutexTestClass::run> thread1(runnable01);
        TThread<KRunnableMutexTestClass, &KRunnableMutexTestClass::run> thread2(runnable02);

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

KRunnableMutexTestClass::KRunnableMutexTestClass(KMutexUnitTest& test, klab::UInt32 id) : 
_test(test), _id(id)
{}

// ---------------------------------------------------------------------------------------------------- //

KRunnableMutexTestClass::~KRunnableMutexTestClass()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableMutexTestClass::run(const IThreadStatus& status)
{
    while(status.checkThreadState() && _test.protectedAccess(_id))
        klab::Sleep(2);           
}

// ---------------------------------------------------------------------------------------------------- //
