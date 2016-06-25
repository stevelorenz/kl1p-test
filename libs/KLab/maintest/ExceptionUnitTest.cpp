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

#include "ExceptionUnitTest.h"
#include "../include/Exception.h"
#include <cstring>

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KExceptionUnitTest::KExceptionUnitTest() : Test::Suite()
{
    TEST_ADD(KExceptionUnitTest::testDefaultConstructor)
    TEST_ADD(KExceptionUnitTest::testErrorCodeMessageFileLineFunctionConstructor)
    TEST_ADD(KExceptionUnitTest::testCopyConstructor)
    TEST_ADD(KExceptionUnitTest::testAffectationOperator)

    TEST_ADD(KExceptionUnitTest::testErrorCode)
    TEST_ADD(KExceptionUnitTest::testWhat)
    TEST_ADD(KExceptionUnitTest::testFile)
    TEST_ADD(KExceptionUnitTest::testLine)
    TEST_ADD(KExceptionUnitTest::testFunction)

    TEST_ADD(KExceptionUnitTest::testThrowExceptionIf)
    TEST_ADD(KExceptionUnitTest::testThrowExceptionIfNot)
    TEST_ADD(KExceptionUnitTest::testThrowException)
    TEST_ADD(KExceptionUnitTest::testThrowTraceExceptionIf)
    TEST_ADD(KExceptionUnitTest::testThrowTraceExceptionIfNot)
    TEST_ADD(KExceptionUnitTest::testThrowTraceException)
    TEST_ADD(KExceptionUnitTest::testFormatExceptionToString)
}

// ---------------------------------------------------------------------------------------------------- //

