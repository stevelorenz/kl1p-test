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

#ifndef KL1P_RESIZINGDOPERATOR_H
#define KL1P_RESIZINGDOPERATOR_H

#include "ProxyOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TResizingOperator : public TProxyOperator<T, TOut, TOp>
{
public:
      
    TResizingOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TOp> op);
    TResizingOperator(const TResizingOperator<T, TOut, TOp>& op);
    virtual ~TResizingOperator(); 

    virtual void				apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void				applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);

    virtual void				column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void				columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TResizingOperator();
    TResizingOperator<T, TOut, TOp>&	operator=(const TResizingOperator<T, TOut, TOp>& op);


private:

    klab::UInt32                _im;
    klab::UInt32                _jn;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TResizingOperator<T, TOut, TOp>::TResizingOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TOp> op) : TProxyOperator<T, TOut, TOp>(m, n, op),
_im(op!=0?op->m():0), _jn(op!=0?op->n():0)
{
    klab::Int32 diff = m - _im;
    if(diff < 0)
        _im = klab::Max(static_cast<klab::Int32>(_im)+diff, 0); 

    diff = n - _jn;
    if(diff < 0)
        _jn = klab::Max(static_cast<klab::Int32>(_jn)+diff, 0); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TResizingOperator<T, TOut, TOp>::TResizingOperator(const TResizingOperator<T, TOut, TOp>& op) : TProxyOperator<T, TOut, TOp>(op),
_im(op._im), _jn(op._jn)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TResizingOperator<T, TOut, TOp>::~TResizingOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TResizingOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    if(this->m()>0 && this->n()>0)
    {
        arma::Col<T> opIn(this->_op->n());
        opIn.fill(klab::TTypeInfo<T>::ZERO);
        for(klab::UInt32 i=0; i<_jn; ++i)
            opIn[i] = in[i];

        arma::Col<TOut> opOut;
        this->_op->apply(opIn, opOut);

        for(klab::UInt32 i=0; i<_im; ++i)
            out[i] = opOut[i];
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TResizingOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    if(this->m()>0 && this->n()>0)
    {
        arma::Col<TOut> opIn(this->_op->m());
        opIn.fill(klab::TTypeInfo<TOut>::ZERO);
        for(klab::UInt32 i=0; i<_im; ++i)
            opIn[i] = in[+i];

        arma::Col<T> opOut;
        this->_op->applyAdjoint(opIn, opOut);

        for(klab::UInt32 i=0; i<_jn; ++i)
            out[i] = opOut[i];
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TResizingOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    if(i<this->_op->n() && this->m()>0 && this->n()>0)
    {
        arma::Col<TOut> opOut;
        this->_op->column(i, opOut);

        for(klab::UInt32 j=0; j<_im; ++j)
            out[j] = opOut[j];
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TResizingOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    if(i<this->_op->m() && this->m()>0 && this->n()>0)
    {
        arma::Col<T> opOut;
        this->_op->columnAdjoint(i, opOut);

        for(klab::UInt32 j=0; j<_jn; ++j)
            out[j] = opOut[j];
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
