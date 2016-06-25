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

#ifndef KL1P_COMPRESSEDSENSINGEXAMPLE_H
#define KL1P_COMPRESSEDSENSINGEXAMPLE_H

#include <KL1pInclude.h>

namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

/// Create a random gaussian sparse signal.
/// @param size		[in] Size of the signal.
/// @param sparsity	[in] Sparsity of the signal.
/// @param mean		[in] Mean of the gaussian of the signal.
/// @param sigma	[in] Sigma (=sqrt(variance)) of the gaussian of the signal.
/// @param out		[out] Created signal.
void CreateGaussianSignal(klab::UInt32 size, klab::UInt32 sparsity, klab::DoubleReal mean, klab::DoubleReal sigma, arma::Col<klab::DoubleReal>& out);

/// Write a signal to a csv file.
/// @param signal	[in] Signal to write.
/// @param filePath	[in] Path to the file to create.
void WriteToCSVFile(const arma::Col<klab::DoubleReal>& signal, const std::string& filePath);

/// Main example function.
/// Run each implemented CS-algorithmes reconstruction on the same random generated signal.
void RunExample();

// ---------------------------------------------------------------------------------------------------- //

}


#endif
