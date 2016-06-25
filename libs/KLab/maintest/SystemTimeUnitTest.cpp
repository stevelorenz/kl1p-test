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

#include "SystemTimeUnitTest.h"
#include "../include/SystemTime.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KSystemTimeUnitTest::KSystemTimeUnitTest() : Test::Suite()
{
    TEST_ADD(KSystemTimeUnitTest::testGetTickCount)
    TEST_ADD(KSystemTimeUnitTest::testGetCurrentTimestamp)
    TEST_ADD(KSystemTimeUnitTest::testGetCurrentMillisecTimestamp)
    TEST_ADD(KSystemTimeUnitTest::testGetCurrentMicrosecTimestamp)
    TEST_ADD(KSystemTimeUnitTest::testConvertTimestampToDateTime)
    TEST_ADD(KSystemTimeUnitTest::testConvertMillisecTimestampToDateTime)
    TEST_ADD(KSystemTimeUnitTest::testConvertMicrosecTimestampToDateTime)
    TEST_ADD(KSystemTimeUnitTest::testGetWeekDayFromDate)
    TEST_ADD(KSystemTimeUnitTest::testIsValidDateTime)
    TEST_ADD(KSystemTimeUnitTest::testCompareDateTimes)
}

// ---------------------------------------------------------------------------------------------------- //

