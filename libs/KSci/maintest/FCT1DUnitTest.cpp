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

#include "FCT1DUnitTest.h"
#include "../include/FCT1D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KFCT1DUnitTest::KFCT1DUnitTest() : Test::Suite()
{
    TEST_ADD(KFCT1DUnitTest::testDefaultConstructor)  
    TEST_ADD(KFCT1DUnitTest::testCopyConstructor)
    TEST_ADD(KFCT1DUnitTest::testAffectationOperator)

    TEST_ADD(KFCT1DUnitTest::testTransform)
    TEST_ADD(KFCT1DUnitTest::testTransform_02)
    TEST_ADD(KFCT1DUnitTest::testTransform_Complex)
    TEST_ADD(KFCT1DUnitTest::testInvert)   
    TEST_ADD(KFCT1DUnitTest::testInvert_02) 
    TEST_ADD(KFCT1DUnitTest::testInvert_Complex)  

    TEST_ADD(KFCT1DUnitTest::testFCTMatrix)
}

// ---------------------------------------------------------------------------------------------------- //

KFCT1DUnitTest::~KFCT1DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testDefaultConstructor()
{
    try
    {
        TFCT1D<klab::DoubleReal> fct;
        TEST_ASSERT(true)

        TFCT1D<std::complex<klab::DoubleReal> > cfct;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testCopyConstructor()
{
    try
    {
        TFCT1D<klab::DoubleReal> fct;
        TFCT1D<klab::DoubleReal> fctCopy(fct);
        TEST_ASSERT(true)

        TFCT1D<std::complex<klab::DoubleReal> > cfct;
        TFCT1D<std::complex<klab::DoubleReal> > cfctCopy(cfct);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testAffectationOperator()
{
    try
    {
        TFCT1D<klab::DoubleReal> fct;
        TFCT1D<klab::DoubleReal> fctCopy; 
        fctCopy = fct;
        TEST_ASSERT(true)

        TFCT1D<std::complex<klab::DoubleReal> > cfct;
        TFCT1D<std::complex<klab::DoubleReal> > cfctCopy;
        cfctCopy = cfct;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testTransform()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TFCT1D<klab::DoubleReal> fct;

        fct.transform(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374716, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.10407138805727052, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.15256418280747208, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.1125301320037508, precision))
        TEST_ASSERT(klab::Equals(F[4], 0.1726629418994039, precision))
        TEST_ASSERT(klab::Equals(F[5], 0.13458532428598555, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.22193217208845287, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.19177103138171281, precision))
        TEST_ASSERT(klab::Equals(F[8], 0.37401210562570764, precision))
        TEST_ASSERT(klab::Equals(F[9], 0.45537506401751277, precision))
        TEST_ASSERT(klab::Equals(F[10], 3.9005670416292335, precision))
        TEST_ASSERT(klab::Equals(F[11], -0.58999660894262074, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.3562182568938006, precision))
        TEST_ASSERT(klab::Equals(F[13], -0.15226885538167151, precision))
        TEST_ASSERT(klab::Equals(F[14], -0.15120895605095352, precision))
        TEST_ASSERT(klab::Equals(F[15], -0.079403771599353384, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.088374341935867712, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.049865480924718757, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.05825286861084699, precision))
        TEST_ASSERT(klab::Equals(F[19], -0.033993502572885304, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.040646390933580467, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.024085325817692321, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.029047217682979909, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.017251254764136165, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.020716136735205226, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.012158323930072025, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.014289604729654605, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.0080976111897570688, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.0089974350800402919, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.0046449610557383579, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.0043513680384154579, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.0015146185228080275, precision))


        // Limit cases.
        fct.transform(arma::Col<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testTransform_02()
{
    try
    {
        klab::UInt32 n = 31;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TFCT1D<klab::DoubleReal> fct;

        fct.transform(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], -0.058760416572786314, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.3404673153517393, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.086526387367694982, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.3701387983840051, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.098820177303547113, precision))
        TEST_ASSERT(klab::Equals(F[5], 0.44909373405857939, precision))
        TEST_ASSERT(klab::Equals(F[6], -0.12996046777694117, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.6652050938983588, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.23613488832853985, precision))
        TEST_ASSERT(klab::Equals(F[9], 1.93760940316606, precision))
        TEST_ASSERT(klab::Equals(F[10], 2.9458325032832309, precision))
        TEST_ASSERT(klab::Equals(F[11], -1.3163029663703283, precision))
        TEST_ASSERT(klab::Equals(F[12], 0.16245740628619593, precision))
        TEST_ASSERT(klab::Equals(F[13], -0.42306905584760501, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.074535993580875315, precision))
        TEST_ASSERT(klab::Equals(F[15], -0.22938047129031591, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.044536772164329122, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.14592303820833799, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.029562906269205928, precision))
        TEST_ASSERT(klab::Equals(F[19], -0.099735596191236703, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.020604577189495345, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.070332698520364445, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.014598470576161326, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.049713278308100198, precision))
        TEST_ASSERT(klab::Equals(F[24], 0.010213020116642319, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.034083981061916922, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.0067685495515945344, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.021376617586916943, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.0038707827779346725, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.01031525600677737, precision))
        TEST_ASSERT(klab::Equals(F[30], 0.001260339583092866, precision))


        // Limit cases.
        fct.transform(arma::Col<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testTransform_Complex()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > f(n);
        arma::Col<std::complex<klab::DoubleReal> > F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = std::complex<klab::DoubleReal>(klab::Cos(klab::DoubleReal(i)), klab::DoubleReal(i+1)); 

        TFCT1D<std::complex<klab::DoubleReal> > fct;

        fct.transform(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], std::complex<klab::DoubleReal>(0.10387013321374716, 93.33809511662426), precision))
        TEST_ASSERT(klab::Equals(F[1], std::complex<klab::DoubleReal>(0.10407138805727323, -51.855595114309729), precision))
        TEST_ASSERT(klab::Equals(F[2], std::complex<klab::DoubleReal>(0.15256418280747178, 2.0816681711721685e-017), precision))
        TEST_ASSERT(klab::Equals(F[3], std::complex<klab::DoubleReal>(0.11253013200375184, -5.7430574923495783), precision))
        TEST_ASSERT(klab::Equals(F[4], std::complex<klab::DoubleReal>(0.17266294189940393, 1.3877787807814457e-017), precision))
        TEST_ASSERT(klab::Equals(F[5], std::complex<klab::DoubleReal>(0.13458532428598657, -2.0537805724316085), precision))
        TEST_ASSERT(klab::Equals(F[6], std::complex<klab::DoubleReal>(0.22193217208845298, 1.3877787807814457e-017), precision))
        TEST_ASSERT(klab::Equals(F[7], std::complex<klab::DoubleReal>(0.19177103138171353, -1.0369905565383166), precision))
        TEST_ASSERT(klab::Equals(F[8], std::complex<klab::DoubleReal>(0.37401210562570769, 0), precision))
        TEST_ASSERT(klab::Equals(F[9], std::complex<klab::DoubleReal>(0.45537506401751265, -0.61814324926683506), precision))
        TEST_ASSERT(klab::Equals(F[10], std::complex<klab::DoubleReal>(3.9005670416292331, 2.2204460492503131e-016), precision))
        TEST_ASSERT(klab::Equals(F[11], std::complex<klab::DoubleReal>(-0.58999660894261985, -0.40565801885616171), precision))
        TEST_ASSERT(klab::Equals(F[12], std::complex<klab::DoubleReal>(-0.3562182568938006, 0), precision))
        TEST_ASSERT(klab::Equals(F[13], std::complex<klab::DoubleReal>(-0.15226885538167148, -0.28293299642081593), precision))
        TEST_ASSERT(klab::Equals(F[14], std::complex<klab::DoubleReal>(-0.15120895605095352, -1.3877787807814457e-017), precision))
        TEST_ASSERT(klab::Equals(F[15], std::complex<klab::DoubleReal>(-0.079403771599350734, -0.20536729645441545), precision))
        TEST_ASSERT(klab::Equals(F[16], std::complex<klab::DoubleReal>(-0.088374341935867712, -6.9388939039072284e-018), precision))
        TEST_ASSERT(klab::Equals(F[17], std::complex<klab::DoubleReal>(-0.049865480924721192, -0.15290265747706322), precision))
        TEST_ASSERT(klab::Equals(F[18], std::complex<klab::DoubleReal>(-0.058252868610846636, -6.9388939039072284e-017), precision))
        TEST_ASSERT(klab::Equals(F[19], std::complex<klab::DoubleReal>(-0.033993502572885012, -0.11542013072649865), precision))
        TEST_ASSERT(klab::Equals(F[20], std::complex<klab::DoubleReal>(-0.040646390933580426, -3.4694469519536142e-018), precision))
        TEST_ASSERT(klab::Equals(F[21], std::complex<klab::DoubleReal>(-0.024085325817692148, -0.087349443444840497), precision))
        TEST_ASSERT(klab::Equals(F[22], std::complex<klab::DoubleReal>(-0.029047217682980821, -1.7347234759768071e-017), precision))
        TEST_ASSERT(klab::Equals(F[23], std::complex<klab::DoubleReal>(-0.017251254764134839, -0.065399665058135992), precision))
        TEST_ASSERT(klab::Equals(F[24], std::complex<klab::DoubleReal>(-0.020716136735205247, 2.2551405187698492e-017), precision))
        TEST_ASSERT(klab::Equals(F[25], std::complex<klab::DoubleReal>(-0.012158323930069949, -0.047502519338403958), precision))
        TEST_ASSERT(klab::Equals(F[26], std::complex<klab::DoubleReal>(-0.014289604729654827, -9.540979117872439e-017), precision))
        TEST_ASSERT(klab::Equals(F[27], std::complex<klab::DoubleReal>(-0.008097611189756642, -0.032278207450325551), precision))
        TEST_ASSERT(klab::Equals(F[28], std::complex<klab::DoubleReal>(-0.0089974350800403058, -4.3368086899420177e-019), precision))
        TEST_ASSERT(klab::Equals(F[29], std::complex<klab::DoubleReal>(-0.0046449610557381532, -0.01874488350208954), precision))
        TEST_ASSERT(klab::Equals(F[30], std::complex<klab::DoubleReal>(-0.0043513680384154553, -5.5727991665754928e-017), precision))
        TEST_ASSERT(klab::Equals(F[31], std::complex<klab::DoubleReal>(-0.0015146185228062212, -0.006148262072112008), precision))


        // Limit cases.
        fct.transform(arma::Col<std::complex<klab::DoubleReal> >(), F);
        TEST_ASSERT(F.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testInvert()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TFCT1D<klab::DoubleReal> fct;

        fct.transform(f, F);
        fct.invert(F, fr);
        TEST_ASSERT(fr.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))                


        // Limit cases.
        fct.invert(arma::Col<klab::DoubleReal>(), fr);
        TEST_ASSERT(fr.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testInvert_02()
{
    try
    {
        klab::UInt32 n = 31;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TFCT1D<klab::DoubleReal> fct;

        fct.transform(f, F);
        fct.invert(F, fr);
        TEST_ASSERT(fr.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))             


        // Limit cases.
        fct.invert(arma::Col<klab::DoubleReal>(), fr);
        TEST_ASSERT(fr.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testInvert_Complex()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<std::complex<klab::DoubleReal> > f(n);
        arma::Col<std::complex<klab::DoubleReal> > F;
        arma::Col<std::complex<klab::DoubleReal> > fr;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = std::complex<klab::DoubleReal>(klab::Cos(klab::DoubleReal(i)), klab::DoubleReal(i+1)); 

        TFCT1D<std::complex<klab::DoubleReal> > fct;

        fct.transform(f, F);
        fct.invert(F, fr);
        TEST_ASSERT(fr.n_rows == n)
        TEST_ASSERT(klab::Equals(fr[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fr[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fr[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fr[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fr[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fr[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fr[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fr[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fr[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fr[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fr[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fr[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fr[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fr[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fr[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fr[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fr[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fr[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fr[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fr[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fr[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fr[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fr[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fr[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fr[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fr[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fr[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fr[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fr[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fr[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fr[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fr[31], f[31], precision))                


        // Limit cases.
        fct.invert(arma::Col<std::complex<klab::DoubleReal> >(), fr);
        TEST_ASSERT(fr.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFCT1DUnitTest::testFCTMatrix()
{
    try
    {
        klab::UInt32 n = 2;
        klab::DoubleReal precision = 1e-12;


        arma::Mat<klab::DoubleReal> fctMatrix(n, n);
        arma::Mat<std::complex<klab::DoubleReal> > cfctMatrix(n, n);

        TFCT1D<klab::DoubleReal> fct;
        TFCT1D<std::complex<klab::DoubleReal> > cfct;


        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<klab::DoubleReal> base(n);
            arma::Col<klab::DoubleReal> col;
            base.fill(klab::TTypeInfo<klab::DoubleReal>::ZERO);
            base[j] = klab::TTypeInfo<klab::DoubleReal>::UNIT;

            fct.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                fctMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(fctMatrix.n_cols==2 && fctMatrix.n_rows==2)
        TEST_ASSERT(klab::Equals(fctMatrix(0, 0), 0.70710678118654746, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 1), 0.70710678118654746, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 0), 0.70710678118654757, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 1), -0.70710678118654757, precision))

       
        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(n);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(klab::TTypeInfo<std::complex<klab::DoubleReal> >::ZERO);
            base[j] = klab::TTypeInfo<std::complex<klab::DoubleReal> >::UNIT;

            cfct.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                cfctMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(cfctMatrix.n_cols==2 && cfctMatrix.n_rows==2)
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 0), std::complex<klab::DoubleReal>(0.70710678118654746, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 1), std::complex<klab::DoubleReal>(0.70710678118654746, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 0), std::complex<klab::DoubleReal>(0.70710678118654757, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 1), std::complex<klab::DoubleReal>(-0.70710678118654757, 0.0), precision))


        n = 4;
        fctMatrix.set_size(n, n);
        cfctMatrix.set_size(n, n);


        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<klab::DoubleReal> base(n);
            arma::Col<klab::DoubleReal> col;
            base.fill(klab::TTypeInfo<klab::DoubleReal>::ZERO);
            base[j] = klab::TTypeInfo<klab::DoubleReal>::UNIT;

            fct.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                fctMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(fctMatrix.n_cols==4 && fctMatrix.n_rows==4)
        TEST_ASSERT(klab::Equals(fctMatrix(0, 0), 0.49999999999999994, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 1), 0.49999999999999994, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 2), 0.49999999999999994, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 3), 0.49999999999999994, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 0), 0.65328148243818818, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 1), 0.27059805007309851, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 2), -0.27059805007309851, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 3), -0.65328148243818818, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 0), 0.5, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 1), -0.5, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 2), -0.5, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 3), 0.5, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 0), 0.27059805007309851, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 1), -0.65328148243818818, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 2), 0.65328148243818818, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 3), -0.27059805007309851, precision))

       
        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(n);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(klab::TTypeInfo<std::complex<klab::DoubleReal> >::ZERO);
            base[j] = klab::TTypeInfo<std::complex<klab::DoubleReal> >::UNIT;

            cfct.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                cfctMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(cfctMatrix.n_cols==4 && cfctMatrix.n_rows==4)
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 0), std::complex<klab::DoubleReal>(0.49999999999999994, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 1), std::complex<klab::DoubleReal>(0.49999999999999994, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 2), std::complex<klab::DoubleReal>(0.49999999999999994, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 3), std::complex<klab::DoubleReal>(0.49999999999999994, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 0), std::complex<klab::DoubleReal>(0.65328148243818818, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 1), std::complex<klab::DoubleReal>(0.27059805007309851, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 2), std::complex<klab::DoubleReal>(-0.27059805007309851, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 3), std::complex<klab::DoubleReal>(-0.65328148243818818, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 0), std::complex<klab::DoubleReal>(0.5, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 1), std::complex<klab::DoubleReal>(-0.5, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 2), std::complex<klab::DoubleReal>(-0.5, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 3), std::complex<klab::DoubleReal>(0.5, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 0), std::complex<klab::DoubleReal>(0.27059805007309851, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 1), std::complex<klab::DoubleReal>(-0.65328148243818818, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 2), std::complex<klab::DoubleReal>(0.65328148243818818, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 3), std::complex<klab::DoubleReal>(-0.27059805007309851, 0.0), precision))



        n = 8;
        fctMatrix.set_size(n, n);
        cfctMatrix.set_size(n, n);
        

        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<klab::DoubleReal> base(n);
            arma::Col<klab::DoubleReal> col;
            base.fill(klab::TTypeInfo<klab::DoubleReal>::ZERO);
            base[j] = klab::TTypeInfo<klab::DoubleReal>::UNIT;

            fct.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                fctMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(fctMatrix.n_cols==8 && fctMatrix.n_rows==8)
        TEST_ASSERT(klab::Equals(fctMatrix(0, 0), 0.35355339059327373, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 1), 0.35355339059327373, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 2), 0.35355339059327373, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 3), 0.35355339059327373, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 4), 0.35355339059327373, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 5), 0.35355339059327373, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 6), 0.35355339059327373, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(0, 7), 0.35355339059327373, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 0), 0.49039264020161522, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 1), 0.41573480615127262, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 2), 0.27778511650980114, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 3), 0.097545161008064124, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 4), -0.097545161008064124, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 5), -0.27778511650980114, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 6), -0.41573480615127262, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(1, 7), -0.49039264020161522, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 0), 0.46193976625564337, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 1), 0.19134171618254489, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 2), -0.19134171618254489, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 3), -0.46193976625564337, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 4), -0.46193976625564337, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 5), -0.19134171618254489, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 6), 0.19134171618254489, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(2, 7), 0.46193976625564337, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 0), 0.41573480615127262, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 1), -0.09754516100806418, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 2), -0.49039264020161522, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 3), -0.27778511650980109, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 4), 0.27778511650980109, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 5), 0.49039264020161522, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 6), 0.09754516100806418, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(3, 7), -0.41573480615127262, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(4, 0), 0.35355339059327379, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(4, 1), -0.35355339059327379, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(4, 2), -0.35355339059327379, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(4, 3), 0.35355339059327379, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(4, 4), 0.35355339059327379, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(4, 5), -0.35355339059327379, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(4, 6), -0.35355339059327379, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(4, 7), 0.35355339059327379, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(5, 0), 0.27778511650980114, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(5, 1), -0.49039264020161533, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(5, 2), 0.097545161008064124, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(5, 3), 0.41573480615127262, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(5, 4), -0.41573480615127262, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(5, 5), -0.097545161008064124, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(5, 6), 0.49039264020161533, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(5, 7), -0.27778511650980114, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(6, 0), 0.19134171618254492, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(6, 1), -0.46193976625564337, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(6, 2), 0.46193976625564337, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(6, 3), -0.19134171618254492, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(6, 4), -0.19134171618254492, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(6, 5), 0.46193976625564337, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(6, 6), -0.46193976625564337, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(6, 7), 0.19134171618254492, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(7, 0), 0.097545161008064166, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(7, 1), -0.27778511650980109, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(7, 2), 0.41573480615127267, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(7, 3), -0.49039264020161522, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(7, 4), 0.49039264020161522, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(7, 5), -0.41573480615127267, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(7, 6), 0.27778511650980109, precision))
        TEST_ASSERT(klab::Equals(fctMatrix(7, 7), -0.097545161008064166, precision))

       
        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(n);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(klab::TTypeInfo<std::complex<klab::DoubleReal> >::ZERO);
            base[j] = klab::TTypeInfo<std::complex<klab::DoubleReal> >::UNIT;

            cfct.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                cfctMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(cfctMatrix.n_cols==8 && cfctMatrix.n_rows==8)
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 0), std::complex<klab::DoubleReal>(0.35355339059327373, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 1), std::complex<klab::DoubleReal>(0.35355339059327373, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 2), std::complex<klab::DoubleReal>(0.35355339059327373, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 3), std::complex<klab::DoubleReal>(0.35355339059327373, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 4), std::complex<klab::DoubleReal>(0.35355339059327373, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 5), std::complex<klab::DoubleReal>(0.35355339059327373, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 6), std::complex<klab::DoubleReal>(0.35355339059327373, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(0, 7), std::complex<klab::DoubleReal>(0.35355339059327373, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 0), std::complex<klab::DoubleReal>(0.49039264020161522, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 1), std::complex<klab::DoubleReal>(0.41573480615127262, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 2), std::complex<klab::DoubleReal>(0.27778511650980114, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 3), std::complex<klab::DoubleReal>(0.097545161008064124, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 4), std::complex<klab::DoubleReal>(-0.097545161008064124, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 5), std::complex<klab::DoubleReal>(-0.27778511650980114, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 6), std::complex<klab::DoubleReal>(-0.41573480615127262, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(1, 7), std::complex<klab::DoubleReal>(-0.49039264020161522, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 0), std::complex<klab::DoubleReal>(0.46193976625564337, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 1), std::complex<klab::DoubleReal>(0.19134171618254489, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 2), std::complex<klab::DoubleReal>(-0.19134171618254489, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 3), std::complex<klab::DoubleReal>(-0.46193976625564337, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 4), std::complex<klab::DoubleReal>(-0.46193976625564337, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 5), std::complex<klab::DoubleReal>(-0.19134171618254489, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 6), std::complex<klab::DoubleReal>(0.19134171618254489, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(2, 7), std::complex<klab::DoubleReal>(0.46193976625564337, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 0), std::complex<klab::DoubleReal>(0.41573480615127262, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 1), std::complex<klab::DoubleReal>(-0.09754516100806418, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 2), std::complex<klab::DoubleReal>(-0.49039264020161522, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 3), std::complex<klab::DoubleReal>(-0.27778511650980109, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 4), std::complex<klab::DoubleReal>(0.27778511650980109, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 5), std::complex<klab::DoubleReal>(0.49039264020161522, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 6), std::complex<klab::DoubleReal>(0.09754516100806418, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(3, 7), std::complex<klab::DoubleReal>(-0.41573480615127262, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(4, 0), std::complex<klab::DoubleReal>(0.35355339059327379, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(4, 1), std::complex<klab::DoubleReal>(-0.35355339059327379, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(4, 2), std::complex<klab::DoubleReal>(-0.35355339059327379, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(4, 3), std::complex<klab::DoubleReal>(0.35355339059327379, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(4, 4), std::complex<klab::DoubleReal>(0.35355339059327379, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(4, 5), std::complex<klab::DoubleReal>(-0.35355339059327379, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(4, 6), std::complex<klab::DoubleReal>(-0.35355339059327379, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(4, 7), std::complex<klab::DoubleReal>(0.35355339059327379, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(5, 0), std::complex<klab::DoubleReal>(0.27778511650980114, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(5, 1), std::complex<klab::DoubleReal>(-0.49039264020161533, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(5, 2), std::complex<klab::DoubleReal>(0.097545161008064124, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(5, 3), std::complex<klab::DoubleReal>(0.41573480615127262, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(5, 4), std::complex<klab::DoubleReal>(-0.41573480615127262, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(5, 5), std::complex<klab::DoubleReal>(-0.097545161008064124, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(5, 6), std::complex<klab::DoubleReal>(0.49039264020161533, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(5, 7), std::complex<klab::DoubleReal>(-0.27778511650980114, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(6, 0), std::complex<klab::DoubleReal>(0.19134171618254492, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(6, 1), std::complex<klab::DoubleReal>(-0.46193976625564337, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(6, 2), std::complex<klab::DoubleReal>(0.46193976625564337, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(6, 3), std::complex<klab::DoubleReal>(-0.19134171618254492, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(6, 4), std::complex<klab::DoubleReal>(-0.19134171618254492, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(6, 5), std::complex<klab::DoubleReal>(0.46193976625564337, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(6, 6), std::complex<klab::DoubleReal>(-0.46193976625564337, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(6, 7), std::complex<klab::DoubleReal>(0.19134171618254492, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(7, 0), std::complex<klab::DoubleReal>(0.097545161008064166, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(7, 1), std::complex<klab::DoubleReal>(-0.27778511650980109, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(7, 2), std::complex<klab::DoubleReal>(0.41573480615127267, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(7, 3), std::complex<klab::DoubleReal>(-0.49039264020161522, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(7, 4), std::complex<klab::DoubleReal>(0.49039264020161522, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(7, 5), std::complex<klab::DoubleReal>(-0.41573480615127267, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(7, 6), std::complex<klab::DoubleReal>(0.27778511650980109, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfctMatrix(7, 7), std::complex<klab::DoubleReal>(-0.097545161008064166, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
