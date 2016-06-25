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

#include "LogOutputUnitTest.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KLogOutputUnitTest::KLogOutputUnitTest() : Test::Suite()
{
    TEST_ADD(KLogOutputUnitTest::testDefaultConstructor) 
    TEST_ADD(KLogOutputUnitTest::testLevelConstructor)  
    TEST_ADD(KLogOutputUnitTest::testLevelEnabledConstructor)
    TEST_ADD(KLogOutputUnitTest::testCopyConstructor)
    TEST_ADD(KLogOutputUnitTest::testAffectationOperator)

    TEST_ADD(KLogOutputUnitTest::testSetLevel)
    TEST_ADD(KLogOutputUnitTest::testSetEnabled)
    TEST_ADD(KLogOutputUnitTest::testLevel)
    TEST_ADD(KLogOutputUnitTest::testIsEnabled)
    TEST_ADD(KLogOutputUnitTest::testWrite)
}

// ---------------------------------------------------------------------------------------------------- //

KLogOutputUnitTest::~KLogOutputUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testDefaultConstructor()
{
    try
    {
        KTestLogOutput output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)

        KWTestLogOutput woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testLevelConstructor()
{
    try
    {
        KTestLogOutput output(klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)

        KWTestLogOutput woutput(klab::DEBUG3_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testLevelEnabledConstructor()
{
    try
    {
        KTestLogOutput output(klab::WARNING_LOG, true);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)

        KWTestLogOutput woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.logs().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testCopyConstructor()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::INFO_LOG, "My message log.");
        TLogData<const klab::Char*> data2(klab::ERROR_LOG, "My message log #2.");


        KTestLogOutput output(klab::INFO_LOG, true);
        output.write(data1);
        output.write(data2);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 2)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[1], data2.toFullString()))

        KTestLogOutput outputCopy(output);
        TEST_ASSERT(outputCopy.level() == klab::INFO_LOG)
        TEST_ASSERT(outputCopy.isEnabled() == true)
        TEST_ASSERT(outputCopy.logs().size() == 2)
        TEST_ASSERT(klab::Equals(outputCopy.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(outputCopy.logs()[1], data2.toFullString()))


        KWTestLogOutput woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.logs().size() == 0)

        KWTestLogOutput woutputCopy(woutput);
        TEST_ASSERT(woutputCopy.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutputCopy.isEnabled() == false)
        TEST_ASSERT(woutputCopy.logs().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testAffectationOperator()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::INFO_LOG, "My message log.");
        TLogData<const klab::Char*> data2(klab::ERROR_LOG, "My message log #2.");


        KTestLogOutput output(klab::INFO_LOG, true);
        output.write(data1);
        output.write(data2);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 2)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[1], data2.toFullString()))

        KTestLogOutput outputCopy;
        outputCopy = output;
        TEST_ASSERT(outputCopy.level() == klab::INFO_LOG)
        TEST_ASSERT(outputCopy.isEnabled() == true)
        TEST_ASSERT(outputCopy.logs().size() == 2)
        TEST_ASSERT(klab::Equals(outputCopy.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(outputCopy.logs()[1], data2.toFullString()))


        KWTestLogOutput woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.logs().size() == 0)

        KWTestLogOutput woutputCopy;
        woutputCopy = woutput;
        TEST_ASSERT(woutputCopy.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutputCopy.isEnabled() == false)
        TEST_ASSERT(woutputCopy.logs().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testSetLevel()
{
    try
    {
        KTestLogOutput output(klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)

        output.setLevel(klab::INFO_LOG);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)


        KWTestLogOutput woutput(klab::DEBUG3_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)

        woutput.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testSetEnabled()
{
    try
    {
        KTestLogOutput output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)

        output.setEnabled(false);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)
        TEST_ASSERT(output.logs().size() == 0)

        output.setEnabled(true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)


        KWTestLogOutput woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)

        woutput.setEnabled(false);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.logs().size() == 0)

        woutput.setEnabled(true);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testLevel()
{
    try
    {
        KTestLogOutput output(klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)

        output.setLevel(klab::INFO_LOG);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)


        KWTestLogOutput woutput(klab::DEBUG3_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)

        woutput.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testIsEnabled()
{
    try
    {
        KTestLogOutput output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)

        output.setEnabled(false);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)
        TEST_ASSERT(output.logs().size() == 0)

        output.setEnabled(true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)


        KWTestLogOutput woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)

        woutput.setEnabled(false);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.logs().size() == 0)

        woutput.setEnabled(true);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputUnitTest::testWrite()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::INFO_LOG, "My message log.");
        TLogData<const klab::Char*> data2(klab::ERROR_LOG, "My message log #2.");
        TLogData<const klab::Char*> data3(klab::DEBUG4_LOG, "My third message log !");
        TLogData<const klab::Char*> data4(klab::WARNING_LOG, "My fourth message log !");

        TLogData<const klab::WideChar*> wdata1(klab::INFO_LOG, L"My message log.");
        TLogData<const klab::WideChar*> wdata2(klab::ERROR_LOG, L"My message log #2.");
        TLogData<const klab::WideChar*> wdata3(klab::DEBUG4_LOG, L"My third message log !");
        TLogData<const klab::WideChar*> wdata4(klab::WARNING_LOG, L"My fourth message log !");


        KTestLogOutput output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 0)

        output.write(data1);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 1)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))

        output.write(data2);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 2)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[1], data2.toString()))

        output.write(data3);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 2)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[1], data2.toFullString()))

        output.write(data4);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 3)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[1], data2.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[2], data4.toFullString()))

        output.setLevel(klab::DEBUG4_LOG);
        output.write(data3);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 4)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[1], data2.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[2], data4.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[3], data3.toString()))

        output.write(data2);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 5)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[1], data2.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[2], data4.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[3], data3.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[4], data2.toFullString()))

        output.setEnabled(false);
        output.write(data1);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == false)
        TEST_ASSERT(output.logs().size() == 5)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[1], data2.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[2], data4.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[3], data3.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[4], data2.toFullString()))

        output.setEnabled(true);
        output.write(data1);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.logs().size() == 6)
        TEST_ASSERT(klab::Equals(output.logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[1], data2.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[2], data4.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[3], data3.toString()))
        TEST_ASSERT(klab::Equals(output.logs()[4], data2.toFullString()))
        TEST_ASSERT(klab::Equals(output.logs()[5], data1.toString()))


        KWTestLogOutput woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 0)

        woutput.write(wdata1);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 1)
        TEST_ASSERT(klab::Equals(woutput.logs()[0], wdata1.toString()))

        woutput.write(wdata2);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 2)
        TEST_ASSERT(klab::Equals(woutput.logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[1], wdata2.toString()))

        woutput.write(wdata3);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 2)
        TEST_ASSERT(klab::Equals(woutput.logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[1], wdata2.toFullString()))

        woutput.write(wdata4);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 3)
        TEST_ASSERT(klab::Equals(woutput.logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[1], wdata2.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[2], wdata4.toFullString()))

        woutput.setLevel(klab::DEBUG4_LOG);
        woutput.write(wdata3);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 4)
        TEST_ASSERT(klab::Equals(woutput.logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[1], wdata2.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[2], wdata4.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[3], wdata3.toString()))

        woutput.write(wdata2);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 5)
        TEST_ASSERT(klab::Equals(woutput.logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[1], wdata2.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[2], wdata4.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[3], wdata3.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[4], wdata2.toFullString()))

        woutput.setEnabled(false);
        woutput.write(wdata1);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.logs().size() == 5)
        TEST_ASSERT(klab::Equals(woutput.logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[1], wdata2.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[2], wdata4.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[3], wdata3.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[4], wdata2.toFullString()))

        woutput.setEnabled(true);
        woutput.write(wdata1);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.logs().size() == 6)
        TEST_ASSERT(klab::Equals(woutput.logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[1], wdata2.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[2], wdata4.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[3], wdata3.toString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[4], wdata2.toFullString()))
        TEST_ASSERT(klab::Equals(woutput.logs()[5], wdata1.toString()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

KTestLogOutput::KTestLogOutput() : TLogOutput<const klab::Char*, ILogData<const klab::Char*> >(),
_logs()
{}

// ---------------------------------------------------------------------------------------------------- //

KTestLogOutput::KTestLogOutput(const KLogLevel& level) : TLogOutput<const klab::Char*, ILogData<const klab::Char*> >(level),
_logs()
{}

// ---------------------------------------------------------------------------------------------------- //

KTestLogOutput::KTestLogOutput(const KLogLevel& level, bool isEnabled) : TLogOutput<const klab::Char*, ILogData<const klab::Char*> >(level, isEnabled),
_logs()
{}

// ---------------------------------------------------------------------------------------------------- //

KTestLogOutput::KTestLogOutput(const KTestLogOutput& output) : TLogOutput<const klab::Char*, ILogData<const klab::Char*> >(output),
_logs(output._logs)
{}

// ---------------------------------------------------------------------------------------------------- //

KTestLogOutput::~KTestLogOutput()
{}

// ---------------------------------------------------------------------------------------------------- //

KTestLogOutput& KTestLogOutput::operator=(const KTestLogOutput& output)
{
    if(this != &output)
    {
        TLogOutput<const klab::Char*, ILogData<const klab::Char*> >::operator=(output);

        _logs = output._logs;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

void KTestLogOutput::clear()
{
    TScopedMutex<KMutex> mutex(this->mutex());

    _logs.clear();
}

// ---------------------------------------------------------------------------------------------------- //

const std::vector<std::string>& KTestLogOutput::logs() const
{
    TScopedMutex<KMutex> mutex(this->mutex());

    return _logs;
}

// ---------------------------------------------------------------------------------------------------- //

void KTestLogOutput::writeLog(const ILogData<const klab::Char*>& log)
{
    if(log.level() < klab::WARNING_LOG) _logs.push_back(log.toString());
    else                                _logs.push_back(log.toFullString());
}

// ---------------------------------------------------------------------------------------------------- //

KWTestLogOutput::KWTestLogOutput() : TLogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> >(),
_logs()
{}

// ---------------------------------------------------------------------------------------------------- //

KWTestLogOutput::KWTestLogOutput(const KLogLevel& level) : TLogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> >(level),
_logs()
{}

// ---------------------------------------------------------------------------------------------------- //

KWTestLogOutput::KWTestLogOutput(const KLogLevel& level, bool isEnabled) : TLogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> >(level, isEnabled),
_logs()
{}

// ---------------------------------------------------------------------------------------------------- //

KWTestLogOutput::KWTestLogOutput(const KWTestLogOutput& output) : TLogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> >(output),
_logs(output._logs)
{}

// ---------------------------------------------------------------------------------------------------- //

KWTestLogOutput::~KWTestLogOutput()
{}

// ---------------------------------------------------------------------------------------------------- //

KWTestLogOutput& KWTestLogOutput::operator=(const KWTestLogOutput& output)
{
    if(this != &output)
    {
        TLogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> >::operator=(output);

        _logs = output._logs;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

void KWTestLogOutput::clear()
{
    TScopedMutex<KMutex> mutex(this->mutex());

    _logs.clear();
}

// ---------------------------------------------------------------------------------------------------- //

const std::vector<std::wstring>& KWTestLogOutput::logs() const
{
    TScopedMutex<KMutex> mutex(this->mutex());

    return _logs;
}

// ---------------------------------------------------------------------------------------------------- //

void KWTestLogOutput::writeLog(const ILogData<const klab::WideChar*>& log)
{
    if(log.level() < klab::WARNING_LOG) _logs.push_back(log.toString());
    else                                _logs.push_back(log.toFullString());
}

// ---------------------------------------------------------------------------------------------------- //
