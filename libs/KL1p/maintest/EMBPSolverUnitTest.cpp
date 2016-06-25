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

#include "EMBPSolverUnitTest.h"
#include "../include/EMBPSolver.h"
#include "../include/MatrixOperator.h"
#include "../include/MultiplicationOperator.h"
#include "../include/NormalRandomMatrixOperator.h"
#include "../include/UniformRandomMatrixOperator.h"
#include "../include/InverseDCT1DOperator.h"
#include "../include/InverseFourier1DOperator.h"
#include "../include/RandomDownSamplingOperator.h"
#include "../include/ScalarOperator.h"
#include "../include/BlockTridiagonalOperator.h"
#include "../include/SeedingOperator.h"
#include "../include/GenericSeedingOperator.h"
#include "../include/Fourier1DOperator.h"
#include "../include/ScalingOperator.h"
#include "../include/RandomDownSamplingOperator.h"
#include "../include/RandomPermutationOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KEMBPSolverUnitTest::KEMBPSolverUnitTest() : Test::Suite()
{
    TEST_ADD(KEMBPSolverUnitTest::testDefaultConstructor)  
    TEST_ADD(KEMBPSolverUnitTest::testToleranceConstructor)
    TEST_ADD(KEMBPSolverUnitTest::testToleranceIterationLimitConstructor)
    TEST_ADD(KEMBPSolverUnitTest::testCopyConstructor)
    TEST_ADD(KEMBPSolverUnitTest::testAffectationOperator)

    TEST_ADD(KEMBPSolverUnitTest::testSetTolerance)
    TEST_ADD(KEMBPSolverUnitTest::testSetIterationLimit)
    TEST_ADD(KEMBPSolverUnitTest::testSetNoiseVariance)
    TEST_ADD(KEMBPSolverUnitTest::testSetMessageDamping)
    TEST_ADD(KEMBPSolverUnitTest::testSetLearningDamping)
    TEST_ADD(KEMBPSolverUnitTest::testEnableDampingLearning)
    TEST_ADD(KEMBPSolverUnitTest::testEnableParameterLearning)
    TEST_ADD(KEMBPSolverUnitTest::testEnableHomogeneous)
    TEST_ADD(KEMBPSolverUnitTest::testTolerance)
    TEST_ADD(KEMBPSolverUnitTest::testIterationLimit)
    TEST_ADD(KEMBPSolverUnitTest::testNoiseVariance)
    TEST_ADD(KEMBPSolverUnitTest::testMessageDamping)
    TEST_ADD(KEMBPSolverUnitTest::testLearningDamping)
    TEST_ADD(KEMBPSolverUnitTest::testIsDampingLearningEnabled)
    TEST_ADD(KEMBPSolverUnitTest::testIsParameterLearningEnabled)
    TEST_ADD(KEMBPSolverUnitTest::testIsHomogeneousEnabled)
    TEST_ADD(KEMBPSolverUnitTest::testResidualNorm)
    TEST_ADD(KEMBPSolverUnitTest::testRelativeResidualNorm)
    TEST_ADD(KEMBPSolverUnitTest::testIterations)
    TEST_ADD(KEMBPSolverUnitTest::testEnableHistory)
    TEST_ADD(KEMBPSolverUnitTest::testIsHistoryEnabled)
    TEST_ADD(KEMBPSolverUnitTest::testHistory)
    TEST_ADD(KEMBPSolverUnitTest::testSolve)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_02)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_03)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_04)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_05)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_06)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_07)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_08)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_09)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_10)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_11)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_12)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_13)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_14)
    TEST_ADD(KEMBPSolverUnitTest::testSolve_15)
}

// ---------------------------------------------------------------------------------------------------- //

KEMBPSolverUnitTest::~KEMBPSolverUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testDefaultConstructor()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.tolerance(), 1e-6))
        TEST_ASSERT(embp.iterationLimit() == 1000)
        TEST_ASSERT(klab::Equals(embp.noiseVariance(), klab::TTypeInfo<klab::DoubleReal>::ZERO))
        TEST_ASSERT(klab::Equals(embp.messageDamping(), 0.5))
        TEST_ASSERT(klab::Equals(embp.learningDamping(), 0.5))
        TEST_ASSERT(embp.isDampingLearningEnabled() == false)
        TEST_ASSERT(embp.isParameterLearningEnabled() == false)
        TEST_ASSERT(embp.isHomogeneousEnabled() == false)
        TEST_ASSERT(klab::Equals(embp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(embp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(embp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testToleranceConstructor()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp(1e-5);
        TEST_ASSERT(klab::Equals(embp.tolerance(), 1e-5))
        TEST_ASSERT(embp.iterationLimit() == 1000)
        TEST_ASSERT(klab::Equals(embp.noiseVariance(), klab::TTypeInfo<klab::DoubleReal>::ZERO))
        TEST_ASSERT(klab::Equals(embp.messageDamping(), 0.5))
        TEST_ASSERT(klab::Equals(embp.learningDamping(), 0.5))
        TEST_ASSERT(embp.isDampingLearningEnabled() == false)
        TEST_ASSERT(embp.isParameterLearningEnabled() == false)
        TEST_ASSERT(embp.isHomogeneousEnabled() == false)
        TEST_ASSERT(klab::Equals(embp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(embp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(embp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testToleranceIterationLimitConstructor()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp(1e-5, 30);
        TEST_ASSERT(klab::Equals(embp.tolerance(), 1e-5))
        TEST_ASSERT(embp.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(embp.noiseVariance(), klab::TTypeInfo<klab::DoubleReal>::ZERO))
        TEST_ASSERT(klab::Equals(embp.messageDamping(), 0.5))
        TEST_ASSERT(klab::Equals(embp.learningDamping(), 0.5))
        TEST_ASSERT(embp.isDampingLearningEnabled() == false)
        TEST_ASSERT(embp.isParameterLearningEnabled() == false)
        TEST_ASSERT(embp.isHomogeneousEnabled() == false)
        TEST_ASSERT(klab::Equals(embp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(embp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(embp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testCopyConstructor()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp(1e-5, 30);
        embp.setNoiseVariance(0.4);
        embp.setMessageDamping(0.1);
        embp.setLearningDamping(0.9);
        embp.enableDampingLearning(true);
        embp.enableParameterLearning(true);
        TEST_ASSERT(klab::Equals(embp.tolerance(), 1e-5))
        TEST_ASSERT(embp.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(embp.noiseVariance(), 0.4))
        TEST_ASSERT(klab::Equals(embp.messageDamping(), 0.1))
        TEST_ASSERT(klab::Equals(embp.learningDamping(), 0.9))
        TEST_ASSERT(embp.isDampingLearningEnabled() == true)
        TEST_ASSERT(embp.isParameterLearningEnabled() == true)
        TEST_ASSERT(embp.isHomogeneousEnabled() == false)
        TEST_ASSERT(klab::Equals(embp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(embp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(embp.iterations() == 0)

        TEMBPSolver<klab::DoubleReal> embp2(embp);
        TEST_ASSERT(klab::Equals(embp2.tolerance(), 1e-5))
        TEST_ASSERT(embp2.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(embp2.noiseVariance(), 0.4))
        TEST_ASSERT(klab::Equals(embp2.messageDamping(), 0.1))
        TEST_ASSERT(klab::Equals(embp2.learningDamping(), 0.9))
        TEST_ASSERT(embp2.isDampingLearningEnabled() == true)
        TEST_ASSERT(embp2.isParameterLearningEnabled() == true)
        TEST_ASSERT(embp2.isHomogeneousEnabled() == false)
        TEST_ASSERT(klab::Equals(embp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(embp2.relativeResidualNorm(), 0.0))
        TEST_ASSERT(embp2.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testAffectationOperator()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp(1e-5, 30);
        embp.setNoiseVariance(0.4);
        embp.setMessageDamping(0.1);
        embp.setLearningDamping(0.9);
        embp.enableDampingLearning(true);
        embp.enableParameterLearning(true);
        TEST_ASSERT(klab::Equals(embp.tolerance(), 1e-5))
        TEST_ASSERT(embp.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(embp.noiseVariance(), 0.4))
        TEST_ASSERT(klab::Equals(embp.messageDamping(), 0.1))
        TEST_ASSERT(klab::Equals(embp.learningDamping(), 0.9))
        TEST_ASSERT(embp.isDampingLearningEnabled() == true)
        TEST_ASSERT(embp.isParameterLearningEnabled() == true)
        TEST_ASSERT(embp.isHomogeneousEnabled() == false)
        TEST_ASSERT(klab::Equals(embp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(embp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(embp.iterations() == 0)

        TEMBPSolver<klab::DoubleReal> embp2;
        embp2 = embp;
        TEST_ASSERT(klab::Equals(embp2.tolerance(), 1e-5))
        TEST_ASSERT(embp2.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(embp2.noiseVariance(), 0.4))
        TEST_ASSERT(klab::Equals(embp2.messageDamping(), 0.1))
        TEST_ASSERT(klab::Equals(embp2.learningDamping(), 0.9))
        TEST_ASSERT(embp2.isDampingLearningEnabled() == true)
        TEST_ASSERT(embp2.isParameterLearningEnabled() == true)
        TEST_ASSERT(embp2.isHomogeneousEnabled() == false)
        TEST_ASSERT(klab::Equals(embp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(embp2.relativeResidualNorm(), 0.0))
        TEST_ASSERT(embp2.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSetTolerance()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.tolerance(), 1e-6))

        embp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(embp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSetIterationLimit()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.iterationLimit() == 1000)

        embp.setIterationLimit(30);
        TEST_ASSERT(embp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSetNoiseVariance()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.noiseVariance(), klab::TTypeInfo<klab::DoubleReal>::ZERO))

        embp.setNoiseVariance(0.01);
        TEST_ASSERT(klab::Equals(embp.noiseVariance(), 0.01))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSetMessageDamping()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.messageDamping(), 0.5))

        embp.setMessageDamping(0.01);
        TEST_ASSERT(klab::Equals(embp.messageDamping(), 0.01))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSetLearningDamping()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.learningDamping(), 0.5))

        embp.setLearningDamping(0.01);
        TEST_ASSERT(klab::Equals(embp.learningDamping(), 0.01))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testEnableDampingLearning()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.isDampingLearningEnabled() == false)

        embp.enableDampingLearning(true);
        TEST_ASSERT(embp.isDampingLearningEnabled() == true)

        embp.enableDampingLearning(false);
        TEST_ASSERT(embp.isDampingLearningEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testEnableParameterLearning()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.isParameterLearningEnabled() == false)

        embp.enableParameterLearning(true);
        TEST_ASSERT(embp.isParameterLearningEnabled() == true)

        embp.enableParameterLearning(false);
        TEST_ASSERT(embp.isParameterLearningEnabled() == false)   
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testEnableHomogeneous()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.isHomogeneousEnabled() == false)

        embp.enableHomogeneous(true);
        TEST_ASSERT(embp.isHomogeneousEnabled() == true)

        embp.enableHomogeneous(false);
        TEST_ASSERT(embp.isHomogeneousEnabled() == false)   
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testTolerance()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.tolerance(), 1e-6))

        embp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(embp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testIterationLimit()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.iterationLimit() == 1000)

        embp.setIterationLimit(30);
        TEST_ASSERT(embp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testNoiseVariance()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.noiseVariance(), klab::TTypeInfo<klab::DoubleReal>::ZERO))

        embp.setNoiseVariance(0.01);
        TEST_ASSERT(klab::Equals(embp.noiseVariance(), 0.01))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testMessageDamping()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.messageDamping(), 0.5))

        embp.setMessageDamping(0.01);
        TEST_ASSERT(klab::Equals(embp.messageDamping(), 0.01))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testLearningDamping()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.learningDamping(), 0.5))

        embp.setLearningDamping(0.01);
        TEST_ASSERT(klab::Equals(embp.learningDamping(), 0.01))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testIsDampingLearningEnabled()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.isDampingLearningEnabled() == false)

        embp.enableDampingLearning(true);
        TEST_ASSERT(embp.isDampingLearningEnabled() == true)

        embp.enableDampingLearning(false);
        TEST_ASSERT(embp.isDampingLearningEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testIsParameterLearningEnabled()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.isParameterLearningEnabled() == false)

        embp.enableParameterLearning(true);
        TEST_ASSERT(embp.isParameterLearningEnabled() == true)

        embp.enableParameterLearning(false);
        TEST_ASSERT(embp.isParameterLearningEnabled() == false)   
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testIsHomogeneousEnabled()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.isHomogeneousEnabled() == false)

        embp.enableHomogeneous(true);
        TEST_ASSERT(embp.isHomogeneousEnabled() == true)

        embp.enableHomogeneous(false);
        TEST_ASSERT(embp.isHomogeneousEnabled() == false)   
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testResidualNorm()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.residualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testRelativeResidualNorm()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(klab::Equals(embp.relativeResidualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testIterations()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testEnableHistory()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.isHistoryEnabled() == false)

        embp.enableHistory(true);
        TEST_ASSERT(embp.isHistoryEnabled() == true)

        embp.enableHistory(false);
        TEST_ASSERT(embp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testIsHistoryEnabled()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.isHistoryEnabled() == false)

        embp.enableHistory(true);
        TEST_ASSERT(embp.isHistoryEnabled() == true)

        embp.enableHistory(false);
        TEST_ASSERT(embp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testHistory()
{
    try
    {
        TEMBPSolver<klab::DoubleReal> embp;
        TEST_ASSERT(embp.history().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve()
{
    try
    {
        klab::UInt32 m = 32;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 12;    // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y(m);
        arma::Col<klab::DoubleReal> xr;
        arma::Mat<klab::DoubleReal> A(m, n);

        x.fill(0.0);
        x[5]  =  0.1273450527495;
        x[13] =  1.094270695640407;
        x[15] =  0.655726328475191;
        x[22] =  0.8544906548270752;
        x[29] = -0.5293306506731519;
        x[34] =  0.1778243729517102;
        x[35] = -0.5044189577772389;
        x[41] =  2.078922249764298;
        x[42] = -0.2239042442217898;
        x[47] = -0.5545832342364362;
        x[53] = -1.347922690481032;
        x[57] =  1.187360783753705;

        A(0, 0) = -0.431058929255128;
        A(0, 1) = -0.0640293293725052;
        A(0, 2) = 0.03137216260178667;
        A(0, 3) = 0.08980882631804447;
        A(0, 4) = 0.3984073950864456;
        A(0, 5) = -0.6110299299799094;
        A(0, 6) = 1.55820250113813;
        A(0, 7) = 2.099159934014919;
        A(0, 8) = 0.7944598824478513;
        A(0, 9) = -0.9193661070921185;
        A(0, 10) = -1.090738356375603;
        A(0, 11) = 0.9832787397667736;
        A(0, 12) = -0.07030963872412953;
        A(0, 13) = -0.4322815889233437;
        A(0, 14) = -0.2141886367485306;
        A(0, 15) = -1.283282181369735;
        A(0, 16) = -0.4472990097831398;
        A(0, 17) = 0.3255036496612943;
        A(0, 18) = -0.3609983969484584;
        A(0, 19) = -1.431095891121696;
        A(0, 20) = 0.2705762695868516;
        A(0, 21) = -0.5408646593735252;
        A(0, 22) = 0.09910207138415968;
        A(0, 23) = 0.8428033991064745;
        A(0, 24) = 0.7217645797038547;
        A(0, 25) = -1.09941215989963;
        A(0, 26) = 1.29762686116276;
        A(0, 27) = -0.6380770284435684;
        A(0, 28) = 0.3599122512685303;
        A(0, 29) = 1.654860044336955;
        A(0, 30) = 0.5904439865646157;
        A(0, 31) = 0.5073249178009254;
        A(0, 32) = -0.6802239048791758;
        A(0, 33) = -0.6066157749162476;
        A(0, 34) = -1.038892543339137;
        A(0, 35) = -1.40837920047749;
        A(0, 36) = 1.311168366912342;
        A(0, 37) = -1.641441792442;
        A(0, 38) = -0.9370465542051387;
        A(0, 39) = -1.105251443317609;
        A(0, 40) = -0.2926675817148794;
        A(0, 41) = 1.306744418351458;
        A(0, 42) = -0.4409635845090546;
        A(0, 43) = -0.7331445834882013;
        A(0, 44) = 0.3307516986281049;
        A(0, 45) = 0.1125903790700051;
        A(0, 46) = -1.96566733568985;
        A(0, 47) = 0.4124463445297792;
        A(0, 48) = -1.112499614849064;
        A(0, 49) = -0.4316354088784425;
        A(0, 50) = 0.9038634227268604;
        A(0, 51) = 0.7015281087561087;
        A(0, 52) = -0.5742075856760612;
        A(0, 53) = 1.089616903374275;
        A(0, 54) = -1.551460224671098;
        A(0, 55) = 0.7929475908043168;
        A(0, 56) = -1.312379332236955;
        A(0, 57) = -1.261218329193658;
        A(0, 58) = 0.1793698230227484;
        A(0, 59) = 0.594381640685025;
        A(0, 60) = -0.1611573806527335;
        A(0, 61) = 0.2457754398139489;
        A(0, 62) = -0.8564933058591249;
        A(0, 63) = -0.0137751297029588;
        A(1, 0) = 0.8324100712955423;
        A(1, 1) = -0.01632197854971153;
        A(1, 2) = 0.1091003690391474;
        A(1, 3) = -0.8202501241173595;
        A(1, 4) = -0.4998001231120233;
        A(1, 5) = 0.1968871745214071;
        A(1, 6) = -0.2590440596715165;
        A(1, 7) = -0.2484310896341931;
        A(1, 8) = -0.06194624557555838;
        A(1, 9) = -0.6326617912670465;
        A(1, 10) = 0.7215019868765904;
        A(1, 11) = 1.737175540396544;
        A(1, 12) = 2.343537272016475;
        A(1, 13) = 0.1367663585893845;
        A(1, 14) = -1.255532300802221;
        A(1, 15) = 0.1174901767406111;
        A(1, 16) = 1.529700972942256;
        A(1, 17) = 0.6108016519842261;
        A(1, 18) = 0.6392134953150673;
        A(1, 19) = -1.883892227853012;
        A(1, 20) = 0.908044020767859;
        A(1, 21) = 0.9888113253159396;
        A(1, 22) = -1.127829923666322;
        A(1, 23) = 0.1465305761949773;
        A(1, 24) = -0.971519060829746;
        A(1, 25) = 0.2458147298864119;
        A(1, 26) = -0.4122735693563095;
        A(1, 27) = 0.9195471258316537;
        A(1, 28) = 0.624178197157486;
        A(1, 29) = 0.1509366706637572;
        A(1, 30) = 2.807699863831833;
        A(1, 31) = -0.5474478703829876;
        A(1, 32) = 1.186897099801884;
        A(1, 33) = -0.5662214183106776;
        A(1, 34) = -0.4060239247962155;
        A(1, 35) = 0.8736264326619816;
        A(1, 36) = -1.20789116757058;
        A(1, 37) = -1.994553904474422;
        A(1, 38) = -1.406910749736436;
        A(1, 39) = 2.364092141209294;
        A(1, 40) = -0.03983613478526589;
        A(1, 41) = -0.2818238335706983;
        A(1, 42) = -0.02294545125744069;
        A(1, 43) = -0.8204712744751367;
        A(1, 44) = -0.2307010419617677;
        A(1, 45) = 0.2030649952061898;
        A(1, 46) = -0.3811195872375988;
        A(1, 47) = -0.04086444239247611;
        A(1, 48) = -1.107684093794347;
        A(1, 49) = -0.3558445895131669;
        A(1, 50) = 1.569784403651148;
        A(1, 51) = 0.3641786925793856;
        A(1, 52) = -1.139245261574371;
        A(1, 53) = -0.09552248067550065;
        A(1, 54) = -0.2886463250639135;
        A(1, 55) = 1.660645373145067;
        A(1, 56) = 1.137888442877561;
        A(1, 57) = -0.5316637330001424;
        A(1, 58) = -2.802789378773934;
        A(1, 59) = 0.9120703476721175;
        A(1, 60) = -0.1676149407476141;
        A(1, 61) = 0.6774994465876714;
        A(1, 62) = -0.5093165141324501;
        A(1, 63) = 0.181848481245366;
        A(2, 0) = 0.5841918064603469;
        A(2, 1) = -0.6344356843624622;
        A(2, 2) = 1.037229697501695;
        A(2, 3) = -0.07052742831643646;
        A(2, 4) = 0.1320901957014532;
        A(2, 5) = 0.2904574190585547;
        A(2, 6) = -0.2136647489727979;
        A(2, 7) = 2.043197551708864;
        A(2, 8) = -0.6302318596365595;
        A(2, 9) = -3.30266102478373;
        A(2, 10) = 0.2681428120150104;
        A(2, 11) = -1.503687946780615;
        A(2, 12) = -1.137675459513058;
        A(2, 13) = -1.736882945844565;
        A(2, 14) = 0.3074902595176672;
        A(2, 15) = -0.495178829849138;
        A(2, 16) = -1.273262486672611;
        A(2, 17) = -0.1599837731640216;
        A(2, 18) = 0.6019530544075274;
        A(2, 19) = -0.5007912264236983;
        A(2, 20) = 0.2594922176109386;
        A(2, 21) = 0.2581632315614216;
        A(2, 22) = -0.3706110191401011;
        A(2, 23) = 0.3595776331520678;
        A(2, 24) = -0.8348514279809391;
        A(2, 25) = 0.8730617414388571;
        A(2, 26) = -0.08072326407182465;
        A(2, 27) = 0.5693763022787123;
        A(2, 28) = 0.1597817245404274;
        A(2, 29) = -1.518309298405403;
        A(2, 30) = 0.5822097716182236;
        A(2, 31) = -1.155827283963635;
        A(2, 32) = -0.2773431748440161;
        A(2, 33) = 1.314789064111048;
        A(2, 34) = -0.02540443229161754;
        A(2, 35) = 1.449811893698888;
        A(2, 36) = 0.2139331001417025;
        A(2, 37) = 0.3541242347953142;
        A(2, 38) = 1.701473799978102;
        A(2, 39) = 2.076400835351201;
        A(2, 40) = -1.223015925823342;
        A(2, 41) = 1.862785255309596;
        A(2, 42) = 0.6234019108883657;
        A(2, 43) = 0.2744369779929839;
        A(2, 44) = 1.897246340072785;
        A(2, 45) = 0.7225484988886703;
        A(2, 46) = 0.4354703134170506;
        A(2, 47) = -0.9869553970089011;
        A(2, 48) = 0.3488975555160102;
        A(2, 49) = 0.4397038697219164;
        A(2, 50) = -0.5494186446145301;
        A(2, 51) = 0.00230074903772355;
        A(2, 52) = -1.032692068059212;
        A(2, 53) = -0.4077507928798254;
        A(2, 54) = 0.872339290622257;
        A(2, 55) = 0.9329827808903263;
        A(2, 56) = 0.4217976865848451;
        A(2, 57) = 2.304189362955214;
        A(2, 58) = -0.542074363289763;
        A(2, 59) = 1.828543936265022;
        A(2, 60) = 1.293191033242002;
        A(2, 61) = 0.7578239234720924;
        A(2, 62) = -0.8570148642956924;
        A(2, 63) = 0.9250726389279064;
        A(3, 0) = -1.34166346589151;
        A(3, 1) = 1.734818463618363;
        A(3, 2) = -0.7366548949187585;
        A(3, 3) = 0.2371967248111666;
        A(3, 4) = 0.3311104577500041;
        A(3, 5) = 0.6089978658208752;
        A(3, 6) = -0.2128414122946932;
        A(3, 7) = -0.5842181547584789;
        A(3, 8) = -2.756634510388993;
        A(3, 9) = 0.007578090155004409;
        A(3, 10) = -1.069770434345322;
        A(3, 11) = 0.528725139559372;
        A(3, 12) = 1.244251115782868;
        A(3, 13) = 1.460890663427895;
        A(3, 14) = -0.7890914908802797;
        A(3, 15) = -0.9718341422734824;
        A(3, 16) = -0.04178528134054397;
        A(3, 17) = -1.186644189627372;
        A(3, 18) = 0.05896727130075501;
        A(3, 19) = -1.184231896821562;
        A(3, 20) = 0.007173504010287755;
        A(3, 21) = 3.111083174847298;
        A(3, 22) = 0.6359472920222195;
        A(3, 23) = 0.6816626844566356;
        A(3, 24) = 0.365659076591269;
        A(3, 25) = 0.899611613906785;
        A(3, 26) = -0.8267567825499715;
        A(3, 27) = 1.46489956280522;
        A(3, 28) = -0.3999873736779166;
        A(3, 29) = -0.3241563246009816;
        A(3, 30) = 0.9375473555494902;
        A(3, 31) = -0.7340387047832985;
        A(3, 32) = 0.7884211156992639;
        A(3, 33) = -1.188234744650461;
        A(3, 34) = 1.712207764709634;
        A(3, 35) = -0.2715741388731723;
        A(3, 36) = -1.568244713918302;
        A(3, 37) = -1.391371297914386;
        A(3, 38) = -1.825379764094613;
        A(3, 39) = -0.2048201335146057;
        A(3, 40) = 0.6221742536567652;
        A(3, 41) = -1.108735509186315;
        A(3, 42) = -0.1420640106365527;
        A(3, 43) = -1.152489753855352;
        A(3, 44) = -0.9773963502390233;
        A(3, 45) = -0.9727588121953873;
        A(3, 46) = -0.5300370235032735;
        A(3, 47) = -0.8063615342492985;
        A(3, 48) = -0.04748331517633537;
        A(3, 49) = -1.57092344511803;
        A(3, 50) = -1.219373604246766;
        A(3, 51) = -0.4794756395912644;
        A(3, 52) = 0.1472537324435444;
        A(3, 53) = -0.1576561065149749;
        A(3, 54) = 0.2787543734142515;
        A(3, 55) = -1.036514656149594;
        A(3, 56) = 0.6401237632561114;
        A(3, 57) = -1.75062069656564;
        A(3, 58) = -1.30996017992952;
        A(3, 59) = -0.9903276876890069;
        A(3, 60) = -0.812177653856618;
        A(3, 61) = 1.118669196480276;
        A(3, 62) = 1.275218051540198;
        A(3, 63) = 0.4406213404044787;
        A(4, 0) = 0.3451649675212734;
        A(4, 1) = 0.02083615362103833;
        A(4, 2) = -0.7454953427400273;
        A(4, 3) = 0.5328817034122234;
        A(4, 4) = 1.770036416398246;
        A(4, 5) = -0.07848692076724977;
        A(4, 6) = 0.04525745176928564;
        A(4, 7) = 0.1946825210828556;
        A(4, 8) = -0.6849842082776039;
        A(4, 9) = -1.081178779899169;
        A(4, 10) = 0.8170751389287645;
        A(4, 11) = 0.449584032608674;
        A(4, 12) = -0.2920312895781;
        A(4, 13) = -1.471895060570783;
        A(4, 14) = 0.7720058756632596;
        A(4, 15) = 0.5401834409272764;
        A(4, 16) = -1.430531363537639;
        A(4, 17) = -0.03208439325040437;
        A(4, 18) = -0.201967156849246;
        A(4, 19) = -0.5465712684703722;
        A(4, 20) = 0.3016032699062112;
        A(4, 21) = 1.44025237290484;
        A(4, 22) = 0.5193813060910077;
        A(4, 23) = -0.5087508268606996;
        A(4, 24) = 1.052183688945218;
        A(4, 25) = -0.1145182417974893;
        A(4, 26) = -0.8439230052836451;
        A(4, 27) = 0.3812300431667353;
        A(4, 28) = -0.0428418542538697;
        A(4, 29) = -0.7604115803559854;
        A(4, 30) = 0.6439908949406314;
        A(4, 31) = -0.3250773455513032;
        A(4, 32) = 0.8870662859673023;
        A(4, 33) = 0.3624798529459776;
        A(4, 34) = 1.268692338159022;
        A(4, 35) = 0.3433859736240885;
        A(4, 36) = 0.7536772204074902;
        A(4, 37) = 0.7858715039077722;
        A(4, 38) = 0.2258977849746525;
        A(4, 39) = 0.2289550137336344;
        A(4, 40) = 0.08692448026212804;
        A(4, 41) = 0.9445426848937869;
        A(4, 42) = -0.1677479632828703;
        A(4, 43) = 0.5875171622237381;
        A(4, 44) = -0.6930412803509688;
        A(4, 45) = -0.6502737760558731;
        A(4, 46) = 0.08910217792697452;
        A(4, 47) = -0.141051684988309;
        A(4, 48) = 0.9645529845272776;
        A(4, 49) = -1.162240469270604;
        A(4, 50) = 0.1810851608416037;
        A(4, 51) = -1.062620284966184;
        A(4, 52) = -1.533545979326203;
        A(4, 53) = 0.1065735958296584;
        A(4, 54) = -0.4668667763638584;
        A(4, 55) = -0.5673967133233815;
        A(4, 56) = 0.2164402888210394;
        A(4, 57) = -1.459339489921065;
        A(4, 58) = -1.35211711544563;
        A(4, 59) = -0.7782850394519724;
        A(4, 60) = 0.1483354752556949;
        A(4, 61) = 1.328021330101157;
        A(4, 62) = -1.751365609755935;
        A(4, 63) = 0.2169315577831981;
        A(5, 0) = -1.187037769393816;
        A(5, 1) = -0.3167426515379083;
        A(5, 2) = 1.176326152088591;
        A(5, 3) = 0.3946345074314719;
        A(5, 4) = -1.168893410477735;
        A(5, 5) = 1.187630473264519;
        A(5, 6) = 0.584297207128943;
        A(5, 7) = -1.22350310479182;
        A(5, 8) = 1.564827240615063;
        A(5, 9) = 0.3168520161772764;
        A(5, 10) = 0.1770684465913581;
        A(5, 11) = 0.8229570182093525;
        A(5, 12) = 0.6096410499021392;
        A(5, 13) = -1.144026919286321;
        A(5, 14) = -0.005828513409837782;
        A(5, 15) = 2.089407114516609;
        A(5, 16) = -0.7206110071199725;
        A(5, 17) = 0.1269381863144968;
        A(5, 18) = -2.238532517859903;
        A(5, 19) = -0.2497715251381594;
        A(5, 20) = 2.067126133743951;
        A(5, 21) = -0.1486737311983966;
        A(5, 22) = -1.000885915982827;
        A(5, 23) = -0.1120358398638883;
        A(5, 24) = 0.8387616411037778;
        A(5, 25) = 0.3802265599238202;
        A(5, 26) = 1.112945789287855;
        A(5, 27) = 0.4178592374708008;
        A(5, 28) = -1.605054282298509;
        A(5, 29) = 0.19318730762291;
        A(5, 30) = -0.8812797774035319;
        A(5, 31) = -2.1246368085216;
        A(5, 32) = -1.152390433643937;
        A(5, 33) = 0.08801845703545473;
        A(5, 34) = -1.944131143502058;
        A(5, 35) = 0.878950645508865;
        A(5, 36) = 0.02180822897927239;
        A(5, 37) = 0.06131152798927372;
        A(5, 38) = -0.1163366078346196;
        A(5, 39) = -0.8658604509398618;
        A(5, 40) = 0.8240109256095909;
        A(5, 41) = 1.2348757306823;
        A(5, 42) = -0.548825933470069;
        A(5, 43) = 0.6288485248026944;
        A(5, 44) = -0.1924882433527011;
        A(5, 45) = 0.1161999004142705;
        A(5, 46) = -1.004793869154934;
        A(5, 47) = -0.620609375374551;
        A(5, 48) = 0.8409323472256678;
        A(5, 49) = 1.18385808703364;
        A(5, 50) = -0.6574551290466767;
        A(5, 51) = 0.05720555186718278;
        A(5, 52) = -0.5670971638771117;
        A(5, 53) = 0.2355591463016312;
        A(5, 54) = -1.326250474777681;
        A(5, 55) = -0.7062957542785687;
        A(5, 56) = -0.01644312046319547;
        A(5, 57) = -0.4767208202092922;
        A(5, 58) = 0.2062360226249639;
        A(5, 59) = -1.260138296908029;
        A(5, 60) = 1.053223713709774;
        A(5, 61) = 1.353571421976902;
        A(5, 62) = -0.5921838537181846;
        A(5, 63) = -0.02332489783704513;
        A(6, 0) = -0.1528705708985069;
        A(6, 1) = -0.4230593937269497;
        A(6, 2) = 1.131741704091009;
        A(6, 3) = 1.075311558691954;
        A(6, 4) = 0.5737109991742885;
        A(6, 5) = 1.308919660678649;
        A(6, 6) = 0.410278663991111;
        A(6, 7) = 0.00966077265898873;
        A(6, 8) = 2.31551157828616;
        A(6, 9) = -1.335024432929957;
        A(6, 10) = -0.8433043524619488;
        A(6, 11) = 1.132622045358363;
        A(6, 12) = 0.3799116633990179;
        A(6, 13) = 1.684370421411989;
        A(6, 14) = 0.5359388956426116;
        A(6, 15) = 1.790707440630706;
        A(6, 16) = -1.415100905712088;
        A(6, 17) = -0.34622913185879;
        A(6, 18) = -1.026377371814184;
        A(6, 19) = 0.32640536436066;
        A(6, 20) = -0.3829149978817087;
        A(6, 21) = 0.1619328883582157;
        A(6, 22) = -0.6481493131568534;
        A(6, 23) = 0.1054308591001289;
        A(6, 24) = -0.03885242817520313;
        A(6, 25) = -0.7647844750471338;
        A(6, 26) = 1.425970306203917;
        A(6, 27) = 0.04718755194213511;
        A(6, 28) = -0.4520184101137934;
        A(6, 29) = -2.077101074180348;
        A(6, 30) = -0.8122784742575844;
        A(6, 31) = -1.392086931715145;
        A(6, 32) = 1.422536112262464;
        A(6, 33) = -0.5541351571054176;
        A(6, 34) = 1.299772874788647;
        A(6, 35) = -0.06279251409504998;
        A(6, 36) = -1.37948056430648;
        A(6, 37) = 1.011373935530421;
        A(6, 38) = -1.46356871907606;
        A(6, 39) = 0.8641034816524091;
        A(6, 40) = -1.474223938327494;
        A(6, 41) = 0.9686594876814259;
        A(6, 42) = 2.04538732657389;
        A(6, 43) = -0.982452485834293;
        A(6, 44) = -0.5098169636395428;
        A(6, 45) = 1.122767939675871;
        A(6, 46) = 1.387116059056607;
        A(6, 47) = 0.8272926842868055;
        A(6, 48) = -1.761355976624785;
        A(6, 49) = 1.273624379384039;
        A(6, 50) = 0.4685775101002604;
        A(6, 51) = 0.00158627088956676;
        A(6, 52) = 0.9172554194872437;
        A(6, 53) = -0.06246425072851154;
        A(6, 54) = -0.8021055298506352;
        A(6, 55) = 0.2101750992325023;
        A(6, 56) = -0.4211727083444125;
        A(6, 57) = 1.478703918345732;
        A(6, 58) = 1.459522125867764;
        A(6, 59) = -0.4743347768432786;
        A(6, 60) = -0.2371711597949307;
        A(6, 61) = -3.21537756914736;
        A(6, 62) = 2.309074180059145;
        A(6, 63) = -0.8834161768077362;
        A(7, 0) = -0.3389038224913568;
        A(7, 1) = 0.2986589706441202;
        A(7, 2) = -0.5068516844789348;
        A(7, 3) = -1.123634882188716;
        A(7, 4) = -1.009516738602982;
        A(7, 5) = 0.5205457767492484;
        A(7, 6) = 0.4791008619866002;
        A(7, 7) = -0.2391547238592451;
        A(7, 8) = -0.967044957831352;
        A(7, 9) = 0.2446309106629011;
        A(7, 10) = 1.024616393197034;
        A(7, 11) = -0.7031872573379506;
        A(7, 12) = -0.2428650719796918;
        A(7, 13) = -1.097061000509035;
        A(7, 14) = -0.1171978480573067;
        A(7, 15) = -1.045698781934902;
        A(7, 16) = 0.6442349710632958;
        A(7, 17) = 2.182208054052226;
        A(7, 18) = -1.026722315870031;
        A(7, 19) = -0.9597503094216444;
        A(7, 20) = -0.3401437625901588;
        A(7, 21) = -0.152006413985004;
        A(7, 22) = 0.9616219494858975;
        A(7, 23) = -0.8261434877080254;
        A(7, 24) = 1.137089499969684;
        A(7, 25) = -1.060637910591004;
        A(7, 26) = -0.2212134150223718;
        A(7, 27) = -1.374144700517549;
        A(7, 28) = -0.1794264564167967;
        A(7, 29) = -1.590069282802557;
        A(7, 30) = -0.02791903763257786;
        A(7, 31) = 0.9085397460265883;
        A(7, 32) = 0.4726363843286369;
        A(7, 33) = 0.3813394880747307;
        A(7, 34) = -0.456647036721225;
        A(7, 35) = 0.8063562674770322;
        A(7, 36) = -0.1410771453662216;
        A(7, 37) = -0.4833618163182959;
        A(7, 38) = 0.6857894986503743;
        A(7, 39) = -1.167425209711473;
        A(7, 40) = -0.5979160782921991;
        A(7, 41) = -0.1509774758733518;
        A(7, 42) = -1.091543248203099;
        A(7, 43) = -1.248593721523877;
        A(7, 44) = 0.5843033175431701;
        A(7, 45) = -0.9814833805834841;
        A(7, 46) = 0.04051938881614948;
        A(7, 47) = 1.846598521381206;
        A(7, 48) = 0.1449586303650474;
        A(7, 49) = -0.9906032850295544;
        A(7, 50) = 0.513189258200573;
        A(7, 51) = 0.409412733362445;
        A(7, 52) = 1.900129791494993;
        A(7, 53) = 0.5721284615501295;
        A(7, 54) = -0.003291656756640657;
        A(7, 55) = -0.62261335331896;
        A(7, 56) = -0.3638502506774186;
        A(7, 57) = -0.9838777027399744;
        A(7, 58) = -0.6707557527045086;
        A(7, 59) = -0.6898374763151564;
        A(7, 60) = 0.2901682604335387;
        A(7, 61) = -0.3739494131775255;
        A(7, 62) = 1.384757909389347;
        A(7, 63) = 0.4197887814982221;
        A(8, 0) = 0.9399047328138495;
        A(8, 1) = 0.9464125463165942;
        A(8, 2) = 0.7495985835157828;
        A(8, 3) = -0.006390750094964756;
        A(8, 4) = -0.5913825798168806;
        A(8, 5) = -0.1102209578963339;
        A(8, 6) = 1.253227875084328;
        A(8, 7) = 0.4961076778576968;
        A(8, 8) = 1.166791695027493;
        A(8, 9) = 1.544104372234362;
        A(8, 10) = -0.1396178115813355;
        A(8, 11) = -1.08492654116126;
        A(8, 12) = 0.8854350286002867;
        A(8, 13) = 1.376137024035775;
        A(8, 14) = -0.1885666319890167;
        A(8, 15) = -0.513417825425167;
        A(8, 16) = 2.184794876881067;
        A(8, 17) = 0.9083010531287159;
        A(8, 18) = 0.7124655942267881;
        A(8, 19) = 0.6841098243963816;
        A(8, 20) = -0.4099812261428726;
        A(8, 21) = -0.3056040727855858;
        A(8, 22) = -0.1346527244272275;
        A(8, 23) = 0.2166878126927498;
        A(8, 24) = 1.816635255320952;
        A(8, 25) = -0.8708612642588725;
        A(8, 26) = -0.8741005821785198;
        A(8, 27) = -0.9965448545000091;
        A(8, 28) = 0.1393813338547208;
        A(8, 29) = -2.156601281990279;
        A(8, 30) = -2.143725428689433;
        A(8, 31) = -0.7439350208384336;
        A(8, 32) = 1.819336831624732;
        A(8, 33) = -1.519544971234753;
        A(8, 34) = -0.4042808112432238;
        A(8, 35) = -0.4884778203669912;
        A(8, 36) = 0.8119709949549816;
        A(8, 37) = 1.044595687172183;
        A(8, 38) = 1.068963982339143;
        A(8, 39) = 0.02847591797981332;
        A(8, 40) = -0.5161040104582755;
        A(8, 41) = -1.413350315483791;
        A(8, 42) = 1.311096371909853;
        A(8, 43) = 0.04162121058748668;
        A(8, 44) = 0.4463095036321165;
        A(8, 45) = -0.04806797991659962;
        A(8, 46) = -1.235306458669973;
        A(8, 47) = -0.6377910409949784;
        A(8, 48) = -0.2032950248382978;
        A(8, 49) = -0.7657977814602652;
        A(8, 50) = -1.433172466715997;
        A(8, 51) = 1.099492887335456;
        A(8, 52) = -0.33662753086933;
        A(8, 53) = 1.458418961870746;
        A(8, 54) = 1.596493038797016;
        A(8, 55) = -0.4599756793704983;
        A(8, 56) = -1.712022476022943;
        A(8, 57) = 0.5844847118690755;
        A(8, 58) = -0.4807629075951234;
        A(8, 59) = -0.5921150468114966;
        A(8, 60) = -1.90063820236188;
        A(8, 61) = 0.2406420137768506;
        A(8, 62) = 0.6478659682030878;
        A(8, 63) = 0.65539882728327;
        A(9, 0) = -1.00328629571678;
        A(9, 1) = 0.368637585440867;
        A(9, 2) = 0.6384552233712406;
        A(9, 3) = 1.375048242645779;
        A(9, 4) = 1.094359397586627;
        A(9, 5) = 0.4346914384641099;
        A(9, 6) = 0.4027082796641071;
        A(9, 7) = -0.3156158906892415;
        A(9, 8) = 0.9785432100386099;
        A(9, 9) = -1.732335166765294;
        A(9, 10) = -0.3458389142899389;
        A(9, 11) = -1.215891630285445;
        A(9, 12) = 0.9835800429954661;
        A(9, 13) = -0.7301120185695065;
        A(9, 14) = 0.1621175355453229;
        A(9, 15) = 0.2316259278036119;
        A(9, 16) = -0.3200831078294054;
        A(9, 17) = 0.3805568678047162;
        A(9, 18) = 0.9603919581620721;
        A(9, 19) = 0.1874459072902532;
        A(9, 20) = -0.652024151577033;
        A(9, 21) = -0.5599235069495604;
        A(9, 22) = -0.1440597795232049;
        A(9, 23) = -0.9093641108758143;
        A(9, 24) = 0.4370020694684548;
        A(9, 25) = 0.01946151664299726;
        A(9, 26) = 1.193056445523211;
        A(9, 27) = 1.240446882730465;
        A(9, 28) = -0.5881094035284307;
        A(9, 29) = 1.537877202854202;
        A(9, 30) = 0.5027062884591657;
        A(9, 31) = 1.46046151474151;
        A(9, 32) = -0.5706617347292361;
        A(9, 33) = -1.053034268197049;
        A(9, 34) = -0.5251317683441591;
        A(9, 35) = -0.7466670164270048;
        A(9, 36) = -1.743062991804922;
        A(9, 37) = -0.7673634860608786;
        A(9, 38) = -0.9738225106757041;
        A(9, 39) = -0.6058774439611767;
        A(9, 40) = 0.2092161049192564;
        A(9, 41) = -0.1572286398240914;
        A(9, 42) = -0.5079977181975813;
        A(9, 43) = -1.27205717822463;
        A(9, 44) = 1.678360088874308;
        A(9, 45) = 0.5093628992783973;
        A(9, 46) = 0.4231973756043324;
        A(9, 47) = -0.1806408563605244;
        A(9, 48) = 1.510105417852432;
        A(9, 49) = 0.9692248847975625;
        A(9, 50) = 0.1875360665974808;
        A(9, 51) = -0.2874902863406585;
        A(9, 52) = 0.541453408510941;
        A(9, 53) = 0.04055737453087407;
        A(9, 54) = 3.063824392024558;
        A(9, 55) = 0.5556042602806067;
        A(9, 56) = 0.2817069756072134;
        A(9, 57) = -0.4418125331614392;
        A(9, 58) = 0.7647918134907457;
        A(9, 59) = 0.4212375351062669;
        A(9, 60) = -0.3304726779752683;
        A(9, 61) = -1.003876157677131;
        A(9, 62) = -0.4386371284991261;
        A(9, 63) = 0.8172679316680366;
        A(10, 0) = 1.432213198606983;
        A(10, 1) = -0.9588515482677122;
        A(10, 2) = 1.2105362577718;
        A(10, 3) = 0.2128978131588137;
        A(10, 4) = -1.615527076903782;
        A(10, 5) = -1.277945739192234;
        A(10, 6) = 0.8504342099655891;
        A(10, 7) = 2.393903097574091;
        A(10, 8) = -1.842498939733209;
        A(10, 9) = -0.4721251178319766;
        A(10, 10) = -0.5664438847980863;
        A(10, 11) = -0.1022252020382701;
        A(10, 12) = 1.684356041638017;
        A(10, 13) = 1.799101377510278;
        A(10, 14) = -0.01431078845980759;
        A(10, 15) = 0.8998387879115054;
        A(10, 16) = -0.9127697123481637;
        A(10, 17) = -1.572056958825487;
        A(10, 18) = -0.3347805242042668;
        A(10, 19) = -0.194263036641906;
        A(10, 20) = -0.5417840690704958;
        A(10, 21) = -0.2201117804028161;
        A(10, 22) = -0.9862829101512816;
        A(10, 23) = 0.6400482805559927;
        A(10, 24) = -1.84124464232491;
        A(10, 25) = -0.761408145471323;
        A(10, 26) = 0.8859983471656422;
        A(10, 27) = 1.090668471471759;
        A(10, 28) = -1.531642353664074;
        A(10, 29) = 0.5415963112672286;
        A(10, 30) = 2.181559782942443;
        A(10, 31) = 0.9998934532105044;
        A(10, 32) = 0.4158577103667869;
        A(10, 33) = 0.6997210611328814;
        A(10, 34) = 0.2409116329563526;
        A(10, 35) = 1.490446574670286;
        A(10, 36) = -2.161120976644972;
        A(10, 37) = 0.1727966738169848;
        A(10, 38) = 0.4723324795235227;
        A(10, 39) = 0.4431558194384705;
        A(10, 40) = -0.5050313399738976;
        A(10, 41) = -1.286193064110895;
        A(10, 42) = 0.05310056691286284;
        A(10, 43) = -0.06994211867609868;
        A(10, 44) = 1.776931738461227;
        A(10, 45) = 0.3981057350669132;
        A(10, 46) = -0.9741031411015449;
        A(10, 47) = 0.6910263040070263;
        A(10, 48) = 0.383740430851566;
        A(10, 49) = 0.2333856278337476;
        A(10, 50) = -0.4701513415340134;
        A(10, 51) = -0.1743503504623961;
        A(10, 52) = 1.456332196528072;
        A(10, 53) = 0.3283023211484678;
        A(10, 54) = 0.2617487973383053;
        A(10, 55) = 0.5784866480713029;
        A(10, 56) = 1.003701783708345;
        A(10, 57) = -0.115766743427119;
        A(10, 58) = -0.2637956626530077;
        A(10, 59) = -0.01021595279904608;
        A(10, 60) = -0.4589912754597937;
        A(10, 61) = -0.5383186254300945;
        A(10, 62) = 0.1483395322013434;
        A(10, 63) = -0.05079361577696345;
        A(11, 0) = -0.2776599783034855;
        A(11, 1) = -0.7979211455482987;
        A(11, 2) = -1.539968071457508;
        A(11, 3) = 1.472917257902094;
        A(11, 4) = 0.1526163600433733;
        A(11, 5) = -0.6765364680559369;
        A(11, 6) = 1.226317911787362;
        A(11, 7) = 0.848943207579585;
        A(11, 8) = -0.8381903663076167;
        A(11, 9) = -1.093376513381303;
        A(11, 10) = 0.2356579841388219;
        A(11, 11) = -2.36162328689552;
        A(11, 12) = -0.8961489493870217;
        A(11, 13) = 0.7925208526054761;
        A(11, 14) = -0.928420100392673;
        A(11, 15) = 2.518419435555763;
        A(11, 16) = -0.4326868699526775;
        A(11, 17) = -0.4884371958368969;
        A(11, 18) = -1.259048440349659;
        A(11, 19) = -2.504578306130965;
        A(11, 20) = 0.8917594513464341;
        A(11, 21) = 0.6947829556935465;
        A(11, 22) = -0.2843464836664896;
        A(11, 23) = 0.7427123131118213;
        A(11, 24) = 1.016979935291112;
        A(11, 25) = 0.4245180786159056;
        A(11, 26) = 2.162388736387479;
        A(11, 27) = -0.4429876101258528;
        A(11, 28) = 1.17271630243883;
        A(11, 29) = 1.0554602632108;
        A(11, 30) = -1.193319308609835;
        A(11, 31) = -0.7047807617461999;
        A(11, 32) = 1.445316447192004;
        A(11, 33) = 1.238889502535316;
        A(11, 34) = 0.3695843170147263;
        A(11, 35) = 0.5000377097317487;
        A(11, 36) = -1.460526969172138;
        A(11, 37) = 0.1047689153958333;
        A(11, 38) = -0.2059855830971631;
        A(11, 39) = 3.127860792741767;
        A(11, 40) = -0.7623011712856264;
        A(11, 41) = 0.2217188770409482;
        A(11, 42) = -1.391546930574096;
        A(11, 43) = 1.363603319320906;
        A(11, 44) = -1.476468986172683;
        A(11, 45) = -0.005608907528561111;
        A(11, 46) = 0.8020655032344448;
        A(11, 47) = -0.2546490461955305;
        A(11, 48) = 0.3065603842248287;
        A(11, 49) = 0.282107527938902;
        A(11, 50) = -0.7297738955491023;
        A(11, 51) = 0.9946561407465665;
        A(11, 52) = 0.1057874621358077;
        A(11, 53) = -0.3113081417855453;
        A(11, 54) = -1.109516311276169;
        A(11, 55) = -1.526388210309369;
        A(11, 56) = 2.133759474974002;
        A(11, 57) = 0.1829789227645364;
        A(11, 58) = -0.005743311461297923;
        A(11, 59) = 1.429548191171658;
        A(11, 60) = 0.5487739029955127;
        A(11, 61) = -0.6635299225730571;
        A(11, 62) = -0.2500223448681423;
        A(11, 63) = 2.140863896143493;
        A(12, 0) = 0.3208958901708582;
        A(12, 1) = 0.5103998980546816;
        A(12, 2) = 1.343322843082524;
        A(12, 3) = -0.5352843481780406;
        A(12, 4) = -0.05479574095112598;
        A(12, 5) = -1.901306055067542;
        A(12, 6) = 2.31606025142822;
        A(12, 7) = -0.3318118627845895;
        A(12, 8) = 0.3577625809514444;
        A(12, 9) = -1.013898070616929;
        A(12, 10) = -0.7944827066461646;
        A(12, 11) = 0.4618826556927645;
        A(12, 12) = -0.8417629882564399;
        A(12, 13) = 1.225198452598123;
        A(12, 14) = 0.9627782134669518;
        A(12, 15) = 0.500741324847351;
        A(12, 16) = 0.2233846310811128;
        A(12, 17) = -2.060375736171322;
        A(12, 18) = 0.7960489550478256;
        A(12, 19) = 1.595280068978013;
        A(12, 20) = 0.6619686045693826;
        A(12, 21) = -0.2006130375905841;
        A(12, 22) = -0.2536172811401378;
        A(12, 23) = 0.3259753856088387;
        A(12, 24) = -1.135332367821216;
        A(12, 25) = 1.179828517308362;
        A(12, 26) = -0.7983066489324538;
        A(12, 27) = 0.8350045887066383;
        A(12, 28) = 0.2935304213753345;
        A(12, 29) = 1.154252501074368;
        A(12, 30) = -0.9226868562170182;
        A(12, 31) = 0.8604064928948725;
        A(12, 32) = 0.951171946340814;
        A(12, 33) = -0.9786077797475108;
        A(12, 34) = -0.9788412475942987;
        A(12, 35) = 1.382286958473927;
        A(12, 36) = -0.7195556035228379;
        A(12, 37) = -0.8259552614310365;
        A(12, 38) = -0.5944698811991845;
        A(12, 39) = -0.2788700936186678;
        A(12, 40) = -0.3354909763542895;
        A(12, 41) = -1.582679972032991;
        A(12, 42) = -0.4585448903441963;
        A(12, 43) = -0.4957034942803235;
        A(12, 44) = -0.2074182164770412;
        A(12, 45) = -0.4795163560274995;
        A(12, 46) = -1.168444036228117;
        A(12, 47) = 0.9954996653206386;
        A(12, 48) = 0.1228600479928733;
        A(12, 49) = -0.3037377091050433;
        A(12, 50) = -0.9457438931031506;
        A(12, 51) = -0.5090013774675272;
        A(12, 52) = 1.240026502624521;
        A(12, 53) = 1.585100587299442;
        A(12, 54) = -0.1797717170552969;
        A(12, 55) = -2.460886286633268;
        A(12, 56) = -1.042780293032187;
        A(12, 57) = -0.6761014685827689;
        A(12, 58) = 0.2387829849054849;
        A(12, 59) = 3.073356327847002;
        A(12, 60) = -0.1434571221314103;
        A(12, 61) = 0.3259855829476406;
        A(12, 62) = 0.827318109922612;
        A(12, 63) = -0.002172157877203559;
        A(13, 0) = 1.843875103392763;
        A(13, 1) = -0.4930855735492852;
        A(13, 2) = -1.691212915181234;
        A(13, 3) = -1.259731224647393;
        A(13, 4) = -0.4667257256678196;
        A(13, 5) = 1.11735317804768;
        A(13, 6) = 1.302815622367588;
        A(13, 7) = 1.085237379510033;
        A(13, 8) = 1.744302305162423;
        A(13, 9) = 0.7615823274128339;
        A(13, 10) = -1.553951324212187;
        A(13, 11) = -1.246762872482759;
        A(13, 12) = 0.7316832431543923;
        A(13, 13) = -0.9307144498784628;
        A(13, 14) = 0.4800070444020901;
        A(13, 15) = -1.439014597999005;
        A(13, 16) = 0.684663259704232;
        A(13, 17) = -1.045304617118589;
        A(13, 18) = -0.1328125886878443;
        A(13, 19) = 0.4228872694573875;
        A(13, 20) = 1.576436748322973;
        A(13, 21) = 0.1002833803395052;
        A(13, 22) = -0.572928893969137;
        A(13, 23) = -0.4596662394111041;
        A(13, 24) = 0.3928653787943905;
        A(13, 25) = -0.2649289440199081;
        A(13, 26) = 1.08267587223692;
        A(13, 27) = 1.78445301410157;
        A(13, 28) = 0.716035379542674;
        A(13, 29) = -0.01811414830504666;
        A(13, 30) = -1.920349935082768;
        A(13, 31) = -0.7111880022964282;
        A(13, 32) = 0.09765812925453242;
        A(13, 33) = 0.2864645142312831;
        A(13, 34) = 0.363734133323173;
        A(13, 35) = 0.2505785028615984;
        A(13, 36) = 0.6423074403813313;
        A(13, 37) = 1.322570657986571;
        A(13, 38) = 0.08368742670073823;
        A(13, 39) = -0.1154021865795368;
        A(13, 40) = -0.06589129850015074;
        A(13, 41) = 2.071752032937372;
        A(13, 42) = 0.1441148310841086;
        A(13, 43) = -0.860451788946914;
        A(13, 44) = -0.7481750381476182;
        A(13, 45) = -0.2074813763363882;
        A(13, 46) = 0.9920288758734495;
        A(13, 47) = -0.3049904020403683;
        A(13, 48) = 0.6907894875708982;
        A(13, 49) = -1.511855263088993;
        A(13, 50) = 0.3296108200997556;
        A(13, 51) = -1.397349789742741;
        A(13, 52) = 0.295182486062034;
        A(13, 53) = 0.7291641039595553;
        A(13, 54) = -0.0266492918217317;
        A(13, 55) = 0.7954275207568304;
        A(13, 56) = -0.7587434483087904;
        A(13, 57) = -0.709651268265761;
        A(13, 58) = 0.5498496972889837;
        A(13, 59) = -0.7873565927834921;
        A(13, 60) = 0.008808535488116947;
        A(13, 61) = -0.3198953583277921;
        A(13, 62) = -0.8173013551471573;
        A(13, 63) = -0.1041224568695235;
        A(14, 0) = -0.4617638579838592;
        A(14, 1) = 0.8411487716524435;
        A(14, 2) = -0.09980210847601252;
        A(14, 3) = 0.4666247971643449;
        A(14, 4) = -0.8275787927673949;
        A(14, 5) = 0.3055362073641591;
        A(14, 6) = -0.9099538097640678;
        A(14, 7) = -0.2477550352221421;
        A(14, 8) = 0.2265639935232574;
        A(14, 9) = 1.404658590875385;
        A(14, 10) = -0.3563974017746553;
        A(14, 11) = 0.9712471311803163;
        A(14, 12) = -0.4192457004139307;
        A(14, 13) = -0.4215191328558902;
        A(14, 14) = -0.4188954907070447;
        A(14, 15) = 0.6320440850768987;
        A(14, 16) = 1.978091433973177;
        A(14, 17) = 1.430918344973732;
        A(14, 18) = 1.02482474688685;
        A(14, 19) = -0.01222924587638289;
        A(14, 20) = -0.9560613295821928;
        A(14, 21) = 0.9719125722373065;
        A(14, 22) = -0.3132680586045425;
        A(14, 23) = 0.1073168117624278;
        A(14, 24) = -0.4213972810007362;
        A(14, 25) = -0.6555261041755833;
        A(14, 26) = 0.5978997801824271;
        A(14, 27) = -0.5270461976157808;
        A(14, 28) = 0.07133336235291275;
        A(14, 29) = -0.9701685781378592;
        A(14, 30) = 0.2411215925133577;
        A(14, 31) = 0.1256785386842436;
        A(14, 32) = 2.233121358236669;
        A(14, 33) = -1.089816670620501;
        A(14, 34) = -0.8324408978057852;
        A(14, 35) = 0.07281200088477152;
        A(14, 36) = 0.6385892022343536;
        A(14, 37) = 0.1553708031830501;
        A(14, 38) = 1.607040045525812;
        A(14, 39) = 1.192937478777962;
        A(14, 40) = -0.3931065211972259;
        A(14, 41) = 0.3831912904284145;
        A(14, 42) = 0.6210221271308293;
        A(14, 43) = -1.107340229923169;
        A(14, 44) = 1.664978177652695;
        A(14, 45) = 0.6177239781077938;
        A(14, 46) = -0.058488126020257;
        A(14, 47) = 0.1277532809875645;
        A(14, 48) = 0.872157084227191;
        A(14, 49) = -1.180527351981853;
        A(14, 50) = -0.1100428153343983;
        A(14, 51) = 1.055351825584927;
        A(14, 52) = 0.9582787838168144;
        A(14, 53) = -0.692646414582076;
        A(14, 54) = -1.956635055062031;
        A(14, 55) = 1.814900141172282;
        A(14, 56) = 0.6503016243167592;
        A(14, 57) = 0.1418189799432524;
        A(14, 58) = -2.106194459432425;
        A(14, 59) = 1.806428917458409;
        A(14, 60) = 0.9704499542447836;
        A(14, 61) = -0.3978508180090851;
        A(14, 62) = -1.201326538950775;
        A(14, 63) = -1.128787949010187;
        A(15, 0) = 1.571571548921988;
        A(15, 1) = 0.9766965167741691;
        A(15, 2) = -0.6918223151533685;
        A(15, 3) = -1.372545635895384;
        A(15, 4) = -0.3489760388700541;
        A(15, 5) = 2.346687948423932;
        A(15, 6) = -1.86925772125654;
        A(15, 7) = -0.2959212207343046;
        A(15, 8) = 0.2506824679435218;
        A(15, 9) = 0.7359701912701386;
        A(15, 10) = 1.471031097647418;
        A(15, 11) = -1.380743617540058;
        A(15, 12) = -0.6452085838575904;
        A(15, 13) = 1.028315064903479;
        A(15, 14) = 0.4743876290677602;
        A(15, 15) = -0.1646416942266672;
        A(15, 16) = -1.663296009414077;
        A(15, 17) = -0.896140864488334;
        A(15, 18) = 0.2945906850713783;
        A(15, 19) = -0.2613535745247689;
        A(15, 20) = 2.206941780273716;
        A(15, 21) = 0.8327026261824971;
        A(15, 22) = 0.068282876285328;
        A(15, 23) = -1.067227586406148;
        A(15, 24) = 0.38483671104932;
        A(15, 25) = -0.7198499884927266;
        A(15, 26) = 0.7405883763147995;
        A(15, 27) = -0.1385569144671314;
        A(15, 28) = 0.5732696135497034;
        A(15, 29) = -1.203165480217646;
        A(15, 30) = 0.3568935736308342;
        A(15, 31) = 0.4123236098421528;
        A(15, 32) = -0.485429912933834;
        A(15, 33) = -1.073589662198638;
        A(15, 34) = 0.06306776231517594;
        A(15, 35) = 0.9455344035311561;
        A(15, 36) = 0.01952532869063387;
        A(15, 37) = -0.1301817898361825;
        A(15, 38) = 0.3430718953097332;
        A(15, 39) = 0.9591028510251232;
        A(15, 40) = -0.06189622448466621;
        A(15, 41) = 0.5950981890409224;
        A(15, 42) = -0.1695032450465809;
        A(15, 43) = -0.2172799793659299;
        A(15, 44) = -0.7773896379294052;
        A(15, 45) = 0.857774029740235;
        A(15, 46) = -0.9433078612441848;
        A(15, 47) = 0.6660867232793248;
        A(15, 48) = -1.096895674231124;
        A(15, 49) = -0.8673450105427263;
        A(15, 50) = 0.7694236475205142;
        A(15, 51) = 0.6139679361084099;
        A(15, 52) = 0.6484009736088759;
        A(15, 53) = 1.210333709205679;
        A(15, 54) = -2.779240904857647;
        A(15, 55) = -1.462815251487022;
        A(15, 56) = 1.781083527613091;
        A(15, 57) = 2.164747593890104;
        A(15, 58) = 0.3624326753671689;
        A(15, 59) = 1.132041307929445;
        A(15, 60) = 0.9852320767949404;
        A(15, 61) = 0.1699080718041306;
        A(15, 62) = 0.6447048480977238;
        A(15, 63) = -1.269660347740418;
        A(16, 0) = 0.3207277993458489;
        A(16, 1) = 1.376060422684961;
        A(16, 2) = 0.8438224416316397;
        A(16, 3) = 1.470938809427927;
        A(16, 4) = 0.1323854028006551;
        A(16, 5) = 0.5169710282342804;
        A(16, 6) = -0.2815959302514933;
        A(16, 7) = 0.5145192935968799;
        A(16, 8) = 1.467200522496165;
        A(16, 9) = 0.3587854956332099;
        A(16, 10) = 1.155717182804529;
        A(16, 11) = 1.869256859073442;
        A(16, 12) = 1.248319480877331;
        A(16, 13) = 1.452561957668774;
        A(16, 14) = 1.032246373642381;
        A(16, 15) = 0.07835159952372053;
        A(16, 16) = -0.2395853287373267;
        A(16, 17) = -1.903668638941256;
        A(16, 18) = -1.932664073589798;
        A(16, 19) = 0.9256300959984964;
        A(16, 20) = -1.182117061495755;
        A(16, 21) = -1.446111236241075;
        A(16, 22) = 0.3390374257755131;
        A(16, 23) = -0.4494365657264196;
        A(16, 24) = 0.1279145507538775;
        A(16, 25) = 0.4567557225277256;
        A(16, 26) = -0.7493268665953018;
        A(16, 27) = -0.5505426413816571;
        A(16, 28) = 0.1733257050568087;
        A(16, 29) = 1.05683774357112;
        A(16, 30) = 1.46912588992287;
        A(16, 31) = -0.07297995996596593;
        A(16, 32) = -1.412621285556534;
        A(16, 33) = 0.8224590356851858;
        A(16, 34) = 1.380881586238668;
        A(16, 35) = -0.2410218058690119;
        A(16, 36) = -1.284809438281624;
        A(16, 37) = 1.568008570239559;
        A(16, 38) = 0.2470780514531021;
        A(16, 39) = -0.3967985951945935;
        A(16, 40) = -0.4477674152984991;
        A(16, 41) = -0.6754732581672273;
        A(16, 42) = -0.7957056837577836;
        A(16, 43) = 0.3990396875309453;
        A(16, 44) = -0.2104729336202157;
        A(16, 45) = 1.137092254578229;
        A(16, 46) = 1.075977790536481;
        A(16, 47) = 1.216943073913638;
        A(16, 48) = 1.242510363554079;
        A(16, 49) = 0.4222667297663006;
        A(16, 50) = 1.190497758275268;
        A(16, 51) = 0.3693631235121102;
        A(16, 52) = -2.372917933739931;
        A(16, 53) = 0.3859453152315861;
        A(16, 54) = 0.1042881907762749;
        A(16, 55) = 1.705200187344074;
        A(16, 56) = 2.386229742380419;
        A(16, 57) = -0.6819537626619262;
        A(16, 58) = -0.7011679454639749;
        A(16, 59) = -0.540399226848198;
        A(16, 60) = 0.1592045279471424;
        A(16, 61) = -0.07034154557187104;
        A(16, 62) = 0.09004158801272982;
        A(16, 63) = 2.188985529160625;
        A(17, 0) = 1.299356869301176;
        A(17, 1) = -0.6662090012233732;
        A(17, 2) = 0.6376660515770116;
        A(17, 3) = 1.378273299838068;
        A(17, 4) = -0.1888517989171498;
        A(17, 5) = -1.266094688504092;
        A(17, 6) = -0.2343077268745587;
        A(17, 7) = 0.8402062735199516;
        A(17, 8) = 0.1531699454797562;
        A(17, 9) = 0.2933848732804216;
        A(17, 10) = -0.9209165571744223;
        A(17, 11) = 0.1981278572786056;
        A(17, 12) = 0.5236510073705284;
        A(17, 13) = 0.8410583239455554;
        A(17, 14) = -0.5665904858769175;
        A(17, 15) = 0.6259621872437292;
        A(17, 16) = 2.471282731118149;
        A(17, 17) = 0.7718250477688629;
        A(17, 18) = -0.6846236783635059;
        A(17, 19) = -1.972847519328608;
        A(17, 20) = -1.295881783305122;
        A(17, 21) = -0.7470957556259077;
        A(17, 22) = 0.505905515946226;
        A(17, 23) = -0.5855166192998506;
        A(17, 24) = 0.3804793089786037;
        A(17, 25) = 0.1556488458892625;
        A(17, 26) = 0.3614723017029961;
        A(17, 27) = -1.183704451097797;
        A(17, 28) = -1.476382982078889;
        A(17, 29) = 0.6709779434017484;
        A(17, 30) = 0.543222511178859;
        A(17, 31) = 0.02547010253764802;
        A(17, 32) = 0.5154958365953741;
        A(17, 33) = 0.02465806795860391;
        A(17, 34) = -0.1138275020732988;
        A(17, 35) = 0.9583566787486133;
        A(17, 36) = 0.5888752518189777;
        A(17, 37) = 1.179700539768146;
        A(17, 38) = -0.2256800239545257;
        A(17, 39) = 1.010738432994925;
        A(17, 40) = -0.1330059970187981;
        A(17, 41) = 0.3895155905542475;
        A(17, 42) = 0.7026476168153719;
        A(17, 43) = 0.8171893052479304;
        A(17, 44) = 0.6832695474463344;
        A(17, 45) = -0.677286671149189;
        A(17, 46) = 0.3794343904660872;
        A(17, 47) = -0.7419746699372327;
        A(17, 48) = 1.091683273059807;
        A(17, 49) = -2.13388127033015;
        A(17, 50) = 0.6295362409210717;
        A(17, 51) = 1.200023321809109;
        A(17, 52) = 0.8617021868471186;
        A(17, 53) = -0.3515517046092549;
        A(17, 54) = -0.4567999199246062;
        A(17, 55) = -1.013504780105621;
        A(17, 56) = 0.1181294803382046;
        A(17, 57) = -0.9864921938858793;
        A(17, 58) = -0.7309891297135731;
        A(17, 59) = -0.3566113175620845;
        A(17, 60) = 0.5433601494506299;
        A(17, 61) = -0.1326976163101934;
        A(17, 62) = 0.8839538862991055;
        A(17, 63) = -0.272954724426387;
        A(18, 0) = -1.049280388286974;
        A(18, 1) = -0.3167472054154024;
        A(18, 2) = -0.6161205199875934;
        A(18, 3) = 0.7295568411866894;
        A(18, 4) = -1.561035149485165;
        A(18, 5) = -0.3494726106827412;
        A(18, 6) = -0.451617270454;
        A(18, 7) = -0.07590245288336163;
        A(18, 8) = 0.1125455325934196;
        A(18, 9) = 0.2951066691169858;
        A(18, 10) = 0.6894547164929825;
        A(18, 11) = -0.7663531383886449;
        A(18, 12) = -0.708047388763361;
        A(18, 13) = -0.557601577441867;
        A(18, 14) = 1.098869062951255;
        A(18, 15) = 0.2843247771817947;
        A(18, 16) = -0.7005033315121096;
        A(18, 17) = -0.999377146050368;
        A(18, 18) = 0.2009331531985844;
        A(18, 19) = -0.1610344338302581;
        A(18, 20) = 0.5556289596361562;
        A(18, 21) = 2.116843231871048;
        A(18, 22) = 1.324135414697219;
        A(18, 23) = 1.849454807866492;
        A(18, 24) = 0.7888270522382038;
        A(18, 25) = -0.1181061921808727;
        A(18, 26) = -0.3102818478504696;
        A(18, 27) = -0.6375156691775805;
        A(18, 28) = 1.438733661638524;
        A(18, 29) = -0.01732581132216857;
        A(18, 30) = -1.355013197865509;
        A(18, 31) = -0.02154843677205005;
        A(18, 32) = 1.232474309165077;
        A(18, 33) = -0.7964561184647285;
        A(18, 34) = -0.5827282333299167;
        A(18, 35) = -0.07421953825509207;
        A(18, 36) = 2.280042997315957;
        A(18, 37) = 0.7882576974284378;
        A(18, 38) = 1.133787361664392;
        A(18, 39) = 0.9183742458867016;
        A(18, 40) = -1.270444782040769;
        A(18, 41) = -1.057658827192271;
        A(18, 42) = 0.3998742086705055;
        A(18, 43) = 0.2458366744162009;
        A(18, 44) = 0.2526355462420011;
        A(18, 45) = -0.3833415570830625;
        A(18, 46) = -1.351580727218303;
        A(18, 47) = 0.02810825244443387;
        A(18, 48) = -0.08976615237000415;
        A(18, 49) = -0.6213276482806092;
        A(18, 50) = -0.2348301825931859;
        A(18, 51) = -0.5187790631355878;
        A(18, 52) = -0.165154168095633;
        A(18, 53) = -0.4861521549335836;
        A(18, 54) = -0.0556452586445253;
        A(18, 55) = 0.7730214199726013;
        A(18, 56) = 0.6254152257082883;
        A(18, 57) = -1.902169292706553;
        A(18, 58) = 1.13900359663899;
        A(18, 59) = 0.5343385071775383;
        A(18, 60) = -0.05440941283841858;
        A(18, 61) = -0.2856825428388395;
        A(18, 62) = -0.3190374496075237;
        A(18, 63) = -1.763195386657731;
        A(19, 0) = -0.1447230587918676;
        A(19, 1) = -1.082319629461366;
        A(19, 2) = 0.5728987481500086;
        A(19, 3) = 1.009843169979766;
        A(19, 4) = 0.8412753603726555;
        A(19, 5) = -0.05556769045141217;
        A(19, 6) = 0.5313719469794596;
        A(19, 7) = 0.159153614981141;
        A(19, 8) = -1.562531641502883;
        A(19, 9) = -0.9248694724052538;
        A(19, 10) = -0.1615989894329072;
        A(19, 11) = -1.183658226512254;
        A(19, 12) = 0.5246576433542112;
        A(19, 13) = 0.03283266662364206;
        A(19, 14) = -1.808885601526254;
        A(19, 15) = -1.041745275905832;
        A(19, 16) = 0.04764016258002891;
        A(19, 17) = 0.8879564551225977;
        A(19, 18) = 0.1310265327854234;
        A(19, 19) = 1.780616183475125;
        A(19, 20) = 0.3896038643592771;
        A(19, 21) = -0.1110445196972953;
        A(19, 22) = -0.9198987237341888;
        A(19, 23) = 0.8743486315327034;
        A(19, 24) = 0.5444941288565122;
        A(19, 25) = -2.769094655339183;
        A(19, 26) = 0.3101224765410934;
        A(19, 27) = 1.201117907420153;
        A(19, 28) = 1.402413744720443;
        A(19, 29) = -0.3192278998764729;
        A(19, 30) = -0.7795094798593759;
        A(19, 31) = 1.523131887916028;
        A(19, 32) = -1.538239181347353;
        A(19, 33) = 0.6494691995977712;
        A(19, 34) = 0.3642951824584554;
        A(19, 35) = 1.098347659990579;
        A(19, 36) = -0.4497684347132306;
        A(19, 37) = 1.399924542788678;
        A(19, 38) = 0.601511361769304;
        A(19, 39) = 0.7126427066698063;
        A(19, 40) = 0.7232926664084303;
        A(19, 41) = 0.7401039262324454;
        A(19, 42) = 0.1860903078153098;
        A(19, 43) = 1.308684251372512;
        A(19, 44) = 0.8500253960645753;
        A(19, 45) = 0.156388984556892;
        A(19, 46) = -0.1579452251182275;
        A(19, 47) = -0.6008491858958682;
        A(19, 48) = -0.225412667076567;
        A(19, 49) = 0.4924764294352691;
        A(19, 50) = 0.5096922090641104;
        A(19, 51) = -1.251103906633309;
        A(19, 52) = 0.2643468034060572;
        A(19, 53) = 2.180416769567206;
        A(19, 54) = -0.5488036503182342;
        A(19, 55) = 0.7311656801319572;
        A(19, 56) = 0.4306132523758431;
        A(19, 57) = -2.497606124617596;
        A(19, 58) = 1.312508924284509;
        A(19, 59) = -0.7812836888837403;
        A(19, 60) = 0.9707818838393488;
        A(19, 61) = 0.008639204081387207;
        A(19, 62) = -0.09895283797010455;
        A(19, 63) = 0.9952555435357486;
        A(20, 0) = 0.6707091244255002;
        A(20, 1) = -1.771521601697502;
        A(20, 2) = 0.5824827639007556;
        A(20, 3) = 1.307165433262584;
        A(20, 4) = 2.039683949753995;
        A(20, 5) = -0.5988998132151934;
        A(20, 6) = -0.6859609250879523;
        A(20, 7) = -1.242263795156991;
        A(20, 8) = 1.39739674753594;
        A(20, 9) = 1.384149859022851;
        A(20, 10) = 1.118483916304244;
        A(20, 11) = -1.291233453968434;
        A(20, 12) = 0.9502174154601171;
        A(20, 13) = -1.026989416118589;
        A(20, 14) = -1.225819339196707;
        A(20, 15) = -2.017725184844413;
        A(20, 16) = -0.6510050488297097;
        A(20, 17) = -1.408486358798831;
        A(20, 18) = -0.6745953746595096;
        A(20, 19) = -1.280934971510577;
        A(20, 20) = 1.756107929803646;
        A(20, 21) = 0.8253115292068479;
        A(20, 22) = -0.8881304300519393;
        A(20, 23) = 0.8528955122356724;
        A(20, 24) = -0.8433222803328526;
        A(20, 25) = -1.476701512438963;
        A(20, 26) = 0.5256756225866933;
        A(20, 27) = -0.8349603863147876;
        A(20, 28) = 0.4764685902279059;
        A(20, 29) = -0.8741615619771875;
        A(20, 30) = 1.025204107048679;
        A(20, 31) = 0.01647786266548999;
        A(20, 32) = 0.7309904270200848;
        A(20, 33) = 0.5962457213227541;
        A(20, 34) = 0.498199939028321;
        A(20, 35) = 0.513976190372452;
        A(20, 36) = -0.03476633668848317;
        A(20, 37) = -1.06912232571106;
        A(20, 38) = 0.8882729078567266;
        A(20, 39) = 0.5252719313174158;
        A(20, 40) = -2.186097529906519;
        A(20, 41) = -0.9133255709191438;
        A(20, 42) = -1.174862597510488;
        A(20, 43) = -1.021435430020475;
        A(20, 44) = 1.647972657244131;
        A(20, 45) = -1.248286237704669;
        A(20, 46) = 1.407445949912479;
        A(20, 47) = 1.996971035233727;
        A(20, 48) = -0.1459718004547665;
        A(20, 49) = -0.3035201023400398;
        A(20, 50) = 1.24278277301886;
        A(20, 51) = -1.714240598978482;
        A(20, 52) = 0.891369997252053;
        A(20, 53) = -1.903894937713268;
        A(20, 54) = 1.241349957913424;
        A(20, 55) = -0.326200304745942;
        A(20, 56) = -0.296909363612946;
        A(20, 57) = 0.7609099883947542;
        A(20, 58) = 0.4705555127828185;
        A(20, 59) = 0.6810510237211159;
        A(20, 60) = 0.6150047962857246;
        A(20, 61) = 0.834718812130855;
        A(20, 62) = -1.047023727639636;
        A(20, 63) = 1.920441910581215;
        A(21, 0) = 0.01312773387816915;
        A(21, 1) = 1.255240425526064;
        A(21, 2) = 2.302080339062968;
        A(21, 3) = -1.668712406405302;
        A(21, 4) = 1.686212679185684;
        A(21, 5) = -0.8347961319680564;
        A(21, 6) = -0.3551610547221547;
        A(21, 7) = -0.3521546099609333;
        A(21, 8) = -0.6075254409136255;
        A(21, 9) = -0.917049802404859;
        A(21, 10) = -0.2857344747215236;
        A(21, 11) = -1.624709635717209;
        A(21, 12) = -0.160660030151431;
        A(21, 13) = 0.2404067350174036;
        A(21, 14) = -0.3384966166901625;
        A(21, 15) = -0.1709350562407352;
        A(21, 16) = 0.02529018175598196;
        A(21, 17) = 0.3967686064776685;
        A(21, 18) = 0.8862768637959926;
        A(21, 19) = 1.076549292221753;
        A(21, 20) = 0.0181058942813506;
        A(21, 21) = -0.0765755130406222;
        A(21, 22) = 1.762051861315364;
        A(21, 23) = -1.220026404640004;
        A(21, 24) = 1.080287872149704;
        A(21, 25) = -2.232192917192815;
        A(21, 26) = -0.5392228538347076;
        A(21, 27) = -0.002088956169105686;
        A(21, 28) = -1.158270148994606;
        A(21, 29) = -0.3941129274714312;
        A(21, 30) = 0.3981120074884456;
        A(21, 31) = 0.9096765291247124;
        A(21, 32) = 0.1222553073013505;
        A(21, 33) = -1.573614271991227;
        A(21, 34) = 0.3435253772959386;
        A(21, 35) = -0.6369967922241335;
        A(21, 36) = -1.585538833251739;
        A(21, 37) = 0.5667015022431166;
        A(21, 38) = 0.3062051259292891;
        A(21, 39) = 0.5095620037737398;
        A(21, 40) = -0.4360940619854841;
        A(21, 41) = -0.7266426858207484;
        A(21, 42) = 1.123681829422702;
        A(21, 43) = -0.3914628741889172;
        A(21, 44) = -0.2272783859932919;
        A(21, 45) = -2.014149471799019;
        A(21, 46) = 1.227319580975065;
        A(21, 47) = 0.131963523420057;
        A(21, 48) = -0.2841047049896897;
        A(21, 49) = -0.5116349280472858;
        A(21, 50) = -1.201504600587476;
        A(21, 51) = 0.6175167843868297;
        A(21, 52) = -2.419234112854629;
        A(21, 53) = 2.393376231481213;
        A(21, 54) = 0.01158365873465993;
        A(21, 55) = 1.272846453655518;
        A(21, 56) = -0.7668756661075279;
        A(21, 57) = -0.2405605197746237;
        A(21, 58) = -0.2783537451645717;
        A(21, 59) = -1.178134371648747;
        A(21, 60) = 0.6269734311449725;
        A(21, 61) = 1.654780792722046;
        A(21, 62) = -0.7353312357901691;
        A(21, 63) = 0.6705022400032857;
        A(22, 0) = 0.3582893723510124;
        A(22, 1) = -0.4982523641977431;
        A(22, 2) = -0.8516522123255708;
        A(22, 3) = 2.669961596207008;
        A(22, 4) = 2.050925788045772;
        A(22, 5) = -0.9130875944668251;
        A(22, 6) = -1.126549646569604;
        A(22, 7) = 0.4304733932271891;
        A(22, 8) = -0.5991392752113306;
        A(22, 9) = 1.123637868846699;
        A(22, 10) = -1.060452255332401;
        A(22, 11) = 1.930803433519195;
        A(22, 12) = 0.3636714130155719;
        A(22, 13) = 2.193981697655806;
        A(22, 14) = -0.7909756305932743;
        A(22, 15) = -2.108274756070689;
        A(22, 16) = -0.3277003356010174;
        A(22, 17) = 0.2316335369793465;
        A(22, 18) = 0.8552853596159504;
        A(22, 19) = 0.621654054611381;
        A(22, 20) = -0.3890522498877568;
        A(22, 21) = 0.3402017048193503;
        A(22, 22) = -1.389889289898235;
        A(22, 23) = 1.349176363895809;
        A(22, 24) = 0.1022652380211584;
        A(22, 25) = 0.0719213061193478;
        A(22, 26) = 0.34670219953479;
        A(22, 27) = 1.000987250783701;
        A(22, 28) = -0.2790388596747666;
        A(22, 29) = 0.6348482115955367;
        A(22, 30) = -0.3929688864578911;
        A(22, 31) = -0.5265464423138652;
        A(22, 32) = -1.308117694808687;
        A(22, 33) = 0.2744094084665677;
        A(22, 34) = 0.7616811859032433;
        A(22, 35) = -1.299813614052154;
        A(22, 36) = -0.3660104293112121;
        A(22, 37) = 1.562823262594358;
        A(22, 38) = -1.899903631343594;
        A(22, 39) = 0.7092076777331279;
        A(22, 40) = 0.7252721708777914;
        A(22, 41) = 1.154202020132607;
        A(22, 42) = -0.259764295980754;
        A(22, 43) = 0.4458983691030095;
        A(22, 44) = -1.650288792735692;
        A(22, 45) = 0.6052489015133866;
        A(22, 46) = -0.5866446487463987;
        A(22, 47) = 2.312412148235806;
        A(22, 48) = 0.3544697150638939;
        A(22, 49) = -0.05435468274746231;
        A(22, 50) = -0.5761469613668331;
        A(22, 51) = -2.175677824124108;
        A(22, 52) = 0.08413548645216665;
        A(22, 53) = 1.038520165468715;
        A(22, 54) = 1.112376982312994;
        A(22, 55) = 0.9986091672381179;
        A(22, 56) = 0.4950312124116866;
        A(22, 57) = -0.990429745934672;
        A(22, 58) = -1.282732510198892;
        A(22, 59) = -0.6358189499894007;
        A(22, 60) = 0.2624575912283815;
        A(22, 61) = -0.184500859528184;
        A(22, 62) = 0.08239580319488378;
        A(22, 63) = 1.540241129888579;
        A(23, 0) = 0.979026223730317;
        A(23, 1) = 0.8106357746673443;
        A(23, 2) = 1.406888847824083;
        A(23, 3) = 1.290533364843277;
        A(23, 4) = 0.6172438447305821;
        A(23, 5) = 0.0118766913985442;
        A(23, 6) = 0.2813498438890229;
        A(23, 7) = 0.2556350441940437;
        A(23, 8) = -0.7884712931548025;
        A(23, 9) = 1.997286611332841;
        A(23, 10) = 0.8166065873219469;
        A(23, 11) = 0.3184285938661053;
        A(23, 12) = 1.169956146437959;
        A(23, 13) = -0.5810123396835504;
        A(23, 14) = 0.4024964690289991;
        A(23, 15) = 2.191486077186675;
        A(23, 16) = -0.5072185808385374;
        A(23, 17) = -0.4816898512035593;
        A(23, 18) = -0.6717749215171147;
        A(23, 19) = -0.1284196590704351;
        A(23, 20) = -1.386143370385465;
        A(23, 21) = -1.000326496204175;
        A(23, 22) = -1.518519423449922;
        A(23, 23) = -0.9797196568706559;
        A(23, 24) = 0.3480575585512166;
        A(23, 25) = 1.167788784982865;
        A(23, 26) = -0.6210294041122252;
        A(23, 27) = 0.7828913000840978;
        A(23, 28) = 0.5482168448902136;
        A(23, 29) = 0.2341015019379585;
        A(23, 30) = -1.269326327303646;
        A(23, 31) = 1.430747621520462;
        A(23, 32) = 0.008249493134789131;
        A(23, 33) = 0.5234906697186048;
        A(23, 34) = 0.8247604343949184;
        A(23, 35) = 0.3979620060195382;
        A(23, 36) = 0.344472563335566;
        A(23, 37) = 1.661215529654211;
        A(23, 38) = 0.5991641578430595;
        A(23, 39) = -1.194517812250319;
        A(23, 40) = 1.398682683316965;
        A(23, 41) = 0.5155794099985669;
        A(23, 42) = -0.2737681773489762;
        A(23, 43) = 0.8879810876365629;
        A(23, 44) = -0.126975914109156;
        A(23, 45) = -0.1312153541876674;
        A(23, 46) = 0.2717899233531129;
        A(23, 47) = 1.261508829850632;
        A(23, 48) = -2.898417529921678;
        A(23, 49) = 2.265254024753383;
        A(23, 50) = -0.1416039546462801;
        A(23, 51) = -1.402953918174573;
        A(23, 52) = -0.9484710600257691;
        A(23, 53) = 2.47424204688702;
        A(23, 54) = -0.3959077678102141;
        A(23, 55) = 1.341897481411155;
        A(23, 56) = -1.16646075246072;
        A(23, 57) = 0.7201999484560908;
        A(23, 58) = 1.014831891745148;
        A(23, 59) = 1.223915623553173;
        A(23, 60) = 2.054169541015211;
        A(23, 61) = 0.6138437830624632;
        A(23, 62) = -0.5444227806061633;
        A(23, 63) = 0.354682065394093;
        A(24, 0) = 0.03691989912325526;
        A(24, 1) = 0.1994423254786603;
        A(24, 2) = -0.1718275104494613;
        A(24, 3) = 0.03933571550240817;
        A(24, 4) = -0.006022207858259538;
        A(24, 5) = 2.720575476684702;
        A(24, 6) = -0.439497610605433;
        A(24, 7) = 0.7840870004000672;
        A(24, 8) = -0.6031163067466393;
        A(24, 9) = 0.1439718324656387;
        A(24, 10) = 2.707154766719272;
        A(24, 11) = -2.403094550281141;
        A(24, 12) = -2.409594281824195;
        A(24, 13) = 0.9742471723724829;
        A(24, 14) = -0.4319867358492846;
        A(24, 15) = -1.118397006421621;
        A(24, 16) = 1.780597711886952;
        A(24, 17) = 0.2807436371603846;
        A(24, 18) = -1.827242568446102;
        A(24, 19) = -0.5517461832784401;
        A(24, 20) = 1.721446525805026;
        A(24, 21) = -0.5532779673785071;
        A(24, 22) = 0.2870033673779083;
        A(24, 23) = -0.8457283753362441;
        A(24, 24) = 1.253949743453914;
        A(24, 25) = 0.1313561224745704;
        A(24, 26) = 1.80271126813167;
        A(24, 27) = -2.360617730233994;
        A(24, 28) = 0.2909207416378284;
        A(24, 29) = -0.9797990026884936;
        A(24, 30) = 0.5000363042662829;
        A(24, 31) = -0.9620858251474863;
        A(24, 32) = 0.9247001433700895;
        A(24, 33) = -0.4831111956753482;
        A(24, 34) = -1.436528699759962;
        A(24, 35) = 0.1179670216428169;
        A(24, 36) = -0.2442378297043674;
        A(24, 37) = -0.1297712321301008;
        A(24, 38) = 0.8464639359108441;
        A(24, 39) = -1.016937804228921;
        A(24, 40) = 0.5184431521136625;
        A(24, 41) = 0.4659450415004182;
        A(24, 42) = -1.717436757594219;
        A(24, 43) = 0.5105955297394806;
        A(24, 44) = 0.09746254204000565;
        A(24, 45) = 0.1766757543820718;
        A(24, 46) = 1.113729449101763;
        A(24, 47) = 0.8010182136053613;
        A(24, 48) = 1.905851728989641;
        A(24, 49) = -0.03017071876792291;
        A(24, 50) = -0.5482711665970961;
        A(24, 51) = -0.418899998377051;
        A(24, 52) = -0.1138466655960242;
        A(24, 53) = -0.8886011131055839;
        A(24, 54) = 0.7288882710164366;
        A(24, 55) = 0.2139634371315466;
        A(24, 56) = 0.3387148225165162;
        A(24, 57) = -0.3016538935722921;
        A(24, 58) = -0.1814791559571324;
        A(24, 59) = 0.3052089202324029;
        A(24, 60) = 0.4696823834011722;
        A(24, 61) = 1.460261037683607;
        A(24, 62) = 1.691443343008102;
        A(24, 63) = -1.085146871591086;
        A(25, 0) = 0.9024028853750432;
        A(25, 1) = -1.414315214880239;
        A(25, 2) = -1.207600039603135;
        A(25, 3) = 0.4060108271000659;
        A(25, 4) = 0.161088323363818;
        A(25, 5) = 2.868395240758029;
        A(25, 6) = 0.3717122549849486;
        A(25, 7) = -1.514541904319216;
        A(25, 8) = 1.375296485452048;
        A(25, 9) = -2.526742913260118;
        A(25, 10) = 0.3031690496679482;
        A(25, 11) = -2.625790906995985;
        A(25, 12) = 0.06205375549615918;
        A(25, 13) = 0.301983984832861;
        A(25, 14) = -1.166765008406818;
        A(25, 15) = -0.2385183040972884;
        A(25, 16) = -1.332571994350307;
        A(25, 17) = -1.172855733283838;
        A(25, 18) = -0.4509366547231412;
        A(25, 19) = 1.850788611648308;
        A(25, 20) = 0.3477050612502675;
        A(25, 21) = -0.6111648702179138;
        A(25, 22) = -1.217354205211618;
        A(25, 23) = 1.038681483444071;
        A(25, 24) = -0.004469716054318891;
        A(25, 25) = -0.366982710257819;
        A(25, 26) = -0.2745319528307179;
        A(25, 27) = 1.680452839711562;
        A(25, 28) = -1.186576062458578;
        A(25, 29) = 0.6890448265970862;
        A(25, 30) = -1.619762852926832;
        A(25, 31) = 0.2046578287835967;
        A(25, 32) = 0.4759126172131512;
        A(25, 33) = -1.088986421935387;
        A(25, 34) = 0.5446690180068113;
        A(25, 35) = -0.7633604867691701;
        A(25, 36) = -0.4310342532535366;
        A(25, 37) = 1.101247636056101;
        A(25, 38) = 0.3619736394143817;
        A(25, 39) = -0.8885306083578749;
        A(25, 40) = 0.9781164802870236;
        A(25, 41) = 0.4012292995707085;
        A(25, 42) = -0.03369897613614391;
        A(25, 43) = 2.218769988655355;
        A(25, 44) = 0.6037537942989129;
        A(25, 45) = -0.9236237864002735;
        A(25, 46) = 0.1132867675349507;
        A(25, 47) = 0.1508046716660553;
        A(25, 48) = 1.970791902848634;
        A(25, 49) = -1.017285066036884;
        A(25, 50) = -0.7268705969518116;
        A(25, 51) = -0.56483555168519;
        A(25, 52) = -1.855814628442383;
        A(25, 53) = -0.3779491381172651;
        A(25, 54) = 2.069852155743848;
        A(25, 55) = 1.580622959856723;
        A(25, 56) = 1.395676798162177;
        A(25, 57) = 0.2971439421239423;
        A(25, 58) = 0.7227478965839078;
        A(25, 59) = 0.1525789870093906;
        A(25, 60) = 0.461993728068077;
        A(25, 61) = 1.423816049721731;
        A(25, 62) = -1.431845550570695;
        A(25, 63) = 0.9229050569930528;
        A(26, 0) = 0.02609394019934516;
        A(26, 1) = 0.07791479694627;
        A(26, 2) = -0.5929763502506263;
        A(26, 3) = 0.07225315836326193;
        A(26, 4) = 3.525844281496972;
        A(26, 5) = 1.2622401047734;
        A(26, 6) = 1.322421157233274;
        A(26, 7) = 2.215255897752826;
        A(26, 8) = 0.5029060034876366;
        A(26, 9) = -0.8321911119361927;
        A(26, 10) = -0.367112777946757;
        A(26, 11) = -0.2917178532181209;
        A(26, 12) = -0.6239402121499655;
        A(26, 13) = -1.155880662858894;
        A(26, 14) = -0.185993927918082;
        A(26, 15) = -0.01365196236734064;
        A(26, 16) = 0.153876300568553;
        A(26, 17) = 0.7273172823262631;
        A(26, 18) = -0.8029244562552331;
        A(26, 19) = -0.1170891883158856;
        A(26, 20) = 0.4661264886735688;
        A(26, 21) = -0.8829361192244355;
        A(26, 22) = 0.3912000903605619;
        A(26, 23) = -0.6372788650095568;
        A(26, 24) = -0.2899559499723326;
        A(26, 25) = -0.4296432879082659;
        A(26, 26) = 0.1000342705901126;
        A(26, 27) = -2.480531477489399;
        A(26, 28) = -0.3840532443298878;
        A(26, 29) = -0.4366224278446555;
        A(26, 30) = -0.1842226659397504;
        A(26, 31) = -0.5973133957093814;
        A(26, 32) = 0.6970708606579983;
        A(26, 33) = 0.470225365454273;
        A(26, 34) = -1.067699548834856;
        A(26, 35) = -0.4464610196190129;
        A(26, 36) = -0.04984478230852933;
        A(26, 37) = -0.9097091177479827;
        A(26, 38) = -2.557301432358045;
        A(26, 39) = -0.07900485125503635;
        A(26, 40) = 1.255712208070094;
        A(26, 41) = 3.057517235211464;
        A(26, 42) = -0.4035862661899012;
        A(26, 43) = -0.6025885959268974;
        A(26, 44) = 0.6200176089485648;
        A(26, 45) = 0.6570324331259723;
        A(26, 46) = -0.465179174390646;
        A(26, 47) = -1.300302370149957;
        A(26, 48) = 0.4546061914649708;
        A(26, 49) = 1.127182300866769;
        A(26, 50) = -0.956645466352103;
        A(26, 51) = -1.260211308871584;
        A(26, 52) = 0.1219365529982226;
        A(26, 53) = -0.8108756570715682;
        A(26, 54) = 0.5887459198061662;
        A(26, 55) = 0.118286022655947;
        A(26, 56) = 0.7606975909060434;
        A(26, 57) = -0.8010475973444238;
        A(26, 58) = -1.956686019538606;
        A(26, 59) = -0.0105863088060766;
        A(26, 60) = -0.1241905632998308;
        A(26, 61) = 1.474858536929303;
        A(26, 62) = 0.8618404299950327;
        A(26, 63) = -1.433755407589862;
        A(27, 0) = -0.516349025761889;
        A(27, 1) = -0.9582231679662977;
        A(27, 2) = -0.6224459405156128;
        A(27, 3) = -0.3921589086898902;
        A(27, 4) = -0.4396102771883829;
        A(27, 5) = -0.601375089185037;
        A(27, 6) = 0.4765539219644238;
        A(27, 7) = 1.926293275660941;
        A(27, 8) = -0.7062070939939177;
        A(27, 9) = 2.588937857028264;
        A(27, 10) = -0.8620948090010725;
        A(27, 11) = -1.490017504080538;
        A(27, 12) = -1.391152423293958;
        A(27, 13) = 1.360082005839139;
        A(27, 14) = -1.687670347987389;
        A(27, 15) = -1.528262848313553;
        A(27, 16) = -2.014391657937645;
        A(27, 17) = 0.1670086632998819;
        A(27, 18) = -0.9795467761688957;
        A(27, 19) = -0.01752013590591731;
        A(27, 20) = -0.1818063760915284;
        A(27, 21) = 1.627859939540969;
        A(27, 22) = 0.01541798873815686;
        A(27, 23) = -1.624124271144562;
        A(27, 24) = -0.7679459253403701;
        A(27, 25) = 0.1424877120012613;
        A(27, 26) = 1.002273229926869;
        A(27, 27) = 1.418165033632953;
        A(27, 28) = 0.05785065883585979;
        A(27, 29) = 1.176959928890035;
        A(27, 30) = 1.642929117016319;
        A(27, 31) = -0.2429903944070973;
        A(27, 32) = 0.465137198889968;
        A(27, 33) = -0.9841549481068423;
        A(27, 34) = -1.376022476431812;
        A(27, 35) = 1.400069164205201;
        A(27, 36) = 0.1409222692251478;
        A(27, 37) = -0.6418481846122094;
        A(27, 38) = 1.363364336907177;
        A(27, 39) = -1.321243511201788;
        A(27, 40) = 0.8847792440347899;
        A(27, 41) = -0.2270216474946418;
        A(27, 42) = -1.963022237566713;
        A(27, 43) = 0.6463617919386884;
        A(27, 44) = 0.7387561898074022;
        A(27, 45) = 2.281187019759889;
        A(27, 46) = -0.5112039731153159;
        A(27, 47) = 1.289860827892325;
        A(27, 48) = 0.7702797812065823;
        A(27, 49) = -0.2886411579443238;
        A(27, 50) = 1.267231954441443;
        A(27, 51) = -0.03380884411750341;
        A(27, 52) = 0.4592120728395838;
        A(27, 53) = 1.007727328936236;
        A(27, 54) = -0.4271258189770338;
        A(27, 55) = -0.7201916917200162;
        A(27, 56) = 0.2391153542721428;
        A(27, 57) = 0.8582519954911532;
        A(27, 58) = 0.9173985111347197;
        A(27, 59) = -1.66888031240844;
        A(27, 60) = 1.003555511315594;
        A(27, 61) = 0.3742193309476131;
        A(27, 62) = -1.70286032468175;
        A(27, 63) = 1.749175942399696;
        A(28, 0) = -1.130108900236731;
        A(28, 1) = -0.8555540834664427;
        A(28, 2) = 0.6220427478443702;
        A(28, 3) = 0.2669049963381642;
        A(28, 4) = -0.7846291782016455;
        A(28, 5) = 0.745837349487163;
        A(28, 6) = 0.06279766441365707;
        A(28, 7) = 0.1693540808594893;
        A(28, 8) = -1.294574678933735;
        A(28, 9) = -0.9047081100483185;
        A(28, 10) = 0.08230720739678947;
        A(28, 11) = -1.550949477969435;
        A(28, 12) = 1.37972807678016;
        A(28, 13) = 0.3095231041678383;
        A(28, 14) = 0.8656572112883948;
        A(28, 15) = -0.6780805542010464;
        A(28, 16) = -0.3644464550416812;
        A(28, 17) = 0.6489328376511847;
        A(28, 18) = -0.1302509675278128;
        A(28, 19) = 1.261921705806301;
        A(28, 20) = 1.308183813451928;
        A(28, 21) = 1.723471718287453;
        A(28, 22) = -0.03268354190199029;
        A(28, 23) = -0.6492979252539395;
        A(28, 24) = 0.3581807736014893;
        A(28, 25) = -0.9712558385982174;
        A(28, 26) = -2.283055655000713;
        A(28, 27) = -0.2963966812912818;
        A(28, 28) = 0.4131659474560548;
        A(28, 29) = -1.419320075911733;
        A(28, 30) = 3.160951793722053;
        A(28, 31) = 0.0617722385976801;
        A(28, 32) = 1.183239865943045;
        A(28, 33) = 0.004455971132272741;
        A(28, 34) = 1.148800963982245;
        A(28, 35) = -0.4433551396618204;
        A(28, 36) = -0.502775698459574;
        A(28, 37) = 0.9370455018144678;
        A(28, 38) = -0.2808485079629703;
        A(28, 39) = -0.5490885870051411;
        A(28, 40) = 0.8043737204355997;
        A(28, 41) = 0.5261285834474233;
        A(28, 42) = -1.343337233509221;
        A(28, 43) = 0.4665156171122393;
        A(28, 44) = -1.081274569116233;
        A(28, 45) = -0.7256998167709964;
        A(28, 46) = 1.23281349638603;
        A(28, 47) = 2.36424355122925;
        A(28, 48) = -0.6627044723842506;
        A(28, 49) = 1.492195273459497;
        A(28, 50) = 0.3108232072185678;
        A(28, 51) = -1.353246858818123;
        A(28, 52) = 0.2416946858651968;
        A(28, 53) = -0.4518218593959149;
        A(28, 54) = -0.1863377583902383;
        A(28, 55) = 2.77374273788821;
        A(28, 56) = 1.453353138104914;
        A(28, 57) = -0.3543679296548252;
        A(28, 58) = -1.345307578954206;
        A(28, 59) = 0.2914892309882365;
        A(28, 60) = -1.009234546257347;
        A(28, 61) = -1.201183261592805;
        A(28, 62) = 0.1396480739504674;
        A(28, 63) = 0.0001580520441376145;
        A(29, 0) = -1.476277653195558;
        A(29, 1) = -1.232147982677682;
        A(29, 2) = 2.295492628334051;
        A(29, 3) = 0.1627772609206032;
        A(29, 4) = -1.150927499224313;
        A(29, 5) = -0.6421618917595376;
        A(29, 6) = 1.857723510624607;
        A(29, 7) = 0.9909588340403145;
        A(29, 8) = -1.032439683210113;
        A(29, 9) = 0.1638946112142855;
        A(29, 10) = -1.565772114002814;
        A(29, 11) = 1.185472107024419;
        A(29, 12) = -1.175349091591128;
        A(29, 13) = 0.9602970645534024;
        A(29, 14) = -0.1955990948119341;
        A(29, 15) = -0.2014609645297603;
        A(29, 16) = -0.09902170447189267;
        A(29, 17) = -0.5669460139981855;
        A(29, 18) = -0.2478676805485759;
        A(29, 19) = 0.5579863201711375;
        A(29, 20) = -1.328501528682123;
        A(29, 21) = -0.9902914455213396;
        A(29, 22) = -0.2195983149287429;
        A(29, 23) = -0.01321120938729149;
        A(29, 24) = -0.9746673019283206;
        A(29, 25) = -0.007163874180342236;
        A(29, 26) = 0.2979281808584803;
        A(29, 27) = 0.3564159510222097;
        A(29, 28) = 0.5456549814215048;
        A(29, 29) = -0.4051745197995077;
        A(29, 30) = 0.6288990750877115;
        A(29, 31) = 1.017827640245488;
        A(29, 32) = 0.02361511879004847;
        A(29, 33) = -0.5181378856021857;
        A(29, 34) = 1.119297962907194;
        A(29, 35) = 0.8059810716355857;
        A(29, 36) = -1.841412231137548;
        A(29, 37) = 1.271806823501531;
        A(29, 38) = 0.5855832811765923;
        A(29, 39) = 0.482565759249995;
        A(29, 40) = 0.7823178426460135;
        A(29, 41) = -0.9100790171503131;
        A(29, 42) = 0.1941845077222625;
        A(29, 43) = 1.080924431931728;
        A(29, 44) = 0.5331728733374628;
        A(29, 45) = -0.864024872952227;
        A(29, 46) = 0.1626688751568583;
        A(29, 47) = -0.1015798467379153;
        A(29, 48) = 1.961554634400853;
        A(29, 49) = 0.9235683220239875;
        A(29, 50) = 0.9782979738964061;
        A(29, 51) = -0.2796515974465982;
        A(29, 52) = -0.5245604328225693;
        A(29, 53) = -0.03648791557758385;
        A(29, 54) = 0.2551624881885273;
        A(29, 55) = -0.9719620141332975;
        A(29, 56) = 1.362780007535288;
        A(29, 57) = -1.896298718947816;
        A(29, 58) = 0.5912846341259587;
        A(29, 59) = -0.7703297690462404;
        A(29, 60) = -0.473127572570183;
        A(29, 61) = 0.7169590629344903;
        A(29, 62) = 1.139897419287395;
        A(29, 63) = -0.7391600307478958;
        A(30, 0) = 1.151142371876862;
        A(30, 1) = -0.8438059789040117;
        A(30, 2) = -1.313961585723616;
        A(30, 3) = -2.099338434954726;
        A(30, 4) = -1.26032113569874;
        A(30, 5) = -0.6408090444056586;
        A(30, 6) = -0.8658497978747625;
        A(30, 7) = -0.9590182560658538;
        A(30, 8) = -1.58772192617479;
        A(30, 9) = -1.772256113078475;
        A(30, 10) = -1.008770600518273;
        A(30, 11) = -0.7107772106347566;
        A(30, 12) = -1.214035018590188;
        A(30, 13) = -0.1108095106901146;
        A(30, 14) = 1.462240604354081;
        A(30, 15) = -1.133471083789827;
        A(30, 16) = -0.5444409850604384;
        A(30, 17) = 0.05433741286630977;
        A(30, 18) = 1.029515839037896;
        A(30, 19) = -0.4281889217962239;
        A(30, 20) = 0.578233752389274;
        A(30, 21) = -0.05526744672008403;
        A(30, 22) = -0.5536621103629115;
        A(30, 23) = -0.02705112199795951;
        A(30, 24) = -0.5018086367817929;
        A(30, 25) = -1.159803935382081;
        A(30, 26) = 0.591941758330929;
        A(30, 27) = -0.1643658399370364;
        A(30, 28) = -0.7127882260832;
        A(30, 29) = -1.322700767770379;
        A(30, 30) = -0.3700440776931771;
        A(30, 31) = 0.2543025876509431;
        A(30, 32) = -2.582898606321643;
        A(30, 33) = 0.9982113752312388;
        A(30, 34) = 1.24391542744844;
        A(30, 35) = -0.5842040182968918;
        A(30, 36) = -1.252647122689415;
        A(30, 37) = 0.9366840156585986;
        A(30, 38) = -0.7193305726855463;
        A(30, 39) = 1.892187640575866;
        A(30, 40) = 0.4835524326710725;
        A(30, 41) = 0.04888643916420993;
        A(30, 42) = 0.1105478490362804;
        A(30, 43) = -1.691269979704362;
        A(30, 44) = -0.566560325041217;
        A(30, 45) = -1.467392156604219;
        A(30, 46) = 0.3166644571065079;
        A(30, 47) = -0.7700098896550935;
        A(30, 48) = 2.031753420307275;
        A(30, 49) = 0.5766685550225877;
        A(30, 50) = -0.9393974867489182;
        A(30, 51) = -0.9913224021616643;
        A(30, 52) = -0.6456500277528799;
        A(30, 53) = -0.6382493201825784;
        A(30, 54) = -0.1513787409737867;
        A(30, 55) = 0.988925670458281;
        A(30, 56) = 1.720993338938634;
        A(30, 57) = -0.2999011182638746;
        A(30, 58) = -2.179483613451112;
        A(30, 59) = 0.9603281362022733;
        A(30, 60) = -0.3352948330629338;
        A(30, 61) = 0.4186602071649935;
        A(30, 62) = 1.453933629565421;
        A(30, 63) = 0.161635128759166;
        A(31, 0) = 1.374511450477159;
        A(31, 1) = 0.881101784131851;
        A(31, 2) = -1.448195440076689;
        A(31, 3) = 1.298817751109545;
        A(31, 4) = -0.1574898117653479;
        A(31, 5) = 0.7982131434075004;
        A(31, 6) = -0.3646421178916153;
        A(31, 7) = 1.203952815303725;
        A(31, 8) = 2.624914133846509;
        A(31, 9) = 0.7890248777397826;
        A(31, 10) = 0.27363671058845;
        A(31, 11) = 1.219345385941715;
        A(31, 12) = 0.4045476136991858;
        A(31, 13) = 0.2959576334498422;
        A(31, 14) = 1.861568639713207;
        A(31, 15) = -0.4885508364565987;
        A(31, 16) = 2.681524452732038;
        A(31, 17) = 0.01043578145798672;
        A(31, 18) = 2.042087489693576;
        A(31, 19) = 0.304072666466162;
        A(31, 20) = 0.8151167647037967;
        A(31, 21) = 1.257671440584185;
        A(31, 22) = 0.4431316362400069;
        A(31, 23) = 0.4871853692295148;
        A(31, 24) = -0.7120639731447598;
        A(31, 25) = 0.3385948113026957;
        A(31, 26) = -0.5176133952824265;
        A(31, 27) = -0.4060131100075348;
        A(31, 28) = 0.002041192230750734;
        A(31, 29) = -1.345579922611285;
        A(31, 30) = 1.095961635561515;
        A(31, 31) = -0.9900944894234357;
        A(31, 32) = 0.3684323111619496;
        A(31, 33) = 1.671653316362218;
        A(31, 34) = -1.800339642594652;
        A(31, 35) = -0.04782956065260512;
        A(31, 36) = -0.6303441842534072;
        A(31, 37) = -0.9663546122259339;
        A(31, 38) = 0.528118426952127;
        A(31, 39) = -0.2182611159795599;
        A(31, 40) = -0.5932714206949661;
        A(31, 41) = -0.5056277420886605;
        A(31, 42) = 0.09458867004853221;
        A(31, 43) = -0.414260651648777;
        A(31, 44) = 0.1742430640317544;
        A(31, 45) = -0.6588596371804216;
        A(31, 46) = 0.3301768827666451;
        A(31, 47) = 1.619891127989533;
        A(31, 48) = -0.2098999237166949;
        A(31, 49) = 0.5368153416283015;
        A(31, 50) = 0.3474803016541505;
        A(31, 51) = 0.0907312980372619;
        A(31, 52) = 1.047742540240497;
        A(31, 53) = 0.2294270222593558;
        A(31, 54) = 1.453738796236184;
        A(31, 55) = -0.8005474209025655;
        A(31, 56) = 1.350337041226638;
        A(31, 57) = -0.7590516114509082;
        A(31, 58) = 0.3135727159061249;
        A(31, 59) = 0.937821452196608;
        A(31, 60) = 0.1823604549646526;
        A(31, 61) = -0.6360820934145216;
        A(31, 62) = -1.438666609435195;
        A(31, 63) = -1.299647446501896;

        y[0]  = -2.037562919008439;
        y[1]  = -2.365326059504922;
        y[2]  =  5.128713204614584;
        y[3]  = -1.496719929355954;
        y[4]  = -0.1647246594251659;
        y[5]  =  0.6735816109616195;
        y[6]  =  6.929442644150667;
        y[7]  = -3.677424564909443;
        y[8]  = -1.793768131189025;
        y[9]  = -1.937794631206184;
        y[10] = -3.091410235007204;
        y[11] =  2.994921387924061;
        y[12] = -6.95113759150783;
        y[13] =  0.2569634385915862;
        y[14] =  1.741949434657935;
        y[15] =  3.390238164122583;
        y[16] = -1.426815368157929;
        y[17] =  1.109518163541706;
        y[18] = -3.300962619932516;
        y[19] = -5.834982630487295;
        y[20] = -2.263377682363473;
        y[21] = -3.205784177264004;
        y[22] = -1.231123247444592;
        y[23] = -2.719226154567583;
        y[24] =  2.87667153862011;
        y[25] =  1.236583428431698;
        y[26] =  6.797372974653632;
        y[27] = -2.23819495038825;
        y[28] = 1.41197671847391;
        y[29] = -3.425277168321983;
        y[30] =  0.804956190155619;
        y[31] = -2.281181012962092;


        klab::KRandom::Instance().setSeed(12345);        

        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > phi0 = new kl1p::TMatrixOperator<klab::DoubleReal>(A);

        // Normalize phi.
        klab::DoubleReal normFactor = 0.0;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col;
            phi0->column(i, col);
            normFactor += arma::dot(col, col);
        }
        klab::TSmartPointer<TOperator<klab::DoubleReal> > normOp = new TScalarOperator<klab::DoubleReal>(m, klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m)));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > phi = normOp * phi0;

        y *= klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m));


        TEMBPSolver<klab::DoubleReal> embp(1e-3, 200);
        embp.setNoiseVariance(1e-15);
        embp.setMessageDamping(0.5);
        embp.setLearningDamping(0.5);
        embp.enableDampingLearning(true);      
        embp.enableParameterLearning(true); 
        embp.enableHomogeneous(true);
        embp.enableHistory(true);

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 68.904403227093241, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00080400651692181710, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.00035489359772312252, 1e-6))
        TEST_ASSERT(iterations == 196)

        TEST_ASSERT(embp.history().size() == 197)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 2.2654861121193828, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 2.2771176477904622, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 1.9738388685261889, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 1.2215417904195904, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 1.6145574935295086, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 3.2943558504436039, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 1.7061442289019673, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 2.9441666686508672, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.91192336425941245, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 1.7667542540136141, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[196].residualNorm(), 0.00080400651692181710, 1e-6))

        // Limit cases.
        try                                         {embp.solve(arma::Col<klab::DoubleReal>(), phi, k, xr); TEST_ASSERT(false)}
        catch(KNullVectorEMBPSolverException&)      {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {embp.solve(y, klab::TSmartPointer<TOperator<klab::DoubleReal> >(0), k, xr); TEST_ASSERT(false)}
        catch(KNullOperatorEMBPSolverException&)    {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        embp.solve(y, phi, 0, xr);
        TEST_ASSERT(xr.n_rows == n)
        bool isZero = true;
        for(klab::UInt32 i=0; i<n && isZero; ++i)
            isZero = klab::Equals(xr[i], 0.0, 0.0);
        TEST_ASSERT(isZero)

        embp.setTolerance(1.0);
        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)
        snr          = klab::SNR(x, xr);
        residualNorm = embp.residualNorm();
        rrNorm       = embp.relativeResidualNorm();
        iterations   = embp.iterations();
        TEST_ASSERT(klab::Equals(snr, 3.2011201246120664, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.81451373978126329, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.35953155281948662, 1e-6))
        TEST_ASSERT(iterations == 4)
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_02()
{
    try
    {
        klab::UInt32 m = 32;    // Number of observations.
        klab::UInt32 n = 128;   // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        x.fill(0.0);
        x[6]   =  1.0;
        x[3]   = -1.0;
        x[105] = -1.0;
        x[21]  =  1.0;
        x[33]  = -1.0;

        klab::KRandom::Instance().setSeed(12345);

        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > phi0 = new TNormalRandomMatrixOperator<klab::DoubleReal>(m, n);

        // Normalize phi.
        klab::DoubleReal normFactor = 0.0;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col;
            phi0->column(i, col);
            normFactor += arma::dot(col, col);
        }
        klab::TSmartPointer<TOperator<klab::DoubleReal> > normOp = new TScalarOperator<klab::DoubleReal>(m, klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m)));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > phi = normOp * phi0;

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal> embp(1e-3, 200);
        embp.setNoiseVariance(1e-15);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(true);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(true);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

#if !defined(KLAB_UNIX_SYSTEM)          // To investigate.
    #if !defined(KLAB_64BITS_PLATFORM)  // To investigate.
        TEST_ASSERT(klab::Equals(snr, 60.207578946948090, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00097007332260543109, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.0010661796372861073, 1e-6))
        TEST_ASSERT(iterations == 112)

        TEST_ASSERT(embp.history().size() == 113)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 0.90985917258248450, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 0.91010686540620855, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 0.89069502535693801, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 0.86402978936356412, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 0.82323333753996875, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 0.69174439327182946, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 0.69799075468347405, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.90074715878528788, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.96572822734575103, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.77778781015863363, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[112].residualNorm(), 0.00097007332260543109, 1e-6))
    #else
/*
std::ofstream of("SolverOut.txt"); // Debug.
of<<"TEST_ASSERT(klab::Equals(snr, "<<std::setprecision(8)<<snr<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(residualNorm, "<<std::setprecision(8)<<residualNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(rrNorm, "<<std::setprecision(8)<<rrNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(iterations == "<<iterations<<")"<<std::endl;
of<<std::endl;
of<<"TEST_ASSERT(embp.history().size() == "<<(iterations+1)<<")"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), "<<std::setprecision(8)<<embp.history()[0].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), "<<std::setprecision(8)<<embp.history()[1].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), "<<std::setprecision(8)<<embp.history()[2].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), "<<std::setprecision(8)<<embp.history()[3].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), "<<std::setprecision(8)<<embp.history()[4].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), "<<std::setprecision(8)<<embp.history()[5].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), "<<std::setprecision(8)<<embp.history()[6].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), "<<std::setprecision(8)<<embp.history()[7].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), "<<std::setprecision(8)<<embp.history()[8].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), "<<std::setprecision(8)<<embp.history()[9].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()["<<iterations<<"].residualNorm(), "<<std::setprecision(8)<<embp.history()[iterations].residualNorm()<<", 1e-6))"<<std::endl;
of.flush();
*/ 
        TEST_ASSERT(klab::Equals(snr, 60.2076, 1e-4))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00097007281, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.0010661791, 1e-6))
        TEST_ASSERT(iterations == 112)

        TEST_ASSERT(embp.history().size() == 113)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 0.90985917, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 0.91010687, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 0.89069503, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 0.86402979, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 0.82323334, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 0.69174439, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 0.69799075, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.90074716, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.96572823, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.77778781, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[112].residualNorm(), 0.00097007281, 1e-8))
    #endif
#else
	#if !defined(KLAB_64BITS_PLATFORM)  // To investigate.
/*
std::ofstream of("SolverOut.txt"); // Debug.
of<<"TEST_ASSERT(klab::Equals(snr, "<<std::setprecision(8)<<snr<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(residualNorm, "<<std::setprecision(8)<<residualNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(rrNorm, "<<std::setprecision(8)<<rrNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(iterations == "<<iterations<<")"<<std::endl;
of<<std::endl;
of<<"TEST_ASSERT(embp.history().size() == "<<(iterations+1)<<")"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), "<<std::setprecision(8)<<embp.history()[0].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), "<<std::setprecision(8)<<embp.history()[1].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), "<<std::setprecision(8)<<embp.history()[2].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), "<<std::setprecision(8)<<embp.history()[3].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), "<<std::setprecision(8)<<embp.history()[4].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), "<<std::setprecision(8)<<embp.history()[5].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), "<<std::setprecision(8)<<embp.history()[6].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), "<<std::setprecision(8)<<embp.history()[7].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), "<<std::setprecision(8)<<embp.history()[8].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), "<<std::setprecision(8)<<embp.history()[9].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()["<<iterations<<"].residualNorm(), "<<std::setprecision(8)<<embp.history()[iterations].residualNorm()<<", 1e-6))"<<std::endl;
of.flush();
*/
		TEST_ASSERT(klab::Equals(snr, 60.207598, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00097007006, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.0010661761, 1e-6))
        TEST_ASSERT(iterations == 112)

        TEST_ASSERT(embp.history().size() == 113)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 0.90985917, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 0.91010687, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 0.89069503, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 0.86402979, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 0.82323334, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 0.69174439, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 0.69799075, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.90074716, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.96572823, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.77778781, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[112].residualNorm(), 0.00097007006, 1e-6))
	#else
/*
std::ofstream of("SolverOut.txt"); // Debug.
of<<"TEST_ASSERT(klab::Equals(snr, "<<std::setprecision(8)<<snr<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(residualNorm, "<<std::setprecision(8)<<residualNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(rrNorm, "<<std::setprecision(8)<<rrNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(iterations == "<<iterations<<")"<<std::endl;
of<<std::endl;
of<<"TEST_ASSERT(embp.history().size() == "<<(iterations+1)<<")"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), "<<std::setprecision(8)<<embp.history()[0].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), "<<std::setprecision(8)<<embp.history()[1].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), "<<std::setprecision(8)<<embp.history()[2].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), "<<std::setprecision(8)<<embp.history()[3].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), "<<std::setprecision(8)<<embp.history()[4].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), "<<std::setprecision(8)<<embp.history()[5].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), "<<std::setprecision(8)<<embp.history()[6].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), "<<std::setprecision(8)<<embp.history()[7].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), "<<std::setprecision(8)<<embp.history()[8].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), "<<std::setprecision(8)<<embp.history()[9].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()["<<iterations<<"].residualNorm(), "<<std::setprecision(8)<<embp.history()[iterations].residualNorm()<<", 1e-6))"<<std::endl;
of.flush();
*/
        TEST_ASSERT(klab::Equals(snr, 60.207603, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00097007006, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.0010661761, 1e-6))
        TEST_ASSERT(iterations == 112)

        TEST_ASSERT(embp.history().size() == 113)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 0.90985917, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 0.91010687, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 0.89069503, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 0.86402979, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 0.82323334, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 0.69174439, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 0.69799075, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.90074716, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.96572823, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.77778781, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[112].residualNorm(), 0.00097007006, 1e-6))
	#endif
#endif      
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_03()
{
    try
    {
        klab::UInt32 m = 30;    // Number of observations.
        klab::UInt32 n = 128;   // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        
        x.fill(0.0);
        x[6]   = std::complex<klab::DoubleReal>( 1.0, -1.0);
        x[3]   = std::complex<klab::DoubleReal>(-1.0, 1.0);
        x[105] = std::complex<klab::DoubleReal>(-1.0, 1.0);
        x[21]  = std::complex<klab::DoubleReal>( 1.0, -1.0);
        x[33]  = std::complex<klab::DoubleReal>(-1.0, 1.0);


        klab::KRandom::Instance().setSeed(98765);

        klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > phi0 = new TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> >(m, n, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));

        // Normalize phi.
        klab::DoubleReal normFactor = 0.0;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            phi0->column(i, col);
            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                normFactor += (col[j].real()*col[j].real()) + (col[j].imag()*col[j].imag());
        }
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > normOp = new TScalarOperator<std::complex<klab::DoubleReal> >(m, klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m)));
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > phi = normOp * phi0;

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > embp(1e-3, 200);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(true);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(true);
        embp.enableHistory(true);

        embp.solve(y, phi, k, xr);   
        TEST_ASSERT(xr.n_rows == n)

        arma::Col<klab::DoubleReal> rx(x.n_rows);
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            rx[i] = klab::CastTo<klab::DoubleReal>(x[i]);

        arma::Col<klab::DoubleReal> rxr(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);

        klab::DoubleReal snr          = klab::SNR(rx, rxr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

		TEST_ASSERT(snr>=63.7 && snr<=63.8)
		TEST_ASSERT(residualNorm>=0.00098 && residualNorm<=0.00099)
		TEST_ASSERT(rrNorm>=0.000665 && rrNorm<=0.000666)
        TEST_ASSERT(iterations==115)
		
		TEST_ASSERT(embp.history().size() == 116)
        TEST_ASSERT(embp.history()[0].residualNorm()>=1.48 && embp.history()[0].residualNorm()<=1.49)
        TEST_ASSERT(embp.history()[1].residualNorm()>=1.48 && embp.history()[1].residualNorm()<=1.49)
        TEST_ASSERT(embp.history()[2].residualNorm()>=1.43 && embp.history()[2].residualNorm()<=1.44)
        TEST_ASSERT(embp.history()[3].residualNorm()>=1.35 && embp.history()[3].residualNorm()<=1.36)
        TEST_ASSERT(embp.history()[4].residualNorm()>=1.05 && embp.history()[4].residualNorm()<=1.06)
        TEST_ASSERT(embp.history()[5].residualNorm()>=1.16 && embp.history()[5].residualNorm()<=1.17)
        TEST_ASSERT(embp.history()[6].residualNorm()>=1.49 && embp.history()[6].residualNorm()<=1.50)
        TEST_ASSERT(embp.history()[7].residualNorm()>=0.87 && embp.history()[7].residualNorm()<=0.88)
        TEST_ASSERT(embp.history()[8].residualNorm()>=1.071 && embp.history()[8].residualNorm()<=1.072)
        TEST_ASSERT(embp.history()[9].residualNorm()>=1.017 && embp.history()[9].residualNorm()<=1.018)
        TEST_ASSERT(embp.history()[115].residualNorm()>=0.00098 && embp.history()[115].residualNorm()<=0.00099)
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_04()
{
    try
    {
        klab::UInt32 m = 32;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 12;    // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y(m);
        arma::Col<klab::DoubleReal> xr;
        arma::Mat<klab::DoubleReal> A(m, n);

        x.fill(0.0);
        x[5]  =  0.1273450527495;
        x[13] =  1.094270695640407;
        x[15] =  0.655726328475191;
        x[22] =  0.8544906548270752;
        x[29] = -0.5293306506731519;
        x[34] =  0.1778243729517102;
        x[35] = -0.5044189577772389;
        x[41] =  2.078922249764298;
        x[42] = -0.2239042442217898;
        x[47] = -0.5545832342364362;
        x[53] = -1.347922690481032;
        x[57] =  1.187360783753705;

        A(0, 0) = -0.431058929255128;
        A(0, 1) = -0.0640293293725052;
        A(0, 2) = 0.03137216260178667;
        A(0, 3) = 0.08980882631804447;
        A(0, 4) = 0.3984073950864456;
        A(0, 5) = -0.6110299299799094;
        A(0, 6) = 1.55820250113813;
        A(0, 7) = 2.099159934014919;
        A(0, 8) = 0.7944598824478513;
        A(0, 9) = -0.9193661070921185;
        A(0, 10) = -1.090738356375603;
        A(0, 11) = 0.9832787397667736;
        A(0, 12) = -0.07030963872412953;
        A(0, 13) = -0.4322815889233437;
        A(0, 14) = -0.2141886367485306;
        A(0, 15) = -1.283282181369735;
        A(0, 16) = -0.4472990097831398;
        A(0, 17) = 0.3255036496612943;
        A(0, 18) = -0.3609983969484584;
        A(0, 19) = -1.431095891121696;
        A(0, 20) = 0.2705762695868516;
        A(0, 21) = -0.5408646593735252;
        A(0, 22) = 0.09910207138415968;
        A(0, 23) = 0.8428033991064745;
        A(0, 24) = 0.7217645797038547;
        A(0, 25) = -1.09941215989963;
        A(0, 26) = 1.29762686116276;
        A(0, 27) = -0.6380770284435684;
        A(0, 28) = 0.3599122512685303;
        A(0, 29) = 1.654860044336955;
        A(0, 30) = 0.5904439865646157;
        A(0, 31) = 0.5073249178009254;
        A(0, 32) = -0.6802239048791758;
        A(0, 33) = -0.6066157749162476;
        A(0, 34) = -1.038892543339137;
        A(0, 35) = -1.40837920047749;
        A(0, 36) = 1.311168366912342;
        A(0, 37) = -1.641441792442;
        A(0, 38) = -0.9370465542051387;
        A(0, 39) = -1.105251443317609;
        A(0, 40) = -0.2926675817148794;
        A(0, 41) = 1.306744418351458;
        A(0, 42) = -0.4409635845090546;
        A(0, 43) = -0.7331445834882013;
        A(0, 44) = 0.3307516986281049;
        A(0, 45) = 0.1125903790700051;
        A(0, 46) = -1.96566733568985;
        A(0, 47) = 0.4124463445297792;
        A(0, 48) = -1.112499614849064;
        A(0, 49) = -0.4316354088784425;
        A(0, 50) = 0.9038634227268604;
        A(0, 51) = 0.7015281087561087;
        A(0, 52) = -0.5742075856760612;
        A(0, 53) = 1.089616903374275;
        A(0, 54) = -1.551460224671098;
        A(0, 55) = 0.7929475908043168;
        A(0, 56) = -1.312379332236955;
        A(0, 57) = -1.261218329193658;
        A(0, 58) = 0.1793698230227484;
        A(0, 59) = 0.594381640685025;
        A(0, 60) = -0.1611573806527335;
        A(0, 61) = 0.2457754398139489;
        A(0, 62) = -0.8564933058591249;
        A(0, 63) = -0.0137751297029588;
        A(1, 0) = 0.8324100712955423;
        A(1, 1) = -0.01632197854971153;
        A(1, 2) = 0.1091003690391474;
        A(1, 3) = -0.8202501241173595;
        A(1, 4) = -0.4998001231120233;
        A(1, 5) = 0.1968871745214071;
        A(1, 6) = -0.2590440596715165;
        A(1, 7) = -0.2484310896341931;
        A(1, 8) = -0.06194624557555838;
        A(1, 9) = -0.6326617912670465;
        A(1, 10) = 0.7215019868765904;
        A(1, 11) = 1.737175540396544;
        A(1, 12) = 2.343537272016475;
        A(1, 13) = 0.1367663585893845;
        A(1, 14) = -1.255532300802221;
        A(1, 15) = 0.1174901767406111;
        A(1, 16) = 1.529700972942256;
        A(1, 17) = 0.6108016519842261;
        A(1, 18) = 0.6392134953150673;
        A(1, 19) = -1.883892227853012;
        A(1, 20) = 0.908044020767859;
        A(1, 21) = 0.9888113253159396;
        A(1, 22) = -1.127829923666322;
        A(1, 23) = 0.1465305761949773;
        A(1, 24) = -0.971519060829746;
        A(1, 25) = 0.2458147298864119;
        A(1, 26) = -0.4122735693563095;
        A(1, 27) = 0.9195471258316537;
        A(1, 28) = 0.624178197157486;
        A(1, 29) = 0.1509366706637572;
        A(1, 30) = 2.807699863831833;
        A(1, 31) = -0.5474478703829876;
        A(1, 32) = 1.186897099801884;
        A(1, 33) = -0.5662214183106776;
        A(1, 34) = -0.4060239247962155;
        A(1, 35) = 0.8736264326619816;
        A(1, 36) = -1.20789116757058;
        A(1, 37) = -1.994553904474422;
        A(1, 38) = -1.406910749736436;
        A(1, 39) = 2.364092141209294;
        A(1, 40) = -0.03983613478526589;
        A(1, 41) = -0.2818238335706983;
        A(1, 42) = -0.02294545125744069;
        A(1, 43) = -0.8204712744751367;
        A(1, 44) = -0.2307010419617677;
        A(1, 45) = 0.2030649952061898;
        A(1, 46) = -0.3811195872375988;
        A(1, 47) = -0.04086444239247611;
        A(1, 48) = -1.107684093794347;
        A(1, 49) = -0.3558445895131669;
        A(1, 50) = 1.569784403651148;
        A(1, 51) = 0.3641786925793856;
        A(1, 52) = -1.139245261574371;
        A(1, 53) = -0.09552248067550065;
        A(1, 54) = -0.2886463250639135;
        A(1, 55) = 1.660645373145067;
        A(1, 56) = 1.137888442877561;
        A(1, 57) = -0.5316637330001424;
        A(1, 58) = -2.802789378773934;
        A(1, 59) = 0.9120703476721175;
        A(1, 60) = -0.1676149407476141;
        A(1, 61) = 0.6774994465876714;
        A(1, 62) = -0.5093165141324501;
        A(1, 63) = 0.181848481245366;
        A(2, 0) = 0.5841918064603469;
        A(2, 1) = -0.6344356843624622;
        A(2, 2) = 1.037229697501695;
        A(2, 3) = -0.07052742831643646;
        A(2, 4) = 0.1320901957014532;
        A(2, 5) = 0.2904574190585547;
        A(2, 6) = -0.2136647489727979;
        A(2, 7) = 2.043197551708864;
        A(2, 8) = -0.6302318596365595;
        A(2, 9) = -3.30266102478373;
        A(2, 10) = 0.2681428120150104;
        A(2, 11) = -1.503687946780615;
        A(2, 12) = -1.137675459513058;
        A(2, 13) = -1.736882945844565;
        A(2, 14) = 0.3074902595176672;
        A(2, 15) = -0.495178829849138;
        A(2, 16) = -1.273262486672611;
        A(2, 17) = -0.1599837731640216;
        A(2, 18) = 0.6019530544075274;
        A(2, 19) = -0.5007912264236983;
        A(2, 20) = 0.2594922176109386;
        A(2, 21) = 0.2581632315614216;
        A(2, 22) = -0.3706110191401011;
        A(2, 23) = 0.3595776331520678;
        A(2, 24) = -0.8348514279809391;
        A(2, 25) = 0.8730617414388571;
        A(2, 26) = -0.08072326407182465;
        A(2, 27) = 0.5693763022787123;
        A(2, 28) = 0.1597817245404274;
        A(2, 29) = -1.518309298405403;
        A(2, 30) = 0.5822097716182236;
        A(2, 31) = -1.155827283963635;
        A(2, 32) = -0.2773431748440161;
        A(2, 33) = 1.314789064111048;
        A(2, 34) = -0.02540443229161754;
        A(2, 35) = 1.449811893698888;
        A(2, 36) = 0.2139331001417025;
        A(2, 37) = 0.3541242347953142;
        A(2, 38) = 1.701473799978102;
        A(2, 39) = 2.076400835351201;
        A(2, 40) = -1.223015925823342;
        A(2, 41) = 1.862785255309596;
        A(2, 42) = 0.6234019108883657;
        A(2, 43) = 0.2744369779929839;
        A(2, 44) = 1.897246340072785;
        A(2, 45) = 0.7225484988886703;
        A(2, 46) = 0.4354703134170506;
        A(2, 47) = -0.9869553970089011;
        A(2, 48) = 0.3488975555160102;
        A(2, 49) = 0.4397038697219164;
        A(2, 50) = -0.5494186446145301;
        A(2, 51) = 0.00230074903772355;
        A(2, 52) = -1.032692068059212;
        A(2, 53) = -0.4077507928798254;
        A(2, 54) = 0.872339290622257;
        A(2, 55) = 0.9329827808903263;
        A(2, 56) = 0.4217976865848451;
        A(2, 57) = 2.304189362955214;
        A(2, 58) = -0.542074363289763;
        A(2, 59) = 1.828543936265022;
        A(2, 60) = 1.293191033242002;
        A(2, 61) = 0.7578239234720924;
        A(2, 62) = -0.8570148642956924;
        A(2, 63) = 0.9250726389279064;
        A(3, 0) = -1.34166346589151;
        A(3, 1) = 1.734818463618363;
        A(3, 2) = -0.7366548949187585;
        A(3, 3) = 0.2371967248111666;
        A(3, 4) = 0.3311104577500041;
        A(3, 5) = 0.6089978658208752;
        A(3, 6) = -0.2128414122946932;
        A(3, 7) = -0.5842181547584789;
        A(3, 8) = -2.756634510388993;
        A(3, 9) = 0.007578090155004409;
        A(3, 10) = -1.069770434345322;
        A(3, 11) = 0.528725139559372;
        A(3, 12) = 1.244251115782868;
        A(3, 13) = 1.460890663427895;
        A(3, 14) = -0.7890914908802797;
        A(3, 15) = -0.9718341422734824;
        A(3, 16) = -0.04178528134054397;
        A(3, 17) = -1.186644189627372;
        A(3, 18) = 0.05896727130075501;
        A(3, 19) = -1.184231896821562;
        A(3, 20) = 0.007173504010287755;
        A(3, 21) = 3.111083174847298;
        A(3, 22) = 0.6359472920222195;
        A(3, 23) = 0.6816626844566356;
        A(3, 24) = 0.365659076591269;
        A(3, 25) = 0.899611613906785;
        A(3, 26) = -0.8267567825499715;
        A(3, 27) = 1.46489956280522;
        A(3, 28) = -0.3999873736779166;
        A(3, 29) = -0.3241563246009816;
        A(3, 30) = 0.9375473555494902;
        A(3, 31) = -0.7340387047832985;
        A(3, 32) = 0.7884211156992639;
        A(3, 33) = -1.188234744650461;
        A(3, 34) = 1.712207764709634;
        A(3, 35) = -0.2715741388731723;
        A(3, 36) = -1.568244713918302;
        A(3, 37) = -1.391371297914386;
        A(3, 38) = -1.825379764094613;
        A(3, 39) = -0.2048201335146057;
        A(3, 40) = 0.6221742536567652;
        A(3, 41) = -1.108735509186315;
        A(3, 42) = -0.1420640106365527;
        A(3, 43) = -1.152489753855352;
        A(3, 44) = -0.9773963502390233;
        A(3, 45) = -0.9727588121953873;
        A(3, 46) = -0.5300370235032735;
        A(3, 47) = -0.8063615342492985;
        A(3, 48) = -0.04748331517633537;
        A(3, 49) = -1.57092344511803;
        A(3, 50) = -1.219373604246766;
        A(3, 51) = -0.4794756395912644;
        A(3, 52) = 0.1472537324435444;
        A(3, 53) = -0.1576561065149749;
        A(3, 54) = 0.2787543734142515;
        A(3, 55) = -1.036514656149594;
        A(3, 56) = 0.6401237632561114;
        A(3, 57) = -1.75062069656564;
        A(3, 58) = -1.30996017992952;
        A(3, 59) = -0.9903276876890069;
        A(3, 60) = -0.812177653856618;
        A(3, 61) = 1.118669196480276;
        A(3, 62) = 1.275218051540198;
        A(3, 63) = 0.4406213404044787;
        A(4, 0) = 0.3451649675212734;
        A(4, 1) = 0.02083615362103833;
        A(4, 2) = -0.7454953427400273;
        A(4, 3) = 0.5328817034122234;
        A(4, 4) = 1.770036416398246;
        A(4, 5) = -0.07848692076724977;
        A(4, 6) = 0.04525745176928564;
        A(4, 7) = 0.1946825210828556;
        A(4, 8) = -0.6849842082776039;
        A(4, 9) = -1.081178779899169;
        A(4, 10) = 0.8170751389287645;
        A(4, 11) = 0.449584032608674;
        A(4, 12) = -0.2920312895781;
        A(4, 13) = -1.471895060570783;
        A(4, 14) = 0.7720058756632596;
        A(4, 15) = 0.5401834409272764;
        A(4, 16) = -1.430531363537639;
        A(4, 17) = -0.03208439325040437;
        A(4, 18) = -0.201967156849246;
        A(4, 19) = -0.5465712684703722;
        A(4, 20) = 0.3016032699062112;
        A(4, 21) = 1.44025237290484;
        A(4, 22) = 0.5193813060910077;
        A(4, 23) = -0.5087508268606996;
        A(4, 24) = 1.052183688945218;
        A(4, 25) = -0.1145182417974893;
        A(4, 26) = -0.8439230052836451;
        A(4, 27) = 0.3812300431667353;
        A(4, 28) = -0.0428418542538697;
        A(4, 29) = -0.7604115803559854;
        A(4, 30) = 0.6439908949406314;
        A(4, 31) = -0.3250773455513032;
        A(4, 32) = 0.8870662859673023;
        A(4, 33) = 0.3624798529459776;
        A(4, 34) = 1.268692338159022;
        A(4, 35) = 0.3433859736240885;
        A(4, 36) = 0.7536772204074902;
        A(4, 37) = 0.7858715039077722;
        A(4, 38) = 0.2258977849746525;
        A(4, 39) = 0.2289550137336344;
        A(4, 40) = 0.08692448026212804;
        A(4, 41) = 0.9445426848937869;
        A(4, 42) = -0.1677479632828703;
        A(4, 43) = 0.5875171622237381;
        A(4, 44) = -0.6930412803509688;
        A(4, 45) = -0.6502737760558731;
        A(4, 46) = 0.08910217792697452;
        A(4, 47) = -0.141051684988309;
        A(4, 48) = 0.9645529845272776;
        A(4, 49) = -1.162240469270604;
        A(4, 50) = 0.1810851608416037;
        A(4, 51) = -1.062620284966184;
        A(4, 52) = -1.533545979326203;
        A(4, 53) = 0.1065735958296584;
        A(4, 54) = -0.4668667763638584;
        A(4, 55) = -0.5673967133233815;
        A(4, 56) = 0.2164402888210394;
        A(4, 57) = -1.459339489921065;
        A(4, 58) = -1.35211711544563;
        A(4, 59) = -0.7782850394519724;
        A(4, 60) = 0.1483354752556949;
        A(4, 61) = 1.328021330101157;
        A(4, 62) = -1.751365609755935;
        A(4, 63) = 0.2169315577831981;
        A(5, 0) = -1.187037769393816;
        A(5, 1) = -0.3167426515379083;
        A(5, 2) = 1.176326152088591;
        A(5, 3) = 0.3946345074314719;
        A(5, 4) = -1.168893410477735;
        A(5, 5) = 1.187630473264519;
        A(5, 6) = 0.584297207128943;
        A(5, 7) = -1.22350310479182;
        A(5, 8) = 1.564827240615063;
        A(5, 9) = 0.3168520161772764;
        A(5, 10) = 0.1770684465913581;
        A(5, 11) = 0.8229570182093525;
        A(5, 12) = 0.6096410499021392;
        A(5, 13) = -1.144026919286321;
        A(5, 14) = -0.005828513409837782;
        A(5, 15) = 2.089407114516609;
        A(5, 16) = -0.7206110071199725;
        A(5, 17) = 0.1269381863144968;
        A(5, 18) = -2.238532517859903;
        A(5, 19) = -0.2497715251381594;
        A(5, 20) = 2.067126133743951;
        A(5, 21) = -0.1486737311983966;
        A(5, 22) = -1.000885915982827;
        A(5, 23) = -0.1120358398638883;
        A(5, 24) = 0.8387616411037778;
        A(5, 25) = 0.3802265599238202;
        A(5, 26) = 1.112945789287855;
        A(5, 27) = 0.4178592374708008;
        A(5, 28) = -1.605054282298509;
        A(5, 29) = 0.19318730762291;
        A(5, 30) = -0.8812797774035319;
        A(5, 31) = -2.1246368085216;
        A(5, 32) = -1.152390433643937;
        A(5, 33) = 0.08801845703545473;
        A(5, 34) = -1.944131143502058;
        A(5, 35) = 0.878950645508865;
        A(5, 36) = 0.02180822897927239;
        A(5, 37) = 0.06131152798927372;
        A(5, 38) = -0.1163366078346196;
        A(5, 39) = -0.8658604509398618;
        A(5, 40) = 0.8240109256095909;
        A(5, 41) = 1.2348757306823;
        A(5, 42) = -0.548825933470069;
        A(5, 43) = 0.6288485248026944;
        A(5, 44) = -0.1924882433527011;
        A(5, 45) = 0.1161999004142705;
        A(5, 46) = -1.004793869154934;
        A(5, 47) = -0.620609375374551;
        A(5, 48) = 0.8409323472256678;
        A(5, 49) = 1.18385808703364;
        A(5, 50) = -0.6574551290466767;
        A(5, 51) = 0.05720555186718278;
        A(5, 52) = -0.5670971638771117;
        A(5, 53) = 0.2355591463016312;
        A(5, 54) = -1.326250474777681;
        A(5, 55) = -0.7062957542785687;
        A(5, 56) = -0.01644312046319547;
        A(5, 57) = -0.4767208202092922;
        A(5, 58) = 0.2062360226249639;
        A(5, 59) = -1.260138296908029;
        A(5, 60) = 1.053223713709774;
        A(5, 61) = 1.353571421976902;
        A(5, 62) = -0.5921838537181846;
        A(5, 63) = -0.02332489783704513;
        A(6, 0) = -0.1528705708985069;
        A(6, 1) = -0.4230593937269497;
        A(6, 2) = 1.131741704091009;
        A(6, 3) = 1.075311558691954;
        A(6, 4) = 0.5737109991742885;
        A(6, 5) = 1.308919660678649;
        A(6, 6) = 0.410278663991111;
        A(6, 7) = 0.00966077265898873;
        A(6, 8) = 2.31551157828616;
        A(6, 9) = -1.335024432929957;
        A(6, 10) = -0.8433043524619488;
        A(6, 11) = 1.132622045358363;
        A(6, 12) = 0.3799116633990179;
        A(6, 13) = 1.684370421411989;
        A(6, 14) = 0.5359388956426116;
        A(6, 15) = 1.790707440630706;
        A(6, 16) = -1.415100905712088;
        A(6, 17) = -0.34622913185879;
        A(6, 18) = -1.026377371814184;
        A(6, 19) = 0.32640536436066;
        A(6, 20) = -0.3829149978817087;
        A(6, 21) = 0.1619328883582157;
        A(6, 22) = -0.6481493131568534;
        A(6, 23) = 0.1054308591001289;
        A(6, 24) = -0.03885242817520313;
        A(6, 25) = -0.7647844750471338;
        A(6, 26) = 1.425970306203917;
        A(6, 27) = 0.04718755194213511;
        A(6, 28) = -0.4520184101137934;
        A(6, 29) = -2.077101074180348;
        A(6, 30) = -0.8122784742575844;
        A(6, 31) = -1.392086931715145;
        A(6, 32) = 1.422536112262464;
        A(6, 33) = -0.5541351571054176;
        A(6, 34) = 1.299772874788647;
        A(6, 35) = -0.06279251409504998;
        A(6, 36) = -1.37948056430648;
        A(6, 37) = 1.011373935530421;
        A(6, 38) = -1.46356871907606;
        A(6, 39) = 0.8641034816524091;
        A(6, 40) = -1.474223938327494;
        A(6, 41) = 0.9686594876814259;
        A(6, 42) = 2.04538732657389;
        A(6, 43) = -0.982452485834293;
        A(6, 44) = -0.5098169636395428;
        A(6, 45) = 1.122767939675871;
        A(6, 46) = 1.387116059056607;
        A(6, 47) = 0.8272926842868055;
        A(6, 48) = -1.761355976624785;
        A(6, 49) = 1.273624379384039;
        A(6, 50) = 0.4685775101002604;
        A(6, 51) = 0.00158627088956676;
        A(6, 52) = 0.9172554194872437;
        A(6, 53) = -0.06246425072851154;
        A(6, 54) = -0.8021055298506352;
        A(6, 55) = 0.2101750992325023;
        A(6, 56) = -0.4211727083444125;
        A(6, 57) = 1.478703918345732;
        A(6, 58) = 1.459522125867764;
        A(6, 59) = -0.4743347768432786;
        A(6, 60) = -0.2371711597949307;
        A(6, 61) = -3.21537756914736;
        A(6, 62) = 2.309074180059145;
        A(6, 63) = -0.8834161768077362;
        A(7, 0) = -0.3389038224913568;
        A(7, 1) = 0.2986589706441202;
        A(7, 2) = -0.5068516844789348;
        A(7, 3) = -1.123634882188716;
        A(7, 4) = -1.009516738602982;
        A(7, 5) = 0.5205457767492484;
        A(7, 6) = 0.4791008619866002;
        A(7, 7) = -0.2391547238592451;
        A(7, 8) = -0.967044957831352;
        A(7, 9) = 0.2446309106629011;
        A(7, 10) = 1.024616393197034;
        A(7, 11) = -0.7031872573379506;
        A(7, 12) = -0.2428650719796918;
        A(7, 13) = -1.097061000509035;
        A(7, 14) = -0.1171978480573067;
        A(7, 15) = -1.045698781934902;
        A(7, 16) = 0.6442349710632958;
        A(7, 17) = 2.182208054052226;
        A(7, 18) = -1.026722315870031;
        A(7, 19) = -0.9597503094216444;
        A(7, 20) = -0.3401437625901588;
        A(7, 21) = -0.152006413985004;
        A(7, 22) = 0.9616219494858975;
        A(7, 23) = -0.8261434877080254;
        A(7, 24) = 1.137089499969684;
        A(7, 25) = -1.060637910591004;
        A(7, 26) = -0.2212134150223718;
        A(7, 27) = -1.374144700517549;
        A(7, 28) = -0.1794264564167967;
        A(7, 29) = -1.590069282802557;
        A(7, 30) = -0.02791903763257786;
        A(7, 31) = 0.9085397460265883;
        A(7, 32) = 0.4726363843286369;
        A(7, 33) = 0.3813394880747307;
        A(7, 34) = -0.456647036721225;
        A(7, 35) = 0.8063562674770322;
        A(7, 36) = -0.1410771453662216;
        A(7, 37) = -0.4833618163182959;
        A(7, 38) = 0.6857894986503743;
        A(7, 39) = -1.167425209711473;
        A(7, 40) = -0.5979160782921991;
        A(7, 41) = -0.1509774758733518;
        A(7, 42) = -1.091543248203099;
        A(7, 43) = -1.248593721523877;
        A(7, 44) = 0.5843033175431701;
        A(7, 45) = -0.9814833805834841;
        A(7, 46) = 0.04051938881614948;
        A(7, 47) = 1.846598521381206;
        A(7, 48) = 0.1449586303650474;
        A(7, 49) = -0.9906032850295544;
        A(7, 50) = 0.513189258200573;
        A(7, 51) = 0.409412733362445;
        A(7, 52) = 1.900129791494993;
        A(7, 53) = 0.5721284615501295;
        A(7, 54) = -0.003291656756640657;
        A(7, 55) = -0.62261335331896;
        A(7, 56) = -0.3638502506774186;
        A(7, 57) = -0.9838777027399744;
        A(7, 58) = -0.6707557527045086;
        A(7, 59) = -0.6898374763151564;
        A(7, 60) = 0.2901682604335387;
        A(7, 61) = -0.3739494131775255;
        A(7, 62) = 1.384757909389347;
        A(7, 63) = 0.4197887814982221;
        A(8, 0) = 0.9399047328138495;
        A(8, 1) = 0.9464125463165942;
        A(8, 2) = 0.7495985835157828;
        A(8, 3) = -0.006390750094964756;
        A(8, 4) = -0.5913825798168806;
        A(8, 5) = -0.1102209578963339;
        A(8, 6) = 1.253227875084328;
        A(8, 7) = 0.4961076778576968;
        A(8, 8) = 1.166791695027493;
        A(8, 9) = 1.544104372234362;
        A(8, 10) = -0.1396178115813355;
        A(8, 11) = -1.08492654116126;
        A(8, 12) = 0.8854350286002867;
        A(8, 13) = 1.376137024035775;
        A(8, 14) = -0.1885666319890167;
        A(8, 15) = -0.513417825425167;
        A(8, 16) = 2.184794876881067;
        A(8, 17) = 0.9083010531287159;
        A(8, 18) = 0.7124655942267881;
        A(8, 19) = 0.6841098243963816;
        A(8, 20) = -0.4099812261428726;
        A(8, 21) = -0.3056040727855858;
        A(8, 22) = -0.1346527244272275;
        A(8, 23) = 0.2166878126927498;
        A(8, 24) = 1.816635255320952;
        A(8, 25) = -0.8708612642588725;
        A(8, 26) = -0.8741005821785198;
        A(8, 27) = -0.9965448545000091;
        A(8, 28) = 0.1393813338547208;
        A(8, 29) = -2.156601281990279;
        A(8, 30) = -2.143725428689433;
        A(8, 31) = -0.7439350208384336;
        A(8, 32) = 1.819336831624732;
        A(8, 33) = -1.519544971234753;
        A(8, 34) = -0.4042808112432238;
        A(8, 35) = -0.4884778203669912;
        A(8, 36) = 0.8119709949549816;
        A(8, 37) = 1.044595687172183;
        A(8, 38) = 1.068963982339143;
        A(8, 39) = 0.02847591797981332;
        A(8, 40) = -0.5161040104582755;
        A(8, 41) = -1.413350315483791;
        A(8, 42) = 1.311096371909853;
        A(8, 43) = 0.04162121058748668;
        A(8, 44) = 0.4463095036321165;
        A(8, 45) = -0.04806797991659962;
        A(8, 46) = -1.235306458669973;
        A(8, 47) = -0.6377910409949784;
        A(8, 48) = -0.2032950248382978;
        A(8, 49) = -0.7657977814602652;
        A(8, 50) = -1.433172466715997;
        A(8, 51) = 1.099492887335456;
        A(8, 52) = -0.33662753086933;
        A(8, 53) = 1.458418961870746;
        A(8, 54) = 1.596493038797016;
        A(8, 55) = -0.4599756793704983;
        A(8, 56) = -1.712022476022943;
        A(8, 57) = 0.5844847118690755;
        A(8, 58) = -0.4807629075951234;
        A(8, 59) = -0.5921150468114966;
        A(8, 60) = -1.90063820236188;
        A(8, 61) = 0.2406420137768506;
        A(8, 62) = 0.6478659682030878;
        A(8, 63) = 0.65539882728327;
        A(9, 0) = -1.00328629571678;
        A(9, 1) = 0.368637585440867;
        A(9, 2) = 0.6384552233712406;
        A(9, 3) = 1.375048242645779;
        A(9, 4) = 1.094359397586627;
        A(9, 5) = 0.4346914384641099;
        A(9, 6) = 0.4027082796641071;
        A(9, 7) = -0.3156158906892415;
        A(9, 8) = 0.9785432100386099;
        A(9, 9) = -1.732335166765294;
        A(9, 10) = -0.3458389142899389;
        A(9, 11) = -1.215891630285445;
        A(9, 12) = 0.9835800429954661;
        A(9, 13) = -0.7301120185695065;
        A(9, 14) = 0.1621175355453229;
        A(9, 15) = 0.2316259278036119;
        A(9, 16) = -0.3200831078294054;
        A(9, 17) = 0.3805568678047162;
        A(9, 18) = 0.9603919581620721;
        A(9, 19) = 0.1874459072902532;
        A(9, 20) = -0.652024151577033;
        A(9, 21) = -0.5599235069495604;
        A(9, 22) = -0.1440597795232049;
        A(9, 23) = -0.9093641108758143;
        A(9, 24) = 0.4370020694684548;
        A(9, 25) = 0.01946151664299726;
        A(9, 26) = 1.193056445523211;
        A(9, 27) = 1.240446882730465;
        A(9, 28) = -0.5881094035284307;
        A(9, 29) = 1.537877202854202;
        A(9, 30) = 0.5027062884591657;
        A(9, 31) = 1.46046151474151;
        A(9, 32) = -0.5706617347292361;
        A(9, 33) = -1.053034268197049;
        A(9, 34) = -0.5251317683441591;
        A(9, 35) = -0.7466670164270048;
        A(9, 36) = -1.743062991804922;
        A(9, 37) = -0.7673634860608786;
        A(9, 38) = -0.9738225106757041;
        A(9, 39) = -0.6058774439611767;
        A(9, 40) = 0.2092161049192564;
        A(9, 41) = -0.1572286398240914;
        A(9, 42) = -0.5079977181975813;
        A(9, 43) = -1.27205717822463;
        A(9, 44) = 1.678360088874308;
        A(9, 45) = 0.5093628992783973;
        A(9, 46) = 0.4231973756043324;
        A(9, 47) = -0.1806408563605244;
        A(9, 48) = 1.510105417852432;
        A(9, 49) = 0.9692248847975625;
        A(9, 50) = 0.1875360665974808;
        A(9, 51) = -0.2874902863406585;
        A(9, 52) = 0.541453408510941;
        A(9, 53) = 0.04055737453087407;
        A(9, 54) = 3.063824392024558;
        A(9, 55) = 0.5556042602806067;
        A(9, 56) = 0.2817069756072134;
        A(9, 57) = -0.4418125331614392;
        A(9, 58) = 0.7647918134907457;
        A(9, 59) = 0.4212375351062669;
        A(9, 60) = -0.3304726779752683;
        A(9, 61) = -1.003876157677131;
        A(9, 62) = -0.4386371284991261;
        A(9, 63) = 0.8172679316680366;
        A(10, 0) = 1.432213198606983;
        A(10, 1) = -0.9588515482677122;
        A(10, 2) = 1.2105362577718;
        A(10, 3) = 0.2128978131588137;
        A(10, 4) = -1.615527076903782;
        A(10, 5) = -1.277945739192234;
        A(10, 6) = 0.8504342099655891;
        A(10, 7) = 2.393903097574091;
        A(10, 8) = -1.842498939733209;
        A(10, 9) = -0.4721251178319766;
        A(10, 10) = -0.5664438847980863;
        A(10, 11) = -0.1022252020382701;
        A(10, 12) = 1.684356041638017;
        A(10, 13) = 1.799101377510278;
        A(10, 14) = -0.01431078845980759;
        A(10, 15) = 0.8998387879115054;
        A(10, 16) = -0.9127697123481637;
        A(10, 17) = -1.572056958825487;
        A(10, 18) = -0.3347805242042668;
        A(10, 19) = -0.194263036641906;
        A(10, 20) = -0.5417840690704958;
        A(10, 21) = -0.2201117804028161;
        A(10, 22) = -0.9862829101512816;
        A(10, 23) = 0.6400482805559927;
        A(10, 24) = -1.84124464232491;
        A(10, 25) = -0.761408145471323;
        A(10, 26) = 0.8859983471656422;
        A(10, 27) = 1.090668471471759;
        A(10, 28) = -1.531642353664074;
        A(10, 29) = 0.5415963112672286;
        A(10, 30) = 2.181559782942443;
        A(10, 31) = 0.9998934532105044;
        A(10, 32) = 0.4158577103667869;
        A(10, 33) = 0.6997210611328814;
        A(10, 34) = 0.2409116329563526;
        A(10, 35) = 1.490446574670286;
        A(10, 36) = -2.161120976644972;
        A(10, 37) = 0.1727966738169848;
        A(10, 38) = 0.4723324795235227;
        A(10, 39) = 0.4431558194384705;
        A(10, 40) = -0.5050313399738976;
        A(10, 41) = -1.286193064110895;
        A(10, 42) = 0.05310056691286284;
        A(10, 43) = -0.06994211867609868;
        A(10, 44) = 1.776931738461227;
        A(10, 45) = 0.3981057350669132;
        A(10, 46) = -0.9741031411015449;
        A(10, 47) = 0.6910263040070263;
        A(10, 48) = 0.383740430851566;
        A(10, 49) = 0.2333856278337476;
        A(10, 50) = -0.4701513415340134;
        A(10, 51) = -0.1743503504623961;
        A(10, 52) = 1.456332196528072;
        A(10, 53) = 0.3283023211484678;
        A(10, 54) = 0.2617487973383053;
        A(10, 55) = 0.5784866480713029;
        A(10, 56) = 1.003701783708345;
        A(10, 57) = -0.115766743427119;
        A(10, 58) = -0.2637956626530077;
        A(10, 59) = -0.01021595279904608;
        A(10, 60) = -0.4589912754597937;
        A(10, 61) = -0.5383186254300945;
        A(10, 62) = 0.1483395322013434;
        A(10, 63) = -0.05079361577696345;
        A(11, 0) = -0.2776599783034855;
        A(11, 1) = -0.7979211455482987;
        A(11, 2) = -1.539968071457508;
        A(11, 3) = 1.472917257902094;
        A(11, 4) = 0.1526163600433733;
        A(11, 5) = -0.6765364680559369;
        A(11, 6) = 1.226317911787362;
        A(11, 7) = 0.848943207579585;
        A(11, 8) = -0.8381903663076167;
        A(11, 9) = -1.093376513381303;
        A(11, 10) = 0.2356579841388219;
        A(11, 11) = -2.36162328689552;
        A(11, 12) = -0.8961489493870217;
        A(11, 13) = 0.7925208526054761;
        A(11, 14) = -0.928420100392673;
        A(11, 15) = 2.518419435555763;
        A(11, 16) = -0.4326868699526775;
        A(11, 17) = -0.4884371958368969;
        A(11, 18) = -1.259048440349659;
        A(11, 19) = -2.504578306130965;
        A(11, 20) = 0.8917594513464341;
        A(11, 21) = 0.6947829556935465;
        A(11, 22) = -0.2843464836664896;
        A(11, 23) = 0.7427123131118213;
        A(11, 24) = 1.016979935291112;
        A(11, 25) = 0.4245180786159056;
        A(11, 26) = 2.162388736387479;
        A(11, 27) = -0.4429876101258528;
        A(11, 28) = 1.17271630243883;
        A(11, 29) = 1.0554602632108;
        A(11, 30) = -1.193319308609835;
        A(11, 31) = -0.7047807617461999;
        A(11, 32) = 1.445316447192004;
        A(11, 33) = 1.238889502535316;
        A(11, 34) = 0.3695843170147263;
        A(11, 35) = 0.5000377097317487;
        A(11, 36) = -1.460526969172138;
        A(11, 37) = 0.1047689153958333;
        A(11, 38) = -0.2059855830971631;
        A(11, 39) = 3.127860792741767;
        A(11, 40) = -0.7623011712856264;
        A(11, 41) = 0.2217188770409482;
        A(11, 42) = -1.391546930574096;
        A(11, 43) = 1.363603319320906;
        A(11, 44) = -1.476468986172683;
        A(11, 45) = -0.005608907528561111;
        A(11, 46) = 0.8020655032344448;
        A(11, 47) = -0.2546490461955305;
        A(11, 48) = 0.3065603842248287;
        A(11, 49) = 0.282107527938902;
        A(11, 50) = -0.7297738955491023;
        A(11, 51) = 0.9946561407465665;
        A(11, 52) = 0.1057874621358077;
        A(11, 53) = -0.3113081417855453;
        A(11, 54) = -1.109516311276169;
        A(11, 55) = -1.526388210309369;
        A(11, 56) = 2.133759474974002;
        A(11, 57) = 0.1829789227645364;
        A(11, 58) = -0.005743311461297923;
        A(11, 59) = 1.429548191171658;
        A(11, 60) = 0.5487739029955127;
        A(11, 61) = -0.6635299225730571;
        A(11, 62) = -0.2500223448681423;
        A(11, 63) = 2.140863896143493;
        A(12, 0) = 0.3208958901708582;
        A(12, 1) = 0.5103998980546816;
        A(12, 2) = 1.343322843082524;
        A(12, 3) = -0.5352843481780406;
        A(12, 4) = -0.05479574095112598;
        A(12, 5) = -1.901306055067542;
        A(12, 6) = 2.31606025142822;
        A(12, 7) = -0.3318118627845895;
        A(12, 8) = 0.3577625809514444;
        A(12, 9) = -1.013898070616929;
        A(12, 10) = -0.7944827066461646;
        A(12, 11) = 0.4618826556927645;
        A(12, 12) = -0.8417629882564399;
        A(12, 13) = 1.225198452598123;
        A(12, 14) = 0.9627782134669518;
        A(12, 15) = 0.500741324847351;
        A(12, 16) = 0.2233846310811128;
        A(12, 17) = -2.060375736171322;
        A(12, 18) = 0.7960489550478256;
        A(12, 19) = 1.595280068978013;
        A(12, 20) = 0.6619686045693826;
        A(12, 21) = -0.2006130375905841;
        A(12, 22) = -0.2536172811401378;
        A(12, 23) = 0.3259753856088387;
        A(12, 24) = -1.135332367821216;
        A(12, 25) = 1.179828517308362;
        A(12, 26) = -0.7983066489324538;
        A(12, 27) = 0.8350045887066383;
        A(12, 28) = 0.2935304213753345;
        A(12, 29) = 1.154252501074368;
        A(12, 30) = -0.9226868562170182;
        A(12, 31) = 0.8604064928948725;
        A(12, 32) = 0.951171946340814;
        A(12, 33) = -0.9786077797475108;
        A(12, 34) = -0.9788412475942987;
        A(12, 35) = 1.382286958473927;
        A(12, 36) = -0.7195556035228379;
        A(12, 37) = -0.8259552614310365;
        A(12, 38) = -0.5944698811991845;
        A(12, 39) = -0.2788700936186678;
        A(12, 40) = -0.3354909763542895;
        A(12, 41) = -1.582679972032991;
        A(12, 42) = -0.4585448903441963;
        A(12, 43) = -0.4957034942803235;
        A(12, 44) = -0.2074182164770412;
        A(12, 45) = -0.4795163560274995;
        A(12, 46) = -1.168444036228117;
        A(12, 47) = 0.9954996653206386;
        A(12, 48) = 0.1228600479928733;
        A(12, 49) = -0.3037377091050433;
        A(12, 50) = -0.9457438931031506;
        A(12, 51) = -0.5090013774675272;
        A(12, 52) = 1.240026502624521;
        A(12, 53) = 1.585100587299442;
        A(12, 54) = -0.1797717170552969;
        A(12, 55) = -2.460886286633268;
        A(12, 56) = -1.042780293032187;
        A(12, 57) = -0.6761014685827689;
        A(12, 58) = 0.2387829849054849;
        A(12, 59) = 3.073356327847002;
        A(12, 60) = -0.1434571221314103;
        A(12, 61) = 0.3259855829476406;
        A(12, 62) = 0.827318109922612;
        A(12, 63) = -0.002172157877203559;
        A(13, 0) = 1.843875103392763;
        A(13, 1) = -0.4930855735492852;
        A(13, 2) = -1.691212915181234;
        A(13, 3) = -1.259731224647393;
        A(13, 4) = -0.4667257256678196;
        A(13, 5) = 1.11735317804768;
        A(13, 6) = 1.302815622367588;
        A(13, 7) = 1.085237379510033;
        A(13, 8) = 1.744302305162423;
        A(13, 9) = 0.7615823274128339;
        A(13, 10) = -1.553951324212187;
        A(13, 11) = -1.246762872482759;
        A(13, 12) = 0.7316832431543923;
        A(13, 13) = -0.9307144498784628;
        A(13, 14) = 0.4800070444020901;
        A(13, 15) = -1.439014597999005;
        A(13, 16) = 0.684663259704232;
        A(13, 17) = -1.045304617118589;
        A(13, 18) = -0.1328125886878443;
        A(13, 19) = 0.4228872694573875;
        A(13, 20) = 1.576436748322973;
        A(13, 21) = 0.1002833803395052;
        A(13, 22) = -0.572928893969137;
        A(13, 23) = -0.4596662394111041;
        A(13, 24) = 0.3928653787943905;
        A(13, 25) = -0.2649289440199081;
        A(13, 26) = 1.08267587223692;
        A(13, 27) = 1.78445301410157;
        A(13, 28) = 0.716035379542674;
        A(13, 29) = -0.01811414830504666;
        A(13, 30) = -1.920349935082768;
        A(13, 31) = -0.7111880022964282;
        A(13, 32) = 0.09765812925453242;
        A(13, 33) = 0.2864645142312831;
        A(13, 34) = 0.363734133323173;
        A(13, 35) = 0.2505785028615984;
        A(13, 36) = 0.6423074403813313;
        A(13, 37) = 1.322570657986571;
        A(13, 38) = 0.08368742670073823;
        A(13, 39) = -0.1154021865795368;
        A(13, 40) = -0.06589129850015074;
        A(13, 41) = 2.071752032937372;
        A(13, 42) = 0.1441148310841086;
        A(13, 43) = -0.860451788946914;
        A(13, 44) = -0.7481750381476182;
        A(13, 45) = -0.2074813763363882;
        A(13, 46) = 0.9920288758734495;
        A(13, 47) = -0.3049904020403683;
        A(13, 48) = 0.6907894875708982;
        A(13, 49) = -1.511855263088993;
        A(13, 50) = 0.3296108200997556;
        A(13, 51) = -1.397349789742741;
        A(13, 52) = 0.295182486062034;
        A(13, 53) = 0.7291641039595553;
        A(13, 54) = -0.0266492918217317;
        A(13, 55) = 0.7954275207568304;
        A(13, 56) = -0.7587434483087904;
        A(13, 57) = -0.709651268265761;
        A(13, 58) = 0.5498496972889837;
        A(13, 59) = -0.7873565927834921;
        A(13, 60) = 0.008808535488116947;
        A(13, 61) = -0.3198953583277921;
        A(13, 62) = -0.8173013551471573;
        A(13, 63) = -0.1041224568695235;
        A(14, 0) = -0.4617638579838592;
        A(14, 1) = 0.8411487716524435;
        A(14, 2) = -0.09980210847601252;
        A(14, 3) = 0.4666247971643449;
        A(14, 4) = -0.8275787927673949;
        A(14, 5) = 0.3055362073641591;
        A(14, 6) = -0.9099538097640678;
        A(14, 7) = -0.2477550352221421;
        A(14, 8) = 0.2265639935232574;
        A(14, 9) = 1.404658590875385;
        A(14, 10) = -0.3563974017746553;
        A(14, 11) = 0.9712471311803163;
        A(14, 12) = -0.4192457004139307;
        A(14, 13) = -0.4215191328558902;
        A(14, 14) = -0.4188954907070447;
        A(14, 15) = 0.6320440850768987;
        A(14, 16) = 1.978091433973177;
        A(14, 17) = 1.430918344973732;
        A(14, 18) = 1.02482474688685;
        A(14, 19) = -0.01222924587638289;
        A(14, 20) = -0.9560613295821928;
        A(14, 21) = 0.9719125722373065;
        A(14, 22) = -0.3132680586045425;
        A(14, 23) = 0.1073168117624278;
        A(14, 24) = -0.4213972810007362;
        A(14, 25) = -0.6555261041755833;
        A(14, 26) = 0.5978997801824271;
        A(14, 27) = -0.5270461976157808;
        A(14, 28) = 0.07133336235291275;
        A(14, 29) = -0.9701685781378592;
        A(14, 30) = 0.2411215925133577;
        A(14, 31) = 0.1256785386842436;
        A(14, 32) = 2.233121358236669;
        A(14, 33) = -1.089816670620501;
        A(14, 34) = -0.8324408978057852;
        A(14, 35) = 0.07281200088477152;
        A(14, 36) = 0.6385892022343536;
        A(14, 37) = 0.1553708031830501;
        A(14, 38) = 1.607040045525812;
        A(14, 39) = 1.192937478777962;
        A(14, 40) = -0.3931065211972259;
        A(14, 41) = 0.3831912904284145;
        A(14, 42) = 0.6210221271308293;
        A(14, 43) = -1.107340229923169;
        A(14, 44) = 1.664978177652695;
        A(14, 45) = 0.6177239781077938;
        A(14, 46) = -0.058488126020257;
        A(14, 47) = 0.1277532809875645;
        A(14, 48) = 0.872157084227191;
        A(14, 49) = -1.180527351981853;
        A(14, 50) = -0.1100428153343983;
        A(14, 51) = 1.055351825584927;
        A(14, 52) = 0.9582787838168144;
        A(14, 53) = -0.692646414582076;
        A(14, 54) = -1.956635055062031;
        A(14, 55) = 1.814900141172282;
        A(14, 56) = 0.6503016243167592;
        A(14, 57) = 0.1418189799432524;
        A(14, 58) = -2.106194459432425;
        A(14, 59) = 1.806428917458409;
        A(14, 60) = 0.9704499542447836;
        A(14, 61) = -0.3978508180090851;
        A(14, 62) = -1.201326538950775;
        A(14, 63) = -1.128787949010187;
        A(15, 0) = 1.571571548921988;
        A(15, 1) = 0.9766965167741691;
        A(15, 2) = -0.6918223151533685;
        A(15, 3) = -1.372545635895384;
        A(15, 4) = -0.3489760388700541;
        A(15, 5) = 2.346687948423932;
        A(15, 6) = -1.86925772125654;
        A(15, 7) = -0.2959212207343046;
        A(15, 8) = 0.2506824679435218;
        A(15, 9) = 0.7359701912701386;
        A(15, 10) = 1.471031097647418;
        A(15, 11) = -1.380743617540058;
        A(15, 12) = -0.6452085838575904;
        A(15, 13) = 1.028315064903479;
        A(15, 14) = 0.4743876290677602;
        A(15, 15) = -0.1646416942266672;
        A(15, 16) = -1.663296009414077;
        A(15, 17) = -0.896140864488334;
        A(15, 18) = 0.2945906850713783;
        A(15, 19) = -0.2613535745247689;
        A(15, 20) = 2.206941780273716;
        A(15, 21) = 0.8327026261824971;
        A(15, 22) = 0.068282876285328;
        A(15, 23) = -1.067227586406148;
        A(15, 24) = 0.38483671104932;
        A(15, 25) = -0.7198499884927266;
        A(15, 26) = 0.7405883763147995;
        A(15, 27) = -0.1385569144671314;
        A(15, 28) = 0.5732696135497034;
        A(15, 29) = -1.203165480217646;
        A(15, 30) = 0.3568935736308342;
        A(15, 31) = 0.4123236098421528;
        A(15, 32) = -0.485429912933834;
        A(15, 33) = -1.073589662198638;
        A(15, 34) = 0.06306776231517594;
        A(15, 35) = 0.9455344035311561;
        A(15, 36) = 0.01952532869063387;
        A(15, 37) = -0.1301817898361825;
        A(15, 38) = 0.3430718953097332;
        A(15, 39) = 0.9591028510251232;
        A(15, 40) = -0.06189622448466621;
        A(15, 41) = 0.5950981890409224;
        A(15, 42) = -0.1695032450465809;
        A(15, 43) = -0.2172799793659299;
        A(15, 44) = -0.7773896379294052;
        A(15, 45) = 0.857774029740235;
        A(15, 46) = -0.9433078612441848;
        A(15, 47) = 0.6660867232793248;
        A(15, 48) = -1.096895674231124;
        A(15, 49) = -0.8673450105427263;
        A(15, 50) = 0.7694236475205142;
        A(15, 51) = 0.6139679361084099;
        A(15, 52) = 0.6484009736088759;
        A(15, 53) = 1.210333709205679;
        A(15, 54) = -2.779240904857647;
        A(15, 55) = -1.462815251487022;
        A(15, 56) = 1.781083527613091;
        A(15, 57) = 2.164747593890104;
        A(15, 58) = 0.3624326753671689;
        A(15, 59) = 1.132041307929445;
        A(15, 60) = 0.9852320767949404;
        A(15, 61) = 0.1699080718041306;
        A(15, 62) = 0.6447048480977238;
        A(15, 63) = -1.269660347740418;
        A(16, 0) = 0.3207277993458489;
        A(16, 1) = 1.376060422684961;
        A(16, 2) = 0.8438224416316397;
        A(16, 3) = 1.470938809427927;
        A(16, 4) = 0.1323854028006551;
        A(16, 5) = 0.5169710282342804;
        A(16, 6) = -0.2815959302514933;
        A(16, 7) = 0.5145192935968799;
        A(16, 8) = 1.467200522496165;
        A(16, 9) = 0.3587854956332099;
        A(16, 10) = 1.155717182804529;
        A(16, 11) = 1.869256859073442;
        A(16, 12) = 1.248319480877331;
        A(16, 13) = 1.452561957668774;
        A(16, 14) = 1.032246373642381;
        A(16, 15) = 0.07835159952372053;
        A(16, 16) = -0.2395853287373267;
        A(16, 17) = -1.903668638941256;
        A(16, 18) = -1.932664073589798;
        A(16, 19) = 0.9256300959984964;
        A(16, 20) = -1.182117061495755;
        A(16, 21) = -1.446111236241075;
        A(16, 22) = 0.3390374257755131;
        A(16, 23) = -0.4494365657264196;
        A(16, 24) = 0.1279145507538775;
        A(16, 25) = 0.4567557225277256;
        A(16, 26) = -0.7493268665953018;
        A(16, 27) = -0.5505426413816571;
        A(16, 28) = 0.1733257050568087;
        A(16, 29) = 1.05683774357112;
        A(16, 30) = 1.46912588992287;
        A(16, 31) = -0.07297995996596593;
        A(16, 32) = -1.412621285556534;
        A(16, 33) = 0.8224590356851858;
        A(16, 34) = 1.380881586238668;
        A(16, 35) = -0.2410218058690119;
        A(16, 36) = -1.284809438281624;
        A(16, 37) = 1.568008570239559;
        A(16, 38) = 0.2470780514531021;
        A(16, 39) = -0.3967985951945935;
        A(16, 40) = -0.4477674152984991;
        A(16, 41) = -0.6754732581672273;
        A(16, 42) = -0.7957056837577836;
        A(16, 43) = 0.3990396875309453;
        A(16, 44) = -0.2104729336202157;
        A(16, 45) = 1.137092254578229;
        A(16, 46) = 1.075977790536481;
        A(16, 47) = 1.216943073913638;
        A(16, 48) = 1.242510363554079;
        A(16, 49) = 0.4222667297663006;
        A(16, 50) = 1.190497758275268;
        A(16, 51) = 0.3693631235121102;
        A(16, 52) = -2.372917933739931;
        A(16, 53) = 0.3859453152315861;
        A(16, 54) = 0.1042881907762749;
        A(16, 55) = 1.705200187344074;
        A(16, 56) = 2.386229742380419;
        A(16, 57) = -0.6819537626619262;
        A(16, 58) = -0.7011679454639749;
        A(16, 59) = -0.540399226848198;
        A(16, 60) = 0.1592045279471424;
        A(16, 61) = -0.07034154557187104;
        A(16, 62) = 0.09004158801272982;
        A(16, 63) = 2.188985529160625;
        A(17, 0) = 1.299356869301176;
        A(17, 1) = -0.6662090012233732;
        A(17, 2) = 0.6376660515770116;
        A(17, 3) = 1.378273299838068;
        A(17, 4) = -0.1888517989171498;
        A(17, 5) = -1.266094688504092;
        A(17, 6) = -0.2343077268745587;
        A(17, 7) = 0.8402062735199516;
        A(17, 8) = 0.1531699454797562;
        A(17, 9) = 0.2933848732804216;
        A(17, 10) = -0.9209165571744223;
        A(17, 11) = 0.1981278572786056;
        A(17, 12) = 0.5236510073705284;
        A(17, 13) = 0.8410583239455554;
        A(17, 14) = -0.5665904858769175;
        A(17, 15) = 0.6259621872437292;
        A(17, 16) = 2.471282731118149;
        A(17, 17) = 0.7718250477688629;
        A(17, 18) = -0.6846236783635059;
        A(17, 19) = -1.972847519328608;
        A(17, 20) = -1.295881783305122;
        A(17, 21) = -0.7470957556259077;
        A(17, 22) = 0.505905515946226;
        A(17, 23) = -0.5855166192998506;
        A(17, 24) = 0.3804793089786037;
        A(17, 25) = 0.1556488458892625;
        A(17, 26) = 0.3614723017029961;
        A(17, 27) = -1.183704451097797;
        A(17, 28) = -1.476382982078889;
        A(17, 29) = 0.6709779434017484;
        A(17, 30) = 0.543222511178859;
        A(17, 31) = 0.02547010253764802;
        A(17, 32) = 0.5154958365953741;
        A(17, 33) = 0.02465806795860391;
        A(17, 34) = -0.1138275020732988;
        A(17, 35) = 0.9583566787486133;
        A(17, 36) = 0.5888752518189777;
        A(17, 37) = 1.179700539768146;
        A(17, 38) = -0.2256800239545257;
        A(17, 39) = 1.010738432994925;
        A(17, 40) = -0.1330059970187981;
        A(17, 41) = 0.3895155905542475;
        A(17, 42) = 0.7026476168153719;
        A(17, 43) = 0.8171893052479304;
        A(17, 44) = 0.6832695474463344;
        A(17, 45) = -0.677286671149189;
        A(17, 46) = 0.3794343904660872;
        A(17, 47) = -0.7419746699372327;
        A(17, 48) = 1.091683273059807;
        A(17, 49) = -2.13388127033015;
        A(17, 50) = 0.6295362409210717;
        A(17, 51) = 1.200023321809109;
        A(17, 52) = 0.8617021868471186;
        A(17, 53) = -0.3515517046092549;
        A(17, 54) = -0.4567999199246062;
        A(17, 55) = -1.013504780105621;
        A(17, 56) = 0.1181294803382046;
        A(17, 57) = -0.9864921938858793;
        A(17, 58) = -0.7309891297135731;
        A(17, 59) = -0.3566113175620845;
        A(17, 60) = 0.5433601494506299;
        A(17, 61) = -0.1326976163101934;
        A(17, 62) = 0.8839538862991055;
        A(17, 63) = -0.272954724426387;
        A(18, 0) = -1.049280388286974;
        A(18, 1) = -0.3167472054154024;
        A(18, 2) = -0.6161205199875934;
        A(18, 3) = 0.7295568411866894;
        A(18, 4) = -1.561035149485165;
        A(18, 5) = -0.3494726106827412;
        A(18, 6) = -0.451617270454;
        A(18, 7) = -0.07590245288336163;
        A(18, 8) = 0.1125455325934196;
        A(18, 9) = 0.2951066691169858;
        A(18, 10) = 0.6894547164929825;
        A(18, 11) = -0.7663531383886449;
        A(18, 12) = -0.708047388763361;
        A(18, 13) = -0.557601577441867;
        A(18, 14) = 1.098869062951255;
        A(18, 15) = 0.2843247771817947;
        A(18, 16) = -0.7005033315121096;
        A(18, 17) = -0.999377146050368;
        A(18, 18) = 0.2009331531985844;
        A(18, 19) = -0.1610344338302581;
        A(18, 20) = 0.5556289596361562;
        A(18, 21) = 2.116843231871048;
        A(18, 22) = 1.324135414697219;
        A(18, 23) = 1.849454807866492;
        A(18, 24) = 0.7888270522382038;
        A(18, 25) = -0.1181061921808727;
        A(18, 26) = -0.3102818478504696;
        A(18, 27) = -0.6375156691775805;
        A(18, 28) = 1.438733661638524;
        A(18, 29) = -0.01732581132216857;
        A(18, 30) = -1.355013197865509;
        A(18, 31) = -0.02154843677205005;
        A(18, 32) = 1.232474309165077;
        A(18, 33) = -0.7964561184647285;
        A(18, 34) = -0.5827282333299167;
        A(18, 35) = -0.07421953825509207;
        A(18, 36) = 2.280042997315957;
        A(18, 37) = 0.7882576974284378;
        A(18, 38) = 1.133787361664392;
        A(18, 39) = 0.9183742458867016;
        A(18, 40) = -1.270444782040769;
        A(18, 41) = -1.057658827192271;
        A(18, 42) = 0.3998742086705055;
        A(18, 43) = 0.2458366744162009;
        A(18, 44) = 0.2526355462420011;
        A(18, 45) = -0.3833415570830625;
        A(18, 46) = -1.351580727218303;
        A(18, 47) = 0.02810825244443387;
        A(18, 48) = -0.08976615237000415;
        A(18, 49) = -0.6213276482806092;
        A(18, 50) = -0.2348301825931859;
        A(18, 51) = -0.5187790631355878;
        A(18, 52) = -0.165154168095633;
        A(18, 53) = -0.4861521549335836;
        A(18, 54) = -0.0556452586445253;
        A(18, 55) = 0.7730214199726013;
        A(18, 56) = 0.6254152257082883;
        A(18, 57) = -1.902169292706553;
        A(18, 58) = 1.13900359663899;
        A(18, 59) = 0.5343385071775383;
        A(18, 60) = -0.05440941283841858;
        A(18, 61) = -0.2856825428388395;
        A(18, 62) = -0.3190374496075237;
        A(18, 63) = -1.763195386657731;
        A(19, 0) = -0.1447230587918676;
        A(19, 1) = -1.082319629461366;
        A(19, 2) = 0.5728987481500086;
        A(19, 3) = 1.009843169979766;
        A(19, 4) = 0.8412753603726555;
        A(19, 5) = -0.05556769045141217;
        A(19, 6) = 0.5313719469794596;
        A(19, 7) = 0.159153614981141;
        A(19, 8) = -1.562531641502883;
        A(19, 9) = -0.9248694724052538;
        A(19, 10) = -0.1615989894329072;
        A(19, 11) = -1.183658226512254;
        A(19, 12) = 0.5246576433542112;
        A(19, 13) = 0.03283266662364206;
        A(19, 14) = -1.808885601526254;
        A(19, 15) = -1.041745275905832;
        A(19, 16) = 0.04764016258002891;
        A(19, 17) = 0.8879564551225977;
        A(19, 18) = 0.1310265327854234;
        A(19, 19) = 1.780616183475125;
        A(19, 20) = 0.3896038643592771;
        A(19, 21) = -0.1110445196972953;
        A(19, 22) = -0.9198987237341888;
        A(19, 23) = 0.8743486315327034;
        A(19, 24) = 0.5444941288565122;
        A(19, 25) = -2.769094655339183;
        A(19, 26) = 0.3101224765410934;
        A(19, 27) = 1.201117907420153;
        A(19, 28) = 1.402413744720443;
        A(19, 29) = -0.3192278998764729;
        A(19, 30) = -0.7795094798593759;
        A(19, 31) = 1.523131887916028;
        A(19, 32) = -1.538239181347353;
        A(19, 33) = 0.6494691995977712;
        A(19, 34) = 0.3642951824584554;
        A(19, 35) = 1.098347659990579;
        A(19, 36) = -0.4497684347132306;
        A(19, 37) = 1.399924542788678;
        A(19, 38) = 0.601511361769304;
        A(19, 39) = 0.7126427066698063;
        A(19, 40) = 0.7232926664084303;
        A(19, 41) = 0.7401039262324454;
        A(19, 42) = 0.1860903078153098;
        A(19, 43) = 1.308684251372512;
        A(19, 44) = 0.8500253960645753;
        A(19, 45) = 0.156388984556892;
        A(19, 46) = -0.1579452251182275;
        A(19, 47) = -0.6008491858958682;
        A(19, 48) = -0.225412667076567;
        A(19, 49) = 0.4924764294352691;
        A(19, 50) = 0.5096922090641104;
        A(19, 51) = -1.251103906633309;
        A(19, 52) = 0.2643468034060572;
        A(19, 53) = 2.180416769567206;
        A(19, 54) = -0.5488036503182342;
        A(19, 55) = 0.7311656801319572;
        A(19, 56) = 0.4306132523758431;
        A(19, 57) = -2.497606124617596;
        A(19, 58) = 1.312508924284509;
        A(19, 59) = -0.7812836888837403;
        A(19, 60) = 0.9707818838393488;
        A(19, 61) = 0.008639204081387207;
        A(19, 62) = -0.09895283797010455;
        A(19, 63) = 0.9952555435357486;
        A(20, 0) = 0.6707091244255002;
        A(20, 1) = -1.771521601697502;
        A(20, 2) = 0.5824827639007556;
        A(20, 3) = 1.307165433262584;
        A(20, 4) = 2.039683949753995;
        A(20, 5) = -0.5988998132151934;
        A(20, 6) = -0.6859609250879523;
        A(20, 7) = -1.242263795156991;
        A(20, 8) = 1.39739674753594;
        A(20, 9) = 1.384149859022851;
        A(20, 10) = 1.118483916304244;
        A(20, 11) = -1.291233453968434;
        A(20, 12) = 0.9502174154601171;
        A(20, 13) = -1.026989416118589;
        A(20, 14) = -1.225819339196707;
        A(20, 15) = -2.017725184844413;
        A(20, 16) = -0.6510050488297097;
        A(20, 17) = -1.408486358798831;
        A(20, 18) = -0.6745953746595096;
        A(20, 19) = -1.280934971510577;
        A(20, 20) = 1.756107929803646;
        A(20, 21) = 0.8253115292068479;
        A(20, 22) = -0.8881304300519393;
        A(20, 23) = 0.8528955122356724;
        A(20, 24) = -0.8433222803328526;
        A(20, 25) = -1.476701512438963;
        A(20, 26) = 0.5256756225866933;
        A(20, 27) = -0.8349603863147876;
        A(20, 28) = 0.4764685902279059;
        A(20, 29) = -0.8741615619771875;
        A(20, 30) = 1.025204107048679;
        A(20, 31) = 0.01647786266548999;
        A(20, 32) = 0.7309904270200848;
        A(20, 33) = 0.5962457213227541;
        A(20, 34) = 0.498199939028321;
        A(20, 35) = 0.513976190372452;
        A(20, 36) = -0.03476633668848317;
        A(20, 37) = -1.06912232571106;
        A(20, 38) = 0.8882729078567266;
        A(20, 39) = 0.5252719313174158;
        A(20, 40) = -2.186097529906519;
        A(20, 41) = -0.9133255709191438;
        A(20, 42) = -1.174862597510488;
        A(20, 43) = -1.021435430020475;
        A(20, 44) = 1.647972657244131;
        A(20, 45) = -1.248286237704669;
        A(20, 46) = 1.407445949912479;
        A(20, 47) = 1.996971035233727;
        A(20, 48) = -0.1459718004547665;
        A(20, 49) = -0.3035201023400398;
        A(20, 50) = 1.24278277301886;
        A(20, 51) = -1.714240598978482;
        A(20, 52) = 0.891369997252053;
        A(20, 53) = -1.903894937713268;
        A(20, 54) = 1.241349957913424;
        A(20, 55) = -0.326200304745942;
        A(20, 56) = -0.296909363612946;
        A(20, 57) = 0.7609099883947542;
        A(20, 58) = 0.4705555127828185;
        A(20, 59) = 0.6810510237211159;
        A(20, 60) = 0.6150047962857246;
        A(20, 61) = 0.834718812130855;
        A(20, 62) = -1.047023727639636;
        A(20, 63) = 1.920441910581215;
        A(21, 0) = 0.01312773387816915;
        A(21, 1) = 1.255240425526064;
        A(21, 2) = 2.302080339062968;
        A(21, 3) = -1.668712406405302;
        A(21, 4) = 1.686212679185684;
        A(21, 5) = -0.8347961319680564;
        A(21, 6) = -0.3551610547221547;
        A(21, 7) = -0.3521546099609333;
        A(21, 8) = -0.6075254409136255;
        A(21, 9) = -0.917049802404859;
        A(21, 10) = -0.2857344747215236;
        A(21, 11) = -1.624709635717209;
        A(21, 12) = -0.160660030151431;
        A(21, 13) = 0.2404067350174036;
        A(21, 14) = -0.3384966166901625;
        A(21, 15) = -0.1709350562407352;
        A(21, 16) = 0.02529018175598196;
        A(21, 17) = 0.3967686064776685;
        A(21, 18) = 0.8862768637959926;
        A(21, 19) = 1.076549292221753;
        A(21, 20) = 0.0181058942813506;
        A(21, 21) = -0.0765755130406222;
        A(21, 22) = 1.762051861315364;
        A(21, 23) = -1.220026404640004;
        A(21, 24) = 1.080287872149704;
        A(21, 25) = -2.232192917192815;
        A(21, 26) = -0.5392228538347076;
        A(21, 27) = -0.002088956169105686;
        A(21, 28) = -1.158270148994606;
        A(21, 29) = -0.3941129274714312;
        A(21, 30) = 0.3981120074884456;
        A(21, 31) = 0.9096765291247124;
        A(21, 32) = 0.1222553073013505;
        A(21, 33) = -1.573614271991227;
        A(21, 34) = 0.3435253772959386;
        A(21, 35) = -0.6369967922241335;
        A(21, 36) = -1.585538833251739;
        A(21, 37) = 0.5667015022431166;
        A(21, 38) = 0.3062051259292891;
        A(21, 39) = 0.5095620037737398;
        A(21, 40) = -0.4360940619854841;
        A(21, 41) = -0.7266426858207484;
        A(21, 42) = 1.123681829422702;
        A(21, 43) = -0.3914628741889172;
        A(21, 44) = -0.2272783859932919;
        A(21, 45) = -2.014149471799019;
        A(21, 46) = 1.227319580975065;
        A(21, 47) = 0.131963523420057;
        A(21, 48) = -0.2841047049896897;
        A(21, 49) = -0.5116349280472858;
        A(21, 50) = -1.201504600587476;
        A(21, 51) = 0.6175167843868297;
        A(21, 52) = -2.419234112854629;
        A(21, 53) = 2.393376231481213;
        A(21, 54) = 0.01158365873465993;
        A(21, 55) = 1.272846453655518;
        A(21, 56) = -0.7668756661075279;
        A(21, 57) = -0.2405605197746237;
        A(21, 58) = -0.2783537451645717;
        A(21, 59) = -1.178134371648747;
        A(21, 60) = 0.6269734311449725;
        A(21, 61) = 1.654780792722046;
        A(21, 62) = -0.7353312357901691;
        A(21, 63) = 0.6705022400032857;
        A(22, 0) = 0.3582893723510124;
        A(22, 1) = -0.4982523641977431;
        A(22, 2) = -0.8516522123255708;
        A(22, 3) = 2.669961596207008;
        A(22, 4) = 2.050925788045772;
        A(22, 5) = -0.9130875944668251;
        A(22, 6) = -1.126549646569604;
        A(22, 7) = 0.4304733932271891;
        A(22, 8) = -0.5991392752113306;
        A(22, 9) = 1.123637868846699;
        A(22, 10) = -1.060452255332401;
        A(22, 11) = 1.930803433519195;
        A(22, 12) = 0.3636714130155719;
        A(22, 13) = 2.193981697655806;
        A(22, 14) = -0.7909756305932743;
        A(22, 15) = -2.108274756070689;
        A(22, 16) = -0.3277003356010174;
        A(22, 17) = 0.2316335369793465;
        A(22, 18) = 0.8552853596159504;
        A(22, 19) = 0.621654054611381;
        A(22, 20) = -0.3890522498877568;
        A(22, 21) = 0.3402017048193503;
        A(22, 22) = -1.389889289898235;
        A(22, 23) = 1.349176363895809;
        A(22, 24) = 0.1022652380211584;
        A(22, 25) = 0.0719213061193478;
        A(22, 26) = 0.34670219953479;
        A(22, 27) = 1.000987250783701;
        A(22, 28) = -0.2790388596747666;
        A(22, 29) = 0.6348482115955367;
        A(22, 30) = -0.3929688864578911;
        A(22, 31) = -0.5265464423138652;
        A(22, 32) = -1.308117694808687;
        A(22, 33) = 0.2744094084665677;
        A(22, 34) = 0.7616811859032433;
        A(22, 35) = -1.299813614052154;
        A(22, 36) = -0.3660104293112121;
        A(22, 37) = 1.562823262594358;
        A(22, 38) = -1.899903631343594;
        A(22, 39) = 0.7092076777331279;
        A(22, 40) = 0.7252721708777914;
        A(22, 41) = 1.154202020132607;
        A(22, 42) = -0.259764295980754;
        A(22, 43) = 0.4458983691030095;
        A(22, 44) = -1.650288792735692;
        A(22, 45) = 0.6052489015133866;
        A(22, 46) = -0.5866446487463987;
        A(22, 47) = 2.312412148235806;
        A(22, 48) = 0.3544697150638939;
        A(22, 49) = -0.05435468274746231;
        A(22, 50) = -0.5761469613668331;
        A(22, 51) = -2.175677824124108;
        A(22, 52) = 0.08413548645216665;
        A(22, 53) = 1.038520165468715;
        A(22, 54) = 1.112376982312994;
        A(22, 55) = 0.9986091672381179;
        A(22, 56) = 0.4950312124116866;
        A(22, 57) = -0.990429745934672;
        A(22, 58) = -1.282732510198892;
        A(22, 59) = -0.6358189499894007;
        A(22, 60) = 0.2624575912283815;
        A(22, 61) = -0.184500859528184;
        A(22, 62) = 0.08239580319488378;
        A(22, 63) = 1.540241129888579;
        A(23, 0) = 0.979026223730317;
        A(23, 1) = 0.8106357746673443;
        A(23, 2) = 1.406888847824083;
        A(23, 3) = 1.290533364843277;
        A(23, 4) = 0.6172438447305821;
        A(23, 5) = 0.0118766913985442;
        A(23, 6) = 0.2813498438890229;
        A(23, 7) = 0.2556350441940437;
        A(23, 8) = -0.7884712931548025;
        A(23, 9) = 1.997286611332841;
        A(23, 10) = 0.8166065873219469;
        A(23, 11) = 0.3184285938661053;
        A(23, 12) = 1.169956146437959;
        A(23, 13) = -0.5810123396835504;
        A(23, 14) = 0.4024964690289991;
        A(23, 15) = 2.191486077186675;
        A(23, 16) = -0.5072185808385374;
        A(23, 17) = -0.4816898512035593;
        A(23, 18) = -0.6717749215171147;
        A(23, 19) = -0.1284196590704351;
        A(23, 20) = -1.386143370385465;
        A(23, 21) = -1.000326496204175;
        A(23, 22) = -1.518519423449922;
        A(23, 23) = -0.9797196568706559;
        A(23, 24) = 0.3480575585512166;
        A(23, 25) = 1.167788784982865;
        A(23, 26) = -0.6210294041122252;
        A(23, 27) = 0.7828913000840978;
        A(23, 28) = 0.5482168448902136;
        A(23, 29) = 0.2341015019379585;
        A(23, 30) = -1.269326327303646;
        A(23, 31) = 1.430747621520462;
        A(23, 32) = 0.008249493134789131;
        A(23, 33) = 0.5234906697186048;
        A(23, 34) = 0.8247604343949184;
        A(23, 35) = 0.3979620060195382;
        A(23, 36) = 0.344472563335566;
        A(23, 37) = 1.661215529654211;
        A(23, 38) = 0.5991641578430595;
        A(23, 39) = -1.194517812250319;
        A(23, 40) = 1.398682683316965;
        A(23, 41) = 0.5155794099985669;
        A(23, 42) = -0.2737681773489762;
        A(23, 43) = 0.8879810876365629;
        A(23, 44) = -0.126975914109156;
        A(23, 45) = -0.1312153541876674;
        A(23, 46) = 0.2717899233531129;
        A(23, 47) = 1.261508829850632;
        A(23, 48) = -2.898417529921678;
        A(23, 49) = 2.265254024753383;
        A(23, 50) = -0.1416039546462801;
        A(23, 51) = -1.402953918174573;
        A(23, 52) = -0.9484710600257691;
        A(23, 53) = 2.47424204688702;
        A(23, 54) = -0.3959077678102141;
        A(23, 55) = 1.341897481411155;
        A(23, 56) = -1.16646075246072;
        A(23, 57) = 0.7201999484560908;
        A(23, 58) = 1.014831891745148;
        A(23, 59) = 1.223915623553173;
        A(23, 60) = 2.054169541015211;
        A(23, 61) = 0.6138437830624632;
        A(23, 62) = -0.5444227806061633;
        A(23, 63) = 0.354682065394093;
        A(24, 0) = 0.03691989912325526;
        A(24, 1) = 0.1994423254786603;
        A(24, 2) = -0.1718275104494613;
        A(24, 3) = 0.03933571550240817;
        A(24, 4) = -0.006022207858259538;
        A(24, 5) = 2.720575476684702;
        A(24, 6) = -0.439497610605433;
        A(24, 7) = 0.7840870004000672;
        A(24, 8) = -0.6031163067466393;
        A(24, 9) = 0.1439718324656387;
        A(24, 10) = 2.707154766719272;
        A(24, 11) = -2.403094550281141;
        A(24, 12) = -2.409594281824195;
        A(24, 13) = 0.9742471723724829;
        A(24, 14) = -0.4319867358492846;
        A(24, 15) = -1.118397006421621;
        A(24, 16) = 1.780597711886952;
        A(24, 17) = 0.2807436371603846;
        A(24, 18) = -1.827242568446102;
        A(24, 19) = -0.5517461832784401;
        A(24, 20) = 1.721446525805026;
        A(24, 21) = -0.5532779673785071;
        A(24, 22) = 0.2870033673779083;
        A(24, 23) = -0.8457283753362441;
        A(24, 24) = 1.253949743453914;
        A(24, 25) = 0.1313561224745704;
        A(24, 26) = 1.80271126813167;
        A(24, 27) = -2.360617730233994;
        A(24, 28) = 0.2909207416378284;
        A(24, 29) = -0.9797990026884936;
        A(24, 30) = 0.5000363042662829;
        A(24, 31) = -0.9620858251474863;
        A(24, 32) = 0.9247001433700895;
        A(24, 33) = -0.4831111956753482;
        A(24, 34) = -1.436528699759962;
        A(24, 35) = 0.1179670216428169;
        A(24, 36) = -0.2442378297043674;
        A(24, 37) = -0.1297712321301008;
        A(24, 38) = 0.8464639359108441;
        A(24, 39) = -1.016937804228921;
        A(24, 40) = 0.5184431521136625;
        A(24, 41) = 0.4659450415004182;
        A(24, 42) = -1.717436757594219;
        A(24, 43) = 0.5105955297394806;
        A(24, 44) = 0.09746254204000565;
        A(24, 45) = 0.1766757543820718;
        A(24, 46) = 1.113729449101763;
        A(24, 47) = 0.8010182136053613;
        A(24, 48) = 1.905851728989641;
        A(24, 49) = -0.03017071876792291;
        A(24, 50) = -0.5482711665970961;
        A(24, 51) = -0.418899998377051;
        A(24, 52) = -0.1138466655960242;
        A(24, 53) = -0.8886011131055839;
        A(24, 54) = 0.7288882710164366;
        A(24, 55) = 0.2139634371315466;
        A(24, 56) = 0.3387148225165162;
        A(24, 57) = -0.3016538935722921;
        A(24, 58) = -0.1814791559571324;
        A(24, 59) = 0.3052089202324029;
        A(24, 60) = 0.4696823834011722;
        A(24, 61) = 1.460261037683607;
        A(24, 62) = 1.691443343008102;
        A(24, 63) = -1.085146871591086;
        A(25, 0) = 0.9024028853750432;
        A(25, 1) = -1.414315214880239;
        A(25, 2) = -1.207600039603135;
        A(25, 3) = 0.4060108271000659;
        A(25, 4) = 0.161088323363818;
        A(25, 5) = 2.868395240758029;
        A(25, 6) = 0.3717122549849486;
        A(25, 7) = -1.514541904319216;
        A(25, 8) = 1.375296485452048;
        A(25, 9) = -2.526742913260118;
        A(25, 10) = 0.3031690496679482;
        A(25, 11) = -2.625790906995985;
        A(25, 12) = 0.06205375549615918;
        A(25, 13) = 0.301983984832861;
        A(25, 14) = -1.166765008406818;
        A(25, 15) = -0.2385183040972884;
        A(25, 16) = -1.332571994350307;
        A(25, 17) = -1.172855733283838;
        A(25, 18) = -0.4509366547231412;
        A(25, 19) = 1.850788611648308;
        A(25, 20) = 0.3477050612502675;
        A(25, 21) = -0.6111648702179138;
        A(25, 22) = -1.217354205211618;
        A(25, 23) = 1.038681483444071;
        A(25, 24) = -0.004469716054318891;
        A(25, 25) = -0.366982710257819;
        A(25, 26) = -0.2745319528307179;
        A(25, 27) = 1.680452839711562;
        A(25, 28) = -1.186576062458578;
        A(25, 29) = 0.6890448265970862;
        A(25, 30) = -1.619762852926832;
        A(25, 31) = 0.2046578287835967;
        A(25, 32) = 0.4759126172131512;
        A(25, 33) = -1.088986421935387;
        A(25, 34) = 0.5446690180068113;
        A(25, 35) = -0.7633604867691701;
        A(25, 36) = -0.4310342532535366;
        A(25, 37) = 1.101247636056101;
        A(25, 38) = 0.3619736394143817;
        A(25, 39) = -0.8885306083578749;
        A(25, 40) = 0.9781164802870236;
        A(25, 41) = 0.4012292995707085;
        A(25, 42) = -0.03369897613614391;
        A(25, 43) = 2.218769988655355;
        A(25, 44) = 0.6037537942989129;
        A(25, 45) = -0.9236237864002735;
        A(25, 46) = 0.1132867675349507;
        A(25, 47) = 0.1508046716660553;
        A(25, 48) = 1.970791902848634;
        A(25, 49) = -1.017285066036884;
        A(25, 50) = -0.7268705969518116;
        A(25, 51) = -0.56483555168519;
        A(25, 52) = -1.855814628442383;
        A(25, 53) = -0.3779491381172651;
        A(25, 54) = 2.069852155743848;
        A(25, 55) = 1.580622959856723;
        A(25, 56) = 1.395676798162177;
        A(25, 57) = 0.2971439421239423;
        A(25, 58) = 0.7227478965839078;
        A(25, 59) = 0.1525789870093906;
        A(25, 60) = 0.461993728068077;
        A(25, 61) = 1.423816049721731;
        A(25, 62) = -1.431845550570695;
        A(25, 63) = 0.9229050569930528;
        A(26, 0) = 0.02609394019934516;
        A(26, 1) = 0.07791479694627;
        A(26, 2) = -0.5929763502506263;
        A(26, 3) = 0.07225315836326193;
        A(26, 4) = 3.525844281496972;
        A(26, 5) = 1.2622401047734;
        A(26, 6) = 1.322421157233274;
        A(26, 7) = 2.215255897752826;
        A(26, 8) = 0.5029060034876366;
        A(26, 9) = -0.8321911119361927;
        A(26, 10) = -0.367112777946757;
        A(26, 11) = -0.2917178532181209;
        A(26, 12) = -0.6239402121499655;
        A(26, 13) = -1.155880662858894;
        A(26, 14) = -0.185993927918082;
        A(26, 15) = -0.01365196236734064;
        A(26, 16) = 0.153876300568553;
        A(26, 17) = 0.7273172823262631;
        A(26, 18) = -0.8029244562552331;
        A(26, 19) = -0.1170891883158856;
        A(26, 20) = 0.4661264886735688;
        A(26, 21) = -0.8829361192244355;
        A(26, 22) = 0.3912000903605619;
        A(26, 23) = -0.6372788650095568;
        A(26, 24) = -0.2899559499723326;
        A(26, 25) = -0.4296432879082659;
        A(26, 26) = 0.1000342705901126;
        A(26, 27) = -2.480531477489399;
        A(26, 28) = -0.3840532443298878;
        A(26, 29) = -0.4366224278446555;
        A(26, 30) = -0.1842226659397504;
        A(26, 31) = -0.5973133957093814;
        A(26, 32) = 0.6970708606579983;
        A(26, 33) = 0.470225365454273;
        A(26, 34) = -1.067699548834856;
        A(26, 35) = -0.4464610196190129;
        A(26, 36) = -0.04984478230852933;
        A(26, 37) = -0.9097091177479827;
        A(26, 38) = -2.557301432358045;
        A(26, 39) = -0.07900485125503635;
        A(26, 40) = 1.255712208070094;
        A(26, 41) = 3.057517235211464;
        A(26, 42) = -0.4035862661899012;
        A(26, 43) = -0.6025885959268974;
        A(26, 44) = 0.6200176089485648;
        A(26, 45) = 0.6570324331259723;
        A(26, 46) = -0.465179174390646;
        A(26, 47) = -1.300302370149957;
        A(26, 48) = 0.4546061914649708;
        A(26, 49) = 1.127182300866769;
        A(26, 50) = -0.956645466352103;
        A(26, 51) = -1.260211308871584;
        A(26, 52) = 0.1219365529982226;
        A(26, 53) = -0.8108756570715682;
        A(26, 54) = 0.5887459198061662;
        A(26, 55) = 0.118286022655947;
        A(26, 56) = 0.7606975909060434;
        A(26, 57) = -0.8010475973444238;
        A(26, 58) = -1.956686019538606;
        A(26, 59) = -0.0105863088060766;
        A(26, 60) = -0.1241905632998308;
        A(26, 61) = 1.474858536929303;
        A(26, 62) = 0.8618404299950327;
        A(26, 63) = -1.433755407589862;
        A(27, 0) = -0.516349025761889;
        A(27, 1) = -0.9582231679662977;
        A(27, 2) = -0.6224459405156128;
        A(27, 3) = -0.3921589086898902;
        A(27, 4) = -0.4396102771883829;
        A(27, 5) = -0.601375089185037;
        A(27, 6) = 0.4765539219644238;
        A(27, 7) = 1.926293275660941;
        A(27, 8) = -0.7062070939939177;
        A(27, 9) = 2.588937857028264;
        A(27, 10) = -0.8620948090010725;
        A(27, 11) = -1.490017504080538;
        A(27, 12) = -1.391152423293958;
        A(27, 13) = 1.360082005839139;
        A(27, 14) = -1.687670347987389;
        A(27, 15) = -1.528262848313553;
        A(27, 16) = -2.014391657937645;
        A(27, 17) = 0.1670086632998819;
        A(27, 18) = -0.9795467761688957;
        A(27, 19) = -0.01752013590591731;
        A(27, 20) = -0.1818063760915284;
        A(27, 21) = 1.627859939540969;
        A(27, 22) = 0.01541798873815686;
        A(27, 23) = -1.624124271144562;
        A(27, 24) = -0.7679459253403701;
        A(27, 25) = 0.1424877120012613;
        A(27, 26) = 1.002273229926869;
        A(27, 27) = 1.418165033632953;
        A(27, 28) = 0.05785065883585979;
        A(27, 29) = 1.176959928890035;
        A(27, 30) = 1.642929117016319;
        A(27, 31) = -0.2429903944070973;
        A(27, 32) = 0.465137198889968;
        A(27, 33) = -0.9841549481068423;
        A(27, 34) = -1.376022476431812;
        A(27, 35) = 1.400069164205201;
        A(27, 36) = 0.1409222692251478;
        A(27, 37) = -0.6418481846122094;
        A(27, 38) = 1.363364336907177;
        A(27, 39) = -1.321243511201788;
        A(27, 40) = 0.8847792440347899;
        A(27, 41) = -0.2270216474946418;
        A(27, 42) = -1.963022237566713;
        A(27, 43) = 0.6463617919386884;
        A(27, 44) = 0.7387561898074022;
        A(27, 45) = 2.281187019759889;
        A(27, 46) = -0.5112039731153159;
        A(27, 47) = 1.289860827892325;
        A(27, 48) = 0.7702797812065823;
        A(27, 49) = -0.2886411579443238;
        A(27, 50) = 1.267231954441443;
        A(27, 51) = -0.03380884411750341;
        A(27, 52) = 0.4592120728395838;
        A(27, 53) = 1.007727328936236;
        A(27, 54) = -0.4271258189770338;
        A(27, 55) = -0.7201916917200162;
        A(27, 56) = 0.2391153542721428;
        A(27, 57) = 0.8582519954911532;
        A(27, 58) = 0.9173985111347197;
        A(27, 59) = -1.66888031240844;
        A(27, 60) = 1.003555511315594;
        A(27, 61) = 0.3742193309476131;
        A(27, 62) = -1.70286032468175;
        A(27, 63) = 1.749175942399696;
        A(28, 0) = -1.130108900236731;
        A(28, 1) = -0.8555540834664427;
        A(28, 2) = 0.6220427478443702;
        A(28, 3) = 0.2669049963381642;
        A(28, 4) = -0.7846291782016455;
        A(28, 5) = 0.745837349487163;
        A(28, 6) = 0.06279766441365707;
        A(28, 7) = 0.1693540808594893;
        A(28, 8) = -1.294574678933735;
        A(28, 9) = -0.9047081100483185;
        A(28, 10) = 0.08230720739678947;
        A(28, 11) = -1.550949477969435;
        A(28, 12) = 1.37972807678016;
        A(28, 13) = 0.3095231041678383;
        A(28, 14) = 0.8656572112883948;
        A(28, 15) = -0.6780805542010464;
        A(28, 16) = -0.3644464550416812;
        A(28, 17) = 0.6489328376511847;
        A(28, 18) = -0.1302509675278128;
        A(28, 19) = 1.261921705806301;
        A(28, 20) = 1.308183813451928;
        A(28, 21) = 1.723471718287453;
        A(28, 22) = -0.03268354190199029;
        A(28, 23) = -0.6492979252539395;
        A(28, 24) = 0.3581807736014893;
        A(28, 25) = -0.9712558385982174;
        A(28, 26) = -2.283055655000713;
        A(28, 27) = -0.2963966812912818;
        A(28, 28) = 0.4131659474560548;
        A(28, 29) = -1.419320075911733;
        A(28, 30) = 3.160951793722053;
        A(28, 31) = 0.0617722385976801;
        A(28, 32) = 1.183239865943045;
        A(28, 33) = 0.004455971132272741;
        A(28, 34) = 1.148800963982245;
        A(28, 35) = -0.4433551396618204;
        A(28, 36) = -0.502775698459574;
        A(28, 37) = 0.9370455018144678;
        A(28, 38) = -0.2808485079629703;
        A(28, 39) = -0.5490885870051411;
        A(28, 40) = 0.8043737204355997;
        A(28, 41) = 0.5261285834474233;
        A(28, 42) = -1.343337233509221;
        A(28, 43) = 0.4665156171122393;
        A(28, 44) = -1.081274569116233;
        A(28, 45) = -0.7256998167709964;
        A(28, 46) = 1.23281349638603;
        A(28, 47) = 2.36424355122925;
        A(28, 48) = -0.6627044723842506;
        A(28, 49) = 1.492195273459497;
        A(28, 50) = 0.3108232072185678;
        A(28, 51) = -1.353246858818123;
        A(28, 52) = 0.2416946858651968;
        A(28, 53) = -0.4518218593959149;
        A(28, 54) = -0.1863377583902383;
        A(28, 55) = 2.77374273788821;
        A(28, 56) = 1.453353138104914;
        A(28, 57) = -0.3543679296548252;
        A(28, 58) = -1.345307578954206;
        A(28, 59) = 0.2914892309882365;
        A(28, 60) = -1.009234546257347;
        A(28, 61) = -1.201183261592805;
        A(28, 62) = 0.1396480739504674;
        A(28, 63) = 0.0001580520441376145;
        A(29, 0) = -1.476277653195558;
        A(29, 1) = -1.232147982677682;
        A(29, 2) = 2.295492628334051;
        A(29, 3) = 0.1627772609206032;
        A(29, 4) = -1.150927499224313;
        A(29, 5) = -0.6421618917595376;
        A(29, 6) = 1.857723510624607;
        A(29, 7) = 0.9909588340403145;
        A(29, 8) = -1.032439683210113;
        A(29, 9) = 0.1638946112142855;
        A(29, 10) = -1.565772114002814;
        A(29, 11) = 1.185472107024419;
        A(29, 12) = -1.175349091591128;
        A(29, 13) = 0.9602970645534024;
        A(29, 14) = -0.1955990948119341;
        A(29, 15) = -0.2014609645297603;
        A(29, 16) = -0.09902170447189267;
        A(29, 17) = -0.5669460139981855;
        A(29, 18) = -0.2478676805485759;
        A(29, 19) = 0.5579863201711375;
        A(29, 20) = -1.328501528682123;
        A(29, 21) = -0.9902914455213396;
        A(29, 22) = -0.2195983149287429;
        A(29, 23) = -0.01321120938729149;
        A(29, 24) = -0.9746673019283206;
        A(29, 25) = -0.007163874180342236;
        A(29, 26) = 0.2979281808584803;
        A(29, 27) = 0.3564159510222097;
        A(29, 28) = 0.5456549814215048;
        A(29, 29) = -0.4051745197995077;
        A(29, 30) = 0.6288990750877115;
        A(29, 31) = 1.017827640245488;
        A(29, 32) = 0.02361511879004847;
        A(29, 33) = -0.5181378856021857;
        A(29, 34) = 1.119297962907194;
        A(29, 35) = 0.8059810716355857;
        A(29, 36) = -1.841412231137548;
        A(29, 37) = 1.271806823501531;
        A(29, 38) = 0.5855832811765923;
        A(29, 39) = 0.482565759249995;
        A(29, 40) = 0.7823178426460135;
        A(29, 41) = -0.9100790171503131;
        A(29, 42) = 0.1941845077222625;
        A(29, 43) = 1.080924431931728;
        A(29, 44) = 0.5331728733374628;
        A(29, 45) = -0.864024872952227;
        A(29, 46) = 0.1626688751568583;
        A(29, 47) = -0.1015798467379153;
        A(29, 48) = 1.961554634400853;
        A(29, 49) = 0.9235683220239875;
        A(29, 50) = 0.9782979738964061;
        A(29, 51) = -0.2796515974465982;
        A(29, 52) = -0.5245604328225693;
        A(29, 53) = -0.03648791557758385;
        A(29, 54) = 0.2551624881885273;
        A(29, 55) = -0.9719620141332975;
        A(29, 56) = 1.362780007535288;
        A(29, 57) = -1.896298718947816;
        A(29, 58) = 0.5912846341259587;
        A(29, 59) = -0.7703297690462404;
        A(29, 60) = -0.473127572570183;
        A(29, 61) = 0.7169590629344903;
        A(29, 62) = 1.139897419287395;
        A(29, 63) = -0.7391600307478958;
        A(30, 0) = 1.151142371876862;
        A(30, 1) = -0.8438059789040117;
        A(30, 2) = -1.313961585723616;
        A(30, 3) = -2.099338434954726;
        A(30, 4) = -1.26032113569874;
        A(30, 5) = -0.6408090444056586;
        A(30, 6) = -0.8658497978747625;
        A(30, 7) = -0.9590182560658538;
        A(30, 8) = -1.58772192617479;
        A(30, 9) = -1.772256113078475;
        A(30, 10) = -1.008770600518273;
        A(30, 11) = -0.7107772106347566;
        A(30, 12) = -1.214035018590188;
        A(30, 13) = -0.1108095106901146;
        A(30, 14) = 1.462240604354081;
        A(30, 15) = -1.133471083789827;
        A(30, 16) = -0.5444409850604384;
        A(30, 17) = 0.05433741286630977;
        A(30, 18) = 1.029515839037896;
        A(30, 19) = -0.4281889217962239;
        A(30, 20) = 0.578233752389274;
        A(30, 21) = -0.05526744672008403;
        A(30, 22) = -0.5536621103629115;
        A(30, 23) = -0.02705112199795951;
        A(30, 24) = -0.5018086367817929;
        A(30, 25) = -1.159803935382081;
        A(30, 26) = 0.591941758330929;
        A(30, 27) = -0.1643658399370364;
        A(30, 28) = -0.7127882260832;
        A(30, 29) = -1.322700767770379;
        A(30, 30) = -0.3700440776931771;
        A(30, 31) = 0.2543025876509431;
        A(30, 32) = -2.582898606321643;
        A(30, 33) = 0.9982113752312388;
        A(30, 34) = 1.24391542744844;
        A(30, 35) = -0.5842040182968918;
        A(30, 36) = -1.252647122689415;
        A(30, 37) = 0.9366840156585986;
        A(30, 38) = -0.7193305726855463;
        A(30, 39) = 1.892187640575866;
        A(30, 40) = 0.4835524326710725;
        A(30, 41) = 0.04888643916420993;
        A(30, 42) = 0.1105478490362804;
        A(30, 43) = -1.691269979704362;
        A(30, 44) = -0.566560325041217;
        A(30, 45) = -1.467392156604219;
        A(30, 46) = 0.3166644571065079;
        A(30, 47) = -0.7700098896550935;
        A(30, 48) = 2.031753420307275;
        A(30, 49) = 0.5766685550225877;
        A(30, 50) = -0.9393974867489182;
        A(30, 51) = -0.9913224021616643;
        A(30, 52) = -0.6456500277528799;
        A(30, 53) = -0.6382493201825784;
        A(30, 54) = -0.1513787409737867;
        A(30, 55) = 0.988925670458281;
        A(30, 56) = 1.720993338938634;
        A(30, 57) = -0.2999011182638746;
        A(30, 58) = -2.179483613451112;
        A(30, 59) = 0.9603281362022733;
        A(30, 60) = -0.3352948330629338;
        A(30, 61) = 0.4186602071649935;
        A(30, 62) = 1.453933629565421;
        A(30, 63) = 0.161635128759166;
        A(31, 0) = 1.374511450477159;
        A(31, 1) = 0.881101784131851;
        A(31, 2) = -1.448195440076689;
        A(31, 3) = 1.298817751109545;
        A(31, 4) = -0.1574898117653479;
        A(31, 5) = 0.7982131434075004;
        A(31, 6) = -0.3646421178916153;
        A(31, 7) = 1.203952815303725;
        A(31, 8) = 2.624914133846509;
        A(31, 9) = 0.7890248777397826;
        A(31, 10) = 0.27363671058845;
        A(31, 11) = 1.219345385941715;
        A(31, 12) = 0.4045476136991858;
        A(31, 13) = 0.2959576334498422;
        A(31, 14) = 1.861568639713207;
        A(31, 15) = -0.4885508364565987;
        A(31, 16) = 2.681524452732038;
        A(31, 17) = 0.01043578145798672;
        A(31, 18) = 2.042087489693576;
        A(31, 19) = 0.304072666466162;
        A(31, 20) = 0.8151167647037967;
        A(31, 21) = 1.257671440584185;
        A(31, 22) = 0.4431316362400069;
        A(31, 23) = 0.4871853692295148;
        A(31, 24) = -0.7120639731447598;
        A(31, 25) = 0.3385948113026957;
        A(31, 26) = -0.5176133952824265;
        A(31, 27) = -0.4060131100075348;
        A(31, 28) = 0.002041192230750734;
        A(31, 29) = -1.345579922611285;
        A(31, 30) = 1.095961635561515;
        A(31, 31) = -0.9900944894234357;
        A(31, 32) = 0.3684323111619496;
        A(31, 33) = 1.671653316362218;
        A(31, 34) = -1.800339642594652;
        A(31, 35) = -0.04782956065260512;
        A(31, 36) = -0.6303441842534072;
        A(31, 37) = -0.9663546122259339;
        A(31, 38) = 0.528118426952127;
        A(31, 39) = -0.2182611159795599;
        A(31, 40) = -0.5932714206949661;
        A(31, 41) = -0.5056277420886605;
        A(31, 42) = 0.09458867004853221;
        A(31, 43) = -0.414260651648777;
        A(31, 44) = 0.1742430640317544;
        A(31, 45) = -0.6588596371804216;
        A(31, 46) = 0.3301768827666451;
        A(31, 47) = 1.619891127989533;
        A(31, 48) = -0.2098999237166949;
        A(31, 49) = 0.5368153416283015;
        A(31, 50) = 0.3474803016541505;
        A(31, 51) = 0.0907312980372619;
        A(31, 52) = 1.047742540240497;
        A(31, 53) = 0.2294270222593558;
        A(31, 54) = 1.453738796236184;
        A(31, 55) = -0.8005474209025655;
        A(31, 56) = 1.350337041226638;
        A(31, 57) = -0.7590516114509082;
        A(31, 58) = 0.3135727159061249;
        A(31, 59) = 0.937821452196608;
        A(31, 60) = 0.1823604549646526;
        A(31, 61) = -0.6360820934145216;
        A(31, 62) = -1.438666609435195;
        A(31, 63) = -1.299647446501896;

        y[0]  = -2.037562919008439;
        y[1]  = -2.365326059504922;
        y[2]  =  5.128713204614584;
        y[3]  = -1.496719929355954;
        y[4]  = -0.1647246594251659;
        y[5]  =  0.6735816109616195;
        y[6]  =  6.929442644150667;
        y[7]  = -3.677424564909443;
        y[8]  = -1.793768131189025;
        y[9]  = -1.937794631206184;
        y[10] = -3.091410235007204;
        y[11] =  2.994921387924061;
        y[12] = -6.95113759150783;
        y[13] =  0.2569634385915862;
        y[14] =  1.741949434657935;
        y[15] =  3.390238164122583;
        y[16] = -1.426815368157929;
        y[17] =  1.109518163541706;
        y[18] = -3.300962619932516;
        y[19] = -5.834982630487295;
        y[20] = -2.263377682363473;
        y[21] = -3.205784177264004;
        y[22] = -1.231123247444592;
        y[23] = -2.719226154567583;
        y[24] =  2.87667153862011;
        y[25] =  1.236583428431698;
        y[26] =  6.797372974653632;
        y[27] = -2.23819495038825;
        y[28] = 1.41197671847391;
        y[29] = -3.425277168321983;
        y[30] =  0.804956190155619;
        y[31] = -2.281181012962092;

        klab::KRandom::Instance().setSeed(12345);

        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > phi0 = new kl1p::TMatrixOperator<klab::DoubleReal>(A);

        // Normalize phi.
        klab::DoubleReal normFactor = 0.0;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col;
            phi0->column(i, col);
            normFactor += arma::dot(col, col);
        }
        klab::TSmartPointer<TOperator<klab::DoubleReal> > normOp = new TScalarOperator<klab::DoubleReal>(m, klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m)));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > phi = normOp * phi0;

        y *= klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m));

        TEMBPSolver<klab::DoubleReal> embp(1e-3, 200);
        embp.setNoiseVariance(1e-15);
        embp.setMessageDamping(0.5);
        embp.setLearningDamping(0.5);
        embp.enableDampingLearning(true);    
        embp.enableParameterLearning(true);   
        embp.enableHomogeneous(false);
        embp.enableHistory(true);

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 65.322773726798204, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.0011337292056148086, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.00050043529269495045, 1e-6))
        TEST_ASSERT(iterations == 200)

        TEST_ASSERT(embp.history().size() == 201)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 2.2654861121193828, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 2.2759234995757893, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 1.5788129782566835, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 2.6928672125588715, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 3.0671513929958683, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 1.7212926927132597, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 2.8777541366504886, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 1.5287359446373709, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.96480987160251741, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.99471262140916339, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[200].residualNorm(), 0.0011337292056148086, 1e-6))

        // Limit cases.
        try                                         {embp.solve(arma::Col<klab::DoubleReal>(), phi, k, xr); TEST_ASSERT(false)}
        catch(KNullVectorEMBPSolverException&)      {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {embp.solve(y, klab::TSmartPointer<TOperator<klab::DoubleReal> >(0), k, xr); TEST_ASSERT(false)}
        catch(KNullOperatorEMBPSolverException&)    {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        embp.solve(y, phi, 0, xr);
        TEST_ASSERT(xr.n_rows == n)
        bool isZero = true;
        for(klab::UInt32 i=0; i<n && isZero; ++i)
            isZero = klab::Equals(xr[i], 0.0, 0.0);
        TEST_ASSERT(isZero)

        embp.setTolerance(1.0);
        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)
        snr          = klab::SNR(x, xr);
        residualNorm = embp.residualNorm();
        rrNorm       = embp.relativeResidualNorm();
        iterations   = embp.iterations();
        TEST_ASSERT(klab::Equals(snr, 5.7922192832727246, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.74071637371089460, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.32695692538055232, 1e-6))
        TEST_ASSERT(iterations == 8)
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_05()
{
    try
    {
        klab::UInt32 m = 32;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        x.fill(0.0);
        x[6]   =  1.0;
        x[3]   = -1.0;
        x[52]  = -1.0;
        x[21]  =  1.0;
        x[33]  = -1.0;

        klab::KRandom::Instance().setSeed(12345);

        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > phi0 = new TNormalRandomMatrixOperator<klab::DoubleReal>(m, n); 

        // Normalize phi.
        klab::DoubleReal normFactor = 0.0;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col;
            phi0->column(i, col);
            normFactor += arma::dot(col, col);
        }
        klab::TSmartPointer<TOperator<klab::DoubleReal> > normOp = new TScalarOperator<klab::DoubleReal>(m, klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m)));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > phi = normOp * phi0;

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal> embp(1e-3, 200);
        embp.setNoiseVariance(1e-15);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(true);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 64.185408051664737, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00078200588519073918, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.00060269844644679569, 1e-6))
        TEST_ASSERT(iterations == 85)

        TEST_ASSERT(embp.history().size() == 86)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 1.2975077168375815, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 1.2970817987179966, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 1.2371192190645421, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 0.96780204597521202, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 1.2822775363311334, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 1.3417802752277728, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 0.66089596590328248, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 1.1512389578916891, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 1.0097282244436174, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.32265822427135271, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[85].residualNorm(), 0.00078200588519073918, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_06()
{
    try
    {
        klab::UInt32 m = 20;    // Number of observations.
        klab::UInt32 n = 32;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        
        x.fill(0.0);
        x[6]  = std::complex<klab::DoubleReal>( 1.0, -1.0);
        x[3]  = std::complex<klab::DoubleReal>(-1.0, 1.0);
        x[26] = std::complex<klab::DoubleReal>(-1.0, 1.0);
        x[21] = std::complex<klab::DoubleReal>( 1.0, -1.0);
        x[16] = std::complex<klab::DoubleReal>(-1.0, 1.0);


        klab::KRandom::Instance().setSeed(98765);

        klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > phi0 = new TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> >(m, n, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));

        // Normalize phi.
        klab::DoubleReal normFactor = 0.0;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            phi0->column(i, col);
            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                normFactor += (col[j].real()*col[j].real()) + (col[j].imag()*col[j].imag());
        }
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > normOp = new TScalarOperator<std::complex<klab::DoubleReal> >(m, klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m)));
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > phi = normOp * phi0;

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > embp(1e-3, 200);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(true);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);

        embp.solve(y, phi, k, xr);   
        TEST_ASSERT(xr.n_rows == n)

        arma::Col<klab::DoubleReal> rx(x.n_rows);
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            rx[i] = klab::CastTo<klab::DoubleReal>(x[i]);

        arma::Col<klab::DoubleReal> rxr(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);

        klab::DoubleReal snr          = klab::SNR(rx, rxr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 72.738799632322809, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00093965150450622955, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.00040548980410801035, 1e-6))
        TEST_ASSERT(iterations == 111)

        TEST_ASSERT(embp.history().size() == 112)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 2.3173246157773537, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 2.3168270085846872, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 2.1089191370011235, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 1.6973975084107977, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 1.4582579763102232, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 1.7798793931197479, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 1.2797540397716052, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 1.3711422482763220, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 1.1106378863604791, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 1.1770497256490262, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[111].residualNorm(), 0.00093965150450622955, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_07()
{
    try
    {
        klab::UInt32 m = 32;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        klab::KRandom::Instance().setSeed(12345);

        x.fill(0.0);
        x[6]   = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[3]   = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[52]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[21]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[33]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);      

        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > phi0 = new TUniformRandomMatrixOperator<klab::DoubleReal>(m, n, -1.0, 1.0);

        // Normalize phi.
        klab::DoubleReal normFactor = 0.0;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<klab::DoubleReal> col;
            phi0->column(i, col);
            normFactor += arma::dot(col, col);
        }
        klab::TSmartPointer<TOperator<klab::DoubleReal> > normOp = new TScalarOperator<klab::DoubleReal>(m, klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m)));
        klab::TSmartPointer<TOperator<klab::DoubleReal> > phi = normOp * phi0;

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal> embp(1e-3, 200);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(true);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 61.754984764433132, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00097437487668657345, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.00072370026750715616, 1e-6))
        TEST_ASSERT(iterations == 92)

        TEST_ASSERT(embp.history().size() == 93)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 1.3463790472855373, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 1.3460166298118215, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 1.2437216686329580, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 0.87183144678808588, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 0.90752120889604193, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 1.1761312092673553, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 0.49351130526683967, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.40138899255591759, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.41572108256198781, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.27274905978361058, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[92].residualNorm(), 0.00097437487668657345, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_08()
{
    try
    {
        klab::UInt32 m = 32;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        klab::KRandom::Instance().setSeed(12345);

        x.fill(0.0);
        x[6]   = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[3]   = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[52]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[21]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[33]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);      

        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > dct  = new TInverseDCT1DOperator<klab::DoubleReal>(n);
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > down = new TRandomDownSamplingOperator<klab::DoubleReal>(m, n);
        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > phi  = down * dct;

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal> embp(1e-3, 200);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(true);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 62.700978034746456, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00099238479124455253, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.00076968057928684095, 1e-6))
        TEST_ASSERT(iterations == 86)

        TEST_ASSERT(embp.history().size() == 87)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 1.2893462794190047, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 1.2901393941372372, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 1.1723595721432443, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 1.9403711120179024, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 3.1707930293510849, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 2.9315090333909093, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 1.7970068375084924, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.81414285024110100, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 1.0043664378780379, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 1.0684051765226219, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[86].residualNorm(), 0.00099238479124455253, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_09()
{
    try
    {
        klab::UInt32 m = 32;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        klab::KRandom::Instance().setSeed(12345);

        x.fill(0.0);
        x[6]   = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[3]   = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[52]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[21]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[33]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0));      

        klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > fourier = new TInverseFourier1DOperator<std::complex<klab::DoubleReal> >(n, true);
        klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > down = new TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(m, n);
        klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > phi0  = down * fourier;

        // Normalize phi.
        klab::DoubleReal normFactor = 0.0;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            arma::Col<std::complex<klab::DoubleReal> > col;
            phi0->column(i, col);
            for(klab::UInt32 j=0; j<col.n_rows; ++j)
                normFactor += (col[j].real()*col[j].real()) + (col[j].imag()*col[j].imag());
        }
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > normOp = new TScalarOperator<std::complex<klab::DoubleReal> >(m, klab::TTypeInfo<klab::DoubleReal>::UNIT / klab::Sqrt(normFactor/static_cast<klab::DoubleReal>(m)));
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > phi = normOp * phi0;

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > embp(1e-3, 200);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(true);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        arma::Col<klab::DoubleReal> rx(x.n_rows);
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            rx[i] = klab::CastTo<klab::DoubleReal>(x[i]);

        arma::Col<klab::DoubleReal> rxr(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);

        klab::DoubleReal snr          = klab::SNR(rx, rxr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 64.559040110943641, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.00071996644624992162, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.00048846903911049647, 1e-6))
        TEST_ASSERT(iterations == 133)

        TEST_ASSERT(embp.history().size() == 134)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 1.4739244222335619, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 1.4720607632853224, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 1.4187963886888786, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 1.2564870696534527, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 0.83516544611331067, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 0.83433999627802369, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 0.73221298000744239, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.48532504771753676, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.46629917315756170, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.39775426657924429, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[133].residualNorm(), 0.00071996644624992162, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_10()
{
    try
    {
        klab::UInt32 m = 34;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 12;    // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y(m);
        arma::Col<klab::DoubleReal> xr;
        arma::Mat<klab::DoubleReal> A00(16, 16);
        arma::Mat<klab::DoubleReal> A01(16, 16);
        arma::Mat<klab::DoubleReal> A10(6, 16);
        arma::Mat<klab::DoubleReal> A11(6, 16);
        arma::Mat<klab::DoubleReal> A12(6, 16);
        arma::Mat<klab::DoubleReal> A21(6, 16);
        arma::Mat<klab::DoubleReal> A22(6, 16);
        arma::Mat<klab::DoubleReal> A23(6, 16);
        arma::Mat<klab::DoubleReal> A32(6, 16);
        arma::Mat<klab::DoubleReal> A33(6, 16);

        x.fill(0.0);
        x[5]  =  0.1273450527495;
        x[13] =  1.094270695640407;
        x[15] =  0.655726328475191;
        x[22] =  0.8544906548270752;
        x[29] = -0.5293306506731519;
        x[34] =  0.1778243729517102;
        x[35] = -0.5044189577772389;
        x[41] =  2.078922249764298;
        x[42] = -0.2239042442217898;
        x[47] = -0.5545832342364362;
        x[53] = -1.347922690481032;
        x[57] =  1.187360783753705;

        A00(0, 0) = -0.053882366156891;
        A00(0, 1) = 0.04009097491823111;
        A00(0, 2) = -0.00800366617156315;
        A00(0, 3) = 0.1720075528356202;
        A00(0, 4) = 0.003921520325223334;
        A00(0, 5) = 0.105477805203955;
        A00(0, 6) = 0.01122610328975556;
        A00(0, 7) = 0.1838673511784909;
        A00(0, 8) = 0.0498009243858057;
        A00(0, 9) = 0.01654817535008188;
        A00(0, 10) = -0.07637874124748867;
        A00(0, 11) = 0.06462137852928505;
        A00(0, 12) = 0.1947753126422662;
        A00(0, 13) = -0.03519949128143666;
        A00(0, 14) = 0.2623949917518648;
        A00(0, 15) = 0.06431491169960998;
        A00(1, 0) = 0.1040512589119428;
        A00(1, 1) = 0.162419608662647;
        A00(1, 2) = -0.002040247318713941;
        A00(1, 3) = -0.08327612515292165;
        A00(1, 4) = 0.01363754612989343;
        A00(1, 5) = 0.07970825644712645;
        A00(1, 6) = -0.1025312655146699;
        A00(1, 7) = 0.1722841624797585;
        A00(1, 8) = -0.06247501538900292;
        A00(1, 9) = -0.02360647486464373;
        A00(1, 10) = 0.02461089681517589;
        A00(1, 11) = -0.1582618360630115;
        A00(1, 12) = -0.03238050745893956;
        A00(1, 13) = -0.02928846585931984;
        A00(1, 14) = -0.03105388620427413;
        A00(1, 15) = 0.105025784189994;
        A00(2, 0) = 0.07302397580754336;
        A00(2, 1) = -0.1311600485358718;
        A00(2, 2) = -0.07930446054530778;
        A00(2, 3) = -0.03959340067692529;
        A00(2, 4) = 0.1296537121877118;
        A00(2, 5) = -0.07701506499844918;
        A00(2, 6) = -0.008815928539554558;
        A00(2, 7) = 0.09119460514833618;
        A00(2, 8) = 0.01651127446268165;
        A00(2, 9) = -0.1951293936856456;
        A00(2, 10) = 0.03630717738231934;
        A00(2, 11) = -0.04368407633534265;
        A00(2, 12) = -0.02670809362159973;
        A00(2, 13) = -0.05645215880675;
        A00(2, 14) = 0.255399693963608;
        A00(2, 15) = -0.009487806610420204;
        A00(3, 0) = -0.1677079332364387;
        A00(3, 1) = -0.01809038234898345;
        A00(3, 2) = 0.2168523079522954;
        A00(3, 3) = -0.1352899536826707;
        A00(3, 4) = -0.09208186186484481;
        A00(3, 5) = 0.07161234351875108;
        A00(3, 6) = 0.02964959060139583;
        A00(3, 7) = 0.1262303962474707;
        A00(3, 8) = 0.04138880721875051;
        A00(3, 9) = 0.1051594200465819;
        A00(3, 10) = 0.0761247332276094;
        A00(3, 11) = -0.006945961306426522;
        A00(3, 12) = -0.02660517653683665;
        A00(3, 13) = 0.06642149337243244;
        A00(3, 14) = -0.07302726934480987;
        A00(3, 15) = 0.01989420187264262;
        A00(4, 0) = 0.04314562094015917;
        A00(4, 1) = 0.08383864055318753;
        A00(4, 2) = 0.002604519202629791;
        A00(4, 3) = -0.2214402002121877;
        A00(4, 4) = -0.09318691784250341;
        A00(4, 5) = 0.07281034548759445;
        A00(4, 6) = 0.06661021292652793;
        A00(4, 7) = 0.1633956791578231;
        A00(4, 8) = 0.2212545520497808;
        A00(4, 9) = 0.2549604937192494;
        A00(4, 10) = -0.009810865095906221;
        A00(4, 11) = -0.07486247665189917;
        A00(4, 12) = 0.005657181471160705;
        A00(4, 13) = -0.08574511563599403;
        A00(4, 14) = 0.02433531513535695;
        A00(4, 15) = -0.1552829743946239;
        A00(5, 0) = -0.148379721174227;
        A00(5, 1) = 0.001640966734771143;
        A00(5, 2) = -0.03959283144223854;
        A00(5, 3) = 0.156905053190758;
        A00(5, 4) = 0.1470407690110739;
        A00(5, 5) = 0.287760042382871;
        A00(5, 6) = 0.04932931342893399;
        A00(5, 7) = -0.2085890508006628;
        A00(5, 8) = -0.1461116763097169;
        A00(5, 9) = 0.2107765848982104;
        A00(5, 10) = 0.1484538091580649;
        A00(5, 11) = -0.104349516496007;
        A00(5, 12) = 0.07303715089111787;
        A00(5, 13) = -0.04439513184026933;
        A00(5, 14) = -0.1529378880989775;
        A00(5, 15) = -0.04401932624511667;
        A00(6, 0) = -0.01910882136231336;
        A00(6, 1) = 0.04478617154387655;
        A00(6, 2) = -0.05288242421586871;
        A00(6, 3) = -0.06228154552471788;
        A00(6, 4) = 0.1414677130113761;
        A00(6, 5) = -0.1064565265406963;
        A00(6, 6) = 0.1344139448364942;
        A00(6, 7) = 0.333745199525876;
        A00(6, 8) = 0.07171387489678606;
        A00(6, 9) = 0.2563657235057215;
        A00(6, 10) = 0.1636149575848311;
        A00(6, 11) = -0.1141359493083531;
        A00(6, 12) = 0.05128483299888888;
        A00(6, 13) = -0.1408187058212005;
        A00(6, 14) = 0.001207596582373591;
        A00(6, 15) = 0.05380917415339864;
        A00(7, 0) = -0.04236297781141959;
        A00(7, 1) = 0.1223782779662896;
        A00(7, 2) = 0.03733237133051502;
        A00(7, 3) = 0.101329471833418;
        A00(7, 4) = -0.06335646055986685;
        A00(7, 5) = 0.1758611059780104;
        A00(7, 6) = -0.1404543602735895;
        A00(7, 7) = 0.1613166706054097;
        A00(7, 8) = -0.1261895923253728;
        A00(7, 9) = 0.07715548059132277;
        A00(7, 10) = 0.06506822209365605;
        A00(7, 11) = 0.001484586424818025;
        A00(7, 12) = 0.05988760774832502;
        A00(7, 13) = 0.03516873048612786;
        A00(7, 14) = -0.02989434048240563;
        A00(7, 15) = 0.03195438052425546;
        A00(8, 0) = 0.1174880916017312;
        A00(8, 1) = 0.004614987390406907;
        A00(8, 2) = 0.1183015682895743;
        A00(8, 3) = 0.02493029068483254;
        A00(8, 4) = 0.09369982293947285;
        A00(8, 5) = -0.02147843880618266;
        A00(8, 6) = -0.0007988437618705945;
        A00(8, 7) = 0.004916964437801021;
        A00(8, 8) = -0.07392282247711007;
        A00(8, 9) = -0.0007527759822824423;
        A00(8, 10) = -0.01377761973704174;
        A00(8, 11) = 0.3400719345855877;
        A00(8, 12) = 0.1566534843855411;
        A00(8, 13) = -0.05493720132567912;
        A00(8, 14) = 0.0620134597322121;
        A00(8, 15) = 0.0980108750500084;
        A00(9, 0) = -0.1254107869645975;
        A00(9, 1) = 0.1128003606718804;
        A00(9, 2) = 0.04607969818010838;
        A00(9, 3) = -0.1767894018600299;
        A00(9, 4) = 0.07980690292140508;
        A00(9, 5) = -0.1509500049503919;
        A00(9, 6) = 0.1718810303307224;
        A00(9, 7) = 0.05075135338750824;
        A00(9, 8) = 0.1367949246983284;
        A00(9, 9) = 0.02013604042047725;
        A00(9, 10) = 0.05433642980801374;
        A00(9, 11) = 0.3585494050947536;
        A00(9, 12) = 0.05033853495801338;
        A00(9, 13) = 0.04646403187311857;
        A00(9, 14) = -0.03945198633615519;
        A00(9, 15) = -0.189317738039902;
        A00(10, 0) = 0.1790266498258729;
        A00(10, 1) = 0.003261742524918145;
        A00(10, 2) = -0.119856443533464;
        A00(10, 3) = 0.00973934961828375;
        A00(10, 4) = 0.1513170322214751;
        A00(10, 5) = -0.07412204378132829;
        A00(10, 6) = 0.02661222664485171;
        A00(10, 7) = 0.009031644795407742;
        A00(10, 8) = -0.2019408846129727;
        A00(10, 9) = 0.4407305351871215;
        A00(10, 10) = -0.1597432173990293;
        A00(10, 11) = 0.157780013096675;
        A00(10, 12) = 0.1063042762456986;
        A00(10, 13) = 0.1653026446541592;
        A00(10, 14) = 0.2992378871967613;
        A00(10, 15) = 0.2769069872191032;
        A00(11, 0) = -0.03470749728793569;
        A00(11, 1) = -0.06454362822023613;
        A00(11, 2) = -0.09974014319353734;
        A00(11, 3) = -0.1197778959957872;
        A00(11, 4) = -0.1924960089321885;
        A00(11, 5) = -0.07780574256445159;
        A00(11, 6) = 0.1841146572377617;
        A00(11, 7) = -0.04901986358623627;
        A00(11, 8) = 0.01907704500542166;
        A00(11, 9) = -0.05495128464854786;
        A00(11, 10) = -0.08456705850699212;
        A00(11, 11) = -0.07517188614812963;
        A00(11, 12) = 0.1532897389734203;
        A00(11, 13) = 0.05956924024555297;
        A00(11, 14) = 0.1061179009474481;
        A00(11, 15) = 0.2407866594576176;
        A00(12, 0) = 0.04011198627135728;
        A00(12, 1) = -0.1412636125295914;
        A00(12, 2) = 0.06379998725683519;
        A00(12, 3) = -0.1069442604333053;
        A00(12, 4) = 0.1679153553853155;
        A00(12, 5) = 0.07775534348054627;
        A00(12, 6) = -0.06691054352225508;
        A00(12, 7) = 0.03336312454227052;
        A00(12, 8) = -0.006849467618890747;
        A00(12, 9) = -0.09807864727520568;
        A00(12, 10) = -0.2376632568834428;
        A00(12, 11) = 0.09322966868589537;
        A00(12, 12) = 0.2895075314285275;
        A00(12, 13) = 0.007849708051707134;
        A00(12, 14) = -0.04147648284807369;
        A00(12, 15) = 0.02116926010743616;
        A00(13, 0) = 0.2304843879240953;
        A00(13, 1) = -0.1845347066494448;
        A00(13, 2) = -0.06163569669366065;
        A00(13, 3) = -0.1540184978347103;
        A00(13, 4) = -0.2114016143976543;
        A00(13, 5) = 0.2869365785417564;
        A00(13, 6) = -0.1574664030809241;
        A00(13, 7) = 0.02034715761507541;
        A00(13, 8) = -0.05834071570847745;
        A00(13, 9) = -0.1438659374030392;
        A00(13, 10) = 0.1396691472559601;
        A00(13, 11) = -0.08027023646994221;
        A00(13, 12) = 0.1628519527959485;
        A00(13, 13) = 0.2322154388280759;
        A00(13, 14) = 0.1356546724387542;
        A00(13, 15) = 0.1238698542550393;
        A00(14, 0) = -0.0577204822479824;
        A00(14, 1) = 0.1438927964846077;
        A00(14, 2) = 0.1051435964565554;
        A00(14, 3) = -0.1054757473630015;
        A00(14, 4) = -0.01247526355950157;
        A00(14, 5) = -0.1642451982154521;
        A00(14, 6) = 0.05832809964554311;
        A00(14, 7) = -0.2624173043693407;
        A00(14, 8) = -0.1034473490959244;
        A00(14, 9) = -0.1575401419623425;
        A00(14, 10) = 0.03819202592051989;
        A00(14, 11) = -0.08010113055070732;
        A00(14, 12) = -0.1137442262205085;
        A00(14, 13) = -0.1082312247343453;
        A00(14, 14) = -0.03096937940276776;
        A00(14, 15) = -0.1198772820082317;
        A00(15, 0) = 0.1964464436152485;
        A00(15, 1) = 0.1718139313096449;
        A00(15, 2) = 0.1220870645967711;
        A00(15, 3) = 0.1101377230164814;
        A00(15, 4) = -0.08647778939417106;
        A00(15, 5) = -0.1810244300095861;
        A00(15, 6) = -0.171568204486923;
        A00(15, 7) = 0.1623522188886931;
        A00(15, 8) = -0.04362200485875676;
        A00(15, 9) = -0.01968622647066848;
        A00(15, 10) = 0.2933359935529915;
        A00(15, 11) = 0.09977664292593755;
        A00(15, 12) = -0.2336572151570675;
        A00(15, 13) = -0.04558026473645192;
        A00(15, 14) = -0.03699015259178808;
        A00(15, 15) = 0.1504941019129657;
        A01(0, 0) = 0.03140378422706046;
        A01(0, 1) = 0.05799619294096244;
        A01(0, 2) = -0.0363411362746672;
        A01(0, 3) = 0.01418224197041674;
        A01(0, 4) = -0.04311521921819182;
        A01(0, 5) = 0.04568373285819372;
        A01(0, 6) = 0.03886750490603732;
        A01(0, 7) = 0.07388886508205572;
        A01(0, 8) = -0.002779232497897805;
        A01(0, 9) = 0.04934416008914216;
        A01(0, 10) = -0.01708743014442976;
        A01(0, 11) = 0.05741755285933015;
        A01(0, 12) = -0.008466549263147478;
        A01(0, 13) = 0.04080312058948904;
        A01(0, 14) = -0.05072618217297076;
        A01(0, 15) = 0.003097118910154011;
        A01(1, 0) = -0.002448640356436157;
        A01(1, 1) = 0.006054573709998019;
        A01(1, 2) = -0.02500815311207364;
        A01(1, 3) = 0.0115970553825751;
        A01(1, 4) = 0.02851987018583676;
        A01(1, 5) = -0.03640242319539815;
        A01(1, 6) = 0.06866789253983656;
        A01(1, 7) = 0.007831691211614545;
        A01(1, 8) = 0.09263644451337057;
        A01(1, 9) = 0.02069912352915612;
        A01(1, 10) = 0.005406165005372355;
        A01(1, 11) = 0.03324574935889612;
        A01(1, 12) = -0.04962927183058337;
        A01(1, 13) = -0.02239645544940655;
        A01(1, 14) = 0.004644207014950861;
        A01(1, 15) = 0.02474332801038726;
        A01(2, 0) = -0.02491210163068832;
        A01(2, 1) = 0.004448752793399038;
        A01(2, 2) = -0.1305491397222799;
        A01(2, 3) = 0.01166511533894182;
        A01(2, 4) = 0.01059927530212246;
        A01(2, 5) = 0.02725309059579353;
        A01(2, 6) = -0.05943848502460998;
        A01(2, 7) = -0.03029276761657923;
        A01(2, 8) = -0.04497057112674922;
        A01(2, 9) = -0.02798803049783665;
        A01(2, 10) = -0.06865632672464642;
        A01(2, 11) = -0.02204113764523831;
        A01(2, 12) = 0.0121546197299012;
        A01(2, 13) = 0.04343661361526142;
        A01(2, 14) = -0.0195736618927531;
        A01(2, 15) = 0.01123892363892927;
        A01(3, 0) = -0.1089655466181539;
        A01(3, 1) = -0.06176448629038494;
        A01(3, 2) = 0.0002995503150489047;
        A01(3, 3) = -0.03655867588948562;
        A01(3, 4) = -0.04228638932548543;
        A01(3, 5) = -0.006387760927368354;
        A01(3, 6) = 0.02089969621497513;
        A01(3, 7) = -0.04678819958717778;
        A01(3, 8) = 0.0491833438384968;
        A01(3, 9) = 0.02073891431019514;
        A01(3, 10) = 0.05774677386133243;
        A01(3, 11) = 0.001297825102346241;
        A01(3, 12) = -0.03119157991799586;
        A01(3, 13) = -0.07150248159383391;
        A01(3, 14) = -0.03841511746875415;
        A01(3, 15) = -0.04117859766978697;
        A01(4, 0) = -0.02707637824255489;
        A01(4, 1) = 0.0552369564640607;
        A01(4, 2) = -0.04273734377904059;
        A01(4, 3) = 0.05471332721891465;
        A01(4, 4) = 0.03229773073141758;
        A01(4, 5) = 0.04421195877233187;
        A01(4, 6) = 0.01777136928358528;
        A01(4, 7) = -0.05104048381933044;
        A01(4, 8) = -0.01154355028878736;
        A01(4, 9) = 0.0375606413151558;
        A01(4, 10) = -0.05818176085193964;
        A01(4, 11) = -0.04059532109776477;
        A01(4, 12) = 0.03051621167660817;
        A01(4, 13) = -0.04845476389680137;
        A01(4, 14) = 0.02135262534546515;
        A01(4, 15) = -0.07975759095490752;
        A01(5, 0) = 0.06185522781274928;
        A01(5, 1) = -0.02401455162231378;
        A01(5, 2) = 0.01252467565420889;
        A01(5, 3) = -0.0362495762925839;
        A01(5, 4) = 0.006999244912207118;
        A01(5, 5) = -0.01129464682689776;
        A01(5, 6) = 0.03253023242452772;
        A01(5, 7) = -0.06422228731611043;
        A01(5, 8) = 0.02409817841033914;
        A01(5, 9) = -0.006350645302873106;
        A01(5, 10) = -0.04522163461862983;
        A01(5, 11) = 0.009502910593744434;
        A01(5, 12) = -0.0002303922218490231;
        A01(5, 13) = -0.0133802536125235;
        A01(5, 14) = 0.08259106801540934;
        A01(5, 15) = -0.006756801371121281;
        A01(6, 0) = 0.09152863169844437;
        A01(6, 1) = -0.02368305931662832;
        A01(6, 2) = -0.05277147425041704;
        A01(6, 3) = 0.04441568663466404;
        A01(6, 4) = -0.03333453143141477;
        A01(6, 5) = -0.04191805595891032;
        A01(6, 6) = 0.04477081739313712;
        A01(6, 7) = 0.07632170704992691;
        A01(6, 8) = 0.01501732707505154;
        A01(6, 9) = 0.01437537481276264;
        A01(6, 10) = 0.06658058693849414;
        A01(6, 11) = 0.08672474136644065;
        A01(6, 12) = 0.02118484496132429;
        A01(6, 13) = -0.03126605707953385;
        A01(6, 14) = 0.07078392669254718;
        A01(6, 15) = -0.08333687703274101;
        A01(7, 0) = -0.03822580833160696;
        A01(7, 1) = -0.03116706445034381;
        A01(7, 2) = 0.009669885797199235;
        A01(7, 3) = 0.07894968539964058;
        A01(7, 4) = 0.040501519130616;
        A01(7, 5) = 0.03227920960293165;
        A01(7, 6) = -0.02779591693493593;
        A01(7, 7) = 0.01258699535927019;
        A01(7, 8) = -0.009600084894457062;
        A01(7, 9) = 0.04624657731571805;
        A01(7, 10) = -0.04336514367189615;
        A01(7, 11) = -0.02296652927579317;
        A01(7, 12) = -0.004632651709142861;
        A01(7, 13) = 0.01591006990383822;
        A01(7, 14) = -0.04133487371722532;
        A01(7, 15) = 0.08662609330571823;
        A01(8, 0) = 0.04612149139069297;
        A01(8, 1) = -0.02384026529135196;
        A01(8, 2) = 0.06103608451606304;
        A01(8, 3) = 0.005690986368744922;
        A01(8, 4) = -0.005518878581565692;
        A01(8, 5) = 0.1070096880176837;
        A01(8, 6) = -0.04288548705047503;
        A01(8, 7) = -0.0949906526453304;
        A01(8, 8) = 0.03499989263091546;
        A01(8, 9) = -0.09524757709352652;
        A01(8, 10) = 0.0543965921054866;
        A01(8, 11) = 0.03851050085844644;
        A01(8, 12) = -0.007453750597400746;
        A01(8, 13) = -0.01707577505331565;
        A01(8, 14) = -0.02029462149592793;
        A01(8, 15) = -0.04420852335757855;
        A01(9, 0) = 0.03868031665768188;
        A01(9, 1) = 0.05436336690066373;
        A01(9, 2) = -0.06847655997232442;
        A01(9, 3) = -0.0998782833448905;
        A01(9, 4) = -0.01367048340844951;
        A01(9, 5) = 0.01198380891274288;
        A01(9, 6) = -0.04806233674546716;
        A01(9, 7) = -0.1037934990683334;
        A01(9, 8) = 0.03887941496190021;
        A01(9, 9) = 0.002452890059188187;
        A01(9, 10) = -0.02886021157178489;
        A01(9, 11) = 0.01193696511206979;
        A01(9, 12) = 0.006408258262206598;
        A01(9, 13) = -0.04612043650938816;
        A01(9, 14) = 0.009155818712614196;
        A01(9, 15) = -0.009428263807351291;
        A01(10, 0) = -0.07283116545002817;
        A01(10, 1) = 0.01987910524991893;
        A01(10, 2) = -0.01866238391155529;
        A01(10, 3) = -0.03289524202833132;
        A01(10, 4) = -0.02239066053294974;
        A01(10, 5) = -0.01451140670579231;
        A01(10, 6) = -0.004040805908897756;
        A01(10, 7) = -0.01153116062879928;
        A01(10, 8) = 0.06658001852801929;
        A01(10, 9) = -0.02466340242703194;
        A01(10, 10) = 0.07111572618098638;
        A01(10, 11) = -0.04569019497474122;
        A01(10, 12) = -0.0005656835830730625;
        A01(10, 13) = -0.007352055539778983;
        A01(10, 14) = 0.03556925120956932;
        A01(10, 15) = -0.0005396411951462593;
        A01(11, 0) = -0.03313238337928659;
        A01(11, 1) = -0.02791528645986746;
        A01(11, 2) = -0.0432195015302311;
        A01(11, 3) = 0.1023367543605585;
        A01(11, 4) = 0.009315199733531386;
        A01(11, 5) = -0.03407728944314022;
        A01(11, 6) = -0.09335135702353901;
        A01(11, 7) = -0.05889811333017164;
        A01(11, 8) = -0.03542339753537428;
        A01(11, 9) = -0.05499012787589486;
        A01(11, 10) = 0.03132713734264868;
        A01(11, 11) = 0.05376196178827635;
        A01(11, 12) = -0.03669902678403792;
        A01(11, 13) = -0.06671102798961393;
        A01(11, 14) = 0.09954926899989812;
        A01(11, 15) = -0.06040989330109055;
        A01(12, 0) = 0.01414180771733667;
        A01(12, 1) = -0.05117255733264751;
        A01(12, 2) = -0.04007784022999672;
        A01(12, 3) = -0.03576172806723692;
        A01(12, 4) = -0.03140468643271593;
        A01(12, 5) = 0.003253478040271412;
        A01(12, 6) = 0.01825751504645591;
        A01(12, 7) = -0.06130666107790693;
        A01(12, 8) = -0.03327360366149897;
        A01(12, 9) = 0.05453854092886228;
        A01(12, 10) = 0.04843022119904891;
        A01(12, 11) = 0.01223497497019907;
        A01(12, 12) = 0.03805715045179206;
        A01(12, 13) = 0.03421810575776187;
        A01(12, 14) = 0.0197935388135987;
        A01(12, 15) = -0.02680348735430704;
        A01(13, 0) = 0.0689496026524417;
        A01(13, 1) = -0.04081076182108322;
        A01(13, 2) = 0.03010418475445807;
        A01(13, 3) = 0.006478503345811464;
        A01(13, 4) = -0.06142531946931586;
        A01(13, 5) = -0.06189257721282143;
        A01(13, 6) = -0.04928262973974483;
        A01(13, 7) = 0.04685989950995071;
        A01(13, 8) = 0.02892231967683354;
        A01(13, 9) = -0.04645975219047278;
        A01(13, 10) = -0.03678971891058207;
        A01(13, 11) = 0.03795907442953121;
        A01(13, 12) = 0.01897394441545226;
        A01(13, 13) = -0.0077317330984117;
        A01(13, 14) = -0.05688204644885544;
        A01(13, 15) = -0.007963443844105442;
        A01(14, 0) = 0.008955728191464129;
        A01(14, 1) = -0.06276021972127559;
        A01(14, 2) = 0.0555240060261103;
        A01(14, 3) = -0.07005457393106132;
        A01(14, 4) = -0.01408784427217559;
        A01(14, 5) = -0.0398751591781697;
        A01(14, 6) = 0.03839191381792677;
        A01(14, 7) = -0.02809593618183857;
        A01(14, 8) = -0.01657214140675773;
        A01(14, 9) = -0.04798894772437317;
        A01(14, 10) = -0.01666200671454661;
        A01(14, 11) = -0.004380130502369233;
        A01(14, 12) = -0.01655829815260198;
        A01(14, 13) = 0.05780013496175026;
        A01(14, 14) = 0.02498373613100299;
        A01(14, 15) = -0.04480437858394262;
        A01(15, 0) = 0.009909094602170935;
        A01(15, 1) = 0.1037588415665381;
        A01(15, 2) = 0.02909177618004261;
        A01(15, 3) = 0.03118894680242001;
        A01(15, 4) = 0.0581476097187925;
        A01(15, 5) = 0.0108164407111977;
        A01(15, 6) = -0.05457868370208748;
        A01(15, 7) = 0.04819885842491096;
        A01(15, 8) = -0.02550410863602168;
        A01(15, 9) = 0.01599114851594203;
        A01(15, 10) = 0.04064772196698586;
        A01(15, 11) = 0.01169875265768423;
        A01(15, 12) = 0.01875181752076527;
        A01(15, 13) = 0.07358496152793891;
        A01(15, 14) = -0.006508034394815785;
        A01(15, 15) = -0.01931166744979097;
        A10(0, 0) = -0.2500477480358611;
        A10(0, 1) = -0.7910654550484373;
        A10(0, 2) = 0.1248758050565201;
        A10(0, 3) = -0.391593266931537;
        A10(0, 4) = 0.9953843810899525;
        A10(0, 5) = -0.3043517630830219;
        A10(0, 6) = -0.0179357210811849;
        A10(0, 7) = -0.8788065561088441;
        A10(0, 8) = -1.064183120826788;
        A10(0, 9) = 0.1294870836386325;
        A10(0, 10) = 0.362764484454971;
        A10(0, 11) = 0.3365019872297152;
        A10(0, 12) = 0.39828037508022;
        A10(0, 13) = 0.5728944497657531;
        A10(0, 14) = -0.3771102787614006;
        A10(0, 15) = -0.4488484162459394;
        A10(1, 0) = 0.855128840186613;
        A10(1, 1) = 0.3601382971950348;
        A10(1, 2) = 0.3827383975988138;
        A10(1, 3) = 0.0266316604970216;
        A10(1, 4) = -0.7449303910699379;
        A10(1, 5) = 1.49901773990919;
        A10(1, 6) = 0.07096060338493709;
        A10(1, 7) = -0.2730446931576697;
        A10(1, 8) = 0.4314633183870499;
        A10(1, 9) = -0.2692728128407294;
        A10(1, 10) = -0.3169324567181225;
        A10(1, 11) = 0.03296370676904017;
        A10(1, 12) = 0.5368754258736318;
        A10(1, 13) = 0.1646811993394586;
        A10(1, 14) = 0.4954438285832905;
        A10(1, 15) = -0.5475832946636055;
        A10(2, 0) = -0.7117753683500945;
        A10(2, 1) = 1.221337465399838;
        A10(2, 2) = 1.105786728018515;
        A10(2, 3) = -0.3639228857197002;
        A10(2, 4) = 0.08601946704936854;
        A10(2, 5) = 0.1819620718917326;
        A10(2, 6) = -0.1935479686567481;
        A10(2, 7) = -1.151785051317562;
        A10(2, 8) = -0.5586688084320896;
        A10(2, 9) = 0.156940464235289;
        A10(2, 10) = 0.03037553722263509;
        A10(2, 11) = -0.1129030729843191;
        A10(2, 12) = -0.1871480024159386;
        A10(2, 13) = -1.080392061554611;
        A10(2, 14) = 0.4781190510654046;
        A10(2, 15) = -0.07281250438182677;
        A10(3, 0) = -0.02335868238410246;
        A10(3, 1) = -0.1789318968889864;
        A10(3, 2) = -0.9298107359385015;
        A10(3, 3) = 0.01413764139242516;
        A10(3, 4) = -1.126079170114269;
        A10(3, 5) = 0.3414485036514747;
        A10(3, 6) = 1.219891387477079;
        A10(3, 7) = -0.5843430452678891;
        A10(3, 8) = 0.4963827486784675;
        A10(3, 9) = -0.6556462868557563;
        A10(3, 10) = 0.005833779184597543;
        A10(3, 11) = -1.251377719944627;
        A10(3, 12) = -0.7038294748967316;
        A10(3, 13) = -0.3827162709566878;
        A10(3, 14) = -0.3755335975229637;
        A10(3, 15) = -0.1385622457829545;
        A10(4, 0) = -0.799691343203906;
        A10(4, 1) = -0.5102537811533559;
        A10(4, 2) = -0.1339322703670741;
        A10(4, 3) = -0.1831900566633423;
        A10(4, 4) = -0.203731761908005;
        A10(4, 5) = -0.08943364802291473;
        A10(4, 6) = 0.5077557247076142;
        A10(4, 7) = 0.7999076724031898;
        A10(4, 8) = -0.7873678109138365;
        A10(4, 9) = 0.4065827211229827;
        A10(4, 10) = -0.2018042388363014;
        A10(4, 11) = -0.573762393486023;
        A10(4, 12) = 0.4450048942261531;
        A10(4, 13) = 0.1123250473713535;
        A10(4, 14) = -1.021459648606699;
        A10(4, 15) = 0.5755168500003669;
        A10(5, 0) = -0.4028337993137109;
        A10(5, 1) = -0.2418793135464495;
        A10(5, 2) = 1.381489044600379;
        A10(5, 3) = -0.2835438065514855;
        A10(5, 4) = -0.05535481561176173;
        A10(5, 5) = -0.6633542682779888;
        A10(5, 6) = 0.2127377564289366;
        A10(5, 7) = -0.5009579726028356;
        A10(5, 8) = 0.2218003938554825;
        A10(5, 9) = 0.09336068099247756;
        A10(5, 10) = 0.3573312069149335;
        A10(5, 11) = -0.57395522307535;
        A10(5, 12) = -0.07424449414343488;
        A10(5, 13) = 0.07324605854107791;
        A10(5, 14) = -0.2520812533768239;
        A10(5, 15) = 1.141561610739185;
        A11(0, 0) = -0.1788869863902119;
        A11(0, 1) = 0.0408006705450825;
        A11(0, 2) = 0.1994100086222516;
        A11(0, 3) = -0.02012930422878227;
        A11(0, 4) = -0.06896827290980501;
        A11(0, 5) = -0.05352361522452798;
        A11(0, 6) = 0.0377004087382764;
        A11(0, 7) = -0.06772300863381198;
        A11(0, 8) = -0.1477646326869693;
        A11(0, 9) = -0.0486315312359696;
        A11(0, 10) = 0.163522976681491;
        A11(0, 11) = 0.0322704039451777;
        A11(0, 12) = -0.03820050909819823;
        A11(0, 13) = 0.1214890715296633;
        A11(0, 14) = 0.103163941150856;
        A11(0, 15) = -0.1103670149030544;
        A11(1, 0) = -0.2354865284816265;
        A11(1, 1) = -0.1199687886777056;
        A11(1, 2) = 0.05286090868217343;
        A11(1, 3) = 0.2225770229343906;
        A11(1, 4) = 0.2313485764560385;
        A11(1, 5) = 0.03800908330827026;
        A11(1, 6) = 0.2583907667179939;
        A11(1, 7) = 0.1114699314183043;
        A11(1, 8) = -0.1619852229131402;
        A11(1, 9) = -0.1732679212981831;
        A11(1, 10) = -0.1660626910852654;
        A11(1, 11) = 0.3888853968559122;
        A11(1, 12) = -0.06999043836869505;
        A11(1, 13) = 0.1040878282728121;
        A11(1, 14) = -0.009571939130077775;
        A11(1, 15) = 0.2034824924426211;
        A11(2, 0) = -0.06259890330296229;
        A11(2, 1) = 0.0855137280495477;
        A11(2, 2) = -0.001528655734547861;
        A11(2, 3) = -0.1601168714388221;
        A11(2, 4) = -0.01463614853948569;
        A11(2, 5) = 0.03382203369835645;
        A11(2, 6) = -0.04786437473521359;
        A11(2, 7) = 0.08274607557117282;
        A11(2, 8) = 0.06945361995451953;
        A11(2, 9) = 0.2151808157256283;
        A11(2, 10) = 0.07227921904865925;
        A11(2, 11) = 0.180031546613105;
        A11(2, 12) = -0.02751397255035201;
        A11(2, 13) = -0.1807639045301344;
        A11(2, 14) = 0.04252521310241878;
        A11(2, 15) = 0.2154339647859316;
        A11(3, 0) = -0.1480289871026953;
        A11(3, 1) = 0.02343073841128165;
        A11(3, 2) = -0.03266919681559611;
        A11(3, 3) = 0.1345686615277192;
        A11(3, 4) = -0.002190016988239664;
        A11(3, 5) = 0.1135055025959824;
        A11(3, 6) = -0.04251797032376985;
        A11(3, 7) = 0.1970545935403716;
        A11(3, 8) = 0.04870048304490963;
        A11(3, 9) = 0.04346313265628344;
        A11(3, 10) = 0.1018895955879746;
        A11(3, 11) = -0.01858421639979958;
        A11(3, 12) = 0.08684786946169332;
        A11(3, 13) = -0.09338696945323846;
        A11(3, 14) = -0.1250408120255218;
        A11(3, 15) = -0.1237864306901675;
        A11(4, 0) = -0.06832140855879652;
        A11(4, 1) = -0.02428287958023825;
        A11(4, 2) = 0.1157037619998121;
        A11(4, 3) = 0.07770675682642263;
        A11(4, 4) = 0.1577402132257876;
        A11(4, 5) = 0.03243652720136733;
        A11(4, 6) = -0.05124765326785907;
        A11(4, 7) = -0.1195076661977741;
        A11(4, 8) = 0.2195134912254557;
        A11(4, 9) = 0.0582658110841961;
        A11(4, 10) = -0.06760808242169066;
        A11(4, 11) = 0.02024161104477696;
        A11(4, 12) = -0.02507662969882302;
        A11(4, 13) = 0.2646054039838811;
        A11(4, 14) = -0.06915974592231339;
        A11(4, 15) = -0.006908430840010504;
        A11(5, 0) = -0.03122144064226992;
        A11(5, 1) = -0.3130722882663706;
        A11(5, 2) = -0.246605939916076;
        A11(5, 3) = -0.01605245738380438;
        A11(5, 4) = 0.06974829002139218;
        A11(5, 5) = 0.0008966880012859694;
        A11(5, 6) = -0.08150301894712912;
        A11(5, 7) = 0.2758677225342144;
        A11(5, 8) = 0.002263236785168825;
        A11(5, 9) = -0.02272579701144105;
        A11(5, 10) = 0.1236014156644925;
        A11(5, 11) = -0.01900080174812549;
        A11(5, 12) = 0.01253542254243815;
        A11(5, 13) = -0.01388056496216191;
        A11(5, 14) = -0.07639560877723922;
        A11(5, 15) = 0.1572089300730231;
        A12(0, 0) = 0.003917353330181752;
        A12(0, 1) = -0.02562035116811746;
        A12(0, 2) = -0.01002510327977626;
        A12(0, 3) = 0.0523410480116851;
        A12(0, 4) = 0.01134480421315322;
        A12(0, 5) = -0.02188541653602893;
        A12(0, 6) = -0.02011014217967227;
        A12(0, 7) = 0.02530012973789249;
        A12(0, 8) = -0.01776554014324318;
        A12(0, 9) = 0.0533308784396865;
        A12(0, 10) = -0.02566575404780264;
        A12(0, 11) = -0.03300040025329743;
        A12(0, 12) = 0.07180881355719657;
        A12(0, 13) = -0.01665719009705406;
        A12(0, 14) = -0.03333524009273544;
        A12(0, 15) = -0.0114615152878801;
        A12(1, 0) = -0.04458139215099274;
        A12(1, 1) = 0.03801144510483524;
        A12(1, 2) = -0.02264700302829475;
        A12(1, 3) = -0.03636218979602536;
        A12(1, 4) = -0.04812015009565916;
        A12(1, 5) = 0.01751631592244543;
        A12(1, 6) = -0.0044286054192472;
        A12(1, 7) = 0.02935828194606869;
        A12(1, 8) = -0.02314457656086539;
        A12(1, 9) = -0.03872681980187381;
        A12(1, 10) = -0.0005222189038654831;
        A12(1, 11) = 0.0144539441142796;
        A12(1, 12) = 0.01727402352159306;
        A12(1, 13) = 0.01521200667704923;
        A12(1, 14) = 0.04270212755812303;
        A12(1, 15) = -0.03035572804901483;
        A12(2, 0) = -0.01464968683048722;
        A12(2, 1) = -0.005322616279212881;
        A12(2, 2) = -0.01238300729211829;
        A12(2, 3) = -0.03510643772836228;
        A12(2, 4) = 0.0154635413300382;
        A12(2, 5) = 0.03331472951135474;
        A12(2, 6) = 0.004167520630308722;
        A12(2, 7) = 0.01288530849594505;
        A12(2, 8) = 0.07310612028009013;
        A12(2, 9) = -0.03343034934870379;
        A12(2, 10) = -0.00106928948470796;
        A12(2, 11) = 0.04159121217431273;
        A12(2, 12) = -0.07278158499160975;
        A12(2, 13) = 0.005056266578243263;
        A12(2, 14) = 0.004042388470076389;
        A12(2, 15) = 0.01415833823327272;
        A12(3, 0) = 0.02513802393258052;
        A12(3, 1) = -0.005694462781437661;
        A12(3, 2) = 0.002699117678114175;
        A12(3, 3) = 0.06965121546369608;
        A12(3, 4) = 0.0006094495168925137;
        A12(3, 5) = 0.005792129595412215;
        A12(3, 6) = -0.03265618869090849;
        A12(3, 7) = -0.0181699035002918;
        A12(3, 8) = 0.03456166430868327;
        A12(3, 9) = 0.04105749063907174;
        A12(3, 10) = 0.01925769261844223;
        A12(3, 11) = 0.03315496499835806;
        A12(3, 12) = 0.0401996616276321;
        A12(3, 13) = 0.01503976523674176;
        A12(3, 14) = 0.01375818302324075;
        A12(3, 15) = -0.03852710793730647;
        A12(4, 0) = 0.02053034876700836;
        A12(4, 1) = -0.03898625516721568;
        A12(4, 2) = 0.01340163096863625;
        A12(4, 3) = -0.05494019814440602;
        A12(4, 4) = -0.001291930430148013;
        A12(4, 5) = 0.01421355395516256;
        A12(4, 6) = 0.008565337866362913;
        A12(4, 7) = 0.004242069454960256;
        A12(4, 8) = 0.03371365531000917;
        A12(4, 9) = -0.02519065897646477;
        A12(4, 10) = 0.02853025007872899;
        A12(4, 11) = -0.001535777070771767;
        A12(4, 12) = -0.04487795229533877;
        A12(4, 13) = 0.03118112706286684;
        A12(4, 14) = 0.04956671575872727;
        A12(4, 15) = -0.01983572802218265;
        A12(5, 0) = -0.03956348965612073;
        A12(5, 1) = -0.01123978166307466;
        A12(5, 2) = 0.01999767139040886;
        A12(5, 3) = -0.0600247506163432;
        A12(5, 4) = -0.008680385568872301;
        A12(5, 5) = 0.02694508348534533;
        A12(5, 6) = -0.03594577265976836;
        A12(5, 7) = -0.04218587443509475;
        A12(5, 8) = -0.0482257780526079;
        A12(5, 9) = -0.06419914874972124;
        A12(5, 10) = -0.03840266278112089;
        A12(5, 11) = 0.04494740904207707;
        A12(5, 12) = 0.01552936763518862;
        A12(5, 13) = 0.02152302024719739;
        A12(5, 14) = -0.0001766810403233573;
        A12(5, 15) = -0.02814679993608013;
        A21(0, 0) = -0.6145900812063602;
        A21(0, 1) = -0.4275275185854707;
        A21(0, 2) = 0.6595441916235713;
        A21(0, 3) = -0.06602336857002138;
        A21(0, 4) = 0.07343030477848184;
        A21(0, 5) = -0.6483501100215264;
        A21(0, 6) = -0.4717673018975361;
        A21(0, 7) = 0.4952881330537086;
        A21(0, 8) = -0.4188864527685028;
        A21(0, 9) = 0.1938124215271216;
        A21(0, 10) = -1.276266910249226;
        A21(0, 11) = 0.3182910291681673;
        A21(0, 12) = -0.5570855093224144;
        A21(0, 13) = -0.2946277812879183;
        A21(0, 14) = -0.4667570455798376;
        A21(0, 15) = -1.386659250998571;
        A21(1, 0) = 0.1374146114741916;
        A21(1, 1) = -0.5929146168987074;
        A21(1, 2) = -0.1480997820089378;
        A21(1, 3) = -1.547970971367441;
        A21(1, 4) = -0.2051495716758982;
        A21(1, 5) = 0.1892802537253854;
        A21(1, 6) = 0.6221556100299504;
        A21(1, 7) = 1.208812052085569;
        A21(1, 8) = 0.2020691596478031;
        A21(1, 9) = -0.3471659909052808;
        A21(1, 10) = 0.1665469162031034;
        A21(1, 11) = 0.8189037506605483;
        A21(1, 12) = 0.6934308880657576;
        A21(1, 13) = -0.07745566987528245;
        A21(1, 14) = -0.001167761999034465;
        A21(1, 15) = 0.7927783546291394;
        A21(2, 0) = 0.4880563506029074;
        A21(2, 1) = -0.4868262464635617;
        A21(2, 2) = -0.3664502324905533;
        A21(2, 3) = -0.8255012410725681;
        A21(2, 4) = -0.240177899459849;
        A21(2, 5) = 0.7253954677474035;
        A21(2, 6) = 0.7971416346420371;
        A21(2, 7) = -0.4462669834757567;
        A21(2, 8) = -0.1734528259944743;
        A21(2, 9) = 1.007746234836816;
        A21(2, 10) = 0.3309055025871774;
        A21(2, 11) = 0.2131140728964998;
        A21(2, 12) = 0.6097022107816607;
        A21(2, 13) = -0.3077626926604185;
        A21(2, 14) = 0.5595688843407464;
        A21(2, 15) = -0.1656907819181616;
        A21(3, 0) = 0.5028981805109667;
        A21(3, 1) = 0.01087931853974635;
        A21(3, 2) = -0.4024083769680446;
        A21(3, 3) = -1.247833775434174;
        A21(3, 4) = 0.07965305249830823;
        A21(3, 5) = -0.2304679316017956;
        A21(3, 6) = -0.1236620583812241;
        A21(3, 7) = 0.6052342119801576;
        A21(3, 8) = 0.1733637347241172;
        A21(3, 9) = -0.1534680271313128;
        A21(3, 10) = -0.2893546844789937;
        A21(3, 11) = 0.2335904150027345;
        A21(3, 12) = -0.2476376023578953;
        A21(3, 13) = -0.6617109044809372;
        A21(3, 14) = 0.4376495414953074;
        A21(3, 15) = 0.1992425736877241;
        A21(4, 0) = -0.06401764333073592;
        A21(4, 1) = -0.4256400929739817;
        A21(4, 2) = 0.2553342111710066;
        A21(4, 3) = 0.04020523237835832;
        A21(4, 4) = -0.5429485196622945;
        A21(4, 5) = -0.0451256764575666;
        A21(4, 6) = -0.4886370802308279;
        A21(4, 7) = 0.3342361380550222;
        A21(4, 8) = 0.2938616065545925;
        A21(4, 9) = 0.05592085727977496;
        A21(4, 10) = -0.3566959026202214;
        A21(4, 11) = 0.02637864345860409;
        A21(4, 12) = 0.4667817554680742;
        A21(4, 13) = -0.3563820932505844;
        A21(4, 14) = -1.319625428423618;
        A21(4, 15) = -0.09188329781951578;
        A21(5, 0) = 0.2125531087101398;
        A21(5, 1) = 0.2373128203656912;
        A21(5, 2) = 0.0870103500069449;
        A21(5, 3) = 0.6528137766458927;
        A21(5, 4) = -0.004004727412375207;
        A21(5, 5) = -0.4621710916601871;
        A21(5, 6) = 0.6669388282960435;
        A21(5, 7) = 0.4140014881965217;
        A21(5, 8) = -0.3014347390489598;
        A21(5, 9) = 0.5602877685361889;
        A21(5, 10) = 0.5140424704685326;
        A21(5, 11) = -0.7681702403195825;
        A21(5, 12) = 0.9975395605463754;
        A21(5, 13) = 0.6714453224959402;
        A21(5, 14) = 0.9394016956444027;
        A21(5, 15) = -0.226968228433237;
        A22(0, 0) = 0.04498903140856629;
        A22(0, 1) = -0.05650230126422418;
        A22(0, 2) = 0.03669130267191681;
        A22(0, 3) = 0.1798417077048155;
        A22(0, 4) = 0.03636509270472855;
        A22(0, 5) = -0.0890985282604;
        A22(0, 6) = -0.09505144754449818;
        A22(0, 7) = 0.06769953890840358;
        A22(0, 8) = 0.13210471794639;
        A22(0, 9) = 0.07935602644944209;
        A22(0, 10) = -0.1774150094889666;
        A22(0, 11) = 0.07277622145227795;
        A22(0, 12) = -0.2679656785861791;
        A22(0, 13) = 0.03014019906416971;
        A22(0, 14) = 0.1281505133810848;
        A22(0, 15) = -0.0230278332424688;
        A22(1, 0) = 0.07802227464468575;
        A22(1, 1) = -0.02242830705209959;
        A22(1, 2) = 0.08950442244283426;
        A22(1, 3) = 0.1753017180900554;
        A22(1, 4) = -0.1483220078073223;
        A22(1, 5) = 0.0002551490288438417;
        A22(1, 6) = 0.02414841345286375;
        A22(1, 7) = 0.13193253290135;
        A22(1, 8) = 0.08387224292521855;
        A22(1, 9) = 0.02926268774224481;
        A22(1, 10) = -0.05064681497493846;
        A22(1, 11) = 0.1171934194436863;
        A22(1, 12) = 0.06283828605739571;
        A22(1, 13) = 0.04461169670385428;
        A22(1, 14) = 0.04976400093605569;
        A22(1, 15) = 0.2053661396270399;
        A22(2, 0) = 0.01997271556755343;
        A22(2, 1) = 0.0174226667318401;
        A22(2, 2) = 0.008916670294114094;
        A22(2, 3) = 0.05955857377848824;
        A22(2, 4) = -0.04800665554123598;
        A22(2, 5) = 0.2068575055421193;
        A22(2, 6) = -0.2596376342725436;
        A22(2, 7) = 0.144281562634296;
        A22(2, 8) = -0.002165726415271071;
        A22(2, 9) = -0.1224748753360617;
        A22(2, 10) = -0.1653375959712974;
        A22(2, 11) = 0.08049886186757893;
        A22(2, 12) = 0.2726949728678053;
        A22(2, 13) = 0.1836407362403588;
        A22(2, 14) = -0.04912111080723639;
        A22(2, 15) = 0.3951189742152567;
        A22(3, 0) = -0.04999842170973957;
        A22(3, 1) = -0.07351367544105383;
        A22(3, 2) = 0.07165870169371293;
        A22(3, 3) = -0.1447837686243258;
        A22(3, 4) = 0.007231332354482474;
        A22(3, 5) = 0.01886708383296964;
        A22(3, 6) = -0.1987586603503196;
        A22(3, 7) = -0.002264268538130833;
        A22(3, 8) = -0.03990348748455911;
        A22(3, 9) = 0.08613060332463578;
        A22(3, 10) = -0.1681974903264106;
        A22(3, 11) = -0.1101599721754415;
        A22(3, 12) = -0.1491649135762294;
        A22(3, 13) = 0.06790281389735738;
        A22(3, 14) = -0.1586657909129557;
        A22(3, 15) = 0.07861238438596394;
        A22(4, 0) = -0.005355231781733712;
        A22(4, 1) = -0.1914552942080092;
        A22(4, 2) = 0.02166571313210109;
        A22(4, 3) = -0.03487985745934583;
        A22(4, 4) = 0.05164574343200685;
        A22(4, 5) = -0.1897886623006753;
        A22(4, 6) = -0.2695751602487849;
        A22(4, 7) = -0.1212710722672324;
        A22(4, 8) = -0.1092701952471484;
        A22(4, 9) = -0.05457780348058194;
        A22(4, 10) = 0.07380549832057697;
        A22(4, 11) = -0.1015348092821981;
        A22(4, 12) = -0.1153358570271273;
        A22(4, 13) = -0.1693766497331886;
        A22(4, 14) = 0.06250453803328536;
        A22(4, 15) = -0.04625550971164714;
        A22(5, 0) = -0.2006317852873136;
        A22(5, 1) = 0.1465895378048537;
        A22(5, 2) = -0.1845478727598611;
        A22(5, 3) = 0.0685271056112767;
        A22(5, 4) = 0.0682068726776881;
        A22(5, 5) = -0.0405195405751227;
        A22(5, 6) = 0.1922346503567753;
        A22(5, 7) = -0.1503956850272058;
        A22(5, 8) = -0.0492641159339289;
        A22(5, 9) = 0.1471199911112544;
        A22(5, 10) = 0.3509624829789791;
        A22(5, 11) = -0.003489879704072232;
        A22(5, 12) = -0.240043741885346;
        A22(5, 13) = -0.09743868498242199;
        A22(5, 14) = -0.2024703566158539;
        A22(5, 15) = 0.1369952044451894;
        A23(0, 0) = 0.02005377817510782;
        A23(0, 1) = -0.05502706756468936;
        A23(0, 2) = 0.03401055288931598;
        A23(0, 3) = -0.0008517767526975586;
        A23(0, 4) = -0.03802978140035697;
        A23(0, 5) = 0.01005219239814486;
        A23(0, 6) = 0.03506437374003669;
        A23(0, 7) = 0.01643821934127078;
        A23(0, 8) = -0.05583875916992206;
        A23(0, 9) = -0.05170789203955588;
        A23(0, 10) = 0.04677166243365397;
        A23(0, 11) = 0.05197160106590074;
        A23(0, 12) = -0.06006528895196076;
        A23(0, 13) = -0.04307878638977863;
        A23(0, 14) = 0.02356868155637408;
        A23(0, 15) = 0.01858728960525699;
        A23(1, 0) = -0.02163977713273595;
        A23(1, 1) = 0.03591318677793667;
        A23(1, 2) = -0.02811217414802216;
        A23(1, 3) = 0.0602070742830868;
        A23(1, 4) = 0.008089810999261661;
        A23(1, 5) = -0.03913692106699436;
        A23(1, 6) = -0.04555223155129965;
        A23(1, 7) = 0.05713114891036508;
        A23(1, 8) = 0.02037676209969201;
        A23(1, 9) = 0.000326089848098201;
        A23(1, 10) = 0.00093346953239991;
        A23(1, 11) = -0.04696910235055038;
        A23(1, 12) = -0.04162483427139108;
        A23(1, 13) = -0.04243735756198087;
        A23(1, 14) = -0.0622025657254998;
        A23(1, 15) = -0.03890214008178048;
        A23(2, 0) = -0.04568808498864123;
        A23(2, 1) = -0.02940661371267845;
        A23(2, 2) = 0.004967880440547388;
        A23(2, 3) = 0.0006513447124300196;
        A23(2, 4) = -0.02361088509213865;
        A23(2, 5) = -0.02688821072889898;
        A23(2, 6) = 0.05623067710737959;
        A23(2, 7) = 0.03759837246115541;
        A23(2, 8) = 0.04871782468255222;
        A23(2, 9) = 0.03655198257167164;
        A23(2, 10) = -0.1020980320156372;
        A23(2, 11) = 0.0143282742654023;
        A23(2, 12) = 0.0276589034996228;
        A23(2, 13) = 0.03251054793688614;
        A23(2, 14) = 0.01084698427667308;
        A23(2, 15) = 0.0001761377245742661;
        A23(3, 0) = -0.02901542747293946;
        A23(3, 1) = 0.05772981027003436;
        A23(3, 2) = 0.01629852175204778;
        A23(3, 3) = 0.03595812207538236;
        A23(3, 4) = -0.009605038698363341;
        A23(3, 5) = 0.0469162272952767;
        A23(3, 6) = 0.01868259349431506;
        A23(3, 7) = 0.003860276505943049;
        A23(3, 8) = -0.06080424248963037;
        A23(3, 9) = 0.01881209797006767;
        A23(3, 10) = 0.01456356583589548;
        A23(3, 11) = 0.00347923500457136;
        A23(3, 12) = 0.04897140746605683;
        A23(3, 13) = 0.0009746957181050857;
        A23(3, 14) = 0.02069278562697159;
        A23(3, 15) = -0.02048119825658339;
        A23(4, 0) = -0.01284981034579654;
        A23(4, 1) = 0.03952425912045243;
        A23(4, 2) = -0.002884786213004459;
        A23(4, 3) = -0.02081357564462842;
        A23(4, 4) = 0.002441762126700434;
        A23(4, 5) = -0.01096295157511756;
        A23(4, 6) = 0.07191560273710514;
        A23(4, 7) = 0.08827187229495857;
        A23(4, 8) = 0.02889493371453198;
        A23(4, 9) = 0.02755414512766417;
        A23(4, 10) = -0.02397859391654225;
        A23(4, 11) = -0.02190411535035447;
        A23(4, 12) = -0.03868286899953164;
        A23(4, 13) = -0.03148269238406789;
        A23(4, 14) = -0.01909664676826735;
        A23(4, 15) = 0.03945776915024628;
        A23(5, 0) = -0.08398364394449122;
        A23(5, 1) = -0.02785890572733076;
        A23(5, 2) = 0.001006794203212529;
        A23(5, 3) = 0.05655526551091499;
        A23(5, 4) = 0.04023317010812758;
        A23(5, 5) = 0.03116508101226014;
        A23(5, 6) = -0.02255738569058996;
        A23(5, 7) = -0.01918830211560181;
        A23(5, 8) = 0.00483256533895101;
        A23(5, 9) = 0.01838616216203803;
        A23(5, 10) = -0.02238186677290889;
        A23(5, 11) = 0.01507376680098459;
        A23(5, 12) = 0.01132350417230717;
        A23(5, 13) = 0.02567252426069338;
        A23(5, 14) = -0.04304596792891215;
        A23(5, 15) = 0.06607789922348281;
        A32(0, 0) = -0.5807585870559894;
        A32(0, 1) = 0.7265951258344345;
        A32(0, 2) = -0.5471888922003886;
        A32(0, 3) = -0.3257549855335131;
        A32(0, 4) = -0.803043956073165;
        A32(0, 5) = 0.695369863508855;
        A32(0, 6) = 0.1919585948858529;
        A32(0, 7) = 0.8331849644486191;
        A32(0, 8) = -0.1347352854957171;
        A32(0, 9) = -0.7266178997750732;
        A32(0, 10) = -0.2478430576144359;
        A32(0, 11) = 0.1195922386385292;
        A32(0, 12) = 0.4539055851193695;
        A32(0, 13) = 0.3569822164733438;
        A32(0, 14) = -0.01943497304102333;
        A32(0, 15) = -0.02786408039138762;
        A32(1, 0) = -0.2269742740839001;
        A32(1, 1) = -0.2552734539581255;
        A32(1, 2) = 0.2033335619618966;
        A32(1, 3) = 0.2036471979631988;
        A32(1, 4) = 0.3044792373753218;
        A32(1, 5) = -1.00642045585733;
        A32(1, 6) = 0.4913483480562856;
        A32(1, 7) = 0.2795295775683745;
        A32(1, 8) = 0.5357376700932068;
        A32(1, 9) = 0.222467524480467;
        A32(1, 10) = 0.4505571161888244;
        A32(1, 11) = -0.8766754464190083;
        A32(1, 12) = -0.9744018346849913;
        A32(1, 13) = 0.01091499055882108;
        A32(1, 14) = -0.8863431530291482;
        A32(1, 15) = 0.0787779433827393;
        A32(2, 0) = -0.01420150938346189;
        A32(2, 1) = -0.2259998439846524;
        A32(2, 2) = -0.4653486086861728;
        A32(2, 3) = 0.2785022325133941;
        A32(2, 4) = -0.5968621926851486;
        A32(2, 5) = -0.7873079075911182;
        A32(2, 6) = -0.03510208249866136;
        A32(2, 7) = 0.7727219008897822;
        A32(2, 8) = -0.041489983199258;
        A32(2, 9) = 0.06594556987413186;
        A32(2, 10) = -0.3265799744100953;
        A32(2, 11) = 0.42131837448106;
        A32(2, 12) = -1.208103352844723;
        A32(2, 13) = -0.7182303105327579;
        A32(2, 14) = -0.204606050103438;
        A32(2, 15) = -0.281060159797636;
        A32(3, 0) = 0.957153238373427;
        A32(3, 1) = -0.293557582790553;
        A32(3, 2) = 0.03525595093138323;
        A32(3, 3) = 0.1920365239074954;
        A32(3, 4) = -0.7692199489672833;
        A32(3, 5) = 0.4883720225932084;
        A32(3, 6) = 0.4507668570404117;
        A32(3, 7) = 0.1400776415246649;
        A32(3, 8) = 0.6139950076666904;
        A32(3, 9) = -0.4267314849382983;
        A32(3, 10) = -0.02673753723829356;
        A32(3, 11) = 0.01219117061663348;
        A32(3, 12) = -0.8164593965101603;
        A32(3, 13) = 0.3291912733336352;
        A32(3, 14) = 0.1925660170004818;
        A32(3, 15) = -1.029380730855778;
        A32(4, 0) = 0.7092205776641811;
        A32(4, 1) = 0.1346736969652208;
        A32(4, 2) = 0.7719362739268502;
        A32(4, 3) = 0.4257927272155767;
        A32(4, 4) = 0.6421992620203968;
        A32(4, 5) = 0.8104694872246032;
        A32(4, 6) = -0.2730674029603809;
        A32(4, 7) = 0.04070314588903099;
        A32(4, 8) = 0.2873214251222939;
        A32(4, 9) = -0.249579297292995;
        A32(4, 10) = 0.732965399590846;
        A32(4, 11) = -0.7711530788572648;
        A32(4, 12) = -0.4022438107669882;
        A32(4, 13) = 1.274582783405213;
        A32(4, 14) = -0.1365330974739957;
        A32(4, 15) = -0.7002510295382629;
        A32(5, 0) = -1.08680234851125;
        A32(5, 1) = 0.20660391406569;
        A32(5, 2) = -0.06363150808622357;
        A32(5, 3) = 0.4610550991148233;
        A32(5, 4) = 0.625706583034381;
        A32(5, 5) = -0.1518145588628454;
        A32(5, 6) = -0.4173995513219337;
        A32(5, 7) = 0.5285698003400956;
        A32(5, 8) = -0.356092032215618;
        A32(5, 9) = 0.7826624560910365;
        A32(5, 10) = -0.6752316900273515;
        A32(5, 11) = -0.07886452177762274;
        A32(5, 12) = 0.3590607747866376;
        A32(5, 13) = -0.2514281985381149;
        A32(5, 14) = -0.2409554727264419;
        A32(5, 15) = -0.3523731113030678;
        A33(0, 0) = -0.20518022405525;
        A33(0, 1) = 0.1264217419413027;
        A33(0, 2) = -0.1032444076788796;
        A33(0, 3) = 0.09853221217855472;
        A33(0, 4) = -0.0162214040162626;
        A33(0, 5) = 0.1170855019573248;
        A33(0, 6) = 0.02823722312183156;
        A33(0, 7) = 0.05904155994044034;
        A33(0, 8) = 0.03088475643163776;
        A33(0, 9) = -0.2374879539179493;
        A33(0, 10) = -0.03510606349537129;
        A33(0, 11) = 0.2595501044189001;
        A33(0, 12) = 0.003559489747476665;
        A33(0, 13) = 0.1491171848472453;
        A33(0, 14) = 0.06565899141467697;
        A33(0, 15) = -0.009875606406879544;
        A33(1, 0) = -0.2493192380593028;
        A33(1, 1) = -0.06042022703978699;
        A33(1, 2) = 0.1653213322483214;
        A33(1, 3) = 0.1749905678485847;
        A33(1, 4) = 0.1376559545070126;
        A33(1, 5) = -0.1207943265282417;
        A33(1, 6) = -0.01454207597932745;
        A33(1, 7) = -0.02574819788714538;
        A33(1, 8) = -0.02821000299431571;
        A33(1, 9) = 0.07489551973038244;
        A33(1, 10) = 0.07319791014707404;
        A33(1, 11) = -0.02560251668932571;
        A33(1, 12) = -0.07573468049514709;
        A33(1, 13) = 0.1198878563781404;
        A33(1, 14) = 0.06369525047171748;
        A33(1, 15) = -0.1651554389002235;
        A33(2, 0) = 0.04426552934941428;
        A33(2, 1) = 0.1305744608965229;
        A33(2, 2) = 0.01942135039788126;
        A33(2, 3) = -0.1336402907138825;
        A33(2, 4) = -0.1137136397184978;
        A33(2, 5) = -0.1171308192756423;
        A33(2, 6) = -0.1829460898845075;
        A33(2, 7) = -0.07430873514989807;
        A33(2, 8) = 0.141723420208049;
        A33(2, 9) = 0.1058079919888555;
        A33(2, 10) = -0.08991632158569329;
        A33(2, 11) = 0.0286193767167043;
        A33(2, 12) = 0.05539447742980882;
        A33(2, 13) = -0.04959982439932419;
        A33(2, 14) = 0.08865095971664098;
        A33(2, 15) = -0.06863607337564263;
        A33(3, 0) = -0.1739214122392983;
        A33(3, 1) = -0.09592043575760982;
        A33(3, 2) = -0.01627272372952281;
        A33(3, 3) = 0.07083768778038957;
        A33(3, 4) = -0.08023102307652617;
        A33(3, 5) = -0.1758638437170545;
        A33(3, 6) = 0.08572368733129679;
        A33(3, 7) = 0.01046092833759228;
        A33(3, 8) = 0.075188920221163;
        A33(3, 9) = 0.04524670492679771;
        A33(3, 10) = 0.06601480336901587;
        A33(3, 11) = -0.1082325563674827;
        A33(3, 12) = 0.3909825990927209;
        A33(3, 13) = 0.1263423041243657;
        A33(3, 14) = -0.1493147265312899;
        A33(3, 15) = 0.06032071990624937;
        A33(4, 0) = 0.09823393798847152;
        A33(4, 1) = 0.0215995842271231;
        A33(4, 2) = 0.1960010712799449;
        A33(4, 3) = 0.1953529078242947;
        A33(4, 4) = 0.1171306877268085;
        A33(4, 5) = 0.2126842249972627;
        A33(4, 6) = 0.1336204977923928;
        A33(4, 7) = 0.2008800056907265;
        A33(4, 8) = 0.1110341134820908;
        A33(4, 9) = -0.3196626790447556;
        A33(4, 10) = -0.1381564304147012;
        A33(4, 11) = 0.1080129352065511;
        A33(4, 12) = -0.03485876170233348;
        A33(4, 13) = 0.1147967807358377;
        A33(4, 14) = -0.1271172255286152;
        A33(4, 15) = 0.2365234550719833;
        A33(5, 0) = 0.007663940998659215;
        A33(5, 1) = 0.01309611442447917;
        A33(5, 2) = 0.1474625674710183;
        A33(5, 3) = 0.2076519412067764;
        A33(5, 4) = 0.1589758529376913;
        A33(5, 5) = -0.2281724705118267;
        A33(5, 6) = -0.121727813834463;
        A33(5, 7) = 0.04288398691371665;
        A33(5, 8) = 0.03827564074116113;
        A33(5, 9) = 0.1704205421133972;
        A33(5, 10) = 0.2955115176511617;
        A33(5, 11) = -0.1459281512139341;
        A33(5, 12) = -0.0144252733224421;
        A33(5, 13) = 0.08908033833372579;
        A33(5, 14) = -0.1110663260447344;
        A33(5, 15) = -0.02728263949744499;

        y[0]  =  0.02870086311938944;
        y[1]  =  0.1175003168716111;
        y[2]  = -0.1515847961351451;
        y[3]  =  0.1505547735841594;
        y[4]  = -0.1455454040444207;
        y[5]  = -0.005920747249115491;
        y[6]  = -0.07756007555081139;
        y[7]  =  0.04965944269336302;
        y[8]  = -0.02618954797937402;
        y[9]  = -0.1091749900743318;
        y[10] =  0.3534608038955141;
        y[11] =  0.1687111793839146;
        y[12] =  0.02986088881618923;
        y[13] =  0.3338523250083144;
        y[14] = -0.2157466124794613;
        y[15] = -0.05983451942612914;
        y[16] =  0.3565182110664509;
        y[17] =  0.1284853842504208;
        y[18] = -1.213635568400954;
        y[19] = -0.3853144428152422;
        y[20] =  0.2873913454624051;
        y[21] =  0.606508894636617;
        y[22] = -0.1888318629757898;
        y[23] =  0.5115393744008212;
        y[24] =  0.4585227388135282;
        y[25] =  0.4625892810224007;
        y[26] = -0.2642870217569031;
        y[27] =  0.2782096036434844;
        y[28] = -1.812428673854987;
        y[29] =  0.5031056817062842;
        y[30] =  0.4263730262135199;
        y[31] = -0.110100103138641;
        y[32] = -1.038368199050394;
        y[33] =  2.23973120817613;

        klab::KRandom::Instance().setSeed(12345);

        TBlockTridiagonalOperator<klab::DoubleReal>::TOperatorArray diagonal;
        diagonal.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A00), 1.0));
        diagonal.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A11), 1.0));
        diagonal.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A22), 1.0));
        diagonal.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A33), 1.0));

        TBlockTridiagonalOperator<klab::DoubleReal>::TOperatorArray lower;
        lower.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A10), 20.0));
        lower.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A21), 20.0));
        lower.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A32), 20.0));

        TBlockTridiagonalOperator<klab::DoubleReal>::TOperatorArray upper;
        upper.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A01), 0.1));
        upper.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A12), 0.1));
        upper.push_back(new TVarianceShadowOperator<klab::DoubleReal>(new TMatrixOperator<klab::DoubleReal>(A23), 0.1));

        klab::TSmartPointer<TBlockOperator<klab::DoubleReal> > phi = new TBlockTridiagonalOperator<klab::DoubleReal>(diagonal, lower, upper);    

        TEMBPSolver<klab::DoubleReal> embp(1e-4, 500);
        embp.setNoiseVariance(1e-15);
        embp.setMessageDamping(0.5);
        embp.setLearningDamping(0.5);
        embp.enableDampingLearning(true);    
        embp.enableParameterLearning(true);   
        embp.enableHomogeneous(false);
        embp.enableHistory(true);

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();
        
#if !defined(KLAB_UNIX_SYSTEM)          // To investigate.
    #if !defined(KLAB_64BITS_PLATFORM)  // To investigate.
        TEST_ASSERT(klab::Equals(snr, 85.174451608026786, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 9.0478769325127729e-005, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 2.4782439176504721e-005, 1e-6))
        TEST_ASSERT(iterations == 403)

        TEST_ASSERT(embp.history().size() == 404)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 3.6509226828207924, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 3.6545916734841173, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 2.9041567519131721, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 2.0897466820893404, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 2.9508472303235815, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 3.8465654398542597, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 2.6109391685341783, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 3.2219323649904377, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 1.0280541897776558, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 1.0643775274260872, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[403].residualNorm(), 9.0478769325127729e-005, 1e-6))
    #else
/*
std::ofstream of("SolverOut.txt"); // Debug.
of<<"TEST_ASSERT(klab::Equals(snr, "<<std::setprecision(8)<<snr<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(residualNorm, "<<std::setprecision(8)<<residualNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(rrNorm, "<<std::setprecision(8)<<rrNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(iterations == "<<iterations<<")"<<std::endl;
of<<std::endl;
of<<"TEST_ASSERT(embp.history().size() == "<<(iterations+1)<<")"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), "<<std::setprecision(8)<<embp.history()[0].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), "<<std::setprecision(8)<<embp.history()[1].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), "<<std::setprecision(8)<<embp.history()[2].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), "<<std::setprecision(8)<<embp.history()[3].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), "<<std::setprecision(8)<<embp.history()[4].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), "<<std::setprecision(8)<<embp.history()[5].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), "<<std::setprecision(8)<<embp.history()[6].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), "<<std::setprecision(8)<<embp.history()[7].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), "<<std::setprecision(8)<<embp.history()[8].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), "<<std::setprecision(8)<<embp.history()[9].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()["<<iterations<<"].residualNorm(), "<<std::setprecision(8)<<embp.history()[iterations].residualNorm()<<", 1e-6))"<<std::endl;
of.flush();
*/
        TEST_ASSERT(klab::Equals(snr, 85.17, 1e-2))
        TEST_ASSERT(klab::Equals(residualNorm, 9.0483362e-005, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 2.4783697e-005, 1e-6))
        TEST_ASSERT(iterations == 403)

        TEST_ASSERT(embp.history().size() == 404)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 3.6509227, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 3.6545917, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 2.9041568, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 2.0897467, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 2.9508472, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 3.8465654, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 2.6109392, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 3.2219324, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 1.0280542, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 1.0643775, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[403].residualNorm(), 9.0483362e-005, 1e-8))
    #endif
#else
	#if !defined(KLAB_64BITS_PLATFORM)  // To investigate.
/*
std::ofstream of("SolverOut.txt"); // Debug.
of<<"TEST_ASSERT(klab::Equals(snr, "<<std::setprecision(8)<<snr<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(residualNorm, "<<std::setprecision(8)<<residualNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(rrNorm, "<<std::setprecision(8)<<rrNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(iterations == "<<iterations<<")"<<std::endl;
of<<std::endl;
of<<"TEST_ASSERT(embp.history().size() == "<<(iterations+1)<<")"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), "<<std::setprecision(8)<<embp.history()[0].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), "<<std::setprecision(8)<<embp.history()[1].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), "<<std::setprecision(8)<<embp.history()[2].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), "<<std::setprecision(8)<<embp.history()[3].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), "<<std::setprecision(8)<<embp.history()[4].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), "<<std::setprecision(8)<<embp.history()[5].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), "<<std::setprecision(8)<<embp.history()[6].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), "<<std::setprecision(8)<<embp.history()[7].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), "<<std::setprecision(8)<<embp.history()[8].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), "<<std::setprecision(8)<<embp.history()[9].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()["<<iterations<<"].residualNorm(), "<<std::setprecision(8)<<embp.history()[iterations].residualNorm()<<", 1e-6))"<<std::endl;
of.flush();
*/
		TEST_ASSERT(klab::Equals(snr, 85.167698, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 9.048723e-05, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 2.4784757e-05, 1e-6))
        TEST_ASSERT(iterations == 403)

        TEST_ASSERT(embp.history().size() == 404)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 3.6509227, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 3.6545917, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 2.9041568, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 2.0897467, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 2.9508472, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 3.8465654, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 2.6109392, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 3.2219324, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 1.0280542, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 1.0643775, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[403].residualNorm(), 9.048723e-05, 1e-6))
	#else
/*
std::ofstream of("SolverOut.txt"); // Debug.
of<<"TEST_ASSERT(klab::Equals(snr, "<<std::setprecision(8)<<snr<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(residualNorm, "<<std::setprecision(8)<<residualNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(rrNorm, "<<std::setprecision(8)<<rrNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(iterations == "<<iterations<<")"<<std::endl;
of<<std::endl;
of<<"TEST_ASSERT(embp.history().size() == "<<(iterations+1)<<")"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), "<<std::setprecision(8)<<embp.history()[0].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), "<<std::setprecision(8)<<embp.history()[1].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), "<<std::setprecision(8)<<embp.history()[2].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), "<<std::setprecision(8)<<embp.history()[3].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), "<<std::setprecision(8)<<embp.history()[4].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), "<<std::setprecision(8)<<embp.history()[5].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), "<<std::setprecision(8)<<embp.history()[6].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), "<<std::setprecision(8)<<embp.history()[7].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), "<<std::setprecision(8)<<embp.history()[8].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), "<<std::setprecision(8)<<embp.history()[9].residualNorm()<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(embp.history()["<<iterations<<"].residualNorm(), "<<std::setprecision(8)<<embp.history()[iterations].residualNorm()<<", 1e-6))"<<std::endl;
of.flush();
*/
		TEST_ASSERT(klab::Equals(snr, 85.162214, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 9.048723e-05, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 2.4784757e-05, 1e-6))
        TEST_ASSERT(iterations == 403)

        TEST_ASSERT(embp.history().size() == 404)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 3.6509227, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 3.6545917, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 2.9041568, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 2.0897467, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 2.9508472, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 3.8465654, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 2.6109392, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 3.2219324, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 1.0280542, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 1.0643775, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[403].residualNorm(), 9.048723e-05, 1e-6))
	#endif
#endif
        // Limit cases.
        try                                         {embp.solve(arma::Col<klab::DoubleReal>(), phi, k, xr); TEST_ASSERT(false)}
        catch(KNullVectorEMBPSolverException&)      {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {embp.solve(y, klab::TSmartPointer<TBlockOperator<klab::DoubleReal> >(0), k, xr); TEST_ASSERT(false)}
        catch(KNullOperatorEMBPSolverException&)    {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        embp.solve(y, phi, 0, xr);
        TEST_ASSERT(xr.n_rows == n)
        bool isZero = true;
        for(klab::UInt32 i=0; i<n && isZero; ++i)
            isZero = klab::Equals(xr[i], 0.0, 0.0);
        TEST_ASSERT(isZero)

        embp.setTolerance(1.0);
        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)
        snr          = klab::SNR(x, xr);
        residualNorm = embp.residualNorm();
        rrNorm       = embp.relativeResidualNorm();
        iterations   = embp.iterations();
        TEST_ASSERT(klab::Equals(snr, 6.3700055456701872, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 0.79435049549751768, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.21757527192654297, 1e-6))
        TEST_ASSERT(iterations == 10)
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_11()
{
    try
    {
        klab::UInt32 m = 34;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        klab::KRandom::Instance().setSeed(12345);

        x.fill(0.0);
        x[6]   = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[3]   = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[52]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[21]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[33]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);      

        klab::TSmartPointer<TBlockOperator<klab::DoubleReal> > phi  = new TSeedingOperator<klab::DoubleReal>(4, 16, 16, 6, 16, 1.0, 20.0, 0.1);   

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal> embp(1e-4, 500);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(false);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 79.658776392905793, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 9.6647954993787214e-005, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 3.5963405109273189e-005, 1e-6))
        TEST_ASSERT(iterations == 47)

        TEST_ASSERT(embp.history().size() == 48)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 2.6873972222632072, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 2.6809056974909531, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 1.4014347620289267, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 2.2451128710473518, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 2.3727863789496344, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 2.3072173427881273, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 1.8912462242364692, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 1.2722527650643638, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.47871484230899553, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.56184690638210866, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[47].residualNorm(), 9.6647954993787214e-005, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_12()
{
    try
    {
        klab::UInt32 m = 68;    // Number of observations.
        klab::UInt32 n = 128;   // Signal size.
        klab::UInt32 k = 10;    // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;

        klab::KRandom::Instance().setSeed(12345);

        x.fill(0.0);
        x[6]   = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[3]   = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[52]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[21]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[33]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);  
        x[70]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[67]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[116] = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[85]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0);
        x[97]  = klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0); 

        klab::TSmartPointer<TBlockOperator<klab::DoubleReal> > phi = new TSeedingOperator<klab::DoubleReal>(4, 32, 32, 12, 32, 1.0, 20.0, 0.1);   

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal> embp(1e-4, 500);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(false);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 80.756558741692345, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 9.9355707526748574e-005, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 3.7070159743321126e-005, 1e-6))
        TEST_ASSERT(iterations == 49)

        TEST_ASSERT(embp.history().size() == 50)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 2.6802071589305561, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 2.6801173921643526, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 2.5115715624166510, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 1.7194077722966932, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 1.6095144778657238, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 1.4834133177986200, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 0.84636061544975127, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.68064729619481212, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.94244479340440201, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.96573840820576407, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[49].residualNorm(), 9.9355707526748574e-005, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_13()
{
    try
    {
        klab::UInt32 m = 34;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        klab::KRandom::Instance().setSeed(12345);

        x.fill(0.0);
        x[6]   = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[3]   = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[52]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[21]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[33]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0));      

        klab::TSmartPointer<TBlockOperator<std::complex<klab::DoubleReal> > > phi = new TSeedingOperator<std::complex<klab::DoubleReal> >(4, 16, 16, 6, 16, std::complex<klab::DoubleReal>(0.5, 0.5), std::complex<klab::DoubleReal>(10.0, 10.0), std::complex<klab::DoubleReal>(0.05, 0.05)); 

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > embp(1e-4, 500);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(false);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        arma::Col<klab::DoubleReal> rx(x.n_rows);
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            rx[i] = klab::CastTo<klab::DoubleReal>(x[i]);

        arma::Col<klab::DoubleReal> rxr(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);

        klab::DoubleReal snr          = klab::SNR(rx, rxr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 78.454366149144278, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 9.2319494367635406e-005, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 2.6528516903304699e-005, 1e-6))
        TEST_ASSERT(iterations == 43)

        TEST_ASSERT(embp.history().size() == 44)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 3.4800096328089500, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 3.4803426794417711, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 1.7547485623781747, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 3.2602328385761719, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 1.9567251158003280, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 0.96971082410739851, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 0.83523393388722589, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.90157662129320060, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.66956329380906088, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 0.30567585734853647, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[43].residualNorm(), 9.2319494367635406e-005, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_14()
{
    try
    {
        klab::UInt32 m = 34;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        klab::KRandom::Instance().setSeed(12345);

        x.fill(0.0);
        x[6]   = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[3]   = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[52]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[21]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[33]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > fourier16 = new TFourier1DOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > opBlock16 = new TScalingOperator<std::complex<klab::DoubleReal> >(fourier16, klab::Sqrt(3.0)); //new TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> >(16, 16, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(klab::INV_SQRT2, klab::INV_SQRT2));  // new TScalingOperator<std::complex<klab::DoubleReal> >(fourier16, klab::INV_SQRT2);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > downsampling1 = new TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(6, 16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > downsampling2 = new TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(6, 16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > downsampling3 = new TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(6, 16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > downsampling4 = new TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(6, 16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > downsampling5 = new TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(6, 16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > downsampling6 = new TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(6, 16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > downsampling7 = new TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(6, 16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > downsampling8 = new TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(6, 16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation1 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation2 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation3 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation4 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation5 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation6 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation7 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation8 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation9 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation10 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation11 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation12 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation13 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation14 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation15 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation16 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation17 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation18 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation19 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > permutation20 = new TRandomPermutationOperator<std::complex<klab::DoubleReal> >(16);

        klab::DoubleReal invN = 1.0 / static_cast<klab::DoubleReal>(n);

        TBlockTridiagonalOperator<std::complex<klab::DoubleReal> >::TOperatorArray diagonal;
        diagonal.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(permutation1*opBlock16*permutation2, invN), 1.0));
        diagonal.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(downsampling2*permutation3*opBlock16*permutation4, klab::Sqrt(invN)), 1.0));
        diagonal.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(downsampling5*permutation5*opBlock16*permutation6, klab::Sqrt(invN)), 1.0));
        diagonal.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(downsampling8*permutation7*opBlock16*permutation8, klab::Sqrt(invN)), 1.0));

        TBlockTridiagonalOperator<std::complex<klab::DoubleReal> >::TOperatorArray lower;
        lower.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(downsampling1*permutation9*opBlock16*permutation10, klab::Sqrt(20.0*invN)), 20.0));
        lower.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(downsampling4*permutation11*opBlock16*permutation12, klab::Sqrt(20.0*invN)), 20.0));
        lower.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(downsampling7*permutation13*opBlock16*permutation14, klab::Sqrt(20.0*invN)), 20.0));

        TBlockTridiagonalOperator<std::complex<klab::DoubleReal> >::TOperatorArray upper;
        upper.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(permutation15*opBlock16*permutation16, klab::Sqrt(0.1*invN)), 0.1));
        upper.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(downsampling3*permutation17*opBlock16*permutation18, klab::Sqrt(0.1*invN)), 0.1));
        upper.push_back(new TVarianceShadowOperator<std::complex<klab::DoubleReal> >(new TScalingOperator<std::complex<klab::DoubleReal> >(downsampling6*permutation19*opBlock16*permutation20, klab::Sqrt(0.1*invN)), 0.1));

        klab::TSmartPointer<TBlockOperator<std::complex<klab::DoubleReal> > > phi = new TBlockTridiagonalOperator<std::complex<klab::DoubleReal> >(diagonal, lower, upper);            

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > embp(1e-4, 500);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(false);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        arma::Col<klab::DoubleReal> rx(x.n_rows);
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            rx[i] = klab::CastTo<klab::DoubleReal>(x[i]);

        arma::Col<klab::DoubleReal> rxr(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);

        klab::DoubleReal snr          = klab::SNR(rx, rxr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 83.747781658632334, 1e-4))
        TEST_ASSERT(klab::Equals(residualNorm, 9.4053804050400590e-005, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 1.8650466639739547e-005, 1e-6))
        TEST_ASSERT(iterations == 107)

        TEST_ASSERT(embp.history().size() == 108)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 5.0429732331734325, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 5.0318465704144835, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 1.9673383197826297, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 3.5094335567534811, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 1.5110820624321841, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 1.5043614232558888, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 2.0952905429780353, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 0.82199603934030485, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 0.84206494071344185, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 1.0929504199830247, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[107].residualNorm(), 9.4053804050400590e-005, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KEMBPSolverUnitTest::testSolve_15()
{
    try
    {
        klab::UInt32 m = 34;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        klab::KRandom::Instance().setSeed(12345);

        x.fill(0.0);
        x[6]   = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[3]   = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[52]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[21]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 
        x[33]  = std::complex<klab::DoubleReal>(klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0), klab::KRandom::Instance().generateDoubleReal(-1.0, 1.0)); 

        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > fourier16 = new TFourier1DOperator<std::complex<klab::DoubleReal> >(16);
        klab::TSmartPointer<TOperator<std::complex<klab::DoubleReal> > > op = new TScalingOperator<std::complex<klab::DoubleReal> >(fourier16, klab::Sqrt(3.0/n));
        klab::TSmartPointer<TBlockOperator<std::complex<klab::DoubleReal> > > phi = new TGenericSeedingOperator<std::complex<klab::DoubleReal> >(op, 4, 16, 6, 1.0, 20.0, 0.1);             

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TEMBPSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > embp(1e-4, 500);
        embp.setNoiseVariance(0.0);
        embp.setMessageDamping(0.5);
        embp.enableDampingLearning(false);
        embp.enableParameterLearning(false);
        embp.enableHomogeneous(false);
        embp.enableHistory(true);        

        embp.solve(y, phi, k, xr);
        TEST_ASSERT(xr.n_rows == n)

        arma::Col<klab::DoubleReal> rx(x.n_rows);
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            rx[i] = klab::CastTo<klab::DoubleReal>(x[i]);

        arma::Col<klab::DoubleReal> rxr(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);

        klab::DoubleReal snr          = klab::SNR(rx, rxr);
        klab::DoubleReal residualNorm = embp.residualNorm();
        klab::DoubleReal rrNorm       = embp.relativeResidualNorm();
        klab::UInt32 iterations       = embp.iterations();

        TEST_ASSERT(klab::Equals(snr, 97.981310103347198, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 5.5327865593043660e-005, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 1.0474475238021209e-005, 1e-6))
        TEST_ASSERT(iterations == 48)

        TEST_ASSERT(embp.history().size() == 49)
        TEST_ASSERT(klab::Equals(embp.history()[0].residualNorm(), 5.2821610950216877, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[1].residualNorm(), 5.2782218102408107, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[2].residualNorm(), 4.2714114023248531, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[3].residualNorm(), 2.6526793841326253, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[4].residualNorm(), 2.8311327474154560, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[5].residualNorm(), 2.0589352952719175, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[6].residualNorm(), 1.8110862444282787, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[7].residualNorm(), 1.2150507085639846, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[8].residualNorm(), 1.1835997081080045, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[9].residualNorm(), 2.1837208234542005, 1e-6))
        TEST_ASSERT(klab::Equals(embp.history()[48].residualNorm(), 5.5327865593043660e-005, 1e-6))
    }
    catch(klab::KException&)
    {
        TEST_ASSERT(false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
