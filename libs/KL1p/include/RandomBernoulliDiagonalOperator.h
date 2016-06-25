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

#ifndef KL1P_RANDOMBERNOULLIDIAGONALOPERATOR_H
#define KL1P_RANDOMBERNOULLIDIAGONALOPERATOR_H

#include "DiagonalOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TRandomBernoulliDiagonalOperator : public TDiagonalOperator<T>
{
public:

    TRandomBernoulliDiagonalOperator(klab::UInt32 n);
    TRandomBernoulliDiagonalOperator(const TRandomBernoulliDiagonalOperator<T>& op);
    virtual ~TRandomBernoulliDiagonalOperator();    


private:

    TRandomBernoulliDiagonalOperator();
    TRandomBernoulliDiagonalOperator<T>&    operator=(const TRandomBernoulliDiagonalOperator<T>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomBernoulliDiagonalOperator<T>::TRandomBernoulliDiagonalOperator(klab::UInt32 n) : TDiagonalOperator<T>()
{
    klab::KBitArray mask;
    klab::KRandom::Instance().generateBitArray(n, n>>1, mask);

    arma::Col<T> diag(n);
    for(klab::UInt32 i=0; i<mask.size(); ++i)
        diag[i] = mask[i] ? -klab::TTypeInfo<T>::UNIT : klab::TTypeInfo<T>::UNIT;

    this->setDiagonal(diag);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomBernoulliDiagonalOperator<T>::TRandomBernoulliDiagonalOperator(const TRandomBernoulliDiagonalOperator<T>& op) : TDiagonalOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomBernoulliDiagonalOperator<T>::~TRandomBernoulliDiagonalOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
