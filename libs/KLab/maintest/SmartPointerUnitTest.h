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

#ifndef KLAB_SMARTPOINTERUNITTEST_H
#define KLAB_SMARTPOINTERUNITTEST_H

#include <cpptest.h>
#include "../include/AtomicCount.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KSmartPointerUnitTest : public Test::Suite
{
public:
    
    KSmartPointerUnitTest();
    virtual ~KSmartPointerUnitTest();


public:

    static bool IsDeleted;
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();
    void    testPointerConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Operators tests.
    void    testIndirectionOperator();
    void    testEqualOperator();
    void    testNotEqualOperator();
    void    testLessThanOperator();

    // Methods tests.
    void    testGet();
    void    testIsValid();
    void    testIsNull();
    void    testReset();
    void    testSwap();

    // Functions tests.
    void    testStatic_pointer_cast();
    void    testConst_pointer_cast();
    void    testDynamic_pointer_cast();
    void    testCheckedDelete();


private:

    KSmartPointerUnitTest(const KSmartPointerUnitTest& test);
    KSmartPointerUnitTest&  operator=(const KSmartPointerUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

class KTestSmartPointerClass
{
public:

    KTestSmartPointerClass();
    KTestSmartPointerClass(klab::UInt32 testCode);
    KTestSmartPointerClass(const KTestSmartPointerClass& obj);
    virtual ~KTestSmartPointerClass();

    KTestSmartPointerClass& operator=(const KTestSmartPointerClass& obj);

    void                setTestCode(klab::UInt32 testCode);
    klab::UInt32        testCode() const;


protected:

    friend void         AddSmartPointerReference(const KTestSmartPointerClass* ptr);
    friend void         ReleaseSmartPointerReference(const KTestSmartPointerClass* ptr);


private:

    friend class KSmartPointerUnitTest;


private:

    klab::UInt32        _testCode;
    mutable klab::TAtomicCount<klab::UInt32>    _countReferences;
};

// ---------------------------------------------------------------------------------------------------- //

class KTestSmartPointerInheritedClass : public KTestSmartPointerClass
{
public:

    KTestSmartPointerInheritedClass();
    KTestSmartPointerInheritedClass(klab::UInt32 testCode);
    KTestSmartPointerInheritedClass(const KTestSmartPointerInheritedClass& obj);
    virtual ~KTestSmartPointerInheritedClass();

    KTestSmartPointerInheritedClass&    operator=(const KTestSmartPointerInheritedClass& obj);

    klab::UInt32        testCode() const;


private:

    friend class KSmartPointerUnitTest;
};

// ---------------------------------------------------------------------------------------------------- //

class ITestSmartPointerInterface
{
public:

    virtual ~ITestSmartPointerInterface() = 0;

    virtual void                setTestCode(klab::UInt32 testCode) = 0;
    virtual klab::UInt32        testCode() const = 0;


protected:

    virtual klab::UInt32        countReferences() const = 0;
    virtual klab::UInt32        incrementReferencesCount() = 0;
    virtual klab::UInt32        decrementReferencesCount() = 0;

    friend void                 AddSmartPointerReference(const ITestSmartPointerInterface* ptr);
    friend void                 ReleaseSmartPointerReference(const ITestSmartPointerInterface* ptr);


private:

    friend class KSmartPointerUnitTest;
};

// ---------------------------------------------------------------------------------------------------- //

class KTestSmartPointerImplementedClass : public virtual ITestSmartPointerInterface
{
public:

    KTestSmartPointerImplementedClass();
    KTestSmartPointerImplementedClass(klab::UInt32 testCode);
    KTestSmartPointerImplementedClass(const KTestSmartPointerImplementedClass& obj);
    virtual ~KTestSmartPointerImplementedClass();

    KTestSmartPointerImplementedClass&  operator=(const KTestSmartPointerImplementedClass& obj);

    virtual void                setTestCode(klab::UInt32 testCode);
    virtual klab::UInt32        testCode() const;


protected:

    virtual klab::UInt32        countReferences() const;
    virtual klab::UInt32        incrementReferencesCount();
    virtual klab::UInt32        decrementReferencesCount();


private:

    friend class KSmartPointerUnitTest;                 


private:

    klab::UInt32                _testCode;
    mutable klab::TAtomicCount<klab::UInt32>    _countReferences;
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
