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

#include "SimpleSignalUnitTest.h"
#include "../include/SimpleSignal.h"
#include "../include/Timer.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KSimpleSignalUnitTest::KSimpleSignalUnitTest() : Test::Suite()
{
    TEST_ADD(KSimpleSignalUnitTest::testDefaultConstructor)

    TEST_ADD(KSimpleSignalUnitTest::testWait)
    TEST_ADD(KSimpleSignalUnitTest::testSet)

    TEST_ADD(KSimpleSignalUnitTest::testSynchronization)
}

// ---------------------------------------------------------------------------------------------------- //

KSimpleSignalUnitTest::~KSimpleSignalUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSimpleSignalUnitTest::testDefaultConstructor()
{
    try
    {
        klab::TSimpleSignal<> signal1;
        TEST_ASSERT(true)

        klab::KSimpleSignal signal2;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSimpleSignalUnitTest::testWait()
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

void KSimpleSignalUnitTest::testSet()
{
    try
    {
        klab::TSimpleSignal<> signal1;
        TEST_ASSERT(true)

        signal1.set();
        TEST_ASSERT(true)


        klab::KSimpleSignal signal2;
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

void KSimpleSignalUnitTest::testSynchronization()
{
    try
    {
        klab::KSimpleSignal signal;
        klab::KTimer  timer;

        KRunnableSimpleSignalTestClass runnable01(signal, 100);
        KRunnableSimpleSignalTestClass runnable02(signal, 200);
        KRunnableSimpleSignalTestClass runnable03(signal, 300);

        TThread<KRunnableSimpleSignalTestClass, &KRunnableSimpleSignalTestClass::run> thread01(runnable01);
        TThread<KRunnableSimpleSignalTestClass, &KRunnableSimpleSignalTestClass::run> thread02(runnable02);
        TThread<KRunnableSimpleSignalTestClass, &KRunnableSimpleSignalTestClass::run> thread03(runnable03);

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
                
        signal.wait();
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

        signal.wait();
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

        signal.wait();
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

KRunnableSimpleSignalTestClass::KRunnableSimpleSignalTestClass(klab::KSimpleSignal& signal, klab::UInt32 sleepTime) : 
_signal(signal), _sleepTime(sleepTime)
{}

// ---------------------------------------------------------------------------------------------------- //

KRunnableSimpleSignalTestClass::~KRunnableSimpleSignalTestClass()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableSimpleSignalTestClass::run(const IThreadStatus& status)
{
    klab::Sleep(_sleepTime);

    _signal.set();
}

// ---------------------------------------------------------------------------------------------------- //
