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

#ifndef KLAB_MATHSUTIL_H
#define KLAB_MATHSUTIL_H

#include <KLabInclude.h>
#include <cmath>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KMathsException, klab::KException)
KLAB_DECLARE_EXCEPTION(KSqrtMathsException, KMathsException)
KLAB_DECLARE_EXCEPTION(KLogMathsException, KMathsException)

// ---------------------------------------------------------------------------------------------------- //

const klab::DoubleReal  ZERO    = 0.0;   
const klab::DoubleReal  PI      = 3.14159265358979323846;   // = PI  
const klab::DoubleReal  PI_2    = 1.57079632679489661923;   // = PI/2 
const klab::DoubleReal  PI_4    = 0.78539816339744830962;   // = PI/4
const klab::DoubleReal  INV_PI  = 0.31830988618379067154;   // = 1/PI

const klab::DoubleReal  E       = 2.7182818284590452354;    // = e    
const klab::DoubleReal  LOG10E  = 0.43429448190325182765;   // = log e
const klab::DoubleReal  LN2     = 0.69314718055994530942;   // = ln 2 
const klab::DoubleReal  LN10    = 2.30258509299404568402;   // = ln 10
const klab::DoubleReal  INV_LN2 = 1.4426950408889634074;    // = 1/ln 2

const klab::DoubleReal  SQRT2      = 1.41421356237309504880;   // = sqrt(2)
const klab::DoubleReal  SQRT3      = 1.73205080756887729352;   // = sqrt(3)
const klab::DoubleReal  SQRT1_2    = 0.70710678118654752440;   // = sqrt(1/2)
const klab::DoubleReal  SQRT2_INV2 = 0.70710678118654752440;   // = sqrt(2)/2
const klab::DoubleReal  INV_SQRT2  = 0.70710678118654752440;   // = 1/sqrt(2)

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T                Sqrt(const T& value)
{
    ThrowTraceExceptionIf(KSqrtMathsException, value<klab::TTypeInfo<T>::ZERO);

    return static_cast<T>(::sqrt(value));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Sqrt(klab::UInt32 value)
{
    ThrowTraceExceptionIf(KSqrtMathsException, value<0);

    return ::sqrt(static_cast<klab::Real>(value));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Sqrt(klab::Int32 value)
{
    ThrowTraceExceptionIf(KSqrtMathsException, value<0);

    return ::sqrt(static_cast<klab::Real>(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline std::complex<T>  Sqrt(const std::complex<T>& value)
{
    return static_cast<std::complex<T> >(std::sqrt(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T                Exp(const T& value)
{
    return static_cast<T>(::exp(value));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Exp(klab::UInt32 value)
{
    return ::exp(static_cast<klab::Real>(value));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Exp(klab::Int32 value)
{
    return ::exp(static_cast<klab::Real>(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline std::complex<T>  Exp(const std::complex<T>& value)
{
    return static_cast<std::complex<T> >(std::exp(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T                Log(const T& value)
{
    ThrowTraceExceptionIf(KLogMathsException, value<=klab::TTypeInfo<T>::ZERO);

    return static_cast<T>(::log(value));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Log(klab::UInt32 value)
{
    ThrowTraceExceptionIf(KLogMathsException, value<=0);

    return ::log(static_cast<klab::Real>(value));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Log(klab::Int32 value)
{
    ThrowTraceExceptionIf(KLogMathsException, value<=0);

    return ::log(static_cast<klab::Real>(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline std::complex<T>  Log(const std::complex<T>& value)
{
    return static_cast<std::complex<T> >(std::log(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T                Log2(const T& value)
{
    ThrowTraceExceptionIf(KLogMathsException, value<=klab::TTypeInfo<T>::ZERO);

    return (klab::Log(value) * static_cast<T>(INV_LN2));  
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Log2(klab::UInt32 value)
{
    ThrowTraceExceptionIf(KLogMathsException, value<=0);

    return (klab::Log(value) * static_cast<klab::Real>(INV_LN2));  
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Log2(klab::Int32 value)
{
    ThrowTraceExceptionIf(KLogMathsException, value<=0);

    return (klab::Log(value) * static_cast<klab::Real>(INV_LN2));  
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline std::complex<T>  Log2(const std::complex<T>& value)
{
    return static_cast<std::complex<T> >(klab::Log(value) * static_cast<T>(INV_LN2));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T                Log10(const T& value)
{
    ThrowTraceExceptionIf(KLogMathsException, value<=klab::TTypeInfo<T>::ZERO);

    return static_cast<T>(::log10(value));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Log10(klab::UInt32 value)
{
    ThrowTraceExceptionIf(KLogMathsException, value<=0);

    return ::log10(static_cast<klab::Real>(value));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::Real       Log10(klab::Int32 value)
{
    ThrowTraceExceptionIf(KLogMathsException, value<=0);

    return ::log10(static_cast<klab::Real>(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline std::complex<T>  Log10(const std::complex<T>& value)
{
    return static_cast<std::complex<T> >(std::log10(value));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T                Pow(const T& base, klab::Int32 exponent)
{
    return static_cast<T>(::pow(base, exponent));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T                Pow(const T& base, const T& exponent)
{
    return static_cast<T>(::pow(base, exponent));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline std::complex<T>  Pow(const std::complex<T>& value, const T& exponent)
{
    return static_cast<std::complex<T> >(std::pow(value, exponent));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline std::complex<T>  Pow(const std::complex<T>& value, const std::complex<T>& exponent)
{
    return static_cast<std::complex<T> >(std::pow(value, exponent));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::DoubleReal Pow(klab::UInt32 base, klab::Int32 exponent)
{
    return static_cast<klab::DoubleReal>(::pow(static_cast<klab::DoubleReal>(base), exponent));
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::DoubleReal Pow(klab::Int32 base, klab::Int32 exponent)
{
    return static_cast<klab::DoubleReal>(::pow(static_cast<klab::DoubleReal>(base), exponent));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline std::complex<T>  Pow(const std::complex<T>& value, klab::Int32 exponent)
{
    return static_cast<std::complex<T> >(std::pow(value, exponent));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline T                Conj(const T& x)
{
    return x;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline std::complex<T>  Conj(const std::complex<T>& x)
{
    return std::complex<T>(x.real(), -x.imag());
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
