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

#include "FWHT2DUnitTest.h"
#include "../include/FWHT2D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KFWHT2DUnitTest::KFWHT2DUnitTest() : Test::Suite()
{
    TEST_ADD(KFWHT2DUnitTest::testDefaultConstructor)  
    TEST_ADD(KFWHT2DUnitTest::testCopyConstructor)
    TEST_ADD(KFWHT2DUnitTest::testAffectationOperator)

    TEST_ADD(KFWHT2DUnitTest::testTransform)
    TEST_ADD(KFWHT2DUnitTest::testTransform_02)
    TEST_ADD(KFWHT2DUnitTest::testTransform_03)
    TEST_ADD(KFWHT2DUnitTest::testInvert)  
    TEST_ADD(KFWHT2DUnitTest::testInvert_02)
    TEST_ADD(KFWHT2DUnitTest::testInvert_03)
}

// ---------------------------------------------------------------------------------------------------- //

KFWHT2DUnitTest::~KFWHT2DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT2DUnitTest::testDefaultConstructor()
{
    try
    {
        TFWHT2D<klab::DoubleReal> fwht;
        TEST_ASSERT(true)

        TFWHT2D<std::complex<klab::DoubleReal> > cfwht;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT2DUnitTest::testCopyConstructor()
{
    try
    {
        TFWHT2D<klab::DoubleReal> fwht;
        TFWHT2D<klab::DoubleReal> fwhtCopy(fwht);
        TEST_ASSERT(true)

        TFWHT2D<std::complex<klab::DoubleReal> > cfwht;
        TFWHT2D<std::complex<klab::DoubleReal> > cfwhtCopy(cfwht);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT2DUnitTest::testAffectationOperator()
{
    try
    {
        TFWHT2D<klab::DoubleReal> fwht;
        TFWHT2D<klab::DoubleReal> fwhtCopy; 
        fwhtCopy = fwht;
        TEST_ASSERT(true)

        TFWHT2D<std::complex<klab::DoubleReal> > cfwht;
        TFWHT2D<std::complex<klab::DoubleReal> > cfwhtCopy;
        cfwhtCopy = cfwht;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT2DUnitTest::testTransform()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(m, n);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
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
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;


        TFWHT2D<klab::DoubleReal> fwht;

        fwht.transform(f, F);
        TEST_ASSERT(F.n_rows==m && F.n_cols==n)
        TEST_ASSERT(klab::Equals(F(0, 0), 7952.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 194.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), 310.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 520.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -860.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -26.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), -142.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 132.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 170.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), -16.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -64.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -130.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 22.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 28.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 36.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 114.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 82.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 72.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -336.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 126.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 282.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -296.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 208.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -10.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -148.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 6.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 106.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -28.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 84.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 22.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), 122.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 140.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 408.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 14.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 138.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), -184.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 484.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), -38.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -482.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 28.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 134.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -32.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -56.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -206.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), 10.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), 116.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), -76.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 270.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), -74.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 256.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 192.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -294.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 134.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), -168.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), -360.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), 602.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), -132.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 170.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -186.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), -100.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -84.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 162.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 478.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -196.0, precision))


        // Limit cases.
        fwht.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        try                                 {fwht.transform(arma::Mat<klab::DoubleReal>(7, 8), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.transform(arma::Mat<klab::DoubleReal>(8, 7), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.transform(arma::Mat<klab::DoubleReal>(7, 7), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT2DUnitTest::testTransform_02()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 4;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(m, n);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;        
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;        
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;        
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;        
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;        
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;        
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;        
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;


        TFWHT2D<klab::DoubleReal> fwht;

        fwht.transform(f, F);
        TEST_ASSERT(F.n_rows==m && F.n_cols==n)
        TEST_ASSERT(klab::Equals(F(0, 0), 3546.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 84.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), 84.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 326.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 96.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 6.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -14.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -8.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 182.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -112.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -64.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 58.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -32.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 14.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 114.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), 56.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), 446.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), -12.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), -172.0, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), -78.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 72.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 42.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), -66.0, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), 32.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 30.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), 44.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), -84.0, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 154., precision))
        TEST_ASSERT(klab::Equals(F(7, 0), -108.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), 166.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 146.0, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), -148.0, precision))


        // Limit cases.
        fwht.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        try                                 {fwht.transform(arma::Mat<klab::DoubleReal>(8, 3), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.transform(arma::Mat<klab::DoubleReal>(7, 4), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.transform(arma::Mat<klab::DoubleReal>(7, 3), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT2DUnitTest::testTransform_03()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(m, n);
        arma::Mat<klab::DoubleReal> F;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
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
        f(3, 7) = 157.0;


        TFWHT2D<klab::DoubleReal> fwht;

        fwht.transform(f, F);
        TEST_ASSERT(F.n_rows==m && F.n_cols==n)
        TEST_ASSERT(klab::Equals(F(0, 0), 4180.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), 104.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), 224.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 168.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), -188.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -32.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), -312.0, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 80.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 152.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), -24.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -60.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -168.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 16.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 72.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -20.0, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), 192.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 4.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 164.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -72.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -84.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 208.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), -232.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -76.0, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), 296.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -140.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 88.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), -40.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -64.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 0.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 92.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), 300.0, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), -28.0, precision))


        // Limit cases.
        fwht.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        try                                 {fwht.transform(arma::Mat<klab::DoubleReal>(3, 8), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.transform(arma::Mat<klab::DoubleReal>(4, 9), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.transform(arma::Mat<klab::DoubleReal>(3, 7), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT2DUnitTest::testInvert()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(m, n);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fr;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
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
        f(3, 7) = 157.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(4, 7) = 170.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(5, 7) = 195.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(6, 7) = 135.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;
        f(7, 7) = 93.0;


        TFWHT2D<klab::DoubleReal> fwht;

        fwht.transform(f, F);
        fwht.invert(F, fr);
        TEST_ASSERT(fr.n_rows==m && fr.n_cols==n)
        TEST_ASSERT(klab::Equals(fr(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fr(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fr(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fr(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fr(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fr(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fr(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fr(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fr(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fr(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fr(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fr(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fr(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fr(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fr(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fr(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fr(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fr(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fr(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fr(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fr(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fr(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fr(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fr(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fr(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fr(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fr(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fr(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fr(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fr(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fr(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fr(3, 7), f(3, 7), precision))
        TEST_ASSERT(klab::Equals(fr(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fr(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fr(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fr(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fr(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fr(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fr(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fr(4, 7), f(4, 7), precision))
        TEST_ASSERT(klab::Equals(fr(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fr(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fr(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fr(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fr(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fr(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fr(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fr(5, 7), f(5, 7), precision))
        TEST_ASSERT(klab::Equals(fr(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fr(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fr(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fr(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fr(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fr(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fr(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fr(6, 7), f(6, 7), precision))
        TEST_ASSERT(klab::Equals(fr(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fr(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fr(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fr(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fr(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fr(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fr(7, 6), f(7, 6), precision))
        TEST_ASSERT(klab::Equals(fr(7, 7), f(7, 7), precision))


        // Limit cases.
        fwht.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        try                                 {fwht.invert(arma::Mat<klab::DoubleReal>(7, 8), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.invert(arma::Mat<klab::DoubleReal>(8, 7), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.invert(arma::Mat<klab::DoubleReal>(7, 7), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT2DUnitTest::testInvert_02()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 4;
        klab::DoubleReal precision = 1e-12;


        arma::Mat<klab::DoubleReal> f(m, n);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fr;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;


        TFWHT2D<klab::DoubleReal> fwht;

        fwht.transform(f, F);
        fwht.invert(F, fr);
        TEST_ASSERT(fr.n_rows==m && fr.n_cols==n)
        TEST_ASSERT(klab::Equals(fr(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fr(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fr(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fr(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fr(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fr(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fr(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fr(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fr(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fr(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fr(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fr(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fr(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fr(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fr(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fr(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fr(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fr(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fr(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fr(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fr(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fr(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fr(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fr(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fr(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fr(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fr(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fr(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fr(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fr(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fr(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fr(7, 3), f(7, 3), precision))


        // Limit cases.
        fwht.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        try                                 {fwht.invert(arma::Mat<klab::DoubleReal>(7, 4), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.invert(arma::Mat<klab::DoubleReal>(8, 3), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.invert(arma::Mat<klab::DoubleReal>(7, 3), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT2DUnitTest::testInvert_03()
{
    try
    {
        klab::UInt32 m = 4;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<klab::DoubleReal> f(m, n);
        arma::Mat<klab::DoubleReal> F;
        arma::Mat<klab::DoubleReal> fr;

        f(0, 0) = 150.0;
        f(0, 1) = 111.0;
        f(0, 2) = 129.0;
        f(0, 3) = 139.0;
        f(0, 4) = 127.0;
        f(0, 5) = 143.0;
        f(0, 6) = 160.0;
        f(0, 7) = 90.0;
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(1, 7) = 85.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
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
        f(3, 7) = 157.0;


        TFWHT2D<klab::DoubleReal> fwht;

        fwht.transform(f, F);
        fwht.invert(F, fr);
        TEST_ASSERT(fr.n_rows==m && fr.n_cols==n)
        TEST_ASSERT(klab::Equals(fr(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fr(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fr(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fr(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fr(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fr(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fr(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fr(0, 7), f(0, 7), precision))
        TEST_ASSERT(klab::Equals(fr(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fr(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fr(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fr(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fr(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fr(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fr(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fr(1, 7), f(1, 7), precision))
        TEST_ASSERT(klab::Equals(fr(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fr(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fr(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fr(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fr(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fr(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fr(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fr(2, 7), f(2, 7), precision))
        TEST_ASSERT(klab::Equals(fr(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fr(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fr(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fr(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fr(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fr(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fr(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fr(3, 7), f(3, 7), precision))


        // Limit cases.
        fwht.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        try                                 {fwht.invert(arma::Mat<klab::DoubleReal>(4, 7), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.invert(arma::Mat<klab::DoubleReal>(3, 8), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        try                                 {fwht.invert(arma::Mat<klab::DoubleReal>(3, 7), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
