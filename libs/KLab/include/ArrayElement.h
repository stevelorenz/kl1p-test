// KLab - A portable C++ collection of classes for general purpose.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KLab C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_ARRAYELEMENT_H
#define KLAB_ARRAYELEMENT_H

#include "IndexedContainerElement.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TArrayElement : public TIndexedContainerElement<T, 1>
{
public:

    TArrayElement();
    TArrayElement(klab::UInt32 i);
    TArrayElement(klab::UInt32 i, const T& value);
    TArrayElement(const TArrayElement<T>& element);
    virtual ~TArrayElement();

    TArrayElement<T>&   operator=(const TArrayElement<T>& element);

    void                setI(klab::UInt32 i);
    klab::UInt32        i() const;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TArrayElement<T>::TArrayElement() : TIndexedContainerElement<T, 1>()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TArrayElement<T>::TArrayElement(klab::UInt32 i) : TIndexedContainerElement<T, 1>()
{
    this->template setIndex<1>(i);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TArrayElement<T>::TArrayElement(klab::UInt32 i, const T& value) : TIndexedContainerElement<T, 1>(value)
{
    this->template setIndex<1>(i);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TArrayElement<T>::TArrayElement(const TArrayElement<T>& element) : TIndexedContainerElement<T, 1>(element)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TArrayElement<T>::~TArrayElement()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TArrayElement<T>& TArrayElement<T>::operator=(const TArrayElement<T>& element)
{
    if(this != &element)
        TIndexedContainerElement<T, 1>::operator=(element);    

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TArrayElement<T>::setI(klab::UInt32 i)
{
    this->template setIndex<1>(i);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TArrayElement<T>::i() const
{
    return this->template index<1>();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
