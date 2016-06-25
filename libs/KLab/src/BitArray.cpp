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

#include "../include/BitArray.h"
#include "../include/FuncUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KBitArray::KBitArray() : 
_bits()
{}

// ---------------------------------------------------------------------------------------------------- //

KBitArray::KBitArray(klab::UInt32 size) : 
_bits(size)
{}

// ---------------------------------------------------------------------------------------------------- //

KBitArray::KBitArray(klab::UInt32 size, bool value) : 
_bits(size, value)
{}

// ---------------------------------------------------------------------------------------------------- //

KBitArray::KBitArray(const KBitArray& bits) : 
_bits(bits._bits)
{}

// ---------------------------------------------------------------------------------------------------- //

KBitArray::~KBitArray()
{}

// ---------------------------------------------------------------------------------------------------- //

KBitArray& KBitArray::operator=(const KBitArray& bits)
{
    if(this != &bits)
    {
        _bits = bits._bits;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

bool KBitArray::operator[](klab::UInt32 i) const
{
    if(i<static_cast<klab::UInt32>(_bits.size()))   return _bits[i];
    else                                            return false;
}

// ---------------------------------------------------------------------------------------------------- //

bool KBitArray::operator==(const KBitArray& bits) const
{
    bool ret = true;

    klab::Int32 n = static_cast<klab::Int32>(klab::Max(this->size(), bits.size()));
    for(klab::Int32 i=n; i>=0 && ret; --i)
        ret = (this->bit(i) == bits[i]);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

bool KBitArray::operator!=(const KBitArray& bits) const
{
    return (this->operator==(bits) == false);
}

// ---------------------------------------------------------------------------------------------------- //

bool KBitArray::operator<(const KBitArray& bits) const
{
    klab::Int32 n = static_cast<klab::Int32>(klab::Max(this->size(), bits.size()));

    klab::Int32 i = n;
    for(; i>=0 && (this->bit(i)==bits[i]); --i);

    if(i >= 0)  return ((this->bit(i)?1:0) < (bits[i]?1:0));
    else        return false;
}

// ---------------------------------------------------------------------------------------------------- //

bool KBitArray::operator<=(const KBitArray& bits) const
{
    klab::Int32 n = static_cast<klab::Int32>(klab::Max(this->size(), bits.size()));

    klab::Int32 i = n;
    for(; i>=0 && (this->bit(i)==bits[i]); --i);

    if(i >= 0)  return ((this->bit(i)?1:0) < (bits[i]?1:0));
    else        return true;
}

// ---------------------------------------------------------------------------------------------------- //

bool KBitArray::operator>=(const KBitArray& bits) const
{
    klab::Int32 n = static_cast<klab::Int32>(klab::Max(this->size(), bits.size()));

    klab::Int32 i = n;
    for(; i>=0 && (this->bit(i)==bits[i]); --i);

    if(i >= 0)  return ((this->bit(i)?1:0) > (bits[i]?1:0));
    else        return true;
}

// ---------------------------------------------------------------------------------------------------- //

bool KBitArray::operator>(const KBitArray& bits) const
{
    klab::Int32 n = static_cast<klab::Int32>(klab::Max(this->size(), bits.size()));

    klab::Int32 i = n;
    for(; i>=0 && (this->bit(i)==bits[i]); --i);

    if(i >= 0)  return ((this->bit(i)?1:0) > (bits[i]?1:0));
    else        return false;
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArray::resize(klab::UInt32 size)
{
    _bits.resize(size);
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArray::fill(bool value)
{
    klab::UInt32 n = this->size();
    for(klab::UInt32 i=0; i<n; ++i)
        _bits[i] = value;
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArray::clear()
{
    _bits.clear();
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArray::push(bool value)
{
    _bits.push_back(value);
}

// ---------------------------------------------------------------------------------------------------- //

bool KBitArray::pop()
{
    bool ret = false;

    if(_bits.size() > 0)
	{
        ret = _bits[_bits.size()-1];
		_bits.pop_back();
	}

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArray::setBit(klab::UInt32 i, bool value)
{
    if(i<static_cast<klab::UInt32>(_bits.size()))    
        _bits[i] = value;
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArray::set(klab::UInt32 i)
{
    this->setBit(i, true);
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArray::set()
{
    this->fill(true);
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArray::reset(klab::UInt32 i)
{
    this->setBit(i, false);
}

// ---------------------------------------------------------------------------------------------------- //

void KBitArray::reset()
{
    this->fill(false);
}

// ---------------------------------------------------------------------------------------------------- //

klab::UInt32 KBitArray::size() const
{
    return static_cast<klab::UInt32>(_bits.size());
}

// ---------------------------------------------------------------------------------------------------- //

bool KBitArray::bit(klab::UInt32 i) const 
{
    if(i<static_cast<klab::UInt32>(_bits.size()))   return _bits[i];
    else                                            return false;
}

// ---------------------------------------------------------------------------------------------------- //
