// KSci - A portable C++ numerical analysis library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KSci C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_COMPLEXPROXYLINEAROPERATOR_H
#define KLAB_COMPLEXPROXYLINEAROPERATOR_H

#include "LinearOperator.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
class TComplexProxyLinearOperator : public TLinearOperator<T, TComplexProxyLinearOperator<T, TOperator> >
{
public:

    TComplexProxyLinearOperator(const TOperator& op);
    TComplexProxyLinearOperator(const TComplexProxyLinearOperator<T, TOperator>& op);
    virtual ~TComplexProxyLinearOperator();

    TComplexProxyLinearOperator<T, TOperator>&  operator=(const TComplexProxyLinearOperator<T, TOperator>& op);

    void	apply(const arma::Col<T>& in, arma::Col<T>& out) const;
	void	applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) const;


private:

    TComplexProxyLinearOperator();
 

private:

    const TOperator&    _op;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
inline TComplexProxyLinearOperator<T, TOperator>::TComplexProxyLinearOperator(const TOperator& op) : TLinearOperator<T, TComplexProxyLinearOperator<T, TOperator> >(op.m()<<1, op.n()<<1),
_op(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
inline TComplexProxyLinearOperator<T, TOperator>::TComplexProxyLinearOperator(const TComplexProxyLinearOperator<T, TOperator>& op) : TLinearOperator<T, TComplexProxyLinearOperator<T, TOperator> >(op),
_op(op._op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
inline TComplexProxyLinearOperator<T, TOperator>::~TComplexProxyLinearOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
inline TComplexProxyLinearOperator<T, TOperator>& TComplexProxyLinearOperator<T, TOperator>::operator=(const TComplexProxyLinearOperator<T, TOperator>& op)
{
    if(this != &op)
    {
        TLinearOperator<T, TComplexProxyLinearOperator<T, TOperator> >::operator=(op);

        _op = op._op;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
inline void TComplexProxyLinearOperator<T, TOperator>::apply(const arma::Col<T>& in, arma::Col<T>& out) const
{
    ThrowTraceExceptionIf(KIncompatibleSizeLinearOperatorException, in.n_rows != this->n());

    klab::UInt32 inSize = in.n_rows>>1;
    arma::Col<std::complex<T> > cIn(inSize);
    arma::Col<std::complex<T> > cOut;
    
    for(klab::UInt32 i=0; i<inSize; ++i)
        cIn[i] = std::complex<T>(in[i], in[inSize+i]);   

    _op.apply(cIn, cOut);

    out.set_size(cOut.n_rows<<1);
    for(klab::UInt32 i=0; i<cOut.n_rows; ++i)
    {
        out[i]             = cOut[i].real();
        out[cOut.n_rows+i] = cOut[i].imag();
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
inline void TComplexProxyLinearOperator<T, TOperator>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) const
{
    ThrowTraceExceptionIf(KIncompatibleSizeLinearOperatorException, in.n_rows != this->m());

    klab::UInt32 inSize = in.n_rows>>1;
    arma::Col<std::complex<T> > cIn(inSize);
    arma::Col<std::complex<T> > cOut;
    
    for(klab::UInt32 i=0; i<inSize; ++i)
        cIn[i] = std::complex<T>(in[i], in[inSize+i]);    

    _op.applyAdjoint(cIn, cOut);

    out.set_size(cOut.n_rows<<1);
    for(klab::UInt32 i=0; i<cOut.n_rows; ++i)
    {
        out[i]             = cOut[i].real();
        out[cOut.n_rows+i] = cOut[i].imag();
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
