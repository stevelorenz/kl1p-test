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

#ifndef KLAB_LOGUNITTEST_H
#define KLAB_LOGUNITTEST_H

#include "LogOutputUnitTest.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KLogUnitTest : public Test::Suite
{
public:
    
    KLogUnitTest();
    virtual ~KLogUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();   
    void    testLevelConstructor();   
    void    testLevelFileLineFunctionConstructor();   

    // Methods tests.
    void    testStream();
    
    // Macro tests.
    void    testLOG();
    void    testWLOG();

    // Functional tests.
    void    testLog();
    void    testWLog();


protected:

    static std::string      RemoveDateString(const std::string& message);
    static std::wstring     RemoveDateString(const std::wstring& message);


private:

    KLogUnitTest(const KLogUnitTest& test);
    KLogUnitTest&   operator=(const KLogUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
