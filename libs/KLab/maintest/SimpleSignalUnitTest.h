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

#ifndef KLAB_SIMPLESIGNALUNITTEST_H
#define KLAB_SIMPLESIGNALUNITTEST_H

#include <cpptest.h>
#include "../include/Thread.h"
#include "../include/SimpleSignal.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KSimpleSignalUnitTest : public Test::Suite
{
public:
    
    KSimpleSignalUnitTest();
    virtual ~KSimpleSignalUnitTest();


protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();    

    // Methods tests.
    void    testWait();
    void    testSet();

    // Functionnal tests.
    void    testSynchronization();


private:

    KSimpleSignalUnitTest(const KSimpleSignalUnitTest& test);
    KSimpleSignalUnitTest&  operator=(const KSimpleSignalUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

class KRunnableSimpleSignalTestClass
{
public:

    KRunnableSimpleSignalTestClass(klab::KSimpleSignal& signal, klab::UInt32 sleepTime);
    virtual ~KRunnableSimpleSignalTestClass();

    void                run(const IThreadStatus& status);


private:

    KRunnableSimpleSignalTestClass();
    KRunnableSimpleSignalTestClass(const KRunnableSimpleSignalTestClass& thread);
    KRunnableSimpleSignalTestClass& operator=(const KRunnableSimpleSignalTestClass& thread);


private:

    klab::KSimpleSignal&    _signal;
    klab::Int32             _sleepTime;
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
