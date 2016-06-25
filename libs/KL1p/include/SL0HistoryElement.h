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

#ifndef KL1P_SL0HISTORYELEMENT_H
#define KL1P_SL0HISTORYELEMENT_H

#include <KSciInclude.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TSL0HistoryElement
{
public:

    TSL0HistoryElement();
    TSL0HistoryElement(const T& sigma);
    TSL0HistoryElement(const TSL0HistoryElement<T>& element);
    virtual ~TSL0HistoryElement();

    TSL0HistoryElement<T>& operator=(const TSL0HistoryElement<T>& element);

    const T&        sigma() const;


private:

    T               _sigma;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSL0HistoryElement<T>::TSL0HistoryElement() :
_sigma(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSL0HistoryElement<T>::TSL0HistoryElement(const T& sigma) : 
_sigma(sigma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSL0HistoryElement<T>::TSL0HistoryElement(const TSL0HistoryElement<T>& element) :
_sigma(element._sigma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSL0HistoryElement<T>::~TSL0HistoryElement()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSL0HistoryElement<T>& TSL0HistoryElement<T>::operator=(const TSL0HistoryElement<T>& element)
{
    if(this != &element)
    {
        _sigma = element._sigma;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TSL0HistoryElement<T>::sigma() const
{
    return _sigma;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
