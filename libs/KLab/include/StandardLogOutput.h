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

#ifndef KLAB_STANDARDLOGOUTPUT_H
#define KLAB_STANDARDLOGOUTPUT_H

#include "LogOutput.h"
#include "StringUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class TString=const klab::Char*, class TLogDataType=ILogData<TString> >
class TStandardLogOutput : public TLogOutput<TString, TLogDataType>
{
public:

    TStandardLogOutput();
    TStandardLogOutput(const KLogLevel& level);
    TStandardLogOutput(const KLogLevel& level, bool isEnabled);
    TStandardLogOutput(const TStandardLogOutput<TString, TLogDataType>& output);
    virtual ~TStandardLogOutput();

    TStandardLogOutput<TString, TLogDataType>&  operator=(const TStandardLogOutput<TString, TLogDataType>& output);


protected:

    virtual void            writeLog(const TLogDataType& log); 
};

// ---------------------------------------------------------------------------------------------------- //

typedef TStandardLogOutput<const klab::Char*, ILogData<const klab::Char*> >         KStandardLogOutput;
typedef TStandardLogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> > KWStandardLogOutput;

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TStandardLogOutput<TString, TLogDataType>::TStandardLogOutput() : TLogOutput<TString, TLogDataType>()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TStandardLogOutput<TString, TLogDataType>::TStandardLogOutput(const KLogLevel& level) : TLogOutput<TString, TLogDataType>(level)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TStandardLogOutput<TString, TLogDataType>::TStandardLogOutput(const KLogLevel& level, bool isEnabled) : TLogOutput<TString, TLogDataType>(level, isEnabled)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TStandardLogOutput<TString, TLogDataType>::TStandardLogOutput(const TStandardLogOutput<TString, TLogDataType>& output) : TLogOutput<TString, TLogDataType>(output)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TStandardLogOutput<TString, TLogDataType>::~TStandardLogOutput()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TStandardLogOutput<TString, TLogDataType>& TStandardLogOutput<TString, TLogDataType>::operator=(const TStandardLogOutput<TString, TLogDataType>& output)
{
    if(this != &output)
    {
        TLogOutput<TString, TLogDataType>::operator=(output);
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline void TStandardLogOutput<TString, TLogDataType>::writeLog(const TLogDataType& log)
{
#if defined(KLAB_MSWINDOWS_SYSTEM)
    ::OutputDebugString(std::string(klab::ConvertStringTo<std::string>(log.toString())+std::string("\n")).c_str());  
#elif defined(KLAB_UNIX_SYSTEM)
    std::cerr<<klab::ConvertStringTo<std::string>(log.toString())<<std::endl; 
#elif defined(KLAB_MACOS_SYSTEM)
    std::cerr<<klab::ConvertStringTo<std::string>(log.toString())<<std::endl;
#else
    std::cerr<<klab::ConvertStringTo<std::string>(log.toString())<<std::endl;
#endif
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
