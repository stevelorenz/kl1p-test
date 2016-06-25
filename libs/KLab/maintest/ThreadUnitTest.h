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

#ifndef KLAB_THREADUNITTEST_H
#define KLAB_THREADUNITTEST_H

#include <cpptest.h>
#include "../include/Thread.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KThreadUnitTest : public Test::Suite
{
public:
    
    KThreadUnitTest();
    virtual ~KThreadUnitTest();

    void            clearTestCode();
    void            incrementTestCode();
    klab::UInt32    testCode() const;

    void            setStopValue(bool value);
    bool            stopValue() const;
    
    
protected:

    // Construction/Affectation tests.
    void    testObjConstructor();    

    // Methods tests.
    void    testStart();
    void    testSuspend();
    void    testResume();
    void    testStop();
    void    testIsStarted();
    void    testIsSuspended();
    void    testIsRunning();
    void    testJoin();


private:

    KThreadUnitTest(const KThreadUnitTest& test);
    KThreadUnitTest&    operator=(const KThreadUnitTest& test);


private:

    KMutex              _mutex;

    klab::UInt32        _testCode;
    bool                _stopValue;
};

// ---------------------------------------------------------------------------------------------------- //

class KRunnableTestClass
{
public:

    KRunnableTestClass(KThreadUnitTest& test);
    virtual ~KRunnableTestClass();

    void            run(const IThreadStatus& status);


private:

    KRunnableTestClass(const KRunnableTestClass& thread);
    KRunnableTestClass&     operator=(const KRunnableTestClass& thread);


private:

    KThreadUnitTest&    _test;
};

// ---------------------------------------------------------------------------------------------------- //

class KRunnableTestClass02
{
public:

    KRunnableTestClass02(KThreadUnitTest& test);
    virtual ~KRunnableTestClass02();

    void            run(const IThreadStatus& status);


private:

    KRunnableTestClass02(const KRunnableTestClass02& thread);
    KRunnableTestClass02&   operator=(const KRunnableTestClass02& thread);


private:

    KThreadUnitTest&    _test;
    klab::UInt32        _countLoops;
};

// ---------------------------------------------------------------------------------------------------- //

class KRunnableTestClass03
{
public:

    KRunnableTestClass03(KThreadUnitTest& test);
    virtual ~KRunnableTestClass03();

    void            run(const IThreadStatus& status);

    void            setThread(klab::TThread<KRunnableTestClass03, &KRunnableTestClass03::run>* thread);


private:

    KRunnableTestClass03(const KRunnableTestClass03& thread);
    KRunnableTestClass03&   operator=(const KRunnableTestClass03& thread);


private:

    KThreadUnitTest&    _test;
    klab::UInt32        _countLoops;

    klab::TThread<KRunnableTestClass03, &KRunnableTestClass03::run>*    _thread;  
};

// ---------------------------------------------------------------------------------------------------- //

class KRunnableTestClass04
{
public:

    KRunnableTestClass04(KThreadUnitTest& test);
    virtual ~KRunnableTestClass04();

    void            run(const IThreadStatus& status);

    void            setThread(klab::TThread<KRunnableTestClass04, &KRunnableTestClass04::run>* thread);


private:

    KRunnableTestClass04(const KRunnableTestClass04& thread);
    KRunnableTestClass04&   operator=(const KRunnableTestClass04& thread);


private:

    KThreadUnitTest&    _test;
    klab::UInt32        _countLoops;

    klab::TThread<KRunnableTestClass04, &KRunnableTestClass04::run>*    _thread;  
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
