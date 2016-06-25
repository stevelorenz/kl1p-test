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

#include "ThreadUnitTest.h"
#include "../include/Thread.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KThreadUnitTest::KThreadUnitTest() : Test::Suite(),
_mutex(),
_testCode(0), _stopValue(false)
{
    TEST_ADD(KThreadUnitTest::testObjConstructor)

    TEST_ADD(KThreadUnitTest::testStart)
    TEST_ADD(KThreadUnitTest::testSuspend)
    TEST_ADD(KThreadUnitTest::testResume)
    TEST_ADD(KThreadUnitTest::testStop)		
    TEST_ADD(KThreadUnitTest::testIsStarted)
    TEST_ADD(KThreadUnitTest::testIsSuspended)
    TEST_ADD(KThreadUnitTest::testIsRunning)
    TEST_ADD(KThreadUnitTest::testJoin)	
}

// ---------------------------------------------------------------------------------------------------- //

KThreadUnitTest::~KThreadUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::clearTestCode()
{
    klab::TScopedMutex<KMutex> mutex(_mutex);

    _testCode = 0;
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::incrementTestCode()
{
    klab::TScopedMutex<KMutex> mutex(_mutex);

    ++_testCode;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KThreadUnitTest::testCode() const
{
    klab::TScopedMutex<KMutex> mutex(_mutex);

    return _testCode;
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::setStopValue(bool value)
{
    klab::TScopedMutex<KMutex> mutex(_mutex);

    _stopValue = value;
}

// ---------------------------------------------------------------------------------------------------- //

bool KThreadUnitTest::stopValue() const
{
    klab::TScopedMutex<KMutex> mutex(_mutex);

    return _stopValue;
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::testObjConstructor()
{
    try
    {
        KRunnableTestClass runnable(*this);

        TThread<KRunnableTestClass, &KRunnableTestClass::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)		
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::testStart()
{
    try
    {     
        KRunnableTestClass runnable(*this);

        this->clearTestCode();
        this->setStopValue(false);

        TThread<KRunnableTestClass, &KRunnableTestClass::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread.start())	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);	
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread.start())
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue() == false)

        thread.stop();
        klab::Sleep(10);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue())	


        this->clearTestCode();
        this->setStopValue(false);

        KRunnableTestClass runnable2(*this);
        TThread<KRunnableTestClass, &KRunnableTestClass::run> thread2(runnable2);
        TEST_ASSERT(thread2.isStarted() == false)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread2.start())
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue() == false)

        thread2.stop();      
        TEST_ASSERT(thread2.start())    // Test stop-start. 
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(100);
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == true)
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::testSuspend()
{
    try
    {    
        KRunnableTestClass runnable(*this);

        this->clearTestCode();
        this->setStopValue(false);

        TThread<KRunnableTestClass, &KRunnableTestClass::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread.start())	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);	
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue() == false)

        thread.suspend();	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        klab::UInt32 testCode = this->testCode();
        TEST_ASSERT(testCode > 0)	
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(100);
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == testCode)	
        TEST_ASSERT(this->stopValue() == false)

        thread.resume();
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > testCode)		
        TEST_ASSERT(this->stopValue() == false)

        thread.suspend();	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue() == false)

        thread.stop();	
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue())

      
        this->clearTestCode();
        this->setStopValue(false);
        KRunnableTestClass03 runnable2(*this);
        TThread<KRunnableTestClass03, &KRunnableTestClass03::run> thread2(runnable2);
        runnable2.setThread(&thread2);
        TEST_ASSERT(thread2.isStarted() == false)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread2.start())	
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == true)
        TEST_ASSERT(this->testCode() >= 0)	
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(10);	
        testCode = this->testCode();
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended()==false || (testCode==5 && thread2.isSuspended()==true))
        TEST_ASSERT(thread2.isRunning()==true || (testCode==5 && thread2.isRunning()==false))        
        TEST_ASSERT(this->testCode() >= 0)	
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(50);
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended() == true)
        TEST_ASSERT(thread2.isRunning() == false)
        TEST_ASSERT(this->testCode()>testCode || (testCode==5 && this->testCode()==testCode))	
        testCode = this->testCode();
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(50);
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended() == true)
        TEST_ASSERT(thread2.isRunning() == false)
        TEST_ASSERT(this->testCode() == testCode)	
        TEST_ASSERT(this->stopValue() == false)

        thread2.resume();
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == true)
        TEST_ASSERT(this->testCode() >= testCode)	
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(50);
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == true)
        TEST_ASSERT(this->testCode() > testCode)	
        TEST_ASSERT(this->stopValue() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::testResume()
{
    try
    {     
        KRunnableTestClass runnable(*this);

        this->clearTestCode();
        this->setStopValue(false);

        TThread<KRunnableTestClass, &KRunnableTestClass::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread.start())	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);	
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue() == false)

        thread.suspend();	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        klab::UInt32 testCode = this->testCode();
        TEST_ASSERT(testCode > 0)	
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(100);
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == testCode)	
        TEST_ASSERT(this->stopValue() == false)

        thread.resume();
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > testCode)		
        TEST_ASSERT(this->stopValue() == false)

        thread.suspend();	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue() == false)

        thread.stop();	
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::testStop()
{
    try
    {
        KRunnableTestClass runnable(*this);

        this->clearTestCode();
        this->setStopValue(false);

        TThread<KRunnableTestClass, &KRunnableTestClass::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        thread.stop();
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread.start())
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread.start())
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue() == false)

        thread.stop();
        klab::Sleep(10);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue())

        thread.stop();
        klab::Sleep(10);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue())


        this->clearTestCode();
        this->setStopValue(false);
        KRunnableTestClass04 runnable2(*this);
        TThread<KRunnableTestClass04, &KRunnableTestClass04::run> thread2(runnable2);
        runnable2.setThread(&thread2);
        TEST_ASSERT(thread2.isStarted() == false)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread2.start())	
        TEST_ASSERT(thread2.isStarted() == true)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == true)
        TEST_ASSERT(this->testCode() >= 0)	
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(10);	
        klab::UInt32 testCode = this->testCode();
        TEST_ASSERT(thread2.isStarted()==true || (testCode==5 && thread2.isSuspended()==false))
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning()==true || (testCode==5 && thread2.isRunning()==false))        
        TEST_ASSERT(this->testCode() >= 0)	
        TEST_ASSERT(this->stopValue()==false || (testCode==5 && this->stopValue()))

        klab::Sleep(50);
        TEST_ASSERT(thread2.isStarted() == false)
        TEST_ASSERT(thread2.isSuspended() == false)
        TEST_ASSERT(thread2.isRunning() == false)
        TEST_ASSERT(this->testCode()>testCode || (testCode==5 && this->testCode()==testCode))	
        TEST_ASSERT(this->stopValue())        
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::testIsStarted()
{
    try
    {
        KRunnableTestClass runnable(*this);

        this->clearTestCode();
        this->setStopValue(false);

        TThread<KRunnableTestClass, &KRunnableTestClass::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread.start())
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue() == false)

        thread.stop();
        klab::Sleep(10);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() > 0)
        TEST_ASSERT(this->stopValue())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::testIsSuspended()
{
    try
    {     
        KRunnableTestClass runnable(*this);

        this->clearTestCode();
        this->setStopValue(false);

        TThread<KRunnableTestClass, &KRunnableTestClass::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread.start())	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);	
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue() == false)

        thread.suspend();	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        klab::UInt32 testCode = this->testCode();
        TEST_ASSERT(testCode > 0)	
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(100);
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == testCode)	
        TEST_ASSERT(this->stopValue() == false)

        thread.resume();
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > testCode)		
        TEST_ASSERT(this->stopValue() == false)

        thread.suspend();	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue() == false)

        thread.stop();	
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::testIsRunning()
{
    try
    {     
        KRunnableTestClass runnable(*this);

        this->clearTestCode();
        this->setStopValue(false);

        TThread<KRunnableTestClass, &KRunnableTestClass::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)

        TEST_ASSERT(thread.start())	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);	
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue() == false)

        thread.suspend();	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        klab::UInt32 testCode = this->testCode();
        TEST_ASSERT(testCode > 0)	
        TEST_ASSERT(this->stopValue() == false)

        klab::Sleep(100);
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == testCode)	
        TEST_ASSERT(this->stopValue() == false)

        thread.resume();
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > testCode)		
        TEST_ASSERT(this->stopValue() == false)

        thread.suspend();	
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == true)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue() == false)

        thread.stop();	
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        klab::Sleep(10);
        TEST_ASSERT(this->testCode() > 0)	
        TEST_ASSERT(this->stopValue())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KThreadUnitTest::testJoin()
{
    try
    {		
        KRunnableTestClass02 runnable(*this);

        this->clearTestCode();
        this->setStopValue(false);

        TThread<KRunnableTestClass02, &KRunnableTestClass02::run> thread(runnable);
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)
        TEST_ASSERT(this->testCode() == 0)
        TEST_ASSERT(this->stopValue() == false)
	
        TEST_ASSERT(thread.start())
        TEST_ASSERT(thread.isStarted() == true)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == true)
        TEST_ASSERT(this->testCode() >= 0)
        TEST_ASSERT(this->stopValue() == false)

        thread.join();		
        TEST_ASSERT(thread.isStarted() == false)
        TEST_ASSERT(thread.isSuspended() == false)
        TEST_ASSERT(thread.isRunning() == false)		
        TEST_ASSERT(this->testCode() == 10)	
        TEST_ASSERT(this->stopValue())		
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

