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

#ifndef KL1P_NORMALRANDOMMATRIXOPERATOR_H
#define KL1P_NORMALRANDOMMATRIXOPERATOR_H

#include "MatrixOperator.h"

namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TNormalRandomMatrixOperator : public TMatrixOperator<T>
{
public:

    TNormalRandomMatrixOperator(klab::UInt32 m, klab::UInt32 n, const T& mean=klab::TTypeInfo<T>::ZERO, const T& deviation=klab::TTypeInfo<T>::UNIT, bool normalize=false);
    TNormalRandomMatrixOperator(const TNormalRandomMatrixOperator<T>& op);
    virtual ~TNormalRandomMatrixOperator();

    virtual bool    isZero();
    virtual T       sum();
    virtual T       normFrobenius();
    virtual T       squaredNormFrobenius();
    virtual T       mean();
    virtual T       variance();


private:

    TNormalRandomMatrixOperator();
    TNormalRandomMatrixOperator<T>&     operator=(const TNormalRandomMatrixOperator<T>& op);


private:

    T               _mean;
    T               _deviation;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TNormalRandomMatrixOperatorSpecialisation
{
public:

    static T                GenerateNormalRandomNumber(klab::KRandom& random, const T& mean, const T& deviation);


private:

    TNormalRandomMatrixOperatorSpecialisation();
    TNormalRandomMatrixOperatorSpecialisation(const TNormalRandomMatrixOperatorSpecialisation<T>& spec);
    TNormalRandomMatrixOperatorSpecialisation<T>&   operator=(const TNormalRandomMatrixOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TNormalRandomMatrixOperatorSpecialisation<std::complex<T> >
{
public:

    static std::complex<T>  GenerateNormalRandomNumber(klab::KRandom& random, const std::complex<T>& mean, const std::complex<T>& deviation);


private:

    TNormalRandomMatrixOperatorSpecialisation();
    TNormalRandomMatrixOperatorSpecialisation(const TNormalRandomMatrixOperatorSpecialisation<std::complex<T> >& spec);
    TNormalRandomMatrixOperatorSpecialisation<std::complex<T> >&    operator=(const TNormalRandomMatrixOperatorSpecialisation<std::complex<T> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNormalRandomMatrixOperator<T>::TNormalRandomMatrixOperator(klab::UInt32 m, klab::UInt32 n, const T& mean, const T& deviation, bool normalize) : TMatrixOperator<T>(),
_mean(mean), _deviation(deviation)
{
    arma::Mat<T>& mat = this->matrixReference();

    mat.set_size(m, n);
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
            mat(i, j) = TNormalRandomMatrixOperatorSpecialisation<T>::GenerateNormalRandomNumber(klab::KRandom::Instance(), mean, deviation);
    }

    // mat.save("./sensingMatrix.csv", arma::csv_ascii);

    this->resize(m, n);

    if(normalize)
        this->normalize();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNormalRandomMatrixOperator<T>::TNormalRandomMatrixOperator(const TNormalRandomMatrixOperator<T>& op) : TMatrixOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNormalRandomMatrixOperator<T>::~TNormalRandomMatrixOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TNormalRandomMatrixOperator<T>::isZero()
{
    return (this->m()==0 || this->n()==0 || (klab::Equals(_mean, klab::TTypeInfo<T>::ZERO) && klab::Equals(_deviation, klab::TTypeInfo<T>::ZERO)));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomMatrixOperator<T>::sum()
{
	if(this->isNormalized())
	{
		return TMatrixOperator<T>::sum();
	}
	else
	{
		T ret = klab::TTypeInfo<T>::ZERO;

		klab::UInt32 mn = this->m() * this->n();
		if(mn > 0)
			ret = _mean * static_cast<T>(mn);

		return ret;
	}
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomMatrixOperator<T>::normFrobenius()
{
    return klab::Sqrt(this->squaredNormFrobenius());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomMatrixOperator<T>::squaredNormFrobenius()
{
	if(this->isNormalized())
	{
		return TMatrixOperator<T>::squaredNormFrobenius();
	}
	else
	{
		T ret = klab::TTypeInfo<T>::ZERO;

		klab::UInt32 mn = this->m() * this->n();
		if(mn > 0)
			ret = (this->variance() + (klab::Conj(_mean)*_mean)) * static_cast<T>(mn);

		return ret;
	}
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomMatrixOperator<T>::mean()
{
	if(this->isNormalized())	return TMatrixOperator<T>::mean();
	else						return _mean;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomMatrixOperator<T>::variance()
{
	if(this->isNormalized())	return TMatrixOperator<T>::variance();
	else						return (klab::Conj(_deviation)*_deviation);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TNormalRandomMatrixOperatorSpecialisation<T>::GenerateNormalRandomNumber(klab::KRandom& random, const T& mean, const T& deviation)
{
    T u1 = random.generate<T>(klab::TTypeInfo<T>::ZERO, klab::TTypeInfo<T>::UNIT);
    T u2 = random.generate<T>(klab::TTypeInfo<T>::ZERO, klab::TTypeInfo<T>::UNIT);

    return (mean + (deviation * (klab::Sqrt(-2.0*klab::Log(u1))*klab::Cos(2.0*klab::PI*u2))));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TNormalRandomMatrixOperatorSpecialisation<std::complex<T> >::GenerateNormalRandomNumber(klab::KRandom& random, const std::complex<T>& mean, const std::complex<T>& deviation)
{
    T real = TNormalRandomMatrixOperatorSpecialisation<T>::GenerateNormalRandomNumber(random, mean.real(), deviation.real());
    T imag = TNormalRandomMatrixOperatorSpecialisation<T>::GenerateNormalRandomNumber(random, mean.imag(), deviation.imag());

    return std::complex<T>(real, imag);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
