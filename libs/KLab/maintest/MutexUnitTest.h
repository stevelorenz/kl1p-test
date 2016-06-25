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

#ifndef KLAB_MUTEXUNITTEST_H
#define KLAB_MUTEXUNITTEST_H

#include <cpptest.h>
#include "../include/Thread.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KMutexUnitTest : public Test::Suite
{
public:
    
    KMutexUnitTest();
    virtual ~KMutexUnitTest();

    bool    unprotectedAccess(klab::UInt32 id);
    bool    protectedAccess(klab::UInt32 id);
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();    

    // Methods tests.
    void    testLock();
    void    testTryToLock();
    void    testUnlock();

    // Functionnal tests.
    void    testSynchronization();


private:

    KMutexUnitTest(const KMutexUnitTest& test);
    KMutexUnitTest&     operator=(const KMutexUnitTest& test);


private:

    KMutex          _mutex;

    bool            _concurrent;
    klab::UInt32    _lastID;
};

// ---------------------------------------------------------------------------------------------------- //

class KRunnableMutexTestClass
{
public:

    KRunnableMutexTestClass(KMutexUnitTest& test, klab::UInt32 id);
    virtual ~KRunnableMutexTestClass();

    void            run(const IThreadStatus& status);


private:

    KRunnableMutexTestClass(const KRunnableMutexTestClass& thread);
    KRunnableMutexTestClass&    operator=(const KRunnableMutexTestClass& thread);


private:

    KMutexUnitTest&     _test;
    klab::UInt32        _id;
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
