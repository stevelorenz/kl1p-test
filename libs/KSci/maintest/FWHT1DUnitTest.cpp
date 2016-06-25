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

#include "FWHT1DUnitTest.h"
#include "../include/FWHT1D.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KFWHT1DUnitTest::KFWHT1DUnitTest() : Test::Suite()
{
    TEST_ADD(KFWHT1DUnitTest::testDefaultConstructor)  
    TEST_ADD(KFWHT1DUnitTest::testCopyConstructor)
    TEST_ADD(KFWHT1DUnitTest::testAffectationOperator)

    TEST_ADD(KFWHT1DUnitTest::testTransform)
    TEST_ADD(KFWHT1DUnitTest::testInvert)   

    TEST_ADD(KFWHT1DUnitTest::testWalshHadamardMatrix)
}

// ---------------------------------------------------------------------------------------------------- //

KFWHT1DUnitTest::~KFWHT1DUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT1DUnitTest::testDefaultConstructor()
{
    try
    {
        TFWHT1D<klab::DoubleReal> fwht;
        TEST_ASSERT(true)

        TFWHT1D<std::complex<klab::DoubleReal> > cfwht;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT1DUnitTest::testCopyConstructor()
{
    try
    {
        TFWHT1D<klab::DoubleReal> fwht;
        TFWHT1D<klab::DoubleReal> fwhtCopy(fwht);
        TEST_ASSERT(true)

        TFWHT1D<std::complex<klab::DoubleReal> > cfwht;
        TFWHT1D<std::complex<klab::DoubleReal> > cfwhtCopy(cfwht);
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT1DUnitTest::testAffectationOperator()
{
    try
    {
        TFWHT1D<klab::DoubleReal> fwht;
        TFWHT1D<klab::DoubleReal> fwhtCopy; 
        fwhtCopy = fwht;
        TEST_ASSERT(true)

        TFWHT1D<std::complex<klab::DoubleReal> > cfwht;
        TFWHT1D<std::complex<klab::DoubleReal> > cfwhtCopy;
        cfwhtCopy = cfwht;
        TEST_ASSERT(true)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT1DUnitTest::testTransform()
{
    try
    {
        klab::UInt32 n = 32;
        klab::DoubleReal precision = 1e-12;

        arma::Col<klab::DoubleReal> f(n);
        arma::Col<klab::DoubleReal> F;

        for(klab::UInt32 i=0; i<n; ++i)
            f[i] = klab::Cos(klab::DoubleReal(i)); 

        TFWHT1D<klab::DoubleReal> fwht;

        fwht.transform(f, F);
        TEST_ASSERT(F.n_rows == n)
        TEST_ASSERT(klab::Equals(F[0], 0.58757820446552489, precision))
        TEST_ASSERT(klab::Equals(F[1], -0.067734564717571999, precision))
        TEST_ASSERT(klab::Equals(F[2], -0.19309876172713025, precision))
        TEST_ASSERT(klab::Equals(F[3], -0.49992077172600569, precision))
        TEST_ASSERT(klab::Equals(F[4], 0.27091716911427977, precision))
        TEST_ASSERT(klab::Equals(F[5], 0.70138782375426556, precision))
        TEST_ASSERT(klab::Equals(F[6], 1.9995274321486791, precision))
        TEST_ASSERT(klab::Equals(F[7], -0.23050058567205056, precision))
        TEST_ASSERT(klab::Equals(F[8], -0.14355512200413756, precision))
        TEST_ASSERT(klab::Equals(F[9], -0.37165534742756701, precision))
        TEST_ASSERT(klab::Equals(F[10], -1.0595209060066728, precision))
        TEST_ASSERT(klab::Equals(F[11], 0.12213895415472353, precision))
        TEST_ASSERT(klab::Equals(F[12], 1.4865056715296125, precision))
        TEST_ASSERT(klab::Equals(F[13], -0.17136070372597967, precision))
        TEST_ASSERT(klab::Equals(F[14], -0.48851778757488873, precision))
        TEST_ASSERT(klab::Equals(F[15], -1.2647423897592329, precision))
        TEST_ASSERT(klab::Equals(F[16], 0.84307778966216573, precision))
        TEST_ASSERT(klab::Equals(F[17], 2.182676343769367, precision))
        TEST_ASSERT(klab::Equals(F[18], 6.2224080274280471, precision))
        TEST_ASSERT(klab::Equals(F[19], -0.717303834672264, precision))
        TEST_ASSERT(klab::Equals(F[20], -8.7300257794865317, precision))
        TEST_ASSERT(klab::Equals(F[21], 1.0063758179808335, precision))
        TEST_ASSERT(klab::Equals(F[22], 2.8689919997937592, precision))
        TEST_ASSERT(klab::Equals(F[23], 7.4276431489468155, precision))
        TEST_ASSERT(klab::Equals(F[24], 4.6259154411317951, precision))
        TEST_ASSERT(klab::Equals(F[25], -0.53326411096268189, precision))
        TEST_ASSERT(klab::Equals(F[26], -1.5202377092075587, precision))
        TEST_ASSERT(klab::Equals(F[27], -3.9358015659778234, precision))        
        TEST_ASSERT(klab::Equals(F[28], 2.1328904073517068, precision))
        TEST_ASSERT(klab::Equals(F[29], 5.5219215748106416, precision))       
        TEST_ASSERT(klab::Equals(F[30], 15.741980817271585, precision))
        TEST_ASSERT(klab::Equals(F[31], -1.8146966826657049, precision))


        // Limit cases.
        fwht.transform(arma::Col<klab::DoubleReal>(), F);
        TEST_ASSERT(F.n_rows == 0)

        try                                 {fwht.transform(arma::Col<klab::DoubleReal>(31), F); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT1DUnitTest::testInvert()
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

        TFWHT1D<klab::DoubleReal> fwht;

        fwht.transform(f, F);
        fwht.invert(F, fr);
        TEST_ASSERT(fr.n_rows==n)
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
        fwht.invert(arma::Col<klab::DoubleReal>(), fr);
        TEST_ASSERT(fr.n_rows == 0)

        try                                 {fwht.invert(arma::Col<klab::DoubleReal>(31), fr); TEST_ASSERT(false)}
        catch(KSizePowerOf2FWHTException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KFWHT1DUnitTest::testWalshHadamardMatrix()
{
    try
    {
        klab::UInt32 n = 2;
        klab::DoubleReal precision = 1e-12;


        arma::Mat<klab::DoubleReal> fwhtMatrix(n, n);
        arma::Mat<std::complex<klab::DoubleReal> > cfwhtMatrix(n, n);

        TFWHT1D<klab::DoubleReal> fwht;
        TFWHT1D<std::complex<klab::DoubleReal> > cfwht;


        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<klab::DoubleReal> base(n);
            arma::Col<klab::DoubleReal> col;
            base.fill(klab::TTypeInfo<klab::DoubleReal>::ZERO);
            base[j] = klab::TTypeInfo<klab::DoubleReal>::UNIT;

            fwht.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                fwhtMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(fwhtMatrix.n_cols==2 && fwhtMatrix.n_rows==2)
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 1),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 1), -1.0, precision))

       
        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(n);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(klab::TTypeInfo<std::complex<klab::DoubleReal> >::ZERO);
            base[j] = klab::TTypeInfo<std::complex<klab::DoubleReal> >::UNIT;

            cfwht.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                cfwhtMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(cfwhtMatrix.n_cols==2 && cfwhtMatrix.n_rows==2)
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 1), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 1), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))


        n = 4;
        fwhtMatrix.set_size(n, n);
        cfwhtMatrix.set_size(n, n);


        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<klab::DoubleReal> base(n);
            arma::Col<klab::DoubleReal> col;
            base.fill(klab::TTypeInfo<klab::DoubleReal>::ZERO);
            base[j] = klab::TTypeInfo<klab::DoubleReal>::UNIT;

            fwht.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                fwhtMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(fwhtMatrix.n_cols==4 && fwhtMatrix.n_rows==4)
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 1),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 2),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 3),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 1), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 2),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 3), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 1),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 2), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 3), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 1), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 2), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 3),  1.0, precision))

       
        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(n);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(klab::TTypeInfo<std::complex<klab::DoubleReal> >::ZERO);
            base[j] = klab::TTypeInfo<std::complex<klab::DoubleReal> >::UNIT;

            cfwht.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                cfwhtMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(cfwhtMatrix.n_cols==4 && cfwhtMatrix.n_rows==4)
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 1), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 2), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 3), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 1), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 2), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 3), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 1), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 2), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 3), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 1), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 2), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 3), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))


        n = 8;
        fwhtMatrix.set_size(n, n);
        cfwhtMatrix.set_size(n, n);
        

        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<klab::DoubleReal> base(n);
            arma::Col<klab::DoubleReal> col;
            base.fill(klab::TTypeInfo<klab::DoubleReal>::ZERO);
            base[j] = klab::TTypeInfo<klab::DoubleReal>::UNIT;

            fwht.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                fwhtMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(fwhtMatrix.n_cols==8 && fwhtMatrix.n_rows==8)
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 1),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 2),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 3),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 4),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 5),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 6),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(0, 7),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 1), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 2),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 3), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 4),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 5), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 6),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(1, 7), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 1),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 2), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 3), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 4),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 5),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 6), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(2, 7), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 1), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 2), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 3),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 4),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 5), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 6), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(3, 7),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(4, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(4, 1),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(4, 2),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(4, 3),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(4, 4), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(4, 5), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(4, 6), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(4, 7), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(5, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(5, 1), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(5, 2),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(5, 3), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(5, 4), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(5, 5),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(5, 6), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(5, 7),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(6, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(6, 1),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(6, 2), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(6, 3), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(6, 4), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(6, 5), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(6, 6),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(6, 7),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(7, 0),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(7, 1), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(7, 2), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(7, 3),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(7, 4), -1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(7, 5),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(7, 6),  1.0, precision))
        TEST_ASSERT(klab::Equals(fwhtMatrix(7, 7), -1.0, precision))

       
        for(klab::UInt32 j=0; j<n; ++j)
        {
            arma::Col<std::complex<klab::DoubleReal> > base(n);
            arma::Col<std::complex<klab::DoubleReal> > col;
            base.fill(klab::TTypeInfo<std::complex<klab::DoubleReal> >::ZERO);
            base[j] = klab::TTypeInfo<std::complex<klab::DoubleReal> >::UNIT;

            cfwht.transform(base, col);

            for(klab::UInt32 i=0; i<n; ++i)
                cfwhtMatrix(i, j) = col[i];
        } 

        TEST_ASSERT(cfwhtMatrix.n_cols==8 && cfwhtMatrix.n_rows==8)
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 1), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 2), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 3), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 4), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 5), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 6), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(0, 7), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 1), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 2), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 3), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 4), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 5), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 6), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(1, 7), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 1), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 2), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 3), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 4), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 5), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 6), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(2, 7), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 1), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 2), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 3), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 4), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 5), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 6), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(3, 7), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(4, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(4, 1), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(4, 2), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(4, 3), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(4, 4), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(4, 5), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(4, 6), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(4, 7), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(5, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(5, 1), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(5, 2), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(5, 3), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(5, 4), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(5, 5), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(5, 6), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(5, 7), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(6, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(6, 1), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(6, 2), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(6, 3), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(6, 4), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(6, 5), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(6, 6), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(6, 7), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(7, 0), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(7, 1), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(7, 2), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(7, 3), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(7, 4), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(7, 5), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(7, 6), std::complex<klab::DoubleReal>( 1.0, 0.0), precision))
        TEST_ASSERT(klab::Equals(cfwhtMatrix(7, 7), std::complex<klab::DoubleReal>(-1.0, 0.0), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
