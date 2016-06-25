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

#ifndef KL1P_MATRIXFROMCSV_H
#define KL1P_MATRIXFROMCSV_H

#include <string>
#include "MatrixOperator.h"

using std::string;

// ---------------------------------------------------------------------------------------------------- //

namespace kl1p
{

// init class
template<class T>
class TMatrixFromCSV : public TMatrixOperator<T>
{
public:
    // init functions
    TMatrixFromCSV(klab::UInt32 m, klab::UInt32 n, string file_name);
    TMatrixFromCSV(const TMatrixFromCSV<T>& op);
    virtual ~TMatrixFromCSV();

private:

    TMatrixFromCSV();
    TMatrixFromCSV<T>&     operator=(const TMatrixFromCSV<T>& op);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
/**
 * @brief Load sensing matrix from a CSV file
 *
 * @para klab::UInt32
 * @para klab::UInt32
 * @para string file_namem
 */
inline TMatrixFromCSV<T>::TMatrixFromCSV(klab::UInt32 m, klab::UInt32 n, string file_name) : TMatrixOperator<T>()
{
    arma::Mat<T>& mat = this->matrixReference();
    // init matrix size -> N * N
    mat.set_size(m, n);
    // load matrix
    mat.load(file_name, arma::csv_ascii);
    // resize matrix
    this->resize(m, n);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixFromCSV<T>::TMatrixFromCSV(const TMatrixFromCSV<T>& op) : TMatrixOperator<T>(op)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixFromCSV<T>::~TMatrixFromCSV()
{}

// ---------------------------------------------------------------------------------------------------- //
}  // end namespace

#endif
