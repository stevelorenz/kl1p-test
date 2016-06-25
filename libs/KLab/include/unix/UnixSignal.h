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

#ifndef KLAB_UNIXSIGNAL_H
#define KLAB_UNIXSIGNAL_H

#include "../SystemUtil.h"
#include "../Mutex.h"
#include <pthread.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<>
class TSignal<UnixSystem>
{
public:

    TSignal(TMutex<UnixSystem>& mutex);    
    virtual ~TSignal();
	
	TMutex<UnixSystem>&         mutex();
    const TMutex<UnixSystem>&	mutex() const;

    void                    	wait();
    void                    	set();


private:

    TSignal();
    TSignal(const TSignal<UnixSystem>& mutex);
    TSignal<UnixSystem>&	operator=(const TSignal<UnixSystem>& mutex);


private:

	TMutex<UnixSystem>&		_mutex;
    pthread_cond_t			_signal;
};

// ---------------------------------------------------------------------------------------------------- //

inline TSignal<UnixSystem>::TSignal(TMutex<UnixSystem>& mutex) : 
_mutex(mutex), _signal()
{
	pthread_cond_init (&_signal, NULL);
}

// ---------------------------------------------------------------------------------------------------- //

inline TSignal<UnixSystem>::~TSignal()
{
    pthread_cond_destroy(&_signal);
}

// ---------------------------------------------------------------------------------------------------- //

inline TMutex<UnixSystem>& TSignal<UnixSystem>::mutex()
{
    return _mutex;
}

// ---------------------------------------------------------------------------------------------------- //

inline const TMutex<UnixSystem>& TSignal<UnixSystem>::mutex() const
{
    return _mutex;
}

// ---------------------------------------------------------------------------------------------------- //

inline void TSignal<UnixSystem>::wait()
{
    pthread_cond_wait(&_signal, &(_mutex._mutex));
}

// ---------------------------------------------------------------------------------------------------- //

inline void TSignal<UnixSystem>::set()
{
    pthread_cond_signal(&_signal);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
