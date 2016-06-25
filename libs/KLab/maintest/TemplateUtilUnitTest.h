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

#ifndef KLAB_TEMPLATEUTILUNITTEST_H
#define KLAB_TEMPLATEUTILUNITTEST_H

#include "../include/TemplateUtil.h"
#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KTemplateUtilUnitTest : public Test::Suite
{
public:
    
    KTemplateUtilUnitTest();
    virtual ~KTemplateUtilUnitTest();


public:

    static klab::Int32      TestValue;
    
    
protected:

    // Template tests.
    void    testNOP();
    void    testVALUE();
    void    testINC();
    void    testDEC();
    void    testTYPEIF();
    void    testVALUEIF();
    void    testIF();
    void    testLOOP();
    void    testFILLARRAY();
    void    testCOPYARRAY();
    void    testMIN();
    void    testMAX();
    void    testPOWER();
    void    testSTATIC_ASSERT();


private:

    KTemplateUtilUnitTest(const KTemplateUtilUnitTest& test);
    KTemplateUtilUnitTest&  operator=(const KTemplateUtilUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

template<klab::UInt32 I>
struct KTemplateUtilUnitTest_IncrementTestValue
{
    static inline void  Do() {++KTemplateUtilUnitTest::TestValue;};
};

// ---------------------------------------------------------------------------------------------------- //

template<klab::UInt32 I>
struct KTemplateUtilUnitTest_DecrementTestValue
{
    static inline void  Do() {--KTemplateUtilUnitTest::TestValue;};
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
