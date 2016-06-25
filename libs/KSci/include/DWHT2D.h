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

#ifndef KLAB_DWHT2D_H
#define KLAB_DWHT2D_H

#include "DWHT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDWHT2D
{
public:

    TDWHT2D();
    TDWHT2D(const TDWHT2D<T>& dwht);
    virtual ~TDWHT2D();

    TDWHT2D<T>&	operator=(const TDWHT2D<T>& dwht);

    void        transform(const arma::Mat<T>& in, arma::Mat<T>& out);
    void        invert(const arma::Mat<T>& in, arma::Mat<T>& out);


protected:

    void        perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse=false);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDWHT2D<T>::TDWHT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDWHT2D<T>::TDWHT2D(const TDWHT2D<T>& dwht)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDWHT2D<T>::~TDWHT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDWHT2D<T>& TDWHT2D<T>::operator=(const TDWHT2D<T>& dwht)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDWHT2D<T>::transform(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDWHT2D<T>::invert(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDWHT2D<T>::perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse)
{
    if(in.n_rows>0 && in.n_cols>0)
    {
        TDWHT1D<T> dwht;

        if(inverse == false)
        {
            arma::Mat<T> tmpMatrix;

            dwht.transformMatrixColumns(in, tmpMatrix);
            dwht.transformMatrixColumns(arma::strans(tmpMatrix), out);
            out = arma::strans(out);
        }
        else
        {
            arma::Mat<T> tmpMatrix;

            dwht.invertMatrixColumns(arma::strans(in), tmpMatrix);
            dwht.invertMatrixColumns(arma::strans(tmpMatrix), out);
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
