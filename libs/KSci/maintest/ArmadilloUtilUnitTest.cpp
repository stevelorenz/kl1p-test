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

#include "ArmadilloUtilUnitTest.h"
#include "../include/ArmadilloUtil.h"
#include "../include/TrigoUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KArmadilloUtilUnitTest::KArmadilloUtilUnitTest() : Test::Suite()
{
    TEST_ADD(KArmadilloUtilUnitTest::testMin_ColVector)
    TEST_ADD(KArmadilloUtilUnitTest::testMin_RowVector)
    TEST_ADD(KArmadilloUtilUnitTest::testMin_Matrix)
    TEST_ADD(KArmadilloUtilUnitTest::testMax_ColVector)
    TEST_ADD(KArmadilloUtilUnitTest::testMax_RowVector)
    TEST_ADD(KArmadilloUtilUnitTest::testMax_Matrix)
    TEST_ADD(KArmadilloUtilUnitTest::testGetFrom_ColVector)
    TEST_ADD(KArmadilloUtilUnitTest::testGetFrom_RowVector)
    TEST_ADD(KArmadilloUtilUnitTest::testGetFrom_Matrix)
    TEST_ADD(KArmadilloUtilUnitTest::testSetTo_ColVector)
    TEST_ADD(KArmadilloUtilUnitTest::testSetTo_RowVector)
    TEST_ADD(KArmadilloUtilUnitTest::testSetTo_Matrix)
    TEST_ADD(KArmadilloUtilUnitTest::testEquals_ColVector)
    TEST_ADD(KArmadilloUtilUnitTest::testEquals_RowVector)
    TEST_ADD(KArmadilloUtilUnitTest::testEquals_Matrix)
    TEST_ADD(KArmadilloUtilUnitTest::testConvert_ColVector)
    TEST_ADD(KArmadilloUtilUnitTest::testConvert_RowVector)
    TEST_ADD(KArmadilloUtilUnitTest::testConvert_Matrix)
    TEST_ADD(KArmadilloUtilUnitTest::testShiftCircular_ColVector)
    TEST_ADD(KArmadilloUtilUnitTest::testShiftCircular_RowVector)
}

// ---------------------------------------------------------------------------------------------------- //

