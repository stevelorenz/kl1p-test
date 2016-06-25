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

#ifndef KLAB_MACMODULE_H
#define KLAB_MACMODULE_H

#include "../SystemUtil.h"
#include "../StringUtil.h"
#include "../ScopedMutex.h"
#include <dlfcn.h>




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<>
class TModule<MacOSSystem>
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

    TModule(const TModule<MacOSSystem>& module);
    TModule<MacOSSystem>&	operator=(const TModule<MacOSSystem>& module);
	
	
private:

	klab::KMutex        _mutex;

    std::string         _path;
	void*				_module;
};

// ---------------------------------------------------------------------------------------------------- //

inline TModule<MacOSSystem>::TModule() : 
_path(), _module(0)
{}

// ---------------------------------------------------------------------------------------------------- //

inline TModule<MacOSSystem>::TModule(const std::string& path) : 
_path(path), _module(0)
{
	klab::TrimString(_path);
}

// ---------------------------------------------------------------------------------------------------- //

inline TModule<MacOSSystem>::~TModule()
{
    this->clean();
}

// ---------------------------------------------------------------------------------------------------- //

inline void TModule<MacOSSystem>::setPath(const std::string& path)
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

inline const std::string& TModule<MacOSSystem>::path() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _path;
}

// ---------------------------------------------------------------------------------------------------- //

inline void TModule<MacOSSystem>::load()
{
	klab::TScopedMutex<klab::KMutex> mutex(_mutex);
	
    if(_module != 0)
        this->clean();
		
	std::ostringstream oss;
    oss<<_path<<".dylib";

    _module = dlopen(oss.str().c_str(), RTLD_LAZY);

    ThrowTraceExceptionIf(KLoadModuleException, _module==0);
}

// ---------------------------------------------------------------------------------------------------- //

inline void TModule<MacOSSystem>::clean()
{
	klab::TScopedMutex<klab::KMutex> mutex(_mutex);
	
    if(_module != 0)
    {
        dlclose(_module);
        _module = 0;
    }
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TModule<MacOSSystem>::isLoaded() const
{
	klab::TScopedMutex<klab::KMutex> mutex(_mutex);
	
    return (_module != 0);
}

// ---------------------------------------------------------------------------------------------------- //

inline KModuleFunction TModule<MacOSSystem>::function(const std::string& name)
{
	klab::TScopedMutex<klab::KMutex> mutex(_mutex);
	
    ThrowTraceExceptionIf(KGetFunctionModuleException, _module==0);    

    KModuleFunction ret = static_cast<KModuleFunction>(dlsym(_module, name.c_str()));
    ThrowTraceExceptionIf(KGetFunctionModuleException, ret==0);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