KExceptionUnitTest::~KExceptionUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testDefaultConstructor()
{
    try
    {
        try
        {
            throw KException();
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == 0)
            TEST_ASSERT(strcmp(e.what(), "") == 0)
            TEST_ASSERT(strcmp(e.file(), "") == 0)
            TEST_ASSERT(e.line() == 0)
            TEST_ASSERT(strcmp(e.function(), "") == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testErrorCodeMessageFileLineFunctionConstructor()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            throw KException(errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testCopyConstructor()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            KException e1(errorCode1, what1, file1, line1, function1);
            KException e2(e1);

            TEST_ASSERT(e2.errorCode()==errorCode1 && e1.errorCode()==e2.errorCode())
            TEST_ASSERT(strcmp(e2.what(), what1)==0 && strcmp(e1.what(), e2.what())==0)
            TEST_ASSERT(strcmp(e2.file(), file1)==0 && strcmp(e1.file(), e2.file())==0)
            TEST_ASSERT(e2.line()==line1 && e1.line()==e2.line())
            TEST_ASSERT(strcmp(e2.function(), function1)==0 && strcmp(e1.function(), e2.function())==0)

            throw e2;
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testAffectationOperator()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            KException e1(errorCode1, what1, file1, line1, function1);
            KException e2;            
            e2 = e1;

            TEST_ASSERT(e2.errorCode()==errorCode1 && e1.errorCode()==e2.errorCode())
            TEST_ASSERT(strcmp(e2.what(), what1)==0 && strcmp(e1.what(), e2.what())==0)
            TEST_ASSERT(strcmp(e2.file(), file1)==0 && strcmp(e1.file(), e2.file())==0)
            TEST_ASSERT(e2.line()==line1 && e1.line()==e2.line())
            TEST_ASSERT(strcmp(e2.function(), function1)==0 && strcmp(e1.function(), e2.function())==0)

            throw e2;
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testErrorCode()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            KException e(errorCode1); 

            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), "") == 0)
            TEST_ASSERT(strcmp(e.file(), "") == 0 )
            TEST_ASSERT(e.line() == 0)
            TEST_ASSERT(strcmp(e.function(), "") == 0)

            throw e;
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), "") == 0)
            TEST_ASSERT(strcmp(e.file(), "") == 0)
            TEST_ASSERT(e.line() == 0)
            TEST_ASSERT(strcmp(e.function(), "") == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testWhat()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            KException e(errorCode1, what1); 

            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), "") == 0 )
            TEST_ASSERT(e.line() == 0)
            TEST_ASSERT(strcmp(e.function(), "") == 0)

            throw e;
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), "") == 0)
            TEST_ASSERT(e.line() == 0)
            TEST_ASSERT(strcmp(e.function(), "") == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testFile()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            KException e(errorCode1, what1, file1); 

            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0 )
            TEST_ASSERT(e.line() == 0)
            TEST_ASSERT(strcmp(e.function(), "") == 0)

            throw e;
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == 0)
            TEST_ASSERT(strcmp(e.function(), "") == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testLine()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            KException e(errorCode1, what1, file1, line1); 

            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0 )
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), "") == 0)

            throw e;
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), "") == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testFunction()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            KException e(errorCode1, what1, file1, line1, function1); 

            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0 )
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)

            throw e;
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testThrowExceptionIf()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            ThrowExceptionIf(true, errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowExceptionIf(false, errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(true);
        }
        catch(KException&)
        {
            TEST_ASSERT(false)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowExceptionIf<KBadArithmeticException>(true, errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(false)
        }
        catch(KBadArithmeticException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowExceptionIf<KBadArithmeticException>(false, errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(true);
        }
        catch(KBadArithmeticException&)
        {
            TEST_ASSERT(false)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testThrowExceptionIfNot()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            ThrowExceptionIfNot(false, errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowExceptionIfNot(true, errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(true);
        }
        catch(KException&)
        {
            TEST_ASSERT(false)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowExceptionIfNot<KBadArithmeticException>(false, errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(false)
        }
        catch(KBadArithmeticException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowExceptionIfNot<KBadArithmeticException>(true, errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(true);
        }
        catch(KBadArithmeticException&)
        {
            TEST_ASSERT(false)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testThrowException()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            ThrowException(errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowException<KBadArithmeticException>(errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(false)
        }
        catch(KBadArithmeticException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), file1) == 0)
            TEST_ASSERT(e.line() == line1)
            TEST_ASSERT(strcmp(e.function(), function1) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testThrowTraceExceptionIf()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";

        try
        {
            ThrowTraceExceptionIf(KException, true, errorCode1, what1);
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), KLAB__FILE__) == 0)
            TEST_ASSERT(e.line()>0)
            TEST_ASSERT(strcmp(e.function(), KLAB__FUNC__) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowTraceExceptionIf(KException, false, errorCode1, what1);
            TEST_ASSERT(true)
        }
        catch(KException&)
        {
            TEST_ASSERT(false)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowTraceExceptionIf(KBadArithmeticException, true, errorCode1, what1);
            TEST_ASSERT(false)
        }
        catch(KBadArithmeticException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), KLAB__FILE__) == 0)
            TEST_ASSERT(e.line()>0)
            TEST_ASSERT(strcmp(e.function(), KLAB__FUNC__) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        } 


        try
        {
            ThrowTraceExceptionIf(KBadArithmeticException, false, errorCode1, what1);
            TEST_ASSERT(true)
        }
        catch(KBadArithmeticException&)
        {
            TEST_ASSERT(false)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testThrowTraceExceptionIfNot()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";

        try
        {
            ThrowTraceExceptionIfNot(KException, false, errorCode1, what1);
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), KLAB__FILE__) == 0)
            TEST_ASSERT(e.line()>0)
            TEST_ASSERT(strcmp(e.function(), KLAB__FUNC__) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowTraceExceptionIfNot(KException, true, errorCode1, what1);
            TEST_ASSERT(true)
        }
        catch(KException&)
        {
            TEST_ASSERT(false)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowTraceExceptionIfNot(KBadArithmeticException, false, errorCode1, what1);
            TEST_ASSERT(false)
        }
        catch(KBadArithmeticException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), KLAB__FILE__) == 0)
            TEST_ASSERT(e.line()>0)
            TEST_ASSERT(strcmp(e.function(), KLAB__FUNC__) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        } 


        try
        {
            ThrowTraceExceptionIfNot(KBadArithmeticException, true, errorCode1, what1);
            TEST_ASSERT(true)
        }
        catch(KBadArithmeticException&)
        {
            TEST_ASSERT(false)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testThrowTraceException()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";

        try
        {
            ThrowTraceException(KException, errorCode1, what1);
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), KLAB__FILE__) == 0)
            TEST_ASSERT(e.line()>0)
            TEST_ASSERT(strcmp(e.function(), KLAB__FUNC__) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }


        try
        {
            ThrowTraceException(KBadArithmeticException, errorCode1, what1);
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(e.errorCode() == errorCode1)
            TEST_ASSERT(strcmp(e.what(), what1) == 0)
            TEST_ASSERT(strcmp(e.file(), KLAB__FILE__) == 0)
            TEST_ASSERT(e.line()>0)
            TEST_ASSERT(strcmp(e.function(), KLAB__FUNC__) == 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KExceptionUnitTest::testFormatExceptionToString()
{
    try
    {
        klab::UInt32 errorCode1 = 123;
        const char  what1[]     = "Exception thrown !";
        const char  file1[]     = "FileWhereExceptionWasThrown.file";
        klab::UInt32 line1      = 456;
        const char  function1[] = "FunctionWhereExceptionWasThrown";

        try
        {
            KException e1(errorCode1, what1, file1, line1, function1);
            TEST_ASSERT(strcmp(FormatExceptionToString(e1), "") != 0)

            throw e1;
            TEST_ASSERT(false)
        }
        catch(KException& e)
        {
            TEST_ASSERT(strcmp(FormatExceptionToString(e), "") != 0)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
