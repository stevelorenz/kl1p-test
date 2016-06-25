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

#ifndef KLAB_SIGNALUNITTEST_H
#define KLAB_SIGNALUNITTEST_H

#include <cpptest.h>
#include "../include/Thread.h"
#include "../include/Signal.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KSignalUnitTest : public Test::Suite
{
public:
    
    KSignalUnitTest();
    virtual ~KSignalUnitTest();


protected:

    // Construction/Affectation tests.
    void    testMutexConstructor();    

    // Methods tests.
    void    testMutex();
    void    testWait();
    void    testSet();

    // Functionnal tests.
    void    testSynchronization();
    void    testSynchronization_02();


private:

    KSignalUnitTest(const KSignalUnitTest& test);
    KSignalUnitTest&    operator=(const KSignalUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

class KRunnableSignalTestClass
{
public:

    KRunnableSignalTestClass();
    virtual ~KRunnableSignalTestClass();

    void                run(const IThreadStatus& status);
    void                sendSignal();

    klab::UInt32        testCode() const;


private:

    KRunnableSignalTestClass(const KRunnableSignalTestClass& thread);
    KRunnableSignalTestClass&   operator=(const KRunnableSignalTestClass& thread);


private:

    klab::KMutex    _mutex;
    klab::KSignal   _signal;
    klab::UInt32    _testCode;
};

// ---------------------------------------------------------------------------------------------------- //

class KRunnableSignalTestClass02
{
public:

    KRunnableSignalTestClass02(klab::KSignal& signal, klab::UInt32 sleepTime);
    virtual ~KRunnableSignalTestClass02();

    void                run(const IThreadStatus& status);


private:

    KRunnableSignalTestClass02();
    KRunnableSignalTestClass02(const KRunnableSignalTestClass02& thread);
    KRunnableSignalTestClass02&     operator=(const KRunnableSignalTestClass02& thread);


private:

    klab::KSignal&  _signal;
    klab::Int32     _sleepTime;
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
