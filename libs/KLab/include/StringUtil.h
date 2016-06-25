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

#ifndef KLAB_STRINGUTIL_H
#define KLAB_STRINGUTIL_H

#include "DefUtil.h"
#include "FuncUtil.h"
#include "Exception.h"
#include <string>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KStringException, KException)
KLAB_DECLARE_EXCEPTION(KBadConversionStringException, KStringException)

// ---------------------------------------------------------------------------------------------------- //

std::string     ToLowerCase(const std::string& str);
std::wstring    ToLowerCase(const std::wstring& str);
std::string     ToUpperCase(const std::string& str);
std::wstring    ToUpperCase(const std::wstring& str);

klab::Int32     Compare(const std::string& left, const std::string& right, bool isCaseSensitive=true);
klab::Int32     Compare(const std::wstring& left, const std::wstring& right, bool isCaseSensitive=true);

bool            Equals(const std::string& left, const std::string& right, bool isCaseSensitive=true);
bool            Equals(const std::wstring& left, const std::wstring& right, bool isCaseSensitive=true);

void            TrimLeftString(std::string& str);
void            TrimLeftString(std::wstring& str);
void            TrimRightString(std::string& str);
void            TrimRightString(std::wstring& str);
void            TrimString(std::string& str);
void            TrimString(std::wstring& str);

std::string     ToLeftTrimmedString(const std::string& str);
std::wstring    ToLeftTrimmedString(const std::wstring& str);
std::string     ToRightTrimmedString(const std::string& str);
std::wstring    ToRightTrimmedString(const std::wstring& str);
std::string     ToTrimmedString(const std::string& str);
std::wstring    ToTrimmedString(const std::wstring& str);

std::string     ToString(const std::wstring& str);
std::wstring    ToWString(const std::string& str);

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T        ConvertStringTo(const std::string& str)
{
    T ret = klab::TTypeInfo<T>::ZERO;

    std::istringstream iss(str);
    if(!(iss>>ret))
        ThrowTraceException(KBadConversionStringException);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline bool     ConvertStringTo<bool>(const std::string& str)
{
    bool ret = false;

    std::istringstream iss(str);
    if(!(iss>>ret))
    {
        std::string tStr = klab::ToTrimmedString(str);

        if(klab::Equals(tStr, "true", false))       ret = true;
        else if(klab::Equals(tStr, "false", false)) ret = false;
        else                                        ThrowTraceException(KBadConversionStringException);
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::UInt8  ConvertStringTo<klab::UInt8>(const std::string& str)
{
    klab::UInt32 ret = klab::TTypeInfo<klab::UInt32>::ZERO;

    std::istringstream iss(str);
    if(!(iss>>ret))
        ThrowTraceException(KBadConversionStringException);

    return static_cast<klab::UInt8>(ret);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::Int8   ConvertStringTo<klab::Int8>(const std::string& str)
{
    klab::Int32 ret = klab::TTypeInfo<klab::Int32>::ZERO;

    std::istringstream iss(str);
    if(!(iss>>ret))
        ThrowTraceException(KBadConversionStringException);

    return static_cast<klab::Int8>(ret);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline std::string  ConvertStringTo<std::string>(const std::string& str)
{
    return str;
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline std::wstring ConvertStringTo<std::wstring>(const std::string& str)
{
    return klab::ToWString(str);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T        ConvertStringTo(const std::wstring& str)
{
    T ret = klab::TTypeInfo<T>::ZERO;

    std::wistringstream iss(str);
    if(!(iss>>ret))
        ThrowTraceException(KBadConversionStringException);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline bool     ConvertStringTo<bool>(const std::wstring& str)
{
    bool ret = false;

    std::wistringstream iss(str);
    if(!(iss>>ret))
    {
        std::wstring tStr = klab::ToTrimmedString(str);

        if(klab::Equals(tStr, L"true", false))          ret = true;
        else if(klab::Equals(tStr, L"false", false))    ret = false;
        else                                            ThrowTraceException(KBadConversionStringException);
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::UInt8  ConvertStringTo<klab::UInt8>(const std::wstring& str)
{
    klab::UInt16 ret = klab::TTypeInfo<klab::UInt32>::ZERO;

    std::wistringstream iss(str);
    if(!(iss>>ret))
        ThrowTraceException(KBadConversionStringException);

    return static_cast<klab::UInt8>(ret);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::Int8   ConvertStringTo<klab::Int8>(const std::wstring& str)
{
    klab::Int16 ret = klab::TTypeInfo<klab::Int32>::ZERO;

    std::wistringstream iss(str);
    if(!(iss>>ret))
        ThrowTraceException(KBadConversionStringException);

    return static_cast<klab::Int8>(ret);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::UInt16  ConvertStringTo<klab::UInt16>(const std::wstring& str)
{
    klab::UInt32 ret = klab::TTypeInfo<klab::UInt32>::ZERO;

    std::wistringstream iss(str);
    if(!(iss>>ret))
        ThrowTraceException(KBadConversionStringException);

    return static_cast<klab::UInt16>(ret);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::Int16   ConvertStringTo<klab::Int16>(const std::wstring& str)
{
    klab::Int32 ret = klab::TTypeInfo<klab::Int32>::ZERO;

    std::wistringstream iss(str);
    if(!(iss>>ret))
        ThrowTraceException(KBadConversionStringException);

    return static_cast<klab::Int16>(ret);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline std::string  ConvertStringTo<std::string>(const std::wstring& str)
{
    return klab::ToString(str);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline std::wstring ConvertStringTo<std::wstring>(const std::wstring& str)
{
    return str;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
