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

#include "GaussUtilUnitTest.h"
#include "../include/GaussUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KGaussUtilUnitTest::KGaussUtilUnitTest() : Test::Suite()
{
    TEST_ADD(KGaussUtilUnitTest::testComputeGaussFunction_ColVector)
    TEST_ADD(KGaussUtilUnitTest::testComputeGaussFunction_RowVector)
    TEST_ADD(KGaussUtilUnitTest::testComputeGaussFunction_Matrix)
    TEST_ADD(KGaussUtilUnitTest::testComputeGaussWienerFunction_ColVector)
    TEST_ADD(KGaussUtilUnitTest::testComputeGaussWienerFunction_RowVector)
    TEST_ADD(KGaussUtilUnitTest::testComputeGaussWienerFunction_Matrix)
}

// ---------------------------------------------------------------------------------------------------- //

KGaussUtilUnitTest::~KGaussUtilUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KGaussUtilUnitTest::testComputeGaussFunction_ColVector()
{
    try
    {
#ifdef KLAB_64BITS_PLATFORM
        klab::DoubleReal precision = 1e-12;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        arma::Col<klab::DoubleReal> x;

        klab::ComputeGaussFunction(32, 4.0, 16, x);
        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.00033546262790251185, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.00088382630693504996, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x[16], 1.0, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.00088382630693504996, precision)) 

        klab::ComputeGaussFunction(32, -10.0, 3, x);
        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.95599748183309996, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.98019867330675525, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.99501247919268232, precision))
        TEST_ASSERT(klab::Equals(x[3], 1.0, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.99501247919268232, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.98019867330675525, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.95599748183309996, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.92311634638663576, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.835270211411272, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.78270453824186814, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.72614903707369094, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.66697681085847438, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.5460744266397094, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.48675225595997168, precision))
        TEST_ASSERT(klab::Equals(x[16], 0.42955735821073915, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.37531109885139957, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.27803730045319414, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.23574607655586352, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.19789869908361465, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.1644744565771549, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.11025052530448522, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.088921617459386343, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.071005353739636984, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.056134762834133725, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.034047454734599344, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.026121409853918233, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.019841094744370288, precision))

        klab::ComputeGaussFunction(32, 8.0, -5, x);
        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.82257756239866464, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.68194075119034814, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.53109599103534522, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.38855812751236413, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.26705183522634335, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.17242162389375282, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.10457900128900145, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.059587318761986086, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[16], 0.031894793362157101, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.016037709275350549, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.0075756774442599355, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.0033616864879322562, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.0014013594188853921, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.00088382630693504996, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.00054878023343204877, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.00033546262790251185, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.00020188496560091579, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.00011961288358102437, precision))
        TEST_ASSERT(klab::Equals(x[30], 6.9769577195997096e-005, precision))
        TEST_ASSERT(klab::Equals(x[31], 4.0065297392951069e-005, precision))        


        // Limit cases.
        try                                 {klab::ComputeGaussFunction(32, 0.0, 16, x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        klab::ComputeGaussFunction(0, 1.0, 0, x);
        TEST_ASSERT(x.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussUtilUnitTest::testComputeGaussFunction_RowVector()
{
    try
    {
#ifdef KLAB_64BITS_PLATFORM
        klab::DoubleReal precision = 1e-12;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        arma::Row<klab::DoubleReal> x;

        klab::ComputeGaussFunction(32, 4.0, 16, x);
        TEST_ASSERT(x.n_cols == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.00033546262790251185, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.00088382630693504996, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x[16], 1.0, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.00088382630693504996, precision)) 

        klab::ComputeGaussFunction(32, -10.0, 3, x);
        TEST_ASSERT(x.n_cols == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.95599748183309996, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.98019867330675525, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.99501247919268232, precision))
        TEST_ASSERT(klab::Equals(x[3], 1.0, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.99501247919268232, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.98019867330675525, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.95599748183309996, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.92311634638663576, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.835270211411272, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.78270453824186814, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.72614903707369094, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.66697681085847438, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.5460744266397094, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.48675225595997168, precision))
        TEST_ASSERT(klab::Equals(x[16], 0.42955735821073915, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.37531109885139957, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.27803730045319414, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.23574607655586352, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.19789869908361465, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.1644744565771549, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.11025052530448522, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.088921617459386343, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.071005353739636984, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.056134762834133725, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.034047454734599344, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.026121409853918233, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.019841094744370288, precision))

        klab::ComputeGaussFunction(32, 8.0, -5, x);
        TEST_ASSERT(x.n_cols == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.82257756239866464, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.68194075119034814, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.53109599103534522, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.38855812751236413, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.32465246735834974, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.26705183522634335, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.21626516682988728, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.17242162389375282, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.1353352832366127, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.10457900128900145, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.079559508718227687, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.059587318761986086, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.04393693362340742, precision))
        TEST_ASSERT(klab::Equals(x[16], 0.031894793362157101, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.022794180883612347, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.016037709275350549, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.011108996538242306, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.0075756774442599355, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.0050860692310127006, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.0033616864879322562, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.0021874911181828851, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.0014013594188853921, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.00088382630693504996, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.00054878023343204877, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.00033546262790251185, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.00020188496560091579, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.00011961288358102437, precision))
        TEST_ASSERT(klab::Equals(x[30], 6.9769577195997096e-005, precision))
        TEST_ASSERT(klab::Equals(x[31], 4.0065297392951069e-005, precision))  


        // Limit cases.
        try                                 {klab::ComputeGaussFunction(32, 0.0, 16, x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        klab::ComputeGaussFunction(0, 1.0, 0, x);
        TEST_ASSERT(x.n_cols == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussUtilUnitTest::testComputeGaussFunction_Matrix()
{
    try
    {
#ifdef KLAB_64BITS_PLATFORM
        klab::DoubleReal precision = 1e-12;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        arma::Mat<klab::DoubleReal> x;

        klab::ComputeGaussFunction(8, 8, 4.0, 4, 4, x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        TEST_ASSERT(klab::Equals(x(0, 0), 0.36787944117144233, precision))
        TEST_ASSERT(klab::Equals(x(0, 1), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x(0, 2), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(x(0, 3), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(x(0, 4), 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x(0, 5), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(x(0, 6), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(x(0, 7), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x(1, 0), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x(1, 1), 0.56978282473092301, precision))
        TEST_ASSERT(klab::Equals(x(1, 2), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(1, 3), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(1, 4), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x(1, 5), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(1, 6), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(1, 7), 0.56978282473092301, precision))
        TEST_ASSERT(klab::Equals(x(2, 0), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(x(2, 1), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(2, 2), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(x(2, 3), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(2, 4), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(2, 5), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(2, 6), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(x(2, 7), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(3, 0), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(x(3, 1), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(3, 2), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(3, 3), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(x(3, 4), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x(3, 5), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(x(3, 6), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(3, 7), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(4, 0), 0.60653065971263342, precision))
        TEST_ASSERT(klab::Equals(x(4, 1), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x(4, 2), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(4, 3), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x(4, 4), 1.0, precision))
        TEST_ASSERT(klab::Equals(x(4, 5), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x(4, 6), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(4, 7), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x(5, 0), 0.5878696731223465, precision))
        TEST_ASSERT(klab::Equals(x(5, 1), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(5, 2), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(5, 3), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(x(5, 4), 0.96923323447634413, precision))
        TEST_ASSERT(klab::Equals(x(5, 5), 0.93941306281347581, precision))
        TEST_ASSERT(klab::Equals(x(5, 6), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(5, 7), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(6, 0), 0.53526142851899028, precision))
        TEST_ASSERT(klab::Equals(x(6, 1), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(6, 2), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(x(6, 3), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(6, 4), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(6, 5), 0.85534532730742252, precision))
        TEST_ASSERT(klab::Equals(x(6, 6), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(x(6, 7), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(7, 0), 0.45783336177161427, precision))
        TEST_ASSERT(klab::Equals(x(7, 1), 0.56978282473092301, precision))
        TEST_ASSERT(klab::Equals(x(7, 2), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(7, 3), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(7, 4), 0.75483960198900735, precision))
        TEST_ASSERT(klab::Equals(x(7, 5), 0.73161562894664178, precision))
        TEST_ASSERT(klab::Equals(x(7, 6), 0.66614361070348782, precision))
        TEST_ASSERT(klab::Equals(x(7, 7), 0.56978282473092301, precision))

        klab::ComputeGaussFunction(8, 8, -10.0, 1, 6, x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        TEST_ASSERT(klab::Equals(x(0, 0), 0.83110428385212565, precision))
        TEST_ASSERT(klab::Equals(x(0, 1), 0.8780954309205613, precision))
        TEST_ASSERT(klab::Equals(x(0, 2), 0.91851228440145738, precision))
        TEST_ASSERT(klab::Equals(x(0, 3), 0.95122942450071402, precision))
        TEST_ASSERT(klab::Equals(x(0, 4), 0.97530991202833262, precision))
        TEST_ASSERT(klab::Equals(x(0, 5), 0.99004983374916811, precision))
        TEST_ASSERT(klab::Equals(x(0, 6), 0.99501247919268232, precision))
        TEST_ASSERT(klab::Equals(x(0, 7), 0.99004983374916811, precision))
        TEST_ASSERT(klab::Equals(x(1, 0), 0.835270211411272, precision))
        TEST_ASSERT(klab::Equals(x(1, 1), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(1, 2), 0.92311634638663576, precision))
        TEST_ASSERT(klab::Equals(x(1, 3), 0.95599748183309996, precision))
        TEST_ASSERT(klab::Equals(x(1, 4), 0.98019867330675525, precision))
        TEST_ASSERT(klab::Equals(x(1, 5), 0.99501247919268232, precision))
        TEST_ASSERT(klab::Equals(x(1, 6), 1.0, precision))
        TEST_ASSERT(klab::Equals(x(1, 7), 0.99501247919268232, precision))
        TEST_ASSERT(klab::Equals(x(2, 0), 0.83110428385212565, precision))
        TEST_ASSERT(klab::Equals(x(2, 1), 0.8780954309205613, precision))
        TEST_ASSERT(klab::Equals(x(2, 2), 0.91851228440145738, precision))
        TEST_ASSERT(klab::Equals(x(2, 3), 0.95122942450071402, precision))
        TEST_ASSERT(klab::Equals(x(2, 4), 0.97530991202833262, precision))
        TEST_ASSERT(klab::Equals(x(2, 5), 0.99004983374916811, precision))
        TEST_ASSERT(klab::Equals(x(2, 6), 0.99501247919268232, precision))
        TEST_ASSERT(klab::Equals(x(2, 7), 0.99004983374916811, precision))
        TEST_ASSERT(klab::Equals(x(3, 0), 0.81873075307798182, precision))
        TEST_ASSERT(klab::Equals(x(3, 1), 0.8650222931107413, precision))
        TEST_ASSERT(klab::Equals(x(3, 2), 0.90483741803595952, precision))
        TEST_ASSERT(klab::Equals(x(3, 3), 0.93706746337740343, precision))
        TEST_ASSERT(klab::Equals(x(3, 4), 0.96078943915232318, precision))
        TEST_ASSERT(klab::Equals(x(3, 5), 0.97530991202833262, precision))
        TEST_ASSERT(klab::Equals(x(3, 6), 0.98019867330675525, precision))
        TEST_ASSERT(klab::Equals(x(3, 7), 0.97530991202833262, precision))
        TEST_ASSERT(klab::Equals(x(4, 0), 0.79851621875937706, precision))
        TEST_ASSERT(klab::Equals(x(4, 1), 0.8436648165963837, precision))
        TEST_ASSERT(klab::Equals(x(4, 2), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(4, 3), 0.91393118527122819, precision))
        TEST_ASSERT(klab::Equals(x(4, 4), 0.93706746337740343, precision))
        TEST_ASSERT(klab::Equals(x(4, 5), 0.95122942450071402, precision))
        TEST_ASSERT(klab::Equals(x(4, 6), 0.95599748183309996, precision))
        TEST_ASSERT(klab::Equals(x(4, 7), 0.95122942450071402, precision))
        TEST_ASSERT(klab::Equals(x(5, 0), 0.77105158580356625, precision))
        TEST_ASSERT(klab::Equals(x(5, 1), 0.81464731641141452, precision))
        TEST_ASSERT(klab::Equals(x(5, 2), 0.85214378896621135, precision))
        TEST_ASSERT(klab::Equals(x(5, 3), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(5, 4), 0.90483741803595952, precision))
        TEST_ASSERT(klab::Equals(x(5, 5), 0.91851228440145738, precision))
        TEST_ASSERT(klab::Equals(x(5, 6), 0.92311634638663576, precision))
        TEST_ASSERT(klab::Equals(x(5, 7), 0.91851228440145738, precision))
        TEST_ASSERT(klab::Equals(x(6, 0), 0.73712337439162778, precision))
        TEST_ASSERT(klab::Equals(x(6, 1), 0.77880078307140488, precision))
        TEST_ASSERT(klab::Equals(x(6, 2), 0.81464731641141452, precision))
        TEST_ASSERT(klab::Equals(x(6, 3), 0.8436648165963837, precision))
        TEST_ASSERT(klab::Equals(x(6, 4), 0.8650222931107413, precision))
        TEST_ASSERT(klab::Equals(x(6, 5), 0.8780954309205613, precision))
        TEST_ASSERT(klab::Equals(x(6, 6), 0.88249690258459546, precision))
        TEST_ASSERT(klab::Equals(x(6, 7), 0.8780954309205613, precision))
        TEST_ASSERT(klab::Equals(x(7, 0), 0.69767632607103103, precision))
        TEST_ASSERT(klab::Equals(x(7, 1), 0.73712337439162778, precision))
        TEST_ASSERT(klab::Equals(x(7, 2), 0.77105158580356625, precision))
        TEST_ASSERT(klab::Equals(x(7, 3), 0.79851621875937706, precision))
        TEST_ASSERT(klab::Equals(x(7, 4), 0.81873075307798182, precision))
        TEST_ASSERT(klab::Equals(x(7, 5), 0.83110428385212565, precision))
        TEST_ASSERT(klab::Equals(x(7, 6), 0.835270211411272, precision))
        TEST_ASSERT(klab::Equals(x(7, 7), 0.83110428385212565, precision))

        klab::ComputeGaussFunction(8, 8, 8.0, -3, 38, x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        TEST_ASSERT(klab::Equals(x(0, 0), 1.1751114156965632e-005, precision))
        TEST_ASSERT(klab::Equals(x(0, 1), 2.1112928077808185e-005, precision))
        TEST_ASSERT(klab::Equals(x(0, 2), 3.7344963557095373e-005, precision))
        TEST_ASSERT(klab::Equals(x(0, 3), 6.5032396795259353e-005, precision))
        TEST_ASSERT(klab::Equals(x(0, 4), 0.00011149146690418283, precision))
        TEST_ASSERT(klab::Equals(x(0, 5), 0.0001881774796065311, precision))
        TEST_ASSERT(klab::Equals(x(0, 6), 0.00031268555156140808, precision))
        TEST_ASSERT(klab::Equals(x(0, 7), 0.00051151942333965607, precision))
        TEST_ASSERT(klab::Equals(x(1, 0), 1.1125731269303538e-005, precision))
        TEST_ASSERT(klab::Equals(x(1, 1), 1.9989318541560501e-005, precision))
        TEST_ASSERT(klab::Equals(x(1, 2), 3.5357500850409981e-005, precision))
        TEST_ASSERT(klab::Equals(x(1, 3), 6.1571435770104257e-005, precision))
        TEST_ASSERT(klab::Equals(x(1, 4), 0.0001055579992694658, precision))
        TEST_ASSERT(klab::Equals(x(1, 5), 0.00017816285682120578, precision))
        TEST_ASSERT(klab::Equals(x(1, 6), 0.00029604473005685538, precision))
        TEST_ASSERT(klab::Equals(x(1, 7), 0.00048429685620343432, precision))
        TEST_ASSERT(klab::Equals(x(2, 0), 1.0370321845440158e-005, precision))
        TEST_ASSERT(klab::Equals(x(2, 1), 1.8632093633157059e-005, precision))
        TEST_ASSERT(klab::Equals(x(2, 2), 3.2956814666271259e-005, precision))
        TEST_ASSERT(klab::Equals(x(2, 3), 5.7390888739468748e-005, precision))
        TEST_ASSERT(klab::Equals(x(2, 4), 9.8390874207554272e-005, precision))
        TEST_ASSERT(klab::Equals(x(2, 5), 0.00016606604288893956, precision))
        TEST_ASSERT(klab::Equals(x(2, 6), 0.00027594403073589844, precision))
        TEST_ASSERT(klab::Equals(x(2, 7), 0.00045141430670910486, precision))
        TEST_ASSERT(klab::Equals(x(3, 0), 9.5163422540768606e-006, precision))
        TEST_ASSERT(klab::Equals(x(3, 1), 1.7097770210583397e-005, precision))
        TEST_ASSERT(klab::Equals(x(3, 2), 3.0242873137666396e-005, precision))
        TEST_ASSERT(klab::Equals(x(3, 3), 5.2664839881567772e-005, precision))
        TEST_ASSERT(klab::Equals(x(3, 4), 9.0288541435057894e-005, precision))
        TEST_ASSERT(klab::Equals(x(3, 5), 0.00015239076708175971, precision))
        TEST_ASSERT(klab::Equals(x(3, 6), 0.00025322047652811852, precision))
        TEST_ASSERT(klab::Equals(x(3, 7), 0.00041424105298328224, precision))
        TEST_ASSERT(klab::Equals(x(4, 0), 8.5972987747721966e-006, precision))
        TEST_ASSERT(klab::Equals(x(4, 1), 1.5446548154550848e-005, precision))
        TEST_ASSERT(klab::Equals(x(4, 2), 2.732215900081375e-005, precision))
        TEST_ASSERT(klab::Equals(x(4, 3), 4.7578717883271245e-005, precision))
        TEST_ASSERT(klab::Equals(x(4, 4), 8.1568899681287412e-005, precision))
        TEST_ASSERT(klab::Equals(x(4, 5), 0.0001376735850959261, precision))
        TEST_ASSERT(klab::Equals(x(4, 6), 0.00022876563646812717, precision))
        TEST_ASSERT(klab::Equals(x(4, 7), 0.00037423560462506594, precision))
        TEST_ASSERT(klab::Equals(x(5, 0), 7.6465958201017975e-006, precision))
        TEST_ASSERT(klab::Equals(x(5, 1), 1.3738444323952124e-005, precision))
        TEST_ASSERT(klab::Equals(x(5, 2), 2.4300831259329465e-005, precision))
        TEST_ASSERT(klab::Equals(x(5, 3), 4.2317387684559621e-005, precision))
        TEST_ASSERT(klab::Equals(x(5, 4), 7.2548881188529125e-005, precision))
        TEST_ASSERT(klab::Equals(x(5, 5), 0.00012244942137198576, precision))
        TEST_ASSERT(klab::Equals(x(5, 6), 0.00020346836901064417, precision))
        TEST_ASSERT(klab::Equals(x(5, 7), 0.00033285203702079357, precision))
        TEST_ASSERT(klab::Equals(x(6, 0), 6.6955830180914168e-006, precision))
        TEST_ASSERT(klab::Equals(x(6, 1), 1.2029783798514364e-005, precision))
        TEST_ASSERT(klab::Equals(x(6, 2), 2.1278518825035179e-005, precision))
        TEST_ASSERT(klab::Equals(x(6, 3), 3.7054342745025098e-005, precision))
        TEST_ASSERT(klab::Equals(x(6, 4), 6.3525922946059503e-005, precision))
        TEST_ASSERT(klab::Equals(x(6, 5), 0.00010722029588095494, precision))
        TEST_ASSERT(klab::Equals(x(6, 6), 0.00017816285682120578, precision))
        TEST_ASSERT(klab::Equals(x(6, 7), 0.00029145498193520206, precision))
        TEST_ASSERT(klab::Equals(x(7, 0), 5.7719533454164476e-006, precision))
        TEST_ASSERT(klab::Equals(x(7, 1), 1.0370321845440158e-005, precision))
        TEST_ASSERT(klab::Equals(x(7, 2), 1.8343229795794281e-005, precision))
        TEST_ASSERT(klab::Equals(x(7, 3), 3.1942840077027507e-005, precision))
        TEST_ASSERT(klab::Equals(x(7, 4), 5.476276860109711e-005, precision))
        TEST_ASSERT(klab::Equals(x(7, 5), 9.242967249221398e-005, precision))
        TEST_ASSERT(klab::Equals(x(7, 6), 0.00015358598268134713, precision))
        TEST_ASSERT(klab::Equals(x(7, 7), 0.00025124989914600612, precision))


        // Limit cases.
        try                                 {klab::ComputeGaussFunction(8, 8, 0.0, 4, 4, x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        klab::ComputeGaussFunction(0, 8, 1.0, 0, 0, x);
        TEST_ASSERT(x.n_rows==0 && x.n_cols==8)

        klab::ComputeGaussFunction(8, 0, 1.0, 0, 0, x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==0)

        klab::ComputeGaussFunction(0, 0, 1.0, 0, 0, x);
        TEST_ASSERT(x.n_rows==0 && x.n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussUtilUnitTest::testComputeGaussWienerFunction_ColVector()
{
    try
    {
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        klab::DoubleReal precision = 1e-12;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        arma::Col<klab::DoubleReal> x;

        klab::ComputeGaussWienerFunction(32, 4.0, 16, 0.4, x);
        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.00083865633381043688, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.0022095614523461545, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.0054686623749786072, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.012714350837277439, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.027763925494091006, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.056911527736694015, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.19580037023510777, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.48406308739795989, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x[16], 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.48406308739795989, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.19580037023510777, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.056911527736694015, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.027763925494091006, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.012714350837277439, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.0054686623749786072, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.0022095614523461545, precision))        

        klab::ComputeGaussWienerFunction(32, -10.0, 3, 0.4, x);
        TEST_ASSERT(x.n_rows == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.72758565482693682, precision))   
        TEST_ASSERT(klab::Equals(x[1], 0.7203161966904672, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.71581065299579061, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.71581065299579061, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.7203161966904672, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.72758565482693682, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.73722870689537545, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.76094399739948604, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.77294502961506328, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.78308526873069784, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.78945427347375596, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.78212053058357112, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.76421893900042781, precision))
        TEST_ASSERT(klab::Equals(x[16], 0.73488966677508494, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.693917454797635, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.58251527146988991, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.51746792310446765, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.45062606760742135, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.38513931688633724, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.26749761036905806, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.21799480194362916, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.17530378520504197, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.1392400050977568, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.08487266964968565, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.065192318265853047, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.04955396720410099, precision))            


        // Limit cases.
        try                                 {klab::ComputeGaussWienerFunction(32, 0.0, 16, 0.4, x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        klab::ComputeGaussWienerFunction(0, 1.0, 0, 0.4, x);
        TEST_ASSERT(x.n_rows == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussUtilUnitTest::testComputeGaussWienerFunction_RowVector()
{
    try
    {
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        klab::DoubleReal precision = 1e-12;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        arma::Row<klab::DoubleReal> x;

        klab::ComputeGaussWienerFunction(32, 4.0, 16, 0.4, x);
        TEST_ASSERT(x.n_cols == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.00083865633381043688, precision))
        TEST_ASSERT(klab::Equals(x[1], 0.0022095614523461545, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.0054686623749786072, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.012714350837277439, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.027763925494091006, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.056911527736694015, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.19580037023510777, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.48406308739795989, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x[16], 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.48406308739795989, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.19580037023510777, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.056911527736694015, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.027763925494091006, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.012714350837277439, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.0054686623749786072, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.0022095614523461545, precision))        

        klab::ComputeGaussWienerFunction(32, -10.0, 3, 0.4, x);
        TEST_ASSERT(x.n_cols == 32)
        TEST_ASSERT(klab::Equals(x[0], 0.72758565482693682, precision))   
        TEST_ASSERT(klab::Equals(x[1], 0.7203161966904672, precision))
        TEST_ASSERT(klab::Equals(x[2], 0.71581065299579061, precision))
        TEST_ASSERT(klab::Equals(x[3], 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(x[4], 0.71581065299579061, precision))
        TEST_ASSERT(klab::Equals(x[5], 0.7203161966904672, precision))
        TEST_ASSERT(klab::Equals(x[6], 0.72758565482693682, precision))
        TEST_ASSERT(klab::Equals(x[7], 0.73722870689537545, precision))
        TEST_ASSERT(klab::Equals(x[8], 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x[9], 0.76094399739948604, precision))
        TEST_ASSERT(klab::Equals(x[10], 0.77294502961506328, precision))
        TEST_ASSERT(klab::Equals(x[11], 0.78308526873069784, precision))
        TEST_ASSERT(klab::Equals(x[12], 0.78945427347375596, precision))
        TEST_ASSERT(klab::Equals(x[13], 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x[14], 0.78212053058357112, precision))
        TEST_ASSERT(klab::Equals(x[15], 0.76421893900042781, precision))
        TEST_ASSERT(klab::Equals(x[16], 0.73488966677508494, precision))
        TEST_ASSERT(klab::Equals(x[17], 0.693917454797635, precision))
        TEST_ASSERT(klab::Equals(x[18], 0.64236835274093307, precision))
        TEST_ASSERT(klab::Equals(x[19], 0.58251527146988991, precision))
        TEST_ASSERT(klab::Equals(x[20], 0.51746792310446765, precision))
        TEST_ASSERT(klab::Equals(x[21], 0.45062606760742135, precision))
        TEST_ASSERT(klab::Equals(x[22], 0.38513931688633724, precision))
        TEST_ASSERT(klab::Equals(x[23], 0.32352432148158317, precision))
        TEST_ASSERT(klab::Equals(x[24], 0.26749761036905806, precision))
        TEST_ASSERT(klab::Equals(x[25], 0.21799480194362916, precision))
        TEST_ASSERT(klab::Equals(x[26], 0.17530378520504197, precision))
        TEST_ASSERT(klab::Equals(x[27], 0.1392400050977568, precision))
        TEST_ASSERT(klab::Equals(x[28], 0.10931476620210449, precision))
        TEST_ASSERT(klab::Equals(x[29], 0.08487266964968565, precision))
        TEST_ASSERT(klab::Equals(x[30], 0.065192318265853047, precision))
        TEST_ASSERT(klab::Equals(x[31], 0.04955396720410099, precision))            


        // Limit cases.
        try                                 {klab::ComputeGaussWienerFunction(32, 0.0, 16, 0.4, x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        klab::ComputeGaussWienerFunction(0, 1.0, 0, 0.4, x);
        TEST_ASSERT(x.n_cols == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KGaussUtilUnitTest::testComputeGaussWienerFunction_Matrix()
{
    try
    {
#if defined(KLAB_64BITS_PLATFORM) || (defined(KLAB_32BITS_PLATFORM) && defined(KLAB_UNIX_SYSTEM))
        klab::DoubleReal precision = 1e-12;
#else
        klab::DoubleReal precision = 1e-16;
#endif

        arma::Mat<klab::DoubleReal> x;

        klab::ComputeGaussWienerFunction(8, 8, 4.0, 4, 4, 0.4, x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        TEST_ASSERT(klab::Equals(x(0, 0), 0.6871944605393091, precision))
        TEST_ASSERT(klab::Equals(x(0, 1), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x(0, 2), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(x(0, 3), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(x(0, 4), 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x(0, 5), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(x(0, 6), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(x(0, 7), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x(1, 0), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x(1, 1), 0.7862842540342283, precision))
        TEST_ASSERT(klab::Equals(x(1, 2), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(1, 3), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(1, 4), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x(1, 5), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(1, 6), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(1, 7), 0.7862842540342283, precision))
        TEST_ASSERT(klab::Equals(x(2, 0), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(x(2, 1), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(2, 2), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(x(2, 3), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(2, 4), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(2, 5), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(2, 6), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(x(2, 7), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(3, 0), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(x(3, 1), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(3, 2), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(3, 3), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(x(3, 4), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x(3, 5), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(x(3, 6), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(3, 7), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(4, 0), 0.7898774562675327, precision))
        TEST_ASSERT(klab::Equals(x(4, 1), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x(4, 2), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(4, 3), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x(4, 4), 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(x(4, 5), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x(4, 6), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(4, 7), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x(5, 0), 0.78846159383079939, precision))
        TEST_ASSERT(klab::Equals(x(5, 1), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(5, 2), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(5, 3), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(x(5, 4), 0.7236253411180279, precision))
        TEST_ASSERT(klab::Equals(x(5, 5), 0.73248758801700931, precision))
        TEST_ASSERT(klab::Equals(x(5, 6), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(5, 7), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(6, 0), 0.77969073335987005, precision))
        TEST_ASSERT(klab::Equals(x(6, 1), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(6, 2), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(x(6, 3), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(6, 4), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(6, 5), 0.75586206608300022, precision))
        TEST_ASSERT(klab::Equals(x(6, 6), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(x(6, 7), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(7, 0), 0.75102495035601424, precision))
        TEST_ASSERT(klab::Equals(x(7, 1), 0.7862842540342283, precision))
        TEST_ASSERT(klab::Equals(x(7, 2), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(7, 3), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(7, 4), 0.77835942516144885, precision))
        TEST_ASSERT(klab::Equals(x(7, 5), 0.78225788708636612, precision))
        TEST_ASSERT(klab::Equals(x(7, 6), 0.78950605559794285, precision))
        TEST_ASSERT(klab::Equals(x(7, 7), 0.7862842540342283, precision))

        klab::ComputeGaussWienerFunction(8, 8, -10.0, 1, 6, 0.4, x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==8)
        TEST_ASSERT(klab::Equals(x(0, 0), 0.76196765839989833, precision))
        TEST_ASSERT(klab::Equals(x(0, 1), 0.74983497018025824, precision))
        TEST_ASSERT(klab::Equals(x(0, 2), 0.73855292209295442, precision))
        TEST_ASSERT(klab::Equals(x(0, 3), 0.7290022583292437, precision))
        TEST_ASSERT(klab::Equals(x(0, 4), 0.72179445943364839, precision))
        TEST_ASSERT(klab::Equals(x(0, 5), 0.71732414535448918, precision))
        TEST_ASSERT(klab::Equals(x(0, 6), 0.71581065299579061, precision))
        TEST_ASSERT(klab::Equals(x(0, 7), 0.71732414535448918, precision))
        TEST_ASSERT(klab::Equals(x(1, 0), 0.76094399739948604, precision))
        TEST_ASSERT(klab::Equals(x(1, 1), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(1, 2), 0.73722870689537545, precision))
        TEST_ASSERT(klab::Equals(x(1, 3), 0.72758565482693682, precision))
        TEST_ASSERT(klab::Equals(x(1, 4), 0.7203161966904672, precision))
        TEST_ASSERT(klab::Equals(x(1, 5), 0.71581065299579061, precision))
        TEST_ASSERT(klab::Equals(x(1, 6), 0.7142857142857143, precision))
        TEST_ASSERT(klab::Equals(x(1, 7), 0.71581065299579061, precision))
        TEST_ASSERT(klab::Equals(x(2, 0), 0.76196765839989833, precision))
        TEST_ASSERT(klab::Equals(x(2, 1), 0.74983497018025824, precision))
        TEST_ASSERT(klab::Equals(x(2, 2), 0.73855292209295442, precision))
        TEST_ASSERT(klab::Equals(x(2, 3), 0.7290022583292437, precision))
        TEST_ASSERT(klab::Equals(x(2, 4), 0.72179445943364839, precision))
        TEST_ASSERT(klab::Equals(x(2, 5), 0.71732414535448918, precision))
        TEST_ASSERT(klab::Equals(x(2, 6), 0.71581065299579061, precision))
        TEST_ASSERT(klab::Equals(x(2, 7), 0.71732414535448918, precision))
        TEST_ASSERT(klab::Equals(x(3, 0), 0.76494012805840683, precision))
        TEST_ASSERT(klab::Equals(x(3, 1), 0.75333078357165206, precision))
        TEST_ASSERT(klab::Equals(x(3, 2), 0.74244242688611517, precision))
        TEST_ASSERT(klab::Equals(x(3, 3), 0.73317487936129377, precision))
        TEST_ASSERT(klab::Equals(x(3, 4), 0.72615642741939579, precision))
        TEST_ASSERT(klab::Equals(x(3, 5), 0.72179445943364839, precision))
        TEST_ASSERT(klab::Equals(x(3, 6), 0.7203161966904672, precision))
        TEST_ASSERT(klab::Equals(x(3, 7), 0.72179445943364839, precision))
        TEST_ASSERT(klab::Equals(x(4, 0), 0.7695591310927008, precision))
        TEST_ASSERT(klab::Equals(x(4, 1), 0.75884811756800841, precision))
        TEST_ASSERT(klab::Equals(x(4, 2), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(4, 3), 0.73986337307290828, precision))
        TEST_ASSERT(klab::Equals(x(4, 4), 0.73317487936129377, precision))
        TEST_ASSERT(klab::Equals(x(4, 5), 0.7290022583292437, precision))
        TEST_ASSERT(klab::Equals(x(4, 6), 0.72758565482693682, precision))
        TEST_ASSERT(klab::Equals(x(4, 7), 0.7290022583292437, precision))
        TEST_ASSERT(klab::Equals(x(5, 0), 0.7752998038876866, precision))
        TEST_ASSERT(klab::Equals(x(5, 1), 0.76589773405967609, precision))
        TEST_ASSERT(klab::Equals(x(5, 2), 0.75668828983818615, precision))
        TEST_ASSERT(klab::Equals(x(5, 3), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(5, 4), 0.74244242688611517, precision))
        TEST_ASSERT(klab::Equals(x(5, 5), 0.73855292209295442, precision))
        TEST_ASSERT(klab::Equals(x(5, 6), 0.73722870689537545, precision))
        TEST_ASSERT(klab::Equals(x(5, 7), 0.73855292209295442, precision))
        TEST_ASSERT(klab::Equals(x(6, 0), 0.7813883450542668, precision))
        TEST_ASSERT(klab::Equals(x(6, 1), 0.77374770013836836, precision))
        TEST_ASSERT(klab::Equals(x(6, 2), 0.76589773405967609, precision))
        TEST_ASSERT(klab::Equals(x(6, 3), 0.75884811756800841, precision))
        TEST_ASSERT(klab::Equals(x(6, 4), 0.75333078357165206, precision))
        TEST_ASSERT(klab::Equals(x(6, 5), 0.74983497018025824, precision))
        TEST_ASSERT(klab::Equals(x(6, 6), 0.74863956256053732, precision))
        TEST_ASSERT(klab::Equals(x(6, 7), 0.74983497018025824, precision))
        TEST_ASSERT(klab::Equals(x(7, 0), 0.78677705230729567, precision))
        TEST_ASSERT(klab::Equals(x(7, 1), 0.7813883450542668, precision))
        TEST_ASSERT(klab::Equals(x(7, 2), 0.7752998038876866, precision))
        TEST_ASSERT(klab::Equals(x(7, 3), 0.7695591310927008, precision))
        TEST_ASSERT(klab::Equals(x(7, 4), 0.76494012805840683, precision))
        TEST_ASSERT(klab::Equals(x(7, 5), 0.76196765839989833, precision))
        TEST_ASSERT(klab::Equals(x(7, 6), 0.76094399739948604, precision))
        TEST_ASSERT(klab::Equals(x(7, 7), 0.76196765839989833, precision))


        // Limit cases.
        try                                 {klab::ComputeGaussWienerFunction(8, 8, 0.0, 4, 4, 0.4, x); TEST_ASSERT(false)}
        catch(KZeroVarianceGaussException&) {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        klab::ComputeGaussWienerFunction(0, 8, 1.0, 0, 0, 0.4, x);
        TEST_ASSERT(x.n_rows==0 && x.n_cols==8)

        klab::ComputeGaussWienerFunction(8, 0, 1.0, 0, 0, 0.4, x);
        TEST_ASSERT(x.n_rows==8 && x.n_cols==0)

        klab::ComputeGaussWienerFunction(0, 0, 1.0, 0, 0, 0.4, x);
        TEST_ASSERT(x.n_rows==0 && x.n_cols==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
