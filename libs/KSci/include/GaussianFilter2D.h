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

#ifndef KLAB_GAUSSIANFILTER2D_H
#define KLAB_GAUSSIANFILTER2D_H

#include "SignalFilter2D.h"
#include "GaussUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGaussianFilter2D : public TSignalFilter2D<T, TGaussianFilter2D<T> >
{
public:

    TGaussianFilter2D(klab::UInt32 m, klab::UInt32 n);
    TGaussianFilter2D(klab::UInt32 m, klab::UInt32 n, const T& sigma);
    TGaussianFilter2D(klab::UInt32 m, klab::UInt32 n, const T& sigma, klab::Int32 ic, klab::Int32 jc);
    TGaussianFilter2D(const TGaussianFilter2D<T>& filter);
    virtual ~TGaussianFilter2D();

    TGaussianFilter2D<T>&   operator=(const TGaussianFilter2D<T>& filter);

    klab::UInt32            m() const;
    klab::UInt32            n() const;
    const T&                sigma() const;
    klab::Int32             ic() const;
    klab::Int32             jc() const;

    void                    apply(arma::Mat<T>& signal);                        
    void                    apply(const arma::Mat<T>& in, arma::Mat<T>& out);  


private:

    T                       _sigma;
    T                       _variance;
    klab::Int32             _ic;
    klab::Int32             _jc;

    arma::Mat<T>            _coefficients;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianFilter2D<T>::TGaussianFilter2D(klab::UInt32 m, klab::UInt32 n) : TSignalFilter2D<T, TGaussianFilter2D<T> >(),
_sigma(klab::TTypeInfo<T>::UNIT), _ic(m>>1), _jc(n>>1),
_coefficients()
{
    klab::ComputeGaussFunction(m, n, _sigma, _ic, _jc, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianFilter2D<T>::TGaussianFilter2D(klab::UInt32 m, klab::UInt32 n, const T& sigma) : TSignalFilter2D<T, TGaussianFilter2D<T> >(),
_sigma(sigma), _ic(m>>1), _jc(n>>1),
_coefficients()
{
    klab::ComputeGaussFunction(m, n, _sigma, _ic, _jc, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianFilter2D<T>::TGaussianFilter2D(klab::UInt32 m, klab::UInt32 n, const T& sigma, klab::Int32 ic, klab::Int32 jc) : TSignalFilter2D<T, TGaussianFilter2D<T> >(),
_sigma(sigma), _ic(ic), _jc(jc),
_coefficients()
{
    klab::ComputeGaussFunction(m, n, _sigma, _ic, _jc, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianFilter2D<T>::TGaussianFilter2D(const TGaussianFilter2D<T>& filter) : TSignalFilter2D<T, TGaussianFilter2D<T> >(),
_sigma(filter._sigma), _ic(filter._ic), _jc(filter._jc),
_coefficients(filter._coefficients)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianFilter2D<T>::~TGaussianFilter2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussianFilter2D<T>& TGaussianFilter2D<T>::operator=(const TGaussianFilter2D<T>& filter)
{
    if(this != &filter)
    {
        TSignalFilter2D<T, TGaussianFilter2D<T> >::operator=(filter);

        _sigma = filter._sigma;
        _ic    = filter._ic;
        _jc    = filter._jc;

        _coefficients = filter._coefficients;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGaussianFilter2D<T>::m() const
{
    return static_cast<klab::UInt32>(_coefficients.n_rows);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGaussianFilter2D<T>::n() const
{
    return static_cast<klab::UInt32>(_coefficients.n_cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TGaussianFilter2D<T>::sigma() const
{
    return _sigma;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussianFilter2D<T>::ic() const
{
    return _ic;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussianFilter2D<T>::jc() const
{
    return _jc;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TGaussianFilter2D<T>::apply(arma::Mat<T>& signal)
{
    klab::UInt32 ms = signal.n_rows;
    klab::UInt32 ns = signal.n_cols;

    if(ms>0 && ns>0)
    {
        if(this->m()>0 && this->n())
        {
            klab::UInt32 minM = klab::Min(ms, this->m());
            klab::UInt32 minN = klab::Min(ns, this->n());

            for(klab::UInt32 i=0; i<minM; ++i)
            {
                for(klab::UInt32 j=0; j<minN; ++j)
                    signal(i, j) *= _coefficients(i, j);

                for(klab::UInt32 j=minN; j<ns; ++j)
                    signal(i, j) = klab::TTypeInfo<T>::ZERO;
            }

            for(klab::UInt32 i=minM; i<ms; ++i)
            {
                for(klab::UInt32 j=0; j<ns; ++j)
                    signal(i, j) = klab::TTypeInfo<T>::ZERO;
            }
        }
        else
        {
            signal.fill(klab::TTypeInfo<T>::ZERO);
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TGaussianFilter2D<T>::apply(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    out = in;
    this->apply(out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
