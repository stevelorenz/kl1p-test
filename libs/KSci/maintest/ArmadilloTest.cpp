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

#include "ArmadilloTest.h"
#include "../include/ArmadilloUtil.h"
#include <KLabInclude.h>

using namespace klab;
using namespace arma;




// ---------------------------------------------------------------------------------------------------- //

KArmadilloTest::KArmadilloTest() : Test::Suite()
{
    TEST_ADD(KArmadilloTest::testMatrixVectorMultiplication)
}

// ---------------------------------------------------------------------------------------------------- //

KArmadilloTest::~KArmadilloTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloTest::testMatrixVectorMultiplication()
{
    try
    {
        Mat<klab::Real> A(3, 3);
        A(0, 0) = 1.0f;
        A(0, 1) = 2.0f;
        A(0, 2) = 3.0f;
        A(1, 0) = 4.0f;
        A(1, 1) = 5.0f;
        A(1, 2) = 6.0f;
        A(2, 0) = 7.0f;
        A(2, 1) = 8.0f;
        A(2, 2) = 9.0f;

        Col<klab::Real> v(3);
        v[0] = 1.0f;
        v[1] = 2.0f;
        v[2] = 3.0f;

        Col<klab::Real> vResult = A * v;

        TEST_ASSERT(vResult.size() == 3)
        TEST_ASSERT(klab::Equals(vResult[0], 14.0f))
        TEST_ASSERT(klab::Equals(vResult[1], 32.0f))
        TEST_ASSERT(klab::Equals(vResult[2], 50.0f))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
