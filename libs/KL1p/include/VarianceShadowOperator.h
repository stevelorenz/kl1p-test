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

#ifndef KL1P_VARIANCESHADOWOPERATOR_H
#define KL1P_VARIANCESHADOWOPERATOR_H

#include "ProxyOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TVarianceShadowOperator : public TProxyOperator<T, TOut, TOp>
{
public:
    
    TVarianceShadowOperator(klab::TSmartPointer<TOp> op);
    TVarianceShadowOperator(klab::TSmartPointer<TOp> op, const T& variance);
    TVarianceShadowOperator(klab::TSmartPointer<TOp> op, const T& variance, const T& mean);
    TVarianceShadowOperator(const TVarianceShadowOperator<T, TOut, TOp>& op);
    virtual ~TVarianceShadowOperator();

    virtual T       sum();
    virtual T       normFrobenius();
    virtual T       squaredNormFrobenius();
    virtual T       mean();
    virtual T       variance();

    virtual void    apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void    applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);
    virtual void    column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void    columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TVarianceShadowOperator();
    TVarianceShadowOperator<T, TOut, TOp>&  operator=(const TVarianceShadowOperator<T, TOut, TOp>& op);


private:

    T               _mean;
    T               _variance;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TVarianceShadowOperator<T, TOut, TOp>::TVarianceShadowOperator(klab::TSmartPointer<TOp> op) : TProxyOperator<T, TOut, TOp>(op!=0?op->m():0, op!=0?op->n():0, op),
_mean(op!=0?op->mean():klab::TTypeInfo<T>::ZERO), _variance(op!=0?op->variance():klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TVarianceShadowOperator<T, TOut, TOp>::TVarianceShadowOperator(klab::TSmartPointer<TOp> op, const T& variance) : TProxyOperator<T, TOut, TOp>(op!=0?op->m():0, op!=0?op->n():0, op),
_mean(op!=0?op->mean():klab::TTypeInfo<T>::ZERO), _variance(variance)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TVarianceShadowOperator<T, TOut, TOp>::TVarianceShadowOperator(klab::TSmartPointer<TOp> op, const T& variance, const T& mean) : TProxyOperator<T, TOut, TOp>(op!=0?op->m():0, op!=0?op->n():0, op),
_mean(mean), _variance(variance)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TVarianceShadowOperator<T, TOut, TOp>::TVarianceShadowOperator(const TVarianceShadowOperator<T, TOut, TOp>& op) : TProxyOperator<T, TOut, TOp>(op),
_mean(op._mean), _variance(op._variance)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TVarianceShadowOperator<T, TOut, TOp>::~TVarianceShadowOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TVarianceShadowOperator<T, TOut, TOp>::sum()
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 mn = this->m() * this->n();
    if(mn > 0)
        ret = _mean * static_cast<T>(mn);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TVarianceShadowOperator<T, TOut, TOp>::normFrobenius()
{
    return klab::Sqrt(this->squaredNormFrobenius());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TVarianceShadowOperator<T, TOut, TOp>::squaredNormFrobenius()
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 mn = this->m() * this->n();
    if(mn > 0)
        ret = (this->variance() + (klab::Conj(_mean)*_mean)) * static_cast<T>(mn);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TVarianceShadowOperator<T, TOut, TOp>::mean()
{
    return _mean;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TVarianceShadowOperator<T, TOut, TOp>::variance()
{
    return _variance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TVarianceShadowOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());   

    this->_op->apply(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TVarianceShadowOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());   

    this->_op->applyAdjoint(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TVarianceShadowOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());
    
    this->_op->column(i, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TVarianceShadowOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());
    
    this->_op->columnAdjoint(i, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
