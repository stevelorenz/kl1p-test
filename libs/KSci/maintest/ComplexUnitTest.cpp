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

#include "ComplexUnitTest.h"
#include "../include/Complex.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KComplexUnitTest::KComplexUnitTest() : Test::Suite()
{
    TEST_ADD(KComplexUnitTest::testDefaultConstructor)
    TEST_ADD(KComplexUnitTest::testValueConstructor)
    TEST_ADD(KComplexUnitTest::testRealImaginaryConstructor)
    TEST_ADD(KComplexUnitTest::testStdComplexConstructor)
    TEST_ADD(KComplexUnitTest::testCopyConstructor)
    TEST_ADD(KComplexUnitTest::testValueAffectationOperator)
    TEST_ADD(KComplexUnitTest::testStdComplexAffectationOperator)
    TEST_ADD(KComplexUnitTest::testAffectationOperator)

    TEST_ADD(KComplexUnitTest::testEqualOperator)
    TEST_ADD(KComplexUnitTest::testNotEqualOperator)
    TEST_ADD(KComplexUnitTest::testAddAndAffectOperator)
    TEST_ADD(KComplexUnitTest::testSubstractAndAffectOperator)
    TEST_ADD(KComplexUnitTest::testMultiplyAndAffectOperator)
    TEST_ADD(KComplexUnitTest::testDivideAndAffectOperator)
    TEST_ADD(KComplexUnitTest::testAddOperator)
    TEST_ADD(KComplexUnitTest::testSubstractOperator)
    TEST_ADD(KComplexUnitTest::testMultiplyOperator)
    TEST_ADD(KComplexUnitTest::testDivideOperator)
    TEST_ADD(KComplexUnitTest::testSignOperator)

    TEST_ADD(KComplexUnitTest::testSet)
    TEST_ADD(KComplexUnitTest::testSetPolar)
    TEST_ADD(KComplexUnitTest::testSetReal)
    TEST_ADD(KComplexUnitTest::testSetImaginary)
    TEST_ADD(KComplexUnitTest::testReal)
    TEST_ADD(KComplexUnitTest::testImaginary)
    TEST_ADD(KComplexUnitTest::testConjugue)
    TEST_ADD(KComplexUnitTest::testConjugate)
    TEST_ADD(KComplexUnitTest::testAbsolute)
    TEST_ADD(KComplexUnitTest::testModulus)
    TEST_ADD(KComplexUnitTest::testArgument)
    TEST_ADD(KComplexUnitTest::testNorm)
    TEST_ADD(KComplexUnitTest::testEquals)

    TEST_ADD(KComplexUnitTest::testStdComplexCastOperator)

    TEST_ADD(KComplexUnitTest::testAbs)
    TEST_ADD(KComplexUnitTest::testConj)
    TEST_ADD(KComplexUnitTest::testEqualsFunction)
    TEST_ADD(KComplexUnitTest::testCos)
    TEST_ADD(KComplexUnitTest::testCosH)
    TEST_ADD(KComplexUnitTest::testSin)
    TEST_ADD(KComplexUnitTest::testSinH)
    TEST_ADD(KComplexUnitTest::testTan)
    TEST_ADD(KComplexUnitTest::testTanH)
    TEST_ADD(KComplexUnitTest::testSqrt)
    TEST_ADD(KComplexUnitTest::testExp)
    TEST_ADD(KComplexUnitTest::testLog)
    TEST_ADD(KComplexUnitTest::testLog10)
    TEST_ADD(KComplexUnitTest::testPow)
    TEST_ADD(KComplexUnitTest::testOstreamOperator)

    TEST_ADD(KComplexUnitTest::testTypeInfoConstants)
}

// ---------------------------------------------------------------------------------------------------- //

