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

#include "Wavelet1DOperatorUnitTest.h"
#include "../include/Wavelet1DOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KWavelet1DOperatorUnitTest::KWavelet1DOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KWavelet1DOperatorUnitTest::testNConstructor)  
    TEST_ADD(KWavelet1DOperatorUnitTest::testNFilterConstructor)  
    TEST_ADD(KWavelet1DOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KWavelet1DOperatorUnitTest::testFilter)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Haar)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Daubechies2)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Daubechies4)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Daubechies6)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Daubechies8)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Daubechies10)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Daubechies9_7)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Delegate)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Name)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApply_Custom)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Haar)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies2)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies4)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies6)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies8)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies10)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies9_7)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Delegate)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Name)
    TEST_ADD(KWavelet1DOperatorUnitTest::testApplyAdjoint_Custom)
}

// ---------------------------------------------------------------------------------------------------- //

KWavelet1DOperatorUnitTest::~KWavelet1DOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testNConstructor()
{
    try
    {
        TWavelet1DOperator<klab::DoubleReal> op(16);
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(op.filter().waveLength() == 0)

        TWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(16);
        TEST_ASSERT(op2.m()==16 && op2.n()==16)
        TEST_ASSERT(op2.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testNFilterConstructor()
{
    try
    {
        THaarWaveletFilter<klab::DoubleReal> filter;

        TWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(16, filter);
        TEST_ASSERT(op.m()==16 && op.n()==16)
        TEST_ASSERT(op.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testCopyConstructor()
{
    try
    {
        THaarWaveletFilter<klab::DoubleReal> filter;

        TWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(16, filter);
        TWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(op);
        TEST_ASSERT(op2.m()==16 && op2.n()==16)
        TEST_ASSERT(op2.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testFilter()
{
    try
    {
        TWavelet1DOperator<klab::DoubleReal> op(0);
        TEST_ASSERT(op.filter().waveLength() == 0)

        TWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op2(0);
        TEST_ASSERT(op2.filter().waveLength() == 2)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(n);
        op.apply(f, F);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.103870133213747, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.149036505534471, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.560295039890957, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.596183820391991, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.427774193751344, precision))
        TEST_ASSERT(klab::Equals(F[5], -1.067599071545589, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.738445595759199, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.852711353248019, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.473220819507864, precision))
        TEST_ASSERT(klab::Equals(F[9], -1.042026988197028, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.110992232302444, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.187125717416838, precision))
        TEST_ASSERT(klab::Equals(F[12], -1.440922072402865, precision))
        TEST_ASSERT(klab::Equals(F[13], 0.696573324158579, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.530300652802833, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.389828601847341, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.325055356816458, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.405770157578161, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.662775291699232, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.145853524386329, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.541382326153988, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.596442609169359, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.044966916178482, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.633868289003271, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.482597650334040, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.232205317980082, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.675860667347709, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.330309239346697, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.400946377274867, precision))
        TEST_ASSERT(klab::Equals(F[29], 0.664014372402643, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.151708583719525, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.537748278018788, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Haar()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, THaarWaveletFilter<klab::DoubleReal> > op(n);
        op.apply(f, F);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.103870133213747, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.149036505534471, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.560295039890957, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.596183820391991, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.427774193751344, precision))
        TEST_ASSERT(klab::Equals(F[5], -1.067599071545589, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.738445595759199, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.852711353248019, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.473220819507864, precision))
        TEST_ASSERT(klab::Equals(F[9], -1.042026988197028, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.110992232302444, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.187125717416838, precision))
        TEST_ASSERT(klab::Equals(F[12], -1.440922072402865, precision))
        TEST_ASSERT(klab::Equals(F[13], 0.696573324158579, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.530300652802833, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.389828601847341, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.325055356816458, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.405770157578161, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.662775291699232, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.145853524386329, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.541382326153988, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.596442609169359, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.044966916178482, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.633868289003271, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.482597650334040, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.232205317980082, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.675860667347709, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.330309239346697, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.400946377274867, precision))
        TEST_ASSERT(klab::Equals(F[29], 0.664014372402643, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.151708583719525, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.537748278018788, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Daubechies2()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 2> > op(n);
        op.apply(f, F);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374708, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.14903650553447087, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.56029503989095719, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.5961838203919918, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.42777419375134396, precision))
        TEST_ASSERT(klab::Equals(F[5], -1.0675990715455894, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.73844559575919921, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.85271135324801883, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.4732208195078642, precision))
        TEST_ASSERT(klab::Equals(F[9], -1.0420269881970283, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.11099223230244448, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.1871257174168384, precision))
        TEST_ASSERT(klab::Equals(F[12], -1.4409220724028655, precision))
        TEST_ASSERT(klab::Equals(F[13], 0.6965733241585792, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.53030065280283334, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.3898286018473414, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.32505535681645775, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.40577015757816093, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.66277529169923211, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.14585352438632904, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.5413823261539874, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.59644260916935932, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.044966916178482474, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.63386828900327141, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.4825976503340399, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.23220531798008198, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.67586066734770867, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.33030923934669704, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.40094637727486704, precision))
        TEST_ASSERT(klab::Equals(F[29], 0.66401437240264294, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.15170858371952489, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.53774827801878766, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Daubechies4()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 4> > op(n);
        op.apply(f, F);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374719, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.25387118326456026, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.39272814897449926, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.30139940145502003, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.25905308179050446, precision))
        TEST_ASSERT(klab::Equals(F[5], 1.1418678599669105, precision))
        TEST_ASSERT(klab::Equals(F[6], -0.12099277909693751, precision))
        TEST_ASSERT(klab::Equals(F[7], -1.1356678886080154, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.39065769974783565, precision))
        TEST_ASSERT(klab::Equals(F[9], -0.96436328647907865, precision))
        TEST_ASSERT(klab::Equals(F[10], 1.6513575205520705, precision))
        TEST_ASSERT(klab::Equals(F[11], -1.1944353316689453, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.089887450393033363, precision))
        TEST_ASSERT(klab::Equals(F[13], 1.3119440487591467, precision))
        TEST_ASSERT(klab::Equals(F[14], -1.6085474232359804, precision))
        TEST_ASSERT(klab::Equals(F[15], 1.3259555985976506, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.12049892467178008, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.40802775017751391, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.46009783959142037, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.025091229281225591, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.48098111097234247, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.37522630625891518, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.16868263029450906, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.51561979221393728, precision))
        TEST_ASSERT(klab::Equals(F[24], 0.26046446048734084, precision))
        TEST_ASSERT(klab::Equals(F[25], 0.29883686968440726, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.50918449641297414, precision))
        TEST_ASSERT(klab::Equals(F[27], 0.12495416511781066, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.40518593535864178, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.46218785554359809, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.020509907408689798, precision))
        TEST_ASSERT(klab::Equals(F[31], 0.35057483129405109, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Daubechies6()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 6> > op(n);
        op.apply(f, F);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374723, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.34385980033794422, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.065792250547563449, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.23002735252301482, precision))
        TEST_ASSERT(klab::Equals(F[4], 0.7921628943723964, precision))
        TEST_ASSERT(klab::Equals(F[5], -0.95781566494688919, precision))
        TEST_ASSERT(klab::Equals(F[6], -1.0915180160774114, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.57419433454903346, precision))
        TEST_ASSERT(klab::Equals(F[8], -1.5770343302853953, precision))
        TEST_ASSERT(klab::Equals(F[9], 1.6267035020762726, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.54953440405191056, precision))
        TEST_ASSERT(klab::Equals(F[11], -0.90830418676903657, precision))
        TEST_ASSERT(klab::Equals(F[12], 1.7369488790224938, precision))
        TEST_ASSERT(klab::Equals(F[13], -1.3452768356930416, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.68692086084730453, precision))
        TEST_ASSERT(klab::Equals(F[15], 0.48767639919053474, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.028935449369875674, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.3825058766732552, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.28942177170665739, precision))
        TEST_ASSERT(klab::Equals(F[19], -0.14162196722606574, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.40729283900007812, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.19736528577030843, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.2430269603650049, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.39963508727343744, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.089586794319159446, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.32507256516880201, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.36014263360568288, precision))
        TEST_ASSERT(klab::Equals(F[27], 0.025328129807279082, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.38122307579559195, precision))
        TEST_ASSERT(klab::Equals(F[29], 0.29196142421493526, precision))
        TEST_ASSERT(klab::Equals(F[30], 0.087829742789895277, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.30633743367561178, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Daubechies8()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 8> > op(n);
        op.apply(f, F);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374686, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.26882400440720744, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.084934961964035341, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.087344211091023471, precision))
        TEST_ASSERT(klab::Equals(F[4], -1.2203539101053422, precision))
        TEST_ASSERT(klab::Equals(F[5], -0.55354376776672143, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.95462837445493687, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.08460966489515187, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.1889745068813942, precision))
        TEST_ASSERT(klab::Equals(F[9], 0.27532916777629546, precision))
        TEST_ASSERT(klab::Equals(F[10], -1.5489088151907193, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.749635232643022, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.73559478513466325, precision))
        TEST_ASSERT(klab::Equals(F[13], -0.15980735606767271, precision))
        TEST_ASSERT(klab::Equals(F[14], 1.3150271796019217, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.8475640839940199, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.12566470622074616, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.32673817887874201, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.14627741281837955, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.20499241367340398, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.31689130175107993, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.05875421183263177, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.26799054297513919, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.28180104519994209, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.033449315983870756, precision))
        TEST_ASSERT(klab::Equals(F[25], 0.30964069926264937, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.22426267894492233, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.12298829046561546, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.32662505496413641, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.15788714578016011, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.22761343731999345, precision))
        TEST_ASSERT(klab::Equals(F[31], 0.20379078254472577, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Daubechies10()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDaubechiesWaveletFilter<klab::DoubleReal, 10> > op(n);
        op.apply(f, F);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374711, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.12242122224296531, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.13322373309703711, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.042907326021494788, precision))
        TEST_ASSERT(klab::Equals(F[4], 0.086074737577175722, precision))
        TEST_ASSERT(klab::Equals(F[5], 0.79339811460807452, precision))
        TEST_ASSERT(klab::Equals(F[6], -0.53231735686336823, precision))
        TEST_ASSERT(klab::Equals(F[7], -0.87282463485334905, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.0755333582704747, precision))
        TEST_ASSERT(klab::Equals(F[9], -1.8654636787826335, precision))
        TEST_ASSERT(klab::Equals(F[10], 1.3624306053966335, precision))
        TEST_ASSERT(klab::Equals(F[11], 0.059925686056928745, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.97103043806953537, precision))
        TEST_ASSERT(klab::Equals(F[13], 1.8544678933602061, precision))
        TEST_ASSERT(klab::Equals(F[14], -1.7134385163280654, precision))
        TEST_ASSERT(klab::Equals(F[15], 0.46529936438429265, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.17579402091364635, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.25237231080892636, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.034253856636807301, precision))
        TEST_ASSERT(klab::Equals(F[19], -0.22386304265103296, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.22057365067489818, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.040280988743006313, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.25409926275168426, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.17120421998314278, precision))
        TEST_ASSERT(klab::Equals(F[24], 0.11160707365267239, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.26409408125682998, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.10819675927903517, precision))
        TEST_ASSERT(klab::Equals(F[27], 0.1740426030595838, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.2415798633477847, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.066516657149017278, precision))
        TEST_ASSERT(klab::Equals(F[30], 0.23347423848893156, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.099446630015907686, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Daubechies9_7()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-9;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > op(n);
        op.apply(f, F);

        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.02863132946047511, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.25459637407747865, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.063855523728026109, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.35062773910967038, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.80491352391178561, precision))
        TEST_ASSERT(klab::Equals(F[5], 1.0332439804700042, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.50121459557930859, precision))
        TEST_ASSERT(klab::Equals(F[7], -0.790488681523142, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.73817120917059853, precision))
        TEST_ASSERT(klab::Equals(F[9], 1.7031730131296794, precision))
        TEST_ASSERT(klab::Equals(F[10], -1.4883651413479453, precision))
        TEST_ASSERT(klab::Equals(F[11], 0.24254774718602537, precision))
        TEST_ASSERT(klab::Equals(F[12], 1.1712855659419741, precision))
        TEST_ASSERT(klab::Equals(F[13], -1.7754145116345372, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.99642162195389039, precision))
        TEST_ASSERT(klab::Equals(F[15], 1.3452472179531350, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.1311706520183073, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.24034315578879645, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.068865435916222018, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.18302688918084487, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.22119755778756817, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.001074438669655369, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.22030330928068592, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.18443148914570393, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.066802147745359503, precision))
        TEST_ASSERT(klab::Equals(F[25], 0.24003049406327615, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.13297371381320069, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.12935731336869913, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.24063698729844366, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.070923328672265279, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.22549257693727426, precision))
        TEST_ASSERT(klab::Equals(F[31], 0.52890355016158441, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Delegate()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TDelegateWaveletFilter<klab::DoubleReal> > op(n, new THaarWaveletFilter<klab::DoubleReal>());
        TEST_ASSERT(op.filter().waveLength() == 2)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.103870133213747, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.149036505534471, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.560295039890957, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.596183820391991, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.427774193751344, precision))
        TEST_ASSERT(klab::Equals(F[5], -1.067599071545589, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.738445595759199, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.852711353248019, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.473220819507864, precision))
        TEST_ASSERT(klab::Equals(F[9], -1.042026988197028, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.110992232302444, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.187125717416838, precision))
        TEST_ASSERT(klab::Equals(F[12], -1.440922072402865, precision))
        TEST_ASSERT(klab::Equals(F[13], 0.696573324158579, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.530300652802833, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.389828601847341, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.325055356816458, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.405770157578161, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.662775291699232, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.145853524386329, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.541382326153988, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.596442609169359, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.044966916178482, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.633868289003271, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.482597650334040, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.232205317980082, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.675860667347709, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.330309239346697, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.400946377274867, precision))
        TEST_ASSERT(klab::Equals(F[29], 0.664014372402643, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.151708583719525, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.537748278018788, precision))


        op.filter().setFilter(new TDaubechiesWaveletFilter<klab::DoubleReal, 4>());
        TEST_ASSERT(op.filter().waveLength() == 4)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374719, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.25387118326456026, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.39272814897449926, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.30139940145502003, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.25905308179050446, precision))
        TEST_ASSERT(klab::Equals(F[5], 1.1418678599669105, precision))
        TEST_ASSERT(klab::Equals(F[6], -0.12099277909693751, precision))
        TEST_ASSERT(klab::Equals(F[7], -1.1356678886080154, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.39065769974783565, precision))
        TEST_ASSERT(klab::Equals(F[9], -0.96436328647907865, precision))
        TEST_ASSERT(klab::Equals(F[10], 1.6513575205520705, precision))
        TEST_ASSERT(klab::Equals(F[11], -1.1944353316689453, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.089887450393033363, precision))
        TEST_ASSERT(klab::Equals(F[13], 1.3119440487591467, precision))
        TEST_ASSERT(klab::Equals(F[14], -1.6085474232359804, precision))
        TEST_ASSERT(klab::Equals(F[15], 1.3259555985976506, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.12049892467178008, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.40802775017751391, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.46009783959142037, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.025091229281225591, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.48098111097234247, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.37522630625891518, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.16868263029450906, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.51561979221393728, precision))
        TEST_ASSERT(klab::Equals(F[24], 0.26046446048734084, precision))
        TEST_ASSERT(klab::Equals(F[25], 0.29883686968440726, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.50918449641297414, precision))
        TEST_ASSERT(klab::Equals(F[27], 0.12495416511781066, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.40518593535864178, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.46218785554359809, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.020509907408689798, precision))
        TEST_ASSERT(klab::Equals(F[31], 0.35057483129405109, precision))


        klab::TSmartPointer<TDaubechiesWaveletFilter<klab::DoubleReal, 8> > daubechies8 = new TDaubechiesWaveletFilter<klab::DoubleReal, 8>();
        op.filter().setFilter(daubechies8);
        TEST_ASSERT(op.filter().waveLength() == 8)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374686, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.26882400440720744, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.084934961964035341, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.087344211091023471, precision))
        TEST_ASSERT(klab::Equals(F[4], -1.2203539101053422, precision))
        TEST_ASSERT(klab::Equals(F[5], -0.55354376776672143, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.95462837445493687, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.08460966489515187, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.1889745068813942, precision))
        TEST_ASSERT(klab::Equals(F[9], 0.27532916777629546, precision))
        TEST_ASSERT(klab::Equals(F[10], -1.5489088151907193, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.749635232643022, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.73559478513466325, precision))
        TEST_ASSERT(klab::Equals(F[13], -0.15980735606767271, precision))
        TEST_ASSERT(klab::Equals(F[14], 1.3150271796019217, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.8475640839940199, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.12566470622074616, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.32673817887874201, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.14627741281837955, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.20499241367340398, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.31689130175107993, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.05875421183263177, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.26799054297513919, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.28180104519994209, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.033449315983870756, precision))
        TEST_ASSERT(klab::Equals(F[25], 0.30964069926264937, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.22426267894492233, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.12298829046561546, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.32662505496413641, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.15788714578016011, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.22761343731999345, precision))
        TEST_ASSERT(klab::Equals(F[31], 0.20379078254472577, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Name()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TWavelet1DOperator<klab::DoubleReal, TNameWaveletFilter<klab::DoubleReal> > op(n, "Haar");
        TEST_ASSERT(op.filter().waveLength() == 2)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.103870133213747, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.149036505534471, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.560295039890957, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.596183820391991, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.427774193751344, precision))
        TEST_ASSERT(klab::Equals(F[5], -1.067599071545589, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.738445595759199, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.852711353248019, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.473220819507864, precision))
        TEST_ASSERT(klab::Equals(F[9], -1.042026988197028, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.110992232302444, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.187125717416838, precision))
        TEST_ASSERT(klab::Equals(F[12], -1.440922072402865, precision))
        TEST_ASSERT(klab::Equals(F[13], 0.696573324158579, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.530300652802833, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.389828601847341, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.325055356816458, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.405770157578161, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.662775291699232, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.145853524386329, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.541382326153988, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.596442609169359, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.044966916178482, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.633868289003271, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.482597650334040, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.232205317980082, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.675860667347709, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.330309239346697, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.400946377274867, precision))
        TEST_ASSERT(klab::Equals(F[29], 0.664014372402643, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.151708583719525, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.537748278018788, precision))


        op.filter().set("Daubechies2");
        TEST_ASSERT(op.filter().waveLength() == 2)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.103870133213747, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.149036505534471, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.560295039890957, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.596183820391991, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.427774193751344, precision))
        TEST_ASSERT(klab::Equals(F[5], -1.067599071545589, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.738445595759199, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.852711353248019, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.473220819507864, precision))
        TEST_ASSERT(klab::Equals(F[9], -1.042026988197028, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.110992232302444, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.187125717416838, precision))
        TEST_ASSERT(klab::Equals(F[12], -1.440922072402865, precision))
        TEST_ASSERT(klab::Equals(F[13], 0.696573324158579, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.530300652802833, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.389828601847341, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.325055356816458, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.405770157578161, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.662775291699232, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.145853524386329, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.541382326153988, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.596442609169359, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.044966916178482, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.633868289003271, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.482597650334040, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.232205317980082, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.675860667347709, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.330309239346697, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.400946377274867, precision))
        TEST_ASSERT(klab::Equals(F[29], 0.664014372402643, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.151708583719525, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.537748278018788, precision))


        op.filter().set("Daubechies4");
        TEST_ASSERT(op.filter().waveLength() == 4)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374719, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.25387118326456026, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.39272814897449926, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.30139940145502003, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.25905308179050446, precision))
        TEST_ASSERT(klab::Equals(F[5], 1.1418678599669105, precision))
        TEST_ASSERT(klab::Equals(F[6], -0.12099277909693751, precision))
        TEST_ASSERT(klab::Equals(F[7], -1.1356678886080154, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.39065769974783565, precision))
        TEST_ASSERT(klab::Equals(F[9], -0.96436328647907865, precision))
        TEST_ASSERT(klab::Equals(F[10], 1.6513575205520705, precision))
        TEST_ASSERT(klab::Equals(F[11], -1.1944353316689453, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.089887450393033363, precision))
        TEST_ASSERT(klab::Equals(F[13], 1.3119440487591467, precision))
        TEST_ASSERT(klab::Equals(F[14], -1.6085474232359804, precision))
        TEST_ASSERT(klab::Equals(F[15], 1.3259555985976506, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.12049892467178008, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.40802775017751391, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.46009783959142037, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.025091229281225591, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.48098111097234247, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.37522630625891518, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.16868263029450906, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.51561979221393728, precision))
        TEST_ASSERT(klab::Equals(F[24], 0.26046446048734084, precision))
        TEST_ASSERT(klab::Equals(F[25], 0.29883686968440726, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.50918449641297414, precision))
        TEST_ASSERT(klab::Equals(F[27], 0.12495416511781066, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.40518593535864178, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.46218785554359809, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.020509907408689798, precision))
        TEST_ASSERT(klab::Equals(F[31], 0.35057483129405109, precision))


        op.filter().set("Daubechies6");
        TEST_ASSERT(op.filter().waveLength() == 6)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374723, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.34385980033794422, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.065792250547563449, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.23002735252301482, precision))
        TEST_ASSERT(klab::Equals(F[4], 0.7921628943723964, precision))
        TEST_ASSERT(klab::Equals(F[5], -0.95781566494688919, precision))
        TEST_ASSERT(klab::Equals(F[6], -1.0915180160774114, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.57419433454903346, precision))
        TEST_ASSERT(klab::Equals(F[8], -1.5770343302853953, precision))
        TEST_ASSERT(klab::Equals(F[9], 1.6267035020762726, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.54953440405191056, precision))
        TEST_ASSERT(klab::Equals(F[11], -0.90830418676903657, precision))
        TEST_ASSERT(klab::Equals(F[12], 1.7369488790224938, precision))
        TEST_ASSERT(klab::Equals(F[13], -1.3452768356930416, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.68692086084730453, precision))
        TEST_ASSERT(klab::Equals(F[15], 0.48767639919053474, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.028935449369875674, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.3825058766732552, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.28942177170665739, precision))
        TEST_ASSERT(klab::Equals(F[19], -0.14162196722606574, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.40729283900007812, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.19736528577030843, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.2430269603650049, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.39963508727343744, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.089586794319159446, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.32507256516880201, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.36014263360568288, precision))
        TEST_ASSERT(klab::Equals(F[27], 0.025328129807279082, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.38122307579559195, precision))
        TEST_ASSERT(klab::Equals(F[29], 0.29196142421493526, precision))
        TEST_ASSERT(klab::Equals(F[30], 0.087829742789895277, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.30633743367561178, precision))


        op.filter().set("Daubechies8");
        TEST_ASSERT(op.filter().waveLength() == 8)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374686, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.26882400440720744, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.084934961964035341, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.087344211091023471, precision))
        TEST_ASSERT(klab::Equals(F[4], -1.2203539101053422, precision))
        TEST_ASSERT(klab::Equals(F[5], -0.55354376776672143, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.95462837445493687, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.08460966489515187, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.1889745068813942, precision))
        TEST_ASSERT(klab::Equals(F[9], 0.27532916777629546, precision))
        TEST_ASSERT(klab::Equals(F[10], -1.5489088151907193, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.749635232643022, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.73559478513466325, precision))
        TEST_ASSERT(klab::Equals(F[13], -0.15980735606767271, precision))
        TEST_ASSERT(klab::Equals(F[14], 1.3150271796019217, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.8475640839940199, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.12566470622074616, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.32673817887874201, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.14627741281837955, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.20499241367340398, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.31689130175107993, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.05875421183263177, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.26799054297513919, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.28180104519994209, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.033449315983870756, precision))
        TEST_ASSERT(klab::Equals(F[25], 0.30964069926264937, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.22426267894492233, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.12298829046561546, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.32662505496413641, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.15788714578016011, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.22761343731999345, precision))
        TEST_ASSERT(klab::Equals(F[31], 0.20379078254472577, precision))
        

        op.filter().set("Daubechies10");
        TEST_ASSERT(op.filter().waveLength() == 10)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374711, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.12242122224296531, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.13322373309703711, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.042907326021494788, precision))
        TEST_ASSERT(klab::Equals(F[4], 0.086074737577175722, precision))
        TEST_ASSERT(klab::Equals(F[5], 0.79339811460807452, precision))
        TEST_ASSERT(klab::Equals(F[6], -0.53231735686336823, precision))
        TEST_ASSERT(klab::Equals(F[7], -0.87282463485334905, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.0755333582704747, precision))
        TEST_ASSERT(klab::Equals(F[9], -1.8654636787826335, precision))
        TEST_ASSERT(klab::Equals(F[10], 1.3624306053966335, precision))
        TEST_ASSERT(klab::Equals(F[11], 0.059925686056928745, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.97103043806953537, precision))
        TEST_ASSERT(klab::Equals(F[13], 1.8544678933602061, precision))
        TEST_ASSERT(klab::Equals(F[14], -1.7134385163280654, precision))
        TEST_ASSERT(klab::Equals(F[15], 0.46529936438429265, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.17579402091364635, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.25237231080892636, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.034253856636807301, precision))
        TEST_ASSERT(klab::Equals(F[19], -0.22386304265103296, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.22057365067489818, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.040280988743006313, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.25409926275168426, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.17120421998314278, precision))
        TEST_ASSERT(klab::Equals(F[24], 0.11160707365267239, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.26409408125682998, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.10819675927903517, precision))
        TEST_ASSERT(klab::Equals(F[27], 0.1740426030595838, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.2415798633477847, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.066516657149017278, precision))
        TEST_ASSERT(klab::Equals(F[30], 0.23347423848893156, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.099446630015907686, precision))


        precision = 1e-9;
        op.filter().set("Daubechies9.7");
        TEST_ASSERT(op.filter().waveLength() == 9)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.02863132946047511, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.25459637407747865, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.063855523728026109, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.35062773910967038, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.80491352391178561, precision))
        TEST_ASSERT(klab::Equals(F[5], 1.0332439804700042, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.50121459557930859, precision))
        TEST_ASSERT(klab::Equals(F[7], -0.790488681523142, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.73817120917059853, precision))
        TEST_ASSERT(klab::Equals(F[9], 1.7031730131296794, precision))
        TEST_ASSERT(klab::Equals(F[10], -1.4883651413479453, precision))
        TEST_ASSERT(klab::Equals(F[11], 0.24254774718602537, precision))
        TEST_ASSERT(klab::Equals(F[12], 1.1712855659419741, precision))
        TEST_ASSERT(klab::Equals(F[13], -1.7754145116345372, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.99642162195389039, precision))
        TEST_ASSERT(klab::Equals(F[15], 1.3452472179531350, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.1311706520183073, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.24034315578879645, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.068865435916222018, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.18302688918084487, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.22119755778756817, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.001074438669655369, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.22030330928068592, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.18443148914570393, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.066802147745359503, precision))
        TEST_ASSERT(klab::Equals(F[25], 0.24003049406327615, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.13297371381320069, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.12935731336869913, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.24063698729844366, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.070923328672265279, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.22549257693727426, precision))
        TEST_ASSERT(klab::Equals(F[31], 0.52890355016158441, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApply_Custom()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        std::vector<klab::DoubleReal> haarWaveletCoefficients(2);
        haarWaveletCoefficients[0] =  0.70710678118654752440084436210485;
        haarWaveletCoefficients[1] = -0.70710678118654752440084436210485;

        std::vector<klab::DoubleReal> haarScalingCoefficients(2);
        haarScalingCoefficients[0] = 0.70710678118654752440084436210485;
        haarScalingCoefficients[1] = 0.70710678118654752440084436210485;

        TWavelet1DOperator<klab::DoubleReal, TCustomWaveletFilter<klab::DoubleReal> > op(n, TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));
        TEST_ASSERT(op.filter().waveLength() == 2)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.103870133213747, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.149036505534471, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.560295039890957, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.596183820391991, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.427774193751344, precision))
        TEST_ASSERT(klab::Equals(F[5], -1.067599071545589, precision))
        TEST_ASSERT(klab::Equals(F[6], 0.738445595759199, precision))
        TEST_ASSERT(klab::Equals(F[7], 0.852711353248019, precision))
        TEST_ASSERT(klab::Equals(F[8], 1.473220819507864, precision))
        TEST_ASSERT(klab::Equals(F[9], -1.042026988197028, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.110992232302444, precision))
        TEST_ASSERT(klab::Equals(F[11], 1.187125717416838, precision))
        TEST_ASSERT(klab::Equals(F[12], -1.440922072402865, precision))
        TEST_ASSERT(klab::Equals(F[13], 0.696573324158579, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.530300652802833, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.389828601847341, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.325055356816458, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.405770157578161, precision))
        TEST_ASSERT(klab::Equals(F[18], -0.662775291699232, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.145853524386329, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.541382326153988, precision))
        TEST_ASSERT(klab::Equals(F[21], -0.596442609169359, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.044966916178482, precision))
        TEST_ASSERT(klab::Equals(F[23], 0.633868289003271, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.482597650334040, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.232205317980082, precision))
        TEST_ASSERT(klab::Equals(F[26], 0.675860667347709, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.330309239346697, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.400946377274867, precision))
        TEST_ASSERT(klab::Equals(F[29], 0.664014372402643, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.151708583719525, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.537748278018788, precision))
        

        std::vector<klab::DoubleReal> db4WaveletCoefficients(4);
        db4WaveletCoefficients[0] = -0.129409522551260340;
        db4WaveletCoefficients[1] = -0.224143868042013390;
        db4WaveletCoefficients[2] =  0.836516303737807720;
        db4WaveletCoefficients[3] = -0.482962913144534100;

        std::vector<klab::DoubleReal> db4ScalingCoefficients(4);
        db4ScalingCoefficients[0] =  0.482962913144534100;
        db4ScalingCoefficients[1] =  0.836516303737807720;
        db4ScalingCoefficients[2] =  0.224143868042013390;
        db4ScalingCoefficients[3] = -0.129409522551260340;
 
        op.filter().set(db4ScalingCoefficients, db4WaveletCoefficients);
        TEST_ASSERT(op.filter().waveLength() == 4)

        op.apply(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.10387013321374719, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.25387118326456026, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.39272814897449926, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.30139940145502003, precision))
        TEST_ASSERT(klab::Equals(F[4], -0.25905308179050446, precision))
        TEST_ASSERT(klab::Equals(F[5], 1.1418678599669105, precision))
        TEST_ASSERT(klab::Equals(F[6], -0.12099277909693751, precision))
        TEST_ASSERT(klab::Equals(F[7], -1.1356678886080154, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.39065769974783565, precision))
        TEST_ASSERT(klab::Equals(F[9], -0.96436328647907865, precision))
        TEST_ASSERT(klab::Equals(F[10], 1.6513575205520705, precision))
        TEST_ASSERT(klab::Equals(F[11], -1.1944353316689453, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.089887450393033363, precision))
        TEST_ASSERT(klab::Equals(F[13], 1.3119440487591467, precision))
        TEST_ASSERT(klab::Equals(F[14], -1.6085474232359804, precision))
        TEST_ASSERT(klab::Equals(F[15], 1.3259555985976506, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.12049892467178008, precision))
        TEST_ASSERT(klab::Equals(F[17], -0.40802775017751391, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.46009783959142037, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.025091229281225591, precision))
        TEST_ASSERT(klab::Equals(F[20], -0.48098111097234247, precision))
        TEST_ASSERT(klab::Equals(F[21], 0.37522630625891518, precision))
        TEST_ASSERT(klab::Equals(F[22], 0.16868263029450906, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.51561979221393728, precision))
        TEST_ASSERT(klab::Equals(F[24], 0.26046446048734084, precision))
        TEST_ASSERT(klab::Equals(F[25], 0.29883686968440726, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.50918449641297414, precision))
        TEST_ASSERT(klab::Equals(F[27], 0.12495416511781066, precision))
        TEST_ASSERT(klab::Equals(F[28], 0.40518593535864178, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.46218785554359809, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.020509907408689798, precision))
        TEST_ASSERT(klab::Equals(F[31], 0.35057483129405109, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Haar()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::THaarWaveletFilter<klab::DoubleReal> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies2()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 2> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies4()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies6()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 6> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies8()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies10()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10>  > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 10> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Daubechies9_7()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > fwt;
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::TBiorthogonalDaubechiesWaveletFilter<klab::DoubleReal, 9, 7> > op(8);

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Delegate()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal> > fwt(new klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4>());
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::TDelegateWaveletFilter<klab::DoubleReal> > op(8, new klab::TDaubechiesWaveletFilter<klab::DoubleReal, 4>());

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Name()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 
        

        klab::TFWT1D<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > fwt("Daubechies4");
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::TNameWaveletFilter<klab::DoubleReal> > op(8, "Daubechies4");

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KWavelet1DOperatorUnitTest::testApplyAdjoint_Custom()
{
    try
    {
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<8; ++i)
            x[i] = klab::Cos(klab::DoubleReal(i)); 

        std::vector<klab::DoubleReal> haarWaveletCoefficients(2);
        haarWaveletCoefficients[0] =  0.70710678118654752440084436210485;
        haarWaveletCoefficients[1] = -0.70710678118654752440084436210485;

        std::vector<klab::DoubleReal> haarScalingCoefficients(2);
        haarScalingCoefficients[0] = 0.70710678118654752440084436210485;
        haarScalingCoefficients[1] = 0.70710678118654752440084436210485;
        

        klab::TFWT1D<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > fwt(klab::TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));
        arma::Mat<klab::DoubleReal> fwtMatrix(8, 8);
        for(klab::UInt32 j=0; j<8; ++j)
        {
            arma::Col<klab::DoubleReal> base(8);
            arma::Col<klab::DoubleReal> col;
            base.fill(0.0);
            base[j] = 1.0;

            fwt.transform(base, col);

            for(klab::UInt32 i=0; i<col.n_rows; ++i)
                fwtMatrix(i, j) = col[i];
        }       

        TWavelet1DOperator<klab::DoubleReal, klab::TCustomWaveletFilter<klab::DoubleReal> > op(8, klab::TCustomWaveletFilter<klab::DoubleReal>(haarScalingCoefficients, haarWaveletCoefficients));

        op.apply(x, y);
        arma::Col<klab::DoubleReal> xt = arma::trans(fwtMatrix) * y;

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], xt[0], precision))
        TEST_ASSERT(klab::Equals(xr[1], xt[1], precision))
        TEST_ASSERT(klab::Equals(xr[2], xt[2], precision))
        TEST_ASSERT(klab::Equals(xr[3], xt[3], precision))
        TEST_ASSERT(klab::Equals(xr[4], xt[4], precision))
        TEST_ASSERT(klab::Equals(xr[5], xt[5], precision))
        TEST_ASSERT(klab::Equals(xr[6], xt[6], precision))
        TEST_ASSERT(klab::Equals(xr[7], xt[7], precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
