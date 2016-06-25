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

#ifndef KLAB_MACMUTEX_H
#define KLAB_MACMUTEX_H

#include "../SystemUtil.h"
#include <pthread.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class System> 
class TSignal;
	
// ---------------------------------------------------------------------------------------------------- //

template<>
class TMutex<MacOSSystem>
{
public:

    TMutex();    
    virtual ~TMutex();

    void				lock();
    bool				tryToLock();
    void				unlock();


private:

    TMutex(const TMutex<MacOSSystem>& mutex);
    TMutex<MacOSSystem>&	operator=(const TMutex<MacOSSystem>& mutex);
	

private:

    friend class TSignal<MacOSSystem>;


private:

	pthread_mutexattr_t	_attr;
    pthread_mutex_t		_mutex;
	klab::UInt32 		_count;
};

// ---------------------------------------------------------------------------------------------------- //

inline TMutex<MacOSSystem>::TMutex() : 
_attr(), _mutex(), _count(0)
{
	pthread_mutexattr_init(&_attr);
	pthread_mutexattr_settype(&_attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&_mutex, &_attr);
}

// ---------------------------------------------------------------------------------------------------- //

inline TMutex<MacOSSystem>::~TMutex()
{
	pthread_mutex_destroy(&_mutex);
}

// ---------------------------------------------------------------------------------------------------- //

inline void TMutex<MacOSSystem>::lock()
{
    pthread_mutex_lock(&_mutex);
	++_count;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TMutex<MacOSSystem>::tryToLock()
{
    bool ret = (pthread_mutex_trylock(&_mutex) == 0);
	if(ret)
        ++_count;

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

inline void TMutex<MacOSSystem>::unlock()
{
	if(_count > 0)
    {
		--_count;
		pthread_mutex_unlock(&_mutex);			
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
