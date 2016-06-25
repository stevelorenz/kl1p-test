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

#ifndef KLAB_WINMODULE_H
#define KLAB_WINMODULE_H

#include "../SystemUtil.h"
#include "../include/ScopedMutex.h"
#include "../StringUtil.h"




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<>
class TModule<MSWindowsSystem>
{
public:

    TModule();
    TModule(const std::string& path);
    virtual ~TModule();

    void                setPath(const std::string& path);
    const std::string&  path() const;

    void                load();
    void                clean();
    bool                isLoaded() const;

    KModuleFunction     function(const std::string& name);


private:

    TModule(const TModule<MSWindowsSystem>& module);
    TModule<MSWindowsSystem>&   operator=(const TModule<MSWindowsSystem>& module);


private:

    klab::KMutex        _mutex;

    std::string         _path;
    HMODULE             _module;
};

// ---------------------------------------------------------------------------------------------------- //

inline TModule<MSWindowsSystem>::TModule() : 
_path(), _module(NULL)
{}

// ---------------------------------------------------------------------------------------------------- //

inline TModule<MSWindowsSystem>::TModule(const std::string& path) : 
_path(path), _module(NULL)
{
    klab::TrimString(_path);
}

// ---------------------------------------------------------------------------------------------------- //

inline TModule<MSWindowsSystem>::~TModule()
{
    this->clean();
}

// ---------------------------------------------------------------------------------------------------- //

inline void TModule<MSWindowsSystem>::setPath(const std::string& path)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(klab::Equals(_path, klab::ToTrimmedString(path)) == false)
    {
        this->clean();
        _path = path;

        klab::TrimString(_path);
    }
}

// ---------------------------------------------------------------------------------------------------- //

inline const std::string& TModule<MSWindowsSystem>::path() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _path;
}

// ---------------------------------------------------------------------------------------------------- //

inline void TModule<MSWindowsSystem>::load()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_module != NULL)
        this->clean();

    std::ostringstream oss;
    oss<<_path<<".dll";

    _module = ::LoadLibraryA(oss.str().c_str());

    ThrowTraceExceptionIf(KLoadModuleException, _module==NULL);
}

// ---------------------------------------------------------------------------------------------------- //

inline void TModule<MSWindowsSystem>::clean()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_module != NULL)
    {
        ::FreeLibrary(_module);
        _module = NULL;
    }
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TModule<MSWindowsSystem>::isLoaded() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return (_module != NULL);
}

// ---------------------------------------------------------------------------------------------------- //

inline KModuleFunction TModule<MSWindowsSystem>::function(const std::string& name)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    ThrowTraceExceptionIf(KGetFunctionModuleException, _module==NULL);    

    KModuleFunction ret = static_cast<KModuleFunction>(::GetProcAddress(_module, name.c_str()));
    ThrowTraceExceptionIf(KGetFunctionModuleException, ret==0);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