KComplexUnitTest::~KComplexUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testDefaultConstructor()
{
    try
    {
        TComplex<klab::Real> c1;
        TEST_ASSERT(c1.real()==0.0f && c1.imaginary()==0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testValueConstructor()
{
    try
    {
        TComplex<klab::Real> c1(1.234f);
        TEST_ASSERT(c1.real()==1.234f && c1.imaginary()==0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testRealImaginaryConstructor()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TEST_ASSERT(c1.real()==1.234f && c1.imaginary()==5.678f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testStdComplexConstructor()
{
    try
    {
        std::complex<klab::Real> cs1(1.234f, 5.678f);
        TComplex<klab::Real> c1copy(cs1);
        TEST_ASSERT(c1copy.real()==1.234f && c1copy.imaginary()==5.678f && c1copy==cs1 && cs1==static_cast<std::complex<klab::Real> >(c1copy))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testCopyConstructor()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c1copy(c1);
        TEST_ASSERT(c1copy.real()==1.234f && c1copy.imaginary()==5.678f && c1copy==c1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testValueAffectationOperator()
{
    try
    {
        TComplex<klab::Real> c1;
        c1 = 1.234f;
        TEST_ASSERT(c1.real()==1.234f && c1.imaginary()==0.0f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testStdComplexAffectationOperator()
{
    try
    {
        std::complex<klab::Real> cs1(1.234f, 5.678f);
        TComplex<klab::Real> c1copy;
        c1copy = cs1;
        TEST_ASSERT(c1copy.real()==1.234f && c1copy.imaginary()==5.678f && c1copy==cs1 && cs1==static_cast<std::complex<klab::Real> >(c1copy))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testAffectationOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c1copy;
        c1copy = c1;
        TEST_ASSERT(c1copy.real()==1.234f && c1copy.imaginary()==5.678f && c1copy==c1)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testEqualOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(c1);
        TComplex<klab::Real> c3;
        TEST_ASSERT(c1==c2 && c2==c1)
        TEST_ASSERT((c1==c3)==false && (c3==c1)==false && (c2==c3)==false && (c3==c2)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testNotEqualOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(c1);
        TComplex<klab::Real> c3;
        TEST_ASSERT((c1!=c2)==false && (c2!=c1)==false)
        TEST_ASSERT(c1!=c3 && c3!=c1 && c2!=c3 && c3!=c2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testAddAndAffectOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(4.321f, 8.765f);
        TComplex<klab::Real> c3(-4.321f, -8.765f);

        TComplex<klab::Real> result1(5.555f, 14.443f);
        TComplex<klab::Real> result2(-3.087f, -3.087f);
        TComplex<klab::Real> result3(5.555f, 5.678f);
        TComplex<klab::Real> result4(-3.087f, 5.678f);
        
        c1 += c2;
        TEST_ASSERT(c1.equals(result1))            
        c1.set(1.234f, 5.678f);
        c1 += c3;
        TEST_ASSERT(c1.equals(result2))

        c1.set(1.234f, 5.678f);
        c1 += 4.321f;
        TEST_ASSERT(c1.equals(result3))

        c1.set(1.234f, 5.678f);
        c1 += -4.321f;
        TEST_ASSERT(c1.equals(result4))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSubstractAndAffectOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(4.321f, 8.765f);
        TComplex<klab::Real> c3(-4.321f, -8.765f);

        TComplex<klab::Real> result1(-3.087f, -3.087f);
        TComplex<klab::Real> result2(5.555f, 14.443f);  
        TComplex<klab::Real> result3(-3.087f, 5.678f);
        TComplex<klab::Real> result4(5.555f, 5.678f);        

        c1 -= c2;
        TEST_ASSERT(c1.equals(result1))

        c1.set(1.234f, 5.678f);
        c1 -= c3;
        TEST_ASSERT(c1.equals(result2))

        c1.set(1.234f, 5.678f);
        c1 -= 4.321f;
        TEST_ASSERT(c1.equals(result3))

        c1.set(1.234f, 5.678f);
        c1 -= -4.321f;
        TEST_ASSERT(c1.equals(result4))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testMultiplyAndAffectOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(4.321f, 8.765f);
        TComplex<klab::Real> c3(-4.321f, -8.765f);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TComplex<klab::Real> result1(-44.435558f,  35.350647f); // -44.435556 + 35.350648i 
        TComplex<klab::Real> result2( 44.435558f, -35.350647f); //  44.435556 - 35.350648i  
        TComplex<klab::Real> result3(  5.332114f,  24.534639f); //   5.332114 + 24.534638i
        TComplex<klab::Real> result4( -5.332114f, -24.534639f); //  -5.332114 - 24.534638i

        c1 *= c2;
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        TEST_ASSERT(c1.equals(result1, 1e-5f))
#else 
        TEST_ASSERT(c1.equals(result1))
#endif

        c1.set(1.234f, 5.678f);
        c1 *= c3;
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        TEST_ASSERT(c1.equals(result2, 1e-5f))
#else 
        TEST_ASSERT(c1.equals(result2))
#endif

        c1.set(1.234f, 5.678f);
        c1 *= 4.321f;
        TEST_ASSERT(c1.equals(result3))

        c1.set(1.234f, 5.678f);
        c1 *= -4.321f;
        TEST_ASSERT(c1.equals(result4))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testDivideAndAffectOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(4.321f, 8.765f);
        TComplex<klab::Real> c3(-4.321f, -8.765f);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TComplex<klab::Real> result1( 0.57698363f,  0.14365616f);   //  0.576983648763817 + 0.143656171854929i 
        TComplex<klab::Real> result2(-0.57698363f, -0.14365616f);   // -0.576983648763817 - 0.143656171854929i 
        TComplex<klab::Real> result3( 0.28558204f,  1.31404767f);   //  0.285582041194168 + 1.3140476741495i
        TComplex<klab::Real> result4(-0.28558204f, -1.31404767f);   // -0.285582041194168 - 1.3140476741495i

        c1 /= c2;
        TEST_ASSERT(c1.equals(result1))

        c1.set(1.234f, 5.678f);
        c1 /= c3;
        TEST_ASSERT(c1.equals(result2))

        c1.set(1.234f, 5.678f);
        c1 /= 4.321f;
        TEST_ASSERT(c1.equals(result3))

        c1.set(1.234f, 5.678f);
        c1 /= -4.321f;
        TEST_ASSERT(c1.equals(result4))


        // Limit cases.
        try
        {
            TComplex<klab::Real> c10(1.234f, 5.678f);
            c10 /= TComplex<klab::Real>(0.0f, 0.0f);
            TEST_ASSERT(false)
        }
        catch(KBadArithmeticException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TComplex<klab::Real> c10(1.234f, 5.678f);
            c10 /= 0.0f;
            TEST_ASSERT(false)
        }
        catch(KBadArithmeticException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testAddOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(4.321f, 8.765f);
        TComplex<klab::Real> c3(-4.321f, -8.765f);

        TComplex<klab::Real> result1(5.555f, 14.443f);
        TComplex<klab::Real> result2(-3.087f, -3.087f);
        TComplex<klab::Real> result3(5.555f, 5.678f);
        TComplex<klab::Real> result4(-3.087f, 5.678f);

        TComplex<klab::Real> result = c1 + c2;
        TEST_ASSERT(result.equals(result1))

        c1.set(1.234f, 5.678f);
        result = c1 + c3;
        TEST_ASSERT(result.equals(result2))

        c1.set(1.234f, 5.678f);
        result = c1 + 4.321f;
        TEST_ASSERT(result.equals(result3))

        c1.set(1.234f, 5.678f);
        result = 4.321f + c1;
        TEST_ASSERT(result.equals(result3))

        c1.set(1.234f, 5.678f);
        result = -4.321f + c1;
        TEST_ASSERT(result.equals(result4))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSubstractOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(4.321f, 8.765f);
        TComplex<klab::Real> c3(-4.321f, -8.765f);

        TComplex<klab::Real> result1(-3.087f, -3.087f);
        TComplex<klab::Real> result2(5.555f, 14.443f);  
        TComplex<klab::Real> result3(-3.087f, 5.678f);
        TComplex<klab::Real> result4(3.087f, -5.678f); 
        TComplex<klab::Real> result5(-5.555f, -5.678f); 

        TComplex<klab::Real> result = c1 - c2;
        TEST_ASSERT(result.equals(result1))

        c1.set(1.234f, 5.678f);
        result = c1 - c3;
        TEST_ASSERT(result.equals(result2))

        c1.set(1.234f, 5.678f);
        result = c1 - 4.321f;
        TEST_ASSERT(result.equals(result3))

        c1.set(1.234f, 5.678f);
        result = 4.321f - c1;
        TEST_ASSERT(result.equals(result4))

        c1.set(1.234f, 5.678f);
        result = -4.321f - c1;
        TEST_ASSERT(result.equals(result5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testMultiplyOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(4.321f, 8.765f);
        TComplex<klab::Real> c3(-4.321f, -8.765f);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TComplex<klab::Real> result1(-44.435558f,  35.350647f); // -44.435556 + 35.350648i 
        TComplex<klab::Real> result2( 44.435558f, -35.350647f); //  44.435556 - 35.350648i  
        TComplex<klab::Real> result3(  5.332114f,  24.534639f); //   5.332114 + 24.534638i
        TComplex<klab::Real> result4( -5.332114f, -24.534639f); //  -5.332114 - 24.534638i

        TComplex<klab::Real> result = c1 * c2;
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        TEST_ASSERT(result.equals(result1, 1e-5f))
#else
        TEST_ASSERT(result.equals(result1))
#endif

        c1.set(1.234f, 5.678f);
        result = c1 * c3;
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        TEST_ASSERT(result.equals(result2, 1e-5f))
#else
        TEST_ASSERT(result.equals(result2))
#endif

        c1.set(1.234f, 5.678f);
        result = c1 * 4.321f;
        TEST_ASSERT(result.equals(result3))

        c1.set(1.234f, 5.678f);
        result = 4.321f * c1;
        TEST_ASSERT(result.equals(result3))

        c1.set(1.234f, 5.678f);
        result = -4.321f * c1;
        TEST_ASSERT(result.equals(result4))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testDivideOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(4.321f, 8.765f);
        TComplex<klab::Real> c3(-4.321f, -8.765f);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TComplex<klab::Real> result1( 0.57698363f,  0.14365616f);   //  0.576983648763817 + 0.143656171854929i 
        TComplex<klab::Real> result2(-0.57698363f, -0.14365616f);   // -0.576983648763817 - 0.143656171854929i 
        TComplex<klab::Real> result3( 0.28558204f,  1.31404767f);   //  0.285582041194168 + 1.3140476741495i
        TComplex<klab::Real> result4( 0.15793035f, -0.72668438f);   //  0.157930351005437 - 0.726684386555i
        TComplex<klab::Real> result5(-0.15793035f,  0.72668438f);   // -0.157930351005437 + 0.726684386555i

        TComplex<klab::Real> result = c1 / c2;
        TEST_ASSERT(result.equals(result1))

        c1.set(1.234f, 5.678f);
        result = c1 / c3;
        TEST_ASSERT(result.equals(result2))

        c1.set(1.234f, 5.678f);
        result = c1 / 4.321f;
        TEST_ASSERT(result.equals(result3))

        c1.set(1.234f, 5.678f);
        result = 4.321f / c1;
        TEST_ASSERT(result.equals(result4))

        c1.set(1.234f, 5.678f);
        result = -4.321f / c1;
        TEST_ASSERT(result.equals(result5))


        // Limit cases.
        try
        {
            TComplex<klab::Real> c10(1.234f, 5.678f);
            result = c10 / TComplex<klab::Real>(0.0f, 0.0f);
            TEST_ASSERT(false)
        }
        catch(KBadArithmeticException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }

        try
        {
            TComplex<klab::Real> c10(1.234f, 5.678f);
            result = c10 / 0.0f;
            TEST_ASSERT(false)
        }
        catch(KBadArithmeticException&)
        {
            TEST_ASSERT(true)
        }
        catch(...)
        {
            TEST_ASSERT(false)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSignOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);

        TComplex<klab::Real> result1( 1.234f,  5.678f);
        TComplex<klab::Real> result2(-1.234f, -5.678f);

        TEST_ASSERT(result1.equals(+c1))
        TEST_ASSERT(result2.equals(-c1))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSet()
{
    try
    {
        TComplex<klab::Real> c1;
        c1.set(1.234f, 5.678f);

        TEST_ASSERT(c1.equals(TComplex<klab::Real>(1.234f, 5.678f)));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSetPolar()
{
    try
    {
        TComplex<klab::Real> c1;
        c1.setPolar(1.234f, 3.14159265f);

        TEST_ASSERT(c1.equals(TComplex<klab::Real>(-1.234f, 0.0f)));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSetReal()
{
    try
    {
        TComplex<klab::Real> c1;
        c1.setReal(1.234f);

        TEST_ASSERT(c1.equals(TComplex<klab::Real>(1.234f, 0.0f)));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSetImaginary()
{
    try
    {
        TComplex<klab::Real> c1;
        c1.setImaginary(5.678f);

        TEST_ASSERT(c1.equals(TComplex<klab::Real>(0.0f, 5.678f)));
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testReal()
{
    try
    {
        TComplex<klab::Real> c1;
        c1.setReal(1.234f);

        TEST_ASSERT(c1.real() == 1.234f);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testImaginary()
{
    try
    {
        TComplex<klab::Real> c1;
        c1.setImaginary(5.678f);

        TEST_ASSERT(c1.imaginary() == 5.678f);
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testConjugue()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        c1.conjugue();

        TEST_ASSERT(c1.equals(TComplex<klab::Real>(1.234f, -5.678f)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testConjugate()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);

        TEST_ASSERT(c1.conjugate().equals(TComplex<klab::Real>(1.234f, -5.678f)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testAbsolute()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        klab::Real result = c1.absolute();

        TEST_ASSERT(result == 5.8105454f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testModulus()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        klab::Real result = c1.modulus();

        TEST_ASSERT(result == 5.8105454f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testArgument()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        klab::Real result = c1.argument();

        TEST_ASSERT(result == 1.3567941f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testNorm()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        klab::Real result = c1.norm();

        TEST_ASSERT(result == 33.76244f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testEquals()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(c1);
        TComplex<klab::Real> c3;

        TEST_ASSERT(c1.equals(c2) && c2.equals(c1))
        TEST_ASSERT(c1.equals(c3)==false && c3.equals(c1)==false && c2.equals(c3)==false && c3.equals(c2)==false)
        TEST_ASSERT(c1.equals(c2) && c2.equals(c1))
        TEST_ASSERT(c1.equals(c3)==false && c3.equals(c1)==false && c2.equals(c3)==false && c3.equals(c2)==false)


        TComplex<klab::Real> c1f_1f(1.0f, 1.0f);
        TComplex<klab::Real> c1f_1f2(1.0f, 1.0f);
        TComplex<klab::Real> c1f_100001f(1.0f, 1.00001f);
        TComplex<klab::Real> c1f_1000001f(1.0f, 1.000001f);

        TEST_ASSERT(c1f_1f.equals(c1f_1f2))    
        TEST_ASSERT(c1f_1f.equals(c1f_1f2, 0.0f))  
        TEST_ASSERT(c1f_1f.equals(c1f_1f2))  
        TEST_ASSERT(c1f_1f.equals(c1f_1000001f))    
        TEST_ASSERT(c1f_1f.equals(c1f_1000001f)) 
        TEST_ASSERT(c1f_1000001f.equals(c1f_1f))    
        TEST_ASSERT(c1f_1000001f.equals(c1f_1f)) 
        TEST_ASSERT(c1f_1f.equals(c1f_100001f)==false)    
        TEST_ASSERT(c1f_1f.equals(c1f_100001f)==false) 
        TEST_ASSERT(c1f_100001f.equals(c1f_1f)==false)    
        TEST_ASSERT(c1f_100001f.equals(c1f_1f)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testStdComplexCastOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TEST_ASSERT(c1.real()==1.234f && c1.imaginary()==5.678f)

        std::complex<klab::Real> cs1(c1);
        TEST_ASSERT(cs1.real()==1.234f && cs1.imag()==5.678f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testAbs()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = Abs(c1);

        TEST_ASSERT(result == 5.8105454f)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testConj()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);

        TEST_ASSERT(klab::Conj(c1).equals(TComplex<klab::Real>(1.234f, -5.678f)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testEqualsFunction()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> c2(c1);
        TComplex<klab::Real> c3;

        TEST_ASSERT(klab::Equals(c1, c2) && klab::Equals(c2, c1))
        TEST_ASSERT(klab::Equals(c1,c3)==false && klab::Equals(c3, c1)==false && klab::Equals(c2, c3)==false && klab::Equals(c3, c2)==false)
        TEST_ASSERT(klab::Equals(c1, c2) && klab::Equals(c2, c1))
        TEST_ASSERT(klab::Equals(c1, c3)==false && klab::Equals(c3, c1)==false && klab::Equals(c2, c3)==false && klab::Equals(c3, c2)==false)


        TComplex<klab::Real> c1f_1f(1.0f, 1.0f);
        TComplex<klab::Real> c1f_1f2(1.0f, 1.0f);
        TComplex<klab::Real> c1f_100001f(1.0f, 1.00001f);
        TComplex<klab::Real> c1f_1000001f(1.0f, 1.000001f);

        TEST_ASSERT(klab::Equals(c1f_1f, c1f_1f2))    
        TEST_ASSERT(klab::Equals(c1f_1f, c1f_1f2, 0.0f))  
        TEST_ASSERT(klab::Equals(c1f_1f, c1f_1f2))  
        TEST_ASSERT(klab::Equals(c1f_1f, c1f_1000001f))    
        TEST_ASSERT(klab::Equals(c1f_1f, c1f_1000001f)) 
        TEST_ASSERT(klab::Equals(c1f_1000001f, c1f_1f))    
        TEST_ASSERT(klab::Equals(c1f_1000001f, c1f_1f)) 
        TEST_ASSERT(klab::Equals(c1f_1f, c1f_100001f)==false)    
        TEST_ASSERT(klab::Equals(c1f_1f, c1f_100001f)==false) 
        TEST_ASSERT(klab::Equals(c1f_100001f, c1f_1f)==false)    
        TEST_ASSERT(klab::Equals(c1f_100001f, c1f_1f)==false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testCos()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = Cos(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(48.308636f, -137.96767f)))    // 48.308634849663 - 137.967674379484i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testCosH()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = CosH(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(1.5321528f, -0.89428133f)))    // 1.53215283 - 0.89428126i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSin()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = Sin(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(137.970903f, 48.307505f)))    // 137.970902608106 + 48.3075045293216i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSinH()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = SinH(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(1.2927320f, -1.0599070f)))    // 1.29273198 - 1.05990691i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testTan()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = Tan(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(0.00001459f, 1.0000182f)))    // 0.000014596 + 1.0000182877i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testTanH()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = TanH(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(0.93050611f, -0.14866191f)))    // 0.9305060883 - 0.1486619022i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testSqrt()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = Sqrt(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(1.8767718f,  1.5127039f)))    // 1.87677190747824 + 1.51270380203776i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testExp()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = Exp(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(2.8248847f, -1.9541883f)))    // 2.82488480915939 - 1.95418816956349i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testLog()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = Log(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(1.7596744f,  1.3567941f)))    // 1.75967447099878 + 1.35679413815657i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testLog10()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);
        TComplex<klab::Real> result = Log10(c1);

        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result.equals(TComplex<klab::Real>(0.76421684f, 0.58924818f)))    // 0.7642169127 + 0.5892482073i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testPow()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);

        TComplex<klab::Real> result1 = Pow(c1, 2);
        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result1.equals(TComplex<klab::Real>(-30.716923f, 14.013304f)))          // -30.716928 + 14.013304i

        TComplex<klab::Real> result2 = Pow(c1, TComplex<klab::Real>(4.321f, 8.765f));
        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result2.equals(TComplex<klab::Real>(-0.010451858f, 0.0088912761f)))     // -0.0104518530794509 + 0.00889128432760393i

        TComplex<klab::Real> result3 = Pow(c1, 4.321f);
        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result3.equals(TComplex<klab::Real>(1830.63444f, -818.56012f), 1e-3f))   // 1830.63444320777 - 818.560499536948i

        TComplex<klab::Real> result4 = Pow(4.321f, c1);
        // Note : Unprecise last digit due to operations on floating point numbers.
        TEST_ASSERT(result4.equals(TComplex<klab::Real>(-2.6782503f, 5.4646864f)))          // -2.67824665889441 + 5.46468802618435i
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testOstreamOperator()
{
    try
    {
        TComplex<klab::Real> c1(1.234f, 5.678f);

        std::ostringstream oss;
        oss<<c1; 

        TEST_ASSERT(oss.str() == "1.234+5.678i");
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KComplexUnitTest::testTypeInfoConstants()
{
    try
    {
        TComplex<klab::Real> fZero          = klab::TTypeInfo<TComplex<klab::Real> >::ZERO;
        TComplex<klab::Real> fUnit          = klab::TTypeInfo<TComplex<klab::Real> >::UNIT;
        TComplex<klab::Real> fMin           = klab::TTypeInfo<TComplex<klab::Real> >::MIN;
        TComplex<klab::Real> fMax           = klab::TTypeInfo<TComplex<klab::Real> >::MAX;
        klab::UInt32 fPrecision             = klab::TTypeInfo<TComplex<klab::Real> >::PRECISION;
        klab::Real fDelta                   = klab::TTypeInfo<TComplex<klab::Real> >::DELTA;
        klab::Real fEpsilon                 = klab::TTypeInfo<TComplex<klab::Real> >::EPSILON;

        TEST_ASSERT(fZero == TComplex<klab::Real>(0.0f, 0.0f))
        TEST_ASSERT(fUnit == TComplex<klab::Real>(1.0f, 0.0f))
        TEST_ASSERT(fMin == TComplex<klab::Real>(klab::TTypeInfo<klab::Real>::MIN, klab::TTypeInfo<klab::Real>::MIN))
        TEST_ASSERT(fMax == TComplex<klab::Real>(klab::TTypeInfo<klab::Real>::MAX, klab::TTypeInfo<klab::Real>::MAX))
        TEST_ASSERT(fPrecision == klab::TTypeInfo<klab::Real>::PRECISION)
        TEST_ASSERT(klab::Abs(fDelta-klab::TTypeInfo<klab::Real>::DELTA) < 1e-6)
        TEST_ASSERT(klab::Abs(fEpsilon-klab::TTypeInfo<klab::Real>::EPSILON) < 1e-6)


        TComplex<klab::DoubleReal> dZero    = klab::TTypeInfo<TComplex<klab::DoubleReal> >::ZERO;
        TComplex<klab::DoubleReal> dUnit    = klab::TTypeInfo<TComplex<klab::DoubleReal> >::UNIT;
        TComplex<klab::DoubleReal> dMin     = klab::TTypeInfo<TComplex<klab::DoubleReal> >::MIN;
        TComplex<klab::DoubleReal> dMax     = klab::TTypeInfo<TComplex<klab::DoubleReal> >::MAX;
        klab::UInt32 dPrecision             = klab::TTypeInfo<TComplex<klab::DoubleReal> >::PRECISION;
        klab::DoubleReal dDelta             = klab::TTypeInfo<TComplex<klab::DoubleReal> >::DELTA;
        klab::DoubleReal dEpsilon           = klab::TTypeInfo<TComplex<klab::DoubleReal> >::EPSILON;

        TEST_ASSERT(dZero == TComplex<klab::DoubleReal>(0.0, 0.0))
        TEST_ASSERT(dUnit == TComplex<klab::DoubleReal>(1.0, 0.0))
        TEST_ASSERT(dMin == TComplex<klab::DoubleReal>(klab::TTypeInfo<klab::DoubleReal>::MIN, klab::TTypeInfo<klab::DoubleReal>::MIN))
        TEST_ASSERT(dMax == TComplex<klab::DoubleReal>(klab::TTypeInfo<klab::DoubleReal>::MAX, klab::TTypeInfo<klab::DoubleReal>::MAX))
        TEST_ASSERT(dPrecision == klab::TTypeInfo<klab::DoubleReal>::PRECISION)
        TEST_ASSERT(klab::Abs(dDelta-klab::TTypeInfo<klab::DoubleReal>::DELTA) < 1e-12)   
        TEST_ASSERT(klab::Abs(dEpsilon-klab::TTypeInfo<klab::DoubleReal>::EPSILON) < 1e-12)        
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
