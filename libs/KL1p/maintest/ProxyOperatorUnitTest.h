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

#ifndef KL1P_PROXYOPERATORUNITTEST_H
#define KL1P_PROXYOPERATORUNITTEST_H

#include <cpptest.h>
#include "../include/ProxyOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KProxyOperatorUnitTest : public Test::Suite
{
public:
    
    KProxyOperatorUnitTest();
    virtual ~KProxyOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testOpConstructor(); 
    void    testNOpConstructor(); 
    void    testMNOpConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testOp();
    void    testIsZero();


private:

    KProxyOperatorUnitTest(const KProxyOperatorUnitTest& test);
    KProxyOperatorUnitTest& operator=(const KProxyOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOp=TOperator<T, T> >
class TTestProxyOperator : public TProxyOperator<T, T, TOp>
{
public:

    TTestProxyOperator(klab::TSmartPointer<TOp> op) : TProxyOperator<T, T, TOp>(op) {};
    TTestProxyOperator(klab::UInt32 n, klab::TSmartPointer<TOp> op) : TProxyOperator<T, T, TOp>(n, op) {};
    TTestProxyOperator(klab::UInt32 m, klab::UInt32 n, klab::TSmartPointer<TOp> op) : TProxyOperator<T, T, TOp>(m, n, op) {};
    TTestProxyOperator(const TTestProxyOperator<T, TOp>& op) : TProxyOperator<T, T, TOp>(op) {};
    virtual ~TTestProxyOperator() {};

    virtual void        apply(const arma::Col<T>& in, arma::Col<T>& out) {out = in;};
    virtual void        applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) {out = in;};
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
