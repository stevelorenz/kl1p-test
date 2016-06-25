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

#include "ModuleUnitTest.h"
#include "../include/Module.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KModuleUnitTest::KModuleUnitTest() : Test::Suite()
{
    TEST_ADD(KModuleUnitTest::testDefaultConstructor) 
    TEST_ADD(KModuleUnitTest::testPathConstructor)  

    TEST_ADD(KModuleUnitTest::testSetPath)
    TEST_ADD(KModuleUnitTest::testPath)
    TEST_ADD(KModuleUnitTest::testLoad)
    TEST_ADD(KModuleUnitTest::testClean)
    TEST_ADD(KModuleUnitTest::testIsLoaded)
    TEST_ADD(KModuleUnitTest::testFunction)
}

// ---------------------------------------------------------------------------------------------------- //

KModuleUnitTest::~KModuleUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KModuleUnitTest::testDefaultConstructor()
{
    try
    {
        TModule<> module1;
        TEST_ASSERT(module1.isLoaded() == false)
        TEST_ASSERT(module1.path() == "")
        
        KModule module2;
        TEST_ASSERT(module2.isLoaded() == false)
        TEST_ASSERT(module2.path() == "")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KModuleUnitTest::testPathConstructor() 
{
    try
    {
        TModule<> module1("MyModule");
        TEST_ASSERT(module1.isLoaded() == false)
        TEST_ASSERT(module1.path() == "MyModule")
        
        KModule module2("MyModule");
        TEST_ASSERT(module2.isLoaded() == false)
        TEST_ASSERT(module2.path() == "MyModule")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KModuleUnitTest::testSetPath()
{
    try
    {
        TModule<> module1;
        TEST_ASSERT(module1.isLoaded() == false)
        TEST_ASSERT(module1.path() == "")

        module1.setPath("MyModule");
        TEST_ASSERT(module1.isLoaded() == false)
        TEST_ASSERT(module1.path() == "MyModule")

        module1.setPath("   MyModule_2 ");
        TEST_ASSERT(module1.isLoaded() == false)
        TEST_ASSERT(module1.path() == "MyModule_2")

        
        KModule module2;
        TEST_ASSERT(module2.isLoaded() == false)
        TEST_ASSERT(module2.path() == "")

        module2.setPath("MyModule");
        TEST_ASSERT(module2.isLoaded() == false)
        TEST_ASSERT(module2.path() == "MyModule")

        module2.setPath("   MyModule__3");
        TEST_ASSERT(module2.isLoaded() == false)
        TEST_ASSERT(module2.path() == "MyModule__3")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KModuleUnitTest::testPath()
{
    try
    {
        TModule<> module1;
        TEST_ASSERT(module1.isLoaded() == false)
        TEST_ASSERT(module1.path() == "")

        module1.setPath("MyModule");
        TEST_ASSERT(module1.isLoaded() == false)
        TEST_ASSERT(module1.path() == "MyModule")

        
        KModule module2;
        TEST_ASSERT(module2.isLoaded() == false)
        TEST_ASSERT(module2.path() == "")

        module2.setPath("MyModule");
        TEST_ASSERT(module2.isLoaded() == false)
        TEST_ASSERT(module2.path() == "MyModule")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KModuleUnitTest::testLoad()
{
    try
    {
#if defined(KLAB_MSWINDOWS_SYSTEM)
        std::string modulePath = "kernel32"; 
#elif defined(KLAB_UNIX_SYSTEM)
        std::string modulePath = "libdl"; 
#elif defined(KLAB_MACOS_SYSTEM)
        std::string modulePath = "libdl"; 
#else
        std::string modulePath = ""; 
#endif

        TModule<> module(modulePath);
        TEST_ASSERT(module.isLoaded() == false)
        TEST_ASSERT(module.path() == modulePath)

        module.load();
        TEST_ASSERT(module.isLoaded() == true)
        TEST_ASSERT(module.path() == modulePath)


        // Limit cases.
        TModule<> module0("MyModule");
        TEST_ASSERT(module0.isLoaded() == false)
        TEST_ASSERT(module0.path() == "MyModule")

        try                             {module0.load(); TEST_ASSERT(false)}
        catch(KLoadModuleException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KModuleUnitTest::testClean()
{
    try
    {
#if defined(KLAB_MSWINDOWS_SYSTEM)
        std::string modulePath = "kernel32"; 
#elif defined(KLAB_UNIX_SYSTEM)
        std::string modulePath = "libdl"; 
#elif defined(KLAB_MACOS_SYSTEM)
        std::string modulePath = "libdl"; 
#else
        std::string modulePath = ""; 
#endif

        TModule<> module(modulePath);
        TEST_ASSERT(module.isLoaded() == false)
        TEST_ASSERT(module.path() == modulePath)

        module.load();
        TEST_ASSERT(module.isLoaded() == true)
        TEST_ASSERT(module.path() == modulePath)

        module.clean();
        TEST_ASSERT(module.isLoaded() == false)
        TEST_ASSERT(module.path() == modulePath)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KModuleUnitTest::testIsLoaded()
{
    try
    {
#if defined(KLAB_MSWINDOWS_SYSTEM)
        std::string modulePath = "kernel32"; 
#elif defined(KLAB_UNIX_SYSTEM)
        std::string modulePath = "libdl"; 
#elif defined(KLAB_MACOS_SYSTEM)
        std::string modulePath = "libdl"; 
#else
        std::string modulePath = ""; 
#endif

        TModule<> module(modulePath);
        TEST_ASSERT(module.isLoaded() == false)
        TEST_ASSERT(module.path() == modulePath)

        module.load();
        TEST_ASSERT(module.isLoaded() == true)
        TEST_ASSERT(module.path() == modulePath)

        module.clean();
        TEST_ASSERT(module.isLoaded() == false)
        TEST_ASSERT(module.path() == modulePath)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KModuleUnitTest::testFunction()
{
    try
    {
#if defined(KLAB_MSWINDOWS_SYSTEM)
        std::string modulePath = "kernel32"; 
        std::string funcName   = "GetCurrentThreadId";
#elif defined(KLAB_UNIX_SYSTEM)
        std::string modulePath = "libdl"; 
        std::string funcName   = "dlsym";
#elif defined(KLAB_MACOS_SYSTEM)
        std::string modulePath = "libdl"; 
        std::string funcName   = "dlsym";
#else
        std::string modulePath = ""; 
        std::string funcName   = "";
#endif

        TModule<> module(modulePath);
        TEST_ASSERT(module.isLoaded() == false)
        TEST_ASSERT(module.path() == modulePath)

        module.load();
        TEST_ASSERT(module.isLoaded() == true)
        TEST_ASSERT(module.path() == modulePath)

        KModuleFunction func = module.function(funcName);
        TEST_ASSERT(func != 0)   

#if defined(KLAB_MSWINDOWS_SYSTEM)
        typedef DWORD (*ModuleFunc)();
        ModuleFunc f = klab::CastModuleFunctionTo<ModuleFunc>(func);
        TEST_ASSERT(f != 0)
        DWORD threadID = f();
        TEST_ASSERT(threadID > 0)
#elif defined(KLAB_UNIX_SYSTEM)
        typedef void* (*ModuleFunc)(void*, char*);
		ModuleFunc f = klab::CastModuleFunctionTo<ModuleFunc>(func);
		TEST_ASSERT(f != 0)
#elif defined(KLAB_MACOS_SYSTEM)
        typedef void* (*ModuleFunc)(void*, char*);
		ModuleFunc f = klab::CastModuleFunctionTo<ModuleFunc>(func);
		TEST_ASSERT(f != 0)
#else
		TEST_ASSERT(false)
#endif


        // Limit cases.
		TEST_ASSERT(module.isLoaded() == true)
        TEST_ASSERT(module.path() == modulePath)
        try                                 {KModuleFunction func0 = module.function("MyBadFunction"); TEST_ASSERT(false)}
        catch(KGetFunctionModuleException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
		
		module.clean();
		TEST_ASSERT(module.isLoaded() == false)
        TEST_ASSERT(module.path() == modulePath)
		try                                 {KModuleFunction func0 = module.function(funcName); TEST_ASSERT(false)}
        catch(KGetFunctionModuleException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}


        TModule<> module0;
        TEST_ASSERT(module0.isLoaded() == false)
        TEST_ASSERT(module0.path() == "")

        try                                 {KModuleFunction func0 = module0.function("function"); TEST_ASSERT(false)}
        catch(KGetFunctionModuleException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
