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

#ifndef KLAB_GAUSSWIENERFILTER2DUNITTEST_H
#define KLAB_GAUSSWIENERFILTER2DUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KGaussWienerFilter2DUnitTest : public Test::Suite
{
public:
    
    KGaussWienerFilter2DUnitTest();
    virtual ~KGaussWienerFilter2DUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testMNConstructor(); 
    void    testMNGammaConstructor(); 
    void    testMNGammaSigmaConstructor(); 
    void    testMNGammaSigmaIcJcConstructor(); 
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testM();
    void    testN();
    void    testGamma();
    void    testSigma();
    void    testIc();
    void    testJc();
    void    testApply_InOut();
    void    testApply_In_Out();


private:

    KGaussWienerFilter2DUnitTest(const KGaussWienerFilter2DUnitTest& test);
    KGaussWienerFilter2DUnitTest&   operator=(const KGaussWienerFilter2DUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
