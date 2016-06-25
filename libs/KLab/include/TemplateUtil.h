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

#ifndef KLAB_TEMPLATEUTIL_H
#define KLAB_TEMPLATEUTIL_H

#include "TypeUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

struct NOP
{
    static inline void  Do() {};
    enum {RESULT = 0};
};

// ---------------------------------------------------------------------------------------------------- //
 
template<klab::Int32 I>
struct VALUE
{
    enum {RESULT = I};
};

// ---------------------------------------------------------------------------------------------------- //
 
template<klab::Int32 I>
struct INC
{
    enum {RESULT = I+1};
};

// ---------------------------------------------------------------------------------------------------- //
 
template<klab::Int32 I>
struct DEC
{
    enum {RESULT = I-1};
};

// ---------------------------------------------------------------------------------------------------- //

template<bool Condition, class THEN, class ELSE>
struct TYPEIF
{
    typedef THEN    RESULT;
};

template<class THEN, class ELSE>
struct TYPEIF<false, THEN, ELSE>
{
    typedef ELSE    RESULT;
};

// ---------------------------------------------------------------------------------------------------- //

template<bool Condition, class THEN, class ELSE>
struct VALUEIF
{
    enum {RESULT = THEN::RESULT};
};

template<class THEN, class ELSE>
struct VALUEIF<false, THEN, ELSE>
{
    enum {RESULT = ELSE::RESULT};
};

// ---------------------------------------------------------------------------------------------------- //

template<bool Condition, class THEN, class ELSE=NOP>
struct IF
{
    static inline void  Do() {THEN::Do();};
};

template<class THEN, class ELSE>
struct IF<false, THEN, ELSE>
{
    static inline void  Do() {ELSE::Do();};
};

// ---------------------------------------------------------------------------------------------------- //

template<klab::UInt32 I, template <klab::UInt32> class BODY>
struct LOOP
{
    static inline void  Do() {klab::LOOP<I-1, BODY>::Do(); BODY<I>::Do();};
};

template<template <klab::UInt32> class BODY>
struct LOOP<0, BODY>
{
    static inline void  Do() {};
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
struct FILLARRAY
{
    static inline void  Do(T* x, const T& value) {klab::FILLARRAY<T, N-1>::Do(x, value); x[N-1]=value;};
};

template<class T>
struct FILLARRAY<T, 0>
{
    static inline void  Do(T* arr, const T& value) {};
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
struct COPYARRAY
{
    static inline void  Do(const T* from, T* to) {klab::COPYARRAY<T, N-1>::Do(from, to); to[N-1]=from[N-1];};
};

template<class T>
struct COPYARRAY<T, 0>
{
    static inline void  Do(const T* from, T* to) {};
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, T NLeft, T NRight>
struct MIN
{
    enum {RESULT = (NLeft<NRight) ? NLeft : NRight};
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, T NLeft, T NRight>
struct MAX
{
    enum {RESULT = (NLeft>NRight) ? NLeft : NRight};
};

// ---------------------------------------------------------------------------------------------------- //

template<klab::UInt32 M, klab::UInt32 N>
struct POWER
{
    enum {RESULT = (M * klab::POWER<M, N-1>::RESULT)};
};

template<klab::UInt32 M>
struct POWER<M, 0>
{
    enum {RESULT = 1};
};

// ---------------------------------------------------------------------------------------------------- //

template<bool> 
struct STATIC_ASSERT;

template<> 
struct STATIC_ASSERT<true> 
{};

#define KLAB_STATIC_ASSERT(condition) klab::STATIC_ASSERT<(condition)>();

// ---------------------------------------------------------------------------------------------------- //

}


#endif
