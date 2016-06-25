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

#ifndef KLAB_MATRIXLINEAROPERATOR_H
#define KLAB_MATRIXLINEAROPERATOR_H

#include "LinearOperator.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TMatrixLinearOperator : public TLinearOperator<T, TMatrixLinearOperator<T> >
{
public:

    TMatrixLinearOperator(const arma::Mat<T>& matrix);
    TMatrixLinearOperator(const TMatrixLinearOperator<T>& op);
    virtual ~TMatrixLinearOperator();

    TMatrixLinearOperator<T>&	operator=(const TMatrixLinearOperator<T>& op);

    void	apply(const arma::Col<T>& in, arma::Col<T>& out) const;
	void	applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) const;


private:

    TMatrixLinearOperator();


private:

    const arma::Mat<T>&		_matrix;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixLinearOperator<T>::TMatrixLinearOperator(const arma::Mat<T>& matrix) : TLinearOperator<T, TMatrixLinearOperator<T> >(matrix.n_rows, matrix.n_cols),
_matrix(matrix)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixLinearOperator<T>::TMatrixLinearOperator(const TMatrixLinearOperator<T>& op) : TLinearOperator<T, TMatrixLinearOperator<T> >(op),
_matrix(op._matrix)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixLinearOperator<T>::~TMatrixLinearOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixLinearOperator<T>& TMatrixLinearOperator<T>::operator=(const TMatrixLinearOperator<T>& op)
{
    if(this != &op)
    {
        TLinearOperator<T, TMatrixLinearOperator<T> >::operator=(op);

        _matrix = op._matrix;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TMatrixLinearOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out) const
{
    ThrowTraceExceptionIf(KIncompatibleSizeLinearOperatorException, in.n_rows != this->n());

    out = _matrix * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TMatrixLinearOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) const
{
    ThrowTraceExceptionIf(KIncompatibleSizeLinearOperatorException, in.n_rows != this->m());

    out = arma::trans(_matrix) * in;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
