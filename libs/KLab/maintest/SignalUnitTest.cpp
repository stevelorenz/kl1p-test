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

#include "SignalUnitTest.h"
#include "../include/Signal.h"
#include "../include/Timer.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KSignalUnitTest::KSignalUnitTest() : Test::Suite()
{
    TEST_ADD(KSignalUnitTest::testMutexConstructor)

    TEST_ADD(KSignalUnitTest::testMutex)
    TEST_ADD(KSignalUnitTest::testWait)
    TEST_ADD(KSignalUnitTest::testSet)

    TEST_ADD(KSignalUnitTest::testSynchronization)
    TEST_ADD(KSignalUnitTest::testSynchronization_02)
}

// ---------------------------------------------------------------------------------------------------- //

KSignalUnitTest::~KSignalUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUnitTest::testMutexConstructor()
{
    try
    {
        klab::KMutex mutex;

        klab::TSignal<> signal1(mutex);
        TEST_ASSERT(true)

        klab::KSignal signal2(mutex);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUnitTest::testMutex()
{
    try
    {
        klab::KMutex mutex;


        klab::TSignal<> signal1(mutex);
        klab::KMutex& m = signal1.mutex();
        TEST_ASSERT(true)

        const klab::TSignal<> signal2(mutex);
        const klab::KMutex& cm = signal2.mutex();
        TEST_ASSERT(true)


        klab::KSignal signal3(mutex);
        klab::KMutex& m2 = signal3.mutex();
        TEST_ASSERT(true)

        const klab::KSignal signal4(mutex);
        const klab::KMutex& cm2 = signal4.mutex();
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUnitTest::testWait()
{
    try
    {
        // Tested in testSynchronization function below.
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUnitTest::testSet()
{
    try
    {
        klab::KMutex mutex;

        klab::TSignal<> signal1(mutex);
        TEST_ASSERT(true)

        signal1.set();
        TEST_ASSERT(true)


        klab::KSignal signal2(mutex);
        TEST_ASSERT(true)

        signal2.set();
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUnitTest::testSynchronization()
{
    try
    {
        KRunnableSignalTestClass runnable;
        TThread<KRunnableSignalTestClass, &KRunnableSignalTestClass::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(runnable.testCode() == 0)

        runnable.sendSignal();
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(runnable.testCode() == 0)

        TEST_ASSERT(thread.start())
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        TEST_ASSERT(runnable.testCode() >= 0)

        runnable.sendSignal();
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        TEST_ASSERT(runnable.testCode() >= 0)

        klab::Sleep(50);
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        TEST_ASSERT(runnable.testCode() == 5)

        klab::Sleep(50);
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        TEST_ASSERT(runnable.testCode() == 5)

        runnable.sendSignal();
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        TEST_ASSERT(runnable.testCode() >= 5)

        klab::Sleep(10);
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        TEST_ASSERT(runnable.testCode() > 5)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSignalUnitTest::testSynchronization_02()
{
    try
    {
        klab::KMutex  mutex;
        klab::KSignal signal(mutex);
        klab::KTimer  timer;

        KRunnableSignalTestClass02 runnable01(signal, 100);
        KRunnableSignalTestClass02 runnable02(signal, 200);
        KRunnableSignalTestClass02 runnable03(signal, 300);

        TThread<KRunnableSignalTestClass02, &KRunnableSignalTestClass02::run> thread01(runnable01);
        TThread<KRunnableSignalTestClass02, &KRunnableSignalTestClass02::run> thread02(runnable02);
        TThread<KRunnableSignalTestClass02, &KRunnableSignalTestClass02::run> thread03(runnable03);

        timer.start();

        thread01.start();
        thread02.start();
        thread03.start();
        TEST_ASSERT(thread01.isStarted() == true)
        TEST_ASSERT(thread01.isSuspended() == false)
        TEST_ASSERT(thread01.isRunning() == true)
        TEST_ASSERT(thread02.isStarted() == true)
        TEST_ASSERT(thread02.isSuspended() == false)
        TEST_ASSERT(thread02.isRunning() == true)
        TEST_ASSERT(thread03.isStarted() == true)
        TEST_ASSERT(thread03.isSuspended() == false)
        TEST_ASSERT(thread03.isRunning() == true)
                
        mutex.lock();
        signal.wait();
        mutex.unlock();
        TEST_ASSERT(timer.durationInMilliseconds() > 90)
        klab::Sleep(10);        
        TEST_ASSERT(thread01.isStarted() == false)
        TEST_ASSERT(thread01.isSuspended() == false)
        TEST_ASSERT(thread01.isRunning() == false)
        TEST_ASSERT(thread02.isStarted() == true)
        TEST_ASSERT(thread02.isSuspended() == false)
        TEST_ASSERT(thread02.isRunning() == true)
        TEST_ASSERT(thread03.isStarted() == true)
        TEST_ASSERT(thread03.isSuspended() == false)
        TEST_ASSERT(thread03.isRunning() == true)

        mutex.lock();
        signal.wait();
        mutex.unlock();
        TEST_ASSERT(timer.durationInMilliseconds() > 180)
        klab::Sleep(10);
        TEST_ASSERT(thread01.isStarted() == false)
        TEST_ASSERT(thread01.isSuspended() == false)
        TEST_ASSERT(thread01.isRunning() == false)
        TEST_ASSERT(thread02.isStarted() == false)
        TEST_ASSERT(thread02.isSuspended() == false)
        TEST_ASSERT(thread02.isRunning() == false)
        TEST_ASSERT(thread03.isStarted() == true)
        TEST_ASSERT(thread03.isSuspended() == false)
        TEST_ASSERT(thread03.isRunning() == true)

        mutex.lock();
        signal.wait();
        mutex.unlock();
        TEST_ASSERT(timer.durationInMilliseconds() > 270)
        klab::Sleep(10);
        TEST_ASSERT(thread01.isStarted() == false)
        TEST_ASSERT(thread01.isSuspended() == false)
        TEST_ASSERT(thread01.isRunning() == false)
        TEST_ASSERT(thread02.isStarted() == false)
        TEST_ASSERT(thread02.isSuspended() == false)
        TEST_ASSERT(thread02.isRunning() == false)
        TEST_ASSERT(thread03.isStarted() == false)
        TEST_ASSERT(thread03.isSuspended() == false)
        TEST_ASSERT(thread03.isRunning() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

KRunnableSignalTestClass::KRunnableSignalTestClass() : 
_mutex(), _signal(_mutex), _testCode(0)
{}

// ---------------------------------------------------------------------------------------------------- //

KRunnableSignalTestClass::~KRunnableSignalTestClass()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableSignalTestClass::run(const IThreadStatus& status)
{
    _mutex.lock();
    _testCode = 0;
    _mutex.unlock();
 
    while(status.checkThreadState())    
    {		
        _mutex.lock();
        if(_testCode == 5)
            _signal.wait();

        ++_testCode;	        
        _mutex.unlock();

        klab::Sleep(2);
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableSignalTestClass::sendSignal()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    _signal.set();
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KRunnableSignalTestClass::testCode() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _testCode;
}

// ---------------------------------------------------------------------------------------------------- //

KRunnableSignalTestClass02::KRunnableSignalTestClass02(klab::KSignal& signal, klab::UInt32 sleepTime) : 
_signal(signal), _sleepTime(sleepTime)
{}

// ---------------------------------------------------------------------------------------------------- //

KRunnableSignalTestClass02::~KRunnableSignalTestClass02()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableSignalTestClass02::run(const IThreadStatus& status)
{
    klab::Sleep(_sleepTime);

    _signal.mutex().lock();
    _signal.set();
    _signal.mutex().unlock();
}

// ---------------------------------------------------------------------------------------------------- //
