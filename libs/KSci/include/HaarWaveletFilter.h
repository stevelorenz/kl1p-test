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

#ifndef KLAB_HAARWAVELETFILTER_H
#define KLAB_HAARWAVELETFILTER_H

#include "StaticWaveletFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class THaarWaveletFilter : public TStaticWaveletFilter<T, 2>
{
public:

    THaarWaveletFilter();
    THaarWaveletFilter(const THaarWaveletFilter<T>& filter);
    virtual ~THaarWaveletFilter();

    THaarWaveletFilter<T>&  operator=(const THaarWaveletFilter<T>& filter);

    virtual void            forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void            forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void            backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void            backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);


protected:

    void                    predictMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    predictMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    updateMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    updateMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);


protected:

    static const T          INV_SQRT2;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T THaarWaveletFilter<T>::INV_SQRT2 = static_cast<T>(klab::INV_SQRT2);

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline THaarWaveletFilter<T>::THaarWaveletFilter() : TStaticWaveletFilter<T, 2>()
{
    this->_h0[0] = static_cast<T>(0.70710678118654752440084436210485);
    this->_h0[1] = static_cast<T>(0.70710678118654752440084436210485);

    this->_h1[0] =  this->_h0[1];
    this->_h1[1] = -this->_h0[0];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline THaarWaveletFilter<T>::THaarWaveletFilter(const THaarWaveletFilter<T>& filter) : TStaticWaveletFilter<T, 2>(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline THaarWaveletFilter<T>::~THaarWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline THaarWaveletFilter<T>& THaarWaveletFilter<T>::operator=(const THaarWaveletFilter<T>& filter)
{
    if(this != &filter)
        TStaticWaveletFilter<T, 2>::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THaarWaveletFilter<T>::forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->splitMatrixRows(inout, rows, cols);
    this->predictMatrixRows(inout, rows, cols, true);
    this->updateMatrixRows(inout, rows, cols, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THaarWaveletFilter<T>::forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->splitMatrixColumns(inout, rows, cols);
    this->predictMatrixColumns(inout, rows, cols, true);
    this->updateMatrixColumns(inout, rows, cols, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THaarWaveletFilter<T>::backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->updateMatrixRows(inout, rows, cols, false);
    this->predictMatrixRows(inout, rows, cols, false);
    this->mergeMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THaarWaveletFilter<T>::backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->updateMatrixColumns(inout, rows, cols, false);
    this->predictMatrixColumns(inout, rows, cols, false);
    this->mergeMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THaarWaveletFilter<T>::predictMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {            
            if(forward)
            {
                for(klab::UInt32 j=0; j<half; ++j)
                    inout(row, j+half) = (inout(row, j) - inout(row, j+half)) * THaarWaveletFilter<T>::INV_SQRT2;
            }
            else
            {
                for(klab::UInt32 j=0; j<half; ++j)
                    inout(row, j+half) = inout(row, j) - inout(row, j+half)*klab::SQRT2;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THaarWaveletFilter<T>::predictMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {      
            if(forward)
            {
                for(klab::UInt32 i=0; i<half; ++i)
                    inout(i+half, col) = (inout(i, col) - inout(i+half, col)) * THaarWaveletFilter<T>::INV_SQRT2;
            }
            else
            {
                for(klab::UInt32 i=0; i<half; ++i)
                    inout(i+half, col) = inout(i, col) - inout(i+half, col)*klab::SQRT2;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THaarWaveletFilter<T>::updateMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {   
            if(forward)
            {
                for(klab::UInt32 j=0; j<half; ++j)
                    inout(row, j) = inout(row, j)*klab::SQRT2 - inout(row, j+half);
            }
            else
            {
                for(klab::UInt32 j=0; j<half; ++j)
                    inout(row, j) = (inout(row, j) + inout(row, j+half)) * THaarWaveletFilter<T>::INV_SQRT2;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THaarWaveletFilter<T>::updateMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {   
            if(forward)
            {
                for(klab::UInt32 i=0; i<half; ++i)
                    inout(i, col) = inout(i, col)*klab::SQRT2 - inout(i+half, col);
            }
            else
            {
                for(klab::UInt32 i=0; i<half; ++i)
                    inout(i, col) = (inout(i, col) + inout(i+half, col)) * THaarWaveletFilter<T>::INV_SQRT2;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
