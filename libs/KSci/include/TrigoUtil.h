// KSci - A portable C++ numerical analysis library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KSci C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_TRIGOUTIL_H
#define KLAB_TRIGOUTIL_H

#include "MathsUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KACosMathsException, KMathsException)
KLAB_DECLARE_EXCEPTION(KASinMathsException, KMathsException)

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        Cos(const T& angle)
{
    return static_cast<T>(::cos(angle));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        CosH(const T& value)
{
    return static_cast<T>(::cosh(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        ACos(const T& value)
{
    ThrowTraceExceptionIf(KACosMathsException, value<-1.0 || value>1.0);

    return static_cast<T>(::acos(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        Sin(const T& angle)
{
    return static_cast<T>(::sin(angle));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        SinH(const T& value)
{
    return static_cast<T>(::sinh(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        ASin(const T& value)
{
    ThrowTraceExceptionIf(KASinMathsException, value<-1.0 || value>1.0);

    return static_cast<T>(::asin(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        Tan(const T& angle)
{
    return static_cast<T>(::tan(angle));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        TanH(const T& value)
{
    return static_cast<T>(::tanh(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        ATan(const T& value)
{
    return static_cast<T>(::atan(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T        ATan2(const T& value1, const T& value2)
{
    return static_cast<T>(::atan2(value1, value2));
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
