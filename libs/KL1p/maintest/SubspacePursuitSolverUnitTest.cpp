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

#include "SubspacePursuitSolverUnitTest.h"
#include "../include/SubspacePursuitSolver.h"
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

KSubspacePursuitSolverUnitTest::KSubspacePursuitSolverUnitTest() : Test::Suite()
{
    TEST_ADD(KSubspacePursuitSolverUnitTest::testDefaultConstructor)  
    TEST_ADD(KSubspacePursuitSolverUnitTest::testToleranceConstructor)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testToleranceIterationLimitConstructor)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testCopyConstructor)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testAffectationOperator)

    TEST_ADD(KSubspacePursuitSolverUnitTest::testSetTolerance)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testSetIterationLimit)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testTolerance)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testIterationLimit)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testResidualNorm)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testRelativeResidualNorm)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testIterations)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testConjugateGradientSolver)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testEnableHistory)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testIsHistoryEnabled)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testHistory)
    TEST_ADD(KSubspacePursuitSolverUnitTest::testSolve)       
    TEST_ADD(KSubspacePursuitSolverUnitTest::testSolve_02)    
    TEST_ADD(KSubspacePursuitSolverUnitTest::testSolve_03)    
    TEST_ADD(KSubspacePursuitSolverUnitTest::testSolve_04)    
}

// ---------------------------------------------------------------------------------------------------- //

