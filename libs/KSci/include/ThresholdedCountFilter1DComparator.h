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

#ifndef KLAB_THRESHOLDEDCOUNTFILTER1DCOMPARATOR_H
#define KLAB_THRESHOLDEDCOUNTFILTER1DCOMPARATOR_H

#include "TrigoUtil.h"
#include "ArmadilloUtil.h"
#include "Complex.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TThresholdedCountFilter1DComparator
{
public:

    TThresholdedCountFilter1DComparator(const T& value, klab::UInt32 index);
    TThresholdedCountFilter1DComparator(const TThresholdedCountFilter1DComparator<T>& comp);
    virtual ~TThresholdedCountFilter1DComparator();

    TThresholdedCountFilter1DComparator<T>&   operator=(const TThresholdedCountFilter1DComparator<T>& comp);

    bool                operator<(const TThresholdedCountFilter1DComparator<T>& right) const;

    const T&            value() const;
    klab::UInt32        index() const;


private:

    T               _value;
    klab::UInt32    _index;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TThresholdedCountFilter1DReverseComparator : public TThresholdedCountFilter1DComparator<T>
{
public:

    TThresholdedCountFilter1DReverseComparator(const T& value, klab::UInt32 index);
    TThresholdedCountFilter1DReverseComparator(const TThresholdedCountFilter1DReverseComparator<T>& comp);
    virtual ~TThresholdedCountFilter1DReverseComparator();

    TThresholdedCountFilter1DReverseComparator<T>&    operator=(const TThresholdedCountFilter1DReverseComparator<T>& comp);

    bool                operator<(const TThresholdedCountFilter1DComparator<T>& right) const;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter1DComparator : public TThresholdedCountFilter1DComparator<T>
{
public:

    TAbsoluteThresholdedCountFilter1DComparator(const T& value, klab::UInt32 index);
    TAbsoluteThresholdedCountFilter1DComparator(const TAbsoluteThresholdedCountFilter1DComparator<T>& comp);
    virtual ~TAbsoluteThresholdedCountFilter1DComparator();

    TAbsoluteThresholdedCountFilter1DComparator<T>&   operator=(const TAbsoluteThresholdedCountFilter1DComparator<T>& comp);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter1DReverseComparator : public TThresholdedCountFilter1DReverseComparator<T>
{
public:

    TAbsoluteThresholdedCountFilter1DReverseComparator(const T& value, klab::UInt32 index);
    TAbsoluteThresholdedCountFilter1DReverseComparator(const TAbsoluteThresholdedCountFilter1DReverseComparator<T>& comp);
    virtual ~TAbsoluteThresholdedCountFilter1DReverseComparator();

    TAbsoluteThresholdedCountFilter1DReverseComparator<T>&    operator=(const TAbsoluteThresholdedCountFilter1DReverseComparator<T>& comp);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >
{
public:

    TAbsoluteThresholdedCountFilter1DComparator(const std::complex<T>& value, klab::UInt32 index);
    TAbsoluteThresholdedCountFilter1DComparator(const TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >& comp);
    virtual ~TAbsoluteThresholdedCountFilter1DComparator();

    TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >&    operator=(const TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >& comp);

    bool                operator<(const TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >& right) const;

    const T&            value() const;
    klab::UInt32 index() const;


private:

    T               _value;
    klab::UInt32    _index;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >
{
public:

    TAbsoluteThresholdedCountFilter1DReverseComparator(const std::complex<T>& value, klab::UInt32 index);
    TAbsoluteThresholdedCountFilter1DReverseComparator(const TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >& comp);
    virtual ~TAbsoluteThresholdedCountFilter1DReverseComparator();

    TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >&     operator=(const TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >& comp);

    bool                operator<(const TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >& right) const;

    const T&            value() const;
    klab::UInt32 index() const;


private:

    T               _value;
    klab::UInt32    _index;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >
{
public:

    TAbsoluteThresholdedCountFilter1DComparator(const TComplex<T>& value, klab::UInt32 index);
    TAbsoluteThresholdedCountFilter1DComparator(const TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >& comp);
    virtual ~TAbsoluteThresholdedCountFilter1DComparator();

    TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >&     operator=(const TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >& comp);

    bool                operator<(const TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >& right) const;

    const T&            value() const;
    klab::UInt32 index() const;


private:

    T               _value;
    klab::UInt32    _index;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >
{
public:

    TAbsoluteThresholdedCountFilter1DReverseComparator(const TComplex<T>& value, klab::UInt32 index);
    TAbsoluteThresholdedCountFilter1DReverseComparator(const TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >& comp);
    virtual ~TAbsoluteThresholdedCountFilter1DReverseComparator();

    TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >&  operator=(const TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >& comp);

    bool                operator<(const TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >& right) const;

    const T&            value() const;
    klab::UInt32 index() const;


private:

    T               _value;
    klab::UInt32    _index;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter1DComparator<T>::TThresholdedCountFilter1DComparator(const T& value, klab::UInt32 index) : 
_value(value), _index(index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter1DComparator<T>::TThresholdedCountFilter1DComparator(const TThresholdedCountFilter1DComparator<T>& comp) : 
_value(comp._value), _index(comp._index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter1DComparator<T>::~TThresholdedCountFilter1DComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter1DComparator<T>& TThresholdedCountFilter1DComparator<T>::operator=(const TThresholdedCountFilter1DComparator<T>& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _index = comp._index;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TThresholdedCountFilter1DComparator<T>::operator<(const TThresholdedCountFilter1DComparator<T>& right) const
{
    return (_value < right._value);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TThresholdedCountFilter1DComparator<T>::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TThresholdedCountFilter1DComparator<T>::index() const
{
    return _index;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter1DReverseComparator<T>::TThresholdedCountFilter1DReverseComparator(const T& value, klab::UInt32 index) : TThresholdedCountFilter1DComparator<T>(value, index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter1DReverseComparator<T>::TThresholdedCountFilter1DReverseComparator(const TThresholdedCountFilter1DReverseComparator<T>& comp) : TThresholdedCountFilter1DComparator<T>(comp)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter1DReverseComparator<T>::~TThresholdedCountFilter1DReverseComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TThresholdedCountFilter1DReverseComparator<T>& TThresholdedCountFilter1DReverseComparator<T>::operator=(const TThresholdedCountFilter1DReverseComparator<T>& comp)
{
    if(this != &comp)
        TThresholdedCountFilter1DComparator<T>::operator=(comp);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TThresholdedCountFilter1DReverseComparator<T>::operator<(const TThresholdedCountFilter1DComparator<T>& right) const
{
    return (this->value() > right.value());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter1DComparator<T>::TAbsoluteThresholdedCountFilter1DComparator(const T& value, klab::UInt32 index) : TThresholdedCountFilter1DComparator<T>(klab::Abs(value), index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter1DComparator<T>::TAbsoluteThresholdedCountFilter1DComparator(const TAbsoluteThresholdedCountFilter1DComparator<T>& comp) : TThresholdedCountFilter1DComparator<T>(comp)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter1DComparator<T>::~TAbsoluteThresholdedCountFilter1DComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter1DComparator<T>& TAbsoluteThresholdedCountFilter1DComparator<T>::operator=(const TAbsoluteThresholdedCountFilter1DComparator<T>& comp)
{
    if(this != &comp)
        TThresholdedCountFilter1DComparator<T>::operator=(comp);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter1DReverseComparator<T>::TAbsoluteThresholdedCountFilter1DReverseComparator(const T& value, klab::UInt32 index) : TThresholdedCountFilter1DReverseComparator<T>(klab::Abs(value), index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter1DReverseComparator<T>::TAbsoluteThresholdedCountFilter1DReverseComparator(const TAbsoluteThresholdedCountFilter1DReverseComparator<T>& comp) : TThresholdedCountFilter1DReverseComparator<T>(comp)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter1DReverseComparator<T>::~TAbsoluteThresholdedCountFilter1DReverseComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TAbsoluteThresholdedCountFilter1DReverseComparator<T>& TAbsoluteThresholdedCountFilter1DReverseComparator<T>::operator=(const TAbsoluteThresholdedCountFilter1DReverseComparator<T>& comp)
{
    if(this != &comp)
        TThresholdedCountFilter1DReverseComparator<T>::operator=(comp);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >::TAbsoluteThresholdedCountFilter1DComparator(const std::complex<T>& value, klab::UInt32 index) : 
_value(klab::Abs(value)), _index(index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >::TAbsoluteThresholdedCountFilter1DComparator(const TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >& comp) : 
_value(comp._value), _index(comp._index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >::~TAbsoluteThresholdedCountFilter1DComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >& TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >::operator=(const TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _index = comp._index;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
bool TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >::operator<(const TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >& right) const
{
    return _value < right._value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T& TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter1DComparator<std::complex<T> >::index() const
{
    return _index;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >::TAbsoluteThresholdedCountFilter1DReverseComparator(const std::complex<T>& value, klab::UInt32 index) : 
_value(klab::Abs(value)), _index(index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >::TAbsoluteThresholdedCountFilter1DReverseComparator(const TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >& comp) : 
_value(comp._value), _index(comp._index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >::~TAbsoluteThresholdedCountFilter1DReverseComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >& TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >::operator=(const TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _index = comp._index;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
bool TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >::operator<(const TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >& right) const
{
    return _value > right._value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T& TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter1DReverseComparator<std::complex<T> >::index() const
{
    return _index;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >::TAbsoluteThresholdedCountFilter1DComparator(const TComplex<T>& value, klab::UInt32 index) :
_value(klab::Abs(value)), _index(index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >::TAbsoluteThresholdedCountFilter1DComparator(const TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >& comp) : 
_value(comp._value), _index(comp._index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >::~TAbsoluteThresholdedCountFilter1DComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >& TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >::operator=(const TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _index = comp._index;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
bool TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >::operator<(const TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >& right) const
{
    return _value < right._value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T& TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter1DComparator<TComplex<T> >::index() const
{
    return _index;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >::TAbsoluteThresholdedCountFilter1DReverseComparator(const TComplex<T>& value, klab::UInt32 index) :
_value(klab::Abs(value)), _index(index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >::TAbsoluteThresholdedCountFilter1DReverseComparator(const TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >& comp) : 
_value(comp._value), _index(comp._index)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >::~TAbsoluteThresholdedCountFilter1DReverseComparator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >& TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >::operator=(const TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >& comp)
{
    if(this != &comp)
    {
        _value = comp._value;
        _index = comp._index;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
bool TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >::operator<(const TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >& right) const
{
    return _value > right._value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const T& TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
klab::UInt32 TAbsoluteThresholdedCountFilter1DReverseComparator<TComplex<T> >::index() const
{
    return _index;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
