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

#include "CoSaMPSolverUnitTest.h"
#include "../include/CoSaMPSolver.h"
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

KCoSaMPSolverUnitTest::KCoSaMPSolverUnitTest() : Test::Suite()
{
    TEST_ADD(KCoSaMPSolverUnitTest::testDefaultConstructor)  
    TEST_ADD(KCoSaMPSolverUnitTest::testToleranceConstructor)
    TEST_ADD(KCoSaMPSolverUnitTest::testToleranceIterationLimitConstructor)
    TEST_ADD(KCoSaMPSolverUnitTest::testCopyConstructor)
    TEST_ADD(KCoSaMPSolverUnitTest::testAffectationOperator)

    TEST_ADD(KCoSaMPSolverUnitTest::testSetTolerance)
    TEST_ADD(KCoSaMPSolverUnitTest::testSetIterationLimit)
    TEST_ADD(KCoSaMPSolverUnitTest::testTolerance)
    TEST_ADD(KCoSaMPSolverUnitTest::testIterationLimit)
    TEST_ADD(KCoSaMPSolverUnitTest::testResidualNorm)
    TEST_ADD(KCoSaMPSolverUnitTest::testRelativeResidualNorm)
    TEST_ADD(KCoSaMPSolverUnitTest::testIterations)
    TEST_ADD(KCoSaMPSolverUnitTest::testLeastSquareSolver)
    TEST_ADD(KCoSaMPSolverUnitTest::testEnableHistory)
    TEST_ADD(KCoSaMPSolverUnitTest::testIsHistoryEnabled)
    TEST_ADD(KCoSaMPSolverUnitTest::testHistory)
    TEST_ADD(KCoSaMPSolverUnitTest::testSolve)        
    TEST_ADD(KCoSaMPSolverUnitTest::testSolve_02)     
    TEST_ADD(KCoSaMPSolverUnitTest::testSolve_03)   
    TEST_ADD(KCoSaMPSolverUnitTest::testSolve_04)    
}

// ---------------------------------------------------------------------------------------------------- //

