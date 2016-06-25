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

#ifndef KL1P_INVERSEFOURIER2DOPERATOR_H
#define KL1P_INVERSEFOURIER2DOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseFourier2DOperator : public TOperator<T, T>
{
public:

    TInverseFourier2DOperator(klab::UInt32 height, klab::UInt32 width, bool shift=false);
    TInverseFourier2DOperator(const TInverseFourier2DOperator<T>& op);
    virtual ~TInverseFourier2DOperator();    

    klab::UInt32     width() const;
    klab::UInt32     height() const;
    bool                    isShift() const;

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TInverseFourier2DOperator();
    TInverseFourier2DOperator<T>&   operator=(const TInverseFourier2DOperator<T>& op);


private:

    klab::UInt32            _width;
    klab::UInt32            _height;

    klab::TFFT2D<T>         _fft;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseFourier2DOperatorSpecialisation
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::UInt32 height, klab::UInt32 width, klab::TFFT2D<T>& fft); 


protected:

    static void     ApplyAdjointToMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out, klab::TFFT1D<T>& fft); 


private:

    TInverseFourier2DOperatorSpecialisation();
    TInverseFourier2DOperatorSpecialisation(const TInverseFourier2DOperatorSpecialisation<T>& spec);
    TInverseFourier2DOperatorSpecialisation<T>&     operator=(const TInverseFourier2DOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseFourier2DOperatorSpecialisation<std::complex<T> >
{
public:

    static void     ApplyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out, klab::UInt32 height, klab::UInt32 width, klab::TFFT2D<std::complex<T> >& fft); 


private:

    TInverseFourier2DOperatorSpecialisation();
    TInverseFourier2DOperatorSpecialisation(const TInverseFourier2DOperatorSpecialisation<T>& spec);
    TInverseFourier2DOperatorSpecialisation<T>&     operator=(const TInverseFourier2DOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseFourier2DOperator<T>::TInverseFourier2DOperator(klab::UInt32 height, klab::UInt32 width, bool shift) : TOperator<T, T>(width*height),
_width(width), _height(height),
_fft(shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseFourier2DOperator<T>::TInverseFourier2DOperator(const TInverseFourier2DOperator<T>& op) : TOperator<T, T>(op),
_width(op._width), _height(op._height),
_fft(op._fft)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseFourier2DOperator<T>::~TInverseFourier2DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseFourier2DOperator<T>::width() const
{
    return _width;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseFourier2DOperator<T>::height() const
{
    return _height;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TInverseFourier2DOperator<T>::isShift() const
{
    return _fft.shift();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseFourier2DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());

    arma::Mat<T> inMatrix(in);
    arma::Mat<T> outMatrix;
    inMatrix.reshape(_height, _width);

    _fft.invert(inMatrix, outMatrix);

    outMatrix.reshape(this->n(), 1);
    out = outMatrix;
    
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseFourier2DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    TInverseFourier2DOperatorSpecialisation<T>::ApplyAdjoint(in, out, _height, _width, _fft);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseFourier2DOperatorSpecialisation<T>::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::UInt32 height, klab::UInt32 width, klab::TFFT2D<T>& fft)
{
    if(in.n_rows>0 && in.n_cols>0)
    {
        if(height>0 && width>0)
        {
            arma::Mat<T> inMatrix(in);
            inMatrix.reshape(height, width);

            arma::Mat<T> tmpMatrix;
            arma::Mat<T> outMatrix;

            klab::TFFT1D<T> fft1D(fft.shift());
            TInverseFourier2DOperatorSpecialisation<T>::ApplyAdjointToMatrixColumns(inMatrix, tmpMatrix, fft1D);
            TInverseFourier2DOperatorSpecialisation<T>::ApplyAdjointToMatrixColumns(arma::strans(tmpMatrix), outMatrix, fft1D);
            outMatrix = arma::strans(outMatrix);

            outMatrix.reshape(width*height, 1);
            out = outMatrix;
        }
        else
        {
            out.set_size(in.n_rows, in.n_cols);
            out.fill(klab::TTypeInfo<T>::ZERO);
        }
    }
    else
    {
        out.set_size(in.n_rows, in.n_cols);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseFourier2DOperatorSpecialisation<T>::ApplyAdjointToMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out, klab::TFFT1D<T>& fft)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;

    if(m>0 && n>0)
    {
        fft.transformMatrixColumns(in, out);

        for(klab::UInt32 j=0; j<n; ++j)
        {        
            klab::UInt32 halfM = m / 2;

            T invM     = klab::TTypeInfo<T>::UNIT / static_cast<T>(m);
            T invHalfM = static_cast<T>(2) * invM;

            out(0, j) *= invM;
            for(klab::UInt32 i=1; i<m; ++i)
                out(i, j) *= invHalfM;

            if(m%2 == 0)
                out(halfM, j) /= static_cast<T>(2);
        }
    }
    else
    {
        out.set_size(m, n);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseFourier2DOperatorSpecialisation<std::complex<T> >::ApplyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out, klab::UInt32 height, klab::UInt32 width, klab::TFFT2D<std::complex<T> >& fft)
{   
    arma::Mat<std::complex<T> > inMatrix(in);
    arma::Mat<std::complex<T> > outMatrix;
    inMatrix.reshape(height, width);

    fft.transform(inMatrix, outMatrix);

    outMatrix.reshape(width*height, 1);
    out.set_size(outMatrix.n_rows);

    // Normalization.
    if(outMatrix.n_rows > 0)
    {
        T invN = klab::TTypeInfo<T>::UNIT / static_cast<T>(outMatrix.n_rows);
        for(klab::UInt32 i=0; i<outMatrix.n_rows; ++i)
            out[i] = outMatrix[i] * invN;
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
