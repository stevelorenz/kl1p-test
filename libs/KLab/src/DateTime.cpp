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

#include "../include/DateTime.h"
#include "../include/ScopedMutex.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KDateTime::KDateTime() : 
_mutex(),
_year(1970), _month(1), _day(1), _weekday(klab::THURSDAY),
_hour(0), _minute(0), _second(0), _millisec(0), _microsec(0)
{}

// ---------------------------------------------------------------------------------------------------- //

KDateTime::KDateTime(bool local) : 
_mutex(),
_year(0), _month(0), _day(0), _weekday(klab::BAD_WEEKDAY),
_hour(0), _minute(0), _second(0), _millisec(0), _microsec(0)
{
    this->now(local);
}

// ---------------------------------------------------------------------------------------------------- //

KDateTime::KDateTime(klab::KMicrosecTimestamp timestamp, bool local) : 
_mutex(),
_year(0), _month(0), _day(0), _weekday(klab::BAD_WEEKDAY),
_hour(0), _minute(0), _second(0), _millisec(0), _microsec(0)
{
    KSystemTime::ConvertMicrosecTimestampToDateTime(timestamp, local, _year, _month, _day, _hour, _minute, _second, _millisec, _microsec);
}

// ---------------------------------------------------------------------------------------------------- //

KDateTime::KDateTime(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day, klab::UInt8 hour, klab::UInt8 minute, klab::UInt8 second, klab::UInt16 millisec, klab::UInt16 microsec) : 
_mutex(),
_year(year), _month(month), _day(day), _weekday(klab::BAD_WEEKDAY),
_hour(hour), _minute(minute), _second(second), _millisec(millisec), _microsec(microsec)
{}

// ---------------------------------------------------------------------------------------------------- //

KDateTime::KDateTime(const KDateTime& date) : 
_mutex(),
_year(date._year), _month(date._month), _day(date._day), _weekday(date._weekday),
_hour(date._hour), _minute(date._minute), _second(date._second), _millisec(date._millisec), _microsec(date._microsec)
{}

// ---------------------------------------------------------------------------------------------------- //

KDateTime::~KDateTime()
{}

// ---------------------------------------------------------------------------------------------------- //

KDateTime& KDateTime::operator=(const KDateTime& date)
{
    if(this != &date)
    {
        klab::TScopedMutex<klab::KMutex> mutex(_mutex);
        klab::TScopedMutex<klab::KMutex> mutex2(date._mutex);

        _year    = date._year;
        _month   = date._month;
        _day     = date._day;
        _weekday = date._weekday;

        _hour     = date._hour;
        _minute   = date._minute;
        _second   = date._second;
        _millisec = date._millisec;
        _microsec = date._microsec;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

bool KDateTime::operator==(const KDateTime& date) const
{
    return (this->compare(date) == 0);
}

// ---------------------------------------------------------------------------------------------------- //

bool KDateTime::operator!=(const KDateTime& date) const
{
    return (this->compare(date)!= 0);
}

// ---------------------------------------------------------------------------------------------------- //

bool KDateTime::operator<(const KDateTime& date) const
{
    return (this->compare(date) < 0);
}

// ---------------------------------------------------------------------------------------------------- //

bool KDateTime::operator<=(const KDateTime& date) const
{
    return (this->compare(date) <= 0);
}

// ---------------------------------------------------------------------------------------------------- //

bool KDateTime::operator>=(const KDateTime& date) const
{
    return (this->compare(date) >= 0);
}

// ---------------------------------------------------------------------------------------------------- //

bool KDateTime::operator>(const KDateTime& date) const
{
    return (this->compare(date) > 0);
}

// ---------------------------------------------------------------------------------------------------- //

klab::Int64 KDateTime::operator-(const KDateTime& date) const
{
    return this->compare(date);
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTime::clear()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    _year    = 1970;
    _month   = 1;
    _day     = 1;
    _weekday = klab::THURSDAY;

    _hour     = 0;
    _minute   = 0;
    _second   = 0;
    _millisec = 0;
    _microsec = 0;
}

// ---------------------------------------------------------------------------------------------------- //

void KDateTime::now(bool local)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    KSystemTime::ConvertMicrosecTimestampToDateTime(KSystemTime::GetCurrentMicrosecTimestamp(), local, _year, _month, _day, _hour, _minute, _second, _millisec, _microsec);
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt16 KDateTime::year() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _year;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt8 KDateTime::month() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _month;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt8 KDateTime::day() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _day;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt8 KDateTime::weekday() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_weekday > 6)
        _weekday = KSystemTime::GetWeekDayFromDate(_year, _month, _day);

    return _weekday;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt8 KDateTime::hour() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _hour;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt8 KDateTime::minute() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _minute;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt8 KDateTime::second() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _second;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt16 KDateTime::milliseconds() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _millisec;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt16 KDateTime::microseconds() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _microsec;
}

// ---------------------------------------------------------------------------------------------------- //

bool KDateTime::isValid() const
{
    return KSystemTime::IsValidDateTime(_year, _month, _day, _hour, _minute, _second, _millisec, _microsec);
}

// ---------------------------------------------------------------------------------------------------- //

bool KDateTime::equals(const KDateTime& date) const
{
    return (this->compare(date) == 0);
}

// ---------------------------------------------------------------------------------------------------- //

klab::Int64 KDateTime::compare(const KDateTime& date) const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return KSystemTime::CompareDateTimes(_year, _month, _day, _hour, _minute, _second, _millisec, _microsec, date._year, date._month, date._day, date._hour, date._minute, date._second, date._millisec, date._microsec);
}

// ---------------------------------------------------------------------------------------------------- //

std::string KDateTime::toString() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    std::ostringstream oss;
    oss<<_year<<"-"
       <<(_month<10?"0":"")<<static_cast<klab::UInt32>(_month)<<"-"
       <<(_day<10?"0":"")<<static_cast<klab::UInt32>(_day)<<" "
       <<(_hour<10?"0":"")<<static_cast<klab::UInt32>(_hour)<<":"
       <<(_minute<10?"0":"")<<static_cast<klab::UInt32>(_minute)<<":"
       <<(_second<10?"0":"")<<static_cast<klab::UInt32>(_second)<<".";

    if(_millisec<100)   oss<<"0";
    if(_millisec<10)    oss<<"0";
    oss<<static_cast<klab::UInt32>(_millisec)<<".";

    if(_microsec<100)   oss<<"0";
    if(_microsec<10)    oss<<"0";
    oss<<static_cast<klab::UInt32>(_microsec);

    return oss.str();
}

// ---------------------------------------------------------------------------------------------------- //
