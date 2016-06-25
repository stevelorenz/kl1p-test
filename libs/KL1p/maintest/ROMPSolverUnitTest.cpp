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

#include "ROMPSolverUnitTest.h"
#include "../include/ROMPSolver.h"
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

KROMPSolverUnitTest::KROMPSolverUnitTest() : Test::Suite()
{
    TEST_ADD(KROMPSolverUnitTest::testDefaultConstructor)  
    TEST_ADD(KROMPSolverUnitTest::testToleranceConstructor)
    TEST_ADD(KROMPSolverUnitTest::testToleranceIterationLimitConstructor)
    TEST_ADD(KROMPSolverUnitTest::testToleranceIterationLimitMaxCoeffConstructor)
    TEST_ADD(KROMPSolverUnitTest::testCopyConstructor)
    TEST_ADD(KROMPSolverUnitTest::testAffectationOperator)

    TEST_ADD(KROMPSolverUnitTest::testSetTolerance)
    TEST_ADD(KROMPSolverUnitTest::testSetIterationLimit)
    TEST_ADD(KROMPSolverUnitTest::testSetMaxCoeffAddedEachIterations)
    TEST_ADD(KROMPSolverUnitTest::testTolerance)
    TEST_ADD(KROMPSolverUnitTest::testIterationLimit)
    TEST_ADD(KROMPSolverUnitTest::testMaxCoeffAddedEachIterations)
    TEST_ADD(KROMPSolverUnitTest::testResidualNorm)
    TEST_ADD(KROMPSolverUnitTest::testRelativeResidualNorm)
    TEST_ADD(KROMPSolverUnitTest::testIterations)
    TEST_ADD(KROMPSolverUnitTest::testSparsity)
    TEST_ADD(KROMPSolverUnitTest::testLeastSquareSolver)
    TEST_ADD(KROMPSolverUnitTest::testEnableHistory)
    TEST_ADD(KROMPSolverUnitTest::testIsHistoryEnabled)
    TEST_ADD(KROMPSolverUnitTest::testHistory)
    TEST_ADD(KROMPSolverUnitTest::testSolve)
    TEST_ADD(KROMPSolverUnitTest::testSolve_02)
    TEST_ADD(KROMPSolverUnitTest::testSolve_03)
    TEST_ADD(KROMPSolverUnitTest::testSolve_04)
}

// ---------------------------------------------------------------------------------------------------- //

