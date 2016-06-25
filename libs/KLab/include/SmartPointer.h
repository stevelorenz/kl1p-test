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

#ifndef KLAB_SMARTPOINTER_H
#define KLAB_SMARTPOINTER_H

#include "TypeUtil.h"
#include "Exception.h"




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TSmartPointer
{
public:

    TSmartPointer();
    TSmartPointer(T* pointer);    
    template<class U>
    TSmartPointer(const TSmartPointer<U>& pointer);
    TSmartPointer(const TSmartPointer<T>& pointer);
    virtual ~TSmartPointer();

    TSmartPointer<T>&   operator=(T* pointer);
    template<class U>
    TSmartPointer<T>&   operator=(const TSmartPointer<U>& pointer); 
    TSmartPointer<T>&   operator=(const TSmartPointer<T>& pointer);    

    T&                  operator*() const;
    T*                  operator->() const;

    T*                  get() const;
    bool                isValid() const;
    bool                isNull() const;

    void                reset();
    void                swap(TSmartPointer<T>& pointer);


private:

    T*                  _pointer;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSmartPointer<T>::TSmartPointer() : 
_pointer(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSmartPointer<T>::TSmartPointer(T* pointer) : 
_pointer(pointer)
{
    if(_pointer != 0)
        AddSmartPointerReference(_pointer);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
template<class U>
inline TSmartPointer<T>::TSmartPointer(const TSmartPointer<U>& pointer) : 
_pointer(pointer.get())
{
    if(_pointer != 0)
        AddSmartPointerReference(_pointer);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSmartPointer<T>::TSmartPointer(const TSmartPointer<T>& pointer) : 
_pointer(pointer._pointer)
{
    if(_pointer != 0)
        AddSmartPointerReference(_pointer);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSmartPointer<T>::~TSmartPointer()
{
    if(_pointer != 0)
        ReleaseSmartPointerReference(_pointer);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSmartPointer<T>& TSmartPointer<T>::operator=(T* pointer)
{
    if(_pointer != pointer)
    {
        if(_pointer != 0)
            ReleaseSmartPointerReference(_pointer);

        _pointer = pointer;

        if(_pointer != 0)
            AddSmartPointerReference(_pointer);
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
template<class U>
inline TSmartPointer<T>& TSmartPointer<T>::operator=(const TSmartPointer<U>& pointer)
{
    if(_pointer != pointer.get())
    {
        if(_pointer != 0)
            ReleaseSmartPointerReference(_pointer);

        _pointer = pointer.get();

        if(_pointer != 0)
            AddSmartPointerReference(_pointer);
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSmartPointer<T>& TSmartPointer<T>::operator=(const TSmartPointer<T>& pointer)
{
    if(this != &pointer)
    {
        if(_pointer != pointer._pointer)
        {
            if(_pointer != 0)
                ReleaseSmartPointerReference(_pointer);

            _pointer = pointer._pointer;

            if(_pointer != 0)
                AddSmartPointerReference(_pointer);
        }
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T& TSmartPointer<T>::operator*() const
{
    ThrowTraceExceptionIf(klab::KNullPointerException, _pointer==0);

    return *_pointer;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T* TSmartPointer<T>::operator->() const
{
    ThrowTraceExceptionIf(klab::KNullPointerException, _pointer==0);

    return _pointer;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T* TSmartPointer<T>::get() const
{
    return _pointer;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TSmartPointer<T>::isValid() const
{
    return (_pointer != 0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TSmartPointer<T>::isNull() const
{
    return (_pointer == 0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TSmartPointer<T>::reset()
{
    if(_pointer != 0)
        ReleaseSmartPointerReference(_pointer);

    _pointer = 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TSmartPointer<T>::swap(TSmartPointer<T>& pointer)
{
    if(this != &pointer)
    {
        if(_pointer != pointer._pointer)
        {
            T* temp  = _pointer;
            _pointer = pointer._pointer;
            pointer._pointer = temp;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
inline bool         operator==(const TSmartPointer<T>& left, const TSmartPointer<U>& right)
{
    return (left.get() == right.get());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
inline bool         operator!=(const TSmartPointer<T>& left, const TSmartPointer<U>& right)
{
    return (left.get() != right.get());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
inline bool         operator==(const TSmartPointer<T>& left, U* right)
{
    return (left.get() == right);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
inline bool         operator!=(const TSmartPointer<T>& left, U* right)
{
    return (left.get() != right);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
inline bool         operator==(T* left, const TSmartPointer<U>& right)
{
    return (left == right.get());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
inline bool         operator!=(T* left, const TSmartPointer<U>& right)
{
    return (left != right.get());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool         operator==(const TSmartPointer<T>& left, int right) // Used for test like (ptr == 0)
{
    return (left.get() == (T*)right);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool         operator!=(const TSmartPointer<T>& left, int right) // Used for test like (ptr != 0)
{
    return (left.get() != (T*)right);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
inline bool         operator<(const TSmartPointer<T>& left, const TSmartPointer<U>& right)
{
    return std::less<T*>()(left.get(), right.get());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
TSmartPointer<T>    static_pointer_cast(const TSmartPointer<U>& pointer)
{
    return static_cast<T*>(pointer.get());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
TSmartPointer<T>    const_pointer_cast(const TSmartPointer<U>& pointer)
{
    return const_cast<T*>(pointer.get());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class U>
TSmartPointer<T>    dynamic_pointer_cast(const TSmartPointer<U>& pointer)
{
    return dynamic_cast<T*>(pointer.get());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T> 
inline void     CheckedDelete(T* pointer)
{
    typedef klab::UInt8     Test_CompleteType[sizeof(T) ? 1 : -1];
    (void)sizeof(Test_CompleteType);

    delete pointer;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
