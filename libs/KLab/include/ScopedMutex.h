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

#ifndef KLAB_SCOPEDMUTEX_H
#define KLAB_SCOPEDMUTEX_H

#include "Mutex.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class MutexType, class System=CurrentSystem>
class TScopedMutex
{
public:

    TScopedMutex(MutexType& mutex); 
    TScopedMutex(const MutexType& mutex);  
    virtual ~TScopedMutex();


protected:

    void        lock();
    bool        tryToLock();
    void        unlock();
	
	
private:

	TScopedMutex();
	TScopedMutex(const TScopedMutex<MutexType, System>& mutex);
	TScopedMutex<MutexType, System>&	operator=(const TScopedMutex<MutexType, System>& mutex);
	
	
private:

	MutexType&			_mutex;
};

// ---------------------------------------------------------------------------------------------------- //

typedef TScopedMutex<TMutex<CurrentSystem>, CurrentSystem>		KScopedMutex;

// ---------------------------------------------------------------------------------------------------- //

template<class MutexType, class System>
inline TScopedMutex<MutexType, System>::TScopedMutex(MutexType& mutex) : 
_mutex(mutex)
{
    _mutex.lock();
}

// ---------------------------------------------------------------------------------------------------- //

template<class MutexType, class System>
inline TScopedMutex<MutexType, System>::TScopedMutex(const MutexType& mutex) : 
_mutex(const_cast<MutexType&>(mutex))
{
    _mutex.lock();
}

// ---------------------------------------------------------------------------------------------------- //

template<class MutexType, class System>
inline TScopedMutex<MutexType, System>::~TScopedMutex()
{
    _mutex.unlock();
}

// ---------------------------------------------------------------------------------------------------- //

template<class MutexType, class System>
inline void TScopedMutex<MutexType, System>::lock()
{
    _mutex.lock();
}

// ---------------------------------------------------------------------------------------------------- //

template<class MutexType, class System>
inline bool TScopedMutex<MutexType, System>::tryToLock()
{
    return _mutex.tryToLock();
}

// ---------------------------------------------------------------------------------------------------- //

template<class MutexType, class System>
inline void TScopedMutex<MutexType, System>::unlock()
{
    _mutex.unlock();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
