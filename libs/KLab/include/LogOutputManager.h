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

#ifndef KLAB_LOGOUTPUTMANAGER_H
#define KLAB_LOGOUTPUTMANAGER_H

#include "LogOutput.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class TString=const klab::Char*, class TLogDataType=ILogData<TString> >
class TLogOutputManager : public TLogOutput<TString, TLogDataType>
{
public:

    TLogOutputManager();
    TLogOutputManager(const KLogLevel& level);
    TLogOutputManager(const KLogLevel& level, bool isEnabled);
    TLogOutputManager(const TLogOutputManager<TString, TLogDataType>& manager);
    virtual ~TLogOutputManager();

    TLogOutputManager<TString, TLogDataType>&   operator=(const TLogOutputManager<TString, TLogDataType>& manager);

    void                    clear();

    void                    registerLogOutput(klab::TSmartPointer<ILogOutput<TString, TLogDataType> > output);
    void                    clearLogOutputs();

    klab::UInt32            countLogOutputs() const;
    klab::TSmartPointer<ILogOutput<TString, TLogDataType> > logOutput(klab::UInt32 i) const;


protected:

    virtual void            writeLog(const TLogDataType& log); 


private:

    typedef std::vector<klab::TSmartPointer<ILogOutput<TString, TLogDataType> > >   KLogOutputArray;


private:
    
    KLogOutputArray         _outputs;
};

// ---------------------------------------------------------------------------------------------------- //

typedef TLogOutputManager<const klab::Char*, ILogData<const klab::Char*> >          KLogOutputManager;
typedef TLogOutputManager<const klab::WideChar*, ILogData<const klab::WideChar*> >  KWLogOutputManager;

typedef klab::TSmartPointer<KLogOutputManager>                                      KLogOutputManagerPtr;
typedef klab::TSmartPointer<const KLogOutputManager>                                KLogOutputManagerConstPtr;
typedef klab::TSmartPointer<KWLogOutputManager>                                     KWLogOutputManagerPtr;
typedef klab::TSmartPointer<const KWLogOutputManager>                               KWLogOutputManagerConstPtr;

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutputManager<TString, TLogDataType>::TLogOutputManager() : TLogOutput<TString, TLogDataType>(),
_outputs()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutputManager<TString, TLogDataType>::TLogOutputManager(const KLogLevel& level) : TLogOutput<TString, TLogDataType>(level), 
_outputs()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutputManager<TString, TLogDataType>::TLogOutputManager(const KLogLevel& level, bool isEnabled) : TLogOutput<TString, TLogDataType>(level, isEnabled), 
_outputs()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutputManager<TString, TLogDataType>::TLogOutputManager(const TLogOutputManager<TString, TLogDataType>& manager) : TLogOutput<TString, TLogDataType>(manager),
_outputs(manager._outputs)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutputManager<TString, TLogDataType>::~TLogOutputManager()
{
    this->clear();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TLogOutputManager<TString, TLogDataType>& TLogOutputManager<TString, TLogDataType>::operator=(const TLogOutputManager<TString, TLogDataType>& manager)
{
    TScopedMutex<KMutex> mutex(this->mutex());

    if(this != &manager)
    {
        TLogOutput<TString, TLogDataType>::operator=(manager);

        _outputs = manager._outputs;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline void TLogOutputManager<TString, TLogDataType>::clear()
{
    this->clearLogOutputs();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline void TLogOutputManager<TString, TLogDataType>::registerLogOutput(klab::TSmartPointer<ILogOutput<TString, TLogDataType> > output)
{
    TScopedMutex<KMutex> mutex(this->mutex());

    if(output.get() != 0)
        _outputs.push_back(output);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline void TLogOutputManager<TString, TLogDataType>::clearLogOutputs()
{
    TScopedMutex<KMutex> mutex(this->mutex());

    _outputs.clear();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline klab::UInt32 TLogOutputManager<TString, TLogDataType>::countLogOutputs() const
{
    TScopedMutex<KMutex> mutex(this->mutex());

    return static_cast<klab::UInt32>(_outputs.size());
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline klab::TSmartPointer<ILogOutput<TString, TLogDataType> > TLogOutputManager<TString, TLogDataType>::logOutput(klab::UInt32 i) const
{
    TScopedMutex<KMutex> mutex(this->mutex());

    if(i < static_cast<klab::UInt32>(_outputs.size()))  return _outputs[i];
    else                                                return klab::TSmartPointer<ILogOutput<TString, TLogDataType> >(0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline void TLogOutputManager<TString, TLogDataType>::writeLog(const TLogDataType& log)
{
    TScopedMutex<KMutex> mutex(this->mutex());

    klab::UInt32 size = static_cast<klab::UInt32>(_outputs.size());
    for(klab::UInt32 i=0; i<size; ++i)
        _outputs[i]->write(log);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
