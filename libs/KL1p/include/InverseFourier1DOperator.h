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

#ifndef KL1P_INVERSEFOURIER1DOPERATOR_H
#define KL1P_INVERSEFOURIER1DOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseFourier1DOperator : public TOperator<T, T>
{
public:
    
    TInverseFourier1DOperator(klab::UInt32 n);
    TInverseFourier1DOperator(klab::UInt32 n, bool shift);
    TInverseFourier1DOperator(const TInverseFourier1DOperator<T>& op);
    virtual ~TInverseFourier1DOperator();    

    bool                    isShift() const;

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TInverseFourier1DOperator();
    TInverseFourier1DOperator<T>&   operator=(const TInverseFourier1DOperator<T>& op);


private:

    klab::TFFT1D<T>         _fft;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseFourier1DOperatorSpecialisation
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFFT1D<T>& fft); 


private:

    TInverseFourier1DOperatorSpecialisation();
    TInverseFourier1DOperatorSpecialisation(const TInverseFourier1DOperatorSpecialisation<T>& spec);
    TInverseFourier1DOperatorSpecialisation<T>&     operator=(const TInverseFourier1DOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseFourier1DOperatorSpecialisation<std::complex<T> >
{
public:

    static void     ApplyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out, klab::TFFT1D<std::complex<T> >& fft); 


private:

    TInverseFourier1DOperatorSpecialisation();
    TInverseFourier1DOperatorSpecialisation(const TInverseFourier1DOperatorSpecialisation<T>& spec);
    TInverseFourier1DOperatorSpecialisation<T>&     operator=(const TInverseFourier1DOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseFourier1DOperator<T>::TInverseFourier1DOperator(klab::UInt32 n) : TOperator<T, T>(n),
_fft()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseFourier1DOperator<T>::TInverseFourier1DOperator(klab::UInt32 n, bool shift) : TOperator<T, T>(n),
_fft(shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseFourier1DOperator<T>::TInverseFourier1DOperator(const TInverseFourier1DOperator<T>& op) : TOperator<T, T>(op),
_fft(op._fft)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TInverseFourier1DOperator<T>::~TInverseFourier1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TInverseFourier1DOperator<T>::isShift() const
{
    return _fft.shift();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseFourier1DOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    _fft.invert(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseFourier1DOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    TInverseFourier1DOperatorSpecialisation<T>::ApplyAdjoint(in, out, _fft);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseFourier1DOperatorSpecialisation<T>::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFFT1D<T>& fft)
{
    fft.transform(in, out);

    if(out.n_rows > 0)
    {
        klab::UInt32 n     = out.n_rows;
        klab::UInt32 halfN = n / 2;

        T invN     = klab::TTypeInfo<T>::UNIT / static_cast<T>(n);
        T invHalfN = static_cast<T>(2) * invN;

        out[0] *= invN;
        for(klab::UInt32 i=1; i<n; ++i)
            out[i] *= invHalfN;

        if(n%2 == 0)
            out[halfN] /= static_cast<T>(2);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseFourier1DOperatorSpecialisation<std::complex<T> >::ApplyAdjoint(const arma::Col<std::complex<T> >& in, arma::Col<std::complex<T> >& out, klab::TFFT1D<std::complex<T> >& fft)
{
    fft.transform(in, out);

    // Normalization.
    if(out.n_rows > 0)
    {
        T invN = klab::TTypeInfo<T>::UNIT / static_cast<T>(out.n_rows);
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
            out[i] *= invN;
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
