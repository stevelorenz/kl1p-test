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

#ifndef LOKO_ILOGOUTPUT_H
#define LOKO_ILOGOUTPUT_H

#include "ILogData.h"
#include "Pointer.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class TString=const klab::Char*, class TLogDataType=ILogData<TString> >
class ILogOutput
{
public:

	virtual ~ILogOutput() = 0;

    virtual void                setLevel(const KLogLevel& level) = 0;
    virtual void                setEnabled(bool isEnabled) = 0;
    virtual KLogLevel           level() const = 0;
    virtual bool                isEnabled() const = 0;

    virtual void                write(const TLogDataType& log) = 0;


protected:

    virtual klab::UInt32        countReferences() const = 0;
    virtual klab::UInt32        incrementReferencesCount() = 0;
    virtual klab::UInt32        decrementReferencesCount() = 0;

    template<class UString, class ULogDataType>
    friend void                 AddSmartPointerReference(ILogOutput<UString, ULogDataType>* ptr);
    template<class UString, class ULogDataType>
    friend void                 ReleaseSmartPointerReference(ILogOutput<UString, ULogDataType>* ptr);
};

// ---------------------------------------------------------------------------------------------------- //

typedef klab::TSmartPointer<ILogOutput<const klab::Char*, ILogData<const klab::Char*> > >               ILogOutputPtr;
typedef klab::TSmartPointer<const ILogOutput<const klab::Char*, ILogData<const klab::Char*> > >         ILogOutputConstPtr;
typedef klab::TSmartPointer<ILogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> > >       IWLogOutputPtr;
typedef klab::TSmartPointer<const ILogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> > > IWLogOutputConstPtr;

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline ILogOutput<TString, TLogDataType>::~ILogOutput()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class UString, class ULogDataType>
inline void AddSmartPointerReference(ILogOutput<UString, ULogDataType>* ptr)
{
    if(ptr != 0)
        ptr->incrementReferencesCount();
}

// ---------------------------------------------------------------------------------------------------- //

template<class UString, class ULogDataType>
inline void ReleaseSmartPointerReference(ILogOutput<UString, ULogDataType>* ptr)
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
