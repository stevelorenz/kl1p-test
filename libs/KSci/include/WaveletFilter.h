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

#ifndef KLAB_WAVELETFILTER_H
#define KLAB_WAVELETFILTER_H

#include "TrigoUtil.h"
#include "ArmadilloUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KWaveletFilterException, KException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TWaveletFilter
{
public:

    TWaveletFilter();
    TWaveletFilter(const TWaveletFilter<T>& filter);
    virtual ~TWaveletFilter();

    TWaveletFilter<T>&      operator=(const TWaveletFilter<T>& filter);

    virtual klab::UInt32    waveLength() const = 0;
    virtual const T&        h0(klab::UInt32 i) const = 0;
    virtual const T&        h1(klab::UInt32 i) const = 0;
    virtual const T&        rh0(klab::UInt32 i) const = 0;
    virtual const T&        rh1(klab::UInt32 i) const = 0;

    virtual void            transformMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);       // Compute filter on every rows of the matrix.
    virtual void            transformMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);    // Compute filter on every columns of the matrix.
    virtual void            invertMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);          // Compute inverse filter on every rows of the matrix.
    virtual void            invertMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);       // Compute inverse filter on every columns of the matrix.    
    
    virtual void            forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void            forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void            backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void            backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);


protected:

    void                    splitMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    void                    splitMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    void                    mergeMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    void                    mergeMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols); 


public:

    klab::UInt32    countReferences() const;

    template<class U>
    friend void     AddSmartPointerReference(const TWaveletFilter<U>* filter);

    template<class U>
    friend void     ReleaseSmartPointerReference(const TWaveletFilter<U>* filter);


private:

    mutable klab::TAtomicCount<klab::UInt32>    _countReferences;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TWaveletFilter<T>::TWaveletFilter() :
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TWaveletFilter<T>::TWaveletFilter(const TWaveletFilter<T>& filter) : 
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TWaveletFilter<T>::~TWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TWaveletFilter<T>& TWaveletFilter<T>::operator=(const TWaveletFilter<T>& filter)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::transformMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
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
            for(klab::UInt32 j=0; j<waveLength(); ++j)
            {
                klab::UInt32 k = (i<<1) + j;
                while(k >= n)
                    k -= n;

                T inKRow            = in(row, k);
                inout(row, i)      += inKRow * h0(j);   // Low pass filter (energy).
                inout(row, i+half) += inKRow * h1(j);   // High pass filter (details).
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::transformMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
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
            for(klab::UInt32 j=0; j<waveLength(); ++j)
            {
                klab::UInt32 k = (i<<1) + j;
                while(k >= m)
                    k -= m;

                T inKCol            = in(k, col);
                inout(i, col)      += inKCol * h0(j);   // Low pass filter (energy).
                inout(i+half, col) += inKCol * h1(j);   // High pass filter (details).
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::invertMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
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
            for(klab::UInt32 j=0; j<waveLength(); ++j)
            {
                klab::UInt32 k = (i<<1) + j;
                while(k >= n)
                    k -= n;

                inout(row, k) += in(row, i)*rh0(j) + in(row, i+half)*rh1(j);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::invertMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
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
            for(klab::UInt32 j=0; j<waveLength(); ++j)
            {
                klab::UInt32 k = (i<<1) + j;
                while(k >= m)
                    k -= m;

                inout(k, col) += in(i, col)*rh0(j) + in(i+half, col)*rh1(j);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->transformMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->transformMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->invertMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->invertMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::splitMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        arma::Mat<T> tmp(m, n);  

        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {                       
            for(klab::UInt32 i=0; i<n; i+=2)
                tmp(row, i>>1) = inout(row, i);

            for(klab::UInt32 i=1; i<n; i+=2)
                tmp(row, half+(i>>1)) = inout(row, i);

            for(klab::UInt32 i=0; i<n; ++i)
                inout(row, i) = tmp(row, i);
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::splitMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        arma::Mat<T> tmp(m, n);  

        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {
            for(klab::UInt32 i=0; i<m; i+=2)
                tmp(i>>1, col) = inout(i, col);

            for(klab::UInt32 i=1; i<m; i+=2)
                tmp(half+(i>>1), col) = inout(i, col);

            for(klab::UInt32 i=0; i<m; ++i)
                inout(i, col) = tmp(i, col);
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::mergeMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        arma::Mat<T> tmp(m, n);  

        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {
            for(klab::UInt32 i=0; i<half; ++i)
            {
                tmp(row, i<<1)     = inout(row, i);
                tmp(row, (i<<1)+1) = inout(row, i+half);
            }

            for(klab::UInt32 i=0; i<n; ++i)
                inout(row, i) = tmp(row, i);
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWaveletFilter<T>::mergeMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        arma::Mat<T> tmp(m, n);  

        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {
            for(klab::UInt32 i=0; i<half; ++i)
            {
                tmp(i<<1, col)     = inout(i, col);
                tmp((i<<1)+1, col) = inout(i+half, col);
            }

            for(klab::UInt32 i=0; i<m; ++i)
                inout(i, col) = tmp(i, col);
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TWaveletFilter<T>::countReferences() const
{
    return _countReferences;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void    AddSmartPointerReference(const TWaveletFilter<T>* filter)
{
    if(filter != 0)
        ++(filter->_countReferences);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void    ReleaseSmartPointerReference(const TWaveletFilter<T>* filter)
{
    if(filter != 0)
    {
        if(--(filter->_countReferences) == 0)
            klab::CheckedDelete(filter);
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
