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

#ifndef KLAB_TIMER_H
#define KLAB_TIMER_H

#include "TypeUtil.h"
#include "Mutex.h"
#include "SystemTime.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KTimer
{
public:

    KTimer();
    KTimer(const KTimer& timer);
    virtual ~KTimer();

    KTimer&                     operator=(const KTimer& timer);  

    void                        start();
    void                        suspend();
    void                        resume();
    void                        stop();

    void                        reset();

    bool                        isStarted() const;
    bool                        isSuspended() const;
    bool                        isRunning() const;

    klab::KMicrosecTime         duration();
    klab::KMicrosecTime         durationInMicroseconds();
    klab::DoubleReal            durationInMilliseconds();
    klab::DoubleReal            durationInSeconds();


protected:

    void                        resetTimer();
    void                        updateTimer();


private:

    klab::KMutex                _mutex;

    bool                        _isStarted;
    bool                        _isSuspended;

    klab::KMicrosecTime         _timestamp;  
    klab::KMicrosecTime         _duration;
    klab::KMicrosecTime         _suspendTimestamp;  
    klab::KMicrosecTime         _suspendDuration;
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
