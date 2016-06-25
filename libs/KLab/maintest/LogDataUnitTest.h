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

#ifndef KLAB_LOGDATAUNITTEST_H
#define KLAB_LOGDATAUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KLogDataUnitTest : public Test::Suite
{
public:
    
    KLogDataUnitTest();
    virtual ~KLogDataUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();  
    void    testLevelConstructor();   
    void    testLevelMessageConstructor();   
    void    testLevelMessageTimestampConstructor(); 
    void    testLevelFileLineFunctionConstructor();
    void    testLevelMessageFileLineFunctionConstructor();
    void    testLevelMessageTimestampFileLineFunctionConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testSet();
    void    testSetLevel();
    void    testSetMessage();
    void    testSetTimestamp();
    void    testUpdateTimestamp();
    void    testSetFile();
    void    testSetLine();
    void    testSetFunction();
    void    testLevel();
    void    testMessage();
    void    testTimestamp();
    void    testFile();
    void    testLine();
    void    testFunction();
    void    testLevelToString();
    void    testTimestampToString();
    void    testLineToString();
    void    testToString();
    void    testToFullString();


private:

    KLogDataUnitTest(const KLogDataUnitTest& test);
    KLogDataUnitTest&   operator=(const KLogDataUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
