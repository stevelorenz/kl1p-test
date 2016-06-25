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

#ifndef KLAB_FUNCUTIL_H
#define KLAB_FUNCUTIL_H

#include "DefUtil.h"
#include "TypeUtil.h"
#include <complex>

#if defined(KLAB_UNIX_SYSTEM)
#include <sys/time.h> 
#endif	




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

#ifndef KLAB_MSWINDOWS_SYSTEM
	#define strcpy_s(dest, size, src) strcpy(dest, src)
	#define sprintf_s(buffer, size, ...) sprintf(buffer, __VA_ARGS__)
#endif

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_MSWINDOWS_SYSTEM)
    inline void Sleep(klab::UInt32 time)    {::Sleep(static_cast<DWORD>(time));} 
#elif defined(KLAB_UNIX_SYSTEM)
    inline void Sleep(klab::UInt32 time)	{timeval tm; tm.tv_sec=time/1000L; tm.tv_usec=1000L*(time%1000L); select(0, NULL, NULL, NULL, &tm);}
#elif defined(KLAB_MACOS_SYSTEM)
    inline void Sleep(klab::UInt32 time)	{timeval tm; tm.tv_sec=time/1000L; tm.tv_usec=1000L*(time%1000L); select(0, NULL, NULL, NULL, &tm);}
#else
    inline void Sleep(klab::UInt32 time)	{timeval tm; tm.tv_sec=time/1000L; tm.tv_usec=1000L*(time%1000L); select(0, NULL, NULL, NULL, &tm);}
#endif

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T            Abs(const T& value)
{
    return (value<klab::TTypeInfo<T>::ZERO ? -value : value);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T            Abs(const std::complex<T>& value)
{
    return static_cast<T>(std::abs(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TE> 
inline bool         Equals(const T& left, const T& right, const TE& epsilon)
{
    return (klab::Abs(static_cast<T>(left-right)) <= epsilon); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline bool         Equals(const T& left, const T& right, const T& epsilon)
{
    return klab::Equals<T, T>(left, right, epsilon);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline bool         Equals(const T& left, const T& right)
{
    return klab::Equals<T, T>(left, right, TTypeInfo<T>::EPSILON); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline bool         Equals(const std::complex<T>& left, const std::complex<T>& right, const T& epsilon)
{
    return (klab::Equals<T>(left.real(), right.real(), epsilon) && klab::Equals<T>(left.imag(), right.imag(), epsilon)); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline bool         Equals(const std::complex<T>& left, const std::complex<T>& right)
{
    return klab::Equals<T>(left, right, TTypeInfo<T>::EPSILON); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T            Min(const T& left, const T& right)
{
    return (left<=right ? left : right);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T            Max(const T& left, const T& right)
{
    return (left>=right ? left : right);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline bool         IsPowerOf2(const T& x)
{
    return ((x>0) && (x & (x-1))==0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T            RoundUpToPowerOf2(const T& x)
{
    T ret = klab::TTypeInfo<T>::ZERO;

    if(x > 0)
    {
        ret = x-1;
        
        for(klab::UInt32 i=1; i<sizeof(T)*CHAR_BIT; i<<=1)
            ret = ret | ret >> i;
    }

    return (ret + 1);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TIn>
inline T                CastTo(const TIn& in)
{
    return T(in);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T                CastTo(const std::complex<T>& in)
{
    return in.real();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
