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

#ifndef KL1P_WALSHHADAMARD1DOPERATOR_H
#define KL1P_WALSHHADAMARD1DOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TWalshHadamard1DOperator : public TOperator<T, T>
{
public:

    TWalshHadamard1DOperator(klab::UInt32 n);
    TWalshHadamard1DOperator(const TWalshHadamard1DOperator<T>& op);
    virtual ~TWalshHadamard1DOperator();    

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TWalshHadamard1DOperator();
    TWalshHadamard1DOperator<T>&  operator=(const TWalshHadamard1DOperator<T>& op);


private:

    klab::TFWHT1D<T>        _fwht;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TWalshHadamard1DOperator<T>::TWalshHadamard1DOperator(klab::UInt32 n) : TOperator<T, T>(n),
_fwht()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TWalshHadamard1DOperator<T>::TWalshHadamard1DOperator(const TWalshHadamard1DOperator<T>& op) : TOperator<T, T>(op),
_fwht(op._fwht)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TWalshHadamard1DOperator<T>::~TWalshHadamard1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWalshHadamard1DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    _fwht.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWalshHadamard1DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    _fwht.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
