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

#ifndef KL1P_COMPLEXPROXYOPERATOR_H
#define KL1P_COMPLEXPROXYOPERATOR_H

#include "ProxyOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<std::complex<T>, std::complex<TOut> > >
class TComplexProxyOperator : public TProxyOperator<T, TOut, TOp>
{
public:
    
    TComplexProxyOperator(klab::TSmartPointer<TOp> op);
    TComplexProxyOperator(const TComplexProxyOperator<T, TOut, TOp>& op);
    virtual ~TComplexProxyOperator();   

    virtual T       sum();
    virtual T       normFrobenius();
    virtual T       squaredNormFrobenius();
    virtual T       mean();
    virtual T       variance();

    virtual void    apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void    applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);
    virtual void    column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void    columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TComplexProxyOperator();
    TComplexProxyOperator<T, TOut, TOp>&    operator=(const TComplexProxyOperator<T, TOut, TOp>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TComplexProxyOperator<T, TOut, TOp>::TComplexProxyOperator(klab::TSmartPointer<TOp> op) : TProxyOperator<T, TOut, TOp>(op!=0?(op->m()<<1):0, op!=0?(op->n()<<1):0, op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TComplexProxyOperator<T, TOut, TOp>::TComplexProxyOperator(const TComplexProxyOperator<T, TOut, TOp>& op) : TProxyOperator<T, TOut, TOp>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TComplexProxyOperator<T, TOut, TOp>::~TComplexProxyOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TComplexProxyOperator<T, TOut, TOp>::sum()
{
    return (this->_op!=0 ? std::norm(this->_op->sum()) : klab::TTypeInfo<T>::ZERO); // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TComplexProxyOperator<T, TOut, TOp>::normFrobenius()
{
    return (this->_op!=0 ? this->_op->normFrobenius().real() : klab::TTypeInfo<T>::ZERO);   // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TComplexProxyOperator<T, TOut, TOp>::squaredNormFrobenius()
{
    return (this->_op!=0 ? this->_op->squaredNormFrobenius().real() : klab::TTypeInfo<T>::ZERO);    // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TComplexProxyOperator<T, TOut, TOp>::mean()
{
    return (this->_op!=0 ? std::norm(this->_op->mean()) : klab::TTypeInfo<T>::ZERO);    // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline T TComplexProxyOperator<T, TOut, TOp>::variance()
{
    return (this->_op!=0 ? this->_op->variance().real() : klab::TTypeInfo<T>::ZERO);    // Not really true with our real matrix...
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TComplexProxyOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());    

    klab::UInt32 n  = in.n_rows;
    klab::UInt32 cn = n>>1;     
      
    arma::Col<std::complex<T> >    cIn(cn);
    arma::Col<std::complex<TOut> > cOut;

    for(klab::UInt32 i=0; i<cn; ++i)
        cIn[i] = std::complex<T>(in[i], in[cn+i]);

    this->_op->apply(cIn, cOut);

    out.set_size(cOut.n_rows<<1);
    for(klab::UInt32 i=0; i<cOut.n_rows; ++i)
    {
        out[i]             = cOut[i].real();
        out[cOut.n_rows+i] = cOut[i].imag();
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TComplexProxyOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());    

    klab::UInt32 n  = in.n_rows;
    klab::UInt32 cn = n>>1;     
      
    arma::Col<std::complex<TOut> > cIn(cn);
    arma::Col<std::complex<T> >    cOut;

    for(klab::UInt32 i=0; i<cn; ++i)
        cIn[i] = std::complex<TOut>(in[i], in[cn+i]);

    this->_op->applyAdjoint(cIn, cOut);

    out.set_size(cOut.n_rows<<1);
    for(klab::UInt32 i=0; i<cOut.n_rows; ++i)
    {
        out[i]             = cOut[i].real();
        out[cOut.n_rows+i] = cOut[i].imag();
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TComplexProxyOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());    

    klab::UInt32 halfSize = this->_op->n();

    arma::Col<std::complex<TOut> > cOut;
    this->_op->column(i%halfSize, cOut);

    out.set_size(cOut.n_rows<<1);
    for(klab::UInt32 j=0; j<cOut.n_rows; ++j)
    {
        if(i < halfSize)
        {
            out[j]             = cOut[j].real();
            out[cOut.n_rows+j] = cOut[j].imag();
        }
        else
        {
            out[j]             = -cOut[j].imag();
            out[cOut.n_rows+j] =  cOut[j].real();
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TComplexProxyOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());    

    klab::UInt32 halfSize = this->_op->m();

    arma::Col<std::complex<T> > cOut;
    this->_op->columnAdjoint(i%halfSize, cOut);

    out.set_size(cOut.n_rows<<1);
    for(klab::UInt32 j=0; j<cOut.n_rows; ++j)
    {
        if(i < halfSize)
        {
            out[j]             = cOut[j].real();
            out[cOut.n_rows+j] = cOut[j].imag();
        }
        else
        {
            out[j]             = -cOut[j].imag();
            out[cOut.n_rows+j] =  cOut[j].real();
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