KSubspacePursuitSolverUnitTest::~KSubspacePursuitSolverUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testDefaultConstructor()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(klab::Equals(sp.tolerance(), 1e-6))
        TEST_ASSERT(sp.iterationLimit() == 50)
        TEST_ASSERT(klab::Equals(sp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(sp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(sp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testToleranceConstructor()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp(1e-5);
        TEST_ASSERT(klab::Equals(sp.tolerance(), 1e-5))
        TEST_ASSERT(sp.iterationLimit() == 50)
        TEST_ASSERT(klab::Equals(sp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(sp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(sp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testToleranceIterationLimitConstructor()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp(1e-5, 30);
        TEST_ASSERT(klab::Equals(sp.tolerance(), 1e-5))
        TEST_ASSERT(sp.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(sp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(sp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testCopyConstructor()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp(1e-5, 30);
        TEST_ASSERT(klab::Equals(sp.tolerance(), 1e-5))
        TEST_ASSERT(sp.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(sp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(sp.iterations() == 0)

        TSubspacePursuitSolver<klab::DoubleReal> sp2(sp);
        TEST_ASSERT(klab::Equals(sp2.tolerance(), 1e-5))
        TEST_ASSERT(sp2.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(sp2.relativeResidualNorm(), 0.0))
        TEST_ASSERT(sp2.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testAffectationOperator()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp(1e-5, 30);
        TEST_ASSERT(klab::Equals(sp.tolerance(), 1e-5))
        TEST_ASSERT(sp.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(sp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(sp.iterations() == 0)

        TSubspacePursuitSolver<klab::DoubleReal> sp2;
        sp2 = sp;
        TEST_ASSERT(klab::Equals(sp2.tolerance(), 1e-5))
        TEST_ASSERT(sp2.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(sp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(sp2.relativeResidualNorm(), 0.0))
        TEST_ASSERT(sp2.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testSetTolerance()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(klab::Equals(sp.tolerance(), 1e-6))

        sp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(sp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testSetIterationLimit()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(sp.iterationLimit() == 50)

        sp.setIterationLimit(30);
        TEST_ASSERT(sp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testTolerance()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(klab::Equals(sp.tolerance(), 1e-6))

        sp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(sp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testIterationLimit()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(sp.iterationLimit() == 50)

        sp.setIterationLimit(30);
        TEST_ASSERT(sp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testResidualNorm()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(klab::Equals(sp.residualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testRelativeResidualNorm()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(klab::Equals(sp.relativeResidualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testIterations()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(sp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testConjugateGradientSolver()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(klab::Equals(sp.conjugateGradientSolver().tolerance(), 1.2345) == false)

        sp.conjugateGradientSolver().setTolerance(1.2345);
        TEST_ASSERT(klab::Equals(sp.conjugateGradientSolver().tolerance(), 1.2345))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testEnableHistory()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(sp.isHistoryEnabled() == false)

        sp.enableHistory(true);
        TEST_ASSERT(sp.isHistoryEnabled() == true)

        sp.enableHistory(false);
        TEST_ASSERT(sp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testIsHistoryEnabled()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(sp.isHistoryEnabled() == false)

        sp.enableHistory(true);
        TEST_ASSERT(sp.isHistoryEnabled() == true)

        sp.enableHistory(false);
        TEST_ASSERT(sp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testHistory()
{
    try
    {
        TSubspacePursuitSolver<klab::DoubleReal> sp;
        TEST_ASSERT(sp.history().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KSubspacePursuitSolverUnitTest::testSolve()
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

        TSubspacePursuitSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > sp(1e-6);
        sp.enableHistory(true);

        sp.solve(y, phi, k, XR);
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
        klab::DoubleReal residualNorm = sp.residualNorm();
        klab::UInt32 iterations       = sp.iterations();

        TEST_ASSERT(klab::Equals(snr, 17.49350978, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 2.79949502, 1e-6))
        TEST_ASSERT(iterations == 3)

        TEST_ASSERT(sp.history().size() == 4)
        TEST_ASSERT(klab::Equals(sp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[1].residualNorm(), 6.64111616, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[2].residualNorm(), 2.79949502, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[3].residualNorm(), 2.79949502, 1e-6))


        // Limit cases.
        try                                                 {sp.solve(arma::Col<std::complex<klab::DoubleReal> >(), phi, k, XR); TEST_ASSERT(false)}
        catch(KNullVectorSubspacePursuitSolverException&)   {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {sp.solve(y, 0, k, XR); TEST_ASSERT(false)}
        catch(KNullOperatorSubspacePursuitSolverException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        sp.solve(y, phi, 0, XR);
        TEST_ASSERT(XR.n_rows == 64)
        bool isZero = true;
        for(klab::UInt32 i=0; i<64 && isZero; ++i)
            isZero = klab::Equals(XR[i], std::complex<klab::DoubleReal>(0.0, 0.0));
        TEST_ASSERT(isZero)

        sp.setTolerance(7.0);
        sp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);
        snr = klab::SNR(rx, rxr);
        residualNorm = sp.residualNorm();
        iterations = sp.iterations();
        TEST_ASSERT(klab::Equals(snr, 10.05976635, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 6.64111617, 1e-6))
        TEST_ASSERT(iterations == 1)
        sp.setTolerance(1e-6);
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

void KSubspacePursuitSolverUnitTest::testSolve_02()
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

        TSubspacePursuitSolver<klab::DoubleReal> sp(1e-6);
        sp.enableHistory(true);

        sp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)

        klab::TFFT1D<klab::DoubleReal> fft;
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = sp.residualNorm();
        klab::UInt32 iterations       = sp.iterations();

        TEST_ASSERT(klab::Equals(snr, 14.26524937, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 3.27015701, 1e-6))
        TEST_ASSERT(iterations == 5)

        TEST_ASSERT(sp.history().size() == 6)
        TEST_ASSERT(klab::Equals(sp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[1].residualNorm(), 6.79162072, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[2].residualNorm(), 3.57669940, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[3].residualNorm(), 3.33128731, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[4].residualNorm(), 3.27015701, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[5].residualNorm(), 3.27015701, 1e-6))


        // Limit cases.
        try                                                 {sp.solve(arma::Col<klab::DoubleReal>(), phi, k, XR); TEST_ASSERT(false)}
        catch(KNullVectorSubspacePursuitSolverException&)   {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        try                                                 {sp.solve(y, 0, k, XR); TEST_ASSERT(false)}
        catch(KNullOperatorSubspacePursuitSolverException&) {TEST_ASSERT(true)}
        catch(...)                                          {TEST_ASSERT(false)}

        sp.solve(y, phi, 0, XR);
        TEST_ASSERT(XR.n_rows == 64)
        bool isZero = true;
        for(klab::UInt32 i=0; i<64 && isZero; ++i)
            isZero = klab::Equals(XR[i], 0.0, 0.0);
        TEST_ASSERT(isZero)

        sp.setTolerance(3.5);
        sp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)
        snr = klab::SNR(x, xr);
        residualNorm = sp.residualNorm();
        iterations = sp.iterations();
        TEST_ASSERT(klab::Equals(snr, 15.35620347, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 3.33128731, 1e-6))
        TEST_ASSERT(iterations == 3)
        sp.setTolerance(1e-6);
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

void KSubspacePursuitSolverUnitTest::testSolve_03()
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

        TSubspacePursuitSolver<klab::DoubleReal> sp(1e-6);
        sp.enableHistory(true);

        sp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > fwt;
        fwt.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = sp.residualNorm();
        klab::UInt32 iterations       = sp.iterations();

        TEST_ASSERT(klab::Equals(snr, 6.39428267, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 10.20461200, 1e-6))
        TEST_ASSERT(iterations == 2)

        TEST_ASSERT(sp.history().size() == 3)
        TEST_ASSERT(klab::Equals(sp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[1].residualNorm(), 10.20461200, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[2].residualNorm(), 10.20461200, 1e-6))
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

void KSubspacePursuitSolverUnitTest::testSolve_04()
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

        TSubspacePursuitSolver<klab::DoubleReal> sp(1e-6);
        sp.enableHistory(true);

        sp.solve(y, phi, phiT, k, XR);
        TEST_ASSERT(XR.n_rows == n)

        arma::Col<klab::DoubleReal> xrTemp;
        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > fwt;
        fwt.invert(XR, xrTemp);
        opInverseBlur->apply(xrTemp, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = sp.residualNorm();
        klab::UInt32 iterations       = sp.iterations();

#if defined(KLAB_UNIX_SYSTEM) && !defined(KLAB_64BITS_PLATFORM)	// To investigate.
		TEST_ASSERT(klab::Equals(snr, 6.39450127, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 10.20454363, 1e-6))
        TEST_ASSERT(iterations == 50)

        TEST_ASSERT(sp.history().size() == 51)
        TEST_ASSERT(klab::Equals(sp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[1].residualNorm(), 10.20454363, 1e-6))
		TEST_ASSERT(klab::Equals(sp.history()[2].residualNorm(), 10.20454363, 1e-6))
#else
        TEST_ASSERT(klab::Equals(snr, 6.39450127, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 10.20454363, 1e-6))
        TEST_ASSERT(iterations == 2)

        TEST_ASSERT(sp.history().size() == 3)
        TEST_ASSERT(klab::Equals(sp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[1].residualNorm(), 10.20454363, 1e-6))
        TEST_ASSERT(klab::Equals(sp.history()[2].residualNorm(), 10.20454363, 1e-6))
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
