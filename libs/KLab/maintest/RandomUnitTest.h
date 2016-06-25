// KLab - A portable C++ collection of classes for general purpose.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KLab C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_RANDOMUNITTEST_H
#define KLAB_RANDOMUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KRandomUnitTest : public Test::Suite
{
public:
    
    KRandomUnitTest();
    virtual ~KRandomUnitTest();
    
    
protected:

    // Construction/Affectation tests.
    void    testDefaultConstructor();
    void    testSeedConstructor();
    void    testCopyConstructor();
    void    testAffectationOperator();

    // Operators tests.
    void    testLowerOperator();

    // Methods tests.
    void    testSetSeed();
    void    testResetSeed();
    void    testSeed();
    void    testGenerateBool();
    void    testGenerateUInt8();
    void    testGenerateInt8();
    void    testGenerateUInt16();
    void    testGenerateInt16();
    void    testGenerateUInt32();
    void    testGenerateInt32();
    void    testGenerateUInt64(); 
    void    testGenerateInt64(); 
    void    testGenerateReal();
    void    testGenerateDoubleReal();
    void    testGenerate();
    void    testGenerateBitArray();

    // Static functions tests.
    void    testInstance();


private:

    KRandomUnitTest(const KRandomUnitTest& test);
    KRandomUnitTest&    operator=(const KRandomUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
