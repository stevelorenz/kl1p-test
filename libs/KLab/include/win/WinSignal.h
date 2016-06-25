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

#ifndef KLAB_WINSIGNAL_H
#define KLAB_WINSIGNAL_H

#include "../SystemUtil.h"
#include "../Mutex.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<>
class TSignal<MSWindowsSystem>
{
public:

    TSignal(TMutex<MSWindowsSystem>& mutex);    
    virtual ~TSignal();

    TMutex<MSWindowsSystem>&        mutex();
    const TMutex<MSWindowsSystem>&  mutex() const;

    void                            wait();
    void                            set();


private:

    TSignal();
    TSignal(const TSignal<MSWindowsSystem>& mutex);
    TSignal<MSWindowsSystem>&   operator=(const TSignal<MSWindowsSystem>& mutex);


private:

    TMutex<MSWindowsSystem>&    _mutex;
    TMutex<MSWindowsSystem>     _countMutex;
    klab::UInt32                _count;

    HANDLE                      _event;
};

// ---------------------------------------------------------------------------------------------------- //

inline TSignal<MSWindowsSystem>::TSignal(TMutex<MSWindowsSystem>& mutex) : 
_mutex(mutex), _countMutex(), _count(0),
_event(::CreateEvent (NULL, TRUE, FALSE, NULL))
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSignal<MSWindowsSystem>::~TSignal()
{
    if(_event != NULL)
        ::CloseHandle(_event);   
}

// ---------------------------------------------------------------------------------------------------- //

inline TMutex<MSWindowsSystem>& TSignal<MSWindowsSystem>::mutex()
{
    return _mutex;
}

// ---------------------------------------------------------------------------------------------------- //

inline const TMutex<MSWindowsSystem>& TSignal<MSWindowsSystem>::mutex() const
{
    return _mutex;
}

// ---------------------------------------------------------------------------------------------------- //

inline void TSignal<MSWindowsSystem>::wait()
{
    _countMutex.lock();
    ++_count;
    _countMutex.unlock();

    _mutex.unlock();
    DWORD result = ::WaitForSingleObject(_event, INFINITE);

    _countMutex.lock();
    --_count;
    bool isLast = (result==WAIT_OBJECT_0 && _count==0);
    _countMutex.unlock();

    if(isLast)
        ::ResetEvent(_event);

    _mutex.lock();
}

// ---------------------------------------------------------------------------------------------------- //

inline void TSignal<MSWindowsSystem>::set()
{
    _countMutex.lock();
    bool haveWaiters = (_count > 0);
    _countMutex.unlock(); 

    if(haveWaiters)
        ::SetEvent(_event);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
