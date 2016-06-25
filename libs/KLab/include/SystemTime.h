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

#ifndef KLAB_SYSTEMTIME_H
#define KLAB_SYSTEMTIME_H

#include "SystemUtil.h"
#include "TemplateUtil.h"
#include "Exception.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KSystemTimeException, KException)

// ---------------------------------------------------------------------------------------------------- //

typedef klab::UInt64    KTime;              // Time duration in seconds. 
typedef klab::UInt64    KMillisecTime;      // Time duration in microseconds. 
typedef klab::UInt64    KMicrosecTime;      // Time duration in microseconds. 

typedef klab::Int64     KTimestamp;         // Timestamp in seconds.
typedef klab::Int64     KMillisecTimestamp; // Timestamp in milliseconds.
typedef klab::Int64     KMicrosecTimestamp; // Timestamp in microseconds.
  
// ---------------------------------------------------------------------------------------------------- //

enum WeekDay
{
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,

    BAD_WEEKDAY,
};

// ---------------------------------------------------------------------------------------------------- //

template<class System>
class TSystemTime
{
public:

    virtual ~TSystemTime();


public:

    static KMicrosecTime        GetTickCount();

    static KTimestamp           GetCurrentTimestamp();
    static KMillisecTimestamp   GetCurrentMillisecTimestamp();
    static KMicrosecTimestamp   GetCurrentMicrosecTimestamp();

    static void                 ConvertTimestampToDateTime(KTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second);
    static void                 ConvertMillisecTimestampToDateTime(KMillisecTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second, klab::UInt16& millisec);
    static void                 ConvertMicrosecTimestampToDateTime(KMicrosecTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second, klab::UInt16& millisec, klab::UInt16& microsec);

    static klab::UInt8          GetWeekDayFromDate(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day);

    static bool                 IsValidDateTime(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day, klab::UInt8 hour=0, klab::UInt8 minute=0, klab::UInt8 second=0, klab::UInt16 millisec=0, klab::UInt16 microsec=0);
    static klab::Int64          CompareDateTimes(klab::UInt16 lyear, klab::UInt8 lmonth, klab::UInt8 lday, klab::UInt8 lhour, klab::UInt8 lminute, klab::UInt8 lsecond, klab::UInt16 lmillisec, klab::UInt16 lmicrosec, klab::UInt16 ryear, klab::UInt8 rmonth, klab::UInt8 rday, klab::UInt8 rhour, klab::UInt8 rminute, klab::UInt8 rsecond, klab::UInt16 rmillisec, klab::UInt16 rmicrosec);


protected:

    TSystemTime();
    TSystemTime(const TSystemTime<System>& system);
    TSystemTime<System>&        operator=(const TSystemTime<System>& system);
};

// ---------------------------------------------------------------------------------------------------- //

typedef TSystemTime<CurrentSystem>  KSystemTime;

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemTime<System>::TSystemTime()
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemTime<System>::TSystemTime(const TSystemTime<System>& date)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false).  
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemTime<System>::~TSystemTime()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemTime<System>& TSystemTime<System>::operator=(const TSystemTime<System>& date)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline KMicrosecTime TSystemTime<System>::GetTickCount()
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline KTimestamp TSystemTime<System>::GetCurrentTimestamp()
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline KMillisecTimestamp TSystemTime<System>::GetCurrentMillisecTimestamp()
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline KMicrosecTimestamp TSystemTime<System>::GetCurrentMicrosecTimestamp()
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TSystemTime<System>::ConvertTimestampToDateTime(KTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TSystemTime<System>::ConvertMillisecTimestampToDateTime(KMillisecTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second, klab::UInt16& millisec)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TSystemTime<System>::ConvertMicrosecTimestampToDateTime(KMicrosecTimestamp timestamp, bool local, klab::UInt16& year, klab::UInt8& month, klab::UInt8& day, klab::UInt8& hour, klab::UInt8& minute, klab::UInt8& second, klab::UInt16& millisec, klab::UInt16& microsec)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline klab::UInt8 TSystemTime<System>::GetWeekDayFromDate(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemTime<System>::IsValidDateTime(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day, klab::UInt8 hour, klab::UInt8 minute, klab::UInt8 second, klab::UInt16 millisec, klab::UInt16 microsec)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline klab::Int64 TSystemTime<System>::CompareDateTimes(klab::UInt16 lyear, klab::UInt8 lmonth, klab::UInt8 lday, klab::UInt8 lhour, klab::UInt8 lminute, klab::UInt8 lsecond, klab::UInt16 lmillisec, klab::UInt16 lmicrosec, klab::UInt16 ryear, klab::UInt8 rmonth, klab::UInt8 rday, klab::UInt8 rhour, klab::UInt8 rminute, klab::UInt8 rsecond, klab::UInt16 rmillisec, klab::UInt16 rmicrosec)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

}

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_MSWINDOWS_SYSTEM)
    #include "win/WinSystemTime.h"
#elif defined(KLAB_UNIX_SYSTEM)
    #include "unix/UnixSystemTime.h"   
#elif defined(KLAB_MACOS_SYSTEM)
    #include "macos/MacSystemTime.h" 
#endif

// ---------------------------------------------------------------------------------------------------- //


#endif
