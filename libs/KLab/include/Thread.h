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

#ifndef KLAB_THREAD_H
#define KLAB_THREAD_H

#include "TypeUtil.h"
#include "FuncUtil.h"
#include "SystemUtil.h"
#include "TemplateUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class IThreadStatus
{
public:

    virtual ~IThreadStatus() = 0;

    virtual bool    checkThreadState() const = 0;
};

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System=CurrentSystem>
class TThread : public IThreadStatus
{
public:

    TThread();    
    virtual ~TThread();
    
    bool            start();
    void            suspend();
    void            resume();
    void            stop();
    bool            isStarted() const;
    bool            isSuspended() const;
    bool   	 		isRunning() const;
	
    virtual bool    checkThreadState() const;

    void            join();


private:

    TThread(TClass& obj);   
    TThread(const TThread<TClass, TRunFunc, System>& thread);
    TThread<TClass, TRunFunc, System>&  operator=(const TThread<TClass, TRunFunc, System>& thread);
};

// ---------------------------------------------------------------------------------------------------- //

inline IThreadStatus::~IThreadStatus()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline TThread<TClass, TRunFunc, System>::TThread(TClass& obj) : IThreadStatus()
{
    KLAB_STATIC_ASSERT(sizeof(System)==0);     // Compile time validation. Equivalent to KLAB_STATIC_ASSERT(false). 
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline TThread<TClass, TRunFunc, System>::~TThread()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline bool TThread<TClass, TRunFunc, System>::start()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline void TThread<TClass, TRunFunc, System>::suspend()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline void TThread<TClass, TRunFunc, System>::resume()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline void TThread<TClass, TRunFunc, System>::stop()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline bool TThread<TClass, TRunFunc, System>::isStarted() const
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline bool TThread<TClass, TRunFunc, System>::isSuspended() const
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline bool TThread<TClass, TRunFunc, System>::isRunning() const
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline bool TThread<TClass, TRunFunc, System>::checkThreadState() const
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&), class System>
inline void TThread<TClass, TRunFunc, System>::join()
{}

// ---------------------------------------------------------------------------------------------------- //

}

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_MSWINDOWS_SYSTEM)
    #include "win/WinThread.h"  
#elif defined(KLAB_UNIX_SYSTEM)
    #include "unix/UnixThread.h"   
#elif defined(KLAB_MACOS_SYSTEM)
    #include "macos/MacThread.h"  
#endif

// ---------------------------------------------------------------------------------------------------- //


#endif
