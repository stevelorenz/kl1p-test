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

#ifndef KL1P_PROXYBLOCKOPERATOR_H
#define KL1P_PROXYBLOCKOPERATOR_H

#include "BlockOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut>, class TBlockOp=TBlockOperator<T, TOut, TOp>, class TBlock=TOp>
class TProxyBlockOperator : public TBlockOperator<T, TOut, TBlock>
{
public:
 
    TProxyBlockOperator(klab::TSmartPointer<TBlockOp> op);
    TProxyBlockOperator(klab::UInt32 n, klab::TSmartPointer<TBlockOp> op);
    TProxyBlockOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TBlockOp> op);
    TProxyBlockOperator(const TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>& op);
    virtual ~TProxyBlockOperator();  

    klab::TSmartPointer<TBlockOp>       op() const;

    virtual bool                        isZero();

    virtual klab::UInt32                countBlockRows() const;
    virtual klab::UInt32                countBlockColumns() const;
    virtual bool                        isZeroBlock(klab::UInt32 i, klab::UInt32 j) const;


protected:

    TProxyBlockOperator();


protected:

    klab::TSmartPointer<TBlockOp>       _op;


private:

    TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>&    operator=(const TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::TProxyBlockOperator() : TBlockOperator<T, TOut, TBlock>(),
_op(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::TProxyBlockOperator(klab::TSmartPointer<TBlockOp> op) : TBlockOperator<T, TOut, TBlock>(op!=0?op->m():0, op!=0?op->n():0),
_op(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::TProxyBlockOperator(klab::UInt32 n, klab::TSmartPointer<TBlockOp> op) : TBlockOperator<T, TOut, TBlock>(n),
_op(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::TProxyBlockOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TBlockOp> op) : TBlockOperator<T, TOut, TBlock>(m, n),
_op(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::TProxyBlockOperator(const TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>& op) : TBlockOperator<T, TOut, TBlock>(op),
_op(op._op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::~TProxyBlockOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline klab::TSmartPointer<TBlockOp> TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::op() const
{
    return _op;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline bool TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::isZero()
{
    if(_op!=0)  return (_op->isZero() || this->m()==0 || this->n()==0);
    else        return true;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline klab::UInt32 TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::countBlockRows() const
{
    return (_op!=0 ? _op->countBlockRows() : 0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline klab::UInt32 TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::countBlockColumns() const
{
    return (_op!=0 ? _op->countBlockColumns() : 0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline bool TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::isZeroBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    return _op->isZeroBlock(i, j);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
