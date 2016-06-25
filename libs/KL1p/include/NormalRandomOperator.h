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

#ifndef KL1P_NORMALRANDOMOPERATOR_H
#define KL1P_NORMALRANDOMOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TNormalRandomOperator : public TOperator<T>
{
public:

    TNormalRandomOperator(klab::UInt32 m, klab::UInt32 n, const T& mean=klab::TTypeInfo<T>::ZERO, const T& deviation=klab::TTypeInfo<T>::UNIT);
    TNormalRandomOperator(const TNormalRandomOperator<T>& op);
    virtual ~TNormalRandomOperator();    

    virtual bool    isZero();
    virtual T       sum();
    virtual T       normFrobenius();
    virtual T       squaredNormFrobenius();
    virtual T       mean();
    virtual T       variance();

    virtual void    apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void    applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);

    virtual void    column(klab::UInt32 i, arma::Col<T>& out);
    virtual void    columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TNormalRandomOperator();
    TNormalRandomOperator<T>&   operator=(const TNormalRandomOperator<T>& op);


private:

    std::vector<klab::UInt32>   _seeds;

    T                           _mean;
    T                           _deviation;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TNormalRandomOperatorSpecialisation
{
public:

    static T                GenerateNormalRandomNumber(klab::KRandom& random, const T& mean, const T& deviation);


private:

    TNormalRandomOperatorSpecialisation();
    TNormalRandomOperatorSpecialisation(const TNormalRandomOperatorSpecialisation<T>& spec);
    TNormalRandomOperatorSpecialisation<T>&     operator=(const TNormalRandomOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TNormalRandomOperatorSpecialisation<std::complex<T> >
{
public:

    static std::complex<T>  GenerateNormalRandomNumber(klab::KRandom& random, const std::complex<T>& mean, const std::complex<T>& deviation);


private:

    TNormalRandomOperatorSpecialisation();
    TNormalRandomOperatorSpecialisation(const TNormalRandomOperatorSpecialisation<std::complex<T> >& spec);
    TNormalRandomOperatorSpecialisation<std::complex<T> >&  operator=(const TNormalRandomOperatorSpecialisation<std::complex<T> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNormalRandomOperator<T>::TNormalRandomOperator(klab::UInt32 m, klab::UInt32 n, const T& mean, const T& deviation) : TOperator<T>(m, n),
_seeds(m),
_mean(mean), _deviation(deviation)
{
    for(klab::UInt32 i=0; i<m; ++i)
        _seeds[i] = klab::KRandom::Instance().generateUInt32();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNormalRandomOperator<T>::TNormalRandomOperator(const TNormalRandomOperator<T>& op) : TOperator<T>(op),
_seeds(op._seeds),
_mean(op._mean), _deviation(op._deviation)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNormalRandomOperator<T>::~TNormalRandomOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TNormalRandomOperator<T>::isZero()
{
    return (this->m()==0 || this->n()==0 || (klab::Equals(_mean, klab::TTypeInfo<T>::ZERO) && klab::Equals(_deviation, klab::TTypeInfo<T>::ZERO)));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomOperator<T>::sum()
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 mn = this->m() * this->n();
    if(mn > 0)
        ret = _mean * static_cast<T>(mn);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomOperator<T>::normFrobenius()
{
    return klab::Sqrt(this->squaredNormFrobenius());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomOperator<T>::squaredNormFrobenius()
{
    T ret = klab::TTypeInfo<T>::ZERO;

    klab::UInt32 mn = this->m() * this->n();
    if(mn > 0)
        ret = (this->variance() + (klab::Conj(_mean)*_mean)) * static_cast<T>(mn);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomOperator<T>::mean()
{
    return _mean;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomOperator<T>::variance()
{
    return (klab::Conj(_deviation)*_deviation);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TNormalRandomOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
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
            out[i] += in[j] * TNormalRandomOperatorSpecialisation<T>::GenerateNormalRandomNumber(random, _mean, _deviation);   
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TNormalRandomOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
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
            out[j] += in[i] * klab::Conj(TNormalRandomOperatorSpecialisation<T>::GenerateNormalRandomNumber(random, _mean, _deviation));   
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TNormalRandomOperator<T>::column(klab::UInt32 i, arma::Col<T>& out)
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
            T value = TNormalRandomOperatorSpecialisation<T>::GenerateNormalRandomNumber(random, _mean, _deviation);
            if(j == i)
                out[i2] = value;   
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TNormalRandomOperator<T>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    klab::UInt32 n = this->n();

    out.set_size(n);
    out.fill(klab::TTypeInfo<T>::ZERO);

    klab::KRandom random(_seeds[i]);
    for(klab::UInt32 j=0; j<n; ++j)
        out[j] = klab::Conj(TNormalRandomOperatorSpecialisation<T>::GenerateNormalRandomNumber(random, _mean, _deviation));        
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomOperatorSpecialisation<T>::GenerateNormalRandomNumber(klab::KRandom& random, const T& mean, const T& deviation)
{
    T u1 = random.generate<T>(klab::TTypeInfo<T>::ZERO, klab::TTypeInfo<T>::UNIT);
    T u2 = random.generate<T>(klab::TTypeInfo<T>::ZERO, klab::TTypeInfo<T>::UNIT);

    return (mean + (deviation * (klab::Sqrt(-2.0*klab::Log(u1))*klab::Cos(2.0*klab::PI*u2))));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TNormalRandomOperatorSpecialisation<std::complex<T> >::GenerateNormalRandomNumber(klab::KRandom& random, const std::complex<T>& mean, const std::complex<T>& deviation)
{
    T real = TNormalRandomOperatorSpecialisation<T>::GenerateNormalRandomNumber(random, mean.real(), deviation.real());
    T imag = TNormalRandomOperatorSpecialisation<T>::GenerateNormalRandomNumber(random, mean.imag(), deviation.imag());

    return std::complex<T>(real, imag);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
