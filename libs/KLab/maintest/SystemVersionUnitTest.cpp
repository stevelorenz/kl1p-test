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

#include "SystemVersionUnitTest.h"
#include "../include/SystemVersion.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KSystemVersionUnitTest::KSystemVersionUnitTest() : Test::Suite()
{
    TEST_ADD(KSystemVersionUnitTest::testConstructor)
    TEST_ADD(KSystemVersionUnitTest::testCopyConstructor)
    TEST_ADD(KSystemVersionUnitTest::testAffectationOperator)
    
    TEST_ADD(KSystemVersionUnitTest::testCode)
    TEST_ADD(KSystemVersionUnitTest::testVersion)
    TEST_ADD(KSystemVersionUnitTest::testSubVersion)
    TEST_ADD(KSystemVersionUnitTest::testIsMSWindows)
    TEST_ADD(KSystemVersionUnitTest::testIsUnix)
    TEST_ADD(KSystemVersionUnitTest::testIsMacOS)
    TEST_ADD(KSystemVersionUnitTest::testIs16Bits)
    TEST_ADD(KSystemVersionUnitTest::testIs32Bits)
    TEST_ADD(KSystemVersionUnitTest::testIs64Bits)
    TEST_ADD(KSystemVersionUnitTest::testName)
    TEST_ADD(KSystemVersionUnitTest::testFullName)
}

// ---------------------------------------------------------------------------------------------------- //

KSystemVersionUnitTest::~KSystemVersionUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testConstructor()
{
    try
    {
        TSystemVersion<> version1;
        TEST_ASSERT(version1.code() > 0)
        TEST_ASSERT(version1.is16Bits() || version1.is32Bits() || version1.is64Bits())
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version1.isMSWindows() && version1.isUnix()==false && version1.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version1.isMSWindows()==false && version1.isUnix() && version1.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version1.isMSWindows()==false && version1.isUnix()==false && version1.isMacOS())
#else
        TEST_ASSERT(version1.isMSWindows()==false && version1.isUnix()==false && version1.isMacOS()==false)
#endif

        KSystemVersion version2;
        TEST_ASSERT(version2.code() > 0)
        TEST_ASSERT(version2.is16Bits() || version2.is32Bits() || version2.is64Bits())
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version2.isMSWindows() && version2.isUnix()==false && version2.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version2.isMSWindows()==false && version2.isUnix() && version2.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version2.isMSWindows()==false && version2.isUnix()==false && version2.isMacOS())
#else
        TEST_ASSERT(version2.isMSWindows()==false && version2.isUnix()==false && version2.isMacOS()==false)
#endif
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testCopyConstructor()
{
    try
    {
        TSystemVersion<> version1;        
        TEST_ASSERT(version1.code() > 0)
        TEST_ASSERT(version1.is16Bits() || version1.is32Bits() || version1.is64Bits())
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version1.isMSWindows() && version1.isUnix()==false && version1.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version1.isMSWindows()==false && version1.isUnix() && version1.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version1.isMSWindows()==false && version1.isUnix()==false && version1.isMacOS())
#else
        TEST_ASSERT(version1.isMSWindows()==false && version1.isUnix()==false && version1.isMacOS()==false)
#endif

        TSystemVersion<> version1_copy(version1);
        TEST_ASSERT(version1_copy.code() > 0)
        TEST_ASSERT(version1_copy.is16Bits()==version1.is16Bits() && version1_copy.is32Bits()==version1.is32Bits() && version1_copy.is64Bits()==version1.is64Bits())
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version1_copy.isMSWindows() && version1_copy.isUnix()==false && version1_copy.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version1_copy.isMSWindows()==false && version1_copy.isUnix() && version1_copy.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version1_copy.isMSWindows()==false && version1_copy.isUnix()==false && version1_copy.isMacOS())
#else
        TEST_ASSERT(version1_copy.isMSWindows()==false && version1_copy.isUnix()==false && version1_copy.isMacOS()==false)
