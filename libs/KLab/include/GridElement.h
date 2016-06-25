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

#ifndef KLAB_GRIDELEMENT_H
#define KLAB_GRIDELEMENT_H

#include "IndexedContainerElement.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGridElement : public TIndexedContainerElement<T, 2>
{
public:

    TGridElement();
    TGridElement(klab::UInt32 i, klab::UInt32 j);
    TGridElement(klab::UInt32 i, klab::UInt32 j, const T& value);
    TGridElement(const TGridElement<T>& element);
    virtual ~TGridElement();

    TGridElement<T>&    operator=(const TGridElement<T>& element);

    void                setI(klab::UInt32 i);
    void                setJ(klab::UInt32 j);

    klab::UInt32        i() const;
    klab::UInt32        j() const;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGridElement<T>::TGridElement() : TIndexedContainerElement<T, 2>()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGridElement<T>::TGridElement(klab::UInt32 i, klab::UInt32 j) : TIndexedContainerElement<T, 2>()
{
    this->template setIndex<1>(i);
    this->template setIndex<2>(j);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGridElement<T>::TGridElement(klab::UInt32 i, klab::UInt32 j, const T& value) : TIndexedContainerElement<T, 2>(value)
{
    this->template setIndex<1>(i);
    this->template setIndex<2>(j);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGridElement<T>::TGridElement(const TGridElement<T>& element) : TIndexedContainerElement<T, 2>(element)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGridElement<T>::~TGridElement()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGridElement<T>& TGridElement<T>::operator=(const TGridElement<T>& element)
{
    if(this != &element)
        TIndexedContainerElement<T, 2>::operator=(element);    

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TGridElement<T>::setI(klab::UInt32 i)
{
    this->template setIndex<1>(i);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TGridElement<T>::setJ(klab::UInt32 j)
{
    this->template setIndex<2>(j);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGridElement<T>::i() const
{
    return this->template index<1>();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGridElement<T>::j() const
{
    return this->template index<2>();
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
