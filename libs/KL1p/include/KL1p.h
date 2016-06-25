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

#ifndef KL1P_KL1P_H
#define KL1P_KL1P_H


#include "Operator.h"
#include "ProxyOperator.h"
#include "ZeroOperator.h"
#include "IdentityOperator.h"
#include "SamplingOperator.h"
#include "DownSamplingOperator.h"
#include "RandomDownSamplingOperator.h"
#include "Fourier1DOperator.h"
#include "Fourier2DOperator.h"
#include "InverseFourier1DOperator.h"
#include "InverseFourier2DOperator.h"
#include "Wavelet1DOperator.h"
#include "Wavelet2DOperator.h"
#include "InverseWavelet1DOperator.h"
#include "InverseWavelet2DOperator.h"
#include "WalshHadamard1DOperator.h"
#include "WalshHadamard2DOperator.h"
#include "InverseWalshHadamard1DOperator.h"
#include "InverseWalshHadamard2DOperator.h"
#include "DCT1DOperator.h"
#include "DCT2DOperator.h"
#include "InverseDCT1DOperator.h"
#include "InverseDCT2DOperator.h"
#include "Gaussian1DDiagonalOperator.h"
#include "Gaussian2DDiagonalOperator.h"
#include "InverseGaussian1DDiagonalOperator.h"
#include "InverseGaussian2DDiagonalOperator.h"
#include "GaussianBlur1DOperator.h"
#include "GaussianBlur2DOperator.h"
#include "InverseGaussianBlur1DOperator.h"
#include "InverseGaussianBlur2DOperator.h"
#include "NormalRandomOperator.h"
#include "UniformRandomOperator.h"
#include "MatrixOperator.h"
#include "NormalRandomMatrixOperator.h"
#include "MatrixFromCSV.h"
#include "UniformRandomMatrixOperator.h"
#include "AdditionOperator.h"
#include "SubtractionOperator.h"
#include "MultiplicationOperator.h"
#include "ScalarOperator.h"
#include "DiagonalOperator.h"
#include "AdjointOperator.h"
#include "ComplexProxyOperator.h"
#include "SubSystemOperator.h"
#include "ProxyLinearOperator.h"
#include "RandomBernoulliDiagonalOperator.h"
#include "PermutationOperator.h"
#include "RandomPermutationOperator.h"
#include "ScalingOperator.h"
#include "NormalizationOperator.h"
#include "ResizingOperator.h"
#include "VarianceShadowOperator.h"
#include "BlockOperator.h"
#include "ProxyBlockOperator.h"
#include "BlockSparseOperator.h"
#include "BlockDiagonalOperator.h"
#include "BlockTridiagonalOperator.h"
#include "RowJointOperator.h"
#include "ColumnJointOperator.h"
#include "JointOperator.h"
#include "AdjointBlockOperator.h"
#include "ComplexProxyBlockOperator.h"
#include "SeedingOperator.h"
#include "GenericSeedingOperator.h"

#include "BasisPursuitSolver.h"
#include "OMPSolver.h"
#include "ROMPSolver.h"
#include "CoSaMPSolver.h"
#include "SubspacePursuitSolver.h"
#include "AMPSolver.h"
#include "SL0Solver.h"
#include "EMBPSolver.h"


#endif
