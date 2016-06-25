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

#ifndef KLAB_SIGNAL_H
#define KLAB_SIGNAL_H

#include "TypeUtil.h"
#include "FuncUtil.h"
#include "SystemUtil.h"
#include "Mutex.h"
#include "TemplateUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class System=CurrentSystem>
class TSignal
{
public:

    TSignal(TMutex<System>& mutex);    
    virtual ~TSignal();

    TMutex<System>&         mutex();
    const TMutex<System>&   mutex() const;

    void                    wait(); // Must be used on locked mutex, and be unlocked after wait. 
    void                    set();  // Must be used on locked mutex, and be unlocked after set. 


private:

    TSignal();
    TSignal(const TSignal<System>& mutex);
    TSignal<System>&    operator=(const TSignal<System>& mutex);
};

// ---------------------------------------------------------------------------------------------------- //

typedef TSignal<CurrentSystem>  KSignal;

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSignal<System>::TSignal(TMutex<System>& mutex)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSignal<System>::~TSignal()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TMutex<System>& TSignal<System>::mutex()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline const TMutex<System>& TSignal<System>::mutex() const
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TSignal<System>::wait()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TSignal<System>::set()
{}

// ---------------------------------------------------------------------------------------------------- //

}

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_MSWINDOWS_SYSTEM)
    #include "win/WinSignal.h"  
#elif defined(KLAB_UNIX_SYSTEM)
    #include "unix/UnixSignal.h"   
#elif defined(KLAB_MACOS_SYSTEM)
    #include "macos/MacSignal.h"  
#endif

// ---------------------------------------------------------------------------------------------------- //


#endif
