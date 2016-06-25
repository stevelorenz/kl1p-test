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

#ifndef KLAB_THRESHOLDEDCOUNTFILTER2DCOMPARATOR_H
#define KLAB_THRESHOLDEDCOUNTFILTER2DCOMPARATOR_H

#include "TrigoUtil.h"
#include "ArmadilloUtil.h"
#include "Complex.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TThresholdedCountFilter2DComparator
{
public:

    TThresholdedCountFilter2DComparator(const T& value, klab::UInt32 i, klab::UInt32 j);
    TThresholdedCountFilter2DComparator(const TThresholdedCountFilter2DComparator<T>& comp);
    virtual ~TThresholdedCountFilter2DComparator();

    TThresholdedCountFilter2DComparator<T>&   operator=(const TThresholdedCountFilter2DComparator<T>& comp);

    bool                operator<(const TThresholdedCountFilter2DComparator<T>& right) const;

    const T&            value() const;
    klab::UInt32        i() const;
    klab::UInt32        j() const;


private:

    T               _value;
    klab::UInt32    _i;
    klab::UInt32    _j;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TThresholdedCountFilter2DReverseComparator : public TThresholdedCountFilter2DComparator<T>
{
public:

    TThresholdedCountFilter2DReverseComparator(const T& value, klab::UInt32 i, klab::UInt32 j);
    TThresholdedCountFilter2DReverseComparator(const TThresholdedCountFilter2DReverseComparator<T>& comp);
    virtual ~TThresholdedCountFilter2DReverseComparator();

    TThresholdedCountFilter2DReverseComparator<T>&    operator=(const TThresholdedCountFilter2DReverseComparator<T>& comp);

    bool                operator<(const TThresholdedCountFilter2DComparator<T>& right) const;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter2DComparator : public TThresholdedCountFilter2DComparator<T>
{
public:

    TAbsoluteThresholdedCountFilter2DComparator(const T& value, klab::UInt32 i, klab::UInt32 j);
    TAbsoluteThresholdedCountFilter2DComparator(const TAbsoluteThresholdedCountFilter2DComparator<T>& comp);
    virtual ~TAbsoluteThresholdedCountFilter2DComparator();

    TAbsoluteThresholdedCountFilter2DComparator<T>&   operator=(const TAbsoluteThresholdedCountFilter2DComparator<T>& comp);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter2DReverseComparator : public TThresholdedCountFilter2DReverseComparator<T>
{
public:

    TAbsoluteThresholdedCountFilter2DReverseComparator(const T& value, klab::UInt32 i, klab::UInt32 j);
    TAbsoluteThresholdedCountFilter2DReverseComparator(const TAbsoluteThresholdedCountFilter2DReverseComparator<T>& comp);
    virtual ~TAbsoluteThresholdedCountFilter2DReverseComparator();

    TAbsoluteThresholdedCountFilter2DReverseComparator<T>&    operator=(const TAbsoluteThresholdedCountFilter2DReverseComparator<T>& comp);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >
{
public:

    TAbsoluteThresholdedCountFilter2DComparator(const std::complex<T>& value, klab::UInt32 i, klab::UInt32 j);
    TAbsoluteThresholdedCountFilter2DComparator(const TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >& comp);
    virtual ~TAbsoluteThresholdedCountFilter2DComparator();

    TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >&    operator=(const TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >& comp);

    bool                operator<(const TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >& right) const;

    const T&            value() const;
    klab::UInt32 i() const;
    klab::UInt32 j() const;


private:

    T               _value;
    klab::UInt32    _i;
    klab::UInt32    _j;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >
{
public:

    TAbsoluteThresholdedCountFilter2DReverseComparator(const std::complex<T>& value, klab::UInt32 i, klab::UInt32 j);
    TAbsoluteThresholdedCountFilter2DReverseComparator(const TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >& comp);
    virtual ~TAbsoluteThresholdedCountFilter2DReverseComparator();

    TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >&     operator=(const TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >& comp);

    bool                operator<(const TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >& right) const;

    const T&            value() const;
    klab::UInt32 i() const;
    klab::UInt32 j() const;


private:

    T               _value;
    klab::UInt32    _i;
    klab::UInt32    _j;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >
{
public:

    TAbsoluteThresholdedCountFilter2DComparator(const TComplex<T>& value, klab::UInt32 i, klab::UInt32 j);
    TAbsoluteThresholdedCountFilter2DComparator(const TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >& comp);
    virtual ~TAbsoluteThresholdedCountFilter2DComparator();

    TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >&     operator=(const TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >& comp);

    bool                operator<(const TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >& right) const;

    const T&            value() const;
    klab::UInt32 i() const;
    klab::UInt32 j() const;


private:

    T               _value;
    klab::UInt32    _i;
    klab::UInt32    _j;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >
{
public:

    TAbsoluteThresholdedCountFilter2DReverseComparator(const TComplex<T>& value, klab::UInt32 i, klab::UInt32 j);
    TAbsoluteThresholdedCountFilter2DReverseComparator(const TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >& comp);
    virtual ~TAbsoluteThresholdedCountFilter2DReverseComparator();

    TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >&  operator=(const TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >& comp);

    bool                operator<(const TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >& right) const;

    const T&            value() const;
    klab::UInt32 i() const;
    klab::UInt32 j() const;


private:

    T               _value;
    klab::UInt32    _i;
    klab::UInt32    _j;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter2DComparator<T>::TThresholdedCountFilter2DComparator(const T& value, klab::UInt32 i, klab::UInt32 j) : 
_value(value), _i(i), _j(j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter2DComparator<T>::TThresholdedCountFilter2DComparator(const TThresholdedCountFilter2DComparator<T>& comp) : 
_value(comp._value), _i(comp._i), _j(comp._j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter2DComparator<T>::~TThresholdedCountFilter2DComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter2DComparator<T>& TThresholdedCountFilter2DComparator<T>::operator=(const TThresholdedCountFilter2DComparator<T>& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _i     = comp._i;
        _j     = comp._j;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TThresholdedCountFilter2DComparator<T>::operator<(const TThresholdedCountFilter2DComparator<T>& right) const
{
    return (_value < right._value);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TThresholdedCountFilter2DComparator<T>::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TThresholdedCountFilter2DComparator<T>::i() const
{
    return _i;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TThresholdedCountFilter2DComparator<T>::j() const
{
    return _j;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter2DReverseComparator<T>::TThresholdedCountFilter2DReverseComparator(const T& value, klab::UInt32 i, klab::UInt32 j) : TThresholdedCountFilter2DComparator<T>(value, i, j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter2DReverseComparator<T>::TThresholdedCountFilter2DReverseComparator(const TThresholdedCountFilter2DReverseComparator<T>& comp) : TThresholdedCountFilter2DComparator<T>(comp)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter2DReverseComparator<T>::~TThresholdedCountFilter2DReverseComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter2DReverseComparator<T>& TThresholdedCountFilter2DReverseComparator<T>::operator=(const TThresholdedCountFilter2DReverseComparator<T>& comp)
{
    if(this != &comp)
        TThresholdedCountFilter2DComparator<T>::operator=(comp);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TThresholdedCountFilter2DReverseComparator<T>::operator<(const TThresholdedCountFilter2DComparator<T>& right) const
{
    return (this->value() > right.value());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter2DComparator<T>::TAbsoluteThresholdedCountFilter2DComparator(const T& value, klab::UInt32 i, klab::UInt32 j) : TThresholdedCountFilter2DComparator<T>(klab::Abs(value), i, j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter2DComparator<T>::TAbsoluteThresholdedCountFilter2DComparator(const TAbsoluteThresholdedCountFilter2DComparator<T>& comp) : TThresholdedCountFilter2DComparator<T>(comp)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter2DComparator<T>::~TAbsoluteThresholdedCountFilter2DComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter2DComparator<T>& TAbsoluteThresholdedCountFilter2DComparator<T>::operator=(const TAbsoluteThresholdedCountFilter2DComparator<T>& comp)
{
    if(this != &comp)
        TThresholdedCountFilter2DComparator<T>::operator=(comp);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter2DReverseComparator<T>::TAbsoluteThresholdedCountFilter2DReverseComparator(const T& value, klab::UInt32 i, klab::UInt32 j) : TThresholdedCountFilter2DReverseComparator<T>(klab::Abs(value), i, j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter2DReverseComparator<T>::TAbsoluteThresholdedCountFilter2DReverseComparator(const TAbsoluteThresholdedCountFilter2DReverseComparator<T>& comp) : TThresholdedCountFilter2DReverseComparator<T>(comp)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter2DReverseComparator<T>::~TAbsoluteThresholdedCountFilter2DReverseComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter2DReverseComparator<T>& TAbsoluteThresholdedCountFilter2DReverseComparator<T>::operator=(const TAbsoluteThresholdedCountFilter2DReverseComparator<T>& comp)
{
    if(this != &comp)
        TThresholdedCountFilter2DReverseComparator<T>::operator=(comp);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >::TAbsoluteThresholdedCountFilter2DComparator(const std::complex<T>& value, klab::UInt32 i, klab::UInt32 j) : 
_value(klab::Abs(value)), _i(i), _j(j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >::TAbsoluteThresholdedCountFilter2DComparator(const TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >& comp) : 
_value(comp._value), _i(comp._i), _j(comp._j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >::~TAbsoluteThresholdedCountFilter2DComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >& TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >::operator=(const TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _i     = comp._i;
        _j     = comp._j;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
bool TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >::operator<(const TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >& right) const
{
    return _value < right._value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T& TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >::i() const
{
    return _i;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter2DComparator<std::complex<T> >::j() const
{
    return _j;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >::TAbsoluteThresholdedCountFilter2DReverseComparator(const std::complex<T>& value, klab::UInt32 i, klab::UInt32 j) : 
_value(klab::Abs(value)), _i(i), _j(j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >::TAbsoluteThresholdedCountFilter2DReverseComparator(const TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >& comp) : 
_value(comp._value), _i(comp._i), _j(comp._j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >::~TAbsoluteThresholdedCountFilter2DReverseComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >& TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >::operator=(const TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _i     = comp._i;
        _j     = comp._j;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
bool TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >::operator<(const TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >& right) const
{
    return _value > right._value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T& TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >::i() const
{
    return _i;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter2DReverseComparator<std::complex<T> >::j() const
{
    return _j;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >::TAbsoluteThresholdedCountFilter2DComparator(const TComplex<T>& value, klab::UInt32 i, klab::UInt32 j) :
_value(klab::Abs(value)), _i(i), _j(j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >::TAbsoluteThresholdedCountFilter2DComparator(const TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >& comp) : 
_value(comp._value), _i(comp._i), _j(comp._j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >::~TAbsoluteThresholdedCountFilter2DComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >& TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >::operator=(const TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _i     = comp._i;
        _j     = comp._j;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
bool TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >::operator<(const TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >& right) const
{
    return _value < right._value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T& TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >::i() const
{
    return _i;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter2DComparator<TComplex<T> >::j() const
{
    return _j;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >::TAbsoluteThresholdedCountFilter2DReverseComparator(const TComplex<T>& value, klab::UInt32 i, klab::UInt32 j) :
_value(klab::Abs(value)), _i(i), _j(j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >::TAbsoluteThresholdedCountFilter2DReverseComparator(const TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >& comp) : 
_value(comp._value), _i(comp._i), _j(comp._j)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >::~TAbsoluteThresholdedCountFilter2DReverseComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >& TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >::operator=(const TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _i     = comp._i;
        _j     = comp._j;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
bool TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >::operator<(const TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >& right) const
{
    return _value > right._value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T& TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >::i() const
{
    return _i;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter2DReverseComparator<TComplex<T> >::j() const
{
    return _j;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
