// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KL1p C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KL1P_SL0HISTORYUNITTEST_H
#define KL1P_SL0HISTORYUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KSL0HistoryUnitTest : public Test::Suite
{
public:
    
    KSL0HistoryUnitTest();
    virtual ~KSL0HistoryUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Operators tests.
    void    testBracketOperator();

    // Methods tests.
    void    testClear();
    void    testPush();
    void    testSize();
    void    testElement();


private:

    KSL0HistoryUnitTest(const KSL0HistoryUnitTest& test);
    KSL0HistoryUnitTest&    operator=(const KSL0HistoryUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
