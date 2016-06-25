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

#include "SL0SolverUnitTest.h"
#include "../include/SL0Solver.h"
#include "../include/DownSamplingOperator.h"
#include "../include/Fourier1DOperator.h"
#include "../include/InverseFourier1DOperator.h"
#include "../include/Wavelet1DOperator.h"
#include "../include/InverseWavelet1DOperator.h"
#include "../include/GaussianBlur1DOperator.h"
#include "../include/InverseGaussianBlur1DOperator.h"
#include "../include/AdjointOperator.h"
#include "../include/MultiplicationOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KSL0SolverUnitTest::KSL0SolverUnitTest() : Test::Suite()
{
    TEST_ADD(KSL0SolverUnitTest::testDefaultConstructor)  
    TEST_ADD(KSL0SolverUnitTest::testToleranceConstructor)
    TEST_ADD(KSL0SolverUnitTest::testToleranceIterationLimitConstructor)
    TEST_ADD(KSL0SolverUnitTest::testToleranceIterationLimitSigmaStepFactorConstructor)
    TEST_ADD(KSL0SolverUnitTest::testToleranceIterationLimitSigmaStepFactorMu0Constructor)
    TEST_ADD(KSL0SolverUnitTest::testToleranceIterationLimitSigmaStepFactorMu0InnerIterationLimitConstructor)
    TEST_ADD(KSL0SolverUnitTest::testCopyConstructor)
    TEST_ADD(KSL0SolverUnitTest::testAffectationOperator)

    TEST_ADD(KSL0SolverUnitTest::testSetTolerance)
    TEST_ADD(KSL0SolverUnitTest::testSetIterationLimit)
    TEST_ADD(KSL0SolverUnitTest::testSetSigmaStepFactor)
    TEST_ADD(KSL0SolverUnitTest::testSetMu0)
    TEST_ADD(KSL0SolverUnitTest::testSetInnerIterationLimit)
    TEST_ADD(KSL0SolverUnitTest::testTolerance)
    TEST_ADD(KSL0SolverUnitTest::testIterationLimit)
    TEST_ADD(KSL0SolverUnitTest::testSigmaStepFactor)
    TEST_ADD(KSL0SolverUnitTest::testMu0)
    TEST_ADD(KSL0SolverUnitTest::testInnerIterationLimit)
    TEST_ADD(KSL0SolverUnitTest::testSigma)
    TEST_ADD(KSL0SolverUnitTest::testIterations)
    TEST_ADD(KSL0SolverUnitTest::testConjugateGradientSolver)
    TEST_ADD(KSL0SolverUnitTest::testEnableHistory)
    TEST_ADD(KSL0SolverUnitTest::testIsHistoryEnabled)
    TEST_ADD(KSL0SolverUnitTest::testHistory)
    TEST_ADD(KSL0SolverUnitTest::testSolve)       
    TEST_ADD(KSL0SolverUnitTest::testSolve_02)    
    TEST_ADD(KSL0SolverUnitTest::testSolve_03)    
    TEST_ADD(KSL0SolverUnitTest::testSolve_04)    
}

// ---------------------------------------------------------------------------------------------------- //

