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

#ifndef KLAB_SIMPLESIGNAL_H
#define KLAB_SIMPLESIGNAL_H

#include "Signal.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class System=CurrentSystem>
class TSimpleSignal
{
public:

    TSimpleSignal();    
    virtual ~TSimpleSignal();

    void                    wait(); 
    void                    set(); 


private:

    TSimpleSignal(const TSimpleSignal<System>& mutex);
    TSimpleSignal<System>&  operator=(const TSimpleSignal<System>& mutex);


private:

    klab::TMutex<System>    _mutex;
    klab::TSignal<System>   _signal;
};

// ---------------------------------------------------------------------------------------------------- //

typedef TSimpleSignal<CurrentSystem>    KSimpleSignal;

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSimpleSignal<System>::TSimpleSignal() : 
_mutex(), _signal(_mutex)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSimpleSignal<System>::~TSimpleSignal()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TSimpleSignal<System>::wait()
{
    _mutex.lock();
    _signal.wait();
    _mutex.unlock();
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TSimpleSignal<System>::set()
{
    _mutex.lock();
    _signal.set();
    _mutex.unlock();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
