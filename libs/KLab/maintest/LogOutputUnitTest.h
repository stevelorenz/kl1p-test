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

#ifndef KLAB_LOGOUTPUTUNITTEST_H
#define KLAB_LOGOUTPUTUNITTEST_H

#include <cpptest.h>
#include "../include/LogOutput.h"
#include "../include/LogData.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KLogOutputUnitTest : public Test::Suite
{
public:
    
    KLogOutputUnitTest();
    virtual ~KLogOutputUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();   
    void    testLevelConstructor();   
    void    testLevelEnabledConstructor();   
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testSetLevel();
    void    testSetEnabled();
    void    testLevel();
    void    testIsEnabled();
    void    testWrite();


private:

    KLogOutputUnitTest(const KLogOutputUnitTest& test);
    KLogOutputUnitTest&     operator=(const KLogOutputUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

class KTestLogOutput : public TLogOutput<const klab::Char*, ILogData<const klab::Char*> >
{
public:

    KTestLogOutput();
    KTestLogOutput(const KLogLevel& level);
    KTestLogOutput(const KLogLevel& level, bool isEnabled);
    KTestLogOutput(const KTestLogOutput& output);
    virtual ~KTestLogOutput();

    KTestLogOutput&     operator=(const KTestLogOutput& output);

    void                clear();

    const std::vector<std::string>& logs() const;


protected:

    virtual void        writeLog(const ILogData<const klab::Char*>& log);


private:

    std::vector<std::string>    _logs;
};

// ---------------------------------------------------------------------------------------------------- //

class KWTestLogOutput : public TLogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> >
{
public:

    KWTestLogOutput();
    KWTestLogOutput(const KLogLevel& level);
    KWTestLogOutput(const KLogLevel& level, bool isEnabled);
    KWTestLogOutput(const KWTestLogOutput& output);
    virtual ~KWTestLogOutput();

    KWTestLogOutput&    operator=(const KWTestLogOutput& output);

    void                clear();

    const std::vector<std::wstring>&    logs() const;


protected:

    virtual void        writeLog(const ILogData<const klab::WideChar*>& log);


private:

    std::vector<std::wstring>   _logs;
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
