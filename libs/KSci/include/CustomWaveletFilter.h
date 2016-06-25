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

#ifndef KLAB_CUSTOMWAVELETFILTER_H
#define KLAB_CUSTOMWAVELETFILTER_H

#include "WaveletFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KCustomWaveletFilterException, KWaveletFilterException)
KLAB_DECLARE_EXCEPTION(KOutOfBoundCustomWaveletFilterException, KCustomWaveletFilterException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TCustomWaveletFilter : public TWaveletFilter<T>
{
public:

    TCustomWaveletFilter();
    TCustomWaveletFilter(klab::UInt32 waveLength);
    TCustomWaveletFilter(const std::vector<T>& h0, const std::vector<T>& h1);
    TCustomWaveletFilter(const TCustomWaveletFilter<T>& filter);
    virtual ~TCustomWaveletFilter();

    TCustomWaveletFilter<T>&        operator=(const TCustomWaveletFilter<T>& filter);

    void                            resize(klab::UInt32 waveLength);
    void                            set(const std::vector<T>& h0, const std::vector<T>& h1);
    void                            setH0(const std::vector<T>& h0);
    void                            setH1(const std::vector<T>& h1);
    void                            setH0Coefficient(klab::UInt32 i, const T& coefficient);
    void                            setH1Coefficient(klab::UInt32 i, const T& coefficient);

    virtual klab::UInt32            waveLength() const;
    virtual const T&                h0(klab::UInt32 i) const;
    virtual const T&                h1(klab::UInt32 i) const;
    virtual const T&                rh0(klab::UInt32 i) const;
    virtual const T&                rh1(klab::UInt32 i) const;


private:

    std::vector<T>                  _h0;  
    std::vector<T>                  _h1;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCustomWaveletFilter<T>::TCustomWaveletFilter() : TWaveletFilter<T>(),
_h0(), _h1()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCustomWaveletFilter<T>::TCustomWaveletFilter(klab::UInt32 waveLength) : TWaveletFilter<T>(),
_h0(waveLength, klab::TTypeInfo<T>::ZERO), _h1(waveLength, klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCustomWaveletFilter<T>::TCustomWaveletFilter(const std::vector<T>& h0, const std::vector<T>& h1) : TWaveletFilter<T>(),
_h0(h0), _h1(h1)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCustomWaveletFilter<T>::TCustomWaveletFilter(const TCustomWaveletFilter<T>& filter) : TWaveletFilter<T>(),
_h0(filter._h0), _h1(filter._h1)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCustomWaveletFilter<T>::~TCustomWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCustomWaveletFilter<T>&  TCustomWaveletFilter<T>::operator=(const TCustomWaveletFilter<T>& filter)
{
    if(this != &filter)
    {
        TWaveletFilter<T>::operator=(filter);

        _h0 = filter._h0;
        _h1 = filter._h1;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void  TCustomWaveletFilter<T>::resize(klab::UInt32 waveLength)
{
    _h0.resize(waveLength, klab::TTypeInfo<T>::ZERO);
    _h1.resize(waveLength, klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void  TCustomWaveletFilter<T>::set(const std::vector<T>& h0, const std::vector<T>& h1)
{
    _h0 = h0;
    _h1 = h1;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void  TCustomWaveletFilter<T>::setH0(const std::vector<T>& h0)
{
    _h0 = h0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void  TCustomWaveletFilter<T>::setH1(const std::vector<T>& h1)
{
    _h1 = h1;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void  TCustomWaveletFilter<T>::setH0Coefficient(klab::UInt32 i, const T& coefficient)
{
    ThrowTraceExceptionIf(KOutOfBoundCustomWaveletFilterException, i>=static_cast<klab::UInt32>(_h0.size()));

    _h0[i] = coefficient;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void  TCustomWaveletFilter<T>::setH1Coefficient(klab::UInt32 i, const T& coefficient)
{
    ThrowTraceExceptionIf(KOutOfBoundCustomWaveletFilterException, i>=static_cast<klab::UInt32>(_h1.size()));

    _h1[i] = coefficient;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32  TCustomWaveletFilter<T>::waveLength() const
{
    return klab::Max(static_cast<klab::UInt32>(_h0.size()), static_cast<klab::UInt32>(_h1.size()));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T&  TCustomWaveletFilter<T>::h0(klab::UInt32 i) const
{
    if(i < static_cast<klab::UInt32>(_h0.size()))   return _h0[i];
    else                                            return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T&  TCustomWaveletFilter<T>::h1(klab::UInt32 i) const
{
    if(i < static_cast<klab::UInt32>(_h1.size()))   return _h1[i];
    else                                            return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T&  TCustomWaveletFilter<T>::rh0(klab::UInt32 i) const
{
    if(i < static_cast<klab::UInt32>(_h0.size()))   return _h0[i];
    else                                            return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T&  TCustomWaveletFilter<T>::rh1(klab::UInt32 i) const
{
    if(i < static_cast<klab::UInt32>(_h1.size()))   return _h1[i];
    else                                            return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
