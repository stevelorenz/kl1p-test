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

#ifndef KL1P_ADJOINTBLOCKOPERATOR_H
#define KL1P_ADJOINTBLOCKOPERATOR_H

#include "ProxyBlockOperator.h"
#include "AdjointOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut>, class TBlockOp=TBlockOperator<T, TOut, TOp>, class TBlock=TOperator<T, TOut> >
class TAdjointBlockOperator : public TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>
{
public:
    
    TAdjointBlockOperator(klab::TSmartPointer<TBlockOp> op);
    TAdjointBlockOperator(const TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>& op);
    virtual ~TAdjointBlockOperator();

    virtual T                           sum();
    virtual T                           normFrobenius();
    virtual T                           squaredNormFrobenius();
    virtual T                           mean();
    virtual T                           variance();

	virtual klab::UInt32                countBlockRows() const;
    virtual klab::UInt32                countBlockColumns() const;
    virtual klab::TSmartPointer<TBlock> block(klab::UInt32 i, klab::UInt32 j) const;
    virtual bool                        isZeroBlock(klab::UInt32 i, klab::UInt32 j) const;
    virtual klab::TSmartPointer<TBlock> inBlock(klab::UInt32 i, klab::UInt32 j) const;

    virtual void                        apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void                        applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);
    virtual void                        column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void                        columnAdjoint(klab::UInt32 i, arma::Col<T>& out);

    virtual void                        applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void                        applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TAdjointBlockOperator();
    TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>&  operator=(const TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::TAdjointBlockOperator(klab::TSmartPointer<TBlockOp> op) : TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>(op!=0?op->n():0, op!=0?op->m():0, op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::TAdjointBlockOperator(const TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>& op) : TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::~TAdjointBlockOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::sum()
{
    return (this->_op!=0 ? klab::Conj(this->_op->sum()) : klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::normFrobenius()
{
    return (this->_op!=0 ? this->_op->normFrobenius() : klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::squaredNormFrobenius()
{
    return (this->_op!=0 ? this->_op->squaredNormFrobenius() : klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::mean()
{
    return (this->_op!=0 ? klab::Conj(this->_op->mean()) : klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::variance()
{
    T ret = klab::TTypeInfo<T>::ZERO;

    if(this->_op != 0)
    {
        klab::UInt32 mn = this->m() * this->n();
        if(mn > 0)
        {
            T mean = this->_op->mean();
            ret = (this->_op->squaredNormFrobenius()/static_cast<T>(mn)) - (mean*klab::Conj(mean));
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline klab::UInt32 TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::countBlockRows() const
{
    return (this->_op!=0 ? this->_op->countBlockColumns() : 0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline klab::UInt32 TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::countBlockColumns() const
{
    return (this->_op!=0 ? this->_op->countBlockRows() : 0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline klab::TSmartPointer<TBlock> TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::block(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    return new TAdjointOperator<T, TOut, TOp>(this->_op->block(j, i));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline bool TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::isZeroBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    return this->_op->isZeroBlock(j, i);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline klab::TSmartPointer<TBlock> TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::inBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m() || j>=this->n());

    return new TAdjointOperator<T, TOut, TOp>(this->_op->inBlock(j, i));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());   

    this->_op->applyAdjoint(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());   

    this->_op->apply(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());
    
    this->_op->columnAdjoint(i, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());
    
    this->_op->column(i, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KNullOperatorException, this->countBlockRows()==0 || this->countBlockColumns()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockColumns()); 

    this->_op->applyBlockVarianceAdjoint(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TAdjointBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KNullOperatorException, this->countBlockRows()==0 || this->countBlockColumns()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockRows()); 

    this->_op->applyBlockVariance(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
