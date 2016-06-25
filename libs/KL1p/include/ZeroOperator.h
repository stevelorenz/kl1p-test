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

#ifndef KL1P_ZEROOPERATOR_H
#define KL1P_ZEROOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TZeroOperator : public TOperator<T>
{
public:
 
    TZeroOperator(klab::UInt32 m, klab::UInt32 n);
    TZeroOperator(const TZeroOperator<T>& op);
    virtual ~TZeroOperator();    

    virtual bool    isZero();
    virtual T       sum();
    virtual T       normFrobenius();
    virtual T       squaredNormFrobenius();
    virtual T       mean();
    virtual T       variance();

    virtual void    apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void    applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);

    virtual void    column(klab::UInt32 i, arma::Col<T>& out);
    virtual void    columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TZeroOperator();
    TZeroOperator<T>&       operator=(const TZeroOperator<T>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TZeroOperator<T>::TZeroOperator(klab::UInt32 m, klab::UInt32 n) : TOperator<T>(m, n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TZeroOperator<T>::TZeroOperator(const TZeroOperator<T>& op) : TOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TZeroOperator<T>::~TZeroOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TZeroOperator<T>::isZero()
{
    return true;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TZeroOperator<T>::sum()
{
    return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TZeroOperator<T>::normFrobenius()
{
    return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TZeroOperator<T>::squaredNormFrobenius()
{
    return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TZeroOperator<T>::mean()
{
    return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TZeroOperator<T>::variance()
{
    return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TZeroOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TZeroOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TZeroOperator<T>::column(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TZeroOperator<T>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
