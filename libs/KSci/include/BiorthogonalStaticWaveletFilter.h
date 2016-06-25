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

#ifndef KLAB_BIORTHOGONALSTATICWAVELETFILTER_H
#define KLAB_BIORTHOGONALSTATICWAVELETFILTER_H

#include "StaticWaveletFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
class TBiorthogonalStaticWaveletFilter : public TStaticWaveletFilter<T, klab::MAX<klab::UInt32, H0, H1>::RESULT>
{
public:

    TBiorthogonalStaticWaveletFilter();
    TBiorthogonalStaticWaveletFilter(const TBiorthogonalStaticWaveletFilter<T, H0, H1>& filter);
    virtual ~TBiorthogonalStaticWaveletFilter();

    TBiorthogonalStaticWaveletFilter<T, H0, H1>& operator=(const TBiorthogonalStaticWaveletFilter<T, H0, H1>& filter);

    virtual void            transformMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);       // Compute filter on every rows of the matrix.
    virtual void            transformMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);    // Compute filter on every columns of the matrix.
    virtual void            invertMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);          // Compute inverse filter on every rows of the matrix.
    virtual void            invertMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);       // Compute inverse filter on every columns of the matrix.  

    virtual const T&        rh0(klab::UInt32 i) const;    
    virtual const T&        rh1(klab::UInt32 i) const;


