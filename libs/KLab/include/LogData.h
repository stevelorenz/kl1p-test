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

#ifndef KLAB_LOGDATA_H
#define KLAB_LOGDATA_H

#include "ILogData.h"
#include "FuncUtil.h"
#include "StringUtil.h"
#include "SystemTime.h"
#include "DateTime.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
struct TLogDataString
{
    typedef std::string     Type;
};

template<>
struct TLogDataString<const klab::Char*>
{
    typedef std::string     Type;
};

template<>
struct TLogDataString<const klab::WideChar*>
{
    typedef std::wstring    Type;
};

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
struct TLogDataOutputStream
{
    typedef std::ostringstream  Type;
};

template<>
struct TLogDataOutputStream<const klab::Char*>
{
    typedef std::ostringstream  Type;
};

template<>
struct TLogDataOutputStream<const klab::WideChar*>
{
    typedef std::wostringstream Type;
};

// ---------------------------------------------------------------------------------------------------- //

template<class TString=const klab::Char*>
class TLogData : public virtual ILogData<TString>
{
public:

    TLogData();
    TLogData(const KLogLevel& level);
    TLogData(const KLogLevel& level, const TString& message);
    TLogData(const KLogLevel& level, const TString& message, klab::KMillisecTimestamp timestamp);
    TLogData(const KLogLevel& level, const TString& file, klab::UInt32 line, const TString& function);
    TLogData(const KLogLevel& level, const TString& message, const TString& file, klab::UInt32 line, const TString& function);
    TLogData(const KLogLevel& level, const TString& message, klab::KMillisecTimestamp timestamp, const TString& file, klab::UInt32 line, const TString& function);
    TLogData(const TLogData<TString>& data);
    virtual ~TLogData();

    TLogData<TString>&              operator=(const TLogData<TString>& data);

    void                            set(const KLogLevel& level, const TString& message);
    void                            set(const KLogLevel& level, const TString& message, klab::KMillisecTimestamp timestamp);
    void                            set(const KLogLevel& level, const TString& message, const TString& file, klab::UInt32 line, const TString& function);
    void                            set(const KLogLevel& level, const TString& message, klab::KMillisecTimestamp timestamp, const TString& file, klab::UInt32 line, const TString& function);
    void                            setLevel(const KLogLevel& level);
    void                            setMessage(const TString& message);
    void                            setTimestamp(klab::KMillisecTimestamp timestamp);
    void                            updateTimestamp();
    void                            setFile(const TString& file);
    void                            setLine(klab::UInt32 line);
    void                            setFunction(const TString& function);
    
    KLogLevel                       level() const;
    TString                         message() const;
    klab::KMillisecTimestamp        timestamp() const;
    TString                         file() const;
    klab::UInt32                    line() const;
    TString                         function() const;

    TString                         levelToString() const;
    TString                         timestampToString() const;
    TString                         lineToString() const;

    TString                         toString() const;
    TString                         toFullString() const;


protected:

    void                            updateLevelString();
    void                            updateTimestampString();
    void                            updateLineString();
    void                            updateString();
    void                            updateFullString();


private:
    
    KLogLevel                               _level;
    typename TLogDataString<TString>::Type  _message;
    klab::KMillisecTimestamp                _timestamp;

    typename TLogDataString<TString>::Type  _file;      
    klab::UInt32                            _line;      
    typename TLogDataString<TString>::Type  _function;  

    typename TLogDataString<TString>::Type  _levelString; 
    typename TLogDataString<TString>::Type  _timestampString; 
    typename TLogDataString<TString>::Type  _lineString; 
    typename TLogDataString<TString>::Type  _string; 
    typename TLogDataString<TString>::Type  _fullString; 
};

// ---------------------------------------------------------------------------------------------------- //

