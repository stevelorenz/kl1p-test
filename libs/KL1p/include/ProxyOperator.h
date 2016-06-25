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

#ifndef KL1P_PROXYOPERATOR_H
#define KL1P_PROXYOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TProxyOperator : public TOperator<T, TOut>
{
public:
 
    TProxyOperator(klab::TSmartPointer<TOp> op);
    TProxyOperator(klab::UInt32 n, klab::TSmartPointer<TOp> op);
    TProxyOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TOp> op);
    TProxyOperator(const TProxyOperator<T, TOut>& op);
    virtual ~TProxyOperator();  

    klab::TSmartPointer<TOp>    op() const;
    virtual bool                isZero();


protected:

    TProxyOperator();


protected:

    klab::TSmartPointer<TOp>    _op;


private:

    TProxyOperator<T, TOut>&    operator=(const TProxyOperator<T, TOut>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TProxyOperator<T, TOut, TOp>::TProxyOperator() : TOperator<T, TOut>(),
_op(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TProxyOperator<T, TOut, TOp>::TProxyOperator(klab::TSmartPointer<TOp> op) : TOperator<T, TOut>(op!=0?op->m():0, op!=0?op->n():0),
_op(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TProxyOperator<T, TOut, TOp>::TProxyOperator(klab::UInt32 n, klab::TSmartPointer<TOp> op) : TOperator<T, TOut>(n),
_op(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TProxyOperator<T, TOut, TOp>::TProxyOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TOp> op) : TOperator<T, TOut>(m, n),
_op(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TProxyOperator<T, TOut, TOp>::TProxyOperator(const TProxyOperator<T, TOut>& op) : TOperator<T, TOut>(op),
_op(op._op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TProxyOperator<T, TOut, TOp>::~TProxyOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TProxyOperator<T, TOut, TOp>::op() const
{
    return _op;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline bool TProxyOperator<T, TOut, TOp>::isZero()
{
    if(_op!=0)  return (_op->isZero() || this->m()==0 || this->n()==0);
    else        return true;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
