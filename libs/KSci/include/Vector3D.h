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

#ifndef KLAB_VECTOR3D_H
#define KLAB_VECTOR3D_H

#include "Vector2D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TVector3D
{
public:

    TVector3D();
    TVector3D(const T& x, const T& y, const T& z);
    TVector3D(const TVector2D<T>& vector);
    TVector3D(const TVector3D<T>& vector);
    virtual ~TVector3D();

    TVector3D<T>&   operator=(const TVector2D<T>& vector);
    TVector3D<T>&   operator=(const TVector3D<T>& vector);

    void            clear();

    void            set(const T& x, const T& y, const T& z);
    void            setX(const T& x);
    void            setY(const T& y);
    void            setZ(const T& z);

    const T&        x() const;
    const T&        y() const;
    const T&        z() const;


private:

    T               _x;
    T               _y;
    T               _z;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     Equals(const TVector3D<T>& left, const TVector3D<T>& right, T epsilon=klab::TTypeInfo<T>::EPSILON)
{
    return (klab::Equals(left.x(), right.x(), epsilon) && klab::Equals(left.y(), right.y(), epsilon) && klab::Equals(left.z(), right.z(), epsilon)); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector3DOnX_LessThan(const TVector3D<T>& left, const TVector3D<T>& right)
{
    return (left.x() < right.x());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector3DOnY_LessThan(const TVector3D<T>& left, const TVector3D<T>& right)
{
    return (left.y() < right.y());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector3DOnZ_LessThan(const TVector3D<T>& left, const TVector3D<T>& right)
{
    return (left.z() < right.z());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector3DOnX_GreaterThan(const TVector3D<T>& left, const TVector3D<T>& right)
{
    return (left.x() > right.x());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector3DOnY_GreaterThan(const TVector3D<T>& left, const TVector3D<T>& right)
{
    return (left.y() > right.y());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool     CompareVector3DOnZ_GreaterThan(const TVector3D<T>& left, const TVector3D<T>& right)
{
    return (left.z() > right.z());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector3D<T>::TVector3D() : 
_x(klab::TTypeInfo<T>::ZERO), _y(klab::TTypeInfo<T>::ZERO), _z(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector3D<T>::TVector3D(const T& x, const T& y, const T& z) : 
_x(x), _y(y), _z(z)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector3D<T>::TVector3D(const TVector2D<T>& vector) : 
_x(vector.x()), _y(vector.y()), _z(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector3D<T>::TVector3D(const TVector3D<T>& vector) : 
_x(vector._x), _y(vector._y), _z(vector._z)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector3D<T>::~TVector3D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector3D<T>& TVector3D<T>::operator=(const TVector2D<T>& vector)
{
    _x = vector.x();
    _y = vector.y();
    _z = klab::TTypeInfo<T>::ZERO;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TVector3D<T>& TVector3D<T>::operator=(const TVector3D<T>& vector)
{
    if(this != &vector)
    {
        _x = vector._x;
        _y = vector._y;
        _z = vector._z;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TVector3D<T>::clear()
{
    _x = klab::TTypeInfo<T>::ZERO;
    _y = klab::TTypeInfo<T>::ZERO;
    _z = klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TVector3D<T>::set(const T& x, const T& y, const T& z)
{
    _x = x;
    _y = y;
    _z = z;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TVector3D<T>::setX(const T& x)
{
    _x = x;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TVector3D<T>::setY(const T& y)
{
    _y = y;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TVector3D<T>::setZ(const T& z)
{
    _z = z;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TVector3D<T>::x() const
{
    return _x;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TVector3D<T>::y() const
{
    return _y;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TVector3D<T>::z() const
{
    return _z;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
