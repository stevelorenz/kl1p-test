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

#include "KL1pTest.h"
#include "OperatorUnitTest.h"
#include "ProxyOperatorUnitTest.h"
#include "ZeroOperatorUnitTest.h"
#include "IdentityOperatorUnitTest.h"
#include "SamplingOperatorUnitTest.h"
#include "DownSamplingOperatorUnitTest.h"
#include "RandomDownSamplingOperatorUnitTest.h"
#include "Fourier1DOperatorUnitTest.h"
#include "Fourier2DOperatorUnitTest.h"
#include "InverseFourier1DOperatorUnitTest.h"
#include "InverseFourier2DOperatorUnitTest.h"
#include "Wavelet1DOperatorUnitTest.h"
#include "Wavelet2DOperatorUnitTest.h"
#include "InverseWavelet1DOperatorUnitTest.h"
#include "InverseWavelet2DOperatorUnitTest.h"
#include "WalshHadamard1DOperatorUnitTest.h"
#include "WalshHadamard2DOperatorUnitTest.h"
#include "InverseWalshHadamard1DOperatorUnitTest.h"
#include "InverseWalshHadamard2DOperatorUnitTest.h"
#include "DCT1DOperatorUnitTest.h"
#include "DCT2DOperatorUnitTest.h"
#include "InverseDCT1DOperatorUnitTest.h"
#include "InverseDCT2DOperatorUnitTest.h"
#include "Gaussian1DDiagonalOperatorUnitTest.h"
#include "Gaussian2DDiagonalOperatorUnitTest.h"
#include "InverseGaussian1DDiagonalOperatorUnitTest.h"
#include "InverseGaussian2DDiagonalOperatorUnitTest.h"
#include "GaussianBlur1DOperatorUnitTest.h"
#include "GaussianBlur2DOperatorUnitTest.h"
#include "InverseGaussianBlur1DOperatorUnitTest.h"
#include "InverseGaussianBlur2DOperatorUnitTest.h"
#include "NormalRandomOperatorUnitTest.h"
#include "UniformRandomOperatorUnitTest.h"
#include "MatrixOperatorUnitTest.h"
#include "NormalRandomMatrixOperatorUnitTest.h"
#include "UniformRandomMatrixOperatorUnitTest.h"
#include "AdditionOperatorUnitTest.h"
#include "SubtractionOperatorUnitTest.h"
#include "MultiplicationOperatorUnitTest.h"
#include "ScalarOperatorUnitTest.h"
#include "DiagonalOperatorUnitTest.h"
#include "AdjointOperatorUnitTest.h"
#include "ComplexProxyOperatorUnitTest.h"
#include "SubSystemOperatorUnitTest.h"
#include "ProxyLinearOperatorUnitTest.h"
#include "RandomBernoulliDiagonalOperatorUnitTest.h"
#include "PermutationOperatorUnitTest.h"
#include "RandomPermutationOperatorUnitTest.h"
#include "ScalingOperatorUnitTest.h"
#include "NormalizationOperatorUnitTest.h"
#include "ResizingOperatorUnitTest.h"
#include "VarianceShadowOperatorUnitTest.h"
#include "BlockOperatorUnitTest.h"
#include "ProxyBlockOperatorUnitTest.h"
#include "BlockSparseOperatorUnitTest.h"
#include "BlockDiagonalOperatorUnitTest.h"
#include "BlockTridiagonalOperatorUnitTest.h"
#include "RowJointOperatorUnitTest.h"
#include "ColumnJointOperatorUnitTest.h"
#include "JointOperatorUnitTest.h"
#include "AdjointBlockOperatorUnitTest.h"
#include "ComplexProxyBlockOperatorUnitTest.h"
#include "SeedingOperatorUnitTest.h"
#include "GenericSeedingOperatorUnitTest.h"
#include "OperatorTest.h"
#include "BasisPursuitHistoryUnitTest.h"
#include "BasisPursuitSolverUnitTest.h"
#include "OMPHistoryUnitTest.h"
#include "OMPSolverUnitTest.h"
#include "ROMPHistoryUnitTest.h"
#include "ROMPSolverUnitTest.h"
#include "CoSaMPHistoryUnitTest.h"
#include "CoSaMPSolverUnitTest.h"
#include "SubspacePursuitHistoryUnitTest.h"
#include "SubspacePursuitSolverUnitTest.h"
#include "AMPHistoryUnitTest.h"
#include "AMPSolverUnitTest.h"
#include "SL0HistoryUnitTest.h"
#include "SL0SolverUnitTest.h"
#include "EMBPHistoryUnitTest.h"
#include "EMBPSolverUnitTest.h"  

