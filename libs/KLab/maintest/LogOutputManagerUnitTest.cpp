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

#include "LogOutputManagerUnitTest.h"
#include "../include/LogOutputManager.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KLogOutputManagerUnitTest::KLogOutputManagerUnitTest() : Test::Suite()
{
    TEST_ADD(KLogOutputManagerUnitTest::testDefaultConstructor) 
    TEST_ADD(KLogOutputManagerUnitTest::testLevelConstructor)  
    TEST_ADD(KLogOutputManagerUnitTest::testLevelEnabledConstructor)
    TEST_ADD(KLogOutputManagerUnitTest::testCopyConstructor)
    TEST_ADD(KLogOutputManagerUnitTest::testAffectationOperator)

    TEST_ADD(KLogOutputManagerUnitTest::testSetLevel)
    TEST_ADD(KLogOutputManagerUnitTest::testSetEnabled)
    TEST_ADD(KLogOutputManagerUnitTest::testLevel)
    TEST_ADD(KLogOutputManagerUnitTest::testIsEnabled)
    TEST_ADD(KLogOutputManagerUnitTest::testWrite)
    TEST_ADD(KLogOutputManagerUnitTest::testClear)
    TEST_ADD(KLogOutputManagerUnitTest::testRegisterLogOutput)
    TEST_ADD(KLogOutputManagerUnitTest::testClearLogOutputs)
    TEST_ADD(KLogOutputManagerUnitTest::testCountLogOutputs)
    TEST_ADD(KLogOutputManagerUnitTest::testLogOutput)
}

// ---------------------------------------------------------------------------------------------------- //

