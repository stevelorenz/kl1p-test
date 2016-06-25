// KSci - A portable C++ numerical analysis library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KSci C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_STATICWAVELETFILTER_H
#define KLAB_STATICWAVELETFILTER_H

#include "WaveletFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
class TStaticWaveletFilter : public TWaveletFilter<T>
{
public:

    TStaticWaveletFilter();
    TStaticWaveletFilter(const TStaticWaveletFilter<T, N>& filter);
    virtual ~TStaticWaveletFilter();

    TStaticWaveletFilter<T, N>& operator=(const TStaticWaveletFilter<T, N>& filter);

    virtual klab::UInt32        waveLength() const;
    virtual const T&            h0(klab::UInt32 i) const;
    virtual const T&            h1(klab::UInt32 i) const;
    virtual const T&            rh0(klab::UInt32 i) const;
    virtual const T&            rh1(klab::UInt32 i) const;


protected:

    T   _h0[N];    
    T   _h1[N];
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline TStaticWaveletFilter<T, N>::TStaticWaveletFilter() : TWaveletFilter<T>()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline TStaticWaveletFilter<T, N>::TStaticWaveletFilter(const TStaticWaveletFilter<T, N>& filter) : TWaveletFilter<T>(filter)
{
    klab::COPYARRAY<T, N>::Do(filter._h0, _h0);
    klab::COPYARRAY<T, N>::Do(filter._h1, _h1);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline TStaticWaveletFilter<T, N>::~TStaticWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline TStaticWaveletFilter<T, N>& TStaticWaveletFilter<T, N>::operator=(const TStaticWaveletFilter<T, N>& filter)
{
    if(this != &filter)
    {
        TWaveletFilter<T>::operator=(filter);

        klab::COPYARRAY<T, N>::Do(filter._h0, _h0);
        klab::COPYARRAY<T, N>::Do(filter._h1, _h1);
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline klab::UInt32 TStaticWaveletFilter<T, N>::waveLength() const
{
    return N;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline const T& TStaticWaveletFilter<T, N>::h0(klab::UInt32 i) const
{
    if(i < N)   return _h0[i];
    else        return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline const T& TStaticWaveletFilter<T, N>::h1(klab::UInt32 i) const
{
    if(i < N)   return _h1[i];
    else        return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline const T& TStaticWaveletFilter<T, N>::rh0(klab::UInt32 i) const
{
    if(i < N)   return _h0[i];
    else        return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 N>
inline const T& TStaticWaveletFilter<T, N>::rh1(klab::UInt32 i) const
{
    if(i < N)   return _h1[i];
    else        return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
