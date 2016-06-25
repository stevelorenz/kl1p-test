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

#ifndef KL1P_OPERATORUNITTEST_H
#define KL1P_OPERATORUNITTEST_H

#include <cpptest.h>
#include "../include/Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KOperatorUnitTest : public Test::Suite
{
public:
    
    KOperatorUnitTest();
    virtual ~KOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testNConstructor();
    void    testMNConstructor();
    void    testCopyConstructor();

    // Methods tests.
    void    testCountRows();
    void    testCountColumns();
    void    testM();
    void    testN();
    void    testIsZero();
    void    testSum();
    void    testNormFrobenius();
    void    testSquaredNormFrobenius();
    void    testMean();
    void    testVariance();
    void    testStandardDeviation();
    void    testApply();
    void    testApplyAdjoint();
    void    testColumn();
    void    testColumnAdjoint();
    void    testToMatrix();
    void    testToMatrixAdjoint();


private:

    KOperatorUnitTest(const KOperatorUnitTest& test);
    KOperatorUnitTest&      operator=(const KOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TTestOperator : public TOperator<T>
{
public:

    TTestOperator() : TOperator<T>() {};
    TTestOperator(klab::UInt32 n) : TOperator<T>(n) {};
    TTestOperator(klab::UInt32 m, klab::UInt32 n) : TOperator<T>(m, n) {};
    TTestOperator(const TTestOperator<T>& op) : TOperator<T>(op) {};
    virtual ~TTestOperator() {};

    virtual void        apply(const arma::Col<T>& in, arma::Col<T>& out) {out = in;};
    virtual void        applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) {out = in;};
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
