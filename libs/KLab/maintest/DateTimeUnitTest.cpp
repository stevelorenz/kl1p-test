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

#include "DateTimeUnitTest.h"
#include "../include/DateTime.h"
#include "../include/StringUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KDateTimeUnitTest::KDateTimeUnitTest() : Test::Suite()
{
    TEST_ADD(KDateTimeUnitTest::testDefaultConstructor)  
    TEST_ADD(KDateTimeUnitTest::testLocalConstructor) 
    TEST_ADD(KDateTimeUnitTest::testTimestampConstructor)  
    TEST_ADD(KDateTimeUnitTest::testDateConstructor)  
    TEST_ADD(KDateTimeUnitTest::testCopyConstructor)
    TEST_ADD(KDateTimeUnitTest::testAffectationOperator)

    TEST_ADD(KDateTimeUnitTest::testEqualOperator)
    TEST_ADD(KDateTimeUnitTest::testNotEqualOperator)
    TEST_ADD(KDateTimeUnitTest::testLessOperator)
    TEST_ADD(KDateTimeUnitTest::testLessOrEqualOperator)
    TEST_ADD(KDateTimeUnitTest::testGreaterOrEqualOperator)
    TEST_ADD(KDateTimeUnitTest::testGreaterOperator)
    TEST_ADD(KDateTimeUnitTest::testSubtractionOperator)

    TEST_ADD(KDateTimeUnitTest::testClear)
    TEST_ADD(KDateTimeUnitTest::testNow)
    TEST_ADD(KDateTimeUnitTest::testYear)
    TEST_ADD(KDateTimeUnitTest::testMonth)
    TEST_ADD(KDateTimeUnitTest::testDay)
    TEST_ADD(KDateTimeUnitTest::testWeekday)
    TEST_ADD(KDateTimeUnitTest::testHour)
    TEST_ADD(KDateTimeUnitTest::testMinute)
    TEST_ADD(KDateTimeUnitTest::testSecond)
    TEST_ADD(KDateTimeUnitTest::testMilliseconds)
    TEST_ADD(KDateTimeUnitTest::testMicroseconds)
    TEST_ADD(KDateTimeUnitTest::testIsValid)
    TEST_ADD(KDateTimeUnitTest::testEquals)
    TEST_ADD(KDateTimeUnitTest::testCompare)
    TEST_ADD(KDateTimeUnitTest::testToString)
}

// ---------------------------------------------------------------------------------------------------- //

