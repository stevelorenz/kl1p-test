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

#ifndef KL1P_DCT1DOPERATOR_H
#define KL1P_DCT1DOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDCT1DOperator : public TOperator<T, T>
{
public:
    
    TDCT1DOperator(klab::UInt32 n);
    TDCT1DOperator(const TDCT1DOperator<T>& op);
    virtual ~TDCT1DOperator();    

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TDCT1DOperator();
    TDCT1DOperator<T>&      operator=(const TDCT1DOperator<T>& op);


private:

    klab::TFCT1D<T>         _fct;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT1DOperator<T>::TDCT1DOperator(klab::UInt32 n) : TOperator<T, T>(n),
_fct()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT1DOperator<T>::TDCT1DOperator(const TDCT1DOperator<T>& op) : TOperator<T, T>(op),
_fct(op._fct)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT1DOperator<T>::~TDCT1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT1DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());    

    _fct.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT1DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());    

    _fct.invert(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
