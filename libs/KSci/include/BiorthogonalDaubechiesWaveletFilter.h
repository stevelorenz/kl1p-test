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

#ifndef KLAB_BIORTHOGONALDAUBECHIESWAVELETFILTER_H
#define KLAB_BIORTHOGONALDAUBECHIESWAVELETFILTER_H

#include "BiorthogonalStaticWaveletFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
class TBiorthogonalDaubechiesWaveletFilter : public TBiorthogonalStaticWaveletFilter<T, H0, H1>
{
public:

    TBiorthogonalDaubechiesWaveletFilter();
    TBiorthogonalDaubechiesWaveletFilter(const TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>& filter);
    virtual ~TBiorthogonalDaubechiesWaveletFilter();

    TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>&    operator=(const TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>& filter);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TBiorthogonalDaubechiesWaveletFilter<T, 9, 7> : public TBiorthogonalStaticWaveletFilter<T, 9, 7>
{
public:

    TBiorthogonalDaubechiesWaveletFilter();
    TBiorthogonalDaubechiesWaveletFilter(const TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>& filter);
    virtual ~TBiorthogonalDaubechiesWaveletFilter();

    TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>&  operator=(const TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>& filter);    

    virtual void            forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void            forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void            backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void            backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);


protected:

    void                    predict1MatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    predict1MatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    predict2MatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    predict2MatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    update1MatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    update1MatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    update2MatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    update2MatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    scaleMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);
    void                    scaleMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward);


