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

#ifndef KL1P_SCALAROPERATOR_H
#define KL1P_SCALAROPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TScalarOperator : public TOperator<T>
{
public:

    TScalarOperator(klab::UInt32 n);
    TScalarOperator(klab::UInt32 n, const T& value);
    TScalarOperator(const TScalarOperator<T>& op);
    virtual ~TScalarOperator();    

    const T&                value() const;         

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);

    virtual void            column(klab::UInt32 i, arma::Col<T>& out);
    virtual void            columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TScalarOperator();
    TScalarOperator<T>&     operator=(const TScalarOperator<T>& op);


private:

    T                       _value;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TScalarOperator<T>::TScalarOperator(klab::UInt32 n) : TOperator<T>(n),
_value(klab::TTypeInfo<T>::UNIT)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TScalarOperator<T>::TScalarOperator(klab::UInt32 n, const T& value) : TOperator<T>(n),
_value(value)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TScalarOperator<T>::TScalarOperator(const TScalarOperator<T>& op) : TOperator<T>(op),
_value(op._value)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TScalarOperator<T>::~TScalarOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TScalarOperator<T>::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TScalarOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());

    out.set_size(this->m());
    if(_value == klab::TTypeInfo<T>::ZERO)
    {        
        out.fill(klab::TTypeInfo<T>::ZERO);
    }
    else if(_value == klab::TTypeInfo<T>::UNIT)
    {
        out = in;
    }
    else
    {
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] = (_value * in[i]);   
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TScalarOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    out.set_size(this->n());
    if(_value == klab::TTypeInfo<T>::ZERO)
    {        
        out.fill(klab::TTypeInfo<T>::ZERO);
    }
    else if(_value == klab::TTypeInfo<T>::UNIT)
    {
        out = in;
    }
    else
    {
        T conj = klab::Conj(_value);
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] = (conj * in[i]);        
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TScalarOperator<T>::column(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<T>::ZERO);

    out[i] = _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TScalarOperator<T>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<T>::ZERO);

    out[i] = klab::Conj(_value);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
