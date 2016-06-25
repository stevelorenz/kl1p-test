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

#ifndef KLAB_EXCEPTION_H
#define KLAB_EXCEPTION_H

#include "TypeUtil.h"
#include "FuncUtil.h"
#include <exception>




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

class KException : public std::exception
{
public:
  
    KException();
    KException(klab::UInt32 errorCode, const char* message=0, const char* file=0, klab::UInt32 line=0, const char* function=0);
    KException(const KException& e);
    virtual ~KException() throw();
    
    KException&                 operator=(const KException& e);
    
    virtual klab::UInt32        errorCode() const;
    virtual const char*         what() const throw();

    virtual const char*         file() const;
    virtual klab::UInt32        line() const;
    virtual const char*         function() const;
  
    
private:
  
    klab::UInt32                _errorCode;
    char*                       _message;

    char*                       _file;
    klab::UInt32                _line;
    char*                       _function;
};

// ---------------------------------------------------------------------------------------------------- //

#define KLAB_DEFAULT_EXCEPTIONMESSAGE ""

// ---------------------------------------------------------------------------------------------------- //

#define KLAB_DECLARE_EXCEPTION(ExceptionName, BaseException) \
class ExceptionName : public BaseException \
{ \
    public: \
 \
        inline ExceptionName() : BaseException() {}; \
        inline ExceptionName(klab::UInt32 errorCode, const char* message=0, const char* file=0, klab::UInt32 line=0, const char* function=0) : BaseException(errorCode, message, file, line, function) {}; \
        inline ExceptionName(const ExceptionName& e) : BaseException(e) {}; \
        inline ~ExceptionName() throw() {}; \
 \
        inline ExceptionName&   operator=(const ExceptionName& e) {if(this!=&e){BaseException::operator=(e);} return *this;}; \
}; 

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KNullPointerException, KException)
KLAB_DECLARE_EXCEPTION(KBadArithmeticException, KException)
KLAB_DECLARE_EXCEPTION(KOverflowException, KException)
KLAB_DECLARE_EXCEPTION(KOutOfBoundException, KException)
KLAB_DECLARE_EXCEPTION(KErrorCodeException, KException)
KLAB_DECLARE_EXCEPTION(KUnimplementedException, KException) // Meaning : Function is not implemented, but it should be (and surely will be in a near future).
KLAB_DECLARE_EXCEPTION(KUndefinedException, KException)     // Meaning : Function cannot be defined.

// ---------------------------------------------------------------------------------------------------- //

inline void ThrowExceptionIf(bool condition, klab::UInt32 errorCode=0, const char* message=0, const char* file=0, klab::UInt32 line=0, const char* function=0)
{
#ifndef KLAB_NOEXCEPTIONS
    if(condition)
        throw KException(errorCode, message, file, line, function);
#endif
}

// ---------------------------------------------------------------------------------------------------- //

template<class E>
inline void ThrowExceptionIf(bool condition, klab::UInt32 errorCode=0, const char* message=0, const char* file=0, klab::UInt32 line=0, const char* function=0)
{
#ifndef KLAB_NOEXCEPTIONS
    if(condition)
        throw E(errorCode, message, file, line, function);
#endif
}

// ---------------------------------------------------------------------------------------------------- //

inline void ThrowExceptionIfNot(bool condition, klab::UInt32 errorCode=0, const char* message=0, const char* file=0, klab::UInt32 line=0, const char* function=0)
{
#ifndef KLAB_NOEXCEPTIONS
    if(!condition)
        throw KException(errorCode, message, file, line, function);
#endif
}

// ---------------------------------------------------------------------------------------------------- //

template<class E>
inline void ThrowExceptionIfNot(bool condition, klab::UInt32 errorCode=0, const char* message=0, const char* file=0, klab::UInt32 line=0, const char* function=0)
{
#ifndef KLAB_NOEXCEPTIONS
    if(!condition)
        throw E(errorCode, message, file, line, function);
#endif
}

// ---------------------------------------------------------------------------------------------------- //

inline void ThrowException(klab::UInt32 errorCode=0, const char* message=0, const char* file=0, klab::UInt32 line=0, const char* function=0)
{
#ifndef KLAB_NOEXCEPTIONS
    throw KException(errorCode, message, file, line, function);
#endif
}

// ---------------------------------------------------------------------------------------------------- //

template<class E>
inline void ThrowException(klab::UInt32 errorCode=0, const char* message=0, const char* file=0, klab::UInt32 line=0, const char* function=0)
{
#ifndef KLAB_NOEXCEPTIONS
    throw E(errorCode, message, file, line, function);
#endif
}

// ---------------------------------------------------------------------------------------------------- //

