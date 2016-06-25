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

#include "StandardLogOutputUnitTest.h"
#include "../include/StandardLogOutput.h"
#include "../include/LogData.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KStandardLogOutputUnitTest::KStandardLogOutputUnitTest() : Test::Suite()
{
    TEST_ADD(KStandardLogOutputUnitTest::testDefaultConstructor) 
    TEST_ADD(KStandardLogOutputUnitTest::testLevelConstructor)  
    TEST_ADD(KStandardLogOutputUnitTest::testLevelEnabledConstructor)
    TEST_ADD(KStandardLogOutputUnitTest::testCopyConstructor)
    TEST_ADD(KStandardLogOutputUnitTest::testAffectationOperator)

    TEST_ADD(KStandardLogOutputUnitTest::testSetLevel)
    TEST_ADD(KStandardLogOutputUnitTest::testSetEnabled)
    TEST_ADD(KStandardLogOutputUnitTest::testLevel)
    TEST_ADD(KStandardLogOutputUnitTest::testIsEnabled)
    TEST_ADD(KStandardLogOutputUnitTest::testWrite)
}

// ---------------------------------------------------------------------------------------------------- //

KStandardLogOutputUnitTest::~KStandardLogOutputUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KStandardLogOutputUnitTest::testDefaultConstructor()
{
    try
    {
        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStandardLogOutputUnitTest::testLevelConstructor()
{
    try
    {
        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output(klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStandardLogOutputUnitTest::testLevelEnabledConstructor()
{
    try
    {
        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output(klab::WARNING_LOG, true);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStandardLogOutputUnitTest::testCopyConstructor()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::INFO_LOG, "My message log.");
        TLogData<const klab::Char*> data2(klab::ERROR_LOG, "My message log #2.");


        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output(klab::INFO_LOG, true);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > outputCopy(output);
        TEST_ASSERT(outputCopy.level() == klab::INFO_LOG)
        TEST_ASSERT(outputCopy.isEnabled() == true)


        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)

        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutputCopy(woutput);
        TEST_ASSERT(woutputCopy.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutputCopy.isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStandardLogOutputUnitTest::testAffectationOperator()
{
    try
    {
        TLogData<const klab::Char*> data1(klab::INFO_LOG, "My message log.");
        TLogData<const klab::Char*> data2(klab::ERROR_LOG, "My message log #2.");


        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output(klab::INFO_LOG, true);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > outputCopy;
        outputCopy = output;
        TEST_ASSERT(outputCopy.level() == klab::INFO_LOG)
        TEST_ASSERT(outputCopy.isEnabled() == true)


        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)

        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutputCopy;
        woutputCopy = woutput;
        TEST_ASSERT(woutputCopy.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutputCopy.isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStandardLogOutputUnitTest::testSetLevel()
{
    try
    {
        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output(klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setLevel(klab::INFO_LOG);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)


        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG);
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

void KStandardLogOutputUnitTest::testSetEnabled()
{
    try
    {
        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setEnabled(false);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)

        output.setEnabled(true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)


        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput;
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

void KStandardLogOutputUnitTest::testLevel()
{
    try
    {
        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output(klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setLevel(klab::INFO_LOG);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)


        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG);
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

void KStandardLogOutputUnitTest::testIsEnabled()
{
    try
    {
        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)

        output.setEnabled(false);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)

        output.setEnabled(true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)


        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput;
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

void KStandardLogOutputUnitTest::testWrite()
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


        TStandardLogOutput<const klab::Char*, TLogData<const klab::Char*> > output;
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


        TStandardLogOutput<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput;
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
