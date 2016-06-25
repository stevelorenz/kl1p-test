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

#ifndef KLAB_DCT2D_H
#define KLAB_DCT2D_H

#include "DCT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDCT2D
{
public:

    TDCT2D();
    TDCT2D(const TDCT2D<T>& dct);
    virtual ~TDCT2D();

    TDCT2D<T>&  operator=(const TDCT2D<T>& dct);

    void        transform(const arma::Mat<T>& in, arma::Mat<T>& out);
    void        invert(const arma::Mat<T>& in, arma::Mat<T>& out);


protected:

    void        perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse=false);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT2D<T>::TDCT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT2D<T>::TDCT2D(const TDCT2D<T>& dct)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT2D<T>::~TDCT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT2D<T>& TDCT2D<T>::operator=(const TDCT2D<T>& dct)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT2D<T>::transform(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT2D<T>::invert(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT2D<T>::perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse)
{
    if(in.n_rows>0 && in.n_cols>0)
    {
        TDCT1D<T> dct;

        if(inverse == false)
        {
            arma::Mat<T> tmpMatrix;

            dct.transformMatrixColumns(in, tmpMatrix);
            dct.transformMatrixColumns(arma::strans(tmpMatrix), out);
            out = arma::strans(out);
        }
        else
        {
            arma::Mat<T> tmpMatrix;

            dct.invertMatrixColumns(arma::strans(in), tmpMatrix);
            dct.invertMatrixColumns(arma::strans(tmpMatrix), out);
        }
    }
    else
    {
        out.set_size(in.n_rows, in.n_cols);
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