KArmadilloUtilUnitTest::~KArmadilloUtilUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testMin_ColVector()
{
    try
    {
        arma::Col<klab::DoubleReal> f(32);

        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 
        f[15] = -12.345;

        TEST_ASSERT(klab::Equals(klab::Min(f), -12.345))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Min(arma::Col<klab::DoubleReal>()), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testMin_RowVector()
{
    try
    {
        arma::Row<klab::DoubleReal> f(32);

        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 
        f[15] = -12.345;

        TEST_ASSERT(klab::Equals(klab::Min(f), -12.345))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Min(arma::Row<klab::DoubleReal>()), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testMin_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(8, 8);

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = -139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = -182.0;
        f(1, 5) = -136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = -171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = -157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = -118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = -115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = -144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = -81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = -144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;


        TEST_ASSERT(klab::Equals(klab::Min(f), -182.0))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Min(arma::Mat<klab::DoubleReal>()), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testMax_ColVector()
{
    try
    {
        arma::Col<klab::DoubleReal> f(32);

        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TEST_ASSERT(klab::Equals(klab::Max(f), 1.0))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Max(arma::Col<klab::DoubleReal>()), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testMax_RowVector()
{
    try
    {
        arma::Row<klab::DoubleReal> f(32);

        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TEST_ASSERT(klab::Equals(klab::Max(f), 1.0))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Max(arma::Row<klab::DoubleReal>()), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testMax_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(8, 8);

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = -139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = -182.0;
        f(1, 5) = -136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = -171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(2, 7) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(3, 7) = -157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = -118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = -115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = -144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = -81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = -144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;


        TEST_ASSERT(klab::Equals(klab::Max(f), 195.0))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::Max(arma::Mat<klab::DoubleReal>()), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testGetFrom_ColVector()
{
    try
    {
        arma::Col<klab::DoubleReal> f(6);
        f[0] = 1.0;
        f[1] = 2.0;
        f[2] = 3.0;
        f[3] = 0.0;
        f[4] = 5.0;
        f[5] = 6.0;


        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0), 1.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1), 2.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2), 3.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 4), 5.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 5), 6.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 6), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 10), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 20), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 101), 0.0))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Col<klab::DoubleReal>(), 0), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Col<klab::DoubleReal>(), 1), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Col<klab::DoubleReal>(), 2), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Col<klab::DoubleReal>(), 5), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Col<klab::DoubleReal>(), 10), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testGetFrom_RowVector()
{
    try
    {
        arma::Row<klab::DoubleReal> f(6);
        f[0] = 1.0;
        f[1] = 2.0;
        f[2] = 3.0;
        f[3] = 0.0;
        f[4] = 5.0;
        f[5] = 6.0;


        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0), 1.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1), 2.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2), 3.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 4), 5.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 5), 6.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 6), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 10), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 20), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 101), 0.0))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Row<klab::DoubleReal>(), 0), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Row<klab::DoubleReal>(), 1), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Row<klab::DoubleReal>(), 2), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Row<klab::DoubleReal>(), 5), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Row<klab::DoubleReal>(), 10), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testGetFrom_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(3, 3);
        f(0, 0) = 1.0;
        f(0, 1) = 2.0;
        f(0, 2) = 3.0;
        f(1, 0) = 4.0;
        f(1, 1) = 0.0;
        f(1, 2) = 5.0;
        f(2, 0) = 0.0;
        f(2, 1) = 6.0;
        f(2, 2) = 7.0;

        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0, 0), 1.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0, 1), 2.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0, 2), 3.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 0), 4.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 1), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 2), 5.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2, 0), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2, 1), 6.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2, 2), 7.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 0), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 1), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 2), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 3), 0.0))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Mat<klab::DoubleReal>(), 0, 0), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Mat<klab::DoubleReal>(), 0, 1), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Mat<klab::DoubleReal>(), 1, 0), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(arma::Mat<klab::DoubleReal>(), 1, 1), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testSetTo_ColVector()
{
    try
    {
        arma::Col<klab::DoubleReal> f(6);
        f[0] = 1.0;
        f[1] = 2.0;
        f[2] = 3.0;
        f[3] = 0.0;
        f[4] = 5.0;
        f[5] = 6.0;


        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0), 1.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1), 2.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2), 3.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 4), 5.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 5), 6.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 6), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 10), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 20), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 101), 0.0))

        klab::SetTo(f, 0, 3.456);
        klab::SetTo(f, 3, 11.23);
        klab::SetTo(f, 6, 1.5);
        klab::SetTo(f, 7, 2.6);
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0), 3.456))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3), 11.23))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 6), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 7), 0.0))


        // Limit cases.
        arma::Col<klab::DoubleReal> f0;
        klab::SetTo(f0, 0, 3.456);
        TEST_ASSERT(klab::Equals(klab::GetFrom(f0, 0), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testSetTo_RowVector()
{
    try
    {
        arma::Row<klab::DoubleReal> f(6);
        f[0] = 1.0;
        f[1] = 2.0;
        f[2] = 3.0;
        f[3] = 0.0;
        f[4] = 5.0;
        f[5] = 6.0;


        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0), 1.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1), 2.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2), 3.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 4), 5.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 5), 6.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 6), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 10), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 20), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 101), 0.0))

        klab::SetTo(f, 0, 3.456);
        klab::SetTo(f, 3, 11.23);
        klab::SetTo(f, 6, 1.5);
        klab::SetTo(f, 7, 2.6);
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0), 3.456))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3), 11.23))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 6), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 7), 0.0))


        // Limit cases.
        arma::Row<klab::DoubleReal> f0;
        klab::SetTo(f0, 0, 3.456);
        TEST_ASSERT(klab::Equals(klab::GetFrom(f0, 0), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testSetTo_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(3, 3);
        f(0, 0) = 1.0;
        f(0, 1) = 2.0;
        f(0, 2) = 3.0;
        f(1, 0) = 4.0;
        f(1, 1) = 0.0;
        f(1, 2) = 5.0;
        f(2, 0) = 0.0;
        f(2, 1) = 6.0;
        f(2, 2) = 7.0;

        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0, 0), 1.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0, 1), 2.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0, 2), 3.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 0), 4.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 1), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 2), 5.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2, 0), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2, 1), 6.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2, 2), 7.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 2, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 0), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 1), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 2), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 3), 0.0))

        klab::SetTo(f, 0, 0, 3.456);
        klab::SetTo(f, 1, 1, 11.23);
        klab::SetTo(f, 1, 2, 12.34);
        klab::SetTo(f, 3, 1, 1.5);
        klab::SetTo(f, 1, 3, 2.6);
        klab::SetTo(f, 3, 3, 2.6);
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 0, 0), 3.456))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 1), 11.23))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 2), 12.34))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 1), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 1, 3), 0.0))
        TEST_ASSERT(klab::Equals(klab::GetFrom(f, 3, 3), 0.0))


        // Limit cases.
        arma::Mat<klab::DoubleReal> f0;
        klab::SetTo(f0, 0, 0, 3.456);
        TEST_ASSERT(klab::Equals(klab::GetFrom(f0, 0, 0), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testEquals_ColVector()
{
    try
    {
        arma::Col<klab::DoubleReal> f1(6);
        arma::Col<klab::DoubleReal> f2(7);
        arma::Col<klab::DoubleReal> f3(f1.n_rows);
        arma::Col<klab::DoubleReal> f4(6);

        f1[0] = 1.0;
        f1[1] = 2.0;
        f1[2] = 3.0;
        f1[3] = 4.0;
        f1[4] = 5.0;
        f1[5] = 6.0;

        f2[0] = 1.0;
        f2[1] = 2.0;
        f2[2] = 3.0;
        f2[3] = 4.0;
        f2[4] = 5.0;
        f2[5] = 6.0;
        f2[6] = 0.0;

        f3[0] = f1[0];
        f3[1] = f1[1];
        f3[2] = f1[2];
        f3[3] = f1[3];
        f3[4] = f1[4];
        f3[5] = f1[5];

        f4[0] = 1.0;
        f4[1] = 2.0;
        f4[2] = 3.0;
        f4[3] = 4.01;
        f4[4] = 5.0;
        f4[5] = 6.0;


        TEST_ASSERT(klab::Equals(f1, f2) && klab::Equals(f2, f1))
        TEST_ASSERT(klab::Equals(f1, f3) && klab::Equals(f3, f1))
        TEST_ASSERT(klab::Equals(f2, f3) && klab::Equals(f3, f2))
        TEST_ASSERT(klab::Equals(f1, f4)==false && klab::Equals(f4, f1)==false)
        TEST_ASSERT(klab::Equals(f1, f4, 0.1) && klab::Equals(f4, f1, 0.1))
        TEST_ASSERT(klab::Equals(f2, f4)==false && klab::Equals(f4, f2)==false)
        TEST_ASSERT(klab::Equals(f2, f4, 0.1) && klab::Equals(f4, f2, 0.1))
        TEST_ASSERT(klab::Equals(f3, f4)==false && klab::Equals(f4, f3)==false)
        TEST_ASSERT(klab::Equals(f3, f4, 0.1) && klab::Equals(f4, f3, 0.1))
        TEST_ASSERT(klab::Equals(f1, f1) && klab::Equals(f2, f2) && klab::Equals(f3, f3) && klab::Equals(f4, f4))


        // Limit cases.
        arma::Col<klab::DoubleReal> f0;
        TEST_ASSERT(klab::Equals(f1, f0)==false && klab::Equals(f0, f1)==false)
        TEST_ASSERT(klab::Equals(f0, f0) && klab::Equals(f0, arma::Col<klab::DoubleReal>()) && klab::Equals(arma::Col<klab::DoubleReal>(), f0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testEquals_RowVector()
{
    try
    {
        arma::Row<klab::DoubleReal> f1(6);
        arma::Row<klab::DoubleReal> f2(7);
        arma::Row<klab::DoubleReal> f3(f1.n_cols);
        arma::Row<klab::DoubleReal> f4(6);

        f1[0] = 1.0;
        f1[1] = 2.0;
        f1[2] = 3.0;
        f1[3] = 4.0;
        f1[4] = 5.0;
        f1[5] = 6.0;

        f2[0] = 1.0;
        f2[1] = 2.0;
        f2[2] = 3.0;
        f2[3] = 4.0;
        f2[4] = 5.0;
        f2[5] = 6.0;
        f2[6] = 0.0;

        f3[0] = f1[0];
        f3[1] = f1[1];
        f3[2] = f1[2];
        f3[3] = f1[3];
        f3[4] = f1[4];
        f3[5] = f1[5];

        f4[0] = 1.0;
        f4[1] = 2.0;
        f4[2] = 3.0;
        f4[3] = 4.01;
        f4[4] = 5.0;
        f4[5] = 6.0;


        TEST_ASSERT(klab::Equals(f1, f2) && klab::Equals(f2, f1))
        TEST_ASSERT(klab::Equals(f1, f3) && klab::Equals(f3, f1))
        TEST_ASSERT(klab::Equals(f2, f3) && klab::Equals(f3, f2))
        TEST_ASSERT(klab::Equals(f1, f4)==false && klab::Equals(f4, f1)==false)
        TEST_ASSERT(klab::Equals(f1, f4, 0.1) && klab::Equals(f4, f1, 0.1))
        TEST_ASSERT(klab::Equals(f2, f4)==false && klab::Equals(f4, f2)==false)
        TEST_ASSERT(klab::Equals(f2, f4, 0.1) && klab::Equals(f4, f2, 0.1))
        TEST_ASSERT(klab::Equals(f3, f4)==false && klab::Equals(f4, f3)==false)
        TEST_ASSERT(klab::Equals(f3, f4, 0.1) && klab::Equals(f4, f3, 0.1))
        TEST_ASSERT(klab::Equals(f1, f1) && klab::Equals(f2, f2) && klab::Equals(f3, f3) && klab::Equals(f4, f4))


        // Limit cases.
        arma::Row<klab::DoubleReal> f0;
        TEST_ASSERT(klab::Equals(f1, f0)==false && klab::Equals(f0, f1)==false)
        TEST_ASSERT(klab::Equals(f0, f0) && klab::Equals(f0, arma::Row<klab::DoubleReal>()) && klab::Equals(arma::Row<klab::DoubleReal>(), f0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testEquals_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> f1(3, 3);
        arma::Mat<klab::DoubleReal> f2(4, 4);
        arma::Mat<klab::DoubleReal> f3(f1.n_rows, f1.n_cols);
        arma::Mat<klab::DoubleReal> f4(3, 3);

        f1(0, 0) = 1.0;
        f1(0, 1) = 2.0;
        f1(0, 2) = 3.0;
        f1(1, 0) = 4.0;
        f1(1, 1) = 5.0;
        f1(1, 2) = 6.0;
        f1(2, 0) = 7.0;
        f1(2, 1) = 8.0;
        f1(2, 2) = 9.0;

        f2(0, 0) = 1.0;
        f2(0, 1) = 2.0;
        f2(0, 2) = 3.0;
        f2(0, 3) = 0.0;
        f2(1, 0) = 4.0;
        f2(1, 1) = 5.0;
        f2(1, 2) = 6.0;
        f2(1, 3) = 0.0;
        f2(2, 0) = 7.0;
        f2(2, 1) = 8.0;
        f2(2, 2) = 9.0;
        f2(2, 3) = 0.0;
        f2(3, 0) = 0.0;
        f2(3, 1) = 0.0;
        f2(3, 2) = 0.0;
        f2(3, 3) = 0.0;

        f3(0, 0) = f1(0, 0);
        f3(0, 1) = f1(0, 1);
        f3(0, 2) = f1(0, 2);
        f3(1, 0) = f1(1, 0);
        f3(1, 1) = f1(1, 1);
        f3(1, 2) = f1(1, 2);
        f3(2, 0) = f1(2, 0);
        f3(2, 1) = f1(2, 1);
        f3(2, 2) = f1(2, 2);

        f4(0, 0) = 1.0;
        f4(0, 1) = 2.0;
        f4(0, 2) = 3.0;
        f4(1, 0) = 4.0;
        f4(1, 1) = 5.01;
        f4(1, 2) = 6.0;
        f4(2, 0) = 7.0;
        f4(2, 1) = 8.0;
        f4(2, 2) = 9.0;


        TEST_ASSERT(klab::Equals(f1, f2) && klab::Equals(f2, f1))
        TEST_ASSERT(klab::Equals(f1, f3) && klab::Equals(f3, f1))
        TEST_ASSERT(klab::Equals(f2, f3) && klab::Equals(f3, f2))
        TEST_ASSERT(klab::Equals(f1, f4)==false && klab::Equals(f4, f1)==false)
        TEST_ASSERT(klab::Equals(f1, f4, 0.1) && klab::Equals(f4, f1, 0.1))
        TEST_ASSERT(klab::Equals(f2, f4)==false && klab::Equals(f4, f2)==false)
        TEST_ASSERT(klab::Equals(f2, f4, 0.1) && klab::Equals(f4, f2, 0.1))
        TEST_ASSERT(klab::Equals(f3, f4)==false && klab::Equals(f4, f3)==false)
        TEST_ASSERT(klab::Equals(f3, f4, 0.1) && klab::Equals(f4, f3, 0.1))
        TEST_ASSERT(klab::Equals(f1, f1) && klab::Equals(f2, f2) && klab::Equals(f3, f3) && klab::Equals(f4, f4))


        // Limit cases.
        arma::Mat<klab::DoubleReal> f0;
        TEST_ASSERT(klab::Equals(f1, f0)==false && klab::Equals(f0, f1)==false)
        TEST_ASSERT(klab::Equals(f0, f0) && klab::Equals(f0, arma::Mat<klab::DoubleReal>()) && klab::Equals(arma::Mat<klab::DoubleReal>(), f0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testConvert_ColVector()
{
    try
    {
        arma::Col<klab::DoubleReal> f(6);
        f[0] = 1.0;
        f[1] = 2.0;
        f[2] = 3.0;
        f[3] = 4.0;
        f[4] = 5.0;
        f[5] = 6.0;

        arma::Col<std::complex<klab::DoubleReal> > f2;
        arma::Col<klab::DoubleReal> f3;

        klab::Convert(f, f2);
        TEST_ASSERT(f2.n_rows == 6)
        TEST_ASSERT(klab::Equals(f2[0], std::complex<klab::DoubleReal>(1.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[1], std::complex<klab::DoubleReal>(2.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[2], std::complex<klab::DoubleReal>(3.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[3], std::complex<klab::DoubleReal>(4.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[4], std::complex<klab::DoubleReal>(5.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[5], std::complex<klab::DoubleReal>(6.0, 0.0)))

        klab::Convert(f2, f3);
        TEST_ASSERT(f3.n_rows == 6)
        TEST_ASSERT(klab::Equals(f3[0], 1.0))
        TEST_ASSERT(klab::Equals(f3[1], 2.0))
        TEST_ASSERT(klab::Equals(f3[2], 3.0))
        TEST_ASSERT(klab::Equals(f3[3], 4.0))
        TEST_ASSERT(klab::Equals(f3[4], 5.0))
        TEST_ASSERT(klab::Equals(f3[5], 6.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testConvert_RowVector()
{
    try
    {
        arma::Row<klab::DoubleReal> f(6);
        f[0] = 1.0;
        f[1] = 2.0;
        f[2] = 3.0;
        f[3] = 4.0;
        f[4] = 5.0;
        f[5] = 6.0;

        arma::Row<std::complex<klab::DoubleReal> > f2;
        arma::Row<klab::DoubleReal> f3;

        klab::Convert(f, f2);
        TEST_ASSERT(f2.n_cols == 6)
        TEST_ASSERT(klab::Equals(f2[0], std::complex<klab::DoubleReal>(1.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[1], std::complex<klab::DoubleReal>(2.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[2], std::complex<klab::DoubleReal>(3.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[3], std::complex<klab::DoubleReal>(4.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[4], std::complex<klab::DoubleReal>(5.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2[5], std::complex<klab::DoubleReal>(6.0, 0.0)))

        klab::Convert(f2, f3);
        TEST_ASSERT(f3.n_cols == 6)
        TEST_ASSERT(klab::Equals(f3[0], 1.0))
        TEST_ASSERT(klab::Equals(f3[1], 2.0))
        TEST_ASSERT(klab::Equals(f3[2], 3.0))
        TEST_ASSERT(klab::Equals(f3[3], 4.0))
        TEST_ASSERT(klab::Equals(f3[4], 5.0))
        TEST_ASSERT(klab::Equals(f3[5], 6.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testConvert_Matrix()
{
    try
    {
        arma::Mat<klab::DoubleReal> f(3, 3);

        f(0, 0) = 1.0;
        f(0, 1) = 2.0;
        f(0, 2) = 3.0;
        f(1, 0) = 4.0;
        f(1, 1) = 5.0;
        f(1, 2) = 6.0;
        f(2, 0) = 7.0;
        f(2, 1) = 8.0;
        f(2, 2) = 9.0;

        arma::Mat<std::complex<klab::DoubleReal> > f2;
        arma::Mat<klab::DoubleReal> f3;

        klab::Convert(f, f2);
        TEST_ASSERT(f2.n_rows==3 && f2.n_cols == 3)
        TEST_ASSERT(klab::Equals(f2(0, 0), std::complex<klab::DoubleReal>(1.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2(0, 1), std::complex<klab::DoubleReal>(2.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2(0, 2), std::complex<klab::DoubleReal>(3.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2(1, 0), std::complex<klab::DoubleReal>(4.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2(1, 1), std::complex<klab::DoubleReal>(5.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2(1, 2), std::complex<klab::DoubleReal>(6.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2(2, 0), std::complex<klab::DoubleReal>(7.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2(2, 1), std::complex<klab::DoubleReal>(8.0, 0.0)))
        TEST_ASSERT(klab::Equals(f2(2, 2), std::complex<klab::DoubleReal>(9.0, 0.0)))

        klab::Convert(f2, f3);
        TEST_ASSERT(f3.n_rows==3 && f3.n_cols == 3)
        TEST_ASSERT(klab::Equals(f3(0, 0), 1.0))
        TEST_ASSERT(klab::Equals(f3(0, 1), 2.0))
        TEST_ASSERT(klab::Equals(f3(0, 2), 3.0))
        TEST_ASSERT(klab::Equals(f3(1, 0), 4.0))
        TEST_ASSERT(klab::Equals(f3(1, 1), 5.0))
        TEST_ASSERT(klab::Equals(f3(1, 2), 6.0))
        TEST_ASSERT(klab::Equals(f3(2, 0), 7.0))
        TEST_ASSERT(klab::Equals(f3(2, 1), 8.0))
        TEST_ASSERT(klab::Equals(f3(2, 2), 9.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testShiftCircular_ColVector()
{
    try
    {
        arma::Col<klab::DoubleReal> f(8);
        arma::Col<klab::DoubleReal> fs;
        f[0] = 1.0;
        f[1] = 2.0;
        f[2] = 3.0;
        f[3] = 4.0;
        f[4] = 5.0;
        f[5] = 6.0;
        f[6] = 7.0;
        f[7] = 8.0;

        klab::ShiftCircular(f, 1, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[7]))
        TEST_ASSERT(klab::Equals(fs[1], f[0]))
        TEST_ASSERT(klab::Equals(fs[2], f[1]))
        TEST_ASSERT(klab::Equals(fs[3], f[2]))
        TEST_ASSERT(klab::Equals(fs[4], f[3]))
        TEST_ASSERT(klab::Equals(fs[5], f[4]))
        TEST_ASSERT(klab::Equals(fs[6], f[5]))
        TEST_ASSERT(klab::Equals(fs[7], f[6]))

        klab::ShiftCircular(f, -1, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[1]))
        TEST_ASSERT(klab::Equals(fs[1], f[2]))
        TEST_ASSERT(klab::Equals(fs[2], f[3]))
        TEST_ASSERT(klab::Equals(fs[3], f[4]))
        TEST_ASSERT(klab::Equals(fs[4], f[5]))
        TEST_ASSERT(klab::Equals(fs[5], f[6]))
        TEST_ASSERT(klab::Equals(fs[6], f[7]))
        TEST_ASSERT(klab::Equals(fs[7], f[0]))

        klab::ShiftCircular(f, 3, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[5]))
        TEST_ASSERT(klab::Equals(fs[1], f[6]))
        TEST_ASSERT(klab::Equals(fs[2], f[7]))
        TEST_ASSERT(klab::Equals(fs[3], f[0]))
        TEST_ASSERT(klab::Equals(fs[4], f[1]))
        TEST_ASSERT(klab::Equals(fs[5], f[2]))
        TEST_ASSERT(klab::Equals(fs[6], f[3]))
        TEST_ASSERT(klab::Equals(fs[7], f[4]))

        klab::ShiftCircular(f, -3, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[3]))
        TEST_ASSERT(klab::Equals(fs[1], f[4]))
        TEST_ASSERT(klab::Equals(fs[2], f[5]))
        TEST_ASSERT(klab::Equals(fs[3], f[6]))
        TEST_ASSERT(klab::Equals(fs[4], f[7]))
        TEST_ASSERT(klab::Equals(fs[5], f[0]))
        TEST_ASSERT(klab::Equals(fs[6], f[1]))
        TEST_ASSERT(klab::Equals(fs[7], f[2]))

        fs = f;
        klab::ShiftCircular(fs, 1);
        TEST_ASSERT(klab::Equals(fs[0], f[7]))
        TEST_ASSERT(klab::Equals(fs[1], f[0]))
        TEST_ASSERT(klab::Equals(fs[2], f[1]))
        TEST_ASSERT(klab::Equals(fs[3], f[2]))
        TEST_ASSERT(klab::Equals(fs[4], f[3]))
        TEST_ASSERT(klab::Equals(fs[5], f[4]))
        TEST_ASSERT(klab::Equals(fs[6], f[5]))
        TEST_ASSERT(klab::Equals(fs[7], f[6]))

        fs = f;
        klab::ShiftCircular(fs, -1);
        TEST_ASSERT(klab::Equals(fs[0], f[1]))
        TEST_ASSERT(klab::Equals(fs[1], f[2]))
        TEST_ASSERT(klab::Equals(fs[2], f[3]))
        TEST_ASSERT(klab::Equals(fs[3], f[4]))
        TEST_ASSERT(klab::Equals(fs[4], f[5]))
        TEST_ASSERT(klab::Equals(fs[5], f[6]))
        TEST_ASSERT(klab::Equals(fs[6], f[7]))
        TEST_ASSERT(klab::Equals(fs[7], f[0]))

        fs = f;
        klab::ShiftCircular(fs, 3);
        TEST_ASSERT(klab::Equals(fs[0], f[5]))
        TEST_ASSERT(klab::Equals(fs[1], f[6]))
        TEST_ASSERT(klab::Equals(fs[2], f[7]))
        TEST_ASSERT(klab::Equals(fs[3], f[0]))
        TEST_ASSERT(klab::Equals(fs[4], f[1]))
        TEST_ASSERT(klab::Equals(fs[5], f[2]))
        TEST_ASSERT(klab::Equals(fs[6], f[3]))
        TEST_ASSERT(klab::Equals(fs[7], f[4]))

        fs = f;
        klab::ShiftCircular(fs, -3);
        TEST_ASSERT(klab::Equals(fs[0], f[3]))
        TEST_ASSERT(klab::Equals(fs[1], f[4]))
        TEST_ASSERT(klab::Equals(fs[2], f[5]))
        TEST_ASSERT(klab::Equals(fs[3], f[6]))
        TEST_ASSERT(klab::Equals(fs[4], f[7]))
        TEST_ASSERT(klab::Equals(fs[5], f[0]))
        TEST_ASSERT(klab::Equals(fs[6], f[1]))
        TEST_ASSERT(klab::Equals(fs[7], f[2]))


        // Limit cases.
        klab::ShiftCircular(arma::Col<klab::DoubleReal>(), 0, fs);
        TEST_ASSERT(fs.n_rows == 0)

        klab::ShiftCircular(arma::Col<klab::DoubleReal>(), 1, fs);
        TEST_ASSERT(fs.n_rows == 0)

        klab::ShiftCircular(arma::Col<klab::DoubleReal>(), -1, fs);
        TEST_ASSERT(fs.n_rows == 0)

        arma::Col<klab::DoubleReal> fs0;
        klab::ShiftCircular(fs0, 0);
        TEST_ASSERT(fs0.n_rows == 0)

        klab::ShiftCircular(fs0, 1);
        TEST_ASSERT(fs0.n_rows == 0)

        klab::ShiftCircular(fs0, -1);
        TEST_ASSERT(fs0.n_rows == 0)
        
        klab::ShiftCircular(f, 0, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[0]))
        TEST_ASSERT(klab::Equals(fs[1], f[1]))
        TEST_ASSERT(klab::Equals(fs[2], f[2]))
        TEST_ASSERT(klab::Equals(fs[3], f[3]))
        TEST_ASSERT(klab::Equals(fs[4], f[4]))
        TEST_ASSERT(klab::Equals(fs[5], f[5]))
        TEST_ASSERT(klab::Equals(fs[6], f[6]))
        TEST_ASSERT(klab::Equals(fs[7], f[7]))

        klab::ShiftCircular(f, 8, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[0]))
        TEST_ASSERT(klab::Equals(fs[1], f[1]))
        TEST_ASSERT(klab::Equals(fs[2], f[2]))
        TEST_ASSERT(klab::Equals(fs[3], f[3]))
        TEST_ASSERT(klab::Equals(fs[4], f[4]))
        TEST_ASSERT(klab::Equals(fs[5], f[5]))
        TEST_ASSERT(klab::Equals(fs[6], f[6]))
        TEST_ASSERT(klab::Equals(fs[7], f[7]))

        klab::ShiftCircular(f, 9, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[7]))
        TEST_ASSERT(klab::Equals(fs[1], f[0]))
        TEST_ASSERT(klab::Equals(fs[2], f[1]))
        TEST_ASSERT(klab::Equals(fs[3], f[2]))
        TEST_ASSERT(klab::Equals(fs[4], f[3]))
        TEST_ASSERT(klab::Equals(fs[5], f[4]))
        TEST_ASSERT(klab::Equals(fs[6], f[5]))
        TEST_ASSERT(klab::Equals(fs[7], f[6]))

        fs = f;
        klab::ShiftCircular(fs, 0);
        TEST_ASSERT(klab::Equals(fs[0], f[0]))
        TEST_ASSERT(klab::Equals(fs[1], f[1]))
        TEST_ASSERT(klab::Equals(fs[2], f[2]))
        TEST_ASSERT(klab::Equals(fs[3], f[3]))
        TEST_ASSERT(klab::Equals(fs[4], f[4]))
        TEST_ASSERT(klab::Equals(fs[5], f[5]))
        TEST_ASSERT(klab::Equals(fs[6], f[6]))
        TEST_ASSERT(klab::Equals(fs[7], f[7]))

        fs = f;
        klab::ShiftCircular(fs, 8);
        TEST_ASSERT(klab::Equals(fs[0], f[0]))
        TEST_ASSERT(klab::Equals(fs[1], f[1]))
        TEST_ASSERT(klab::Equals(fs[2], f[2]))
        TEST_ASSERT(klab::Equals(fs[3], f[3]))
        TEST_ASSERT(klab::Equals(fs[4], f[4]))
        TEST_ASSERT(klab::Equals(fs[5], f[5]))
        TEST_ASSERT(klab::Equals(fs[6], f[6]))
        TEST_ASSERT(klab::Equals(fs[7], f[7]))

        fs = f;
        klab::ShiftCircular(fs, 9);
        TEST_ASSERT(klab::Equals(fs[0], f[7]))
        TEST_ASSERT(klab::Equals(fs[1], f[0]))
        TEST_ASSERT(klab::Equals(fs[2], f[1]))
        TEST_ASSERT(klab::Equals(fs[3], f[2]))
        TEST_ASSERT(klab::Equals(fs[4], f[3]))
        TEST_ASSERT(klab::Equals(fs[5], f[4]))
        TEST_ASSERT(klab::Equals(fs[6], f[5]))
        TEST_ASSERT(klab::Equals(fs[7], f[6]))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KArmadilloUtilUnitTest::testShiftCircular_RowVector()
{
    try
    {
        arma::Row<klab::DoubleReal> f(8);
        arma::Row<klab::DoubleReal> fs;
        f[0] = 1.0;
        f[1] = 2.0;
        f[2] = 3.0;
        f[3] = 4.0;
        f[4] = 5.0;
        f[5] = 6.0;
        f[6] = 7.0;
        f[7] = 8.0;

        klab::ShiftCircular(f, 1, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[7]))
        TEST_ASSERT(klab::Equals(fs[1], f[0]))
        TEST_ASSERT(klab::Equals(fs[2], f[1]))
        TEST_ASSERT(klab::Equals(fs[3], f[2]))
        TEST_ASSERT(klab::Equals(fs[4], f[3]))
        TEST_ASSERT(klab::Equals(fs[5], f[4]))
        TEST_ASSERT(klab::Equals(fs[6], f[5]))
        TEST_ASSERT(klab::Equals(fs[7], f[6]))

        klab::ShiftCircular(f, -1, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[1]))
        TEST_ASSERT(klab::Equals(fs[1], f[2]))
        TEST_ASSERT(klab::Equals(fs[2], f[3]))
        TEST_ASSERT(klab::Equals(fs[3], f[4]))
        TEST_ASSERT(klab::Equals(fs[4], f[5]))
        TEST_ASSERT(klab::Equals(fs[5], f[6]))
        TEST_ASSERT(klab::Equals(fs[6], f[7]))
        TEST_ASSERT(klab::Equals(fs[7], f[0]))

        klab::ShiftCircular(f, 3, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[5]))
        TEST_ASSERT(klab::Equals(fs[1], f[6]))
        TEST_ASSERT(klab::Equals(fs[2], f[7]))
        TEST_ASSERT(klab::Equals(fs[3], f[0]))
        TEST_ASSERT(klab::Equals(fs[4], f[1]))
        TEST_ASSERT(klab::Equals(fs[5], f[2]))
        TEST_ASSERT(klab::Equals(fs[6], f[3]))
        TEST_ASSERT(klab::Equals(fs[7], f[4]))

        klab::ShiftCircular(f, -3, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[3]))
        TEST_ASSERT(klab::Equals(fs[1], f[4]))
        TEST_ASSERT(klab::Equals(fs[2], f[5]))
        TEST_ASSERT(klab::Equals(fs[3], f[6]))
        TEST_ASSERT(klab::Equals(fs[4], f[7]))
        TEST_ASSERT(klab::Equals(fs[5], f[0]))
        TEST_ASSERT(klab::Equals(fs[6], f[1]))
        TEST_ASSERT(klab::Equals(fs[7], f[2]))

        fs = f;
        klab::ShiftCircular(fs, 1);
        TEST_ASSERT(klab::Equals(fs[0], f[7]))
        TEST_ASSERT(klab::Equals(fs[1], f[0]))
        TEST_ASSERT(klab::Equals(fs[2], f[1]))
        TEST_ASSERT(klab::Equals(fs[3], f[2]))
        TEST_ASSERT(klab::Equals(fs[4], f[3]))
        TEST_ASSERT(klab::Equals(fs[5], f[4]))
        TEST_ASSERT(klab::Equals(fs[6], f[5]))
        TEST_ASSERT(klab::Equals(fs[7], f[6]))

        fs = f;
        klab::ShiftCircular(fs, -1);
        TEST_ASSERT(klab::Equals(fs[0], f[1]))
        TEST_ASSERT(klab::Equals(fs[1], f[2]))
        TEST_ASSERT(klab::Equals(fs[2], f[3]))
        TEST_ASSERT(klab::Equals(fs[3], f[4]))
        TEST_ASSERT(klab::Equals(fs[4], f[5]))
        TEST_ASSERT(klab::Equals(fs[5], f[6]))
        TEST_ASSERT(klab::Equals(fs[6], f[7]))
        TEST_ASSERT(klab::Equals(fs[7], f[0]))

        fs = f;
        klab::ShiftCircular(fs, 3);
        TEST_ASSERT(klab::Equals(fs[0], f[5]))
        TEST_ASSERT(klab::Equals(fs[1], f[6]))
        TEST_ASSERT(klab::Equals(fs[2], f[7]))
        TEST_ASSERT(klab::Equals(fs[3], f[0]))
        TEST_ASSERT(klab::Equals(fs[4], f[1]))
        TEST_ASSERT(klab::Equals(fs[5], f[2]))
        TEST_ASSERT(klab::Equals(fs[6], f[3]))
        TEST_ASSERT(klab::Equals(fs[7], f[4]))

        fs = f;
        klab::ShiftCircular(fs, -3);
        TEST_ASSERT(klab::Equals(fs[0], f[3]))
        TEST_ASSERT(klab::Equals(fs[1], f[4]))
        TEST_ASSERT(klab::Equals(fs[2], f[5]))
        TEST_ASSERT(klab::Equals(fs[3], f[6]))
        TEST_ASSERT(klab::Equals(fs[4], f[7]))
        TEST_ASSERT(klab::Equals(fs[5], f[0]))
        TEST_ASSERT(klab::Equals(fs[6], f[1]))
        TEST_ASSERT(klab::Equals(fs[7], f[2]))


        // Limit cases.
        klab::ShiftCircular(arma::Row<klab::DoubleReal>(), 0, fs);
        TEST_ASSERT(fs.n_cols == 0)

        klab::ShiftCircular(arma::Row<klab::DoubleReal>(), 1, fs);
        TEST_ASSERT(fs.n_cols == 0)

        klab::ShiftCircular(arma::Row<klab::DoubleReal>(), -1, fs);
        TEST_ASSERT(fs.n_cols == 0)

        arma::Row<klab::DoubleReal> fs0;
        klab::ShiftCircular(fs0, 0);
        TEST_ASSERT(fs0.n_cols == 0)

        klab::ShiftCircular(fs0, 1);
        TEST_ASSERT(fs0.n_cols == 0)

        klab::ShiftCircular(fs0, -1);
        TEST_ASSERT(fs0.n_cols == 0)

        klab::ShiftCircular(f, 0, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[0]))
        TEST_ASSERT(klab::Equals(fs[1], f[1]))
        TEST_ASSERT(klab::Equals(fs[2], f[2]))
        TEST_ASSERT(klab::Equals(fs[3], f[3]))
        TEST_ASSERT(klab::Equals(fs[4], f[4]))
        TEST_ASSERT(klab::Equals(fs[5], f[5]))
        TEST_ASSERT(klab::Equals(fs[6], f[6]))
        TEST_ASSERT(klab::Equals(fs[7], f[7]))

        klab::ShiftCircular(f, 8, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[0]))
        TEST_ASSERT(klab::Equals(fs[1], f[1]))
        TEST_ASSERT(klab::Equals(fs[2], f[2]))
        TEST_ASSERT(klab::Equals(fs[3], f[3]))
        TEST_ASSERT(klab::Equals(fs[4], f[4]))
        TEST_ASSERT(klab::Equals(fs[5], f[5]))
        TEST_ASSERT(klab::Equals(fs[6], f[6]))
        TEST_ASSERT(klab::Equals(fs[7], f[7]))

        klab::ShiftCircular(f, 9, fs);
        TEST_ASSERT(klab::Equals(fs[0], f[7]))
        TEST_ASSERT(klab::Equals(fs[1], f[0]))
        TEST_ASSERT(klab::Equals(fs[2], f[1]))
        TEST_ASSERT(klab::Equals(fs[3], f[2]))
        TEST_ASSERT(klab::Equals(fs[4], f[3]))
        TEST_ASSERT(klab::Equals(fs[5], f[4]))
        TEST_ASSERT(klab::Equals(fs[6], f[5]))
        TEST_ASSERT(klab::Equals(fs[7], f[6]))

        fs = f;
        klab::ShiftCircular(fs, 0);
        TEST_ASSERT(klab::Equals(fs[0], f[0]))
        TEST_ASSERT(klab::Equals(fs[1], f[1]))
        TEST_ASSERT(klab::Equals(fs[2], f[2]))
        TEST_ASSERT(klab::Equals(fs[3], f[3]))
        TEST_ASSERT(klab::Equals(fs[4], f[4]))
        TEST_ASSERT(klab::Equals(fs[5], f[5]))
        TEST_ASSERT(klab::Equals(fs[6], f[6]))
        TEST_ASSERT(klab::Equals(fs[7], f[7]))

        fs = f;
        klab::ShiftCircular(fs, 8);
        TEST_ASSERT(klab::Equals(fs[0], f[0]))
        TEST_ASSERT(klab::Equals(fs[1], f[1]))
        TEST_ASSERT(klab::Equals(fs[2], f[2]))
        TEST_ASSERT(klab::Equals(fs[3], f[3]))
        TEST_ASSERT(klab::Equals(fs[4], f[4]))
        TEST_ASSERT(klab::Equals(fs[5], f[5]))
        TEST_ASSERT(klab::Equals(fs[6], f[6]))
        TEST_ASSERT(klab::Equals(fs[7], f[7]))

        fs = f;
        klab::ShiftCircular(fs, 9);
        TEST_ASSERT(klab::Equals(fs[0], f[7]))
        TEST_ASSERT(klab::Equals(fs[1], f[0]))
        TEST_ASSERT(klab::Equals(fs[2], f[1]))
        TEST_ASSERT(klab::Equals(fs[3], f[2]))
        TEST_ASSERT(klab::Equals(fs[4], f[3]))
        TEST_ASSERT(klab::Equals(fs[5], f[4]))
        TEST_ASSERT(klab::Equals(fs[6], f[5]))
        TEST_ASSERT(klab::Equals(fs[7], f[6]))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
