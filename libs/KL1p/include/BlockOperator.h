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

#ifndef KL1P_BLOCKOPERATOR_H
#define KL1P_BLOCKOPERATOR_H

#include "Operator.h"
#include "ZeroOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=kl1p::TOperator<T, TOut> >
class TBlockOperator : public TOperator<T, TOut>
{
public:

    TBlockOperator();
    TBlockOperator(klab::UInt32 n);
    TBlockOperator(klab::UInt32 m, klab::UInt32 n);
    TBlockOperator(const TBlockOperator<T, TOut, TOp>& op);
    virtual ~TBlockOperator();   

    virtual bool                        isZero();
    virtual T                           sum();
    virtual T                           squaredNormFrobenius();

    virtual klab::UInt32                countBlockRows() const = 0;
    virtual klab::UInt32                countBlockColumns() const = 0;
    virtual klab::TSmartPointer<TOp>    block(klab::UInt32 i, klab::UInt32 j) const = 0;
    virtual bool                        isZeroBlock(klab::UInt32 i, klab::UInt32 j) const;
    virtual klab::TSmartPointer<TOp>    inBlock(klab::UInt32 i, klab::UInt32 j) const;    

    virtual void                        apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void                        applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);
    virtual void                        column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void                        columnAdjoint(klab::UInt32 i, arma::Col<T>& out);

    virtual void                        applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void                        applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TBlockOperator<T, TOut>&            operator=(const TBlockOperator<T, TOut>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockOperator<T, TOut, TOp>::TBlockOperator() : TOperator<T, TOut>()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockOperator<T, TOut, TOp>::TBlockOperator(klab::UInt32 n) : TOperator<T, TOut>(n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockOperator<T, TOut, TOp>::TBlockOperator(klab::UInt32 m, klab::UInt32 n) : TOperator<T, TOut>(m, n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockOperator<T, TOut, TOp>::TBlockOperator(const TBlockOperator<T, TOut, TOp>& op) : TOperator<T, TOut>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockOperator<T, TOut, TOp>::~TBlockOperator()
{}


// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline bool TBlockOperator<T, TOut, TOp>::isZero()
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockRows();

    bool ret = true;
    for(klab::UInt32 i=0; i<m && ret; ++i)
    {
        for(klab::UInt32 j=0; j<n && ret; ++j)
            ret = this->isZeroBlock(i, j);
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TBlockOperator<T, TOut, TOp>::sum()
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();

    T ret = klab::TTypeInfo<T>::ZERO;
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
        {
            klab::TSmartPointer<TOp> op = this->block(i, j);
            ThrowTraceExceptionIf(KNullOperatorException, op==0);

            ret += op->sum();
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TBlockOperator<T, TOut, TOp>::squaredNormFrobenius()
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();

    T ret = klab::TTypeInfo<T>::ZERO;
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
        {
            klab::TSmartPointer<TOp> op = this->block(i, j);
            ThrowTraceExceptionIf(KNullOperatorException, op==0);

            ret += op->squaredNormFrobenius();
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline bool TBlockOperator<T, TOut, TOp>::isZeroBlock(klab::UInt32 i, klab::UInt32 j) const
{
    klab::TSmartPointer<TOp> op = this->block(i, j);
    ThrowTraceExceptionIf(KNullOperatorException, op==0);

    return op->isZero();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TBlockOperator<T, TOut, TOp>::inBlock(klab::UInt32 i, klab::UInt32 j) const
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();
    ThrowTraceExceptionIf(KNullOperatorException, m==0 || n==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m() || j>=this->n());    

    klab::UInt32 s = 0;
    bool found = false;
    klab::UInt32 ib = 0;
    for(; ib<m && found==false; ++ib)
    {
        klab::TSmartPointer<TOp> op = this->block(ib, 0);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        s += op->m();
        found = (i<s);       
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);

    s = 0;
    found = false;
    klab::UInt32 jb = 0;
    for(; jb<n && found==false; ++jb)
    {
        klab::TSmartPointer<TOp> op = this->block(0, jb);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        s += op->n();
        found = (j<s);       
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);

    return this->block(ib-1, jb-1);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();
    ThrowTraceExceptionIf(KNullOperatorException, m==0 || n==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    klab::UInt32 mBlock = 0;
    for(klab::UInt32 i=0, r=0; i<m; ++i)
    {
        for(klab::UInt32 j=0, s=0; j<n; ++j)
        {
            klab::TSmartPointer<TOp> op = this->block(i, j);
            ThrowTraceExceptionIf(KNullOperatorException, op==0);

            if(op->isZero() == false)
            {
                arma::Col<T> subIn(op->n());
                for(klab::UInt32 k=0; k<subIn.n_rows; ++k, ++s)
                    subIn[k] = in[s];

                arma::Col<TOut> subOut;
                op->apply(subIn, subOut);

                for(klab::UInt32 k=0; k<subOut.n_rows; ++k)
                    out[r+k] += subOut[k];
            }
            else
            {
                s += op->n();
            }

            if(j == 0)
                mBlock = op->m();
        }

        r += mBlock;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();
    ThrowTraceExceptionIf(KNullOperatorException, m==0 || n==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    klab::UInt32 nBlock = 0;
    for(klab::UInt32 j=0, r=0; j<n; ++j)
    {
        for(klab::UInt32 i=0, s=0; i<m; ++i)
        {
            klab::TSmartPointer<TOp> op = this->block(i, j);
            ThrowTraceExceptionIf(KNullOperatorException, op==0);

            if(op->isZero() == false)
            {
                arma::Col<T> subIn(op->m());
                for(klab::UInt32 k=0; k<subIn.n_rows; ++k, ++s)
                    subIn[k] = in[s];

                arma::Col<T> subOut;
                op->applyAdjoint(subIn, subOut);

                for(klab::UInt32 k=0; k<subOut.n_rows; ++k)
                    out[r+k] += subOut[k];
            }
            else
            {
                s += op->m();
            }

            if(i == 0)
                nBlock = op->n();
        }

        r += nBlock;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();
    ThrowTraceExceptionIf(KNullOperatorException, m==0 || n==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n()); 

    out.set_size(this->m());

    klab::UInt32 s = 0;
    bool found = false;
    klab::UInt32 jb = 0;
    for(; jb<n && found==false; ++jb)
    {
        klab::TSmartPointer<TOp> op = this->block(0, jb);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);
        
        if(i<(s+op->n()))   found = true;
        else                s += op->n();
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);

    klab::UInt32 iCol = i-s;
    for(klab::UInt32 ib=0, r=0; ib<m; ++ib)
    {
        klab::TSmartPointer<TOp> op = this->block(ib, jb-1);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        arma::Col<TOut> subOut;
        op->column(iCol, subOut);

        for(klab::UInt32 k=0; k<subOut.n_rows; ++k)
            out[r+k] = subOut[k];

        r += op->m();
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();
    ThrowTraceExceptionIf(KNullOperatorException, m==0 || n==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m()); 

    out.set_size(this->n());

    klab::UInt32 s = 0;
    bool found = false;
    klab::UInt32 ib = 0;
    for(; ib<m && found==false; ++ib)
    {
        klab::TSmartPointer<TOp> op = this->block(ib, 0);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(i<(s+op->m()))   found = true;
        else                s += op->m();     
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);

    klab::UInt32 iCol = i-s;
    for(klab::UInt32 jb=0, r=0; jb<n; ++jb)
    {
        klab::TSmartPointer<TOp> op = this->block(ib-1, jb);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        arma::Col<T> subOut;
        op->columnAdjoint(iCol, subOut);

        for(klab::UInt32 k=0; k<subOut.n_rows; ++k)
            out[r+k] = subOut[k];

        r += op->n();
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockOperator<T, TOut, TOp>::applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out)
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();
    ThrowTraceExceptionIf(KNullOperatorException, m==0 || n==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=n); 

    arma::Mat<T> matrix(m, n);
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
        {
            klab::TSmartPointer<TOp> op = this->block(i, j);
            ThrowTraceExceptionIf(KNullOperatorException, op==0);

            matrix(i, j) = op->variance();
        }
    }

    out = matrix * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockOperator<T, TOut, TOp>::applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();
    ThrowTraceExceptionIf(KNullOperatorException, m==0 || n==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=m); 

    arma::Mat<T> matrix(m, n);
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
        {
            klab::TSmartPointer<TOp> op = this->block(i, j);
            ThrowTraceExceptionIf(KNullOperatorException, op==0);

            matrix(i, j) = op->variance();
        }
    }

    out = arma::trans(matrix) * in;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
