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

#ifndef KLAB_LOGOUTPUT_H
#define KLAB_LOGOUTPUT_H

#include "ILogOutput.h"
#include "ScopedMutex.h"
#include "Pointer.h"
#include "AtomicCount.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class TString=const klab::Char*, class TLogDataType=ILogData<TString> >
class TLogOutput : public virtual ILogOutput<TString, TLogDataType>
{
public:

    TLogOutput();
    TLogOutput(const KLogLevel& level);
    TLogOutput(const KLogLevel& level, bool isEnabled);
    TLogOutput(const TLogOutput<TString, TLogDataType>& output);
    virtual ~TLogOutput();

    TLogOutput<TString, TLogDataType>&  operator=(const TLogOutput<TString, TLogDataType>& output);

    void                        setLevel(const KLogLevel& level);
    void                        setEnabled(bool isEnabled);
    KLogLevel                   level() const;
    bool                        isEnabled() const;

    void                        write(const TLogDataType& log);


protected:

    virtual void                writeLog(const TLogDataType& log) = 0; 

    KMutex&                     mutex();
    const KMutex&               mutex() const;

    klab::UInt32                countReferences() const;
    klab::UInt32                incrementReferencesCount();
    klab::UInt32                decrementReferencesCount();

    template<class T, class U>
    friend void                 AddSmartPointerReference(TLogOutput<T, U>* ptr);
    template<class T, class U>
    friend void                 ReleaseSmartPointerReference(TLogOutput<T, U>* ptr);


private:

    KMutex                      _mutex;
    
    KLogLevel                   _level;
    bool                        _isEnabled; 

    mutable klab::TAtomicCount<klab::UInt32>    _countReferences;
};

// ---------------------------------------------------------------------------------------------------- //

typedef TLogOutput<const klab::Char*, ILogData<const klab::Char*> >         KLogOutput;
typedef TLogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> > KWLogOutput;

typedef klab::TSmartPointer<KLogOutput>                                     KLogOutputPtr;
typedef klab::TSmartPointer<const KLogOutput>                               KLogOutputConstPtr;
typedef klab::TSmartPointer<KWLogOutput>                                    KWLogOutputPtr;
typedef klab::TSmartPointer<const KWLogOutput>                              KWLogOutputConstPtr;

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutput<TString, TLogDataType>::TLogOutput() : ILogOutput<TString, TLogDataType>(), 
_mutex(),
_level(klab::DEBUG_LOG), _isEnabled(true),
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutput<TString, TLogDataType>::TLogOutput(const KLogLevel& level) : ILogOutput<TString, TLogDataType>(), 
_mutex(), 
_level(level), _isEnabled(true),
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutput<TString, TLogDataType>::TLogOutput(const KLogLevel& level, bool isEnabled) : ILogOutput<TString, TLogDataType>(),  
_mutex(),
_level(level), _isEnabled(isEnabled),
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutput<TString, TLogDataType>::TLogOutput(const TLogOutput<TString, TLogDataType>& output) : ILogOutput<TString, TLogDataType>(),  
_mutex(),
_level(output._level), _isEnabled(output._isEnabled),
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutput<TString, TLogDataType>::~TLogOutput()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutput<TString, TLogDataType>& TLogOutput<TString, TLogDataType>::operator=(const TLogOutput<TString, TLogDataType>& output)
{
    TScopedMutex<KMutex> mutex(_mutex);

    if(this != &output)
    {
        _level     = output._level;
        _isEnabled = output._isEnabled;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline void TLogOutput<TString, TLogDataType>::setLevel(const KLogLevel& level)
{
    TScopedMutex<KMutex> mutex(_mutex);

    _level = level;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline void TLogOutput<TString, TLogDataType>::setEnabled(bool isEnabled)
{
    TScopedMutex<KMutex> mutex(_mutex);

    _isEnabled = isEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline KLogLevel TLogOutput<TString, TLogDataType>::level() const
{
    TScopedMutex<KMutex> mutex(_mutex);

    return _level;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline bool TLogOutput<TString, TLogDataType>::isEnabled() const
{
    TScopedMutex<KMutex> mutex(_mutex);

    return _isEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline void TLogOutput<TString, TLogDataType>::write(const TLogDataType& log)
{
    TScopedMutex<KMutex> mutex(_mutex);

    if(_isEnabled && log.level()>=_level)
        this->writeLog(log);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline KMutex& TLogOutput<TString, TLogDataType>::mutex()
{
    return _mutex;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline const KMutex& TLogOutput<TString, TLogDataType>::mutex() const
{
    return _mutex;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline klab::UInt32 TLogOutput<TString, TLogDataType>::countReferences() const
{
    return _countReferences;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline klab::UInt32 TLogOutput<TString, TLogDataType>::incrementReferencesCount()
{
    return (++_countReferences);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline klab::UInt32 TLogOutput<TString, TLogDataType>::decrementReferencesCount()
{
    return (--_countReferences);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
inline void AddSmartPointerReference(TLogOutput<T, U>* ptr)
{
    if(ptr != 0)
        ptr->incrementReferencesCount();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
inline void ReleaseSmartPointerReference(TLogOutput<T, U>* ptr)
{
    if(ptr != 0)
    {
        if(ptr->decrementReferencesCount() == 0)
            klab::CheckedDelete(ptr);
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
