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

#ifndef KLAB_FWT2D_H
#define KLAB_FWT2D_H

#include "FWT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter=TDelegateWaveletFilter<T> >
class TFWT2D
{
public:

    TFWT2D();
    TFWT2D(const TFilter& filter);
    TFWT2D(const TFWT2D<T, TFilter>& fwt);
    virtual ~TFWT2D();

    TFWT2D<T, TFilter>& operator=(const TFWT2D<T, TFilter>& fwt);

    const TFilter&  filter() const;
    TFilter&        filter();

    void            transform(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);
    void            invert(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 level=klab::TTypeInfo<klab::UInt32>::MAX);


private:

    TFilter         _filter;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT2D<T, TFilter>::TFWT2D() : 
_filter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT2D<T, TFilter>::TFWT2D(const TFilter& filter) : 
_filter(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT2D<T, TFilter>::TFWT2D(const TFWT2D<T, TFilter>& fwt) : 
_filter(fwt._filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT2D<T, TFilter>::~TFWT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFWT2D<T, TFilter>& TFWT2D<T, TFilter>::operator=(const TFWT2D<T, TFilter>& fwt)
{
    if(this != &fwt)
    {
        _filter = fwt._filter;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const TFilter& TFWT2D<T, TFilter>::filter() const
{
    return _filter;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFilter& TFWT2D<T, TFilter>::filter()
{
    return _filter;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT2D<T, TFilter>::transform(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 level)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;

    out = in;

    if(m>0 && n>0)
    {
        ThrowTraceExceptionIf(KSizePowerOf2FWTException, klab::IsPowerOf2(m)==false);
        ThrowTraceExceptionIf(KSizePowerOf2FWTException, klab::IsPowerOf2(n)==false);

        klab::UInt32 l  = 0;
        klab::UInt32 hm = m;
        klab::UInt32 hn = n;

        TFWT1D<T, TFilter> fwt(_filter);

        while(hm>1 && hn>1 && l<level)
        {          
            fwt.transformMatrixColumns(out, hm, hn, 1);     // Apply FWT1D on columns.
            fwt.transformMatrixRows(out, hm, hn, 1);        // Apply FWT1D on rows.

            hm >>= 1;
            hn >>= 1;
            ++l;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TFWT2D<T, TFilter>::invert(const arma::Mat<T>& in, arma::Mat<T>& out, klab::UInt32 level)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;

    out = in;

    if(m>0 && n>0)
    {
        ThrowTraceExceptionIf(KSizePowerOf2FWTException, klab::IsPowerOf2(m)==false); 
        ThrowTraceExceptionIf(KSizePowerOf2FWTException, klab::IsPowerOf2(n)==false);         

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

        TFWT1D<T, TFilter> fwt(_filter);

        while(hm<=m && hn<=n && l>=0)
        {          
            fwt.invertMatrixRows(out, hm, hn, 1);       // Apply FWT1D on rows.
            fwt.invertMatrixColumns(out, hm, hn, 1);    // Apply FWT1D on columns.

            hm <<= 1;
            hn <<= 1;
            --l;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