KDateTimeUnitTest::~KDateTimeUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testDefaultConstructor()
{
    try
    {
        KDateTime date;
        TEST_ASSERT(date.year() == 1970)
        TEST_ASSERT(date.month() == 1)
        TEST_ASSERT(date.day() == 1)
        TEST_ASSERT(date.weekday() == 4)
        TEST_ASSERT(date.hour() == 0)
        TEST_ASSERT(date.minute() == 0)
        TEST_ASSERT(date.second() == 0)
        TEST_ASSERT(date.milliseconds() == 0)
        TEST_ASSERT(date.microseconds() == 0)
        TEST_ASSERT(date.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testLocalConstructor() 
{
    try
    {
        KDateTime date(false);
        TEST_ASSERT(date.year() >= 2012)
        TEST_ASSERT(date.month()>0 && date.month()<=12)
        TEST_ASSERT(date.day()>0 && date.day()<=31)
        TEST_ASSERT(date.weekday() < 7)
        TEST_ASSERT(date.hour() < 24)
        TEST_ASSERT(date.minute() < 60)
        TEST_ASSERT(date.second() < 60)
        TEST_ASSERT(date.milliseconds() < 1000)
        TEST_ASSERT(date.microseconds() < 1000)
        TEST_ASSERT(date.isValid())

        KDateTime date2(true);
        TEST_ASSERT(date2.year() >= 2012)
        TEST_ASSERT(date2.month()>0 && date2.month()<=12)
        TEST_ASSERT(date2.day()>0 && date2.day()<=31)
        TEST_ASSERT(date2.weekday() < 7)
        TEST_ASSERT(date2.hour() < 24)
        TEST_ASSERT(date2.minute() < 60)
        TEST_ASSERT(date2.second() < 60)
        TEST_ASSERT(date2.milliseconds() < 1000)
        TEST_ASSERT(date2.microseconds() < 1000)
        TEST_ASSERT(date2.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testTimestampConstructor() 
{
    try
    {
        KDateTime date(KSystemTime::GetCurrentMicrosecTimestamp());
        TEST_ASSERT(date.year() >= 2012)
        TEST_ASSERT(date.month()>0 && date.month()<=12)
        TEST_ASSERT(date.day()>0 && date.day()<=31)
        TEST_ASSERT(date.weekday() < 7)
        TEST_ASSERT(date.hour() < 24)
        TEST_ASSERT(date.minute() < 60)
        TEST_ASSERT(date.second() < 60)
        TEST_ASSERT(date.milliseconds() < 1000)
        TEST_ASSERT(date.microseconds() < 1000)
        TEST_ASSERT(date.isValid())

        KDateTime date2(KSystemTime::GetCurrentMicrosecTimestamp(), false);
        TEST_ASSERT(date2.year() >= 2012)
        TEST_ASSERT(date2.month()>0 && date2.month()<=12)
        TEST_ASSERT(date2.day()>0 && date2.day()<=31)
        TEST_ASSERT(date2.weekday() < 7)
        TEST_ASSERT(date2.hour() < 24)
        TEST_ASSERT(date2.minute() < 60)
        TEST_ASSERT(date2.second() < 60)
        TEST_ASSERT(date2.milliseconds() < 1000)
        TEST_ASSERT(date2.microseconds() < 1000)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(KSystemTime::GetCurrentMicrosecTimestamp(), true);
        TEST_ASSERT(date3.year() >= 2012)
        TEST_ASSERT(date3.month()>0 && date3.month()<=12)
        TEST_ASSERT(date3.day()>0 && date3.day()<=31)
        TEST_ASSERT(date3.weekday() < 7)
        TEST_ASSERT(date3.hour() < 24)
        TEST_ASSERT(date3.minute() < 60)
        TEST_ASSERT(date3.second() < 60)
        TEST_ASSERT(date3.milliseconds() < 1000)
        TEST_ASSERT(date3.microseconds() < 1000)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(0, false);
        TEST_ASSERT(date4.year() == 1970)
        TEST_ASSERT(date4.month() == 1)
        TEST_ASSERT(date4.day() == 1)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 0)
        TEST_ASSERT(date4.minute() == 0)
        TEST_ASSERT(date4.second() == 0)
        TEST_ASSERT(date4.milliseconds() == 0)
        TEST_ASSERT(date4.microseconds() == 0)
        TEST_ASSERT(date4.isValid())

        KDateTime date5(1000000000123456LL, false);
        TEST_ASSERT(date5.year() == 2001)
        TEST_ASSERT(date5.month() == 9)
        TEST_ASSERT(date5.day() == 9)
        TEST_ASSERT(date5.weekday() == 0)
        TEST_ASSERT(date5.hour() == 1)
        TEST_ASSERT(date5.minute() == 46)
        TEST_ASSERT(date5.second() == 40)
        TEST_ASSERT(date5.milliseconds() == 123)
        TEST_ASSERT(date5.microseconds() == 456)
        TEST_ASSERT(date5.isValid())


        // Limit cases.
        try                             {KDateTime date0(klab::KMicrosecTimestamp(-1)); TEST_ASSERT(false)}
        catch(KSystemTimeException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        try                             {KDateTime date0(-1, false); TEST_ASSERT(false)}
        catch(KSystemTimeException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}

        try                             {KDateTime date0(-1, true); TEST_ASSERT(false)}
        catch(KSystemTimeException&)    {TEST_ASSERT(true)}
        catch(...)                      {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
 
void KDateTimeUnitTest::testDateConstructor()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

		KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
		TEST_ASSERT(date4.year() == 2037)
		TEST_ASSERT(date4.month() == 12)
		TEST_ASSERT(date4.day() == 31)
		TEST_ASSERT(date4.weekday() == 4)
		TEST_ASSERT(date4.hour() == 23)
		TEST_ASSERT(date4.minute() == 59)
		TEST_ASSERT(date4.second() == 59)
		TEST_ASSERT(date4.milliseconds() == 999)
		TEST_ASSERT(date4.microseconds() == 999)
		TEST_ASSERT(date4.isValid())


        // Limit cases.
        KDateTime date01(2012, 5, 8, 12, 31, 9, 56, 1000);
        TEST_ASSERT(date01.year() == 2012)
        TEST_ASSERT(date01.month() == 5)
        TEST_ASSERT(date01.day() == 8)
        TEST_ASSERT(date01.weekday() == 2)
        TEST_ASSERT(date01.hour() == 12)
        TEST_ASSERT(date01.minute() == 31)
        TEST_ASSERT(date01.second() == 9)
        TEST_ASSERT(date01.milliseconds() == 56)
        TEST_ASSERT(date01.microseconds() == 1000)
        TEST_ASSERT(date01.isValid() == false)

        KDateTime date02(2012, 5, 8, 12, 31, 9, 1000, 753);
        TEST_ASSERT(date02.year() == 2012)
        TEST_ASSERT(date02.month() == 5)
        TEST_ASSERT(date02.day() == 8)
        TEST_ASSERT(date02.weekday() == 2)
        TEST_ASSERT(date02.hour() == 12)
        TEST_ASSERT(date02.minute() == 31)
        TEST_ASSERT(date02.second() == 9)
        TEST_ASSERT(date02.milliseconds() == 1000)
        TEST_ASSERT(date02.microseconds() == 753)
        TEST_ASSERT(date02.isValid() == false)

        KDateTime date03(2012, 5, 8, 12, 31, 60, 56, 753);
        TEST_ASSERT(date03.year() == 2012)
        TEST_ASSERT(date03.month() == 5)
        TEST_ASSERT(date03.day() == 8)
        TEST_ASSERT(date03.weekday() == 2)
        TEST_ASSERT(date03.hour() == 12)
        TEST_ASSERT(date03.minute() == 31)
        TEST_ASSERT(date03.second() == 60)
        TEST_ASSERT(date03.milliseconds() == 56)
        TEST_ASSERT(date03.microseconds() == 753)
        TEST_ASSERT(date03.isValid() == false)

        KDateTime date04(2012, 5, 8, 12, 60, 9, 56, 753);
        TEST_ASSERT(date04.year() == 2012)
        TEST_ASSERT(date04.month() == 5)
        TEST_ASSERT(date04.day() == 8)
        TEST_ASSERT(date04.weekday() == 2)
        TEST_ASSERT(date04.hour() == 12)
        TEST_ASSERT(date04.minute() == 60)
        TEST_ASSERT(date04.second() == 9)
        TEST_ASSERT(date04.milliseconds() == 56)
        TEST_ASSERT(date04.microseconds() == 753)
        TEST_ASSERT(date04.isValid() == false)

        KDateTime date05(2012, 5, 8, 24, 31, 9, 56, 753);
        TEST_ASSERT(date05.year() == 2012)
        TEST_ASSERT(date05.month() == 5)
        TEST_ASSERT(date05.day() == 8)
        TEST_ASSERT(date05.weekday() == 2)
        TEST_ASSERT(date05.hour() == 24)
        TEST_ASSERT(date05.minute() == 31)
        TEST_ASSERT(date05.second() == 9)
        TEST_ASSERT(date05.milliseconds() == 56)
        TEST_ASSERT(date05.microseconds() == 753)
        TEST_ASSERT(date05.isValid() == false)

        KDateTime date06(2012, 5, 0, 12, 31, 9, 56, 753);
        TEST_ASSERT(date06.year() == 2012)
        TEST_ASSERT(date06.month() == 5)
        TEST_ASSERT(date06.day() == 0)
        TEST_ASSERT(date06.weekday() == 7)
        TEST_ASSERT(date06.hour() == 12)
        TEST_ASSERT(date06.minute() == 31)
        TEST_ASSERT(date06.second() == 9)
        TEST_ASSERT(date06.milliseconds() == 56)
        TEST_ASSERT(date06.microseconds() == 753)
        TEST_ASSERT(date06.isValid() == false)

        KDateTime date07(2012, 5, 32, 13, 31, 9, 56, 753);
        TEST_ASSERT(date07.year() == 2012)
        TEST_ASSERT(date07.month() == 5)
        TEST_ASSERT(date07.day() == 32)
        TEST_ASSERT(date07.weekday() == 7)
        TEST_ASSERT(date07.hour() == 13)
        TEST_ASSERT(date07.minute() == 31)
        TEST_ASSERT(date07.second() == 9)
        TEST_ASSERT(date07.milliseconds() == 56)
        TEST_ASSERT(date07.microseconds() == 753)
        TEST_ASSERT(date07.isValid() == false)

        KDateTime date08(2012, 4, 31, 12, 31, 9, 56, 753);
        TEST_ASSERT(date08.year() == 2012)
        TEST_ASSERT(date08.month() == 4)
        TEST_ASSERT(date08.day() == 31)
        TEST_ASSERT(date08.weekday() == 7)
        TEST_ASSERT(date08.hour() == 12)
        TEST_ASSERT(date08.minute() == 31)
        TEST_ASSERT(date08.second() == 9)
        TEST_ASSERT(date08.milliseconds() == 56)
        TEST_ASSERT(date08.microseconds() == 753)
        TEST_ASSERT(date08.isValid() == false)

        KDateTime date09(2012, 2, 30, 12, 31, 9, 56, 753);
        TEST_ASSERT(date09.year() == 2012)
        TEST_ASSERT(date09.month() == 2)
        TEST_ASSERT(date09.day() == 30)
        TEST_ASSERT(date09.weekday() == 7)
        TEST_ASSERT(date09.hour() == 12)
        TEST_ASSERT(date09.minute() == 31)
        TEST_ASSERT(date09.second() == 9)
        TEST_ASSERT(date09.milliseconds() == 56)
        TEST_ASSERT(date09.microseconds() == 753)
        TEST_ASSERT(date09.isValid() == false)

        KDateTime date010(2012, 0, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date010.year() == 2012)
        TEST_ASSERT(date010.month() == 0)
        TEST_ASSERT(date010.day() == 8)
        TEST_ASSERT(date010.weekday() == 7)
        TEST_ASSERT(date010.hour() == 12)
        TEST_ASSERT(date010.minute() == 31)
        TEST_ASSERT(date010.second() == 9)
        TEST_ASSERT(date010.milliseconds() == 56)
        TEST_ASSERT(date010.microseconds() == 753)
        TEST_ASSERT(date010.isValid() == false)

        KDateTime date011(2012, 13, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date011.year() == 2012)
        TEST_ASSERT(date011.month() == 13)
        TEST_ASSERT(date011.day() == 8)
        TEST_ASSERT(date011.weekday() == 7)
        TEST_ASSERT(date011.hour() == 12)
        TEST_ASSERT(date011.minute() == 31)
        TEST_ASSERT(date011.second() == 9)
        TEST_ASSERT(date011.milliseconds() == 56)
        TEST_ASSERT(date011.microseconds() == 753)
        TEST_ASSERT(date011.isValid() == false)

        KDateTime date012(1969, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date012.year() == 1969)
        TEST_ASSERT(date012.month() == 5)
        TEST_ASSERT(date012.day() == 8)
        TEST_ASSERT(date012.weekday() == 7)
        TEST_ASSERT(date012.hour() == 12)
        TEST_ASSERT(date012.minute() == 31)
        TEST_ASSERT(date012.second() == 9)
        TEST_ASSERT(date012.milliseconds() == 56)
        TEST_ASSERT(date012.microseconds() == 753)
        TEST_ASSERT(date012.isValid() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
  
void KDateTimeUnitTest::testCopyConstructor()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime dateCopy(date);
        TEST_ASSERT(dateCopy.year() == 2012)
        TEST_ASSERT(dateCopy.month() == 5)
        TEST_ASSERT(dateCopy.day() == 8)
        TEST_ASSERT(dateCopy.weekday() == 2)
        TEST_ASSERT(dateCopy.hour() == 12)
        TEST_ASSERT(dateCopy.minute() == 31)
        TEST_ASSERT(dateCopy.second() == 9)
        TEST_ASSERT(dateCopy.milliseconds() == 56)
        TEST_ASSERT(dateCopy.microseconds() == 753)
        TEST_ASSERT(dateCopy.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testAffectationOperator()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime dateCopy;
        dateCopy = date;
        TEST_ASSERT(dateCopy.year() == 2012)
        TEST_ASSERT(dateCopy.month() == 5)
        TEST_ASSERT(dateCopy.day() == 8)
        TEST_ASSERT(dateCopy.weekday() == 2)
        TEST_ASSERT(dateCopy.hour() == 12)
        TEST_ASSERT(dateCopy.minute() == 31)
        TEST_ASSERT(dateCopy.second() == 9)
        TEST_ASSERT(dateCopy.milliseconds() == 56)
        TEST_ASSERT(dateCopy.microseconds() == 753)
        TEST_ASSERT(dateCopy.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testEqualOperator()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date1b(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date2b(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        TEST_ASSERT(date1 == date1)
        TEST_ASSERT(date1b == date1b)
        TEST_ASSERT(date2 == date2)
        TEST_ASSERT(date2b == date2b)
        TEST_ASSERT(date3 == date3)
        TEST_ASSERT(date4 == date4)
        
        TEST_ASSERT((date1==date2)==false && (date2==date1)==false)
        TEST_ASSERT(date1==date1b && date1b==date1)
        TEST_ASSERT((date1==date3)==false && (date3==date1)==false)
        TEST_ASSERT((date1==date4)==false && (date4==date1)==false)
        TEST_ASSERT((date2==date1b)==false && (date1b==date2)==false)
        TEST_ASSERT(date2==date2b && date2b==date2)
        TEST_ASSERT((date2==date3)==false && (date3==date2)==false)
        TEST_ASSERT((date2==date4)==false && (date4==date2)==false)
        TEST_ASSERT((date3==date4)==false && (date4==date3)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testNotEqualOperator()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date1b(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date2b(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        TEST_ASSERT((date1!=date1) == false)
        TEST_ASSERT((date1b!=date1b) == false)
        TEST_ASSERT((date2!=date2) == false)
        TEST_ASSERT((date2b!=date2b) == false)
        TEST_ASSERT((date3!=date3) == false)
        TEST_ASSERT((date4!=date4) == false)
       
        TEST_ASSERT(date1!=date2 && date2!=date1)
        TEST_ASSERT((date1!=date1b)==false && (date1b!=date1)==false)
        TEST_ASSERT(date1!=date3 && date3!=date1)
        TEST_ASSERT(date1!=date4 && date4!=date1)
        TEST_ASSERT(date2!=date1b && date1b!=date2)
        TEST_ASSERT((date2!=date2b)==false && (date2b!=date2)==false)
        TEST_ASSERT(date2!=date3 && date3!=date2)
        TEST_ASSERT(date2!=date4 && date4!=date2)
        TEST_ASSERT(date3!=date4 && date4!=date3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testLessOperator()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date1b(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date2b(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        TEST_ASSERT((date1<date1) == false)
        TEST_ASSERT((date1b<date1b) == false)
        TEST_ASSERT((date2<date2) == false)
        TEST_ASSERT((date2b<date2b) == false)
        TEST_ASSERT((date3<date3) == false)
        TEST_ASSERT((date4<date4) == false)
       
        TEST_ASSERT((date1<date2)==false && date2<date1)
        TEST_ASSERT((date1<date1b)==false && (date1b<date1)==false)
        TEST_ASSERT((date1<date3)==false && date3<date1)
        TEST_ASSERT(date1<date4 && (date4<date1)==false)
        TEST_ASSERT(date2<date1b && (date1b<date2)==false)
        TEST_ASSERT((date2<date2b)==false && (date2b<date2)==false)
        TEST_ASSERT(date2<date3 && (date3<date2)==false)
        TEST_ASSERT(date2<date4 && (date4<date2)==false)
        TEST_ASSERT(date3<date4 && (date4<date3)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testLessOrEqualOperator()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date1b(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date2b(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        TEST_ASSERT(date1<=date1)
        TEST_ASSERT(date1b<=date1b)
        TEST_ASSERT(date2<=date2)
        TEST_ASSERT(date2b<=date2b)
        TEST_ASSERT(date3<=date3)
        TEST_ASSERT(date4<=date4)
       
        TEST_ASSERT((date1<=date2)==false && date2<=date1)
        TEST_ASSERT(date1<=date1b && date1b<=date1)
        TEST_ASSERT((date1<=date3)==false && date3<=date1)
        TEST_ASSERT(date1<=date4 && (date4<=date1)==false)
        TEST_ASSERT(date2<=date1b && (date1b<=date2)==false)
        TEST_ASSERT(date2<=date2b && date2b<=date2)
        TEST_ASSERT(date2<=date3 && (date3<=date2)==false)
        TEST_ASSERT(date2<=date4 && (date4<=date2)==false)
        TEST_ASSERT(date3<=date4 && (date4<=date3)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testGreaterOrEqualOperator()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date1b(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date2b(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        TEST_ASSERT(date1>=date1)
        TEST_ASSERT(date1b>=date1b)
        TEST_ASSERT(date2>=date2)
        TEST_ASSERT(date2b>=date2b)
        TEST_ASSERT(date3>=date3)
        TEST_ASSERT(date4>=date4)
       
        TEST_ASSERT(date1>=date2 && (date2>=date1)==false)
        TEST_ASSERT(date1>=date1b && date1b>=date1)
        TEST_ASSERT(date1>=date3 && (date3>=date1)==false)
        TEST_ASSERT((date1>=date4)==false && date4>=date1)
        TEST_ASSERT((date2>=date1b)==false && date1b>=date2)
        TEST_ASSERT(date2>=date2b && date2b>=date2)
        TEST_ASSERT((date2>=date3)==false && date3>=date2)
        TEST_ASSERT((date2>=date4)==false && date4>=date2)
        TEST_ASSERT((date3>=date4)==false && date4>=date3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testGreaterOperator()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date1b(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date2b(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        TEST_ASSERT((date1>date1) == false)
        TEST_ASSERT((date1b>date1b) == false)
        TEST_ASSERT((date2>date2) == false)
        TEST_ASSERT((date2b>date2b) == false)
        TEST_ASSERT((date3>date3) == false)
        TEST_ASSERT((date4>date4) == false)
       
        TEST_ASSERT(date1>date2 && (date2>date1)==false)
        TEST_ASSERT((date1>date1b)==false && (date1b>date1)==false)
        TEST_ASSERT(date1>date3 && (date3>date1)==false)
        TEST_ASSERT((date1>date4)==false && date4>date1)
        TEST_ASSERT((date2>date1b)==false && date1b>date2)
        TEST_ASSERT((date2>date2b)==false && (date2b>date2)==false)
        TEST_ASSERT((date2>date3)==false && date3>date2)
        TEST_ASSERT((date2>date4)==false && date4>date2)
        TEST_ASSERT((date3>date4)==false && date4>date3)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testSubtractionOperator()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date1b(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date2b(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        TEST_ASSERT((date1-date1) == 0)
        TEST_ASSERT((date1b-date1b) == 0)
        TEST_ASSERT((date2-date2) == 0)
        TEST_ASSERT((date2b-date2b) == 0)
        TEST_ASSERT((date3-date3) == 0)
        TEST_ASSERT((date4-date4) == 0)

        klab::Int64 diff = date1 - date2;
        TEST_ASSERT(diff == 1336480269056753LL) 

        diff = date2 - date1;
        TEST_ASSERT(diff == -1336480269056753LL)  

        diff = date1 - date1b;
        TEST_ASSERT(diff == 0)

        diff = date1b - date1;
        TEST_ASSERT(diff == 0)

        diff = date1 - date3;
        TEST_ASSERT(diff == 336480269056753LL)  

        diff = date3 - date1;
        TEST_ASSERT(diff == -336480269056753LL) 

        diff = date1 - date4;
        TEST_ASSERT(diff == -809436530943246LL)  

        diff = date4 - date1;
        TEST_ASSERT(diff == 809436530943246LL) 

        diff = date2 - date1b;
        TEST_ASSERT(diff == -1336480269056753LL) 

        diff = date1b - date2;
        TEST_ASSERT(diff == 1336480269056753LL)  

        diff = date2 - date2b;
        TEST_ASSERT(diff == 0)

        diff = date2b - date2;
        TEST_ASSERT(diff == 0)

        diff = date2 - date3;
        TEST_ASSERT(diff == -1000000000000000LL)  

        diff = date3 - date2;
        TEST_ASSERT(diff == 1000000000000000LL)  

        diff = date2 - date4;
        TEST_ASSERT(diff == -2145916799999999LL)  

        diff = date4 - date2;
        TEST_ASSERT(diff == 2145916799999999LL)  

        diff = date3 - date4;
        TEST_ASSERT(diff == -1145916799999999LL)  

        diff = date4 - date3;
        TEST_ASSERT(diff == 1145916799999999LL)  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testClear()
{
    try
    {
        KDateTime date(1000000000123456LL, false);
        TEST_ASSERT(date.year() == 2001)
        TEST_ASSERT(date.month() == 9)
        TEST_ASSERT(date.day() == 9)
        TEST_ASSERT(date.weekday() == 0)
        TEST_ASSERT(date.hour() == 1)
        TEST_ASSERT(date.minute() == 46)
        TEST_ASSERT(date.second() == 40)
        TEST_ASSERT(date.milliseconds() == 123)
        TEST_ASSERT(date.microseconds() == 456)
        TEST_ASSERT(date.isValid())

        date.clear();
        TEST_ASSERT(date.year() == 1970)
        TEST_ASSERT(date.month() == 1)
        TEST_ASSERT(date.day() == 1)
        TEST_ASSERT(date.weekday() == 4)
        TEST_ASSERT(date.hour() == 0)
        TEST_ASSERT(date.minute() == 0)
        TEST_ASSERT(date.second() == 0)
        TEST_ASSERT(date.milliseconds() == 0)
        TEST_ASSERT(date.microseconds() == 0)
        TEST_ASSERT(date.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testNow()
{
    try
    {
        KDateTime date;
        date.now(false);
        TEST_ASSERT(date.year() >= 2012)
        TEST_ASSERT(date.month()>0 && date.month()<=12)
        TEST_ASSERT(date.day()>0 && date.day()<=31)
        TEST_ASSERT(date.weekday() < 7)
        TEST_ASSERT(date.hour() < 24)
        TEST_ASSERT(date.minute() < 60)
        TEST_ASSERT(date.second() < 60)
        TEST_ASSERT(date.milliseconds() < 1000)
        TEST_ASSERT(date.microseconds() < 1000)
        TEST_ASSERT(date.isValid())

        date.now(true);
        TEST_ASSERT(date.year() >= 2012)
        TEST_ASSERT(date.month()>0 && date.month()<=12)
        TEST_ASSERT(date.day()>0 && date.day()<=31)
        TEST_ASSERT(date.weekday() < 7)
        TEST_ASSERT(date.hour() < 24)
        TEST_ASSERT(date.minute() < 60)
        TEST_ASSERT(date.second() < 60)
        TEST_ASSERT(date.milliseconds() < 1000)
        TEST_ASSERT(date.microseconds() < 1000)
        TEST_ASSERT(date.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testYear()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.year() == 2037)
        TEST_ASSERT(date4.month() == 12)
        TEST_ASSERT(date4.day() == 31)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 23)
        TEST_ASSERT(date4.minute() == 59)
        TEST_ASSERT(date4.second() == 59)
        TEST_ASSERT(date4.milliseconds() == 999)
        TEST_ASSERT(date4.microseconds() == 999)
        TEST_ASSERT(date4.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testMonth()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.year() == 2037)
        TEST_ASSERT(date4.month() == 12)
        TEST_ASSERT(date4.day() == 31)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 23)
        TEST_ASSERT(date4.minute() == 59)
        TEST_ASSERT(date4.second() == 59)
        TEST_ASSERT(date4.milliseconds() == 999)
        TEST_ASSERT(date4.microseconds() == 999)
        TEST_ASSERT(date4.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testDay()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.year() == 2037)
        TEST_ASSERT(date4.month() == 12)
        TEST_ASSERT(date4.day() == 31)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 23)
        TEST_ASSERT(date4.minute() == 59)
        TEST_ASSERT(date4.second() == 59)
        TEST_ASSERT(date4.milliseconds() == 999)
        TEST_ASSERT(date4.microseconds() == 999)
        TEST_ASSERT(date4.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testWeekday()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.year() == 2037)
        TEST_ASSERT(date4.month() == 12)
        TEST_ASSERT(date4.day() == 31)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 23)
        TEST_ASSERT(date4.minute() == 59)
        TEST_ASSERT(date4.second() == 59)
        TEST_ASSERT(date4.milliseconds() == 999)
        TEST_ASSERT(date4.microseconds() == 999)
        TEST_ASSERT(date4.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testHour()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.year() == 2037)
        TEST_ASSERT(date4.month() == 12)
        TEST_ASSERT(date4.day() == 31)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 23)
        TEST_ASSERT(date4.minute() == 59)
        TEST_ASSERT(date4.second() == 59)
        TEST_ASSERT(date4.milliseconds() == 999)
        TEST_ASSERT(date4.microseconds() == 999)
        TEST_ASSERT(date4.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testMinute()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.year() == 2037)
        TEST_ASSERT(date4.month() == 12)
        TEST_ASSERT(date4.day() == 31)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 23)
        TEST_ASSERT(date4.minute() == 59)
        TEST_ASSERT(date4.second() == 59)
        TEST_ASSERT(date4.milliseconds() == 999)
        TEST_ASSERT(date4.microseconds() == 999)
        TEST_ASSERT(date4.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testSecond()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.year() == 2037)
        TEST_ASSERT(date4.month() == 12)
        TEST_ASSERT(date4.day() == 31)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 23)
        TEST_ASSERT(date4.minute() == 59)
        TEST_ASSERT(date4.second() == 59)
        TEST_ASSERT(date4.milliseconds() == 999)
        TEST_ASSERT(date4.microseconds() == 999)
        TEST_ASSERT(date4.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testMilliseconds()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.year() == 2037)
        TEST_ASSERT(date4.month() == 12)
        TEST_ASSERT(date4.day() == 31)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 23)
        TEST_ASSERT(date4.minute() == 59)
        TEST_ASSERT(date4.second() == 59)
        TEST_ASSERT(date4.milliseconds() == 999)
        TEST_ASSERT(date4.microseconds() == 999)
        TEST_ASSERT(date4.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testMicroseconds()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.year() == 2012)
        TEST_ASSERT(date.month() == 5)
        TEST_ASSERT(date.day() == 8)
        TEST_ASSERT(date.weekday() == 2)
        TEST_ASSERT(date.hour() == 12)
        TEST_ASSERT(date.minute() == 31)
        TEST_ASSERT(date.second() == 9)
        TEST_ASSERT(date.milliseconds() == 56)
        TEST_ASSERT(date.microseconds() == 753)
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.year() == 1970)
        TEST_ASSERT(date2.month() == 1)
        TEST_ASSERT(date2.day() == 1)
        TEST_ASSERT(date2.weekday() == 4)
        TEST_ASSERT(date2.hour() == 0)
        TEST_ASSERT(date2.minute() == 0)
        TEST_ASSERT(date2.second() == 0)
        TEST_ASSERT(date2.milliseconds() == 0)
        TEST_ASSERT(date2.microseconds() == 0)
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.year() == 2001)
        TEST_ASSERT(date3.month() == 9)
        TEST_ASSERT(date3.day() == 9)
        TEST_ASSERT(date3.weekday() == 0)
        TEST_ASSERT(date3.hour() == 1)
        TEST_ASSERT(date3.minute() == 46)
        TEST_ASSERT(date3.second() == 40)
        TEST_ASSERT(date3.milliseconds() == 0)
        TEST_ASSERT(date3.microseconds() == 0)
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.year() == 2037)
        TEST_ASSERT(date4.month() == 12)
        TEST_ASSERT(date4.day() == 31)
        TEST_ASSERT(date4.weekday() == 4)
        TEST_ASSERT(date4.hour() == 23)
        TEST_ASSERT(date4.minute() == 59)
        TEST_ASSERT(date4.second() == 59)
        TEST_ASSERT(date4.milliseconds() == 999)
        TEST_ASSERT(date4.microseconds() == 999)
        TEST_ASSERT(date4.isValid())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testIsValid()
{
    try
    {
        KDateTime date(2012, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date.isValid())

        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        TEST_ASSERT(date2.isValid())

        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        TEST_ASSERT(date3.isValid())

        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);
        TEST_ASSERT(date4.isValid())


        // Limit cases.
        KDateTime date01(2012, 5, 8, 12, 31, 9, 56, 1000);
        TEST_ASSERT(date01.isValid() == false)

        KDateTime date02(2012, 5, 8, 12, 31, 9, 1000, 753);
        TEST_ASSERT(date02.isValid() == false)

        KDateTime date03(2012, 5, 8, 12, 31, 60, 56, 753);
        TEST_ASSERT(date03.isValid() == false)

        KDateTime date04(2012, 5, 8, 12, 60, 9, 56, 753);
        TEST_ASSERT(date04.isValid() == false)

        KDateTime date05(2012, 5, 8, 24, 31, 9, 56, 753);
        TEST_ASSERT(date05.isValid() == false)

        KDateTime date06(2012, 5, 0, 12, 31, 9, 56, 753);
        TEST_ASSERT(date06.isValid() == false)

        KDateTime date07(2012, 5, 32, 13, 31, 9, 56, 753);
        TEST_ASSERT(date07.isValid() == false)

        KDateTime date08(2012, 4, 31, 12, 31, 9, 56, 753);
        TEST_ASSERT(date08.isValid() == false)

        KDateTime date09(2012, 2, 30, 12, 31, 9, 56, 753);
        TEST_ASSERT(date09.isValid() == false)

        KDateTime date010(2012, 0, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date010.isValid() == false)

        KDateTime date011(2012, 13, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date011.isValid() == false)

        KDateTime date012(1969, 5, 8, 12, 31, 9, 56, 753);
        TEST_ASSERT(date012.isValid() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testEquals()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date1b(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date2b(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        TEST_ASSERT(date1.equals(date1))
        TEST_ASSERT(date1b.equals(date1b))
        TEST_ASSERT(date2.equals(date2))
        TEST_ASSERT(date2b.equals(date2b))
        TEST_ASSERT(date3.equals(date3))
        TEST_ASSERT(date4.equals(date4))
        
        TEST_ASSERT((date1.equals(date2))==false && (date2.equals(date1))==false)
        TEST_ASSERT(date1.equals(date1b) && date1b.equals(date1))
        TEST_ASSERT((date1.equals(date3))==false && (date3.equals(date1))==false)
        TEST_ASSERT((date1.equals(date4))==false && (date4.equals(date1))==false)
        TEST_ASSERT((date2.equals(date1b))==false && (date1b.equals(date2))==false)
        TEST_ASSERT(date2.equals(date2b) && date2b.equals(date2))
        TEST_ASSERT((date2.equals(date3))==false && (date3.equals(date2))==false)
        TEST_ASSERT((date2.equals(date4))==false && (date4.equals(date2))==false)
        TEST_ASSERT((date3.equals(date4))==false && (date4.equals(date3))==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testCompare()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date1b(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date2b(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        TEST_ASSERT(date1.compare(date1) == 0)
        TEST_ASSERT(date1b.compare(date1b) == 0)
        TEST_ASSERT(date2.compare(date2) == 0)
        TEST_ASSERT(date2b.compare(date2b) == 0)
        TEST_ASSERT(date3.compare(date3) == 0)
        TEST_ASSERT(date4.compare(date4) == 0)

        klab::Int64 diff = date1.compare(date2);
        TEST_ASSERT(diff == 1336480269056753LL) 

        diff = date2.compare(date1);
        TEST_ASSERT(diff == -1336480269056753LL)  

        diff = date1.compare(date1b);
        TEST_ASSERT(diff == 0)

        diff = date1b.compare(date1);
        TEST_ASSERT(diff == 0)

        diff = date1.compare(date3);
        TEST_ASSERT(diff == 336480269056753LL)  

        diff = date3.compare(date1);
        TEST_ASSERT(diff == -336480269056753LL) 

        diff = date1.compare(date4);
        TEST_ASSERT(diff == -809436530943246LL)  

        diff = date4.compare(date1);
        TEST_ASSERT(diff == 809436530943246LL) 

        diff = date2.compare(date1b);
        TEST_ASSERT(diff == -1336480269056753LL) 

        diff = date1b.compare(date2);
        TEST_ASSERT(diff == 1336480269056753LL)  

        diff = date2.compare(date2b);
        TEST_ASSERT(diff == 0)

        diff = date2b.compare(date2);
        TEST_ASSERT(diff == 0)

        diff = date2.compare(date3);
        TEST_ASSERT(diff == -1000000000000000LL)  

        diff = date3.compare(date2);
        TEST_ASSERT(diff == 1000000000000000LL)  

        diff = date2.compare(date4);
        TEST_ASSERT(diff == -2145916799999999LL)  

        diff = date4.compare(date2);
        TEST_ASSERT(diff == 2145916799999999LL)  

        diff = date3.compare(date4);
        TEST_ASSERT(diff == -1145916799999999LL)  

        diff = date4.compare(date3);
        TEST_ASSERT(diff == 1145916799999999LL)  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTimeUnitTest::testToString()
{
    try
    {
        KDateTime date1(2012, 5, 8, 12, 31, 9, 56, 753);
        KDateTime date2(1970, 1, 1, 0, 0, 0, 0, 0);
        KDateTime date3(2001, 9, 9, 1, 46, 40, 0, 0);
        KDateTime date4(2037, 12, 31, 23, 59, 59, 999, 999);

        std::string str = date1.toString();
        TEST_ASSERT(klab::Equals(str, "2012-05-08 12:31:09.056.753"))

        str = date2.toString();
        TEST_ASSERT(klab::Equals(str, "1970-01-01 00:00:00.000.000"))

        str = date3.toString();
        TEST_ASSERT(klab::Equals(str, "2001-09-09 01:46:40.000.000"))

        str = date4.toString();
        TEST_ASSERT(klab::Equals(str, "2037-12-31 23:59:59.999.999"))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
