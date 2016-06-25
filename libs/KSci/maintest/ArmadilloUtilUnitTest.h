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

#ifndef KLAB_ARMADILLOUTILUNITTEST_H
#define KLAB_ARMADILLOUTILUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KArmadilloUtilUnitTest : public Test::Suite
{
public:
    
    KArmadilloUtilUnitTest();
    virtual ~KArmadilloUtilUnitTest();
    
    
protected:

    // Functions tests.
    void    testMin_ColVector();
    void    testMin_RowVector();
    void    testMin_Matrix();
    void    testMax_ColVector();
    void    testMax_RowVector();
    void    testMax_Matrix();
    void    testGetFrom_ColVector();
    void    testGetFrom_RowVector();
    void    testGetFrom_Matrix();
    void    testSetTo_ColVector();
    void    testSetTo_RowVector();
    void    testSetTo_Matrix();
    void    testEquals_ColVector();
    void    testEquals_RowVector();
    void    testEquals_Matrix();
    void    testConvert_ColVector();
    void    testConvert_RowVector();
    void    testConvert_Matrix();
    void    testShiftCircular_ColVector();
    void    testShiftCircular_RowVector();


private:

    KArmadilloUtilUnitTest(const KArmadilloUtilUnitTest& test);
    KArmadilloUtilUnitTest&     operator=(const KArmadilloUtilUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
