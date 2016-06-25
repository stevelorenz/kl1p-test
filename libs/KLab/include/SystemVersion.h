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

#ifndef KLAB_SYSTEMVERSION_H
#define KLAB_SYSTEMVERSION_H

#include "SystemVersionImpl.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class System=CurrentSystem>
class TSystemVersion
{
public:

    TSystemVersion();
    TSystemVersion(const TSystemVersion<System>& system);
    virtual ~TSystemVersion();

    TSystemVersion<System>&     operator=(const TSystemVersion<System>& system);

    KOperatingSystemCode        code() const;
    KOperatingSystemCode        version() const;
    KOperatingSystemCode        subVersion() const;

    bool                        isMSWindows() const;
    bool                        isUnix() const;
    bool                        isMacOS() const;

    bool                        is16Bits() const;
    bool                        is32Bits() const;
    bool                        is64Bits() const;

    const std::string&          name() const;
    const std::string&          fullName() const;


private:

    KOperatingSystemCode        _code;

    std::string                 _name;
    std::string                 _fullName;
    klab::UInt8                 _wordSize;

    bool                        _isMSWindows;
    bool                        _isUnix;
    bool                        _isMacOS;
};

// ---------------------------------------------------------------------------------------------------- //

typedef TSystemVersion<CurrentSystem>   KSystemVersion;

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemVersion<System>::TSystemVersion() : 
_code(0),
_name(), _fullName(), _wordSize(),
_isMSWindows(false), _isUnix(false), _isMacOS(false)
{
    TSystemVersionImpl<System> impl;

    _code = impl.code();

    _name     = impl.name();
    _fullName = impl.fullName();
    _wordSize = impl.wordSize();

    _isMSWindows = impl.isMSWindows();
    _isUnix      = impl.isUnix();
    _isMacOS     = impl.isMacOS();
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemVersion<System>::TSystemVersion(const TSystemVersion<System>& system) : 
_code(system._code), 
_name(system._name), _fullName(system._fullName), _wordSize(system._wordSize),
_isMSWindows(system._isMSWindows), _isUnix(system._isUnix), _isMacOS(system._isMacOS)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemVersion<System>::~TSystemVersion()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TSystemVersion<System>& TSystemVersion<System>::operator=(const TSystemVersion<System>& system)
{
    if(this != &system)
    {
        _code = system._code;

        _name     = system._name;
        _fullName = system._fullName;
        _wordSize = system._wordSize;

        _isMSWindows = system._isMSWindows;
        _isUnix      = system._isUnix;
        _isMacOS     = system._isMacOS;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline KOperatingSystemCode TSystemVersion<System>::code() const
{
    return _code;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline KOperatingSystemCode TSystemVersion<System>::version() const
{
    return (_code & KLAB_OPERATINGSYSTEM_MASK);
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline KOperatingSystemCode TSystemVersion<System>::subVersion() const
{
    return (_code & KLAB_SUBVERSIONOPERATINGSYSTEM_MASK);
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemVersion<System>::isMSWindows() const
{
    return _isMSWindows;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemVersion<System>::isUnix() const
{
    return _isUnix;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemVersion<System>::isMacOS() const
{
    return _isMacOS;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemVersion<System>::is16Bits() const
{
    return (_wordSize == 16);
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemVersion<System>::is32Bits() const
{
    return (_wordSize == 32);
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TSystemVersion<System>::is64Bits() const
{
    return (_wordSize == 64); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline const std::string& TSystemVersion<System>::name() const
{
    return _name;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline const std::string& TSystemVersion<System>::fullName() const
{
    return _fullName;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
