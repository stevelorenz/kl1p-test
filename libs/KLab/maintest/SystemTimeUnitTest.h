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

#ifndef KLAB_SYSTEMTIMEUNITTEST_H
#define KLAB_SYSTEMTIMEUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KSystemTimeUnitTest : public Test::Suite
{
public:
    
    KSystemTimeUnitTest();
    virtual ~KSystemTimeUnitTest();
    
    
protected:

    // Static functions tests.
    void    testGetTickCount();
    void    testGetCurrentTimestamp();
    void    testGetCurrentMillisecTimestamp();
    void    testGetCurrentMicrosecTimestamp();
    void    testConvertTimestampToDateTime();
    void    testConvertMillisecTimestampToDateTime();
    void    testConvertMicrosecTimestampToDateTime();
    void    testGetWeekDayFromDate();
    void    testIsValidDateTime();
    void    testCompareDateTimes();


private:

    KSystemTimeUnitTest(const KSystemTimeUnitTest& test);
    KSystemTimeUnitTest&    operator=(const KSystemTimeUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
