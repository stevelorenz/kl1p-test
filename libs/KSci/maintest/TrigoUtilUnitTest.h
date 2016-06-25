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

#ifndef KLAB_TRIGOUTILUNITTEST_H
#define KLAB_TRIGOUTILUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KTrigoUtilUnitTest : public Test::Suite
{
public:
    
    KTrigoUtilUnitTest();
    virtual ~KTrigoUtilUnitTest();
    
    
protected:

    // Functions tests.
    void    testCos();
    void    testCosH();
    void    testACos();
    void    testSin();
    void    testSinH();
    void    testASin();
    void    testTan();
    void    testTanH();        
    void    testATan();
    void    testATan2();


private:

    KTrigoUtilUnitTest(const KTrigoUtilUnitTest& test);
    KTrigoUtilUnitTest&    operator=(const KTrigoUtilUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