KRunnableTestClass::KRunnableTestClass(KThreadUnitTest& test) : 
_test(test)
{}

// ---------------------------------------------------------------------------------------------------- //

KRunnableTestClass::~KRunnableTestClass()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableTestClass::run(const IThreadStatus& status)
{
    _test.clearTestCode();  

    while(status.checkThreadState())    
    {
        _test.incrementTestCode();  			
        _test.setStopValue(false); 		
    }

    _test.setStopValue(true);      	
}

// ---------------------------------------------------------------------------------------------------- //

KRunnableTestClass02::KRunnableTestClass02(KThreadUnitTest& test) : 
_test(test)
{}

// ---------------------------------------------------------------------------------------------------- //

KRunnableTestClass02::~KRunnableTestClass02()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableTestClass02::run(const IThreadStatus& status)
{
    _countLoops = 0;

    _test.clearTestCode();  
    while(status.checkThreadState() && _countLoops<10)    
    {		
        klab::Sleep(10);

        _test.incrementTestCode();  
        _test.setStopValue(false); 

        ++_countLoops;		
    }

    _test.setStopValue(true);       
}

// ---------------------------------------------------------------------------------------------------- //

KRunnableTestClass03::KRunnableTestClass03(KThreadUnitTest& test) : 
_test(test), _thread(0)
{}

