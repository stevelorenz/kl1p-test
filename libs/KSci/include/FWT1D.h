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

#ifndef KLAB_FWT1D_H
#define KLAB_FWT1D_H

#include "DWT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KFWTException, KWaveletException)
KLAB_DECLARE_EXCEPTION(KSizePowerOf2FWTException, KFWTException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter=TDelegateWaveletFilter<T> >
class TFWT1D
{
public:

    TFWT1D();
    TFWT1D(const TFilter& filter);
    TFWT1D(const TFWT1D<T, TFilter>& fwt);
    virtual ~TFWT1D();

    TFWT1D<T, TFilter>& operator=(const TFWT1D<T, TFilter>& fwt);

    const TFilter&      filter() const;
    TFilter&            filter();

    void                transform(const arma::Col<T>& in, arma::Col<T>& out, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);
    void                invert(const arma::Col<T>& in, arma::Col<T>& out, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);

    void        transformMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);                             // Compute FWT on every rows of the matrix.
    void        transformMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);                          // Compute FWT on every columns of the matrix.
    void        transformMatrixRows(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);       // Compute FWT on every rows of the matrix.
    void        transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);    // Compute FWT on every columns of the matrix.
  
    void        invertMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);                                // Compute inverse FWT on every rows of the matrix.
    void        invertMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);                             // Compute inverse FWT on every columns of the matrix.
    void        invertMatrixRows(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);          // Compute inverse FWT on every rows of the matrix.
    void        invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);       // Compute inverse FWT on every columns of the matrix.


private:

    TFilter     _filter;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT1D<T, TFilter>::TFWT1D() : 
_filter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT1D<T, TFilter>::TFWT1D(const TFilter& filter) : 
_filter(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT1D<T, TFilter>::TFWT1D(const TFWT1D<T, TFilter>& fwt) : 
_filter(fwt._filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT1D<T, TFilter>::~TFWT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT1D<T, TFilter>& TFWT1D<T, TFilter>::operator=(const TFWT1D<T, TFilter>& fwt)
{
    if(this != &fwt)
    {
        _filter = fwt._filter;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const TFilter& TFWT1D<T, TFilter>::filter() const
{
    return _filter;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFilter& TFWT1D<T, TFilter>::filter()
{
    return _filter;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::transform(const arma::Col<T>& in, arma::Col<T>& out, klab::UInt32 level)
{
    this->transformMatrixColumns(in, out, in.n_rows, in.n_cols, level);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::invert(const arma::Col<T>& in, arma::Col<T>& out, klab::UInt32 level)
{
    this->invertMatrixColumns(in, out, in.n_rows, in.n_cols, level);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::transformMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        ThrowTraceExceptionIf(KSizePowerOf2FWTException, klab::IsPowerOf2(n)==false);

        klab::UInt32 l = 0;
        klab::UInt32 h = n;

        while(h>1 && l<level)
        {
            _filter.forwardOnMatrixRows(inout, m, h);

            h >>= 1;
            ++l;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::transformMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        ThrowTraceExceptionIf(KSizePowerOf2FWTException, klab::IsPowerOf2(m)==false);

        klab::UInt32 l = 0;
        klab::UInt32 h = m;

        while(h>1 && l<level)
        {
            _filter.forwardOnMatrixColumns(inout, h, n);

            h >>= 1;
            ++l;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::transformMatrixRows(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level)
{
    out = in;
    this->transformMatrixRows(out, rows, cols, level);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level)
{
    out = in;
    this->transformMatrixColumns(out, rows, cols, level);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::invertMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        ThrowTraceExceptionIf(KSizePowerOf2FWTException, klab::IsPowerOf2(n)==false); 

        klab::Int32  l = static_cast<klab::Int32>(klab::Log2(n)+0.5);	// To avoid rounding error.
        klab::UInt32 h = 2;

        if(level < static_cast<klab::UInt32>(l))
        {
            h <<= (l-level);
            l   = static_cast<klab::Int32>(level);        
        }

        while(h<=n && l>=0)
        {
            _filter.backwardOnMatrixRows(inout, m, h);

            h <<= 1;
            --l;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::invertMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        ThrowTraceExceptionIf(KSizePowerOf2FWTException, klab::IsPowerOf2(m)==false); 

        klab::Int32  l = static_cast<klab::Int32>(klab::Log2(m)+0.5);	// To avoid rounding error.
        klab::UInt32 h = 2;

        if(level < static_cast<klab::UInt32>(l))
        {
            h <<= (l-level);
            l   = static_cast<klab::Int32>(level);        
        }

        while(h<=m && l>=0)
        {
            _filter.backwardOnMatrixColumns(inout, h, n);

            h <<= 1;
            --l;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::invertMatrixRows(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level)
{
    out = in;
    this->invertMatrixRows(out, rows, cols, level);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT1D<T, TFilter>::invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 rows, klab::UInt32 cols, klab::UInt32 level)
{
    out = in;
    this->invertMatrixColumns(out, rows, cols, level);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
