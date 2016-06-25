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

#ifndef KL1P_RANDOMDOWNSAMPLINGOPERATOR_H
#define KL1P_RANDOMDOWNSAMPLINGOPERATOR_H

#include "DownSamplingOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TRandomDownSamplingOperator : public TDownSamplingOperator<T>
{
public:
    
    TRandomDownSamplingOperator(klab::UInt32 m, klab::UInt32 n);
    TRandomDownSamplingOperator(klab::UInt32 m, klab::UInt32 n, klab::UInt32 forceIndex);
    TRandomDownSamplingOperator(const TRandomDownSamplingOperator<T>& op);
    virtual ~TRandomDownSamplingOperator();


private:

    TRandomDownSamplingOperator();
    TRandomDownSamplingOperator<T>&     operator=(const TRandomDownSamplingOperator<T>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomDownSamplingOperator<T>::TRandomDownSamplingOperator(klab::UInt32 m, klab::UInt32 n) : TDownSamplingOperator<T>()
{
    klab::KBitArray mask;
    klab::KRandom::Instance().generateBitArray(n, m, mask);

    this->setMask(mask);
}


// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomDownSamplingOperator<T>::TRandomDownSamplingOperator(klab::UInt32 m, klab::UInt32 n, klab::UInt32 forceIndex) : TDownSamplingOperator<T>()
{
    klab::KBitArray mask;
    klab::KRandom::Instance().generateBitArray(n, m, mask);

    // Note: During tests, when the first bit of a random downsampling operation is not set when using a SRM measurement matrix, 
    //       the CS-reconstruction algorithms don't recover correctly the original signal (the first value of the recovered signal is zero).
    if(n>0 && forceIndex<n && mask.bit(forceIndex)==false)
    {
        for(klab::UInt32 i=0; i<n; ++i)
        {
            if(mask.bit(i))
            {
                mask.setBit(i, false);
                mask.setBit(forceIndex, true);
                i = n;
            }
        }
    }

    this->setMask(mask);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomDownSamplingOperator<T>::TRandomDownSamplingOperator(const TRandomDownSamplingOperator<T>& op) : TDownSamplingOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRandomDownSamplingOperator<T>::~TRandomDownSamplingOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