KSystemTimeUnitTest::~KSystemTimeUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testGetTickCount()
{
    try
    {
        KMicrosecTime tick = KSystemTime::GetTickCount();
        TEST_ASSERT(tick > 0)

        klab::Sleep(50);
        KMicrosecTime tick2 = KSystemTime::GetTickCount();
        KMicrosecTime diff = tick2 - tick;
        TEST_ASSERT(tick2 > tick)
        TEST_ASSERT(diff >= 40000)
        TEST_ASSERT(diff < 100000)

        klab::Sleep(100);
        KMicrosecTime tick3 = KSystemTime::GetTickCount();
        diff = tick3 - tick2;
        TEST_ASSERT(tick3 > tick2)
        TEST_ASSERT(diff >= 90000)
        TEST_ASSERT(diff < 200000)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testGetCurrentTimestamp()
{
    try
    {
        klab::UInt16 year  = 0;
        klab::UInt8 month  = 0;
        klab::UInt8 day    = 0;
        klab::UInt8 hour   = 0;
        klab::UInt8 minute = 0;
        klab::UInt8 second = 0;

        klab::KTimestamp timestamp = KSystemTime::GetCurrentTimestamp();
        TEST_ASSERT(timestamp > 1336502000)

        KSystemTime::ConvertTimestampToDateTime(timestamp, false, year, month, day, hour, minute, second);
        TEST_ASSERT(year >= 2012)
        TEST_ASSERT(month>0 && month<=12)
        TEST_ASSERT(day>0 && day<=31)
        TEST_ASSERT(hour < 24)
        TEST_ASSERT(minute < 60)
        TEST_ASSERT(second < 60)

        klab::Sleep(1500);
        klab::KTimestamp timestamp2 = KSystemTime::GetCurrentTimestamp();
        TEST_ASSERT(timestamp2 > timestamp)
        TEST_ASSERT(timestamp2-timestamp >= 1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testGetCurrentMillisecTimestamp()
{
    try
    {
        klab::UInt16 year  = 0;
        klab::UInt8 month  = 0;
        klab::UInt8 day    = 0;
        klab::UInt8 hour   = 0;
        klab::UInt8 minute = 0;
        klab::UInt8 second = 0;
        klab::UInt16 millisec = 0;

        klab::KMillisecTimestamp timestamp = KSystemTime::GetCurrentMillisecTimestamp();
        TEST_ASSERT(timestamp > 1336502000000LL)

        KSystemTime::ConvertMillisecTimestampToDateTime(timestamp, false, year, month, day, hour, minute, second, millisec);
        TEST_ASSERT(year >= 2012)
        TEST_ASSERT(month>0 && month<=12)
        TEST_ASSERT(day>0 && day<=31)
        TEST_ASSERT(hour < 24)
        TEST_ASSERT(minute < 60)
        TEST_ASSERT(second < 60)
        TEST_ASSERT(millisec < 1000)

        klab::Sleep(1000);
        klab::KMillisecTimestamp timestamp2 = KSystemTime::GetCurrentMillisecTimestamp();
        TEST_ASSERT(timestamp2 > timestamp)
        TEST_ASSERT(timestamp2-timestamp >= 900)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testGetCurrentMicrosecTimestamp()
{
    try
    {
        klab::UInt16 year  = 0;
        klab::UInt8 month  = 0;
        klab::UInt8 day    = 0;
        klab::UInt8 hour   = 0;
        klab::UInt8 minute = 0;
        klab::UInt8 second = 0;
        klab::UInt16 millisec = 0;
        klab::UInt16 microsec = 0;

        klab::KMicrosecTimestamp timestamp = KSystemTime::GetCurrentMicrosecTimestamp();
        TEST_ASSERT(timestamp > 1336502000000000LL)

        KSystemTime::ConvertMicrosecTimestampToDateTime(timestamp, false, year, month, day, hour, minute, second, millisec, microsec);
        TEST_ASSERT(year >= 2012)
        TEST_ASSERT(month>0 && month<=12)
        TEST_ASSERT(day>0 && day<=31)
        TEST_ASSERT(hour < 24)
        TEST_ASSERT(minute < 60)
        TEST_ASSERT(second < 60)
        TEST_ASSERT(millisec < 1000)
        TEST_ASSERT(microsec < 1000)

        klab::Sleep(1000);
        klab::KMicrosecTimestamp timestamp2 = KSystemTime::GetCurrentMicrosecTimestamp();
        TEST_ASSERT(timestamp2 > timestamp)
        TEST_ASSERT(timestamp2-timestamp >= 900000)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testConvertTimestampToDateTime()
{
    try
    {
        klab::UInt16 year  = 0;
        klab::UInt8 month  = 0;
        klab::UInt8 day    = 0;
        klab::UInt8 hour   = 0;
        klab::UInt8 minute = 0;
        klab::UInt8 second = 0;

        KSystemTime::ConvertTimestampToDateTime(0, false, year, month, day, hour, minute, second);
        TEST_ASSERT(year   == 1970)
        TEST_ASSERT(month  == 1)
        TEST_ASSERT(day    == 1)
        TEST_ASSERT(hour   == 0)
        TEST_ASSERT(minute == 0)
        TEST_ASSERT(second == 0)

        KSystemTime::ConvertTimestampToDateTime(1000000000, false, year, month, day, hour, minute, second);
        TEST_ASSERT(year   == 2001)
        TEST_ASSERT(month  == 9)
        TEST_ASSERT(day    == 9)
        TEST_ASSERT(hour   == 1)
        TEST_ASSERT(minute == 46)
        TEST_ASSERT(second == 40)

        KSystemTime::ConvertTimestampToDateTime(1336420705, false, year, month, day, hour, minute, second);
        TEST_ASSERT(year   == 2012)
        TEST_ASSERT(month  == 5)
        TEST_ASSERT(day    == 7)
        TEST_ASSERT(hour   == 19)
        TEST_ASSERT(minute == 58)
        TEST_ASSERT(second == 25)        

        KSystemTime::ConvertTimestampToDateTime(KSystemTime::GetCurrentTimestamp(), false, year, month, day, hour, minute, second);
        TEST_ASSERT(year >= 2012)
        TEST_ASSERT(month>0 && month<=12)
        TEST_ASSERT(day>0 && day<=31)
        TEST_ASSERT(hour < 24)
        TEST_ASSERT(minute < 60)
        TEST_ASSERT(second < 60)

/*      // Only valid on GMT+1 time-zone !
        KSystemTime::ConvertTimestampToDateTime(0, true, year, month, day, hour, minute, second);
        TEST_ASSERT(year   == 1970)
        TEST_ASSERT(month  == 1)
        TEST_ASSERT(day    == 1)
        TEST_ASSERT(hour   == 1)
        TEST_ASSERT(minute == 0)
        TEST_ASSERT(second == 0)

        KSystemTime::ConvertTimestampToDateTime(1000000000, true, year, month, day, hour, minute, second);
        TEST_ASSERT(year   == 2001)
        TEST_ASSERT(month  == 9)
        TEST_ASSERT(day    == 9)
        TEST_ASSERT(hour   == 3)
        TEST_ASSERT(minute == 46)
        TEST_ASSERT(second == 40)

        KSystemTime::ConvertTimestampToDateTime(1336420705, true, year, month, day, hour, minute, second);
        TEST_ASSERT(year   == 2012)
        TEST_ASSERT(month  == 5)
        TEST_ASSERT(day    == 7)
        TEST_ASSERT(hour   == 21)
        TEST_ASSERT(minute == 58)
        TEST_ASSERT(second == 25)
*/
        KSystemTime::ConvertTimestampToDateTime(KSystemTime::GetCurrentTimestamp(), true, year, month, day, hour, minute, second);
        TEST_ASSERT(year >= 2012)
        TEST_ASSERT(month>0 && month<=12)
        TEST_ASSERT(day>0 && day<=31)
        TEST_ASSERT(hour < 24)
        TEST_ASSERT(minute < 60)
        TEST_ASSERT(second < 60)


        // Limit cases.
        try                             {KSystemTime::ConvertTimestampToDateTime(-1, false, year, month, day, hour, minute, second); TEST_ASSERT(false)}
        catch(KSystemTimeException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        try                             {KSystemTime::ConvertTimestampToDateTime(-1, true, year, month, day, hour, minute, second); TEST_ASSERT(false)}
        catch(KSystemTimeException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testConvertMillisecTimestampToDateTime()
{
    try
    {
        klab::UInt16 year  = 0;
        klab::UInt8 month  = 0;
        klab::UInt8 day    = 0;
        klab::UInt8 hour   = 0;
        klab::UInt8 minute = 0;
        klab::UInt8 second = 0;
        klab::UInt16 millisec = 0;

        KSystemTime::ConvertMillisecTimestampToDateTime(0, false, year, month, day, hour, minute, second, millisec);
        TEST_ASSERT(year   == 1970)
        TEST_ASSERT(month  == 1)
        TEST_ASSERT(day    == 1)
        TEST_ASSERT(hour   == 0)
        TEST_ASSERT(minute == 0)
        TEST_ASSERT(second == 0)
        TEST_ASSERT(millisec == 0)

        KSystemTime::ConvertMillisecTimestampToDateTime(1000000000123LL, false, year, month, day, hour, minute, second, millisec);
        TEST_ASSERT(year   == 2001)
        TEST_ASSERT(month  == 9)
        TEST_ASSERT(day    == 9)
        TEST_ASSERT(hour   == 1)
        TEST_ASSERT(minute == 46)
        TEST_ASSERT(second == 40)
        TEST_ASSERT(millisec == 123)

        KSystemTime::ConvertMillisecTimestampToDateTime(1336420705456LL, false, year, month, day, hour, minute, second, millisec);
        TEST_ASSERT(year   == 2012)
        TEST_ASSERT(month  == 5)
        TEST_ASSERT(day    == 7)
        TEST_ASSERT(hour   == 19)
        TEST_ASSERT(minute == 58)
        TEST_ASSERT(second == 25)      
        TEST_ASSERT(millisec == 456)

        KSystemTime::ConvertMillisecTimestampToDateTime(KSystemTime::GetCurrentMillisecTimestamp(), false, year, month, day, hour, minute, second, millisec);
        TEST_ASSERT(year >= 2012)
        TEST_ASSERT(month>0 && month<=12)
        TEST_ASSERT(day>0 && day<=31)
        TEST_ASSERT(hour < 24)
        TEST_ASSERT(minute < 60)
        TEST_ASSERT(second < 60)
        TEST_ASSERT(millisec < 1000)

/*      // Only valid on GMT+1 time-zone !
        KSystemTime::ConvertMillisecTimestampToDateTime(0, true, year, month, day, hour, minute, second, millisec);
        TEST_ASSERT(year   == 1970)
        TEST_ASSERT(month  == 1)
        TEST_ASSERT(day    == 1)
        TEST_ASSERT(hour   == 1)
        TEST_ASSERT(minute == 0)
        TEST_ASSERT(second == 0)
        TEST_ASSERT(millisec == 0)

        KSystemTime::ConvertMillisecTimestampToDateTime(1000000000123LL, true, year, month, day, hour, minute, second, millisec);
        TEST_ASSERT(year   == 2001)
        TEST_ASSERT(month  == 9)
        TEST_ASSERT(day    == 9)
        TEST_ASSERT(hour   == 3)
        TEST_ASSERT(minute == 46)
        TEST_ASSERT(second == 40)
        TEST_ASSERT(millisec == 123)

        KSystemTime::ConvertMillisecTimestampToDateTime(1336420705456LL, true, year, month, day, hour, minute, second, millisec);
        TEST_ASSERT(year   == 2012)
        TEST_ASSERT(month  == 5)
        TEST_ASSERT(day    == 7)
        TEST_ASSERT(hour   == 21)
        TEST_ASSERT(minute == 58)
        TEST_ASSERT(second == 25)
        TEST_ASSERT(millisec == 456)
*/
        KSystemTime::ConvertMillisecTimestampToDateTime(KSystemTime::GetCurrentMillisecTimestamp(), true, year, month, day, hour, minute, second, millisec);
        TEST_ASSERT(year >= 2012)
        TEST_ASSERT(month>0 && month<=12)
        TEST_ASSERT(day>0 && day<=31)
        TEST_ASSERT(hour < 24)
        TEST_ASSERT(minute < 60)
        TEST_ASSERT(second < 60)
        TEST_ASSERT(millisec < 1000)


        // Limit cases.
        try                             {KSystemTime::ConvertMillisecTimestampToDateTime(-1, false, year, month, day, hour, minute, second, millisec); TEST_ASSERT(false)}
        catch(KSystemTimeException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        try                             {KSystemTime::ConvertMillisecTimestampToDateTime(-1, true, year, month, day, hour, minute, second, millisec); TEST_ASSERT(false)}
        catch(KSystemTimeException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testConvertMicrosecTimestampToDateTime()
{
    try
    {
        klab::UInt16 year  = 0;
        klab::UInt8 month  = 0;
        klab::UInt8 day    = 0;
        klab::UInt8 hour   = 0;
        klab::UInt8 minute = 0;
        klab::UInt8 second = 0;
        klab::UInt16 millisec = 0;
        klab::UInt16 microsec = 0;

        KSystemTime::ConvertMicrosecTimestampToDateTime(0, false, year, month, day, hour, minute, second, millisec, microsec);
        TEST_ASSERT(year   == 1970)
        TEST_ASSERT(month  == 1)
        TEST_ASSERT(day    == 1)
        TEST_ASSERT(hour   == 0)
        TEST_ASSERT(minute == 0)
        TEST_ASSERT(second == 0)
        TEST_ASSERT(millisec == 0)
        TEST_ASSERT(microsec == 0)

        KSystemTime::ConvertMicrosecTimestampToDateTime(1000000000123456LL, false, year, month, day, hour, minute, second, millisec, microsec);
        TEST_ASSERT(year   == 2001)
        TEST_ASSERT(month  == 9)
        TEST_ASSERT(day    == 9)
        TEST_ASSERT(hour   == 1)
        TEST_ASSERT(minute == 46)
        TEST_ASSERT(second == 40)
        TEST_ASSERT(millisec == 123)
        TEST_ASSERT(microsec == 456)

        KSystemTime::ConvertMicrosecTimestampToDateTime(1336420705456032LL, false, year, month, day, hour, minute, second, millisec, microsec);
        TEST_ASSERT(year   == 2012)
        TEST_ASSERT(month  == 5)
        TEST_ASSERT(day    == 7)
        TEST_ASSERT(hour   == 19)
        TEST_ASSERT(minute == 58)
        TEST_ASSERT(second == 25)      
        TEST_ASSERT(millisec == 456)
        TEST_ASSERT(microsec == 32)

        KSystemTime::ConvertMicrosecTimestampToDateTime(KSystemTime::GetCurrentMicrosecTimestamp(), false, year, month, day, hour, minute, second, millisec, microsec);
        TEST_ASSERT(year >= 2012)
        TEST_ASSERT(month>0 && month<=12)
        TEST_ASSERT(day>0 && day<=31)
        TEST_ASSERT(hour < 24)
        TEST_ASSERT(minute < 60)
        TEST_ASSERT(second < 60)
        TEST_ASSERT(millisec < 1000)
        TEST_ASSERT(microsec < 1000)

/*      // Only valid on GMT+1 time-zone !
        KSystemTime::ConvertMicrosecTimestampToDateTime(0, true, year, month, day, hour, minute, second, millisec, microsec);
        TEST_ASSERT(year   == 1970)
        TEST_ASSERT(month  == 1)
        TEST_ASSERT(day    == 1)
        TEST_ASSERT(hour   == 1)
        TEST_ASSERT(minute == 0)
        TEST_ASSERT(second == 0)
        TEST_ASSERT(millisec == 0)
        TEST_ASSERT(microsec == 0)

        KSystemTime::ConvertMicrosecTimestampToDateTime(1000000000123456, true, year, month, day, hour, minute, second, millisec, microsec);
        TEST_ASSERT(year   == 2001)
        TEST_ASSERT(month  == 9)
        TEST_ASSERT(day    == 9)
        TEST_ASSERT(hour   == 3)
        TEST_ASSERT(minute == 46)
        TEST_ASSERT(second == 40)
        TEST_ASSERT(millisec == 123)
        TEST_ASSERT(microsec == 456)

        KSystemTime::ConvertMicrosecTimestampToDateTime(1336420705456032, true, year, month, day, hour, minute, second, millisec, microsec);
        TEST_ASSERT(year   == 2012)
        TEST_ASSERT(month  == 5)
        TEST_ASSERT(day    == 7)
        TEST_ASSERT(hour   == 21)
        TEST_ASSERT(minute == 58)
        TEST_ASSERT(second == 25)
        TEST_ASSERT(millisec == 456)
        TEST_ASSERT(microsec == 32)
*/
        KSystemTime::ConvertMicrosecTimestampToDateTime(KSystemTime::GetCurrentMicrosecTimestamp(), true, year, month, day, hour, minute, second, millisec, microsec);
        TEST_ASSERT(year >= 2012)
        TEST_ASSERT(month>0 && month<=12)
        TEST_ASSERT(day>0 && day<=31)
        TEST_ASSERT(hour < 24)
        TEST_ASSERT(minute < 60)
        TEST_ASSERT(second < 60)
        TEST_ASSERT(millisec < 1000)
        TEST_ASSERT(microsec < 1000)


        // Limit cases.
        try                             {KSystemTime::ConvertMicrosecTimestampToDateTime(-1, false, year, month, day, hour, minute, second, millisec, microsec); TEST_ASSERT(false)}
        catch(KSystemTimeException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        try                             {KSystemTime::ConvertMicrosecTimestampToDateTime(-1, true, year, month, day, hour, minute, second, millisec, microsec); TEST_ASSERT(false)}
        catch(KSystemTimeException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testGetWeekDayFromDate()
{
    try
    {
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 6)  == 0)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 7)  == 1)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 8)  == 2)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 9)  == 3)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 10) == 4)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 11) == 5)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 12) == 6)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 13) == 0)
        
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 6)  == klab::SUNDAY)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 7)  == klab::MONDAY)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 8)  == klab::TUESDAY)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 9)  == klab::WEDNESDAY)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 10) == klab::THURSDAY)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 11) == klab::FRIDAY)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 12) == klab::SATURDAY)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 13) == klab::SUNDAY)


        // Limit cases.
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 32) == 7)
        TEST_ASSERT(KSystemTime::GetWeekDayFromDate(2012, 5, 32) == klab::BAD_WEEKDAY)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testIsValidDateTime()
{
    try
    {
        TEST_ASSERT(KSystemTime::IsValidDateTime(1970, 1, 1, 0, 0, 0, 0, 0) == true)
        TEST_ASSERT(KSystemTime::IsValidDateTime(2001, 9, 9, 1, 46, 40, 0, 0) == true)
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 5, 8, 12, 31, 9, 56, 753) == true) 	
        TEST_ASSERT(KSystemTime::IsValidDateTime(2037, 12, 31, 23, 59, 59, 999, 999) == true) 

        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 5, 8, 12, 31, 9, 56, 1000) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 5, 8, 12, 31, 9, 1000, 753) == false)
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 5, 8, 12, 31, 60, 56, 753) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 5, 8, 12, 60, 9, 56, 753) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 5, 8, 24, 31, 9, 56, 753) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 5, 0, 12, 31, 9, 56, 753) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 5, 32, 13, 31, 9, 56, 753) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 4, 31, 12, 31, 9, 56, 753) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 2, 30, 12, 31, 9, 56, 753) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 0, 8, 12, 31, 9, 56, 753) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(2012, 13, 8, 12, 31, 9, 56, 753) == false) 
        TEST_ASSERT(KSystemTime::IsValidDateTime(1969, 5, 8, 12, 31, 9, 56, 753) == false) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSystemTimeUnitTest::testCompareDateTimes()
{
    try
    {
        klab::Int64 diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 30, 0, 0, 2009, 2, 13, 23, 31, 29, 999, 999);
        TEST_ASSERT(diff == 1)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 30, 0, 0, 2009, 2, 13, 23, 31, 30, 0, 0);
        TEST_ASSERT(diff == 0)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 29, 999, 999, 2009, 2, 13, 23, 31, 29, 999, 999);
        TEST_ASSERT(diff == 0)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 30, 0, 0, 2009, 2, 13, 23, 31, 30, 0, 1);
        TEST_ASSERT(diff == -1)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 30, 0, 1, 2009, 2, 13, 23, 31, 29, 999, 999);
        TEST_ASSERT(diff == 2)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 29, 999, 999, 2009, 2, 13, 23, 31, 30, 0, 1);
        TEST_ASSERT(diff == -2)


        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 30, 0, 0, 2009, 2, 13, 23, 31, 29, 999, 0);
        TEST_ASSERT(diff == 1000)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 30, 0, 0, 2009, 2, 13, 23, 31, 30, 1, 0);
        TEST_ASSERT(diff == -1000)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 30, 1, 0, 2009, 2, 13, 23, 31, 29, 999, 0);
        TEST_ASSERT(diff == 2000)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 29, 999, 0, 2009, 2, 13, 23, 31, 30, 1, 0);
        TEST_ASSERT(diff == -2000)

        
        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 30, 0, 0, 2009, 2, 13, 23, 31, 29, 0, 0);
        TEST_ASSERT(diff == 1000000)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 30, 0, 0, 2009, 2, 13, 23, 31, 31, 0, 0);
        TEST_ASSERT(diff == -1000000)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 31, 0, 0, 2009, 2, 13, 23, 31, 29, 0, 0);
        TEST_ASSERT(diff == 2000000)

        diff = KSystemTime::CompareDateTimes(2009, 2, 13, 23, 31, 29, 0, 0, 2009, 2, 13, 23, 31, 31, 0, 0);
        TEST_ASSERT(diff == -2000000)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
