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

#ifndef KL1P_INVERSEGAUSSIAN1DDIAGONALOPERATOR_H
#define KL1P_INVERSEGAUSSIAN1DDIAGONALOPERATOR_H

#include "DiagonalOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseGaussian1DDiagonalOperator : public TDiagonalOperator<T>   
{
public:

    TInverseGaussian1DDiagonalOperator(klab::UInt32 n);
    TInverseGaussian1DDiagonalOperator(klab::UInt32 n, const T& gamma);
    TInverseGaussian1DDiagonalOperator(klab::UInt32 n, const T& gamma, const T& sigma);
    TInverseGaussian1DDiagonalOperator(klab::UInt32 n, const T& gamma, const T& sigma, klab::Int32 c);
    TInverseGaussian1DDiagonalOperator(const TInverseGaussian1DDiagonalOperator<T>& op);
    virtual ~TInverseGaussian1DDiagonalOperator();    

    const T&                gamma() const;
    const T&                sigma() const;
    klab::Int32      c() const;


private:

    TInverseGaussian1DDiagonalOperator();
    TInverseGaussian1DDiagonalOperator<T>&  operator=(const TInverseGaussian1DDiagonalOperator<T>& op);


private:

    klab::TGaussWienerFilter1D<T>   _filter;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussian1DDiagonalOperator<T>::TInverseGaussian1DDiagonalOperator(klab::UInt32 n) : TDiagonalOperator<T>(),
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
inline TInverseGaussian1DDiagonalOperator<T>::TInverseGaussian1DDiagonalOperator(klab::UInt32 n, const T& gamma) : TDiagonalOperator<T>(),
_filter(n, gamma)
{
    arma::Col<T> in(n);
    in.fill(klab::TTypeInfo<T>::UNIT);

    arma::Col<T> diag;
    _filter.apply(in, diag);

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussian1DDiagonalOperator<T>::TInverseGaussian1DDiagonalOperator(klab::UInt32 n, const T& gamma, const T& sigma) : TDiagonalOperator<T>(),
_filter(n, gamma, sigma)
{
    arma::Col<T> in(n);
    in.fill(klab::TTypeInfo<T>::UNIT);

    arma::Col<T> diag;
    _filter.apply(in, diag);

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussian1DDiagonalOperator<T>::TInverseGaussian1DDiagonalOperator(klab::UInt32 n, const T& gamma, const T& sigma, klab::Int32 c) : TDiagonalOperator<T>(),
_filter(n, gamma, sigma, c)
{
    arma::Col<T> in(n);
    in.fill(klab::TTypeInfo<T>::UNIT);

    arma::Col<T> diag;
    _filter.apply(in, diag);

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussian1DDiagonalOperator<T>::TInverseGaussian1DDiagonalOperator(const TInverseGaussian1DDiagonalOperator<T>& op) : TDiagonalOperator<T>(op),
_filter(op._filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussian1DDiagonalOperator<T>::~TInverseGaussian1DDiagonalOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TInverseGaussian1DDiagonalOperator<T>::gamma() const
{
    return _filter.gamma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TInverseGaussian1DDiagonalOperator<T>::sigma() const
{
    return _filter.sigma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TInverseGaussian1DDiagonalOperator<T>::c() const
{
    return _filter.c();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
