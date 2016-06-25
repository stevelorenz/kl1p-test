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

#include "BasisPursuitSolverUnitTest.h"
#include "../include/BasisPursuitSolver.h"
#include "../include/MatrixOperator.h"
#include "../include/DownSamplingOperator.h"
#include "../include/Fourier1DOperator.h"
#include "../include/NormalRandomMatrixOperator.h"
#include "../include/MultiplicationOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KBasisPursuitSolverUnitTest::KBasisPursuitSolverUnitTest() : Test::Suite()
{
    TEST_ADD(KBasisPursuitSolverUnitTest::testDefaultConstructor)  
    TEST_ADD(KBasisPursuitSolverUnitTest::testToleranceConstructor)
    TEST_ADD(KBasisPursuitSolverUnitTest::testToleranceIterationLimitConstructor)
    TEST_ADD(KBasisPursuitSolverUnitTest::testToleranceIterationLimitBacktrackingIterationLimitConstructor)
    TEST_ADD(KBasisPursuitSolverUnitTest::testCopyConstructor)
    TEST_ADD(KBasisPursuitSolverUnitTest::testAffectationOperator)

    TEST_ADD(KBasisPursuitSolverUnitTest::testSetTolerance)
    TEST_ADD(KBasisPursuitSolverUnitTest::testSetIterationLimit)
    TEST_ADD(KBasisPursuitSolverUnitTest::testSetBacktrackingIterationLimit)
    TEST_ADD(KBasisPursuitSolverUnitTest::testSetAlpha)
    TEST_ADD(KBasisPursuitSolverUnitTest::testSetBeta)
    TEST_ADD(KBasisPursuitSolverUnitTest::testSetMu)
    TEST_ADD(KBasisPursuitSolverUnitTest::testTolerance)
    TEST_ADD(KBasisPursuitSolverUnitTest::testIterationLimit)
    TEST_ADD(KBasisPursuitSolverUnitTest::testBacktrackingIterationLimit)
    TEST_ADD(KBasisPursuitSolverUnitTest::testAlpha)
    TEST_ADD(KBasisPursuitSolverUnitTest::testBeta)
    TEST_ADD(KBasisPursuitSolverUnitTest::testMu)
    TEST_ADD(KBasisPursuitSolverUnitTest::testResidualNorm)
    TEST_ADD(KBasisPursuitSolverUnitTest::testRelativeResidualNorm)
    TEST_ADD(KBasisPursuitSolverUnitTest::testDualityGap)
    TEST_ADD(KBasisPursuitSolverUnitTest::testIterations)
    TEST_ADD(KBasisPursuitSolverUnitTest::testConjugateGradientSolver)
    TEST_ADD(KBasisPursuitSolverUnitTest::testEnableHistory)
    TEST_ADD(KBasisPursuitSolverUnitTest::testIsHistoryEnabled)
    TEST_ADD(KBasisPursuitSolverUnitTest::testHistory)
    TEST_ADD(KBasisPursuitSolverUnitTest::testSolve)       
    TEST_ADD(KBasisPursuitSolverUnitTest::testSolve_02)   
    TEST_ADD(KBasisPursuitSolverUnitTest::testSolve_03)   
    TEST_ADD(KBasisPursuitSolverUnitTest::testSolve_04)   
}

// ---------------------------------------------------------------------------------------------------- //