KSL0SolverUnitTest::~KSL0SolverUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testDefaultConstructor()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-6))
        TEST_ASSERT(sl0.iterationLimit() == 50)
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 0.5))
        TEST_ASSERT(klab::Equals(sl0.mu0(), 2.0))
        TEST_ASSERT(sl0.innerIterationLimit() == 3)
        TEST_ASSERT(klab::Equals(sl0.sigma(), 0.0))
        TEST_ASSERT(sl0.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testToleranceConstructor()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0(1e-5);
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-5))
        TEST_ASSERT(sl0.iterationLimit() == 50)
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 0.5))
        TEST_ASSERT(klab::Equals(sl0.mu0(), 2.0))
        TEST_ASSERT(sl0.innerIterationLimit() == 3)
        TEST_ASSERT(klab::Equals(sl0.sigma(), 0.0))
        TEST_ASSERT(sl0.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testToleranceIterationLimitConstructor()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0(1e-5, 30);
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-5))
        TEST_ASSERT(sl0.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 0.5))
        TEST_ASSERT(klab::Equals(sl0.mu0(), 2.0))
        TEST_ASSERT(sl0.innerIterationLimit() == 3)
        TEST_ASSERT(klab::Equals(sl0.sigma(), 0.0))
        TEST_ASSERT(sl0.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testToleranceIterationLimitSigmaStepFactorConstructor()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0(1e-5, 30, 1.1);
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-5))
        TEST_ASSERT(sl0.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 1.1))
        TEST_ASSERT(klab::Equals(sl0.mu0(), 2.0))
        TEST_ASSERT(sl0.innerIterationLimit() == 3)
        TEST_ASSERT(klab::Equals(sl0.sigma(), 0.0))
        TEST_ASSERT(sl0.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testToleranceIterationLimitSigmaStepFactorMu0Constructor()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0(1e-5, 30, 1.1, 0.75);
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-5))
        TEST_ASSERT(sl0.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 1.1))
        TEST_ASSERT(klab::Equals(sl0.mu0(), 0.75))
        TEST_ASSERT(sl0.innerIterationLimit() == 3)
        TEST_ASSERT(klab::Equals(sl0.sigma(), 0.0))
        TEST_ASSERT(sl0.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testToleranceIterationLimitSigmaStepFactorMu0InnerIterationLimitConstructor()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0(1e-5, 30, 1.1, 0.75, 10);
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-5))
        TEST_ASSERT(sl0.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 1.1))
        TEST_ASSERT(klab::Equals(sl0.mu0(), 0.75))
        TEST_ASSERT(sl0.innerIterationLimit() == 10)
        TEST_ASSERT(klab::Equals(sl0.sigma(), 0.0))
        TEST_ASSERT(sl0.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testCopyConstructor()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0(1e-5, 30, 1.1, 0.75, 10);
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-5))
        TEST_ASSERT(sl0.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 1.1))
        TEST_ASSERT(klab::Equals(sl0.mu0(), 0.75))
        TEST_ASSERT(sl0.innerIterationLimit() == 10)
        TEST_ASSERT(klab::Equals(sl0.sigma(), 0.0))
        TEST_ASSERT(sl0.iterations() == 0)

        TSL0Solver<klab::DoubleReal> sl02(sl0);
        TEST_ASSERT(klab::Equals(sl02.tolerance(), 1e-5))
        TEST_ASSERT(sl02.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sl02.sigmaStepFactor(), 1.1))
        TEST_ASSERT(klab::Equals(sl02.mu0(), 0.75))
        TEST_ASSERT(sl02.innerIterationLimit() == 10)
        TEST_ASSERT(klab::Equals(sl02.sigma(), 0.0))
        TEST_ASSERT(sl02.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testAffectationOperator()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0(1e-5, 30, 1.1, 0.75, 10);
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-5))
        TEST_ASSERT(sl0.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 1.1))
        TEST_ASSERT(klab::Equals(sl0.mu0(), 0.75))
        TEST_ASSERT(sl0.innerIterationLimit() == 10)
        TEST_ASSERT(klab::Equals(sl0.sigma(), 0.0))
        TEST_ASSERT(sl0.iterations() == 0)

        TSL0Solver<klab::DoubleReal> sl02;
        sl02 = sl0;
        TEST_ASSERT(klab::Equals(sl02.tolerance(), 1e-5))
        TEST_ASSERT(sl02.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sl02.sigmaStepFactor(), 1.1))
        TEST_ASSERT(klab::Equals(sl02.mu0(), 0.75))
        TEST_ASSERT(sl02.innerIterationLimit() == 10)
        TEST_ASSERT(klab::Equals(sl02.sigma(), 0.0))
        TEST_ASSERT(sl02.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testSetTolerance()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-6))

        sl0.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testSetIterationLimit()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(sl0.iterationLimit() == 50)

        sl0.setIterationLimit(30);
        TEST_ASSERT(sl0.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testSetSigmaStepFactor()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 0.5))

        sl0.setSigmaStepFactor(1.1);
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 1.1))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testSetMu0()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(klab::Equals(sl0.mu0(), 2.0))

        sl0.setMu0(0.75);
        TEST_ASSERT(klab::Equals(sl0.mu0(), 0.75))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testSetInnerIterationLimit()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(sl0.innerIterationLimit() == 3)

        sl0.setInnerIterationLimit(10);
        TEST_ASSERT(sl0.innerIterationLimit() == 10)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testTolerance()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-6))

        sl0.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(sl0.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testIterationLimit()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(sl0.iterationLimit() == 50)

        sl0.setIterationLimit(30);
        TEST_ASSERT(sl0.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testSigmaStepFactor()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 0.5))

        sl0.setSigmaStepFactor(1.1);
        TEST_ASSERT(klab::Equals(sl0.sigmaStepFactor(), 1.1))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testMu0()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(klab::Equals(sl0.mu0(), 2.0))

        sl0.setMu0(0.75);
        TEST_ASSERT(klab::Equals(sl0.mu0(), 0.75))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testInnerIterationLimit()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(sl0.innerIterationLimit() == 3)

        sl0.setInnerIterationLimit(10);
        TEST_ASSERT(sl0.innerIterationLimit() == 10)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testSigma()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(klab::Equals(sl0.sigma(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testIterations()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(sl0.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}


// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testConjugateGradientSolver()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(klab::Equals(sl0.conjugateGradientSolver().tolerance(), 1.2345) == false)

        sl0.conjugateGradientSolver().setTolerance(1.2345);
        TEST_ASSERT(klab::Equals(sl0.conjugateGradientSolver().tolerance(), 1.2345))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testEnableHistory()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(sl0.isHistoryEnabled() == false)

        sl0.enableHistory(true);
        TEST_ASSERT(sl0.isHistoryEnabled() == true)

        sl0.enableHistory(false);
        TEST_ASSERT(sl0.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testIsHistoryEnabled()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(sl0.isHistoryEnabled() == false)

        sl0.enableHistory(true);
        TEST_ASSERT(sl0.isHistoryEnabled() == true)

        sl0.enableHistory(false);
        TEST_ASSERT(sl0.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testHistory()
{
    try
    {
        TSL0Solver<klab::DoubleReal> sl0;
        TEST_ASSERT(sl0.history().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSL0SolverUnitTest::testSolve()
{
    try
    {
        klab::UInt32 m = 48;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<std::complex<klab::DoubleReal> > x(n);
        arma::Col<std::complex<klab::DoubleReal> > y;
        arma::Col<std::complex<klab::DoubleReal> > XR;
        arma::Col<std::complex<klab::DoubleReal> > xr;

        for(klab::UInt32 i=0; i<n; ++i)
        {
            klab::DoubleReal t = static_cast<klab::DoubleReal>(i+1) / static_cast<klab::DoubleReal>(n);
            x[i] = 4.0 * klab::Sin(4.0 * klab::PI * t) - ((t-0.3)>=0.0 ? 1.0 : -1.0) - ((0.72-t)>=0.0 ? 1.0 : -1.0);
        }

        KBitArray bits(n);
        for(klab::UInt32 i=0; i<n; ++i)
            bits.setBit(i, ((i+1)%4==0 ? false : true));

        TDownSamplingOperator<std::complex<klab::DoubleReal> >* opBitMask = new TDownSamplingOperator<std::complex<klab::DoubleReal> >(bits);
        TInverseFourier1DOperator<std::complex<klab::DoubleReal> >* opInverseFourier = new TInverseFourier1DOperator<std::complex<klab::DoubleReal> >(n);   
        klab::TSmartPointer<TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal> > > phi = new TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal> >(opBitMask, opInverseFourier);

        opBitMask->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TSL0Solver<klab::DoubleReal, std::complex<klab::DoubleReal> > sl0(1e-6);
        sl0.enableHistory(true);

        sl0.solve(y, phi, XR);
        TEST_ASSERT(XR.n_rows == n)

        klab::TFFT1D<std::complex<klab::DoubleReal> > fft;
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)


        arma::Col<klab::DoubleReal> rx(x.n_rows);
        for(klab::UInt32 i=0; i<x.n_rows; ++i)
            rx[i] = klab::CastTo<klab::DoubleReal>(x[i]);

        arma::Col<klab::DoubleReal> rxr(xr.n_rows);
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);

        klab::DoubleReal snr    = klab::SNR(rx, rxr);
        klab::DoubleReal sigma  = sl0.sigma();
        klab::UInt32 iterations = sl0.iterations();

        TEST_ASSERT(klab::Equals(snr, 25.13775496, 1e-6))     
        TEST_ASSERT(klab::Equals(sigma, 7.03458467e-007, 1e-7)) 
        TEST_ASSERT(iterations == 28)                           

        TEST_ASSERT(sl0.history().size() == 29)
        TEST_ASSERT(klab::Equals(sl0.history()[0].sigma(), 188.83319455, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[1].sigma(), 94.41659727, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[2].sigma(), 47.20829863, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[3].sigma(), 23.60414931, 1e-6))


        // Limit cases.
        try                                     {sl0.solve(arma::Col<std::complex<klab::DoubleReal> >(), phi, XR); TEST_ASSERT(false)}
        catch(KNullVectorSL0SolverException&)   {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {sl0.solve(y, 0, XR); TEST_ASSERT(false)}
        catch(KNullOperatorSL0SolverException&) {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        sl0.setTolerance(1.0);
        sl0.solve(y, phi, XR);
        TEST_ASSERT(XR.n_rows == n)
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);
        snr    = klab::SNR(rx, rxr);
        sigma  = sl0.sigma();
        iterations = sl0.iterations();
        TEST_ASSERT(klab::Equals(snr, 25.29216012, 1e-6))
        TEST_ASSERT(klab::Equals(sigma, 0.73762967, 1e-6))
        TEST_ASSERT(iterations == 8)
        sl0.setTolerance(1e-6);
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

void KSL0SolverUnitTest::testSolve_02()
{
    try
    {
        klab::UInt32 m = 48;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> XR;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<n; ++i)
        {
            klab::DoubleReal t = static_cast<klab::DoubleReal>(i+1) / static_cast<klab::DoubleReal>(n);
            x[i] = 4.0 * klab::Sin(4.0 * klab::PI * t) - ((t-0.3)>=0.0 ? 1.0 : -1.0) - ((0.72-t)>=0.0 ? 1.0 : -1.0);
        }

        KBitArray bits(n);
        for(klab::UInt32 i=0; i<n; ++i)
            bits.setBit(i, ((i+1)%4==0 ? false : true));

        TDownSamplingOperator<klab::DoubleReal>*      opBitMask = new TDownSamplingOperator<klab::DoubleReal>(bits);
        TInverseFourier1DOperator<klab::DoubleReal>* opInverseFourier = new TInverseFourier1DOperator<klab::DoubleReal>(n);   
        klab::TSmartPointer<TMultiplicationOperator<klab::DoubleReal> >    phi = new TMultiplicationOperator<klab::DoubleReal>(opBitMask, opInverseFourier);

        opBitMask->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TSL0Solver<klab::DoubleReal> sl0(1e-6);
        sl0.enableHistory(true);

        sl0.solve(y, phi, XR);
        TEST_ASSERT(XR.n_rows == n)

        klab::TFFT1D<klab::DoubleReal> fft;
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr    = klab::SNR(x, xr);
        klab::DoubleReal sigma  = sl0.sigma();
        klab::UInt32 iterations = sl0.iterations();

        TEST_ASSERT(klab::Equals(snr, 39.32151723, 1e-6))
        TEST_ASSERT(klab::Equals(sigma, 6.9860522654e-7, 1e-7))
        TEST_ASSERT(iterations == 28)

        TEST_ASSERT(sl0.history().size() == 29)
        TEST_ASSERT(klab::Equals(sl0.history()[0].sigma(), 187.53041255, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[1].sigma(), 93.76520627, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[2].sigma(), 46.88260314, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[3].sigma(), 23.44130157, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[4].sigma(), 11.72065078, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[5].sigma(), 5.86032539, 1e-6))


        // Limit cases.
        try                                     {sl0.solve(arma::Col<klab::DoubleReal>(), phi, XR); TEST_ASSERT(false)}
        catch(KNullVectorSL0SolverException&)   {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        try                                     {sl0.solve(y, 0, XR); TEST_ASSERT(false)}
        catch(KNullOperatorSL0SolverException&) {TEST_ASSERT(true)}
        catch(...)                              {TEST_ASSERT(false)}

        sl0.setTolerance(1.0);
        sl0.solve(y, phi, XR);
        TEST_ASSERT(XR.n_rows == n)
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)
        snr    = klab::SNR(x, xr);
        sigma  = sl0.sigma();
        iterations = sl0.iterations();
        TEST_ASSERT(klab::Equals(snr, 32.36438027, 1e-6))
        TEST_ASSERT(klab::Equals(sigma, 0.73254067, 1e-6))
        TEST_ASSERT(iterations == 8)
        sl0.setTolerance(1e-6);
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

void KSL0SolverUnitTest::testSolve_03()
{
    try
    {
        klab::UInt32 m = 48;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> XR;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<n; ++i)
        {
            klab::DoubleReal t = static_cast<klab::DoubleReal>(i+1) / static_cast<klab::DoubleReal>(n);
            x[i] = 4.0 * klab::Sin(4.0 * klab::PI * t) - ((t-0.3)>=0.0 ? 1.0 : -1.0) - ((0.72-t)>=0.0 ? 1.0 : -1.0);
        }

        KBitArray bits(n);
        for(klab::UInt32 i=0; i<n; ++i)
            bits.setBit(i, ((i+1)%4==0 ? false : true));

        TDownSamplingOperator<klab::DoubleReal>* opBitMask = new TDownSamplingOperator<klab::DoubleReal>(bits);
        TInverseWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> >* opInverseWavelet = new TInverseWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> >(n);          
        klab::TSmartPointer<TMultiplicationOperator<klab::DoubleReal> > phi = new TMultiplicationOperator<klab::DoubleReal>(opBitMask, opInverseWavelet);

        opBitMask->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TSL0Solver<klab::DoubleReal> sl0(1e-6);
        sl0.enableHistory(true);

        sl0.solve(y, phi, XR);
        TEST_ASSERT(XR.n_rows == n)

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > fwt;
        fwt.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr    = klab::SNR(x, xr);
        klab::DoubleReal sigma  = sl0.sigma();
        klab::UInt32 iterations = sl0.iterations();

        TEST_ASSERT(klab::Equals(snr, 31.76898055, 1e-6))
        TEST_ASSERT(klab::Equals(sigma, 5.7292751659e-007, 1e-7))
        TEST_ASSERT(iterations == 25)

        TEST_ASSERT(sl0.history().size() == 26)
        TEST_ASSERT(klab::Equals(sl0.history()[0].sigma(), 19.22425739, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[1].sigma(), 9.61212869, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[2].sigma(), 4.80606435, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[3].sigma(), 2.40303217, 1e-6))
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

void KSL0SolverUnitTest::testSolve_04()
{
    try
    {
        klab::UInt32 m = 48;    // Number of observations.
        klab::UInt32 n = 64;    // Signal size.
        klab::UInt32 k = 5;     // Estimated sparsity.

        arma::Col<klab::DoubleReal> x(n);
        arma::Col<klab::DoubleReal> y;
        arma::Col<klab::DoubleReal> XR;
        arma::Col<klab::DoubleReal> xr;

        for(klab::UInt32 i=0; i<n; ++i)
        {
            klab::DoubleReal t = static_cast<klab::DoubleReal>(i+1) / static_cast<klab::DoubleReal>(n);
            x[i] = 4.0 * klab::Sin(4.0 * klab::PI * t) - ((t-0.3)>=0.0 ? 1.0 : -1.0) - ((0.72-t)>=0.0 ? 1.0 : -1.0);
        }

        KBitArray bits(n);
        for(klab::UInt32 i=0; i<n; ++i)
            bits.setBit(i, ((i+1)%4==0 ? false : true));

        TDownSamplingOperator<klab::DoubleReal>* opBitMask = new TDownSamplingOperator<klab::DoubleReal>(bits);
        TWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> >* opWavelet = new TWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> >(n);           
        TInverseWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> >* opInverseWavelet = new TInverseWavelet1DOperator<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> >(n);           
        klab::TSmartPointer<TGaussianBlur1DOperator<klab::DoubleReal> > opBlur = new TGaussianBlur1DOperator<klab::DoubleReal>(n, 32);
        klab::TSmartPointer<TInverseGaussianBlur1DOperator<klab::DoubleReal> > opInverseBlur = new TInverseGaussianBlur1DOperator<klab::DoubleReal>(n, 1.0, 32);
        klab::TSmartPointer<TMultiplicationOperator<klab::DoubleReal> > phi  = new TMultiplicationOperator<klab::DoubleReal>(new TMultiplicationOperator<klab::DoubleReal>(opBitMask, opInverseBlur), opInverseWavelet);
        klab::TSmartPointer<TMultiplicationOperator<klab::DoubleReal> > phiT = new TMultiplicationOperator<klab::DoubleReal>(new TMultiplicationOperator<klab::DoubleReal>(opWavelet, opBlur), new TAdjointOperator<klab::DoubleReal>(opBitMask));

        opBitMask->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TSL0Solver<klab::DoubleReal> sl0(1e-6);
        sl0.enableHistory(true);

        sl0.solve(y, phi, phiT, XR);
        TEST_ASSERT(XR.n_rows == n)

        arma::Col<klab::DoubleReal> xrTemp;
        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > fwt;
        fwt.invert(XR, xrTemp);
        opInverseBlur->apply(xrTemp, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr    = klab::SNR(x, xr);
        klab::DoubleReal sigma  = sl0.sigma();
        klab::UInt32 iterations = sl0.iterations();

        TEST_ASSERT(klab::Equals(snr, 30.79755268, 1e-6))
        TEST_ASSERT(klab::Equals(sigma, 6.108195033e-007, 1e-7))
        TEST_ASSERT(iterations == 26)

        TEST_ASSERT(sl0.history().size() == 27)
        TEST_ASSERT(klab::Equals(sl0.history()[0].sigma(), 40.99140422, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[1].sigma(), 20.49570211, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[2].sigma(), 10.24785105, 1e-6))
        TEST_ASSERT(klab::Equals(sl0.history()[3].sigma(), 5.12392553, 1e-6))
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
