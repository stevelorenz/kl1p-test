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

#ifndef KL1P_DIAGONALOPERATOR_H
#define KL1P_DIAGONALOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDiagonalOperator : public TOperator<T>
{
public:
        
    TDiagonalOperator(const arma::Col<T>& diag);
    TDiagonalOperator(const TDiagonalOperator<T>& op);
    virtual ~TDiagonalOperator();    

    const arma::Col<T>&         diagonal() const;         

    virtual void                apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void                applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);

    virtual void                column(klab::UInt32 i, arma::Col<T>& out);
    virtual void                columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


protected:

    TDiagonalOperator();

    void                        setDiagonal(const arma::Col<T>& diag);


private:

    TDiagonalOperator<T>&       operator=(const TDiagonalOperator<T>& op);


private:

    arma::Col<T>                _diagonal;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDiagonalOperator<T>::TDiagonalOperator() : TOperator<T>(),
_diagonal()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDiagonalOperator<T>::TDiagonalOperator(const arma::Col<T>& diag) : TOperator<T>(diag.n_rows),
_diagonal(diag)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDiagonalOperator<T>::TDiagonalOperator(const TDiagonalOperator<T>& op) : TOperator<T>(op),
_diagonal(op._diagonal)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDiagonalOperator<T>::~TDiagonalOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDiagonalOperator<T>::setDiagonal(const arma::Col<T>& diag)
{
    _diagonal = diag;

    this->resize(diag.n_rows, diag.n_rows);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const arma::Col<T>& TDiagonalOperator<T>::diagonal() const
{
    return _diagonal;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDiagonalOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());

    out.set_size(this->m());
    for(klab::UInt32 i=0; i<out.n_rows; ++i)
        out[i] = (_diagonal[i] * in[i]);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDiagonalOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    out.set_size(this->n());
    for(klab::UInt32 i=0; i<out.n_rows; ++i)
        out[i] = (klab::Conj(_diagonal[i]) * in[i]);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDiagonalOperator<T>::column(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<T>::ZERO);

    out[i] = _diagonal[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDiagonalOperator<T>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<T>::ZERO);

    out[i] = klab::Conj(_diagonal[i]);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
