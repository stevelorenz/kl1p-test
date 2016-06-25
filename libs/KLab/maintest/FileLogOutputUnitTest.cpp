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

#include "FileLogOutputUnitTest.h"
#include "../include/FileLogOutput.h"
#include "../include/LogData.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KFileLogOutputUnitTest::KFileLogOutputUnitTest() : Test::Suite()
{
    TEST_ADD(KFileLogOutputUnitTest::testPathConstructor) 
    TEST_ADD(KFileLogOutputUnitTest::testPathAppendConstructor)
    TEST_ADD(KFileLogOutputUnitTest::testPathAppendLevelConstructor)  
    TEST_ADD(KFileLogOutputUnitTest::testPathAppendLevelEnabledConstructor)

    TEST_ADD(KFileLogOutputUnitTest::testSetLevel)
    TEST_ADD(KFileLogOutputUnitTest::testSetEnabled)
    TEST_ADD(KFileLogOutputUnitTest::testLevel)
    TEST_ADD(KFileLogOutputUnitTest::testIsEnabled)
    TEST_ADD(KFileLogOutputUnitTest::testWrite)
}

// ---------------------------------------------------------------------------------------------------- //

KFileLogOutputUnitTest::~KFileLogOutputUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KFileLogOutputUnitTest::testPathConstructor()
{
    try
    {
        TFileLogOutput<const klab::Char*, TLogData<const klab::Char*> > output("log_test.txt");
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        TFileLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput("wlog_test.txt");
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFileLogOutputUnitTest::testPathAppendConstructor()
{
    try
    {
        TFileLogOutput<const klab::Char*, TLogData<const klab::Char*> > output("log_test.txt", true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        TFileLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput("wlog_test.txt", true);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFileLogOutputUnitTest::testPathAppendLevelConstructor()
{
    try
    {
        TFileLogOutput<const klab::Char*, TLogData<const klab::Char*> > output("log_test.txt", true, klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        TFileLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput("wlog_test.txt", true, klab::DEBUG3_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFileLogOutputUnitTest::testPathAppendLevelEnabledConstructor()
{
    try
    {
        TFileLogOutput<const klab::Char*, TLogData<const klab::Char*> > output("log_test.txt", true, klab::WARNING_LOG, true);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        TFileLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput("wlog_test.txt", true, klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFileLogOutputUnitTest::testSetLevel()
{
    try
    {
        TFileLogOutput<const klab::Char*, TLogData<const klab::Char*> > output("log_test.txt", true, klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setLevel(klab::INFO_LOG);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)


        TFileLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput("wlog_test.txt", true, klab::DEBUG3_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFileLogOutputUnitTest::testSetEnabled()
{
    try
    {
        TFileLogOutput<const klab::Char*, TLogData<const klab::Char*> > output("log_test.txt", true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setEnabled(false);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)

        output.setEnabled(true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)


        TFileLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput("wlog_test.txt", true);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.setEnabled(false);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)

        woutput.setEnabled(true);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFileLogOutputUnitTest::testLevel()
{
    try
    {
        TFileLogOutput<const klab::Char*, TLogData<const klab::Char*> > output("log_test.txt", true, klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setLevel(klab::INFO_LOG);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)


        TFileLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput("wlog_test.txt", true, klab::DEBUG3_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFileLogOutputUnitTest::testIsEnabled()
{
    try
    {
        TFileLogOutput<const klab::Char*, TLogData<const klab::Char*> > output("log_test.txt", true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setEnabled(false);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)

        output.setEnabled(true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)


        TFileLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput("wlog_test.txt", true);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.setEnabled(false);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)

        woutput.setEnabled(true);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFileLogOutputUnitTest::testWrite()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::INFO_LOG, "My message log.", KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);
        TLogData<const klab::Char*> data2(klab::ERROR_LOG, "My message log #2.", KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);
        TLogData<const klab::Char*> data3(klab::DEBUG4_LOG, "My third message log !", KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);
        TLogData<const klab::Char*> data4(klab::WARNING_LOG, "My fourth message log !", KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);

        TLogData<const klab::WideChar*> wdata1(klab::INFO_LOG, L"My message log.", klab::ToWString(KLAB__FILE__).c_str(), KLAB__LINE__, klab::ToWString(KLAB__FUNC__).c_str());
        TLogData<const klab::WideChar*> wdata2(klab::ERROR_LOG, L"My message log #2.", klab::ToWString(KLAB__FILE__).c_str(), KLAB__LINE__, klab::ToWString(KLAB__FUNC__).c_str());
        TLogData<const klab::WideChar*> wdata3(klab::DEBUG4_LOG, L"My third message log !", klab::ToWString(KLAB__FILE__).c_str(), KLAB__LINE__, klab::ToWString(KLAB__FUNC__).c_str());
        TLogData<const klab::WideChar*> wdata4(klab::WARNING_LOG, L"My fourth message log !", klab::ToWString(KLAB__FILE__).c_str(), KLAB__LINE__, klab::ToWString(KLAB__FUNC__).c_str());


        TFileLogOutput<const klab::Char*, TLogData<const klab::Char*> > output("log_test.txt");
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.write(data1);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.write(data2);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.write(data3);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.write(data4);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setLevel(klab::DEBUG4_LOG);
        output.write(data3);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.write(data2);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setEnabled(false);
        output.write(data1);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == false)

        output.setEnabled(true);
        output.write(data1);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)


        TFileLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput("wlog_test.txt");
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.write(wdata1);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.write(wdata2);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.write(wdata3);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.write(wdata4);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.setLevel(klab::DEBUG4_LOG);
        woutput.write(wdata3);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.write(wdata2);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)

        woutput.setEnabled(false);
        woutput.write(wdata1);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)

        woutput.setEnabled(true);
        woutput.write(wdata1);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
