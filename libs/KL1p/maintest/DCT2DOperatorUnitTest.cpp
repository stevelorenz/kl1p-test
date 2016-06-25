// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KL1p C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#include "DCT2DOperatorUnitTest.h"
#include "../include/DCT2DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KDCT2DOperatorUnitTest::KDCT2DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KDCT2DOperatorUnitTest::testHeightWidthConstructor) 
    TEST_ADD(KDCT2DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KDCT2DOperatorUnitTest::testWidth) 
    TEST_ADD(KDCT2DOperatorUnitTest::testHeight) 
    TEST_ADD(KDCT2DOperatorUnitTest::testApply)
    TEST_ADD(KDCT2DOperatorUnitTest::testApply_Complex)
    TEST_ADD(KDCT2DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KDCT2DOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KDCT2DOperatorUnitTest::~KDCT2DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DOperatorUnitTest::testHeightWidthConstructor()
{
    try
    {
        TDCT2DOperator<klab::DoubleReal> op1(32, 64);
        TEST_ASSERT(op1.m()==2048 && op1.n()==2048)
        TEST_ASSERT(op1.height()==32 && op1.width()==64)

        TDCT2DOperator<std::complex<klab::DoubleReal> > op2(64, 32);
        TEST_ASSERT(op2.m()==2048 && op2.n()==2048)
        TEST_ASSERT(op2.height()==64 && op2.width()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        TDCT2DOperator<klab::DoubleReal> op1(32, 64);
        TDCT2DOperator<klab::DoubleReal> op1Copy(op1);
        TEST_ASSERT(op1Copy.m()==2048 && op1Copy.n()==2048)
        TEST_ASSERT(op1Copy.height()==32 && op1Copy.width()==64)

        TDCT2DOperator<std::complex<klab::DoubleReal> > op2(64, 32);
        TDCT2DOperator<std::complex<klab::DoubleReal> > op2Copy(op2);
        TEST_ASSERT(op2Copy.m()==2048 && op2Copy.n()==2048)
        TEST_ASSERT(op2Copy.height()==64 && op2Copy.width()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DOperatorUnitTest::testWidth()
{
    try
    {
        TDCT2DOperator<klab::DoubleReal> op1(0, 0);
        TEST_ASSERT(op1.m()==0 && op1.n()==0)
        TEST_ASSERT(op1.height()==0 && op1.width()==0)

        TDCT2DOperator<klab::DoubleReal> op2(32, 64);
        TEST_ASSERT(op2.m()==2048 && op2.n()==2048)
        TEST_ASSERT(op2.height()==32 && op2.width()==64)

        TDCT2DOperator<klab::DoubleReal> op3(64, 32);
        TEST_ASSERT(op3.m()==2048 && op3.n()==2048)
        TEST_ASSERT(op3.height()==64 && op3.width()==32)


        TDCT2DOperator<std::complex<klab::DoubleReal> > op4(0, 0);
        TEST_ASSERT(op4.m()==0 && op4.n()==0)
        TEST_ASSERT(op4.height()==0 && op4.width()==0)

        TDCT2DOperator<klab::DoubleReal> op5(32, 64);
        TEST_ASSERT(op5.m()==2048 && op5.n()==2048)
        TEST_ASSERT(op5.height()==32 && op5.width()==64)

        TDCT2DOperator<klab::DoubleReal> op6(64, 32);
        TEST_ASSERT(op6.m()==2048 && op6.n()==2048)
        TEST_ASSERT(op6.height()==64 && op6.width()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DOperatorUnitTest::testHeight()
{
    try
    {
        TDCT2DOperator<klab::DoubleReal> op1(0, 0);
        TEST_ASSERT(op1.m()==0 && op1.n()==0)
        TEST_ASSERT(op1.height()==0 && op1.width()==0)

        TDCT2DOperator<klab::DoubleReal> op2(32, 64);
        TEST_ASSERT(op2.m()==2048 && op2.n()==2048)
        TEST_ASSERT(op2.height()==32 && op2.width()==64)

        TDCT2DOperator<klab::DoubleReal> op3(64, 32);
        TEST_ASSERT(op3.m()==2048 && op3.n()==2048)
        TEST_ASSERT(op3.height()==64 && op3.width()==32)


        TDCT2DOperator<std::complex<klab::DoubleReal> > op4(0, 0);
        TEST_ASSERT(op4.m()==0 && op4.n()==0)
        TEST_ASSERT(op4.height()==0 && op4.width()==0)

        TDCT2DOperator<klab::DoubleReal> op5(32, 64);
        TEST_ASSERT(op5.m()==2048 && op5.n()==2048)
        TEST_ASSERT(op5.height()==32 && op5.width()==64)

        TDCT2DOperator<klab::DoubleReal> op6(64, 32);
        TEST_ASSERT(op6.m()==2048 && op6.n()==2048)
        TEST_ASSERT(op6.height()==64 && op6.width()==32)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DOperatorUnitTest::testApply()
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

        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        f.reshape(8, 8);

        TDCT2DOperator<klab::DoubleReal> op(8, 8);
        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(F.n_rows==m && F.n_cols==n)
        TEST_ASSERT(klab::Equals(F(0, 0), 993.99999999999989, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -79.725687570031695, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -17.642582857261822, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 77.597126833117841, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 65.000000000000043, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -22.353875643833121, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 3.7900224438186507, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 32.26344514199868, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 55.121588424797956, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 62.896418469705921, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -52.093248079998347, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -17.651277683044238, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -16.925155746483991, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 21.07155482851395, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 0.93401359628967739, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -12.439383866665844, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), -2.1359381836141518, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 20.670701910318009, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -47.06980515339464, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 58.172551983704508, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), -43.806671203190859, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 65.632348515986791, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 4.5030483272049366, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), -9.8702793143597454, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -12.305059475689626, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), -12.645289431786033, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 59.345692892650746, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -42.820191279106709, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 9.5462896570149152, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 23.45056917390502, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -41.654504309270642, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 22.910800486414974, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -18.500000000000004, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 13.316132234562343, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 15.141542309801121, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 15.979219070479832, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -3.4999999999999996, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 9.1131724102100282, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -3.2952536291615822, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), -8.7704201057332547, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -0.33153898154587147, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -6.4212081265006287, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 32.823958693327114, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), 3.4652877996664477, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -27.746936220141126, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -11.384390185138166, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 23.909557929214703, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), 17.086943615247598, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 19.01480391894113, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -13.687552399773056, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 16.003048327204937, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -12.516658300326551, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -9.7262818227485894, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 3.6753141068708395, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 16.56980515339464, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), -13.224028632860408, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 15.49067728443905, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -9.4246652409044138, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), -9.0224062674116485, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 12.196212124452416, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), -7.0632844440140614, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 10.859129957041418, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), 2.8599107314539114, precision))
        TEST_ASSERT(klab::Equals(F(7, 7), -16.691837005461053, precision))


        // Limit cases.
        try                                         {op.apply(arma::Col<klab::DoubleReal>(), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<klab::DoubleReal>(56), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<klab::DoubleReal>(49), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<klab::DoubleReal>(63), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > f(m, n);
        arma::Mat<std::complex<klab::DoubleReal> > F;

        f(0, 0) = std::complex<klab::DoubleReal>(150.0, 0.0);
        f(0, 1) = std::complex<klab::DoubleReal>(111.0, 0.0);
        f(0, 2) = std::complex<klab::DoubleReal>(129.0, 0.0);
        f(0, 3) = std::complex<klab::DoubleReal>(139.0, 0.0);
        f(0, 4) = std::complex<klab::DoubleReal>(127.0, 0.0);
        f(0, 5) = std::complex<klab::DoubleReal>(143.0, 0.0);
        f(0, 6) = std::complex<klab::DoubleReal>(160.0, 0.0);
        f(0, 7) = std::complex<klab::DoubleReal>(90.0, 0.0);
        f(1, 0) = std::complex<klab::DoubleReal>(127.0, 0.0);
        f(1, 1) = std::complex<klab::DoubleReal>(108.0, 0.0);
        f(1, 2) = std::complex<klab::DoubleReal>(120.0, 0.0);
        f(1, 3) = std::complex<klab::DoubleReal>(167.0, 0.0);
        f(1, 4) = std::complex<klab::DoubleReal>(182.0, 0.0);
        f(1, 5) = std::complex<klab::DoubleReal>(136.0, 0.0);
        f(1, 6) = std::complex<klab::DoubleReal>(118.0, 0.0);
        f(1, 7) = std::complex<klab::DoubleReal>(85.0, 0.0);
        f(2, 0) = std::complex<klab::DoubleReal>(124.0, 0.0);
        f(2, 1) = std::complex<klab::DoubleReal>(114.0, 0.0);
        f(2, 2) = std::complex<klab::DoubleReal>(132.0, 0.0);
        f(2, 3) = std::complex<klab::DoubleReal>(141.0, 0.0);
        f(2, 4) = std::complex<klab::DoubleReal>(171.0, 0.0);
        f(2, 5) = std::complex<klab::DoubleReal>(184.0, 0.0);
        f(2, 6) = std::complex<klab::DoubleReal>(110.0, 0.0);
        f(2, 7) = std::complex<klab::DoubleReal>(141.0, 0.0);
        f(3, 0) = std::complex<klab::DoubleReal>(127.0, 0.0);
        f(3, 1) = std::complex<klab::DoubleReal>(115.0, 0.0);
        f(3, 2) = std::complex<klab::DoubleReal>(107.0, 0.0);
        f(3, 3) = std::complex<klab::DoubleReal>(85.0, 0.0);
        f(3, 4) = std::complex<klab::DoubleReal>(161.0, 0.0);
        f(3, 5) = std::complex<klab::DoubleReal>(122.0, 0.0);
        f(3, 6) = std::complex<klab::DoubleReal>(97.0, 0.0);
        f(3, 7) = std::complex<klab::DoubleReal>(157.0, 0.0);
        f(4, 0) = std::complex<klab::DoubleReal>(121.0, 0.0);
        f(4, 1) = std::complex<klab::DoubleReal>(107.0, 0.0);
        f(4, 2) = std::complex<klab::DoubleReal>(73.0, 0.0);
        f(4, 3) = std::complex<klab::DoubleReal>(118.0, 0.0);
        f(4, 4) = std::complex<klab::DoubleReal>(153.0, 0.0);
        f(4, 5) = std::complex<klab::DoubleReal>(97.0, 0.0);
        f(4, 6) = std::complex<klab::DoubleReal>(126.0, 0.0);
        f(4, 7) = std::complex<klab::DoubleReal>(170.0, 0.0);
        f(5, 0) = std::complex<klab::DoubleReal>(115.0, 0.0);
        f(5, 1) = std::complex<klab::DoubleReal>(98.0, 0.0);
        f(5, 2) = std::complex<klab::DoubleReal>(90.0, 0.0);
        f(5, 3) = std::complex<klab::DoubleReal>(91.0, 0.0);
        f(5, 4) = std::complex<klab::DoubleReal>(140.0, 0.0);
        f(5, 5) = std::complex<klab::DoubleReal>(87.0, 0.0);
        f(5, 6) = std::complex<klab::DoubleReal>(144.0, 0.0);
        f(5, 7) = std::complex<klab::DoubleReal>(195.0, 0.0);
        f(6, 0) = std::complex<klab::DoubleReal>(120.0, 0.0);
        f(6, 1) = std::complex<klab::DoubleReal>(81.0, 0.0);
        f(6, 2) = std::complex<klab::DoubleReal>(84.0, 0.0);
        f(6, 3) = std::complex<klab::DoubleReal>(77.0, 0.0);
        f(6, 4) = std::complex<klab::DoubleReal>(151.0, 0.0);
        f(6, 5) = std::complex<klab::DoubleReal>(138.0, 0.0);
        f(6, 6) = std::complex<klab::DoubleReal>(144.0, 0.0);
        f(6, 7) = std::complex<klab::DoubleReal>(135.0, 0.0);
        f(7, 0) = std::complex<klab::DoubleReal>(126.0, 0.0);
        f(7, 1) = std::complex<klab::DoubleReal>(71.0, 0.0);
        f(7, 2) = std::complex<klab::DoubleReal>(70.0, 0.0);
        f(7, 3) = std::complex<klab::DoubleReal>(108.0, 0.0);
        f(7, 4) = std::complex<klab::DoubleReal>(149.0, 0.0);
        f(7, 5) = std::complex<klab::DoubleReal>(175.0, 0.0);
        f(7, 6) = std::complex<klab::DoubleReal>(125.0, 0.0);
        f(7, 7) = std::complex<klab::DoubleReal>(93.0, 0.0);

        f.reshape(64, 1);
        arma::Col<std::complex<klab::DoubleReal> > x(f);
        arma::Col<std::complex<klab::DoubleReal> > y;
        f.reshape(8, 8);

        TDCT2DOperator<std::complex<klab::DoubleReal> > op(8, 8);
        op.apply(x, y);
        F = y;
        F.reshape(8, 8);

        TEST_ASSERT(F.n_rows==m && F.n_cols==n)
        TEST_ASSERT(klab::Equals(F(0, 0), std::complex<klab::DoubleReal>(993.99999999999989, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 1), std::complex<klab::DoubleReal>(-79.725687570031695, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 2), std::complex<klab::DoubleReal>(-17.642582857261822, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 3), std::complex<klab::DoubleReal>(77.597126833117841, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 4), std::complex<klab::DoubleReal>(65.000000000000043, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 5), std::complex<klab::DoubleReal>(-22.353875643833121, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 6), std::complex<klab::DoubleReal>(3.7900224438186507, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(0, 7), std::complex<klab::DoubleReal>(32.26344514199868, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 0), std::complex<klab::DoubleReal>(55.121588424797956, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 1), std::complex<klab::DoubleReal>(62.896418469705921, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 2), std::complex<klab::DoubleReal>(-52.093248079998347, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 3), std::complex<klab::DoubleReal>(-17.651277683044238, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 4), std::complex<klab::DoubleReal>(-16.925155746483991, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 5), std::complex<klab::DoubleReal>(21.07155482851395, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 6), std::complex<klab::DoubleReal>(0.93401359628967739, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(1, 7), std::complex<klab::DoubleReal>(-12.439383866665844, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 0), std::complex<klab::DoubleReal>(-2.1359381836141518, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 1), std::complex<klab::DoubleReal>(20.670701910318009, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 2), std::complex<klab::DoubleReal>(-47.06980515339464, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 3), std::complex<klab::DoubleReal>(58.172551983704508, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 4), std::complex<klab::DoubleReal>(-43.806671203190859, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 5), std::complex<klab::DoubleReal>(65.632348515986791, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 6), std::complex<klab::DoubleReal>(4.5030483272049366, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(2, 7), std::complex<klab::DoubleReal>(-9.8702793143597454, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 0), std::complex<klab::DoubleReal>(-12.305059475689626, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 1), std::complex<klab::DoubleReal>(-12.645289431786033, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 2), std::complex<klab::DoubleReal>(59.345692892650746, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 3), std::complex<klab::DoubleReal>(-42.820191279106709, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 4), std::complex<klab::DoubleReal>(9.5462896570149152, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 5), std::complex<klab::DoubleReal>(23.45056917390502, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 6), std::complex<klab::DoubleReal>(-41.654504309270642, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(3, 7), std::complex<klab::DoubleReal>(22.910800486414974, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 0), std::complex<klab::DoubleReal>(-18.500000000000004, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 1), std::complex<klab::DoubleReal>(13.316132234562343, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 2), std::complex<klab::DoubleReal>(15.141542309801121, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 3), std::complex<klab::DoubleReal>(15.979219070479832, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 4), std::complex<klab::DoubleReal>(-3.4999999999999996, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 5), std::complex<klab::DoubleReal>(9.1131724102100282, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 6), std::complex<klab::DoubleReal>(-3.2952536291615822, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(4, 7), std::complex<klab::DoubleReal>(-8.7704201057332547, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 0), std::complex<klab::DoubleReal>(-0.33153898154587147, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 1), std::complex<klab::DoubleReal>(-6.4212081265006287, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 2), std::complex<klab::DoubleReal>(32.823958693327114, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 3), std::complex<klab::DoubleReal>(3.4652877996664477, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 4), std::complex<klab::DoubleReal>(-27.746936220141126, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 5), std::complex<klab::DoubleReal>(-11.384390185138166, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 6), std::complex<klab::DoubleReal>(23.909557929214703, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(5, 7), std::complex<klab::DoubleReal>(17.086943615247598, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 0), std::complex<klab::DoubleReal>(19.01480391894113, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 1), std::complex<klab::DoubleReal>(-13.687552399773056, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 2), std::complex<klab::DoubleReal>(16.003048327204937, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 3), std::complex<klab::DoubleReal>(-12.516658300326551, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 4), std::complex<klab::DoubleReal>(-9.7262818227485894, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 5), std::complex<klab::DoubleReal>(3.6753141068708395, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 6), std::complex<klab::DoubleReal>(16.56980515339464, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(6, 7), std::complex<klab::DoubleReal>(-13.224028632860408, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 0), std::complex<klab::DoubleReal>(15.49067728443905, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 1), std::complex<klab::DoubleReal>(-9.4246652409044138, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 2), std::complex<klab::DoubleReal>(-9.0224062674116485, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 3), std::complex<klab::DoubleReal>(12.196212124452416, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 4), std::complex<klab::DoubleReal>(-7.0632844440140614, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 5), std::complex<klab::DoubleReal>(10.859129957041418, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 6), std::complex<klab::DoubleReal>(2.8599107314539114, 0.0), precision))
        TEST_ASSERT(klab::Equals(F(7, 7), std::complex<klab::DoubleReal>(-16.691837005461053, 0.0), precision))


        // Limit cases.
        try                                         {op.apply(arma::Col<std::complex<klab::DoubleReal> >(), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<std::complex<klab::DoubleReal> >(56), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<std::complex<klab::DoubleReal> >(49), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.apply(arma::Col<std::complex<klab::DoubleReal> >(63), y); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DOperatorUnitTest::testApplyAdjoint()
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

        f.reshape(64, 1);
        arma::Col<klab::DoubleReal> x(f);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        f.reshape(8, 8);

        klab::TFCT2D<klab::DoubleReal> fct;
        arma::Mat<klab::DoubleReal> fctMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<klab::DoubleReal> base(64);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<klab::DoubleReal> inMatrix(base);
            arma::Mat<klab::DoubleReal> outMatrix;
            inMatrix.reshape(8, 8);
            fct.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fctMatrix(i, j) = outMatrix[i];
        } 


        TDCT2DOperator<klab::DoubleReal> op(8, 8);
        op.apply(x, y);

        arma::Col<klab::DoubleReal> xt = arma::trans(fctMatrix) * y;

        op.applyAdjoint(y, xr);
        F = xr;
        F.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
        TEST_ASSERT(klab::Equals(xr[8], xt[8], precision))
        TEST_ASSERT(klab::Equals(xr[9], xt[9], precision))
        TEST_ASSERT(klab::Equals(xr[10], xt[10], precision))
        TEST_ASSERT(klab::Equals(xr[11], xt[11], precision))
        TEST_ASSERT(klab::Equals(xr[12], xt[12], precision))
        TEST_ASSERT(klab::Equals(xr[13], xt[13], precision))
        TEST_ASSERT(klab::Equals(xr[14], xt[14], precision))
        TEST_ASSERT(klab::Equals(xr[15], xt[15], precision))
        TEST_ASSERT(klab::Equals(xr[16], xt[16], precision))
        TEST_ASSERT(klab::Equals(xr[17], xt[17], precision))
        TEST_ASSERT(klab::Equals(xr[18], xt[18], precision))
        TEST_ASSERT(klab::Equals(xr[19], xt[19], precision))
        TEST_ASSERT(klab::Equals(xr[20], xt[20], precision))
        TEST_ASSERT(klab::Equals(xr[21], xt[21], precision))
        TEST_ASSERT(klab::Equals(xr[22], xt[22], precision))
        TEST_ASSERT(klab::Equals(xr[23], xt[23], precision))
        TEST_ASSERT(klab::Equals(xr[24], xt[24], precision))
        TEST_ASSERT(klab::Equals(xr[25], xt[25], precision))
        TEST_ASSERT(klab::Equals(xr[26], xt[26], precision))
        TEST_ASSERT(klab::Equals(xr[27], xt[27], precision))
        TEST_ASSERT(klab::Equals(xr[28], xt[28], precision))
        TEST_ASSERT(klab::Equals(xr[29], xt[29], precision))
        TEST_ASSERT(klab::Equals(xr[30], xt[30], precision))
        TEST_ASSERT(klab::Equals(xr[31], xt[31], precision))
        TEST_ASSERT(klab::Equals(xr[32], xt[32], precision))
        TEST_ASSERT(klab::Equals(xr[33], xt[33], precision))
        TEST_ASSERT(klab::Equals(xr[34], xt[34], precision))
        TEST_ASSERT(klab::Equals(xr[35], xt[35], precision))
        TEST_ASSERT(klab::Equals(xr[36], xt[36], precision))
        TEST_ASSERT(klab::Equals(xr[37], xt[37], precision))
        TEST_ASSERT(klab::Equals(xr[38], xt[38], precision))
        TEST_ASSERT(klab::Equals(xr[39], xt[39], precision))
        TEST_ASSERT(klab::Equals(xr[40], xt[40], precision))
        TEST_ASSERT(klab::Equals(xr[41], xt[41], precision))
        TEST_ASSERT(klab::Equals(xr[42], xt[42], precision))
        TEST_ASSERT(klab::Equals(xr[43], xt[43], precision))
        TEST_ASSERT(klab::Equals(xr[44], xt[44], precision))
        TEST_ASSERT(klab::Equals(xr[45], xt[45], precision))
        TEST_ASSERT(klab::Equals(xr[46], xt[46], precision))
        TEST_ASSERT(klab::Equals(xr[47], xt[47], precision))
        TEST_ASSERT(klab::Equals(xr[48], xt[48], precision))
        TEST_ASSERT(klab::Equals(xr[49], xt[49], precision))
        TEST_ASSERT(klab::Equals(xr[50], xt[50], precision))
        TEST_ASSERT(klab::Equals(xr[51], xt[51], precision))
        TEST_ASSERT(klab::Equals(xr[52], xt[52], precision))
        TEST_ASSERT(klab::Equals(xr[53], xt[53], precision))
        TEST_ASSERT(klab::Equals(xr[54], xt[54], precision))
        TEST_ASSERT(klab::Equals(xr[55], xt[55], precision))
        TEST_ASSERT(klab::Equals(xr[56], xt[56], precision))
        TEST_ASSERT(klab::Equals(xr[57], xt[57], precision))
        TEST_ASSERT(klab::Equals(xr[58], xt[58], precision))
        TEST_ASSERT(klab::Equals(xr[59], xt[59], precision))
        TEST_ASSERT(klab::Equals(xr[60], xt[60], precision))
        TEST_ASSERT(klab::Equals(xr[61], xt[61], precision))
        TEST_ASSERT(klab::Equals(xr[62], xt[62], precision))
        TEST_ASSERT(klab::Equals(xr[63], xt[63], precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    
        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(56), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(49), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<klab::DoubleReal>(63), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > f(m, n);
        arma::Mat<std::complex<klab::DoubleReal> > F;

        f(0, 0) = std::complex<klab::DoubleReal>(150.0, 0.0);
        f(0, 1) = std::complex<klab::DoubleReal>(111.0, 0.0);
        f(0, 2) = std::complex<klab::DoubleReal>(129.0, 0.0);
        f(0, 3) = std::complex<klab::DoubleReal>(139.0, 0.0);
        f(0, 4) = std::complex<klab::DoubleReal>(127.0, 0.0);
        f(0, 5) = std::complex<klab::DoubleReal>(143.0, 0.0);
        f(0, 6) = std::complex<klab::DoubleReal>(160.0, 0.0);
        f(0, 7) = std::complex<klab::DoubleReal>(90.0, 0.0);
        f(1, 0) = std::complex<klab::DoubleReal>(127.0, 0.0);
        f(1, 1) = std::complex<klab::DoubleReal>(108.0, 0.0);
        f(1, 2) = std::complex<klab::DoubleReal>(120.0, 0.0);
        f(1, 3) = std::complex<klab::DoubleReal>(167.0, 0.0);
        f(1, 4) = std::complex<klab::DoubleReal>(182.0, 0.0);
        f(1, 5) = std::complex<klab::DoubleReal>(136.0, 0.0);
        f(1, 6) = std::complex<klab::DoubleReal>(118.0, 0.0);
        f(1, 7) = std::complex<klab::DoubleReal>(85.0, 0.0);
        f(2, 0) = std::complex<klab::DoubleReal>(124.0, 0.0);
        f(2, 1) = std::complex<klab::DoubleReal>(114.0, 0.0);
        f(2, 2) = std::complex<klab::DoubleReal>(132.0, 0.0);
        f(2, 3) = std::complex<klab::DoubleReal>(141.0, 0.0);
        f(2, 4) = std::complex<klab::DoubleReal>(171.0, 0.0);
        f(2, 5) = std::complex<klab::DoubleReal>(184.0, 0.0);
        f(2, 6) = std::complex<klab::DoubleReal>(110.0, 0.0);
        f(2, 7) = std::complex<klab::DoubleReal>(141.0, 0.0);
        f(3, 0) = std::complex<klab::DoubleReal>(127.0, 0.0);
        f(3, 1) = std::complex<klab::DoubleReal>(115.0, 0.0);
        f(3, 2) = std::complex<klab::DoubleReal>(107.0, 0.0);
        f(3, 3) = std::complex<klab::DoubleReal>(85.0, 0.0);
        f(3, 4) = std::complex<klab::DoubleReal>(161.0, 0.0);
        f(3, 5) = std::complex<klab::DoubleReal>(122.0, 0.0);
        f(3, 6) = std::complex<klab::DoubleReal>(97.0, 0.0);
        f(3, 7) = std::complex<klab::DoubleReal>(157.0, 0.0);
        f(4, 0) = std::complex<klab::DoubleReal>(121.0, 0.0);
        f(4, 1) = std::complex<klab::DoubleReal>(107.0, 0.0);
        f(4, 2) = std::complex<klab::DoubleReal>(73.0, 0.0);
        f(4, 3) = std::complex<klab::DoubleReal>(118.0, 0.0);
        f(4, 4) = std::complex<klab::DoubleReal>(153.0, 0.0);
        f(4, 5) = std::complex<klab::DoubleReal>(97.0, 0.0);
        f(4, 6) = std::complex<klab::DoubleReal>(126.0, 0.0);
        f(4, 7) = std::complex<klab::DoubleReal>(170.0, 0.0);
        f(5, 0) = std::complex<klab::DoubleReal>(115.0, 0.0);
        f(5, 1) = std::complex<klab::DoubleReal>(98.0, 0.0);
        f(5, 2) = std::complex<klab::DoubleReal>(90.0, 0.0);
        f(5, 3) = std::complex<klab::DoubleReal>(91.0, 0.0);
        f(5, 4) = std::complex<klab::DoubleReal>(140.0, 0.0);
        f(5, 5) = std::complex<klab::DoubleReal>(87.0, 0.0);
        f(5, 6) = std::complex<klab::DoubleReal>(144.0, 0.0);
        f(5, 7) = std::complex<klab::DoubleReal>(195.0, 0.0);
        f(6, 0) = std::complex<klab::DoubleReal>(120.0, 0.0);
        f(6, 1) = std::complex<klab::DoubleReal>(81.0, 0.0);
        f(6, 2) = std::complex<klab::DoubleReal>(84.0, 0.0);
        f(6, 3) = std::complex<klab::DoubleReal>(77.0, 0.0);
        f(6, 4) = std::complex<klab::DoubleReal>(151.0, 0.0);
        f(6, 5) = std::complex<klab::DoubleReal>(138.0, 0.0);
        f(6, 6) = std::complex<klab::DoubleReal>(144.0, 0.0);
        f(6, 7) = std::complex<klab::DoubleReal>(135.0, 0.0);
        f(7, 0) = std::complex<klab::DoubleReal>(126.0, 0.0);
        f(7, 1) = std::complex<klab::DoubleReal>(71.0, 0.0);
        f(7, 2) = std::complex<klab::DoubleReal>(70.0, 0.0);
        f(7, 3) = std::complex<klab::DoubleReal>(108.0, 0.0);
        f(7, 4) = std::complex<klab::DoubleReal>(149.0, 0.0);
        f(7, 5) = std::complex<klab::DoubleReal>(175.0, 0.0);
        f(7, 6) = std::complex<klab::DoubleReal>(125.0, 0.0);
        f(7, 7) = std::complex<klab::DoubleReal>(93.0, 0.0);

        f.reshape(64, 1);
        arma::Col<std::complex<klab::DoubleReal> > x(f);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;
        f.reshape(8, 8);

        klab::TFCT2D<std::complex<klab::DoubleReal> > fct;
        arma::Mat<std::complex<klab::DoubleReal> > fctMatrix(64, 64);
        for(klab::UInt32 j=0; j<64; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(64);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(0.0);
            base[j] = 1.0;

            arma::Mat<std::complex<klab::DoubleReal> > inMatrix(base);
            arma::Mat<std::complex<klab::DoubleReal> > outMatrix;
            inMatrix.reshape(8, 8);
            fct.transform(inMatrix, outMatrix);
            outMatrix.reshape(64, 1);

            for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
                fctMatrix(i, j) = outMatrix[i];
        } 


        TDCT2DOperator<std::complex<klab::DoubleReal> > op(8, 8);
        op.apply(x, y);

        arma::Col<std::complex<klab::DoubleReal> > xt = arma::trans(fctMatrix) * y;

        op.applyAdjoint(y, xr);
        F = xr;
        F.reshape(8, 8);

        TEST_ASSERT(xr.n_rows==64)
        TEST_ASSERT(F.n_rows==8 && F.n_cols==8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
        TEST_ASSERT(klab::Equals(xr[8], xt[8], precision))
        TEST_ASSERT(klab::Equals(xr[9], xt[9], precision))
        TEST_ASSERT(klab::Equals(xr[10], xt[10], precision))
        TEST_ASSERT(klab::Equals(xr[11], xt[11], precision))
        TEST_ASSERT(klab::Equals(xr[12], xt[12], precision))
        TEST_ASSERT(klab::Equals(xr[13], xt[13], precision))
        TEST_ASSERT(klab::Equals(xr[14], xt[14], precision))
        TEST_ASSERT(klab::Equals(xr[15], xt[15], precision))
        TEST_ASSERT(klab::Equals(xr[16], xt[16], precision))
        TEST_ASSERT(klab::Equals(xr[17], xt[17], precision))
        TEST_ASSERT(klab::Equals(xr[18], xt[18], precision))
        TEST_ASSERT(klab::Equals(xr[19], xt[19], precision))
        TEST_ASSERT(klab::Equals(xr[20], xt[20], precision))
        TEST_ASSERT(klab::Equals(xr[21], xt[21], precision))
        TEST_ASSERT(klab::Equals(xr[22], xt[22], precision))
        TEST_ASSERT(klab::Equals(xr[23], xt[23], precision))
        TEST_ASSERT(klab::Equals(xr[24], xt[24], precision))
        TEST_ASSERT(klab::Equals(xr[25], xt[25], precision))
        TEST_ASSERT(klab::Equals(xr[26], xt[26], precision))
        TEST_ASSERT(klab::Equals(xr[27], xt[27], precision))
        TEST_ASSERT(klab::Equals(xr[28], xt[28], precision))
        TEST_ASSERT(klab::Equals(xr[29], xt[29], precision))
        TEST_ASSERT(klab::Equals(xr[30], xt[30], precision))
        TEST_ASSERT(klab::Equals(xr[31], xt[31], precision))
        TEST_ASSERT(klab::Equals(xr[32], xt[32], precision))
        TEST_ASSERT(klab::Equals(xr[33], xt[33], precision))
        TEST_ASSERT(klab::Equals(xr[34], xt[34], precision))
        TEST_ASSERT(klab::Equals(xr[35], xt[35], precision))
        TEST_ASSERT(klab::Equals(xr[36], xt[36], precision))
        TEST_ASSERT(klab::Equals(xr[37], xt[37], precision))
        TEST_ASSERT(klab::Equals(xr[38], xt[38], precision))
        TEST_ASSERT(klab::Equals(xr[39], xt[39], precision))
        TEST_ASSERT(klab::Equals(xr[40], xt[40], precision))
        TEST_ASSERT(klab::Equals(xr[41], xt[41], precision))
        TEST_ASSERT(klab::Equals(xr[42], xt[42], precision))
        TEST_ASSERT(klab::Equals(xr[43], xt[43], precision))
        TEST_ASSERT(klab::Equals(xr[44], xt[44], precision))
        TEST_ASSERT(klab::Equals(xr[45], xt[45], precision))
        TEST_ASSERT(klab::Equals(xr[46], xt[46], precision))
        TEST_ASSERT(klab::Equals(xr[47], xt[47], precision))
        TEST_ASSERT(klab::Equals(xr[48], xt[48], precision))
        TEST_ASSERT(klab::Equals(xr[49], xt[49], precision))
        TEST_ASSERT(klab::Equals(xr[50], xt[50], precision))
        TEST_ASSERT(klab::Equals(xr[51], xt[51], precision))
        TEST_ASSERT(klab::Equals(xr[52], xt[52], precision))
        TEST_ASSERT(klab::Equals(xr[53], xt[53], precision))
        TEST_ASSERT(klab::Equals(xr[54], xt[54], precision))
        TEST_ASSERT(klab::Equals(xr[55], xt[55], precision))
        TEST_ASSERT(klab::Equals(xr[56], xt[56], precision))
        TEST_ASSERT(klab::Equals(xr[57], xt[57], precision))
        TEST_ASSERT(klab::Equals(xr[58], xt[58], precision))
        TEST_ASSERT(klab::Equals(xr[59], xt[59], precision))
        TEST_ASSERT(klab::Equals(xr[60], xt[60], precision))
        TEST_ASSERT(klab::Equals(xr[61], xt[61], precision))
        TEST_ASSERT(klab::Equals(xr[62], xt[62], precision))
        TEST_ASSERT(klab::Equals(xr[63], xt[63], precision))


        // Limit cases.
        try                                         {op.applyAdjoint(arma::Col<std::complex<klab::DoubleReal> >(), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<std::complex<klab::DoubleReal> >(56), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<std::complex<klab::DoubleReal> >(49), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {op.applyAdjoint(arma::Col<std::complex<klab::DoubleReal> >(63), xr); TEST_ASSERT(false)}
        catch(KIncompatibleSizeOperatorException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
