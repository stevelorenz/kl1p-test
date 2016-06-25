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

#ifndef KL1P_GAUSSIAN1DDIAGONALOPERATOR_H
#define KL1P_GAUSSIAN1DDIAGONALOPERATOR_H

#include "DiagonalOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGaussian1DDiagonalOperator : public TDiagonalOperator<T> 
{
public:

    TGaussian1DDiagonalOperator(klab::UInt32 n);
    TGaussian1DDiagonalOperator(klab::UInt32 n, const T& sigma);
    TGaussian1DDiagonalOperator(klab::UInt32 n, const T& sigma, klab::Int32 c);
    TGaussian1DDiagonalOperator(const TGaussian1DDiagonalOperator<T>& op);
    virtual ~TGaussian1DDiagonalOperator();    

    const T&                sigma() const;
    klab::Int32      c() const;


private:

    TGaussian1DDiagonalOperator();
    TGaussian1DDiagonalOperator<T>& operator=(const TGaussian1DDiagonalOperator<T>& op);


private:

    klab::TGaussianFilter1D<T>  _filter;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian1DDiagonalOperator<T>::TGaussian1DDiagonalOperator(klab::UInt32 n) : TDiagonalOperator<T>(),
_filter(n)
{
    arma::Col<T> in(n);
    in.fill(klab::TTypeInfo<T>::UNIT);

    arma::Col<T> diag;
    _filter.apply(in, diag);

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian1DDiagonalOperator<T>::TGaussian1DDiagonalOperator(klab::UInt32 n, const T& sigma) : TDiagonalOperator<T>(),
_filter(n, sigma)
{
    arma::Col<T> in(n);
    in.fill(klab::TTypeInfo<T>::UNIT);

    arma::Col<T> diag;
    _filter.apply(in, diag);

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian1DDiagonalOperator<T>::TGaussian1DDiagonalOperator(klab::UInt32 n, const T& sigma, klab::Int32 c) : TDiagonalOperator<T>(),
_filter(n, sigma, c)
{
    arma::Col<T> in(n);
    in.fill(klab::TTypeInfo<T>::UNIT);

    arma::Col<T> diag;
    _filter.apply(in, diag);

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian1DDiagonalOperator<T>::TGaussian1DDiagonalOperator(const TGaussian1DDiagonalOperator<T>& op) : TDiagonalOperator<T>(op),
_filter(op._filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussian1DDiagonalOperator<T>::~TGaussian1DDiagonalOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TGaussian1DDiagonalOperator<T>::sigma() const
{
    return _filter.sigma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussian1DDiagonalOperator<T>::c() const
{
    return _filter.c();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
