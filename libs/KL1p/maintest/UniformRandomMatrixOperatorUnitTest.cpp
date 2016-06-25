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

#include "UniformRandomMatrixOperatorUnitTest.h"
#include "../include/UniformRandomMatrixOperator.h"

using namespace klab;
using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KUniformRandomMatrixOperatorUnitTest::KUniformRandomMatrixOperatorUnitTest() : Test::Suite()
{
    TEST_ADD(KUniformRandomMatrixOperatorUnitTest::testMNConstructor)  
    TEST_ADD(KUniformRandomMatrixOperatorUnitTest::testCopyConstructor)

    TEST_ADD(KUniformRandomMatrixOperatorUnitTest::testApply)
    TEST_ADD(KUniformRandomMatrixOperatorUnitTest::testApply_Complex)
    TEST_ADD(KUniformRandomMatrixOperatorUnitTest::testApplyAdjoint)
    TEST_ADD(KUniformRandomMatrixOperatorUnitTest::testApplyAdjoint_Complex)
}

// ---------------------------------------------------------------------------------------------------- //

KUniformRandomMatrixOperatorUnitTest::~KUniformRandomMatrixOperatorUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KUniformRandomMatrixOperatorUnitTest::testMNConstructor()
{
    try
    {
        klab::DoubleReal precision = 1e-15;

        klab::KRandom::Instance().setSeed(123456);
        TUniformRandomMatrixOperator<klab::DoubleReal> op(4, 8);

        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)
        TEST_ASSERT(klab::Equals(op.matrix()(0, 0), 0.0069278208608991873, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 1), 5.4130128127604662e-005, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 2), 0.1229823569165409, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 3), 0.054233764566486542, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 4), 0.73650439362104136, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 5), 0.25000385258533059, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 6), 0.96725137532384631, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 7), 0.67983326699207458, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 0), 0.9389106388978099, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 1), 0.39060028238154043, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 2), 0.68616019774878956, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 3), 0.547523999071439, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 4), 0.66710455267951352, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 5), 0.70895730322537653, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 6), 0.96133157102462985, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 7), 0.82198063657725351, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 0), 0.14955592387200303, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 1), 0.19106159364068509, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 2), 0.61045346052161598, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 3), 0.46123335061163911, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 4), 0.93938974508717021, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 5), 0.61303529620900243, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 6), 0.80414212522849149, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 7), 0.59243277309653508, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 0), 0.70621952634556151, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 1), 0.24825706254121543, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 2), 0.29104290129083132, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 3), 0.65165154614880128, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 4), 0.55273285407672912, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 5), 0.53132136196612001, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 6), 0.28478099913222293, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 7), 0.75513695717817497, precision))


        klab::KRandom::Instance().setSeed(123456);
        TUniformRandomMatrixOperator<klab::DoubleReal> op2(4, 8, -1.0, 2.0);

        TEST_ASSERT(op2.matrix().n_rows==4 && op2.matrix().n_cols==8)
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 0), -0.97921653741730241, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 1), -0.99983760961561718, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 2), -0.63105292925037726, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 3), -0.83729870630054037, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 4), 1.2095131808631239, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 5), -0.24998844224400818, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 6), 1.9017541259715389, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(0, 7), 1.0394998009762237, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 0), 1.8167319166934295, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 1), 0.17180084714462129, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 2), 1.0584805932463688, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 3), 0.64257199721431713, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 4), 1.0013136580385407, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 5), 1.1268719096761295, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 6), 1.8839947130738897, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(1, 7), 1.4659419097317605, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 0), -0.55133222838399087, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 1), -0.42681521907794473, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 2), 0.83136038156484782, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 3), 0.3837000518349174, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 4), 1.8181692352615109, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 5), 0.8391058886270073, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 6), 1.4124263756854747, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(2, 7), 0.77729831928960524, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 0), 1.1186585790366843, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 1), -0.25522881237635375, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 2), -0.12687129612750603, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 3), 0.95495463844640383, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 4), 0.65819856223018736, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 5), 0.59396408589836014, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 6), -0.14565700260333125, precision))
        TEST_ASSERT(klab::Equals(op2.matrix()(3, 7), 1.2654108715345247, precision))

		
		klab::KRandom::Instance().setSeed(123456);	
        TUniformRandomMatrixOperator<klab::DoubleReal> op3(4, 8, -1.0, 2.0, true);

        TEST_ASSERT(op3.matrix().n_rows==4 && op3.matrix().n_cols==8)
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 0), -0.4060817154586257, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 1), -0.88494936254471435, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 2), -0.42297659820775296, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 3), -0.56798565593799555, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 4), 0.48557537572194348, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 5), -0.16173025238510139, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 6), 0.62759483373768421, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(0, 7), 0.44588670341399733, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 0), 0.7533998712941562, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 1), 0.15205974320542281, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 2), 0.70946904744124628, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 3), 0.43589184430694522, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 4), 0.40199086988916488, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 5), 0.72903081727159247, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 6), 0.62173407832636884, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(1, 7), 0.62880628251478132, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 0), -0.22863782272335817, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 1), -0.37777120245818574, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 2), 0.55723691275265341, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 3), 0.26028479918213604, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 4), 0.72992855597337758, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 5), 0.54286032557060493, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 6), 0.4661125664508281, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(2, 7), 0.33341707697470757, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 0), 0.46390841803577021, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 1), -0.2259012590077816, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 2), -0.085038174705832539, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 3), 0.64779813061639036, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 4), 0.26424268805941581, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 5), 0.38426561107278656, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 6), -0.048068034181267857, precision))
        TEST_ASSERT(klab::Equals(op3.matrix()(3, 7), 0.54278979317059817, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KUniformRandomMatrixOperatorUnitTest::testCopyConstructor()
{
    try
    {
        klab::KRandom::Instance().setSeed(123456);

        klab::DoubleReal precision = 1e-15;

        TUniformRandomMatrixOperator<klab::DoubleReal> op(4, 8);

        TUniformRandomMatrixOperator<klab::DoubleReal> op2(op);
        TEST_ASSERT(op2.matrix().n_rows==4 && op2.matrix().n_cols==8)
        TEST_ASSERT(klab::Equals(op.matrix()(0, 0), 0.0069278208608991873, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 1), 5.4130128127604662e-005, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 2), 0.1229823569165409, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 3), 0.054233764566486542, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 4), 0.73650439362104136, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 5), 0.25000385258533059, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 6), 0.96725137532384631, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(0, 7), 0.67983326699207458, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 0), 0.9389106388978099, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 1), 0.39060028238154043, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 2), 0.68616019774878956, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 3), 0.547523999071439, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 4), 0.66710455267951352, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 5), 0.70895730322537653, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 6), 0.96133157102462985, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(1, 7), 0.82198063657725351, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 0), 0.14955592387200303, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 1), 0.19106159364068509, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 2), 0.61045346052161598, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 3), 0.46123335061163911, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 4), 0.93938974508717021, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 5), 0.61303529620900243, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 6), 0.80414212522849149, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(2, 7), 0.59243277309653508, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 0), 0.70621952634556151, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 1), 0.24825706254121543, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 2), 0.29104290129083132, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 3), 0.65165154614880128, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 4), 0.55273285407672912, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 5), 0.53132136196612001, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 6), 0.28478099913222293, precision))
        TEST_ASSERT(klab::Equals(op.matrix()(3, 7), 0.75513695717817497, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KUniformRandomMatrixOperatorUnitTest::testApply()
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

        TUniformRandomMatrixOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], 17.984889056953435, precision))
        TEST_ASSERT(klab::Equals(y[1], 26.863120465733278, precision))
        TEST_ASSERT(klab::Equals(y[2], 22.951590459226367, precision))
        TEST_ASSERT(klab::Equals(y[3], 18.668623633427018, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KUniformRandomMatrixOperatorUnitTest::testApply_Complex()
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

        TUniformRandomMatrixOperator<std::complex<klab::DoubleReal> > op(4, 8, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(27.503310034787908, 20.354557906517392), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(18.829933592158394, 20.233905056664234), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(17.055743813069263, 11.308728980641233), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(20.700630015577509, 19.597791797384190), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KUniformRandomMatrixOperatorUnitTest::testApplyAdjoint()
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

        TUniformRandomMatrixOperator<klab::DoubleReal> op(4, 8);
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], 17.984889056953435, precision))
        TEST_ASSERT(klab::Equals(y[1], 26.863120465733278, precision))
        TEST_ASSERT(klab::Equals(y[2], 22.951590459226367, precision))
        TEST_ASSERT(klab::Equals(y[3], 18.668623633427018, precision))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], 41.963358544244016, precision))
        TEST_ASSERT(klab::Equals(xr[1], 19.513501078564005, precision))
        TEST_ASSERT(klab::Equals(xr[2], 40.088476301712561, precision))
        TEST_ASSERT(klab::Equals(xr[3], 38.435067808373169, precision))
        TEST_ASSERT(klab::Equals(xr[4], 63.045710104528254, precision))
        TEST_ASSERT(klab::Equals(xr[5], 47.530270584747683, precision))
        TEST_ASSERT(klab::Equals(xr[6], 66.993084495339289, precision))
        TEST_ASSERT(klab::Equals(xr[7], 62.002332772939646, precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KUniformRandomMatrixOperatorUnitTest::testApplyAdjoint_Complex()
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

        TUniformRandomMatrixOperator<std::complex<klab::DoubleReal> > op(4, 8, std::complex<klab::DoubleReal>(0.0, 0.0), std::complex<klab::DoubleReal>(1.0, 1.0));
        TEST_ASSERT(op.matrix().n_rows==4 && op.matrix().n_cols==8)

        op.apply(x, y);
        TEST_ASSERT(y.n_rows == 4)
        TEST_ASSERT(klab::Equals(y[0], std::complex<klab::DoubleReal>(27.503310034787908, 20.354557906517392), precision))
        TEST_ASSERT(klab::Equals(y[1], std::complex<klab::DoubleReal>(18.829933592158394, 20.233905056664234), precision))
        TEST_ASSERT(klab::Equals(y[2], std::complex<klab::DoubleReal>(17.055743813069263, 11.308728980641233), precision))
        TEST_ASSERT(klab::Equals(y[3], std::complex<klab::DoubleReal>(20.700630015577509, 19.597791797384190), precision))

        op.applyAdjoint(y, xr);
        TEST_ASSERT(xr.n_rows == 8)
        TEST_ASSERT(klab::Equals(xr[0], std::complex<klab::DoubleReal>(25.970096102893290, -6.7232702570212197), precision))
        TEST_ASSERT(klab::Equals(xr[1], std::complex<klab::DoubleReal>(66.784585207191782, -4.8681184201679111), precision))
        TEST_ASSERT(klab::Equals(xr[2], std::complex<klab::DoubleReal>(66.247262500239344,  10.127071386012977), precision))
        TEST_ASSERT(klab::Equals(xr[3], std::complex<klab::DoubleReal>(107.83442986064173,  14.123356241134697), precision))
        TEST_ASSERT(klab::Equals(xr[4], std::complex<klab::DoubleReal>(93.023038634095599,  11.697771815495301), precision))
        TEST_ASSERT(klab::Equals(xr[5], std::complex<klab::DoubleReal>(86.452173065543647, -20.964444169580922), precision))
        TEST_ASSERT(klab::Equals(xr[6], std::complex<klab::DoubleReal>(88.238613308011949,  4.1396629376573593), precision))
        TEST_ASSERT(klab::Equals(xr[7], std::complex<klab::DoubleReal>(96.871922467042509, -4.0118708311016444), precision))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
