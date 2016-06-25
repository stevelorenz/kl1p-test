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

#include "SmartPointerUnitTest.h"
#include "../include/SmartPointer.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

bool KSmartPointerUnitTest::IsDeleted = false;

// ---------------------------------------------------------------------------------------------------- //

KSmartPointerUnitTest::KSmartPointerUnitTest() : Test::Suite()
{
    TEST_ADD(KSmartPointerUnitTest::testDefaultConstructor)
    TEST_ADD(KSmartPointerUnitTest::testPointerConstructor)
    TEST_ADD(KSmartPointerUnitTest::testCopyConstructor)
    TEST_ADD(KSmartPointerUnitTest::testAffectationOperator)

    TEST_ADD(KSmartPointerUnitTest::testIndirectionOperator)
    TEST_ADD(KSmartPointerUnitTest::testEqualOperator)
    TEST_ADD(KSmartPointerUnitTest::testNotEqualOperator)
    TEST_ADD(KSmartPointerUnitTest::testLessThanOperator)

    TEST_ADD(KSmartPointerUnitTest::testGet)
    TEST_ADD(KSmartPointerUnitTest::testIsValid)
    TEST_ADD(KSmartPointerUnitTest::testIsNull)
    TEST_ADD(KSmartPointerUnitTest::testReset)
    TEST_ADD(KSmartPointerUnitTest::testSwap)

    TEST_ADD(KSmartPointerUnitTest::testStatic_pointer_cast)
    TEST_ADD(KSmartPointerUnitTest::testConst_pointer_cast)
    TEST_ADD(KSmartPointerUnitTest::testDynamic_pointer_cast)
    TEST_ADD(KSmartPointerUnitTest::testCheckedDelete)
}

// ---------------------------------------------------------------------------------------------------- //

