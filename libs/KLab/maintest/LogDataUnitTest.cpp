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

#include "LogDataUnitTest.h"
#include "../include/LogData.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KLogDataUnitTest::KLogDataUnitTest() : Test::Suite()
{
    TEST_ADD(KLogDataUnitTest::testDefaultConstructor) 
    TEST_ADD(KLogDataUnitTest::testLevelConstructor)  
    TEST_ADD(KLogDataUnitTest::testLevelMessageConstructor)  
    TEST_ADD(KLogDataUnitTest::testLevelMessageTimestampConstructor)
    TEST_ADD(KLogDataUnitTest::testLevelFileLineFunctionConstructor)
    TEST_ADD(KLogDataUnitTest::testLevelMessageFileLineFunctionConstructor)
    TEST_ADD(KLogDataUnitTest::testLevelMessageTimestampFileLineFunctionConstructor)
    TEST_ADD(KLogDataUnitTest::testCopyConstructor)
    TEST_ADD(KLogDataUnitTest::testAffectationOperator)

    TEST_ADD(KLogDataUnitTest::testSet)
    TEST_ADD(KLogDataUnitTest::testSetLevel)
    TEST_ADD(KLogDataUnitTest::testSetMessage)
    TEST_ADD(KLogDataUnitTest::testSetTimestamp)
    TEST_ADD(KLogDataUnitTest::testUpdateTimestamp)
    TEST_ADD(KLogDataUnitTest::testSetFile)
    TEST_ADD(KLogDataUnitTest::testSetLine)
    TEST_ADD(KLogDataUnitTest::testSetFunction)
    TEST_ADD(KLogDataUnitTest::testLevel)
    TEST_ADD(KLogDataUnitTest::testMessage)
    TEST_ADD(KLogDataUnitTest::testTimestamp)
    TEST_ADD(KLogDataUnitTest::testFile)
    TEST_ADD(KLogDataUnitTest::testLine)
    TEST_ADD(KLogDataUnitTest::testFunction)
    TEST_ADD(KLogDataUnitTest::testLevelToString)
    TEST_ADD(KLogDataUnitTest::testTimestampToString)
    TEST_ADD(KLogDataUnitTest::testLineToString)
    TEST_ADD(KLogDataUnitTest::testToString)
    TEST_ADD(KLogDataUnitTest::testToFullString)
}

// ---------------------------------------------------------------------------------------------------- //

KLogDataUnitTest::~KLogDataUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testDefaultConstructor()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testLevelConstructor()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::WARNING_LOG);
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2(klab::DEBUG2_LOG);
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3(klab::FATAL_ERROR_LOG);
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testLevelMessageConstructor()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::WARNING_LOG, "My warning message log !");
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2(klab::DEBUG2_LOG, L"My debug2 message log.");
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!");
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
   
