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

#ifndef KL1P_DOWNSAMPLINGOPERATOR_H
#define KL1P_DOWNSAMPLINGOPERATOR_H

#include "SamplingOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDownSamplingOperator : public TSamplingOperator<T>
{
public:

    TDownSamplingOperator(klab::UInt32 n, const kl1p::KSamplingIndicesArray& indices);
    TDownSamplingOperator(const klab::KBitArray& mask);
    TDownSamplingOperator(const TDownSamplingOperator<T>& op);
    virtual ~TDownSamplingOperator();    


protected:

    TDownSamplingOperator();    

     void   setMask(const klab::KBitArray& mask);


private:

    TDownSamplingOperator<T>&   operator=(const TDownSamplingOperator<T>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDownSamplingOperator<T>::TDownSamplingOperator() : TSamplingOperator<T>()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDownSamplingOperator<T>::TDownSamplingOperator(klab::UInt32 n, const kl1p::KSamplingIndicesArray& indices) : TSamplingOperator<T>(n, indices)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDownSamplingOperator<T>::TDownSamplingOperator(const klab::KBitArray& mask) : TSamplingOperator<T>()
{
    this->setMask(mask);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDownSamplingOperator<T>::TDownSamplingOperator(const TDownSamplingOperator<T>& op) : TSamplingOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDownSamplingOperator<T>::~TDownSamplingOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDownSamplingOperator<T>::setMask(const klab::KBitArray& mask)
{
    klab::UInt32 n = mask.size();

    kl1p::KSamplingIndicesArray indices;
    for(klab::UInt32 i=0; i<n; ++i)
    {
        if(mask[i])
            indices.push_back(i);
    }

    this->set(n, indices);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