#endif


        KSystemVersion version2;
        TEST_ASSERT(version2.code() > 0)
        TEST_ASSERT(version2.is16Bits() || version2.is32Bits() || version2.is64Bits())
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version2.isMSWindows() && version2.isUnix()==false && version2.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version2.isMSWindows()==false && version2.isUnix() && version2.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version2.isMSWindows()==false && version2.isUnix()==false && version2.isMacOS())
#else
        TEST_ASSERT(version2.isMSWindows()==false && version2.isUnix()==false && version2.isMacOS()==false)
#endif


        KSystemVersion version2_copy(version2);
        TEST_ASSERT(version2_copy.code() > 0)
        TEST_ASSERT(version2_copy.is16Bits()==version2.is16Bits() || version2_copy.is32Bits()==version2.is32Bits() || version2_copy.is64Bits()==version2.is64Bits())       
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version2_copy.isMSWindows() && version2_copy.isUnix()==false && version2_copy.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version2_copy.isMSWindows()==false && version2_copy.isUnix() && version2_copy.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version2_copy.isMSWindows()==false && version2_copy.isUnix()==false && version2_copy.isMacOS())
#else
        TEST_ASSERT(version2_copy.isMSWindows()==false && version2_copy.isUnix()==false && version2_copy.isMacOS()==false)
#endif
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testAffectationOperator()
{
    try
    {
        TSystemVersion<> version1;        
        TEST_ASSERT(version1.code() > 0)
        TEST_ASSERT(version1.is16Bits() || version1.is32Bits() || version1.is64Bits())
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version1.isMSWindows() && version1.isUnix()==false && version1.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version1.isMSWindows()==false && version1.isUnix() && version1.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version1.isMSWindows()==false && version1.isUnix()==false && version1.isMacOS())
#else
        TEST_ASSERT(version1.isMSWindows()==false && version1.isUnix()==false && version1.isMacOS()==false)
#endif

        TSystemVersion<> version1_copy;
        version1_copy = version1;
        TEST_ASSERT(version1_copy.code() > 0)
        TEST_ASSERT(version1_copy.is16Bits()==version1.is16Bits() && version1_copy.is32Bits()==version1.is32Bits() && version1_copy.is64Bits()==version1.is64Bits())
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version1_copy.isMSWindows() && version1_copy.isUnix()==false && version1_copy.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version1_copy.isMSWindows()==false && version1_copy.isUnix() && version1_copy.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version1_copy.isMSWindows()==false && version1_copy.isUnix()==false && version1_copy.isMacOS())
#else
        TEST_ASSERT(version1_copy.isMSWindows()==false && version1_copy.isUnix()==false && version1_copy.isMacOS()==false)
#endif


        KSystemVersion version2;
        TEST_ASSERT(version2.code() > 0)
        TEST_ASSERT(version2.is16Bits() || version2.is32Bits() || version2.is64Bits())
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version2.isMSWindows() && version2.isUnix()==false && version2.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version2.isMSWindows()==false && version2.isUnix() && version2.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version2.isMSWindows()==false && version2.isUnix()==false && version2.isMacOS())
#else
        TEST_ASSERT(version2.isMSWindows()==false && version2.isUnix()==false && version2.isMacOS()==false)
#endif


        KSystemVersion version2_copy;
        version2_copy = version2;
        TEST_ASSERT(version2_copy.code() > 0)
        TEST_ASSERT(version2_copy.is16Bits()==version2.is16Bits() || version2_copy.is32Bits()==version2.is32Bits() || version2_copy.is64Bits()==version2.is64Bits()) 
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version2_copy.isMSWindows() && version2_copy.isUnix()==false && version2_copy.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version2_copy.isMSWindows()==false && version2_copy.isUnix() && version2_copy.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version2_copy.isMSWindows()==false && version2_copy.isUnix()==false && version2_copy.isMacOS())
#else
        TEST_ASSERT(version2_copy.isMSWindows()==false && version2_copy.isUnix()==false && version2_copy.isMacOS()==false)
