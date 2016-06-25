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

#ifndef KLAB_UNIXMUTEX_H
#define KLAB_UNIXMUTEX_H

#include "../SystemUtil.h"
#include <pthread.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class System> 
class TSignal;
	
// ---------------------------------------------------------------------------------------------------- //

template<>
class TMutex<UnixSystem>
{
public:

    TMutex();    
    virtual ~TMutex();

    void				lock();
    bool				tryToLock();
    void				unlock();


private:

    TMutex(const TMutex<UnixSystem>& mutex);
    TMutex<UnixSystem>&	operator=(const TMutex<UnixSystem>& mutex);
	

private:

    friend class TSignal<UnixSystem>;


private:

	pthread_mutexattr_t	_attr;
    pthread_mutex_t		_mutex;
	klab::UInt32 		_count;
};

// ---------------------------------------------------------------------------------------------------- //

inline TMutex<UnixSystem>::TMutex() : 
_attr(), _mutex(), _count(0)
{
	pthread_mutexattr_init(&_attr);
	pthread_mutexattr_settype(&_attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&_mutex, &_attr);
}

// ---------------------------------------------------------------------------------------------------- //

inline TMutex<UnixSystem>::~TMutex()
{
	pthread_mutex_destroy(&_mutex);
}

// ---------------------------------------------------------------------------------------------------- //

inline void TMutex<UnixSystem>::lock()
{
    pthread_mutex_lock(&_mutex);
	++_count;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TMutex<UnixSystem>::tryToLock()
{
    bool ret = (pthread_mutex_trylock(&_mutex) == 0);
	if(ret)
        ++_count;

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

inline void TMutex<UnixSystem>::unlock()
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
