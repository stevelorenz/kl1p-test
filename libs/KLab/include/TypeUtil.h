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

#ifndef KLAB_TYPEUTIL_H
#define KLAB_TYPEUTIL_H

#include "DefUtil.h"
#include "TypeInfo.h"
#include <float.h>

#if !defined(_MSC_VER)
#if ULONGLONG_MAX != 0xFFFFFFFFFFFFFFFF
#include <inttypes.h>
#endif
#endif




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

typedef char                    Char;
typedef wchar_t                 WideChar;

// ---------------------------------------------------------------------------------------------------- //

#if UCHAR_MAX == 0xFF
	typedef unsigned char       UByte;
	typedef char                Byte;
	typedef unsigned char       UInt8;
	typedef char                Int8;
#else
#error No 8 bits integer type for this platform.
#endif

// ---------------------------------------------------------------------------------------------------- //

#if USHRT_MAX == 0xFFFF
	typedef unsigned short      UWord;
	typedef short               Word;
	typedef unsigned short      UInt16;
	typedef short               Int16;
#elif UINT_MAX == 0xFFFF
	typedef unsigned int        UWord;
	typedef int                 Word;
	typedef unsigned int        UInt16;
	typedef int                 Int16;
#elif ULONG_MAX == 0xFFFF
	typedef unsigned long       UWord;
	typedef long                Word;
	typedef unsigned long       UInt16;
	typedef long                Int16;
#else
#error No 16 bits integer type for this platform.
#endif

// ---------------------------------------------------------------------------------------------------- //

#if USHRT_MAX == 0xFFFFFFFF
	typedef unsigned short      UDWord;
	typedef short               DWord;
	typedef unsigned short      UInt32;
	typedef short               Int32;
#elif UINT_MAX == 0xFFFFFFFF
	typedef unsigned int        UDWord;
	typedef int                 DWord;
	typedef unsigned int        UInt32;
	typedef int                 Int32;
#elif ULONG_MAX == 0xFFFFFFFF
	typedef unsigned long       UDWord;
	typedef long                DWord;
	typedef unsigned long       UInt32;
	typedef long                Int32;
#else
#error No 32 bits integer type for this platform.
#endif

// ---------------------------------------------------------------------------------------------------- //

#ifdef _MSC_VER
#   ifndef LONGLONG_MAX
#       define LONGLONG_MAX 0x7fffffffffffffffLL
#   endif
#   ifndef LONGLONG_MIN
#       define LONGLONG_MIN (-LONGLONG_MAX-1LL)
#   endif
#   ifndef ULONGLONG_MAX
#       define ULONGLONG_MAX 0xffffffffffffffffULL
#   endif

	typedef unsigned __int64    UQWord;
	typedef __int64             QWord;
	typedef unsigned __int64    UInt64;
	typedef __int64             Int64;
#elif ULONGLONG_MAX == 0xFFFFFFFFFFFFFFFF
	typedef unsigned long long  UQWord;
	typedef long long           QWord;
	typedef unsigned long long  UInt64;
	typedef long long           Int64;
#else
	typedef uint64_t            UQWord;
	typedef int64_t             QWord;
	typedef uint64_t            UInt64;
	typedef int64_t             Int64;
#endif

// ---------------------------------------------------------------------------------------------------- //

typedef float                   Real;
typedef double                  DoubleReal;

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_16BITS_PLATFORM)
	typedef klab::UInt16        UnsignedInteger;
#elif defined(KLAB_32BITS_PLATFORM)
	typedef klab::UInt32        UnsignedInteger;
#elif defined(KLAB_64BITS_PLATFORM)
	typedef klab::UInt64        UnsignedInteger;
#else
#error Unknown integer type for this platform.
#endif

// ---------------------------------------------------------------------------------------------------- //

template<>
class TTypeInfo<klab::UInt8>
{
public:

