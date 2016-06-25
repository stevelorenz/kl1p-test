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

#ifndef KL1P_INVERSEGAUSSIANBLUR2DOPERATOR_H
#define KL1P_INVERSEGAUSSIANBLUR2DOPERATOR_H

#include "Operator.h"
#include "Fourier2DOperator.h"
#include "InverseFourier2DOperator.h"
#include "InverseGaussian2DDiagonalOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseGaussianBlur2DOperator : public TOperator<T, T>
{
public:

    TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width);
    TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma);
    TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma, const T& sigma);
    TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma, const T& sigma, klab::Int32 ic, klab::Int32 jc);
    TInverseGaussianBlur2DOperator(const TInverseGaussianBlur2DOperator<T>& op);
    virtual ~TInverseGaussianBlur2DOperator();    

    klab::UInt32            width() const;
    klab::UInt32            height() const;
    T                       gamma() const;
    T                       sigma() const;
    klab::Int32             ic() const;
    klab::Int32             jc() const;

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TInverseGaussianBlur2DOperator();
    TInverseGaussianBlur2DOperator<T>&  operator=(const TInverseGaussianBlur2DOperator<T>& op);


private:

    TFourier2DOperator<std::complex<T> >                    _fft;
    TInverseFourier2DOperator<std::complex<T> >             _ifft;
    TInverseGaussian2DDiagonalOperator<std::complex<T> >    _gaussian;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseGaussianBlur2DOperator<std::complex<T> > : public TOperator<std::complex<T>, std::complex<T> >
{
public:

    TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width);
    TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const std::complex<T>& gamma);
    TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const std::complex<T>& gamma, const std::complex<T>& sigma);
    TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const std::complex<T>& gamma, const std::complex<T>& sigma, klab::Int32 ic, klab::Int32 jc);
    TInverseGaussianBlur2DOperator(const TInverseGaussianBlur2DOperator<std::complex<T> >& op);
    virtual ~TInverseGaussianBlur2DOperator();    

    klab::UInt32            width() const;
    klab::UInt32            height() const;
    std::complex<T>         gamma() const;
    std::complex<T>         sigma() const;
    klab::Int32             ic() const;
    klab::Int32             jc() const;

    virtual void            apply(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out);
    virtual void            applyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out);


private:

    TInverseGaussianBlur2DOperator();
    TInverseGaussianBlur2DOperator<std::complex<T> >&   operator=(const TInverseGaussianBlur2DOperator<std::complex<T> >& op);


private:

    TFourier2DOperator<std::complex<T> >                    _fft;
    TInverseFourier2DOperator<std::complex<T> >             _ifft;
    TInverseGaussian2DDiagonalOperator<std::complex<T> >    _gaussian;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<T>::TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width) : TOperator<T, T>(width*height),
