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

#ifndef KLAB_ATOMICCOUNT_H
#define KLAB_ATOMICCOUNT_H

#include "TypeUtil.h"
#include "ScopedMutex.h"




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAtomicCount
{
public:

    TAtomicCount();
    TAtomicCount(const T& count);
    virtual ~TAtomicCount();

    T                   operator++();
    T                   operator++(int);
    T                   operator--();
    T                   operator--(int);

                        operator T() const;

 
private:

    TAtomicCount(const TAtomicCount<T>& count);
    TAtomicCount<T>&    operator=(const T& count);
    TAtomicCount<T>&    operator=(const TAtomicCount<T>& count);


private:

    klab::KMutex        _mutex;
    T                   _count;
};

// ---------------------------------------------------------------------------------------------------- //

typedef TAtomicCount<klab::Int8>    KAtomicInt8Count;
typedef TAtomicCount<klab::UInt8>   KAtomicUInt8Count;
typedef TAtomicCount<klab::Int16>   KAtomicInt16Count;
typedef TAtomicCount<klab::UInt16>  KAtomicUInt16Count;
typedef TAtomicCount<klab::Int32>   KAtomicInt32Count;
typedef TAtomicCount<klab::UInt32>  KAtomicUInt32Count;
typedef TAtomicCount<klab::Int64>   KAtomicInt64Count;
typedef TAtomicCount<klab::UInt64>  KAtomicUInt64Count;

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAtomicCount<T>::TAtomicCount() : 
_mutex(), _count(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAtomicCount<T>::TAtomicCount(const T& count) : 
_mutex(), _count(count)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAtomicCount<T>::~TAtomicCount() 
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TAtomicCount<T>::operator++()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return (++_count);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TAtomicCount<T>::operator++(int)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    T ret = _count;
    ++_count;

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TAtomicCount<T>::operator--()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return (--_count);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TAtomicCount<T>::operator--(int)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    T ret = _count;
    --_count;

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAtomicCount<T>::operator T() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _count;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
