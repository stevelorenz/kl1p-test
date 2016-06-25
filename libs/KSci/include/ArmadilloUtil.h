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
//
// 
// The KSci library use Armadillo C++ library for linear algebra operations.
//   Armadillo: An Open Source C++ Linear Algebra Library for Fast Prototyping and Computationally Intensive Experiments.
//   Conrad Sanderson - Technical Report, NICTA, 2010.
// See http://arma.sourceforge.net/ for more info.

#ifndef KLAB_ARMADILLOUTIL_H
#define KLAB_ARMADILLOUTIL_H

#include <armadillo>
#include "MathsUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T    Min(const arma::Col<T>& col)
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 n = col.n_rows;
    if(n > 0)
    {
        ret = col[0];
        for(klab::UInt32 i=1; i<n; ++i)
        {
            if(col[i] < ret)
                ret = col[i];
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T    Min(const arma::Row<T>& row)
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 n = row.n_cols;
    if(n > 0)
    {
        ret = row[0];
        for(klab::UInt32 i=1; i<n; ++i)
        {
            if(row[i] < ret)
                ret = row[i];
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T    Min(const arma::Mat<T>& mat)
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 m = mat.n_rows;
    klab::UInt32 n = mat.n_cols;
    if(m>0 && n>0)
    {
        ret = mat(0, 0);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                if(mat(i, j) < ret)
                    ret = mat(i, j);
            }
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T    Max(const arma::Col<T>& col)
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 n = col.n_rows;
    if(n > 0)
    {
        ret = col[0];
        for(klab::UInt32 i=1; i<n; ++i)
        {
            if(col[i] > ret)
                ret = col[i];
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T    Max(const arma::Row<T>& row)
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 n = row.n_cols;
    if(n > 0)
    {
        ret = row[0];
        for(klab::UInt32 i=1; i<n; ++i)
        {
            if(row[i] > ret)
                ret = row[i];
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T    Max(const arma::Mat<T>& mat)
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 m = mat.n_rows;
    klab::UInt32 n = mat.n_cols;
    if(m>0 && n>0)
    {
        ret = mat(0, 0);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                if(mat(i, j) > ret)
                    ret = mat(i, j);
            }
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T        GetFrom(const arma::Col<T>& col, klab::UInt32 i)
{
    if(i<col.n_rows)    return col[i];
    else                return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T        GetFrom(const arma::Row<T>& row, klab::UInt32 i)
{
    if(i<row.n_cols)    return row[i];
    else                return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T        GetFrom(const arma::Mat<T>& mat, klab::UInt32 i, klab::UInt32 j)
{
    if(i<mat.n_rows && j<mat.n_cols)    return mat(i, j);
    else                                return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void     SetTo(arma::Col<T>& col, klab::UInt32 i, const T& value)
{
    if(i < col.n_rows)    
        col[i] = value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void     SetTo(arma::Row<T>& row, klab::UInt32 i, const T& value)
{
    if(i < row.n_cols)    
        row[i] = value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void     SetTo(arma::Mat<T>& mat, klab::UInt32 i, klab::UInt32 j, const T& value)
{
    if(i<mat.n_rows && j<mat.n_cols)    
        mat(i, j) = value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     Equals(const arma::Col<T>& left, const arma::Col<T>& right, const T& epsilon)
{
    klab::UInt32 n = klab::Max(left.n_rows, right.n_rows);

    bool ret = true;
    for(klab::UInt32 i=0; i<n && ret; ++i)
        ret = klab::Equals(klab::GetFrom(left, i), klab::GetFrom(right, i), epsilon);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     Equals(const arma::Row<T>& left, const arma::Row<T>& right, const T& epsilon)
{
    klab::UInt32 n = klab::Max(left.n_cols, right.n_cols);

    bool ret = true;
    for(klab::UInt32 i=0; i<n && ret; ++i)
        ret = klab::Equals(klab::GetFrom(left, i), klab::GetFrom(right, i), epsilon);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     Equals(const arma::Mat<T>& left, const arma::Mat<T>& right, const T& epsilon)
{
    klab::UInt32 m = klab::Max(left.n_rows, right.n_rows);
    klab::UInt32 n = klab::Max(left.n_cols, right.n_cols);

    bool ret = true;
    for(klab::UInt32 i=0; i<m && ret; ++i)
    {
        for(klab::UInt32 j=0; j<n && ret; ++j)
            ret = klab::Equals(klab::GetFrom(left, i, j), klab::GetFrom(right, i, j), epsilon);
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     Equals(const arma::Col<T>& left, const arma::Col<T>& right)
{
    return klab::Equals<T>(left, right, klab::TTypeInfo<T>::EPSILON); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     Equals(const arma::Row<T>& left, const arma::Row<T>& right)
{
    return klab::Equals<T>(left, right, klab::TTypeInfo<T>::EPSILON); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     Equals(const arma::Mat<T>& left, const arma::Mat<T>& right)
{
    return klab::Equals<T>(left, right, klab::TTypeInfo<T>::EPSILON); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class TIn, class TOut>
inline void         Convert(const arma::Col<TIn>& in, class arma::Col<TOut>& out)
{
    out.set_size(in.n_rows);
    for(klab::UInt32 i=0; i<in.n_rows; ++i)
        out[i] = in[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void         Convert(const arma::Col<std::complex<T> >& in, class arma::Col<T>& out)
{
    out.set_size(in.n_rows);
    for(klab::UInt32 i=0; i<in.n_rows; ++i)
        out[i] = in[i].real();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TIn, class TOut>
inline void         Convert(const arma::Row<TIn>& in, class arma::Row<TOut>& out)
{
    out.set_size(in.n_cols);
    for(klab::UInt32 i=0; i<in.n_cols; ++i)
        out[i] = in[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void         Convert(const arma::Row<std::complex<T> >& in, class arma::Row<T>& out)
{
    out.set_size(in.n_cols);
    for(klab::UInt32 i=0; i<in.n_cols; ++i)
        out[i] = in[i].real();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TIn, class TOut>
inline void         Convert(const arma::Mat<TIn>& in, class arma::Mat<TOut>& out)
{
    out.set_size(in.n_rows, in.n_cols);
    for(klab::UInt32 i=0; i<in.n_rows; ++i)
    {
        for(klab::UInt32 j=0; j<in.n_cols; ++j)
            out(i, j) = in(i, j);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void         Convert(const arma::Mat<std::complex<T> >& in, class arma::Mat<T>& out)
{
    out.set_size(in.n_rows, in.n_cols);
    for(klab::UInt32 i=0; i<in.n_rows; ++i)
    {
        for(klab::UInt32 j=0; j<in.n_cols; ++j)
            out(i, j) = in(i, j).real();
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void         ShiftCircular(const arma::Col<T>& in, klab::Int32 d, arma::Col<T>& out)
{
    klab::UInt32 n = in.n_rows;
    out.set_size(n);

    if(n > 0)
    {
        klab::Int32 s = d;
        klab::UInt32 absD = klab::Abs(d);
        if(absD > n)
            s = ((d>=0?1:-1) * (absD%n));

        if(s < 0)
            s = ((n+s) % n);

        if(static_cast<klab::UInt32>(s) < n)
        {
            klab::UInt32 ns = (n-static_cast<klab::UInt32>(s));
            for(klab::UInt32 i=0; i<static_cast<klab::UInt32>(s); ++i)
                out[i] = in[ns+i];

            for(klab::UInt32 i=0; i<ns; ++i)
                out[s+i] = in[i]; 
        }
        else
        {
            out = in;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void         ShiftCircular(const arma::Row<T>& in, klab::Int32 d, arma::Row<T>& out)
{
    klab::UInt32 n = in.n_cols;
    out.set_size(n);

    if(n > 0)
    {
        klab::Int32 s = d;
        klab::UInt32 absD = klab::Abs(d);
        if(absD > n)
            s = ((d>=0?1:-1) * (absD%n));

        if(s < 0)
            s = ((n+s) % n);

        if(static_cast<klab::UInt32>(s) < n)
        {
            klab::UInt32 ns = (n-static_cast<klab::UInt32>(s));
            for(klab::UInt32 i=0; i<static_cast<klab::UInt32>(s); ++i)
                out[i] = in[ns+i];

            for(klab::UInt32 i=0; i<ns; ++i)
                out[s+i] = in[i]; 
        }
        else
        {
            out = in;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void         ShiftCircular(arma::Col<T>& inout, klab::Int32 d)
{
    arma::Col<T> in(inout);
    klab::ShiftCircular(in, d, inout);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void         ShiftCircular(arma::Row<T>& inout, klab::Int32 d)
{
    arma::Row<T> in(inout);
    klab::ShiftCircular(in, d, inout);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
