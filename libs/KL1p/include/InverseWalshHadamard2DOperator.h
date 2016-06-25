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

#ifndef KL1P_INVERSEWALSHHADAMARD2DOPERATOR_H
#define KL1P_INVERSEWALSHHADAMARD2DOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseWalshHadamard2DOperator : public TOperator<T, T>
{
public:

    TInverseWalshHadamard2DOperator(klab::UInt32 height, klab::UInt32 width);
    TInverseWalshHadamard2DOperator(const TInverseWalshHadamard2DOperator<T>& op);
    virtual ~TInverseWalshHadamard2DOperator();    

    klab::UInt32     width() const;
    klab::UInt32     height() const;

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TInverseWalshHadamard2DOperator();
    TInverseWalshHadamard2DOperator<T>&  operator=(const TInverseWalshHadamard2DOperator<T>& op);


private:

    klab::UInt32            _height;
    klab::UInt32            _width;

    klab::TFWHT2D<T>        _fwht;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseWalshHadamard2DOperator<T>::TInverseWalshHadamard2DOperator(klab::UInt32 height, klab::UInt32 width) : TOperator<T, T>(width*height),
_height(height), _width(width),
_fwht()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseWalshHadamard2DOperator<T>::TInverseWalshHadamard2DOperator(const TInverseWalshHadamard2DOperator<T>& op) : TOperator<T, T>(op),
_height(op._height), _width(op._width),
_fwht(op._fwht)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseWalshHadamard2DOperator<T>::~TInverseWalshHadamard2DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseWalshHadamard2DOperator<T>::width() const
{
    return _width;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseWalshHadamard2DOperator<T>::height() const
{
    return _height;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseWalshHadamard2DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());

    arma::Mat<T> inMatrix(in);
    arma::Mat<T> outMatrix;
    inMatrix.reshape(_height, _width);

    _fwht.invert(inMatrix, outMatrix);

    outMatrix.reshape(this->m(), 1);
    out = outMatrix;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseWalshHadamard2DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    arma::Mat<T> inMatrix(in);
    arma::Mat<T> outMatrix;
    inMatrix.reshape(_height, _width);

    _fwht.invert(inMatrix, outMatrix);

    outMatrix.reshape(this->n(), 1);
    out = outMatrix;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
