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

#ifndef KLAB_DAUBECHIESWAVELETFILTER_H
#define KLAB_DAUBECHIESWAVELETFILTER_H

#include "StaticWaveletFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
class TDaubechiesWaveletFilter : public TStaticWaveletFilter<T, N>
{
public:

    TDaubechiesWaveletFilter();
    TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, N>& filter);
    virtual ~TDaubechiesWaveletFilter();

    TDaubechiesWaveletFilter<T, N>&     operator=(const TDaubechiesWaveletFilter<T, N>& filter);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDaubechiesWaveletFilter<T, 2> : public TStaticWaveletFilter<T, 2>
{
public:

    TDaubechiesWaveletFilter();
    TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 2>& filter);
    virtual ~TDaubechiesWaveletFilter();

    TDaubechiesWaveletFilter<T, 2>&     operator=(const TDaubechiesWaveletFilter<T, 2>& filter);

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
class TDaubechiesWaveletFilter<T, 4> : public TStaticWaveletFilter<T, 4>
{
public:

    TDaubechiesWaveletFilter();
    TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 4>& filter);
    virtual ~TDaubechiesWaveletFilter();

    TDaubechiesWaveletFilter<T, 4>&     operator=(const TDaubechiesWaveletFilter<T, 4>& filter);

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

    static const T          SQRT3_DIV4;
    static const T          SQRT3MIN2_DIV4;
    static const T          SQRT3MIN1_INVSQRT2;
    static const T          SQRT3ADD1_INVSQRT2;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDaubechiesWaveletFilter<T, 6> : public TStaticWaveletFilter<T, 6>
{
public:

    TDaubechiesWaveletFilter();
    TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 6>& filter);
    virtual ~TDaubechiesWaveletFilter();

    TDaubechiesWaveletFilter<T, 6>&     operator=(const TDaubechiesWaveletFilter<T, 6>& filter);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDaubechiesWaveletFilter<T, 8> : public TStaticWaveletFilter<T, 8>
{
public:

    TDaubechiesWaveletFilter();
    TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 8>& filter);
    virtual ~TDaubechiesWaveletFilter();

    TDaubechiesWaveletFilter<T, 8>&     operator=(const TDaubechiesWaveletFilter<T, 8>& filter);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDaubechiesWaveletFilter<T, 10> : public TStaticWaveletFilter<T, 10>
{
public:

    TDaubechiesWaveletFilter();
    TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 10>& filter);
    virtual ~TDaubechiesWaveletFilter();

    TDaubechiesWaveletFilter<T, 10>&    operator=(const TDaubechiesWaveletFilter<T, 10>& filter);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline TDaubechiesWaveletFilter<T, N>::TDaubechiesWaveletFilter() : TStaticWaveletFilter<T, N>()
{
    // Undefined Daubechies wavelet instanciated (unknown coefficient N).
    KLAB_STATIC_ASSERT(sizeof(T)==0);	// Compile time validation. 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline TDaubechiesWaveletFilter<T, N>::TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, N>& filter) : TStaticWaveletFilter<T, N>(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline TDaubechiesWaveletFilter<T, N>::~TDaubechiesWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline TDaubechiesWaveletFilter<T, N>& TDaubechiesWaveletFilter<T, N>::operator=(const TDaubechiesWaveletFilter<T, N>& filter)
{
    if(this != &filter)
        TStaticWaveletFilter<T, N>::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T TDaubechiesWaveletFilter<T, 2>::INV_SQRT2 = static_cast<T>(klab::INV_SQRT2);

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 2>::TDaubechiesWaveletFilter() : TStaticWaveletFilter<T, 2>()
{
    this->_h0[0] = static_cast<T>(0.70710678118654752440084436210485);
    this->_h0[1] = static_cast<T>(0.70710678118654752440084436210485);

    this->_h1[0] =  this->_h0[1];
    this->_h1[1] = -this->_h0[0];                   
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 2>::TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 2>& filter) : TStaticWaveletFilter<T, 2>(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 2>::~TDaubechiesWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 2>& TDaubechiesWaveletFilter<T, 2>::operator=(const TDaubechiesWaveletFilter<T, 2>& filter)
{
    if(this != &filter)
        TStaticWaveletFilter<T, 2>::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 2>::forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->splitMatrixRows(inout, rows, cols);
    this->predictMatrixRows(inout, rows, cols, true);
    this->updateMatrixRows(inout, rows, cols, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 2>::forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->splitMatrixColumns(inout, rows, cols);
    this->predictMatrixColumns(inout, rows, cols, true);
    this->updateMatrixColumns(inout, rows, cols, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 2>::backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->updateMatrixRows(inout, rows, cols, false);
    this->predictMatrixRows(inout, rows, cols, false);
    this->mergeMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 2>::backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->updateMatrixColumns(inout, rows, cols, false);
    this->predictMatrixColumns(inout, rows, cols, false);
    this->mergeMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 2>::predictMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
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
                    inout(row, j+half) = (inout(row, j) - inout(row, j+half)) * TDaubechiesWaveletFilter<T, 2>::INV_SQRT2;
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
inline void TDaubechiesWaveletFilter<T, 2>::predictMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
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
                    inout(i+half, col) = (inout(i, col) - inout(i+half, col)) * TDaubechiesWaveletFilter<T, 2>::INV_SQRT2;
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
inline void TDaubechiesWaveletFilter<T, 2>::updateMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
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
                    inout(row, j) = (inout(row, j) + inout(row, j+half)) * TDaubechiesWaveletFilter<T, 2>::INV_SQRT2;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 2>::updateMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
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
                    inout(i, col) = (inout(i, col) + inout(i+half, col)) * TDaubechiesWaveletFilter<T, 2>::INV_SQRT2;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T TDaubechiesWaveletFilter<T, 4>::SQRT3_DIV4     = static_cast<T>(0.43301270189221932338186158537647);

template<class T>
const T TDaubechiesWaveletFilter<T, 4>::SQRT3MIN2_DIV4 = static_cast<T>(-0.06698729810778067661813841462353);

template<class T>
const T TDaubechiesWaveletFilter<T, 4>::SQRT3MIN1_INVSQRT2 = static_cast<T>(0.51763809020504152469779767524812);

template<class T>
const T TDaubechiesWaveletFilter<T, 4>::SQRT3ADD1_INVSQRT2 = static_cast<T>(1.9318516525781365734994863994578);

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 4>::TDaubechiesWaveletFilter() : TStaticWaveletFilter<T, 4>()
{
    this->_h0[0] = static_cast<T>( 0.482962913144534100);                            
    this->_h0[1] = static_cast<T>( 0.836516303737807720);                             
    this->_h0[2] = static_cast<T>( 0.224143868042013390);                           
    this->_h0[3] = static_cast<T>(-0.129409522551260340);   

    this->_h1[0] =  this->_h0[3];
    this->_h1[1] = -this->_h0[2];
    this->_h1[2] =  this->_h0[1];
    this->_h1[3] = -this->_h0[0];                           
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 4>::TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 4>& filter) : TStaticWaveletFilter<T, 4>(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 4>::~TDaubechiesWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 4>& TDaubechiesWaveletFilter<T, 4>::operator=(const TDaubechiesWaveletFilter<T, 4>& filter)
{
    if(this != &filter)
        TStaticWaveletFilter<T, 4>::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 4>::forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->splitMatrixRows(inout, rows, cols);
    this->predictMatrixRows(inout, rows, cols, true);
    this->updateMatrixRows(inout, rows, cols, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 4>::forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->splitMatrixColumns(inout, rows, cols);
    this->predictMatrixColumns(inout, rows, cols, true);
    this->updateMatrixColumns(inout, rows, cols, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 4>::backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->updateMatrixRows(inout, rows, cols, false);
    this->predictMatrixRows(inout, rows, cols, false);
    this->mergeMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 4>::backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->updateMatrixColumns(inout, rows, cols, false);    
    this->predictMatrixColumns(inout, rows, cols, false);
    this->mergeMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 4>::predictMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>1)
    {
        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {            
            if(forward)
            {
                for(klab::UInt32 j=0; j<half; ++j)
                    inout(row, j) += inout(row, j+half)*klab::SQRT3;   

                inout(row, half) += -TDaubechiesWaveletFilter<T, 4>::SQRT3_DIV4*inout(row, 0) - TDaubechiesWaveletFilter<T, 4>::SQRT3MIN2_DIV4*inout(row, half-1);
                for(klab::UInt32 j=1; j<half; ++j)
                    inout(row, j+half) += -TDaubechiesWaveletFilter<T, 4>::SQRT3_DIV4*inout(row, j) - TDaubechiesWaveletFilter<T, 4>::SQRT3MIN2_DIV4*inout(row, j-1);
            }
            else
            {
                inout(row, half) += TDaubechiesWaveletFilter<T, 4>::SQRT3_DIV4*inout(row, 0) + TDaubechiesWaveletFilter<T, 4>::SQRT3MIN2_DIV4*inout(row, half-1);
                for(klab::UInt32 j=1; j<half; ++j)
                    inout(row, j+half) += TDaubechiesWaveletFilter<T, 4>::SQRT3_DIV4*inout(row, j) + TDaubechiesWaveletFilter<T, 4>::SQRT3MIN2_DIV4*inout(row, j-1);

                for(klab::UInt32 j=0; j<half; ++j)
                    inout(row, j) += -inout(row, j+half)*klab::SQRT3;   
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 4>::predictMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>1 && n>0)
    {
        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {      
            if(forward)
            {
                for(klab::UInt32 i=0; i<half; ++i)
                    inout(i, col) += inout(i+half, col)*klab::SQRT3; 

                inout(half, col) += -TDaubechiesWaveletFilter<T, 4>::SQRT3_DIV4*inout(0, col) - TDaubechiesWaveletFilter<T, 4>::SQRT3MIN2_DIV4*inout(half-1, col);
                for(klab::UInt32 i=1; i<half; ++i)
                    inout(i+half, col) += -TDaubechiesWaveletFilter<T, 4>::SQRT3_DIV4*inout(i, col) - TDaubechiesWaveletFilter<T, 4>::SQRT3MIN2_DIV4*inout(i-1, col);
            }
            else
            {
                inout(half, col) += TDaubechiesWaveletFilter<T, 4>::SQRT3_DIV4*inout(0, col) + TDaubechiesWaveletFilter<T, 4>::SQRT3MIN2_DIV4*inout(half-1, col);
                for(klab::UInt32 i=1; i<half; ++i)
                    inout(i+half, col) += TDaubechiesWaveletFilter<T, 4>::SQRT3_DIV4*inout(i, col) + TDaubechiesWaveletFilter<T, 4>::SQRT3MIN2_DIV4*inout(i-1, col);

                for(klab::UInt32 i=0; i<half; ++i)
                    inout(i, col) += -inout(i+half, col)*klab::SQRT3; 
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 4>::updateMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>1)
    {
        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {   
            if(forward)
            {
                inout(row, half-1) += -inout(row, half);
                for(klab::UInt32 j=0; j<half-1; ++j)
                    inout(row, j) += -inout(row, j+half+1);  


                for(klab::UInt32 j=0; j<half; ++j)
                    inout(row, j) *= TDaubechiesWaveletFilter<T, 4>::SQRT3MIN1_INVSQRT2;

                T temp = -TDaubechiesWaveletFilter<T, 4>::SQRT3ADD1_INVSQRT2 * inout(row, half);
                for(klab::UInt32 j=0; j<half-1; ++j)
                    inout(row, j+half) = -TDaubechiesWaveletFilter<T, 4>::SQRT3ADD1_INVSQRT2 * inout(row, j+half+1);
                inout(row, n-1) = temp;
            }
            else
            {
                for(klab::UInt32 j=0; j<half; ++j)
                    inout(row, j) *= TDaubechiesWaveletFilter<T, 4>::SQRT3ADD1_INVSQRT2;

                T temp = -TDaubechiesWaveletFilter<T, 4>::SQRT3MIN1_INVSQRT2 * inout(row, n-1);
                for(klab::UInt32 j=n-1; j>half; --j)
                    inout(row,j) = -TDaubechiesWaveletFilter<T, 4>::SQRT3MIN1_INVSQRT2 * inout(row, j-1);
                inout(row, half) = temp;


                inout(row, half-1) += inout(row, half);
                for(klab::UInt32 j=0; j<half-1; ++j)
                    inout(row, j) += inout(row, j+half+1);                
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDaubechiesWaveletFilter<T, 4>::updateMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>1 && n>0)
    {
        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {   
            if(forward)
            {
                inout(half-1, col) += -inout(half, col);
                for(klab::UInt32 i=0; i<half-1; ++i)
                    inout(i, col) += -inout(i+half+1, col); 


                for(klab::UInt32 i=0; i<half; ++i)
                    inout(i, col) *= TDaubechiesWaveletFilter<T, 4>::SQRT3MIN1_INVSQRT2;

                T temp = -TDaubechiesWaveletFilter<T, 4>::SQRT3ADD1_INVSQRT2 * inout(half, col);
                for(klab::UInt32 i=0; i<half-1; ++i)
                    inout(i+half, col) = -TDaubechiesWaveletFilter<T, 4>::SQRT3ADD1_INVSQRT2 * inout(i+half+1, col);
                inout(m-1, col) = temp;
            }
            else
            {
                for(klab::UInt32 i=0; i<half; ++i)
                    inout(i, col) *= TDaubechiesWaveletFilter<T, 4>::SQRT3ADD1_INVSQRT2;

                T temp = -TDaubechiesWaveletFilter<T, 4>::SQRT3MIN1_INVSQRT2 * inout(m-1, col);
                for(klab::UInt32 i=m-1; i>half; --i)
                    inout(i, col) = -TDaubechiesWaveletFilter<T, 4>::SQRT3MIN1_INVSQRT2 * inout(i-1, col);
                inout(half, col) = temp;


                inout(half-1, col) += inout(half, col);
                for(klab::UInt32 i=0; i<half-1; ++i)
                    inout(i, col) += inout(i+half+1, col);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 6>::TDaubechiesWaveletFilter() : TStaticWaveletFilter<T, 6>()
{
    this->_h0[0] = static_cast<T>( 0.332670552950082630);                            
    this->_h0[1] = static_cast<T>( 0.806891509311092660);                             
    this->_h0[2] = static_cast<T>( 0.459877502118491490);                             
    this->_h0[3] = static_cast<T>(-0.135011020010254610);                             
    this->_h0[4] = static_cast<T>(-0.085441273882026658);                        
    this->_h0[5] = static_cast<T>( 0.035226291885709554);  

    this->_h1[0] =  this->_h0[5];
    this->_h1[1] = -this->_h0[4];
    this->_h1[2] =  this->_h0[3];
    this->_h1[3] = -this->_h0[2];
    this->_h1[4] =  this->_h0[1];
    this->_h1[5] = -this->_h0[0];                          
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 6>::TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 6>& filter) : TStaticWaveletFilter<T, 6>(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 6>::~TDaubechiesWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 6>& TDaubechiesWaveletFilter<T, 6>::operator=(const TDaubechiesWaveletFilter<T, 6>& filter)
{
    if(this != &filter)
        TStaticWaveletFilter<T, 6>::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 8>::TDaubechiesWaveletFilter() : TStaticWaveletFilter<T, 8>()
{
    this->_h0[0] = static_cast<T>( 0.23037781330889656);                             
    this->_h0[1] = static_cast<T>( 0.71484657055291567);                            
    this->_h0[2] = static_cast<T>( 0.63088076792985892);                            
    this->_h0[3] = static_cast<T>(-0.027983769416860017);                           
    this->_h0[4] = static_cast<T>(-0.18703481171909311);                           
    this->_h0[5] = static_cast<T>( 0.030841381835560837);                           
    this->_h0[6] = static_cast<T>( 0.032883011666885203);                           
    this->_h0[7] = static_cast<T>(-0.010597401785069051);   

    this->_h1[0] =  this->_h0[7];
    this->_h1[1] = -this->_h0[6];
    this->_h1[2] =  this->_h0[5];
    this->_h1[3] = -this->_h0[4];
    this->_h1[4] =  this->_h0[3];
    this->_h1[5] = -this->_h0[2];
    this->_h1[6] =  this->_h0[1];
    this->_h1[7] = -this->_h0[0];                    
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 8>::TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 8>& filter) : TStaticWaveletFilter<T, 8>(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 8>::~TDaubechiesWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 8>& TDaubechiesWaveletFilter<T, 8>::operator=(const TDaubechiesWaveletFilter<T, 8>& filter)
{
    if(this != &filter)
        TStaticWaveletFilter<T, 8>::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 10>::TDaubechiesWaveletFilter() : TStaticWaveletFilter<T, 10>()
{
    this->_h0[0] = static_cast<T>( 0.16010239797419540);                             
    this->_h0[1] = static_cast<T>( 0.60382926979719864);                            
    this->_h0[2] = static_cast<T>( 0.72430852843778171);                            
    this->_h0[3] = static_cast<T>( 0.13842814590131708);                           
    this->_h0[4] = static_cast<T>(-0.24229488706639299);                           
    this->_h0[5] = static_cast<T>(-0.03224486958464360);                           
    this->_h0[6] = static_cast<T>( 0.077571493840045427);                           
    this->_h0[7] = static_cast<T>(-0.0062414902127984851);   
    this->_h0[8] = static_cast<T>(-0.012580751999082195);  
    this->_h0[9] = static_cast<T>( 0.0033357252854738098);  

    this->_h1[0] =  this->_h0[9];
    this->_h1[1] = -this->_h0[8];
    this->_h1[2] =  this->_h0[7];
    this->_h1[3] = -this->_h0[6];
    this->_h1[4] =  this->_h0[5];
    this->_h1[5] = -this->_h0[4];
    this->_h1[6] =  this->_h0[3];
    this->_h1[7] = -this->_h0[2];       
    this->_h1[8] =  this->_h0[1];             
    this->_h1[9] = -this->_h0[0];             
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 10>::TDaubechiesWaveletFilter(const TDaubechiesWaveletFilter<T, 10>& filter) : TStaticWaveletFilter<T, 10>(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 10>::~TDaubechiesWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDaubechiesWaveletFilter<T, 10>& TDaubechiesWaveletFilter<T, 10>::operator=(const TDaubechiesWaveletFilter<T, 10>& filter)
{
    if(this != &filter)
        TStaticWaveletFilter<T, 10>::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
