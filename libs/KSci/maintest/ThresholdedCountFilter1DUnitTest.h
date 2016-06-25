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

#ifndef KLAB_THRESHOLDEDCOUNTFILTER1DUNITTEST_H
#define KLAB_THRESHOLDEDCOUNTFILTER1DUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KThresholdedCountFilter1DUnitTest : public Test::Suite
{
public:
    
    KThresholdedCountFilter1DUnitTest();
    virtual ~KThresholdedCountFilter1DUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testCountConstructor(); 
    void    testCountValueConstructor(); 
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Methods tests.
    void    testCount();
    void    testValue();
    void    testApply_InOut();
    void    testApply_In_Out();


private:

    KThresholdedCountFilter1DUnitTest(const KThresholdedCountFilter1DUnitTest& test);
    KThresholdedCountFilter1DUnitTest&    operator=(const KThresholdedCountFilter1DUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
