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

#ifndef KLAB_FWHT2D_H
#define KLAB_FWHT2D_H

#include "FWHT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFWHT2D
{
public:

    TFWHT2D();
    TFWHT2D(const TFWHT2D<T>& fwht);
    virtual ~TFWHT2D();

    TFWHT2D<T>&	operator=(const TFWHT2D<T>& fwht);

    void        transform(const arma::Mat<T>& in, arma::Mat<T>& out);
    void        invert(const arma::Mat<T>& in, arma::Mat<T>& out);


protected:

    void        perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse=false);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFWHT2D<T>::TFWHT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFWHT2D<T>::TFWHT2D(const TFWHT2D<T>& fwht)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFWHT2D<T>::~TFWHT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFWHT2D<T>& TFWHT2D<T>::operator=(const TFWHT2D<T>& fwht)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFWHT2D<T>::transform(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFWHT2D<T>::invert(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFWHT2D<T>::perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse)
{
    if(in.n_rows>0 && in.n_cols>0)
    {
        TFWHT1D<T> fwht;

        if(inverse == false)
        {
            arma::Mat<T> tmpMatrix;

            fwht.transformMatrixColumns(in, tmpMatrix);
            fwht.transformMatrixColumns(arma::strans(tmpMatrix), out);
            out = arma::strans(out);
        }
        else
        {
            arma::Mat<T> tmpMatrix;

            fwht.invertMatrixColumns(arma::strans(in), tmpMatrix);
            fwht.invertMatrixColumns(arma::strans(tmpMatrix), out);
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
