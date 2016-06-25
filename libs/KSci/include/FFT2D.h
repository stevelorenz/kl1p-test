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

#ifndef KLAB_FFT2D_H
#define KLAB_FFT2D_H

#include "FFT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFFT2D
{
public:

    TFFT2D();
    TFFT2D(bool shift);
    TFFT2D(const TFFT2D<T>& fft);
    virtual ~TFFT2D();

    TFFT2D<T>&  operator=(const TFFT2D<T>& fft);

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
inline TFFT2D<T>::TFFT2D() : 
_shift(false)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFFT2D<T>::TFFT2D(bool shift) : 
_shift(shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFFT2D<T>::TFFT2D(const TFFT2D<T>& fft) : 
_shift(fft._shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFFT2D<T>::~TFFT2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFFT2D<T>& TFFT2D<T>::operator=(const TFFT2D<T>& fft)
{
    if(this != &fft)
    {
        _shift = fft._shift;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT2D<T>::setShift(bool shift)
{
    _shift = shift;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TFFT2D<T>::shift() const
{
    return _shift;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT2D<T>::transform(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT2D<T>::invert(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT2D<T>::perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse)
{
    if(in.n_rows>0 && in.n_cols>0)
    {
        TFFT1D<T> fft(_shift);

        if(inverse == false)
        {
            arma::Mat<T> tmpMatrix;

            fft.transformMatrixColumns(in, tmpMatrix);
            fft.transformMatrixColumns(arma::strans(tmpMatrix), out);
            out = arma::strans(out);
        }
        else
        {
            arma::Mat<T> tmpMatrix;

            fft.invertMatrixColumns(arma::strans(in), tmpMatrix);
            fft.invertMatrixColumns(arma::strans(tmpMatrix), out);
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
