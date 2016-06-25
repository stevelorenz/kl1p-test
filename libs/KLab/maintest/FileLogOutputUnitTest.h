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

#ifndef KLAB_FILELOGOUTPUTUNITTEST_H
#define KLAB_FILELOGOUTPUTUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KFileLogOutputUnitTest : public Test::Suite
{
public:
    
    KFileLogOutputUnitTest();
    virtual ~KFileLogOutputUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testPathConstructor();  
    void    testPathAppendConstructor();   
    void    testPathAppendLevelConstructor();   
    void    testPathAppendLevelEnabledConstructor();   

    // Methods tests.
    void    testSetLevel();
    void    testSetEnabled();
    void    testLevel();
    void    testIsEnabled();
    void    testWrite();


private:

    KFileLogOutputUnitTest(const KFileLogOutputUnitTest& test);
    KFileLogOutputUnitTest&     operator=(const KFileLogOutputUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
