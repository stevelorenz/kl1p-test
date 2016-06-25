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

#ifndef KL1P_FOURIER1DOPERATOR_H
#define KL1P_FOURIER1DOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFourier1DOperator : public TOperator<T, T>
{
public:
    
    TFourier1DOperator(klab::UInt32 n);   
    TFourier1DOperator(klab::UInt32 n, bool shift);
    TFourier1DOperator(const TFourier1DOperator<T>& op);
    virtual ~TFourier1DOperator();    

    bool                    isShift() const;

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TFourier1DOperator();   
    TFourier1DOperator<T>&  operator=(const TFourier1DOperator<T>& op);


private:

    klab::TFFT1D<T>         _fft;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFourier1DOperatorSpecialisation
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFFT1D<T>& fft); 


private:

    TFourier1DOperatorSpecialisation();
    TFourier1DOperatorSpecialisation(const TFourier1DOperatorSpecialisation<T>& spec);
    TFourier1DOperatorSpecialisation<T>&    operator=(const TFourier1DOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFourier1DOperatorSpecialisation<std::complex<T> >
{
public:

    static void     ApplyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out, klab::TFFT1D<std::complex<T> >& fft); 


private:

    TFourier1DOperatorSpecialisation();
    TFourier1DOperatorSpecialisation(const TFourier1DOperatorSpecialisation<T>& spec);
    TFourier1DOperatorSpecialisation<T>&    operator=(const TFourier1DOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFourier1DOperator<T>::TFourier1DOperator(klab::UInt32 n) : TOperator<T, T>(n),
_fft()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFourier1DOperator<T>::TFourier1DOperator(klab::UInt32 n, bool shift) : TOperator<T, T>(n),
_fft(shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFourier1DOperator<T>::TFourier1DOperator(const TFourier1DOperator<T>& op) : TOperator<T, T>(op),
_fft(op._fft)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFourier1DOperator<T>::~TFourier1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TFourier1DOperator<T>::isShift() const
{
    return _fft.shift();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFourier1DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    _fft.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFourier1DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    TFourier1DOperatorSpecialisation<T>::ApplyAdjoint(in, out, _fft);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFourier1DOperatorSpecialisation<T>::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFFT1D<T>& fft)
{
    // To optimize.
    arma::Mat<T> fftMatrix(in.n_rows, in.n_rows);
    for(klab::UInt32 j=0; j<in.n_rows; ++j)
    {
        arma::Col<T> base(in.n_rows);
        arma::Col<T> col;
        base.fill(klab::TTypeInfo<T>::ZERO);
        base[j] = klab::TTypeInfo<T>::UNIT;

        fft.transform(base, col);

        for(klab::UInt32 i=0; i<col.n_rows; ++i)
            fftMatrix(i, j) = col[i];
    } 

    out = arma::trans(fftMatrix) * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFourier1DOperatorSpecialisation<std::complex<T> >::ApplyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out, klab::TFFT1D<std::complex<T> >& fft)
{
    fft.invert(in, out);

    // Normalization.
    for(klab::UInt32 i=0; i<out.n_rows; ++i)
        out[i] *= static_cast<T>(out.n_rows);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
