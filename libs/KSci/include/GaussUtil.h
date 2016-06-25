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

#ifndef KLAB_GAUSSUTIL_H
#define KLAB_GAUSSUTIL_H

#include "MathsUtil.h"
#include "ArmadilloUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KGaussException, KException)
KLAB_DECLARE_EXCEPTION(KZeroVarianceGaussException, KGaussException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void     ComputeGaussFunction(klab::UInt32 n, const T& sigma, klab::Int32 c, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KZeroVarianceGaussException, sigma==klab::TTypeInfo<T>::ZERO);

    if(out.n_rows != n)
        out.set_size(n);

    T variance = sigma*sigma;
    for(klab::UInt32 i=0; i<n; ++i)
    {
        klab::Int32 x = (static_cast<klab::Int32>(i) - c);
        out[i] = klab::Exp(static_cast<T>(-x*x) / (static_cast<T>(2)*variance));
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void     ComputeGaussFunction(klab::UInt32 n, const T& sigma, klab::Int32 c, arma::Row<T>& out)
{
    ThrowTraceExceptionIf(KZeroVarianceGaussException, sigma==klab::TTypeInfo<T>::ZERO);

    if(out.n_cols != n)
        out.set_size(n);

    T variance = sigma*sigma;
    for(klab::UInt32 i=0; i<n; ++i)
    {
        klab::Int32 x = (static_cast<klab::Int32>(i) - c);
        out[i] = klab::Exp(static_cast<T>(-x*x) / (static_cast<T>(2)*variance));
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void     ComputeGaussFunction(klab::UInt32 m, klab::UInt32 n, const T& sigma, klab::Int32 ic, klab::Int32 jc, arma::Mat<T>& out)
{
    ThrowTraceExceptionIf(KZeroVarianceGaussException, sigma==klab::TTypeInfo<T>::ZERO);

    if(out.n_rows!=m || out.n_cols!=n)
        out.set_size(m, n);

    T variance = sigma*sigma;
    for(klab::UInt32 i=0; i<m; ++i)
    {
        klab::Int32 y  = (static_cast<klab::Int32>(i) - ic);
        klab::Int32 yy = y*y;

        for(klab::UInt32 j=0; j<n; ++j)
        {
            klab::Int32 x = (static_cast<klab::Int32>(j) - jc);
            out(i, j) = klab::Exp(static_cast<T>(-(x*x + yy)) / (static_cast<T>(2)*variance));
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void     ComputeGaussWienerFunction(klab::UInt32 n, const T& sigma, klab::Int32 c, const T& gamma, arma::Col<T>& out)
{
    klab::ComputeGaussFunction(n, sigma, c, out);

    if(klab::Equals(gamma, klab::TTypeInfo<T>::ZERO))
    {
        for(klab::UInt32 i=0; i<n; ++i)
        {
            if(klab::Equals(out[i], klab::TTypeInfo<T>::ZERO))  out[i] = klab::TTypeInfo<T>::ZERO;
            else                                                out[i] = klab::TTypeInfo<T>::UNIT / out[i];
        }
    }
    else
    {
        for(klab::UInt32 i=0; i<n; ++i)
        {
            T a = (out[i]*out[i]) + gamma;
            if(a != klab::TTypeInfo<T>::ZERO)   out[i] /= a;
            else                                out[i]  = klab::TTypeInfo<T>::UNIT / out[i];
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void     ComputeGaussWienerFunction(klab::UInt32 n, const T& sigma, klab::Int32 c, const T& gamma, arma::Row<T>& out)
{
    klab::ComputeGaussFunction(n, sigma, c, out);

    if(klab::Equals(gamma, klab::TTypeInfo<T>::ZERO))
    {
        for(klab::UInt32 i=0; i<n; ++i)
        {
            if(klab::Equals(out[i], klab::TTypeInfo<T>::ZERO))  out[i] = klab::TTypeInfo<T>::ZERO;
            else                                                out[i] = klab::TTypeInfo<T>::UNIT / out[i];
        }
    }
    else
    {
        for(klab::UInt32 i=0; i<n; ++i)
        {
            T a = (out[i]*out[i]) + gamma;
            if(a != klab::TTypeInfo<T>::ZERO)   out[i] /= a;
            else                                out[i]  = klab::TTypeInfo<T>::UNIT / out[i];
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void     ComputeGaussWienerFunction(klab::UInt32 m, klab::UInt32 n, const T& sigma, klab::Int32 ic, klab::Int32 jc, const T& gamma, arma::Mat<T>& out)
{
    klab::ComputeGaussFunction(m, n, sigma, ic, jc, out);

    if(klab::Equals(gamma, klab::TTypeInfo<T>::ZERO))
    {
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                if(klab::Equals(out(i, j), klab::TTypeInfo<T>::ZERO))   out(i, j) = klab::TTypeInfo<T>::ZERO;
                else                                                    out(i, j) = klab::TTypeInfo<T>::UNIT / out(i, j);
            }
        }
    }
    else
    {
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                T a = (out(i, j)*out(i, j)) + gamma;
                if(a != klab::TTypeInfo<T>::ZERO)   out(i, j) /= a;
                else                                out(i, j)  = klab::TTypeInfo<T>::UNIT / out(i, j);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
