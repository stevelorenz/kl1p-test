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

#ifndef KLAB_LOG_H
#define KLAB_LOG_H

#include "LogOutputManager.h"
#include "LogData.h"
#include "Singleton.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
struct TLogStream
{
    typedef std::ostringstream  Type;
};

template<>
struct TLogStream<const klab::Char*>
{
    typedef std::ostringstream  Type;
};

template<>
struct TLogStream<const klab::WideChar*>
{
    typedef std::wostringstream Type;
};

// ---------------------------------------------------------------------------------------------------- //

template<class TString=const klab::Char*, class TLogDataType=TLogData<TString>, class TLogOutputType=TLogOutput<TString, ILogData<TString> > >
class TLog
{
public:

    TLog();
    TLog(const KLogLevel& level);
    TLog(const KLogLevel& level, const TString& file, klab::UInt32 line, const TString& function);
    virtual ~TLog();

    typename TLogStream<TString>::Type& stream();  


private:

    TLog(const TLog<TString, TLogDataType, TLogOutputType>& log);
    TLog<TString, TLogDataType, TLogOutputType>&    operator=(const TLog<TString, TLogDataType, TLogOutputType>& log);
    

private:
    
    TLogDataType                        _log;
    typename TLogStream<TString>::Type  _messageBuffer;
};

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType, class TLogOutputType>
inline TLog<TString, TLogDataType, TLogOutputType>::TLog() : 
_log(klab::INFO_LOG), _messageBuffer()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType, class TLogOutputType>
inline TLog<TString, TLogDataType, TLogOutputType>::TLog(const KLogLevel& level) : 
_log(level), _messageBuffer()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType, class TLogOutputType>
inline TLog<TString, TLogDataType, TLogOutputType>::TLog(const KLogLevel& level, const TString& file, klab::UInt32 line, const TString& function) : 
_log(level, file, line, function), _messageBuffer()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType, class TLogOutputType>
inline TLog<TString, TLogDataType, TLogOutputType>::~TLog()
{
    _log.setMessage(_messageBuffer.str().c_str());
    klab::TSingleton<TLogOutputType>::Instance().write(_log);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType, class TLogOutputType>
inline typename TLogStream<TString>::Type& TLog<TString, TLogDataType, TLogOutputType>::stream()
{
    return _messageBuffer;
}

// ---------------------------------------------------------------------------------------------------- //

#define LOG(level) klab::TLog<const klab::Char*, klab::TLogData<const klab::Char*>, klab::TLogOutputManager<const klab::Char*, klab::ILogData<const klab::Char*> > >(level, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__).stream()
#define WLOG(level) klab::TLog<const klab::WideChar*, klab::TLogData<const klab::WideChar*>, klab::TLogOutputManager<const klab::WideChar*, klab::ILogData<const klab::WideChar*> > >(level, klab::ToWString(KLAB__FILE__).c_str(), KLAB__LINE__, klab::ToWString(KLAB__FUNC__).c_str()).stream()

// ---------------------------------------------------------------------------------------------------- //

}


#endif
