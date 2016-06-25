// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KL1p C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KL1P_GAUSSIAN2DDIAGONALOPERATOR_H
#define KL1P_GAUSSIAN2DDIAGONALOPERATOR_H

#include "DiagonalOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGaussian2DDiagonalOperator : public TDiagonalOperator<T>  
{
public:

    TGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width);
    TGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& sigma);
    TGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& sigma, klab::Int32 ic, klab::Int32 jc);
    TGaussian2DDiagonalOperator(const TGaussian2DDiagonalOperator<T>& op);
    virtual ~TGaussian2DDiagonalOperator();    

    klab::UInt32            width() const;
    klab::UInt32            height() const;
    const T&                sigma() const;
    klab::Int32      ic() const;
    klab::Int32      jc() const;


private:

    TGaussian2DDiagonalOperator();
    TGaussian2DDiagonalOperator<T>& operator=(const TGaussian2DDiagonalOperator<T>& op);


private:

    klab::TGaussianFilter2D<T>  _filter;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian2DDiagonalOperator<T>::TGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width) : TDiagonalOperator<T>(),
_filter(height, width)
{
    arma::Mat<T> in(height, width);
    in.fill(klab::TTypeInfo<T>::UNIT);

    arma::Mat<T> diag;
    _filter.apply(in, diag); 
    diag.reshape(width*height, 1);

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian2DDiagonalOperator<T>::TGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& sigma) : TDiagonalOperator<T>(),
_filter(height, width, sigma)
{
    arma::Mat<T> in(height, width);
    in.fill(klab::TTypeInfo<T>::UNIT);

    arma::Mat<T> diag;
    _filter.apply(in, diag); 
    diag.reshape(width*height, 1);

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian2DDiagonalOperator<T>::TGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& sigma, klab::Int32 ic, klab::Int32 jc) : TDiagonalOperator<T>(),
_filter(height, width, sigma, ic, jc)
{
    arma::Mat<T> in(height, width);
    in.fill(klab::TTypeInfo<T>::UNIT);

    arma::Mat<T> diag;
    _filter.apply(in, diag); 
    diag.reshape(width*height, 1);

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian2DDiagonalOperator<T>::TGaussian2DDiagonalOperator(const TGaussian2DDiagonalOperator<T>& op) : TDiagonalOperator<T>(op),
_filter(op._filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian2DDiagonalOperator<T>::~TGaussian2DDiagonalOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGaussian2DDiagonalOperator<T>::width() const
{
    return _filter.n();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGaussian2DDiagonalOperator<T>::height() const
{
    return _filter.m();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TGaussian2DDiagonalOperator<T>::sigma() const
{
    return _filter.sigma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussian2DDiagonalOperator<T>::ic() const
{
    return _filter.ic();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussian2DDiagonalOperator<T>::jc() const
{
    return _filter.jc();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
