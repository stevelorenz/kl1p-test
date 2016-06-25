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

#include "../include/StringUtil.h"
#include "../include/LibUtil.h"


using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

std::string     klab::ToLowerCase(const std::string& str)
{
    std::string ret = str;
    std::transform(ret.begin(), ret.end(), ret.begin(), tolower);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

std::wstring    klab::ToLowerCase(const std::wstring& str)
{
    std::wstring ret = str;
    std::transform(ret.begin(), ret.end(), ret.begin(), tolower);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

std::string     klab::ToUpperCase(const std::string& str)
{
    std::string ret = str;
    std::transform(ret.begin(), ret.end(), ret.begin(), toupper);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

std::wstring    klab::ToUpperCase(const std::wstring& str)
{
    std::wstring ret = str;
    std::transform(ret.begin(), ret.end(), ret.begin(), toupper);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

klab::Int32     klab::Compare(const std::string& left, const std::string& right, bool isCaseSensitive)
{
    if(isCaseSensitive) return static_cast<klab::Int32>(left.compare(right));
    else                return static_cast<klab::Int32>(klab::ToLowerCase(left).compare(klab::ToLowerCase(right)));     
}

// ---------------------------------------------------------------------------------------------------- //

klab::Int32     klab::Compare(const std::wstring& left, const std::wstring& right, bool isCaseSensitive)
{
    if(isCaseSensitive) return static_cast<klab::Int32>(left.compare(right));
    else                return static_cast<klab::Int32>(klab::ToLowerCase(left).compare(klab::ToLowerCase(right)));      
}

// ---------------------------------------------------------------------------------------------------- //

bool            klab::Equals(const std::string& left, const std::string& right, bool isCaseSensitive)
{
    return (klab::Compare(left, right, isCaseSensitive) == 0);
}

// ---------------------------------------------------------------------------------------------------- //

bool            klab::Equals(const std::wstring& left, const std::wstring& right, bool isCaseSensitive)
{
    return (klab::Compare(left, right, isCaseSensitive) == 0);
}

// ---------------------------------------------------------------------------------------------------- //

void            klab::TrimLeftString(std::string& str)
{
    if(str.length() > 0)
    {
        size_t i = 0;
	    bool space = (str[i] == 0x20);
	    while(space)
	    {
            ++i;
		    space = (str[i] == 0x20);
	    }

	    str.erase(0, i);
    }
}

// ---------------------------------------------------------------------------------------------------- //

void            klab::TrimLeftString(std::wstring& str)
{
    if(str.length() > 0)
    {
        size_t i = 0;
	    bool space = (str[i] == 0x20);
	    while(space)
	    {
            ++i;
		    space = (str[i] == 0x20);
	    }

	    str.erase(0, i);
    }
}

// ---------------------------------------------------------------------------------------------------- //

void            klab::TrimRightString(std::string& str)
{
    if(str.length() > 0)
    {
        size_t i = str.length()-1;
        bool space = (str[i] == 0x20);
        while(space)
        {
            --i;
	        space = (str[i] == 0x20);
        }

        str.erase(i+1, str.length());
    }
}

// ---------------------------------------------------------------------------------------------------- //

void            klab::TrimRightString(std::wstring& str)
{
    if(str.length() > 0)
    {
        size_t i = str.length()-1;
        bool space = (str[i] == 0x20);
        while(space)
        {
            --i;
	        space = (str[i] == 0x20);
        }

        str.erase(i+1, str.length());
    }
}

// ---------------------------------------------------------------------------------------------------- //

void            klab::TrimString(std::string& str)
{
    klab::TrimLeftString(str);
    klab::TrimRightString(str);
}

// ---------------------------------------------------------------------------------------------------- //

void            klab::TrimString(std::wstring& str)
{
    klab::TrimLeftString(str);
    klab::TrimRightString(str);
}

// ---------------------------------------------------------------------------------------------------- //

std::string     klab::ToLeftTrimmedString(const std::string& str)
{
    std::string ret(str);
    klab::TrimLeftString(ret);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

std::wstring    klab::ToLeftTrimmedString(const std::wstring& str)
{
    std::wstring ret(str);
    klab::TrimLeftString(ret);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

std::string     klab::ToRightTrimmedString(const std::string& str)
{
    std::string ret(str);
    klab::TrimRightString(ret);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

std::wstring    klab::ToRightTrimmedString(const std::wstring& str)
{
    std::wstring ret(str);
    klab::TrimRightString(ret);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

std::string     klab::ToTrimmedString(const std::string& str)
{
    std::string ret(str);
    klab::TrimString(ret);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

std::wstring    klab::ToTrimmedString(const std::wstring& str)
{
    std::wstring ret(str);
    klab::TrimString(ret);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

std::string     klab::ToString(const std::wstring& str)
{
    size_t length = str.length();
    if(length > 0)
    {        
        std::locale loc;
        std::vector<klab::Char> buffer(str.length());
        std::use_facet<std::ctype<klab::WideChar> >(loc).narrow(str.c_str(), str.c_str()+length, '?', &buffer[0]);

        return std::string(&buffer[0], buffer.size());
    }
    else
    {
        return std::string();
    }
}

// ---------------------------------------------------------------------------------------------------- //

std::wstring    klab::ToWString(const std::string& str)
{
    size_t length = str.length();
    if(length > 0)
    {       
        std::locale loc;
        std::vector<klab::WideChar> buffer(str.length());
        std::use_facet<std::ctype<klab::WideChar> >(loc).widen(str.c_str(), str.c_str()+length, &buffer[0]);

        return std::wstring(&buffer[0], buffer.size());
    }
    else
    {
        return std::wstring();
    }
}

// ---------------------------------------------------------------------------------------------------- //
