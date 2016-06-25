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

#ifndef KLAB_MODULE_H
#define KLAB_MODULE_H

#include "SystemUtil.h"
#include "Exception.h"
#include "TemplateUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KModuleException, KException)
KLAB_DECLARE_EXCEPTION(KLoadModuleException, KModuleException)
KLAB_DECLARE_EXCEPTION(KGetFunctionModuleException, KModuleException)

// ---------------------------------------------------------------------------------------------------- //

typedef void*   KModuleFunction;
  
// ---------------------------------------------------------------------------------------------------- //

template<class System=CurrentSystem>
class TModule
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

    TModule(const TModule<System>& module);
    TModule<System>&    operator=(const TModule<System>& module);
};

// ---------------------------------------------------------------------------------------------------- //

typedef TModule<CurrentSystem>  KModule;

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TModule<System>::TModule()
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TModule<System>::TModule(const std::string& path)
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline TModule<System>::~TModule()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TModule<System>::setPath(const std::string& path)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline const std::string& TModule<System>::path() const
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TModule<System>::load()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline void TModule<System>::clean()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline bool TModule<System>::isLoaded() const
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class System>
inline KModuleFunction TModule<System>::function(const std::string& name)
{
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T    CastModuleFunctionTo(KModuleFunction func)
{
    return (T)func;
}

// ---------------------------------------------------------------------------------------------------- //

}

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_MSWINDOWS_SYSTEM)
    #include "win/WinModule.h"  
#elif defined(KLAB_UNIX_SYSTEM)
    #include "unix/UnixModule.h"   
#elif defined(KLAB_MACOS_SYSTEM)
    #include "macos/MacModule.h" 
#endif

// ---------------------------------------------------------------------------------------------------- //


#endif
