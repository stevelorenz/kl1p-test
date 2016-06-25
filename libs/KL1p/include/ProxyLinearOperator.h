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

#ifndef KL1P_PROXYLINEAROPERATOR_H
#define KL1P_PROXYLINEAROPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOp=TOperator<T, T> >
class TProxyLinearOperator : public klab::TLinearOperator<T, TProxyLinearOperator<T, TOp> >
{
public:

    TProxyLinearOperator(klab::TSmartPointer<TOp> op);
    TProxyLinearOperator(const TProxyLinearOperator<T, TOp>& op);
    virtual ~TProxyLinearOperator();

    TProxyLinearOperator<T, TOp>&   operator=(const TProxyLinearOperator<T, TOp>& op);

    void                        apply(const arma::Col<T>& in, arma::Col<T>& out) const;
    void                        applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) const;


private:

    klab::TSmartPointer<TOp>    _op;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOp>
inline TProxyLinearOperator<T, TOp>::TProxyLinearOperator(klab::TSmartPointer<TOp> op) : klab::TLinearOperator<T, TProxyLinearOperator<T, TOp> >(op!=0?op->m():0, op!=0?op->n():0),
_op(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOp>
inline TProxyLinearOperator<T, TOp>::TProxyLinearOperator(const TProxyLinearOperator<T, TOp>& op) : klab::TLinearOperator<T, TProxyLinearOperator<T, TOp> >(op),
_op(op._op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOp>
inline TProxyLinearOperator<T, TOp>::~TProxyLinearOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOp>
inline TProxyLinearOperator<T, TOp>& TProxyLinearOperator<T, TOp>::operator=(const TProxyLinearOperator<T, TOp>& op)
{
    if(this != &op)
    {
        klab::TLinearOperator<T, TProxyLinearOperator<T, TOp> >::operator=(op);

        _op = op._op;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOp>
inline void TProxyLinearOperator<T, TOp>::apply(const arma::Col<T>& in, arma::Col<T>& out) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows != this->n());

    _op->apply(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOp>
inline void TProxyLinearOperator<T, TOp>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows != this->m());

    _op->applyAdjoint(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