protected:

    static const T          ALPHA;
    static const T          BETA;
    static const T          GAMMA;
    static const T          DELTA;
    static const T          ZETA;
    static const T          INV_ZETA;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>::TBiorthogonalDaubechiesWaveletFilter() : TBiorthogonalStaticWaveletFilter<T, H0, H1>()
{
    // Undefined Daubechies wavelet instanciated (unknown coefficients H0/H1).
    KLAB_STATIC_ASSERT(sizeof(T)==0);  // Compile time validation. 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>::TBiorthogonalDaubechiesWaveletFilter(const TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>& filter) : TBiorthogonalStaticWaveletFilter<T, H0, H1>(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>::~TBiorthogonalDaubechiesWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 H0, klab::UInt32 H1>
inline TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>& TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>::operator=(const TBiorthogonalDaubechiesWaveletFilter<T, H0, H1>& filter)
{
    if(this != &filter)
        TBiorthogonalStaticWaveletFilter<T, H0, H1>::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ALPHA = static_cast<T>(-1.5861343420693648);

template<class T>
const T TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::BETA  = static_cast<T>(-0.0529801185718856);

template<class T>
const T TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::GAMMA = static_cast<T>(0.8829110755411875);

template<class T>
const T TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::DELTA = static_cast<T>(0.4435068520511142);

template<class T>
const T TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ZETA  = static_cast<T>(1.1496043988602418);

template<class T>
const T TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::INV_ZETA = klab::TTypeInfo<T>::UNIT / TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ZETA;

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::TBiorthogonalDaubechiesWaveletFilter() : TBiorthogonalStaticWaveletFilter<T, 9, 7>()
{
    this->_h0[0] = static_cast<T>( 0.02674875741080976) * klab::SQRT2;                            
    this->_h0[1] = static_cast<T>(-0.01686411844287495) * klab::SQRT2;                             
    this->_h0[2] = static_cast<T>(-0.07822326652898785) * klab::SQRT2;                             
    this->_h0[3] = static_cast<T>( 0.2668641184428723) * klab::SQRT2;                             
    this->_h0[4] = static_cast<T>( 0.6029490182363579) * klab::SQRT2;                        
    this->_h0[5] = static_cast<T>( 0.2668641184428723) * klab::SQRT2;
    this->_h0[6] = static_cast<T>(-0.07822326652898785) * klab::SQRT2;
    this->_h0[7] = static_cast<T>(-0.01686411844287495) * klab::SQRT2;
    this->_h0[8] = static_cast<T>( 0.02674875741080976) * klab::SQRT2;

    this->_h1[0]= klab::TTypeInfo<T>::ZERO;    
    this->_h1[1]= klab::TTypeInfo<T>::ZERO;    
    this->_h1[2]= static_cast<T>( 0.04563588155712474) * klab::SQRT2;    
    this->_h1[3]= static_cast<T>(-0.028771763114249785) * klab::SQRT2;    
    this->_h1[4]= static_cast<T>(-0.2956358815571235) * klab::SQRT2;    
    this->_h1[5]= static_cast<T>( 0.557543526228497) * klab::SQRT2;    
    this->_h1[6]= static_cast<T>(-0.2956358815571235) * klab::SQRT2;    
    this->_h1[7]= static_cast<T>(-0.028771763114249785) * klab::SQRT2;    
    this->_h1[8]= static_cast<T>( 0.04563588155712474) * klab::SQRT2; 

    this->_rh0[0] = -this->_h1[8];
    this->_rh0[1] =  this->_h1[7];
    this->_rh0[2] = -this->_h1[6];
    this->_rh0[3] =  this->_h1[5];
    this->_rh0[4] = -this->_h1[4];
    this->_rh0[5] =  this->_h1[3];
    this->_rh0[6] = -this->_h1[2];
    this->_rh0[7] =  this->_h1[1];
    this->_rh0[8] = -this->_h1[0];

    this->_rh1[0] =  this->_h0[8];
    this->_rh1[1] = -this->_h0[7];
    this->_rh1[2] =  this->_h0[6];
    this->_rh1[3] = -this->_h0[5];
    this->_rh1[4] =  this->_h0[4];
    this->_rh1[5] = -this->_h0[3];
    this->_rh1[6] =  this->_h0[2];
    this->_rh1[7] = -this->_h0[1];
    this->_rh1[8] =  this->_h0[0];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::TBiorthogonalDaubechiesWaveletFilter(const TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>& filter) : TBiorthogonalStaticWaveletFilter<T, 9, 7>(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::~TBiorthogonalDaubechiesWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>& TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::operator=(const TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>& filter)
{
    if(this != &filter)
        TBiorthogonalStaticWaveletFilter<T, 9, 7>::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->splitMatrixRows(inout, rows, cols);
    this->predict1MatrixRows(inout, rows, cols, true);
    this->update1MatrixRows(inout, rows, cols, true);
    this->predict2MatrixRows(inout, rows, cols, true);
    this->update2MatrixRows(inout, rows, cols, true);
    this->scaleMatrixRows(inout, rows, cols, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->splitMatrixColumns(inout, rows, cols);
    this->predict1MatrixColumns(inout, rows, cols, true);
    this->update1MatrixColumns(inout, rows, cols, true);
    this->predict2MatrixColumns(inout, rows, cols, true);
    this->update2MatrixColumns(inout, rows, cols, true);
    this->scaleMatrixColumns(inout, rows, cols, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->scaleMatrixRows(inout, rows, cols, false);
    this->update2MatrixRows(inout, rows, cols, false);
    this->predict2MatrixRows(inout, rows, cols, false);
    this->update1MatrixRows(inout, rows, cols, false);
    this->predict1MatrixRows(inout, rows, cols, false);
    this->mergeMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    this->scaleMatrixColumns(inout, rows, cols, false);
    this->update2MatrixColumns(inout, rows, cols, false);
    this->predict2MatrixColumns(inout, rows, cols, false);
    this->update1MatrixColumns(inout, rows, cols, false);
    this->predict1MatrixColumns(inout, rows, cols, false);
    this->mergeMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::predict1MatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T a = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ALPHA : -TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ALPHA);

        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {            
            inout(row, n-1) += static_cast<T>(2) * a * inout(row, half-1);
            for (klab::UInt32 i=0; i<half-1; ++i)
                inout(row, i+half) += a * (inout(row, i) + inout(row, i+1));
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::predict1MatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T a = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ALPHA : -TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ALPHA);

        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {      
            inout(m-1, col) += static_cast<T>(2) * a * inout(half-1, col);
            for (klab::UInt32 i=0; i<half-1; ++i)
                inout(i+half, col) += a * (inout(i, col) + inout(i+1, col));
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::update1MatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T b = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::BETA : -TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::BETA);

        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {   
            inout(row, 0) += static_cast<T>(2) * b * inout(row, half);
            for (klab::UInt32 i=1; i<half; ++i)
                inout(row, i) += b * (inout(row, i+half) + inout(row, i+half-1));
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::update1MatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T b = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::BETA : -TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::BETA);

        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {   
            inout(0, col) += static_cast<T>(2) * b * inout(half, col);
            for (klab::UInt32 i=1; i<half; ++i)
                inout(i, col) += b * (inout(i+half, col) + inout(i+half-1, col));
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::predict2MatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T c = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::GAMMA : -TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::GAMMA);

        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {            
            inout(row, n-1) += static_cast<T>(2) * c * inout(row, half-1);
            for (klab::UInt32 i=0; i<half-1; ++i)
                inout(row, i+half) += c * (inout(row, i) + inout(row, i+1));
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::predict2MatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T c = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::GAMMA : -TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::GAMMA);

        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {      
            inout(m-1, col) += static_cast<T>(2) * c * inout(half-1, col);
            for (klab::UInt32 i=0; i<half-1; ++i)
                inout(i+half, col) += c * (inout(i, col) + inout(i+1, col));
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::update2MatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T d = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::DELTA : -TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::DELTA);

        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {   
            inout(row, 0) += static_cast<T>(2) * d * inout(row, half);
            for (klab::UInt32 i=1; i<half; ++i)
                inout(row, i) += d * (inout(row, i+half) + inout(row, i+half-1));
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::update2MatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T d = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::DELTA : -TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::DELTA);

        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {   
            inout(0, col) += static_cast<T>(2) * d * inout(half, col);
            for (klab::UInt32 i=1; i<half; ++i)
                inout(i, col) += d * (inout(i+half, col) + inout(i+half-1, col));
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::scaleMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T z  = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ZETA : TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::INV_ZETA);
        T iz = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::INV_ZETA : TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ZETA);

        klab::UInt32 half = n>>1;
        for(klab::UInt32 row=0; row<m; ++row)
        {   
            for (klab::UInt32 i=0; i<half; ++i)
            {
                inout(row, i)      *= z;
                inout(row, i+half) *= iz;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::scaleMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols, bool forward)
{
    klab::UInt32 m = klab::Min(rows, inout.n_rows);
    klab::UInt32 n = klab::Min(cols, inout.n_cols);

    if(m>0 && n>0)
    {
        T z  = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ZETA : TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::INV_ZETA);
        T iz = (forward ? TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::INV_ZETA : TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>::ZETA);

        klab::UInt32 half = m>>1;
        for(klab::UInt32 col=0; col<n; ++col)
        {   
            for (klab::UInt32 i=0; i<half; ++i)
            {
                inout(i, col)      *= z;
                inout(i+half, col) *= iz;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