_fft(height, width, true), _ifft(height, width, true), _gaussian(height, width)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<T>::TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma) : TOperator<T, T>(width*height),
_fft(height, width, true), _ifft(height, width, true), _gaussian(height, width, gamma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<T>::TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma, const T& sigma) : TOperator<T, T>(width*height),
_fft(height, width, true), _ifft(height, width, true), _gaussian(height, width, gamma, sigma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<T>::TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const T& gamma, const T& sigma, klab::Int32 ic, klab::Int32 jc) : TOperator<T, T>(width*height),
_fft(height, width, true), _ifft(height, width, true), _gaussian(height, width, gamma, sigma, ic, jc)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<T>::TInverseGaussianBlur2DOperator(const TInverseGaussianBlur2DOperator<T>& op) : TOperator<T, T>(op),
_fft(op._fft), _ifft(op._ifft), _gaussian(op._gaussian)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<T>::~TInverseGaussianBlur2DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseGaussianBlur2DOperator<T>::width() const
{
    return _gaussian.width();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseGaussianBlur2DOperator<T>::height() const
{
    return _gaussian.height();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TInverseGaussianBlur2DOperator<T>::gamma() const
{
    return _gaussian.gamma().real();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TInverseGaussianBlur2DOperator<T>::sigma() const
{
    return _gaussian.sigma().real();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TInverseGaussianBlur2DOperator<T>::ic() const
{
    return _gaussian.ic();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TInverseGaussianBlur2DOperator<T>::jc() const
{
    return _gaussian.jc();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseGaussianBlur2DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    arma::Col<std::complex<T> > tmp1;   
    arma::Col<std::complex<T> > tmp2;
    klab::Convert(in, tmp1);    

    _fft.apply(tmp1, tmp2);
    _gaussian.apply(tmp2, tmp1);
    _ifft.apply(tmp1, tmp2);

    klab::Convert(tmp2, out);    
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseGaussianBlur2DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    arma::Col<std::complex<T> > tmp1;   
    arma::Col<std::complex<T> > tmp2;
    klab::Convert(in, tmp1);    

    _ifft.applyAdjoint(tmp1, tmp2);
    _gaussian.applyAdjoint(tmp2, tmp1);
    _fft.applyAdjoint(tmp1, tmp2);

    klab::Convert(tmp2, out);    
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<std::complex<T> >::TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width) : TOperator<std::complex<T>, std::complex<T> >(width*height),
_fft(height, width, true), _ifft(height, width, true), _gaussian(height, width)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<std::complex<T> >::TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const std::complex<T>& gamma) : TOperator<std::complex<T>, std::complex<T> >(width*height),
_fft(height, width, true), _ifft(height, width, true), _gaussian(height, width, gamma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<std::complex<T> >::TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const std::complex<T>& gamma, const std::complex<T>& sigma) : TOperator<std::complex<T>, std::complex<T> >(width*height),
_fft(height, width, true), _ifft(height, width, true), _gaussian(height, width, gamma, sigma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<std::complex<T> >::TInverseGaussianBlur2DOperator(klab::UInt32 height, klab::UInt32 width, const std::complex<T>& gamma, const std::complex<T>& sigma, klab::Int32 ic, klab::Int32 jc) : TOperator<std::complex<T>, std::complex<T> >(width*height),
_fft(height, width, true), _ifft(height, width, true), _gaussian(height, width, gamma, sigma, ic, jc)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<std::complex<T> >::TInverseGaussianBlur2DOperator(const TInverseGaussianBlur2DOperator<std::complex<T> >& op) : TOperator<std::complex<T>, std::complex<T> >(op),
_fft(op._fft), _ifft(op._ifft), _gaussian(op._gaussian)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur2DOperator<std::complex<T> >::~TInverseGaussianBlur2DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseGaussianBlur2DOperator<std::complex<T> >::width() const
{
    return _gaussian.width();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TInverseGaussianBlur2DOperator<std::complex<T> >::height() const
{
    return _gaussian.height();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TInverseGaussianBlur2DOperator<std::complex<T> >::gamma() const
{
    return _gaussian.gamma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TInverseGaussianBlur2DOperator<std::complex<T> >::sigma() const
{
    return _gaussian.sigma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TInverseGaussianBlur2DOperator<std::complex<T> >::ic() const
{
    return _gaussian.ic();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TInverseGaussianBlur2DOperator<std::complex<T> >::jc() const
{
    return _gaussian.jc();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseGaussianBlur2DOperator<std::complex<T> >::apply(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());

    arma::Col<std::complex<T> > tmp1;      
    arma::Col<std::complex<T> > tmp2;

    _fft.apply(in, tmp1);
    _gaussian.apply(tmp1, tmp2);
    _ifft.apply(tmp2, out);   
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseGaussianBlur2DOperator<std::complex<T> >::applyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    arma::Col<std::complex<T> > tmp1;      
    arma::Col<std::complex<T> > tmp2;

    _ifft.applyAdjoint(in, tmp1);
    _gaussian.applyAdjoint(tmp1, tmp2);
    _fft.applyAdjoint(tmp2, out); 
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
