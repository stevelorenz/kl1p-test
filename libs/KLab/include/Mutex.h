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

#ifndef KLAB_MUTEX_H
#define KLAB_MUTEX_H

#include "TypeUtil.h"
#include "FuncUtil.h"
#include "SystemUtil.h"
#include "TemplateUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class System=CurrentSystem>
class TMutex
{
public:

    TMutex();    
    virtual ~TMutex();

    void                lock();
    bool                tryToLock();
    void                unlock();


private:

    TMutex(const TMutex<System>& mutex);
    TMutex<System>&     operator=(const TMutex<System>& mutex);
};

// ---------------------------------------------------------------------------------------------------- //

typedef TMutex<CurrentSystem>   KMutex;

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TMutex<System>::TMutex()
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TMutex<System>::~TMutex()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TMutex<System>::lock()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TMutex<System>::tryToLock()
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TMutex<System>::unlock()
{}

// ---------------------------------------------------------------------------------------------------- //

}

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_MSWINDOWS_SYSTEM)
    #include "win/WinMutex.h"   
#elif defined(KLAB_UNIX_SYSTEM)
    #include "unix/UnixMutex.h"   
#elif defined(KLAB_MACOS_SYSTEM)
    #include "macos/MacMutex.h"  
#endif

// ---------------------------------------------------------------------------------------------------- //


#endif