void KLogDataUnitTest::testLevelMessageTimestampConstructor()
{
    try
    {
        klab::KMillisecTimestamp timestamp = KSystemTime::GetCurrentMillisecTimestamp();


        TLogData<const klab::Char*> data1(klab::WARNING_LOG, "My warning message log !", timestamp);
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2(klab::DEBUG2_LOG, L"My debug2 message log.", timestamp);
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() == timestamp)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!", timestamp);
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() == timestamp)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testLevelFileLineFunctionConstructor()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::WARNING_LOG, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data1.file(), "file.cpp"))
        TEST_ASSERT(data1.line() == 123)
        TEST_ASSERT(klab::Equals(data1.function(), "char* function(int)"))

        TLogData<const klab::WideChar*> data2(klab::DEBUG2_LOG, L"file.cpp", 123, L"char* function(int)");
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data2.file(), L"file.cpp"))
        TEST_ASSERT(data2.line() == 123)
        TEST_ASSERT(klab::Equals(data2.function(), L"char* function(int)"))

        KLogData data3(klab::FATAL_ERROR_LOG, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data3.file(), "file.cpp"))
        TEST_ASSERT(data3.line() == 123)
        TEST_ASSERT(klab::Equals(data3.function(), "char* function(int)"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testLevelMessageFileLineFunctionConstructor()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::WARNING_LOG, "My warning message log !", "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data1.file(), "file.cpp"))
        TEST_ASSERT(data1.line() == 123)
        TEST_ASSERT(klab::Equals(data1.function(), "char* function(int)"))

        TLogData<const klab::WideChar*> data2(klab::DEBUG2_LOG, L"My debug2 message log.", L"file.cpp", 123, L"char* function(int)");
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data2.file(), L"file.cpp"))
        TEST_ASSERT(data2.line() == 123)
        TEST_ASSERT(klab::Equals(data2.function(), L"char* function(int)"))

        KLogData data3(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!", "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data3.file(), "file.cpp"))
        TEST_ASSERT(data3.line() == 123)
        TEST_ASSERT(klab::Equals(data3.function(), "char* function(int)"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testLevelMessageTimestampFileLineFunctionConstructor()
{
    try
    {
        klab::KMillisecTimestamp timestamp = KSystemTime::GetCurrentMillisecTimestamp();


        TLogData<const klab::Char*> data1(klab::WARNING_LOG, "My warning message log !", timestamp, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data1.file(), "file.cpp"))
        TEST_ASSERT(data1.line() == 123)
        TEST_ASSERT(klab::Equals(data1.function(), "char* function(int)"))

        TLogData<const klab::WideChar*> data2(klab::DEBUG2_LOG, L"My debug2 message log.", timestamp, L"file.cpp", 123, L"char* function(int)");
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data2.file(), L"file.cpp"))
        TEST_ASSERT(data2.line() == 123)
        TEST_ASSERT(klab::Equals(data2.function(), L"char* function(int)"))

        KLogData data3(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!", timestamp, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data3.file(), "file.cpp"))
        TEST_ASSERT(data3.line() == 123)
        TEST_ASSERT(klab::Equals(data3.function(), "char* function(int)"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
  
void KLogDataUnitTest::testCopyConstructor()
{
    try
    {
        klab::KMillisecTimestamp timestamp = KSystemTime::GetCurrentMillisecTimestamp();


        TLogData<const klab::Char*> data1(klab::WARNING_LOG, "My warning message log !", timestamp, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data1.file(), "file.cpp"))
        TEST_ASSERT(data1.line() == 123)
        TEST_ASSERT(klab::Equals(data1.function(), "char* function(int)"))

        TLogData<const klab::Char*> data1Copy(data1);
        TEST_ASSERT(data1Copy.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1Copy.message(), "My warning message log !"))
        TEST_ASSERT(data1Copy.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data1Copy.file(), "file.cpp"))
        TEST_ASSERT(data1Copy.line() == 123)
        TEST_ASSERT(klab::Equals(data1Copy.function(), "char* function(int)"))


        TLogData<const klab::WideChar*> data2(klab::DEBUG2_LOG, L"My debug2 message log.", timestamp, L"file.cpp", 123, L"char* function(int)");
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data2.file(), L"file.cpp"))
        TEST_ASSERT(data2.line() == 123)
        TEST_ASSERT(klab::Equals(data2.function(), L"char* function(int)"))

        TLogData<const klab::WideChar*> data2Copy(data2);
        TEST_ASSERT(data2Copy.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2Copy.message(), L"My debug2 message log."))
        TEST_ASSERT(data2Copy.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data2Copy.file(), L"file.cpp"))
        TEST_ASSERT(data2Copy.line() == 123)
        TEST_ASSERT(klab::Equals(data2Copy.function(), L"char* function(int)"))


        KLogData data3(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!", timestamp, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data3.file(), "file.cpp"))
        TEST_ASSERT(data3.line() == 123)
        TEST_ASSERT(klab::Equals(data3.function(), "char* function(int)"))

        KLogData data3Copy(data3);
        TEST_ASSERT(data3Copy.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3Copy.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3Copy.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data3Copy.file(), "file.cpp"))
        TEST_ASSERT(data3Copy.line() == 123)
        TEST_ASSERT(klab::Equals(data3Copy.function(), "char* function(int)"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testAffectationOperator()
{
    try
    {
        klab::KMillisecTimestamp timestamp = KSystemTime::GetCurrentMillisecTimestamp();


        TLogData<const klab::Char*> data1(klab::WARNING_LOG, "My warning message log !", timestamp, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data1.file(), "file.cpp"))
        TEST_ASSERT(data1.line() == 123)
        TEST_ASSERT(klab::Equals(data1.function(), "char* function(int)"))

        TLogData<const klab::Char*> data1Copy;
        data1Copy = data1;
        TEST_ASSERT(data1Copy.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1Copy.message(), "My warning message log !"))
        TEST_ASSERT(data1Copy.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data1Copy.file(), "file.cpp"))
        TEST_ASSERT(data1Copy.line() == 123)
        TEST_ASSERT(klab::Equals(data1Copy.function(), "char* function(int)"))


        TLogData<const klab::WideChar*> data2(klab::DEBUG2_LOG, L"My debug2 message log.", timestamp, L"file.cpp", 123, L"char* function(int)");
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data2.file(), L"file.cpp"))
        TEST_ASSERT(data2.line() == 123)
        TEST_ASSERT(klab::Equals(data2.function(), L"char* function(int)"))

        TLogData<const klab::WideChar*> data2Copy;
        data2Copy = data2;
        TEST_ASSERT(data2Copy.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2Copy.message(), L"My debug2 message log."))
        TEST_ASSERT(data2Copy.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data2Copy.file(), L"file.cpp"))
        TEST_ASSERT(data2Copy.line() == 123)
        TEST_ASSERT(klab::Equals(data2Copy.function(), L"char* function(int)"))


        KLogData data3(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!", timestamp, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data3.file(), "file.cpp"))
        TEST_ASSERT(data3.line() == 123)
        TEST_ASSERT(klab::Equals(data3.function(), "char* function(int)"))

        KLogData data3Copy;
        data3Copy = data3;
        TEST_ASSERT(data3Copy.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3Copy.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3Copy.timestamp() == timestamp)   
        TEST_ASSERT(klab::Equals(data3Copy.file(), "file.cpp"))
        TEST_ASSERT(data3Copy.line() == 123)
        TEST_ASSERT(klab::Equals(data3Copy.function(), "char* function(int)"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testSet()
{
    try
    {
        klab::KMillisecTimestamp timestamp = KSystemTime::GetCurrentMillisecTimestamp();


        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.set(klab::WARNING_LOG, "My warning message log !");
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.set(klab::DEBUG2_LOG, L"My debug2 message log.");
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.set(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!");
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.set(klab::WARNING_LOG, "My warning message log !", timestamp);
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.set(klab::DEBUG2_LOG, L"My debug2 message log.", timestamp);
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() == timestamp)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.set(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!", timestamp);
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() == timestamp)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.set(klab::WARNING_LOG, "My warning message log !", "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() >= timestamp)
        TEST_ASSERT(klab::Equals(data1.file(), "file.cpp"))
        TEST_ASSERT(data1.line() == 123)
        TEST_ASSERT(klab::Equals(data1.function(), "char* function(int)"))

        data2.set(klab::DEBUG2_LOG, L"My debug2 message log.", L"file.cpp", 123, L"char* function(int)");
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() >= timestamp)
        TEST_ASSERT(klab::Equals(data2.file(), L"file.cpp"))
        TEST_ASSERT(data2.line() == 123)
        TEST_ASSERT(klab::Equals(data2.function(), L"char* function(int)"))

        data3.set(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!", "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() >= timestamp)
        TEST_ASSERT(klab::Equals(data3.file(), "file.cpp"))
        TEST_ASSERT(data3.line() == 123)
        TEST_ASSERT(klab::Equals(data3.function(), "char* function(int)"))


        data1.set(klab::WARNING_LOG, "My warning message log !", timestamp, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data1.file(), "file.cpp"))
        TEST_ASSERT(data1.line() == 123)
        TEST_ASSERT(klab::Equals(data1.function(), "char* function(int)"))

        data2.set(klab::DEBUG2_LOG, L"My debug2 message log.", timestamp, L"file.cpp", 123, L"char* function(int)");
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data2.file(), L"file.cpp"))
        TEST_ASSERT(data2.line() == 123)
        TEST_ASSERT(klab::Equals(data2.function(), L"char* function(int)"))

        data3.set(klab::FATAL_ERROR_LOG, "My fatal-error message log !!!", timestamp, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() == timestamp)
        TEST_ASSERT(klab::Equals(data3.file(), "file.cpp"))
        TEST_ASSERT(data3.line() == 123)
        TEST_ASSERT(klab::Equals(data3.function(), "char* function(int)"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testSetLevel()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setLevel(klab::WARNING_LOG);
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setLevel(klab::DEBUG2_LOG);
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setLevel(klab::FATAL_ERROR_LOG);
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testSetMessage()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)

        
        data1.setMessage("My warning message log !");
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setMessage(L"My debug2 message log.");
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setMessage("My fatal-error message log !!!");
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testSetTimestamp()
{
    try
    {
        klab::KMillisecTimestamp timestamp = KSystemTime::GetCurrentMillisecTimestamp();


        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setTimestamp(timestamp);
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setTimestamp(timestamp);
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() == timestamp)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setTimestamp(timestamp);
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() == timestamp)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testUpdateTimestamp()
{
    try
    {
        klab::KMillisecTimestamp timestamp = KSystemTime::GetCurrentMillisecTimestamp();


        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        klab::Sleep(100);

        data1.updateTimestamp();
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() > timestamp)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.updateTimestamp();
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() > timestamp)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.updateTimestamp();
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() > timestamp)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testSetFile()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setFile("file.cpp");
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data1.file(), "file.cpp"))
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setFile(L"file.cpp");
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data2.file(), L"file.cpp"))
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setFile("file.cpp");
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data3.file(), "file.cpp"))
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testSetLine()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setLine(123);
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 123)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setLine(456);
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 456)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setLine(789);
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 789)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testSetFunction()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setFunction("char* function(int)");
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(klab::Equals(data1.function(), "char* function(int)"))

        data2.setFunction(L"char* function(int)");
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(klab::Equals(data2.function(), L"char* function(int)"))

        data3.setFunction("char* function(int)");
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(klab::Equals(data3.function(), "char* function(int)"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testLevel()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setLevel(klab::WARNING_LOG);
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setLevel(klab::DEBUG2_LOG);
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setLevel(klab::FATAL_ERROR_LOG);
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testMessage()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)

        
        data1.setMessage("My warning message log !");
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(klab::Equals(data1.message(), "My warning message log !"))
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setMessage(L"My debug2 message log.");
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(klab::Equals(data2.message(), L"My debug2 message log."))
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setMessage("My fatal-error message log !!!");
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(klab::Equals(data3.message(), "My fatal-error message log !!!"))
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testTimestamp()
{
    try
    {
        klab::KMillisecTimestamp timestamp = KSystemTime::GetCurrentMillisecTimestamp();


        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setTimestamp(timestamp);
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() == timestamp)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setTimestamp(timestamp);
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() == timestamp)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setTimestamp(timestamp);
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() == timestamp)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testFile()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setFile("file.cpp");
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data1.file(), "file.cpp"))
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setFile(L"file.cpp");
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data2.file(), L"file.cpp"))
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setFile("file.cpp");
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(klab::Equals(data3.file(), "file.cpp"))
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testLine()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setLine(123);
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 123)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        data2.setLine(456);
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 456)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        data3.setLine(789);
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 789)
        TEST_ASSERT(std::string(data3.function()).length() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testFunction()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(std::string(data1.function()).length() == 0)

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(std::wstring(data2.function()).length() == 0)

        KLogData data3;
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(std::string(data3.function()).length() == 0)


        data1.setFunction("char* function(int)");
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data1.message()).length() == 0)
        TEST_ASSERT(data1.timestamp() >= 0)
        TEST_ASSERT(std::string(data1.file()).length() == 0)
        TEST_ASSERT(data1.line() == 0)
        TEST_ASSERT(klab::Equals(data1.function(), "char* function(int)"))

        data2.setFunction(L"char* function(int)");
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(std::wstring(data2.message()).length() == 0)
        TEST_ASSERT(data2.timestamp() >= 0)
        TEST_ASSERT(std::wstring(data2.file()).length() == 0)
        TEST_ASSERT(data2.line() == 0)
        TEST_ASSERT(klab::Equals(data2.function(), L"char* function(int)"))

        data3.setFunction("char* function(int)");
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(std::string(data3.message()).length() == 0)
        TEST_ASSERT(data3.timestamp() >= 0)
        TEST_ASSERT(std::string(data3.file()).length() == 0)
        TEST_ASSERT(data3.line() == 0)
        TEST_ASSERT(klab::Equals(data3.function(), "char* function(int)"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testLevelToString()
{
    try
    {
        TLogData<const klab::Char*> data1;
        data1.setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(data1.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(klab::Equals(data1.levelToString(), "Debug4"))

        data1.setLevel(klab::DEBUG3_LOG);
        TEST_ASSERT(data1.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(klab::Equals(data1.levelToString(), "Debug3"))

        data1.setLevel(klab::DEBUG2_LOG);
        TEST_ASSERT(data1.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data1.levelToString(), "Debug2"))

        data1.setLevel(klab::DEBUG1_LOG);
        TEST_ASSERT(data1.level() == klab::DEBUG1_LOG)
        TEST_ASSERT(klab::Equals(data1.levelToString(), "Debug1"))

        data1.setLevel(klab::DEBUG_LOG);
        TEST_ASSERT(data1.level() == klab::DEBUG_LOG)
        TEST_ASSERT(klab::Equals(data1.levelToString(), "Debug"))

        data1.setLevel(klab::INFO_LOG);
        TEST_ASSERT(data1.level() == klab::INFO_LOG)
        TEST_ASSERT(klab::Equals(data1.levelToString(), "Info"))

        data1.setLevel(klab::WARNING_LOG);
        TEST_ASSERT(data1.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data1.levelToString(), "Warning"))

        data1.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(data1.level() == klab::ERROR_LOG)
        TEST_ASSERT(klab::Equals(data1.levelToString(), "ERROR"))

        data1.setLevel(klab::FATAL_ERROR_LOG);
        TEST_ASSERT(data1.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data1.levelToString(), "FATAL"))


        TLogData<const klab::WideChar*> data2;
        data2.setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(data2.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(klab::Equals(data2.levelToString(), L"Debug4"))

        data2.setLevel(klab::DEBUG3_LOG);
        TEST_ASSERT(data2.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(klab::Equals(data2.levelToString(), L"Debug3"))

        data2.setLevel(klab::DEBUG2_LOG);
        TEST_ASSERT(data2.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data2.levelToString(), L"Debug2"))

        data2.setLevel(klab::DEBUG1_LOG);
        TEST_ASSERT(data2.level() == klab::DEBUG1_LOG)
        TEST_ASSERT(klab::Equals(data2.levelToString(), L"Debug1"))

        data2.setLevel(klab::DEBUG_LOG);
        TEST_ASSERT(data2.level() == klab::DEBUG_LOG)
        TEST_ASSERT(klab::Equals(data2.levelToString(), L"Debug"))

        data2.setLevel(klab::INFO_LOG);
        TEST_ASSERT(data2.level() == klab::INFO_LOG)
        TEST_ASSERT(klab::Equals(data2.levelToString(), L"Info"))

        data2.setLevel(klab::WARNING_LOG);
        TEST_ASSERT(data2.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data2.levelToString(), L"Warning"))

        data2.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(data2.level() == klab::ERROR_LOG)
        TEST_ASSERT(klab::Equals(data2.levelToString(), L"ERROR"))

        data2.setLevel(klab::FATAL_ERROR_LOG);
        TEST_ASSERT(data2.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data2.levelToString(), L"FATAL"))


        KLogData data3;
        data3.setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(data3.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(klab::Equals(data3.levelToString(), "Debug4"))

        data3.setLevel(klab::DEBUG3_LOG);
        TEST_ASSERT(data3.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(klab::Equals(data3.levelToString(), "Debug3"))

        data3.setLevel(klab::DEBUG2_LOG);
        TEST_ASSERT(data3.level() == klab::DEBUG2_LOG)
        TEST_ASSERT(klab::Equals(data3.levelToString(), "Debug2"))

        data3.setLevel(klab::DEBUG1_LOG);
        TEST_ASSERT(data3.level() == klab::DEBUG1_LOG)
        TEST_ASSERT(klab::Equals(data3.levelToString(), "Debug1"))

        data3.setLevel(klab::DEBUG_LOG);
        TEST_ASSERT(data3.level() == klab::DEBUG_LOG)
        TEST_ASSERT(klab::Equals(data3.levelToString(), "Debug"))

        data3.setLevel(klab::INFO_LOG);
        TEST_ASSERT(data3.level() == klab::INFO_LOG)
        TEST_ASSERT(klab::Equals(data3.levelToString(), "Info"))

        data3.setLevel(klab::WARNING_LOG);
        TEST_ASSERT(data3.level() == klab::WARNING_LOG)
        TEST_ASSERT(klab::Equals(data3.levelToString(), "Warning"))

        data3.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(data3.level() == klab::ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.levelToString(), "ERROR"))

        data3.setLevel(klab::FATAL_ERROR_LOG);
        TEST_ASSERT(data3.level() == klab::FATAL_ERROR_LOG)
        TEST_ASSERT(klab::Equals(data3.levelToString(), "FATAL"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testTimestampToString()
{
    try
    {
        klab::KMillisecTimestamp timestamp = 1327744997097LL;


        TLogData<const klab::Char*> data1;
        data1.setTimestamp(timestamp);
        std::string str1 = data1.timestampToString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097"))

        TLogData<const klab::WideChar*> data2;
        data2.setTimestamp(timestamp);
        std::wstring str2 = data2.timestampToString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097"))

        KLogData data3;
        data3.setTimestamp(timestamp);
        std::string str3 = data3.timestampToString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testLineToString()
{
    try
    {
        TLogData<const klab::Char*> data1;
        TEST_ASSERT(klab::Equals(data1.lineToString(), "0"))
        data1.setLine(1);
        TEST_ASSERT(klab::Equals(data1.lineToString(), "1"))
        data1.setLine(12);
        TEST_ASSERT(klab::Equals(data1.lineToString(), "12"))
        data1.setLine(456);
        TEST_ASSERT(klab::Equals(data1.lineToString(), "456"))

        TLogData<const klab::WideChar*> data2;
        TEST_ASSERT(klab::Equals(data2.lineToString(), L"0"))
        data2.setLine(1);
        TEST_ASSERT(klab::Equals(data2.lineToString(), L"1"))
        data2.setLine(12);
        TEST_ASSERT(klab::Equals(data2.lineToString(), L"12"))
        data2.setLine(456);
        TEST_ASSERT(klab::Equals(data2.lineToString(), L"456"))

        KLogData data3;
        TEST_ASSERT(klab::Equals(data3.lineToString(), "0"))
        data3.setLine(1);
        TEST_ASSERT(klab::Equals(data3.lineToString(), "1"))
        data3.setLine(12);
        TEST_ASSERT(klab::Equals(data3.lineToString(), "12"))
        data3.setLine(456);
        TEST_ASSERT(klab::Equals(data3.lineToString(), "456"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testToString()
{
    try
    {
        klab::KMillisecTimestamp timestamp = 1327744997097LL;


        TLogData<const klab::Char*> data1(klab::DEBUG4_LOG, "My message log.", timestamp, "file.cpp", 123, "char* function(int)");
        std::string str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug4]  My message log."))
        data1.setLevel(klab::DEBUG3_LOG);
        str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug3]  My message log."))
        data1.setLevel(klab::DEBUG2_LOG);
        str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug2]  My message log."))
        data1.setLevel(klab::DEBUG1_LOG);
        str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug1]  My message log."))
        data1.setLevel(klab::DEBUG_LOG);
        str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug]   My message log."))
        data1.setLevel(klab::INFO_LOG);
        str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Info]    My message log."))
        data1.setLevel(klab::WARNING_LOG);
        str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Warning] My message log."))
        data1.setLevel(klab::ERROR_LOG);
        str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [ERROR]   My message log."))
        data1.setLevel(klab::FATAL_ERROR_LOG);
        str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [FATAL]   My message log."))


        TLogData<const klab::WideChar*> data2(klab::DEBUG4_LOG, L"My message log.", timestamp, L"file.cpp", 123, L"char* function(int)");
        std::wstring str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug4]  My message log."))
        data2.setLevel(klab::DEBUG3_LOG);
        str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug3]  My message log."))
        data2.setLevel(klab::DEBUG2_LOG);
        str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug2]  My message log."))
        data2.setLevel(klab::DEBUG1_LOG);
        str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug1]  My message log."))
        data2.setLevel(klab::DEBUG_LOG);
        str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug]   My message log."))
        data2.setLevel(klab::INFO_LOG);
        str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Info]    My message log."))
        data2.setLevel(klab::WARNING_LOG);
        str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Warning] My message log."))
        data2.setLevel(klab::ERROR_LOG);
        str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [ERROR]   My message log."))
        data2.setLevel(klab::FATAL_ERROR_LOG);
        str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [FATAL]   My message log."))


        KLogData data3(klab::DEBUG4_LOG, "My message log.", timestamp, "file.cpp", 123, "char* function(int)");
        std::string str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug4]  My message log."))
        data3.setLevel(klab::DEBUG3_LOG);
        str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug3]  My message log."))
        data3.setLevel(klab::DEBUG2_LOG);
        str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug2]  My message log."))
        data3.setLevel(klab::DEBUG1_LOG);
        str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug1]  My message log."))
        data3.setLevel(klab::DEBUG_LOG);
        str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug]   My message log."))
        data3.setLevel(klab::INFO_LOG);
        str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Info]    My message log."))
        data3.setLevel(klab::WARNING_LOG);
        str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Warning] My message log."))
        data3.setLevel(klab::ERROR_LOG);
        str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [ERROR]   My message log."))
        data3.setLevel(klab::FATAL_ERROR_LOG);
        str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [FATAL]   My message log."))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogDataUnitTest::testToFullString()
{
    try
    {
        klab::KMillisecTimestamp timestamp = 1327744997097LL;


        TLogData<const klab::Char*> data1(klab::DEBUG4_LOG, "My message log.", timestamp);
        std::string str1 = data1.toString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug4]  My message log."))
        data1.setLevel(klab::DEBUG3_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug3]  My message log."))
        data1.setLevel(klab::DEBUG2_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug2]  My message log."))
        data1.setLevel(klab::DEBUG1_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug1]  My message log."))
        data1.setLevel(klab::DEBUG_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug]   My message log."))
        data1.setLevel(klab::INFO_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Info]    My message log."))
        data1.setLevel(klab::WARNING_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Warning] My message log."))
        data1.setLevel(klab::ERROR_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [ERROR]   My message log."))
        data1.setLevel(klab::FATAL_ERROR_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [FATAL]   My message log."))

        data1.setFile("file.cpp");
        data1.setLine(123);
        data1.setFunction("char* function(int)");
        data1.setLevel(klab::DEBUG4_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug4]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data1.setLevel(klab::DEBUG3_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug3]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data1.setLevel(klab::DEBUG2_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug2]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data1.setLevel(klab::DEBUG1_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug1]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data1.setLevel(klab::DEBUG_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Debug]   My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data1.setLevel(klab::INFO_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Info]    My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data1.setLevel(klab::WARNING_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [Warning] My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data1.setLevel(klab::ERROR_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [ERROR]   My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data1.setLevel(klab::FATAL_ERROR_LOG);
        str1 = data1.toFullString();
        TEST_ASSERT(klab::Equals(str1, "2012-01-28 11:03:17.097 - [FATAL]   My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))


        TLogData<const klab::WideChar*> data2(klab::DEBUG4_LOG, L"My message log.", timestamp);
        std::wstring str2 = data2.toString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug4]  My message log."))
        data2.setLevel(klab::DEBUG3_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug3]  My message log."))
        data2.setLevel(klab::DEBUG2_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug2]  My message log."))
        data2.setLevel(klab::DEBUG1_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug1]  My message log."))
        data2.setLevel(klab::DEBUG_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug]   My message log."))
        data2.setLevel(klab::INFO_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Info]    My message log."))
        data2.setLevel(klab::WARNING_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Warning] My message log."))
        data2.setLevel(klab::ERROR_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [ERROR]   My message log."))
        data2.setLevel(klab::FATAL_ERROR_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [FATAL]   My message log."))

        data2.setFile(L"file.cpp");
        data2.setLine(123);
        data2.setFunction(L"char* function(int)");
        data2.setLevel(klab::DEBUG4_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug4]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data2.setLevel(klab::DEBUG3_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug3]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data2.setLevel(klab::DEBUG2_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug2]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data2.setLevel(klab::DEBUG1_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug1]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data2.setLevel(klab::DEBUG_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Debug]   My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data2.setLevel(klab::INFO_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Info]    My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data2.setLevel(klab::WARNING_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [Warning] My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data2.setLevel(klab::ERROR_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [ERROR]   My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data2.setLevel(klab::FATAL_ERROR_LOG);
        str2 = data2.toFullString();
        TEST_ASSERT(klab::Equals(str2, L"2012-01-28 11:03:17.097 - [FATAL]   My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))


        KLogData data3(klab::DEBUG4_LOG, "My message log.", timestamp);
        std::string str3 = data3.toString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug4]  My message log."))
        data3.setLevel(klab::DEBUG3_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug3]  My message log."))
        data3.setLevel(klab::DEBUG2_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug2]  My message log."))
        data3.setLevel(klab::DEBUG1_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug1]  My message log."))
        data3.setLevel(klab::DEBUG_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug]   My message log."))
        data3.setLevel(klab::INFO_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Info]    My message log."))
        data3.setLevel(klab::WARNING_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Warning] My message log."))
        data3.setLevel(klab::ERROR_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [ERROR]   My message log."))
        data3.setLevel(klab::FATAL_ERROR_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [FATAL]   My message log."))

        data3.setFile("file.cpp");
        data3.setLine(123);
        data3.setFunction("char* function(int)");
        data3.setLevel(klab::DEBUG4_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug4]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data3.setLevel(klab::DEBUG3_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug3]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data3.setLevel(klab::DEBUG2_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug2]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data3.setLevel(klab::DEBUG1_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug1]  My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data3.setLevel(klab::DEBUG_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Debug]   My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data3.setLevel(klab::INFO_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Info]    My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data3.setLevel(klab::WARNING_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [Warning] My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data3.setLevel(klab::ERROR_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [ERROR]   My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
        data3.setLevel(klab::FATAL_ERROR_LOG);
        str3 = data3.toFullString();
        TEST_ASSERT(klab::Equals(str3, "2012-01-28 11:03:17.097 - [FATAL]   My message log.\n                                    file=\"file.cpp\", line=123, function=\"char* function(int)\""))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