KBasisPursuitSolverUnitTest::~KBasisPursuitSolverUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testDefaultConstructor()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-6))
        TEST_ASSERT(bp.iterationLimit() == 50)
        TEST_ASSERT(bp.backtrackingIterationLimit() == 32)
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.01))
        TEST_ASSERT(klab::Equals(bp.beta(), 0.5))
        TEST_ASSERT(klab::Equals(bp.mu(), 10.0))
        TEST_ASSERT(klab::Equals(bp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.dualityGap(), 0.0))
        TEST_ASSERT(bp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testToleranceConstructor()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp(1e-5);
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-5))
        TEST_ASSERT(bp.iterationLimit() == 50)
        TEST_ASSERT(bp.backtrackingIterationLimit() == 32)
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.01))
        TEST_ASSERT(klab::Equals(bp.beta(), 0.5))
        TEST_ASSERT(klab::Equals(bp.mu(), 10.0))
        TEST_ASSERT(klab::Equals(bp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.dualityGap(), 0.0))
        TEST_ASSERT(bp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testToleranceIterationLimitConstructor()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp(1e-5, 30);
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-5))
        TEST_ASSERT(bp.iterationLimit() == 30)
        TEST_ASSERT(bp.backtrackingIterationLimit() == 32)
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.01))
        TEST_ASSERT(klab::Equals(bp.beta(), 0.5))
        TEST_ASSERT(klab::Equals(bp.mu(), 10.0))
        TEST_ASSERT(klab::Equals(bp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.dualityGap(), 0.0))
        TEST_ASSERT(bp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testToleranceIterationLimitBacktrackingIterationLimitConstructor()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp(1e-5, 30, 16);
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-5))
        TEST_ASSERT(bp.iterationLimit() == 30)
        TEST_ASSERT(bp.backtrackingIterationLimit() == 16)
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.01))
        TEST_ASSERT(klab::Equals(bp.beta(), 0.5))
        TEST_ASSERT(klab::Equals(bp.mu(), 10.0))
        TEST_ASSERT(klab::Equals(bp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.dualityGap(), 0.0))
        TEST_ASSERT(bp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testCopyConstructor()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp(1e-5, 30, 16);
        bp.setAlpha(0.02);
        bp.setBeta(0.1);
        bp.setMu(5.0);
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-5))
        TEST_ASSERT(bp.iterationLimit() == 30)
        TEST_ASSERT(bp.backtrackingIterationLimit() == 16)
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.02))
        TEST_ASSERT(klab::Equals(bp.beta(), 0.1))
        TEST_ASSERT(klab::Equals(bp.mu(), 5.0))
        TEST_ASSERT(klab::Equals(bp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.dualityGap(), 0.0))
        TEST_ASSERT(bp.iterations() == 0)

        TBasisPursuitSolver<klab::DoubleReal> bp2(bp);
        TEST_ASSERT(klab::Equals(bp2.tolerance(), 1e-5))
        TEST_ASSERT(bp2.iterationLimit() == 30)
        TEST_ASSERT(bp2.backtrackingIterationLimit() == 16)
        TEST_ASSERT(klab::Equals(bp2.alpha(), 0.02))
        TEST_ASSERT(klab::Equals(bp2.beta(), 0.1))
        TEST_ASSERT(klab::Equals(bp2.mu(), 5.0))
        TEST_ASSERT(klab::Equals(bp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp2.dualityGap(), 0.0))
        TEST_ASSERT(bp2.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testAffectationOperator()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp(1e-5, 30, 16);
        bp.setAlpha(0.02);
        bp.setBeta(0.1);
        bp.setMu(5.0);
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-5))
        TEST_ASSERT(bp.iterationLimit() == 30)
        TEST_ASSERT(bp.backtrackingIterationLimit() == 16)
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.02))
        TEST_ASSERT(klab::Equals(bp.beta(), 0.1))
        TEST_ASSERT(klab::Equals(bp.mu(), 5.0))
        TEST_ASSERT(klab::Equals(bp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.dualityGap(), 0.0))
        TEST_ASSERT(bp.iterations() == 0)

        TBasisPursuitSolver<klab::DoubleReal> bp2;
        bp2 = bp;
        TEST_ASSERT(klab::Equals(bp2.tolerance(), 1e-5))
        TEST_ASSERT(bp2.iterationLimit() == 30)
        TEST_ASSERT(bp2.backtrackingIterationLimit() == 16)
        TEST_ASSERT(klab::Equals(bp2.alpha(), 0.02))
        TEST_ASSERT(klab::Equals(bp2.beta(), 0.1))
        TEST_ASSERT(klab::Equals(bp2.mu(), 5.0))
        TEST_ASSERT(klab::Equals(bp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(bp2.dualityGap(), 0.0))
        TEST_ASSERT(bp2.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testSetTolerance()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-6))

        bp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testSetIterationLimit()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(bp.iterationLimit() == 50)

        bp.setIterationLimit(30);
        TEST_ASSERT(bp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testSetBacktrackingIterationLimit()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(bp.backtrackingIterationLimit() == 32)

        bp.setBacktrackingIterationLimit(16);
        TEST_ASSERT(bp.backtrackingIterationLimit() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testSetAlpha()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.01))

        bp.setAlpha(0.05);
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.05))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testSetBeta()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.beta(), 0.5))

        bp.setBeta(0.1);
        TEST_ASSERT(klab::Equals(bp.beta(), 0.1))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testSetMu()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.mu(), 10.0))

        bp.setMu(5.0);
        TEST_ASSERT(klab::Equals(bp.mu(), 5.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testTolerance()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-6))

        bp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(bp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testIterationLimit()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(bp.iterationLimit() == 50)

        bp.setIterationLimit(30);
        TEST_ASSERT(bp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testBacktrackingIterationLimit()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(bp.backtrackingIterationLimit() == 32)

        bp.setBacktrackingIterationLimit(16);
        TEST_ASSERT(bp.backtrackingIterationLimit() == 16)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testAlpha()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.01))

        bp.setAlpha(0.05);
        TEST_ASSERT(klab::Equals(bp.alpha(), 0.05))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testBeta()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.beta(), 0.5))

        bp.setBeta(0.1);
        TEST_ASSERT(klab::Equals(bp.beta(), 0.1))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testMu()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.mu(), 10.0))

        bp.setMu(5.0);
        TEST_ASSERT(klab::Equals(bp.mu(), 5.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testResidualNorm()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.residualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testRelativeResidualNorm()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.relativeResidualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testDualityGap()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.dualityGap(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testIterations()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(bp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testConjugateGradientSolver()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(klab::Equals(bp.conjugateGradientSolver().tolerance(), 1.2345) == false)

        bp.conjugateGradientSolver().setTolerance(1.2345);
        TEST_ASSERT(klab::Equals(bp.conjugateGradientSolver().tolerance(), 1.2345))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testEnableHistory()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(bp.isHistoryEnabled() == false)

        bp.enableHistory(true);
        TEST_ASSERT(bp.isHistoryEnabled() == true)

        bp.enableHistory(false);
        TEST_ASSERT(bp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testIsHistoryEnabled()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(bp.isHistoryEnabled() == false)

        bp.enableHistory(true);
        TEST_ASSERT(bp.isHistoryEnabled() == true)

        bp.enableHistory(false);
        TEST_ASSERT(bp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testHistory()
{
    try
    {
        TBasisPursuitSolver<klab::DoubleReal> bp;
        TEST_ASSERT(bp.history().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KBasisPursuitSolverUnitTest::testSolve()
{
    try
    {
        klab::UInt32 m = 30;    // Number of observations.
        klab::UInt32 n = 128;   // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> xr;
        arma::Mat<klab::DoubleReal> A(m, n);

        x.fill(0.0);
        x[6]   =  1.0;
        x[3]   = -1.0;
        x[105] = -1.0;
        x[21]  =  1.0;
        x[33]  = -1.0;
    
        A(0, 0) = 0.065183320555289151;
        A(0, 1) = 0.022563470619482256;
        A(0, 2) = -0.11766814834934326;
        A(0, 3) = 0.051192987268510688;
        A(0, 4) = -0.11536270545640007;
        A(0, 5) = -0.03091227003133578;
        A(0, 6) = 0.18161380897606527;
        A(0, 7) = 0.0035633142879575828;
        A(0, 8) = 0.051354258348934971;
        A(0, 9) = 0.0051689057941326777;
        A(0, 10) = -0.11501094932659875;
        A(0, 11) = -0.030115198960257099;
        A(0, 12) = 0.058263262372945782;
        A(0, 13) = 0.12374983896418604;
        A(0, 14) = 0.029645712805125242;
        A(0, 15) = 0.025021475850203097;
        A(0, 16) = -0.048150366416987;
        A(0, 17) = -0.05460441817968896;
        A(0, 18) = 0.020931013112740888;
        A(0, 19) = 0.12385679940142677;
        A(0, 20) = -0.076376975165828698;
        A(0, 21) = -0.013733086101846172;
        A(0, 22) = 0.066850707325661882;
        A(0, 23) = 0.010034147798875848;
        A(0, 24) = 0.0040375356309960767;
        A(0, 25) = 0.019705414085120471;
        A(0, 26) = -0.056158841863633041;
        A(0, 27) = -0.055791839931537371;
        A(0, 28) = 0.054478452318788756;
        A(0, 29) = 0.071703821011001548;
        A(0, 30) = -0.10916827330414028;
        A(0, 31) = -0.080007378971593324;
        A(0, 32) = -0.01838737649620991;
        A(0, 33) = 0.050000699251362447;
        A(0, 34) = -0.033470825712239222;
        A(0, 35) = -0.018320506432342738;
        A(0, 36) = -0.11536441272153464;
        A(0, 37) = 0.069387553768697652;
        A(0, 38) = 0.093448766415525894;
        A(0, 39) = -0.13731876040581154;
        A(0, 40) = 0.17219116305612042;
        A(0, 41) = -0.086828495861680288;
        A(0, 42) = 0.11513221002748608;
        A(0, 43) = -0.0072267253702953419;
        A(0, 44) = 0.08646112713940303;
        A(0, 45) = -0.019177799017444291;
        A(0, 46) = 0.086335371276838102;
        A(0, 47) = 0.033359787375076722;
        A(0, 48) = 0.025736284857275117;
        A(0, 49) = -0.00083815556553631584;
        A(0, 50) = 0.057818427830460595;
        A(0, 51) = 0.031979116938883508;
        A(0, 52) = -0.051676204408399526;
        A(0, 53) = -0.032609594802794704;
        A(0, 54) = -0.01005949902920974;
        A(0, 55) = 0.0085473405499081542;
        A(0, 56) = 0.15127401142424871;
        A(0, 57) = -0.11498003595859205;
        A(0, 58) = 0.16136126427910685;
        A(0, 59) = 0.028015662494376373;
        A(0, 60) = -0.12578201006867232;
        A(0, 61) = -0.19393222239713279;
        A(0, 62) = -0.12483840330723942;
        A(0, 63) = -0.067051412468489627;
        A(0, 64) = -0.00053348844581491139;
        A(0, 65) = -0.019824901189012006;
        A(0, 66) = 0.030347295830991265;
        A(0, 67) = 0.12786349443739511;
        A(0, 68) = 0.13457754692308443;
        A(0, 69) = -0.06869594998419129;
        A(0, 70) = -0.021772563922546638;
        A(0, 71) = 0.0096216247952277019;
        A(0, 72) = -0.024529344914378828;
        A(0, 73) = 0.093359352412570415;
        A(0, 74) = -0.066680063091489605;
        A(0, 75) = -0.11917761092742381;
        A(0, 76) = 0.011736825284728757;
        A(0, 77) = -0.053837031931344072;
        A(0, 78) = -0.019801962210726325;
        A(0, 79) = 0.062653047537366141;
        A(0, 80) = -0.19053872768407398;
        A(0, 81) = -0.16843284916589205;
        A(0, 82) = 0.022771574001092434;
        A(0, 83) = -0.064944148704804569;
        A(0, 84) = 0.025137056087542776;
        A(0, 85) = -0.020451218098126136;
        A(0, 86) = -0.064254541375377505;
        A(0, 87) = -0.017832001541334762;
        A(0, 88) = -0.15178396578258385;
        A(0, 89) = -0.049763252832432478;
        A(0, 90) = 0.0082454898033334223;
        A(0, 91) = -0.14254310465961731;
        A(0, 92) = -0.077108882263156195;
        A(0, 93) = 0.12226746389982202;
        A(0, 94) = 0.065890425966856042;
        A(0, 95) = -0.019114049056952541;
        A(0, 96) = 0.043871864292855792;
        A(0, 97) = -0.11352876624721681;
        A(0, 98) = 0.058299416098382226;
        A(0, 99) = 0.079119711039602997;
        A(0, 100) = 0.1466106207854575;
        A(0, 101) = -0.098167446994633395;
        A(0, 102) = 0.029955759811143623;
        A(0, 103) = -0.17193252473841789;
        A(0, 104) = 0.018989904749143777;
        A(0, 105) = 0.21752162303292816;
        A(0, 106) = -0.025725206680786261;
        A(0, 107) = 0.0075394698596798204;
        A(0, 108) = -0.044233835496698612;
        A(0, 109) = 0.094411432605156442;
        A(0, 110) = -0.084586438360491747;
        A(0, 111) = 0.16974746592309248;
        A(0, 112) = 0.060055353839035409;
        A(0, 113) = -0.092542471385261185;
        A(0, 114) = 0.066946593757318068;
        A(0, 115) = 0.25184177900276261;
        A(0, 116) = -0.18807499156042229;
        A(0, 117) = -0.086951201499382069;
        A(0, 118) = 0.13743038505428806;
        A(0, 119) = -0.038721270395005974;
        A(0, 120) = 0.0019040786229493067;
        A(0, 121) = -0.080609724591075432;
        A(0, 122) = -0.048957877287526208;
        A(0, 123) = 0.075152544933625692;
        A(0, 124) = 0.011369517775538324;
        A(0, 125) = 0.034853487827183824;
        A(0, 126) = 0.061724687933683908;
        A(0, 127) = 0.016147260531413764;
        A(1, 0) = 0.019248358191115214;
        A(1, 1) = -0.11499616857764519;
        A(1, 2) = -0.12835937775755107;
        A(1, 3) = -0.066883999142303446;
        A(1, 4) = 0.00074070659247549298;
        A(1, 5) = -0.13413717828556526;
        A(1, 6) = 0.089512672896689904;
        A(1, 7) = -0.057693516223916969;
        A(1, 8) = -0.035774795210753253;
        A(1, 9) = 0.01293916833271924;
        A(1, 10) = -0.073333342352842598;
        A(1, 11) = -0.030730191588589723;
        A(1, 12) = 0.024994583896641463;
        A(1, 13) = -0.037167808227901458;
        A(1, 14) = -0.068190566489239726;
        A(1, 15) = -0.059706636117022545;
        A(1, 16) = 0.10137295758819669;
        A(1, 17) = -0.036111211540494959;
        A(1, 18) = -0.00010374395323606289;
        A(1, 19) = 0.14223399976571674;
        A(1, 20) = -0.047578562304846944;
        A(1, 21) = 0.071767429912564823;
        A(1, 22) = -0.068327962768524333;
        A(1, 23) = -0.04191301750377853;
        A(1, 24) = -0.0062680183491079233;
        A(1, 25) = 0.12910221629037488;
        A(1, 26) = -0.058898113394511883;
        A(1, 27) = 0.1596894033305058;
        A(1, 28) = 0.003314124614369602;
        A(1, 29) = 0.032081917720090836;
        A(1, 30) = -0.067035027122347435;
        A(1, 31) = -0.049172127389440247;
        A(1, 32) = -0.078533289058658556;
        A(1, 33) = -0.011282507792607798;
        A(1, 34) = -0.052211267319001595;
        A(1, 35) = 0.011142101969616699;
        A(1, 36) = 0.048441587182974463;
        A(1, 37) = 0.052722306299229804;
        A(1, 38) = 0.0037523439153307053;
        A(1, 39) = 0.066696496523982643;
        A(1, 40) = -0.068338826780485917;
        A(1, 41) = -0.041348084272447232;
        A(1, 42) = -0.010477305561836086;
        A(1, 43) = 0.046161846046899144;
        A(1, 44) = -0.039134285469450421;
        A(1, 45) = -0.041412632333808569;
        A(1, 46) = -0.10431400496028331;
        A(1, 47) = -0.066629464225521129;
        A(1, 48) = 0.050810560511751139;
        A(1, 49) = -0.094569962145170494;
        A(1, 50) = 0.012603349590126173;
        A(1, 51) = 0.096865536743173344;
        A(1, 52) = -0.0738536189753628;
        A(1, 53) = -0.094287731030324881;
        A(1, 54) = 0.041284953109730148;
        A(1, 55) = 0.0011775511061794218;
        A(1, 56) = -0.10983161272088074;
        A(1, 57) = -0.086969897526424311;
        A(1, 58) = 0.1001684719237296;
        A(1, 59) = 0.23573862969476628;
        A(1, 60) = -0.0057167541703069293;
        A(1, 61) = 0.078051069262003711;
        A(1, 62) = 0.063328263716485159;
        A(1, 63) = -0.040554779287337979;
        A(1, 64) = -0.021153946307614933;
        A(1, 65) = 0.047570790934681105;
        A(1, 66) = -0.2966315360618228;
        A(1, 67) = 0.074912435025538487;
        A(1, 68) = 0.15907490493596402;
        A(1, 69) = 0.14588924829747763;
        A(1, 70) = 0.11138390667627138;
        A(1, 71) = 0.13116808695564977;
        A(1, 72) = 0.087669058646657486;
        A(1, 73) = -0.11686557215576862;
        A(1, 74) = -0.05121919359366077;
        A(1, 75) = 0.014176443811487881;
        A(1, 76) = 0.13828361461425792;
        A(1, 77) = 0.020934910877805128;
        A(1, 78) = 0.11946206649935792;
        A(1, 79) = 0.022261558557133868;
        A(1, 80) = 0.059074989323282291;
        A(1, 81) = 0.0071244757047876674;
        A(1, 82) = -0.090456034649995271;
        A(1, 83) = 0.030590572372252246;
        A(1, 84) = -0.047538926190295164;
        A(1, 85) = 0.020714002322561854;
        A(1, 86) = -0.10680158315383433;
        A(1, 87) = -0.091725052801910484;
        A(1, 88) = -0.10664577739111521;
        A(1, 89) = 0.11150018739430388;
        A(1, 90) = 0.033821923456183352;
        A(1, 91) = 0.0010550571627804262;
        A(1, 92) = -0.18634419621865506;
        A(1, 93) = -0.013491186429040888;
        A(1, 94) = 0.1197349858704809;
        A(1, 95) = -0.053955183889366667;
        A(1, 96) = -0.0037031419571727942;
        A(1, 97) = 0.15098012481114476;
        A(1, 98) = -0.0046619084751138157;
        A(1, 99) = 0.088727512938763492;
        A(1, 100) = -0.0050772770453435812;
        A(1, 101) = 1.5826643285588027e-005;
        A(1, 102) = 0.098163302447897269;
        A(1, 103) = -0.11454830382201724;
        A(1, 104) = 0.0078273736945123004;
        A(1, 105) = -0.25726161019089155;
        A(1, 106) = -0.15601965547158034;
        A(1, 107) = -0.12012774334354512;
        A(1, 108) = -0.012393034181960597;
        A(1, 109) = -0.099875015988014071;
        A(1, 110) = -0.060586787502570405;
        A(1, 111) = 0.079895900827405608;
        A(1, 112) = -0.011143796875160691;
        A(1, 113) = -0.067227225405364771;
        A(1, 114) = -0.059995196859329684;
        A(1, 115) = 0.092890409395232243;
        A(1, 116) = 0.17302612547788151;
        A(1, 117) = -0.020348999908751549;
        A(1, 118) = -0.028995014332808475;
        A(1, 119) = -0.043802755804054037;
        A(1, 120) = 0.19372201252654148;
        A(1, 121) = 0.096537510791188358;
        A(1, 122) = 0.13008355515226058;
        A(1, 123) = 0.026231916023383511;
        A(1, 124) = 0.046068622549542165;
        A(1, 125) = -2.9079452886684315e-006;
        A(1, 126) = -0.0066909707307050157;
        A(1, 127) = -0.015027872166521211;
        A(2, 0) = 0.011577055662988407;
        A(2, 1) = 0.022311181708334189;
        A(2, 2) = 0.015575472165037171;
        A(2, 3) = -0.0027007183910405831;
        A(2, 4) = -0.13886778714825512;
        A(2, 5) = -0.01950685929963902;
        A(2, 6) = -0.019987433679858592;
        A(2, 7) = -0.12771468098465577;
        A(2, 8) = 0.05138303899589805;
        A(2, 9) = -0.025433043885735709;
        A(2, 10) = -0.0066377333894224455;
        A(2, 11) = 0.050298450636477608;
        A(2, 12) = 0.039760949109762675;
        A(2, 13) = -0.14756823873766672;
        A(2, 14) = 0.20916305964689;
        A(2, 15) = 0.010650584519944013;
        A(2, 16) = 0.073540667454342068;
        A(2, 17) = 0.071316377891706653;
        A(2, 18) = -0.1249102756562169;
        A(2, 19) = 0.070918892524605162;
        A(2, 20) = 0.07387463986392992;
        A(2, 21) = 0.13041034603692159;
        A(2, 22) = 0.031057158848942289;
        A(2, 23) = -0.098020699590328011;
        A(2, 24) = 0.076017861306082068;
        A(2, 25) = -0.02382798096499196;
        A(2, 26) = -0.015712700637387098;
        A(2, 27) = 0.028916946126507664;
        A(2, 28) = 0.062009079915010659;
        A(2, 29) = 0.11887727092589744;
        A(2, 30) = -0.044030214646262472;
        A(2, 31) = -0.09525839776505246;
        A(2, 32) = 0.12359069562544742;
        A(2, 33) = -0.10614788648169676;
        A(2, 34) = 0.086823044358624743;
        A(2, 35) = 0.073947598308914675;
        A(2, 36) = 0.16068894021381042;
        A(2, 37) = -0.052526681930623521;
        A(2, 38) = 0.12478598617219092;
        A(2, 39) = 0.031966253239477917;
        A(2, 40) = -0.053043713286338674;
        A(2, 41) = 0.0014063375539460771;
        A(2, 42) = -0.059751917538386198;
        A(2, 43) = -0.068150981592916993;
        A(2, 44) = 0.16663002292738147;
        A(2, 45) = 0.12313183742994638;
        A(2, 46) = -0.16202768774705448;
        A(2, 47) = 0.021515890797312545;
        A(2, 48) = -0.005044985427979088;
        A(2, 49) = 0.066077183342018522;
        A(2, 50) = 0.018615531139286615;
        A(2, 51) = 0.011624802810873802;
        A(2, 52) = 0.097863740562193852;
        A(2, 53) = 0.025499286891301477;
        A(2, 54) = -0.063312645387411451;
        A(2, 55) = 0.066960490934570155;
        A(2, 56) = -0.023823013321726656;
        A(2, 57) = 0.11873437519807073;
        A(2, 58) = 0.1511488371455891;
        A(2, 59) = -0.0098054270067033066;
        A(2, 60) = -0.040978422165866772;
        A(2, 61) = -0.20689865583795986;
        A(2, 62) = -0.017791485754274514;
        A(2, 63) = 0.038668640407042314;
        A(2, 64) = -0.14016440356497112;
        A(2, 65) = -0.037136418312465475;
        A(2, 66) = -0.049077501408487621;
        A(2, 67) = -0.1164256867149141;
        A(2, 68) = -0.1074844850976383;
        A(2, 69) = -0.042718773728780482;
        A(2, 70) = 0.10984820168020143;
        A(2, 71) = 0.0060737450575625122;
        A(2, 72) = -0.088119923512751774;
        A(2, 73) = 0.023193627535261149;
        A(2, 74) = -0.15672245674126856;
        A(2, 75) = -0.099244408665912859;
        A(2, 76) = -0.14752376937760914;
        A(2, 77) = -0.0078999583810226114;
        A(2, 78) = -0.080778819087026693;
        A(2, 79) = 0.13806976389759676;
        A(2, 80) = 0.0600365310298345;
        A(2, 81) = 0.05989850666816527;
        A(2, 82) = -0.11149860289594618;
        A(2, 83) = -0.012899582986690958;
        A(2, 84) = -0.18267236808512621;
        A(2, 85) = 0.047826960522133158;
        A(2, 86) = 0.032180696465925904;
        A(2, 87) = -0.033889474817849138;
        A(2, 88) = -0.047217227476587562;
        A(2, 89) = 0.12182793627370533;
        A(2, 90) = 0.011074489710212942;
        A(2, 91) = 0.037767453838525311;
        A(2, 92) = 0.028172468396594132;
        A(2, 93) = 0.15241552124971181;
        A(2, 94) = 0.070302243920003823;
        A(2, 95) = -0.029585965731136969;
        A(2, 96) = 0.058286327154268687;
        A(2, 97) = -0.068967753340746743;
        A(2, 98) = -0.21206644326420832;
        A(2, 99) = 0.019556044179065868;
        A(2, 100) = 0.013416674761079127;
        A(2, 101) = -0.076475708176920398;
        A(2, 102) = 0.056754357277123489;
        A(2, 103) = -0.0058660739222330463;
        A(2, 104) = 0.079923559115015558;
        A(2, 105) = 0.029493957829370837;
        A(2, 106) = -0.1437205933368636;
        A(2, 107) = -0.11105986263865228;
        A(2, 108) = 0.14615095050568178;
        A(2, 109) = 0.062296353995628287;
        A(2, 110) = -0.0063175014176354814;
        A(2, 111) = 0.048866812277092796;
        A(2, 112) = -0.067493670920080989;
        A(2, 113) = 0.15191319176946277;
        A(2, 114) = 0.019157917779194795;
        A(2, 115) = -0.10099739547926029;
        A(2, 116) = -0.059587675119095546;
        A(2, 117) = 0.027704838316782734;
        A(2, 118) = 0.0053985581135847019;
        A(2, 119) = -0.064901555225427954;
        A(2, 120) = -0.048784034805557826;
        A(2, 121) = 0.18912677295197011;
        A(2, 122) = -0.05294335436433506;
        A(2, 123) = 0.014090447897387677;
        A(2, 124) = -0.13439576825032945;
        A(2, 125) = -0.14408432743142552;
        A(2, 126) = -0.0063436517834685492;
        A(2, 127) = 0.0033279463180070634;
        A(3, 0) = -0.13453641138174172;
        A(3, 1) = 0.040812814914764003;
        A(3, 2) = 0.1778451150907136;
        A(3, 3) = 0.053798627890253956;
        A(3, 4) = 0.0030192769869450686;
        A(3, 5) = 0.023252119596532991;
        A(3, 6) = 0.17599429149077694;
        A(3, 7) = -0.016363773015335235;
        A(3, 8) = 0.049134931474365248;
        A(3, 9) = 0.085786496356177758;
        A(3, 10) = -0.023933012475704427;
        A(3, 11) = 0.039488291421507254;
        A(3, 12) = 0.1152693818407423;
        A(3, 13) = 0.015276479060493245;
        A(3, 14) = 0.013282131123936114;
        A(3, 15) = -0.0025328294033201727;
        A(3, 16) = -0.064448397344210817;
        A(3, 17) = -0.12357812789929659;
        A(3, 18) = -0.13162753342011943;
        A(3, 19) = -0.048304756101731058;
        A(3, 20) = 7.1101886664558245e-005;
        A(3, 21) = -0.15355317052098288;
        A(3, 22) = -0.0034282713045220292;
        A(3, 23) = 0.071285913587501623;
        A(3, 24) = -0.035823402494302096;
        A(3, 25) = 0.010391992643232316;
        A(3, 26) = 0.02463968875721469;
        A(3, 27) = -0.013145189088425734;
        A(3, 28) = -0.012844405688973506;
        A(3, 29) = 0.0065087504781746151;
        A(3, 30) = 0.093132365045023105;
        A(3, 31) = 0.0070512188813427606;
        A(3, 32) = -0.1856111909278913;
        A(3, 33) = -0.038124405104230728;
        A(3, 34) = -0.13848340530905157;
        A(3, 35) = 0.023662022142640498;
        A(3, 36) = 0.16725726949285888;
        A(3, 37) = 0.0049715444223442269;
        A(3, 38) = 0.025194680216724202;
        A(3, 39) = -0.095765583370636898;
        A(3, 40) = -0.042955597279516977;
        A(3, 41) = 0.02683948012406244;
        A(3, 42) = 0.06832355900101271;
        A(3, 43) = 0.12481702647413453;
        A(3, 44) = -0.055660239992176855;
        A(3, 45) = 0.024734655949642921;
        A(3, 46) = -0.056205596292263002;
        A(3, 47) = 0.036070761693582781;
        A(3, 48) = 0.093928181316112358;
        A(3, 49) = -0.018283190645658143;
        A(3, 50) = 0.11337390339845894;
        A(3, 51) = -0.0020827672871621405;
        A(3, 52) = 0.0019180592930070697;
        A(3, 53) = 0.022481715999660364;
        A(3, 54) = -0.11585904563032251;
        A(3, 55) = -0.0087492421338034657;
        A(3, 56) = -0.065423420732897808;
        A(3, 57) = 0.19915655440613553;
        A(3, 58) = -0.026653864607070407;
        A(3, 59) = 0.074447012962371051;
        A(3, 60) = -0.051899223419136511;
        A(3, 61) = -0.00074465172919453704;
        A(3, 62) = -0.12660205251918411;
        A(3, 63) = -0.0087661258777846779;
        A(3, 64) = 0.092418386128718499;
        A(3, 65) = -0.1597785293854303;
        A(3, 66) = -0.12895200060744974;
        A(3, 67) = 0.030094696847227737;
        A(3, 68) = 0.0093334013782725433;
        A(3, 69) = 0.095925436639051037;
        A(3, 70) = -0.015731016114469046;
        A(3, 71) = 0.14860208596871111;
        A(3, 72) = 0.1243813135512945;
        A(3, 73) = -0.026652242455831657;
        A(3, 74) = 0.097095833197190923;
        A(3, 75) = -0.031908547248874666;
        A(3, 76) = 0.25498994462329505;
        A(3, 77) = 0.057744588921142509;
        A(3, 78) = -0.069621140922042454;
        A(3, 79) = -0.050193391636762813;
        A(3, 80) = -0.11146937958634856;
        A(3, 81) = 0.062272193852926275;
        A(3, 82) = 0.0029027997341054199;
        A(3, 83) = -0.17060071389337861;
        A(3, 84) = 0.027027630910364031;
        A(3, 85) = 0.18419731094904657;
        A(3, 86) = 0.097009790820742584;
        A(3, 87) = 0.036960222128266995;
        A(3, 88) = 0.069176899974399617;
        A(3, 89) = 0.099221521738144441;
        A(3, 90) = -0.18246539340313966;
        A(3, 91) = 0.10020989838589879;
        A(3, 92) = 0.035190892831426908;
        A(3, 93) = 0.0041328293375252553;
        A(3, 94) = -0.038281091976417062;
        A(3, 95) = -0.11017941655680066;
        A(3, 96) = 0.029676532177947624;
        A(3, 97) = -0.23691066317515894;
        A(3, 98) = -0.0050785070165938265;
        A(3, 99) = -0.069601225249225365;
        A(3, 100) = -0.043719414928680395;
        A(3, 101) = -0.1572289953733525;
        A(3, 102) = 0.012999897970748256;
        A(3, 103) = 0.077306195778586814;
        A(3, 104) = 0.044102782673642121;
        A(3, 105) = -0.047867333364338058;
        A(3, 106) = -0.11082086929318655;
        A(3, 107) = 0.13096606811561162;
        A(3, 108) = 0.055286782429505799;
        A(3, 109) = 0.061855798800059252;
        A(3, 110) = 0.024837085726197264;
        A(3, 111) = 0.071060086130434116;
        A(3, 112) = -0.021428668984353916;
        A(3, 113) = -0.033591538842056193;
        A(3, 114) = -0.044553978275060538;
        A(3, 115) = 0.0012204862939508843;
        A(3, 116) = -0.15102819054368338;
        A(3, 117) = 0.12503548003418397;
        A(3, 118) = 0.0068231711377413698;
        A(3, 119) = 0.071493092760672644;
        A(3, 120) = 0.12217921585002339;
        A(3, 121) = -0.00027039256353212152;
        A(3, 122) = -0.074727803371105378;
        A(3, 123) = -0.06637189289753867;
        A(3, 124) = -0.007901285886672077;
        A(3, 125) = -0.075641659992151583;
        A(3, 126) = -0.068896835189431987;
        A(3, 127) = 0.085175816588313594;
        A(4, 0) = 0.053584682140583963;
        A(4, 1) = -0.023462506130338314;
        A(4, 2) = -0.11863065997890634;
        A(4, 3) = -0.016093082423071468;
        A(4, 4) = 0.14246117655978674;
        A(4, 5) = -0.036285463433755542;
        A(4, 6) = -0.057727061364998271;
        A(4, 7) = 0.0069041390808706332;
        A(4, 8) = -0.0063371364000491676;
        A(4, 9) = -0.12398684467736903;
        A(4, 10) = -0.13846099783462365;
        A(4, 11) = 0.070782937593632245;
        A(4, 12) = -0.14577264280932939;
        A(4, 13) = -0.02176463062307436;
        A(4, 14) = -0.1622205409190581;
        A(4, 15) = -0.047794463608972937;
        A(4, 16) = -0.010002069692461049;
        A(4, 17) = 0.15468284136334143;
        A(4, 18) = -0.014838058965616907;
        A(4, 19) = -0.20209892426050061;
        A(4, 20) = -0.02849907837249609;
        A(4, 21) = -0.19890282102947693;
        A(4, 22) = 0.25517412899810443;
        A(4, 23) = 0.112341761191332;
        A(4, 24) = -0.077631834308580908;
        A(4, 25) = -0.10410385004535287;
        A(4, 26) = -0.17066381162725994;
        A(4, 27) = 0.12801056987245574;
        A(4, 28) = -0.003151596298004343;
        A(4, 29) = 0.094039071237761465;
        A(4, 30) = 0.060115153249844726;
        A(4, 31) = -0.038049450517080516;
        A(4, 32) = 0.020587987872587477;
        A(4, 33) = -0.10371183340578946;
        A(4, 34) = 0.019483328939834538;
        A(4, 35) = -0.084400102420769799;
        A(4, 36) = 0.020326364334131389;
        A(4, 37) = -0.029284636800919077;
        A(4, 38) = 0.18644129842452647;
        A(4, 39) = 0.023066604207882615;
        A(4, 40) = -0.022878356318055286;
        A(4, 41) = -0.00022945362822547957;
        A(4, 42) = -0.18568722525558168;
        A(4, 43) = -0.028572760418738224;
        A(4, 44) = 0.13048442118249171;
        A(4, 45) = -0.01998317872654308;
        A(4, 46) = 0.15321838154530809;
        A(4, 47) = 0.036633165197032282;
        A(4, 48) = -0.035883035106023704;
        A(4, 49) = 0.031500796682354983;
        A(4, 50) = 0.017137895720524619;
        A(4, 51) = -0.026490289797384228;
        A(4, 52) = 0.043858587697917062;
        A(4, 53) = 0.063096634666919532;
        A(4, 54) = -0.028245711147983677;
        A(4, 55) = -0.031580192072670189;
        A(4, 56) = 0.037925020307689267;
        A(4, 57) = 0.021876900296999666;
        A(4, 58) = 0.14911131938815003;
        A(4, 59) = 0.06107995103019602;
        A(4, 60) = 0.089730172306341047;
        A(4, 61) = -0.025243201455419403;
        A(4, 62) = -0.10056806490218498;
        A(4, 63) = 0.00095643154676500891;
        A(4, 64) = -0.1396358097852769;
        A(4, 65) = -0.089396292940787686;
        A(4, 66) = -0.18185989188080154;
        A(4, 67) = -0.0017394140118867016;
        A(4, 68) = 0.098019125927134201;
        A(4, 69) = -0.076809370665512064;
        A(4, 70) = -0.06758236274138911;
        A(4, 71) = 0.030072736951727387;
        A(4, 72) = -0.018712217880835203;
        A(4, 73) = 0.08258603465936748;
        A(4, 74) = 0.073639188877641315;
        A(4, 75) = -0.069289682053993246;
        A(4, 76) = -0.1297270322645814;
        A(4, 77) = -0.10807336595460977;
        A(4, 78) = -0.059638844117493206;
        A(4, 79) = -0.041927837827060832;
        A(4, 80) = 0.0045162978722785452;
        A(4, 81) = 0.0078932024413271573;
        A(4, 82) = -0.038482989138075178;
        A(4, 83) = -0.086460792763966537;
        A(4, 84) = -0.027779906446631041;
        A(4, 85) = 0.0063977089035232096;
        A(4, 86) = 0.08119833653458286;
        A(4, 87) = 0.047215641673279345;
        A(4, 88) = -0.079489146182605247;
        A(4, 89) = 0.039509635623373007;
        A(4, 90) = -0.016358763365720633;
        A(4, 91) = 0.035448789852425514;
        A(4, 92) = -0.12251103002704147;
        A(4, 93) = -0.12985978050590671;
        A(4, 94) = 0.011092333899007687;
        A(4, 95) = 0.11449369508120331;
        A(4, 96) = -0.10049853351427043;
        A(4, 97) = 0.019430881756306168;
        A(4, 98) = 0.031148815221459153;
        A(4, 99) = 0.0038884684892963404;
        A(4, 100) = 0.16257640543818475;
        A(4, 101) = 0.029399860487665325;
        A(4, 102) = -0.16377555622319032;
        A(4, 103) = 0.099517515828760728;
        A(4, 104) = -0.020348465028286994;
        A(4, 105) = -0.1324666133326321;
        A(4, 106) = -0.069642484175030495;
        A(4, 107) = 0.050924954082476853;
        A(4, 108) = -0.035531614591239297;
        A(4, 109) = 0.069525053311940754;
        A(4, 110) = 0.047187547979428708;
        A(4, 111) = 0.066390575555750356;
        A(4, 112) = -0.041281866287356306;
        A(4, 113) = 0.017439408753713966;
        A(4, 114) = -0.026981579885950575;
        A(4, 115) = -0.035525093605464186;
        A(4, 116) = -0.027373038173673314;
        A(4, 117) = 0.11829849600556104;
        A(4, 118) = -0.10254790929200325;
        A(4, 119) = -0.024587610084361132;
        A(4, 120) = 0.022354530803989983;
        A(4, 121) = -0.14304309001429927;
        A(4, 122) = 0.043394917342350937;
        A(4, 123) = 0.10679347173226339;
        A(4, 124) = 0.12232494339523578;
        A(4, 125) = -0.051304088627804244;
        A(4, 126) = -0.10343209805743994;
        A(4, 127) = 0.07002465157690925;
        A(5, 0) = -0.077704994798389479;
        A(5, 1) = 0.038130890480048876;
        A(5, 2) = 0.14960911270342986;
        A(5, 3) = -0.08894413913779442;
        A(5, 4) = -0.16632943977676964;
        A(5, 5) = -0.051673108452923083;
        A(5, 6) = 0.11271608182557623;
        A(5, 7) = -0.15769109029172845;
        A(5, 8) = -0.037810829320511607;
        A(5, 9) = 0.042201759044728886;
        A(5, 10) = -0.1009612365761858;
        A(5, 11) = -0.13839246801894955;
        A(5, 12) = -0.15059624306155811;
        A(5, 13) = -0.033178762220049965;
        A(5, 14) = 0.005960154015880216;
        A(5, 15) = -0.011830322959525028;
        A(5, 16) = 0.097591589119731648;
        A(5, 17) = 0.081706564370648105;
        A(5, 18) = 0.085211832430527074;
        A(5, 19) = -0.061217525262125247;
        A(5, 20) = 0.17675263864647772;
        A(5, 21) = 0.093249669349045869;
        A(5, 22) = 0.082700890880735761;
        A(5, 23) = 0.028681846307874216;
        A(5, 24) = 0.04325967922523806;
        A(5, 25) = -0.093399603350820315;
        A(5, 26) = 0.022385002968775686;
        A(5, 27) = 0.087742723043225557;
        A(5, 28) = 0.088621741372443774;
        A(5, 29) = -0.073001163672415201;
        A(5, 30) = -0.022310302843646788;
        A(5, 31) = -0.034563293170753767;
        A(5, 32) = -0.12631373029816792;
        A(5, 33) = 0.094707831684625321;
        A(5, 34) = 0.039034922084128378;
        A(5, 35) = 0.083203303633693562;
        A(5, 36) = 0.034116744489025581;
        A(5, 37) = -0.021361120186296476;
        A(5, 38) = 0.12154976081905901;
        A(5, 39) = -0.041400448388980618;
        A(5, 40) = 0.017386419389472385;
        A(5, 41) = 0.036267430234239673;
        A(5, 42) = -0.05711072933464665;
        A(5, 43) = 0.098668054374864297;
        A(5, 44) = -0.031466716093256061;
        A(5, 45) = 0.0082172394527477571;
        A(5, 46) = 0.10570304225557986;
        A(5, 47) = 0.14373288564536416;
        A(5, 48) = -0.10334435288430788;
        A(5, 49) = -0.094352845261217122;
        A(5, 50) = 0.052905764062681909;
        A(5, 51) = -0.11689927090097221;
        A(5, 52) = -0.047196747107049047;
        A(5, 53) = -0.0067972639526063562;
        A(5, 54) = 0.084867976173404663;
        A(5, 55) = 0.0018816048290974385;
        A(5, 56) = 0.11113514484477721;
        A(5, 57) = -0.13113442676874293;
        A(5, 58) = 0.11330633305620003;
        A(5, 59) = 0.021268974330265186;
        A(5, 60) = -0.13704626897219496;
        A(5, 61) = -0.0073493906518634772;
        A(5, 62) = -0.034081262150319404;
        A(5, 63) = 0.032553350176454554;
        A(5, 64) = -0.05088328772780655;
        A(5, 65) = -0.047873556636338355;
        A(5, 66) = -0.063645334482781271;
        A(5, 67) = -0.22420192275378065;
        A(5, 68) = 0.010356080362395562;
        A(5, 69) = 0.054911965827287537;
        A(5, 70) = -0.094366196302786615;
        A(5, 71) = 0.067031160991963351;
        A(5, 72) = -0.10202867411174552;
        A(5, 73) = -0.12809422089079314;
        A(5, 74) = -0.07491522767599075;
        A(5, 75) = -0.020696447306035218;
        A(5, 76) = 0.17625489470783029;
        A(5, 77) = 0.070788282636169098;
        A(5, 78) = 0.052551742373179527;
        A(5, 79) = 0.0094329857781881229;
        A(5, 80) = -0.20514060330779532;
        A(5, 81) = -0.060190359048896178;
        A(5, 82) = 0.14706543365929847;
        A(5, 83) = 0.11485694449495454;
        A(5, 84) = -0.046841320879342993;
        A(5, 85) = -0.046633657183215896;
        A(5, 86) = 0.057382008852516486;
        A(5, 87) = -0.061820024599677906;
        A(5, 88) = 0.10485413893803315;
        A(5, 89) = -0.049083638147909371;
        A(5, 90) = 0.1091050815154978;
        A(5, 91) = -0.061518677545704996;
        A(5, 92) = -0.024047990818706011;
        A(5, 93) = 0.091044705866838146;
        A(5, 94) = -0.054714040791138591;
        A(5, 95) = 0.06768498186296612;
        A(5, 96) = 0.037591391286708575;
        A(5, 97) = -0.15026413413795647;
        A(5, 98) = -0.10657415332509088;
        A(5, 99) = -0.0081688011617103255;
        A(5, 100) = 0.012276350829391745;
        A(5, 101) = 0.099273904230326143;
        A(5, 102) = -0.00022344470205893502;
        A(5, 103) = 0.073691544932564551;
        A(5, 104) = -0.12516795475277198;
        A(5, 105) = -0.095337120086448887;
        A(5, 106) = -0.001349300852995089;
        A(5, 107) = 0.050243569495387025;
        A(5, 108) = -0.1412177032918781;
        A(5, 109) = -0.00039009898801626967;
        A(5, 110) = 0.14552570849280808;
        A(5, 111) = -0.056793732309384032;
        A(5, 112) = -0.1245801007320021;
        A(5, 113) = -0.073605312643876708;
        A(5, 114) = -0.032072936599958926;
        A(5, 115) = 0.0094647912779058513;
        A(5, 116) = 0.14889373227695879;
        A(5, 117) = 0.017207970083448973;
        A(5, 118) = -0.080499713146957988;
        A(5, 119) = 0.12611106285415577;
        A(5, 120) = -0.10291844846376669;
        A(5, 121) = -0.023690307510447404;
        A(5, 122) = 5.3717624334155556e-006;
        A(5, 123) = 0.0072690707773551237;
        A(5, 124) = -0.12737160546980494;
        A(5, 125) = 0.053307910671363951;
        A(5, 126) = 0.022448568163580415;
        A(5, 127) = -0.12529688793310703;
        A(6, 0) = 0.049877482153528108;
        A(6, 1) = -0.029775296270749971;
        A(6, 2) = 0.13641750269258007;
        A(6, 3) = 0.091129358002296046;
        A(6, 4) = 0.045738918228026677;
        A(6, 5) = 0.14106837286686272;
        A(6, 6) = 0.15147957527537442;
        A(6, 7) = -0.070664069757869305;
        A(6, 8) = -0.062230871621230595;
        A(6, 9) = 0.080329049730712226;
        A(6, 10) = -0.033834754245305076;
        A(6, 11) = -0.068944729412884778;
        A(6, 12) = 0.017376973792826628;
        A(6, 13) = 0.030661257139876798;
        A(6, 14) = -0.089289867341035084;
        A(6, 15) = -0.03334938461803845;
        A(6, 16) = 0.036384205456715404;
        A(6, 17) = -0.0083460966858256436;
        A(6, 18) = -0.00016331682616299234;
        A(6, 19) = 0.13847411862668021;
        A(6, 20) = -0.034742976203032606;
        A(6, 21) = 0.077738507394428974;
        A(6, 22) = 0.067524467644672154;
        A(6, 23) = 0.03119986232862625;
        A(6, 24) = 0.11875343765323551;
        A(6, 25) = -0.075023464696486963;
        A(6, 26) = 0.050088709521245431;
        A(6, 27) = -0.042485565440787021;
        A(6, 28) = 0.11153321942353489;
        A(6, 29) = -0.08146520850045269;
        A(6, 30) = -0.043419294013364786;
        A(6, 31) = 0.090828407760804586;
        A(6, 32) = -0.025415583473595106;
        A(6, 33) = 0.12080057729999374;
        A(6, 34) = -0.17066708702530581;
        A(6, 35) = 0.0078346500646838402;
        A(6, 36) = 0.017161428676003745;
        A(6, 37) = -0.069974475616849774;
        A(6, 38) = -0.049575314997780867;
        A(6, 39) = -0.022195286628632033;
        A(6, 40) = 0.18862252009550165;
        A(6, 41) = -0.047373771380108003;
        A(6, 42) = -0.066322849883748633;
        A(6, 43) = -0.16404214788652172;
        A(6, 44) = 0.013553280352361814;
        A(6, 45) = -0.088364646986674622;
        A(6, 46) = -0.00751308952541015;
        A(6, 47) = 0.11214210568874114;
        A(6, 48) = -0.16219307158204943;
        A(6, 49) = 0.11539175319376832;
        A(6, 50) = -0.068405358725606435;
        A(6, 51) = 0.026355097270904196;
        A(6, 52) = 0.02131079646072848;
        A(6, 53) = -0.057030572655144274;
        A(6, 54) = 0.00029329999081595393;
        A(6, 55) = -0.092697237665045604;
        A(6, 56) = -0.092998685266429931;
        A(6, 57) = 0.11252992493011525;
        A(6, 58) = -0.13883828611229557;
        A(6, 59) = -0.072123437576935234;
        A(6, 60) = 0.11861744682793479;
        A(6, 61) = 0.15770310632452911;
        A(6, 62) = -0.11671861463235826;
        A(6, 63) = 0.066956452543402739;
        A(6, 64) = -0.14832494276907315;
        A(6, 65) = 0.061703250014232693;
        A(6, 66) = 0.00081426934400313095;
        A(6, 67) = -0.057111959596467934;
        A(6, 68) = -0.011109494946167621;
        A(6, 69) = 0.032965692582928571;
        A(6, 70) = 0.028967704111107159;
        A(6, 71) = -0.01763655038686858;
        A(6, 72) = -0.024208995188294013;
        A(6, 73) = 0.050983926179185485;
        A(6, 74) = 0.040641999441733641;
        A(6, 75) = -0.10784156713852384;
        A(6, 76) = -0.096577049109784693;
        A(6, 77) = -0.058644251006187732;
        A(6, 78) = -0.077141782768139072;
        A(6, 79) = 0.055243312832016389;
        A(6, 80) = 0.089558802153600889;
        A(6, 81) = 0.10845021609357382;
        A(6, 82) = 0.10323277849636253;
        A(6, 83) = -0.066322150399460628;
        A(6, 84) = -0.09554319077678905;
        A(6, 85) = 0.015455813090537698;
        A(6, 86) = 0.099931430879773145;
        A(6, 87) = -0.16536106940838219;
        A(6, 88) = -0.12565599536006486;
        A(6, 89) = 0.076529824012582015;
        A(6, 90) = 0.088948797080458608;
        A(6, 91) = 0.080514646685928948;
        A(6, 92) = 0.091549883148196842;
        A(6, 93) = 0.065519631424079294;
        A(6, 94) = 0.10702859750071356;
        A(6, 95) = -0.0056888014783649798;
        A(6, 96) = 0.079350124811719297;
        A(6, 97) = -0.033885554134399448;
        A(6, 98) = -0.075877736110265048;
        A(6, 99) = 0.161824544642024;
        A(6, 100) = 0.12789621621151032;
        A(6, 101) = -0.10906787555104852;
        A(6, 102) = -0.026085032896195917;
        A(6, 103) = -0.025595406175846033;
        A(6, 104) = -0.016522254118756116;
        A(6, 105) = -0.08187676527940993;
        A(6, 106) = -0.011057622546293316;
        A(6, 107) = -0.023642747051204761;
        A(6, 108) = 0.077615946049138407;
        A(6, 109) = 0.068257798550404244;
        A(6, 110) = 0.020311258280994494;
        A(6, 111) = -0.058565516744961917;
        A(6, 112) = 0.16135657728314123;
        A(6, 113) = -0.12410129733890152;
        A(6, 114) = -0.17583271541225698;
        A(6, 115) = 0.025717972105843534;
        A(6, 116) = 0.19762420388095756;
        A(6, 117) = -0.05462373577590645;
        A(6, 118) = 0.070221248190656033;
        A(6, 119) = 0.08146696989479775;
        A(6, 120) = 0.096189136981316439;
        A(6, 121) = -0.20416379484135755;
        A(6, 122) = 0.0025136509782398954;
        A(6, 123) = 0.0067823420845566189;
        A(6, 124) = 0.016419502987072281;
        A(6, 125) = -0.0033011992178245131;
        A(6, 126) = 0.063519368282758865;
        A(6, 127) = 0.14026174609880357;
        A(7, 0) = 0.082473389260081326;
        A(7, 1) = 0.072904627472902744;
        A(7, 2) = -0.15929193654919815;
        A(7, 3) = -0.084850175298757949;
        A(7, 4) = 0.014884672908100034;
        A(7, 5) = 0.0095239941649696586;
        A(7, 6) = -0.021998489498927;
        A(7, 7) = -0.0072418251318885629;
        A(7, 8) = 0.096638978462094627;
        A(7, 9) = -0.10055393042024952;
        A(7, 10) = 0.088339228286057669;
        A(7, 11) = -0.026966299729113734;
        A(7, 12) = 0.045809789638544748;
        A(7, 13) = -0.12254806810604478;
        A(7, 14) = -0.071741465220205275;
        A(7, 15) = 0.0098870901589073502;
        A(7, 16) = -0.028088365246462622;
        A(7, 17) = -0.038262618839887311;
        A(7, 18) = 0.060970798754360518;
        A(7, 19) = 0.059019305123138105;
        A(7, 20) = -0.012033749500492588;
        A(7, 21) = 0.10169286438042324;
        A(7, 22) = -0.038963841887768191;
        A(7, 23) = -0.1160771919022479;
        A(7, 24) = -0.08810952552501819;
        A(7, 25) = 0.028877532209742436;
        A(7, 26) = 0.16486657606511812;
        A(7, 27) = -0.071520282044212749;
        A(7, 28) = -0.086242682148593236;
        A(7, 29) = 0.10005253891534807;
        A(7, 30) = 0.035397278196483549;
        A(7, 31) = -0.072414345075981976;
        A(7, 32) = 0.080994198735460821;
        A(7, 33) = 0.015485561329552229;
        A(7, 34) = 0.010563133815146772;
        A(7, 35) = 0.037009036259685518;
        A(7, 36) = 0.076466291249251014;
        A(7, 37) = -0.066002744529198729;
        A(7, 38) = 0.047801508689772829;
        A(7, 39) = 0.017718354213090728;
        A(7, 40) = -0.097500428905426956;
        A(7, 41) = -0.022309598009284507;
        A(7, 42) = -0.046026971111658488;
        A(7, 43) = -0.17927120821902381;
        A(7, 44) = 0.0019665165709921231;
        A(7, 45) = -0.086081982151310396;
        A(7, 46) = -0.11799695076647726;
        A(7, 47) = -0.12387444577792506;
        A(7, 48) = -0.083989216498074823;
        A(7, 49) = 0.031001681793820443;
        A(7, 50) = 0.11527730357417219;
        A(7, 51) = -0.056930191835849908;
        A(7, 52) = 0.0529466239699381;
        A(7, 53) = 0.052487788013678718;
        A(7, 54) = -0.0062248807645584603;
        A(7, 55) = 0.027473789272352105;
        A(7, 56) = 0.0092408062618621473;
        A(7, 57) = -0.047593430342048756;
        A(7, 58) = 0.086855558968251562;
        A(7, 59) = -0.22623565318286265;
        A(7, 60) = -0.036488276263042185;
        A(7, 61) = 0.10328385352457925;
        A(7, 62) = -0.10345861883723374;
        A(7, 63) = 0.078772460379209278;
        A(7, 64) = -0.0063860433989043255;
        A(7, 65) = -0.23053411367428997;
        A(7, 66) = -0.062784145827511309;
        A(7, 67) = 0.015469946505995978;
        A(7, 68) = 0.12741276118113221;
        A(7, 69) = 0.086959186339709144;
        A(7, 70) = -0.082099271094921586;
        A(7, 71) = 0.22607537380228404;
        A(7, 72) = 0.024699864706205554;
        A(7, 73) = -0.089693877570999059;
        A(7, 74) = 0.036126844183177569;
        A(7, 75) = 0.016407984856029852;
        A(7, 76) = -0.14644761091982933;
        A(7, 77) = 0.14866516193975962;
        A(7, 78) = 0.079939321966084637;
        A(7, 79) = -0.036094608107685923;
        A(7, 80) = 0.0083139868330294742;
        A(7, 81) = 0.1269549821548398;
        A(7, 82) = 0.035948463229320979;
        A(7, 83) = -0.024520600134201147;
        A(7, 84) = 0.035208615827398322;
        A(7, 85) = 0.035696535974232418;
        A(7, 86) = -0.14951240767713625;
        A(7, 87) = 0.18436745705554802;
        A(7, 88) = 0.17625730209285745;
        A(7, 89) = 0.020731615737532412;
        A(7, 90) = -0.081017052582200252;
        A(7, 91) = 0.037172666976007573;
        A(7, 92) = 0.0073334618239161153;
        A(7, 93) = 0.10014235846427023;
        A(7, 94) = 0.17132542274930984;
        A(7, 95) = 0.062546180619929989;
        A(7, 96) = 0.055245572547983776;
        A(7, 97) = 0.026080798382137203;
        A(7, 98) = 0.041841340882239994;
        A(7, 99) = -0.026512876653698995;
        A(7, 100) = 0.10492155674937287;
        A(7, 101) = 0.02600208188540282;
        A(7, 102) = 0.063382558884224699;
        A(7, 103) = -0.038334725118085292;
        A(7, 104) = 0.0072609297584669309;
        A(7, 105) = -0.0049774550473910273;
        A(7, 106) = 0.08027201372346765;
        A(7, 107) = 0.1718901988679033;
        A(7, 108) = -0.01973357476040092;
        A(7, 109) = 0.14292937421976615;
        A(7, 110) = -0.029964521617578385;
        A(7, 111) = -0.017584735116119177;
        A(7, 112) = -0.078371185489124237;
        A(7, 113) = -0.062750745053571338;
        A(7, 114) = -0.012307884631888522;
        A(7, 115) = 0.1406767240454784;
        A(7, 116) = 0.1439193109922266;
        A(7, 117) = -0.010272563141044955;
        A(7, 118) = 0.13420559927101983;
        A(7, 119) = 0.09433659403286565;
        A(7, 120) = -0.025617204389278888;
        A(7, 121) = -0.16908235825657131;
        A(7, 122) = -0.13581814092451244;
        A(7, 123) = -0.03215513457480651;
        A(7, 124) = -0.015211023138934871;
        A(7, 125) = -0.0011258600226464223;
        A(7, 126) = -0.076157189220594571;
        A(7, 127) = -0.085256169341634658;
        A(8, 0) = 0.0071155871409413381;
        A(8, 1) = 0.082416195611074397;
        A(8, 2) = 0.0024041200717113131;
        A(8, 3) = 0.063360278236193154;
        A(8, 4) = 0.071335971258181835;
        A(8, 5) = 0.12042768967852704;
        A(8, 6) = 0.0019045679406837178;
        A(8, 7) = -0.055361036377134548;
        A(8, 8) = 0.065589262440253981;
        A(8, 9) = 0.036917830598886731;
        A(8, 10) = -0.13829715968705342;
        A(8, 11) = -0.20456493652567859;
        A(8, 12) = 0.0037608731633814122;
        A(8, 13) = 0.01597683323226709;
        A(8, 14) = 0.052598829300837487;
        A(8, 15) = 0.15558378229716507;
        A(8, 16) = 0.041547734761533138;
        A(8, 17) = 0.079089577770517297;
        A(8, 18) = -0.19549053782080461;
        A(8, 19) = -0.27513590108497826;
        A(8, 20) = -0.1200499005134861;
        A(8, 21) = -0.02070207442143588;
        A(8, 22) = 0.092588775353424996;
        A(8, 23) = 0.0055200100300186157;
        A(8, 24) = -0.012818988225172658;
        A(8, 25) = 0.053029918473802694;
        A(8, 26) = -0.010126611777715849;
        A(8, 27) = -0.075253078413542202;
        A(8, 28) = 0.06676734338361226;
        A(8, 29) = 0.056611819564128293;
        A(8, 30) = 0.004016089158659697;
        A(8, 31) = -0.10728886729147731;
        A(8, 32) = -0.1038514020930648;
        A(8, 33) = -0.069461153995679342;
        A(8, 34) = -0.00028734634346939958;
        A(8, 35) = 0.11247170875906903;
        A(8, 36) = -0.13977742154264458;
        A(8, 37) = 0.010725288616496357;
        A(8, 38) = -0.25715868533200303;
        A(8, 39) = -0.041238310806434253;
        A(8, 40) = -0.0065132232463471912;
        A(8, 41) = -0.023600730268876866;
        A(8, 42) = 0.012833200396792494;
        A(8, 43) = 0.046078327345941833;
        A(8, 44) = 0.0215063567671093;
        A(8, 45) = -0.016806017837735235;
        A(8, 46) = -0.060096879083620061;
        A(8, 47) = -0.12122614122280621;
        A(8, 48) = -0.081499585256110119;
        A(8, 49) = 0.023962961422336365;
        A(8, 50) = -0.079976108886098907;
        A(8, 51) = -0.057087650957332856;
        A(8, 52) = -0.070588358876967336;
        A(8, 53) = 0.029984190899050842;
        A(8, 54) = -0.0012265413193894847;
        A(8, 55) = 0.067059600975752129;
        A(8, 56) = 0.025873154478571629;
        A(8, 57) = 0.053428907415874319;
        A(8, 58) = 0.054859171249420011;
        A(8, 59) = -0.090793370974846216;
        A(8, 60) = -0.00044001221790037487;
        A(8, 61) = 0.014516833362145209;
        A(8, 62) = -0.081430095489125817;
        A(8, 63) = -0.065419089062671951;
        A(8, 64) = 0.027430956663449604;
        A(8, 65) = -0.095401381080042813;
        A(8, 66) = 0.046846593461389932;
        A(8, 67) = 0.13049162501167186;
        A(8, 68) = 0.11245406071294374;
        A(8, 69) = 0.21973889262189186;
        A(8, 70) = 0.044936916700643842;
        A(8, 71) = 0.090096582823802063;
        A(8, 72) = -0.033069849355156306;
        A(8, 73) = -0.052894610095594853;
        A(8, 74) = 0.0067450055745455068;
        A(8, 75) = -0.015188988880361604;
        A(8, 76) = -0.014601574446928459;
        A(8, 77) = -0.17991813546422752;
        A(8, 78) = -0.029196288220437655;
        A(8, 79) = 0.14723819628991686;
        A(8, 80) = -0.0036622432425119228;
        A(8, 81) = 0.020918363696157606;
        A(8, 82) = 0.064606052187097807;
        A(8, 83) = 0.10927254280214922;
        A(8, 84) = -0.19466133443381745;
        A(8, 85) = 0.022508436951932914;
        A(8, 86) = 0.1215475253553886;
        A(8, 87) = -0.016418272181333883;
        A(8, 88) = -0.096725714784319738;
        A(8, 89) = 0.023565259271850297;
        A(8, 90) = 0.021941470305930941;
        A(8, 91) = 0.035336423443182226;
        A(8, 92) = -0.024923801129199889;
        A(8, 93) = -0.051979258052057546;
        A(8, 94) = 0.12611084670921491;
        A(8, 95) = -0.014435860682368115;
        A(8, 96) = 0.0027903482319182656;
        A(8, 97) = 0.1266731070655116;
        A(8, 98) = 0.13058810287959574;
        A(8, 99) = -0.032660747673690663;
        A(8, 100) = 0.019922825265529263;
        A(8, 101) = 0.077949497703938095;
        A(8, 102) = 0.034011277545941146;
        A(8, 103) = -0.007658334370745791;
        A(8, 104) = 0.14511825952120264;
        A(8, 105) = 0.013194257617087212;
        A(8, 106) = 0.073933184950955674;
        A(8, 107) = -0.0096523956947769524;
        A(8, 108) = -0.038664885953430095;
        A(8, 109) = -0.0079331879718882309;
        A(8, 110) = 0.20242496713158462;
        A(8, 111) = 0.049284322604758873;
        A(8, 112) = -0.11550536634299327;
        A(8, 113) = -0.021333488466377677;
        A(8, 114) = 0.0074575024457900346;
        A(8, 115) = -0.097610377719723099;
        A(8, 116) = -0.0030988211656184095;
        A(8, 117) = -0.037764759566063746;
        A(8, 118) = 0.11312169697568913;
        A(8, 119) = 0.041034319216885856;
        A(8, 120) = -0.061109219905696288;
        A(8, 121) = 0.15663324462848019;
        A(8, 122) = 0.089667832503426026;
        A(8, 123) = -0.12539549613097675;
        A(8, 124) = -0.092943584413973823;
        A(8, 125) = 0.18444386986732081;
        A(8, 126) = -0.0018471642831396212;
        A(8, 127) = 0.019205767562591774;
        A(9, 0) = 0.084031829406486167;
        A(9, 1) = 0.1537106435503772;
        A(9, 2) = 0.15679666432723005;
        A(9, 3) = -0.047914136883579872;
        A(9, 4) = -0.060274993100422912;
        A(9, 5) = 0.04641790568338261;
        A(9, 6) = 0.058269103607330092;
        A(9, 7) = 0.041217259783250984;
        A(9, 8) = -0.12474664604855261;
        A(9, 9) = 0.019864708005543505;
        A(9, 10) = -0.061551710398636543;
        A(9, 11) = 0.03706097935468422;
        A(9, 12) = -0.11313334605549483;
        A(9, 13) = 0.088710885214662805;
        A(9, 14) = 0.029724167279703517;
        A(9, 15) = 0.11183932086160527;
        A(9, 16) = -0.026626198605649638;
        A(9, 17) = 0.1929629482861337;
        A(9, 18) = -0.067990588753828574;
        A(9, 19) = 0.092993920463862054;
        A(9, 20) = -0.18616537436069502;
        A(9, 21) = 0.080600590758932805;
        A(9, 22) = -0.093425896024773802;
        A(9, 23) = -0.038776414433424562;
        A(9, 24) = -0.022559981055839645;
        A(9, 25) = -0.083467879895866015;
        A(9, 26) = 0.012895161195022414;
        A(9, 27) = -0.074315418854474;
        A(9, 28) = -0.0801476805156313;
        A(9, 29) = -0.036482574594179522;
        A(9, 30) = 0.0017987837050737303;
        A(9, 31) = 0.02280653016414631;
        A(9, 32) = 0.094072253483260648;
        A(9, 33) = 0.07104789728783481;
        A(9, 34) = -0.011905445712623966;
        A(9, 35) = 0.058074444373675642;
        A(9, 36) = 0.13282653730661781;
        A(9, 37) = 0.094165258846902772;
        A(9, 38) = 0.086455066375282483;
        A(9, 39) = -0.11418682030402817;
        A(9, 40) = -0.037185220255161265;
        A(9, 41) = 0.0068673404865865484;
        A(9, 42) = -0.077722954954606849;
        A(9, 43) = 0.035203988798162417;
        A(9, 44) = -0.037463571426766713;
        A(9, 45) = 0.079318423103464458;
        A(9, 46) = -0.031089436809599882;
        A(9, 47) = 0.083811034300246931;
        A(9, 48) = 0.017728853550615632;
        A(9, 49) = 0.20547530793711055;
        A(9, 50) = 0.25681388181500886;
        A(9, 51) = 0.058090995408585838;
        A(9, 52) = 0.11987960624483056;
        A(9, 53) = 0.017979753831728472;
        A(9, 54) = -0.027331351867460524;
        A(9, 55) = 0.02232999667670485;
        A(9, 56) = 0.25441822060495656;
        A(9, 57) = 0.001224190959082435;
        A(9, 58) = -0.019103707277760191;
        A(9, 59) = 0.14111564155333936;
        A(9, 60) = 0.17043513046443354;
        A(9, 61) = 0.14656222185228657;
        A(9, 62) = -0.030615031648308713;
        A(9, 63) = -0.026440323933753965;
        A(9, 64) = -0.12884570351452157;
        A(9, 65) = 0.048378803257801174;
        A(9, 66) = 0.16576487117660743;
        A(9, 67) = 0.10979984162444852;
        A(9, 68) = -0.05217516710917669;
        A(9, 69) = 0.064288832162924137;
        A(9, 70) = 0.01345997555158842;
        A(9, 71) = 0.084763206021384846;
        A(9, 72) = 0.13090347168553026;
        A(9, 73) = 0.074220958603255519;
        A(9, 74) = -0.0051989924313640828;
        A(9, 75) = 0.1496222085160675;
        A(9, 76) = 0.018491259318934312;
        A(9, 77) = -0.065862531424092388;
        A(9, 78) = 0.043370759417440216;
        A(9, 79) = -0.10889468312614185;
        A(9, 80) = -0.12104815715960249;
        A(9, 81) = 0.12611468561898245;
        A(9, 82) = -0.050939777501140822;
        A(9, 83) = 0.075399179527830706;
        A(9, 84) = 0.048485450999700405;
        A(9, 85) = 0.0023325700748813502;
        A(9, 86) = -0.10414933573870744;
        A(9, 87) = 0.014991372234372035;
        A(9, 88) = -0.094102968030805631;
        A(9, 89) = -0.051497090448154863;
        A(9, 90) = 0.094972820698011939;
        A(9, 91) = 0.019167934467281888;
        A(9, 92) = -0.085899772263327068;
        A(9, 93) = -0.024016771797757634;
        A(9, 94) = -0.084511504675607876;
        A(9, 95) = -0.017929685642923441;
        A(9, 96) = 0.066193178470945302;
        A(9, 97) = 0.091974448354238458;
        A(9, 98) = 0.031859465255362054;
        A(9, 99) = 0.057549927662537512;
        A(9, 100) = 0.088052912583336182;
        A(9, 101) = 0.047325605226953449;
        A(9, 102) = -0.12397303650428679;
        A(9, 103) = -0.041020693511706903;
        A(9, 104) = 0.05674031050441939;
        A(9, 105) = -0.11636174080134061;
        A(9, 106) = 0.060369986413723105;
        A(9, 107) = 0.065828332630055122;
        A(9, 108) = 0.030476867387597001;
        A(9, 109) = -0.098827110141753383;
        A(9, 110) = 0.065629086200489323;
        A(9, 111) = 0.074375394656045368;
        A(9, 112) = -0.10781986447858462;
        A(9, 113) = 0.050667118127741495;
        A(9, 114) = 0.0036713162435675767;
        A(9, 115) = 0.11438685231327392;
        A(9, 116) = 0.017551480049581618;
        A(9, 117) = 0.034165520927395242;
        A(9, 118) = -0.005541979796601362;
        A(9, 119) = -0.0050034223854434103;
        A(9, 120) = 0.0044837362664292904;
        A(9, 121) = 0.17191108857029702;
        A(9, 122) = -0.13085827666266164;
        A(9, 123) = -0.021706126598340952;
        A(9, 124) = -0.036003861659805486;
        A(9, 125) = -0.074261184658995533;
        A(9, 126) = -0.0062983640831469206;
        A(9, 127) = 0.037964633616805417;
        A(10, 0) = 0.072035034047933252;
        A(10, 1) = 0.090009623090892166;
        A(10, 2) = 0.05741713204158351;
        A(10, 3) = 0.15542748702409892;
        A(10, 4) = 0.10580459304298317;
        A(10, 5) = 0.25190537669502217;
        A(10, 6) = -0.043103672327707329;
        A(10, 7) = 0.12988396081374151;
        A(10, 8) = 0.0090609208427261667;
        A(10, 9) = 0.084414485237649939;
        A(10, 10) = 0.062716436561283492;
        A(10, 11) = -0.0086939961702559784;
        A(10, 12) = -0.042622378050427921;
        A(10, 13) = -0.1041891582563526;
        A(10, 14) = 0.016634772525667189;
        A(10, 15) = -0.053126371633938824;
        A(10, 16) = 0.074673205148650598;
        A(10, 17) = -0.016625403949123915;
        A(10, 18) = 0.08947378924600842;
        A(10, 19) = 0.15337371794446453;
        A(10, 20) = -0.0087301097522287513;
        A(10, 21) = 0.017579081991106409;
        A(10, 22) = 0.058916695589520021;
        A(10, 23) = -0.039397429445671546;
        A(10, 24) = 0.13596809722248704;
        A(10, 25) = 0.065037521980053692;
        A(10, 26) = -0.002078184149869107;
        A(10, 27) = 0.037194398310623662;
        A(10, 28) = 0.14073050792753505;
        A(10, 29) = 0.016125191363179633;
        A(10, 30) = 0.12808997423065074;
        A(10, 31) = -0.2787132027349713;
        A(10, 32) = 0.0094837697835927458;
        A(10, 33) = -0.24849143733795148;
        A(10, 34) = 0.0029534359289384582;
        A(10, 35) = -0.029112391549174436;
        A(10, 36) = 0.11532823376429885;
        A(10, 37) = 0.14848192139126726;
        A(10, 38) = -0.089747893682916857;
        A(10, 39) = 0.07721515443764243;
        A(10, 40) = 0.0497983983497449;
        A(10, 41) = 0.022047648917316691;
        A(10, 42) = 0.034321023247780282;
        A(10, 43) = 0.047857165773929233;
        A(10, 44) = 0.085915714294883663;
        A(10, 45) = -0.061570676062451098;
        A(10, 46) = 0.01668639412685935;
        A(10, 47) = 0.099404800305562369;
        A(10, 48) = -0.020151378236475698;
        A(10, 49) = -0.026323126517792766;
        A(10, 50) = 0.00053573474160353851;
        A(10, 51) = 0.13060363976144876;
        A(10, 52) = -0.086698968740468216;
        A(10, 53) = -0.002216878236340921;
        A(10, 54) = -0.0075408666002452045;
        A(10, 55) = -0.034204331579933522;
        A(10, 56) = -0.14079544470285965;
        A(10, 57) = -0.12157619394867661;
        A(10, 58) = -0.12188109070164727;
        A(10, 59) = 0.066724865508058812;
        A(10, 60) = -0.015357166558269714;
        A(10, 61) = -0.18235709201779454;
        A(10, 62) = -0.11625992436121553;
        A(10, 63) = 0.033566763009384173;
        A(10, 64) = -0.23184230773213158;
        A(10, 65) = 0.05466811086329728;
        A(10, 66) = -0.059176742672680652;
        A(10, 67) = 0.091492330134978941;
        A(10, 68) = -0.019864678574276512;
        A(10, 69) = 0.032968492401449639;
        A(10, 70) = 0.053379820336214467;
        A(10, 71) = 0.12526927654506001;
        A(10, 72) = -0.08797382059844619;
        A(10, 73) = -0.041160670419099696;
        A(10, 74) = 0.10906399660499094;
        A(10, 75) = 0.076660329148196676;
        A(10, 76) = -0.032399526680802981;
        A(10, 77) = 0.10511660572245732;
        A(10, 78) = 0.039883880490856234;
        A(10, 79) = -0.14629825111562994;
        A(10, 80) = -0.021569801652262841;
        A(10, 81) = -0.043868100903892059;
        A(10, 82) = -0.038423145290996094;
        A(10, 83) = 0.120940710317141;
        A(10, 84) = 0.017031962695676264;
        A(10, 85) = -0.015900123882597733;
        A(10, 86) = 0.033559456110723515;
        A(10, 87) = 0.098607562865165782;
        A(10, 88) = -0.055154150357427524;
        A(10, 89) = 0.0082385891426005747;
        A(10, 90) = -0.074357481439354334;
        A(10, 91) = -0.030223421239480869;
        A(10, 92) = 0.017575510081949772;
        A(10, 93) = 0.027942705751009565;
        A(10, 94) = -0.18903254309757925;
        A(10, 95) = -0.089121609022679904;
        A(10, 96) = -0.023424366919986152;
        A(10, 97) = 0.0013732166019260472;
        A(10, 98) = 0.084824657055970587;
        A(10, 99) = -0.061728451791628058;
        A(10, 100) = 0.13953976429194093;
        A(10, 101) = -0.015256232837045504;
        A(10, 102) = 0.02285949030276219;
        A(10, 103) = 0.0057955284231602372;
        A(10, 104) = 0.031293736838992829;
        A(10, 105) = 0.055277236718374929;
        A(10, 106) = -0.047431715679836707;
        A(10, 107) = 0.016372608483839188;
        A(10, 108) = -0.084005728722822928;
        A(10, 109) = -0.15361561931378309;
        A(10, 110) = 0.030885540240371167;
        A(10, 111) = -0.1258673930591287;
        A(10, 112) = -0.12113698042712485;
        A(10, 113) = 0.040660730952258549;
        A(10, 114) = -0.025745427045877362;
        A(10, 115) = 0.049594441634238158;
        A(10, 116) = -0.03046743282882744;
        A(10, 117) = -0.10598524470854342;
        A(10, 118) = -0.069118672212358886;
        A(10, 119) = 0.11790345157872116;
        A(10, 120) = -0.068389550699914009;
        A(10, 121) = -0.10128608068420822;
        A(10, 122) = -0.0045498948251106374;
        A(10, 123) = -0.0039362870522448561;
        A(10, 124) = -0.046274835505630878;
        A(10, 125) = -0.016154370463601089;
        A(10, 126) = 0.016836494002061265;
        A(10, 127) = -0.012655884348387336;
        A(11, 0) = -0.045246453112492917;
        A(11, 1) = 0.019049602429928751;
        A(11, 2) = 0.028527889017773575;
        A(11, 3) = 0.15957946778793958;
        A(11, 4) = -0.076183362125329737;
        A(11, 5) = -0.02537318976334468;
        A(11, 6) = 0.081263287846159618;
        A(11, 7) = 0.0096372396520084669;
        A(11, 8) = 0.025388649997245195;
        A(11, 9) = 0.1442878676648254;
        A(11, 10) = 0.041684927010694393;
        A(11, 11) = 0.072504698331091105;
        A(11, 12) = -0.030624828023770506;
        A(11, 13) = -0.21717077937787951;
        A(11, 14) = -0.016067110013279484;
        A(11, 15) = -0.1119992487196157;
        A(11, 16) = -0.11839092446457783;
        A(11, 17) = 0.11473697219448081;
        A(11, 18) = 0.087942405197508872;
        A(11, 19) = 0.014348215482971102;
        A(11, 20) = 0.089782165143074133;
        A(11, 21) = -0.068686045109591864;
        A(11, 22) = -0.011346088019116483;
        A(11, 23) = 0.078198408063313601;
        A(11, 24) = -0.074714724670324181;
        A(11, 25) = -0.15057072429633694;
        A(11, 26) = -0.025474999851392122;
        A(11, 27) = -0.19629947851183274;
        A(11, 28) = 0.028927238545228523;
        A(11, 29) = -0.097603544168090431;
        A(11, 30) = 0.036962108027383117;
        A(11, 31) = -0.02072455402896255;
        A(11, 32) = 0.019857489850354824;
        A(11, 33) = 0.063556840144974244;
        A(11, 34) = 0.016526322485135723;
        A(11, 35) = 0.10008115508117486;
        A(11, 36) = 0.046236597537840769;
        A(11, 37) = 0.036577622562675265;
        A(11, 38) = -0.081666298749641833;
        A(11, 39) = -0.022105587405146704;
        A(11, 40) = -0.010523123979046839;
        A(11, 41) = -0.086353159356776385;
        A(11, 42) = 0.0062203500938175227;
        A(11, 43) = 0.016567772144023628;
        A(11, 44) = -0.16001814325620689;
        A(11, 45) = 0.090825541927341727;
        A(11, 46) = 0.029456558957604601;
        A(11, 47) = -0.060289844982400337;
        A(11, 48) = -0.0066165884661466209;
        A(11, 49) = 0.066436910885080858;
        A(11, 50) = -0.076201765492148993;
        A(11, 51) = -0.064137333304348162;
        A(11, 52) = 0.067505929961163905;
        A(11, 53) = 0.0086075067220852987;
        A(11, 54) = 0.11690821338385901;
        A(11, 55) = 0.048502381207139129;
        A(11, 56) = -0.21140808666308733;
        A(11, 57) = -0.065397624959739428;
        A(11, 58) = 0.11110808790284049;
        A(11, 59) = 0.12232893099150743;
        A(11, 60) = -0.13117127578721649;
        A(11, 61) = 0.10278869187115511;
        A(11, 62) = -0.11771931758137338;
        A(11, 63) = 0.011322304600550073;
        A(11, 64) = -0.07390962109233945;
        A(11, 65) = 0.053347120125381828;
        A(11, 66) = 0.04319924238757291;
        A(11, 67) = -0.056281230087667194;
        A(11, 68) = 0.10313872027786017;
        A(11, 69) = 0.23891893639204043;
        A(11, 70) = 0.07123447616269675;
        A(11, 71) = 0.033475416621611465;
        A(11, 72) = -0.04329519639438556;
        A(11, 73) = 0.054747872792862161;
        A(11, 74) = 0.085059038053224761;
        A(11, 75) = -0.035167741408697953;
        A(11, 76) = 0.0072367976077893637;
        A(11, 77) = -0.093504527650525637;
        A(11, 78) = -0.012723738885880145;
        A(11, 79) = 0.07160952051272293;
        A(11, 80) = 0.24341640522462188;
        A(11, 81) = -0.14403646532618666;
        A(11, 82) = 0.04343467252855477;
        A(11, 83) = 0.06320270087798098;
        A(11, 84) = 0.075071850934015166;
        A(11, 85) = 0.0078135809180556112;
        A(11, 86) = 0.021306552054462961;
        A(11, 87) = -0.0073194658003781984;
        A(11, 88) = 0.039726095795650319;
        A(11, 89) = -0.031063849555601444;
        A(11, 90) = 0.12379181616482904;
        A(11, 91) = -0.08086186087784758;
        A(11, 92) = -0.18766927229958849;
        A(11, 93) = -0.03356737133787463;
        A(11, 94) = 0.046774909959874642;
        A(11, 95) = 0.059269806308966555;
        A(11, 96) = 0.033156730210092092;
        A(11, 97) = -0.0085796217581234867;
        A(11, 98) = -0.072810169536937377;
        A(11, 99) = -0.1954925313427866;
        A(11, 100) = 0.017701995216656243;
        A(11, 101) = -0.078198988888417933;
        A(11, 102) = -0.061940752381243053;
        A(11, 103) = -0.0011840193707725183;
        A(11, 104) = 0.066215010106502756;
        A(11, 105) = 0.046167646013711323;
        A(11, 106) = 0.058049311135694205;
        A(11, 107) = -0.064278147054983678;
        A(11, 108) = -0.055729850104552808;
        A(11, 109) = -0.058967823093583345;
        A(11, 110) = -0.094127536794304967;
        A(11, 111) = -0.0023950990679082306;
        A(11, 112) = -0.028902703971888398;
        A(11, 113) = 0.116918523153862;
        A(11, 114) = 0.041011304942544742;
        A(11, 115) = 0.063770807665426643;
        A(11, 116) = -0.01853827755745683;
        A(11, 117) = 0.12467591318117498;
        A(11, 118) = 0.10005095615979634;
        A(11, 119) = -0.21384318303939875;
        A(11, 120) = -0.036985251731401041;
        A(11, 121) = -0.06902391345671291;
        A(11, 122) = -0.1865408118653121;
        A(11, 123) = -0.030982422686847956;
        A(11, 124) = 0.077427593182760879;
        A(11, 125) = -0.082373641840961354;
        A(11, 126) = -0.077721416131944027;
        A(11, 127) = 0.01290143332003461;
        A(12, 0) = -0.018629761669549695;
        A(12, 1) = -0.044725762429802605;
        A(12, 2) = -0.076893274994727048;
        A(12, 3) = 0.038948187458906824;
        A(12, 4) = -0.028635438380773016;
        A(12, 5) = -0.029548189482322237;
        A(12, 6) = -0.00039073023778804158;
        A(12, 7) = -0.083226648815072121;
        A(12, 8) = 0.009875526677418537;
        A(12, 9) = 0.15541506759653362;
        A(12, 10) = -0.10877162727231042;
        A(12, 11) = -0.071601459532221343;
        A(12, 12) = 0.017584194097347565;
        A(12, 13) = 0.031473972655470056;
        A(12, 14) = 0.0012421604332915268;
        A(12, 15) = -0.016310559585982601;
        A(12, 16) = 0.15964241797833245;
        A(12, 17) = 0.059689206044521215;
        A(12, 18) = -0.084505494131219147;
        A(12, 19) = 0.12382524049648384;
        A(12, 20) = -0.10271974718999224;
        A(12, 21) = 0.017277453549008105;
        A(12, 22) = -0.013901074865079008;
        A(12, 23) = -0.047012533924353617;
        A(12, 24) = -0.096823296829737726;
        A(12, 25) = 0.057374232438650329;
        A(12, 26) = 0.025353546040744149;
        A(12, 27) = 0.1569157974704817;
        A(12, 28) = -0.012030864315694965;
        A(12, 29) = 0.024929530897388166;
        A(12, 30) = 0.037204900516393011;
        A(12, 31) = -0.093877806616181364;
        A(12, 32) = 0.09844956414145202;
        A(12, 33) = -0.11050781967833377;
        A(12, 34) = -0.10449782201123758;
        A(12, 35) = 0.22111975244221602;
        A(12, 36) = -0.088899177430925458;
        A(12, 37) = -0.20313568657135761;
        A(12, 38) = 0.10919137402528474;
        A(12, 39) = 0.014476246217620378;
        A(12, 40) = 0.15792290785355156;
        A(12, 41) = 0.028818470141672964;
        A(12, 42) = -0.027074320576120539;
        A(12, 43) = 0.027413726136808966;
        A(12, 44) = 0.037614720570418855;
        A(12, 45) = 0.17287305519347129;
        A(12, 46) = -0.055149578382204259;
        A(12, 47) = -0.11311526845643999;
        A(12, 48) = -0.1342507150345795;
        A(12, 49) = 0.046184899911608158;
        A(12, 50) = 0.11021430461880456;
        A(12, 51) = 0.086852967789712299;
        A(12, 52) = 0.13661914663610422;
        A(12, 53) = -0.17865992959378868;
        A(12, 54) = -0.071258188242362311;
        A(12, 55) = 0.027537063153854895;
        A(12, 56) = -0.015079639461487156;
        A(12, 57) = 0.12602652697235195;
        A(12, 58) = 0.0044569507571796604;
        A(12, 59) = -0.10776899200480475;
        A(12, 60) = -0.09379852701521782;
        A(12, 61) = -0.07238711299061483;
        A(12, 62) = 0.085584668254737428;
        A(12, 63) = 0.075749806161778843;
        A(12, 64) = 0.099588942033072503;
        A(12, 65) = 0.0018007729675488526;
        A(12, 66) = -0.028607579227948019;
        A(12, 67) = -0.042297915762814317;
        A(12, 68) = -0.019770271390202626;
        A(12, 69) = 0.13988038441704354;
        A(12, 70) = -0.16288742877227583;
        A(12, 71) = 0.011009726606691798;
        A(12, 72) = -0.096683109264533357;
        A(12, 73) = 0.079594971331650888;
        A(12, 74) = 0.092546802940141962;
        A(12, 75) = -0.16788620759160872;
        A(12, 76) = 0.033114010370259739;
        A(12, 77) = -0.045195357787152605;
        A(12, 78) = 0.11028190140557143;
        A(12, 79) = -0.24415493577826886;
        A(12, 80) = 0.0019003593509028249;
        A(12, 81) = 0.078544416216674892;
        A(12, 82) = 0.017253035256366581;
        A(12, 83) = -0.0028622445995749035;
        A(12, 84) = 0.10165383714256929;
        A(12, 85) = -0.051959204406824097;
        A(12, 86) = 0.12252268062813353;
        A(12, 87) = -0.069930268855304845;
        A(12, 88) = 0.04737281006764283;
        A(12, 89) = -0.12637830906246889;
        A(12, 90) = -0.052002396497606275;
        A(12, 91) = 0.096883617492234175;
        A(12, 92) = -0.040667416921680993;
        A(12, 93) = -0.014561822140967424;
        A(12, 94) = -0.082289372604033975;
        A(12, 95) = -0.020261994603290541;
        A(12, 96) = 0.093372110284387425;
        A(12, 97) = 0.050306928637503877;
        A(12, 98) = 0.085195015565307453;
        A(12, 99) = 0.062425509452490008;
        A(12, 100) = -0.10337129598317536;
        A(12, 101) = -0.034282953045061834;
        A(12, 102) = -0.13799868469850471;
        A(12, 103) = 0.023832383980956797;
        A(12, 104) = -0.011218703027413915;
        A(12, 105) = 0.098224775722507526;
        A(12, 106) = 0.059293867077522919;
        A(12, 107) = -0.053112396468370113;
        A(12, 108) = -0.053686034877567443;
        A(12, 109) = -0.1636361780288757;
        A(12, 110) = -0.011124540907460099;
        A(12, 111) = -0.032481798708432826;
        A(12, 112) = 0.055769049518061255;
        A(12, 113) = 0.0035589295042791;
        A(12, 114) = -0.039307473177782111;
        A(12, 115) = 0.033091849313230302;
        A(12, 116) = -0.033804570152893551;
        A(12, 117) = 0.025177589050679801;
        A(12, 118) = -0.034653944596883826;
        A(12, 119) = -0.16985741164543111;
        A(12, 120) = -0.032367358640368722;
        A(12, 121) = -0.087035891152259029;
        A(12, 122) = 0.069734465196461135;
        A(12, 123) = -0.071004967768170488;
        A(12, 124) = 0.094104704182128768;
        A(12, 125) = 0.0080025471003104063;
        A(12, 126) = -0.059573085039076212;
        A(12, 127) = -0.14821071325891294;
        A(13, 0) = 0.16900506109390687;
        A(13, 1) = -0.11219834986011985;
        A(13, 2) = 0.13662736650180254;
        A(13, 3) = -0.083427173646301006;
        A(13, 4) = -0.018727611904189881;
        A(13, 5) = -0.14307640177143241;
        A(13, 6) = -0.022393062497165661;
        A(13, 7) = 0.026840893805320263;
        A(13, 8) = 0.037511515949397348;
        A(13, 9) = -0.098156904139717227;
        A(13, 10) = 0.0062851505853756678;
        A(13, 11) = -0.045858713263222169;
        A(13, 12) = 0.050506278219446032;
        A(13, 13) = 0.022670606767344639;
        A(13, 14) = -0.056360075205854412;
        A(13, 15) = 0.01342187028240785;
        A(13, 16) = -0.037733395631307245;
        A(13, 17) = -0.030314246294042148;
        A(13, 18) = -0.022538013759591895;
        A(13, 19) = -0.10392702986521965;
        A(13, 20) = -0.13433052358498049;
        A(13, 21) = 0.099497149839859328;
        A(13, 22) = 0.043642816946792666;
        A(13, 23) = 0.061169781419619693;
        A(13, 24) = 0.10655132543613083;
        A(13, 25) = 0.13240842021538576;
        A(13, 26) = 0.10445387052066608;
        A(13, 27) = 0.092482184842457127;
        A(13, 28) = -0.10869729788061162;
        A(13, 29) = 0.0025242977874280204;
        A(13, 30) = 0.080597979165299719;
        A(13, 31) = -0.053196543564465827;
        A(13, 32) = 0.14028386519484304;
        A(13, 33) = 0.080753710276331742;
        A(13, 34) = 0.020048294185102872;
        A(13, 35) = -0.050468955307216103;
        A(13, 36) = 0.03159987326516922;
        A(13, 37) = 0.19045902247835972;
        A(13, 38) = -0.0041917778133832573;
        A(13, 39) = 0.046530532793223278;
        A(13, 40) = 0.0038256055733599924;
        A(13, 41) = -0.0012680968775104912;
        A(13, 42) = -0.15557100075010172;
        A(13, 43) = -0.14836702311755826;
        A(13, 44) = 0.094718187150237804;
        A(13, 45) = -0.0516427956473028;
        A(13, 46) = 0.030526104199246139;
        A(13, 47) = -0.098717270048886849;
        A(13, 48) = -0.064852051025406116;
        A(13, 49) = 0.064086936313431597;
        A(13, 50) = 0.13712893984161267;
        A(13, 51) = -0.087344685388273877;
        A(13, 52) = -0.14742422053061913;
        A(13, 53) = 0.062435548839384132;
        A(13, 54) = 0.09083952441751203;
        A(13, 55) = 0.011108603153436588;
        A(13, 56) = -0.14453479475720543;
        A(13, 57) = 0.046360305242805704;
        A(13, 58) = 0.01300145450630147;
        A(13, 59) = 0.085923156668018669;
        A(13, 60) = -0.071286200264921912;
        A(13, 61) = 0.12356027150337352;
        A(13, 62) = 0.013196857903151204;
        A(13, 63) = -0.015380279939413113;
        A(13, 64) = 0.011418799607912363;
        A(13, 65) = 0.078465211230154736;
        A(13, 66) = 0.038480618547754593;
        A(13, 67) = -0.23098199715376538;
        A(13, 68) = -0.045943113115581372;
        A(13, 69) = 0.17256374898420798;
        A(13, 70) = 0.13256401501801721;
        A(13, 71) = 0.20382589889184488;
        A(13, 72) = -0.063411247560106992;
        A(13, 73) = 0.077972516634696926;
        A(13, 74) = -0.1075784716368639;
        A(13, 75) = -0.10628080834864279;
        A(13, 76) = 0.068881599670505139;
        A(13, 77) = 0.077356465525771495;
        A(13, 78) = -0.09684605838726576;
        A(13, 79) = -0.043938735092240236;
        A(13, 80) = -0.10454572959350003;
        A(13, 81) = -0.159288947644396;
        A(13, 82) = -0.00013391096741563469;
        A(13, 83) = 0.0098387703610381787;
        A(13, 84) = -0.025392889913637872;
        A(13, 85) = -0.025713061060481487;
        A(13, 86) = 0.036537160171639861;
        A(13, 87) = -0.02620775513777613;
        A(13, 88) = 0.058962089663213306;
        A(13, 89) = 0.036273416042289106;
        A(13, 90) = -0.12198405336460588;
        A(13, 91) = -0.067978298585840063;
        A(13, 92) = 0.0030260727966550556;
        A(13, 93) = -0.089975389227779631;
        A(13, 94) = -0.08228814479704781;
        A(13, 95) = 0.065089977295071877;
        A(13, 96) = -0.059378186028658131;
        A(13, 97) = -0.079410368440637397;
        A(13, 98) = 0.073641966249536173;
        A(13, 99) = 0.013645619192864765;
        A(13, 100) = 0.086309251585444904;
        A(13, 101) = 0.080339485793736093;
        A(13, 102) = -0.09500825064977679;
        A(13, 103) = -0.095582227571455125;
        A(13, 104) = 0.036240740303167672;
        A(13, 105) = 0.20980955349803698;
        A(13, 106) = 0.042094646745255815;
        A(13, 107) = 0.026811025539722644;
        A(13, 108) = 0.1304256671721562;
        A(13, 109) = -0.06048589683425519;
        A(13, 110) = 0.027351803394418662;
        A(13, 111) = -0.083324788865564964;
        A(13, 112) = 0.16142520690316089;
        A(13, 113) = -0.057433596900813164;
        A(13, 114) = -0.073732997395797556;
        A(13, 115) = -0.056657953939737403;
        A(13, 116) = -0.090784434194408098;
        A(13, 117) = -0.027312065454414183;
        A(13, 118) = -0.084613185787109274;
        A(13, 119) = -0.12645163872611548;
        A(13, 120) = 0.11482557301742201;
        A(13, 121) = 0.071430594082610599;
        A(13, 122) = -0.054033493761847233;
        A(13, 123) = -0.024692725290571954;
        A(13, 124) = -0.046221429583246057;
        A(13, 125) = 0.070641948176314806;
        A(13, 126) = -0.037893382526702581;
        A(13, 127) = 0.055637437801698927;
        A(14, 0) = -0.06904112531909061;
        A(14, 1) = -0.1211699987423327;
        A(14, 2) = -0.024141978151194399;
        A(14, 3) = 0.056112413350715123;
        A(14, 4) = 0.014455991438837528;
        A(14, 5) = 0.020780693916313091;
        A(14, 6) = 0.097860405024299074;
        A(14, 7) = 0.094215151756836743;
        A(14, 8) = -0.053012189594495433;
        A(14, 9) = 0.010769396543963194;
        A(14, 10) = -0.071960331730491073;
        A(14, 11) = -0.018812483157738525;
        A(14, 12) = -0.11656179358781299;
        A(14, 13) = -0.031053644951128379;
        A(14, 14) = -0.13450429986496629;
        A(14, 15) = 0.012593752630037584;
        A(14, 16) = -0.0054693771465255878;
        A(14, 17) = -0.044724556843592549;
        A(14, 18) = -0.036350323862038084;
        A(14, 19) = -0.057514307683807109;
        A(14, 20) = -0.14736832981689454;
        A(14, 21) = 0.030628018386070856;
        A(14, 22) = 0.066268992316235148;
        A(14, 23) = -0.033434768044111586;
        A(14, 24) = -0.071015035625907746;
        A(14, 25) = 0.17352427641578583;
        A(14, 26) = 0.042253391159020687;
        A(14, 27) = 0.051520140688241615;
        A(14, 28) = 0.088912088177085929;
        A(14, 29) = 0.15722801286241722;
        A(14, 30) = 0.011368002140066395;
        A(14, 31) = 0.045954466263012986;
        A(14, 32) = -0.070807368426161962;
        A(14, 33) = -0.08923024146084868;
        A(14, 34) = -0.016347309390140469;
        A(14, 35) = 0.043290334159362301;
        A(14, 36) = 0.094948632947416053;
        A(14, 37) = 0.084692351217333914;
        A(14, 38) = 0.11749858099178086;
        A(14, 39) = -0.035774324641249633;
        A(14, 40) = -0.0066319448500515021;
        A(14, 41) = 0.016301222000811237;
        A(14, 42) = 0.10539111148966751;
        A(14, 43) = 0.091882816027395814;
        A(14, 44) = -0.068099177481144302;
        A(14, 45) = -0.0044692885995876799;
        A(14, 46) = 0.071969658400453246;
        A(14, 47) = -0.11213537170131654;
        A(14, 48) = 0.0034843964565316257;
        A(14, 49) = 0.0072183207741095268;
        A(14, 50) = -0.063419741414238728;
        A(14, 51) = 0.022677213241097782;
        A(14, 52) = -0.068998674885809783;
        A(14, 53) = 0.04813965982115518;
        A(14, 54) = -0.12794336130022177;
        A(14, 55) = 0.037786715699002778;
        A(14, 56) = 0.07089939625380047;
        A(14, 57) = -0.054474792678410267;
        A(14, 58) = 0.082314796800399964;
        A(14, 59) = -0.068015140195563928;
        A(14, 60) = 0.1013902321023471;
        A(14, 61) = 0.14439557781106677;
        A(14, 62) = -0.015593777760190282;
        A(14, 63) = -0.10938866119455186;
        A(14, 64) = 0.002415055048301952;
        A(14, 65) = 0.12580912162270597;
        A(14, 66) = -0.053230712913966749;
        A(14, 67) = 0.0051659683248697144;
        A(14, 68) = -0.086490556198821039;
        A(14, 69) = -0.090365193433653609;
        A(14, 70) = 0.045470363443858908;
        A(14, 71) = 0.16138236120415458;
        A(14, 72) = -0.071377139139954027;
        A(14, 73) = 0.15934732295317161;
        A(14, 74) = -0.11614166189206851;
        A(14, 75) = -0.015788269053475218;
        A(14, 76) = -0.04013080733963547;
        A(14, 77) = 0.019525249686449662;
        A(14, 78) = -0.17769121386673201;
        A(14, 79) = -0.070863559794257222;
        A(14, 80) = 0.01283730227353936;
        A(14, 81) = 0.077589210669038441;
        A(14, 82) = -0.0091164892920181026;
        A(14, 83) = 0.052492818282693088;
        A(14, 84) = 0.0058171644447573348;
        A(14, 85) = 0.0026009196256252531;
        A(14, 86) = 0.069158686681215401;
        A(14, 87) = 0.10666046594493149;
        A(14, 88) = 0.063445382522088076;
        A(14, 89) = -0.014154803741245095;
        A(14, 90) = 0.16088761114192793;
        A(14, 91) = -0.13070640241626671;
        A(14, 92) = -0.066210785149167728;
        A(14, 93) = 0.035718735320824486;
        A(14, 94) = 0.059970824273352943;
        A(14, 95) = -0.21695264939103953;
        A(14, 96) = -0.060290660594311415;
        A(14, 97) = -0.0066084635605007658;
        A(14, 98) = -0.19019221218810956;
        A(14, 99) = -0.067781398806867954;
        A(14, 100) = -0.1447229993294244;
        A(14, 101) = -0.0012301921826419135;
        A(14, 102) = -0.012782067620101936;
        A(14, 103) = 0.13244207061379287;
        A(14, 104) = -0.13943771833193194;
        A(14, 105) = -0.067404021414519885;
        A(14, 106) = 0.20694308564252067;
        A(14, 107) = -0.15197906903874089;
        A(14, 108) = 0.042934938216811991;
        A(14, 109) = 0.036340020439899978;
        A(14, 110) = -0.078219092098787774;
        A(14, 111) = -0.071719683269909323;
        A(14, 112) = -0.011247500859095184;
        A(14, 113) = -0.064070347877544911;
        A(14, 114) = -0.10129040958625557;
        A(14, 115) = -0.098285071709936056;
        A(14, 116) = -0.084207529702609335;
        A(14, 117) = -0.21733703845314012;
        A(14, 118) = 0.15763044999794157;
        A(14, 119) = 0.0031945437368425741;
        A(14, 120) = 0.00027546568560782433;
        A(14, 121) = -0.066853988867238118;
        A(14, 122) = -0.16156367539841771;
        A(14, 123) = -0.046507508690428412;
        A(14, 124) = -0.019365053364558835;
        A(14, 125) = -0.081643802317810613;
        A(14, 126) = 0.027300629188046849;
        A(14, 127) = -0.14495938939027914;
        A(15, 0) = -0.01667848977581491;
        A(15, 1) = 0.069551405245214193;
        A(15, 2) = 0.056535606526975729;
        A(15, 3) = 0.033296508888976728;
        A(15, 4) = -0.049784671930104975;
        A(15, 5) = 0.07721437527968375;
        A(15, 6) = 0.19350857567884616;
        A(15, 7) = -0.11412961261351744;
        A(15, 8) = -0.065382151448263884;
        A(15, 9) = -0.047252163967406537;
        A(15, 10) = -0.047208123485745511;
        A(15, 11) = 0.046069022381341959;
        A(15, 12) = -0.021289837466546339;
        A(15, 13) = -0.0026716799558102466;
        A(15, 14) = 0.096048219540094806;
        A(15, 15) = 0.021745426373659036;
        A(15, 16) = -0.19778799750117798;
        A(15, 17) = 0.1278122160235938;
        A(15, 18) = -0.0215217426893431;
        A(15, 19) = -0.0071055829763609357;
        A(15, 20) = 0.17145619926054534;
        A(15, 21) = -0.03128384091042416;
        A(15, 22) = -0.14096354071930217;
        A(15, 23) = -0.04243292582386219;
        A(15, 24) = -0.027416945482575422;
        A(15, 25) = 0.023773184217492312;
        A(15, 26) = 0.22062484220325046;
        A(15, 27) = 0.17917969625180058;
        A(15, 28) = 0.097299793466703782;
        A(15, 29) = 0.20113782898410748;
        A(15, 30) = 0.011151795017125536;
        A(15, 31) = -0.053940578232697864;
        A(15, 32) = -0.10331724152291646;
        A(15, 33) = 0.053029923407362609;
        A(15, 34) = -0.0073814018047687734;
        A(15, 35) = 0.088496709632195802;
        A(15, 36) = -0.053444352129644178;
        A(15, 37) = 0.043551244582276341;
        A(15, 38) = 0.11437882283952447;
        A(15, 39) = 0.065859285925591191;
        A(15, 40) = 0.10340868792305549;
        A(15, 41) = 0.1732596034563991;
        A(15, 42) = 0.16299844772870059;
        A(15, 43) = 0.006987234468647803;
        A(15, 44) = 0.11411285668891089;
        A(15, 45) = -0.13004828907829363;
        A(15, 46) = -0.053821594700280591;
        A(15, 47) = -0.027998791958344614;
        A(15, 48) = 0.16924876231745875;
        A(15, 49) = -0.026934639139222366;
        A(15, 50) = 0.027538271147808747;
        A(15, 51) = -0.15375273366874498;
        A(15, 52) = -0.11384523810189726;
        A(15, 53) = 0.020504791193660828;
        A(15, 54) = 0.048869729652680806;
        A(15, 55) = -0.14619794886012827;
        A(15, 56) = 0.033261430218019986;
        A(15, 57) = 0.036247340188917163;
        A(15, 58) = -0.0085290023330899054;
        A(15, 59) = 0.022122953976737622;
        A(15, 60) = 0.047550918762216315;
        A(15, 61) = 0.085259102910804282;
        A(15, 62) = 0.099082631544736594;
        A(15, 63) = -0.0085111941137083619;
        A(15, 64) = 0.079477635804333771;
        A(15, 65) = -0.012594121410947144;
        A(15, 66) = -0.066137702873986987;
        A(15, 67) = 0.062788334086359254;
        A(15, 68) = -0.01202498785104756;
        A(15, 69) = 0.05706753131368994;
        A(15, 70) = 0.064946618998331762;
        A(15, 71) = -0.10137824152854769;
        A(15, 72) = 0.017144126702169506;
        A(15, 73) = -0.018090389296768927;
        A(15, 74) = -0.05037310410745198;
        A(15, 75) = 0.0073332024900703147;
        A(15, 76) = -0.075475106766465891;
        A(15, 77) = 0.048352104480281342;
        A(15, 78) = -0.061012726577774373;
        A(15, 79) = 0.00059070404644273253;
        A(15, 80) = 0.13573501806861893;
        A(15, 81) = 0.0088515977232667548;
        A(15, 82) = 0.075361298622531617;
        A(15, 83) = 0.004134703740553955;
        A(15, 84) = 0.029723181750310034;
        A(15, 85) = 0.085070532146800951;
        A(15, 86) = 0.050987857807091266;
        A(15, 87) = 0.12027276735914105;
        A(15, 88) = -0.17291513474447678;
        A(15, 89) = 0.01623558379125703;
        A(15, 90) = -0.0033062169555106678;
        A(15, 91) = -0.0068311696695479915;
        A(15, 92) = 0.06523780586872148;
        A(15, 93) = 0.081853201889156235;
        A(15, 94) = -0.039778736625549115;
        A(15, 95) = 0.1213627012112081;
        A(15, 96) = -0.068291503554341548;
        A(15, 97) = 0.19507054967938178;
        A(15, 98) = 0.051151894973571685;
        A(15, 99) = 0.038944402436656964;
        A(15, 100) = 0.041961685631068606;
        A(15, 101) = 0.060356469913762791;
        A(15, 102) = -0.098799597426047547;
        A(15, 103) = -0.03084541082692897;
        A(15, 104) = 0.18751566040708878;
        A(15, 105) = 0.040248827057281764;
        A(15, 106) = 0.0018488808880515462;
        A(15, 107) = -0.10731870313609011;
        A(15, 108) = 0.021246394537416259;
        A(15, 109) = -0.041419419999117496;
        A(15, 110) = 0.053434191694572988;
        A(15, 111) = -0.073941872709752846;
        A(15, 112) = 0.041144865891005217;
        A(15, 113) = -0.06479885073895271;
        A(15, 114) = 0.02781757437110231;
        A(15, 115) = 0.019121462896298846;
        A(15, 116) = -0.038721491101543243;
        A(15, 117) = 0.1696024233868601;
        A(15, 118) = -0.15239786389853024;
        A(15, 119) = -0.0048701120380408303;
        A(15, 120) = -0.023435695146716493;
        A(15, 121) = -0.13355450763964138;
        A(15, 122) = -0.16118198555518595;
        A(15, 123) = 0.05588220673715049;
        A(15, 124) = 0.058019092768980145;
        A(15, 125) = 0.0110699980516442;
        A(15, 126) = 0.0012950789801700405;
        A(15, 127) = -0.14819277212414711;
        A(16, 0) = 0.061744701515976622;
        A(16, 1) = 0.017699979442898188;
        A(16, 2) = 0.025729322553985724;
        A(16, 3) = 0.04776648201029865;
        A(16, 4) = 0.025786089698559393;
        A(16, 5) = 0.11657739043193528;
        A(16, 6) = 0.060672161833908778;
        A(16, 7) = 0.040271113935343911;
        A(16, 8) = -0.057768935532258849;
        A(16, 9) = -0.11586831857488701;
        A(16, 10) = -0.0017837399774834478;
        A(16, 11) = -0.22057591225125112;
        A(16, 12) = 0.035814680964562626;
        A(16, 13) = -0.074757642258910711;
        A(16, 14) = 0.046457267274953619;
        A(16, 15) = -0.021172541547858203;
        A(16, 16) = -0.015355863244925883;
        A(16, 17) = 0.11154069804197002;
        A(16, 18) = 0.12218457071084532;
        A(16, 19) = -0.016777433296799739;
        A(16, 20) = -0.0017603170806782253;
        A(16, 21) = -0.049110577712067199;
        A(16, 22) = -0.0014715703607010092;
        A(16, 23) = -0.036195189935638944;
        A(16, 24) = 0.062823077428128343;
        A(16, 25) = -0.063329205032340324;
        A(16, 26) = -0.24625867244944111;
        A(16, 27) = 0.015287901082477975;
        A(16, 28) = 0.012663644193881395;
        A(16, 29) = 0.080856214794940678;
        A(16, 30) = -0.0052574908609016747;
        A(16, 31) = 0.070797561021486641;
        A(16, 32) = 0.19224185619943226;
        A(16, 33) = -0.10799115423445957;
        A(16, 34) = -0.051249623013409948;
        A(16, 35) = 0.040188292153935268;
        A(16, 36) = 0.061414720825467589;
        A(16, 37) = -0.040666179863059426;
        A(16, 38) = 0.0035974496416398688;
        A(16, 39) = -0.021636543932697774;
        A(16, 40) = -0.014650208460206867;
        A(16, 41) = 0.03571026944623848;
        A(16, 42) = 0.0045533315852126777;
        A(16, 43) = -0.13000117702531308;
        A(16, 44) = -0.015507215696560731;
        A(16, 45) = 0.12454120157779665;
        A(16, 46) = -0.019386470806324385;
        A(16, 47) = -0.091608913304871725;
        A(16, 48) = 0.039930094813666966;
        A(16, 49) = -0.11597395747892029;
        A(16, 50) = -0.10948697313896935;
        A(16, 51) = 0.11973462742028435;
        A(16, 52) = -0.10628044844366191;
        A(16, 53) = 0.047968096089646306;
        A(16, 54) = -0.11721467400967669;
        A(16, 55) = 0.0075403852974422281;
        A(16, 56) = 0.15807533445276326;
        A(16, 57) = -0.089415173121903432;
        A(16, 58) = 0.0089199478677369354;
        A(16, 59) = -1.6705913915955606e-005;
        A(16, 60) = -0.035565083278790689;
        A(16, 61) = 0.094915233857787037;
        A(16, 62) = 0.09912942418604978;
        A(16, 63) = -0.0045955056899105902;
        A(16, 64) = 0.083684375990066465;
        A(16, 65) = 0.064628418778351404;
        A(16, 66) = 0.092732607684257395;
        A(16, 67) = -0.028261872788403294;
        A(16, 68) = -0.1720483645668795;
        A(16, 69) = -0.10165255154350678;
        A(16, 70) = -0.059106756297573129;
        A(16, 71) = -0.0016268848321722255;
        A(16, 72) = -0.059228445164461525;
        A(16, 73) = -0.19856232918441519;
        A(16, 74) = 0.020167092972915773;
        A(16, 75) = -0.031351472157168124;
        A(16, 76) = 0.15799394356963242;
        A(16, 77) = 0.13649962476976774;
        A(16, 78) = -0.04348073842963851;
        A(16, 79) = 0.099739242549730059;
        A(16, 80) = 0.029123733900040132;
        A(16, 81) = -0.15313647560738813;
        A(16, 82) = 0.077155793375297918;
        A(16, 83) = 0.0014219303432012609;
        A(16, 84) = -0.0030431577677234971;
        A(16, 85) = -0.039129597372711843;
        A(16, 86) = 0.014415292859303284;
        A(16, 87) = -0.045331196836420166;
        A(16, 88) = 0.070214519438902501;
        A(16, 89) = 0.13222463511834603;
        A(16, 90) = -0.03305482260031431;
        A(16, 91) = 0.099577557334501937;
        A(16, 92) = -0.039142555210723032;
        A(16, 93) = -0.022497040352261147;
        A(16, 94) = 0.041953452343639439;
        A(16, 95) = -0.15290776596890401;
        A(16, 96) = 0.1800474263625827;
        A(16, 97) = 0.040992388695044277;
        A(16, 98) = 0.11103731364574614;
        A(16, 99) = -0.06351929220539157;
        A(16, 100) = 0.11019647058881232;
        A(16, 101) = 0.040557434986898289;
        A(16, 102) = -0.092170096463855294;
        A(16, 103) = 0.086413676718798932;
        A(16, 104) = 0.17123655913363142;
        A(16, 105) = 0.021780316692205232;
        A(16, 106) = 0.075555377350119524;
        A(16, 107) = -0.077594317701807913;
        A(16, 108) = 0.014043254904860296;
        A(16, 109) = 0.13439673765343976;
        A(16, 110) = 0.011859577117637847;
        A(16, 111) = 0.0039884325486311285;
        A(16, 112) = -0.090030379583411063;
        A(16, 113) = -0.20544786777327478;
        A(16, 114) = 0.004327468379313068;
        A(16, 115) = 0.12785310606059594;
        A(16, 116) = 0.022424914355724981;
        A(16, 117) = 0.10601006075995337;
        A(16, 118) = -0.066578211366266057;
        A(16, 119) = -0.09527729700653717;
        A(16, 120) = 0.13917966863860393;
        A(16, 121) = -0.039387680878816667;
        A(16, 122) = 0.016269330078544315;
        A(16, 123) = -0.11392711416925527;
        A(16, 124) = 0.026695910302985432;
        A(16, 125) = -0.18460273345876249;
        A(16, 126) = 0.0053567633701585588;
        A(16, 127) = 0.056135181228267675;
        A(17, 0) = -0.0091893424466542931;
        A(17, 1) = 0.16874147708850537;
        A(17, 2) = 0.041537616270096014;
        A(17, 3) = 0.13256739148420499;
        A(17, 4) = 0.048789919723444639;
        A(17, 5) = -0.034352611072679333;
        A(17, 6) = 0.042242084253217155;
        A(17, 7) = 0.021700140812789769;
        A(17, 8) = 0.12155866689555728;
        A(17, 9) = -0.066893985021673624;
        A(17, 10) = 0.11022556133080613;
        A(17, 11) = 0.092831002501402665;
        A(17, 12) = 0.11404344026337061;
        A(17, 13) = -0.1319724192766783;
        A(17, 14) = -0.14838786465438214;
        A(17, 15) = -0.024364598676825097;
        A(17, 16) = -0.035814863645788605;
        A(17, 17) = -0.12923820872399117;
        A(17, 18) = -0.014711712747695081;
        A(17, 19) = -0.089420242948730883;
        A(17, 20) = 0.13515060579666552;
        A(17, 21) = 0.057620630608766474;
        A(17, 22) = 0.023691612732098039;
        A(17, 23) = -0.17897512675387928;
        A(17, 24) = -0.0048551739515619655;
        A(17, 25) = 0.077721239520998214;
        A(17, 26) = -0.049267645022691563;
        A(17, 27) = -0.10790236972750003;
        A(17, 28) = -0.19064257242646232;
        A(17, 29) = -0.078139356661462989;
        A(17, 30) = -0.033334379577964729;
        A(17, 31) = -0.095600896229675214;
        A(17, 32) = -0.15558283468097489;
        A(17, 33) = -0.00012926579038135058;
        A(17, 34) = 0.051609926293935959;
        A(17, 35) = 0.049013078248038799;
        A(17, 36) = 0.015116446958196127;
        A(17, 37) = 0.050863303471880089;
        A(17, 38) = -0.061034950052971715;
        A(17, 39) = -0.017976351999660203;
        A(17, 40) = -0.02199961899656443;
        A(17, 41) = 0.017658388893607064;
        A(17, 42) = -0.029600776543953732;
        A(17, 43) = -0.0084010035859408277;
        A(17, 44) = 0.055250600091228501;
        A(17, 45) = 0.1194810472773155;
        A(17, 46) = -0.10679192142133054;
        A(17, 47) = 0.24953273789962133;
        A(17, 48) = -0.037605567231519504;
        A(17, 49) = -0.031343397230195427;
        A(17, 50) = 0.10957227590615662;
        A(17, 51) = 0.067689137693640156;
        A(17, 52) = -0.043121514673867899;
        A(17, 53) = -0.17504441696672768;
        A(17, 54) = -0.0082050998636522612;
        A(17, 55) = -0.0064041995808237521;
        A(17, 56) = 0.13138388902412362;
        A(17, 57) = 0.017473127224949814;
        A(17, 58) = -0.0087278625930284383;
        A(17, 59) = -0.087732929193077791;
        A(17, 60) = -0.05522025710378245;
        A(17, 61) = 0.1707963246205339;
        A(17, 62) = 0.00038667093853878703;
        A(17, 63) = -0.073585812022947908;
        A(17, 64) = -0.14361336502448571;
        A(17, 65) = 0.0690490013001646;
        A(17, 66) = -0.12944182888722944;
        A(17, 67) = -0.049561268317343622;
        A(17, 68) = -0.15300735847746608;
        A(17, 69) = -0.16116569508718875;
        A(17, 70) = 0.012688064410333919;
        A(17, 71) = 0.079679069893624846;
        A(17, 72) = -0.012801164157132911;
        A(17, 73) = 0.13980914427840474;
        A(17, 74) = -0.080645507788080162;
        A(17, 75) = 0.071797441485842176;
        A(17, 76) = -0.062018027967160147;
        A(17, 77) = -0.034652842352932943;
        A(17, 78) = 0.084673451507884606;
        A(17, 79) = 0.091235847300361328;
        A(17, 80) = 0.037851921881313332;
        A(17, 81) = -0.045535891255628215;
        A(17, 82) = 0.019705945425588199;
        A(17, 83) = 0.0089172834427657457;
        A(17, 84) = -0.089119918663014552;
        A(17, 85) = -0.025906940591965424;
        A(17, 86) = 0.15668637509799804;
        A(17, 87) = -0.050315536773121811;
        A(17, 88) = 0.10595768858968027;
        A(17, 89) = -0.035616554699957455;
        A(17, 90) = -0.021764760919921723;
        A(17, 91) = 0.057431040059377596;
        A(17, 92) = -0.150288820386696;
        A(17, 93) = 0.0026492294464497447;
        A(17, 94) = 0.10635542940673864;
        A(17, 95) = 0.057666543509096627;
        A(17, 96) = -0.065207192812409789;
        A(17, 97) = 0.097888264793288715;
        A(17, 98) = 0.0041334679251750495;
        A(17, 99) = 0.088332994844411483;
        A(17, 100) = -0.16189103310621139;
        A(17, 101) = -0.089581990118158983;
        A(17, 102) = -0.17615269451054497;
        A(17, 103) = -0.065243387555674021;
        A(17, 104) = 0.045864734485595179;
        A(17, 105) = 0.065091089125127621;
        A(17, 106) = 0.040552792736590418;
        A(17, 107) = -0.019731418632483122;
        A(17, 108) = -0.12011359696573434;
        A(17, 109) = -0.055070365615704407;
        A(17, 110) = 0.10347962725786064;
        A(17, 111) = 0.044956401751243741;
        A(17, 112) = 0.026140876456827989;
        A(17, 113) = -0.1207713168607219;
        A(17, 114) = 0.135254080908285;
        A(17, 115) = 0.063790278714053822;
        A(17, 116) = -0.10435119479165618;
        A(17, 117) = 0.0030187421246983016;
        A(17, 118) = -0.079098004672565295;
        A(17, 119) = 0.041590160727178777;
        A(17, 120) = 0.099585121843506583;
        A(17, 121) = -0.027673209210853811;
        A(17, 122) = 0.061909501055768423;
        A(17, 123) = 0.027618177301816767;
        A(17, 124) = 0.070265627188412672;
        A(17, 125) = 0.045984735390865852;
        A(17, 126) = 0.0018307766759746464;
        A(17, 127) = -0.049485222359776648;
        A(18, 0) = -0.13835002534869958;
        A(18, 1) = -0.052976952084811513;
        A(18, 2) = -0.17569982739695875;
        A(18, 3) = -0.089504063727685962;
        A(18, 4) = 0.094879966308444322;
        A(18, 5) = 0.023368875941516935;
        A(18, 6) = -0.044668117313615308;
        A(18, 7) = 0.082348801869131891;
        A(18, 8) = 0.10685315170898749;
        A(18, 9) = 0.13242804326329907;
        A(18, 10) = -0.10176394524376275;
        A(18, 11) = -0.11093598984688244;
        A(18, 12) = 0.061282368275784996;
        A(18, 13) = 0.058189941942532006;
        A(18, 14) = -0.083124124073750541;
        A(18, 15) = 0.055403468598711196;
        A(18, 16) = -0.012389901725042817;
        A(18, 17) = -0.0089361631502697988;
        A(18, 18) = 0.0376593085596559;
        A(18, 19) = -0.10352809151353008;
        A(18, 20) = 0.17067835663410866;
        A(18, 21) = -0.029150628049766147;
        A(18, 22) = -0.11925529984049643;
        A(18, 23) = -0.053061462975924206;
        A(18, 24) = 0.0060777978863230143;
        A(18, 25) = -0.063695750628820783;
        A(18, 26) = 0.009245604313236587;
        A(18, 27) = 0.17944712023127093;
        A(18, 28) = 0.14477096403695361;
        A(18, 29) = 0.047232547006580944;
        A(18, 30) = 0.040546435076522336;
        A(18, 31) = 0.048189936384809423;
        A(18, 32) = 0.044408493548524053;
        A(18, 33) = -0.017248574305694188;
        A(18, 34) = 0.02016718786837066;
        A(18, 35) = -0.14798596994607277;
        A(18, 36) = -0.013148120561525478;
        A(18, 37) = 0.0026072336304395205;
        A(18, 38) = -0.030783884361079393;
        A(18, 39) = 0.043716372533697929;
        A(18, 40) = 0.052316061497535385;
        A(18, 41) = -0.11340970006050197;
        A(18, 42) = 0.054700906068246277;
        A(18, 43) = -0.00057051228172781687;
        A(18, 44) = -0.027961869377926857;
        A(18, 45) = 0.059705223767079534;
        A(18, 46) = -0.18319700334312344;
        A(18, 47) = 0.1092748323555003;
        A(18, 48) = 0.09148583551574585;
        A(18, 49) = 0.18406544553174076;
        A(18, 50) = 0.043823190316302683;
        A(18, 51) = 0.042115927119501267;
        A(18, 52) = 0.17585704440943542;
        A(18, 53) = 0.013614561437223621;
        A(18, 54) = 0.14636559761564888;
        A(18, 55) = 0.084186976632113164;
        A(18, 56) = -0.031704200617168388;
        A(18, 57) = 0.0024611868251496055;
        A(18, 58) = -0.045831928504285538;
        A(18, 59) = -0.026233458783217079;
        A(18, 60) = 0.00045462586941791977;
        A(18, 61) = -0.0041609585591718679;
        A(18, 62) = -0.093069559471998131;
        A(18, 63) = -0.025935165628059434;
        A(18, 64) = -0.090652381141883898;
        A(18, 65) = 0.064767143415467188;
        A(18, 66) = -0.023515713756298365;
        A(18, 67) = 0.005463956914037435;
        A(18, 68) = -0.078297668421375477;
        A(18, 69) = -0.096394591878417757;
        A(18, 70) = -0.0042543366527073162;
        A(18, 71) = 0.050145531579276599;
        A(18, 72) = -0.044535150824683414;
        A(18, 73) = -0.043101700528319561;
        A(18, 74) = -0.038577636176586022;
        A(18, 75) = -0.04872577244310658;
        A(18, 76) = 0.20833216361359841;
        A(18, 77) = 0.20654122661352348;
        A(18, 78) = -0.022546255255107995;
        A(18, 79) = 0.15788215609229805;
        A(18, 80) = -0.15738265341374369;
        A(18, 81) = -0.081469096242809846;
        A(18, 82) = -0.030449711090075722;
        A(18, 83) = 0.06434485387359376;
        A(18, 84) = 0.11089914501280879;
        A(18, 85) = 0.0092858002192746508;
        A(18, 86) = 0.072468846900071854;
        A(18, 87) = 0.10098406546181406;
        A(18, 88) = -0.057308956234682171;
        A(18, 89) = -0.18104928284120311;
        A(18, 90) = -0.09512749669259532;
        A(18, 91) = 0.00033533218427526869;
        A(18, 92) = -0.078239432930673133;
        A(18, 93) = 0.021206950524669053;
        A(18, 94) = 0.090224747669693309;
        A(18, 95) = 0.081887716840626651;
        A(18, 96) = -0.029743751420234471;
        A(18, 97) = 0.089047755449794957;
        A(18, 98) = -0.022371907451794907;
        A(18, 99) = 0.07148038024224862;
        A(18, 100) = 0.045816948545119141;
        A(18, 101) = -0.018777673570342268;
        A(18, 102) = -0.10668640605449134;
        A(18, 103) = 0.10742547100216265;
        A(18, 104) = 0.10480603586340598;
        A(18, 105) = 0.055621928618434208;
        A(18, 106) = 0.12090739583984694;
        A(18, 107) = -0.029595940357018548;
        A(18, 108) = 0.07772285451572597;
        A(18, 109) = -0.030490155564738247;
        A(18, 110) = 0.090608794239257009;
        A(18, 111) = 0.05477231242979605;
        A(18, 112) = 0.06877085405889867;
        A(18, 113) = 0.19032797811368335;
        A(18, 114) = -0.18777321428357061;
        A(18, 115) = -0.026937924223991258;
        A(18, 116) = 0.12442668333903212;
        A(18, 117) = 0.035086361685099994;
        A(18, 118) = 0.1686009280654828;
        A(18, 119) = 0.04067430271439261;
        A(18, 120) = 0.043682440045558227;
        A(18, 121) = 0.048919560397090639;
        A(18, 122) = -0.076996355314669293;
        A(18, 123) = 0.053380271935720085;
        A(18, 124) = 0.069025681604013192;
        A(18, 125) = 0.010417728847031384;
        A(18, 126) = 0.046698230990556124;
        A(18, 127) = 0.044790577236220847;
        A(19, 0) = -0.015625270229336505;
        A(19, 1) = -0.056055775237373165;
        A(19, 2) = -0.058363480856054785;
        A(19, 3) = -0.14236798898041164;
        A(19, 4) = -0.02135692764171947;
        A(19, 5) = -0.056326226447984476;
        A(19, 6) = 0.048488441386549515;
        A(19, 7) = -0.082156789200710151;
        A(19, 8) = -0.13577059978023881;
        A(19, 9) = 0.078948079102773766;
        A(19, 10) = 0.02644356074974135;
        A(19, 11) = -0.026739992758643409;
        A(19, 12) = 0.14285108149766346;
        A(19, 13) = 0.037942161419171144;
        A(19, 14) = -0.0011818578292002307;
        A(19, 15) = 0.065584903389936527;
        A(19, 16) = -0.016158519268244971;
        A(19, 17) = 0.012805473986983005;
        A(19, 18) = 0.026395537697265256;
        A(19, 19) = 0.091000847461338685;
        A(19, 20) = -0.10781842158212912;
        A(19, 21) = -0.034884106115332936;
        A(19, 22) = -0.042237397753223924;
        A(19, 23) = -0.15531614899548621;
        A(19, 24) = -0.039500097004502167;
        A(19, 25) = -0.049641576894228608;
        A(19, 26) = -0.15313469748974512;
        A(19, 27) = 0.030898917759803846;
        A(19, 28) = -0.075960340314594504;
        A(19, 29) = -0.11146373957941072;
        A(19, 30) = 0.13781467661500665;
        A(19, 31) = -0.059997315085298222;
        A(19, 32) = -0.11904728718798696;
        A(19, 33) = 0.054050794330175407;
        A(19, 34) = -0.079958531380012438;
        A(19, 35) = -0.011161480440405193;
        A(19, 36) = 0.051728855476545092;
        A(19, 37) = -0.033914308561210221;
        A(19, 38) = -0.058562845219827984;
        A(19, 39) = 0.044840836161052777;
        A(19, 40) = 0.142578896613796;
        A(19, 41) = 0.066747648108463509;
        A(19, 42) = -0.11603837636257815;
        A(19, 43) = -0.073539955664758488;
        A(19, 44) = -0.11080679561473292;
        A(19, 45) = 0.12128507141452796;
        A(19, 46) = -0.037021373402524593;
        A(19, 47) = -0.075043106309792176;
        A(19, 48) = 0.18427642654225751;
        A(19, 49) = -0.15068781571859141;
        A(19, 50) = 0.0081812912351393891;
        A(19, 51) = 0.12857871661751022;
        A(19, 52) = -0.12719427440789194;
        A(19, 53) = 0.056577138083497819;
        A(19, 54) = 0.0282889064942701;
        A(19, 55) = 0.068339137170332687;
        A(19, 56) = -0.012215489714436756;
        A(19, 57) = 0.15133172413879961;
        A(19, 58) = 0.063268460953804728;
        A(19, 59) = 0.050483112234914695;
        A(19, 60) = 0.03855766935492682;
        A(19, 61) = 0.13902898413469106;
        A(19, 62) = 0.044873646982925841;
        A(19, 63) = 0.086178636262116387;
        A(19, 64) = -0.034639005923946316;
        A(19, 65) = 0.15160323619363936;
        A(19, 66) = 0.0010404053734367202;
        A(19, 67) = -0.020360610141279385;
        A(19, 68) = 0.054632729387277708;
        A(19, 69) = -0.012062124158040545;
        A(19, 70) = 0.066827919753065207;
        A(19, 71) = -0.00076508473014801417;
        A(19, 72) = -0.088452929670744335;
        A(19, 73) = 0.037340572224938626;
        A(19, 74) = 0.10203688466437733;
        A(19, 75) = -0.032862289027503842;
        A(19, 76) = -0.17854007409334108;
        A(19, 77) = -0.041118999600520859;
        A(19, 78) = -0.058147806218699874;
        A(19, 79) = -0.0097975549224439823;
        A(19, 80) = -0.012837159685705165;
        A(19, 81) = -0.093589788616930222;
        A(19, 82) = 0.052067004440009806;
        A(19, 83) = -0.13574576528527046;
        A(19, 84) = 0.06813310865942325;
        A(19, 85) = 0.082307353430632169;
        A(19, 86) = 0.14150590207633884;
        A(19, 87) = 0.098082585895206631;
        A(19, 88) = 0.10348454951209662;
        A(19, 89) = -0.0031711423212567036;
        A(19, 90) = -0.084022670754070744;
        A(19, 91) = -0.11670813604682023;
        A(19, 92) = 0.02614457447762665;
        A(19, 93) = 0.084464162440369986;
        A(19, 94) = -0.10045100963862064;
        A(19, 95) = 0.17861547720214122;
        A(19, 96) = -0.11026774527528019;
        A(19, 97) = 0.089405727219050962;
        A(19, 98) = -0.070909034390589099;
        A(19, 99) = 0.035893152994486532;
        A(19, 100) = 0.19173730534362313;
        A(19, 101) = -0.031257560557195724;
        A(19, 102) = -0.061405958314109194;
        A(19, 103) = 0.13312633031573923;
        A(19, 104) = -0.0224519595585249;
        A(19, 105) = -0.00034850605331635844;
        A(19, 106) = -0.050766315087395417;
        A(19, 107) = -0.024675551859426947;
        A(19, 108) = -0.055092490696876412;
        A(19, 109) = 0.1055586025907476;
        A(19, 110) = -0.077452569184895043;
        A(19, 111) = 0.11419318855669057;
        A(19, 112) = -0.16394508275076264;
        A(19, 113) = 0.051211690141204663;
        A(19, 114) = 0.011671559759139976;
        A(19, 115) = 0.024767640596132418;
        A(19, 116) = -0.0098667479839271328;
        A(19, 117) = -0.048113144511647284;
        A(19, 118) = 0.063237224542686432;
        A(19, 119) = 0.12672725085282727;
        A(19, 120) = -0.14598924363146709;
        A(19, 121) = 0.073016648837853484;
        A(19, 122) = 0.050085875209774769;
        A(19, 123) = -0.12708469004047343;
        A(19, 124) = -0.14069132319931221;
        A(19, 125) = 0.094845632445825417;
        A(19, 126) = 0.1641465593428193;
        A(19, 127) = -0.058842369896269432;
        A(20, 0) = -0.17413553016695532;
        A(20, 1) = -0.003271823520150402;
        A(20, 2) = 0.020695103383724527;
        A(20, 3) = -0.0090367671152584931;
        A(20, 4) = -0.0079475014370229691;
        A(20, 5) = 0.027104070585674996;
        A(20, 6) = 0.012373054447880734;
        A(20, 7) = -0.011682758603084892;
        A(20, 8) = 0.0067119502078946455;
        A(20, 9) = -0.027642284666939423;
        A(20, 10) = 0.1567537834941802;
        A(20, 11) = -0.12957384658528426;
        A(20, 12) = 0.13405324136290722;
        A(20, 13) = -0.09784428481972704;
        A(20, 14) = -0.15196743043857494;
        A(20, 15) = -0.067819429064654255;
        A(20, 16) = 0.056405476894390093;
        A(20, 17) = 0.16487093334395325;
        A(20, 18) = -0.059073872712985462;
        A(20, 19) = -0.032039289055725395;
        A(20, 20) = -0.11524623957217656;
        A(20, 21) = 0.078511446922656103;
        A(20, 22) = 0.067758983825641925;
        A(20, 23) = -0.061204698944567273;
        A(20, 24) = -0.022684709975800472;
        A(20, 25) = 0.088316469745518766;
        A(20, 26) = -0.067223385025296761;
        A(20, 27) = 0.10058038775179241;
        A(20, 28) = 0.014757144725353367;
        A(20, 29) = -0.036872627058440147;
        A(20, 30) = -0.079233360906509565;
        A(20, 31) = 0.071597842078343743;
        A(20, 32) = -0.013919685430784014;
        A(20, 33) = -0.069920547650819273;
        A(20, 34) = 0.047294022978316974;
        A(20, 35) = -0.04439474462906106;
        A(20, 36) = -0.077681412830704552;
        A(20, 37) = 0.093016852142836878;
        A(20, 38) = 0.13316457508875584;
        A(20, 39) = -0.049735727347370716;
        A(20, 40) = -0.0033707356544424097;
        A(20, 41) = -0.088534468774144781;
        A(20, 42) = 0.18869904028652323;
        A(20, 43) = 0.13935164760909691;
        A(20, 44) = 0.13581731705978112;
        A(20, 45) = 0.067510629670338454;
        A(20, 46) = 0.1213731725584354;
        A(20, 47) = 0.047437390012419575;
        A(20, 48) = -0.15027449969764317;
        A(20, 49) = -0.077069449412008356;
        A(20, 50) = 0.063487150277469789;
        A(20, 51) = -0.020937899866832574;
        A(20, 52) = -0.010368256477445104;
        A(20, 53) = 0.0080825262614539414;
        A(20, 54) = 0.15396839967949486;
        A(20, 55) = -0.070341272763650653;
        A(20, 56) = 0.063465057466361052;
        A(20, 57) = 0.28081128983677006;
        A(20, 58) = 0.033520328708392985;
        A(20, 59) = 0.016433239239816398;
        A(20, 60) = -0.078891800890182107;
        A(20, 61) = 0.013696594211484912;
        A(20, 62) = 0.10549890973956383;
        A(20, 63) = 0.18427457874816666;
        A(20, 64) = -0.094007412491242781;
        A(20, 65) = 0.025992401325410114;
        A(20, 66) = -0.10536510837355795;
        A(20, 67) = 0.12537336318768885;
        A(20, 68) = -0.07670523733944884;
        A(20, 69) = -0.013325637635495581;
        A(20, 70) = 0.0039652722930371594;
        A(20, 71) = -0.010271722826730487;
        A(20, 72) = 0.11188256946206597;
        A(20, 73) = -0.015748791416860267;
        A(20, 74) = 0.090894016168204472;
        A(20, 75) = 0.0011708677357251326;
        A(20, 76) = 0.040802725437012598;
        A(20, 77) = -0.051532104683628642;
        A(20, 78) = -0.0044530230901178372;
        A(20, 79) = 0.0049342459634241602;
        A(20, 80) = 0.081644898896581414;
        A(20, 81) = -0.053471788231700235;
        A(20, 82) = -0.089446317179595919;
        A(20, 83) = 0.025289976254566169;
        A(20, 84) = 0.031205293463769913;
        A(20, 85) = -0.045971340417420223;
        A(20, 86) = -0.18922243549158624;
        A(20, 87) = -0.03416108460650228;
        A(20, 88) = 0.048491169087636996;
        A(20, 89) = 0.033311036186333833;
        A(20, 90) = 0.16755570049278323;
        A(20, 91) = -0.0035283616417004816;
        A(20, 92) = 0.061497050136261125;
        A(20, 93) = -0.016281026073257675;
        A(20, 94) = -0.069511180359870764;
        A(20, 95) = 0.14750074395818433;
        A(20, 96) = -0.14553805191113275;
        A(20, 97) = -0.015154379134093655;
        A(20, 98) = -0.026189587305910658;
        A(20, 99) = -0.13131877491673671;
        A(20, 100) = -0.020536324060685777;
        A(20, 101) = 0.028023111004049448;
        A(20, 102) = 0.068059398283777564;
        A(20, 103) = 0.0064343830660972962;
        A(20, 104) = 0.19174885379382531;
        A(20, 105) = 0.1067959267765087;
        A(20, 106) = 0.001629573378056276;
        A(20, 107) = 0.19931246049256821;
        A(20, 108) = 0.1630225053135759;
        A(20, 109) = -0.00027623966628071567;
        A(20, 110) = 0.019399228743548349;
        A(20, 111) = -0.038012221436577349;
        A(20, 112) = -0.032239333326597376;
        A(20, 113) = -0.058367334643870783;
        A(20, 114) = -0.034611156466859749;
        A(20, 115) = 0.035722383965940373;
        A(20, 116) = 0.082456204320041748;
        A(20, 117) = -0.015212643124775591;
        A(20, 118) = 0.14266556631150928;
        A(20, 119) = -0.049770115600215464;
        A(20, 120) = -0.016611138862026691;
        A(20, 121) = -0.063254382181372165;
        A(20, 122) = -0.0076210154461163835;
        A(20, 123) = -0.066026677957696456;
        A(20, 124) = -0.033568356320889683;
        A(20, 125) = -0.042733350964217875;
        A(20, 126) = 0.16465046582985976;
        A(20, 127) = 0.045295040248616719;
        A(21, 0) = -0.032534056314289801;
        A(21, 1) = -0.0074270584516257024;
        A(21, 2) = -0.057934964356262039;
        A(21, 3) = 0.017709319430670528;
        A(21, 4) = -0.033013984653783815;
        A(21, 5) = 0.099549241249599629;
        A(21, 6) = -0.075850968258978135;
        A(21, 7) = -0.062872065636022309;
        A(21, 8) = 0.04592508042529244;
        A(21, 9) = -0.078898192028654557;
        A(21, 10) = -0.0260384529540716;
        A(21, 11) = 0.0094415019516165266;
        A(21, 12) = -0.14176888263594539;
        A(21, 13) = 0.030680224753564134;
        A(21, 14) = -0.15619746335839496;
        A(21, 15) = -0.040378309344327519;
        A(21, 16) = -0.077422734879166677;
        A(21, 17) = -0.016851045061259607;
        A(21, 18) = -0.029226631711892749;
        A(21, 19) = 0.14008871656562125;
        A(21, 20) = -0.025342801452587698;
        A(21, 21) = 0.0091739081992930852;
        A(21, 22) = 0.058392870771971465;
        A(21, 23) = -0.077848298480460515;
        A(21, 24) = -0.089094488020705798;
        A(21, 25) = 0.10922214305769136;
        A(21, 26) = 0.15758704958341052;
        A(21, 27) = 0.024744742547092427;
        A(21, 28) = 0.041698370078341367;
        A(21, 29) = -0.19267009736112695;
        A(21, 30) = -0.013841175269572376;
        A(21, 31) = 0.02621567327339263;
        A(21, 32) = 0.05253877834638887;
        A(21, 33) = -0.030300170676587749;
        A(21, 34) = -0.106738431374387;
        A(21, 35) = 0.02070131111104366;
        A(21, 36) = -0.036305634514212246;
        A(21, 37) = -0.069536207515587908;
        A(21, 38) = -0.18093363078131602;
        A(21, 39) = -0.041216231643201595;
        A(21, 40) = -0.038562897253080743;
        A(21, 41) = 0.051384698867886797;
        A(21, 42) = -0.04657945386930705;
        A(21, 43) = -0.083634837137128243;
        A(21, 44) = 0.077030922796387333;
        A(21, 45) = -0.040431244903845101;
        A(21, 46) = -0.13568555382469072;
        A(21, 47) = 0.11169421577007907;
        A(21, 48) = 0.055540382280806114;
        A(21, 49) = -0.10033568895328146;
        A(21, 50) = -0.093632767234408998;
        A(21, 51) = 0.043217540377093716;
        A(21, 52) = -0.062204228988429283;
        A(21, 53) = 0.010259836550734494;
        A(21, 54) = -0.028298660066451882;
        A(21, 55) = 0.039644973353629501;
        A(21, 56) = 0.022835753548434534;
        A(21, 57) = -0.091075617246802562;
        A(21, 58) = -0.024348439373109564;
        A(21, 59) = 0.051265149538690019;
        A(21, 60) = -0.074871456036303408;
        A(21, 61) = 0.12127765924288034;
        A(21, 62) = -0.036481132800177132;
        A(21, 63) = -0.032188327166262666;
        A(21, 64) = 0.043731516471189759;
        A(21, 65) = 0.0087685973186059293;
        A(21, 66) = 0.031690264526759958;
        A(21, 67) = 0.028751288957250487;
        A(21, 68) = 0.067760007878439291;
        A(21, 69) = -0.069557520916553622;
        A(21, 70) = -0.037988840830913986;
        A(21, 71) = 0.026996478064783239;
        A(21, 72) = 0.15807520883763976;
        A(21, 73) = 0.062810557940857173;
        A(21, 74) = -0.18652250834961925;
        A(21, 75) = -0.30764850575379882;
        A(21, 76) = 0.038817918105245701;
        A(21, 77) = -0.083467607538049715;
        A(21, 78) = -0.1234385982221298;
        A(21, 79) = 0.049921282813632714;
        A(21, 80) = 0.036327363187089901;
        A(21, 81) = 0.0020622730459131933;
        A(21, 82) = -0.049239933119751472;
        A(21, 83) = 0.075438462396855685;
        A(21, 84) = 0.091570700259587828;
        A(21, 85) = 0.17941019938159261;
        A(21, 86) = -0.0013682321363285566;
        A(21, 87) = -0.017619208297914538;
        A(21, 88) = 0.046666650904948329;
        A(21, 89) = 0.0081705674076905446;
        A(21, 90) = 0.20470703428620915;
        A(21, 91) = -0.005254104053088765;
        A(21, 92) = -0.10191682003129485;
        A(21, 93) = -0.051665705577652959;
        A(21, 94) = -0.16495244070720527;
        A(21, 95) = -0.08088557863113105;
        A(21, 96) = 0.096702531243516979;
        A(21, 97) = -0.033713277377601124;
        A(21, 98) = 0.047927004393113676;
        A(21, 99) = 0.052592513406678178;
        A(21, 100) = -0.031689982946007438;
        A(21, 101) = 0.097330132013481063;
        A(21, 102) = 0.007376908976427482;
        A(21, 103) = 0.062823573499393867;
        A(21, 104) = 0.097547946238032909;
        A(21, 105) = 0.18509658463076289;
        A(21, 106) = -0.089353615331762004;
        A(21, 107) = 0.21413577639288967;
        A(21, 108) = 0.070562052175179385;
        A(21, 109) = 0.056580366926454108;
        A(21, 110) = 0.0026589772355597105;
        A(21, 111) = 0.10358127325285432;
        A(21, 112) = -0.16925897239109339;
        A(21, 113) = 0.18556667270968938;
        A(21, 114) = -0.0840931944963971;
        A(21, 115) = -0.075509985975604835;
        A(21, 116) = 0.041995629836892229;
        A(21, 117) = 0.0508519389316325;
        A(21, 118) = -0.13221651642417201;
        A(21, 119) = 0.032552082467978208;
        A(21, 120) = -0.0041915406715881606;
        A(21, 121) = -0.048734156742050332;
        A(21, 122) = 0.056110674004881012;
        A(21, 123) = 0.10619418277767463;
        A(21, 124) = -0.01695208906115676;
        A(21, 125) = -0.065796120716888951;
        A(21, 126) = -0.01035096373954799;
        A(21, 127) = -0.12446170311963786;
        A(22, 0) = 0.092389302123538672;
        A(22, 1) = -0.026790757692591233;
        A(22, 2) = -0.045270204293510558;
        A(22, 3) = -0.067774397154026264;
        A(22, 4) = -0.08215948274728975;
        A(22, 5) = 0.049863921251987013;
        A(22, 6) = 0.1190829486916854;
        A(22, 7) = -0.064151752474198562;
        A(22, 8) = -0.14802304139326108;
        A(22, 9) = -0.0075460373619848781;
        A(22, 10) = 0.075889598049425341;
        A(22, 11) = 0.13617915290044233;
        A(22, 12) = 0.038493037643514694;
        A(22, 13) = 0.14661212737799165;
        A(22, 14) = -0.075194971212981424;
        A(22, 15) = -0.064160864090183622;
        A(22, 16) = 0.059925586011832233;
        A(22, 17) = 0.031276529999950925;
        A(22, 18) = -0.12027259887036053;
        A(22, 19) = 0.052117723928809132;
        A(22, 20) = 0.018530882427365544;
        A(22, 21) = -0.087435878848264093;
        A(22, 22) = 0.023076927658835643;
        A(22, 23) = 0.014845602494446167;
        A(22, 24) = 0.010888117268303445;
        A(22, 25) = -0.09586596512614648;
        A(22, 26) = -0.066230764335838188;
        A(22, 27) = -0.031830123715770521;
        A(22, 28) = 0.042161417346191332;
        A(22, 29) = -0.052729402938072115;
        A(22, 30) = 0.12480668310723644;
        A(22, 31) = 0.14073158388970364;
        A(22, 32) = 0.02192264795304967;
        A(22, 33) = -0.042774093149523254;
        A(22, 34) = 0.0098004036773913748;
        A(22, 35) = 0.044977241386737477;
        A(22, 36) = -0.010047685626103902;
        A(22, 37) = 0.01291168103797008;
        A(22, 38) = 0.048118308584614453;
        A(22, 39) = 0.12248905652604716;
        A(22, 40) = -0.07910380911150465;
        A(22, 41) = -0.18610270687835562;
        A(22, 42) = 0.093621035134265451;
        A(22, 43) = 0.021875406383306317;
        A(22, 44) = -0.10945881118572699;
        A(22, 45) = 0.037994406695549626;
        A(22, 46) = 0.091658190886187194;
        A(22, 47) = -0.06147213544960399;
        A(22, 48) = -0.051759917056425644;
        A(22, 49) = 0.042132754745413101;
        A(22, 50) = 0.16170762697561541;
        A(22, 51) = -0.14850610347081727;
        A(22, 52) = -0.12399454872104582;
        A(22, 53) = -0.052173307701804221;
        A(22, 54) = 0.11556056563558252;
        A(22, 55) = 0.10547968041253403;
        A(22, 56) = 0.023971533027010709;
        A(22, 57) = -0.15793761132220158;
        A(22, 58) = -0.013478452595720385;
        A(22, 59) = -0.212470143737436;
        A(22, 60) = -0.05377408123444638;
        A(22, 61) = -0.052438161459497243;
        A(22, 62) = 0.096024319496085378;
        A(22, 63) = -0.024599076547295696;
        A(22, 64) = -0.036894451273312812;
        A(22, 65) = -0.061651143483028331;
        A(22, 66) = -0.061139299475088282;
        A(22, 67) = -0.021001550644510796;
        A(22, 68) = -0.0018331391375003975;
        A(22, 69) = -0.081813722290684593;
        A(22, 70) = 0.20581376275317706;
        A(22, 71) = 0.052680684907435327;
        A(22, 72) = 0.060659173615138187;
        A(22, 73) = 0.13696918515616105;
        A(22, 74) = 0.053298849565619887;
        A(22, 75) = -0.11911499087744552;
        A(22, 76) = 0.070508586322762273;
        A(22, 77) = 0.070174086888828341;
        A(22, 78) = 0.059196377981095276;
        A(22, 79) = 0.11240291432898462;
        A(22, 80) = 0.056059195580870219;
        A(22, 81) = -0.04308050875883454;
        A(22, 82) = -0.030497916266950253;
        A(22, 83) = -0.028886552483172165;
        A(22, 84) = -0.13245811746651581;
        A(22, 85) = -0.063050667398601865;
        A(22, 86) = 0.047441718332951952;
        A(22, 87) = 0.076740330308510407;
        A(22, 88) = 0.063606036108160749;
        A(22, 89) = -0.063052909610855079;
        A(22, 90) = 0.08163221432830424;
        A(22, 91) = 0.022369166813185324;
        A(22, 92) = 0.1829980560934335;
        A(22, 93) = 0.064803548857838067;
        A(22, 94) = -0.070365962290401735;
        A(22, 95) = -0.23235697802324937;
        A(22, 96) = -0.043655949607148581;
        A(22, 97) = 0.18057077356450801;
        A(22, 98) = 0.13316367051216163;
        A(22, 99) = 0.14752526006840919;
        A(22, 100) = 0.10207135281818165;
        A(22, 101) = -0.10561906949529173;
        A(22, 102) = -0.02412657648170511;
        A(22, 103) = -0.042569286201351267;
        A(22, 104) = 0.030570139494857061;
        A(22, 105) = 0.0097427571933694362;
        A(22, 106) = -0.083661638809141695;
        A(22, 107) = 0.098640492582001263;
        A(22, 108) = -0.1864478249240713;
        A(22, 109) = -0.053986564720332364;
        A(22, 110) = 0.014627549761721231;
        A(22, 111) = -0.030303768603441063;
        A(22, 112) = -0.0787946360310567;
        A(22, 113) = 0.046552834775057034;
        A(22, 114) = -0.0056820411212674879;
        A(22, 115) = -0.20379706627846789;
        A(22, 116) = 0.0042128594903125885;
        A(22, 117) = 0.087644404884244687;
        A(22, 118) = 0.052890505379382488;
        A(22, 119) = -0.028064792587796906;
        A(22, 120) = 0.092281892592583778;
        A(22, 121) = -0.022824273015497845;
        A(22, 122) = -0.03188743243788688;
        A(22, 123) = -0.067387980194639568;
        A(22, 124) = -0.054307137435821225;
        A(22, 125) = -0.060780793481316243;
        A(22, 126) = -0.034438277412651389;
        A(22, 127) = -0.00031383799507804511;
        A(23, 0) = 0.080300463205160488;
        A(23, 1) = 0.037509803804267376;
        A(23, 2) = 0.037590438978647153;
        A(23, 3) = -0.033233553638864606;
        A(23, 4) = 0.085677539305475073;
        A(23, 5) = -0.016719941106148994;
        A(23, 6) = -0.20876230584313146;
        A(23, 7) = 0.1199229670025157;
        A(23, 8) = 0.075699030646227322;
        A(23, 9) = 0.058015670305461904;
        A(23, 10) = 0.017244440628453477;
        A(23, 11) = -0.14137290315845932;
        A(23, 12) = -0.042022698268167298;
        A(23, 13) = 0.011316754736251523;
        A(23, 14) = 0.13428301129059483;
        A(23, 15) = -0.011847632514678897;
        A(23, 16) = 0.022818506795210844;
        A(23, 17) = -0.056668584448559461;
        A(23, 18) = 0.037500732275557558;
        A(23, 19) = 0.1587559502419631;
        A(23, 20) = 0.027266280175085814;
        A(23, 21) = -0.043310219322513499;
        A(23, 22) = 0.13904349648820075;
        A(23, 23) = -0.092495533593468335;
        A(23, 24) = 0.049418422786601995;
        A(23, 25) = 0.010996130778632665;
        A(23, 26) = -0.041090888416790039;
        A(23, 27) = 0.057726613377818092;
        A(23, 28) = -0.11934983573531217;
        A(23, 29) = 0.013908410557130272;
        A(23, 30) = 0.10977472547316669;
        A(23, 31) = 0.061152696159338715;
        A(23, 32) = -0.14316345209542314;
        A(23, 33) = 0.016538808394869459;
        A(23, 34) = -0.057786613223020332;
        A(23, 35) = 0.15768393274734271;
        A(23, 36) = -0.093296248995787645;
        A(23, 37) = -0.069108894705050647;
        A(23, 38) = 0.013243660055008856;
        A(23, 39) = 0.089677079340938881;
        A(23, 40) = -0.097195943944896612;
        A(23, 41) = -0.0090601433897893133;
        A(23, 42) = -0.016122934115638921;
        A(23, 43) = 0.041324179638920502;
        A(23, 44) = -0.10375705843392716;
        A(23, 45) = 0.023083257424043824;
        A(23, 46) = 0.14802009468892155;
        A(23, 47) = 0.19315146811460979;
        A(23, 48) = -0.099812715355721379;
        A(23, 49) = -0.075778814256086277;
        A(23, 50) = 0.096043891778091084;
        A(23, 51) = -0.18908911701631381;
        A(23, 52) = -0.06877175525971202;
        A(23, 53) = 0.14586466032440065;
        A(23, 54) = -0.2513329468386859;
        A(23, 55) = 0.072257129959813371;
        A(23, 56) = -0.026570697344044363;
        A(23, 57) = 0.014504106956547858;
        A(23, 58) = -0.10812657691202204;
        A(23, 59) = 0.064240076707794469;
        A(23, 60) = 0.048381479801186747;
        A(23, 61) = -0.054194066493052973;
        A(23, 62) = -0.013820954532602049;
        A(23, 63) = 0.1249724222359872;
        A(23, 64) = 0.038517618584049819;
        A(23, 65) = -0.080281598404398996;
        A(23, 66) = -0.069960204462412148;
        A(23, 67) = 0.005249541923883598;
        A(23, 68) = -0.089636506807517599;
        A(23, 69) = 0.10844648369517673;
        A(23, 70) = 0.06197565402685809;
        A(23, 71) = -0.18097722505411165;
        A(23, 72) = 0.054409264646273429;
        A(23, 73) = -0.10398067296698471;
        A(23, 74) = -0.10611976903946027;
        A(23, 75) = -0.055118615273356271;
        A(23, 76) = -0.017523574901011793;
        A(23, 77) = 0.13065710862212793;
        A(23, 78) = -0.058065452859859756;
        A(23, 79) = -0.089908980098688557;
        A(23, 80) = 0.056801997526261666;
        A(23, 81) = -0.035704100679574864;
        A(23, 82) = 0.011196240500663507;
        A(23, 83) = 0.10455206252307729;
        A(23, 84) = 0.057125489112752358;
        A(23, 85) = 0.070693534683989603;
        A(23, 86) = 0.043806043741696193;
        A(23, 87) = 0.029709598561400326;
        A(23, 88) = -0.099953474369994633;
        A(23, 89) = -0.05546901951012255;
        A(23, 90) = 0.1096891283033132;
        A(23, 91) = -0.048220423704721613;
        A(23, 92) = -0.17674442095135517;
        A(23, 93) = 0.12901465405664841;
        A(23, 94) = 0.068844018676586183;
        A(23, 95) = 0.10194825322383466;
        A(23, 96) = -0.052854421653747118;
        A(23, 97) = 0.020128879553269346;
        A(23, 98) = 0.013152638476261334;
        A(23, 99) = 0.13838844117005344;
        A(23, 100) = 0.038530823621865121;
        A(23, 101) = -0.045767183059611478;
        A(23, 102) = -0.075853755358401331;
        A(23, 103) = -0.013678796594376178;
        A(23, 104) = 0.088412592450707497;
        A(23, 105) = -0.0094041273210123868;
        A(23, 106) = 0.0095126851369580073;
        A(23, 107) = 0.063585588901350104;
        A(23, 108) = -0.035450117204359907;
        A(23, 109) = 0.12444479408886507;
        A(23, 110) = -0.063149284768713787;
        A(23, 111) = 0.052430561337133252;
        A(23, 112) = 0.0083667584435622895;
        A(23, 113) = -0.02298760794434411;
        A(23, 114) = 0.042656011500066399;
        A(23, 115) = -0.094140882587490385;
        A(23, 116) = -0.0098472882488018915;
        A(23, 117) = -0.13884220447326184;
        A(23, 118) = 0.10166521533731057;
        A(23, 119) = -0.11263634484359186;
        A(23, 120) = 0.11982943322598469;
        A(23, 121) = 0.089876340568873711;
        A(23, 122) = -0.15935568591407223;
        A(23, 123) = -0.074660265428135308;
        A(23, 124) = 0.096982531004979389;
        A(23, 125) = 0.043401495946791296;
        A(23, 126) = -0.024407830511677095;
        A(23, 127) = 0.02482954284040961;
        A(24, 0) = 0.11603578770205314;
        A(24, 1) = -0.031733229248347213;
        A(24, 2) = -0.0060148933783814307;
        A(24, 3) = 0.10424361141360723;
        A(24, 4) = -0.021193105148573081;
        A(24, 5) = 0.029093336821564224;
        A(24, 6) = -0.04615296687143098;
        A(24, 7) = -0.038904228904529076;
        A(24, 8) = -0.017425108221982066;
        A(24, 9) = -0.14751115719914695;
        A(24, 10) = -0.01062405275642239;
        A(24, 11) = 0.022963738335959088;
        A(24, 12) = -0.012805904398142524;
        A(24, 13) = 0.24218482946715392;
        A(24, 14) = 0.071223301570033593;
        A(24, 15) = 0.039211161476701922;
        A(24, 16) = -0.060410860753186468;
        A(24, 17) = -0.042260766511490327;
        A(24, 18) = 0.084867289867660747;
        A(24, 19) = -0.055431958641736633;
        A(24, 20) = 0.056973210747339062;
        A(24, 21) = 0.10538895750057664;
        A(24, 22) = -0.10446950931947993;
        A(24, 23) = -0.037804169617502506;
        A(24, 24) = 0.036398205979394013;
        A(24, 25) = -0.12843743303695004;
        A(24, 26) = 0.037143226778210671;
        A(24, 27) = 0.068333535671324233;
        A(24, 28) = -0.078902171742928393;
        A(24, 29) = -0.074480333373686758;
        A(24, 30) = -0.018246243633402201;
        A(24, 31) = -0.014973784650505584;
        A(24, 32) = -0.11471437744468788;
        A(24, 33) = -0.012590134251335344;
        A(24, 34) = 0.012916061462471071;
        A(24, 35) = 0.12115994422430768;
        A(24, 36) = -0.018469877938489344;
        A(24, 37) = -0.076679959991903315;
        A(24, 38) = -0.033561507671163636;
        A(24, 39) = 0.00018047371627395725;
        A(24, 40) = 0.045704315560268494;
        A(24, 41) = -0.19937064506558239;
        A(24, 42) = -0.07952231849955288;
        A(24, 43) = -0.0085217106742366405;
        A(24, 44) = 0.074867687149167556;
        A(24, 45) = 0.096467374694743799;
        A(24, 46) = -0.058775199976623151;
        A(24, 47) = 0.052974356334153171;
        A(24, 48) = 0.093971273701096883;
        A(24, 49) = -0.055077039943104034;
        A(24, 50) = -0.044346315670880022;
        A(24, 51) = -0.13211120215182751;
        A(24, 52) = -0.11225661873610505;
        A(24, 53) = 0.058789762898032109;
        A(24, 54) = -0.058456300103392304;
        A(24, 55) = -0.054520035783023779;
        A(24, 56) = -0.021745464787888504;
        A(24, 57) = 0.035822368728094189;
        A(24, 58) = 0.086691615465802271;
        A(24, 59) = 0.040639904294457359;
        A(24, 60) = 0.076946064181026258;
        A(24, 61) = -0.097167096806855952;
        A(24, 62) = 0.11992487465816619;
        A(24, 63) = 0.012840579068887404;
        A(24, 64) = -0.020420952576897418;
        A(24, 65) = -0.12382704479487351;
        A(24, 66) = -0.079333358817861674;
        A(24, 67) = 0.025287487892613605;
        A(24, 68) = 0.089441986133140389;
        A(24, 69) = -0.15335653289058071;
        A(24, 70) = 0.007261249136353707;
        A(24, 71) = 0.15872890573151127;
        A(24, 72) = -0.023905938286952415;
        A(24, 73) = -0.031949218899182286;
        A(24, 74) = 0.0029693707302244285;
        A(24, 75) = 0.076775734495864917;
        A(24, 76) = 0.072495232121849607;
        A(24, 77) = -0.02626243155665426;
        A(24, 78) = -0.043065574766248248;
        A(24, 79) = -0.009678079135356385;
        A(24, 80) = 0.0093234458985211408;
        A(24, 81) = 0.10618962577667762;
        A(24, 82) = -0.16641828673727471;
        A(24, 83) = -0.02907926244947194;
        A(24, 84) = 0.079384017587438571;
        A(24, 85) = -0.13925994511625137;
        A(24, 86) = 0.14837333180736434;
        A(24, 87) = -0.00097954926775924156;
        A(24, 88) = 0.063274535241472099;
        A(24, 89) = 0.081476094224553319;
        A(24, 90) = 0.10386174864540837;
        A(24, 91) = 0.059248143073407658;
        A(24, 92) = 0.022596641488841683;
        A(24, 93) = -0.18430006012018513;
        A(24, 94) = -0.13502029239837787;
        A(24, 95) = 0.017298098841872091;
        A(24, 96) = 0.12009127986457507;
        A(24, 97) = -0.10560315756846159;
        A(24, 98) = -0.18367581569766891;
        A(24, 99) = -0.13546308212505404;
        A(24, 100) = 0.14217248272128569;
        A(24, 101) = -0.14574736806470012;
        A(24, 102) = 0.044014679844743138;
        A(24, 103) = -0.093731382249361811;
        A(24, 104) = 0.16239840597214833;
        A(24, 105) = -0.0065765147504469323;
        A(24, 106) = 0.28126213209003514;
        A(24, 107) = -0.056791206243306094;
        A(24, 108) = 0.035380621683946234;
        A(24, 109) = -0.16973004960609939;
        A(24, 110) = -0.075831138703154777;
        A(24, 111) = 0.047908504633380852;
        A(24, 112) = -0.04541554641809116;
        A(24, 113) = 0.042001936671825758;
        A(24, 114) = 0.010391241233952801;
        A(24, 115) = -0.0027207419775296983;
        A(24, 116) = 0.092629975165058109;
        A(24, 117) = -0.070843122736480413;
        A(24, 118) = 0.058067248881966287;
        A(24, 119) = -0.03048498118280641;
        A(24, 120) = 0.045955825242662854;
        A(24, 121) = -0.10540243394340473;
        A(24, 122) = -0.0073301787891844467;
        A(24, 123) = -0.033259112697000985;
        A(24, 124) = 0.067850337322678728;
        A(24, 125) = 0.15940214949250731;
        A(24, 126) = -0.003492618960789378;
        A(24, 127) = -0.011167788275296339;
        A(25, 0) = -0.048266407329006243;
        A(25, 1) = -0.023913480425246388;
        A(25, 2) = 0.098575820736506212;
        A(25, 3) = -0.13624150986514308;
        A(25, 4) = 0.071525388090330891;
        A(25, 5) = 0.055926136360385015;
        A(25, 6) = -0.015077347398621176;
        A(25, 7) = 0.21846031883118747;
        A(25, 8) = 0.014908893008112505;
        A(25, 9) = -0.00025421612805037741;
        A(25, 10) = 0.031303441734914443;
        A(25, 11) = 0.0035363824242750017;
        A(25, 12) = 0.12164212130584287;
        A(25, 13) = 0.14281071118744362;
        A(25, 14) = -0.081383012298283763;
        A(25, 15) = -0.056753553724894212;
        A(25, 16) = 0.002394569545846402;
        A(25, 17) = -0.04369678124049866;
        A(25, 18) = -0.14864848774144357;
        A(25, 19) = 0.026728843794193269;
        A(25, 20) = 0.032294778778399508;
        A(25, 21) = -0.041282090179040248;
        A(25, 22) = -0.02896659554735314;
        A(25, 23) = -0.022866177279540035;
        A(25, 24) = 0.079340991995048418;
        A(25, 25) = -0.1644332285348537;
        A(25, 26) = 0.029430658735457353;
        A(25, 27) = 0.015047942734233856;
        A(25, 28) = -0.062770079323309969;
        A(25, 29) = 0.099108732655570547;
        A(25, 30) = 0.060691935202719621;
        A(25, 31) = 0.047236015801479098;
        A(25, 32) = 0.10360143110122323;
        A(25, 33) = -0.061990801767438562;
        A(25, 34) = -0.06804630840413603;
        A(25, 35) = 0.13643193110341065;
        A(25, 36) = -0.03340920721781819;
        A(25, 37) = -0.079993770869719288;
        A(25, 38) = -0.10641098961774011;
        A(25, 39) = -0.070008997413625013;
        A(25, 40) = -0.04085250413278111;
        A(25, 41) = 0.054987323138954464;
        A(25, 42) = -0.055219311550456229;
        A(25, 43) = 0.15119864462254212;
        A(25, 44) = 0.088826803261239595;
        A(25, 45) = 0.05151857984337347;
        A(25, 46) = -0.0020103785920339073;
        A(25, 47) = -0.19902495660929562;
        A(25, 48) = -0.009910686987172148;
        A(25, 49) = 0.079479794477185284;
        A(25, 50) = -0.13921480883071619;
        A(25, 51) = 0.077291615954280787;
        A(25, 52) = -0.066931204968210201;
        A(25, 53) = -0.14973015695490197;
        A(25, 54) = -0.11403428503855804;
        A(25, 55) = -0.10598001714905511;
        A(25, 56) = 0.079368028755471942;
        A(25, 57) = -0.003176877314691285;
        A(25, 58) = 0.18889947535543966;
        A(25, 59) = 0.065166156574319539;
        A(25, 60) = 0.0038024865658842569;
        A(25, 61) = 0.061590137727706336;
        A(25, 62) = 0.038019562604883775;
        A(25, 63) = 0.018151746767328576;
        A(25, 64) = -0.096362835892390378;
        A(25, 65) = -0.085234284864963691;
        A(25, 66) = -0.048185574361984916;
        A(25, 67) = -0.083746797502790613;
        A(25, 68) = 0.037056606307960191;
        A(25, 69) = 0.083329593860733853;
        A(25, 70) = 0.12667952840325011;
        A(25, 71) = -0.075226356032051286;
        A(25, 72) = -0.088983884707636615;
        A(25, 73) = 0.071953300795067565;
        A(25, 74) = -0.14632397552765747;
        A(25, 75) = 0.042726620310769459;
        A(25, 76) = 0.094618601644187394;
        A(25, 77) = -0.062408909569254628;
        A(25, 78) = 0.052645161690624644;
        A(25, 79) = 0.085701215666458844;
        A(25, 80) = 0.04311470816991797;
        A(25, 81) = 0.040575631974624722;
        A(25, 82) = 0.0094628185528305188;
        A(25, 83) = 0.28625721428184059;
        A(25, 84) = -0.027927758693847657;
        A(25, 85) = -0.064152343862231065;
        A(25, 86) = -0.066163927056645422;
        A(25, 87) = -0.041115551247264653;
        A(25, 88) = -0.044658394605375878;
        A(25, 89) = -0.13338458840069081;
        A(25, 90) = -0.14270807238401559;
        A(25, 91) = -0.09200484935821937;
        A(25, 92) = 0.11534327226959802;
        A(25, 93) = 0.032014926086276874;
        A(25, 94) = -0.11843082282366013;
        A(25, 95) = 0.061319912193736018;
        A(25, 96) = -0.095789815195493566;
        A(25, 97) = -0.034702609638187235;
        A(25, 98) = -0.12767307722054821;
        A(25, 99) = -0.052173786648940297;
        A(25, 100) = -0.049917535379727151;
        A(25, 101) = -0.011237471061613043;
        A(25, 102) = -0.064018955227108251;
        A(25, 103) = -0.1115471212475778;
        A(25, 104) = -0.038215300003129227;
        A(25, 105) = 0.050798518934379769;
        A(25, 106) = -0.05642851911236766;
        A(25, 107) = 0.040965393697401452;
        A(25, 108) = -0.033923228847733224;
        A(25, 109) = 0.21542920718988617;
        A(25, 110) = -0.061806408083025483;
        A(25, 111) = -0.0079994625365543554;
        A(25, 112) = -0.076093209913428661;
        A(25, 113) = 0.085318141311184481;
        A(25, 114) = -0.019829679073092979;
        A(25, 115) = 0.11603692838422192;
        A(25, 116) = 0.065105042919864395;
        A(25, 117) = 0.0066438494037795032;
        A(25, 118) = -0.057101968174982129;
        A(25, 119) = 0.17430804033646402;
        A(25, 120) = 0.077266041979807298;
        A(25, 121) = -0.11390147933042043;
        A(25, 122) = -0.047620167997960594;
        A(25, 123) = -0.019001407093935503;
        A(25, 124) = 0.13252739920517304;
        A(25, 125) = -0.0074989008419786701;
        A(25, 126) = -0.01065445073675764;
        A(25, 127) = 0.029655593815371879;
        A(26, 0) = 0.053087200372449204;
        A(26, 1) = 0.046470251831580829;
        A(26, 2) = -0.032805852515927089;
        A(26, 3) = -0.067743638015199323;
        A(26, 4) = -0.11446053414513914;
        A(26, 5) = 0.050213961459533205;
        A(26, 6) = 0.037003869074576173;
        A(26, 7) = -0.026819576840705323;
        A(26, 8) = 0.12377131621058458;
        A(26, 9) = 0.12645013782279213;
        A(26, 10) = 0.038900302147237893;
        A(26, 11) = -0.10477585896499605;
        A(26, 12) = 0.077164406075302824;
        A(26, 13) = 0.0038417610215065491;
        A(26, 14) = 0.023342510993854385;
        A(26, 15) = 0.10958268090989061;
        A(26, 16) = 0.0094528998678499471;
        A(26, 17) = 0.055405074003774299;
        A(26, 18) = 0.13686955468392883;
        A(26, 19) = -0.010384133496549928;
        A(26, 20) = -0.060664661290164547;
        A(26, 21) = -0.10855509643218872;
        A(26, 22) = -0.066165497346371754;
        A(26, 23) = -0.03288863438620708;
        A(26, 24) = 0.042086857313037872;
        A(26, 25) = 0.061063288335493869;
        A(26, 26) = 0.026486373690131321;
        A(26, 27) = -0.01413977943140686;
        A(26, 28) = -0.0210558490677131;
        A(26, 29) = -0.0048944170762467223;
        A(26, 30) = 0.0019252414286985431;
        A(26, 31) = 0.14482905126386114;
        A(26, 32) = 0.15181774302793286;
        A(26, 33) = 0.10022516507857121;
        A(26, 34) = -0.016475529496676709;
        A(26, 35) = -0.083862603615055681;
        A(26, 36) = 0.073406396204389004;
        A(26, 37) = 0.045636965795003107;
        A(26, 38) = 0.19520766017236538;
        A(26, 39) = 0.031228038350084163;
        A(26, 40) = 0.016498932808366881;
        A(26, 41) = 0.046018472827022185;
        A(26, 42) = -0.048214519366764852;
        A(26, 43) = 0.15705335709080132;
        A(26, 44) = -0.00019877354716703322;
        A(26, 45) = -0.078818802046578831;
        A(26, 46) = -0.1371063189662759;
        A(26, 47) = 0.0065359119463043796;
        A(26, 48) = -0.050672331725023487;
        A(26, 49) = -0.039549619048573049;
        A(26, 50) = -0.11240239920022875;
        A(26, 51) = -0.078142251391175643;
        A(26, 52) = -0.13113221858852553;
        A(26, 53) = 0.025440002292240773;
        A(26, 54) = -0.11026666429054499;
        A(26, 55) = 0.028902083667340817;
        A(26, 56) = 0.0017113223564769464;
        A(26, 57) = -0.16153965904585879;
        A(26, 58) = 0.076011648440845403;
        A(26, 59) = -0.083025019332543998;
        A(26, 60) = -0.16703460778271179;
        A(26, 61) = 0.015428731672097171;
        A(26, 62) = -0.16385833712446987;
        A(26, 63) = -0.020349570862277466;
        A(26, 64) = -0.020615038120152827;
        A(26, 65) = 0.067639394838353128;
        A(26, 66) = -0.0826004478913656;
        A(26, 67) = 0.057640833043489659;
        A(26, 68) = -0.072311257122083805;
        A(26, 69) = 0.020952129225627086;
        A(26, 70) = 0.15181207955697967;
        A(26, 71) = -0.10723393630536072;
        A(26, 72) = 0.10060314747171575;
        A(26, 73) = 0.052759828832155839;
        A(26, 74) = -0.0072774584343960735;
        A(26, 75) = -0.058934011387309318;
        A(26, 76) = -0.055824756149324452;
        A(26, 77) = -0.034553032660629507;
        A(26, 78) = -0.14714904794811726;
        A(26, 79) = -0.084810919524456366;
        A(26, 80) = 0.00081615505208755892;
        A(26, 81) = 0.19342937956008388;
        A(26, 82) = 0.0023696641827920945;
        A(26, 83) = 0.03228628428240872;
        A(26, 84) = 0.0050179767039606159;
        A(26, 85) = -0.066677332832583272;
        A(26, 86) = -0.00020703643893527253;
        A(26, 87) = -0.075723565702812315;
        A(26, 88) = 0.12691849965078189;
        A(26, 89) = 0.08778312123565285;
        A(26, 90) = -0.069478481624528576;
        A(26, 91) = 0.14048900178040846;
        A(26, 92) = 0.0019148049246736978;
        A(26, 93) = -0.0025167352023848857;
        A(26, 94) = 0.030718911858702836;
        A(26, 95) = -0.013588551942746925;
        A(26, 96) = -0.13466404961177963;
        A(26, 97) = -0.16922865797488396;
        A(26, 98) = 0.14471747563899157;
        A(26, 99) = 0.01488978501185045;
        A(26, 100) = -0.029145705657984848;
        A(26, 101) = -0.00082421663912116139;
        A(26, 102) = -0.13967562488689861;
        A(26, 103) = 0.022378547361425118;
        A(26, 104) = 0.0016791771364610348;
        A(26, 105) = -0.081165101845926249;
        A(26, 106) = 0.021021748010782527;
        A(26, 107) = -0.10693908508739458;
        A(26, 108) = 0.025216041454335824;
        A(26, 109) = -0.13524300888706392;
        A(26, 110) = 0.024681350166306314;
        A(26, 111) = -0.037503261012335316;
        A(26, 112) = -0.15363847517067269;
        A(26, 113) = 0.18255979423409049;
        A(26, 114) = 0.14749347308218774;
        A(26, 115) = 0.052080427907978025;
        A(26, 116) = 0.039001405469059683;
        A(26, 117) = 0.059851684962549605;
        A(26, 118) = 0.05564574123670353;
        A(26, 119) = -0.043973575014133487;
        A(26, 120) = 0.014472904260447832;
        A(26, 121) = -0.069270226120983283;
        A(26, 122) = 0.068482981676912885;
        A(26, 123) = 0.049882759617367281;
        A(26, 124) = 0.100146093835174;
        A(26, 125) = 0.21140072525624068;
        A(26, 126) = 0.21679651129617311;
        A(26, 127) = 0.11183384392979842;
        A(27, 0) = 0.09907495857577539;
        A(27, 1) = 0.061678057024906655;
        A(27, 2) = -0.15103883972658075;
        A(27, 3) = -0.010572189979784825;
        A(27, 4) = -0.18664779964880221;
        A(27, 5) = 0.074712579470554291;
        A(27, 6) = -0.11303110821063328;
        A(27, 7) = 0.07348115419946652;
        A(27, 8) = -0.11378260877605234;
        A(27, 9) = 0.032324083977105719;
        A(27, 10) = -0.031816149106267351;
        A(27, 11) = 0.030231012266496771;
        A(27, 12) = -0.015381350854216765;
        A(27, 13) = 0.059413247001182251;
        A(27, 14) = -0.024750052917969681;
        A(27, 15) = 0.10295717346078241;
        A(27, 16) = -0.074563160081535143;
        A(27, 17) = 0.15580320064706607;
        A(27, 18) = 0.14207799191716425;
        A(27, 19) = 0.038428669596265494;
        A(27, 20) = 0.050347840891578954;
        A(27, 21) = -0.020229098049076688;
        A(27, 22) = -0.023137590349507603;
        A(27, 23) = 0.056434824821625075;
        A(27, 24) = -0.032634654531112327;
        A(27, 25) = 0.001009852100776594;
        A(27, 26) = -0.1764443258526226;
        A(27, 27) = -0.052546664671629273;
        A(27, 28) = -0.022835082968475803;
        A(27, 29) = -0.0013939330420406377;
        A(27, 30) = -0.11587280582050935;
        A(27, 31) = -0.015952881329288175;
        A(27, 32) = -0.14576681669739108;
        A(27, 33) = -0.14015180372025288;
        A(27, 34) = -0.0012345585380928595;
        A(27, 35) = 0.14487777448822536;
        A(27, 36) = 0.098741008797386759;
        A(27, 37) = 0.073473801685584456;
        A(27, 38) = 0.11229584900442779;
        A(27, 39) = 0.02816016037849528;
        A(27, 40) = 0.10448430997334818;
        A(27, 41) = 0.020562449878774897;
        A(27, 42) = -0.1037358843291491;
        A(27, 43) = 0.025804431897246335;
        A(27, 44) = 0.063555299603123949;
        A(27, 45) = -0.12745470220426389;
        A(27, 46) = 0.11946724601341657;
        A(27, 47) = -0.081921804306504725;
        A(27, 48) = -0.010096280666524248;
        A(27, 49) = 0.15810365096345044;
        A(27, 50) = -0.050501758191434092;
        A(27, 51) = 0.1210063315715427;
        A(27, 52) = 0.08201064735980268;
        A(27, 53) = -0.086884866201720312;
        A(27, 54) = 0.16706628772238968;
        A(27, 55) = -0.049933939823060838;
        A(27, 56) = -0.017697931665627855;
        A(27, 57) = 0.1136263239423243;
        A(27, 58) = -0.083899782973957199;
        A(27, 59) = -0.12937787618750324;
        A(27, 60) = -0.088977216492582986;
        A(27, 61) = 0.12714660354246476;
        A(27, 62) = -0.028459213617002571;
        A(27, 63) = -0.0086901097165784646;
        A(27, 64) = 0.004130378301660409;
        A(27, 65) = -0.051077355458117868;
        A(27, 66) = 0.029581969151146789;
        A(27, 67) = -0.026903702373539437;
        A(27, 68) = -0.099772761079150785;
        A(27, 69) = 0.032843503979023109;
        A(27, 70) = 0.034397973304738212;
        A(27, 71) = 0.0077635681716033402;
        A(27, 72) = -0.033710275394668629;
        A(27, 73) = -0.13719839697910968;
        A(27, 74) = -0.15691294673673156;
        A(27, 75) = 0.050966330255631825;
        A(27, 76) = 0.11577816465238952;
        A(27, 77) = 0.13418545164263748;
        A(27, 78) = -0.024957021371931301;
        A(27, 79) = -0.06221026241801085;
        A(27, 80) = 0.089031223643809831;
        A(27, 81) = 0.0088073100737445509;
        A(27, 82) = 0.066403201773225062;
        A(27, 83) = -0.1516726903469891;
        A(27, 84) = -0.15059042876215922;
        A(27, 85) = 0.10033772629029809;
        A(27, 86) = -0.046782346953484891;
        A(27, 87) = -0.10421238371843873;
        A(27, 88) = -0.041299903205445167;
        A(27, 89) = 0.042348809982726922;
        A(27, 90) = 0.045193152676351517;
        A(27, 91) = 0.011076897682605905;
        A(27, 92) = -0.10127731923668279;
        A(27, 93) = 0.054796691536947585;
        A(27, 94) = -0.028477008443016198;
        A(27, 95) = -0.058041628719318741;
        A(27, 96) = -0.12438767642716056;
        A(27, 97) = -0.01189534377851742;
        A(27, 98) = 0.062053080117674284;
        A(27, 99) = -0.095137955469923458;
        A(27, 100) = -0.075146247787202469;
        A(27, 101) = -0.1198357317696698;
        A(27, 102) = 0.050704449584968628;
        A(27, 103) = -0.02586894679961925;
        A(27, 104) = 0.047359473845309377;
        A(27, 105) = 0.06054620076319419;
        A(27, 106) = 0.10131304684708016;
        A(27, 107) = 0.11523839067286677;
        A(27, 108) = -0.008710601156835529;
        A(27, 109) = 0.08683193141056296;
        A(27, 110) = -0.18067092387438827;
        A(27, 111) = 0.084727483224426525;
        A(27, 112) = -0.0098513068019378397;
        A(27, 113) = 0.12142977319682191;
        A(27, 114) = -0.087658998830064214;
        A(27, 115) = -0.075001852806019356;
        A(27, 116) = -0.048352483204021329;
        A(27, 117) = -0.048668213616221652;
        A(27, 118) = -0.11952778857938033;
        A(27, 119) = 0.11251981590698253;
        A(27, 120) = 0.04347718470060797;
        A(27, 121) = 0.058670165057435393;
        A(27, 122) = 0.031340957217398241;
        A(27, 123) = 0.019773877225276806;
        A(27, 124) = 0.050027768481250602;
        A(27, 125) = 0.2361402693705732;
        A(27, 126) = -0.049684768855955408;
        A(27, 127) = -0.058578730854581387;
        A(28, 0) = 0.058665436709732524;
        A(28, 1) = 0.0091969639728280862;
        A(28, 2) = 0.16482991605859643;
        A(28, 3) = -0.13517357491841395;
        A(28, 4) = 0.10505248191027219;
        A(28, 5) = 0.091818688032936982;
        A(28, 6) = 0.016330450145935892;
        A(28, 7) = 0.00036978713818740933;
        A(28, 8) = 0.076981069345373951;
        A(28, 9) = -0.12482148107150876;
        A(28, 10) = -0.060791447768995241;
        A(28, 11) = 0.14309428665716228;
        A(28, 12) = 0.13366109499208506;
        A(28, 13) = -0.055480141907547659;
        A(28, 14) = -0.0021991564865521604;
        A(28, 15) = -0.043458756549153377;
        A(28, 16) = -0.046036685932172111;
        A(28, 17) = -0.082293991344055503;
        A(28, 18) = 0.1516344949243088;
        A(28, 19) = -0.04865467614647237;
        A(28, 20) = 0.014678542268803489;
        A(28, 21) = 0.10228530361625873;
        A(28, 22) = 0.079615560391904566;
        A(28, 23) = 0.13252382655784536;
        A(28, 24) = 0.098373733739017727;
        A(28, 25) = -0.19193041816610359;
        A(28, 26) = -0.13270798547029408;
        A(28, 27) = 0.17942363826983937;
        A(28, 28) = 0.022828430397755228;
        A(28, 29) = -0.024814743838276011;
        A(28, 30) = -0.056957079014480237;
        A(28, 31) = -0.041730395573381832;
        A(28, 32) = 0.025415027789188055;
        A(28, 33) = 0.098198361644950299;
        A(28, 34) = -0.11583136420536726;
        A(28, 35) = -0.14457140348202813;
        A(28, 36) = 0.092372602648343946;
        A(28, 37) = -0.19957903157882842;
        A(28, 38) = 0.039271865250202362;
        A(28, 39) = 0.050507174786374065;
        A(28, 40) = 0.14861313868248854;
        A(28, 41) = 0.088155799199601176;
        A(28, 42) = 0.036666366864728364;
        A(28, 43) = 0.16246067080043403;
        A(28, 44) = 0.082036204062951507;
        A(28, 45) = -0.057086035935562912;
        A(28, 46) = 0.10661060745707988;
        A(28, 47) = -0.02795655792037828;
        A(28, 48) = -0.033866145607748421;
        A(28, 49) = 0.021861232264358689;
        A(28, 50) = 0.11376127863644464;
        A(28, 51) = 0.091475999971560029;
        A(28, 52) = 0.099278939646245457;
        A(28, 53) = 0.14788183676521938;
        A(28, 54) = -0.054904232810083303;
        A(28, 55) = -0.085604151562263808;
        A(28, 56) = -0.057496627864593162;
        A(28, 57) = -0.13959300582847461;
        A(28, 58) = 0.028300459401365042;
        A(28, 59) = -0.087821043871215032;
        A(28, 60) = -0.12257972251356827;
        A(28, 61) = 0.11441377514383044;
        A(28, 62) = 0.035263340010537832;
        A(28, 63) = 0.036635306793823867;
        A(28, 64) = 0.13079927660394697;
        A(28, 65) = 0.097343985774924507;
        A(28, 66) = -0.0089334017204673044;
        A(28, 67) = 0.14621561428332489;
        A(28, 68) = 0.034475969474933518;
        A(28, 69) = 0.051956634267945057;
        A(28, 70) = 0.00019941933954992566;
        A(28, 71) = 0.073987911948304286;
        A(28, 72) = 0.046518490578849742;
        A(28, 73) = 0.063061484446046812;
        A(28, 74) = -0.020504577610644864;
        A(28, 75) = -0.086887557447836383;
        A(28, 76) = -0.049420424282305864;
        A(28, 77) = 0.057230924487053678;
        A(28, 78) = 0.078359413481024195;
        A(28, 79) = 0.10901375583677388;
        A(28, 80) = 0.15769438469864017;
        A(28, 81) = 0.08654355289392747;
        A(28, 82) = -0.10825198025451473;
        A(28, 83) = 0.0095608827783965206;
        A(28, 84) = -0.0081634336214225917;
        A(28, 85) = -0.023086719886679867;
        A(28, 86) = 0.015627570971583751;
        A(28, 87) = -0.025992586235309905;
        A(28, 88) = -0.022616756776304342;
        A(28, 89) = -0.11480263999503244;
        A(28, 90) = 0.017435883811344175;
        A(28, 91) = -0.042393569597767175;
        A(28, 92) = -0.046661146959416512;
        A(28, 93) = -0.089643486126079086;
        A(28, 94) = 0.041786572259308458;
        A(28, 95) = 0.10690166888577299;
        A(28, 96) = 0.098295877579668456;
        A(28, 97) = -0.0097398451560981314;
        A(28, 98) = 0.056238186128313841;
        A(28, 99) = 0.10336126154384184;
        A(28, 100) = -0.1510408026058645;
        A(28, 101) = -0.040466324606858103;
        A(28, 102) = 0.15729250509940035;
        A(28, 103) = 0.0070175712504958396;
        A(28, 104) = 0.078694107292074253;
        A(28, 105) = -0.005002101363208819;
        A(28, 106) = 0.090476515188255155;
        A(28, 107) = -0.021290892500304366;
        A(28, 108) = -0.043573046199598217;
        A(28, 109) = -0.032130285014205694;
        A(28, 110) = 0.06975132375666207;
        A(28, 111) = 0.036223184765889989;
        A(28, 112) = -0.11550263364546223;
        A(28, 113) = 0.069755868790412109;
        A(28, 114) = -0.037614284939066218;
        A(28, 115) = 0.011378751381529915;
        A(28, 116) = -0.15464189365655778;
        A(28, 117) = -0.089412397171371699;
        A(28, 118) = -0.02694466246866551;
        A(28, 119) = 0.0091897962161908986;
        A(28, 120) = 0.018363253350553246;
        A(28, 121) = 0.048664857182861294;
        A(28, 122) = -0.064685157779740335;
        A(28, 123) = -0.14716208684699011;
        A(28, 124) = -0.17025228460792918;
        A(28, 125) = -1.1205221312704516e-005;
        A(28, 126) = 0.010117815710481334;
        A(28, 127) = -0.02584723247481889;
        A(29, 0) = 0.031190397193786766;
        A(29, 1) = 0.1969747826995083;
        A(29, 2) = -0.013831564190463322;
        A(29, 3) = 0.0256362144111031;
        A(29, 4) = 0.0047711504206159397;
        A(29, 5) = 0.0046797408784470763;
        A(29, 6) = 0.053811557454119904;
        A(29, 7) = -0.045798405042105812;
        A(29, 8) = -0.17695251827814937;
        A(29, 9) = 0.072912318812560509;
        A(29, 10) = 0.08704416757589932;
        A(29, 11) = -0.11385994285089684;
        A(29, 12) = -0.073670672443319499;
        A(29, 13) = 0.028529241783950627;
        A(29, 14) = 0.024992044861772436;
        A(29, 15) = 0.0021019950835348723;
        A(29, 16) = -0.021165212708235643;
        A(29, 17) = 0.047516156920526756;
        A(29, 18) = 0.17851077512081959;
        A(29, 19) = -0.0052244884568212677;
        A(29, 20) = 0.10107730983696092;
        A(29, 21) = 0.073936215461014143;
        A(29, 22) = 0.051291004954548629;
        A(29, 23) = 0.023300829282733984;
        A(29, 24) = 0.063397233104185574;
        A(29, 25) = -0.058608154163736728;
        A(29, 26) = 0.18899308050969615;
        A(29, 27) = 0.060891943416214657;
        A(29, 28) = -0.14731355088065146;
        A(29, 29) = -0.0087013213729397534;
        A(29, 30) = 0.029963257814910414;
        A(29, 31) = -0.19327662731942613;
        A(29, 32) = 0.09385265576748579;
        A(29, 33) = 0.042518607631488431;
        A(29, 34) = -0.073029568830973488;
        A(29, 35) = 0.047574315056090145;
        A(29, 36) = -0.031691825158647428;
        A(29, 37) = -0.12045462657655392;
        A(29, 38) = -0.13358421661453684;
        A(29, 39) = -0.15020406782237783;
        A(29, 40) = -0.10896192514851923;
        A(29, 41) = 0.019796908836690386;
        A(29, 42) = 0.027284079200183588;
        A(29, 43) = 0.074954802050331448;
        A(29, 44) = 0.044722782351954163;
        A(29, 45) = -0.063738916860772793;
        A(29, 46) = 0.037108983494523934;
        A(29, 47) = -0.034826841917545412;
        A(29, 48) = 0.088006519932067553;
        A(29, 49) = 0.18863290409634043;
        A(29, 50) = 0.13381899693160654;
        A(29, 51) = 0.10372997363493683;
        A(29, 52) = -0.035623676811731141;
        A(29, 53) = -0.044957624697442342;
        A(29, 54) = 0.026602595571867716;
        A(29, 55) = 0.17906223863622969;
        A(29, 56) = -0.019049467336704849;
        A(29, 57) = -0.0041531651553351236;
        A(29, 58) = 0.088493597784522093;
        A(29, 59) = -0.13511226069562476;
        A(29, 60) = 0.025237291921202297;
        A(29, 61) = -0.14809132038988482;
        A(29, 62) = 0.030614477639365329;
        A(29, 63) = 0.11121378182380989;
        A(29, 64) = 0.045791672537105949;
        A(29, 65) = 0.18890334449451748;
        A(29, 66) = -0.053607366815308248;
        A(29, 67) = 0.10045747449749622;
        A(29, 68) = 0.12614844538836723;
        A(29, 69) = -0.066254609803669873;
        A(29, 70) = -0.032838994834408018;
        A(29, 71) = -0.0051040579035558989;
        A(29, 72) = 0.046594988462201559;
        A(29, 73) = -0.042281207384881288;
        A(29, 74) = -0.03237958355854597;
        A(29, 75) = 0.066767775396235421;
        A(29, 76) = 0.088405266564359722;
        A(29, 77) = -0.040788218284210934;
        A(29, 78) = -0.14656723490771617;
        A(29, 79) = 0.070187929035989555;
        A(29, 80) = -0.0092476674127268538;
        A(29, 81) = -0.046903219439632854;
        A(29, 82) = 0.1437250460849919;
        A(29, 83) = 0.055823938892926146;
        A(29, 84) = -0.10148495790772663;
        A(29, 85) = -0.047386236813860678;
        A(29, 86) = 0.068295978731926027;
        A(29, 87) = 0.047359577336594946;
        A(29, 88) = 0.025968529013039025;
        A(29, 89) = 0.18543557695957497;
        A(29, 90) = -0.079649043196951999;
        A(29, 91) = 0.02272793652776485;
        A(29, 92) = -0.010115401398208969;
        A(29, 93) = -0.10398985135861365;
        A(29, 94) = -0.014391410914482337;
        A(29, 95) = 0.063551739371513871;
        A(29, 96) = -0.19108500167910708;
        A(29, 97) = 0.059380649575079901;
        A(29, 98) = -0.06440577635352851;
        A(29, 99) = 0.098772176582187898;
        A(29, 100) = -0.10332355607025423;
        A(29, 101) = 0.018125213226132902;
        A(29, 102) = 0.039382792199563407;
        A(29, 103) = 0.099995438979122983;
        A(29, 104) = -0.12386004849075181;
        A(29, 105) = -0.068902085506261396;
        A(29, 106) = 0.0050481806630096465;
        A(29, 107) = 0.13684879544612588;
        A(29, 108) = 0.069361508247815576;
        A(29, 109) = 0.008963657353908909;
        A(29, 110) = -0.14203806333485752;
        A(29, 111) = 0.045891958751194999;
        A(29, 112) = -0.0091632902805212704;
        A(29, 113) = -0.031907909838113924;
        A(29, 114) = -0.046733903615148162;
        A(29, 115) = -0.076545383289871705;
        A(29, 116) = -0.070373223016448105;
        A(29, 117) = -0.030458939718476487;
        A(29, 118) = 0.031439746574530192;
        A(29, 119) = -0.20132330266597379;
        A(29, 120) = 0.094374515065398665;
        A(29, 121) = -0.088450125048812084;
        A(29, 122) = 0.033598604444834035;
        A(29, 123) = 0.030799108563546677;
        A(29, 124) = 0.0086320824901485252;
        A(29, 125) = -0.09158169025252999;
        A(29, 126) = 0.088398399568703045;
        A(29, 127) = 0.062328302379332047;


        klab::TSmartPointer<kl1p::TMatrixOperator<klab::DoubleReal> > phi = new kl1p::TMatrixOperator<klab::DoubleReal>(A);

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TBasisPursuitSolver<klab::DoubleReal> bp(1e-3);
        bp.conjugateGradientSolver().setTolerance(1e-8);
        bp.enableHistory(true);

        bp.solve(y, phi, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = bp.residualNorm();
        klab::DoubleReal rrNorm       = bp.relativeResidualNorm();
        klab::DoubleReal dg           = bp.dualityGap();
        klab::UInt32 iterations       = bp.iterations();

        TEST_ASSERT(klab::Equals(snr, 73.463046984225954, 1e-3))
        TEST_ASSERT(klab::Equals(residualNorm, 2.2876307371701295e-005, 1e-8))
        TEST_ASSERT(klab::Equals(rrNorm, 2.5153083597171819e-005, 1e-8))
        TEST_ASSERT(klab::Equals(dg, 0.00040519959492592902, 1e-8))
        TEST_ASSERT(iterations == 11)

        TEST_ASSERT(bp.history().size() == 12)
        TEST_ASSERT(klab::Equals(bp.history()[0].residualNorm(), 514.96918372321795, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[1].residualNorm(), 5.2162044, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[2].residualNorm(), 2.2575324, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[3].residualNorm(), 1.1615724, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[4].residualNorm(), 0.36185468, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[5].residualNorm(), 0.17687852, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[6].residualNorm(), 0.16631225, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[7].residualNorm(), 0.10926168, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[8].residualNorm(), 0.059498308, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[9].residualNorm(), 0.0020143622, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[10].residualNorm(), 0.00021016888, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[11].residualNorm(), 2.2876276e-005, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[0].dualityGap(), 256.0, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[1].dualityGap(), 12.592815, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[2].dualityGap(), 6.5816521, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[3].dualityGap(), 3.8052161, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[4].dualityGap(), 1.5136876, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[5].dualityGap(), 0.81807769, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[6].dualityGap(), 0.77378347, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[7].dualityGap(), 0.53305482, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[8].dualityGap(), 0.31276145, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[9].dualityGap(), 0.034097991, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[10].dualityGap(), 0.0037174159, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[11].dualityGap(), 0.00040519902, 1e-6))


        // Limit cases.
        try                                                 {bp.solve(arma::Col<klab::DoubleReal>(), phi, xr); TEST_ASSERT(false)}
        catch(KNullVectorBasisPursuitSolverException&)      {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {bp.solve(y, 0, xr); TEST_ASSERT(false)}
        catch(KNullOperatorBasisPursuitSolverException&)    {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        bp.setTolerance(0.4);
        bp.solve(y, phi, xr);
        TEST_ASSERT(xr.n_rows == n)
        snr          = klab::SNR(x, xr);
        residualNorm = bp.residualNorm();
        rrNorm       = bp.relativeResidualNorm();
        dg           = bp.dualityGap();
        iterations   = bp.iterations();
        TEST_ASSERT(klab::Equals(snr, 11.667566911559790, 1e-5))
        TEST_ASSERT(klab::Equals(residualNorm, 0.059498388316654785, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 0.065419995933308286, 1e-6))
        TEST_ASSERT(klab::Equals(dg, 0.31276180855112190, 1e-6))
        TEST_ASSERT(iterations == 8)
        bp.setTolerance(1e-6);
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

void KBasisPursuitSolverUnitTest::testSolve_02()
{
    try
    {
        klab::UInt32 m = 15;    // Number of observations.
        klab::UInt32 n = 128;   // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        x.fill(0.0);
        x[6]   =  1.0;
        x[3]   = -1.0;
        x[105] = -1.0;
        x[21]  =  1.0;
        x[33]  = -1.0;


        KBitArray measures(n);
        measures.reset();
        measures.set(8);
        measures.set(10);
        measures.set(4);
        measures.set(55);
        measures.set(26);
        measures.set(35);
        measures.set(6);
        measures.set(23);
        measures.set(42);
        measures.set(1);
        measures.set(52);
        measures.set(3);
        measures.set(29);
        measures.set(59);
        measures.set(53);

        klab::TSmartPointer<TDownSamplingOperator<std::complex<klab::DoubleReal> > > maskOp = new TDownSamplingOperator<std::complex<klab::DoubleReal> >(measures);
        klab::TSmartPointer<kl1p::TFourier1DOperator<std::complex<klab::DoubleReal> > > fourierOp = new kl1p::TFourier1DOperator<std::complex<klab::DoubleReal> >(n);
        klab::TSmartPointer<kl1p::TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, TDownSamplingOperator<std::complex<klab::DoubleReal> >, kl1p::TFourier1DOperator<std::complex<klab::DoubleReal> > > > phi = new kl1p::TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, TDownSamplingOperator<std::complex<klab::DoubleReal> >, kl1p::TFourier1DOperator<std::complex<klab::DoubleReal> > >(maskOp, fourierOp);

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TBasisPursuitSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > bp(1e-3);
        bp.conjugateGradientSolver().setTolerance(1e-8);
        bp.enableHistory(true);

        bp.solve(y, phi, xr);
        TEST_ASSERT(xr.n_rows == n)

        arma::Col<klab::DoubleReal> rx(x.n_rows);
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            rx[i] = klab::CastTo<klab::DoubleReal>(x[i]);

        arma::Col<klab::DoubleReal> rxr(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);


        klab::DoubleReal snr          = klab::SNR(rx, rxr);
        klab::DoubleReal residualNorm = bp.residualNorm();
        klab::DoubleReal rrNorm       = bp.relativeResidualNorm();
        klab::DoubleReal dg           = bp.dualityGap();
        klab::UInt32 iterations       = bp.iterations();

        TEST_ASSERT(klab::Equals(snr, 93.863247124709019, 1e-1))
        TEST_ASSERT(klab::Equals(residualNorm, 7.6088404351780092e-006, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 9.4588954184965683e-007, 1e-8))
        TEST_ASSERT(klab::Equals(dg, 0.00019127313215704737, 1e-6))
        TEST_ASSERT(iterations == 10)

        TEST_ASSERT(bp.history().size() == 11)
        TEST_ASSERT(klab::Equals(bp.history()[0].residualNorm(), 1593.7745415720544, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[1].residualNorm(), 1325.1876972086484, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[2].residualNorm(), 966.84571364792282, 1e-1))
        TEST_ASSERT(klab::Equals(bp.history()[3].residualNorm(), 546.11392550184394, 1))
        TEST_ASSERT(klab::Equals(bp.history()[4].residualNorm(), 147.82643234900704, 2e-1))
        TEST_ASSERT(klab::Equals(bp.history()[5].residualNorm(), 1.4931988564970546, 1e-2))
        TEST_ASSERT(klab::Equals(bp.history()[6].residualNorm(), 0.27840702891367575, 1e-3))
        TEST_ASSERT(klab::Equals(bp.history()[7].residualNorm(), 0.0064809236900278955, 1e-4))
        TEST_ASSERT(klab::Equals(bp.history()[8].residualNorm(), 0.00064090454919801473, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[9].residualNorm(), 6.9788722954902015e-005, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[10].residualNorm(), 7.6069339851179873e-006, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[0].dualityGap(), 512.00000000000000, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[1].dualityGap(), 408.64566284420528, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[2].dualityGap(), 280.38097503969294, 1e-2))
        TEST_ASSERT(klab::Equals(bp.history()[3].dualityGap(), 154.92397424306779, 1e-1))
        TEST_ASSERT(klab::Equals(bp.history()[4].dualityGap(), 47.422115698543969, 1e-1))
        TEST_ASSERT(klab::Equals(bp.history()[5].dualityGap(), 5.0850328645598761, 1e-2))
        TEST_ASSERT(klab::Equals(bp.history()[6].dualityGap(), 1.3547718999764375, 1e-2))
        TEST_ASSERT(klab::Equals(bp.history()[7].dualityGap(), 0.14769637828123452, 1e-3))
        TEST_ASSERT(klab::Equals(bp.history()[8].dualityGap(), 0.016099075219065222, 1e-4))
        TEST_ASSERT(klab::Equals(bp.history()[9].dualityGap(), 0.0017543598447289689, 1e-6))
        TEST_ASSERT(klab::Equals(bp.history()[10].dualityGap(), 0.00019122522311782286, 1e-6))


        // Limit cases.
        try                                                 {bp.solve(arma::Col<std::complex<klab::DoubleReal> >(), phi, xr); TEST_ASSERT(false)}
        catch(KNullVectorBasisPursuitSolverException&)      {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {bp.solve(y, 0, xr); TEST_ASSERT(false)}
        catch(KNullOperatorBasisPursuitSolverException&)    {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        bp.setTolerance(0.4);
        bp.solve(y, phi, xr);
        TEST_ASSERT(xr.n_rows == n)

        rxr.set_size(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);

        snr          = klab::SNR(rx, rxr);
        residualNorm = bp.residualNorm();
        rrNorm       = bp.relativeResidualNorm();
        dg           = bp.dualityGap();
        iterations   = bp.iterations();

        TEST_ASSERT(klab::Equals(snr, 36.175660473194050, 1e-2))
        TEST_ASSERT(klab::Equals(residualNorm, 0.0064809236900278955, 1e-4))
        TEST_ASSERT(klab::Equals(rrNorm, 0.00080567308411162079, 1e-5))
        TEST_ASSERT(klab::Equals(dg, 0.14769637828123452, 1e-3))
        TEST_ASSERT(iterations == 7)
        bp.setTolerance(1e-6);
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

void KBasisPursuitSolverUnitTest::testSolve_03()
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

        klab::TSmartPointer<kl1p::TOperator<klab::DoubleReal> > phi = new TNormalRandomMatrixOperator<klab::DoubleReal>(m, n);

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TBasisPursuitSolver<klab::DoubleReal> bp(1e-5);

        bp.solve(y, phi, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = bp.residualNorm();
        klab::DoubleReal rrNorm       = bp.relativeResidualNorm();
        klab::DoubleReal dg           = bp.dualityGap();
        klab::UInt32 iterations       = bp.iterations();

#if !defined(KLAB_UNIX_SYSTEM)          // To investigate.
    #if !defined(KLAB_64BITS_PLATFORM)  // To investigate.
        TEST_ASSERT(klab::Equals(snr, 109.64983000005432, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 7.2754655256600676e-006, 1e-8))
        TEST_ASSERT(klab::Equals(rrNorm, 7.0432035036131715e-007, 1e-8))
        TEST_ASSERT(klab::Equals(dg, 9.6950474619646304e-006, 1e-8))
        TEST_ASSERT(iterations == 17)
    #else
/*
std::ofstream of("SolverOut.txt"); // Debug.
of<<"TEST_ASSERT(klab::Equals(snr, "<<std::setprecision(8)<<snr<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(residualNorm, "<<std::setprecision(8)<<residualNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(rrNorm, "<<std::setprecision(8)<<rrNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(dg, "<<std::setprecision(8)<<dg<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(iterations == "<<iterations<<")"<<std::endl;
of.flush();
*/
        TEST_ASSERT(klab::Equals(snr, 128.14989, 1e-1))
        TEST_ASSERT(klab::Equals(residualNorm, 9.1559768e-007, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 8.8636813e-008, 1e-6))
        TEST_ASSERT(klab::Equals(dg, 1.0979214e-006, 1e-8))
        TEST_ASSERT(iterations == 18)
    #endif
#else
	#if !defined(KLAB_64BITS_PLATFORM)  // To investigate.
/*
std::ofstream of("SolverOut.txt"); // Debug.
of<<"TEST_ASSERT(klab::Equals(snr, "<<std::setprecision(8)<<snr<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(residualNorm, "<<std::setprecision(8)<<residualNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(rrNorm, "<<std::setprecision(8)<<rrNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(dg, "<<std::setprecision(8)<<dg<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(iterations == "<<iterations<<")"<<std::endl;
of.flush();
*/
		TEST_ASSERT(klab::Equals(snr, 109.4139, 1e-4))
		TEST_ASSERT(klab::Equals(residualNorm, 7.6135005e-06, 1e-6))
		TEST_ASSERT(klab::Equals(rrNorm, 7.370447e-07, 1e-6))
		TEST_ASSERT(klab::Equals(dg, 9.9187894e-06, 1e-6))
		TEST_ASSERT(iterations == 17)
    #else
/*
std::ofstream of("SolverOut.txt"); // Debug.
of<<"TEST_ASSERT(klab::Equals(snr, "<<std::setprecision(8)<<snr<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(residualNorm, "<<std::setprecision(8)<<residualNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(rrNorm, "<<std::setprecision(8)<<rrNorm<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(klab::Equals(dg, "<<std::setprecision(8)<<dg<<", 1e-6))"<<std::endl;
of<<"TEST_ASSERT(iterations == "<<iterations<<")"<<std::endl;
of.flush();
*/
        TEST_ASSERT(klab::Equals(snr, 109.66366, 1e-4))
        TEST_ASSERT(klab::Equals(residualNorm, 7.3936796e-06, 1e-6))
        TEST_ASSERT(klab::Equals(rrNorm, 7.1576437e-07, 1e-6))
        TEST_ASSERT(klab::Equals(dg, 9.6270366e-06, 1e-6))
        TEST_ASSERT(iterations == 17)
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

void KBasisPursuitSolverUnitTest::testSolve_04()
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
        x[6]   =  1.0;
        x[3]   = -1.0;
        x[105] = -1.0;
        x[21]  =  1.0;
        x[33]  = -1.0;


        klab::KRandom::Instance().setSeed(12345);

        klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > phi = new TNormalRandomMatrixOperator<std::complex<klab::DoubleReal> >(m, n, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));                

        phi->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TBasisPursuitSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > bp(1e-5);

        bp.solve(y, phi, xr);   
        TEST_ASSERT(xr.n_rows == n)

        arma::Col<klab::DoubleReal> rx(x.n_rows);
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            rx[i] = klab::CastTo<klab::DoubleReal>(x[i]);

        arma::Col<klab::DoubleReal> rxr(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);

        klab::DoubleReal snr          = klab::SNR(rx, rxr);
        klab::DoubleReal residualNorm = bp.residualNorm();
        klab::DoubleReal rrNorm       = bp.relativeResidualNorm();
        klab::DoubleReal dg           = bp.dualityGap();
        klab::UInt32 iterations       = bp.iterations();
		
		TEST_ASSERT(snr>120.0 && snr<140.0)
        TEST_ASSERT(residualNorm <= 1e-5)
		TEST_ASSERT(rrNorm <= 1e-6)
		TEST_ASSERT(dg <= 1e-5)
        TEST_ASSERT(iterations==16 || iterations==17)
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
