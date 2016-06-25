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

#ifndef KL1P_SUBSYSTEMOPERATORUNITTEST_H
#define KL1P_SUBSYSTEMOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KSubSystemOperatorUnitTest : public Test::Suite
{
public:
    
    KSubSystemOperatorUnitTest();
    virtual ~KSubSystemOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testOpConstructor(); 
    void    testOpIndexesConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testOp();
    void    testIndexes();
    void    testApply();
    void    testApplyAdjoint();
    void    testColumn();
    void    testColumnAdjoint();


private:

    KSubSystemOperatorUnitTest(const KSubSystemOperatorUnitTest& test);
    KSubSystemOperatorUnitTest&     operator=(const KSubSystemOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
