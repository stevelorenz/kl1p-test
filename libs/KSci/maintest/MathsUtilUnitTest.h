// KSci - A portable C++ numerical analysis library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KSci C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_MATHSUTILUNITTEST_H
#define KLAB_MATHSUTILUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KMathsUtilUnitTest : public Test::Suite
{
public:
    
    KMathsUtilUnitTest();
    virtual ~KMathsUtilUnitTest();
    
    
protected:

    // Functions tests.
    void    testSqrt();
    void    testExp();
    void    testLog();
    void    testLog2();
    void    testLog10();
    void    testPow();
    void    testConj();


private:

    KMathsUtilUnitTest(const KMathsUtilUnitTest& test);
    KMathsUtilUnitTest&     operator=(const KMathsUtilUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
