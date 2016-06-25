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

#ifndef KLAB_DFT2D_H
#define KLAB_DFT2D_H

#include "DFT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDFT2D
{
public:

    TDFT2D();
    TDFT2D(bool shift);
    TDFT2D(const TDFT2D<T>& dft);
    virtual ~TDFT2D();

    TDFT2D<T>&  operator=(const TDFT2D<T>& dft);

    void        setShift(bool shift);
    bool        shift() const;

    void        transform(const arma::Mat<T>& in, arma::Mat<T>& out);
    void        invert(const arma::Mat<T>& in, arma::Mat<T>& out);


protected:

    void        perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse=false);


private:

    bool        _shift;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT2D<T>::TDFT2D() : 
_shift(false)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT2D<T>::TDFT2D(bool shift) : 
_shift(shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT2D<T>::TDFT2D(const TDFT2D<T>& dft) : 
_shift(dft._shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT2D<T>::~TDFT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT2D<T>& TDFT2D<T>::operator=(const TDFT2D<T>& dft)
{
    if(this != &dft)
    {
        _shift = dft._shift;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT2D<T>::setShift(bool shift)
{
    _shift = shift;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TDFT2D<T>::shift() const
{
    return _shift;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT2D<T>::transform(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT2D<T>::invert(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT2D<T>::perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse)
{
    if(in.n_rows>0 && in.n_cols>0)
    {
        TDFT1D<T> dft(_shift);

        if(inverse == false)
        {
            arma::Mat<T> tmpMatrix;

            dft.transformMatrixColumns(in, tmpMatrix);
            dft.transformMatrixColumns(arma::strans(tmpMatrix), out);
            out = arma::strans(out);
        }
        else
        {
            arma::Mat<T> tmpMatrix;

            dft.invertMatrixColumns(arma::strans(in), tmpMatrix);
            dft.invertMatrixColumns(arma::strans(tmpMatrix), out);
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
