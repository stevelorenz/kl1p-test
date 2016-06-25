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

#include "MathsUtilUnitTest.h"
#include "../include/MathsUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KMathsUtilUnitTest::KMathsUtilUnitTest() : Test::Suite()
{
    TEST_ADD(KMathsUtilUnitTest::testSqrt)
    TEST_ADD(KMathsUtilUnitTest::testExp)
    TEST_ADD(KMathsUtilUnitTest::testLog)
    TEST_ADD(KMathsUtilUnitTest::testLog2)
    TEST_ADD(KMathsUtilUnitTest::testLog10)
    TEST_ADD(KMathsUtilUnitTest::testPow)
    TEST_ADD(KMathsUtilUnitTest::testConj)
}

// ---------------------------------------------------------------------------------------------------- //

KMathsUtilUnitTest::~KMathsUtilUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KMathsUtilUnitTest::testSqrt()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Sqrt(1.2345f), static_cast<klab::Real>(::sqrt(1.2345f)))) 
        TEST_ASSERT(klab::Equals(klab::Sqrt(2.0f), static_cast<klab::Real>(klab::SQRT2))) 
        TEST_ASSERT(klab::Equals(klab::Sqrt(std::complex<klab::Real>(1.23f, 4.56f)), std::sqrt(std::complex<klab::Real>(1.23f, 4.56f)))) 


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Sqrt(0.0f), 0.0f)) 
        TEST_ASSERT(klab::Equals(klab::Sqrt(1.0f), 1.0f))

        try
        {
            klab::Sqrt(-1.0f);
            TEST_ASSERT(false)
        }
        catch(KSqrtMathsException&)
        {
            TEST_ASSERT(true)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMathsUtilUnitTest::testExp()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Exp(1.2345f), static_cast<klab::Real>(::exp(1.2345f))))
        TEST_ASSERT(klab::Equals(klab::Exp(std::complex<klab::Real>(1.23f, 4.56f)), std::exp(std::complex<klab::Real>(1.23f, 4.56f)))) 


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Exp(0.0f), 1.0f)) 
        TEST_ASSERT(klab::Equals(klab::Exp(1.0f), static_cast<klab::Real>(klab::E)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMathsUtilUnitTest::testLog()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Log(1.2345f), static_cast<klab::Real>(::log(1.2345f)))) 
        TEST_ASSERT(klab::Equals(klab::Log(2.0f), static_cast<klab::Real>(klab::LN2)))
        TEST_ASSERT(klab::Equals(klab::Log(std::complex<klab::Real>(1.23f, 4.56f)), std::log(std::complex<klab::Real>(1.23f, 4.56f)))) 


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Log(1.0f), 0.0f))

        try
        {
            klab::Log(0.0f);
            TEST_ASSERT(false)
        }
        catch(KLogMathsException&)
        {
            TEST_ASSERT(true)
        }

        try
        {
            klab::Log(-1.0f);
            TEST_ASSERT(false)
        }
        catch(KLogMathsException&)
        {
            TEST_ASSERT(true)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMathsUtilUnitTest::testLog2()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Log2(1.2345f), static_cast<klab::Real>(::log(1.2345f))/static_cast<klab::Real>(::log(2.0f)))) 
        TEST_ASSERT(klab::Equals(klab::Log2(2.0f), 1.0f)) 
        TEST_ASSERT(klab::Equals(klab::Log2(std::complex<klab::Real>(1.23f, 4.56f)), std::log(std::complex<klab::Real>(1.23f, 4.56f))*static_cast<klab::Real>(INV_LN2))) 


        // Limit cases.
        TEST_ASSERT(klab::Equals(Log2(1.0f), 0.0f))

        try
        {
            klab::Log2(0.0f);
            TEST_ASSERT(false)
        }
        catch(KLogMathsException&)
        {
            TEST_ASSERT(true)
        }

        try
        {
            klab::Log2(-1.0f);
            TEST_ASSERT(false)
        }
        catch(KLogMathsException&)
        {
            TEST_ASSERT(true)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMathsUtilUnitTest::testLog10()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Log10(1.2345f), static_cast<klab::Real>(::log10(1.2345f)))) 
        TEST_ASSERT(klab::Equals(klab::Log10(10.0f), 1.0f))
        TEST_ASSERT(klab::Equals(klab::Log10(std::complex<klab::Real>(1.23f, 4.56f)), std::log10(std::complex<klab::Real>(1.23f, 4.56f)))) 


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Log10(1.0f), 0.0f))

        try
        {
            klab::Log10(0.0f);
            TEST_ASSERT(false)
        }
        catch(KLogMathsException&)
        {
            TEST_ASSERT(true)
        }

        try
        {
            klab::Log10(-1.0f);
            TEST_ASSERT(false)
        }
        catch(KLogMathsException&)
        {
            TEST_ASSERT(true)
        }
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMathsUtilUnitTest::testPow()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Pow(1.2345f, 2), static_cast<klab::Real>(::pow(1.2345f, 2)))) 
        TEST_ASSERT(klab::Equals(klab::Pow(1.2345f, 1.2345f), static_cast<klab::Real>(::pow(1.2345f, 1.2345f))))
        TEST_ASSERT(klab::Equals(klab::Pow(1.2345f, 1), 1.2345f))
        TEST_ASSERT(klab::Equals(klab::Pow(1.2345f, 1.0f), 1.2345f))  
        TEST_ASSERT(klab::Equals(klab::Pow(0.0f, 2000), 0.0f))
        TEST_ASSERT(klab::Equals(klab::Pow(0.0f, 2000.0f), 0.0f))
        TEST_ASSERT(klab::Equals(klab::Pow(1.0f, 2000), 1.0f))
        TEST_ASSERT(klab::Equals(klab::Pow(1.0f, 2000.0f), 1.0f))
        TEST_ASSERT(klab::Equals(klab::Pow(std::complex<klab::Real>(1.23f, 4.56f), 7.89f), std::pow(std::complex<klab::Real>(1.23f, 4.56f), 7.89f))) 
        TEST_ASSERT(klab::Equals(klab::Pow(std::complex<klab::Real>(1.23f, 4.56f), std::complex<klab::Real>(7.89f, 1.47f)), std::pow(std::complex<klab::Real>(1.23f, 4.56f), std::complex<klab::Real>(7.89f, 1.47f)))) 
        TEST_ASSERT(klab::Equals(klab::Pow(std::complex<klab::Real>(1.23f, 4.56f), 4), std::pow(std::complex<klab::Real>(1.23f, 4.56f), 4))) 


         // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Pow(1.2345f, 0), 1.0f))
        TEST_ASSERT(klab::Equals(klab::Pow(1.2345f, 0.0f), 1.0f))
        TEST_ASSERT(klab::Equals(klab::Pow(0.0f, 0), 1.0f))
        TEST_ASSERT(klab::Equals(klab::Pow(0.0f, 0.0f), 1.0f)) 
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KMathsUtilUnitTest::testConj()
{
    try
    {
        TEST_ASSERT(klab::Equals(klab::Conj(1.234f), 1.234f))
        TEST_ASSERT(klab::Equals(klab::Conj(-1.234f), -1.234f))

        TEST_ASSERT(klab::Equals(klab::Conj(std::complex<klab::Real>(1.234f, 5.678f)), std::complex<klab::Real>(1.234f, -5.678f)))
        TEST_ASSERT(klab::Equals(klab::Conj(std::complex<klab::Real>(1.234f, -5.678f)), std::complex<klab::Real>(1.234f, 5.678f)))
        TEST_ASSERT(klab::Equals(klab::Conj(std::complex<klab::Real>(-1.234f, 5.678f)), std::complex<klab::Real>(-1.234f, -5.678f)))
        TEST_ASSERT(klab::Equals(klab::Conj(std::complex<klab::Real>(-1.234f, -5.678f)), std::complex<klab::Real>(-1.234f, 5.678f)))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
