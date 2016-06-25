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

#ifndef KL1P_FOURIER2DOPERATOR_H
#define KL1P_FOURIER2DOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFourier2DOperator : public TOperator<T, T>
{
public:
    
    TFourier2DOperator(klab::UInt32 height, klab::UInt32 width, bool shift=false); 
    TFourier2DOperator(const TFourier2DOperator<T>& op);
    virtual ~TFourier2DOperator();    

    klab::UInt32     width() const;
    klab::UInt32     height() const;
    bool                    isShift() const;

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TFourier2DOperator();
    TFourier2DOperator<T>&  operator=(const TFourier2DOperator<T>& op);


private:

    klab::UInt32            _width;
    klab::UInt32            _height;

    klab::TFFT2D<T>         _fft;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFourier2DOperatorSpecialisation
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::UInt32 height, klab::UInt32 width, klab::TFFT2D<T>& fft); 


private:

    TFourier2DOperatorSpecialisation();
    TFourier2DOperatorSpecialisation(const TFourier2DOperatorSpecialisation<T>& spec);
    TFourier2DOperatorSpecialisation<T>&    operator=(const TFourier2DOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFourier2DOperatorSpecialisation<std::complex<T> >
{
public:

    static void     ApplyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out, klab::UInt32 height, klab::UInt32 width, klab::TFFT2D<std::complex<T> >& fft); 


private:

    TFourier2DOperatorSpecialisation();
    TFourier2DOperatorSpecialisation(const TFourier2DOperatorSpecialisation<T>& spec);
    TFourier2DOperatorSpecialisation<T>&    operator=(const TFourier2DOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFourier2DOperator<T>::TFourier2DOperator(klab::UInt32 height, klab::UInt32 width, bool shift) : TOperator<T, T>(width*height),
_width(width), _height(height),
_fft(shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFourier2DOperator<T>::TFourier2DOperator(const TFourier2DOperator<T>& op) : TOperator<T, T>(op),
_width(op._width), _height(op._height),
_fft(op._fft)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFourier2DOperator<T>::~TFourier2DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TFourier2DOperator<T>::width() const
{
    return _width;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TFourier2DOperator<T>::height() const
{
    return _height;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TFourier2DOperator<T>::isShift() const
{
    return _fft.shift();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFourier2DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());

    arma::Mat<T> inMatrix(in);
    arma::Mat<T> outMatrix;
    inMatrix.reshape(_height, _width);

    _fft.transform(inMatrix, outMatrix);

    outMatrix.reshape(this->n(), 1);
    out = outMatrix;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFourier2DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    TFourier2DOperatorSpecialisation<T>::ApplyAdjoint(in, out, _width, _height, _fft);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFourier2DOperatorSpecialisation<T>::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::UInt32 height, klab::UInt32 width, klab::TFFT2D<T>& fft)
{
    // To optimize.
    arma::Mat<T> fftMatrix(in.n_rows, in.n_rows);
    for(klab::UInt32 j=0; j<in.n_rows; ++j)
    {
        arma::Mat<T> base(in.n_rows, 1);
        arma::Mat<T> col;
        base.fill(klab::TTypeInfo<T>::ZERO);
        base[j] = klab::TTypeInfo<T>::UNIT;
        base.reshape(height, width);

        fft.transform(base, col);

        col.reshape(width*height, 1);
        for(klab::UInt32 i=0; i<col.n_rows; ++i)
            fftMatrix(i, j) = col[i];
    } 

    out = arma::trans(fftMatrix) * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFourier2DOperatorSpecialisation<std::complex<T> >::ApplyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out, klab::UInt32 height, klab::UInt32 width, klab::TFFT2D<std::complex<T> >& fft)
{
    arma::Mat<std::complex<T> > inMatrix(in);
    arma::Mat<std::complex<T> > outMatrix;
    inMatrix.reshape(height, width);

    fft.invert(inMatrix, outMatrix);

    outMatrix.reshape(width*height, 1);
    out.set_size(outMatrix.n_rows);

    // Normalization.
    for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
        out[i] = outMatrix[i] * static_cast<T>(outMatrix.n_rows);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
