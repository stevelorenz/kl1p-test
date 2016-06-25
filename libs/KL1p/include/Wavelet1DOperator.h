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

#ifndef KL1P_WAVELET1DOPERATOR_H
#define KL1P_WAVELET1DOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter=klab::TDelegateWaveletFilter<T> >
class TWavelet1DOperator : public TOperator<T, T>
{
public:

    TWavelet1DOperator(klab::UInt32 n);
    TWavelet1DOperator(klab::UInt32 n, const TFilter& filter);
    TWavelet1DOperator(const TWavelet1DOperator<T, TFilter>& op);
    virtual ~TWavelet1DOperator();    

    const TFilter&          filter() const;
    TFilter&                filter();

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TWavelet1DOperator();
    TWavelet1DOperator<T, TFilter>&     operator=(const TWavelet1DOperator<T, TFilter>& op);


private:

    klab::TFWT1D<T, TFilter>    _fwt;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
class TWavelet1DOperatorSpecialisation
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, TFilter>& fwt); 


private:

    TWavelet1DOperatorSpecialisation();
    TWavelet1DOperatorSpecialisation(const TWavelet1DOperatorSpecialisation<T, TFilter>& spec);
    TWavelet1DOperatorSpecialisation<T, TFilter>&   operator=(const TWavelet1DOperatorSpecialisation<T, TFilter>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::THaarWaveletFilter<T> >& fwt); 


private:

    TWavelet1DOperatorSpecialisation();
    TWavelet1DOperatorSpecialisation(const TWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >& spec);
    TWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >&  operator=(const TWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 2> >& fwt); 


private:

    TWavelet1DOperatorSpecialisation();
    TWavelet1DOperatorSpecialisation(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >& spec);
    TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >&     operator=(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 4> >& fwt); 


private:

    TWavelet1DOperatorSpecialisation();
    TWavelet1DOperatorSpecialisation(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >& spec);
    TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >&     operator=(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 6> >& fwt); 


private:

    TWavelet1DOperatorSpecialisation();
    TWavelet1DOperatorSpecialisation(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >& spec);
    TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >&     operator=(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 8> >& fwt); 


private:

    TWavelet1DOperatorSpecialisation();
    TWavelet1DOperatorSpecialisation(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >& spec);
    TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >&     operator=(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 10> >& fwt); 


private:

    TWavelet1DOperatorSpecialisation();
    TWavelet1DOperatorSpecialisation(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >& spec);
    TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >&    operator=(const TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TWavelet1DOperator<T, TFilter>::TWavelet1DOperator(klab::UInt32 n) : TOperator<T, T>(n),
_fwt()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TWavelet1DOperator<T, TFilter>::TWavelet1DOperator(klab::UInt32 n, const TFilter& filter) : TOperator<T, T>(n),
_fwt(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TWavelet1DOperator<T, TFilter>::TWavelet1DOperator(const TWavelet1DOperator<T, TFilter>& op) : TOperator<T, T>(op),
_fwt(op._fwt)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TWavelet1DOperator<T, TFilter>::~TWavelet1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const TFilter& TWavelet1DOperator<T, TFilter>::filter() const
{
    return _fwt.filter();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFilter& TWavelet1DOperator<T, TFilter>::filter()
{
    return _fwt.filter();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TWavelet1DOperator<T, TFilter>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    _fwt.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TWavelet1DOperator<T, TFilter>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    TWavelet1DOperatorSpecialisation<T, TFilter>::ApplyAdjoint(in, out, _fwt);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TWavelet1DOperatorSpecialisation<T, TFilter>::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, TFilter>& fwt)
{
    arma::Mat<T> fwtMatrix(in.n_rows, in.n_rows);
    for(klab::UInt32 j=0; j<in.n_rows; ++j)
    {
        arma::Col<T> base(in.n_rows);
        arma::Col<T> col;
        base.fill(0.0);
        base[j] = 1.0;

        fwt.transform(base, col);

        for(klab::UInt32 i=0; i<col.n_rows; ++i)
            fwtMatrix(i, j) = col[i];
    } 

    out = arma::trans(fwtMatrix) * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::THaarWaveletFilter<T> >& fwt)
{
    fwt.invert(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 2> >& fwt)
{
    fwt.invert(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 4> >& fwt)
{
    fwt.invert(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 6> >& fwt)
{
    fwt.invert(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 8> >& fwt)
{
    fwt.invert(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 10> >& fwt)
{
    fwt.invert(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
