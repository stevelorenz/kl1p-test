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

#ifndef KL1P_IDENTITYOPERATOR_H
#define KL1P_IDENTITYOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TIdentityOperator : public TOperator<T>
{
public:
 
    TIdentityOperator(klab::UInt32 n);
    TIdentityOperator(const TIdentityOperator<T>& op);
    virtual ~TIdentityOperator();    

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);

    virtual void            column(klab::UInt32 i, arma::Col<T>& out);
    virtual void            columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TIdentityOperator();
    TIdentityOperator<T>&   operator=(const TIdentityOperator<T>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TIdentityOperator<T>::TIdentityOperator(klab::UInt32 n) : TOperator<T>(n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TIdentityOperator<T>::TIdentityOperator(const TIdentityOperator<T>& op) : TOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TIdentityOperator<T>::~TIdentityOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TIdentityOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());

    out = in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TIdentityOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    out = in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TIdentityOperator<T>::column(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<T>::ZERO);

    out[i] = klab::TTypeInfo<T>::UNIT;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TIdentityOperator<T>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<T>::ZERO);

    out[i] = klab::TTypeInfo<T>::UNIT;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
