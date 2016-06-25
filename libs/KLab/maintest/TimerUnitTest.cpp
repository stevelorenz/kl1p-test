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

#include "TimerUnitTest.h"
#include "../include/Timer.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KTimerUnitTest::KTimerUnitTest() : Test::Suite()
{
    TEST_ADD(KTimerUnitTest::testDefaultConstructor)
    TEST_ADD(KTimerUnitTest::testCopyConstructor)
    TEST_ADD(KTimerUnitTest::testAffectationOperator)

    TEST_ADD(KTimerUnitTest::testStart)
    TEST_ADD(KTimerUnitTest::testSuspend)
    TEST_ADD(KTimerUnitTest::testResume)
    TEST_ADD(KTimerUnitTest::testStop)
    TEST_ADD(KTimerUnitTest::testReset)
    TEST_ADD(KTimerUnitTest::testIsStarted)
    TEST_ADD(KTimerUnitTest::testIsSuspended)
    TEST_ADD(KTimerUnitTest::testIsRunning)
    TEST_ADD(KTimerUnitTest::testDuration)
    TEST_ADD(KTimerUnitTest::testDurationInMicroseconds)
    TEST_ADD(KTimerUnitTest::testDurationInMilliseconds)
    TEST_ADD(KTimerUnitTest::testDurationInSeconds)
}

// ---------------------------------------------------------------------------------------------------- //

