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

#ifndef KLAB_GAUSSWIENERFILTER2D_H
#define KLAB_GAUSSWIENERFILTER2D_H

#include "SignalFilter2D.h"
#include "GaussUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGaussWienerFilter2D : public TSignalFilter2D<T, TGaussWienerFilter2D<T> >
{
public:

    TGaussWienerFilter2D(klab::UInt32 m, klab::UInt32 n);
    TGaussWienerFilter2D(klab::UInt32 m, klab::UInt32 n, const T& gamma);
    TGaussWienerFilter2D(klab::UInt32 m, klab::UInt32 n, const T& gamma, const T& sigma);
    TGaussWienerFilter2D(klab::UInt32 m, klab::UInt32 n, const T& gamma, const T& sigma, klab::Int32 ic, klab::Int32 jc);
    TGaussWienerFilter2D(const TGaussWienerFilter2D<T>& filter);
    virtual ~TGaussWienerFilter2D();

    TGaussWienerFilter2D<T>&    operator=(const TGaussWienerFilter2D<T>& filter);

    klab::UInt32                m() const;
    klab::UInt32                n() const;
    const T&                    gamma() const;
    const T&                    sigma() const;
    klab::Int32                 ic() const;
    klab::Int32                 jc() const;

    void                        apply(arma::Mat<T>& signal);                        
    void                        apply(const arma::Mat<T>& in, arma::Mat<T>& out);  


private:

    T                           _gamma;
    T                           _sigma;
    T                           _variance;
    klab::Int32                 _ic;
    klab::Int32                 _jc;

    arma::Mat<T>                _coefficients;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter2D<T>::TGaussWienerFilter2D(klab::UInt32 m, klab::UInt32 n) : TSignalFilter2D<T, TGaussWienerFilter2D<T> >(),
_gamma(klab::TTypeInfo<T>::ZERO), _sigma(klab::TTypeInfo<T>::UNIT), _ic(m>>1), _jc(n>>1),
_coefficients()
{
    klab::ComputeGaussWienerFunction(m, n, _sigma, _ic, _jc, _gamma, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter2D<T>::TGaussWienerFilter2D(klab::UInt32 m, klab::UInt32 n, const T& gamma) : TSignalFilter2D<T, TGaussWienerFilter2D<T> >(),
_gamma(gamma), _sigma(klab::TTypeInfo<T>::UNIT), _ic(m>>1), _jc(n>>1),
_coefficients()
{
    klab::ComputeGaussWienerFunction(m, n, _sigma, _ic, _jc, _gamma, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter2D<T>::TGaussWienerFilter2D(klab::UInt32 m, klab::UInt32 n, const T& gamma, const T& sigma) : TSignalFilter2D<T, TGaussWienerFilter2D<T> >(),
_gamma(gamma), _sigma(sigma), _ic(m>>1), _jc(n>>1),
_coefficients()
{
    klab::ComputeGaussWienerFunction(m, n, _sigma, _ic, _jc, _gamma, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter2D<T>::TGaussWienerFilter2D(klab::UInt32 m, klab::UInt32 n, const T& gamma, const T& sigma, klab::Int32 ic, klab::Int32 jc) : TSignalFilter2D<T, TGaussWienerFilter2D<T> >(),
_gamma(gamma), _sigma(sigma), _ic(ic), _jc(jc),
_coefficients()
{
    klab::ComputeGaussWienerFunction(m, n, _sigma, _ic, _jc, _gamma, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter2D<T>::TGaussWienerFilter2D(const TGaussWienerFilter2D<T>& filter) : TSignalFilter2D<T, TGaussWienerFilter2D<T> >(),
_gamma(filter._gamma), _sigma(filter._sigma), _ic(filter._ic), _jc(filter._jc),
_coefficients(filter._coefficients)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter2D<T>::~TGaussWienerFilter2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter2D<T>& TGaussWienerFilter2D<T>::operator=(const TGaussWienerFilter2D<T>& filter)
{
    if(this != &filter)
    {
        TSignalFilter2D<T, TGaussWienerFilter2D<T> >::operator=(filter);

        _gamma = filter._gamma;
        _sigma = filter._sigma;
        _ic    = filter._ic;
        _jc    = filter._jc;

        _coefficients = filter._coefficients;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGaussWienerFilter2D<T>::m() const
{
    return static_cast<klab::UInt32>(_coefficients.n_rows);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGaussWienerFilter2D<T>::n() const
{
    return static_cast<klab::UInt32>(_coefficients.n_cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TGaussWienerFilter2D<T>::gamma() const
{
    return _gamma;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TGaussWienerFilter2D<T>::sigma() const
{
    return _sigma;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussWienerFilter2D<T>::ic() const
{
    return _ic;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussWienerFilter2D<T>::jc() const
{
    return _jc;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TGaussWienerFilter2D<T>::apply(arma::Mat<T>& signal)
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
inline void TGaussWienerFilter2D<T>::apply(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    out = in;
    this->apply(out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
