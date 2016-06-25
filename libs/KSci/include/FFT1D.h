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

#ifndef KLAB_FFT1D_H
#define KLAB_FFT1D_H

#include "DFT1D.h"
#include "FFTWUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KFFTException, KFourierException)
KLAB_DECLARE_EXCEPTION(KRadix2BadSizeFFTException, KFFTException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFFT1D
{
public:

    TFFT1D();
    TFFT1D(bool shift);
    TFFT1D(const TFFT1D<T>& fft);
    virtual ~TFFT1D();

    TFFT1D<T>&  operator=(const TFFT1D<T>& fft);

    void        setShift(bool shift);
    bool        shift() const;

    void        transform(const arma::Col<T>& in, arma::Col<T>& out);
    void        invert(const arma::Col<T>& in, arma::Col<T>& out);

    void        transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);  // Compute FFT on every columns of the matrix.    
    void        invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);     // Compute inverse FFT on every columns of the matrix.


private:

    bool        _shift;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFFT1DSpecialisation
{
public:

    static void     Perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse, bool shift);
    static void     PerformRadix2(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse, bool shift);


private:

    TFFT1DSpecialisation();
    TFFT1DSpecialisation(const TFFT1DSpecialisation<T>& fft);
    TFFT1DSpecialisation<T>&    operator=(const TFFT1DSpecialisation<T>& fft);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFFT1DSpecialisation<std::complex<T> >
{
public:

    static void     Perform(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse, bool shift);
    static void     PerformRadix2(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse, bool shift);


protected:

    static void     ReorderRadix2(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse, bool shift);
    static void     ShiftColumns(arma::Mat<std::complex<T> >& mat);


private:

    TFFT1DSpecialisation();
    TFFT1DSpecialisation(const TFFT1DSpecialisation<T>& fft);
    TFFT1DSpecialisation<T>&    operator=(const TFFT1DSpecialisation<T>& fft);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFFT1D<T>::TFFT1D() : 
_shift(false)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFFT1D<T>::TFFT1D(bool shift) : 
_shift(shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFFT1D<T>::TFFT1D(const TFFT1D<T>& fft) : 
_shift(fft._shift)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFFT1D<T>::~TFFT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFFT1D<T>& TFFT1D<T>::operator=(const TFFT1D<T>& fft)
{
    if(this != &fft)
    {
        _shift = fft._shift;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1D<T>::setShift(bool shift)
{
    _shift = shift;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TFFT1D<T>::shift() const
{
    return _shift;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1D<T>::transform(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->transformMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1D<T>::invert(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->invertMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1D<T>::transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    if(ComputeFFTW1D_MatrixColumns(in, out, false, _shift) == false)
        TFFT1DSpecialisation<T>::Perform(in, out, false, _shift); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1D<T>::invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    if(ComputeFFTW1D_MatrixColumns(in, out, true, _shift) == false)
        TFFT1DSpecialisation<T>::Perform(in, out, true, _shift); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1DSpecialisation<T>::Perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse, bool shift)
{
    if(klab::IsPowerOf2(in.n_rows))   
    {
        TFFT1DSpecialisation<T>::PerformRadix2(in, out, inverse, shift); 
    }
    else                        
    {
        // Note : This code must be optimized in order to compute FFT algorithm with sizes != 2^n. 
        // => Use combinations of different radixes for different sizes (currently, only radix 2 is implemented).
        TDFT1D<T> dft(shift);
        if(inverse==false)  dft.transformMatrixColumns(in, out);
        else                dft.invertMatrixColumns(in, out);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1DSpecialisation<T>::PerformRadix2(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse, bool shift)
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

            TFFT1DSpecialisation<std::complex<T> >::PerformRadix2(cIn, cOut, false, false);
            
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

            TFFT1DSpecialisation<std::complex<T> >::PerformRadix2(cIn, cOut, true, false);

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
inline void TFFT1DSpecialisation<std::complex<T> >::Perform(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse, bool shift)
{
    if(klab::IsPowerOf2(in.n_rows))   
    {
        TFFT1DSpecialisation<std::complex<T> >::PerformRadix2(in, out, inverse, shift); 
    }
    else                        
    {
        // Note : This code must be optimized in order to compute FFT algorithm with sizes != 2^n. 
        // => Use combinations of different radixes for different sizes (currently, only radix 2 is implemented).
        TDFT1D<std::complex<T> > dft(shift);
        if(inverse==false)  dft.transformMatrixColumns(in, out);
        else                dft.invertMatrixColumns(in, out);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1DSpecialisation<std::complex<T> >::ReorderRadix2(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse, bool shift)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;

    for(klab::UInt32 j=0; j<n; ++j)
    {
        klab::UInt32 target = 0;
        klab::UInt32 halfM  = m / 2;

        for(klab::UInt32 i=0; i<m; ++i)
        {
            klab::UInt32 iShift = i;
            if(shift && inverse)
                iShift = i<halfM ? i+halfM : i-halfM; 

            out(target, j) = in(iShift, j);

            klab::UInt32 mask = m;
            while(target & (mask>>=1))
                target &= ~mask;

            target |= mask;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1DSpecialisation<std::complex<T> >::PerformRadix2(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse, bool shift)
{   
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;

    if(m > 0)
    {
        ThrowTraceExceptionIf(KRadix2BadSizeFFTException, klab::IsPowerOf2(m)==false); 

        if(out.n_rows!=m || out.n_cols!=n)
            out.set_size(m, n);

        out.fill(klab::TTypeInfo<T>::ZERO);

        TFFT1DSpecialisation<std::complex<T> >::ReorderRadix2(in, out, inverse, shift);    

        T pi = T(inverse ? klab::PI : -klab::PI);

        for(klab::UInt32 j=0; j<n; ++j)
        {
            for(klab::UInt32 step=1; step<m; step<<=1)
            {
                klab::UInt32 jump = step<<1;
                T delta           = pi / T(step);
                T sinA            = klab::Sin(delta / T(2));

                std::complex<T> mult(T(-2) * sinA*sinA, klab::Sin(delta));
                std::complex<T> factor(T(1));

                for(klab::UInt32 group=0; group<step; ++group)
                {
                    for(klab::UInt32 pair=group; pair<m; pair+=jump)
                    {
                        klab::UInt32 match = pair + step;

                        std::complex<T> product(factor * out(match, j));
                        out(match, j) = out(pair, j) - product;
                        out(pair, j) += product;
                    }

                    factor = mult*factor + factor;
                }
            }

            if(inverse)
            {
                T invM = klab::TTypeInfo<T>::UNIT / static_cast<T>(m);
                for(klab::UInt32 i=0; i<m; ++i)
                    out(i, j) *= invM;
            }
        }

        if(shift && inverse==false)
            TFFT1DSpecialisation<std::complex<T> >::ShiftColumns(out);
    }
    else
    {
        out.set_size(0, n);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFFT1DSpecialisation<std::complex<T> >::ShiftColumns(arma::Mat<std::complex<T> >& mat)
{
    klab::UInt32 m = mat.n_rows;
    klab::UInt32 n = mat.n_cols;

    klab::UInt32 halfM = m>>1;

    for(klab::UInt32 j=0; j<n; ++j)
    {
        for(klab::UInt32 i=0; i<halfM; ++i)
        {
            klab::UInt32 i2 = halfM + i;

            std::complex<T> tmp = mat(i, j);
            mat(i, j)           = mat(i2, j);
            mat(i2, j)          = tmp;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
