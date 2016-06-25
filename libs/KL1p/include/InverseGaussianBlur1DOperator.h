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

#ifndef KL1P_INVERSEGAUSSIANBLUR1DOPERATOR_H
#define KL1P_INVERSEGAUSSIANBLUR1DOPERATOR_H

#include "Operator.h"
#include "Fourier1DOperator.h"
#include "InverseFourier1DOperator.h"
#include "InverseGaussian1DDiagonalOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseGaussianBlur1DOperator : public TOperator<T, T>
{
public:

    TInverseGaussianBlur1DOperator(klab::UInt32 n);
    TInverseGaussianBlur1DOperator(klab::UInt32 n, const T& gamma);
    TInverseGaussianBlur1DOperator(klab::UInt32 n, const T& gamma, const T& sigma);
    TInverseGaussianBlur1DOperator(klab::UInt32 n, const T& gamma, const T& sigma, klab::Int32 c);
    TInverseGaussianBlur1DOperator(const TInverseGaussianBlur1DOperator<T>& op);
    virtual ~TInverseGaussianBlur1DOperator();    

    T                       gamma() const;
    T                       sigma() const;
    klab::Int32             c() const;

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TInverseGaussianBlur1DOperator();
    TInverseGaussianBlur1DOperator<T>& operator=(const TInverseGaussianBlur1DOperator<T>& op);


private:

    TFourier1DOperator<std::complex<T> >                    _fft;
    TInverseFourier1DOperator<std::complex<T> >             _ifft;
    TInverseGaussian1DDiagonalOperator<std::complex<T> >    _gaussian;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseGaussianBlur1DOperator<std::complex<T> > : public TOperator<std::complex<T>, std::complex<T> >
{
public:

    TInverseGaussianBlur1DOperator(klab::UInt32 n);
    TInverseGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& gamma);
    TInverseGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& gamma, const std::complex<T>& sigma);
    TInverseGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& gamma, const std::complex<T>& sigma, klab::Int32 c);
    TInverseGaussianBlur1DOperator(const TInverseGaussianBlur1DOperator<std::complex<T> >& op);
    virtual ~TInverseGaussianBlur1DOperator();    

    std::complex<T>         gamma() const;
    std::complex<T>         sigma() const;
    klab::Int32             c() const;

    virtual void            apply(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out);
    virtual void            applyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out);


private:

    TInverseGaussianBlur1DOperator();
    TInverseGaussianBlur1DOperator<std::complex<T> >& operator=(const TInverseGaussianBlur1DOperator<std::complex<T> >& op);


private:

    TFourier1DOperator<std::complex<T> >                    _fft;
    TInverseFourier1DOperator<std::complex<T> >             _ifft;
    TInverseGaussian1DDiagonalOperator<std::complex<T> >    _gaussian;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<T>::TInverseGaussianBlur1DOperator(klab::UInt32 n) : TOperator<T, T>(n),
_fft(n, true), _ifft(n, true), _gaussian(n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<T>::TInverseGaussianBlur1DOperator(klab::UInt32 n, const T& gamma) : TOperator<T, T>(n),
_fft(n, true), _ifft(n, true), _gaussian(n, gamma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<T>::TInverseGaussianBlur1DOperator(klab::UInt32 n, const T& gamma, const T& sigma) : TOperator<T, T>(n),
_fft(n, true), _ifft(n, true), _gaussian(n, gamma, sigma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<T>::TInverseGaussianBlur1DOperator(klab::UInt32 n, const T& gamma, const T& sigma, klab::Int32 c) : TOperator<T, T>(n),
_fft(n, true), _ifft(n, true), _gaussian(n, gamma, sigma, c)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<T>::TInverseGaussianBlur1DOperator(const TInverseGaussianBlur1DOperator<T>& op) : TOperator<T, T>(op),
_fft(op._fft), _ifft(op._ifft), _gaussian(op._gaussian)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<T>::~TInverseGaussianBlur1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TInverseGaussianBlur1DOperator<T>::gamma() const
{
    return _gaussian.gamma().real();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TInverseGaussianBlur1DOperator<T>::sigma() const
{
    return _gaussian.sigma().real();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TInverseGaussianBlur1DOperator<T>::c() const
{
    return _gaussian.c();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseGaussianBlur1DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
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
inline void TInverseGaussianBlur1DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
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
inline TInverseGaussianBlur1DOperator<std::complex<T> >::TInverseGaussianBlur1DOperator(klab::UInt32 n) : TOperator<std::complex<T>, std::complex<T> >(n),
_fft(n, true), _ifft(n, true), _gaussian(n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<std::complex<T> >::TInverseGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& gamma) : TOperator<std::complex<T>, std::complex<T> >(n),
_fft(n, true), _ifft(n, true), _gaussian(n, gamma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<std::complex<T> >::TInverseGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& gamma, const std::complex<T>& sigma) : TOperator<std::complex<T>, std::complex<T> >(n),
_fft(n, true), _ifft(n, true), _gaussian(n, gamma, sigma)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<std::complex<T> >::TInverseGaussianBlur1DOperator(klab::UInt32 n, const std::complex<T>& gamma, const std::complex<T>& sigma, klab::Int32 c) : TOperator<std::complex<T>, std::complex<T> >(n),
_fft(n, true), _ifft(n, true), _gaussian(n, gamma, sigma, c)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<std::complex<T> >::TInverseGaussianBlur1DOperator(const TInverseGaussianBlur1DOperator<std::complex<T> >& op) : TOperator<std::complex<T>, std::complex<T> >(op),
_fft(op._fft), _ifft(op._ifft), _gaussian(op._gaussian)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseGaussianBlur1DOperator<std::complex<T> >::~TInverseGaussianBlur1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TInverseGaussianBlur1DOperator<std::complex<T> >::gamma() const
{
    return _gaussian.gamma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TInverseGaussianBlur1DOperator<std::complex<T> >::sigma() const
{
    return _gaussian.sigma();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TInverseGaussianBlur1DOperator<std::complex<T> >::c() const
{
    return _gaussian.c();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseGaussianBlur1DOperator<std::complex<T> >::apply(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out)
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
inline void TInverseGaussianBlur1DOperator<std::complex<T> >::applyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out)
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
