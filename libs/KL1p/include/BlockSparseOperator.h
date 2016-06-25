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

#ifndef KL1P_BLOCKSPARSEOPERATOR_H
#define KL1P_BLOCKSPARSEOPERATOR_H

#include "ProxyOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TBlockSparseOperator : public TProxyOperator<T, TOut, TOp>
{
public:
      
    TBlockSparseOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TOp> op, klab::UInt32 i=0, klab::UInt32 j=0);
    TBlockSparseOperator(const TBlockSparseOperator<T, TOut, TOp>& op);
    virtual ~TBlockSparseOperator(); 

    klab::UInt32         i() const;
    klab::UInt32         j() const;

    virtual void				apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void				applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);

    virtual void				column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void				columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TBlockSparseOperator();
    TBlockSparseOperator<T, TOut, TOp>&	operator=(const TBlockSparseOperator<T, TOut, TOp>& op);


private:

    klab::UInt32                _i;
    klab::UInt32                _j;
    klab::UInt32                _im;
    klab::UInt32                _jn;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockSparseOperator<T, TOut, TOp>::TBlockSparseOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TOp> op, klab::UInt32 i, klab::UInt32 j) : TProxyOperator<T, TOut, TOp>(m, n, op),
_i(i), _j(j), _im(op!=0?op->m():0), _jn(op!=0?op->n():0)
{
    klab::Int32 diff = m - (_i+_im);
    if(diff < 0)
        _im = klab::Max(static_cast<klab::Int32>(_im)+diff, 0); 

    diff = n - (_j+_jn);
    if(diff < 0)
        _jn = klab::Max(static_cast<klab::Int32>(_jn)+diff, 0); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockSparseOperator<T, TOut, TOp>::TBlockSparseOperator(const TBlockSparseOperator<T, TOut, TOp>& op) : TProxyOperator<T, TOut, TOp>(op),
_i(op._i), _j(op._j), _im(op._im), _jn(op._jn)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockSparseOperator<T, TOut, TOp>::~TBlockSparseOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TBlockSparseOperator<T, TOut, TOp>::i() const
{
    return _i;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TBlockSparseOperator<T, TOut, TOp>::j() const
{
    return _j;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockSparseOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    if(_i<this->m() || _j<this->n())
    {
        arma::Col<T> opIn(this->_op->n());
        opIn.fill(klab::TTypeInfo<T>::ZERO);
        for(klab::UInt32 i=0; i<_jn; ++i)
            opIn[i] = in[_j+i];

        arma::Col<TOut> opOut;
        this->_op->apply(opIn, opOut);

        for(klab::UInt32 i=0; i<_im; ++i)
            out[_i+i] = opOut[i];
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockSparseOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    if(_i<this->m() || _j<this->n())
    {
        arma::Col<TOut> opIn(this->_op->m());
        opIn.fill(klab::TTypeInfo<TOut>::ZERO);
        for(klab::UInt32 i=0; i<_im; ++i)
            opIn[i] = in[_i+i];

        arma::Col<T> opOut;
        this->_op->applyAdjoint(opIn, opOut);

        for(klab::UInt32 i=0; i<_jn; ++i)
            out[_j+i] = opOut[i];
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockSparseOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    if(i>=_j && (i-_j)<this->_op->n() && (_i<this->m() || _j<this->n()))
    {
        arma::Col<TOut> opOut;
        this->_op->column(i-_j, opOut);

        for(klab::UInt32 j=0; j<_im; ++j)
            out[_i+j] = opOut[j];
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockSparseOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    if(i>=_i && (i-_i)<this->_op->m() && (_i<this->m() || _j<this->n()))
    {
        arma::Col<T> opOut;
        this->_op->columnAdjoint(i-_i, opOut);

        for(klab::UInt32 j=0; j<_jn; ++j)
            out[_j+j] = opOut[j];
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