typedef TLogData<const klab::Char*>         KLogData;
typedef TLogData<const klab::WideChar*>     KWLogData;

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>::TLogData() : ILogData<TString>(),
_level(klab::INFO_LOG), _message(), _timestamp(KSystemTime::GetCurrentMillisecTimestamp()),
_file(), _line(0), _function(),
_levelString(), _timestampString(), _lineString(), _string(), _fullString() 
{
    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>::TLogData(const KLogLevel& level) : ILogData<TString>(), 
_level(level), _message(), _timestamp(KSystemTime::GetCurrentMillisecTimestamp()),
_file(), _line(0), _function(),
_levelString(), _timestampString(), _lineString(), _string(), _fullString() 
{
    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>::TLogData(const KLogLevel& level, const TString& message) : ILogData<TString>(), 
_level(level), _message(message), _timestamp(KSystemTime::GetCurrentMillisecTimestamp()),
_file(), _line(0), _function(),
_levelString(), _timestampString(), _lineString(), _string(), _fullString() 
{
    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>::TLogData(const KLogLevel& level, const TString& message, klab::KMillisecTimestamp timestamp) : ILogData<TString>(), 
_level(level), _message(message), _timestamp(timestamp),
_file(), _line(0), _function(),
_levelString(), _timestampString(), _lineString(), _string(), _fullString() 
{
    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>::TLogData(const KLogLevel& level, const TString& file, klab::UInt32 line, const TString& function) : ILogData<TString>(), 
_level(level), _message(), _timestamp(KSystemTime::GetCurrentMillisecTimestamp()),
_file(file), _line(line), _function(function),
_levelString(), _timestampString(), _lineString(), _string(), _fullString() 
{
    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>::TLogData(const KLogLevel& level, const TString& message, const TString& file, klab::UInt32 line, const TString& function) : ILogData<TString>(), 
_level(level), _message(message), _timestamp(KSystemTime::GetCurrentMillisecTimestamp()),
_file(file), _line(line), _function(function),
_levelString(), _timestampString(), _lineString(), _string(), _fullString() 
{
    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>::TLogData(const KLogLevel& level, const TString& message, klab::KMillisecTimestamp timestamp, const TString& file, klab::UInt32 line, const TString& function) : ILogData<TString>(), 
_level(level), _message(message), _timestamp(timestamp),
_file(file), _line(line), _function(function),
_levelString(), _timestampString(), _lineString(), _string(), _fullString() 
{
    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>::TLogData(const TLogData<TString>& data) : ILogData<TString>(), 
_level(data._level), _message(data._message), _timestamp(data._timestamp),
_file(data._file), _line(data._line), _function(data._function),
_levelString(data._levelString), _timestampString(data._timestampString), _lineString(data._lineString), _string(data._string), _fullString(data._fullString)   
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>::~TLogData()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TLogData<TString>& TLogData<TString>::operator=(const TLogData<TString>& data)
{
    if(this != &data)
    {
        _level     = data._level;
        _message   = data._message;
        _timestamp = data._timestamp;

        _file     = data._file;
        _line     = data._line;
        _function = data._function;

        _levelString     = data._levelString;
        _timestampString = data._timestampString;
        _lineString      = data._lineString;
        _string          = data._string;
        _fullString      = data._string;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::set(const KLogLevel& level, const TString& message)
{
    _level     = level;
    _message   = message;
    _timestamp = KSystemTime::GetCurrentMillisecTimestamp();

    _file.clear();
    _line = 0;
    _function.clear();

    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::set(const KLogLevel& level, const TString& message, klab::KMillisecTimestamp timestamp)
{
    _level     = level;
    _message   = message;
    _timestamp = timestamp;

    _file.clear();
    _line = 0;
    _function.clear();

    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::set(const KLogLevel& level, const TString& message, const TString& file, klab::UInt32 line, const TString& function)
{
    _level     = level;
    _message   = message;
    _timestamp = KSystemTime::GetCurrentMillisecTimestamp();

    _file     = file;
    _line     = line;
    _function = function;

    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::set(const KLogLevel& level, const TString& message, klab::KMillisecTimestamp timestamp, const TString& file, klab::UInt32 line, const TString& function)
{
    _level     = level;
    _message   = message;
    _timestamp = timestamp;

    _file     = file;
    _line     = line;
    _function = function;

    this->updateLevelString();
    this->updateTimestampString();
    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::setLevel(const KLogLevel& level)
{
    _level = level;

    this->updateLevelString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::setMessage(const TString& message)
{
    _message = message;

    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::setTimestamp(klab::KMillisecTimestamp timestamp)
{
    _timestamp = timestamp;

    this->updateTimestampString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::updateTimestamp()
{
    _timestamp = KSystemTime::GetCurrentMillisecTimestamp();

    this->updateTimestampString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::setFile(const TString& file)
{
    _file = file;

    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::setLine(klab::UInt32 line)
{
    _line = line;

    this->updateLineString();
    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::setFunction(const TString& function)
{
    _function = function;

    this->updateString();
    this->updateFullString();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline KLogLevel TLogData<TString>::level() const
{
    return _level;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline  TString TLogData<TString>::message() const
{
    return _message.c_str();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline klab::KMillisecTimestamp TLogData<TString>::timestamp() const
{
    return _timestamp;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TString TLogData<TString>::file() const
{
    return _file.c_str();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline klab::UInt32 TLogData<TString>::line() const
{
    return _line;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TString TLogData<TString>::function() const
{
    return _function.c_str();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TString TLogData<TString>::levelToString() const
{
    return _levelString.c_str();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TString TLogData<TString>::timestampToString() const
{
    return _timestampString.c_str(); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TString TLogData<TString>::lineToString() const
{
    return _lineString.c_str(); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TString TLogData<TString>::toString() const
{
    return _string.c_str();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline TString TLogData<TString>::toFullString() const
{
    return _fullString.c_str();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::updateLevelString()
{
    switch(_level)
    {
    case klab::DEBUG4_LOG:      _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("Debug4");     break;
    case klab::DEBUG3_LOG:      _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("Debug3");     break;
    case klab::DEBUG2_LOG:      _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("Debug2");     break;
    case klab::DEBUG1_LOG:      _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("Debug1");     break;
    case klab::DEBUG_LOG:       _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("Debug");      break;
    case klab::INFO_LOG:        _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("Info");       break;
    case klab::WARNING_LOG:     _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("Warning");    break;
    case klab::ERROR_LOG:       _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("ERROR");      break;
    case klab::FATAL_ERROR_LOG: _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("FATAL");      break;
    default:                    _levelString = klab::ConvertStringTo<typename TLogDataString<TString>::Type>("");           break;
    };
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::updateTimestampString()
{
    klab::KMicrosecTimestamp timestamp = static_cast<klab::KMicrosecTimestamp>(_timestamp)*1000;
    klab::KDateTime date(timestamp, true);

    typename TLogDataOutputStream<TString>::Type oss;
    oss<<date.year()<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("-")
        <<(date.month()<10?klab::ConvertStringTo<typename TLogDataString<TString>::Type>("0"):klab::ConvertStringTo<typename TLogDataString<TString>::Type>(""))<<static_cast<klab::UInt32>(date.month())<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("-")
       <<(date.day()<10?klab::ConvertStringTo<typename TLogDataString<TString>::Type>("0"):klab::ConvertStringTo<typename TLogDataString<TString>::Type>(""))<<static_cast<klab::UInt32>(date.day())<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>(" ")
       <<(date.hour()<10?klab::ConvertStringTo<typename TLogDataString<TString>::Type>("0"):klab::ConvertStringTo<typename TLogDataString<TString>::Type>(""))<<static_cast<klab::UInt32>(date.hour())<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>(":")
       <<(date.minute()<10?klab::ConvertStringTo<typename TLogDataString<TString>::Type>("0"):klab::ConvertStringTo<typename TLogDataString<TString>::Type>(""))<<static_cast<klab::UInt32>(date.minute())<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>(":")
       <<(date.second()<10?klab::ConvertStringTo<typename TLogDataString<TString>::Type>("0"):klab::ConvertStringTo<typename TLogDataString<TString>::Type>(""))<<static_cast<klab::UInt32>(date.second())<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>(".");

    if(date.milliseconds()<100) oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("0");
    if(date.milliseconds()<10)  oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("0");

    oss<<static_cast<klab::UInt32>(date.milliseconds());

    _timestampString = oss.str();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::updateLineString()
{
    typename TLogDataOutputStream<TString>::Type oss;
    oss<<_line;

    _lineString = oss.str();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::updateString()
{
    typename TLogDataOutputStream<TString>::Type oss;
    oss<<_timestampString<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>(" - [")<<_levelString<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("]");

    switch(_level)
    {
    case klab::DEBUG4_LOG:      oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("  ");        break; 
    case klab::DEBUG3_LOG:      oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("  ");        break; 
    case klab::DEBUG2_LOG:      oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("  ");        break;
    case klab::DEBUG1_LOG:      oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("  ");        break;
    case klab::DEBUG_LOG:       oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("   ");       break;
    case klab::INFO_LOG:        oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("    ");      break;
    case klab::WARNING_LOG:     oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>(" ");         break;
    case klab::ERROR_LOG:       oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("   ");       break;
    case klab::FATAL_ERROR_LOG: oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("   ");       break;
    default:                    oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("        ");  break;
    };

    oss<<_message;

    _string = oss.str();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline void TLogData<TString>::updateFullString()
{
    typename TLogDataOutputStream<TString>::Type oss;
    oss<<this->toString();

    if(_file.length()>0 || _line>0 || _function.length()>0) 
        oss<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("\n                                    ")
           <<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("file=\"")<<_file
           <<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("\", line=")<<_line
           <<klab::ConvertStringTo<typename TLogDataString<TString>::Type>(", function=\"")<<_function<<klab::ConvertStringTo<typename TLogDataString<TString>::Type>("\"");

    _fullString = oss.str();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
