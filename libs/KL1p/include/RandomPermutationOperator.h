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

#ifndef KL1P_RANDOMPERMUTATIONOPERATOR_H
#define KL1P_RANDOMPERMUTATIONOPERATOR_H

#include "PermutationOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TRandomPermutationOperator : public TPermutationOperator<T>
{
public:
    
    TRandomPermutationOperator(klab::UInt32 n);
    TRandomPermutationOperator(const TRandomPermutationOperator<T>& op);
    virtual ~TRandomPermutationOperator();    


private:

    TRandomPermutationOperator();
    TRandomPermutationOperator<T>&   operator=(const TRandomPermutationOperator<T>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomPermutationOperator<T>::TRandomPermutationOperator(klab::UInt32 n) : TPermutationOperator<T>()
{
    std::vector<klab::TArrayElement<klab::DoubleReal> > indices(n);
    for(klab::UInt32 i=0; i<n; ++i)
        indices[i] = klab::TArrayElement<klab::DoubleReal>(i, klab::KRandom::Instance().generateDoubleReal());

    std::sort(indices.begin(), indices.end());

    std::vector<klab::UInt32> permutations(n);
    for(klab::UInt32 i=0; i<n; ++i)
        permutations[i] = indices[i].i();

    this->set(n, permutations);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomPermutationOperator<T>::TRandomPermutationOperator(const TRandomPermutationOperator<T>& op) : TPermutationOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomPermutationOperator<T>::~TRandomPermutationOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
