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

#ifndef LOKO_ILOGDATA_H
#define LOKO_ILOGDATA_H

#include "TypeUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

enum KLogLevel
{
    DEBUG4_LOG,
    DEBUG3_LOG,
    DEBUG2_LOG,
    DEBUG1_LOG,
    DEBUG_LOG,
    INFO_LOG,
    WARNING_LOG,
    ERROR_LOG,
    FATAL_ERROR_LOG
};

// ---------------------------------------------------------------------------------------------------- //

template<class TString=const klab::Char*>
class ILogData
{
public:

	virtual ~ILogData() = 0;

    virtual KLogLevel           level() const = 0;
    virtual TString             message() const = 0;
    virtual TString             file() const = 0;
    virtual klab::UInt32        line() const = 0;
    virtual TString             function() const = 0;

    virtual TString             levelToString() const = 0;
    virtual TString             timestampToString() const = 0;
    virtual TString             lineToString() const = 0;

    virtual TString             toString() const = 0;
    virtual TString             toFullString() const = 0;
};

// ---------------------------------------------------------------------------------------------------- //

template<class TString>
inline ILogData<TString>::~ILogData()
{}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
