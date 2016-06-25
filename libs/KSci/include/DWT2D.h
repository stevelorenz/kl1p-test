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

#ifndef KLAB_DWT2D_H
#define KLAB_DWT2D_H

#include "DWT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter=TDelegateWaveletFilter<T> >
class TDWT2D
{
public:

    TDWT2D();
    TDWT2D(const TFilter& filter);
    TDWT2D(const TDWT2D<T, TFilter>& dwt);
    virtual ~TDWT2D();

    TDWT2D<T, TFilter>& operator=(const TDWT2D<T, TFilter>& dwt);

    const TFilter&  filter() const;
    TFilter&        filter();

    void            transform(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);
    void            invert(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);


private:

    TFilter     _filter;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDWT2D<T, TFilter>::TDWT2D() : 
_filter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDWT2D<T, TFilter>::TDWT2D(const TFilter& filter) : 
_filter(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDWT2D<T, TFilter>::TDWT2D(const TDWT2D<T, TFilter>& dwt) : 
_filter(dwt._filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDWT2D<T, TFilter>::~TDWT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDWT2D<T, TFilter>& TDWT2D<T, TFilter>::operator=(const TDWT2D<T, TFilter>& dwt)
{
    if(this != &dwt)
    {
        _filter = dwt._filter;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const TFilter& TDWT2D<T, TFilter>::filter() const
{
    return _filter;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFilter& TDWT2D<T, TFilter>::filter()
{
    return _filter;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDWT2D<T, TFilter>::transform(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 level)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;

    out = in;

    if(m>0 && n>0)
    {
        ThrowTraceExceptionIf(KSizePowerOf2DWTException, klab::IsPowerOf2(m)==false);
        ThrowTraceExceptionIf(KSizePowerOf2DWTException, klab::IsPowerOf2(n)==false);

        klab::UInt32 l  = 0;
        klab::UInt32 hm = m;
        klab::UInt32 hn = n;

        TDWT1D<T, TFilter> dwt(_filter);

        while(hm>1 && hn>1 && l<level)
        {           
            dwt.transformMatrixColumns(out, hm, hn, 1);     // Apply DWT1D on columns.
            dwt.transformMatrixRows(out, hm, hn, 1);        // Apply DWT1D on rows.

            hm >>= 1;
            hn >>= 1;
            ++l;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDWT2D<T, TFilter>::invert(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 level)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;

    out = in;

    if(m>0 && n>0)
    {
        ThrowTraceExceptionIf(KSizePowerOf2DWTException, klab::IsPowerOf2(m)==false); 
        ThrowTraceExceptionIf(KSizePowerOf2DWTException, klab::IsPowerOf2(n)==false);         

        klab::Int32   l = static_cast<klab::Int32>(klab::Log2(klab::Min(m, n))+0.5);	// To avoid rounding error.
        klab::UInt32 hm = 2;
        klab::UInt32 hn = 2;

        if(m > n)       hm <<= static_cast<klab::UInt32>(klab::Log2(m/n)+0.5);	// To avoid rounding error.
        else if(m < n)  hn <<= static_cast<klab::UInt32>(klab::Log2(n/m)+0.5);	// To avoid rounding error.

        if(level < static_cast<klab::UInt32>(l))
        {
            hm <<= (l-level);
            hn <<= (l-level);
            l    = static_cast<klab::Int32>(level);        
        }

        TDWT1D<T, TFilter> dwt(_filter);

        while(hm<=m && hn<=n && l>=0)
        {          
            dwt.invertMatrixRows(out, hm, hn, 1);       // Apply DWT1D on rows.
            dwt.invertMatrixColumns(out, hm, hn, 1);    // Apply DWT1D on columns.

            hm <<= 1;
            hn <<= 1;
            --l;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
