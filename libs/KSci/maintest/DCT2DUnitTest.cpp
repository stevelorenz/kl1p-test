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

#include "DCT2DUnitTest.h"
#include "../include/DCT2D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KDCT2DUnitTest::KDCT2DUnitTest() : Test::Suite()
{
    TEST_ADD(KDCT2DUnitTest::testDefaultConstructor)  
    TEST_ADD(KDCT2DUnitTest::testCopyConstructor)
    TEST_ADD(KDCT2DUnitTest::testAffectationOperator)

    TEST_ADD(KDCT2DUnitTest::testTransform)
    TEST_ADD(KDCT2DUnitTest::testTransform_02)
    TEST_ADD(KDCT2DUnitTest::testTransform_03)
    TEST_ADD(KDCT2DUnitTest::testTransform_04)
    TEST_ADD(KDCT2DUnitTest::testTransform_Complex)
    TEST_ADD(KDCT2DUnitTest::testInvert)   
    TEST_ADD(KDCT2DUnitTest::testInvert_02) 
    TEST_ADD(KDCT2DUnitTest::testInvert_03) 
    TEST_ADD(KDCT2DUnitTest::testInvert_04) 
    TEST_ADD(KDCT2DUnitTest::testInvert_Complex)  
}

// ---------------------------------------------------------------------------------------------------- //

