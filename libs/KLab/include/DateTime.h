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

#ifndef KLAB_DATETIME_H
#define KLAB_DATETIME_H

#include "TypeUtil.h"
#include "Mutex.h"
#include "SystemTime.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KDateTime
{
public:

    KDateTime();
    KDateTime(bool local);
    KDateTime(klab::KMicrosecTimestamp timestamp, bool local=false);
    KDateTime(klab::UInt16 year, klab::UInt8 month, klab::UInt8 day, klab::UInt8 hour=0, klab::UInt8 minute=0, klab::UInt8 second=0, klab::UInt16 millisec=0, klab::UInt16 microsec=0);
    KDateTime(const KDateTime& date);
    virtual ~KDateTime();

    KDateTime&          operator=(const KDateTime& date);

    bool                operator==(const KDateTime& date) const;
    bool                operator!=(const KDateTime& date) const;
    bool                operator<(const KDateTime& date) const;
    bool                operator<=(const KDateTime& date) const;
    bool                operator>=(const KDateTime& date) const;
    bool                operator>(const KDateTime& date) const;
    klab::Int64         operator-(const KDateTime& date) const;

    void                clear();
    void                now(bool local=false);

    klab::UInt16        year() const;
    klab::UInt8         month() const;
    klab::UInt8         day() const;
    klab::UInt8         weekday() const;
    klab::UInt8         hour() const;
    klab::UInt8         minute() const;
    klab::UInt8         second() const;
    klab::UInt16        milliseconds() const;
    klab::UInt16        microseconds() const;
    bool                isValid() const;

    bool                equals(const KDateTime& date) const;
    klab::Int64         compare(const KDateTime& date) const;

    std::string         toString() const;


private:

    klab::KMutex        _mutex;

    klab::UInt16        _year;
    klab::UInt8         _month;
    klab::UInt8         _day;
    mutable klab::UInt8 _weekday;

    klab::UInt8         _hour;
    klab::UInt8         _minute;
    klab::UInt8         _second;
    klab::UInt16        _millisec;
    klab::UInt16        _microsec;
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
