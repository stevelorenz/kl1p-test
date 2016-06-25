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

#ifndef KL1P_MULTIPLICATIONOPERATOR_H
#define KL1P_MULTIPLICATIONOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TLinROut=T, class TLeft=TOperator<TLinROut, TOut>, class TRight=TOperator<T, TLinROut> >
class TMultiplicationOperator : public TOperator<T, TOut>
{
public:
    
    TMultiplicationOperator(klab::TSmartPointer<TLeft> left, klab::TSmartPointer<TRight> right);
    TMultiplicationOperator(const TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>& op);
    virtual ~TMultiplicationOperator();    

    klab::TSmartPointer<TLeft>  left() const;
    klab::TSmartPointer<TRight> right() const;
    virtual bool                isZero();

    virtual void    apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void    applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);

    virtual void    column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void    columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TMultiplicationOperator();
    TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>&    operator=(const TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>& op);


private:

    klab::TSmartPointer<TLeft>      _left;
    klab::TSmartPointer<TRight>     _right;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::TMultiplicationOperator(klab::TSmartPointer<TLeft> left, klab::TSmartPointer<TRight> right) : TOperator<T, TOut>(left!=0?left->m():(right!=0?right->m():0), right!=0?right->n():(left!=0?left->n():0)),
_left(left), _right(right)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::TMultiplicationOperator(const TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>& op) : TOperator<T, TOut>(op),
_left(op._left), _right(op._right)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::~TMultiplicationOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline klab::TSmartPointer<TLeft> TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::left() const
{
    return _left;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline klab::TSmartPointer<TRight> TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::right() const
{
    return _right;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline bool TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::isZero()
{
    return ((_left==0 && _right==0) || (_left!=0 && _left->isZero()) || (_right!=0 && _right->isZero()));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline void TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _left==0 && _right==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());    

    if(_left == 0)
    {
        _right->apply(in, out);
    }
    else if(_right == 0)
    {
        _left->apply(in, out);
    }
    else
    {
        ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, _left->n()!=_right->m());

        arma::Col<TLinROut> tmp;
        _right->apply(in, tmp);
        _left->apply(tmp, out);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline void TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _left==0 && _right==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    if(_left == 0)
    {
        _right->applyAdjoint(in, out);
    }
    else if(_right == 0)
    {
        _left->applyAdjoint(in, out);
    }
    else
    {
        ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, _left->n()!=_right->m());

        arma::Col<TLinROut> tmp;
        _left->applyAdjoint(in, tmp);
        _right->applyAdjoint(tmp, out);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline void TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _left==0 && _right==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());    

    if(_left == 0)
    {
        _right->column(i, out);
    }
    else if(_right == 0)
    {
        _left->column(i, out);
    }
    else
    {
        ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, _left->n()!=_right->m());

        arma::Col<TLinROut> tmp;
        _right->column(i, tmp);
        _left->apply(tmp, out);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut, class TLeft, class TRight>
inline void TMultiplicationOperator<T, TOut, TLinROut, TLeft, TRight>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _left==0 && _right==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    if(_left == 0)
    {
        _right->columnAdjoint(i, out);
    }
    else if(_right == 0)
    {
        _left->columnAdjoint(i, out);
    }
    else
    {
        ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, _left->n()!=_right->m());

        arma::Col<TLinROut> tmp;
        _left->columnAdjoint(i, tmp);
        _right->applyAdjoint(tmp, out);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLinROut>
inline klab::TSmartPointer<TOperator<T, TOut> >     operator*(klab::TSmartPointer<TOperator<TLinROut, TOut> > left, klab::TSmartPointer<TOperator<T, TLinROut> > right)
{
    return new TMultiplicationOperator<T, TOut, TLinROut, TOperator<TLinROut, TOut>, TOperator<T, TLinROut> >(left, right);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
