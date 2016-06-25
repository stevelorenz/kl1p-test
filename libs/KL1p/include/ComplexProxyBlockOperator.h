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

#ifndef KL1P_COMPLEXPROXYBLOCKOPERATOR_H
#define KL1P_COMPLEXPROXYBLOCKOPERATOR_H

#include "ProxyBlockOperator.h"
#include "ComplexProxyOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<std::complex<T>, std::complex<TOut> >, class TBlockOp=TBlockOperator<std::complex<T>, std::complex<TOut>, TOp>, class TBlock=TOperator<T, TOut> >
class TComplexProxyBlockOperator : public TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>
{
public:
    
    TComplexProxyBlockOperator(klab::TSmartPointer<TBlockOp> op);
    TComplexProxyBlockOperator(const TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>& op);
    virtual ~TComplexProxyBlockOperator();    

    virtual T       sum();
    virtual T       normFrobenius();
    virtual T       squaredNormFrobenius();
    virtual T       mean();
    virtual T       variance();

    virtual klab::TSmartPointer<TBlock> block(klab::UInt32 i, klab::UInt32 j) const;
    virtual klab::TSmartPointer<TBlock> inBlock(klab::UInt32 i, klab::UInt32 j) const;

    virtual void    apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void    applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);
    virtual void    column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void    columnAdjoint(klab::UInt32 i, arma::Col<T>& out);

    virtual void    applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void    applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TComplexProxyBlockOperator();
    TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp>& operator=(const TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::TComplexProxyBlockOperator(klab::TSmartPointer<TBlockOp> op) : TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>(op!=0?(op->m()<<1):0, op!=0?(op->n()<<1):0, op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::TComplexProxyBlockOperator(const TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>& op) : TProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::~TComplexProxyBlockOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::sum()
{
    return (this->_op!=0 ? std::norm(this->_op->sum()) : klab::TTypeInfo<T>::ZERO); // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::normFrobenius()
{
    return (this->_op!=0 ? this->_op->normFrobenius().real() : klab::TTypeInfo<T>::ZERO);   // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::squaredNormFrobenius()
{
    return (this->_op!=0 ? this->_op->squaredNormFrobenius().real() : klab::TTypeInfo<T>::ZERO);    // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::mean()
{
    return (this->_op!=0 ? std::norm(this->_op->mean()) : klab::TTypeInfo<T>::ZERO);    // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline T TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::variance()
{
    return (this->_op!=0 ? this->_op->variance().real() : klab::TTypeInfo<T>::ZERO);    // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline klab::TSmartPointer<TBlock> TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::block(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m() || j>=this->n());

    return new TComplexProxyOperator<T, TOut, TOp>(this->_op->block(i, j));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline klab::TSmartPointer<TBlock> TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::inBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m() || j>=this->n());

    return new TComplexProxyOperator<T, TOut, TOp>(this->_op->inBlock(i>>1, j>>1));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());    

    klab::UInt32 n  = in.n_rows;
    klab::UInt32 cn = (n>>1);     
      
    arma::Col<std::complex<T> >    cIn(cn);
    arma::Col<std::complex<TOut> > cOut;

    klab::UInt32 nb = this->countBlockColumns();    
    for(klab::UInt32 j=0, k=0, l=0; j<nb; ++j)
    {
        klab::TSmartPointer<TOp> op = this->_op->block(0, j);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        klab::UInt32 nOp = op->n();
        for(klab::UInt32 i=0; i<nOp; ++i, ++k, ++l)
            cIn[k] = std::complex<T>(in[l], in[l+nOp]);

        l += nOp;
    }

    this->_op->apply(cIn, cOut);

    out.set_size(cOut.n_rows<<1);
    klab::UInt32 mb = this->countBlockRows();  
    for(klab::UInt32 i=0, k=0, l=0; i<mb; ++i)
    {
        klab::TSmartPointer<TOp> op = this->_op->block(i, 0);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        klab::UInt32 mOp = op->m();
        for(klab::UInt32 j=0; j<mOp; ++j, ++k, ++l)
        {
            out[l]     = cOut[k].real();
            out[l+mOp] = cOut[k].imag();
        }

        l += mOp;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());    

    klab::UInt32 n  = in.n_rows;
    klab::UInt32 cn = (n>>1);     
      
    arma::Col<std::complex<TOut> > cIn(cn);
    arma::Col<std::complex<T> >    cOut;

    klab::UInt32 mb = this->countBlockRows();  
    for(klab::UInt32 i=0, k=0, l=0; i<mb; ++i)
    {
        klab::TSmartPointer<TOp> op = this->_op->block(i, 0);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        klab::UInt32 mOp = op->m();
        for(klab::UInt32 j=0; j<mOp; ++j, ++k, ++l)
            cIn[k] = std::complex<TOut>(in[l], in[l+mOp]);

        l += mOp;
    }

    this->_op->applyAdjoint(cIn, cOut);

    out.set_size(cOut.n_rows<<1);
    klab::UInt32 nb = this->countBlockColumns();   
    for(klab::UInt32 j=0, k=0, l=0; j<nb; ++j)
    {
        klab::TSmartPointer<TOp> op = this->_op->block(0, j);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        klab::UInt32 nOp = op->n();
        for(klab::UInt32 i=0; i<nOp; ++i, ++k, ++l)
        {
            out[l]     = cOut[k].real();
            out[l+nOp] = cOut[k].imag();
        }

        l += nOp;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::column(klab::UInt32 i, arma::Col<TOut>& out)
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
        klab::TSmartPointer<TOp> op = this->_op->block(0, jb);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);
        
        if(i<(s+(op->n()<<1)))  found = true;
        else                    s += op->n()<<1;
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);

    klab::UInt32 iCol = i-s;
    for(klab::UInt32 ib=0, r=0; ib<m; ++ib)
    {
        klab::TSmartPointer<TBlock> op = this->block(ib, jb-1);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        arma::Col<TOut> subOut;
        op->column(iCol, subOut);

        for(klab::UInt32 k=0; k<subOut.n_rows; ++k)
            out[r+k] = subOut[k];

        r += op->m();
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
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
        klab::TSmartPointer<TOp> op = this->_op->block(ib, 0);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(i<(s+(op->m()<<1)))  found = true;
        else                    s += op->m()<<1;     
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);

    klab::UInt32 iCol = i-s;
    for(klab::UInt32 jb=0, r=0; jb<n; ++jb)
    {
        klab::TSmartPointer<TBlock> op = this->block(ib-1, jb);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        arma::Col<T> subOut;
        op->columnAdjoint(iCol, subOut);

        for(klab::UInt32 k=0; k<subOut.n_rows; ++k)
            out[r+k] = subOut[k];

        r += op->n();
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KNullOperatorException, this->countBlockRows()==0 || this->countBlockColumns()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockColumns());

    arma::Col<std::complex<T> > cIn(in.n_rows);
    for(klab::UInt32 i=0; i<cIn.n_rows; ++i)
        cIn[i] = std::complex<T>(in[i]);

    arma::Col<std::complex<T> > cOut;
    this->_op->applyBlockVariance(cIn, cOut);

    out.set_size(cOut.n_rows);
    for(klab::UInt32 i=0; i<out.n_rows; ++i)
        out[i] = cOut[i].real();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp, class TBlockOp, class TBlock>
inline void TComplexProxyBlockOperator<T, TOut, TOp, TBlockOp, TBlock>::applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KNullOperatorException, this->countBlockRows()==0 || this->countBlockColumns()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockRows()); 

    arma::Col<std::complex<T> > cIn(in.n_rows);
    for(klab::UInt32 i=0; i<cIn.n_rows; ++i)
        cIn[i] = std::complex<T>(in[i]);

    arma::Col<std::complex<T> > cOut;
    this->_op->applyBlockVarianceAdjoint(cIn, cOut);

    out.set_size(cOut.n_rows);
    for(klab::UInt32 i=0; i<out.n_rows; ++i)
        out[i] = cOut[i].real();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
