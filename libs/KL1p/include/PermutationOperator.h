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

#ifndef KL1P_PERMUTATIONOPERATOR_H
#define KL1P_PERMUTATIONOPERATOR_H

#include "SamplingOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TPermutationOperator : public TSamplingOperator<T>
{
public:
   
    TPermutationOperator(const std::vector<klab::UInt32>& permutations);
    TPermutationOperator(const TPermutationOperator<T>& op);
    virtual ~TPermutationOperator();    


protected:

    TPermutationOperator();


private:

    TPermutationOperator<T>&    operator=(const TPermutationOperator<T>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TPermutationOperator<T>::TPermutationOperator() : TSamplingOperator<T>()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TPermutationOperator<T>::TPermutationOperator(const std::vector<klab::UInt32>& permutations) : TSamplingOperator<T>(static_cast<klab::UInt32>(permutations.size()), permutations)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TPermutationOperator<T>::TPermutationOperator(const TPermutationOperator<T>& op) : TSamplingOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TPermutationOperator<T>::~TPermutationOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