KDCT2DUnitTest::~KDCT2DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testDefaultConstructor()
{
    try
    {
        TDCT2D<klab::DoubleReal> dct;
        TEST_ASSERT(true)

        TDCT2D<std::complex<klab::DoubleReal> > cdct;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testCopyConstructor()
{
    try
    {
        TDCT2D<klab::DoubleReal> dct;
        TDCT2D<klab::DoubleReal> dctCopy(dct);
        TEST_ASSERT(true)

        TDCT2D<std::complex<klab::DoubleReal> > cdct;
        TDCT2D<std::complex<klab::DoubleReal> > cdctCopy(cdct);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testAffectationOperator()
{
    try
    {
        TDCT2D<klab::DoubleReal> dct;
        TDCT2D<klab::DoubleReal> dctCopy; 
        dctCopy = dct;
        TEST_ASSERT(true)

        TDCT2D<std::complex<klab::DoubleReal> > cdct;
        TDCT2D<std::complex<klab::DoubleReal> > cdctCopy;
        cdctCopy = cdct;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testTransform()
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


        TDCT2D<klab::DoubleReal> dct;

        dct.transform(f, F);
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
        dct.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.transform(arma::Mat<klab::DoubleReal>(8, 0), F);
        TEST_ASSERT(F.n_rows==8 && F.n_cols==0)

        dct.transform(arma::Mat<klab::DoubleReal>(0, 8), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testTransform_02()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 7;
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
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;


        TDCT2D<klab::DoubleReal> dct;

        dct.transform(f, F);
        TEST_ASSERT(F.n_rows==m && F.n_cols==n)
        TEST_ASSERT(klab::Equals(F(0, 0), 920.18045590447707, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -78.683214434105551, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), 10.426522982034964, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 99.685149375351841, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 7.6216193757920818, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -13.498065058753685, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 35.369508167689006, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 73.489067796912849, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 33.031176233241645, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -45.758452342947514, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -20.181393995409934, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 5.8448282083027205, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 13.205316128774475, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -14.83417382143732, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 31.247691185838047, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -32.765799771420873, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 14.861036489791729, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -0.25122672545484798, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 16.637945070734801, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 40.216157633004244, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -18.448495410053493, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -25.900554758695815, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 14.555084730643246, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 32.990966645077762, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -43.444793270922077, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 44.264859172080179, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -37.641392395370616, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), 13.995048660358204, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -13.630323337533644, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 10.674475753846878, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 21.711967197097295, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 4.6049361434803044, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), 3.7199552056427789, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 2.7794118973271815, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), -10.43272253126997, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), -5.273367635165398, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 3.3079016610481338, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 31.396682506819463, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -14.714744610132939, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -26.466459145414071, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), 18.018468239746078, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 21.409190610604963, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 10.488582696583471, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -2.6710537230797433, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 7.465762833740663, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), -14.64858306062961, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -4.4207276585797102, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 18.372109351764298, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), -9.8499937171532714, precision))
        TEST_ASSERT(klab::Equals(F(7, 0), 17.496809501892294, precision))
        TEST_ASSERT(klab::Equals(F(7, 1), -16.371214065557655, precision))
        TEST_ASSERT(klab::Equals(F(7, 2), 2.4052692436644185, precision))
        TEST_ASSERT(klab::Equals(F(7, 3), 3.002024300505882, precision))
        TEST_ASSERT(klab::Equals(F(7, 4), 0.74878925523796236, precision))
        TEST_ASSERT(klab::Equals(F(7, 5), 10.836856727372002, precision))
        TEST_ASSERT(klab::Equals(F(7, 6), -17.33358396522592, precision))


        // Limit cases.
        dct.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.transform(arma::Mat<klab::DoubleReal>(8, 0), F);
        TEST_ASSERT(F.n_rows==8 && F.n_cols==0)

        dct.transform(arma::Mat<klab::DoubleReal>(0, 7), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testTransform_03()
{
    try
    {
        klab::UInt32 m = 7;
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


        TDCT2D<klab::DoubleReal> dct;

        dct.transform(f, F);
        TEST_ASSERT(F.n_rows==m && F.n_cols==n)
        TEST_ASSERT(klab::Equals(F(0, 0), 940.0914184269526, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -70.325878794282573, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), -8.6823370727761926, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 52.011961013180283, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 64.810851163762877, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -27.057361881482926, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), -1.7553656795609531, precision))
        TEST_ASSERT(klab::Equals(F(0, 7), 36.504365609233922, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 46.651921121230004, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 66.965263098228419, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -76.508348485642003, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), 17.968248902119697, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), -29.80671441948121, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 39.156203546834647, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), 10.378161490982357, precision))
        TEST_ASSERT(klab::Equals(F(1, 7), -25.02686096142245, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), -7.6309037451162931, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), 2.1040451850306061, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), -3.6216656580865001, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), 22.875033707685571, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), -31.631518353031826, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 57.537121295532046, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), -14.422744579178016, precision))
        TEST_ASSERT(klab::Equals(F(2, 7), 10.936873091633231, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -17.228272023045292, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), -0.30098775562375346, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 48.389215067998911, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -28.835751071089984, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 15.217701586561832, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), 17.38132728307729, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -34.690165785333505, precision))
        TEST_ASSERT(klab::Equals(F(3, 7), 5.0618178194329975, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -11.913989943709286, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 6.2607117744273735, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 19.746912434484699, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 24.194882379652498, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -25.764389633964797, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), -4.4896898324325161, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), 19.991908046452494, precision))
        TEST_ASSERT(klab::Equals(F(4, 7), 6.912741776031778, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 16.923649098184715, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), -16.045148987891199, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 30.285550906567167, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -17.930081799783469, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -16.089012832919387, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), -3.6960582134041493, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 21.310280271301085, precision))
        TEST_ASSERT(klab::Equals(F(5, 7), -0.56953214492331705, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 18.205799945455972, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -10.383268161697927, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), -9.5252990236867472, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 11.457817089424653, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), -7.172645599751351, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 12.79309521313321, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), 4.8790810022868154, precision))
        TEST_ASSERT(klab::Equals(F(6, 7), -21.441505901954194, precision))


        // Limit cases.
        dct.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.transform(arma::Mat<klab::DoubleReal>(7, 0), F);
        TEST_ASSERT(F.n_rows==7 && F.n_cols==0)

        dct.transform(arma::Mat<klab::DoubleReal>(0, 8), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testTransform_04()
{
    try
    {
        klab::UInt32 m = 7;
        klab::UInt32 n = 7;
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
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;


        TDCT2D<klab::DoubleReal> dct;

        dct.transform(f, F);
        TEST_ASSERT(F.n_rows==m && F.n_cols==n)
        TEST_ASSERT(klab::Equals(F(0, 0), 865.99999999999977, precision))
        TEST_ASSERT(klab::Equals(F(0, 1), -60.960700676739656, precision))
        TEST_ASSERT(klab::Equals(F(0, 2), 3.8048213227080838, precision))
        TEST_ASSERT(klab::Equals(F(0, 3), 81.733297806488963, precision))
        TEST_ASSERT(klab::Equals(F(0, 4), 9.334679189517205, precision))
        TEST_ASSERT(klab::Equals(F(0, 5), -22.523724060063444, precision))
        TEST_ASSERT(klab::Equals(F(0, 6), 39.470983363763366, precision))
        TEST_ASSERT(klab::Equals(F(1, 0), 78.653428884459615, precision))
        TEST_ASSERT(klab::Equals(F(1, 1), 14.634970981966395, precision))
        TEST_ASSERT(klab::Equals(F(1, 2), -41.754808173989282, precision))
        TEST_ASSERT(klab::Equals(F(1, 3), -4.4915776463935391, precision))
        TEST_ASSERT(klab::Equals(F(1, 4), 3.9710838422260588, precision))
        TEST_ASSERT(klab::Equals(F(1, 5), 34.674736163172724, precision))
        TEST_ASSERT(klab::Equals(F(1, 6), -28.50178427855657, precision))
        TEST_ASSERT(klab::Equals(F(2, 0), 9.192898164424923, precision))
        TEST_ASSERT(klab::Equals(F(2, 1), -22.986397873112875, precision))
        TEST_ASSERT(klab::Equals(F(2, 2), 30.352141843844798, precision))
        TEST_ASSERT(klab::Equals(F(2, 3), -23.341737015219181, precision))
        TEST_ASSERT(klab::Equals(F(2, 4), 30.019363210984274, precision))
        TEST_ASSERT(klab::Equals(F(2, 5), 12.242914540972224, precision))
        TEST_ASSERT(klab::Equals(F(2, 6), 0.63176425172207284, precision))
        TEST_ASSERT(klab::Equals(F(3, 0), -26.664219028332685, precision))
        TEST_ASSERT(klab::Equals(F(3, 1), 21.24276870439942, precision))
        TEST_ASSERT(klab::Equals(F(3, 2), 26.361561982710057, precision))
        TEST_ASSERT(klab::Equals(F(3, 3), -24.908064505813172, precision))
        TEST_ASSERT(klab::Equals(F(3, 4), 36.619401827426586, precision))
        TEST_ASSERT(klab::Equals(F(3, 5), -30.582028731069446, precision))
        TEST_ASSERT(klab::Equals(F(3, 6), -1.6716560051623757, precision))
        TEST_ASSERT(klab::Equals(F(4, 0), -7.8494551936364934, precision))
        TEST_ASSERT(klab::Equals(F(4, 1), 3.4314736101155385, precision))
        TEST_ASSERT(klab::Equals(F(4, 2), 31.681998900919403, precision))
        TEST_ASSERT(klab::Equals(F(4, 3), 0.58313039974880976, precision))
        TEST_ASSERT(klab::Equals(F(4, 4), -23.635002770130853, precision))
        TEST_ASSERT(klab::Equals(F(4, 5), 19.838652526605419, precision))
        TEST_ASSERT(klab::Equals(F(4, 6), 9.5416879449325265, precision))
        TEST_ASSERT(klab::Equals(F(5, 0), 4.9512312795402451, precision))
        TEST_ASSERT(klab::Equals(F(5, 1), 1.5904510846759026, precision))
        TEST_ASSERT(klab::Equals(F(5, 2), 16.519140064009932, precision))
        TEST_ASSERT(klab::Equals(F(5, 3), -22.4319674587733, precision))
        TEST_ASSERT(klab::Equals(F(5, 4), -12.13431335320475, precision))
        TEST_ASSERT(klab::Equals(F(5, 5), 18.273093523846789, precision))
        TEST_ASSERT(klab::Equals(F(5, 6), 4.0592011995364787, precision))
        TEST_ASSERT(klab::Equals(F(6, 0), 19.727199263639012, precision))
        TEST_ASSERT(klab::Equals(F(6, 1), -17.033148427007941, precision))
        TEST_ASSERT(klab::Equals(F(6, 2), 1.5610511559168221, precision))
        TEST_ASSERT(klab::Equals(F(6, 3), 2.5807986369936082, precision))
        TEST_ASSERT(klab::Equals(F(6, 4), 1.449765350802688, precision))
        TEST_ASSERT(klab::Equals(F(6, 5), 14.046952459661833, precision))
        TEST_ASSERT(klab::Equals(F(6, 6), -21.717139073713938, precision))


        // Limit cases.
        dct.transform(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.transform(arma::Mat<klab::DoubleReal>(7, 0), F);
        TEST_ASSERT(F.n_rows==7 && F.n_cols==0)

        dct.transform(arma::Mat<klab::DoubleReal>(0, 7), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testTransform_Complex()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > f(m, n);
        arma::Mat<std::complex<klab::DoubleReal> > F;

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


        TDCT2D<std::complex<klab::DoubleReal> > dct;

        dct.transform(f, F);
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
        dct.transform(arma::Mat<std::complex<klab::DoubleReal> >(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.transform(arma::Mat<std::complex<klab::DoubleReal> >(8, 0), F);
        TEST_ASSERT(F.n_rows==8 && F.n_cols==0)

        dct.transform(arma::Mat<std::complex<klab::DoubleReal> >(0, 8), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testInvert()
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


        TDCT2D<klab::DoubleReal> dct;

        dct.transform(f, F);
        dct.invert(F, fr);
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
        dct.invert(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.invert(arma::Mat<klab::DoubleReal>(8, 0), F);
        TEST_ASSERT(F.n_rows==8 && F.n_cols==0)

        dct.invert(arma::Mat<klab::DoubleReal>(0, 8), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testInvert_02()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 7;
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
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;
        f(7, 0) = 126.0;
        f(7, 1) = 71.0;
        f(7, 2) = 70.0;
        f(7, 3) = 108.0;
        f(7, 4) = 149.0;
        f(7, 5) = 175.0;
        f(7, 6) = 125.0;


        TDCT2D<klab::DoubleReal> dct;

        dct.transform(f, F);
        dct.invert(F, fr);
        TEST_ASSERT(fr.n_rows==m && fr.n_cols==n)
        TEST_ASSERT(klab::Equals(fr(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fr(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fr(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fr(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fr(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fr(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fr(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fr(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fr(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fr(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fr(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fr(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fr(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fr(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fr(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fr(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fr(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fr(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fr(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fr(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fr(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fr(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fr(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fr(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fr(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fr(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fr(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fr(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fr(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fr(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fr(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fr(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fr(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fr(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fr(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fr(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fr(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fr(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fr(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fr(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fr(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fr(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fr(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fr(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fr(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fr(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fr(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fr(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fr(6, 6), f(6, 6), precision))
        TEST_ASSERT(klab::Equals(fr(7, 0), f(7, 0), precision))
        TEST_ASSERT(klab::Equals(fr(7, 1), f(7, 1), precision))
        TEST_ASSERT(klab::Equals(fr(7, 2), f(7, 2), precision))
        TEST_ASSERT(klab::Equals(fr(7, 3), f(7, 3), precision))
        TEST_ASSERT(klab::Equals(fr(7, 4), f(7, 4), precision))
        TEST_ASSERT(klab::Equals(fr(7, 5), f(7, 5), precision))
        TEST_ASSERT(klab::Equals(fr(7, 6), f(7, 6), precision))            


        // Limit cases.
        dct.invert(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.invert(arma::Mat<klab::DoubleReal>(8, 0), F);
        TEST_ASSERT(F.n_rows==8 && F.n_cols==0)

        dct.invert(arma::Mat<klab::DoubleReal>(0, 7), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testInvert_03()
{
    try
    {
        klab::UInt32 m = 7;
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


        TDCT2D<klab::DoubleReal> dct;

        dct.transform(f, F);
        dct.invert(F, fr);
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


        // Limit cases.
        dct.invert(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.invert(arma::Mat<klab::DoubleReal>(7, 0), F);
        TEST_ASSERT(F.n_rows==7 && F.n_cols==0)

        dct.invert(arma::Mat<klab::DoubleReal>(0, 8), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testInvert_04()
{
    try
    {
        klab::UInt32 m = 7;
        klab::UInt32 n = 7;
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
        f(1, 0) = 127.0;
        f(1, 1) = 108.0;
        f(1, 2) = 120.0;
        f(1, 3) = 167.0;
        f(1, 4) = 182.0;
        f(1, 5) = 136.0;
        f(1, 6) = 118.0;
        f(2, 0) = 124.0;
        f(2, 1) = 114.0;
        f(2, 2) = 132.0;
        f(2, 3) = 141.0;
        f(2, 4) = 171.0;
        f(2, 5) = 184.0;
        f(2, 6) = 110.0;
        f(3, 0) = 127.0;
        f(3, 1) = 115.0;
        f(3, 2) = 107.0;
        f(3, 3) = 85.0;
        f(3, 4) = 161.0;
        f(3, 5) = 122.0;
        f(3, 6) = 97.0;
        f(4, 0) = 121.0;
        f(4, 1) = 107.0;
        f(4, 2) = 73.0;
        f(4, 3) = 118.0;
        f(4, 4) = 153.0;
        f(4, 5) = 97.0;
        f(4, 6) = 126.0;
        f(5, 0) = 115.0;
        f(5, 1) = 98.0;
        f(5, 2) = 90.0;
        f(5, 3) = 91.0;
        f(5, 4) = 140.0;
        f(5, 5) = 87.0;
        f(5, 6) = 144.0;
        f(6, 0) = 120.0;
        f(6, 1) = 81.0;
        f(6, 2) = 84.0;
        f(6, 3) = 77.0;
        f(6, 4) = 151.0;
        f(6, 5) = 138.0;
        f(6, 6) = 144.0;


        TDCT2D<klab::DoubleReal> dct;

        dct.transform(f, F);
        dct.invert(F, fr);
        TEST_ASSERT(fr.n_rows==m && fr.n_cols==n)
        TEST_ASSERT(klab::Equals(fr(0, 0), f(0, 0), precision))
        TEST_ASSERT(klab::Equals(fr(0, 1), f(0, 1), precision))
        TEST_ASSERT(klab::Equals(fr(0, 2), f(0, 2), precision))
        TEST_ASSERT(klab::Equals(fr(0, 3), f(0, 3), precision))
        TEST_ASSERT(klab::Equals(fr(0, 4), f(0, 4), precision))
        TEST_ASSERT(klab::Equals(fr(0, 5), f(0, 5), precision))
        TEST_ASSERT(klab::Equals(fr(0, 6), f(0, 6), precision))
        TEST_ASSERT(klab::Equals(fr(1, 0), f(1, 0), precision))
        TEST_ASSERT(klab::Equals(fr(1, 1), f(1, 1), precision))
        TEST_ASSERT(klab::Equals(fr(1, 2), f(1, 2), precision))
        TEST_ASSERT(klab::Equals(fr(1, 3), f(1, 3), precision))
        TEST_ASSERT(klab::Equals(fr(1, 4), f(1, 4), precision))
        TEST_ASSERT(klab::Equals(fr(1, 5), f(1, 5), precision))
        TEST_ASSERT(klab::Equals(fr(1, 6), f(1, 6), precision))
        TEST_ASSERT(klab::Equals(fr(2, 0), f(2, 0), precision))
        TEST_ASSERT(klab::Equals(fr(2, 1), f(2, 1), precision))
        TEST_ASSERT(klab::Equals(fr(2, 2), f(2, 2), precision))
        TEST_ASSERT(klab::Equals(fr(2, 3), f(2, 3), precision))
        TEST_ASSERT(klab::Equals(fr(2, 4), f(2, 4), precision))
        TEST_ASSERT(klab::Equals(fr(2, 5), f(2, 5), precision))
        TEST_ASSERT(klab::Equals(fr(2, 6), f(2, 6), precision))
        TEST_ASSERT(klab::Equals(fr(3, 0), f(3, 0), precision))
        TEST_ASSERT(klab::Equals(fr(3, 1), f(3, 1), precision))
        TEST_ASSERT(klab::Equals(fr(3, 2), f(3, 2), precision))
        TEST_ASSERT(klab::Equals(fr(3, 3), f(3, 3), precision))
        TEST_ASSERT(klab::Equals(fr(3, 4), f(3, 4), precision))
        TEST_ASSERT(klab::Equals(fr(3, 5), f(3, 5), precision))
        TEST_ASSERT(klab::Equals(fr(3, 6), f(3, 6), precision))
        TEST_ASSERT(klab::Equals(fr(4, 0), f(4, 0), precision))
        TEST_ASSERT(klab::Equals(fr(4, 1), f(4, 1), precision))
        TEST_ASSERT(klab::Equals(fr(4, 2), f(4, 2), precision))
        TEST_ASSERT(klab::Equals(fr(4, 3), f(4, 3), precision))
        TEST_ASSERT(klab::Equals(fr(4, 4), f(4, 4), precision))
        TEST_ASSERT(klab::Equals(fr(4, 5), f(4, 5), precision))
        TEST_ASSERT(klab::Equals(fr(4, 6), f(4, 6), precision))
        TEST_ASSERT(klab::Equals(fr(5, 0), f(5, 0), precision))
        TEST_ASSERT(klab::Equals(fr(5, 1), f(5, 1), precision))
        TEST_ASSERT(klab::Equals(fr(5, 2), f(5, 2), precision))
        TEST_ASSERT(klab::Equals(fr(5, 3), f(5, 3), precision))
        TEST_ASSERT(klab::Equals(fr(5, 4), f(5, 4), precision))
        TEST_ASSERT(klab::Equals(fr(5, 5), f(5, 5), precision))
        TEST_ASSERT(klab::Equals(fr(5, 6), f(5, 6), precision))
        TEST_ASSERT(klab::Equals(fr(6, 0), f(6, 0), precision))
        TEST_ASSERT(klab::Equals(fr(6, 1), f(6, 1), precision))
        TEST_ASSERT(klab::Equals(fr(6, 2), f(6, 2), precision))
        TEST_ASSERT(klab::Equals(fr(6, 3), f(6, 3), precision))
        TEST_ASSERT(klab::Equals(fr(6, 4), f(6, 4), precision))
        TEST_ASSERT(klab::Equals(fr(6, 5), f(6, 5), precision))
        TEST_ASSERT(klab::Equals(fr(6, 6), f(6, 6), precision))           


        // Limit cases.
        dct.invert(arma::Mat<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.invert(arma::Mat<klab::DoubleReal>(7, 0), F);
        TEST_ASSERT(F.n_rows==7 && F.n_cols==0)

        dct.invert(arma::Mat<klab::DoubleReal>(0, 7), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==7)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KDCT2DUnitTest::testInvert_Complex()
{
    try
    {
        klab::UInt32 m = 8;
        klab::UInt32 n = 8;
        klab::DoubleReal precision = 1e-12;

        arma::Mat<std::complex<klab::DoubleReal> > f(m, n);
        arma::Mat<std::complex<klab::DoubleReal> > F;
        arma::Mat<std::complex<klab::DoubleReal> > fr;

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


        TDCT2D<std::complex<klab::DoubleReal> > dct;

        dct.transform(f, F);
        dct.invert(F, fr);
        TEST_ASSERT(F.n_rows==m && F.n_cols==n)
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
        dct.invert(arma::Mat<std::complex<klab::DoubleReal> >(), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==0)

        dct.invert(arma::Mat<std::complex<klab::DoubleReal> >(8, 0), F);
        TEST_ASSERT(F.n_rows==8 && F.n_cols==0)

        dct.invert(arma::Mat<std::complex<klab::DoubleReal> >(0, 8), F);
        TEST_ASSERT(F.n_rows==0 && F.n_cols==8)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