protected:

    T   _rh0[klab::MAX<klab::UInt32, H0, H1>::RESULT];    
    T   _rh1[klab::MAX<klab::UInt32, H0, H1>::RESULT];
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline TBiorthogonalStaticWaveletFilter<T, H0, H1>::TBiorthogonalStaticWaveletFilter() : TStaticWaveletFilter<T, klab::MAX<klab::UInt32, H0, H1>::RESULT>()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline TBiorthogonalStaticWaveletFilter<T, H0, H1>::TBiorthogonalStaticWaveletFilter(const TBiorthogonalStaticWaveletFilter<T, H0, H1>& filter) : TStaticWaveletFilter<T, klab::MAX<klab::UInt32, H0, H1>::RESULT>(filter)
{
    klab::COPYARRAY<T, klab::MAX<klab::UInt32, H0, H1>::RESULT>::Do(filter._rh0, _rh0);    
    klab::COPYARRAY<T, klab::MAX<klab::UInt32, H0, H1>::RESULT>::Do(filter._rh1, _rh1);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline TBiorthogonalStaticWaveletFilter<T, H0, H1>::~TBiorthogonalStaticWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline TBiorthogonalStaticWaveletFilter<T, H0, H1>& TBiorthogonalStaticWaveletFilter<T, H0, H1>::operator=(const TBiorthogonalStaticWaveletFilter<T, H0, H1>& filter)
{
    if(this != &filter)
    {
        TStaticWaveletFilter<T, klab::MAX<klab::UInt32, H0, H1>::RESULT>::operator=(filter);

        klab::COPYARRAY<T, klab::MAX<klab::UInt32, H0, H1>::RESULT>::Do(filter._rh0, _rh0);    
        klab::COPYARRAY<T, klab::MAX<klab::UInt32, H0, H1>::RESULT>::Do(filter._rh1, _rh1);
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline const T& TBiorthogonalStaticWaveletFilter<T, H0, H1>::rh0(klab::UInt32 i) const
{
    if(i < klab::MAX<klab::UInt32, H0, H1>::RESULT) return _rh0[i];
    else                                            return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline const T& TBiorthogonalStaticWaveletFilter<T, H0, H1>::rh1(klab::UInt32 i) const
{
    if(i < klab::MAX<klab::UInt32, H0, H1>::RESULT) return _rh1[i];
    else                                            return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline void TBiorthogonalStaticWaveletFilter<T, H0, H1>::transformMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    arma::Mat<T> in(m, n);
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
        {
            in(i, j)    = inout(i, j);
            inout(i, j) = klab::TTypeInfo<T>::ZERO;
        }
    }

    klab::UInt32 half = n>>1;
    for(klab::UInt32 row=0; row<m; ++row)
    {
        for(klab::UInt32 i=0; i<half; ++i)
        {
            for(klab::UInt32 j=0; j<this->waveLength(); ++j)
            {
                klab::UInt32 k = klab::Abs(static_cast<klab::Int32>((i<<1) + j) - static_cast<klab::Int32>(this->waveLength()>>1));
                while(k >= n)
                    k = klab::Abs(static_cast<klab::Int32>(n<<1) - static_cast<klab::Int32>(k) - 2);  

                T inKRow            = in(row, k);
                inout(row, i)      += inKRow * this->h0(j); // Low pass filter (energy).
                inout(row, i+half) += inKRow * this->h1(j); // High pass filter (details).
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline void TBiorthogonalStaticWaveletFilter<T, H0, H1>::transformMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    arma::Mat<T> in(m, n);
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
        {
            in(i, j)    = inout(i, j);
            inout(i, j) = klab::TTypeInfo<T>::ZERO;
        }
    }

    klab::UInt32 half = m>>1;
    for(klab::UInt32 col=0; col<n; ++col)
    {
        for(klab::UInt32 i=0; i<half; ++i)
        {
            for(klab::UInt32 j=0; j<this->waveLength(); ++j)
            {
                klab::UInt32 k = klab::Abs(static_cast<klab::Int32>((i<<1) + j) - static_cast<klab::Int32>(this->waveLength()>>1));
                while(k >= m)
                    k = klab::Abs(static_cast<klab::Int32>(m<<1) - static_cast<klab::Int32>(k) - 2); 

                T inKCol            = in(k, col);
                inout(i, col)      += inKCol * this->h0(j); // Low pass filter (energy).
                inout(i+half, col) += inKCol * this->h1(j); // High pass filter (details).
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline void TBiorthogonalStaticWaveletFilter<T, H0, H1>::invertMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    arma::Mat<T> in(m, n);
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
        {
            in(i, j)    = inout(i, j);
            inout(i, j) = klab::TTypeInfo<T>::ZERO;
        }
    }

    klab::UInt32 half = n>>1;
    for(klab::UInt32 row=0; row<m; ++row)
    {
        for(klab::UInt32 i=0; i<n; ++i)
        {
            for(klab::UInt32 j=0; j<this->waveLength(); ++j)
            {
                klab::UInt32 k = klab::Abs(static_cast<klab::Int32>(i+j) - static_cast<klab::Int32>(this->waveLength()>>1));
                while(k >= n)
                    k = klab::Abs(static_cast<klab::Int32>(n<<1) - static_cast<klab::Int32>(k) - 2); 

                if(k%2 == 0)    inout(row, i) += in(row, k>>1) * this->rh0(j>0?j-1:(this->waveLength()-1));
                else            inout(row, i) += in(row, (k>>1)+half) * this->rh1(j);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline void TBiorthogonalStaticWaveletFilter<T, H0, H1>::invertMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    arma::Mat<T> in(m, n);
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
        {
            in(i, j)    = inout(i, j);
            inout(i, j) = klab::TTypeInfo<T>::ZERO;
        }
    }

    klab::UInt32 half = m>>1;
    for(klab::UInt32 col=0; col<n; ++col)
    {
        for(klab::UInt32 i=0; i<m; ++i)
        {            
            for(klab::UInt32 j=0; j<this->waveLength(); ++j)
            {
                klab::UInt32 k = klab::Abs(static_cast<klab::Int32>(i+j) - static_cast<klab::Int32>(this->waveLength()>>1));
                while(k >= m)
                    k = klab::Abs(static_cast<klab::Int32>(m<<1) - static_cast<klab::Int32>(k) - 2); 
  
                if(k%2 == 0)    inout(i, col) += in(k>>1, col) * this->rh0(j>0?j-1:(this->waveLength()-1));
                else            inout(i, col) += in((k>>1)+half, col) * this->rh1(j);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
