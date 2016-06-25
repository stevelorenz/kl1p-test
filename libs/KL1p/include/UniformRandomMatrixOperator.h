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

#ifndef KL1P_UNIFORMRANDOMMATRIXOPERATOR_H
#define KL1P_UNIFORMRANDOMMATRIXOPERATOR_H

#include "MatrixOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TUniformRandomMatrixOperator : public TMatrixOperator<T>
{
public:
    
    TUniformRandomMatrixOperator(klab::UInt32 m, klab::UInt32 n, const T& min=klab::TTypeInfo<T>::ZERO, const T& max=klab::TTypeInfo<T>::UNIT, bool normalize=false);
    TUniformRandomMatrixOperator(const TUniformRandomMatrixOperator<T>& op);
    virtual ~TUniformRandomMatrixOperator();    


private:

    TUniformRandomMatrixOperator();
    TUniformRandomMatrixOperator<T>&    operator=(const TUniformRandomMatrixOperator<T>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TUniformRandomMatrixOperatorSpecialisation
{
public:

    static T                GenerateUniformRandomNumber(klab::KRandom& random, const T& min, const T& max);


private:

    TUniformRandomMatrixOperatorSpecialisation();
    TUniformRandomMatrixOperatorSpecialisation(const TUniformRandomMatrixOperatorSpecialisation<T>& spec);
    TUniformRandomMatrixOperatorSpecialisation<T>&  operator=(const TUniformRandomMatrixOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TUniformRandomMatrixOperatorSpecialisation<std::complex<T> >
{
public:

    static std::complex<T>  GenerateUniformRandomNumber(klab::KRandom& random, const std::complex<T>& min, const std::complex<T>& max);


private:

    TUniformRandomMatrixOperatorSpecialisation();
    TUniformRandomMatrixOperatorSpecialisation(const TUniformRandomMatrixOperatorSpecialisation<std::complex<T> >& spec);
    TUniformRandomMatrixOperatorSpecialisation<std::complex<T> >&   operator=(const TUniformRandomMatrixOperatorSpecialisation<std::complex<T> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TUniformRandomMatrixOperator<T>::TUniformRandomMatrixOperator(klab::UInt32 m, klab::UInt32 n, const T& min, const T& max, bool normalize) : TMatrixOperator<T>()
{
    arma::Mat<T>& mat = this->matrixReference();

    mat.set_size(m, n);
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
            mat(i, j) = TUniformRandomMatrixOperatorSpecialisation<T>::GenerateUniformRandomNumber(klab::KRandom::Instance(), min, max); 
    }
    
    this->resize(m, n);
	
	if(normalize)
		this->normalize();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TUniformRandomMatrixOperator<T>::TUniformRandomMatrixOperator(const TUniformRandomMatrixOperator<T>& op) : TMatrixOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TUniformRandomMatrixOperator<T>::~TUniformRandomMatrixOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TUniformRandomMatrixOperatorSpecialisation<T>::GenerateUniformRandomNumber(klab::KRandom& random, const T& min, const T& max)
{
    return random.generate<T>(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TUniformRandomMatrixOperatorSpecialisation<std::complex<T> >::GenerateUniformRandomNumber(klab::KRandom& random, const std::complex<T>& min, const std::complex<T>& max)
{
    T real = TUniformRandomMatrixOperatorSpecialisation<T>::GenerateUniformRandomNumber(random, min.real(), max.real());
    T imag = TUniformRandomMatrixOperatorSpecialisation<T>::GenerateUniformRandomNumber(random, min.imag(), max.imag());

    return std::complex<T>(real, imag);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
