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

#ifndef KL1P_INVERSEWAVELET1DOPERATOR_H
#define KL1P_INVERSEWAVELET1DOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter=klab::TDelegateWaveletFilter<T> >
class TInverseWavelet1DOperator : public TOperator<T, T>
{
public:

    TInverseWavelet1DOperator(klab::UInt32 n);
    TInverseWavelet1DOperator(klab::UInt32 n, const TFilter& filter);
    TInverseWavelet1DOperator(const TInverseWavelet1DOperator<T, TFilter>& op);
    virtual ~TInverseWavelet1DOperator();    

    const TFilter&          filter() const;
    TFilter&                filter();

    virtual void            apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void            applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


private:

    TInverseWavelet1DOperator();
    TInverseWavelet1DOperator<T, TFilter>&  operator=(const TInverseWavelet1DOperator<T, TFilter>& op);


private:

    klab::TFWT1D<T, TFilter>    _fwt;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
class TInverseWavelet1DOperatorSpecialisation
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, TFilter>& fwt); 


private:

    TInverseWavelet1DOperatorSpecialisation();
    TInverseWavelet1DOperatorSpecialisation(const TInverseWavelet1DOperatorSpecialisation<T, TFilter>& spec);
    TInverseWavelet1DOperatorSpecialisation<T, TFilter>&   operator=(const TInverseWavelet1DOperatorSpecialisation<T, TFilter>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::THaarWaveletFilter<T> >& fwt); 


private:

    TInverseWavelet1DOperatorSpecialisation();
    TInverseWavelet1DOperatorSpecialisation(const TInverseWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >& spec);
    TInverseWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >&  operator=(const TInverseWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 2> >& fwt); 


private:

    TInverseWavelet1DOperatorSpecialisation();
    TInverseWavelet1DOperatorSpecialisation(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >& spec);
    TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >&     operator=(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 4> >& fwt); 


private:

    TInverseWavelet1DOperatorSpecialisation();
    TInverseWavelet1DOperatorSpecialisation(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >& spec);
    TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >&     operator=(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 6> >& fwt); 


private:

    TInverseWavelet1DOperatorSpecialisation();
    TInverseWavelet1DOperatorSpecialisation(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >& spec);
    TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >&     operator=(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 8> >& fwt); 


private:

    TInverseWavelet1DOperatorSpecialisation();
    TInverseWavelet1DOperatorSpecialisation(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >& spec);
    TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >&     operator=(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >
{
public:

    static void     ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 10> >& fwt); 


private:

    TInverseWavelet1DOperatorSpecialisation();
    TInverseWavelet1DOperatorSpecialisation(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >& spec);
    TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >&    operator=(const TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TInverseWavelet1DOperator<T, TFilter>::TInverseWavelet1DOperator(klab::UInt32 n) : TOperator<T, T>(n),
_fwt()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TInverseWavelet1DOperator<T, TFilter>::TInverseWavelet1DOperator(klab::UInt32 n, const TFilter& filter) : TOperator<T, T>(n),
_fwt(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TInverseWavelet1DOperator<T, TFilter>::TInverseWavelet1DOperator(const TInverseWavelet1DOperator<T, TFilter>& op) : TOperator<T, T>(op),
_fwt(op._fwt)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TInverseWavelet1DOperator<T, TFilter>::~TInverseWavelet1DOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const TFilter& TInverseWavelet1DOperator<T, TFilter>::filter() const
{
    return _fwt.filter();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TFilter& TInverseWavelet1DOperator<T, TFilter>::filter()
{
    return _fwt.filter();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TInverseWavelet1DOperator<T, TFilter>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    _fwt.invert(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TInverseWavelet1DOperator<T, TFilter>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    TInverseWavelet1DOperatorSpecialisation<T, TFilter>::ApplyAdjoint(in, out, _fwt);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TInverseWavelet1DOperatorSpecialisation<T, TFilter>::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, TFilter>& fwt)
{
    arma::Mat<T> fwtMatrix(in.n_rows, in.n_rows);
    for(klab::UInt32 j=0; j<in.n_rows; ++j)
    {
        arma::Col<T> base(in.n_rows);
        arma::Col<T> col;
        base.fill(0.0);
        base[j] = 1.0;

        fwt.invert(base, col);

        for(klab::UInt32 i=0; i<col.n_rows; ++i)
            fwtMatrix(i, j) = col[i];
    } 

    out = arma::trans(fwtMatrix) * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseWavelet1DOperatorSpecialisation<T, klab::THaarWaveletFilter<T> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::THaarWaveletFilter<T> >& fwt)
{
    fwt.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 2> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 2> >& fwt)
{
    fwt.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 4> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 4> >& fwt)
{
    fwt.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 6> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 6> >& fwt)
{
    fwt.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 8> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 8> >& fwt)
{
    fwt.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TInverseWavelet1DOperatorSpecialisation<T, klab::TDaubechiesWaveletFilter<T, 10> >::ApplyAdjoint(const arma::Col<T>& in, arma::Col<T>& out, klab::TFWT1D<T, klab::TDaubechiesWaveletFilter<T, 10> >& fwt)
{
    fwt.transform(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
