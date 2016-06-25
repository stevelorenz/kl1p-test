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

#ifndef KLAB_SYSTEMVERSIONUNITTEST_H
#define KLAB_SYSTEMVERSIONUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KSystemVersionUnitTest : public Test::Suite
{
public:
    
    KSystemVersionUnitTest();
    virtual ~KSystemVersionUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();
    
    // Methods tests.
    void    testCode();
    void    testVersion();
    void    testSubVersion();
    void    testIsMSWindows();
    void    testIsUnix();
    void    testIsMacOS();
    void    testIs16Bits();
    void    testIs32Bits();
    void    testIs64Bits();
    void    testName();
    void    testFullName();


private:

    KSystemVersionUnitTest(const KSystemVersionUnitTest& test);
    KSystemVersionUnitTest&     operator=(const KSystemVersionUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
