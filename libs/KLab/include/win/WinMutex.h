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

#ifndef KLAB_WINMUTEX_H
#define KLAB_WINMUTEX_H

#include "../SystemUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<>
class TMutex<MSWindowsSystem>
{
public:

    TMutex();    
    virtual ~TMutex();

    void                    lock();
    bool                    tryToLock();
    void                    unlock();


private:

    TMutex(const TMutex<MSWindowsSystem>& mutex);
    TMutex<MSWindowsSystem>&    operator=(const TMutex<MSWindowsSystem>& mutex);


private:

    CRITICAL_SECTION        _criticalSection;
    klab::UInt32            _count;
};

// ---------------------------------------------------------------------------------------------------- //

inline TMutex<MSWindowsSystem>::TMutex() : 
_criticalSection(), _count(0)
{
    ::InitializeCriticalSection(&_criticalSection);
}

// ---------------------------------------------------------------------------------------------------- //

inline TMutex<MSWindowsSystem>::~TMutex()
{
    ::DeleteCriticalSection(&_criticalSection);
}

// ---------------------------------------------------------------------------------------------------- //

inline void TMutex<MSWindowsSystem>::lock()
{
    ::EnterCriticalSection(&_criticalSection);
    ++_count;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TMutex<MSWindowsSystem>::tryToLock()
{
    bool ret = (::TryEnterCriticalSection(&_criticalSection) == TRUE);
    if(ret)
        ++_count;

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

inline void TMutex<MSWindowsSystem>::unlock()
{
    if(_count > 0)
    {
        --_count;
        ::LeaveCriticalSection(&_criticalSection);        
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
