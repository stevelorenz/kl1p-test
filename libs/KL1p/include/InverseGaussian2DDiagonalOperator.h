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

#ifndef KL1P_INVERSEGAUSSIAN2DDIAGONALOPERATOR_H
#define KL1P_INVERSEGAUSSIAN2DDIAGONALOPERATOR_H

#include "DiagonalOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseGaussian2DDiagonalOperator : public TDiagonalOperator<T>   
{
public:

    TInverseGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width);
    TInverseGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma);
    TInverseGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma, const T& sigma);
    TInverseGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma, const T& sigma, klab::Int32 ic, klab::Int32 jc);
    TInverseGaussian2DDiagonalOperator(const TInverseGaussian2DDiagonalOperator<T>& op);
    virtual ~TInverseGaussian2DDiagonalOperator();    

    klab::UInt32            width() const;
    klab::UInt32            height() const;
    const T&                gamma() const;
    const T&                sigma() const;
    klab::Int32      ic() const;
    klab::Int32      jc() const;


private:

    TInverseGaussian2DDiagonalOperator();
    TInverseGaussian2DDiagonalOperator<T>&  operator=(const TInverseGaussian2DDiagonalOperator<T>& op);


private:

    klab::TGaussWienerFilter2D<T>   _filter;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussian2DDiagonalOperator<T>::TInverseGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width) : TDiagonalOperator<T>(),
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
inline TInverseGaussian2DDiagonalOperator<T>::TInverseGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma) : TDiagonalOperator<T>(),
_filter(height, width, gamma)
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
inline TInverseGaussian2DDiagonalOperator<T>::TInverseGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma, const T& sigma) : TDiagonalOperator<T>(),
_filter(height, width, gamma, sigma)
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
inline TInverseGaussian2DDiagonalOperator<T>::TInverseGaussian2DDiagonalOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma, const T& sigma, klab::Int32 ic, klab::Int32 jc) : TDiagonalOperator<T>(),
_filter(height, width, gamma, sigma, ic, jc)
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
inline TInverseGaussian2DDiagonalOperator<T>::TInverseGaussian2DDiagonalOperator(const TInverseGaussian2DDiagonalOperator<T>& op) : TDiagonalOperator<T>(op),
_filter(op._filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussian2DDiagonalOperator<T>::~TInverseGaussian2DDiagonalOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseGaussian2DDiagonalOperator<T>::width() const
{
    return _filter.n();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseGaussian2DDiagonalOperator<T>::height() const
{
    return _filter.m();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TInverseGaussian2DDiagonalOperator<T>::gamma() const
{
    return _filter.gamma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TInverseGaussian2DDiagonalOperator<T>::sigma() const
{
    return _filter.sigma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TInverseGaussian2DDiagonalOperator<T>::ic() const
{
    return _filter.ic();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TInverseGaussian2DDiagonalOperator<T>::jc() const
{
    return _filter.jc();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