// ---------------------------------------------------------------------------------------------------- //

KRunnableTestClass03::~KRunnableTestClass03()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableTestClass03::run(const IThreadStatus& status)
{
    _countLoops = 0;

    _test.clearTestCode();  
    while(status.checkThreadState())    
    {		
        klab::Sleep(2);

        _test.incrementTestCode();  
        _test.setStopValue(false); 

        ++_countLoops;	

        if(_thread!=0 && _countLoops==5)
            _thread->suspend();
    }

    _test.setStopValue(true);       
}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableTestClass03::setThread(klab::TThread<KRunnableTestClass03, &KRunnableTestClass03::run>* thread)
{
    _thread = thread;
}

// ---------------------------------------------------------------------------------------------------- //

KRunnableTestClass04::KRunnableTestClass04(KThreadUnitTest& test) : 
_test(test), _thread(0)
{}

// ---------------------------------------------------------------------------------------------------- //

KRunnableTestClass04::~KRunnableTestClass04()
{}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableTestClass04::run(const IThreadStatus& status)
{
    _countLoops = 0;

    _test.clearTestCode();  
    while(status.checkThreadState())    
    {		
        klab::Sleep(2);

        _test.incrementTestCode();  
        _test.setStopValue(false); 

        ++_countLoops;	

        if(_thread!=0 && _countLoops==5)
            _thread->stop();
    }

    _test.setStopValue(true);       
}

// ---------------------------------------------------------------------------------------------------- //

void KRunnableTestClass04::setThread(klab::TThread<KRunnableTestClass04, &KRunnableTestClass04::run>* thread)
{
    _thread = thread;
}

// ---------------------------------------------------------------------------------------------------- //
