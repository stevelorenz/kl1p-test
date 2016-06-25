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

#include "NormalRandomMatrixOperatorUnitTest.h"
#include "../include/NormalRandomMatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KNormalRandomMatrixOperatorUnitTest::KNormalRandomMatrixOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testDefaultConstructor)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testMNConstructor)  
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testIsZero)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testSum)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testNormFrobenius)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testSquaredNormFrobenius)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testMean)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testVariance)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testApply)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testApply_Complex)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KNormalRandomMatrixOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KNormalRandomMatrixOperatorUnitTest::~KNormalRandomMatrixOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testDefaultConstructor()
{
    try
    {
        TNormalRandomMatrixOperator<klab::DoubleReal> op(0, 0);
        TEST_ASSERT(op.matrix().n_rows==0 && op.matrix().n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testMNConstructor()
{
    try
    {
        klab::DoubleReal precision = 1e-15;

        klab::KRandom::Instance().setSeed(123456);
        TNormalRandomMatrixOperator<klab::DoubleReal> op(4, 8);

        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
        TEST_ASSERT(klab::Equals(op.matrix()(0, 0),  3.1534772522276588, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 1),  1.9295796720427096, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 2), -1.8931905603602584e-005, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 3), -0.11012013885075753, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 4), -0.27443265025564478, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 5), -0.82951513357617668, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 6), -0.22947284945975430, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 7),  0.12272940408141395, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 0),  0.70551724141211181, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 1), -0.96420447183722147, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 2), -0.26812353740200373, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 3), -0.55201288516764102, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 4),  0.0091337889930380393, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 5), -0.91026976664382997, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 6), -1.0679077378417197, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 7),  0.051147715696420064, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 0), -1.6306064351609864, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 1), -0.94273651286875149, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 2), -0.11734193323575276, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 3),  0.34093950427255204, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 4), -0.24556879849756338, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 5), -0.96727433423242770, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 6), -1.2983723600981372, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 7),  1.2573487849896718, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 0), -0.38652703527035603, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 1),  0.0067927372592515292, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 2),  0.65291575753355391, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 3), -0.72072314107790303, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 4), -0.10555175857370022, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 5),  1.2593493954038599, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 6),  0.059283010135765903, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 7), -0.76540437113428617, precision))


        klab::KRandom::Instance().setSeed(123456);
        TNormalRandomMatrixOperator<klab::DoubleReal> op2(4, 8, 1.0, 2.0);

        TEST_ASSERT(op2.matrix().n_rows==4 && op2.matrix().n_cols==8)
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 0), 7.3069545044553177, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 1), 4.8591593440854197, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 2), 0.99996213618879282, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 3), 0.77975972229848489, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 4), 0.45113469948871043, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 5), -0.65903026715235336, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 6), 0.54105430108049135, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 7), 1.2454588081628279, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 0), 2.4110344828242236, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 1), -0.92840894367444293, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 2), 0.46375292519599254, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 3), -0.10402577033528204, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 4), 1.0182675779860761, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 5), -0.82053953328765994, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 6), -1.1358154756834393, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 7), 1.1022954313928401, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 0), -2.2612128703219727, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 1), -0.88547302573750297, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 2), 0.76531613352849448, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 3), 1.6818790085451041, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 4), 0.50886240300487318, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 5), -0.9345486684648554, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 6), -1.5967447201962743, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 7), 3.5146975699793437, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 0), 0.22694592945928793, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 1), 1.0135854745185031, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 2), 2.3058315150671076, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 3), -0.44144628215580606, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 4), 0.7888964828525995, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 5), 3.5186987908077199, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 6), 1.1185660202715317, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 7), -0.53080874226857233, precision))
		
		klab::KRandom::Instance().setSeed(123456);	
        TNormalRandomMatrixOperator<klab::DoubleReal> op3(4, 8, 1.0, 2.0, true);

        TEST_ASSERT(op3.matrix().n_rows==4 && op3.matrix().n_cols==8)
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 0), 0.9107457362736886, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 1), 0.94778292300972689, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 2), 0.37481591535290598, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 3), 0.40856832128697884, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 4), 0.30971716091885931, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 5), -0.17389794351090249, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 6), 0.23318706364590464, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 7), 0.31736116592396235, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 0), 0.30051362354892397, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 1), -0.1810869082643255, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 2), 0.1738285589666628, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 3), -0.054506065318672289, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 4), 0.69907046313883214, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 5), -0.21651530213426895, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 6), -0.48952106117495853, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 7), 0.28088103838256651, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 0), -0.28183971573892247, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 1), -0.17271222307234646, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 2), 0.28686352886932881, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 3), 0.88124900976360254, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 4), 0.34934891715409211, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 5), -0.24659882809194314, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 6), -0.68817531244295327, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 7), 0.89559647526530928, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 0), 0.028286755787748412, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 1), 0.19770065884516924, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 2), 0.86429507547502105, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 3), -0.23130326083928601, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 4), 0.54160050026055495, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 5), 0.92847705796538949, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 6), 0.48208677990418586, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 7), -0.1352578505406197, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-15;

        TNormalRandomMatrixOperator<klab::DoubleReal> op(4, 8);

        TNormalRandomMatrixOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.matrix().n_rows==4 && op2.matrix().n_cols==8)
        TEST_ASSERT(klab::Equals(op.matrix()(0, 0),  3.1534772522276588, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 1),  1.9295796720427096, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 2), -1.8931905603602584e-005, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 3), -0.11012013885075753, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 4), -0.27443265025564478, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 5), -0.82951513357617668, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 6), -0.22947284945975430, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 7),  0.12272940408141395, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 0),  0.70551724141211181, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 1), -0.96420447183722147, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 2), -0.26812353740200373, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 3), -0.55201288516764102, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 4),  0.0091337889930380393, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 5), -0.91026976664382997, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 6), -1.0679077378417197, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 7),  0.051147715696420064, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 0), -1.6306064351609864, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 1), -0.94273651286875149, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 2), -0.11734193323575276, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 3),  0.34093950427255204, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 4), -0.24556879849756338, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 5), -0.96727433423242770, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 6), -1.2983723600981372, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 7),  1.2573487849896718, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 0), -0.38652703527035603, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 1),  0.0067927372592515292, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 2),  0.65291575753355391, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 3), -0.72072314107790303, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 4), -0.10555175857370022, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 5),  1.2593493954038599, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 6),  0.059283010135765903, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 7), -0.76540437113428617, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testIsZero()
{
    try
    {
        TNormalRandomMatrixOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.m()==4 && op.n()==8)
        TEST_ASSERT(op.isZero() == false)

        TNormalRandomMatrixOperator<klab::DoubleReal> op2(4, 8, 0, 0);
        TEST_ASSERT(op2.m()==4 && op2.n()==8)
        TEST_ASSERT(op2.isZero())

        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > op3(4, 8, 0, 0);
        TEST_ASSERT(op3.m()==4 && op3.n()==8)
        TEST_ASSERT(op3.isZero())


        // Limit cases.
        TNormalRandomMatrixOperator<klab::DoubleReal> op0(0, 8);
        TEST_ASSERT(op0.m()==0 && op0.n()==8)
        TEST_ASSERT(op0.isZero())

        TNormalRandomMatrixOperator<klab::DoubleReal> op00(4, 0);
        TEST_ASSERT(op00.m()==4 && op00.n()==0)
        TEST_ASSERT(op00.isZero())

        TNormalRandomMatrixOperator<klab::DoubleReal> op000(0, 0);
        TEST_ASSERT(op000.m()==0 && op000.n()==0)
        TEST_ASSERT(op000.isZero())
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testSum()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);
        klab::DoubleReal precision = 1e-6;        

        TNormalRandomMatrixOperator<klab::DoubleReal> op(40, 80, 1.0, 2.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j];
        }
        TEST_ASSERT(klab::Equals(op.sum(), sum, 250))

        TNormalRandomMatrixOperator<klab::DoubleReal> op2(40, 80, 1.0, 2.0, true);
        sum = 0.0;
        for(klab::UInt32 i=0; i<op2.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j];
        }
        TEST_ASSERT(klab::Equals(op2.sum(), sum, 1e-9))


        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1.0, 2.0), std::complex<klab::DoubleReal>(3.0, 4.0));
        std::complex<klab::DoubleReal> csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j];
        }
        TEST_ASSERT(klab::Equals(cop.sum(), csum, 4e2))

        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop2(40, 80, std::complex<klab::DoubleReal>(1.0, 2.0), std::complex<klab::DoubleReal>(3.0, 4.0), true);
        csum = 0.0;
        for(klab::UInt32 i=0; i<cop2.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j];
        }
        TEST_ASSERT(klab::Equals(cop2.sum(), csum, 1e-9))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testNormFrobenius()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);     

        TNormalRandomMatrixOperator<klab::DoubleReal> op(40, 80, 1000.0, 2000.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j] * col[j];
        }
        TEST_ASSERT(klab::Equals(op.normFrobenius(), klab::Sqrt(sum), 10000.0))

        TNormalRandomMatrixOperator<klab::DoubleReal> op2(40, 80, 1000.0, 2000.0, true);
        sum = 0.0;
        for(klab::UInt32 i=0; i<op2.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j] * col[j];
        }
        TEST_ASSERT(klab::Equals(op2.normFrobenius(), klab::Sqrt(klab::DoubleReal(op2.n())), 1e-9))


        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0));
        std::complex<klab::DoubleReal> csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j].real()*col[j].real() + col[j].imag()*col[j].imag();
        }
        TEST_ASSERT(klab::Equals(cop.normFrobenius(), klab::Sqrt(csum), 10000.0))

        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop2(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0), true);
        csum = 0.0;
        for(klab::UInt32 i=0; i<cop2.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j].real()*col[j].real() + col[j].imag()*col[j].imag();
        }
        TEST_ASSERT(klab::Equals(cop2.normFrobenius(), std::complex<klab::DoubleReal>(klab::Sqrt(klab::DoubleReal(cop2.n()))), 10000.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testSquaredNormFrobenius()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);   

        TNormalRandomMatrixOperator<klab::DoubleReal> op(40, 80, 1000.0, 2000.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j] * col[j];
        }
        TEST_ASSERT(klab::Equals(op.squaredNormFrobenius(), sum, 1e10))

        TNormalRandomMatrixOperator<klab::DoubleReal> op2(40, 80, 1000.0, 2000.0, true);
        sum = 0.0;
        for(klab::UInt32 i=0; i<op2.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j] * col[j];
        }
        TEST_ASSERT(klab::Equals(op2.squaredNormFrobenius(), sum, 1e10))


        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0));
        std::complex<klab::DoubleReal>  csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j].real()*col[j].real() + col[j].imag()*col[j].imag();
        }
        TEST_ASSERT(klab::Equals(cop.squaredNormFrobenius(), csum, 1e10))

        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop2(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0), true);
        csum = 0.0;
        for(klab::UInt32 i=0; i<cop2.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j].real()*col[j].real() + col[j].imag()*col[j].imag();
        }
        TEST_ASSERT(klab::Equals(cop2.squaredNormFrobenius(), csum, 1e10))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testMean()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);
        klab::DoubleReal precision = 1e-12;        

        TNormalRandomMatrixOperator<klab::DoubleReal> op(40, 80, 1000.0, 2000.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j];
        }
        TEST_ASSERT(klab::Equals(op.mean(), sum/static_cast<klab::DoubleReal>(op.m()*op.n()), 100))
        TEST_ASSERT(klab::Equals(op.mean(), 1000.0, precision))

        TNormalRandomMatrixOperator<klab::DoubleReal> op2(40, 80, 1000.0, 2000.0, true);
        sum = 0.0;
        for(klab::UInt32 i=0; i<op2.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j];
        }
        TEST_ASSERT(klab::Equals(op2.mean(), sum/static_cast<klab::DoubleReal>(op2.m()*op2.n()), 1e-9))


        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0));
        std::complex<klab::DoubleReal> csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j];
        }
        TEST_ASSERT(klab::Equals(cop.mean(), csum/static_cast<klab::DoubleReal>(cop.m()*cop.n()), 200))
        TEST_ASSERT(klab::Equals(cop.mean(), std::complex<klab::DoubleReal>(1000.0, 2000.0), precision))

        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop2(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0), true);
        csum = 0.0;
        for(klab::UInt32 i=0; i<cop2.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j];
        }
        TEST_ASSERT(klab::Equals(cop2.mean(), csum/static_cast<klab::DoubleReal>(cop2.m()*cop2.n()), 1e-9))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testVariance()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);
        klab::DoubleReal precision = 1e-12;        

        TNormalRandomMatrixOperator<klab::DoubleReal> op(40, 80, 1000.0, 2000.0);
        klab::DoubleReal sum = 0.0;
        for(klab::UInt32 i=0; i<op.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j] * col[j];
        }
        TEST_ASSERT(klab::Equals(op.variance(), (sum/static_cast<klab::DoubleReal>(op.m()*op.n())) - op.mean()*op.mean(), 400000.0))
        TEST_ASSERT(klab::Equals(op.variance(), 4000000.0, precision))

        TNormalRandomMatrixOperator<klab::DoubleReal> op2(40, 80, 1000.0, 2000.0, true);
        sum = 0.0;
        for(klab::UInt32 i=0; i<op2.n(); ++i)
        {
            arma::Col<klab::DoubleReal> col;
            op2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                sum += col[j] * col[j];
        }
        TEST_ASSERT(klab::Equals(op2.variance(), (sum/static_cast<klab::DoubleReal>(op2.m()*op2.n())) - op2.mean()*op2.mean(), 1e-9))


        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0));
        std::complex<klab::DoubleReal> csum = 0.0;
        for(klab::UInt32 i=0; i<cop.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j].real()*col[j].real() + col[j].imag()*col[j].imag();
        }
        TEST_ASSERT(klab::Equals(cop.variance(), (csum/static_cast<klab::DoubleReal>(cop.m()*cop.n())) - klab::Conj(cop.mean())*cop.mean(), 1000000.0))
        TEST_ASSERT(klab::Equals(cop.variance(), std::complex<klab::DoubleReal>(25000000.0, 0.0), precision))

        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > cop2(40, 80, std::complex<klab::DoubleReal>(1000.0, 2000.0), std::complex<klab::DoubleReal>(3000.0, 4000.0), true);
        csum = 0.0;
        for(klab::UInt32 i=0; i<cop2.n(); ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            cop2.column(i, col);

            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                csum += col[j].real()*col[j].real() + col[j].imag()*col[j].imag();
        }
        TEST_ASSERT(klab::Equals(cop2.variance(), (csum/static_cast<klab::DoubleReal>(cop2.m()*cop2.n())) - klab::Conj(cop2.mean())*cop2.mean(), 1000000.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testApply()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12;        

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;

        TNormalRandomMatrixOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], -0.40162952110901640, precision))
        TEST_ASSERT(klab::Equals(y[1], -16.717435949357370, precision))
        TEST_ASSERT(klab::Equals(y[2], -8.5656534821675088, precision))
        TEST_ASSERT(klab::Equals(y[3],  0.022996828967926319, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testApply_Complex()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12;        

        arma::Col<std::complex<klab::DoubleReal> > x(8);
        arma::Col<std::complex<klab::DoubleReal> > y;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;

        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > op(4, 8, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(-5.1482303573234542, -14.384094701189083), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(-6.0752249975979629,  0.26855027151932731), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(-23.611992484184714,  25.423872784823658), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(-1.8035648566224123,  4.6833114946677856), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testApplyAdjoint()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12;        

        arma::Col<klab::DoubleReal> x(8);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;

        TNormalRandomMatrixOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], -0.40162952110901640, precision))
        TEST_ASSERT(klab::Equals(y[1], -16.717435949357370, precision))
        TEST_ASSERT(klab::Equals(y[2], -8.5656534821675088, precision))
        TEST_ASSERT(klab::Equals(y[3],  0.022996828967926319, precision))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0],  0.89735194014520658, precision))
        TEST_ASSERT(klab::Equals(xr[1],  23.419360846036149, precision))
        TEST_ASSERT(klab::Equals(xr[2],  5.5024709976768600, precision))
        TEST_ASSERT(klab::Equals(xr[3],  6.3355235508518470, precision))
        TEST_ASSERT(klab::Equals(xr[4],  2.0585565996559558, precision))
        TEST_ASSERT(klab::Equals(xr[5],  23.864832098241806, precision))
        TEST_ASSERT(klab::Equals(xr[6],  29.067613326497561, precision))
        TEST_ASSERT(klab::Equals(xr[7], -11.691966284758204, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KNormalRandomMatrixOperatorUnitTest::testApplyAdjoint_Complex()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-12;        

        arma::Col<std::complex<klab::DoubleReal> > x(8);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;
        x[0] = 1.0;
        x[1] = 2.0;
        x[2] = 3.0;
        x[3] = 4.0;
        x[4] = 5.0;
        x[5] = 6.0;
        x[6] = 7.0;
        x[7] = 8.0;

        TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> > op(4, 8, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(-5.1482303573234542, -14.384094701189083), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(-6.0752249975979629,  0.26855027151932731), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(-23.611992484184714,  25.423872784823658), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(-1.8035648566224123,  4.6833114946677856), precision))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], std::complex<klab::DoubleReal>(-16.127061955026637,  18.898349032727978), precision))
        TEST_ASSERT(klab::Equals(xr[1], std::complex<klab::DoubleReal>(-10.751376125618602, -16.701349764534747), precision))
        TEST_ASSERT(klab::Equals(xr[2], std::complex<klab::DoubleReal>( 34.350470793654488,   9.9455947111831442), precision))
        TEST_ASSERT(klab::Equals(xr[3], std::complex<klab::DoubleReal>( 48.388422417896024,  16.955795146010903), precision))
        TEST_ASSERT(klab::Equals(xr[4], std::complex<klab::DoubleReal>( 50.361584453641413, -19.383211286303059), precision))
        TEST_ASSERT(klab::Equals(xr[5], std::complex<klab::DoubleReal>( 25.098297916889621, -7.2190500154578991), precision))
        TEST_ASSERT(klab::Equals(xr[6], std::complex<klab::DoubleReal>( 60.659238690325516, -30.290654125176282), precision))
        TEST_ASSERT(klab::Equals(xr[7], std::complex<klab::DoubleReal>( 51.685626869591374,  33.638665147405632), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