    static const klab::UInt8	ZERO;
    static const klab::UInt8	UNIT;
    static const klab::UInt8	MIN;
    static const klab::UInt8	MAX;
    static const int    		PRECISION;
    static const klab::UInt8	DELTA;
    static const klab::UInt8	EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<klab::UInt8>& info);
    TTypeInfo<klab::UInt8>&		operator=(const TTypeInfo<klab::UInt8>& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<>
class TTypeInfo<klab::Int8>
{
public:

    static const klab::Int8		ZERO;
    static const klab::Int8		UNIT;
    static const klab::Int8		MIN;
    static const klab::Int8		MAX;
    static const int    		PRECISION;
    static const klab::Int8		DELTA;
    static const klab::Int8		EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<klab::Int8>& info);
    TTypeInfo<klab::Int8>&		operator=(const TTypeInfo<klab::Int8>& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<>
class TTypeInfo<klab::UInt16>
{
public:

    static const klab::UInt16	ZERO;
    static const klab::UInt16	UNIT;
    static const klab::UInt16	MIN;
    static const klab::UInt16	MAX;
    static const int    		PRECISION;
    static const klab::UInt16	DELTA;
    static const klab::UInt16	EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<klab::UInt16>& info);
    TTypeInfo<klab::UInt16>&	operator=(const TTypeInfo<klab::UInt16>& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<>
class TTypeInfo<klab::Int16>
{
public:

    static const klab::Int16	ZERO;
    static const klab::Int16	UNIT;
    static const klab::Int16	MIN;
    static const klab::Int16	MAX;
    static const int    		PRECISION;
    static const klab::Int16	DELTA;
    static const klab::Int16	EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<klab::Int16>& info);
    TTypeInfo<klab::Int16>&		operator=(const TTypeInfo<klab::Int16>& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<>
class TTypeInfo<klab::UInt32>
{
public:

    static const klab::UInt32	ZERO;
    static const klab::UInt32	UNIT;
    static const klab::UInt32	MIN;
    static const klab::UInt32	MAX;
    static const int    		PRECISION;
    static const klab::UInt32	DELTA;
    static const klab::UInt32	EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<klab::UInt32>& info);
    TTypeInfo<klab::UInt32>&	operator=(const TTypeInfo<klab::UInt32>& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<>
class TTypeInfo<klab::Int32>
{
public:

    static const klab::Int32	ZERO;
    static const klab::Int32	UNIT;
    static const klab::Int32	MIN;
    static const klab::Int32	MAX;
    static const int    		PRECISION;
    static const klab::Int32	DELTA;
    static const klab::Int32	EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<klab::Int32>& info);
    TTypeInfo<klab::Int32>&		operator=(const TTypeInfo<klab::Int32>& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<>
class TTypeInfo<klab::UInt64>
{
public:

    static const klab::UInt64	ZERO;
    static const klab::UInt64	UNIT;
    static const klab::UInt64	MIN;
    static const klab::UInt64	MAX;
    static const int    		PRECISION;
    static const klab::UInt64	DELTA;
    static const klab::UInt64	EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<klab::UInt64>& info);
    TTypeInfo<klab::UInt64>&	operator=(const TTypeInfo<klab::UInt64>& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<>
class TTypeInfo<klab::Int64>
{
public:

    static const klab::Int64	ZERO;
    static const klab::Int64	UNIT;
    static const klab::Int64	MIN;
    static const klab::Int64	MAX;
    static const int    		PRECISION;
    static const klab::Int64	DELTA;
    static const klab::Int64	EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<klab::Int64>& info);
    TTypeInfo<klab::Int64>&		operator=(const TTypeInfo<klab::Int64>& info);
};

// ---------------------------------------------------------------------------------------------------- //

const klab::UInt8       MIN_UINT8           = klab::TTypeInfo<klab::UInt8>::MIN;
const klab::UInt8       MAX_UINT8           = klab::TTypeInfo<klab::UInt8>::MAX;
const klab::Int8        MIN_INT8            = klab::TTypeInfo<klab::Int8>::MIN;
const klab::Int8        MAX_INT8            = klab::TTypeInfo<klab::Int8>::MAX;

const klab::UInt16      MIN_UINT16          = klab::TTypeInfo<klab::UInt16>::MIN;
const klab::UInt16      MAX_UINT16          = klab::TTypeInfo<klab::UInt16>::MAX;
const klab::Int16       MIN_INT16           = klab::TTypeInfo<klab::Int16>::MIN;
const klab::Int16       MAX_INT16           = klab::TTypeInfo<klab::Int16>::MAX;

const klab::UInt32      MIN_UINT32          = klab::TTypeInfo<klab::UInt32>::MIN;
const klab::UInt32      MAX_UINT32          = klab::TTypeInfo<klab::UInt32>::MAX;
const klab::Int32       MIN_INT32           = klab::TTypeInfo<klab::Int32>::MIN;
const klab::Int32       MAX_INT32           = klab::TTypeInfo<klab::Int32>::MAX;

const klab::UInt64      MIN_UINT64          = klab::TTypeInfo<klab::UInt64>::MIN;
const klab::UInt64      MAX_UINT64          = klab::TTypeInfo<klab::UInt64>::MAX;
const klab::Int64       MIN_INT64           = klab::TTypeInfo<klab::Int64>::MIN;
const klab::Int64       MAX_INT64           = klab::TTypeInfo<klab::Int64>::MAX;

const klab::UInt64      MIN_UNSIGNEDINTEGER = klab::TTypeInfo<klab::UnsignedInteger>::MIN;
const klab::UInt64      MAX_UNSIGNEDINTEGER = klab::TTypeInfo<klab::UnsignedInteger>::MAX;

const klab::Real        MIN_REAL            = klab::TTypeInfo<klab::Real>::MIN;
const klab::Real        MAX_REAL            = klab::TTypeInfo<klab::Real>::MAX;
const klab::UInt32      REAL_PRECISION      = klab::TTypeInfo<klab::Real>::PRECISION;
const klab::Real        REAL_DELTA          = klab::TTypeInfo<klab::Real>::DELTA;
const klab::Real        REAL_EPSILON        = klab::TTypeInfo<klab::Real>::EPSILON;

const klab::DoubleReal  MIN_DOUBLEREAL      = klab::TTypeInfo<klab::DoubleReal>::MIN;
const klab::DoubleReal  MAX_DOUBLEREAL      = klab::TTypeInfo<klab::DoubleReal>::MAX;
const klab::UInt32      DOUBLEREAL_PRECISION= klab::TTypeInfo<klab::DoubleReal>::PRECISION;
const klab::DoubleReal  DOUBLEREAL_DELTA    = klab::TTypeInfo<klab::DoubleReal>::DELTA;
const klab::DoubleReal  DOUBLEREAL_EPSILON  = klab::TTypeInfo<klab::DoubleReal>::EPSILON;

// ---------------------------------------------------------------------------------------------------- //

const klab::Real        REAL_INFINITY       = std::numeric_limits<klab::Real>::infinity();
const klab::DoubleReal  DOUBLEREAL_INFINITY = std::numeric_limits<klab::DoubleReal>::infinity();

// ---------------------------------------------------------------------------------------------------- //

}


#endif
