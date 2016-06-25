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

#ifndef KLAB_TYPEINFO_H
#define KLAB_TYPEINFO_H

#include "DefUtil.h"
#include <limits.h>
#include <limits>
#include <complex>




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TTypeInfo
{
public:

    static const T      ZERO;
    static const T      UNIT;
    static const T      MIN;
    static const T      MAX;
    static const int    PRECISION;
    static const T      DELTA;
    static const T      EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<T>& info);
    TTypeInfo<T>&       operator=(const TTypeInfo<T>& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TTypeInfo<std::complex<T> >
{
public:

    static const std::complex<T>    ZERO;
    static const std::complex<T>    UNIT;
    static const std::complex<T>    MIN;
    static const std::complex<T>    MAX;
    static const int                PRECISION;
    static const T                  DELTA;
    static const T                  EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<std::complex<T> >& info);
    TTypeInfo<std::complex<T> >&    operator=(const TTypeInfo<std::complex<T> >& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T TTypeInfo<T>::ZERO          = T();

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
const T TTypeInfo<T>::UNIT          = T(1);

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
const T TTypeInfo<T>::MIN           = std::numeric_limits<T>::min();

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
const T TTypeInfo<T>::MAX           = std::numeric_limits<T>::max();

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
const int TTypeInfo<T>::PRECISION   = std::numeric_limits<T>::digits10;

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
const T TTypeInfo<T>::DELTA         = std::numeric_limits<T>::epsilon();


// ---------------------------------------------------------------------------------------------------- //

template<class T> 
const T TTypeInfo<T>::EPSILON       = static_cast<T>(::pow(static_cast<T>(10), -TTypeInfo<T>::PRECISION));

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const std::complex<T> TTypeInfo<std::complex<T> >::ZERO = std::complex<T>(klab::TTypeInfo<T>::ZERO, klab::TTypeInfo<T>::ZERO);

template<class T> 
const std::complex<T> TTypeInfo<std::complex<T> >::UNIT = std::complex<T>(klab::TTypeInfo<T>::UNIT, klab::TTypeInfo<T>::ZERO);

template<class T> 
const std::complex<T> TTypeInfo<std::complex<T> >::MIN  = std::complex<T>(klab::TTypeInfo<T>::MIN, klab::TTypeInfo<T>::MIN);

template<class T> 
const std::complex<T> TTypeInfo<std::complex<T> >::MAX  = std::complex<T>(klab::TTypeInfo<T>::MAX, klab::TTypeInfo<T>::MAX);

template<class T> 
const int TTypeInfo<std::complex<T> >::PRECISION        = klab::TTypeInfo<T>::PRECISION;

template<class T> 
const T TTypeInfo<std::complex<T> >::DELTA              = klab::TTypeInfo<T>::DELTA;

template<class T> 
const T TTypeInfo<std::complex<T> >::EPSILON            = klab::TTypeInfo<T>::EPSILON;

// ---------------------------------------------------------------------------------------------------- //

}


#endif
