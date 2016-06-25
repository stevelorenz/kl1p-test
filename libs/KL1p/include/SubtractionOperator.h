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

#ifndef KL1P_SUBTRACTIONOPERATOR_H
#define KL1P_SUBTRACTIONOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TLeft=TOperator<T, TOut>, class TRight=TOperator<T, TOut> >
class TSubtractionOperator : public TOperator<T, TOut>
{
public:
    
    TSubtractionOperator(klab::TSmartPointer<TLeft> left, klab::TSmartPointer<TRight> right);
    TSubtractionOperator(const TSubtractionOperator<T, TOut, TLeft, TRight>& op);
    virtual ~TSubtractionOperator();    

    klab::TSmartPointer<TLeft>  left() const;
    klab::TSmartPointer<TRight> right() const;
    virtual bool                isZero();

    virtual void    apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void    applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);

    virtual void    column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void    columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TSubtractionOperator();
    TSubtractionOperator<T, TOut, TLeft, TRight>&   operator=(const TSubtractionOperator<T, TOut, TLeft, TRight>& op);


private:

    klab::TSmartPointer<TLeft>      _left;
    klab::TSmartPointer<TRight>     _right;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline TSubtractionOperator<T, TOut, TLeft, TRight>::TSubtractionOperator(klab::TSmartPointer<TLeft> left, klab::TSmartPointer<TRight> right) : TOperator<T, TOut>(klab::Max(left!=0?left->m():0, right!=0?right->m():0), klab::Max(left!=0?left->n():0, right!=0?right->n():0)),
_left(left), _right(right)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline TSubtractionOperator<T, TOut, TLeft, TRight>::TSubtractionOperator(const TSubtractionOperator<T, TOut, TLeft, TRight>& op) : TOperator<T, TOut>(op),
_left(op._left), _right(op._right)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline TSubtractionOperator<T, TOut, TLeft, TRight>::~TSubtractionOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline klab::TSmartPointer<TLeft> TSubtractionOperator<T, TOut, TLeft, TRight>::left() const
{
    return _left;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline klab::TSmartPointer<TRight> TSubtractionOperator<T, TOut, TLeft, TRight>::right() const
{
    return _right;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline bool TSubtractionOperator<T, TOut, TLeft, TRight>::isZero()
{
    return ((_left==0 && _right==0) || (_left==0 && _right!=0 && _right->isZero()) || (_right==0 && _left!=0 && _left->isZero()) || (_left!=0 && _left->isZero() && _right!=0 && _right->isZero()));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline void TSubtractionOperator<T, TOut, TLeft, TRight>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _left==0 && _right==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());    

    if(_left == 0)
    {
        _right->apply(in, out);
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] = -out[i];
    }
    else if(_right == 0)
    {
        _left->apply(in, out);
    }
    else
    {
        ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, _left->m()!=_right->m() || _left->n()!=_right->n());

        arma::Col<TOut> lTmp;
        _left->apply(in, lTmp);

        arma::Col<TOut> rTmp;
        _right->apply(in, rTmp);

        out.set_size(this->m());
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
        {
            if(i < lTmp.n_rows)
            {
                if(i < rTmp.n_rows) out[i] = lTmp[i] - rTmp[i];
                else                out[i] = lTmp[i];
            }
            else
            {
                if(i < rTmp.n_rows) out[i] = -rTmp[i];
                else                out[i] = klab::TTypeInfo<TOut>::ZERO;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline void TSubtractionOperator<T, TOut, TLeft, TRight>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _left==0 && _right==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    if(_left == 0)
    {
        _right->applyAdjoint(in, out);
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] = -out[i];
    }
    else if(_right == 0)
    {
        _left->applyAdjoint(in, out);
    }
    else
    {
        ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, _left->m()!=_right->m() || _left->n()!=_right->n());

        arma::Col<T> lTmp;
        _left->applyAdjoint(in, lTmp);

        arma::Col<T> rTmp;
        _right->applyAdjoint(in, rTmp);

        out.set_size(this->n());
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
        {
            if(i < lTmp.n_rows)
            {
                if(i < rTmp.n_rows) out[i] = lTmp[i] - rTmp[i];
                else                out[i] = lTmp[i];
            }
            else
            {
                if(i < rTmp.n_rows) out[i] = -rTmp[i];
                else                out[i] = klab::TTypeInfo<T>::ZERO;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline void TSubtractionOperator<T, TOut, TLeft, TRight>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _left==0 && _right==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());    

    if(_left == 0)
    {
        _right->column(i, out);
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] = -out[i];
    }
    else if(_right == 0)
    {
        _left->column(i, out);
    }
    else
    {
        ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, _left->m()!=_right->m() || _left->n()!=_right->n());

        arma::Col<TOut> lTmp;
        _left->column(i, lTmp);

        arma::Col<TOut> rTmp;
        _right->column(i, rTmp);

        out.set_size(this->m());
        for(klab::UInt32 j=0; j<out.n_rows; ++j)
        {
            if(j < lTmp.n_rows)
            {
                if(j<rTmp.n_rows)   out[j] = lTmp[j] - rTmp[j];
                else                out[j] = lTmp[j];
            }
            else
            {
                if(j<rTmp.n_rows)   out[j] = -rTmp[j];
                else                out[j] = klab::TTypeInfo<TOut>::ZERO;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TLeft, class TRight>
inline void TSubtractionOperator<T, TOut, TLeft, TRight>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _left==0 && _right==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    if(_left == 0)
    {
        _right->columnAdjoint(i, out);
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] = -out[i];
    }
    else if(_right == 0)
    {
        _left->columnAdjoint(i, out);
    }
    else
    {
        ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, _left->m()!=_right->m() || _left->n()!=_right->n());

        arma::Col<T> lTmp;
        _left->columnAdjoint(i, lTmp);

        arma::Col<T> rTmp;
        _right->columnAdjoint(i, rTmp);

        out.set_size(this->n());
        for(klab::UInt32 j=0; j<out.n_rows; ++j)
        {
            if(j < lTmp.n_rows)
            {
                if(j<rTmp.n_rows)   out[j] = lTmp[j] - rTmp[j];
                else                out[j] = lTmp[j];
            }
            else
            {
                if(j<rTmp.n_rows)   out[j] = -rTmp[j];
                else                out[j] = klab::TTypeInfo<T>::ZERO;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline klab::TSmartPointer<TOperator<T, TOut> >     operator-(klab::TSmartPointer<TOperator<T, TOut> > left, klab::TSmartPointer<TOperator<T, TOut> > right)
{
    return new TSubtractionOperator<T, TOut, TOperator<T, TOut>, TOperator<T, TOut> >(left, right);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
