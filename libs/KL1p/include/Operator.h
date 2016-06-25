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

#ifndef KL1P_OPERATOR_H
#define KL1P_OPERATOR_H

#include <KSciInclude.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KOperatorException, klab::KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorException, KOperatorException)
KLAB_DECLARE_EXCEPTION(KOutOfBoundOperatorException, KOperatorException)   
KLAB_DECLARE_EXCEPTION(KIncompatibleSizeOperatorException, KOperatorException)
KLAB_DECLARE_EXCEPTION(KZeroNormOperatorException, KOperatorException)
KLAB_DECLARE_EXCEPTION(KDefectOperatorException, KOperatorException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T>
class TOperator
{
public:

    TOperator();
    TOperator(klab::UInt32 n);
    TOperator(klab::UInt32 m, klab::UInt32 n);
    TOperator(const TOperator<T, TOut>& op);
    virtual ~TOperator();    

    klab::UInt32 countRows() const;
    klab::UInt32 countColumns() const;
    klab::UInt32 m() const;
    klab::UInt32 n() const;

    virtual bool    isZero();
    virtual T       sum();
    virtual T       normFrobenius();
    virtual T       squaredNormFrobenius();
    virtual T       mean();
    virtual T       variance();
    virtual T       standardDeviation();

    virtual void    apply(const arma::Col<T>& in, arma::Col<TOut>& out) = 0;
    virtual void    applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out) = 0;
    virtual void    column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void    columnAdjoint(klab::UInt32 i, arma::Col<T>& out);
    virtual void    toMatrix(arma::Mat<TOut>& out);
    virtual void    toMatrixAdjoint(arma::Mat<T>& out);


protected:

    void            resize(klab::UInt32 n);
    void            resize(klab::UInt32 m, klab::UInt32 n);


protected:

    klab::UInt32    countReferences() const;

    template<class U, class UOut>
    friend void     AddSmartPointerReference(const TOperator<U, UOut>* op);

    template<class U, class UOut>
    friend void     ReleaseSmartPointerReference(const TOperator<U, UOut>* op);


private:

    TOperator<T, TOut>& operator=(const TOperator<T, TOut>& op);


private:

    klab::UInt32    _m;
    klab::UInt32    _n;

    mutable klab::TAtomicCount<klab::UInt32>    _countReferences;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
class TOperatorSpecialisation
{
public:

    static T        ComputeSquaredFrobeniusNorm(TOperator<T, TOut>& op);


private:

    TOperatorSpecialisation();
    TOperatorSpecialisation(const TOperatorSpecialisation<T, TOut>& op);
    TOperatorSpecialisation<T, TOut>&   operator=(const TOperatorSpecialisation<T, TOut>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
class TOperatorSpecialisation<T, std::complex<TOut> >
{
public:

    static T        ComputeSquaredFrobeniusNorm(TOperator<T, std::complex<TOut> >& op);


private:

    TOperatorSpecialisation();
    TOperatorSpecialisation(const TOperatorSpecialisation<T, std::complex<TOut> >& op);
    TOperatorSpecialisation<T, std::complex<TOut> >&    operator=(const TOperatorSpecialisation<T, std::complex<TOut> >& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline TOperator<T, TOut>::TOperator() : 
_m(0), _n(0),
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline TOperator<T, TOut>::TOperator(klab::UInt32 n) : 
_m(n), _n(n),
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline TOperator<T, TOut>::TOperator(klab::UInt32 m, klab::UInt32 n) : 
_m(m), _n(n),
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline TOperator<T, TOut>::TOperator(const TOperator<T, TOut>& op) : 
_m(op._m), _n(op._n),
_countReferences(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline TOperator<T, TOut>::~TOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline klab::UInt32 TOperator<T, TOut>::countRows() const
{
    return this->m();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline klab::UInt32 TOperator<T, TOut>::countColumns() const
{
    return this->n();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline klab::UInt32 TOperator<T, TOut>::m() const
{
    return _m;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline klab::UInt32 TOperator<T, TOut>::n() const
{
    return _n;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline bool TOperator<T, TOut>::isZero()
{
    return (_m==0 || _n==0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline T TOperator<T, TOut>::sum()
{
    T ret = klab::TTypeInfo<T>::ZERO;

    arma::Col<T> x(this->n());
    x.fill(klab::TTypeInfo<T>::UNIT);

    arma::Col<T> y;
    this->apply(x, y);

    for(klab::UInt32 i=0; i<y.n_rows; ++i)
        ret += y[i];

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline T TOperator<T, TOut>::normFrobenius()
{
    return klab::Sqrt(this->squaredNormFrobenius());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline T TOperator<T, TOut>::squaredNormFrobenius()
{
    return TOperatorSpecialisation<T, TOut>::ComputeSquaredFrobeniusNorm(*this);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline T TOperator<T, TOut>::mean()
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 mn = this->m() * this->n();
    if(mn > 0)
        ret = this->sum() / static_cast<T>(mn);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline T TOperator<T, TOut>::variance()
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 mn = this->m() * this->n();
    if(mn > 0)
    {
        T mean = this->mean();
        ret = (this->squaredNormFrobenius()/static_cast<T>(mn)) - (mean*klab::Conj(mean));
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline T TOperator<T, TOut>::standardDeviation()
{
    return klab::Sqrt(this->variance());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline void TOperator<T, TOut>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    arma::Col<T> in(this->n());
    in.fill(klab::TTypeInfo<T>::ZERO);
    in[i] = klab::TTypeInfo<T>::UNIT;

    this->apply(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline void TOperator<T, TOut>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    arma::Col<TOut> in(this->m());
    in.fill(klab::TTypeInfo<T>::ZERO);
    in[i] = klab::TTypeInfo<T>::UNIT;

    this->applyAdjoint(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline void TOperator<T, TOut>::toMatrix(arma::Mat<TOut>& out)
{
    klab::UInt32 m = this->m();
    klab::UInt32 n = this->n();
    out.set_size(m, n);

    for(klab::UInt32 j=0; j<n; ++j)
    {
        arma::Col<TOut> col;
        this->column(j, col);

        klab::UInt32 i = 0;
        for(; i<m && i<col.n_rows; ++i)
            out(i, j) = col[i];

        for(; i<m; ++i)
            out(i, j) = klab::TTypeInfo<TOut>::ZERO;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline void TOperator<T, TOut>::toMatrixAdjoint(arma::Mat<T>& out)
{
    klab::UInt32 m = this->m();
    klab::UInt32 n = this->n();
    out.set_size(n, m);

    for(klab::UInt32 j=0; j<m; ++j)
    {
        arma::Col<T> col;
        this->columnAdjoint(j, col);

        klab::UInt32 i = 0;
        for(; i<n && i<col.n_rows; ++i)
            out(i, j) = col[i];

        for(; i<n; ++i)
            out(i, j) = klab::TTypeInfo<T>::ZERO;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline void TOperator<T, TOut>::resize(klab::UInt32 n)
{
    _m = n;
    _n = n;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline void TOperator<T, TOut>::resize(klab::UInt32 m, klab::UInt32 n)
{
    _m = m;
    _n = n;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline klab::UInt32 TOperator<T, TOut>::countReferences() const
{
    return _countReferences;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline void    AddSmartPointerReference(const TOperator<T, TOut>* op)
{
    if(op != 0)
        ++(op->_countReferences);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline void    ReleaseSmartPointerReference(const TOperator<T, TOut>* op)
{
    if(op != 0)
    {
        if(--(op->_countReferences) == 0)
            klab::CheckedDelete(op);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline T TOperatorSpecialisation<T, TOut>::ComputeSquaredFrobeniusNorm(TOperator<T, TOut>& op)
{
    klab::UInt32 n = op.n();

    T ret = klab::TTypeInfo<T>::ZERO;
    for(klab::UInt32 i=0; i<n; ++i)
    {
        arma::Col<T> col;
        op.column(i, col);

        ret += arma::dot(col, col);
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut>
inline T TOperatorSpecialisation<T, std::complex<TOut> >::ComputeSquaredFrobeniusNorm(TOperator<T, std::complex<TOut> >& op)
{    
    klab::UInt32 n = op.n();

    T ret = klab::TTypeInfo<T>::ZERO;
    for(klab::UInt32 i=0; i<n; ++i)
    {
        arma::Col<std::complex<TOut> > col;
        op.column(i, col);

        for(klab::UInt32 j=0; j<col.n_rows; ++j)
        {
            std::complex<TOut> value = col[j];
            ret += static_cast<T>(value.real()*value.real()) + (value.imag()*value.imag());
        }
    }

    return ret;   
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
