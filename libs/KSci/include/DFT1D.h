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

#ifndef KLAB_DFT1D_H
#define KLAB_DFT1D_H

#include "TrigoUtil.h"
#include "ArmadilloUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KFourierException, KException)
KLAB_DECLARE_EXCEPTION(KDFTException, KFourierException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDFT1D
{
public:

    TDFT1D();
    TDFT1D(bool shift);
    TDFT1D(const TDFT1D<T>& dft);
    virtual ~TDFT1D();

    TDFT1D<T>&  operator=(const TDFT1D<T>& dft);

    void        setShift(bool shift);
    bool        shift() const;

    void        transform(const arma::Col<T>& in, arma::Col<T>& out);
    void        invert(const arma::Col<T>& in, arma::Col<T>& out);

    void        transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);  // Compute DFT on every columns of the matrix.    
    void        invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);     // Compute inverse DFT on every columns of the matrix.


private:

    bool        _shift;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDFT1DSpecialisation
{
public:

    static void     Perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse, bool shift);

private:

    TDFT1DSpecialisation();
    TDFT1DSpecialisation(const TDFT1DSpecialisation<T>& dft);
    TDFT1DSpecialisation<T>&    operator=(const TDFT1DSpecialisation<T>& dft);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDFT1DSpecialisation<std::complex<T> >
{
public:

    static void     Perform(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse, bool shift);

private:

    TDFT1DSpecialisation();
    TDFT1DSpecialisation(const TDFT1DSpecialisation<T>& dft);
    TDFT1DSpecialisation<T>&    operator=(const TDFT1DSpecialisation<T>& dft);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT1D<T>::TDFT1D() : 
_shift(false)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT1D<T>::TDFT1D(bool shift) : 
_shift(shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT1D<T>::TDFT1D(const TDFT1D<T>& dft) : 
_shift(dft._shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT1D<T>::~TDFT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDFT1D<T>& TDFT1D<T>::operator=(const TDFT1D<T>& dft)
{
    if(this != &dft)
    {
        _shift = dft._shift;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT1D<T>::setShift(bool shift)
{
    _shift = shift;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TDFT1D<T>::shift() const
{
    return _shift;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT1D<T>::transform(const arma::Col<T>& in, arma::Col<T>& out)
{
    TDFT1DSpecialisation<T>::Perform(in, out, false, _shift);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT1D<T>::invert(const arma::Col<T>& in, arma::Col<T>& out)
{
    TDFT1DSpecialisation<T>::Perform(in, out, true, _shift);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT1D<T>::transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    TDFT1DSpecialisation<T>::Perform(in, out, false, _shift);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT1D<T>::invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    TDFT1DSpecialisation<T>::Perform(in, out, true, _shift);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT1DSpecialisation<T>::Perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse, bool shift)
{
    klab::UInt32     m = in.n_rows;
    klab::UInt32     n = in.n_cols;
    klab::UInt32 halfM = m / 2;

    if(out.n_rows!=m || out.n_cols!=n)  
        out.set_size(m, n);

    out.fill(klab::TTypeInfo<T>::ZERO);

    if(m>0 && n>0)
    {
        if(inverse == false)
        {
            arma::Mat<std::complex<T> > cIn(in.n_rows, in.n_cols);
            arma::Mat<std::complex<T> > cOut;

            for(klab::UInt32 i=0; i<m; ++i)
            {
                for(klab::UInt32 j=0; j<n; ++j)
                    cIn(i, j) = std::complex<T>(in(i, j), 0.0);
            }

            TDFT1DSpecialisation<std::complex<T> >::Perform(cIn, cOut, false, false);
            
            for(klab::UInt32 j=0; j<n; ++j)
            {
                for(klab::UInt32 i=0; i<=halfM; ++i)
                    out(i, j) = cOut(i, j).real();

                for(klab::UInt32 i=halfM+1; i<m; ++i)
                    out(i, j) = cOut(i-halfM, j).imag();
            }
        }
        else
        {
            arma::Mat<std::complex<T> > cIn(in.n_rows, in.n_cols);
            arma::Mat<std::complex<T> > cOut;

            for(klab::UInt32 j=0; j<n; ++j)
            {
                cIn(0, j) = std::complex<T>(in(0, j), 0.0);
                for(klab::UInt32 i=1; i<=halfM; ++i)
                {                    
                    T real      = in(i, j);
                    T imaginary = 0.0;
                    if(i+halfM < m)
                        imaginary = in(i+halfM, j);

                    cIn(i, j)   = std::complex<T>(real, imaginary);
                    cIn(m-i, j) = std::complex<T>(real, -imaginary);
                }
            }

            TDFT1DSpecialisation<std::complex<T> >::Perform(cIn, cOut, true, false);

            for(klab::UInt32 i=0; i<m; ++i)
            {
                for(klab::UInt32 j=0; j<n; ++j)
                    out(i, j) = cOut(i, j).real();
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDFT1DSpecialisation<std::complex<T> >::Perform(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse, bool shift)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;

    if(out.n_rows!=m || out.n_cols!=n)  
        out.set_size(m, n);

    out.fill(klab::TTypeInfo<T>::ZERO);
    
    T invM               = klab::TTypeInfo<T>::UNIT / static_cast<T>(m);
    klab::UInt32 halfM   = m / 2;
    klab::UInt32 mEven   = m % 2;
    T invM2Pi            = T(inverse?2:-2) * T(klab::PI) * invM;

    for(klab::UInt32 j=0; j<n; ++j)
    {
        for(klab::UInt32 x=0; x<m; ++x)
        {
            klab::UInt32 xi = x;
            if(shift && inverse==false)
                xi = (x<(halfM+mEven)) ? x+halfM : x-halfM-mEven; 

            T w2pi = invM2Pi * x;                   

            for(klab::UInt32 k=0; k<m; ++k)
            {
                klab::UInt32 ki = k;
                if(shift && inverse)
                    ki = (k<(halfM+mEven)) ? k+halfM : k-halfM-mEven; 

                T a     = w2pi * k; 
                T cosA  = klab::Cos(a);
                T sinA  = klab::Sin(a);
                
                std::complex<T> inValue(in(ki, j));
                if(klab::Equals(inValue.imag(), klab::TTypeInfo<T>::ZERO))  out(xi, j) += std::complex<T>(inValue.real()*cosA, inValue.real()*sinA);
                else                                                        out(xi, j) += std::complex<T>(inValue.real()*cosA - inValue.imag()*sinA, inValue.real()*sinA + inValue.imag()*cosA);
            }

            if(inverse)
                out(xi, j) *= invM;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
