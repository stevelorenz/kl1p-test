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

#ifndef KL1P_ROWJOINTOPERATORUNITTEST_H
#define KL1P_ROWJOINTOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KRowJointOperatorUnitTest : public Test::Suite
{
public:
    
    KRowJointOperatorUnitTest();
    virtual ~KRowJointOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testOpConstructor(); 
    void    testOp1Op2Constructor(); 
    void    testOp1Op2Op3Constructor(); 
    void    testOperatorArrayConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
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

    KRowJointOperatorUnitTest(const KRowJointOperatorUnitTest& test);
    KRowJointOperatorUnitTest&  operator=(const KRowJointOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
