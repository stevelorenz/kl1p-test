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

#include "../include/Random.h"
#include "../include/FuncUtil.h"
#include "../include/ArrayElement.h"
#include "../include/Singleton.h"
#include "../include/SystemTime.h"
#include "../include/LibUtil.h"
#include "../include/ScopedMutex.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KRandom::KRandom() :  
_mutex(),
_seed(0), 
_x1(0), _x2(0), _x3(0), _x4(0), _x5(0)
{
    this->setSeed(KSystemTime::GetCurrentMicrosecTimestamp());
}

// ---------------------------------------------------------------------------------------------------- //

KRandom::KRandom(klab::UInt64 seed) :  
_mutex(),
_seed(0), 
_x1(0), _x2(0), _x3(0), _x4(0), _x5(0)
{
    this->setSeed(seed);
}

// ---------------------------------------------------------------------------------------------------- //

KRandom::KRandom(const KRandom& random) : 
_mutex(), 
_seed(random._seed), 
_x1(random._x1), _x2(random._x2), _x3(random._x3), _x4(random._x4), _x5(random._x5)
{}

// ---------------------------------------------------------------------------------------------------- //

KRandom::~KRandom()
{}

// ---------------------------------------------------------------------------------------------------- //

KRandom& KRandom::operator=(const KRandom& random)
{
    if(this != &random)
    {
        klab::TScopedMutex<klab::KMutex> mutex(_mutex);
        klab::TScopedMutex<klab::KMutex> mutex2(random._mutex);

        _seed = random._seed;

        _x1 = random._x1;
        _x2 = random._x2;
        _x3 = random._x3;
        _x4 = random._x4;
        _x5 = random._x5;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

void KRandom::setSeed(klab::UInt64 seed)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    _seed = seed;

    // The initial seeds _x1, _x2, _x3, _x4, _x5 must be larger than 1, 511, 4095, 131071 and 8388607 respectively.
    if(_seed == 0)
    {
        _x1 = 2;
        _x2 = 512;
        _x3 = 4096;
        _x4 = 131072;
        _x5 = 8388608;
    }
    else if(_seed == 1)
    {
        _x1 = 4;
        _x2 = 1024;
        _x3 = 8192;
        _x4 = 262144;
        _x5 = 16777216;
    }
    else
    {
        _x1 = _seed;
        while(_x1 < 2)
            _x1 *= _seed;

        _x2 = _x1;
        while(_x2 < 512)
            _x2 *= _seed;

        _x3 = _x2;
        while(_x3 < 4096)
            _x3 *= _seed;

        _x4 = _x3;
        while(_x4 < 131072)
            _x4 *= _seed;

        _x5 = _x4;
        while(_x5 < 8388608)
            _x5 *= _seed;
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KRandom::resetSeed()
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    this->setSeed(KSystemTime::GetCurrentMicrosecTimestamp());
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt64 KRandom::seed() const
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    return _seed;
}

// ---------------------------------------------------------------------------------------------------- //

bool KRandom::generateBool()
{
    return (this->generateUInt32(0, 1)==1 ? true : false);
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt8 KRandom::generateUInt8(klab::UInt8 min, klab::UInt8 max)
{
    if(max>min) return static_cast<klab::UInt8>(this->generateUInt64(min, max));
    else        return min;
}

// ---------------------------------------------------------------------------------------------------- //

klab::Int8 KRandom::generateInt8(klab::Int8 min, klab::Int8 max)
{
    if(max>min) return static_cast<klab::Int8>(this->generateInt64(min, max));
    else        return min;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt16 KRandom::generateUInt16(klab::UInt16 min, klab::UInt16 max)
{
    if(max>min) return static_cast<klab::UInt16>(this->generateUInt64(min, max));
    else        return min;
}

// ---------------------------------------------------------------------------------------------------- //

klab::Int16 KRandom::generateInt16(klab::Int16 min, klab::Int16 max)
{
    if(max>min) return static_cast<klab::Int16>(this->generateInt64(min, max));
    else        return min;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KRandom::generateUInt32(klab::UInt32 min, klab::UInt32 max)
{
    if(max>min) return static_cast<klab::UInt32>(this->generateUInt64(min, max));
    else        return min;
}

// ---------------------------------------------------------------------------------------------------- //

klab::Int32 KRandom::generateInt32(klab::Int32 min, klab::Int32 max)
{
    if(max>min) return static_cast<klab::Int32>(this->generateInt64(min, max));
    else        return min;
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt64 KRandom::generateUInt64(klab::UInt64 min, klab::UInt64 max)
{
    if(max>min) 
    {
        if(min==0 && max==klab::TTypeInfo<klab::UInt64>::MAX)   return this->generateUniformRandomNumber();
        else                                                    return (min + (this->generateUniformRandomNumber() % ((max-min)+1)));
    }
    else
    {
        return min;
    }
}

// ---------------------------------------------------------------------------------------------------- //

klab::Int64 KRandom::generateInt64(klab::Int64 min, klab::Int64 max)
{
    if(max>min) return (min + this->generateUInt64(0, max-min));
    else        return min;
}

// ---------------------------------------------------------------------------------------------------- //

klab::Real KRandom::generateReal(klab::Real min, klab::Real max)
{
    if(max>min) return (min + (static_cast<klab::Real>(this->generateUInt32(klab::TTypeInfo<klab::UInt32>::MIN, klab::TTypeInfo<klab::UInt32>::MAX)*2.3283064365386963e-10) * (max-min)));
    else        return min;
}

// ---------------------------------------------------------------------------------------------------- //

klab::DoubleReal KRandom::generateDoubleReal(klab::DoubleReal min, klab::DoubleReal max)
{
    if(max>min) return (min + (this->generateUniformRandomNumber()*5.421010862427522170037264e-20 * (max-min)));
    else        return min;
}

// ---------------------------------------------------------------------------------------------------- //

void KRandom::generateBitArray(klab::UInt32 n, KBitArray& result)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    result.resize(n);

    for(klab::UInt32 i=0; i<n; ++i)
        result.setBit(i, this->generateBool());
}

// ---------------------------------------------------------------------------------------------------- //

void KRandom::generateBitArray(klab::UInt32 n, klab::UInt32 countTrues, KBitArray& result)
{
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    result.resize(n);
    result.reset();

    if(n>0 && countTrues>0)
    {
        if(countTrues < n)
        {
            std::vector<klab::TArrayElement<klab::UInt32> > elements;
            for(klab::UInt32 i=0; i<n; ++i)
                elements.push_back(klab::TArrayElement<klab::UInt32>(i, this->generateUInt32(klab::TTypeInfo<klab::UInt32>::MIN, klab::TTypeInfo<klab::UInt32>::MAX)));

            std::sort(elements.begin(), elements.end());

            for(klab::UInt32 i=0; i<countTrues; ++i)
                result.setBit(elements[i].i(), true);
        }
        else
        {
            result.set();
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

KRandom& KRandom::Instance()
{
    return klab::TSingleton<KRandom>::Instance();
}

// ---------------------------------------------------------------------------------------------------- //

// Tausworthe random numbers generator.
klab::UInt64 KRandom::generateUniformRandomNumber()
{ 
    klab::TScopedMutex<klab::KMutex> mutex(_mutex);

    klab::UInt64 b = 0;

    b = ((_x1 << 1) ^ _x1) >> 53;
    _x1 = ((_x1 & 18446744073709551614ULL) << 10) ^ b;

    b = ((_x2 << 24) ^ _x2) >> 50;
    _x2 = ((_x2 & 18446744073709551104ULL) << 5) ^ b;

    b = ((_x3 << 3) ^ _x3) >> 23;
    _x3 = ((_x3 & 18446744073709547520ULL) << 29) ^ b;

    b = ((_x4 << 5) ^ _x4) >> 24;
    _x4 = ((_x4 & 18446744073709420544ULL) << 23) ^ b;

    b = ((_x5 << 3) ^ _x5) >> 33;
    _x5 = ((_x5 & 18446744073701163008ULL) << 8) ^ b;

    return (_x1 ^ _x2 ^ _x3 ^ _x4 ^ _x5);
}

// ---------------------------------------------------------------------------------------------------- //
