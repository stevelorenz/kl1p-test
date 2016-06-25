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

#ifndef KL1P_COMPLEXPROXYBLOCKOPERATORUNITTEST_H
#define KL1P_COMPLEXPROXYBLOCKOPERATORUNITTEST_H

#include <cpptest.h>
#include "../include/Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KComplexProxyBlockOperatorUnitTest : public Test::Suite
{
public:
    
    KComplexProxyBlockOperatorUnitTest();
    virtual ~KComplexProxyBlockOperatorUnitTest();


public:

    static void     GenerateTestOperators_01(std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > >& operators, klab::UInt32& m, klab::UInt32& n, klab::UInt32& blockRows, klab::UInt32& blockCols);
    static void     GenerateTestOperators_02(std::vector<klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > >& operators, klab::UInt32& m, klab::UInt32& n, klab::UInt32& blockRows, klab::UInt32& blockCols);
    
    
protected:

    // Constructor/Affectation tests.
    void    testOpConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testOp();
    void    testIsZero();
    void    testSum();
    void    testNormFrobenius();
    void    testSquaredNormFrobenius();
    void    testMean();
    void    testVariance();
    void    testCountBlockRows();
    void    testCountBlockColumns();
    void    testBlock();
    void    testIsZeroBlock();
    void    testInBlock();
    void    testApply();
    void    testApplyAdjoint();
    void    testColumn();
    void    testColumnAdjoint();
    void    testApplyBlockVariance();
    void    testApplyBlockVarianceAdjoint();


private:

    KComplexProxyBlockOperatorUnitTest(const KComplexProxyBlockOperatorUnitTest& test);
    KComplexProxyBlockOperatorUnitTest& operator=(const KComplexProxyBlockOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
