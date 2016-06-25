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

#ifndef KLAB_GAUSSWIENERFILTER1D_H
#define KLAB_GAUSSWIENERFILTER1D_H

#include "SignalFilter1D.h"
#include "GaussUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGaussWienerFilter1D : public TSignalFilter1D<T, TGaussWienerFilter1D<T> >
{
public:

    TGaussWienerFilter1D(klab::UInt32 size);
    TGaussWienerFilter1D(klab::UInt32 size, const T& gamma);
    TGaussWienerFilter1D(klab::UInt32 size, const T& gamma, const T& sigma);
    TGaussWienerFilter1D(klab::UInt32 size, const T& gamma, const T& sigma, klab::Int32 c);
    TGaussWienerFilter1D(const TGaussWienerFilter1D<T>& filter);
    virtual ~TGaussWienerFilter1D();

    TGaussWienerFilter1D<T>&    operator=(const TGaussWienerFilter1D<T>& filter);

    klab::UInt32                size() const;
    const T&                    gamma() const;
    const T&                    sigma() const;
    klab::Int32                 c() const;

    void                        apply(arma::Col<T>& signal);                        
    void                        apply(const arma::Col<T>& in, arma::Col<T>& out);  


private:

    T                           _gamma;
    T                           _sigma;
    T                           _variance;
    klab::Int32                 _c;

    arma::Col<T>                _coefficients;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter1D<T>::TGaussWienerFilter1D(klab::UInt32 size) : TSignalFilter1D<T, TGaussWienerFilter1D<T> >(),
_gamma(klab::TTypeInfo<T>::ZERO), _sigma(klab::TTypeInfo<T>::UNIT), _c(size>>1),
_coefficients()
{
    klab::ComputeGaussWienerFunction(size, _sigma, _c, _gamma, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter1D<T>::TGaussWienerFilter1D(klab::UInt32 size, const T& gamma) : TSignalFilter1D<T, TGaussWienerFilter1D<T> >(),
_gamma(gamma), _sigma(klab::TTypeInfo<T>::UNIT), _c(size>>1),
_coefficients()
{
    klab::ComputeGaussWienerFunction(size, _sigma, _c, _gamma, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter1D<T>::TGaussWienerFilter1D(klab::UInt32 size, const T& gamma, const T& sigma) : TSignalFilter1D<T, TGaussWienerFilter1D<T> >(),
_gamma(gamma), _sigma(sigma), _c(size>>1),
_coefficients()
{
    klab::ComputeGaussWienerFunction(size, _sigma, _c, _gamma, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter1D<T>::TGaussWienerFilter1D(klab::UInt32 size, const T& gamma, const T& sigma, klab::Int32 c) : TSignalFilter1D<T, TGaussWienerFilter1D<T> >(),
_gamma(gamma), _sigma(sigma), _c(c),
_coefficients()
{
    klab::ComputeGaussWienerFunction(size, _sigma, _c, _gamma, _coefficients);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter1D<T>::TGaussWienerFilter1D(const TGaussWienerFilter1D<T>& filter) : TSignalFilter1D<T, TGaussWienerFilter1D<T> >(),
_gamma(filter._gamma), _sigma(filter._sigma), _c(filter._c),
_coefficients(filter._coefficients)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter1D<T>::~TGaussWienerFilter1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TGaussWienerFilter1D<T>& TGaussWienerFilter1D<T>::operator=(const TGaussWienerFilter1D<T>& filter)
{
    if(this != &filter)
    {
        TSignalFilter1D<T, TGaussWienerFilter1D<T> >::operator=(filter);

        _gamma = filter._gamma;
        _sigma = filter._sigma;
        _c     = filter._c;

        _coefficients = filter._coefficients;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TGaussWienerFilter1D<T>::size() const
{
    return static_cast<klab::UInt32>(_coefficients.n_rows);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TGaussWienerFilter1D<T>::gamma() const
{
    return _gamma;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TGaussWienerFilter1D<T>::sigma() const
{
    return _sigma;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::Int32 TGaussWienerFilter1D<T>::c() const
{
    return _c;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TGaussWienerFilter1D<T>::apply(arma::Col<T>& signal)
{
    klab::UInt32 n = signal.n_rows;

    if(n > 0)
    {
        if(this->size() > 0)
        {
            klab::UInt32 minSize = klab::Min(n, this->size());

            for(klab::UInt32 i=0; i<minSize; ++i)
                signal[i] *= _coefficients[i];

            for(klab::UInt32 i=minSize; i<n; ++i)
                signal[i] = klab::TTypeInfo<T>::ZERO;
        }
        else
        {
            signal.fill(klab::TTypeInfo<T>::ZERO);
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TGaussWienerFilter1D<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    out = in;
    this->apply(out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
