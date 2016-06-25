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

#include "TypeInfoUnitTest.h"
#include "../include/TypeUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KTypeInfoUnitTest::KTypeInfoUnitTest() : Test::Suite()
{
    TEST_ADD(KTypeInfoUnitTest::testUInt8TypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testInt8TypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testUInt16TypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testInt16TypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testUInt32TypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testInt32TypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testUInt64TypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testInt64TypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testRealTypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testDoubleRealTypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testComplexRealTypeInfo)
    TEST_ADD(KTypeInfoUnitTest::testComplexDoubleRealTypeInfo)
}

// ---------------------------------------------------------------------------------------------------- //

KTypeInfoUnitTest::~KTypeInfoUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testUInt8TypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::UInt8>::ZERO == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt8>::UNIT == 1);
        TEST_ASSERT(TTypeInfo<klab::UInt8>::MIN  == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt8>::MAX  == 255);
        TEST_ASSERT(TTypeInfo<klab::UInt8>::PRECISION == 1);
        TEST_ASSERT(TTypeInfo<klab::UInt8>::DELTA     == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt8>::EPSILON   == 0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testInt8TypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::Int8>::ZERO == 0);
        TEST_ASSERT(TTypeInfo<klab::Int8>::UNIT == 1);
        TEST_ASSERT(TTypeInfo<klab::Int8>::MIN  == -128);
        TEST_ASSERT(TTypeInfo<klab::Int8>::MAX  == 127);
        TEST_ASSERT(TTypeInfo<klab::Int8>::PRECISION == 1);
        TEST_ASSERT(TTypeInfo<klab::Int8>::DELTA     == 0);
        TEST_ASSERT(TTypeInfo<klab::Int8>::EPSILON   == 0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testUInt16TypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::UInt16>::ZERO == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt16>::UNIT == 1);
        TEST_ASSERT(TTypeInfo<klab::UInt16>::MIN  == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt16>::MAX  == 65535);
        TEST_ASSERT(TTypeInfo<klab::UInt16>::PRECISION == 1);
        TEST_ASSERT(TTypeInfo<klab::UInt16>::DELTA     == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt16>::EPSILON   == 0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testInt16TypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::Int16>::ZERO == 0);
        TEST_ASSERT(TTypeInfo<klab::Int16>::UNIT == 1);
        TEST_ASSERT(TTypeInfo<klab::Int16>::MIN  == -32768);
        TEST_ASSERT(TTypeInfo<klab::Int16>::MAX  == 32767);
        TEST_ASSERT(TTypeInfo<klab::Int16>::PRECISION == 1);
        TEST_ASSERT(TTypeInfo<klab::Int16>::DELTA     == 0);
        TEST_ASSERT(TTypeInfo<klab::Int16>::EPSILON   == 0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testUInt32TypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::UInt32>::ZERO == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt32>::UNIT == 1);
        TEST_ASSERT(TTypeInfo<klab::UInt32>::MIN  == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt32>::MAX  == std::numeric_limits<klab::UInt32>::max());
        TEST_ASSERT(TTypeInfo<klab::UInt32>::PRECISION == 1);
        TEST_ASSERT(TTypeInfo<klab::UInt32>::DELTA     == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt32>::EPSILON   == 0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testInt32TypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::Int32>::ZERO == 0);
        TEST_ASSERT(TTypeInfo<klab::Int32>::UNIT == 1);
        TEST_ASSERT(TTypeInfo<klab::Int32>::MIN  == std::numeric_limits<klab::Int32>::min());
        TEST_ASSERT(TTypeInfo<klab::Int32>::MAX  == std::numeric_limits<klab::Int32>::max());
        TEST_ASSERT(TTypeInfo<klab::Int32>::PRECISION == 1);
        TEST_ASSERT(TTypeInfo<klab::Int32>::DELTA     == 0);
        TEST_ASSERT(TTypeInfo<klab::Int32>::EPSILON   == 0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testUInt64TypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::UInt64>::ZERO == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt64>::UNIT == 1);
        TEST_ASSERT(TTypeInfo<klab::UInt64>::MIN  == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt64>::MAX  == std::numeric_limits<klab::UInt64>::max());
        TEST_ASSERT(TTypeInfo<klab::UInt64>::PRECISION == 1);
        TEST_ASSERT(TTypeInfo<klab::UInt64>::DELTA     == 0);
        TEST_ASSERT(TTypeInfo<klab::UInt64>::EPSILON   == 0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testInt64TypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::Int64>::ZERO == 0);
        TEST_ASSERT(TTypeInfo<klab::Int64>::UNIT == 1);
        TEST_ASSERT(TTypeInfo<klab::Int64>::MIN  == std::numeric_limits<klab::Int64>::min());
        TEST_ASSERT(TTypeInfo<klab::Int64>::MAX  == std::numeric_limits<klab::Int64>::max());
        TEST_ASSERT(TTypeInfo<klab::Int64>::PRECISION == 1);
        TEST_ASSERT(TTypeInfo<klab::Int64>::DELTA     == 0);
        TEST_ASSERT(TTypeInfo<klab::Int64>::EPSILON   == 0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testRealTypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::Real>::ZERO == 0.0f);
        TEST_ASSERT(TTypeInfo<klab::Real>::UNIT == 1.0f);
        TEST_ASSERT(TTypeInfo<klab::Real>::MIN  == FLT_MIN);
        TEST_ASSERT(TTypeInfo<klab::Real>::MAX  == FLT_MAX);
        TEST_ASSERT(TTypeInfo<klab::Real>::PRECISION == 6);
        TEST_ASSERT(TTypeInfo<klab::Real>::DELTA     == FLT_EPSILON);
        TEST_ASSERT(TTypeInfo<klab::Real>::EPSILON<=1e-6 && TTypeInfo<klab::Real>::EPSILON>0);
        TEST_ASSERT(klab::REAL_EPSILON<=1e-6 && klab::REAL_EPSILON>0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testDoubleRealTypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<klab::DoubleReal>::ZERO == 0.0);
        TEST_ASSERT(TTypeInfo<klab::DoubleReal>::UNIT == 1.0);
        TEST_ASSERT(TTypeInfo<klab::DoubleReal>::MIN  == DBL_MIN);
        TEST_ASSERT(TTypeInfo<klab::DoubleReal>::MAX  == DBL_MAX);
        TEST_ASSERT(TTypeInfo<klab::DoubleReal>::PRECISION == 15);
        TEST_ASSERT(TTypeInfo<klab::DoubleReal>::DELTA     == DBL_EPSILON);
        TEST_ASSERT(TTypeInfo<klab::DoubleReal>::EPSILON   <= 1e-15 && TTypeInfo<klab::DoubleReal>::EPSILON>0);
        TEST_ASSERT(klab::DOUBLEREAL_EPSILON<=1e-15 && klab::DOUBLEREAL_EPSILON>0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testComplexRealTypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<std::complex<klab::Real> >::ZERO == std::complex<klab::Real>(0.0f, 0.0f));
        TEST_ASSERT(TTypeInfo<std::complex<klab::Real> >::UNIT == std::complex<klab::Real>(1.0f, 0.0f));
        TEST_ASSERT(TTypeInfo<std::complex<klab::Real> >::MIN  == std::complex<klab::Real>(FLT_MIN, FLT_MIN));
        TEST_ASSERT(TTypeInfo<std::complex<klab::Real> >::MAX  == std::complex<klab::Real>(FLT_MAX, FLT_MAX));
        TEST_ASSERT(TTypeInfo<std::complex<klab::Real> >::PRECISION == 6);
        TEST_ASSERT(TTypeInfo<std::complex<klab::Real> >::DELTA     == FLT_EPSILON);
        TEST_ASSERT(TTypeInfo<std::complex<klab::Real> >::EPSILON<=1e-6 && TTypeInfo<std::complex<klab::Real> >::EPSILON>0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KTypeInfoUnitTest::testComplexDoubleRealTypeInfo()
{
    try
    {
        TEST_ASSERT(TTypeInfo<std::complex<klab::DoubleReal> >::ZERO == std::complex<klab::DoubleReal>(0.0, 0.0));
        TEST_ASSERT(TTypeInfo<std::complex<klab::DoubleReal> >::UNIT == std::complex<klab::DoubleReal>(1.0, 0.0));
        TEST_ASSERT(TTypeInfo<std::complex<klab::DoubleReal> >::MIN  == std::complex<klab::DoubleReal>(DBL_MIN, DBL_MIN));
        TEST_ASSERT(TTypeInfo<std::complex<klab::DoubleReal> >::MAX  == std::complex<klab::DoubleReal>(DBL_MAX, DBL_MAX));
        TEST_ASSERT(TTypeInfo<std::complex<klab::DoubleReal> >::PRECISION == 15);
        TEST_ASSERT(TTypeInfo<std::complex<klab::DoubleReal> >::DELTA     == DBL_EPSILON);
        TEST_ASSERT(TTypeInfo<std::complex<klab::DoubleReal> >::EPSILON<= 1e-15 && TTypeInfo<std::complex<klab::DoubleReal> >::EPSILON>0);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
