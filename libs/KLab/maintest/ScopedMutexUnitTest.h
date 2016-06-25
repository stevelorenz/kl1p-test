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

#ifndef KLAB_SCOPEDMUTEXUNITTEST_H
#define KLAB_SCOPEDMUTEXUNITTEST_H

#include <cpptest.h>
#include "../include/Thread.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KScopedMutexUnitTest : public Test::Suite
{
public:
    
    KScopedMutexUnitTest();
    virtual ~KScopedMutexUnitTest();

    bool    unprotectedAccess(klab::UInt32 id);
    bool    protectedAccess(klab::UInt32 id);
    
    
protected:

    // Construction/Affectation tests.
    void    testMutexConstructor();    

    // Functionnal tests.
    void    testSynchronization();


private:

    KScopedMutexUnitTest(const KScopedMutexUnitTest& test);
    KScopedMutexUnitTest&   operator=(const KScopedMutexUnitTest& test);


private:

    KMutex          _mutex;

    bool            _concurrent;
    klab::UInt32    _lastID;
};

// ---------------------------------------------------------------------------------------------------- //

class KRunnableScopedMutexTestClass
{
public:

    KRunnableScopedMutexTestClass(KScopedMutexUnitTest& test, klab::UInt32 id);
    virtual ~KRunnableScopedMutexTestClass();

    void            run(const IThreadStatus& status);


private:

    KRunnableScopedMutexTestClass(const KRunnableScopedMutexTestClass& thread);
    KRunnableScopedMutexTestClass&  operator=(const KRunnableScopedMutexTestClass& thread);


private:

    KScopedMutexUnitTest&   _test;
    klab::UInt32            _id;
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