KLogOutputManagerUnitTest::~KLogOutputManagerUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testDefaultConstructor()
{
    try
    {
        KLogOutputManager output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        TLogOutputManager<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testLevelConstructor()
{
    try
    {
        KLogOutputManager output(klab::WARNING_LOG);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        TLogOutputManager<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testLevelEnabledConstructor()
{
    try
    {
        KLogOutputManager output(klab::WARNING_LOG, true);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        TLogOutputManager<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testCopyConstructor()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output(klab::WARNING_LOG, true);
        output.registerLogOutput(out1);
        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)        

        KLogOutputManager outputCopy(output);
        TEST_ASSERT(outputCopy.level() == klab::WARNING_LOG)
        TEST_ASSERT(outputCopy.isEnabled() == true)
        TEST_ASSERT(outputCopy.countLogOutputs() == 2)
        TEST_ASSERT(outputCopy.logOutput(0).get() != 0)        
        TEST_ASSERT(outputCopy.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(outputCopy.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(outputCopy.logOutput(1).get() != 0)
        TEST_ASSERT(outputCopy.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(outputCopy.logOutput(1)->isEnabled() == false) 


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        woutput.registerLogOutput(wout1);
        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutputCopy(woutput);
        TEST_ASSERT(woutputCopy.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutputCopy.isEnabled() == false)
        TEST_ASSERT(woutputCopy.countLogOutputs() == 2)
        TEST_ASSERT(woutputCopy.logOutput(0).get() != 0)        
        TEST_ASSERT(woutputCopy.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutputCopy.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutputCopy.logOutput(1).get() != 0)
        TEST_ASSERT(woutputCopy.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutputCopy.logOutput(1)->isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testAffectationOperator()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output(klab::WARNING_LOG, true);
        output.registerLogOutput(out1);
        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)

        KLogOutputManager outputCopy;
        outputCopy = output;
        TEST_ASSERT(outputCopy.level() == klab::WARNING_LOG)
        TEST_ASSERT(outputCopy.isEnabled() == true)
        TEST_ASSERT(outputCopy.countLogOutputs() == 2)
        TEST_ASSERT(outputCopy.logOutput(0).get() != 0)        
        TEST_ASSERT(outputCopy.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(outputCopy.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(outputCopy.logOutput(1).get() != 0)
        TEST_ASSERT(outputCopy.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(outputCopy.logOutput(1)->isEnabled() == false)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        woutput.registerLogOutput(wout1);
        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutputCopy;
        woutputCopy = woutput;
        TEST_ASSERT(woutputCopy.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutputCopy.isEnabled() == false)
        TEST_ASSERT(woutputCopy.countLogOutputs() == 2)
        TEST_ASSERT(woutputCopy.logOutput(0).get() != 0)        
        TEST_ASSERT(woutputCopy.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutputCopy.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutputCopy.logOutput(1).get() != 0)
        TEST_ASSERT(woutputCopy.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutputCopy.logOutput(1)->isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testSetLevel()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.setLevel(klab::INFO_LOG);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.registerLogOutput(out1);
        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)

        output.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.setLevel(klab::INFO_LOG);
        TEST_ASSERT(woutput.level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.registerLogOutput(wout1);
        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        woutput.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testSetEnabled()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.setEnabled(false);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.registerLogOutput(out1);
        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)

        output.setEnabled(true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.setEnabled(false);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.registerLogOutput(wout1);
        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        woutput.setEnabled(true);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testLevel()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.setLevel(klab::INFO_LOG);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.registerLogOutput(out1);
        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::INFO_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)

        output.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.setLevel(klab::INFO_LOG);
        TEST_ASSERT(woutput.level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.registerLogOutput(wout1);
        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        woutput.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testIsEnabled()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output;
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.setEnabled(false);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.registerLogOutput(out1);
        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == false)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)

        output.setEnabled(true);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput;
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.setEnabled(false);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.registerLogOutput(wout1);
        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        woutput.setEnabled(true);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testWrite()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, true);

        TLogData<const klab::Char*> data1(klab::INFO_LOG, "My message log.");
        TLogData<const klab::Char*> data2(klab::ERROR_LOG, "My message log #2.");
        TLogData<const klab::Char*> data3(klab::DEBUG4_LOG, "My third message log !");
        TLogData<const klab::Char*> data4(klab::WARNING_LOG, "My fourth message log !");

        TLogData<const klab::WideChar*> wdata1(klab::INFO_LOG, L"My message log.");
        TLogData<const klab::WideChar*> wdata2(klab::ERROR_LOG, L"My message log #2.");
        TLogData<const klab::WideChar*> wdata3(klab::DEBUG4_LOG, L"My third message log !");
        TLogData<const klab::WideChar*> wdata4(klab::WARNING_LOG, L"My fourth message log !");


        KLogOutputManager output;
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

        output.write(data1);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 1)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 1)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))

        output.write(data2);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 2)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 2)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))

        output.write(data3);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 2)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 2)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))

        output.write(data4);
        TEST_ASSERT(output.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[2], data4.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[2], data4.toString()))

        output.setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[2], data4.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[2], data4.toString()))

        output.write(data3);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[2], data4.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[2], data4.toString()))

        out1->setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[2], data4.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[2], data4.toString()))

        output.write(data3);
        TEST_ASSERT(output.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[2], data4.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[3], data3.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[2], data4.toString()))

        output.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[2], data4.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[3], data3.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[2], data4.toString()))

        output.write(data1);
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[2], data4.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[3], data3.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[2], data4.toString()))

        output.write(data2);
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 5)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[2], data4.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[3], data3.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[4], data2.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 4)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[2], data4.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[3], data2.toString()))

        output.write(data4);
        TEST_ASSERT(output.level() == klab::ERROR_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(out1->logs().size() == 5)
        TEST_ASSERT(klab::Equals(out1->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[2], data4.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[3], data3.toString()))
        TEST_ASSERT(klab::Equals(out1->logs()[4], data2.toString()))
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(out2->logs().size() == 4)
        TEST_ASSERT(klab::Equals(out2->logs()[0], data1.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[1], data2.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[2], data4.toString()))
        TEST_ASSERT(klab::Equals(out2->logs()[3], data2.toString()))


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput;
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

        woutput.write(wdata1);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 1)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 1)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))

        woutput.write(wdata2);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 2)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 2)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))

        woutput.write(wdata3);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 2)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 2)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))

        woutput.write(wdata4);
        TEST_ASSERT(woutput.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[2], wdata4.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[2], wdata4.toString()))

        woutput.setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[2], wdata4.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[2], wdata4.toString()))

        woutput.write(wdata3);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[2], wdata4.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[2], wdata4.toString()))

        wout1->setLevel(klab::DEBUG4_LOG);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[2], wdata4.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[2], wdata4.toString()))

        woutput.write(wdata3);
        TEST_ASSERT(woutput.level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[2], wdata4.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[3], wdata3.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[2], wdata4.toString()))

        woutput.setLevel(klab::ERROR_LOG);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[2], wdata4.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[3], wdata3.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[2], wdata4.toString()))

        woutput.write(wdata1);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 4)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[2], wdata4.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[3], wdata3.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 3)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[2], wdata4.toString()))

        woutput.write(wdata2);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 5)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[2], wdata4.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[3], wdata3.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[4], wdata2.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 4)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[2], wdata4.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[3], wdata2.toString()))

        woutput.write(wdata4);
        TEST_ASSERT(woutput.level() == klab::ERROR_LOG)
        TEST_ASSERT(woutput.isEnabled() == true)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG4_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(wout1->logs().size() == 5)
        TEST_ASSERT(klab::Equals(wout1->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[2], wdata4.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[3], wdata3.toString()))
        TEST_ASSERT(klab::Equals(wout1->logs()[4], wdata2.toString()))
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == true)
        TEST_ASSERT(wout2->logs().size() == 4)
        TEST_ASSERT(klab::Equals(wout2->logs()[0], wdata1.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[1], wdata2.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[2], wdata4.toString()))
        TEST_ASSERT(klab::Equals(wout2->logs()[3], wdata2.toString()))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testClear()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output(klab::WARNING_LOG, true);
        output.registerLogOutput(out1);
        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)

        output.clear();
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.clear();
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        woutput.registerLogOutput(wout1);
        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        woutput.clear();
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.clear();
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testRegisterLogOutput()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output(klab::WARNING_LOG, true);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.registerLogOutput(out1);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 1)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)

        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.registerLogOutput(wout1);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 1)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)

        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)


        // Limit cases.
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)

        output.registerLogOutput(0);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)

        KLogOutputManager output0;
        TEST_ASSERT(output0.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output0.isEnabled() == true)
        TEST_ASSERT(output0.countLogOutputs() == 0)

        output0.registerLogOutput(0);
        TEST_ASSERT(output0.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output0.isEnabled() == true)
        TEST_ASSERT(output0.countLogOutputs() == 0)


        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        woutput.registerLogOutput(0);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput0;
        TEST_ASSERT(woutput0.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput0.isEnabled() == true)
        TEST_ASSERT(woutput0.countLogOutputs() == 0)

        woutput0.registerLogOutput(0);
        TEST_ASSERT(woutput0.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput0.isEnabled() == true)
        TEST_ASSERT(woutput0.countLogOutputs() == 0)

    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testClearLogOutputs()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output(klab::WARNING_LOG, true);
        output.registerLogOutput(out1);
        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)

        output.clearLogOutputs();
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.clearLogOutputs();
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        woutput.registerLogOutput(wout1);
        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)

        woutput.clearLogOutputs();
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.clearLogOutputs();
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testCountLogOutputs()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output(klab::WARNING_LOG, true);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.registerLogOutput(out1);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 1)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)

        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.registerLogOutput(wout1);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 1)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)

        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KLogOutputManagerUnitTest::testLogOutput()
{
    try
    {
        klab::TSmartPointer<KTestLogOutput> out1 = new KTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KTestLogOutput> out2 = new KTestLogOutput(klab::INFO_LOG, false);
        klab::TSmartPointer<KWTestLogOutput> wout1 = new KWTestLogOutput(klab::DEBUG3_LOG, true);
        klab::TSmartPointer<KWTestLogOutput> wout2 = new KWTestLogOutput(klab::INFO_LOG, false);


        KLogOutputManager output(klab::WARNING_LOG, true);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 0)

        output.registerLogOutput(out1);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 1)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)

        output.registerLogOutput(out2);
        TEST_ASSERT(output.level() == klab::WARNING_LOG)
        TEST_ASSERT(output.isEnabled() == true)
        TEST_ASSERT(output.countLogOutputs() == 2)
        TEST_ASSERT(output.logOutput(0).get() != 0)        
        TEST_ASSERT(output.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(output.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(output.logOutput(1).get() != 0)
        TEST_ASSERT(output.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(output.logOutput(1)->isEnabled() == false)


        TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> > woutput(klab::DEBUG3_LOG, false);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 0)

        woutput.registerLogOutput(wout1);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 1)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)

        woutput.registerLogOutput(wout2);
        TEST_ASSERT(woutput.level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.isEnabled() == false)
        TEST_ASSERT(woutput.countLogOutputs() == 2)
        TEST_ASSERT(woutput.logOutput(0).get() != 0)        
        TEST_ASSERT(woutput.logOutput(0)->level() == klab::DEBUG3_LOG)
        TEST_ASSERT(woutput.logOutput(0)->isEnabled() == true)
        TEST_ASSERT(woutput.logOutput(1).get() != 0)
        TEST_ASSERT(woutput.logOutput(1)->level() == klab::INFO_LOG)
        TEST_ASSERT(woutput.logOutput(1)->isEnabled() == false)


        // Limit cases.
        TEST_ASSERT(output.logOutput(2).get() == 0)
        TEST_ASSERT(woutput.logOutput(2).get() == 0)


        KLogOutputManager output0;
        TEST_ASSERT(output0.level() == klab::DEBUG_LOG)
        TEST_ASSERT(output0.isEnabled() == true)
        TEST_ASSERT(output0.countLogOutputs() == 0)
        TEST_ASSERT(output0.logOutput(0).get() == 0)

        TLogOutputManager<const klab::WideChar*, TLogData<const klab::WideChar*> > woutput0;
        TEST_ASSERT(woutput0.level() == klab::DEBUG_LOG)
        TEST_ASSERT(woutput0.isEnabled() == true)
        TEST_ASSERT(woutput0.countLogOutputs() == 0)
        TEST_ASSERT(woutput0.logOutput(0).get() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
