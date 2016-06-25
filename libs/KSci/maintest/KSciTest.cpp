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

#include "KSciTest.h"
#include "MathsUtilUnitTest.h"
#include "TrigoUtilUnitTest.h"
#include "ComplexUnitTest.h"
#include "ArmadilloTest.h"
#include "ArmadilloUtilUnitTest.h"
#include "MatrixLinearOperatorUnitTest.h"
#include "ComplexProxyLinearOperatorUnitTest.h"
#include "LeastSquareSystemSolverUnitTest.h"
#include "ConjugateGradientSystemSolverUnitTest.h"
#include "DFT1DUnitTest.h"
#include "DFT2DUnitTest.h"
#include "FFT1DUnitTest.h"
#include "FFT2DUnitTest.h"
#include "DWT1DUnitTest.h"
#include "DWT2DUnitTest.h"
#include "FWT1DUnitTest.h"
#include "FWT2DUnitTest.h"
#include "DWHT1DUnitTest.h"
#include "DWHT2DUnitTest.h"   
#include "FWHT1DUnitTest.h"   
#include "FWHT2DUnitTest.h"   
#include "DCT1DUnitTest.h"
#include "DCT2DUnitTest.h"
#include "FCT1DUnitTest.h"
#include "FCT2DUnitTest.h"
#include "ThresholdedCountFilter1DUnitTest.h"
#include "ThresholdedCountFilter2DUnitTest.h"
#include "SignalUtilUnitTest.h"
#include "GaussUtilUnitTest.h"
#include "GaussianFilter1DUnitTest.h"
#include "GaussianFilter2DUnitTest.h"
#include "GaussWienerFilter1DUnitTest.h"
#include "GaussWienerFilter2DUnitTest.h"
#include "Vector2DUnitTest.h"
#include "Vector3DUnitTest.h"
#include "LinearInterpolationFilterUnitTest.h"
#include "CubicInterpolationFilterUnitTest.h"
#include "Interpolator1DUnitTest.h"
#include "BilinearInterpolationFilterUnitTest.h"
#include "BicubicInterpolationFilterUnitTest.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KSciTest::KSciTest()
{}

// ---------------------------------------------------------------------------------------------------- //

KSciTest::~KSciTest()
{}

// ---------------------------------------------------------------------------------------------------- //

bool KSciTest::run()
{
    Test::Suite tests;
    
    tests.add(std::auto_ptr<Test::Suite>(new KMathsUtilUnitTest()));   
	tests.add(std::auto_ptr<Test::Suite>(new KTrigoUtilUnitTest()));  
	tests.add(std::auto_ptr<Test::Suite>(new KComplexUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KArmadilloTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KArmadilloUtilUnitTest()));      
    tests.add(std::auto_ptr<Test::Suite>(new KMatrixLinearOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KComplexProxyLinearOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KLeastSquareSystemSolverUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KConjugateGradientSystemSolverUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KDFT1DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KDFT2DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KFFT1DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KFFT2DUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KDWT1DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KDWT2DUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KFWT1DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KFWT2DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KDWHT1DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KDWHT2DUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KFWHT1DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KFWHT2DUnitTest()));     
    tests.add(std::auto_ptr<Test::Suite>(new KDCT1DUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KDCT2DUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KFCT1DUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KFCT2DUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KThresholdedCountFilter1DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KThresholdedCountFilter2DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KSignalUtilUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KGaussUtilUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KGaussianFilter1DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KGaussianFilter2DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KGaussWienerFilter1DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KGaussWienerFilter2DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KVector2DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KVector3DUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KLinearInterpolationFilterUnitTest()));
	tests.add(std::auto_ptr<Test::Suite>(new KCubicInterpolationFilterUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KInterpolator1DUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KBilinearInterpolationFilterUnitTest()));
	tests.add(std::auto_ptr<Test::Suite>(new KBicubicInterpolationFilterUnitTest()));
    
    Test::TextOutput output(Test::TextOutput::Verbose);
    return tests.run(output);
}
    
// ---------------------------------------------------------------------------------------------------- //
