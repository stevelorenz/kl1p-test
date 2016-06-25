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

#ifndef KLAB_UNIXSYSTEMTIME_H
#define KLAB_UNIXSYSTEMTIME_H

#include "../SystemUtil.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<>
class TSystemTime<UnixSystem>
{
public:

    virtual ~TSystemTime();


public:

    static KMicrosecTime        GetTickCount();

    static KTimestamp           GetCurrentTimestamp();
    static KMillisecTimestamp   GetCurrentMillisecTimestamp();
    static KMicrosecTimestamp   GetCurrentMicrosecTimestamp();
    
    static void                 ConvertTimestampToDateTime(const KTimestamp& timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second);
    static void                 ConvertMillisecTimestampToDateTime(KMillisecTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second, klab::UInt16& millisec);
    static void                 ConvertMicrosecTimestampToDateTime(KMicrosecTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second, klab::UInt16& millisec, klab::UInt16& microsec);

    static klab::UInt8          GetWeekDayFromDate(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day);

	static bool                 IsValidDateTime(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day, klab::UInt8 hour=0, klab::UInt8 minute=0, klab::UInt8 second=0, klab::UInt16 millisec=0, klab::UInt16 microsec=0);
    static klab::Int64          CompareDateTimes(klab::UInt16 lyear, klab::UInt8 lmonth, klab::UInt8 lday, klab::UInt8 lhour, klab::UInt8 lminute, klab::UInt8 lsecond, klab::UInt16 lmillisec, klab::UInt16 lmicrosec, klab::UInt16 ryear, klab::UInt8 rmonth, klab::UInt8 rday, klab::UInt8 rhour, klab::UInt8 rminute, klab::UInt8 rsecond, klab::UInt16 rmillisec, klab::UInt16 rmicrosec);

    
protected:

    TSystemTime();
    TSystemTime(const TSystemTime<UnixSystem>& system);
    TSystemTime<UnixSystem>&	operator=(const TSystemTime<UnixSystem>& system);
};

// ---------------------------------------------------------------------------------------------------- //

inline TSystemTime<UnixSystem>::TSystemTime()
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemTime<UnixSystem>::TSystemTime(const TSystemTime<UnixSystem>& system)
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemTime<UnixSystem>::~TSystemTime()
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemTime<UnixSystem>& TSystemTime<UnixSystem>::operator=(const TSystemTime<UnixSystem>& system)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

inline KMicrosecTime TSystemTime<UnixSystem>::GetTickCount()
{ 
    timeval tv;
	::gettimeofday(&tv, 0); 
	
	return (static_cast<KMicrosecTimestamp>(tv.tv_sec)*1000000 + tv.tv_usec); 
}

// ---------------------------------------------------------------------------------------------------- //

inline KTimestamp TSystemTime<UnixSystem>::GetCurrentTimestamp()
{
    return static_cast<KTimestamp>(TSystemTime<UnixSystem>::GetCurrentMicrosecTimestamp()/1000000);
}

// ---------------------------------------------------------------------------------------------------- //

inline KMillisecTimestamp TSystemTime<UnixSystem>::GetCurrentMillisecTimestamp()
{
    return static_cast<KTimestamp>(TSystemTime<UnixSystem>::GetCurrentMicrosecTimestamp()/1000);
}

// ---------------------------------------------------------------------------------------------------- //

inline KMicrosecTimestamp TSystemTime<UnixSystem>::GetCurrentMicrosecTimestamp()
{ 
	timeval tv;
	::gettimeofday(&tv, 0); 
	
	return (static_cast<KMicrosecTimestamp>(tv.tv_sec)*1000000 + tv.tv_usec); 
}

// ---------------------------------------------------------------------------------------------------- //

inline void TSystemTime<UnixSystem>::ConvertTimestampToDateTime(const KTimestamp& timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second)
{
    ThrowTraceExceptionIf(KSystemTimeException, timestamp<0);   // This implementation does not support pre-epoch timestamps.  

    time_t time = timestamp;
    tm* current = 0;

    if(local)   current = ::localtime(&time);
    else        current = ::gmtime(&time);

    ThrowTraceExceptionIf(KSystemTimeException, current==0);

    year   = current->tm_year + 1900;
    month  = current->tm_mon + 1;
    day    = current->tm_mday;
    hour   = current->tm_hour;
    minute = current->tm_min;
    second = current->tm_sec;
}

// ---------------------------------------------------------------------------------------------------- //

inline void TSystemTime<UnixSystem>::ConvertMillisecTimestampToDateTime(KMillisecTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second, klab::UInt16& millisec)
{
    ThrowTraceExceptionIf(KSystemTimeException, timestamp<0);   // This implementation does not support pre-epoch timestamps.  

    KTimestamp sec = timestamp / 1000;

    time_t time = sec;
    tm* current = 0;

    if(local)   current = ::localtime(&time);
    else        current = ::gmtime(&time);

    ThrowTraceExceptionIf(KSystemTimeException, current==0);

    year     = current->tm_year + 1900;
    month    = current->tm_mon + 1;
    day      = current->tm_mday;
    hour     = current->tm_hour;
    minute   = current->tm_min;
    second   = current->tm_sec;
    millisec = static_cast<klab::UInt16>(timestamp - static_cast<KMillisecTimestamp>(sec)*1000);
}

