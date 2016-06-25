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

#ifndef KLAB_EXCEPTIONUNITTEST_H
#define KLAB_EXCEPTIONUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KExceptionUnitTest : public Test::Suite
{
public:
    
    KExceptionUnitTest();
    virtual ~KExceptionUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();
    void    testErrorCodeMessageFileLineFunctionConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Getters/Setters tests.
    void    testErrorCode();
    void    testWhat();
    void    testFile();
    void    testLine();
    void    testFunction();

    // Functions tests.
    void    testThrowExceptionIf();
    void    testThrowExceptionIfNot();
    void    testThrowException();
    void    testThrowTraceExceptionIf();
    void    testThrowTraceExceptionIfNot();
    void    testThrowTraceException();
    void    testFormatExceptionToString();


private:

    KExceptionUnitTest(const KExceptionUnitTest& test);
    KExceptionUnitTest&     operator=(const KExceptionUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
