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

#ifndef KL1P_NORMALIZATIONOPERATOR_H
#define KL1P_NORMALIZATIONOPERATOR_H

#include "ScalingOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TNormalizationOperator : public TScalingOperator<T, TOut, TOp>
{
public:

    TNormalizationOperator(klab::TSmartPointer<TOp> op);
    TNormalizationOperator(klab::TSmartPointer<TOp> op, const T& scale);
    TNormalizationOperator(const TNormalizationOperator<T, TOut, TOp>& op);
    virtual ~TNormalizationOperator();

    virtual void            setScale(const T& scale);


private:

    TNormalizationOperator();
    TNormalizationOperator<T, TOut, TOp>&   operator=(const TNormalizationOperator<T, TOut, TOp>& op);


private:

    T                       _normFactor;
    T                       _normScale;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TNormalizationOperator<T, TOut, TOp>::TNormalizationOperator(klab::TSmartPointer<TOp> op) : TScalingOperator<T, TOut, TOp>(op),
_normFactor(klab::TTypeInfo<T>::UNIT), _normScale(klab::TTypeInfo<T>::UNIT)
{
    ThrowTraceExceptionIf(KNullOperatorException, op==0);
    T norm = op->normFrobenius();
    ThrowTraceExceptionIf(KZeroNormOperatorException, norm==klab::TTypeInfo<T>::ZERO);

    _normFactor = klab::TTypeInfo<T>::UNIT / norm;
    TScalingOperator<T, TOut, TOp>::setScale(_normFactor*_normScale);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TNormalizationOperator<T, TOut, TOp>::TNormalizationOperator(klab::TSmartPointer<TOp> op, const T& scale) : TScalingOperator<T, TOut, TOp>(op, scale),
_normFactor(klab::TTypeInfo<T>::UNIT), _normScale(scale)
{
    ThrowTraceExceptionIf(KNullOperatorException, op==0);
    T norm = op->normFrobenius();
    ThrowTraceExceptionIf(KZeroNormOperatorException, norm==klab::TTypeInfo<T>::ZERO);

    _normFactor = klab::TTypeInfo<T>::UNIT / norm;
    TScalingOperator<T, TOut, TOp>::setScale(_normFactor*_normScale);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TNormalizationOperator<T, TOut, TOp>::TNormalizationOperator(const TNormalizationOperator<T, TOut, TOp>& op) : TScalingOperator<T, TOut, TOp>(op),
_normFactor(op._normFactor), _normScale(op._normScale)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TNormalizationOperator<T, TOut, TOp>::~TNormalizationOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TNormalizationOperator<T, TOut, TOp>::setScale(const T& scale)
{
    _normScale = scale;

    TScalingOperator<T, TOut, TOp>::setScale(_normFactor*_normScale);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
