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

#ifndef KL1P_GAUSSIANBLUR1DOPERATOR_H
#define KL1P_GAUSSIANBLUR1DOPERATOR_H

#include "Operator.h"
#include "Fourier1DOperator.h"
#include "InverseFourier1DOperator.h"
#include "Gaussian1DDiagonalOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGaussianBlur1DOperator : public TOperator<T, T>
{
public:

    TGaussianBlur1DOperator(klab::UInt32 n);
    TGaussianBlur1DOperator(klab::UInt32 n, const T& sigma);
    TGaussianBlur1DOperator(klab::UInt32 n, const T& sigma, klab::Int32 c);
    TGaussianBlur1DOperator(const TGaussianBlur1DOperator<T>& op);
    virtual ~TGaussianBlur1DOperator();    

    T                       sigma() const;
    klab::Int32             c() const;

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TGaussianBlur1DOperator();
    TGaussianBlur1DOperator<T>& operator=(const TGaussianBlur1DOperator<T>& op);


private:

    TFourier1DOperator<std::complex<T> >            _fft;
    TInverseFourier1DOperator<std::complex<T> >     _ifft;
    TGaussian1DDiagonalOperator<std::complex<T> >   _gaussian;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGaussianBlur1DOperator<std::complex<T> > : public TOperator<std::complex<T>, std::complex<T> >
{
public:

    TGaussianBlur1DOperator(klab::UInt32 n);
    TGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& sigma);
    TGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& sigma, klab::Int32 c);
    TGaussianBlur1DOperator(const TGaussianBlur1DOperator<std::complex<T> >& op);
    virtual ~TGaussianBlur1DOperator();    

    klab::UInt32            size() const;
    std::complex<T>         sigma() const;
    klab::Int32             c() const;

    virtual void            apply(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out);
    virtual void            applyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out);


private:

    TGaussianBlur1DOperator();
    TGaussianBlur1DOperator<std::complex<T> >& operator=(const TGaussianBlur1DOperator<std::complex<T> >& op);


private:

    TFourier1DOperator<std::complex<T> >            _fft;
    TInverseFourier1DOperator<std::complex<T> >     _ifft;
    TGaussian1DDiagonalOperator<std::complex<T> >   _gaussian;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianBlur1DOperator<T>::TGaussianBlur1DOperator(klab::UInt32 n) : TOperator<T, T>(n),
_fft(n, true), _ifft(n, true), _gaussian(n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianBlur1DOperator<T>::TGaussianBlur1DOperator(klab::UInt32 n, const T& sigma) : TOperator<T, T>(n),
_fft(n, true), _ifft(n, true), _gaussian(n, sigma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianBlur1DOperator<T>::TGaussianBlur1DOperator(klab::UInt32 n, const T& sigma, klab::Int32 c) : TOperator<T, T>(n),
_fft(n, true), _ifft(n, true), _gaussian(n, sigma, c)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianBlur1DOperator<T>::TGaussianBlur1DOperator(const TGaussianBlur1DOperator<T>& op) : TOperator<T, T>(op),
_fft(op._fft), _ifft(op._ifft), _gaussian(op._gaussian)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianBlur1DOperator<T>::~TGaussianBlur1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TGaussianBlur1DOperator<T>::sigma() const
{
    return _gaussian.sigma().real();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussianBlur1DOperator<T>::c() const
{
    return _gaussian.c();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TGaussianBlur1DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

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
inline void TGaussianBlur1DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

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
inline TGaussianBlur1DOperator<std::complex<T> >::TGaussianBlur1DOperator(klab::UInt32 n) : TOperator<std::complex<T>, std::complex<T> >(n),
_fft(n, true), _ifft(n, true), _gaussian(n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianBlur1DOperator<std::complex<T> >::TGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& sigma) : TOperator<std::complex<T>, std::complex<T> >(n),
_fft(n, true), _ifft(n, true), _gaussian(n, sigma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianBlur1DOperator<std::complex<T> >::TGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& sigma, klab::Int32 c) : TOperator<std::complex<T>, std::complex<T> >(n),
_fft(n, true), _ifft(n, true), _gaussian(n, sigma, c)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianBlur1DOperator<std::complex<T> >::TGaussianBlur1DOperator(const TGaussianBlur1DOperator<std::complex<T> >& op) : TOperator<std::complex<T>, std::complex<T> >(op),
_fft(op._fft), _ifft(op._ifft), _gaussian(op._gaussian)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianBlur1DOperator<std::complex<T> >::~TGaussianBlur1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGaussianBlur1DOperator<std::complex<T> >::size() const
{
    return _gaussian.size();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TGaussianBlur1DOperator<std::complex<T> >::sigma() const
{
    return _gaussian.sigma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussianBlur1DOperator<std::complex<T> >::c() const
{
    return _gaussian.c();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TGaussianBlur1DOperator<std::complex<T> >::apply(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out)
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
inline void TGaussianBlur1DOperator<std::complex<T> >::applyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out)
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