// ---------------------------------------------------------------------------------------------------- //

inline void TSystemTime<UnixSystem>::ConvertMicrosecTimestampToDateTime(KMicrosecTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second, klab::UInt16& millisec, klab::UInt16& microsec)
{
    ThrowTraceExceptionIf(KSystemTimeException, timestamp<0);   // This implementation does not support pre-epoch timestamps.  

    KMillisecTimestamp millis = timestamp / 1000;
    KTimestamp sec = timestamp / 1000000;

    time_t time = sec;
    tm* current = 0;

    if(local)   current = ::localtime(&time);
    else        current = ::gmtime(&time);

    ThrowTraceExceptionIf(KSystemTimeException, current==0);

    year     = current->tm_year + 1900;
    month    = current->tm_mon + 1;
    day      = current->tm_mday;
    hour     = current->tm_hour;
    minute   = current->tm_min;
    second   = current->tm_sec;
    millisec = static_cast<klab::UInt16>(millis - static_cast<KMillisecTimestamp>(sec)*1000);
    microsec = static_cast<klab::UInt16>(timestamp - static_cast<KMicrosecTimestamp>((sec*1000)+millisec)*1000);
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::UInt8 TSystemTime<UnixSystem>::GetWeekDayFromDate(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day)
{
    if(TSystemTime<UnixSystem>::IsValidDateTime(year, month, day))
    {
        tm time;
        time.tm_year  = year - 1900;
        time.tm_mon   = month - 1;
        time.tm_mday  = day;
        time.tm_hour  = 12;
        time.tm_min   = 0;
        time.tm_sec   = 0;
        time.tm_isdst = 0;

        ::mktime(&time);

        if(time.tm_wday<7)  return static_cast<klab::UInt8>(time.tm_wday);
        else                return 7;
    }
    else
    {
        return 7;
    }
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemTime<UnixSystem>::IsValidDateTime(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day, klab::UInt8 hour, klab::UInt8 minute, klab::UInt8 second, klab::UInt16 millisec, klab::UInt16 microsec)
{
    bool ret = true;

    if(hour<24 && minute<60 && second<60 && millisec<1000 && microsec<1000)
    {
        tm time;
        time.tm_year  = year - 1900;
        time.tm_mon   = month - 1;
        time.tm_mday  = day;
        time.tm_hour  = 12;
        time.tm_min   = 0;
        time.tm_sec   = 0;
        time.tm_isdst = 0;
		
        return (::mktime(&time)>=0 && time.tm_year==(year-1900) && time.tm_mon==(month-1) && time.tm_mday==day);
    }
    else
    {
        return false;
    }
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Int64 TSystemTime<UnixSystem>::CompareDateTimes(klab::UInt16 lyear, klab::UInt8 lmonth, klab::UInt8 lday, klab::UInt8 lhour, klab::UInt8 lminute, klab::UInt8 lsecond, klab::UInt16 lmillisec, klab::UInt16 lmicrosec, klab::UInt16 ryear, klab::UInt8 rmonth, klab::UInt8 rday, klab::UInt8 rhour, klab::UInt8 rminute, klab::UInt8 rsecond, klab::UInt16 rmillisec, klab::UInt16 rmicrosec)
{
    tm ltime;
    ltime.tm_year  = lyear - 1900;
    ltime.tm_mon   = lmonth - 1;
    ltime.tm_mday  = lday;
    ltime.tm_hour  = lhour;
    ltime.tm_min   = lminute;
    ltime.tm_sec   = lsecond;
    ltime.tm_isdst = 0;

    tm rtime;
    rtime.tm_year  = ryear - 1900;
    rtime.tm_mon   = rmonth - 1;
    rtime.tm_mday  = rday;
    rtime.tm_hour  = rhour;
    rtime.tm_min   = rminute;
    rtime.tm_sec   = rsecond;
    rtime.tm_isdst = 0;

	char* tz = getenv("TZ");    // Warning! Not thread-safe.
    setenv("TZ", "UTC0", 1);	// Warning! Not thread-safe.
    tzset();                   	// Warning! Not thread-safe.
	
    klab::Int64 left  = (((static_cast<KMicrosecTimestamp>(::mktime(&ltime))*1000)+lmillisec)*1000)+lmicrosec; 
    klab::Int64 right = (((static_cast<KMicrosecTimestamp>(::mktime(&rtime))*1000)+rmillisec)*1000)+rmicrosec; 
	
	if(tz != 0)
    {
        setenv("TZ", tz, 1);	// Warning! Not thread-safe.
        tzset();               	// Warning! Not thread-safe.
    }
    else
    {
        unsetenv("TZ");			// Warning! Not thread-safe.
        tzset();               	// Warning! Not thread-safe.
    }

    return (left - right);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
