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

#include "FFT1DUnitTest.h"
#include "../include/FFT1D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KFFT1DUnitTest::KFFT1DUnitTest() : Test::Suite()
{
    TEST_ADD(KFFT1DUnitTest::testDefaultConstructor)  
    TEST_ADD(KFFT1DUnitTest::testShiftConstructor)
    TEST_ADD(KFFT1DUnitTest::testCopyConstructor)
    TEST_ADD(KFFT1DUnitTest::testAffectationOperator)

    TEST_ADD(KFFT1DUnitTest::testSetShift)
    TEST_ADD(KFFT1DUnitTest::testShift)
    TEST_ADD(KFFT1DUnitTest::testTransform)
    TEST_ADD(KFFT1DUnitTest::testTransform_Real)
    TEST_ADD(KFFT1DUnitTest::testTransform_02)  
    TEST_ADD(KFFT1DUnitTest::testTransform_02_Real) 
    TEST_ADD(KFFT1DUnitTest::testInvert)   
    TEST_ADD(KFFT1DUnitTest::testInvert_Real)     
    TEST_ADD(KFFT1DUnitTest::testInvert_02)  
    TEST_ADD(KFFT1DUnitTest::testInvert_02_Real)
}

// ---------------------------------------------------------------------------------------------------- //

KFFT1DUnitTest::~KFFT1DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testDefaultConstructor()
{
    try
    {
        TFFT1D<klab::Real> fft;
        TEST_ASSERT(fft.shift() == false)

        TFFT1D<std::complex<klab::Real> > fftc;
        TEST_ASSERT(fftc.shift() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testShiftConstructor()
{
    try
    {
        TFFT1D<klab::Real> fft1(true);
        TEST_ASSERT(fft1.shift() == true)

        TFFT1D<klab::Real> fft2(false);
        TEST_ASSERT(fft2.shift() == false)


        TFFT1D<std::complex<klab::Real> > fft1c(true);
        TEST_ASSERT(fft1c.shift() == true)

        TFFT1D<std::complex<klab::Real> > fft2c(false);
        TEST_ASSERT(fft2c.shift() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testCopyConstructor()
{
    try
    {
        TFFT1D<klab::Real> fft1;
        TEST_ASSERT(fft1.shift() == false)

        TFFT1D<klab::Real> fft2(fft1);
        TEST_ASSERT(fft2.shift() == false)

        TFFT1D<klab::Real> fft3(true);
        TEST_ASSERT(fft3.shift() == true)

        TFFT1D<klab::Real> fft4(fft3);
        TEST_ASSERT(fft4.shift() == true)


        TFFT1D<std::complex<klab::Real> > fft1c;
        TEST_ASSERT(fft1c.shift() == false)

        TFFT1D<std::complex<klab::Real> > fft2c(fft1c);
        TEST_ASSERT(fft2c.shift() == false)

        TFFT1D<std::complex<klab::Real> > fft3c(true);
        TEST_ASSERT(fft3c.shift() == true)

        TFFT1D<std::complex<klab::Real> > fft4c(fft3c);
        TEST_ASSERT(fft4c.shift() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testAffectationOperator()
{
    try
    {
        TFFT1D<klab::Real> fft1;
        TEST_ASSERT(fft1.shift() == false)

        TFFT1D<klab::Real> fft2;
        fft2 = fft1;
        TEST_ASSERT(fft2.shift() == false)

        TFFT1D<klab::Real> fft3(true);
        TEST_ASSERT(fft3.shift() == true)

        TFFT1D<klab::Real> fft4;
        fft4 = fft3;
        TEST_ASSERT(fft4.shift() == true)


        TFFT1D<std::complex<klab::Real> > fft1c;
        TEST_ASSERT(fft1c.shift() == false)

        TFFT1D<std::complex<klab::Real> > fft2c;
        fft2c = fft1c;
        TEST_ASSERT(fft2c.shift() == false)

        TFFT1D<std::complex<klab::Real> > fft3c(true);
        TEST_ASSERT(fft3c.shift() == true)

        TFFT1D<std::complex<klab::Real> > fft4c;
        fft4c = fft3c;
        TEST_ASSERT(fft4c.shift() == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testSetShift()
{
    try
    {
        TFFT1D<klab::Real> fft;
        TEST_ASSERT(fft.shift() == false)

        fft.setShift(true);
        TEST_ASSERT(fft.shift() == true)

        fft.setShift(false);
        TEST_ASSERT(fft.shift() == false)


        TFFT1D<std::complex<klab::Real> > fftc;
        TEST_ASSERT(fftc.shift() == false)

        fftc.setShift(true);
        TEST_ASSERT(fftc.shift() == true)

        fftc.setShift(false);
        TEST_ASSERT(fftc.shift() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testShift()
{
    try
    {
        TFFT1D<klab::Real> fft;
        TEST_ASSERT(fft.shift() == false)

        fft.setShift(true);
        TEST_ASSERT(fft.shift() == true)

        fft.setShift(false);
        TEST_ASSERT(fft.shift() == false)


        TFFT1D<std::complex<klab::Real> > fftc;
        TEST_ASSERT(fftc.shift() == false)

        fftc.setShift(true);
        TEST_ASSERT(fftc.shift() == true)

        fftc.setShift(false);
        TEST_ASSERT(fftc.shift() == false)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testTransform()
{
    try
    {
        arma::Col<std::complex<klab::DoubleReal> > f(32);
        arma::Col<std::complex<klab::DoubleReal> > F;

        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));       


        klab::DoubleReal precision = 1e-5;

        TFFT1D<std::complex<klab::DoubleReal> > fft;
        fft.transform(f, F);

        TEST_ASSERT(F.n_rows==32)
        TEST_ASSERT(klab::Equals(F[0], std::complex<klab::DoubleReal>(0.587578, 0.0), precision))
        TEST_ASSERT(klab::Equals(F[1], std::complex<klab::DoubleReal>(0.609594, 0.0367113), precision))
        TEST_ASSERT(klab::Equals(F[2], std::complex<klab::DoubleReal>(0.687733, 0.0826952), precision))
        TEST_ASSERT(klab::Equals(F[3], std::complex<klab::DoubleReal>(0.879697, 0.158157), precision))
        TEST_ASSERT(klab::Equals(F[4], std::complex<klab::DoubleReal>(1.47377, 0.351375), precision))
        TEST_ASSERT(klab::Equals(F[5], std::complex<klab::DoubleReal>(15.27845, 4.51398), precision))
        TEST_ASSERT(klab::Equals(F[6], std::complex<klab::DoubleReal>(-1.38905, -0.485848), precision))
        TEST_ASSERT(klab::Equals(F[7], std::complex<klab::DoubleReal>(-0.589176, -0.235495), precision))
        TEST_ASSERT(klab::Equals(F[8], std::complex<klab::DoubleReal>(-0.34651, -0.153411), precision))
        TEST_ASSERT(klab::Equals(F[9], std::complex<klab::DoubleReal>(-0.232596, -0.110547), precision))
        TEST_ASSERT(klab::Equals(F[10], std::complex<klab::DoubleReal>(-0.168475, -0.0829686), precision))
        TEST_ASSERT(klab::Equals(F[11], std::complex<klab::DoubleReal>(-0.128819, -0.0628897), precision))
        TEST_ASSERT(klab::Equals(F[12], std::complex<klab::DoubleReal>(-0.103101, -0.046986), precision))
        TEST_ASSERT(klab::Equals(F[13], std::complex<klab::DoubleReal>(-0.0862395, -0.0335699), precision))
        TEST_ASSERT(klab::Equals(F[14], std::complex<klab::DoubleReal>(-0.0755652, -0.021664), precision))
        TEST_ASSERT(klab::Equals(F[15], std::complex<klab::DoubleReal>(-0.0696373, -0.010631), precision))
        TEST_ASSERT(klab::Equals(F[16], std::complex<klab::DoubleReal>(-0.0677346, 0.0), precision))
        TEST_ASSERT(klab::Equals(F[17], std::complex<klab::DoubleReal>(-0.0696373, 0.010631), precision))
        TEST_ASSERT(klab::Equals(F[18], std::complex<klab::DoubleReal>(-0.0755652, 0.021664), precision))
        TEST_ASSERT(klab::Equals(F[19], std::complex<klab::DoubleReal>(-0.0862395, 0.0335699), precision))
        TEST_ASSERT(klab::Equals(F[20], std::complex<klab::DoubleReal>(-0.103101, 0.0469861), precision))
        TEST_ASSERT(klab::Equals(F[21], std::complex<klab::DoubleReal>(-0.128819, 0.0628897), precision))
        TEST_ASSERT(klab::Equals(F[22], std::complex<klab::DoubleReal>(-0.168475, 0.0829686), precision))
        TEST_ASSERT(klab::Equals(F[23], std::complex<klab::DoubleReal>(-0.232596, 0.110547), precision))
        TEST_ASSERT(klab::Equals(F[24], std::complex<klab::DoubleReal>(-0.34651, 0.153411), precision))
        TEST_ASSERT(klab::Equals(F[25], std::complex<klab::DoubleReal>(-0.589176, 0.235495), precision))
        TEST_ASSERT(klab::Equals(F[26], std::complex<klab::DoubleReal>(-1.38905, 0.485848), precision))
        TEST_ASSERT(klab::Equals(F[27], std::complex<klab::DoubleReal>(15.27845, -4.51398), precision))
        TEST_ASSERT(klab::Equals(F[28], std::complex<klab::DoubleReal>(1.47377, -0.351375), precision))
        TEST_ASSERT(klab::Equals(F[29], std::complex<klab::DoubleReal>(0.879697, -0.158157), precision))
        TEST_ASSERT(klab::Equals(F[30], std::complex<klab::DoubleReal>(0.687733, -0.0826952), precision))
        TEST_ASSERT(klab::Equals(F[31], std::complex<klab::DoubleReal>(0.609594, -0.0367113), precision))


        F.fill(0.0);

        TFFT1D<std::complex<klab::DoubleReal> > fft2(true);
        fft2.transform(f, F);

        TEST_ASSERT(F.n_rows==32)
        TEST_ASSERT(klab::Equals(F[0], std::complex<klab::DoubleReal>(-0.0677346, 0.0), precision))
        TEST_ASSERT(klab::Equals(F[1], std::complex<klab::DoubleReal>(-0.0696373, 0.010631), precision))
        TEST_ASSERT(klab::Equals(F[2], std::complex<klab::DoubleReal>(-0.0755652, 0.021664), precision))
        TEST_ASSERT(klab::Equals(F[3], std::complex<klab::DoubleReal>(-0.0862395, 0.0335699), precision))
        TEST_ASSERT(klab::Equals(F[4], std::complex<klab::DoubleReal>(-0.103101, 0.0469861), precision))
        TEST_ASSERT(klab::Equals(F[5], std::complex<klab::DoubleReal>(-0.128819, 0.0628897), precision))
        TEST_ASSERT(klab::Equals(F[6], std::complex<klab::DoubleReal>(-0.168475, 0.0829686), precision))
        TEST_ASSERT(klab::Equals(F[7], std::complex<klab::DoubleReal>(-0.232596, 0.110547), precision))
        TEST_ASSERT(klab::Equals(F[8], std::complex<klab::DoubleReal>(-0.34651, 0.153411), precision))
        TEST_ASSERT(klab::Equals(F[9], std::complex<klab::DoubleReal>(-0.589176, 0.235495), precision))
        TEST_ASSERT(klab::Equals(F[10], std::complex<klab::DoubleReal>(-1.38905, 0.485848), precision))
        TEST_ASSERT(klab::Equals(F[11], std::complex<klab::DoubleReal>(15.27845, -4.51398), precision))
        TEST_ASSERT(klab::Equals(F[12], std::complex<klab::DoubleReal>(1.47377, -0.351375), precision))
        TEST_ASSERT(klab::Equals(F[13], std::complex<klab::DoubleReal>(0.879697, -0.158157), precision))
        TEST_ASSERT(klab::Equals(F[14], std::complex<klab::DoubleReal>(0.687733, -0.0826952), precision))
        TEST_ASSERT(klab::Equals(F[15], std::complex<klab::DoubleReal>(0.609594, -0.0367113), precision))
        TEST_ASSERT(klab::Equals(F[16], std::complex<klab::DoubleReal>(0.587578, 0.0), precision))
        TEST_ASSERT(klab::Equals(F[17], std::complex<klab::DoubleReal>(0.609594, 0.0367113), precision))
        TEST_ASSERT(klab::Equals(F[18], std::complex<klab::DoubleReal>(0.687733, 0.0826952), precision))
        TEST_ASSERT(klab::Equals(F[19], std::complex<klab::DoubleReal>(0.879697, 0.158157), precision))
        TEST_ASSERT(klab::Equals(F[20], std::complex<klab::DoubleReal>(1.47377, 0.351375), precision))
        TEST_ASSERT(klab::Equals(F[21], std::complex<klab::DoubleReal>(15.27845, 4.51398), precision))
        TEST_ASSERT(klab::Equals(F[22], std::complex<klab::DoubleReal>(-1.38905, -0.485848), precision))
        TEST_ASSERT(klab::Equals(F[23], std::complex<klab::DoubleReal>(-0.589176, -0.235495), precision))
        TEST_ASSERT(klab::Equals(F[24], std::complex<klab::DoubleReal>(-0.34651, -0.153411), precision))
        TEST_ASSERT(klab::Equals(F[25], std::complex<klab::DoubleReal>(-0.232596, -0.110547), precision))
        TEST_ASSERT(klab::Equals(F[26], std::complex<klab::DoubleReal>(-0.168475, -0.0829686), precision))
        TEST_ASSERT(klab::Equals(F[27], std::complex<klab::DoubleReal>(-0.128819, -0.0628897), precision))
        TEST_ASSERT(klab::Equals(F[28], std::complex<klab::DoubleReal>(-0.103101, -0.046986), precision))
        TEST_ASSERT(klab::Equals(F[29], std::complex<klab::DoubleReal>(-0.0862395, -0.0335699), precision))
        TEST_ASSERT(klab::Equals(F[30], std::complex<klab::DoubleReal>(-0.0755652, -0.021664), precision))
        TEST_ASSERT(klab::Equals(F[31], std::complex<klab::DoubleReal>(-0.0696373, -0.010631), precision))        


        // Limit cases.
        arma::Col<std::complex<klab::DoubleReal> > f0;
        arma::Col<std::complex<klab::DoubleReal> > F0;

        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)

        TFFT1D<std::complex<klab::DoubleReal> > fft0;
        fft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)

        TFFT1D<std::complex<klab::DoubleReal> > fft00(true);
        fft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)


        f0.set_size(32);
        f0.fill(0.0);
        fft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 32)
        TEST_ASSERT(F0.n_rows == 32)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<32 && areAllZeros; ++i)
            areAllZeros = (F0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(32);
        f0.fill(0.0);
        fft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 32)
        TEST_ASSERT(F0.n_rows == 32)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<32 && areAllZeros; ++i)
            areAllZeros = (F0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testTransform_Real()
{
    try
    {
        arma::Col<klab::DoubleReal> f(32);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));       


        klab::DoubleReal precision = 1e-5;

        TFFT1D<klab::DoubleReal> fft;
        fft.transform(f, F);

        TEST_ASSERT(F.n_rows==32)
        TEST_ASSERT(klab::Equals(F[0], 0.587578, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.609594, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.687733, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.879697, precision))
        TEST_ASSERT(klab::Equals(F[4], 1.47377, precision))
        TEST_ASSERT(klab::Equals(F[5], 15.27845, precision))
        TEST_ASSERT(klab::Equals(F[6], -1.38905, precision))
        TEST_ASSERT(klab::Equals(F[7], -0.589176, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.34651, precision))
        TEST_ASSERT(klab::Equals(F[9], -0.232596, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.168475, precision))
        TEST_ASSERT(klab::Equals(F[11], -0.128819, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.103101, precision))
        TEST_ASSERT(klab::Equals(F[13], -0.0862395, precision))
        TEST_ASSERT(klab::Equals(F[14], -0.0755652, precision))
        TEST_ASSERT(klab::Equals(F[15], -0.0696373, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.0677346, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.0367113, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.0826952, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.158157, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.351375, precision))
        TEST_ASSERT(klab::Equals(F[21], 4.51398, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.485848, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.235495, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.153411, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.110547, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.0829686, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.0628897, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.046986, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.0335699, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.021664, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.010631, precision))


        F.fill(0.0);

        TFFT1D<klab::DoubleReal> fft2(true);
        fft2.transform(f, F);

        TEST_ASSERT(F.n_rows==32)
        TEST_ASSERT(klab::Equals(F[0], 0.587578, precision))
        TEST_ASSERT(klab::Equals(F[1], 0.609594, precision))
        TEST_ASSERT(klab::Equals(F[2], 0.687733, precision))
        TEST_ASSERT(klab::Equals(F[3], 0.879697, precision))
        TEST_ASSERT(klab::Equals(F[4], 1.47377, precision))
        TEST_ASSERT(klab::Equals(F[5], 15.27845, precision))
        TEST_ASSERT(klab::Equals(F[6], -1.38905, precision))
        TEST_ASSERT(klab::Equals(F[7], -0.589176, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.34651, precision))
        TEST_ASSERT(klab::Equals(F[9], -0.232596, precision))
        TEST_ASSERT(klab::Equals(F[10], -0.168475, precision))
        TEST_ASSERT(klab::Equals(F[11], -0.128819, precision))
        TEST_ASSERT(klab::Equals(F[12], -0.103101, precision))
        TEST_ASSERT(klab::Equals(F[13], -0.0862395, precision))
        TEST_ASSERT(klab::Equals(F[14], -0.0755652, precision))
        TEST_ASSERT(klab::Equals(F[15], -0.0696373, precision))
        TEST_ASSERT(klab::Equals(F[16], -0.0677346, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.0367113, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.0826952, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.158157, precision))
        TEST_ASSERT(klab::Equals(F[20], 0.351375, precision))
        TEST_ASSERT(klab::Equals(F[21], 4.51398, precision))
        TEST_ASSERT(klab::Equals(F[22], -0.485848, precision))
        TEST_ASSERT(klab::Equals(F[23], -0.235495, precision))
        TEST_ASSERT(klab::Equals(F[24], -0.153411, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.110547, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.0829686, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.0628897, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.046986, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.0335699, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.021664, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.010631, precision))    


        // Limit cases.
        arma::Col<klab::DoubleReal> f0;
        arma::Col<klab::DoubleReal> F0;

        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)

        TFFT1D<klab::DoubleReal> fft0;
        fft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)

        TFFT1D<klab::DoubleReal> fft00(true);
        fft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)


        f0.set_size(32);
        f0.fill(0.0);
        fft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 32)
        TEST_ASSERT(F0.n_rows == 32)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<32 && areAllZeros; ++i)
            areAllZeros = (F0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(32);
        f0.fill(0.0);
        fft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 32)
        TEST_ASSERT(F0.n_rows == 32)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<32 && areAllZeros; ++i)
            areAllZeros = (F0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testTransform_02()
{
    try
    {
        arma::Col<std::complex<klab::DoubleReal> > f(33);
        arma::Col<std::complex<klab::DoubleReal> > F;

        for(klab::UInt32 i=0; i<33; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));       


        klab::DoubleReal precision = 1e-5;

        TFFT1D<std::complex<klab::DoubleReal> > fft;
        fft.transform(f, F);

        TEST_ASSERT(F.n_rows==33)
        TEST_ASSERT(klab::Equals(F[0], std::complex<klab::DoubleReal>(1.4218, 0.0), precision))
        TEST_ASSERT(klab::Equals(F[1], std::complex<klab::DoubleReal>(1.45925, 0.217111), precision))
        TEST_ASSERT(klab::Equals(F[2], std::complex<klab::DoubleReal>(1.59073, 0.485223), precision))
        TEST_ASSERT(klab::Equals(F[3], std::complex<klab::DoubleReal>(1.90453, 0.910145), precision))
        TEST_ASSERT(klab::Equals(F[4], std::complex<klab::DoubleReal>(2.80013, 1.906), precision))
        TEST_ASSERT(klab::Equals(F[5], std::complex<klab::DoubleReal>(11.089021, 10.381073), precision))
        TEST_ASSERT(klab::Equals(F[6], std::complex<klab::DoubleReal>(-2.86199, -3.69016), precision))
        TEST_ASSERT(klab::Equals(F[7], std::complex<klab::DoubleReal>(-0.874769, -1.61671), precision))
        TEST_ASSERT(klab::Equals(F[8], std::complex<klab::DoubleReal>(-0.34719, -1.02708), precision))
        TEST_ASSERT(klab::Equals(F[9], std::complex<klab::DoubleReal>(-0.109664, -0.734645), precision))
        TEST_ASSERT(klab::Equals(F[10], std::complex<klab::DoubleReal>(0.0216109, -0.551983), precision))
        TEST_ASSERT(klab::Equals(F[11], std::complex<klab::DoubleReal>(0.102238, -0.421764), precision))
        TEST_ASSERT(klab::Equals(F[12], std::complex<klab::DoubleReal>(0.154638, -0.320368), precision))
        TEST_ASSERT(klab::Equals(F[13], std::complex<klab::DoubleReal>(0.189455, -0.236123), precision))
        TEST_ASSERT(klab::Equals(F[14], std::complex<klab::DoubleReal>(0.212266, -0.162444), precision))
        TEST_ASSERT(klab::Equals(F[15], std::complex<klab::DoubleReal>(0.226134, -0.0951707), precision))
        TEST_ASSERT(klab::Equals(F[16], std::complex<klab::DoubleReal>(0.232706, -0.0313582), precision))
        TEST_ASSERT(klab::Equals(F[17], std::complex<klab::DoubleReal>(0.232706, 0.0313582), precision))
        TEST_ASSERT(klab::Equals(F[18], std::complex<klab::DoubleReal>(0.226134, 0.0951707), precision))
        TEST_ASSERT(klab::Equals(F[19], std::complex<klab::DoubleReal>(0.212266, 0.162444), precision))
        TEST_ASSERT(klab::Equals(F[20], std::complex<klab::DoubleReal>(0.189455, 0.236123), precision))
        TEST_ASSERT(klab::Equals(F[21], std::complex<klab::DoubleReal>(0.154638, 0.320368), precision))
        TEST_ASSERT(klab::Equals(F[22], std::complex<klab::DoubleReal>(0.102238, 0.421764), precision))
        TEST_ASSERT(klab::Equals(F[23], std::complex<klab::DoubleReal>(0.0216109, 0.551983), precision))
        TEST_ASSERT(klab::Equals(F[24], std::complex<klab::DoubleReal>(-0.109664, 0.734645), precision))
        TEST_ASSERT(klab::Equals(F[25], std::complex<klab::DoubleReal>(-0.34719, 1.02708), precision))
        TEST_ASSERT(klab::Equals(F[26], std::complex<klab::DoubleReal>(-0.874769, 1.61671), precision))
        TEST_ASSERT(klab::Equals(F[27], std::complex<klab::DoubleReal>(-2.86199, 3.69016), precision))
        TEST_ASSERT(klab::Equals(F[28], std::complex<klab::DoubleReal>(11.089021, -10.381073), precision))
        TEST_ASSERT(klab::Equals(F[29], std::complex<klab::DoubleReal>(2.80013, -1.906), precision))
        TEST_ASSERT(klab::Equals(F[30], std::complex<klab::DoubleReal>(1.90453, -0.910145), precision))
        TEST_ASSERT(klab::Equals(F[31], std::complex<klab::DoubleReal>(1.59073, -0.485223), precision))
        TEST_ASSERT(klab::Equals(F[32], std::complex<klab::DoubleReal>(1.45925, -0.217111), precision))


        F.fill(0.0);

        TFFT1D<std::complex<klab::DoubleReal> > fft2(true);
        fft2.transform(f, F);

        TEST_ASSERT(F.n_rows==33)
        TEST_ASSERT(klab::Equals(F[0], std::complex<klab::DoubleReal>(0.232706, 0.0313582), precision))
        TEST_ASSERT(klab::Equals(F[1], std::complex<klab::DoubleReal>(0.226134, 0.0951707), precision))
        TEST_ASSERT(klab::Equals(F[2], std::complex<klab::DoubleReal>(0.212266, 0.162444), precision))
        TEST_ASSERT(klab::Equals(F[3], std::complex<klab::DoubleReal>(0.189455, 0.236123), precision))
        TEST_ASSERT(klab::Equals(F[4], std::complex<klab::DoubleReal>(0.154638, 0.320368), precision))
        TEST_ASSERT(klab::Equals(F[5], std::complex<klab::DoubleReal>(0.102238, 0.421764), precision))
        TEST_ASSERT(klab::Equals(F[6], std::complex<klab::DoubleReal>(0.0216109, 0.551983), precision))
        TEST_ASSERT(klab::Equals(F[7], std::complex<klab::DoubleReal>(-0.109664, 0.734645), precision))
        TEST_ASSERT(klab::Equals(F[8], std::complex<klab::DoubleReal>(-0.34719, 1.02708), precision))
        TEST_ASSERT(klab::Equals(F[9], std::complex<klab::DoubleReal>(-0.874769, 1.61671), precision))
        TEST_ASSERT(klab::Equals(F[10], std::complex<klab::DoubleReal>(-2.86199, 3.69016), precision))
        TEST_ASSERT(klab::Equals(F[11], std::complex<klab::DoubleReal>(11.089021, -10.381073), precision))
        TEST_ASSERT(klab::Equals(F[12], std::complex<klab::DoubleReal>(2.80013, -1.906), precision))
        TEST_ASSERT(klab::Equals(F[13], std::complex<klab::DoubleReal>(1.90453, -0.910145), precision))
        TEST_ASSERT(klab::Equals(F[14], std::complex<klab::DoubleReal>(1.59073, -0.485223), precision))
        TEST_ASSERT(klab::Equals(F[15], std::complex<klab::DoubleReal>(1.45925, -0.217111), precision))
        TEST_ASSERT(klab::Equals(F[16], std::complex<klab::DoubleReal>(1.4218, 0.0), precision))
        TEST_ASSERT(klab::Equals(F[17], std::complex<klab::DoubleReal>(1.45925, 0.217111), precision))
        TEST_ASSERT(klab::Equals(F[18], std::complex<klab::DoubleReal>(1.59073, 0.485223), precision))
        TEST_ASSERT(klab::Equals(F[19], std::complex<klab::DoubleReal>(1.90453, 0.910145), precision))
        TEST_ASSERT(klab::Equals(F[20], std::complex<klab::DoubleReal>(2.80013, 1.906), precision))
        TEST_ASSERT(klab::Equals(F[21], std::complex<klab::DoubleReal>(11.089021, 10.381073), precision))
        TEST_ASSERT(klab::Equals(F[22], std::complex<klab::DoubleReal>(-2.86199, -3.69016), precision))
        TEST_ASSERT(klab::Equals(F[23], std::complex<klab::DoubleReal>(-0.874769, -1.61671), precision))
        TEST_ASSERT(klab::Equals(F[24], std::complex<klab::DoubleReal>(-0.34719, -1.02708), precision))
        TEST_ASSERT(klab::Equals(F[25], std::complex<klab::DoubleReal>(-0.109664, -0.734645), precision))
        TEST_ASSERT(klab::Equals(F[26], std::complex<klab::DoubleReal>(0.0216109, -0.551983), precision))
        TEST_ASSERT(klab::Equals(F[27], std::complex<klab::DoubleReal>(0.102238, -0.421764), precision))
        TEST_ASSERT(klab::Equals(F[28], std::complex<klab::DoubleReal>(0.154638, -0.320368), precision))
        TEST_ASSERT(klab::Equals(F[29], std::complex<klab::DoubleReal>(0.189455, -0.236123), precision))
        TEST_ASSERT(klab::Equals(F[30], std::complex<klab::DoubleReal>(0.212266, -0.162444), precision))
        TEST_ASSERT(klab::Equals(F[31], std::complex<klab::DoubleReal>(0.226134, -0.0951707), precision))
        TEST_ASSERT(klab::Equals(F[32], std::complex<klab::DoubleReal>(0.232706, -0.0313582), precision))             


        // Limit cases.
        arma::Col<std::complex<klab::DoubleReal> > f0;
        arma::Col<std::complex<klab::DoubleReal> > F0;

        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)

        TFFT1D<std::complex<klab::DoubleReal> > fft0;
        fft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)

        TFFT1D<std::complex<klab::DoubleReal> > fft00(true);
        fft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)


        f0.set_size(33);
        f0.fill(0.0);
        fft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 33)
        TEST_ASSERT(F0.n_rows == 33)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<33 && areAllZeros; ++i)
            areAllZeros = (F0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(33);
        f0.fill(0.0);
        fft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 33)
        TEST_ASSERT(F0.n_rows == 33)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<33 && areAllZeros; ++i)
            areAllZeros = (F0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testTransform_02_Real()
{
    try
    {
        arma::Col<klab::DoubleReal> f(33);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<33; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));       


        klab::DoubleReal precision = 1e-5;

        TFFT1D<klab::DoubleReal> fft;
        fft.transform(f, F);

        TEST_ASSERT(F.n_rows==33)
        TEST_ASSERT(klab::Equals(F[0], 1.4218, precision))
        TEST_ASSERT(klab::Equals(F[1], 1.45925, precision))
        TEST_ASSERT(klab::Equals(F[2], 1.59073, precision))
        TEST_ASSERT(klab::Equals(F[3], 1.90453, precision))
        TEST_ASSERT(klab::Equals(F[4], 2.80013, precision))
        TEST_ASSERT(klab::Equals(F[5], 11.089021, precision))
        TEST_ASSERT(klab::Equals(F[6], -2.86199, precision))
        TEST_ASSERT(klab::Equals(F[7], -0.874769, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.34719, precision))
        TEST_ASSERT(klab::Equals(F[9], -0.109664, precision))
        TEST_ASSERT(klab::Equals(F[10], 0.0216109, precision))
        TEST_ASSERT(klab::Equals(F[11], 0.102238, precision))
        TEST_ASSERT(klab::Equals(F[12], 0.154638, precision))
        TEST_ASSERT(klab::Equals(F[13], 0.189455, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.212266, precision))
        TEST_ASSERT(klab::Equals(F[15], 0.226134, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.232706, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.217111, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.485223, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.910145, precision))
        TEST_ASSERT(klab::Equals(F[20], 1.906, precision))
        TEST_ASSERT(klab::Equals(F[21], 10.381073, precision))
        TEST_ASSERT(klab::Equals(F[22], -3.69016, precision))
        TEST_ASSERT(klab::Equals(F[23], -1.61671, precision))
        TEST_ASSERT(klab::Equals(F[24], -1.02708, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.734645, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.551983, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.421764, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.320368, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.236123, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.162444, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.0951707, precision))
        TEST_ASSERT(klab::Equals(F[32], -0.0313582, precision))


        F.fill(0.0);

        TFFT1D<klab::DoubleReal> fft2(true);
        fft2.transform(f, F);

        TEST_ASSERT(F.n_rows==33)
        TEST_ASSERT(klab::Equals(F[0], 1.4218, precision))
        TEST_ASSERT(klab::Equals(F[1], 1.45925, precision))
        TEST_ASSERT(klab::Equals(F[2], 1.59073, precision))
        TEST_ASSERT(klab::Equals(F[3], 1.90453, precision))
        TEST_ASSERT(klab::Equals(F[4], 2.80013, precision))
        TEST_ASSERT(klab::Equals(F[5], 11.089021, precision))
        TEST_ASSERT(klab::Equals(F[6], -2.86199, precision))
        TEST_ASSERT(klab::Equals(F[7], -0.874769, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.34719, precision))
        TEST_ASSERT(klab::Equals(F[9], -0.109664, precision))
        TEST_ASSERT(klab::Equals(F[10], 0.0216109, precision))
        TEST_ASSERT(klab::Equals(F[11], 0.102238, precision))
        TEST_ASSERT(klab::Equals(F[12], 0.154638, precision))
        TEST_ASSERT(klab::Equals(F[13], 0.189455, precision))
        TEST_ASSERT(klab::Equals(F[14], 0.212266, precision))
        TEST_ASSERT(klab::Equals(F[15], 0.226134, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.232706, precision))
        TEST_ASSERT(klab::Equals(F[17], 0.217111, precision))
        TEST_ASSERT(klab::Equals(F[18], 0.485223, precision))
        TEST_ASSERT(klab::Equals(F[19], 0.910145, precision))
        TEST_ASSERT(klab::Equals(F[20], 1.906, precision))
        TEST_ASSERT(klab::Equals(F[21], 10.381073, precision))
        TEST_ASSERT(klab::Equals(F[22], -3.69016, precision))
        TEST_ASSERT(klab::Equals(F[23], -1.61671, precision))
        TEST_ASSERT(klab::Equals(F[24], -1.02708, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.734645, precision))
        TEST_ASSERT(klab::Equals(F[26], -0.551983, precision))
        TEST_ASSERT(klab::Equals(F[27], -0.421764, precision))
        TEST_ASSERT(klab::Equals(F[28], -0.320368, precision))
        TEST_ASSERT(klab::Equals(F[29], -0.236123, precision))
        TEST_ASSERT(klab::Equals(F[30], -0.162444, precision))
        TEST_ASSERT(klab::Equals(F[31], -0.0951707, precision))
        TEST_ASSERT(klab::Equals(F[32], -0.0313582, precision))          


        // Limit cases.
        arma::Col<klab::DoubleReal> f0;
        arma::Col<klab::DoubleReal> F0;

        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)

        TFFT1D<klab::DoubleReal> fft0;
        fft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)

        TFFT1D<klab::DoubleReal> fft00(true);
        fft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)


        f0.set_size(33);
        f0.fill(0.0);
        fft0.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 33)
        TEST_ASSERT(F0.n_rows == 33)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<33 && areAllZeros; ++i)
            areAllZeros = (F0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(33);
        f0.fill(0.0);
        fft00.transform(f0, F0);
        TEST_ASSERT(f0.n_rows == 33)
        TEST_ASSERT(F0.n_rows == 33)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<33 && areAllZeros; ++i)
            areAllZeros = (F0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testInvert()
{
    try
    {
        arma::Col<std::complex<klab::DoubleReal> > f(32);
        arma::Col<std::complex<klab::DoubleReal> > F;
        arma::Col<std::complex<klab::DoubleReal> > fR;

        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));  


        klab::DoubleReal precision = 1e-5;

        TFFT1D<std::complex<klab::DoubleReal> > fft;
        fft.transform(f, F);
        fft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==32)
        TEST_ASSERT(klab::Equals(fR[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fR[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fR[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fR[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fR[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fR[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fR[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fR[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fR[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fR[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fR[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fR[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fR[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fR[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fR[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fR[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fR[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fR[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fR[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fR[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fR[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fR[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fR[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fR[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fR[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fR[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fR[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fR[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fR[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fR[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fR[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fR[31], f[31], precision))


        F.fill(0.0);
        fR.fill(0.0);

        TFFT1D<std::complex<klab::DoubleReal> > fft2(true);
        fft2.transform(f, F);
        fft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==32)
        TEST_ASSERT(klab::Equals(fR[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fR[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fR[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fR[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fR[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fR[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fR[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fR[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fR[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fR[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fR[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fR[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fR[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fR[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fR[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fR[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fR[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fR[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fR[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fR[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fR[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fR[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fR[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fR[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fR[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fR[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fR[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fR[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fR[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fR[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fR[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fR[31], f[31], precision))


        // Limit cases.
        arma::Col<std::complex<klab::DoubleReal> > f0;
        arma::Col<std::complex<klab::DoubleReal> > F0;
        arma::Col<std::complex<klab::DoubleReal> > fR0;

        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        TFFT1D<std::complex<klab::DoubleReal> > fft0;
        fft0.transform(f0, F0);
        fft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        TFFT1D<std::complex<klab::DoubleReal> > fft00(true);
        fft00.transform(f0, F0);
        fft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        f0.set_size(32);
        f0.fill(0.0);
        fft0.transform(f0, F0);
        fft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 32)
        TEST_ASSERT(F0.n_rows == 32)
        TEST_ASSERT(fR0.n_rows == 32)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<32 && areAllZeros; ++i)
            areAllZeros = (fR0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(32);
        f0.fill(0.0);
        fft00.transform(f0, F0);
        fft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 32)
        TEST_ASSERT(F0.n_rows == 32)
        TEST_ASSERT(fR0.n_rows == 32)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<32 && areAllZeros; ++i)
            areAllZeros = (fR0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testInvert_Real()
{
    try
    {
        arma::Col<klab::DoubleReal> f(32);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fR;

        for(klab::UInt32 i=0; i<32; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));  


        klab::DoubleReal precision = 1e-5;

        TFFT1D<klab::DoubleReal> fft;
        fft.transform(f, F);
        fft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==32)
        TEST_ASSERT(klab::Equals(fR[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fR[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fR[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fR[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fR[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fR[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fR[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fR[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fR[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fR[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fR[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fR[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fR[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fR[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fR[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fR[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fR[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fR[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fR[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fR[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fR[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fR[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fR[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fR[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fR[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fR[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fR[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fR[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fR[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fR[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fR[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fR[31], f[31], precision))


        F.fill(0.0);
        fR.fill(0.0);

        TFFT1D<klab::DoubleReal> fft2(true);
        fft2.transform(f, F);
        fft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==32)
        TEST_ASSERT(klab::Equals(fR[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fR[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fR[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fR[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fR[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fR[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fR[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fR[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fR[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fR[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fR[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fR[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fR[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fR[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fR[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fR[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fR[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fR[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fR[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fR[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fR[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fR[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fR[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fR[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fR[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fR[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fR[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fR[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fR[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fR[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fR[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fR[31], f[31], precision))


        // Limit cases.
        arma::Col<klab::DoubleReal> f0;
        arma::Col<klab::DoubleReal> F0;
        arma::Col<klab::DoubleReal> fR0;

        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        TFFT1D<klab::DoubleReal> fft0;
        fft0.transform(f0, F0);
        fft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        TFFT1D<klab::DoubleReal> fft00(true);
        fft00.transform(f0, F0);
        fft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        f0.set_size(32);
        f0.fill(0.0);
        fft0.transform(f0, F0);
        fft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 32)
        TEST_ASSERT(F0.n_rows == 32)
        TEST_ASSERT(fR0.n_rows == 32)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<32 && areAllZeros; ++i)
            areAllZeros = (fR0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(32);
        f0.fill(0.0);
        fft00.transform(f0, F0);
        fft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 32)
        TEST_ASSERT(F0.n_rows == 32)
        TEST_ASSERT(fR0.n_rows == 32)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<32 && areAllZeros; ++i)
            areAllZeros = (fR0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testInvert_02()
{
    try
    {
        arma::Col<std::complex<klab::DoubleReal> > f(33);
        arma::Col<std::complex<klab::DoubleReal> > F;
        arma::Col<std::complex<klab::DoubleReal> > fR;

        for(klab::UInt32 i=0; i<33; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));  


        klab::DoubleReal precision = 1e-5;

        TFFT1D<std::complex<klab::DoubleReal> > fft;
        fft.transform(f, F);
        fft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==33)
        TEST_ASSERT(klab::Equals(fR[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fR[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fR[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fR[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fR[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fR[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fR[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fR[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fR[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fR[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fR[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fR[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fR[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fR[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fR[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fR[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fR[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fR[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fR[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fR[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fR[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fR[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fR[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fR[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fR[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fR[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fR[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fR[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fR[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fR[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fR[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fR[31], f[31], precision))
        TEST_ASSERT(klab::Equals(fR[32], f[32], precision))


        F.fill(0.0);
        fR.fill(0.0);

        TFFT1D<std::complex<klab::DoubleReal> > fft2(true);
        fft2.transform(f, F);
        fft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==33)
        TEST_ASSERT(klab::Equals(fR[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fR[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fR[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fR[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fR[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fR[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fR[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fR[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fR[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fR[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fR[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fR[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fR[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fR[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fR[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fR[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fR[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fR[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fR[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fR[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fR[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fR[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fR[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fR[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fR[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fR[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fR[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fR[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fR[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fR[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fR[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fR[31], f[31], precision))
        TEST_ASSERT(klab::Equals(fR[32], f[32], precision))


        // Limit cases.
        arma::Col<std::complex<klab::DoubleReal> > f0;
        arma::Col<std::complex<klab::DoubleReal> > F0;
        arma::Col<std::complex<klab::DoubleReal> > fR0;

        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        TFFT1D<std::complex<klab::DoubleReal> > fft0;
        fft0.transform(f0, F0);
        fft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        TFFT1D<std::complex<klab::DoubleReal> > fft00(true);
        fft00.transform(f0, F0);
        fft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)


        f0.set_size(33);
        f0.fill(0.0);
        fft0.transform(f0, F0);
        fft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 33)
        TEST_ASSERT(F0.n_rows == 33)
        TEST_ASSERT(fR0.n_rows == 33)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<33 && areAllZeros; ++i)
            areAllZeros = (fR0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(33);
        f0.fill(0.0);
        fft00.transform(f0, F0);
        fft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 33)
        TEST_ASSERT(F0.n_rows == 33)
        TEST_ASSERT(fR0.n_rows == 33)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<33 && areAllZeros; ++i)
            areAllZeros = (fR0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFFT1DUnitTest::testInvert_02_Real()
{
    try
    {
        arma::Col<klab::DoubleReal> f(33);
        arma::Col<klab::DoubleReal> F;
        arma::Col<klab::DoubleReal> fR;

        for(klab::UInt32 i=0; i<33; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i));  


        klab::DoubleReal precision = 1e-5;

        TFFT1D<klab::DoubleReal> fft;
        fft.transform(f, F);
        fft.invert(F, fR);

        TEST_ASSERT(fR.n_rows==33)
        TEST_ASSERT(klab::Equals(fR[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fR[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fR[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fR[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fR[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fR[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fR[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fR[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fR[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fR[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fR[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fR[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fR[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fR[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fR[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fR[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fR[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fR[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fR[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fR[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fR[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fR[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fR[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fR[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fR[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fR[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fR[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fR[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fR[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fR[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fR[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fR[31], f[31], precision))
        TEST_ASSERT(klab::Equals(fR[32], f[32], precision))


        F.fill(0.0);
        fR.fill(0.0);

        TFFT1D<klab::DoubleReal> fft2(true);
        fft2.transform(f, F);
        fft2.invert(F, fR);

        TEST_ASSERT(fR.n_rows==33)
        TEST_ASSERT(klab::Equals(fR[0], f[0], precision))
        TEST_ASSERT(klab::Equals(fR[1], f[1], precision))
        TEST_ASSERT(klab::Equals(fR[2], f[2], precision))
        TEST_ASSERT(klab::Equals(fR[3], f[3], precision))
        TEST_ASSERT(klab::Equals(fR[4], f[4], precision))
        TEST_ASSERT(klab::Equals(fR[5], f[5], precision))
        TEST_ASSERT(klab::Equals(fR[6], f[6], precision))
        TEST_ASSERT(klab::Equals(fR[7], f[7], precision))
        TEST_ASSERT(klab::Equals(fR[8], f[8], precision))
        TEST_ASSERT(klab::Equals(fR[9], f[9], precision))
        TEST_ASSERT(klab::Equals(fR[10], f[10], precision))
        TEST_ASSERT(klab::Equals(fR[11], f[11], precision))
        TEST_ASSERT(klab::Equals(fR[12], f[12], precision))
        TEST_ASSERT(klab::Equals(fR[13], f[13], precision))
        TEST_ASSERT(klab::Equals(fR[14], f[14], precision))
        TEST_ASSERT(klab::Equals(fR[15], f[15], precision))
        TEST_ASSERT(klab::Equals(fR[16], f[16], precision))
        TEST_ASSERT(klab::Equals(fR[17], f[17], precision))
        TEST_ASSERT(klab::Equals(fR[18], f[18], precision))
        TEST_ASSERT(klab::Equals(fR[19], f[19], precision))
        TEST_ASSERT(klab::Equals(fR[20], f[20], precision))
        TEST_ASSERT(klab::Equals(fR[21], f[21], precision))
        TEST_ASSERT(klab::Equals(fR[22], f[22], precision))
        TEST_ASSERT(klab::Equals(fR[23], f[23], precision))
        TEST_ASSERT(klab::Equals(fR[24], f[24], precision))
        TEST_ASSERT(klab::Equals(fR[25], f[25], precision))
        TEST_ASSERT(klab::Equals(fR[26], f[26], precision))
        TEST_ASSERT(klab::Equals(fR[27], f[27], precision))
        TEST_ASSERT(klab::Equals(fR[28], f[28], precision))
        TEST_ASSERT(klab::Equals(fR[29], f[29], precision))
        TEST_ASSERT(klab::Equals(fR[30], f[30], precision))
        TEST_ASSERT(klab::Equals(fR[31], f[31], precision))
        TEST_ASSERT(klab::Equals(fR[32], f[32], precision))


        // Limit cases.
        arma::Col<klab::DoubleReal> f0;
        arma::Col<klab::DoubleReal> F0;
        arma::Col<klab::DoubleReal> fR0;

        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        TFFT1D<klab::DoubleReal> fft0;
        fft0.transform(f0, F0);
        fft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)

        TFFT1D<klab::DoubleReal> fft00(true);
        fft00.transform(f0, F0);
        fft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 0)
        TEST_ASSERT(F0.n_rows == 0)
        TEST_ASSERT(fR0.n_rows == 0)


        f0.set_size(33);
        f0.fill(0.0);
        fft0.transform(f0, F0);
        fft0.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 33)
        TEST_ASSERT(F0.n_rows == 33)
        TEST_ASSERT(fR0.n_rows == 33)

        bool areAllZeros = true;
        for(klab::UInt32 i=0; i<33 && areAllZeros; ++i)
            areAllZeros = (fR0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)


        f0.set_size(33);
        f0.fill(0.0);
        fft00.transform(f0, F0);
        fft00.invert(F0, fR0);
        TEST_ASSERT(f0.n_rows == 33)
        TEST_ASSERT(F0.n_rows == 33)
        TEST_ASSERT(fR0.n_rows == 33)

        areAllZeros = true;
        for(klab::UInt32 i=0; i<33 && areAllZeros; ++i)
            areAllZeros = (fR0[i]==0.0?true:false);
        TEST_ASSERT(areAllZeros == true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
