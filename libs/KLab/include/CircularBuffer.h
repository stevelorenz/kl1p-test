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

#ifndef KLAB_CIRCULARBUFFER_H
#define KLAB_CIRCULARBUFFER_H

#include "TypeUtil.h"
#include "Mutex.h"
#include "ScopedMutex.h"
#include "Exception.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TCircularBuffer
{
public:

    TCircularBuffer();
    TCircularBuffer(klab::UInt32 capacity);
    TCircularBuffer(const TCircularBuffer<T>& buffer);
    virtual ~TCircularBuffer();

    TCircularBuffer<T>& operator=(const TCircularBuffer<T>& buffer);

    const T&            operator[](klab::UInt32 i) const;
    T&                  operator[](klab::UInt32 i);

    void                push(const T& value);
    void                push(const T* buffer, klab::UInt32 size);
    void                push(const std::vector<T>& buffer);
    void                pop();
    void                clear();

    void                reserve(klab::UInt32 capacity);
    void                resize(klab::UInt32 size, const T& value=T());
    klab::UInt32        capacity() const;
    klab::UInt32        size() const;

    const T&            at(klab::UInt32 i) const;
    T&                  at(klab::UInt32 i);
    const T&            front() const;
    T&                  front();
    const T&            back() const;
    T&                  back();


protected:

    static const klab::UInt32   DEFAULT_CAPACITY = 128;


private:

    klab::KMutex        _mutex;

    klab::UInt32        _capacity;
    klab::UInt32        _size;
    T*                  _buffer;

    klab::UInt32        _head;
    klab::UInt32        _tail;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCircularBuffer<T>::TCircularBuffer() : 
_mutex(),
_capacity(TCircularBuffer<T>::DEFAULT_CAPACITY), _size(0), _buffer(new T[TCircularBuffer<T>::DEFAULT_CAPACITY]), 
_head(0), _tail(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCircularBuffer<T>::TCircularBuffer(klab::UInt32 capacity) : 
_mutex(),
_capacity(capacity), _size(0), _buffer(capacity>0 ? new T[capacity] : 0),
_head(0), _tail(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCircularBuffer<T>::TCircularBuffer(const TCircularBuffer<T>& buffer) : 
_mutex(),
_capacity(buffer._capacity), _size(buffer._size), _buffer(buffer._capacity>0 ? new T[buffer._capacity] : 0),
_head(0), _tail(0)
{
    if(_capacity > 0)
    {
        for(klab::UInt32 i=0; i<_size; ++i)
            _buffer[i] = buffer[i];

        _tail = _size;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCircularBuffer<T>::~TCircularBuffer()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_buffer != 0)
        delete[] _buffer;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCircularBuffer<T>& TCircularBuffer<T>::operator=(const TCircularBuffer<T>& buffer)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(this != &buffer)
    {
        if(_capacity != buffer._capacity)
        {
            if(_buffer != 0)
                delete[] _buffer;

            _capacity = buffer._capacity;  

            if(_capacity>0) _buffer = new T[_capacity];
            else            _buffer = 0;
        }

        _size = buffer._size;
        _head = 0;

        if(_capacity > 0)
        {
            for(klab::UInt32 i=0; i<_size; ++i)
                _buffer[i] = buffer[i];

            
            _tail = _size;
        }
        else
        {
            _tail = 0;
        }
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TCircularBuffer<T>::operator[](klab::UInt32 i) const
{
    return this->at(i);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T& TCircularBuffer<T>::operator[](klab::UInt32 i)
{
    return this->at(i);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TCircularBuffer<T>::push(const T& value)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_capacity > 0)
    {        
        _buffer[_tail++] = value;

        if(_size < _capacity)
            ++_size;

        if(_tail >= _capacity)
            _tail = 0;            

        if(_size == _capacity)
            _head = _tail;       
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TCircularBuffer<T>::push(const T* buffer, klab::UInt32 size)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_capacity>0 && size>0 && buffer!=0)
    {
        // May be optimized.
        for(klab::UInt32 i=0; i<size; ++i)
            this->push(buffer[i]);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TCircularBuffer<T>::push(const std::vector<T>& buffer)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(buffer.size() > 0)
        this->push(&(buffer[0]), static_cast<klab::UInt32>(buffer.size()));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TCircularBuffer<T>::pop()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_size > 0)
    {
        if(_tail>0) --_tail;
        else        _tail = _capacity-1;

        --_size;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TCircularBuffer<T>::clear()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    _size = 0;
    _head = 0;
    _tail = 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TCircularBuffer<T>::reserve(klab::UInt32 capacity)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    if(_capacity != capacity)
    {
        if(_buffer != 0)
            delete[] _buffer;

        _capacity = capacity;  
        _size = 0;

        if(_capacity>0) _buffer = new T[_capacity];
        else            _buffer = 0;
    }

    _head = 0;
    _tail = 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TCircularBuffer<T>::resize(klab::UInt32 size, const T& value)
{
	klab::TScopedMutex<klab::KMutex> mutex(_mutex);
	
    if(size == 0)
    {
        _size = 0;
        _head = 0;
        _tail = 0;
    }
    else if(size < _size)
    {
        _tail = (_head+size) % _capacity;
        _size = size;
    }
    else if(size > _size)
    {
        klab::UInt32 prevSize = _size;
        _size = size;
        if(_size >= _capacity)
            _size = _capacity;

        if(_size != prevSize)
        {
            klab::UInt32 end = _head+_size;
            for(klab::UInt32 i=_tail; i<end; ++i)
                _buffer[i%_capacity] = value;

            _tail = (_head+_size) % _capacity; 
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TCircularBuffer<T>::capacity() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _capacity;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TCircularBuffer<T>::size() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _size;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TCircularBuffer<T>::at(klab::UInt32 i) const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    ThrowTraceExceptionIf(klab::KOutOfBoundException, i>=_size);
    return _buffer[(_head+i)%_capacity];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T& TCircularBuffer<T>::at(klab::UInt32 i)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    ThrowTraceExceptionIf(klab::KOutOfBoundException, i>=_size);
    return _buffer[(_head+i)%_capacity];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TCircularBuffer<T>::front() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    ThrowTraceExceptionIf(klab::KOutOfBoundException, _size==0);
    return _buffer[_head];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T& TCircularBuffer<T>::front()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    ThrowTraceExceptionIf(klab::KOutOfBoundException, _size==0);
    return _buffer[_head];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TCircularBuffer<T>::back() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    ThrowTraceExceptionIf(klab::KOutOfBoundException, _size==0);
    return _buffer[(_tail==0 ? _capacity-1 : _tail-1)];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T& TCircularBuffer<T>::back()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    ThrowTraceExceptionIf(klab::KOutOfBoundException, _size==0);
    return _buffer[(_tail==0 ? _capacity-1 : _tail-1)];
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
