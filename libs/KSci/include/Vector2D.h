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

#ifndef KLAB_VECTOR2D_H
#define KLAB_VECTOR2D_H

#include "MathsUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TVector2D
{
public:

    TVector2D();
    TVector2D(const T& x, const T& y);
    TVector2D(const TVector2D<T>& vector);
    virtual ~TVector2D();

    TVector2D<T>&   operator=(const TVector2D<T>& vector);

    void            clear();

    void            set(const T& x, const T& y);
    void            setX(const T& x);
    void            setY(const T& y);

    const T&        x() const;
    const T&        y() const;


private:

    T               _x;
    T               _y;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     Equals(const TVector2D<T>& left, const TVector2D<T>& right, T epsilon=klab::TTypeInfo<T>::EPSILON)
{
    return (klab::Equals(left.x(), right.x(), epsilon) && klab::Equals(left.y(), right.y(), epsilon)); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector2DOnX_LessThan(const TVector2D<T>& left, const TVector2D<T>& right)
{
    return (left.x() < right.x());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector2DOnY_LessThan(const TVector2D<T>& left, const TVector2D<T>& right)
{
    return (left.y() < right.y());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector2DOnX_GreaterThan(const TVector2D<T>& left, const TVector2D<T>& right)
{
    return (left.x() > right.x());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector2DOnY_GreaterThan(const TVector2D<T>& left, const TVector2D<T>& right)
{
    return (left.y() > right.y());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector2D<T>::TVector2D() : 
_x(klab::TTypeInfo<T>::ZERO), _y(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector2D<T>::TVector2D(const T& x, const T& y) : 
_x(x), _y(y)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector2D<T>::TVector2D(const TVector2D<T>& vector) : 
_x(vector._x), _y(vector._y)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector2D<T>::~TVector2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector2D<T>& TVector2D<T>::operator=(const TVector2D<T>& vector)
{
    if(this != &vector)
    {
        _x = vector._x;
        _y = vector._y;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TVector2D<T>::clear()
{
    _x = klab::TTypeInfo<T>::ZERO;
    _y = klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TVector2D<T>::set(const T& x, const T& y)
{
    _x = x;
    _y = y;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TVector2D<T>::setX(const T& x)
{
    _x = x;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TVector2D<T>::setY(const T& y)
{
    _y = y;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TVector2D<T>::x() const
{
    return _x;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TVector2D<T>::y() const
{
    return _y;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
