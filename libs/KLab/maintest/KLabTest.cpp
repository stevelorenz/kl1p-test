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

#include "KLabTest.h"
#include "TypeInfoUnitTest.h"
#include "FuncUtilUnitTest.h"
#include "StringUtilUnitTest.h"
#include "TemplateUtilUnitTest.h"
#include "ExceptionUnitTest.h"
#include "SmartPointerUnitTest.h"
#include "AtomicCountUnitTest.h"
#include "BitArrayUnitTest.h"
#include "CircularBufferUnitTest.h"
#include "IndexedContainerElementUnitTest.h"
#include "ArrayElementUnitTest.h"
#include "GridElementUnitTest.h"
#include "RandomUnitTest.h"
#include "RGBColorUnitTest.h"
#include "SingletonUnitTest.h"
#include "SystemVersionUnitTest.h"
#include "MutexUnitTest.h"
#include "ScopedMutexUnitTest.h"
#include "SignalUnitTest.h"
#include "SimpleSignalUnitTest.h"
#include "ThreadUnitTest.h"
#include "ModuleUnitTest.h"
#include "SystemTimeUnitTest.h"
#include "DateTimeUnitTest.h"
#include "TimerUnitTest.h"
#include "LogDataUnitTest.h"
#include "LogOutputUnitTest.h"
#include "LogOutputManagerUnitTest.h"
#include "LogUnitTest.h"
#include "StandardLogOutputUnitTest.h"
#include "FileLogOutputUnitTest.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KLabTest::KLabTest()
{}

// ---------------------------------------------------------------------------------------------------- //

KLabTest::~KLabTest()
{}

// ---------------------------------------------------------------------------------------------------- //

bool KLabTest::run()
{
    Test::Suite tests;
    
    tests.add(std::auto_ptr<Test::Suite>(new KTypeInfoUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KFuncUtilUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KStringUtilUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KTemplateUtilUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KExceptionUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KSmartPointerUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KAtomicCountUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KBitArrayUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KCircularBufferUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KIndexedContainerElementUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KArrayElementUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KGridElementUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KRandomUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KRGBColorUnitTest()));   
    tests.add(std::auto_ptr<Test::Suite>(new KSingletonUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KSystemVersionUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KMutexUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KScopedMutexUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KSignalUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KSimpleSignalUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KThreadUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KModuleUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KSystemTimeUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KDateTimeUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KTimerUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KLogDataUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KLogOutputUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KLogOutputManagerUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KLogUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KStandardLogOutputUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KFileLogOutputUnitTest()));    
    
    Test::TextOutput output(Test::TextOutput::Verbose);
    return tests.run(output);
}
    
// ---------------------------------------------------------------------------------------------------- //
