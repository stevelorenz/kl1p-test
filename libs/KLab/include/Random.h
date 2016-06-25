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

#ifndef KLAB_RANDOM_H
#define KLAB_RANDOM_H

#include "TypeUtil.h"
#include "BitArray.h"
#include "Mutex.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KRandom
{
public:

    KRandom();
    KRandom(klab::UInt64 seed);
    KRandom(const KRandom& random);
    virtual ~KRandom();

    KRandom&            operator=(const KRandom& random);
    
    void                setSeed(klab::UInt64 seed);
    void                resetSeed();
    klab::UInt64 seed() const;

    bool                generateBool();
    klab::UInt8         generateUInt8(klab::UInt8 min=klab::TTypeInfo<klab::UInt8>::MIN, klab::UInt8 max=static_cast<klab::UInt8>(klab::TTypeInfo<klab::Int8>::MAX));
    klab::Int8          generateInt8(klab::Int8 min=klab::TTypeInfo<klab::Int8>::MIN, klab::Int8 max=klab::TTypeInfo<klab::Int8>::MAX);
    klab::UInt16        generateUInt16(klab::UInt16 min=klab::TTypeInfo<klab::UInt16>::MIN, klab::UInt16 max=static_cast<klab::UInt16>(klab::TTypeInfo<klab::Int16>::MAX));
    klab::Int16         generateInt16(klab::Int16 min=klab::TTypeInfo<klab::Int16>::MIN, klab::Int16 max=klab::TTypeInfo<klab::Int16>::MAX);
    klab::UInt32        generateUInt32(klab::UInt32 min=klab::TTypeInfo<klab::UInt32>::MIN, klab::UInt32 max=static_cast<klab::UInt32>(klab::TTypeInfo<klab::Int32>::MAX));
    klab::Int32         generateInt32(klab::Int32 min=klab::TTypeInfo<klab::Int32>::MIN, klab::Int32 max=klab::TTypeInfo<klab::Int32>::MAX);
    klab::UInt64        generateUInt64(klab::UInt64 min=klab::TTypeInfo<klab::UInt64>::MIN, klab::UInt64 max=static_cast<klab::UInt64>(klab::TTypeInfo<klab::Int64>::MAX));
    klab::Int64         generateInt64(klab::Int64 min=klab::TTypeInfo<klab::Int64>::MIN, klab::Int64 max=klab::TTypeInfo<klab::Int64>::MAX);
    klab::Real          generateReal(klab::Real min=0.0f, klab::Real max=1.0f);
    klab::DoubleReal    generateDoubleReal(klab::DoubleReal min=0.0, klab::DoubleReal max=1.0);

    template<class T>
    T                   generate(const T& min, const T& max);

    void                generateBitArray(klab::UInt32 n, KBitArray& result);
    void                generateBitArray(klab::UInt32 n, klab::UInt32 countTrues, KBitArray& result);


public:

    static KRandom&     Instance();


protected:

    klab::UInt64        generateUniformRandomNumber();


private:

    klab::KMutex        _mutex;

    klab::UInt64        _seed;

    klab::UInt64        _x1;
    klab::UInt64        _x2;
    klab::UInt64        _x3;
    klab::UInt64        _x4;
    klab::UInt64        _x5;
};

// ---------------------------------------------------------------------------------------------------- //

template<>
inline bool KRandom::generate<bool>(const bool& min, const bool& max)
{
    if(min && max)          return true;
    else if(!min && !max)   return false;
    else                    return this->generateBool();
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::UInt8 KRandom::generate<klab::UInt8>(const klab::UInt8& min, const klab::UInt8& max)
{
    return this->generateUInt8(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::Int8 KRandom::generate<klab::Int8>(const klab::Int8& min, const klab::Int8& max)
{
    return this->generateInt8(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::UInt16 KRandom::generate<klab::UInt16>(const klab::UInt16& min, const klab::UInt16& max)
{
    return this->generateUInt16(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::Int16 KRandom::generate<klab::Int16>(const klab::Int16& min, const klab::Int16& max)
{
    return this->generateInt16(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::UInt32 KRandom::generate<klab::UInt32>(const klab::UInt32& min, const klab::UInt32& max)
{
    return this->generateUInt32(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::Int32 KRandom::generate<klab::Int32>(const klab::Int32& min, const klab::Int32& max)
{
    return this->generateInt32(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::UInt64 KRandom::generate<klab::UInt64>(const klab::UInt64& min, const klab::UInt64& max)
{
    return this->generateUInt64(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::Int64 KRandom::generate<klab::Int64>(const klab::Int64& min, const klab::Int64& max)
{
    return this->generateInt64(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::Real KRandom::generate<klab::Real>(const klab::Real& min, const klab::Real& max)
{
    return this->generateReal(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

template<>
inline klab::DoubleReal KRandom::generate<klab::DoubleReal>(const klab::DoubleReal& min, const klab::DoubleReal& max)
{
    return this->generateDoubleReal(min, max);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
