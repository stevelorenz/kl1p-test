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

#ifndef KLAB_INDEXEDCONTAINERELEMENT_H
#define KLAB_INDEXEDCONTAINERELEMENT_H

#include "TemplateUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
class TIndexedContainerElement
{
public:

    TIndexedContainerElement();
    TIndexedContainerElement(const T& value);
    TIndexedContainerElement(const TIndexedContainerElement<T, Dim>& element);
    virtual ~TIndexedContainerElement();

    TIndexedContainerElement<T, Dim>&   operator=(const TIndexedContainerElement<T, Dim>& element);
    bool                                operator<(const TIndexedContainerElement<T, Dim>& right) const;
	bool                                operator>(const TIndexedContainerElement<T, Dim>& right) const;

    template<klab::UInt32 I>
    void                setIndex(klab::UInt32 index);
    void                setValue(const T& value);

    template<klab::UInt32 I>
    klab::UInt32        index() const;
    const T&            value() const;


private:

    template<bool Condition, klab::UInt32 I>
    struct TINDEXEDCONTAINERELEMENT_ASSIGN_INDEXESARRAY_IF
    {
        static inline void  Do(klab::UInt32* indexes, klab::UInt32 index) {indexes[I-1] = index;};
    };

    template<klab::UInt32 I>
    struct TINDEXEDCONTAINERELEMENT_ASSIGN_INDEXESARRAY_IF<false, I>
    {
        static inline void  Do(klab::UInt32* indexes, klab::UInt32 index) {};
    };

    template<bool Condition, klab::UInt32 I>
    struct TINDEXEDCONTAINERELEMENT_GETINDEX_IF
    {
        static inline klab::UInt32  Do(const klab::UInt32* indexes) {return indexes[I-1];};
    };

    template<klab::UInt32 I>
    struct TINDEXEDCONTAINERELEMENT_GETINDEX_IF<false, I>
    {
        static inline klab::UInt32  Do(const klab::UInt32* indexes) {return 0;};
    };


private:

    klab::UInt32    _indexes[Dim];
    T               _value;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
inline TIndexedContainerElement<T, Dim>::TIndexedContainerElement() : 
_value()
{
    klab::FILLARRAY<klab::UInt32, Dim>::Do(_indexes, 0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
inline TIndexedContainerElement<T, Dim>::TIndexedContainerElement(const T& value) : 
_value(value)
{
    klab::FILLARRAY<klab::UInt32, Dim>::Do(_indexes, 0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
inline TIndexedContainerElement<T, Dim>::TIndexedContainerElement(const TIndexedContainerElement<T, Dim>& element) : 
_value(element._value)
{
    klab::COPYARRAY<klab::UInt32, Dim>::Do(element._indexes, _indexes);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
inline TIndexedContainerElement<T, Dim>::~TIndexedContainerElement()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
inline TIndexedContainerElement<T, Dim>& TIndexedContainerElement<T, Dim>::operator=(const TIndexedContainerElement<T, Dim>& element) 
{
    if(this != &element)
    {
        klab::COPYARRAY<klab::UInt32, Dim>::Do(element._indexes, _indexes);

        _value = element._value;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
inline bool TIndexedContainerElement<T, Dim>::operator<(const TIndexedContainerElement<T, Dim>& right) const
{
    return (_value < right._value);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
inline bool TIndexedContainerElement<T, Dim>::operator>(const TIndexedContainerElement<T, Dim>& right) const
{
    return (_value > right._value);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
template<klab::UInt32 I>
inline void TIndexedContainerElement<T, Dim>::setIndex(klab::UInt32 index)
{
    TINDEXEDCONTAINERELEMENT_ASSIGN_INDEXESARRAY_IF<(I>0 && I<=Dim), I>::Do(_indexes, index);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
inline void TIndexedContainerElement<T, Dim>::setValue(const T& value)
{
    _value = value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
template<klab::UInt32 I>
inline klab::UInt32 TIndexedContainerElement<T, Dim>::index() const
{
    return TINDEXEDCONTAINERELEMENT_GETINDEX_IF<(I>0 && I<=Dim), I>::Do(_indexes);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, klab::UInt32 Dim>
inline const T& TIndexedContainerElement<T, Dim>::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
