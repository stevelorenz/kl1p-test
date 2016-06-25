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

#include "FuncUtilUnitTest.h"
#include "../include/FuncUtil.h"
#include "../include/TypeUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KFuncUtilUnitTest::KFuncUtilUnitTest() : Test::Suite()
{
    TEST_ADD(KFuncUtilUnitTest::testEquals)
    TEST_ADD(KFuncUtilUnitTest::testAbs)
    TEST_ADD(KFuncUtilUnitTest::testMin)
    TEST_ADD(KFuncUtilUnitTest::testMax)
    TEST_ADD(KFuncUtilUnitTest::testIsPowerOf2)
    TEST_ADD(KFuncUtilUnitTest::testRoundUpToPowerOf2)
    TEST_ADD(KFuncUtilUnitTest::testCastTo)
    TEST_ADD(KFuncUtilUnitTest::testSleep)
}

// ---------------------------------------------------------------------------------------------------- //

KFuncUtilUnitTest::~KFuncUtilUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KFuncUtilUnitTest::testAbs()
{
    try
    {
        TEST_ASSERT(klab::Equals(Abs(1.2345f), 1.2345f))
        TEST_ASSERT(klab::Equals(Abs(-1.2345f), 1.2345f))
        TEST_ASSERT(klab::Equals(Abs(std::complex<klab::Real>(1.23f, 4.56f)), 4.72297576f))
        TEST_ASSERT(klab::Equals(Abs(std::complex<klab::Real>(-1.23f, 4.56f)), 4.72297576f))
        TEST_ASSERT(klab::Equals(Abs(std::complex<klab::Real>(1.23f, -4.56f)), 4.72297576f))
        TEST_ASSERT(klab::Equals(Abs(std::complex<klab::Real>(-1.23f, -4.56f)), 4.72297576f))


        // Limit cases.
        TEST_ASSERT(klab::Equals(Abs(0.0f), 0.0f))
        TEST_ASSERT(klab::Equals(Abs(-0.0f), 0.0f))
        TEST_ASSERT(klab::Equals(Abs(std::complex<klab::Real>(0.0f, 0.0f)), 0.0f))
        TEST_ASSERT(klab::Equals(Abs(std::complex<klab::Real>(0.0f, -0.0f)), 0.0f))
        TEST_ASSERT(klab::Equals(Abs(std::complex<klab::Real>(-0.0f, 0.0f)), 0.0f))
        TEST_ASSERT(klab::Equals(Abs(std::complex<klab::Real>(-0.0f, -0.0f)), 0.0f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFuncUtilUnitTest::testEquals()
{
    try
    {
        // Integer values comparison.
        klab::Int32 iEpsilon = klab::TTypeInfo<klab::Int32>::EPSILON;
        TEST_ASSERT(iEpsilon == 0)
        TEST_ASSERT(klab::Equals<klab::Int32>(1, 1))   
        TEST_ASSERT(klab::Equals<klab::Int32>(1, 0) == false)
        TEST_ASSERT(klab::Equals<klab::Int32>(0, 1) == false)
        TEST_ASSERT(klab::Equals<klab::Int32>(1, 1, 0)) 
        TEST_ASSERT(klab::Equals<klab::Int32>(1, 0, 0) == false)
        TEST_ASSERT(klab::Equals<klab::Int32>(0, 1, 0) == false)
        TEST_ASSERT(klab::Equals<klab::Int32>(1, 0, 1))
        TEST_ASSERT(klab::Equals<klab::Int32>(0, 1, 1))


        // Floating point values comparison.
        klab::Real fEpsilon = klab::TTypeInfo<klab::Real>::EPSILON;
        TEST_ASSERT(fEpsilon > 0.0f)
        TEST_ASSERT(klab::Equals(1.0f, 1.0f))   
        TEST_ASSERT(klab::Equals(1.0f, 0.0f) == false)
        TEST_ASSERT(klab::Equals(0.0f, 1.0f) == false)
        TEST_ASSERT(klab::Equals(1.0f, 1.0f, 0.0f))   
        TEST_ASSERT(klab::Equals(1.0f, 1.000001f))
        TEST_ASSERT(klab::Equals(1.0f, 1.000001f, fEpsilon))
        TEST_ASSERT(klab::Equals(1.0f, 1.000002f) == false)
        TEST_ASSERT(klab::Equals(1.0f, 1.000002f, fEpsilon) == false)
        TEST_ASSERT(klab::Equals(1.0f, 1.000002f, 0.00001f))

        // Double-floating point values comparison.
        klab::DoubleReal dEpsilon = klab::TTypeInfo<klab::DoubleReal>::EPSILON;
        TEST_ASSERT(dEpsilon > 0.0)
        TEST_ASSERT(klab::Equals(1.0, 1.0))   
        TEST_ASSERT(klab::Equals(1.0, 0.0) == false)
        TEST_ASSERT(klab::Equals(0.0, 1.0) == false)
        TEST_ASSERT(klab::Equals(1.0, 1.0, 0.0))   
        TEST_ASSERT(klab::Equals(1.0, 1.0000000000000001))
        TEST_ASSERT(klab::Equals(1.0, 1.0000000000000001, dEpsilon))
        TEST_ASSERT(klab::Equals(1.0, 1.000001) == false)
        TEST_ASSERT(klab::Equals(1.0, 1.000001, dEpsilon) == false)
        TEST_ASSERT(klab::Equals(1.0, 1.000001, 0.000001))


        // Complex values comparison.
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(1.0f, 2.0f)))   
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(0.0f, 0.0f)) == false)
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(0.0f, 0.0f), std::complex<klab::Real>(1.0f, 2.0f)) == false)
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(1.0f, 2.0f), 0.0f))  
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(1.0000001f, 2.0000001f)))  
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(1.00001f, 2.000001f)) == false)
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(1.00001f, 2.00001f)) == false) 
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(1.00001f, 2.00001f)) == false) 
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(1.000001f, 2.0000001f), 0.000001f))
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(1.0000001f, 2.000001f), 0.000001f)) 
        TEST_ASSERT(klab::Equals(std::complex<klab::Real>(1.0f, 2.0f), std::complex<klab::Real>(1.000001f, 2.000001f), 0.000001f)) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFuncUtilUnitTest::testMin()
{
    try
    {
        TEST_ASSERT(klab::Min(123, 456) == 123)
        TEST_ASSERT(klab::Min(456, 123) == 123)
        TEST_ASSERT(klab::Min(456, 789) == 456)
        TEST_ASSERT(klab::Min(789, 456) == 456)
        TEST_ASSERT(klab::Min(123, 123) == 123)
        TEST_ASSERT(klab::Min(456, 456) == 456)
        TEST_ASSERT(klab::Min(123, -456) == -456)
        TEST_ASSERT(klab::Min(-456, 123) == -456)

        TEST_ASSERT(klab::Min(123.0, 456.0) == 123.0)
        TEST_ASSERT(klab::Min(456.0, 123.0) == 123.0)
        TEST_ASSERT(klab::Min(456.0, 789.0) == 456.0)
        TEST_ASSERT(klab::Min(789.0, 456.0) == 456.0)
        TEST_ASSERT(klab::Min(123.0, 123.0) == 123.0)
        TEST_ASSERT(klab::Min(456.0, 456.0) == 456.0)
        TEST_ASSERT(klab::Min(123.0, -456.0) == -456.0)
        TEST_ASSERT(klab::Min(-456.0, 123.0) == -456.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFuncUtilUnitTest::testMax()
{
    try
    {
        TEST_ASSERT(klab::Max(123, 456) == 456)
        TEST_ASSERT(klab::Max(456, 123) == 456)
        TEST_ASSERT(klab::Max(456, 789) == 789)
        TEST_ASSERT(klab::Max(789, 456) == 789)
        TEST_ASSERT(klab::Max(123, 123) == 123)
        TEST_ASSERT(klab::Max(456, 456) == 456)
        TEST_ASSERT(klab::Max(123, -456) == 123)
        TEST_ASSERT(klab::Max(-456, 123) == 123)

        TEST_ASSERT(klab::Max(123.0, 456.0) == 456.0)
        TEST_ASSERT(klab::Max(456.0, 123.0) == 456.0)
        TEST_ASSERT(klab::Max(456.0, 789.0) == 789.0)
        TEST_ASSERT(klab::Max(789.0, 456.0) == 789.0)
        TEST_ASSERT(klab::Max(123.0, 123.0) == 123.0)
        TEST_ASSERT(klab::Max(456.0, 456.0) == 456.0)
        TEST_ASSERT(klab::Max(123.0, -456.0) == 123.0)
        TEST_ASSERT(klab::Max(-456.0, 123.0) == 123.0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFuncUtilUnitTest::testIsPowerOf2()
{
    try
    {
        TEST_ASSERT(klab::IsPowerOf2(0) == false)
        TEST_ASSERT(klab::IsPowerOf2(1) == true)
        TEST_ASSERT(klab::IsPowerOf2(2) == true)
        TEST_ASSERT(klab::IsPowerOf2(4) == true)
        TEST_ASSERT(klab::IsPowerOf2(8) == true)
        TEST_ASSERT(klab::IsPowerOf2(16) == true)
        TEST_ASSERT(klab::IsPowerOf2(32) == true)
        TEST_ASSERT(klab::IsPowerOf2(64) == true)
        TEST_ASSERT(klab::IsPowerOf2(128) == true)
        TEST_ASSERT(klab::IsPowerOf2(256) == true)
        TEST_ASSERT(klab::IsPowerOf2(512) == true)
        TEST_ASSERT(klab::IsPowerOf2(1024) == true)
        TEST_ASSERT(klab::IsPowerOf2(2048) == true)
        TEST_ASSERT(klab::IsPowerOf2(4096) == true)
        TEST_ASSERT(klab::IsPowerOf2(8192) == true)
        TEST_ASSERT(klab::IsPowerOf2(16384) == true)
        TEST_ASSERT(klab::IsPowerOf2(32768) == true)
        TEST_ASSERT(klab::IsPowerOf2(65536) == true)
        TEST_ASSERT(klab::IsPowerOf2(131072) == true)
        TEST_ASSERT(klab::IsPowerOf2(262144) == true)
        TEST_ASSERT(klab::IsPowerOf2(524288) == true)
        TEST_ASSERT(klab::IsPowerOf2(1048576) == true)
        TEST_ASSERT(klab::IsPowerOf2(2097152) == true)
        TEST_ASSERT(klab::IsPowerOf2(4194304) == true)
        TEST_ASSERT(klab::IsPowerOf2(8388608) == true)
        TEST_ASSERT(klab::IsPowerOf2(16777216) == true)
        TEST_ASSERT(klab::IsPowerOf2(33554432) == true)
        TEST_ASSERT(klab::IsPowerOf2(67108864) == true)
        TEST_ASSERT(klab::IsPowerOf2(134217728) == true)
        TEST_ASSERT(klab::IsPowerOf2(268435456) == true)
        TEST_ASSERT(klab::IsPowerOf2(536870912) == true)
        TEST_ASSERT(klab::IsPowerOf2(1073741824) == true)
        TEST_ASSERT(klab::IsPowerOf2(2147483648ULL) == true)
        TEST_ASSERT(klab::IsPowerOf2(4294967296ULL) == true)

        TEST_ASSERT(klab::IsPowerOf2(3) == false)
        TEST_ASSERT(klab::IsPowerOf2(24) == false)
        TEST_ASSERT(klab::IsPowerOf2(63) == false)
        TEST_ASSERT(klab::IsPowerOf2(511) == false) 
        TEST_ASSERT(klab::IsPowerOf2(513) == false)        
        TEST_ASSERT(klab::IsPowerOf2(200000) == false)
        TEST_ASSERT(klab::IsPowerOf2(4294967295ULL) == false) 

        TEST_ASSERT(klab::IsPowerOf2(-1) == false)
        TEST_ASSERT(klab::IsPowerOf2(-2) == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFuncUtilUnitTest::testRoundUpToPowerOf2()
{
    try
    {
        TEST_ASSERT(klab::RoundUpToPowerOf2(0) == 1)
        TEST_ASSERT(klab::RoundUpToPowerOf2(1) == 1)
        TEST_ASSERT(klab::RoundUpToPowerOf2(2) == 2)
        TEST_ASSERT(klab::RoundUpToPowerOf2(4) == 4)
        TEST_ASSERT(klab::RoundUpToPowerOf2(8) == 8)
        TEST_ASSERT(klab::RoundUpToPowerOf2(16) == 16)
        TEST_ASSERT(klab::RoundUpToPowerOf2(32) == 32)
        TEST_ASSERT(klab::RoundUpToPowerOf2(64) == 64)
        TEST_ASSERT(klab::RoundUpToPowerOf2(128) == 128)
        TEST_ASSERT(klab::RoundUpToPowerOf2(256) == 256)
        TEST_ASSERT(klab::RoundUpToPowerOf2(512) == 512)
        TEST_ASSERT(klab::RoundUpToPowerOf2(1024) == 1024)
        TEST_ASSERT(klab::RoundUpToPowerOf2(2048) == 2048)
        TEST_ASSERT(klab::RoundUpToPowerOf2(4096) == 4096)
        TEST_ASSERT(klab::RoundUpToPowerOf2(8192) == 8192)
        TEST_ASSERT(klab::RoundUpToPowerOf2(16384) == 16384)
        TEST_ASSERT(klab::RoundUpToPowerOf2(32768) == 32768)
        TEST_ASSERT(klab::RoundUpToPowerOf2(65536) == 65536)
        TEST_ASSERT(klab::RoundUpToPowerOf2(131072) == 131072)
        TEST_ASSERT(klab::RoundUpToPowerOf2(262144) == 262144)
        TEST_ASSERT(klab::RoundUpToPowerOf2(524288) == 524288)
        TEST_ASSERT(klab::RoundUpToPowerOf2(1048576) == 1048576)
        TEST_ASSERT(klab::RoundUpToPowerOf2(2097152) == 2097152)
        TEST_ASSERT(klab::RoundUpToPowerOf2(4194304) == 4194304)
        TEST_ASSERT(klab::RoundUpToPowerOf2(8388608) == 8388608)
        TEST_ASSERT(klab::RoundUpToPowerOf2(16777216) == 16777216)
        TEST_ASSERT(klab::RoundUpToPowerOf2(33554432) == 33554432)
        TEST_ASSERT(klab::RoundUpToPowerOf2(67108864) == 67108864)
        TEST_ASSERT(klab::RoundUpToPowerOf2(134217728) == 134217728)
        TEST_ASSERT(klab::RoundUpToPowerOf2(268435456) == 268435456)
        TEST_ASSERT(klab::RoundUpToPowerOf2(536870912) == 536870912)
        TEST_ASSERT(klab::RoundUpToPowerOf2(1073741824) == 1073741824)
        TEST_ASSERT(klab::RoundUpToPowerOf2(2147483648ULL) == 2147483648ULL)
        TEST_ASSERT(klab::RoundUpToPowerOf2(4294967296ULL) == 4294967296ULL)

        TEST_ASSERT(klab::RoundUpToPowerOf2(3) == 4)
        TEST_ASSERT(klab::RoundUpToPowerOf2(24) == 32)
        TEST_ASSERT(klab::RoundUpToPowerOf2(63) == 64)
        TEST_ASSERT(klab::RoundUpToPowerOf2(65) == 128)        
        TEST_ASSERT(klab::RoundUpToPowerOf2(511) == 512) 
        TEST_ASSERT(klab::RoundUpToPowerOf2(513) == 1024)
        TEST_ASSERT(klab::RoundUpToPowerOf2(200000) == 262144)        
        TEST_ASSERT(klab::RoundUpToPowerOf2(static_cast<klab::UInt64>(4294967295ULL)) == static_cast<klab::UInt64>(4294967296ULL))

        TEST_ASSERT(klab::RoundUpToPowerOf2(-1) == 1)
        TEST_ASSERT(klab::RoundUpToPowerOf2(-2) == 1)
        TEST_ASSERT(klab::RoundUpToPowerOf2(-3) == 1)
        TEST_ASSERT(klab::RoundUpToPowerOf2(-4) == 1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFuncUtilUnitTest::testCastTo()
{
    try
    {
        TEST_ASSERT(klab::CastTo<klab::UInt32>(1.2345) == 1)
        TEST_ASSERT(klab::Equals(klab::CastTo<klab::DoubleReal>(1), 1.0))
        TEST_ASSERT(klab::Equals(klab::CastTo<std::complex<klab::DoubleReal> >(1.2345), std::complex<klab::DoubleReal>(1.2345, 0.0)))
        TEST_ASSERT(klab::Equals(klab::CastTo<klab::DoubleReal>(std::complex<klab::DoubleReal>(1.2345, 6.789)), 1.2345))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFuncUtilUnitTest::testSleep()
{
    try
    {
        klab::Sleep(10);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