#define ThrowTraceExceptionIf_0(E, condition)                           klab::ThrowExceptionIf<E>(condition, 0, 0, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);
#define ThrowTraceExceptionIf_1(E, condition, errorCode)                klab::ThrowExceptionIf<E>(condition, errorCode, 0, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);
#define ThrowTraceExceptionIf_2(E, condition, errorCode, message)       klab::ThrowExceptionIf<E>(condition, errorCode, message, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__); 

#define ThrowTraceExceptionIfNot_0(E, condition)                        klab::ThrowExceptionIfNot<E>(condition, 0, 0, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);
#define ThrowTraceExceptionIfNot_1(E, condition, errorCode)             klab::ThrowExceptionIfNot<E>(condition, errorCode, 0, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);
#define ThrowTraceExceptionIfNot_2(E, condition, errorCode, message)    klab::ThrowExceptionIfNot<E>(condition, errorCode, message, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);

#define ThrowTraceException_0(E)                                        klab::ThrowException<E>(0, 0, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);
#define ThrowTraceException_1(E, errorCode)                             klab::ThrowException<E>(errorCode, 0, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);
#define ThrowTraceException_2(E, errorCode, message)                    klab::ThrowException<E>(errorCode, message, KLAB__FILE__, KLAB__LINE__, KLAB__FUNC__);

#define KLAB_EXCEPTION_GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
#define KLAB_EXCEPTION_GET_5TH_ARG(arg1, arg2, arg3, arg4, arg5, ...) arg5

#if defined(_MSC_VER)
    #define KLAB_THROWTRACEEXCEPTIONIF_MACROSWITCH_VSSTUDIO_VAARGS_FIX(tuple)       KLAB_EXCEPTION_GET_5TH_ARG tuple
    #define KLAB_THROWTRACEEXCEPTIONIFNOT_MACROSWITCH_VSSTUDIO_VAARGS_FIX(tuple)    KLAB_EXCEPTION_GET_5TH_ARG tuple
    #define KLAB_THROWTRACEEXCEPTION_MACROSWITCH_VSSTUDIO_VAARGS_FIX(tuple)         KLAB_EXCEPTION_GET_4TH_ARG tuple

    #define KLAB_THROWTRACEEXCEPTIONIF_MACROSWITCH(...)     KLAB_THROWTRACEEXCEPTIONIF_MACROSWITCH_VSSTUDIO_VAARGS_FIX((__VA_ARGS__, ThrowTraceExceptionIf_2, ThrowTraceExceptionIf_1, ThrowTraceExceptionIf_0, ))
    #define KLAB_THROWTRACEEXCEPTIONIFNOT_MACROSWITCH(...)  KLAB_THROWTRACEEXCEPTIONIFNOT_MACROSWITCH_VSSTUDIO_VAARGS_FIX((__VA_ARGS__, ThrowTraceExceptionIfNot_2, ThrowTraceExceptionIfNot_1, ThrowTraceExceptionIfNot_0, ))
    #define KLAB_THROWTRACEEXCEPTION_MACROSWITCH(...)       KLAB_THROWTRACEEXCEPTION_MACROSWITCH_VSSTUDIO_VAARGS_FIX((__VA_ARGS__, ThrowTraceException_2, ThrowTraceException_1, ThrowTraceException_0, ))
#else
    #define KLAB_THROWTRACEEXCEPTIONIF_MACROSWITCH(...)     KLAB_EXCEPTION_GET_5TH_ARG(__VA_ARGS__, ThrowTraceExceptionIf_2, ThrowTraceExceptionIf_1, ThrowTraceExceptionIf_0, )
    #define KLAB_THROWTRACEEXCEPTIONIFNOT_MACROSWITCH(...)  KLAB_EXCEPTION_GET_5TH_ARG(__VA_ARGS__, ThrowTraceExceptionIfNot_2, ThrowTraceExceptionIfNot_1, ThrowTraceExceptionIfNot_0, )
    #define KLAB_THROWTRACEEXCEPTION_MACROSWITCH(...)       KLAB_EXCEPTION_GET_4TH_ARG(__VA_ARGS__, ThrowTraceException_2, ThrowTraceException_1, ThrowTraceException_0, )
#endif


#define ThrowTraceExceptionIf(...)      KLAB_THROWTRACEEXCEPTIONIF_MACROSWITCH(__VA_ARGS__)(__VA_ARGS__)
#define ThrowTraceExceptionIfNot(...)   KLAB_THROWTRACEEXCEPTIONIFNOT_MACROSWITCH(__VA_ARGS__)(__VA_ARGS__)
#define ThrowTraceException(...)        KLAB_THROWTRACEEXCEPTION_MACROSWITCH(__VA_ARGS__)(__VA_ARGS__)

// ---------------------------------------------------------------------------------------------------- //

const char*     FormatExceptionToString(const std::exception& e);
const char*     FormatExceptionToString(const KException& e);
const char*     FormatExceptionToString(const KErrorCodeException& e);

// ---------------------------------------------------------------------------------------------------- //

}


#endif
