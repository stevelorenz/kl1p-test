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

#ifndef KLAB_SYSTEMVERSIONIMPL_H
#define KLAB_SYSTEMVERSIONIMPL_H

#include "SystemUtil.h"
#include "TemplateUtil.h"




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<class System>
class TSystemVersionImpl
{
public:

    TSystemVersionImpl();
    TSystemVersionImpl(const TSystemVersionImpl<System>& system);
    virtual ~TSystemVersionImpl();

    TSystemVersionImpl<System>&     operator=(const TSystemVersionImpl<System>& system);

    KOperatingSystemCode            code();

    bool                            isMSWindows();
    bool                            isUnix();
    bool                            isMacOS();

    klab::UInt8                     wordSize();

    std::string                     name();
    std::string                     fullName();
};

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemVersionImpl<System>::TSystemVersionImpl()
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemVersionImpl<System>::TSystemVersionImpl(const TSystemVersionImpl<System>& system)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false).  
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemVersionImpl<System>::~TSystemVersionImpl()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemVersionImpl<System>& TSystemVersionImpl<System>::operator=(const TSystemVersionImpl<System>& system)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline KOperatingSystemCode TSystemVersionImpl<System>::code()
{
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemVersionImpl<System>::isMSWindows() 
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemVersionImpl<System>::isUnix()
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemVersionImpl<System>::isMacOS()
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline klab::UInt8 TSystemVersionImpl<System>::wordSize()
{
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline std::string TSystemVersionImpl<System>::name()
{
    return std::string();
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline std::string TSystemVersionImpl<System>::fullName()
{
    return std::string();
}

// ---------------------------------------------------------------------------------------------------- //

}

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_MSWINDOWS_SYSTEM)
    #include "win/WinSystemVersionImpl.h"
#elif defined(KLAB_UNIX_SYSTEM)
    #include "unix/UnixSystemVersionImpl.h"   
#elif defined(KLAB_MACOS_SYSTEM)
    #include "macos/MacSystemVersionImpl.h" 
#endif

// ---------------------------------------------------------------------------------------------------- //


#endif
