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

#include "../include/Exception.h"
#include <cstring>
#include <typeinfo>

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KException::KException() : std::exception(),
_errorCode(0), _message(new char[strlen(KLAB_DEFAULT_EXCEPTIONMESSAGE)+1]), 
_file(new char[1]), _line(0), _function(new char[1])
{
    strcpy_s(_message, strlen(KLAB_DEFAULT_EXCEPTIONMESSAGE)+1, KLAB_DEFAULT_EXCEPTIONMESSAGE);
    strcpy_s(_file, 1, "");
    strcpy_s(_function, 1, "");
}

// ---------------------------------------------------------------------------------------------------- //

KException::KException(klab::UInt32 errorCode, const char* message, const char* file, klab::UInt32 line, const char* function) : std::exception(),
_errorCode(errorCode), _message(message!=0?new char[strlen(message)+1]:new char[strlen(KLAB_DEFAULT_EXCEPTIONMESSAGE)+1]),
_file(file!=0?new char[strlen(file)+1]:new char[1]), _line(line), _function(function!=0?new char[strlen(function)+1]:new char[1])
{
    if(message != 0)    strcpy_s(_message, strlen(message)+1, message);
    else                strcpy_s(_message, strlen(KLAB_DEFAULT_EXCEPTIONMESSAGE)+1, KLAB_DEFAULT_EXCEPTIONMESSAGE);

    if(file != 0)       strcpy_s(_file, strlen(file)+1, file);
    else                strcpy_s(_file, 1, "");

    if(function != 0)   strcpy_s(_function, strlen(function)+1, function);
    else                strcpy_s(_function, 1, "");
}

// ---------------------------------------------------------------------------------------------------- //

KException::KException(const KException& e) : std::exception(e),
_errorCode(e._errorCode), _message(new char[strlen(e._message)+1]),
_file(new char[strlen(e._file)+1]), _line(e._line), _function(new char[strlen(e._function)+1])
{
    strcpy_s(_message, strlen(e._message)+1, e._message);
    strcpy_s(_file, strlen(e._file)+1, e._file);
    strcpy_s(_function, strlen(e._function)+1, e._function);
}

// ---------------------------------------------------------------------------------------------------- //

KException::~KException() throw()
{
    if(_message != 0)
        delete[] _message;

    if(_file != 0)
        delete[] _file;

    if(_function != 0)
        delete[] _function;
}

// ---------------------------------------------------------------------------------------------------- //

KException& KException::operator=(const KException& e)
{
    if(this != &e)
    {
        delete[] _message;
        delete[] _file;
        delete[] _function;

        _message    = new char[strlen(e._message)+1];
        _file       = new char[strlen(e._file)+1];
        _function   = new char[strlen(e._function)+1];


        _errorCode = e._errorCode;
        strcpy_s(_message, strlen(e._message)+1, e._message); 
        strcpy_s(_file, strlen(e._file)+1, e._file);
        _line = e._line;
        strcpy_s(_function, strlen(e._function)+1, e._function);
    }
    
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KException::errorCode() const
{
    return _errorCode;
}

// ---------------------------------------------------------------------------------------------------- //

const char* KException::what() const throw()
{
    return _message;
}

// ---------------------------------------------------------------------------------------------------- //

const char* KException::file() const
{
    return _file;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KException::line() const
{
    return _line;
}

// ---------------------------------------------------------------------------------------------------- //

const char* KException::function() const
{
    return _function;
}

// ---------------------------------------------------------------------------------------------------- //

const char* klab::FormatExceptionToString(const std::exception& e)
{
    static char     ResultBuffer[1025];
    sprintf_s(ResultBuffer, 1025, "Exception=%s, Message=\"%s\"", typeid(e).name(), e.what());

    return ResultBuffer;
}

// ---------------------------------------------------------------------------------------------------- //

const char* klab::FormatExceptionToString(const KException& e)
{
    static char     ResultBuffer[1025];
    sprintf_s(ResultBuffer, 1025, "Exception=%s, Error=%i, Message=\"%s\", File=%s, Line=%i, Function=%s", typeid(e).name(), e.errorCode(), e.what(), e.file(), e.line(), e.function());

    return ResultBuffer;
}

// ---------------------------------------------------------------------------------------------------- //

const char* klab::FormatExceptionToString(const KErrorCodeException& e)
{
    static char     ResultBuffer[1025];
    sprintf_s(ResultBuffer, 1025, "Error #%i, Message=\"%s\", File=%s, Line=%i, Function=%s", e.errorCode(), e.what(), e.file(), e.line(), e.function());

    return ResultBuffer;
}

// ---------------------------------------------------------------------------------------------------- //