KROMPSolverUnitTest::~KROMPSolverUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testDefaultConstructor()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-6))
        TEST_ASSERT(romp.iterationLimit() == klab::TTypeInfo<klab::UInt32>::MAX)
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 0)
        TEST_ASSERT(klab::Equals(romp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(romp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(romp.iterations() == 0)
        TEST_ASSERT(romp.sparsity() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testToleranceConstructor()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp(1e-5);
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-5))
        TEST_ASSERT(romp.iterationLimit() == klab::TTypeInfo<klab::UInt32>::MAX)
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 0)
        TEST_ASSERT(klab::Equals(romp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(romp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(romp.iterations() == 0)
        TEST_ASSERT(romp.sparsity() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testToleranceIterationLimitConstructor()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp(1e-5, 30);
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-5))
        TEST_ASSERT(romp.iterationLimit() == 30)
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 0)
        TEST_ASSERT(klab::Equals(romp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(romp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(romp.iterations() == 0)
        TEST_ASSERT(romp.sparsity() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testToleranceIterationLimitMaxCoeffConstructor()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-6))
        TEST_ASSERT(romp.iterationLimit() == klab::TTypeInfo<klab::UInt32>::MAX)
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 0)
        TEST_ASSERT(klab::Equals(romp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(romp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(romp.iterations() == 0)
        TEST_ASSERT(romp.sparsity() == 0)

        TROMPSolver<klab::DoubleReal> romp2(1e-5, 30, 20);
        TEST_ASSERT(klab::Equals(romp2.tolerance(), 1e-5))
        TEST_ASSERT(romp2.iterationLimit() == 30)
        TEST_ASSERT(romp2.maxCoeffAddedEachIterations() == 20)
        TEST_ASSERT(klab::Equals(romp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(romp2.relativeResidualNorm(), 0.0))
        TEST_ASSERT(romp2.iterations() == 0)
        TEST_ASSERT(romp2.sparsity() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testCopyConstructor()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp(1e-5, 30, 20);
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-5))
        TEST_ASSERT(romp.iterationLimit() == 30)
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 20)
        TEST_ASSERT(klab::Equals(romp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(romp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(romp.iterations() == 0)
        TEST_ASSERT(romp.sparsity() == 0)

        TROMPSolver<klab::DoubleReal> romp2(romp);
        TEST_ASSERT(klab::Equals(romp2.tolerance(), 1e-5))
        TEST_ASSERT(romp2.iterationLimit() == 30)
        TEST_ASSERT(romp2.maxCoeffAddedEachIterations() == 20)
        TEST_ASSERT(klab::Equals(romp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(romp2.relativeResidualNorm(), 0.0))
        TEST_ASSERT(romp2.iterations() == 0)
        TEST_ASSERT(romp2.sparsity() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testAffectationOperator()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp(1e-5, 30, 20);
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-5))
        TEST_ASSERT(romp.iterationLimit() == 30)
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 20)
        TEST_ASSERT(klab::Equals(romp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(romp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(romp.iterations() == 0)
        TEST_ASSERT(romp.sparsity() == 0)

        TROMPSolver<klab::DoubleReal> romp2;
        romp2 = romp;
        TEST_ASSERT(klab::Equals(romp2.tolerance(), 1e-5))
        TEST_ASSERT(romp2.iterationLimit() == 30)
        TEST_ASSERT(romp2.maxCoeffAddedEachIterations() == 20)
        TEST_ASSERT(klab::Equals(romp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(romp2.relativeResidualNorm(), 0.0))
        TEST_ASSERT(romp2.iterations() == 0)
        TEST_ASSERT(romp2.sparsity() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testSetTolerance()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-6))

        romp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testSetIterationLimit()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(romp.iterationLimit() == klab::TTypeInfo<klab::UInt32>::MAX)

        romp.setIterationLimit(30);
        TEST_ASSERT(romp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testSetMaxCoeffAddedEachIterations()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 0)

        romp.setMaxCoeffAddedEachIterations(20);
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 20)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testTolerance()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-6))

        romp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(romp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testIterationLimit()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(romp.iterationLimit() == klab::TTypeInfo<klab::UInt32>::MAX)

        romp.setIterationLimit(30);
        TEST_ASSERT(romp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testMaxCoeffAddedEachIterations()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 0)

        romp.setMaxCoeffAddedEachIterations(20);
        TEST_ASSERT(romp.maxCoeffAddedEachIterations() == 20)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testResidualNorm()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(klab::Equals(romp.residualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testRelativeResidualNorm()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(klab::Equals(romp.relativeResidualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testIterations()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(romp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testSparsity()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(romp.sparsity() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testLeastSquareSolver()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(klab::Equals(romp.leastSquareSolver().aTolerance(), 1.2345) == false)

        romp.leastSquareSolver().setATolerance(1.2345);
        TEST_ASSERT(klab::Equals(romp.leastSquareSolver().aTolerance(), 1.2345))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testEnableHistory()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(romp.isHistoryEnabled() == false)

        romp.enableHistory(true);
        TEST_ASSERT(romp.isHistoryEnabled() == true)

        romp.enableHistory(false);
        TEST_ASSERT(romp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testIsHistoryEnabled()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(romp.isHistoryEnabled() == false)

        romp.enableHistory(true);
        TEST_ASSERT(romp.isHistoryEnabled() == true)

        romp.enableHistory(false);
        TEST_ASSERT(romp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testHistory()
{
    try
    {
        TROMPSolver<klab::DoubleReal> romp;
        TEST_ASSERT(romp.history().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KROMPSolverUnitTest::testSolve()
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

        TDownSamplingOperator<std::complex<klab::DoubleReal> >* opBitMask      = new TDownSamplingOperator<std::complex<klab::DoubleReal> >(bits);
        TInverseFourier1DOperator<std::complex<klab::DoubleReal> >* opInverseFourier = new TInverseFourier1DOperator<std::complex<klab::DoubleReal> >(n);   
        klab::TSmartPointer<TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal> > > phi = new TMultiplicationOperator<std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal>, std::complex<klab::DoubleReal> >(opBitMask, opInverseFourier);

        opBitMask->apply(x, y);
        TEST_ASSERT(y.n_rows == m)

        TROMPSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > romp(1e-6);
        romp.enableHistory(true);

        romp.solve(y, phi, k, XR);
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

        klab::DoubleReal snr          = klab::SNR(rx, rxr);
        klab::DoubleReal residualNorm = romp.residualNorm();
        klab::UInt32 iterations       = romp.iterations();
        klab::UInt32 sparsity         = romp.sparsity();

        TEST_ASSERT(klab::Equals(snr, 17.493509778182350, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 2.7994950211634433, 1e-6))
        TEST_ASSERT(iterations == 2)
        TEST_ASSERT(sparsity   == 5)

        TEST_ASSERT(romp.history().size() == 3)
        TEST_ASSERT(klab::Equals(romp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(romp.history()[0].sparsity() == 0)
        TEST_ASSERT(klab::Equals(romp.history()[1].residualNorm(), 8.806287, 1e-6))
        TEST_ASSERT(romp.history()[1].sparsity() == 2)
        TEST_ASSERT(klab::Equals(romp.history()[2].residualNorm(), 2.799495, 1e-6))
        TEST_ASSERT(romp.history()[2].sparsity() == 5)


        // Limit cases.
        try                                         {romp.solve(arma::Col<std::complex<klab::DoubleReal> >(), phi, k, XR); TEST_ASSERT(false)}
        catch(KNullVectorROMPSolverException&)      {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {romp.solve(y, 0, k, XR); TEST_ASSERT(false)}
        catch(KNullOperatorROMPSolverException&)    {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}


        romp.solve(y, phi, 0, XR);
        TEST_ASSERT(XR.n_rows == 64)
        bool isZero = true;
        for(klab::UInt32 i=0; i<64 && isZero; ++i)
            isZero = klab::Equals(XR[i], std::complex<klab::DoubleReal>(0.0, 0.0));
        TEST_ASSERT(isZero)

        romp.setTolerance(9.0);
        romp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);
        snr = klab::SNR(rx, rxr);
        residualNorm = romp.residualNorm();
        iterations = romp.iterations();
        sparsity = romp.sparsity();
        TEST_ASSERT(klab::Equals(snr, 7.6002766021824151, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 8.8062874126138198, 1e-6))
        TEST_ASSERT(iterations == 1)
        TEST_ASSERT(sparsity   == 2)
        romp.setTolerance(1e-6);
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

void KROMPSolverUnitTest::testSolve_02()
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

        TROMPSolver<klab::DoubleReal> romp(1e-6);
        romp.enableHistory(true);

        romp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)

        klab::TFFT1D<klab::DoubleReal> fft;
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = romp.residualNorm();
        klab::UInt32 iterations       = romp.iterations();
        klab::UInt32 sparsity         = romp.sparsity();

        TEST_ASSERT(klab::Equals(snr, 20.596621464205729, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 1.9594259477465348, 1e-6))
        TEST_ASSERT(iterations == 3)
        TEST_ASSERT(sparsity   == 6)

        TEST_ASSERT(romp.history().size() == 4)
        TEST_ASSERT(klab::Equals(romp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(romp.history()[0].sparsity() == 0)
        TEST_ASSERT(klab::Equals(romp.history()[1].residualNorm(), 9.0916552, 1e-6))
        TEST_ASSERT(romp.history()[1].sparsity() == 1)
        TEST_ASSERT(klab::Equals(romp.history()[2].residualNorm(), 3.60348987, 1e-6))
        TEST_ASSERT(romp.history()[2].sparsity() == 3)
        TEST_ASSERT(klab::Equals(romp.history()[3].residualNorm(), 1.95942595, 1e-6))
        TEST_ASSERT(romp.history()[3].sparsity() == 6)


        // Limit cases.
        try                                         {romp.solve(arma::Col<klab::DoubleReal>(), phi, k, XR); TEST_ASSERT(false)}
        catch(KNullVectorROMPSolverException&)      {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {romp.solve(y, 0, k, XR); TEST_ASSERT(false)}
        catch(KNullOperatorROMPSolverException&)    {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        romp.solve(y, phi, 0, XR);
        TEST_ASSERT(XR.n_rows == 64)
        bool isZero = true;
        for(klab::UInt32 i=0; i<64 && isZero; ++i)
            isZero = klab::Equals(XR[i], 0.0, 0.0);
        TEST_ASSERT(isZero)

        romp.setTolerance(4.0);
        romp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)
        snr = klab::SNR(x, xr);
        residualNorm = romp.residualNorm();
        iterations = romp.iterations();
        sparsity = romp.sparsity();
        TEST_ASSERT(klab::Equals(snr, 15.246543269623466, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 3.6034898651384268, 1e-6))
        TEST_ASSERT(iterations == 2)
        TEST_ASSERT(sparsity   == 3)
        romp.setTolerance(1e-6);
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

void KROMPSolverUnitTest::testSolve_03()
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

        TROMPSolver<klab::DoubleReal> romp(1e-6);
        romp.enableHistory(true);

        romp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > fwt;
        fwt.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = romp.residualNorm();
        klab::UInt32 iterations       = romp.iterations();
        klab::UInt32 sparsity         = romp.sparsity();

        TEST_ASSERT(klab::Equals(snr, 6.3942826562143935, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 10.204612003851395, 1e-6))
        TEST_ASSERT(iterations == 1)
        TEST_ASSERT(sparsity   == 5)

        TEST_ASSERT(romp.history().size() == 2)
        TEST_ASSERT(klab::Equals(romp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(romp.history()[0].sparsity() == 0)
        TEST_ASSERT(klab::Equals(romp.history()[1].residualNorm(), 10.20461201, 1e-6))
        TEST_ASSERT(romp.history()[1].sparsity() == 5)
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

void KROMPSolverUnitTest::testSolve_04()
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

        TROMPSolver<klab::DoubleReal> romp(1e-6);
        romp.enableHistory(true);

        romp.solve(y, phi, phiT, k, XR);
        TEST_ASSERT(XR.n_rows == n)

        arma::Col<klab::DoubleReal> xrTemp;
        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > fwt;
        fwt.invert(XR, xrTemp);
        opInverseBlur->apply(xrTemp, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = romp.residualNorm();
        klab::UInt32 iterations       = romp.iterations();
        klab::UInt32 sparsity         = romp.sparsity();

        TEST_ASSERT(klab::Equals(snr, 6.3945012597301423, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 10.204543630592063, 1e-6))
        TEST_ASSERT(iterations == 1)
        TEST_ASSERT(sparsity   == 5)

        TEST_ASSERT(romp.history().size() == 2)
        TEST_ASSERT(klab::Equals(romp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(romp.history()[0].sparsity() == 0)
        TEST_ASSERT(klab::Equals(romp.history()[1].residualNorm(), 10.20454363, 1e-6))
        TEST_ASSERT(romp.history()[1].sparsity() == 5)
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
