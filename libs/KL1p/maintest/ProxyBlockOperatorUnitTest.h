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

#ifndef KL1P_PROXYBLOCKOPERATORUNITTEST_H
#define KL1P_PROXYBLOCKOPERATORUNITTEST_H

#include <cpptest.h>
#include "../include/ProxyBlockOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KProxyBlockOperatorUnitTest : public Test::Suite
{
public:
    
    KProxyBlockOperatorUnitTest();
    virtual ~KProxyBlockOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testOpConstructor(); 
    void    testNOpConstructor(); 
    void    testMNOpConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testOp();
    void    testIsZero();
    void    testCountBlockRows();
    void    testCountBlockColumns();
    void    testBlock();
    void    testIsZeroBlock();
    void    testInBlock();
    void    testApplyBlockVariance();
    void    testApplyBlockVarianceAdjoint();


private:

    KProxyBlockOperatorUnitTest(const KProxyBlockOperatorUnitTest& test);
    KProxyBlockOperatorUnitTest&    operator=(const KProxyBlockOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOp=TOperator<T, T>, class TBlockOp=TBlockOperator<T, T, TOp>, class TBlock=TOp>
class TTestProxyBlockOperator : public TProxyBlockOperator<T, T, TOp, TBlockOp, TBlock>
{
public:

    TTestProxyBlockOperator(klab::TSmartPointer<TBlockOp> op) : TProxyBlockOperator<T, T, TOp, TBlockOp, TBlock>(op) {};
    TTestProxyBlockOperator(klab::UInt32 n, klab::TSmartPointer<TBlockOp> op) : TProxyBlockOperator<T, T, TOp, TBlockOp, TBlock>(n, op) {};
    TTestProxyBlockOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TBlockOp> op) : TProxyBlockOperator<T, T, TOp, TBlockOp, TBlock>(m, n, op) {};
    TTestProxyBlockOperator(const TTestProxyBlockOperator<T, TOp, TBlockOp, TBlock>& op) : TProxyBlockOperator<T, T, TOp, TBlockOp, TBlock>(op) {};
    virtual ~TTestProxyBlockOperator() {};

    virtual klab::TSmartPointer<TBlock> block(klab::UInt32 i, klab::UInt32 j) const {return this->_op->block(i, j);};
    virtual klab::TSmartPointer<TBlock> inBlock(klab::UInt32 i, klab::UInt32 j) const {return this->_op->inBlock(i, j);};
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