KSmartPointerUnitTest::~KSmartPointerUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testDefaultConstructor()
{
    try
    {
        klab::TSmartPointer<KTestSmartPointerClass> ptr01;
        TEST_ASSERT(ptr01.get() == 0)
        TEST_ASSERT(ptr01.isValid() == false)
        TEST_ASSERT(ptr01.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerClass> ptr01c;
        TEST_ASSERT(ptr01c.get() == 0)
        TEST_ASSERT(ptr01c.isValid() == false)
        TEST_ASSERT(ptr01c.isNull() == true)


        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr02;
        TEST_ASSERT(ptr02.get() == 0)
        TEST_ASSERT(ptr02.isValid() == false)
        TEST_ASSERT(ptr02.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr02c;
        TEST_ASSERT(ptr02c.get() == 0)
        TEST_ASSERT(ptr02c.isValid() == false)
        TEST_ASSERT(ptr02c.isNull() == true)


        klab::TSmartPointer<ITestSmartPointerInterface> ptr03;
        TEST_ASSERT(ptr03.get() == 0)
        TEST_ASSERT(ptr03.isValid() == false)
        TEST_ASSERT(ptr03.isNull() == true)

        klab::TSmartPointer<const ITestSmartPointerInterface> ptr03c;
        TEST_ASSERT(ptr03c.get() == 0)
        TEST_ASSERT(ptr03c.isValid() == false)
        TEST_ASSERT(ptr03c.isNull() == true)


        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr04;
        TEST_ASSERT(ptr04.get() == 0)
        TEST_ASSERT(ptr04.isValid() == false)
        TEST_ASSERT(ptr04.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptr04c;
        TEST_ASSERT(ptr04c.get() == 0)
        TEST_ASSERT(ptr04c.isValid() == false)
        TEST_ASSERT(ptr04c.isNull() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testPointerConstructor()
{
    try
    {
        KTestSmartPointerClass*            p01 = 0;
        KTestSmartPointerInheritedClass*   p02 = 0;
        ITestSmartPointerInterface*        p03 = 0;
        KTestSmartPointerImplementedClass* p04 = 0;

        p01 = new KTestSmartPointerClass(123);
        TEST_ASSERT(p01->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerClass> ptr(p01);
            TEST_ASSERT(ptr.get() == p01)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p01 = new KTestSmartPointerClass(123);
        TEST_ASSERT(p01->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerClass> ptr(p01);
            TEST_ASSERT(ptr.get() == p01)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerClass> ptr(p02);
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerClass> ptr(p02);
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr(p02);
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr(p02);
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)       

        p03 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p03->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<ITestSmartPointerInterface> ptr(p03);
            TEST_ASSERT(ptr.get() == p03)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p03 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p03->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const ITestSmartPointerInterface> ptr(p03);
            TEST_ASSERT(ptr.get() == p03)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<ITestSmartPointerInterface> ptr(p04);
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const ITestSmartPointerInterface> ptr(p04);
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr(p04);
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptr(p04);
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)


        // Limit cases.
        klab::TSmartPointer<KTestSmartPointerClass> ptr01(0);
        TEST_ASSERT(ptr01.get() == 0)
        TEST_ASSERT(ptr01.isValid() == false)
        TEST_ASSERT(ptr01.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerClass> ptr01c(0);
        TEST_ASSERT(ptr01c.get() == 0)
        TEST_ASSERT(ptr01c.isValid() == false)
        TEST_ASSERT(ptr01c.isNull() == true)

        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr02(0);
        TEST_ASSERT(ptr02.get() == 0)
        TEST_ASSERT(ptr02.isValid() == false)
        TEST_ASSERT(ptr02.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr02c(0);
        TEST_ASSERT(ptr02c.get() == 0)
        TEST_ASSERT(ptr02c.isValid() == false)
        TEST_ASSERT(ptr02c.isNull() == true)

        klab::TSmartPointer<ITestSmartPointerInterface> ptr03(0);
        TEST_ASSERT(ptr03.get() == 0)
        TEST_ASSERT(ptr03.isValid() == false)
        TEST_ASSERT(ptr03.isNull() == true)

        klab::TSmartPointer<const ITestSmartPointerInterface> ptr03c(0);
        TEST_ASSERT(ptr03c.get() == 0)
        TEST_ASSERT(ptr03c.isValid() == false)
        TEST_ASSERT(ptr03c.isNull() == true)

        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr04(0);
        TEST_ASSERT(ptr04.get() == 0)
        TEST_ASSERT(ptr04.isValid() == false)
        TEST_ASSERT(ptr04.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptr04c(0);
        TEST_ASSERT(ptr04c.get() == 0)
        TEST_ASSERT(ptr04c.isValid() == false)
        TEST_ASSERT(ptr04c.isNull() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testCopyConstructor()
{
    try
    {
        KTestSmartPointerClass*            p01 = 0;
        KTestSmartPointerInheritedClass*   p02 = 0;
        ITestSmartPointerInterface*        p03 = 0;
        KTestSmartPointerImplementedClass* p04 = 0;

        p01 = new KTestSmartPointerClass(123);
        TEST_ASSERT(p01->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerClass> ptr(p01);
            TEST_ASSERT(ptr.get() == p01)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 1)

            klab::TSmartPointer<KTestSmartPointerClass> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p01)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p01 = new KTestSmartPointerClass(123);
        TEST_ASSERT(p01->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerClass> ptr(p01);
            TEST_ASSERT(ptr.get() == p01)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 1)

            klab::TSmartPointer<const KTestSmartPointerClass> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p01)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerClass> ptr(p02);
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 1)

            klab::TSmartPointer<KTestSmartPointerClass> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p02)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerClass> ptr(p02);
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 1)

            klab::TSmartPointer<const KTestSmartPointerClass> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p02)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr(p02);
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 1)

            klab::TSmartPointer<KTestSmartPointerInheritedClass> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p02)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 2)

            klab::TSmartPointer<KTestSmartPointerClass> ptrCopy2(ptr);
            TEST_ASSERT(ptrCopy2.get() == p02)
            TEST_ASSERT(ptrCopy2.isValid() == true)
            TEST_ASSERT(ptrCopy2.isNull() == false)
            TEST_ASSERT(ptrCopy2->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 3)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr(p02);
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 1)

            klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p02)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 2)

            klab::TSmartPointer<const KTestSmartPointerClass> ptrCopy2(ptr);
            TEST_ASSERT(ptrCopy2.get() == p02)
            TEST_ASSERT(ptrCopy2.isValid() == true)
            TEST_ASSERT(ptrCopy2.isNull() == false)
            TEST_ASSERT(ptrCopy2->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 3)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)       

        p03 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p03->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<ITestSmartPointerInterface> ptr(p03);
            TEST_ASSERT(ptr.get() == p03)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 1)

            klab::TSmartPointer<ITestSmartPointerInterface> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p03)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p03 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p03->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const ITestSmartPointerInterface> ptr(p03);
            TEST_ASSERT(ptr.get() == p03)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 1)

            klab::TSmartPointer<const ITestSmartPointerInterface> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p03)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<ITestSmartPointerInterface> ptr(p04);
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            klab::TSmartPointer<ITestSmartPointerInterface> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p04)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const ITestSmartPointerInterface> ptr(p04);
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            klab::TSmartPointer<const ITestSmartPointerInterface> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p04)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr(p04);
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            klab::TSmartPointer<KTestSmartPointerImplementedClass> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p04)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 2)

            klab::TSmartPointer<ITestSmartPointerInterface> ptrCopy2(ptr);
            TEST_ASSERT(ptrCopy2.get() == p04)
            TEST_ASSERT(ptrCopy2.isValid() == true)
            TEST_ASSERT(ptrCopy2.isNull() == false)
            TEST_ASSERT(ptrCopy2->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 3)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptr(p04);
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptrCopy(ptr);
            TEST_ASSERT(ptrCopy.get() == p04)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 2)

            klab::TSmartPointer<const ITestSmartPointerInterface> ptrCopy2(ptr);
            TEST_ASSERT(ptrCopy2.get() == p04)
            TEST_ASSERT(ptrCopy2.isValid() == true)
            TEST_ASSERT(ptrCopy2.isNull() == false)
            TEST_ASSERT(ptrCopy2->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 3)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)


        // Limit cases.
        klab::TSmartPointer<KTestSmartPointerClass> ptr;
        TEST_ASSERT(ptr.get() == 0)
        TEST_ASSERT(ptr.isValid() == false)
        TEST_ASSERT(ptr.isNull() == true)

        klab::TSmartPointer<KTestSmartPointerClass> ptrCopy(ptr);
        TEST_ASSERT(ptrCopy.get() == 0)
        TEST_ASSERT(ptrCopy.isValid() == false)
        TEST_ASSERT(ptrCopy.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerClass> ptrc;
        TEST_ASSERT(ptrc.get() == 0)
        TEST_ASSERT(ptrc.isValid() == false)
        TEST_ASSERT(ptrc.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerClass> ptrcCopy(ptrc);
        TEST_ASSERT(ptrcCopy.get() == 0)
        TEST_ASSERT(ptrcCopy.isValid() == false)
        TEST_ASSERT(ptrcCopy.isNull() == true)


        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr2;
        TEST_ASSERT(ptr2.get() == 0)
        TEST_ASSERT(ptr2.isValid() == false)
        TEST_ASSERT(ptr2.isNull() == true)

        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr2Copy(ptr2);
        TEST_ASSERT(ptr2Copy.get() == 0)
        TEST_ASSERT(ptr2Copy.isValid() == false)
        TEST_ASSERT(ptr2Copy.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptrc2;
        TEST_ASSERT(ptrc2.get() == 0)
        TEST_ASSERT(ptrc2.isValid() == false)
        TEST_ASSERT(ptrc2.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptrc2Copy(ptrc2);
        TEST_ASSERT(ptrc2Copy.get() == 0)
        TEST_ASSERT(ptrc2Copy.isValid() == false)
        TEST_ASSERT(ptrc2Copy.isNull() == true)


        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3;
        TEST_ASSERT(ptr3.get() == 0)
        TEST_ASSERT(ptr3.isValid() == false)
        TEST_ASSERT(ptr3.isNull() == true)

        klab::TSmartPointer<KTestSmartPointerClass> ptr3Copy(ptr3);
        TEST_ASSERT(ptr3Copy.get() == 0)
        TEST_ASSERT(ptr3Copy.isValid() == false)
        TEST_ASSERT(ptr3Copy.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptrc3;
        TEST_ASSERT(ptrc3.get() == 0)
        TEST_ASSERT(ptrc3.isValid() == false)
        TEST_ASSERT(ptrc3.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerClass> ptrc3Copy(ptrc3);
        TEST_ASSERT(ptrc3Copy.get() == 0)
        TEST_ASSERT(ptrc3Copy.isValid() == false)
        TEST_ASSERT(ptrc3Copy.isNull() == true)

        
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4;
        TEST_ASSERT(ptr4.get() == 0)
        TEST_ASSERT(ptr4.isValid() == false)
        TEST_ASSERT(ptr4.isNull() == true)

        klab::TSmartPointer<ITestSmartPointerInterface> ptr4Copy(ptr4);
        TEST_ASSERT(ptr4Copy.get() == 0)
        TEST_ASSERT(ptr4Copy.isValid() == false)
        TEST_ASSERT(ptr4Copy.isNull() == true)

        klab::TSmartPointer<const ITestSmartPointerInterface> ptrc4;
        TEST_ASSERT(ptrc4.get() == 0)
        TEST_ASSERT(ptrc4.isValid() == false)
        TEST_ASSERT(ptrc4.isNull() == true)

        klab::TSmartPointer<const ITestSmartPointerInterface> ptrc4Copy(ptrc4);
        TEST_ASSERT(ptrc4Copy.get() == 0)
        TEST_ASSERT(ptrc4Copy.isValid() == false)
        TEST_ASSERT(ptrc4Copy.isNull() == true)


        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5;
        TEST_ASSERT(ptr5.get() == 0)
        TEST_ASSERT(ptr5.isValid() == false)
        TEST_ASSERT(ptr5.isNull() == true)

        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5Copy(ptr5);
        TEST_ASSERT(ptr5Copy.get() == 0)
        TEST_ASSERT(ptr5Copy.isValid() == false)
        TEST_ASSERT(ptr5Copy.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptrc5;
        TEST_ASSERT(ptrc5.get() == 0)
        TEST_ASSERT(ptrc5.isValid() == false)
        TEST_ASSERT(ptrc5.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptrc5Copy(ptrc5);
        TEST_ASSERT(ptrc5Copy.get() == 0)
        TEST_ASSERT(ptrc5Copy.isValid() == false)
        TEST_ASSERT(ptrc5Copy.isNull() == true)


        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr6;
        TEST_ASSERT(ptr6.get() == 0)
        TEST_ASSERT(ptr6.isValid() == false)
        TEST_ASSERT(ptr6.isNull() == true)

        klab::TSmartPointer<ITestSmartPointerInterface> ptr6Copy(ptr6);
        TEST_ASSERT(ptr6Copy.get() == 0)
        TEST_ASSERT(ptr6Copy.isValid() == false)
        TEST_ASSERT(ptr6Copy.isNull() == true)

        klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptrc6;
        TEST_ASSERT(ptrc6.get() == 0)
        TEST_ASSERT(ptrc6.isValid() == false)
        TEST_ASSERT(ptrc6.isNull() == true)

        klab::TSmartPointer<const ITestSmartPointerInterface> ptrc6Copy(ptrc6);
        TEST_ASSERT(ptrc6Copy.get() == 0)
        TEST_ASSERT(ptrc6Copy.isValid() == false)
        TEST_ASSERT(ptrc6Copy.isNull() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testAffectationOperator()
{
    try
    {
        KTestSmartPointerClass*            p01 = 0;
        KTestSmartPointerClass*            p01b= 0;
        KTestSmartPointerInheritedClass*   p02 = 0;
        ITestSmartPointerInterface*        p03 = 0;
        KTestSmartPointerImplementedClass* p04 = 0;

        p01 = new KTestSmartPointerClass(123);
        TEST_ASSERT(p01->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerClass> ptr;
            ptr = p01;
            TEST_ASSERT(ptr.get() == p01)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 1)

            klab::TSmartPointer<KTestSmartPointerClass> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p01)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p01 = new KTestSmartPointerClass(123);
        TEST_ASSERT(p01->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerClass> ptr;
            ptr = p01;
            TEST_ASSERT(ptr.get() == p01)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 1)

            klab::TSmartPointer<const KTestSmartPointerClass> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p01)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerClass> ptr;
            ptr = p02;
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 1)

            klab::TSmartPointer<KTestSmartPointerClass> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p02)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerClass> ptr;
            ptr = p02;
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 1)

            klab::TSmartPointer<const KTestSmartPointerClass> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p02)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr;
            ptr = p02;
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 1)

            klab::TSmartPointer<KTestSmartPointerInheritedClass> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p02)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 2)

            klab::TSmartPointer<KTestSmartPointerClass> ptrCopy2;
            ptrCopy2 = ptr;
            TEST_ASSERT(ptrCopy2.get() == p02)
            TEST_ASSERT(ptrCopy2.isValid() == true)
            TEST_ASSERT(ptrCopy2.isNull() == false)
            TEST_ASSERT(ptrCopy2->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 3)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p02 = new KTestSmartPointerInheritedClass(123);
        TEST_ASSERT(p02->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr;
            ptr = p02;
            TEST_ASSERT(ptr.get() == p02)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 1)

            klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p02)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 246)
            TEST_ASSERT(p02->_countReferences == 2)

            klab::TSmartPointer<const KTestSmartPointerClass> ptrCopy2;
            ptrCopy2 = ptr;
            TEST_ASSERT(ptrCopy2.get() == p02)
            TEST_ASSERT(ptrCopy2.isValid() == true)
            TEST_ASSERT(ptrCopy2.isNull() == false)
            TEST_ASSERT(ptrCopy2->testCode() == 123)
            TEST_ASSERT(p02->_countReferences == 3)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)       

        p03 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p03->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<ITestSmartPointerInterface> ptr;
            ptr = p03;
            TEST_ASSERT(ptr.get() == p03)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 1)

            klab::TSmartPointer<ITestSmartPointerInterface> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p03)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p03 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p03->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const ITestSmartPointerInterface> ptr;
            ptr = p03;
            TEST_ASSERT(ptr.get() == p03)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 1)

            klab::TSmartPointer<const ITestSmartPointerInterface> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p03)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p03->countReferences() == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<ITestSmartPointerInterface> ptr;
            ptr = p04;
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            klab::TSmartPointer<ITestSmartPointerInterface> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p04)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const ITestSmartPointerInterface> ptr;
            ptr = p04;
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            klab::TSmartPointer<const ITestSmartPointerInterface> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p04)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 2)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr;
            ptr = p04;
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            klab::TSmartPointer<KTestSmartPointerImplementedClass> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p04)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 2)

            klab::TSmartPointer<ITestSmartPointerInterface> ptrCopy2;
            ptrCopy2 = ptr;
            TEST_ASSERT(ptrCopy2.get() == p04)
            TEST_ASSERT(ptrCopy2.isValid() == true)
            TEST_ASSERT(ptrCopy2.isNull() == false)
            TEST_ASSERT(ptrCopy2->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 3)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)

        p04 = new KTestSmartPointerImplementedClass(123);
        TEST_ASSERT(p04->countReferences() == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptr;
            ptr = p04;
            TEST_ASSERT(ptr.get() == p04)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 1)

            klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptrCopy;
            ptrCopy = ptr;
            TEST_ASSERT(ptrCopy.get() == p04)
            TEST_ASSERT(ptrCopy.isValid() == true)
            TEST_ASSERT(ptrCopy.isNull() == false)
            TEST_ASSERT(ptrCopy->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 2)

            klab::TSmartPointer<const ITestSmartPointerInterface> ptrCopy2;
            ptrCopy2 = ptr;
            TEST_ASSERT(ptrCopy2.get() == p04)
            TEST_ASSERT(ptrCopy2.isValid() == true)
            TEST_ASSERT(ptrCopy2.isNull() == false)
            TEST_ASSERT(ptrCopy2->testCode() == 123)
            TEST_ASSERT(p04->countReferences() == 3)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)


        p01 = new KTestSmartPointerClass(123);
        p01b = new KTestSmartPointerClass(234);
        TEST_ASSERT(p01->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;
        {
            klab::TSmartPointer<KTestSmartPointerClass> ptr(p01);
            TEST_ASSERT(ptr.get() == p01)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 123)
            TEST_ASSERT(p01->_countReferences == 1)

            klab::TSmartPointer<KTestSmartPointerClass> ptr2(p01b);
            TEST_ASSERT(ptr2.get() == p01b)
            TEST_ASSERT(ptr2.isValid() == true)
            TEST_ASSERT(ptr2.isNull() == false)
            TEST_ASSERT(ptr2->testCode() == 234)
            TEST_ASSERT(p01b->_countReferences == 1)

            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
            ptr = ptr2;
            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)
            TEST_ASSERT(ptr.get() == p01b)
            TEST_ASSERT(ptr.isValid() == true)
            TEST_ASSERT(ptr.isNull() == false)
            TEST_ASSERT(ptr->testCode() == 234)            
            TEST_ASSERT(ptr2.get() == p01b)
            TEST_ASSERT(ptr2.isValid() == true)
            TEST_ASSERT(ptr2.isNull() == false)
            TEST_ASSERT(ptr2->testCode() == 234)
            TEST_ASSERT(p01b->_countReferences == 2)

            ptr = 0;
            TEST_ASSERT(ptr.get() == 0)
            TEST_ASSERT(ptr.isValid() == false)
            TEST_ASSERT(ptr.isNull() == true)           
            TEST_ASSERT(ptr2.get() == p01b)
            TEST_ASSERT(ptr2.isValid() == true)
            TEST_ASSERT(ptr2.isNull() == false)
            TEST_ASSERT(ptr2->testCode() == 234)
            TEST_ASSERT(p01b->_countReferences == 1)

            KSmartPointerUnitTest::IsDeleted = false;
            TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        }
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)


        // Limit cases.
        KSmartPointerUnitTest::IsDeleted = false;

        p01 = new KTestSmartPointerClass(123);
        klab::TSmartPointer<KTestSmartPointerClass> ptr(p01);
        TEST_ASSERT(ptr.get() == p01)
        TEST_ASSERT(ptr.isValid() == true)
        TEST_ASSERT(ptr.isNull() == false)
        TEST_ASSERT(ptr->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 1)

        ptr = p01;
        TEST_ASSERT(ptr.get() == p01)
        TEST_ASSERT(ptr.isValid() == true)
        TEST_ASSERT(ptr.isNull() == false)
        TEST_ASSERT(ptr->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 1)

        ptr = ptr;
        TEST_ASSERT(ptr.get() == p01)
        TEST_ASSERT(ptr.isValid() == true)
        TEST_ASSERT(ptr.isNull() == false)
        TEST_ASSERT(ptr->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 1)


        klab::TSmartPointer<KTestSmartPointerClass> ptr2(p01);
        TEST_ASSERT(ptr2.get() == p01)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 2)

        ptr = ptr2;
        TEST_ASSERT(ptr.get() == p01)
        TEST_ASSERT(ptr.isValid() == true)
        TEST_ASSERT(ptr.isNull() == false)
        TEST_ASSERT(ptr->testCode() == 123)
        TEST_ASSERT(ptr2.get() == p01)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 2)


        ptr = 0;
        TEST_ASSERT(ptr.get() == 0)
        TEST_ASSERT(ptr.isValid() == false)
        TEST_ASSERT(ptr.isNull() == true)
        TEST_ASSERT(ptr2.get() == p01)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 1)

        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        ptr2 = 0;
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)
        TEST_ASSERT(ptr.get() == 0)
        TEST_ASSERT(ptr.isValid() == false)
        TEST_ASSERT(ptr.isNull() == true)
        TEST_ASSERT(ptr2.get() == 0)
        TEST_ASSERT(ptr2.isValid() == false)
        TEST_ASSERT(ptr2.isNull() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testIndirectionOperator()
{
    try
    {
        klab::TSmartPointer<KTestSmartPointerClass> ptr(new KTestSmartPointerClass(123));
        TEST_ASSERT(ptr.get() != 0)
        TEST_ASSERT(ptr.isValid() == true)
        TEST_ASSERT(ptr.isNull() == false)
        TEST_ASSERT(ptr->testCode() == 123)
        TEST_ASSERT((*ptr).testCode() == 123)

        klab::TSmartPointer<const KTestSmartPointerClass> ptrc(new KTestSmartPointerClass(123));
        TEST_ASSERT(ptrc.get() != 0)
        TEST_ASSERT(ptrc.isValid() == true)
        TEST_ASSERT(ptrc.isNull() == false)
        TEST_ASSERT(ptrc->testCode() == 123)
        TEST_ASSERT((*ptrc).testCode() == 123)


        klab::TSmartPointer<KTestSmartPointerClass> ptr2(new KTestSmartPointerInheritedClass(234));
        TEST_ASSERT(ptr2.get() != 0)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT((*ptr2).testCode() == 234)

        klab::TSmartPointer<const KTestSmartPointerClass> ptr2c(new KTestSmartPointerInheritedClass(234));
        TEST_ASSERT(ptr2c.get() != 0)
        TEST_ASSERT(ptr2c.isValid() == true)
        TEST_ASSERT(ptr2c.isNull() == false)
        TEST_ASSERT(ptr2c->testCode() == 234)
        TEST_ASSERT((*ptr2c).testCode() == 234)


        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3(new KTestSmartPointerInheritedClass(345));
        TEST_ASSERT(ptr3.get() != 0)
        TEST_ASSERT(ptr3.isValid() == true)
        TEST_ASSERT(ptr3.isNull() == false)
        TEST_ASSERT(ptr3->testCode() == 690)
        TEST_ASSERT((*ptr3).testCode() == 690)

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr3c(new KTestSmartPointerInheritedClass(345));
        TEST_ASSERT(ptr3c.get() != 0)
        TEST_ASSERT(ptr3c.isValid() == true)
        TEST_ASSERT(ptr3c.isNull() == false)
        TEST_ASSERT(ptr3c->testCode() == 690)
        TEST_ASSERT((*ptr3c).testCode() == 690)


        klab::TSmartPointer<ITestSmartPointerInterface> ptr4(new KTestSmartPointerImplementedClass(456));
        TEST_ASSERT(ptr4.get() != 0)
        TEST_ASSERT(ptr4.isValid() == true)
        TEST_ASSERT(ptr4.isNull() == false)
        TEST_ASSERT(ptr4->testCode() == 456)
        TEST_ASSERT((*ptr4).testCode() == 456)

        klab::TSmartPointer<const ITestSmartPointerInterface> ptr4c(new KTestSmartPointerImplementedClass(456));
        TEST_ASSERT(ptr4c.get() != 0)
        TEST_ASSERT(ptr4c.isValid() == true)
        TEST_ASSERT(ptr4c.isNull() == false)
        TEST_ASSERT(ptr4c->testCode() == 456)
        TEST_ASSERT((*ptr4c).testCode() == 456)


        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5(new KTestSmartPointerImplementedClass(567));
        TEST_ASSERT(ptr5.get() != 0)
        TEST_ASSERT(ptr5.isValid() == true)
        TEST_ASSERT(ptr5.isNull() == false)
        TEST_ASSERT(ptr5->testCode() == 567)
        TEST_ASSERT((*ptr5).testCode() == 567)

        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5c(new KTestSmartPointerImplementedClass(567));
        TEST_ASSERT(ptr5c.get() != 0)
        TEST_ASSERT(ptr5c.isValid() == true)
        TEST_ASSERT(ptr5c.isNull() == false)
        TEST_ASSERT(ptr5c->testCode() == 567)
        TEST_ASSERT((*ptr5c).testCode() == 567)


        // Limit cases.
        klab::TSmartPointer<KTestSmartPointerClass> ptr0;
        TEST_ASSERT(ptr0.get() == 0)
        TEST_ASSERT(ptr0.isValid() == false)
        TEST_ASSERT(ptr0.isNull() == true)

        try                             {ptr0->testCode(); TEST_ASSERT(false)}
        catch(KNullPointerException&)   {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        try                             {(*ptr0).testCode(); TEST_ASSERT(false)}
        catch(KNullPointerException&)   {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}


        klab::TSmartPointer<const KTestSmartPointerClass> ptr0c;
        TEST_ASSERT(ptr0c.get() == 0)
        TEST_ASSERT(ptr0c.isValid() == false)
        TEST_ASSERT(ptr0c.isNull() == true)

        try                             {ptr0c->testCode(); TEST_ASSERT(false)}
        catch(KNullPointerException&)   {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        try                             {(*ptr0c).testCode(); TEST_ASSERT(false)}
        catch(KNullPointerException&)   {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testEqualOperator()
{
    try
    {
        KTestSmartPointerClass*            p01 = new KTestSmartPointerClass(123);
        KTestSmartPointerClass*            p02 = new KTestSmartPointerInheritedClass(234);
        KTestSmartPointerInheritedClass*   p03 = new KTestSmartPointerInheritedClass(345);
        ITestSmartPointerInterface*        p04 = new KTestSmartPointerImplementedClass(456);
        KTestSmartPointerImplementedClass* p05 = new KTestSmartPointerImplementedClass(567);


        klab::TSmartPointer<KTestSmartPointerClass> ptr1(p01);
        klab::TSmartPointer<KTestSmartPointerClass> ptr1b(ptr1);
        klab::TSmartPointer<KTestSmartPointerClass> ptr2(p02);
        klab::TSmartPointer<KTestSmartPointerClass> ptr2b(ptr2);
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3(p03);
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3b(ptr3);
        klab::TSmartPointer<KTestSmartPointerClass> ptr3c(ptr3);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4(p04);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4b(ptr4);
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5(p05);
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5b(ptr5);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr5c(ptr5);

        klab::TSmartPointer<KTestSmartPointerClass> ptr0a;
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr0b;
        klab::TSmartPointer<ITestSmartPointerInterface> ptr0c;
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr0d;


        TEST_ASSERT(ptr1==ptr1b && ptr1b==ptr1) 
        TEST_ASSERT(ptr2==ptr2b && ptr2b==ptr2)
        TEST_ASSERT(ptr3==ptr3b && ptr3b==ptr3)
        TEST_ASSERT(ptr3==ptr3c && ptr3c==ptr3)
        TEST_ASSERT(ptr3b==ptr3c && ptr3c==ptr3b)
        TEST_ASSERT(ptr4==ptr4b && ptr4b==ptr4)
        TEST_ASSERT(ptr5==ptr5b && ptr5b==ptr5)
        TEST_ASSERT(ptr5==ptr5c && ptr5c==ptr5)
        TEST_ASSERT(ptr5b==ptr5c && ptr5c==ptr5b)

        TEST_ASSERT((ptr1==ptr2)==false && (ptr2==ptr1)==false) 
        TEST_ASSERT((ptr1==ptr3)==false && (ptr3==ptr1)==false)       
        TEST_ASSERT((ptr2==ptr3)==false && (ptr3==ptr2)==false)
        TEST_ASSERT((ptr4==ptr5)==false && (ptr5==ptr4)==false)

        TEST_ASSERT(ptr0a==ptr0b && ptr0b==ptr0a) 
        TEST_ASSERT(ptr0c==ptr0d && ptr0d==ptr0c)

        TEST_ASSERT((ptr1==ptr0a)==false && (ptr0a==ptr1)==false)
        TEST_ASSERT((ptr2==ptr0a)==false && (ptr0a==ptr2)==false)
        TEST_ASSERT((ptr1==ptr0b)==false && (ptr0b==ptr1)==false)
        TEST_ASSERT((ptr2==ptr0b)==false && (ptr0b==ptr2)==false)
        TEST_ASSERT((ptr4==ptr0c)==false && (ptr0c==ptr4)==false)
        TEST_ASSERT((ptr5==ptr0c)==false && (ptr0c==ptr5)==false)
        TEST_ASSERT((ptr4==ptr0d)==false && (ptr0d==ptr4)==false)
        TEST_ASSERT((ptr5==ptr0d)==false && (ptr0d==ptr5)==false)


        TEST_ASSERT(ptr1==p01 && p01==ptr1) 
        TEST_ASSERT(ptr2==p02 && p02==ptr2)
        TEST_ASSERT(ptr3==p03 && p03==ptr3)
        TEST_ASSERT(ptr4==p04 && p04==ptr4)
        TEST_ASSERT(ptr5==p05 && p05==ptr5)

        TEST_ASSERT((ptr1==p02)==false && (p02==ptr1)==false) 
        TEST_ASSERT((ptr1==p03)==false && (p03==ptr1)==false)      
        TEST_ASSERT((ptr2==p01)==false && (p01==ptr2)==false)         
        TEST_ASSERT((ptr2==p03)==false && (p03==ptr2)==false)
        TEST_ASSERT((ptr3==p01)==false && (p01==ptr3)==false)         
        TEST_ASSERT((ptr3==p02)==false && (p02==ptr3)==false)
        TEST_ASSERT((ptr4==p05)==false && (p05==ptr4)==false)
        TEST_ASSERT((ptr5==p04)==false && (p04==ptr5)==false)

        TEST_ASSERT((ptr1==0) == false)
        TEST_ASSERT((ptr2==0) == false)
        TEST_ASSERT((ptr3==0) == false)
        TEST_ASSERT((ptr4==0) == false)
        TEST_ASSERT((ptr5==0) == false)

        TEST_ASSERT(ptr0a == 0)
        TEST_ASSERT(ptr0b == 0)
        TEST_ASSERT(ptr0c == 0)
        TEST_ASSERT(ptr0d == 0)

        TEST_ASSERT((ptr1==ptr0a)==false && (ptr0a==ptr1)==false)
        TEST_ASSERT((ptr2==ptr0a)==false && (ptr0a==ptr2)==false)
        TEST_ASSERT((ptr1==ptr0b)==false && (ptr0b==ptr1)==false)
        TEST_ASSERT((ptr2==ptr0b)==false && (ptr0b==ptr2)==false)
        TEST_ASSERT((ptr4==ptr0c)==false && (ptr0c==ptr4)==false)
        TEST_ASSERT((ptr5==ptr0c)==false && (ptr0c==ptr5)==false)
        TEST_ASSERT((ptr4==ptr0d)==false && (ptr0d==ptr4)==false)
        TEST_ASSERT((ptr5==ptr0d)==false && (ptr0d==ptr5)==false)


        // Limit cases.
        TEST_ASSERT(ptr1 == ptr1)
        TEST_ASSERT(ptr1b == ptr1b)
        TEST_ASSERT(ptr2 == ptr2)
        TEST_ASSERT(ptr2b == ptr2b)
        TEST_ASSERT(ptr3 == ptr3)
        TEST_ASSERT(ptr3b == ptr3b)
        TEST_ASSERT(ptr3c == ptr3c)
        TEST_ASSERT(ptr4 == ptr4)
        TEST_ASSERT(ptr4b == ptr4b)
        TEST_ASSERT(ptr5 == ptr5)
        TEST_ASSERT(ptr5b == ptr5b)
        TEST_ASSERT(ptr5c == ptr5c)

        TEST_ASSERT(ptr0a == ptr0a)
        TEST_ASSERT(ptr0b == ptr0b)
        TEST_ASSERT(ptr0c == ptr0c)
        TEST_ASSERT(ptr0d == ptr0d)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testNotEqualOperator()
{
    try
    {
        KTestSmartPointerClass*            p01 = new KTestSmartPointerClass(123);
        KTestSmartPointerClass*            p02 = new KTestSmartPointerInheritedClass(234);
        KTestSmartPointerInheritedClass*   p03 = new KTestSmartPointerInheritedClass(345);
        ITestSmartPointerInterface*        p04 = new KTestSmartPointerImplementedClass(456);
        KTestSmartPointerImplementedClass* p05 = new KTestSmartPointerImplementedClass(567);


        klab::TSmartPointer<KTestSmartPointerClass> ptr1(p01);
        klab::TSmartPointer<KTestSmartPointerClass> ptr1b(ptr1);
        klab::TSmartPointer<KTestSmartPointerClass> ptr2(p02);
        klab::TSmartPointer<KTestSmartPointerClass> ptr2b(ptr2);
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3(p03);
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3b(ptr3);
        klab::TSmartPointer<KTestSmartPointerClass> ptr3c(ptr3);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4(p04);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4b(ptr4);
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5(p05);
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5b(ptr5);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr5c(ptr5);

        klab::TSmartPointer<KTestSmartPointerClass> ptr0a;
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr0b;
        klab::TSmartPointer<ITestSmartPointerInterface> ptr0c;
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr0d;


        TEST_ASSERT((ptr1!=ptr1b)==false && (ptr1b!=ptr1)==false) 
        TEST_ASSERT((ptr2!=ptr2b)==false && (ptr2b!=ptr2)==false)
        TEST_ASSERT((ptr3!=ptr3b)==false && (ptr3b!=ptr3)==false)
        TEST_ASSERT((ptr3!=ptr3c)==false && (ptr3c!=ptr3)==false)
        TEST_ASSERT((ptr3b!=ptr3c)==false && (ptr3c!=ptr3b)==false)
        TEST_ASSERT((ptr4!=ptr4b)==false && (ptr4b!=ptr4)==false)
        TEST_ASSERT((ptr5!=ptr5b)==false && (ptr5b!=ptr5)==false)
        TEST_ASSERT((ptr5!=ptr5c)==false && (ptr5c!=ptr5)==false)
        TEST_ASSERT((ptr5b!=ptr5c)==false && (ptr5c!=ptr5b)==false)

        TEST_ASSERT(ptr1!=ptr2 && ptr2!=ptr1) 
        TEST_ASSERT(ptr1!=ptr3 && ptr3!=ptr1)       
        TEST_ASSERT(ptr2!=ptr3 && ptr3!=ptr2)
        TEST_ASSERT(ptr4!=ptr5 && ptr5!=ptr4)

        TEST_ASSERT((ptr0a!=ptr0b)==false && (ptr0b!=ptr0a)==false) 
        TEST_ASSERT((ptr0c!=ptr0d)==false && (ptr0d!=ptr0c)==false)

        TEST_ASSERT(ptr1!=ptr0a && ptr0a!=ptr1)
        TEST_ASSERT(ptr2!=ptr0a && ptr0a!=ptr2)
        TEST_ASSERT(ptr1!=ptr0b && ptr0b!=ptr1)
        TEST_ASSERT(ptr2!=ptr0b && ptr0b!=ptr2)
        TEST_ASSERT(ptr4!=ptr0c && ptr0c!=ptr4)
        TEST_ASSERT(ptr5!=ptr0c && ptr0c!=ptr5)
        TEST_ASSERT(ptr4!=ptr0d && ptr0d!=ptr4)
        TEST_ASSERT(ptr5!=ptr0d && ptr0d!=ptr5)


        TEST_ASSERT((ptr1!=p01)==false && (p01!=ptr1)==false) 
        TEST_ASSERT((ptr2!=p02)==false && (p02!=ptr2)==false)
        TEST_ASSERT((ptr3!=p03)==false && (p03!=ptr3)==false)
        TEST_ASSERT((ptr4!=p04)==false && (p04!=ptr4)==false)
        TEST_ASSERT((ptr5!=p05)==false && (p05!=ptr5)==false)

        TEST_ASSERT(ptr1!=p02 && p02!=ptr1) 
        TEST_ASSERT(ptr1!=p03 && p03!=ptr1)      
        TEST_ASSERT(ptr2!=p01 && p01!=ptr2)         
        TEST_ASSERT(ptr2!=p03 && p03!=ptr2)
        TEST_ASSERT(ptr3!=p01 && p01!=ptr3)         
        TEST_ASSERT(ptr3!=p02 && p02!=ptr3)
        TEST_ASSERT(ptr4!=p05 && p05!=ptr4)
        TEST_ASSERT(ptr5!=p04 && p04!=ptr5)

        TEST_ASSERT(ptr1 != 0)
        TEST_ASSERT(ptr2 != 0)
        TEST_ASSERT(ptr3 != 0)
        TEST_ASSERT(ptr4 != 0)
        TEST_ASSERT(ptr5 != 0)

        TEST_ASSERT((ptr0a!=0)==false)
        TEST_ASSERT((ptr0b!=0)==false)
        TEST_ASSERT((ptr0c!=0)==false)
        TEST_ASSERT((ptr0d!=0)==false)

        TEST_ASSERT(ptr1!=ptr0a && ptr0a!=ptr1)
        TEST_ASSERT(ptr2!=ptr0a && ptr0a!=ptr2)
        TEST_ASSERT(ptr1!=ptr0b && ptr0b!=ptr1)
        TEST_ASSERT(ptr2!=ptr0b && ptr0b!=ptr2)
        TEST_ASSERT(ptr4!=ptr0c && ptr0c!=ptr4)
        TEST_ASSERT(ptr5!=ptr0c && ptr0c!=ptr5)
        TEST_ASSERT(ptr4!=ptr0d && ptr0d!=ptr4)
        TEST_ASSERT(ptr5!=ptr0d && ptr0d!=ptr5)


        // Limit cases.
        TEST_ASSERT((ptr1!=ptr1)==false)
        TEST_ASSERT((ptr1b!=ptr1b)==false)
        TEST_ASSERT((ptr2!=ptr2)==false)
        TEST_ASSERT((ptr2b!=ptr2b)==false)
        TEST_ASSERT((ptr3!=ptr3)==false)
        TEST_ASSERT((ptr3b!=ptr3b)==false)
        TEST_ASSERT((ptr3c!=ptr3c)==false)
        TEST_ASSERT((ptr4!=ptr4)==false)
        TEST_ASSERT((ptr4b!=ptr4b)==false)
        TEST_ASSERT((ptr5!=ptr5)==false)
        TEST_ASSERT((ptr5b!=ptr5b)==false)
        TEST_ASSERT((ptr5c!=ptr5c)==false)

        TEST_ASSERT((ptr0a!=ptr0a)==false)
        TEST_ASSERT((ptr0b!=ptr0b)==false)
        TEST_ASSERT((ptr0c!=ptr0c)==false)
        TEST_ASSERT((ptr0d!=ptr0d)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testLessThanOperator()
{
    try
    {
        KTestSmartPointerClass*            p01 = new KTestSmartPointerClass(123);
        KTestSmartPointerClass*            p02 = new KTestSmartPointerInheritedClass(234);
        KTestSmartPointerInheritedClass*   p03 = new KTestSmartPointerInheritedClass(345);
        ITestSmartPointerInterface*        p04 = new KTestSmartPointerImplementedClass(456);
        KTestSmartPointerImplementedClass* p05 = new KTestSmartPointerImplementedClass(567);

        klab::TSmartPointer<KTestSmartPointerClass> ptr1(p01);
        klab::TSmartPointer<KTestSmartPointerClass> ptr1b(ptr1);
        klab::TSmartPointer<KTestSmartPointerClass> ptr2(p02);
        klab::TSmartPointer<KTestSmartPointerClass> ptr2b(ptr2);
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3(p03);
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3b(ptr3);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4(p04);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4b(ptr4);
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5(p05);
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5b(ptr5);


        TEST_ASSERT((ptr1<ptr1b)==false && (ptr1b<ptr1)==false)
        TEST_ASSERT((ptr2<ptr2b)==false && (ptr2b<ptr2)==false)
        TEST_ASSERT(((ptr1<ptr2)==false && ptr2<ptr1) || (ptr1<ptr2 && (ptr2<ptr1)==false))
        TEST_ASSERT((ptr3<ptr3b)==false && (ptr3b<ptr3)==false)
        TEST_ASSERT((ptr4<ptr4b)==false && (ptr4b<ptr4)==false)
        TEST_ASSERT((ptr5<ptr5b)==false && (ptr5b<ptr5)==false)


        // Limit cases.
        TEST_ASSERT((ptr1<ptr1)==false)
        TEST_ASSERT((ptr1b<ptr1b)==false)
        TEST_ASSERT((ptr2<ptr2)==false)
        TEST_ASSERT((ptr2b<ptr2b)==false)
        TEST_ASSERT((ptr3<ptr3)==false)
        TEST_ASSERT((ptr3b<ptr3b)==false)
        TEST_ASSERT((ptr4<ptr4)==false)
        TEST_ASSERT((ptr4b<ptr4b)==false)
        TEST_ASSERT((ptr5<ptr5)==false)
        TEST_ASSERT((ptr5b<ptr5b)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testGet()
{
    try
    {
        klab::TSmartPointer<KTestSmartPointerClass> ptr;
        TEST_ASSERT(ptr.get() == 0)
        TEST_ASSERT(ptr.isValid() == false)
        TEST_ASSERT(ptr.isNull() == true)

        ptr = new KTestSmartPointerClass(123);
        TEST_ASSERT(ptr.get() != 0)
        TEST_ASSERT(ptr.isValid() == true)
        TEST_ASSERT(ptr.isNull() == false)
        TEST_ASSERT(ptr->testCode() == 123)
        TEST_ASSERT((*ptr).testCode() == 123)

        klab::TSmartPointer<const KTestSmartPointerClass> ptrc;
        TEST_ASSERT(ptrc.get() == 0)
        TEST_ASSERT(ptrc.isValid() == false)
        TEST_ASSERT(ptrc.isNull() == true)

        ptrc = new KTestSmartPointerClass(123);
        TEST_ASSERT(ptrc.get() != 0)
        TEST_ASSERT(ptrc.isValid() == true)
        TEST_ASSERT(ptrc.isNull() == false)
        TEST_ASSERT(ptrc->testCode() == 123)
        TEST_ASSERT((*ptrc).testCode() == 123)


        klab::TSmartPointer<KTestSmartPointerClass> ptr2;
        TEST_ASSERT(ptr2.get() == 0)
        TEST_ASSERT(ptr2.isValid() == false)
        TEST_ASSERT(ptr2.isNull() == true)

        ptr2 = new KTestSmartPointerInheritedClass(234);
        TEST_ASSERT(ptr2.get() != 0)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT((*ptr2).testCode() == 234)

        klab::TSmartPointer<const KTestSmartPointerClass> ptr2c;
        TEST_ASSERT(ptr2c.get() == 0)
        TEST_ASSERT(ptr2c.isValid() == false)
        TEST_ASSERT(ptr2c.isNull() == true)

        ptr2c = new KTestSmartPointerInheritedClass(234);
        TEST_ASSERT(ptr2c.get() != 0)
        TEST_ASSERT(ptr2c.isValid() == true)
        TEST_ASSERT(ptr2c.isNull() == false)
        TEST_ASSERT(ptr2c->testCode() == 234)
        TEST_ASSERT((*ptr2c).testCode() == 234)


        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3;
        TEST_ASSERT(ptr3.get() == 0)
        TEST_ASSERT(ptr3.isValid() == false)
        TEST_ASSERT(ptr3.isNull() == true)

        ptr3 = new KTestSmartPointerInheritedClass(345);
        TEST_ASSERT(ptr3.get() != 0)
        TEST_ASSERT(ptr3.isValid() == true)
        TEST_ASSERT(ptr3.isNull() == false)
        TEST_ASSERT(ptr3->testCode() == 690)
        TEST_ASSERT((*ptr3).testCode() == 690)

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr3c;
        TEST_ASSERT(ptr3c.get() == 0)
        TEST_ASSERT(ptr3c.isValid() == false)
        TEST_ASSERT(ptr3c.isNull() == true)

        ptr3c = new KTestSmartPointerInheritedClass(345);
        TEST_ASSERT(ptr3c.get() != 0)
        TEST_ASSERT(ptr3c.isValid() == true)
        TEST_ASSERT(ptr3c.isNull() == false)
        TEST_ASSERT(ptr3c->testCode() == 690)
        TEST_ASSERT((*ptr3c).testCode() == 690)


        klab::TSmartPointer<ITestSmartPointerInterface> ptr4;
        TEST_ASSERT(ptr4.get() == 0)
        TEST_ASSERT(ptr4.isValid() == false)
        TEST_ASSERT(ptr4.isNull() == true)

        ptr4 = new KTestSmartPointerImplementedClass(456);
        TEST_ASSERT(ptr4.get() != 0)
        TEST_ASSERT(ptr4.isValid() == true)
        TEST_ASSERT(ptr4.isNull() == false)
        TEST_ASSERT(ptr4->testCode() == 456)
        TEST_ASSERT((*ptr4).testCode() == 456)

        klab::TSmartPointer<const ITestSmartPointerInterface> ptr4c;
        TEST_ASSERT(ptr4c.get() == 0)
        TEST_ASSERT(ptr4c.isValid() == false)
        TEST_ASSERT(ptr4c.isNull() == true)

        ptr4c = new KTestSmartPointerImplementedClass(456);
        TEST_ASSERT(ptr4c.get() != 0)
        TEST_ASSERT(ptr4c.isValid() == true)
        TEST_ASSERT(ptr4c.isNull() == false)
        TEST_ASSERT(ptr4c->testCode() == 456)
        TEST_ASSERT((*ptr4c).testCode() == 456)


        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5;
        TEST_ASSERT(ptr5.get() == 0)
        TEST_ASSERT(ptr5.isValid() == false)
        TEST_ASSERT(ptr5.isNull() == true)

        ptr5 = new KTestSmartPointerImplementedClass(567);
        TEST_ASSERT(ptr5.get() != 0)
        TEST_ASSERT(ptr5.isValid() == true)
        TEST_ASSERT(ptr5.isNull() == false)
        TEST_ASSERT(ptr5->testCode() == 567)
        TEST_ASSERT((*ptr5).testCode() == 567)

        klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptr5c;
        TEST_ASSERT(ptr5c.get() == 0)
        TEST_ASSERT(ptr5c.isValid() == false)
        TEST_ASSERT(ptr5c.isNull() == true)

        ptr5c = new KTestSmartPointerImplementedClass(567);
        TEST_ASSERT(ptr5c.get() != 0)
        TEST_ASSERT(ptr5c.isValid() == true)
        TEST_ASSERT(ptr5c.isNull() == false)
        TEST_ASSERT(ptr5c->testCode() == 567)
        TEST_ASSERT((*ptr5c).testCode() == 567)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testIsValid()
{
    try
    {
        klab::TSmartPointer<KTestSmartPointerClass> ptr;
        TEST_ASSERT(ptr.get() == 0)
        TEST_ASSERT(ptr.isValid() == false)
        TEST_ASSERT(ptr.isNull() == true)

        ptr = new KTestSmartPointerClass(123);
        TEST_ASSERT(ptr.get() != 0)
        TEST_ASSERT(ptr.isValid() == true)
        TEST_ASSERT(ptr.isNull() == false)
        TEST_ASSERT(ptr->testCode() == 123)
        TEST_ASSERT((*ptr).testCode() == 123)

        klab::TSmartPointer<const KTestSmartPointerClass> ptrc;
        TEST_ASSERT(ptrc.get() == 0)
        TEST_ASSERT(ptrc.isValid() == false)
        TEST_ASSERT(ptrc.isNull() == true)

        ptrc = new KTestSmartPointerClass(123);
        TEST_ASSERT(ptrc.get() != 0)
        TEST_ASSERT(ptrc.isValid() == true)
        TEST_ASSERT(ptrc.isNull() == false)
        TEST_ASSERT(ptrc->testCode() == 123)
        TEST_ASSERT((*ptrc).testCode() == 123)


        klab::TSmartPointer<KTestSmartPointerClass> ptr2;
        TEST_ASSERT(ptr2.get() == 0)
        TEST_ASSERT(ptr2.isValid() == false)
        TEST_ASSERT(ptr2.isNull() == true)

        ptr2 = new KTestSmartPointerInheritedClass(234);
        TEST_ASSERT(ptr2.get() != 0)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT((*ptr2).testCode() == 234)

        klab::TSmartPointer<const KTestSmartPointerClass> ptr2c;
        TEST_ASSERT(ptr2c.get() == 0)
        TEST_ASSERT(ptr2c.isValid() == false)
        TEST_ASSERT(ptr2c.isNull() == true)

        ptr2c = new KTestSmartPointerInheritedClass(234);
        TEST_ASSERT(ptr2c.get() != 0)
        TEST_ASSERT(ptr2c.isValid() == true)
        TEST_ASSERT(ptr2c.isNull() == false)
        TEST_ASSERT(ptr2c->testCode() == 234)
        TEST_ASSERT((*ptr2c).testCode() == 234)


        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3;
        TEST_ASSERT(ptr3.get() == 0)
        TEST_ASSERT(ptr3.isValid() == false)
        TEST_ASSERT(ptr3.isNull() == true)

        ptr3 = new KTestSmartPointerInheritedClass(345);
        TEST_ASSERT(ptr3.get() != 0)
        TEST_ASSERT(ptr3.isValid() == true)
        TEST_ASSERT(ptr3.isNull() == false)
        TEST_ASSERT(ptr3->testCode() == 690)
        TEST_ASSERT((*ptr3).testCode() == 690)

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr3c;
        TEST_ASSERT(ptr3c.get() == 0)
        TEST_ASSERT(ptr3c.isValid() == false)
        TEST_ASSERT(ptr3c.isNull() == true)

        ptr3c = new KTestSmartPointerInheritedClass(345);
        TEST_ASSERT(ptr3c.get() != 0)
        TEST_ASSERT(ptr3c.isValid() == true)
        TEST_ASSERT(ptr3c.isNull() == false)
        TEST_ASSERT(ptr3c->testCode() == 690)
        TEST_ASSERT((*ptr3c).testCode() == 690)


        klab::TSmartPointer<ITestSmartPointerInterface> ptr4;
        TEST_ASSERT(ptr4.get() == 0)
        TEST_ASSERT(ptr4.isValid() == false)
        TEST_ASSERT(ptr4.isNull() == true)

        ptr4 = new KTestSmartPointerImplementedClass(456);
        TEST_ASSERT(ptr4.get() != 0)
        TEST_ASSERT(ptr4.isValid() == true)
        TEST_ASSERT(ptr4.isNull() == false)
        TEST_ASSERT(ptr4->testCode() == 456)
        TEST_ASSERT((*ptr4).testCode() == 456)

        klab::TSmartPointer<const ITestSmartPointerInterface> ptr4c;
        TEST_ASSERT(ptr4c.get() == 0)
        TEST_ASSERT(ptr4c.isValid() == false)
        TEST_ASSERT(ptr4c.isNull() == true)

        ptr4c = new KTestSmartPointerImplementedClass(456);
        TEST_ASSERT(ptr4c.get() != 0)
        TEST_ASSERT(ptr4c.isValid() == true)
        TEST_ASSERT(ptr4c.isNull() == false)
        TEST_ASSERT(ptr4c->testCode() == 456)
        TEST_ASSERT((*ptr4c).testCode() == 456)


        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5;
        TEST_ASSERT(ptr5.get() == 0)
        TEST_ASSERT(ptr5.isValid() == false)
        TEST_ASSERT(ptr5.isNull() == true)

        ptr5 = new KTestSmartPointerImplementedClass(567);
        TEST_ASSERT(ptr5.get() != 0)
        TEST_ASSERT(ptr5.isValid() == true)
        TEST_ASSERT(ptr5.isNull() == false)
        TEST_ASSERT(ptr5->testCode() == 567)
        TEST_ASSERT((*ptr5).testCode() == 567)

        klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptr5c;
        TEST_ASSERT(ptr5c.get() == 0)
        TEST_ASSERT(ptr5c.isValid() == false)
        TEST_ASSERT(ptr5c.isNull() == true)

        ptr5c = new KTestSmartPointerImplementedClass(567);
        TEST_ASSERT(ptr5c.get() != 0)
        TEST_ASSERT(ptr5c.isValid() == true)
        TEST_ASSERT(ptr5c.isNull() == false)
        TEST_ASSERT(ptr5c->testCode() == 567)
        TEST_ASSERT((*ptr5c).testCode() == 567)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testIsNull()
{
    try
    {
        klab::TSmartPointer<KTestSmartPointerClass> ptr;
        TEST_ASSERT(ptr.get() == 0)
        TEST_ASSERT(ptr.isValid() == false)
        TEST_ASSERT(ptr.isNull() == true)

        ptr = new KTestSmartPointerClass(123);
        TEST_ASSERT(ptr.get() != 0)
        TEST_ASSERT(ptr.isValid() == true)
        TEST_ASSERT(ptr.isNull() == false)
        TEST_ASSERT(ptr->testCode() == 123)
        TEST_ASSERT((*ptr).testCode() == 123)

        klab::TSmartPointer<const KTestSmartPointerClass> ptrc;
        TEST_ASSERT(ptrc.get() == 0)
        TEST_ASSERT(ptrc.isValid() == false)
        TEST_ASSERT(ptrc.isNull() == true)

        ptrc = new KTestSmartPointerClass(123);
        TEST_ASSERT(ptrc.get() != 0)
        TEST_ASSERT(ptrc.isValid() == true)
        TEST_ASSERT(ptrc.isNull() == false)
        TEST_ASSERT(ptrc->testCode() == 123)
        TEST_ASSERT((*ptrc).testCode() == 123)


        klab::TSmartPointer<KTestSmartPointerClass> ptr2;
        TEST_ASSERT(ptr2.get() == 0)
        TEST_ASSERT(ptr2.isValid() == false)
        TEST_ASSERT(ptr2.isNull() == true)

        ptr2 = new KTestSmartPointerInheritedClass(234);
        TEST_ASSERT(ptr2.get() != 0)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT((*ptr2).testCode() == 234)

        klab::TSmartPointer<const KTestSmartPointerClass> ptr2c;
        TEST_ASSERT(ptr2c.get() == 0)
        TEST_ASSERT(ptr2c.isValid() == false)
        TEST_ASSERT(ptr2c.isNull() == true)

        ptr2c = new KTestSmartPointerInheritedClass(234);
        TEST_ASSERT(ptr2c.get() != 0)
        TEST_ASSERT(ptr2c.isValid() == true)
        TEST_ASSERT(ptr2c.isNull() == false)
        TEST_ASSERT(ptr2c->testCode() == 234)
        TEST_ASSERT((*ptr2c).testCode() == 234)


        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3;
        TEST_ASSERT(ptr3.get() == 0)
        TEST_ASSERT(ptr3.isValid() == false)
        TEST_ASSERT(ptr3.isNull() == true)

        ptr3 = new KTestSmartPointerInheritedClass(345);
        TEST_ASSERT(ptr3.get() != 0)
        TEST_ASSERT(ptr3.isValid() == true)
        TEST_ASSERT(ptr3.isNull() == false)
        TEST_ASSERT(ptr3->testCode() == 690)
        TEST_ASSERT((*ptr3).testCode() == 690)

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr3c;
        TEST_ASSERT(ptr3c.get() == 0)
        TEST_ASSERT(ptr3c.isValid() == false)
        TEST_ASSERT(ptr3c.isNull() == true)

        ptr3c = new KTestSmartPointerInheritedClass(345);
        TEST_ASSERT(ptr3c.get() != 0)
        TEST_ASSERT(ptr3c.isValid() == true)
        TEST_ASSERT(ptr3c.isNull() == false)
        TEST_ASSERT(ptr3c->testCode() == 690)
        TEST_ASSERT((*ptr3c).testCode() == 690)


        klab::TSmartPointer<ITestSmartPointerInterface> ptr4;
        TEST_ASSERT(ptr4.get() == 0)
        TEST_ASSERT(ptr4.isValid() == false)
        TEST_ASSERT(ptr4.isNull() == true)

        ptr4 = new KTestSmartPointerImplementedClass(456);
        TEST_ASSERT(ptr4.get() != 0)
        TEST_ASSERT(ptr4.isValid() == true)
        TEST_ASSERT(ptr4.isNull() == false)
        TEST_ASSERT(ptr4->testCode() == 456)
        TEST_ASSERT((*ptr4).testCode() == 456)

        klab::TSmartPointer<const ITestSmartPointerInterface> ptr4c;
        TEST_ASSERT(ptr4c.get() == 0)
        TEST_ASSERT(ptr4c.isValid() == false)
        TEST_ASSERT(ptr4c.isNull() == true)

        ptr4c = new KTestSmartPointerImplementedClass(456);
        TEST_ASSERT(ptr4c.get() != 0)
        TEST_ASSERT(ptr4c.isValid() == true)
        TEST_ASSERT(ptr4c.isNull() == false)
        TEST_ASSERT(ptr4c->testCode() == 456)
        TEST_ASSERT((*ptr4c).testCode() == 456)


        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5;
        TEST_ASSERT(ptr5.get() == 0)
        TEST_ASSERT(ptr5.isValid() == false)
        TEST_ASSERT(ptr5.isNull() == true)

        ptr5 = new KTestSmartPointerImplementedClass(567);
        TEST_ASSERT(ptr5.get() != 0)
        TEST_ASSERT(ptr5.isValid() == true)
        TEST_ASSERT(ptr5.isNull() == false)
        TEST_ASSERT(ptr5->testCode() == 567)
        TEST_ASSERT((*ptr5).testCode() == 567)

        klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptr5c;
        TEST_ASSERT(ptr5c.get() == 0)
        TEST_ASSERT(ptr5c.isValid() == false)
        TEST_ASSERT(ptr5c.isNull() == true)

        ptr5c = new KTestSmartPointerImplementedClass(567);
        TEST_ASSERT(ptr5c.get() != 0)
        TEST_ASSERT(ptr5c.isValid() == true)
        TEST_ASSERT(ptr5c.isNull() == false)
        TEST_ASSERT(ptr5c->testCode() == 567)
        TEST_ASSERT((*ptr5c).testCode() == 567)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testReset()
{
    try
    {
        KTestSmartPointerClass* p01 = 0;


        p01 = new KTestSmartPointerClass(123);
        TEST_ASSERT(p01->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;

        klab::TSmartPointer<KTestSmartPointerClass> ptr(p01);
        TEST_ASSERT(ptr.get() == p01)
        TEST_ASSERT(ptr.isValid() == true)
        TEST_ASSERT(ptr.isNull() == false)
        TEST_ASSERT(ptr->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 1)

        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        ptr.reset();
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)
        TEST_ASSERT(ptr.get() == 0)
        TEST_ASSERT(ptr.isValid() == false)
        TEST_ASSERT(ptr.isNull() == true)


        p01 = new KTestSmartPointerClass(123);
        TEST_ASSERT(p01->_countReferences == 0)
        KSmartPointerUnitTest::IsDeleted = false;

        klab::TSmartPointer<const KTestSmartPointerClass> ptrc(p01);
        TEST_ASSERT(ptrc.get() == p01)
        TEST_ASSERT(ptrc.isValid() == true)
        TEST_ASSERT(ptrc.isNull() == false)
        TEST_ASSERT(ptrc->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 1)

        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == false)
        ptrc.reset();
        TEST_ASSERT(KSmartPointerUnitTest::IsDeleted == true)
        TEST_ASSERT(ptrc.get() == 0)
        TEST_ASSERT(ptrc.isValid() == false)
        TEST_ASSERT(ptrc.isNull() == true)


        // Limit cases.
        klab::TSmartPointer<KTestSmartPointerClass> ptr0;
        TEST_ASSERT(ptr0.get() == 0)
        TEST_ASSERT(ptr0.isValid() == false)
        TEST_ASSERT(ptr0.isNull() == true)

        ptr0.reset();
        TEST_ASSERT(ptr0.get() == 0)
        TEST_ASSERT(ptr0.isValid() == false)
        TEST_ASSERT(ptr0.isNull() == true)


        klab::TSmartPointer<const KTestSmartPointerClass> ptr0c;
        TEST_ASSERT(ptr0c.get() == 0)
        TEST_ASSERT(ptr0c.isValid() == false)
        TEST_ASSERT(ptr0c.isNull() == true)

        ptrc.reset();
        TEST_ASSERT(ptr0c.get() == 0)
        TEST_ASSERT(ptr0c.isValid() == false)
        TEST_ASSERT(ptr0c.isNull() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testSwap()
{
    try
    {
        KTestSmartPointerClass* p01 = new KTestSmartPointerClass(123);
        KTestSmartPointerClass* p02 = new KTestSmartPointerClass(234);

        klab::TSmartPointer<KTestSmartPointerClass> ptr1(p01);
        TEST_ASSERT(ptr1.get() == p01)
        TEST_ASSERT(ptr1.isValid() == true)
        TEST_ASSERT(ptr1.isNull() == false)
        TEST_ASSERT(ptr1->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 1)

        klab::TSmartPointer<KTestSmartPointerClass> ptr2(p02);
        TEST_ASSERT(ptr2.get() == p02)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT(p02->_countReferences == 1)

        ptr1.swap(ptr2);
        TEST_ASSERT(ptr1.get() == p02)
        TEST_ASSERT(ptr1.isValid() == true)
        TEST_ASSERT(ptr1.isNull() == false)
        TEST_ASSERT(ptr1->testCode() == 234)
        TEST_ASSERT(ptr2.get() == p01)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 1)
        TEST_ASSERT(p02->_countReferences == 1)

        ptr2.swap(ptr1);
        TEST_ASSERT(ptr1.get() == p01)
        TEST_ASSERT(ptr1.isValid() == true)
        TEST_ASSERT(ptr1.isNull() == false)
        TEST_ASSERT(ptr1->testCode() == 123)
        TEST_ASSERT(ptr2.get() == p02)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT(p01->_countReferences == 1)
        TEST_ASSERT(p02->_countReferences == 1)


        // Limit cases
        ptr1.swap(ptr1);
        TEST_ASSERT(ptr1.get() == p01)
        TEST_ASSERT(ptr1.isValid() == true)
        TEST_ASSERT(ptr1.isNull() == false)
        TEST_ASSERT(ptr1->testCode() == 123)
        TEST_ASSERT(ptr2.get() == p02)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT(p01->_countReferences == 1)
        TEST_ASSERT(p02->_countReferences == 1)

        ptr2.swap(ptr2);
        TEST_ASSERT(ptr1.get() == p01)
        TEST_ASSERT(ptr1.isValid() == true)
        TEST_ASSERT(ptr1.isNull() == false)
        TEST_ASSERT(ptr1->testCode() == 123)
        TEST_ASSERT(ptr2.get() == p02)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT(p01->_countReferences == 1)
        TEST_ASSERT(p02->_countReferences == 1)


        klab::TSmartPointer<KTestSmartPointerClass> ptr3(p01);
        TEST_ASSERT(ptr1.get() == p01)
        TEST_ASSERT(ptr1.isValid() == true)
        TEST_ASSERT(ptr1.isNull() == false)
        TEST_ASSERT(ptr1->testCode() == 123)
        TEST_ASSERT(ptr2.get() == p02)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT(ptr3.get() == p01)
        TEST_ASSERT(ptr3.isValid() == true)
        TEST_ASSERT(ptr3.isNull() == false)
        TEST_ASSERT(ptr3->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 2)
        TEST_ASSERT(p02->_countReferences == 1)

        ptr1.swap(ptr3);
        TEST_ASSERT(ptr1.get() == p01)
        TEST_ASSERT(ptr1.isValid() == true)
        TEST_ASSERT(ptr1.isNull() == false)
        TEST_ASSERT(ptr1->testCode() == 123)
        TEST_ASSERT(ptr2.get() == p02)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT(ptr3.get() == p01)
        TEST_ASSERT(ptr3.isValid() == true)
        TEST_ASSERT(ptr3.isNull() == false)
        TEST_ASSERT(ptr3->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 2)
        TEST_ASSERT(p02->_countReferences == 1)

        klab::TSmartPointer<KTestSmartPointerClass> ptr0;
        ptr1.swap(ptr0);
        TEST_ASSERT(ptr0.get() == p01)
        TEST_ASSERT(ptr0.isValid() == true)
        TEST_ASSERT(ptr0.isNull() == false)
        TEST_ASSERT(ptr1.get() == 0)
        TEST_ASSERT(ptr1.isValid() == false)
        TEST_ASSERT(ptr1.isNull() == true)
        TEST_ASSERT(ptr2.get() == p02)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT(ptr3.get() == p01)
        TEST_ASSERT(ptr3.isValid() == true)
        TEST_ASSERT(ptr3.isNull() == false)
        TEST_ASSERT(ptr3->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 2)
        TEST_ASSERT(p02->_countReferences == 1)

        ptr1.swap(ptr0);
        TEST_ASSERT(ptr0.get() == 0)
        TEST_ASSERT(ptr0.isValid() == false)
        TEST_ASSERT(ptr0.isNull() == true)
        TEST_ASSERT(ptr1.get() == p01)
        TEST_ASSERT(ptr1.isValid() == true)
        TEST_ASSERT(ptr1.isNull() == false)
        TEST_ASSERT(ptr2.get() == p02)
        TEST_ASSERT(ptr2.isValid() == true)
        TEST_ASSERT(ptr2.isNull() == false)
        TEST_ASSERT(ptr2->testCode() == 234)
        TEST_ASSERT(ptr3.get() == p01)
        TEST_ASSERT(ptr3.isValid() == true)
        TEST_ASSERT(ptr3.isNull() == false)
        TEST_ASSERT(ptr3->testCode() == 123)
        TEST_ASSERT(p01->_countReferences == 2)
        TEST_ASSERT(p02->_countReferences == 1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testStatic_pointer_cast()
{
    try
    {
        KTestSmartPointerClass*            p01 = new KTestSmartPointerClass(123);
        KTestSmartPointerClass*            p02 = new KTestSmartPointerInheritedClass(234);
        KTestSmartPointerInheritedClass*   p03 = new KTestSmartPointerInheritedClass(345);
        ITestSmartPointerInterface*        p04 = new KTestSmartPointerImplementedClass(456);
        KTestSmartPointerImplementedClass* p05 = new KTestSmartPointerImplementedClass(567);

        klab::TSmartPointer<KTestSmartPointerClass> ptr1(p01);
        klab::TSmartPointer<KTestSmartPointerClass> ptr2(p02);
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3(p03);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4(p04);
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5(p05);


        klab::TSmartPointer<KTestSmartPointerClass> ptr01 = klab::static_pointer_cast<KTestSmartPointerClass, KTestSmartPointerInheritedClass>(ptr3);
        TEST_ASSERT(ptr01.get()!=0 && ptr01.get()==ptr3.get() && (ptr01->testCode()<<1)==ptr3->testCode())

        klab::TSmartPointer<ITestSmartPointerInterface> ptr02 = klab::static_pointer_cast<ITestSmartPointerInterface, KTestSmartPointerImplementedClass>(ptr5);
        TEST_ASSERT(ptr02.get()!=0 && ptr02.get()==ptr5.get() && ptr02->testCode()==ptr5->testCode())


        // Limit cases.
        klab::TSmartPointer<KTestSmartPointerClass> ptr0a = klab::static_pointer_cast<KTestSmartPointerClass, KTestSmartPointerClass>(ptr1);
        TEST_ASSERT(ptr0a.get()!=0 && ptr0a.get()==ptr1.get())

        klab::TSmartPointer<KTestSmartPointerClass> ptr0b = klab::static_pointer_cast<KTestSmartPointerClass, KTestSmartPointerClass>(ptr2);
        TEST_ASSERT(ptr0b.get()!=0 && ptr0b.get()==ptr2.get())

        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr0c = klab::static_pointer_cast<KTestSmartPointerInheritedClass, KTestSmartPointerInheritedClass>(ptr3);
        TEST_ASSERT(ptr0c.get()!=0 && ptr0c.get()==ptr3.get())

        klab::TSmartPointer<ITestSmartPointerInterface> ptr0d = klab::static_pointer_cast<ITestSmartPointerInterface, ITestSmartPointerInterface>(ptr4);
        TEST_ASSERT(ptr0d.get()!=0 && ptr0d.get()==ptr4.get())

        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr0e = klab::static_pointer_cast<KTestSmartPointerImplementedClass, KTestSmartPointerImplementedClass>(ptr5);
        TEST_ASSERT(ptr0e.get()!=0 && ptr0e.get()==ptr5.get())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testConst_pointer_cast()
{
    try
    {
        KTestSmartPointerClass*            p01 = new KTestSmartPointerClass(123);
        KTestSmartPointerClass*            p02 = new KTestSmartPointerInheritedClass(234);
        KTestSmartPointerInheritedClass*   p03 = new KTestSmartPointerInheritedClass(345);
        ITestSmartPointerInterface*        p04 = new KTestSmartPointerImplementedClass(456);
        KTestSmartPointerImplementedClass* p05 = new KTestSmartPointerImplementedClass(567);

        klab::TSmartPointer<KTestSmartPointerClass> ptr1(p01);
        klab::TSmartPointer<KTestSmartPointerClass> ptr2(p02);
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3(p03);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4(p04);
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5(p05);


        klab::TSmartPointer<const KTestSmartPointerClass> ptr0a = klab::const_pointer_cast<const KTestSmartPointerClass, KTestSmartPointerClass>(ptr1);
        TEST_ASSERT(ptr0a.get()!=0 && ptr0a.get()==ptr1.get())

        klab::TSmartPointer<const KTestSmartPointerClass> ptr0b = klab::const_pointer_cast<const KTestSmartPointerClass, KTestSmartPointerClass>(ptr2);
        TEST_ASSERT(ptr0b.get()!=0 && ptr0b.get()==ptr2.get())

        klab::TSmartPointer<const KTestSmartPointerInheritedClass> ptr0c = klab::const_pointer_cast<const KTestSmartPointerInheritedClass, KTestSmartPointerInheritedClass>(ptr3);
        TEST_ASSERT(ptr0c.get()!=0 && ptr0c.get()==ptr3.get())

        klab::TSmartPointer<const ITestSmartPointerInterface> ptr0d = klab::const_pointer_cast<const ITestSmartPointerInterface, ITestSmartPointerInterface>(ptr4);
        TEST_ASSERT(ptr0d.get()!=0 && ptr0d.get()==ptr4.get())

        klab::TSmartPointer<const KTestSmartPointerImplementedClass> ptr0e = klab::const_pointer_cast<const KTestSmartPointerImplementedClass, KTestSmartPointerImplementedClass>(ptr5);
        TEST_ASSERT(ptr0e.get()!=0 && ptr0e.get()==ptr5.get())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testDynamic_pointer_cast()
{
    try
    {
        KTestSmartPointerClass*            p01 = new KTestSmartPointerClass(123);
        KTestSmartPointerClass*            p02 = new KTestSmartPointerInheritedClass(234);
        KTestSmartPointerInheritedClass*   p03 = new KTestSmartPointerInheritedClass(345);
        ITestSmartPointerInterface*        p04 = new KTestSmartPointerImplementedClass(456);
        KTestSmartPointerImplementedClass* p05 = new KTestSmartPointerImplementedClass(567);

        klab::TSmartPointer<KTestSmartPointerClass> ptr1(p01);
        klab::TSmartPointer<KTestSmartPointerClass> ptr2(p02);
        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr3(p03);
        klab::TSmartPointer<ITestSmartPointerInterface> ptr4(p04);
        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr5(p05);


        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr01 = klab::dynamic_pointer_cast<KTestSmartPointerInheritedClass, KTestSmartPointerClass>(ptr2);
        TEST_ASSERT(ptr01.get()!=0 && ptr01.get()==ptr2.get() && ptr01->testCode()==(ptr2->testCode()<<1))

        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr02 = klab::dynamic_pointer_cast<KTestSmartPointerImplementedClass, ITestSmartPointerInterface>(ptr4);
        TEST_ASSERT(ptr02.get()!=0 && ptr02.get()==ptr4.get() && ptr02->testCode()==ptr4->testCode())


        // Limit cases.
        klab::TSmartPointer<KTestSmartPointerClass> ptr0a = klab::dynamic_pointer_cast<KTestSmartPointerClass, KTestSmartPointerClass>(ptr1);
        TEST_ASSERT(ptr0a.get()!=0 && ptr0a.get()==ptr1.get())

        klab::TSmartPointer<KTestSmartPointerClass> ptr0b = klab::dynamic_pointer_cast<KTestSmartPointerClass, KTestSmartPointerClass>(ptr2);
        TEST_ASSERT(ptr0b.get()!=0 && ptr0b.get()==ptr2.get())

        klab::TSmartPointer<KTestSmartPointerInheritedClass> ptr0c = klab::dynamic_pointer_cast<KTestSmartPointerInheritedClass, KTestSmartPointerInheritedClass>(ptr3);
        TEST_ASSERT(ptr0c.get()!=0 && ptr0c.get()==ptr3.get())

        klab::TSmartPointer<ITestSmartPointerInterface> ptr0d = klab::dynamic_pointer_cast<ITestSmartPointerInterface, ITestSmartPointerInterface>(ptr4);
        TEST_ASSERT(ptr0d.get()!=0 && ptr0d.get()==ptr4.get())

        klab::TSmartPointer<KTestSmartPointerImplementedClass> ptr0e = klab::dynamic_pointer_cast<KTestSmartPointerImplementedClass, KTestSmartPointerImplementedClass>(ptr5);
        TEST_ASSERT(ptr0e.get()!=0 && ptr0e.get()==ptr5.get())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSmartPointerUnitTest::testCheckedDelete()
{
    try
    {
        KTestSmartPointerClass*            p01 = new KTestSmartPointerClass(123);
        KTestSmartPointerClass*            p02 = new KTestSmartPointerInheritedClass(234);
        KTestSmartPointerInheritedClass*   p03 = new KTestSmartPointerInheritedClass(345);
        ITestSmartPointerInterface*        p04 = new KTestSmartPointerImplementedClass(456);
        KTestSmartPointerImplementedClass* p05 = new KTestSmartPointerImplementedClass(567);


        klab::CheckedDelete(p01);
        TEST_ASSERT(true)

        klab::CheckedDelete(p02);
        TEST_ASSERT(true)

        klab::CheckedDelete(p03);
        TEST_ASSERT(true)

        klab::CheckedDelete(p04);
        TEST_ASSERT(true)

        klab::CheckedDelete(p05);        
        TEST_ASSERT(true)


        // Limit cases.
        klab::CheckedDelete<KTestSmartPointerClass>(0);    
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerClass::KTestSmartPointerClass() : 
_testCode(0), _countReferences()
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerClass::KTestSmartPointerClass(klab::UInt32 testCode) : 
_testCode(testCode), _countReferences()
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerClass::KTestSmartPointerClass(const KTestSmartPointerClass& obj) : 
_testCode(obj._testCode), _countReferences()
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerClass::~KTestSmartPointerClass()
{
    KSmartPointerUnitTest::IsDeleted = true;
}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerClass& KTestSmartPointerClass::operator=(const KTestSmartPointerClass& obj)
{
    if(this != &obj)
    {
        _testCode = obj._testCode;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

void KTestSmartPointerClass::setTestCode(klab::UInt32 testCode)
{
    _testCode = testCode;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KTestSmartPointerClass::testCode() const
{
    return _testCode;
}

// ---------------------------------------------------------------------------------------------------- //

void    klab::AddSmartPointerReference(const KTestSmartPointerClass* ptr)
{
    if(ptr != 0)
        ++(ptr->_countReferences);
}

// ---------------------------------------------------------------------------------------------------- //

void    klab::ReleaseSmartPointerReference(const KTestSmartPointerClass* ptr)
{
    if(ptr != 0)
    {
        if(--(ptr->_countReferences) == 0)
            klab::CheckedDelete(ptr);
    }
}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerInheritedClass::KTestSmartPointerInheritedClass() : KTestSmartPointerClass()
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerInheritedClass::KTestSmartPointerInheritedClass(klab::UInt32 testCode) : KTestSmartPointerClass(testCode)
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerInheritedClass::KTestSmartPointerInheritedClass(const KTestSmartPointerInheritedClass& obj) : KTestSmartPointerClass(obj)
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerInheritedClass::~KTestSmartPointerInheritedClass()
{
    KSmartPointerUnitTest::IsDeleted = true;
}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerInheritedClass& KTestSmartPointerInheritedClass::operator=(const KTestSmartPointerInheritedClass& obj)
{
    if(this != &obj)
    {
        KTestSmartPointerClass::operator=(obj);
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KTestSmartPointerInheritedClass::testCode() const
{
    return (KTestSmartPointerClass::testCode()<<1);
}

// ---------------------------------------------------------------------------------------------------- //

ITestSmartPointerInterface::~ITestSmartPointerInterface()
{}

// ---------------------------------------------------------------------------------------------------- //

void    klab::AddSmartPointerReference(const ITestSmartPointerInterface* ptr)
{
    if(ptr != 0)
        const_cast<ITestSmartPointerInterface*>(ptr)->incrementReferencesCount();
}

// ---------------------------------------------------------------------------------------------------- //

void    klab::ReleaseSmartPointerReference(const ITestSmartPointerInterface* ptr)
{
    if(ptr != 0)
    {
        if(const_cast<ITestSmartPointerInterface*>(ptr)->decrementReferencesCount() == 0)
            klab::CheckedDelete(ptr);
    }
}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerImplementedClass::KTestSmartPointerImplementedClass() : ITestSmartPointerInterface(),
_testCode(0), _countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerImplementedClass::KTestSmartPointerImplementedClass(klab::UInt32 testCode) : ITestSmartPointerInterface(),
_testCode(testCode), _countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerImplementedClass::KTestSmartPointerImplementedClass(const KTestSmartPointerImplementedClass& obj) : ITestSmartPointerInterface(),
_testCode(obj._testCode), _countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerImplementedClass::~KTestSmartPointerImplementedClass()
{
    KSmartPointerUnitTest::IsDeleted = true;
}

// ---------------------------------------------------------------------------------------------------- //

KTestSmartPointerImplementedClass& KTestSmartPointerImplementedClass::operator=(const KTestSmartPointerImplementedClass& obj)
{
    if(this != &obj)
    {
        _testCode = obj._testCode;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

void KTestSmartPointerImplementedClass::setTestCode(klab::UInt32 testCode)
{
    _testCode = testCode;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KTestSmartPointerImplementedClass::testCode() const
{
    return _testCode;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KTestSmartPointerImplementedClass::countReferences() const
{
    return _countReferences;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KTestSmartPointerImplementedClass::incrementReferencesCount()
{
    return (++_countReferences);
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KTestSmartPointerImplementedClass::decrementReferencesCount()
{
    return (--_countReferences);
}

// ---------------------------------------------------------------------------------------------------- //
