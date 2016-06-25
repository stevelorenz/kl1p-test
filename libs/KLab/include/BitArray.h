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

#ifndef KLAB_BITARRAY_H
#define KLAB_BITARRAY_H

#include "TypeUtil.h"
#include <vector>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KBitArray
{
public:

    KBitArray();
    KBitArray(klab::UInt32 size);
    KBitArray(klab::UInt32 size, bool value);
    KBitArray(const KBitArray& bits);
    virtual ~KBitArray();

    KBitArray&      operator=(const KBitArray& bits);
    bool            operator[](klab::UInt32 i) const;

    bool            operator==(const KBitArray& bits) const;
    bool            operator!=(const KBitArray& bits) const;
    bool            operator<(const KBitArray& bits) const;
    bool            operator<=(const KBitArray& bits) const;
    bool            operator>=(const KBitArray& bits) const;
    bool            operator>(const KBitArray& bits) const;

    void            resize(klab::UInt32 size);
    void            fill(bool value);
    void            clear();
    void            push(bool value);
    bool            pop();
    void            setBit(klab::UInt32 i, bool value);
    void            set(klab::UInt32 i);
    void            set();
    void            reset(klab::UInt32 i); 
    void            reset();

    klab::UInt32    size() const;
    bool            bit(klab::UInt32 i) const; 
    

private:

    std::vector<bool>   _bits;
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