#endif
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testCode()
{
    try
    {
        KSystemVersion version;        
        TEST_ASSERT(version.code() > 0)
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT((version.code() & KLAB_OPERATINGSYSTEMTYPE_MASK) == KLAB_MSWINDOWS_OSTYPE)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT((version.code() & KLAB_OPERATINGSYSTEMTYPE_MASK) == KLAB_UNIX_OSTYPE)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT((version.code() & KLAB_OPERATINGSYSTEMTYPE_MASK) == KLAB_MACOS_OSTYPE)
#else
        TEST_ASSERT((version.code() & KLAB_OPERATINGSYSTEMTYPE_MASK) == KLAB_UNKNOWN_OSTYPE)
#endif
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testVersion()
{
    try
    {
        KSystemVersion version;        
        TEST_ASSERT(version.code() > 0)
        TEST_ASSERT(version.version() > 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testSubVersion()
{
    try
    {
        KSystemVersion version;        
        TEST_ASSERT(version.code() > 0)
        TEST_ASSERT(version.subVersion() >= 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testIsMSWindows()
{
    try
    {
        KSystemVersion version;
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version.isMSWindows() && version.isUnix()==false && version.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version.isMSWindows()==false && version.isUnix() && version.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version.isMSWindows()==false && version.isUnix()==false && version.isMacOS())
#else
        TEST_ASSERT(version.isMSWindows()==false && version.isUnix()==false && version.isMacOS()==false)
#endif
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testIsUnix()
{
    try
    {
        KSystemVersion version;
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version.isMSWindows() && version.isUnix()==false && version.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version.isMSWindows()==false && version.isUnix() && version.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version.isMSWindows()==false && version.isUnix()==false && version.isMacOS())
#else
        TEST_ASSERT(version.isMSWindows()==false && version.isUnix()==false && version.isMacOS()==false)
#endif
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testIsMacOS()
{
    try
    {
        KSystemVersion version;
#if defined(KLAB_MSWINDOWS_SYSTEM)
        TEST_ASSERT(version.isMSWindows() && version.isUnix()==false && version.isMacOS()==false)
#elif defined(KLAB_UNIX_SYSTEM)
        TEST_ASSERT(version.isMSWindows()==false && version.isUnix() && version.isMacOS()==false)
#elif defined(KLAB_MACOS_SYSTEM)
        TEST_ASSERT(version.isMSWindows()==false && version.isUnix()==false && version.isMacOS())
#else
        TEST_ASSERT(version.isMSWindows()==false && version.isUnix()==false && version.isMacOS()==false)
#endif
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testIs16Bits()
{
    try
    {
        KSystemVersion version;
        TEST_ASSERT((version.is16Bits() && version.is32Bits()==false && version.is64Bits()==false) || (version.is16Bits()==false && version.is32Bits() && version.is64Bits()==false) || (version.is16Bits()==false && version.is32Bits()==false && version.is64Bits()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testIs32Bits()
{
    try
    {
        KSystemVersion version;
        TEST_ASSERT((version.is16Bits() && version.is32Bits()==false && version.is64Bits()==false) || (version.is16Bits()==false && version.is32Bits() && version.is64Bits()==false) || (version.is16Bits()==false && version.is32Bits()==false && version.is64Bits()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testIs64Bits()
{
    try
    {
        KSystemVersion version;
        TEST_ASSERT((version.is16Bits() && version.is32Bits()==false && version.is64Bits()==false) || (version.is16Bits()==false && version.is32Bits() && version.is64Bits()==false) || (version.is16Bits()==false && version.is32Bits()==false && version.is64Bits()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testName()
{
    try
    {
        KSystemVersion version;
        TEST_ASSERT(version.name().length() > 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemVersionUnitTest::testFullName()
{
    try
    {
        KSystemVersion version;
        TEST_ASSERT(version.fullName().length() > 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