KCoSaMPSolverUnitTest::~KCoSaMPSolverUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testDefaultConstructor()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(klab::Equals(cosamp.tolerance(), 1e-6))
        TEST_ASSERT(cosamp.iterationLimit() == 50)
        TEST_ASSERT(klab::Equals(cosamp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(cosamp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(cosamp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testToleranceConstructor()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp(1e-5);
        TEST_ASSERT(klab::Equals(cosamp.tolerance(), 1e-5))
        TEST_ASSERT(cosamp.iterationLimit() == 50)
        TEST_ASSERT(klab::Equals(cosamp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(cosamp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(cosamp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testToleranceIterationLimitConstructor()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp(1e-5, 30);
        TEST_ASSERT(klab::Equals(cosamp.tolerance(), 1e-5))
        TEST_ASSERT(cosamp.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(cosamp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(cosamp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(cosamp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testCopyConstructor()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp(1e-5, 30);
        TEST_ASSERT(klab::Equals(cosamp.tolerance(), 1e-5))
        TEST_ASSERT(cosamp.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(cosamp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(cosamp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(cosamp.iterations() == 0)

        TCoSaMPSolver<klab::DoubleReal> cosamp2(cosamp);
        TEST_ASSERT(klab::Equals(cosamp2.tolerance(), 1e-5))
        TEST_ASSERT(cosamp2.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(cosamp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(cosamp2.relativeResidualNorm(), 0.0))
        TEST_ASSERT(cosamp2.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testAffectationOperator()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp(1e-5, 30);
        TEST_ASSERT(klab::Equals(cosamp.tolerance(), 1e-5))
        TEST_ASSERT(cosamp.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(cosamp.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(cosamp.relativeResidualNorm(), 0.0))
        TEST_ASSERT(cosamp.iterations() == 0)

        TCoSaMPSolver<klab::DoubleReal> cosamp2;
        cosamp2 = cosamp;
        TEST_ASSERT(klab::Equals(cosamp2.tolerance(), 1e-5))
        TEST_ASSERT(cosamp2.iterationLimit() == 30)
        TEST_ASSERT(klab::Equals(cosamp2.residualNorm(), 0.0))
        TEST_ASSERT(klab::Equals(cosamp2.relativeResidualNorm(), 0.0))
        TEST_ASSERT(cosamp2.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testSetTolerance()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(klab::Equals(cosamp.tolerance(), 1e-6))

        cosamp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(cosamp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testSetIterationLimit()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(cosamp.iterationLimit() == 50)

        cosamp.setIterationLimit(30);
        TEST_ASSERT(cosamp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testTolerance()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(klab::Equals(cosamp.tolerance(), 1e-6))

        cosamp.setTolerance(1e-5);
        TEST_ASSERT(klab::Equals(cosamp.tolerance(), 1e-5))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testIterationLimit()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(cosamp.iterationLimit() == 50)

        cosamp.setIterationLimit(30);
        TEST_ASSERT(cosamp.iterationLimit() == 30)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testResidualNorm()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(klab::Equals(cosamp.residualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testRelativeResidualNorm()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(klab::Equals(cosamp.relativeResidualNorm(), 0.0))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testIterations()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(cosamp.iterations() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testLeastSquareSolver()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(klab::Equals(cosamp.leastSquareSolver().aTolerance(), 1.2345) == false)

        cosamp.leastSquareSolver().setATolerance(1.2345);
        TEST_ASSERT(klab::Equals(cosamp.leastSquareSolver().aTolerance(), 1.2345))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testEnableHistory()
{
    try
    {    
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(cosamp.isHistoryEnabled() == false)

        cosamp.enableHistory(true);
        TEST_ASSERT(cosamp.isHistoryEnabled() == true)

        cosamp.enableHistory(false);
        TEST_ASSERT(cosamp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testIsHistoryEnabled()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(cosamp.isHistoryEnabled() == false)

        cosamp.enableHistory(true);
        TEST_ASSERT(cosamp.isHistoryEnabled() == true)

        cosamp.enableHistory(false);
        TEST_ASSERT(cosamp.isHistoryEnabled() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testHistory()
{
    try
    {
        TCoSaMPSolver<klab::DoubleReal> cosamp;
        TEST_ASSERT(cosamp.history().size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCoSaMPSolverUnitTest::testSolve()
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

        TCoSaMPSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > cosamp(1e-6);
        cosamp.enableHistory(true);   

        cosamp.solve(y, phi, k, XR);
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
        klab::DoubleReal residualNorm = cosamp.residualNorm();
        klab::UInt32 iterations       = cosamp.iterations();

        TEST_ASSERT(klab::Equals(snr, 17.49350977, 1e-6))             
        TEST_ASSERT(klab::Equals(residualNorm, 2.79949502, 1e-6))     
        TEST_ASSERT(iterations == 5)                                                            

        TEST_ASSERT(cosamp.history().size() == 6)
        TEST_ASSERT(klab::Equals(cosamp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[1].residualNorm(), 5.57243215, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[2].residualNorm(), 2.81691145, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[3].residualNorm(), 2.79949502, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[4].residualNorm(), 2.79949502, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[5].residualNorm(), 2.79949502, 1e-6))


        // Limit cases.
        try                                         {cosamp.solve(arma::Col<std::complex<klab::DoubleReal> >(), phi, k, XR); TEST_ASSERT(false)}
        catch(KNullVectorCoSaMPSolverException&)    {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {cosamp.solve(y, 0, k, XR); TEST_ASSERT(false)}
        catch(KNullOperatorCoSaMPSolverException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        cosamp.solve(y, phi, 0, XR);
        TEST_ASSERT(XR.n_rows == 64)
        bool isZero = true;
        for(klab::UInt32 i=0; i<64 && isZero; ++i)
            isZero = klab::Equals(XR[i], std::complex<klab::DoubleReal>(0.0, 0.0));
        TEST_ASSERT(isZero)

        cosamp.setTolerance(3.0);
        cosamp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)
        for(klab::UInt32 i=0; i<xr.n_rows; ++i)
            rxr[i] = klab::CastTo<klab::DoubleReal>(xr[i]);
        snr = klab::SNR(rx, rxr);
        residualNorm = cosamp.residualNorm();
        iterations = cosamp.iterations();
        TEST_ASSERT(klab::Equals(snr, 17.42464998, 1e-6))                
        TEST_ASSERT(klab::Equals(residualNorm, 2.81691145, 1e-6))         
        TEST_ASSERT(iterations == 2)                                    
        cosamp.setTolerance(1e-6);
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

void KCoSaMPSolverUnitTest::testSolve_02()
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

        TCoSaMPSolver<klab::DoubleReal> cosamp(1e-6);
        cosamp.enableHistory(true);  

        cosamp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)

        klab::TFFT1D<klab::DoubleReal> fft;
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = cosamp.residualNorm();
        klab::UInt32 iterations       = cosamp.iterations();

        TEST_ASSERT(klab::Equals(snr, 7.29832256, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 5.73697267, 1e-6))
        TEST_ASSERT(iterations == 4)

        TEST_ASSERT(cosamp.history().size() == 5)
        TEST_ASSERT(klab::Equals(cosamp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[1].residualNorm(), 5.73900293, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[2].residualNorm(), 5.73697267, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[3].residualNorm(), 5.73697267, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[4].residualNorm(), 5.73697267, 1e-6))


        // Limit cases.
        try                                         {cosamp.solve(arma::Col<klab::DoubleReal>(), phi, k, XR); TEST_ASSERT(false)}
        catch(KNullVectorCoSaMPSolverException&)    {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        try                                         {cosamp.solve(y, 0, k, XR); TEST_ASSERT(false)}
        catch(KNullOperatorCoSaMPSolverException&)  {TEST_ASSERT(true)}
        catch(...)                                  {TEST_ASSERT(false)}

        cosamp.solve(y, phi, 0, XR);
        TEST_ASSERT(XR.n_rows == 64)
        bool isZero = true;
        for(klab::UInt32 i=0; i<64 && isZero; ++i)
            isZero = klab::Equals(XR[i], 0.0, 0.0);
        TEST_ASSERT(isZero)

        cosamp.setTolerance(6.0);
        cosamp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)
        fft.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)
        snr = klab::SNR(x, xr);
        residualNorm = cosamp.residualNorm();
        iterations = cosamp.iterations();
        TEST_ASSERT(klab::Equals(snr, 7.29592891, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 5.73900293, 1e-6))
        TEST_ASSERT(iterations == 1)
        cosamp.setTolerance(1e-6);
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

void KCoSaMPSolverUnitTest::testSolve_03()
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

        TCoSaMPSolver<klab::DoubleReal> cosamp(1e-6);
        cosamp.enableHistory(true);   

        cosamp.solve(y, phi, k, XR);
        TEST_ASSERT(XR.n_rows == n)

        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > fwt;
        fwt.invert(XR, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = cosamp.residualNorm();
        klab::UInt32 iterations       = cosamp.iterations();

        TEST_ASSERT(klab::Equals(snr, 6.39622986, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 10.20647941, 1e-6))
        TEST_ASSERT(iterations==4 || iterations==5)

        TEST_ASSERT(cosamp.history().size()==5 || cosamp.history().size()==6)
        TEST_ASSERT(klab::Equals(cosamp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[1].residualNorm(), 10.21178107, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[2].residualNorm(), 10.20647941, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[3].residualNorm(), 10.20647941, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[4].residualNorm(), 10.20647941, 1e-6))
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

void KCoSaMPSolverUnitTest::testSolve_04()
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

        TCoSaMPSolver<klab::DoubleReal> cosamp(1e-6);
        cosamp.enableHistory(true);   

        cosamp.solve(y, phi, phiT, k, XR);
        TEST_ASSERT(XR.n_rows == n)

        arma::Col<klab::DoubleReal> xrTemp;
        klab::TFWT1D<klab::DoubleReal, klab::TDaubechiesWaveletFilter<klab::DoubleReal, 8> > fwt;
        fwt.invert(XR, xrTemp);
        opInverseBlur->apply(xrTemp, xr);
        TEST_ASSERT(xr.n_rows == n)

        klab::DoubleReal snr          = klab::SNR(x, xr);
        klab::DoubleReal residualNorm = cosamp.residualNorm();
        klab::UInt32 iterations       = cosamp.iterations();

        TEST_ASSERT(klab::Equals(snr, 6.3929528924166483, 1e-6))
        TEST_ASSERT(klab::Equals(residualNorm, 10.209749096386659, 1e-6))
        TEST_ASSERT(iterations == 5)

        TEST_ASSERT(cosamp.history().size() == 6)
        TEST_ASSERT(klab::Equals(cosamp.history()[0].residualNorm(), 21.18933556, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[1].residualNorm(), 10.21179282, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[2].residualNorm(), 10.20974909, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[3].residualNorm(), 10.20974909, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[4].residualNorm(), 10.20974909, 1e-6))
        TEST_ASSERT(klab::Equals(cosamp.history()[5].residualNorm(), 10.20974909, 1e-6))
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
