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

#ifndef KLAB_MACSIGNAL_H
#define KLAB_MACSIGNAL_H

#include "../SystemUtil.h"
#include "../Mutex.h"
#include <pthread.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<>
class TSignal<MacOSSystem>
{
public:

    TSignal(TMutex<MacOSSystem>& mutex);    
    virtual ~TSignal();
	
	TMutex<MacOSSystem>&         mutex();
    const TMutex<MacOSSystem>&	mutex() const;

    void                    	wait();
    void                    	set();


private:

    TSignal();
    TSignal(const TSignal<MacOSSystem>& mutex);
    TSignal<MacOSSystem>&	operator=(const TSignal<MacOSSystem>& mutex);


private:

	TMutex<MacOSSystem>&		_mutex;
    pthread_cond_t			_signal;
};

// ---------------------------------------------------------------------------------------------------- //

inline TSignal<MacOSSystem>::TSignal(TMutex<MacOSSystem>& mutex) : 
_mutex(mutex), _signal()
{
	pthread_cond_init (&_signal, NULL);
}

// ---------------------------------------------------------------------------------------------------- //

inline TSignal<MacOSSystem>::~TSignal()
{
    pthread_cond_destroy(&_signal);
}

// ---------------------------------------------------------------------------------------------------- //

inline TMutex<MacOSSystem>& TSignal<MacOSSystem>::mutex()
{
    return _mutex;
}

// ---------------------------------------------------------------------------------------------------- //

inline const TMutex<MacOSSystem>& TSignal<MacOSSystem>::mutex() const
{
    return _mutex;
}

// ---------------------------------------------------------------------------------------------------- //

inline void TSignal<MacOSSystem>::wait()
{
    pthread_cond_wait(&_signal, &(_mutex._mutex));
}

// ---------------------------------------------------------------------------------------------------- //

inline void TSignal<MacOSSystem>::set()
{
    pthread_cond_signal(&_signal);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
