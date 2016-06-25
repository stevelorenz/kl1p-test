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

#ifndef KLAB_LOGOUTPUTMANAGERUNITTEST_H
#define KLAB_LOGOUTPUTMANAGERUNITTEST_H

#include "LogOutputUnitTest.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KLogOutputManagerUnitTest : public Test::Suite
{
public:
    
    KLogOutputManagerUnitTest();
    virtual ~KLogOutputManagerUnitTest();
    
    
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
    void    testClear();
    void    testRegisterLogOutput();
    void    testClearLogOutputs();
    void    testCountLogOutputs();
    void    testLogOutput();


private:

    KLogOutputManagerUnitTest(const KLogOutputManagerUnitTest& test);
    KLogOutputManagerUnitTest&  operator=(const KLogOutputManagerUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
