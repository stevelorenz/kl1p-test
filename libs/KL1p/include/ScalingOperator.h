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

#ifndef KL1P_SCALINGOPERATOR_H
#define KL1P_SCALINGOPERATOR_H

#include "ProxyOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TScalingOperator : public TProxyOperator<T, TOut, TOp>
{
public:
  
    TScalingOperator(klab::TSmartPointer<TOp> op);
    TScalingOperator(klab::TSmartPointer<TOp> op, const T& scale);
    TScalingOperator(const TScalingOperator<T, TOut, TOp>& op);
    virtual ~TScalingOperator();    

    virtual void                setScale(const T& scale);
    const T&                    scale() const;  

    virtual void                apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void                applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);

    virtual void                column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void                columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TScalingOperator();
    TScalingOperator<T, TOut, TOp>& operator=(const TScalingOperator<T, TOut, TOp>& op);


private:

    T                                   _scale;
    T                                   _conjScale;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TScalingOperator<T, TOut, TOp>::TScalingOperator(klab::TSmartPointer<TOp> op) : TProxyOperator<T, TOut, TOp>(op),
_scale(klab::TTypeInfo<T>::UNIT), _conjScale(klab::Conj(_scale))
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TScalingOperator<T, TOut, TOp>::TScalingOperator(klab::TSmartPointer<TOp> op, const T& scale) : TProxyOperator<T, TOut, TOp>(op),
_scale(scale), _conjScale(klab::Conj(_scale))
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TScalingOperator<T, TOut, TOp>::TScalingOperator(const TScalingOperator<T, TOut, TOp>& op) : TProxyOperator<T, TOut, TOp>(op),
_scale(op._scale), _conjScale(op._conjScale)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TScalingOperator<T, TOut, TOp>::~TScalingOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TScalingOperator<T, TOut, TOp>::setScale(const T& scale)
{
    _scale = scale;
    _conjScale = klab::Conj(_scale);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline const T& TScalingOperator<T, TOut, TOp>::scale() const
{
    return _scale;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TScalingOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());  

    this->_op->apply(in, out);

    if(_scale == klab::TTypeInfo<T>::ZERO)  
    {
        out.fill(klab::TTypeInfo<TOut>::ZERO);
    }
    else if(_scale != klab::TTypeInfo<T>::UNIT)
    {
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] *= static_cast<TOut>(_scale);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TScalingOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());  

    this->_op->applyAdjoint(in, out);

    if(_conjScale == klab::TTypeInfo<T>::ZERO)  
    {
        out.fill(klab::TTypeInfo<T>::ZERO);
    }
    else if(_conjScale != klab::TTypeInfo<T>::UNIT)
    {
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] *= _conjScale;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TScalingOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    this->_op->column(i, out);

    if(_scale == klab::TTypeInfo<T>::ZERO)  
    {
        out.fill(klab::TTypeInfo<TOut>::ZERO);
    }
    else if(_scale != klab::TTypeInfo<T>::UNIT)
    {
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] *= static_cast<TOut>(_scale);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TScalingOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    this->_op->columnAdjoint(i, out);

    if(_conjScale == klab::TTypeInfo<T>::ZERO)  
    {
        out.fill(klab::TTypeInfo<T>::ZERO);
    }
    else if(_conjScale != klab::TTypeInfo<T>::UNIT)
    {
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] *= _conjScale;
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
