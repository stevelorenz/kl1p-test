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

#ifndef KL1P_RESIZINGDOPERATORUNITTEST_H
#define KL1P_RESIZINGDOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KResizingOperatorUnitTest : public Test::Suite
{
public:
    
    KResizingOperatorUnitTest();
    virtual ~KResizingOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testMNOpConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testOp();
    void    testApply();
    void    testApply_02();
    void    testApply_03();
    void    testApply_04();
    void    testApplyAdjoint();
    void    testApplyAdjoint_02();
    void    testApplyAdjoint_03();
    void    testApplyAdjoint_04();
    void    testColumn();
    void    testColumn_02();
    void    testColumn_03();
    void    testColumn_04();
    void    testColumnAdjoint();
    void    testColumnAdjoint_02();
    void    testColumnAdjoint_03();
    void    testColumnAdjoint_04();


private:

    KResizingOperatorUnitTest(const KResizingOperatorUnitTest& test);
    KResizingOperatorUnitTest&   operator=(const KResizingOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
