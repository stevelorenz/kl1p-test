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

#include "../include/Timer.h"
#include "../include/ScopedMutex.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KTimer::KTimer() : 
_mutex(), 
_isStarted(false), _isSuspended(false), 
_timestamp(0), _duration(0), _suspendTimestamp(0), _suspendDuration(0)
{}

// ---------------------------------------------------------------------------------------------------- //

KTimer::KTimer(const KTimer& timer) : 
_mutex(), 
_isStarted(timer._isStarted), _isSuspended(timer._isSuspended), 
_timestamp(timer._timestamp), _duration(timer._duration), _suspendTimestamp(timer._suspendTimestamp), _suspendDuration(timer._suspendDuration)
{}

// ---------------------------------------------------------------------------------------------------- //

KTimer::~KTimer()
{}

// ---------------------------------------------------------------------------------------------------- //

KTimer& KTimer::operator=(const KTimer& timer)
{
    if(this != &timer)
    {
        klab::TScopedMutex<klab::KMutex> mutex(_mutex);
        klab::TScopedMutex<klab::KMutex> mutex2(timer._mutex);

        _isStarted   = timer._isStarted;
        _isSuspended = timer._isSuspended;

        _timestamp = timer._timestamp;
        _duration  = timer._duration;
        _suspendTimestamp = timer._suspendTimestamp;
        _suspendDuration  = timer._suspendDuration;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

void KTimer::start()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_isStarted == false)
    {
        this->resetTimer();

        _isStarted   = true;
        _isSuspended = false;
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimer::suspend()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_isStarted && _isSuspended==false)
    {
        _suspendTimestamp = KSystemTime::GetTickCount();

        _isSuspended = true;
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimer::resume()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_isStarted && _isSuspended)
    {
        _suspendDuration += KSystemTime::GetTickCount() - _suspendTimestamp;

        _isSuspended = false;
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimer::stop()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_isStarted)
    {
        if(_isSuspended)
            this->resume();

        this->updateTimer();

        _isStarted   = false;
        _isSuspended = false;
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTimer::reset()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    this->resetTimer();
}

// ---------------------------------------------------------------------------------------------------- //

bool KTimer::isStarted() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _isStarted;
}

// ---------------------------------------------------------------------------------------------------- //

bool KTimer::isSuspended() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _isSuspended;
}

// ---------------------------------------------------------------------------------------------------- //

bool KTimer::isRunning() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return (_isStarted && _isSuspended==false);
}

// ---------------------------------------------------------------------------------------------------- //

klab::KMicrosecTime KTimer::duration()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(this->isRunning())
        this->updateTimer();

    return _duration;
}

// ---------------------------------------------------------------------------------------------------- //

klab::KMicrosecTime KTimer::durationInMicroseconds()
{
    return this->duration();
}

// ---------------------------------------------------------------------------------------------------- //

klab::DoubleReal KTimer::durationInMilliseconds()
{
    return (static_cast<klab::DoubleReal>(this->duration()) / 1000.0);
}

// ---------------------------------------------------------------------------------------------------- //

klab::DoubleReal KTimer::durationInSeconds()
{
    return (static_cast<klab::DoubleReal>(this->duration()) / 1000000.0);
}

// ---------------------------------------------------------------------------------------------------- //

void KTimer::resetTimer()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    _timestamp = KSystemTime::GetTickCount();
    _duration  = 0;

    _suspendTimestamp = _timestamp;
    _suspendDuration  = 0;
}

// ---------------------------------------------------------------------------------------------------- //

void KTimer::updateTimer()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);
    
    _duration = (KSystemTime::GetTickCount()-_timestamp) - _suspendDuration;
}

// ---------------------------------------------------------------------------------------------------- //
