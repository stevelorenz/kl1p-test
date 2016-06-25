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

#ifndef KLAB_FILELOGOUTPUT_H
#define KLAB_FILELOGOUTPUT_H

#include "LogOutput.h"
#include <fstream>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
struct TFileLogOutputStream
{
    typedef std::ofstream   Type;
};

template<>
struct TFileLogOutputStream<const klab::Char*>
{
    typedef std::ofstream   Type;
};

template<>
struct TFileLogOutputStream<const klab::WideChar*>
{
    typedef std::wofstream  Type;
};

// ---------------------------------------------------------------------------------------------------- //

template<class TString=const klab::Char*, class TLogDataType=ILogData<TString> >
class TFileLogOutput : public TLogOutput<TString, TLogDataType>
{
public:
   
    TFileLogOutput(const std::string& path);
    TFileLogOutput(const std::string& path, bool append);
    TFileLogOutput(const std::string& path, bool append, const KLogLevel& level);
    TFileLogOutput(const std::string& path, bool append, const KLogLevel& level, bool isEnabled);
    virtual ~TFileLogOutput();    


protected:

    virtual void            writeLog(const TLogDataType& log); 


private:

    TFileLogOutput();  
    TFileLogOutput(const TFileLogOutput<TString, TLogDataType>& output);
    TFileLogOutput<TString, TLogDataType>&  operator=(const TFileLogOutput<TString, TLogDataType>& output);


private:

    typename TFileLogOutputStream<TString>::Type    _file;
};

// ---------------------------------------------------------------------------------------------------- //

typedef TFileLogOutput<const klab::Char*, ILogData<const klab::Char*> >         KFileLogOutput;
typedef TFileLogOutput<const klab::WideChar*, ILogData<const klab::WideChar*> > KWFileLogOutput;

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TFileLogOutput<TString, TLogDataType>::TFileLogOutput(const std::string& path) : TLogOutput<TString, TLogDataType>(),
_file()
{
    _file.open(path.c_str());
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TFileLogOutput<TString, TLogDataType>::TFileLogOutput(const std::string& path, bool append) : TLogOutput<TString, TLogDataType>(),
_file()
{
    if(append)  _file.open(path.c_str(), std::ios::app);
    else        _file.open(path.c_str());
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TFileLogOutput<TString, TLogDataType>::TFileLogOutput(const std::string& path, bool append, const KLogLevel& level) : TLogOutput<TString, TLogDataType>(level),
_file()
{
    if(append)  _file.open(path.c_str(), std::ios::app);
    else        _file.open(path.c_str());
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TFileLogOutput<TString, TLogDataType>::TFileLogOutput(const std::string& path, bool append, const KLogLevel& level, bool isEnabled) : TLogOutput<TString, TLogDataType>(level, isEnabled),
_file()
{
    if(append)  _file.open(path.c_str(), std::ios::app);
    else        _file.open(path.c_str());
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline TFileLogOutput<TString, TLogDataType>::~TFileLogOutput()
{
    _file.close();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString, class TLogDataType>
inline void TFileLogOutput<TString, TLogDataType>::writeLog(const TLogDataType& log)
{
    if(_file.is_open())
    {
        if(log.level()<klab::WARNING_LOG)   _file<<log.toString()<<std::endl;
        else                                _file<<log.toFullString()<<std::endl;

        _file.flush();
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
