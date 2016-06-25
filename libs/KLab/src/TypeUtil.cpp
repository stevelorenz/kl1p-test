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

#include "../include/TypeUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

const klab::UInt8 TTypeInfo<klab::UInt8>::ZERO    = 0;
const klab::UInt8 TTypeInfo<klab::UInt8>::UNIT    = 1;
const klab::UInt8 TTypeInfo<klab::UInt8>::MIN     = std::numeric_limits<klab::UInt8>::min();
const klab::UInt8 TTypeInfo<klab::UInt8>::MAX     = std::numeric_limits<klab::UInt8>::max();
const int TTypeInfo<klab::UInt8>::PRECISION       = 1;
const klab::UInt8 TTypeInfo<klab::UInt8>::DELTA   = std::numeric_limits<klab::UInt8>::epsilon();
const klab::UInt8 TTypeInfo<klab::UInt8>::EPSILON = 0;

// ---------------------------------------------------------------------------------------------------- //

const klab::Int8 TTypeInfo<klab::Int8>::ZERO     = 0;
const klab::Int8 TTypeInfo<klab::Int8>::UNIT     = 1;
const klab::Int8 TTypeInfo<klab::Int8>::MIN      = std::numeric_limits<klab::Int8>::min();
const klab::Int8 TTypeInfo<klab::Int8>::MAX      = std::numeric_limits<klab::Int8>::max();
const int TTypeInfo<klab::Int8>::PRECISION       = 1;
const klab::Int8 TTypeInfo<klab::Int8>::DELTA    = std::numeric_limits<klab::Int8>::epsilon();
const klab::Int8 TTypeInfo<klab::Int8>::EPSILON  = 0;

// ---------------------------------------------------------------------------------------------------- //

const klab::UInt16 TTypeInfo<klab::UInt16>::ZERO    = 0;
const klab::UInt16 TTypeInfo<klab::UInt16>::UNIT    = 1;
const klab::UInt16 TTypeInfo<klab::UInt16>::MIN     = std::numeric_limits<klab::UInt16>::min();
const klab::UInt16 TTypeInfo<klab::UInt16>::MAX     = std::numeric_limits<klab::UInt16>::max();
const int TTypeInfo<klab::UInt16>::PRECISION        = 1;
const klab::UInt16 TTypeInfo<klab::UInt16>::DELTA   = std::numeric_limits<klab::UInt16>::epsilon();
const klab::UInt16 TTypeInfo<klab::UInt16>::EPSILON = 0;

// ---------------------------------------------------------------------------------------------------- //

const klab::Int16 TTypeInfo<klab::Int16>::ZERO    = 0;
const klab::Int16 TTypeInfo<klab::Int16>::UNIT    = 1;
const klab::Int16 TTypeInfo<klab::Int16>::MIN     = std::numeric_limits<klab::Int16>::min();
const klab::Int16 TTypeInfo<klab::Int16>::MAX     = std::numeric_limits<klab::Int16>::max();
const int TTypeInfo<klab::Int16>::PRECISION       = 1;
const klab::Int16 TTypeInfo<klab::Int16>::DELTA   = std::numeric_limits<klab::Int16>::epsilon();
const klab::Int16 TTypeInfo<klab::Int16>::EPSILON = 0;

// ---------------------------------------------------------------------------------------------------- //

const klab::UInt32 TTypeInfo<klab::UInt32>::ZERO= 0;
const klab::UInt32 TTypeInfo<klab::UInt32>::UNIT= 1;
const klab::UInt32 TTypeInfo<klab::UInt32>::MIN = std::numeric_limits<klab::UInt32>::min();
const klab::UInt32 TTypeInfo<klab::UInt32>::MAX = std::numeric_limits<klab::UInt32>::max();
const int TTypeInfo<klab::UInt32>::PRECISION        = 1;
const klab::UInt32 TTypeInfo<klab::UInt32>::DELTA   = std::numeric_limits<klab::UInt32>::epsilon();
const klab::UInt32 TTypeInfo<klab::UInt32>::EPSILON = 0;

// ---------------------------------------------------------------------------------------------------- //

const klab::Int32 TTypeInfo<klab::Int32>::ZERO  = 0;
const klab::Int32 TTypeInfo<klab::Int32>::UNIT  = 1;
const klab::Int32  TTypeInfo<klab::Int32>::MIN  = std::numeric_limits<klab::Int32>::min();
const klab::Int32  TTypeInfo<klab::Int32>::MAX  = std::numeric_limits<klab::Int32>::max();
const int TTypeInfo<klab::Int32>::PRECISION       = 1;
const klab::Int32 TTypeInfo<klab::Int32>::DELTA   = std::numeric_limits<klab::Int32>::epsilon();
const klab::Int32 TTypeInfo<klab::Int32>::EPSILON = 0;

// ---------------------------------------------------------------------------------------------------- //

const klab::UInt64 TTypeInfo<klab::UInt64>::ZERO= 0;
const klab::UInt64 TTypeInfo<klab::UInt64>::UNIT= 1;
const klab::UInt64 TTypeInfo<klab::UInt64>::MIN = std::numeric_limits<klab::UInt64>::min();
const klab::UInt64 TTypeInfo<klab::UInt64>::MAX = std::numeric_limits<klab::UInt64>::max();
const int TTypeInfo<klab::UInt64>::PRECISION        = 1;
const klab::UInt64 TTypeInfo<klab::UInt64>::DELTA   = std::numeric_limits<klab::UInt64>::epsilon();
const klab::UInt64 TTypeInfo<klab::UInt64>::EPSILON = 0;

// ---------------------------------------------------------------------------------------------------- //

const klab::Int64 TTypeInfo<klab::Int64>::ZERO  = 0;
const klab::Int64 TTypeInfo<klab::Int64>::UNIT  = 1;
const klab::Int64  TTypeInfo<klab::Int64>::MIN  = std::numeric_limits<klab::Int64>::min();
const klab::Int64  TTypeInfo<klab::Int64>::MAX  = std::numeric_limits<klab::Int64>::max();
const int TTypeInfo<klab::Int64>::PRECISION       = 1;
const klab::Int64 TTypeInfo<klab::Int64>::DELTA   = std::numeric_limits<klab::Int64>::epsilon();
const klab::Int64 TTypeInfo<klab::Int64>::EPSILON = 0;

// ---------------------------------------------------------------------------------------------------- //
