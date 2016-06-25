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

#ifndef KL1P_MATRIXOPERATORUNITTEST_H
#define KL1P_MATRIXOPERATORUNITTEST_H

#include <cpptest.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KMatrixOperatorUnitTest : public Test::Suite
{
public:
    
    KMatrixOperatorUnitTest();
    virtual ~KMatrixOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testMatrixConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testMatrix();
	void	testNormalize();
	void	testIsNormalized();
	void	testSquaredNormFrobenius();
    void    testApply();
    void    testApply_Complex();
    void    testApplyAdjoint();
    void    testApplyAdjoint_Complex();
    void    testColumn();
    void    testColumn_Complex();
    void    testColumnAdjoint();
    void    testColumnAdjoint_Complex();
    void    testToMatrix();
    void    testToMatrix_Complex();
    void    testToMatrixAdjoint();
    void    testToMatrixAdjoint_Complex();

    // Functions tests.
    void    testToOperator();
    void    testToOperator_Complex();


private:

    KMatrixOperatorUnitTest(const KMatrixOperatorUnitTest& test);
    KMatrixOperatorUnitTest&    operator=(const KMatrixOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
