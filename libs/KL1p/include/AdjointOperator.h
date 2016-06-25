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

#ifndef KL1P_ADJOINTOPERATOR_H
#define KL1P_ADJOINTOPERATOR_H

#include "ProxyOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TAdjointOperator : public TProxyOperator<T, TOut, TOp>
{
public:
    
    TAdjointOperator(klab::TSmartPointer<TOp> op);
    TAdjointOperator(const TAdjointOperator<T, TOut, TOp>& op);
    virtual ~TAdjointOperator();

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

    TAdjointOperator();
    TAdjointOperator<T, TOut, TOp>& operator=(const TAdjointOperator<T, TOut, TOp>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TAdjointOperator<T, TOut, TOp>::TAdjointOperator(klab::TSmartPointer<TOp> op) : TProxyOperator<T, TOut, TOp>(op!=0?op->n():0, op!=0?op->m():0, op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TAdjointOperator<T, TOut, TOp>::TAdjointOperator(const TAdjointOperator<T, TOut, TOp>& op) : TProxyOperator<T, TOut, TOp>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TAdjointOperator<T, TOut, TOp>::~TAdjointOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TAdjointOperator<T, TOut, TOp>::sum()
{
    return (this->_op!=0 ? klab::Conj(this->_op->sum()) : klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TAdjointOperator<T, TOut, TOp>::normFrobenius()
{
    return (this->_op!=0 ? this->_op->normFrobenius() : klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TAdjointOperator<T, TOut, TOp>::squaredNormFrobenius()
{
    return (this->_op!=0 ? this->_op->squaredNormFrobenius() : klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TAdjointOperator<T, TOut, TOp>::mean()
{
    return (this->_op!=0 ? klab::Conj(this->_op->mean()) : klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TAdjointOperator<T, TOut, TOp>::variance()
{
    T ret = klab::TTypeInfo<T>::ZERO;

    if(this->_op != 0)
    {
        klab::UInt32 mn = this->m() * this->n();
        if(mn > 0)
        {
            T mean = this->_op->mean();
            ret = (this->_op->squaredNormFrobenius()/static_cast<T>(mn)) - (mean*klab::Conj(mean));
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TAdjointOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());   

    this->_op->applyAdjoint(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TAdjointOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());   

    this->_op->apply(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TAdjointOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());
    
    this->_op->columnAdjoint(i, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TAdjointOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());
    
    this->_op->column(i, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
