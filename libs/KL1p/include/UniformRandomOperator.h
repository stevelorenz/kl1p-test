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

#ifndef KL1P_UNIFORMRANDOMOPERATOR_H
#define KL1P_UNIFORMRANDOMOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TUniformRandomOperator : public TOperator<T>
{
public:

    TUniformRandomOperator(klab::UInt32 m, klab::UInt32 n, const T& min=klab::TTypeInfo<T>::ZERO, const T& max=klab::TTypeInfo<T>::UNIT);
    TUniformRandomOperator(const TUniformRandomOperator<T>& op);
    virtual ~TUniformRandomOperator();    

    const T&                    min() const;
    const T&                    max() const;

    virtual void                apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void                applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);

    virtual void                column(klab::UInt32 i, arma::Col<T>& out);
    virtual void                columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TUniformRandomOperator();
    TUniformRandomOperator<T>&  operator=(const TUniformRandomOperator<T>& op);


private:

    std::vector<klab::UInt32>   _seeds;

    T                           _min;
    T                           _max;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TUniformRandomOperatorSpecialisation
{
public:

    static T                GenerateUniformRandomNumber(klab::KRandom& random, const T& min, const T& max);


private:

    TUniformRandomOperatorSpecialisation();
    TUniformRandomOperatorSpecialisation(const TUniformRandomOperatorSpecialisation<T>& spec);
    TUniformRandomOperatorSpecialisation<T>&    operator=(const TUniformRandomOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TUniformRandomOperatorSpecialisation<std::complex<T> >
{
public:

    static std::complex<T>  GenerateUniformRandomNumber(klab::KRandom& random, const std::complex<T>& min, const std::complex<T>& max);


private:

    TUniformRandomOperatorSpecialisation();
    TUniformRandomOperatorSpecialisation(const TUniformRandomOperatorSpecialisation<std::complex<T> >& spec);
    TUniformRandomOperatorSpecialisation<std::complex<T> >& operator=(const TUniformRandomOperatorSpecialisation<std::complex<T> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TUniformRandomOperator<T>::TUniformRandomOperator(klab::UInt32 m, klab::UInt32 n, const T& min, const T& max) : TOperator<T>(m,n),
_seeds(m),
_min(min), _max(max)
{
    for(klab::UInt32 i=0; i<m; ++i)
        _seeds[i] = klab::KRandom::Instance().generateUInt32();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TUniformRandomOperator<T>::TUniformRandomOperator(const TUniformRandomOperator<T>& op) : TOperator<T>(op),
_seeds(op._seeds),
_min(op._min), _max(op._max)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TUniformRandomOperator<T>::~TUniformRandomOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TUniformRandomOperator<T>::min() const
{
    return _min;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TUniformRandomOperator<T>::max() const
{
    return _max;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TUniformRandomOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());    

    klab::UInt32 m = this->m();
    klab::UInt32 n = this->n();

    out.set_size(m);
    out.fill(klab::TTypeInfo<T>::ZERO);

    klab::KRandom random;
    for(klab::UInt32 i=0; i<m; ++i)
    {
        random.setSeed(_seeds[i]);
        for(klab::UInt32 j=0; j<n; ++j)
            out[i] += in[j] * TUniformRandomOperatorSpecialisation<T>::GenerateUniformRandomNumber(random, _min, _max); 
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TUniformRandomOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    klab::UInt32 m = this->m();
    klab::UInt32 n = this->n();

    out.set_size(n);
    out.fill(klab::TTypeInfo<T>::ZERO);
    
    klab::KRandom random;
    for(klab::UInt32 i=0; i<m; ++i)
    {
        random.setSeed(_seeds[i]);
        for(klab::UInt32 j=0; j<n; ++j)
            out[j] += in[i] * klab::Conj(TUniformRandomOperatorSpecialisation<T>::GenerateUniformRandomNumber(random, _min, _max)); 
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TUniformRandomOperator<T>::column(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    klab::UInt32 m = this->m();

    out.set_size(m);
    out.fill(klab::TTypeInfo<T>::ZERO);

    klab::KRandom random;
    for(klab::UInt32 i2=0; i2<m; ++i2)
    {
        random.setSeed(_seeds[i2]);
        for(klab::UInt32 j=0; j<=i; ++j)
        {
            T value = TUniformRandomOperatorSpecialisation<T>::GenerateUniformRandomNumber(random, _min, _max); 
            if(j == i)
                out[i2] = value; 
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TUniformRandomOperator<T>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    klab::UInt32 n = this->n();

    out.set_size(n);
    out.fill(klab::TTypeInfo<T>::ZERO);

    klab::KRandom random(_seeds[i]);
    for(klab::UInt32 j=0; j<n; ++j)
        out[j] = klab::Conj(TUniformRandomOperatorSpecialisation<T>::GenerateUniformRandomNumber(random, _min, _max)); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TUniformRandomOperatorSpecialisation<T>::GenerateUniformRandomNumber(klab::KRandom& random, const T& min, const T& max)
{
    return random.generate<T>(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TUniformRandomOperatorSpecialisation<std::complex<T> >::GenerateUniformRandomNumber(klab::KRandom& random, const std::complex<T>& min, const std::complex<T>& max)
{
    T real = TUniformRandomOperatorSpecialisation<T>::GenerateUniformRandomNumber(random, min.real(), max.real());
    T imag = TUniformRandomOperatorSpecialisation<T>::GenerateUniformRandomNumber(random, min.imag(), max.imag());

    return std::complex<T>(real, imag);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
