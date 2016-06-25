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

#ifndef KLAB_NAMEWAVELETFILTER_H
#define KLAB_NAMEWAVELETFILTER_H

#include "DelegateWaveletFilter.h"
#include "HaarWaveletFilter.h"
#include "DaubechiesWaveletFilter.h"
#include "BiorthogonalDaubechiesWaveletFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KNameWaveletFilterException, KWaveletFilterException)
KLAB_DECLARE_EXCEPTION(KUnknownNameWaveletFilterException, KNameWaveletFilterException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TNameWaveletFilter : public TDelegateWaveletFilter<T>
{
public:

    TNameWaveletFilter();
    TNameWaveletFilter(const klab::Char* name);
    TNameWaveletFilter(const std::string& name);
    TNameWaveletFilter(const TNameWaveletFilter<T>& filter);
    virtual ~TNameWaveletFilter();

    TNameWaveletFilter<T>&                  operator=(const TNameWaveletFilter<T>& filter);

    void                                    set(const std::string& name);
    const std::string&                      name() const;


protected:

    static TWaveletFilter<T>*               CreateWaveletFilterByName(const std::string& name);


private:

    std::string                             _name;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNameWaveletFilter<T>::TNameWaveletFilter() : TDelegateWaveletFilter<T>(),
_name()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNameWaveletFilter<T>::TNameWaveletFilter(const klab::Char* name) : TDelegateWaveletFilter<T>(TNameWaveletFilter<T>::CreateWaveletFilterByName(name)),
_name(name)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNameWaveletFilter<T>::TNameWaveletFilter(const std::string& name) : TDelegateWaveletFilter<T>(TNameWaveletFilter<T>::CreateWaveletFilterByName(name)),
_name(name)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNameWaveletFilter<T>::TNameWaveletFilter(const TNameWaveletFilter<T>& filter) : TDelegateWaveletFilter<T>(filter),
_name(filter._name)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNameWaveletFilter<T>::~TNameWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TNameWaveletFilter<T>& TNameWaveletFilter<T>::operator=(const TNameWaveletFilter<T>& filter)
{
    if(this != &filter)
    {
        TDelegateWaveletFilter<T>::operator=(filter);

        _name = filter._name;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TNameWaveletFilter<T>::set(const std::string& name)
{
    _name = name;
    this->setFilter(TNameWaveletFilter<T>::CreateWaveletFilterByName(name));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const std::string& TNameWaveletFilter<T>::name() const
{
    return _name;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TWaveletFilter<T>* TNameWaveletFilter<T>::CreateWaveletFilterByName(const std::string& name)
{
    TWaveletFilter<T>* ret = 0;

    if(klab::Equals(name, "haar", false))               ret = new THaarWaveletFilter<T>();
    else if(klab::Equals(name, "daubechies2", false))   ret = new TDaubechiesWaveletFilter<T, 2>();
    else if(klab::Equals(name, "daubechies4", false))   ret = new TDaubechiesWaveletFilter<T, 4>();
    else if(klab::Equals(name, "daubechies6", false))   ret = new TDaubechiesWaveletFilter<T, 6>();
    else if(klab::Equals(name, "daubechies8", false))   ret = new TDaubechiesWaveletFilter<T, 8>();
    else if(klab::Equals(name, "daubechies10", false))  ret = new TDaubechiesWaveletFilter<T, 10>();
    else if(klab::Equals(name, "daubechies9.7", false)) ret = new TBiorthogonalDaubechiesWaveletFilter<T, 9, 7>();
    else                                                ThrowTraceException(KUnknownNameWaveletFilterException);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
