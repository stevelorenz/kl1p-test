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

#include "LogUnitTest.h"
#include "../include/Log.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KLogUnitTest::KLogUnitTest() : Test::Suite()
{
    TEST_ADD(KLogUnitTest::testDefaultConstructor) 
    TEST_ADD(KLogUnitTest::testLevelConstructor)  
    TEST_ADD(KLogUnitTest::testLevelFileLineFunctionConstructor) 

    TEST_ADD(KLogUnitTest::testStream)
    
    TEST_ADD(KLogUnitTest::testLOG)
    TEST_ADD(KLogUnitTest::testWLOG)

    TEST_ADD(KLogUnitTest::testLog)
    TEST_ADD(KLogUnitTest::testWLog)
}

// ---------------------------------------------------------------------------------------------------- //

KLogUnitTest::~KLogUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KLogUnitTest::testDefaultConstructor()
{
    try
    {
        TLog<const klab::Char*, TLogData<const klab::Char*>, TLogOutputManager<const klab::Char*, TLogData<const klab::Char*> > > log;
        TEST_ASSERT(true)

        TLog<const klab::WideChar*, TLogData<const klab::WideChar*>, TLogOutputManager<const klab::WideChar*, TLogData<const klab::WideChar*> > > wlog;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogUnitTest::testLevelConstructor()  
{
    try
    {
        TLog<const klab::Char*, TLogData<const klab::Char*>, TLogOutputManager<const klab::Char*, TLogData<const klab::Char*> > > log(klab::INFO_LOG);
        TEST_ASSERT(true)

        TLog<const klab::WideChar*, TLogData<const klab::WideChar*>, TLogOutputManager<const klab::WideChar*, TLogData<const klab::WideChar*> > > wlog(klab::WARNING_LOG);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogUnitTest::testLevelFileLineFunctionConstructor()
{
    try
    {
        TLog<const klab::Char*, TLogData<const klab::Char*>, TLogOutputManager<const klab::Char*, TLogData<const klab::Char*> > > log(klab::INFO_LOG, "file.cpp", 123, "char* function(int)");
        TEST_ASSERT(true)

        TLog<const klab::WideChar*, TLogData<const klab::WideChar*>, TLogOutputManager<const klab::WideChar*, TLogData<const klab::WideChar*> > > wlog(klab::WARNING_LOG, L"file.cpp", 123, L"char* function(int)");
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KLogUnitTest::testStream()
{
    try
    {
        TLog<const klab::Char*, TLogData<const klab::Char*>, TLogOutputManager<const klab::Char*, TLogData<const klab::Char*> > > log(klab::INFO_LOG, "file.cpp", 123, "char* function(int)");
        log.stream()<<"This is a message.";
        TEST_ASSERT(klab::Equals(log.stream().str(), "This is a message."))

        TLog<const klab::WideChar*, TLogData<const klab::WideChar*>, TLogOutputManager<const klab::WideChar*, TLogData<const klab::WideChar*> > > wlog(klab::WARNING_LOG, L"file.cpp", 123, L"char* function(int)");
        wlog.stream()<<L"This is a message.";
        TEST_ASSERT(klab::Equals(wlog.stream().str(), L"This is a message."))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogUnitTest::testLOG()
{
    try
    {
        LOG(klab::DEBUG4_LOG)<<"This is a debug4 message.";
        LOG(klab::DEBUG3_LOG)<<"This is a debug3 message.";
        LOG(klab::DEBUG2_LOG)<<"This is a debug2 message.";
        LOG(klab::DEBUG1_LOG)<<"This is a debug1 message.";
        LOG(klab::DEBUG_LOG)<<"This is a debug message.";
        LOG(klab::INFO_LOG)<<"This is an information message.";
        LOG(klab::WARNING_LOG)<<"This is a warning message !";
        LOG(klab::ERROR_LOG)<<"This is an error message !!!";
        LOG(klab::FATAL_ERROR_LOG)<<"THIS IS A FATAL ERROR MESSAGE !!!";
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogUnitTest::testWLOG()
{
    try
    {
        WLOG(klab::DEBUG4_LOG)<<L"This is a debug4 message.";
        WLOG(klab::DEBUG3_LOG)<<L"This is a debug3 message.";
        WLOG(klab::DEBUG2_LOG)<<L"This is a debug2 message.";
        WLOG(klab::DEBUG1_LOG)<<L"This is a debug1 message.";
        WLOG(klab::DEBUG_LOG)<<L"This is a debug message.";
        WLOG(klab::INFO_LOG)<<L"This is an information message.";
        WLOG(klab::WARNING_LOG)<<L"This is a warning message !";
        WLOG(klab::ERROR_LOG)<<L"This is an error message !!!";
        WLOG(klab::FATAL_ERROR_LOG)<<L"THIS IS A FATAL ERROR MESSAGE !!!";
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogUnitTest::testLog()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, true);

        TLogData<const klab::Char*> data1(klab::INFO_LOG, "My message log.", KLAB__FILE__, 0, KLAB__FUNC__);
        TLogData<const klab::Char*> data2(klab::ERROR_LOG, "My message log #2.", KLAB__FILE__, 0, KLAB__FUNC__);
        TLogData<const klab::Char*> data2_2(data2);
        TLogData<const klab::Char*> data3(klab::DEBUG4_LOG, "My third message log !", KLAB__FILE__, 0, KLAB__FUNC__);
        TLogData<const klab::Char*> data4(klab::WARNING_LOG, "My fourth message log !", KLAB__FILE__, 0, KLAB__FUNC__);


        TLogOutputManager<const klab::Char*, ILogData<const klab::Char*> >& output = TSingleton<TLogOutputManager<const klab::Char*, ILogData<const klab::Char*> > >::Instance();
        output.registerLogOutput(out1);
        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 0)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 0)

        LOG(klab::INFO_LOG)<<data1.message();
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 1)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 1)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))

        LOG(klab::ERROR_LOG)<<data2.message(); data2.setLine(KLAB__LINE__);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 2)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 2)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))

        LOG(klab::DEBUG4_LOG)<<data3.message();
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 2)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 2)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))

        LOG(klab::WARNING_LOG)<<data4.message(); data4.setLine(KLAB__LINE__);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))

        output.setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))

        LOG(klab::DEBUG4_LOG)<<data3.message();
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))

        out1->setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))

        LOG(klab::DEBUG4_LOG)<<data3.message();
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[3]), KLogUnitTest::RemoveDateString(data3.toString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))

        output.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[3]), KLogUnitTest::RemoveDateString(data3.toString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))

        LOG(klab::INFO_LOG)<<data1.message();
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[3]), KLogUnitTest::RemoveDateString(data3.toString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))

        LOG(klab::ERROR_LOG)<<data2.message(); data2_2.setLine(KLAB__LINE__);
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 5)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[3]), KLogUnitTest::RemoveDateString(data3.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[4]), KLogUnitTest::RemoveDateString(data2_2.toFullString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[3]), KLogUnitTest::RemoveDateString(data2_2.toFullString())))

        LOG(klab::WARNING_LOG)<<data4.message();
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 5)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[3]), KLogUnitTest::RemoveDateString(data3.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out1->logs()[4]), KLogUnitTest::RemoveDateString(data2_2.toFullString())))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[0]), KLogUnitTest::RemoveDateString(data1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[1]), KLogUnitTest::RemoveDateString(data2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[2]), KLogUnitTest::RemoveDateString(data4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(out2->logs()[3]), KLogUnitTest::RemoveDateString(data2_2.toFullString())))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogUnitTest::testWLog()
{
    try
    {
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, true);

        TLogData<const klab::WideChar*> wdata1(klab::INFO_LOG, L"My message log.", klab::ToWString(KLAB__FILE__).c_str(), 0, klab::ToWString(KLAB__FUNC__).c_str());
        TLogData<const klab::WideChar*> wdata2(klab::ERROR_LOG, L"My message log #2.", klab::ToWString(KLAB__FILE__).c_str(), 0, klab::ToWString(KLAB__FUNC__).c_str());
        TLogData<const klab::WideChar*> wdata2_2(wdata2);
        TLogData<const klab::WideChar*> wdata3(klab::DEBUG4_LOG, L"My third message log !",klab::ToWString(KLAB__FILE__).c_str(), 0, klab::ToWString(KLAB__FUNC__).c_str());
        TLogData<const klab::WideChar*> wdata4(klab::WARNING_LOG, L"My fourth message log !", klab::ToWString(KLAB__FILE__).c_str(), 0, klab::ToWString(KLAB__FUNC__).c_str());


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> >& woutput = TSingleton<TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > >::Instance();
        woutput.registerLogOutput(wout1);
        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 0)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 0)

        WLOG(klab::INFO_LOG)<<wdata1.message();
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 1)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 1)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))

        WLOG(klab::ERROR_LOG)<<wdata2.message(); wdata2.setLine(KLAB__LINE__);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 2)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 2)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))

        WLOG(klab::DEBUG4_LOG)<<wdata3.message();
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 2)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 2)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))

        WLOG(klab::WARNING_LOG)<<wdata4.message(); wdata4.setLine(KLAB__LINE__);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))

        woutput.setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))

        WLOG(klab::DEBUG4_LOG)<<wdata3.message();
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))

        wout1->setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))

        WLOG(klab::DEBUG4_LOG)<<wdata3.message();
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[3]), KLogUnitTest::RemoveDateString(wdata3.toString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))

        woutput.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[3]), KLogUnitTest::RemoveDateString(wdata3.toString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))

        WLOG(klab::INFO_LOG)<<wdata1.message();
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[3]), KLogUnitTest::RemoveDateString(wdata3.toString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))

        WLOG(klab::ERROR_LOG)<<wdata2.message(); wdata2_2.setLine(KLAB__LINE__);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 5)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[3]), KLogUnitTest::RemoveDateString(wdata3.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[4]), KLogUnitTest::RemoveDateString(wdata2_2.toFullString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[3]), KLogUnitTest::RemoveDateString(wdata2_2.toFullString())))

        WLOG(klab::WARNING_LOG)<<wdata4.message();
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 5)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[3]), KLogUnitTest::RemoveDateString(wdata3.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout1->logs()[4]), KLogUnitTest::RemoveDateString(wdata2_2.toFullString())))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 4)
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[0]), KLogUnitTest::RemoveDateString(wdata1.toString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[1]), KLogUnitTest::RemoveDateString(wdata2.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[2]), KLogUnitTest::RemoveDateString(wdata4.toFullString())))
        TEST_ASSERT(klab::Equals(KLogUnitTest::RemoveDateString(wout2->logs()[3]), KLogUnitTest::RemoveDateString(wdata2_2.toFullString())))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

std::string KLogUnitTest::RemoveDateString(const std::string& message)
{
    return message.substr(23, message.length()-24);
}

// ---------------------------------------------------------------------------------------------------- //

std::wstring KLogUnitTest::RemoveDateString(const std::wstring& message)
{
    return message.substr(23, message.length()-24);
}

// ---------------------------------------------------------------------------------------------------- //
