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

#ifndef KLAB_TIMERUNITTEST_H
#define KLAB_TIMERUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KTimerUnitTest : public Test::Suite
{
public:
    
    KTimerUnitTest();
    virtual ~KTimerUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testStart();
    void    testSuspend();
    void    testResume();
    void    testStop();
    void    testReset();
    void    testIsStarted();
    void    testIsSuspended();
    void    testIsRunning();
    void    testDuration();
    void    testDurationInMicroseconds();
    void    testDurationInMilliseconds();
    void    testDurationInSeconds();


private:

    KTimerUnitTest(const KTimerUnitTest& test);
    KTimerUnitTest&     operator=(const KTimerUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
