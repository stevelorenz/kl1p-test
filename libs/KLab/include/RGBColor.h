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

#ifndef KLAB_RGBCOLOR_H
#define KLAB_RGBCOLOR_H

#include "TypeUtil.h"
#include "FuncUtil.h"




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TRGBColor
{
public:

    TRGBColor();
    TRGBColor(const T& red, const T& green, const T& blue);
    TRGBColor(const TRGBColor<T>& color);
    virtual ~TRGBColor();

    const TRGBColor<T>&         operator=(const TRGBColor<T>& color);

    bool                        operator==(const  TRGBColor<T>& color) const;
    bool                        operator!=(const  TRGBColor<T>& color) const;

    void                        set(const T& red, const T& green, const T& blue);
    void                        setRed(const T& red);
    void                        setGreen(const T& green);
    void                        setBlue(const T& blue);

    const T&                    red() const;
    const T&                    green() const;
    const T&                    blue() const;

    bool                        isEqual(const  TRGBColor<T>& color, const T& epsilon=std::numeric_limits<T>::epsilon()) const;


public:

    static const TRGBColor<T>   BLACK;


private:

    T                           _red;
    T                           _green;
    T                           _blue;
};

// ---------------------------------------------------------------------------------------------------- //

typedef TRGBColor<klab::UInt8>      KRGBColor;

// ---------------------------------------------------------------------------------------------------- //

template<class T> const TRGBColor<T> TRGBColor<T>::BLACK    = TRGBColor<T>(T(), T(), T());

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRGBColor<T>::TRGBColor() : 
_red(T()), _green(T()), _blue(T())
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRGBColor<T>::TRGBColor(const T& red, const T& green, const T& blue) : 
_red(red), _green(green), _blue(blue)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRGBColor<T>::TRGBColor(const TRGBColor<T>& color) : 
_red(color._red), _green(color._green), _blue(color._blue)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TRGBColor<T>::~TRGBColor()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const TRGBColor<T>& TRGBColor<T>::operator=(const TRGBColor<T>& color)
{
    if(this != &color)
    {
        _red    = color._red;
        _green  = color._green;
        _blue   = color._blue;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TRGBColor<T>::operator==(const  TRGBColor<T>& color) const
{
    return this->isEqual(color);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TRGBColor<T>::operator!=(const  TRGBColor<T>& color) const
{
    return (this->isEqual(color) == false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TRGBColor<T>::set(const T& red, const T& green, const T& blue)
{
    _red    = red;
    _green  = green;
    _blue   = blue;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TRGBColor<T>::setRed(const T& red)
{
    _red = red;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TRGBColor<T>::setGreen(const T& green)
{
    _green = green;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TRGBColor<T>::setBlue(const T& blue)
{
    _blue = blue;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TRGBColor<T>::red() const
{
    return _red;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TRGBColor<T>::green() const
{
    return _green;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TRGBColor<T>::blue() const
{
    return _blue;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TRGBColor<T>::isEqual(const  TRGBColor<T>& color, const T& epsilon) const
{
    return (klab::Abs(_red-color._red)<=epsilon && klab::Abs(_green-color._green)<=epsilon && klab::Abs(_blue-color._blue)<=epsilon);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