KTimerUnitTest::~KTimerUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testDefaultConstructor()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testCopyConstructor()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        KTimer timerCopy(timer);
        TEST_ASSERT(timerCopy.isStarted() == false)
        TEST_ASSERT(timerCopy.isSuspended() == false)
        TEST_ASSERT(timerCopy.isRunning() == false)
        TEST_ASSERT(timerCopy.duration() == 0)


        timer.start();
        klab::Sleep(100);
        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        KTimer timerCopy2(timer);
        TEST_ASSERT(timerCopy2.isStarted() == false)
        TEST_ASSERT(timerCopy2.isSuspended() == false)
        TEST_ASSERT(timerCopy2.isRunning() == false)
        TEST_ASSERT(timerCopy2.duration() == duration)


        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        KTimer timerCopy3(timer);
        TEST_ASSERT(timerCopy3.isStarted() == true)
        TEST_ASSERT(timerCopy3.isSuspended() == false)
        TEST_ASSERT(timerCopy3.isRunning() == true)
        TEST_ASSERT(timerCopy3.duration() >= duration)


        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        KTimer timerCopy4(timer);
        TEST_ASSERT(timerCopy4.isStarted() == true)
        TEST_ASSERT(timerCopy4.isSuspended() == true)
        TEST_ASSERT(timerCopy4.isRunning() == false)
        TEST_ASSERT(timerCopy4.duration() == duration)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testAffectationOperator()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        KTimer timerCopy;
        timerCopy = timer;
        TEST_ASSERT(timerCopy.isStarted() == false)
        TEST_ASSERT(timerCopy.isSuspended() == false)
        TEST_ASSERT(timerCopy.isRunning() == false)
        TEST_ASSERT(timerCopy.duration() == 0)


        timer.start();
        klab::Sleep(100);
        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        KTimer timerCopy2;
        timerCopy2 = timer;
        TEST_ASSERT(timerCopy2.isStarted() == false)
        TEST_ASSERT(timerCopy2.isSuspended() == false)
        TEST_ASSERT(timerCopy2.isRunning() == false)
        TEST_ASSERT(timerCopy2.duration() == duration)


        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        KTimer timerCopy3;
        timerCopy3 = timer;
        TEST_ASSERT(timerCopy3.isStarted() == true)
        TEST_ASSERT(timerCopy3.isSuspended() == false)
        TEST_ASSERT(timerCopy3.isRunning() == true)
        TEST_ASSERT(timerCopy3.duration() >= duration)


        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        KTimer timerCopy4;
        timerCopy4 = timer;
        TEST_ASSERT(timerCopy4.isStarted() == true)
        TEST_ASSERT(timerCopy4.isSuspended() == true)
        TEST_ASSERT(timerCopy4.isRunning() == false)
        TEST_ASSERT(timerCopy4.duration() == duration)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testStart()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration>=0 && duration<90000)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testSuspend()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == duration)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        klab::KMicrosecTime duration2 = timer.duration();
        TEST_ASSERT(duration2 == duration)

        timer.resume();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        klab::KMicrosecTime duration3 = timer.duration();
        TEST_ASSERT(duration3 >= duration)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration3 = timer.duration();
        TEST_ASSERT(duration3 >= 90000+duration)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testResume()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.resume();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        timer.resume();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        TEST_ASSERT(timer.duration() >= duration)        

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        klab::KMicrosecTime duration2 = timer.duration();
        TEST_ASSERT(duration2 == duration)

        timer.resume();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        klab::KMicrosecTime duration3 = timer.duration();
        TEST_ASSERT(duration3 >= duration)

        timer.resume();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        TEST_ASSERT(timer.duration() >= duration3)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration3 = timer.duration();
        TEST_ASSERT(duration3 >= 90000+duration)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testStop()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == duration)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(timer.duration() == duration)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == duration)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 0)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        klab::KMicrosecTime duration2 = timer.duration();
        TEST_ASSERT(duration2 == duration)

        timer.resume();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        klab::KMicrosecTime duration3 = timer.duration();
        TEST_ASSERT(duration3 >= duration)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration3 = timer.duration();
        TEST_ASSERT(duration3 >= 90000+duration)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration >= 90000)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == duration)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testReset()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration == 0)

        timer.reset();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration == 0)

        timer.start();
        klab::Sleep(10);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration > 9000)

        timer.reset();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration < 1000)
        
        klab::Sleep(10);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        duration = timer.duration();
        TEST_ASSERT(duration > 9000)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)        
        TEST_ASSERT(timer.duration() >= duration)
        duration = timer.duration();
        klab::Sleep(10);
        TEST_ASSERT(timer.duration() == duration)

        timer.reset();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration == 0)

        klab::Sleep(10);
        timer.resume();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)        
        TEST_ASSERT(timer.duration() < 1000)

        klab::Sleep(10);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)        
        TEST_ASSERT(timer.duration() > 9000)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)        
        TEST_ASSERT(timer.duration() > 9000)

        timer.reset();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        duration = timer.duration();
        TEST_ASSERT(duration == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testIsStarted()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)

        timer.resume();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testIsSuspended()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)

        timer.resume();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testIsRunning()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)

        timer.suspend();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == true)
        TEST_ASSERT(timer.isRunning() == false)

        timer.resume();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)

        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testDuration()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        TEST_ASSERT(timer.duration() >= 0)

        klab::Sleep(100);
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        TEST_ASSERT(timer.duration() >= 90000)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testDurationInMicroseconds()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        TEST_ASSERT(timer.duration() >= 0)

        klab::Sleep(100);
        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration >= 90000)
        TEST_ASSERT(timer.durationInMicroseconds() == timer.duration())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testDurationInMilliseconds()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        TEST_ASSERT(timer.duration() >= 0)

        klab::Sleep(100);
        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration >= 90000)	
        TEST_ASSERT(klab::Equals(timer.durationInMilliseconds(), static_cast<klab::DoubleReal>(timer.duration())/1000.0, 1e-6))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimerUnitTest::testDurationInSeconds()
{
    try
    {
        KTimer timer;
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        TEST_ASSERT(timer.duration() == 0)

        timer.start();
        TEST_ASSERT(timer.isStarted() == true)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == true)
        TEST_ASSERT(timer.duration() >= 0)

        klab::Sleep(100);
        timer.stop();
        TEST_ASSERT(timer.isStarted() == false)
        TEST_ASSERT(timer.isSuspended() == false)
        TEST_ASSERT(timer.isRunning() == false)
        klab::KMicrosecTime duration = timer.duration();
        TEST_ASSERT(duration >= 90000)
        TEST_ASSERT(klab::Equals(timer.durationInSeconds(), static_cast<klab::DoubleReal>(timer.duration())/1000000.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