using namespace kl1p;




// ---------------------------------------------------------------------------------------------------- //

KL1pTest::KL1pTest()
{}

// ---------------------------------------------------------------------------------------------------- //

KL1pTest::~KL1pTest()
{}

// ---------------------------------------------------------------------------------------------------- //

bool KL1pTest::run()
{
    Test::Suite tests;
    
    tests.add(std::auto_ptr<Test::Suite>(new KOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KProxyOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KZeroOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KIdentityOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KSamplingOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KDownSamplingOperatorUnitTest()));   
    tests.add(std::auto_ptr<Test::Suite>(new KRandomDownSamplingOperatorUnitTest()));   
    tests.add(std::auto_ptr<Test::Suite>(new KFourier1DOperatorUnitTest()));   
    tests.add(std::auto_ptr<Test::Suite>(new KFourier2DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KInverseFourier1DOperatorUnitTest()));   
    tests.add(std::auto_ptr<Test::Suite>(new KInverseFourier2DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KWavelet1DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KWavelet2DOperatorUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KInverseWavelet1DOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KInverseWavelet2DOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KWalshHadamard1DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KWalshHadamard2DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KInverseWalshHadamard1DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KInverseWalshHadamard2DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KDCT1DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KDCT2DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KInverseDCT1DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KInverseDCT2DOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KGaussian1DDiagonalOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KGaussian2DDiagonalOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KInverseGaussian1DDiagonalOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KInverseGaussian2DDiagonalOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KGaussianBlur1DOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KGaussianBlur2DOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KInverseGaussianBlur1DOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KInverseGaussianBlur2DOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KNormalRandomOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KUniformRandomOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KMatrixOperatorUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KNormalRandomMatrixOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KUniformRandomMatrixOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KAdditionOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KSubtractionOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KMultiplicationOperatorUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KScalarOperatorUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KDiagonalOperatorUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KAdjointOperatorUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KComplexProxyOperatorUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KSubSystemOperatorUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KProxyLinearOperatorUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KRandomBernoulliDiagonalOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KPermutationOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KRandomPermutationOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KScalingOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KNormalizationOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KResizingOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KVarianceShadowOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KBlockOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KProxyBlockOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KBlockSparseOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KBlockDiagonalOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KBlockTridiagonalOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KRowJointOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KColumnJointOperatorUnitTest()));        
    tests.add(std::auto_ptr<Test::Suite>(new KJointOperatorUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KAdjointBlockOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KComplexProxyBlockOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KSeedingOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KGenericSeedingOperatorUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KOperatorTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KBasisPursuitHistoryUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KBasisPursuitSolverUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KOMPHistoryUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KOMPSolverUnitTest())); 
    tests.add(std::auto_ptr<Test::Suite>(new KROMPHistoryUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KROMPSolverUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KCoSaMPHistoryUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KCoSaMPSolverUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KSubspacePursuitHistoryUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KSubspacePursuitSolverUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KAMPHistoryUnitTest()));  
    tests.add(std::auto_ptr<Test::Suite>(new KAMPSolverUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KSL0HistoryUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KSL0SolverUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KEMBPHistoryUnitTest()));
    tests.add(std::auto_ptr<Test::Suite>(new KEMBPSolverUnitTest())); 
    
    Test::TextOutput output(Test::TextOutput::Verbose);
    return tests.run(output);
}
    
// ---------------------------------------------------------------------------------------------------- //
