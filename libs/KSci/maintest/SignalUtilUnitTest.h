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

#ifndef KLAB_SIGNALUTILUNITTEST_H
#define KLAB_SIGNALUTILUNITTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KSignalUtilUnitTest : public Test::Suite
{
public:
    
    KSignalUtilUnitTest();
    virtual ~KSignalUtilUnitTest();
    
    
protected:

    // Functions tests.
    void    testSquaredError_Vector();
    void    testSquaredError_Matrix();
    void    testRootSquaredError_Vector();
    void    testRootSquaredError_Matrix();
    void    testSqrtSquaredError_Vector();
    void    testSqrtSquaredError_Matrix();
    void    testMeanSquaredError_Vector();
    void    testMeanSquaredError_Matrix();
    void    testRootMeanSquaredError_Vector();
    void    testRootMeanSquaredError_Matrix();
    void    testSNR_Vector();
    void    testSNR_Matrix();
    void    testPSNR_Vector();
    void    testPSNR_Matrix();
    void    testSparsify_Vector();
    void    testSparsify_Matrix();
    void    testConvolve_Vector();
    void    testConvolve_Vector_Complex();
    void    testConvolve_Matrix();
    void    testConvolve_Matrix_Complex();
    void    testCrossCorrelate_Vector();
    void    testCrossCorrelate_Vector_Complex();
    void    testCrossCorrelate_Matrix();
    void    testCrossCorrelate_Matrix_Complex();
    void    testCorrelation_Vector();
    void    testCorrelation_Vector_Complex();
    void    testCorrelation_Matrix();
    void    testCorrelation_Matrix_Complex();
    void    testDownsample_Vector();
    void    testDownsample_Matrix();
    void    testUpsample_Vector();
    void    testUpsample_Matrix();


private:

    KSignalUtilUnitTest(const KSignalUtilUnitTest& test);
    KSignalUtilUnitTest&    operator=(const KSignalUtilUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}

#endif
