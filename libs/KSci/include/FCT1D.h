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

#ifndef KLAB_FCT1D_H
#define KLAB_FCT1D_H

#include "DCT1D.h"
#include "FFT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KFCTException, KCosineTransformException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFCT1D
{
public:

    TFCT1D();
    TFCT1D(const TFCT1D<T>& fct);
    virtual ~TFCT1D();

    TFCT1D<T>&  operator=(const TFCT1D<T>& fct);

    void        transform(const arma::Col<T>& in, arma::Col<T>& out);
    void        invert(const arma::Col<T>& in, arma::Col<T>& out);

    void        transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);  // Compute FCT on every columns of the matrix.    
    void        invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);     // Compute inverse FCT on every columns of the matrix.


protected:

    void        perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse=false);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFCT1DSpecialisation
{
public:

    static void     Perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse);

private:

    TFCT1DSpecialisation();
    TFCT1DSpecialisation(const TFCT1DSpecialisation<T>& fct);
    TFCT1DSpecialisation<T>&    operator=(const TFCT1DSpecialisation<T>& fct);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFCT1DSpecialisation<std::complex<T> >
{
public:

    static void     Perform(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse);

private:

    TFCT1DSpecialisation();
    TFCT1DSpecialisation(const TFCT1DSpecialisation<T>& fct);
    TFCT1DSpecialisation<T>&    operator=(const TFCT1DSpecialisation<T>& fct);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFCT1D<T>::TFCT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFCT1D<T>::TFCT1D(const TFCT1D<T>& fct)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFCT1D<T>::~TFCT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFCT1D<T>& TFCT1D<T>::operator=(const TFCT1D<T>& fct)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFCT1D<T>::transform(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->transformMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFCT1D<T>::invert(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->invertMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFCT1D<T>::transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    TFCT1DSpecialisation<T>::Perform(in, out, false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFCT1D<T>::invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    TFCT1DSpecialisation<T>::Perform(in, out, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFCT1DSpecialisation<T>::Perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse)
{
    if(klab::IsPowerOf2(in.n_rows))   
    {
        klab::UInt32 m = in.n_rows;
        klab::UInt32 n = in.n_cols;    

        if(out.n_rows!=m || out.n_cols!=n)  
            out.set_size(m, n);

        out.fill(klab::TTypeInfo<T>::ZERO);

        if(m>0 && n>0)
        {    
            T piInv2m = (static_cast<T>(klab::PI) / static_cast<T>(m<<1));
            T invSqrtM = (klab::TTypeInfo<T>::UNIT / klab::Sqrt(static_cast<T>(m)));
            T sqrt2InvSqrtM = (invSqrtM * static_cast<T>(klab::SQRT2));

            arma::Mat<std::complex<T> > fftIn(m<<1, n);
            arma::Mat<std::complex<T> > fftOut;
            TFFT1D<std::complex<T> > fft;

            std::vector<T> cosBuffer(m);
            std::vector<T> sinBuffer(m);

            T iPiInv2m = 0;
            for(klab::UInt32 i=0; i<m; ++i)
            {
                cosBuffer[i] = klab::Cos(iPiInv2m);
                sinBuffer[i] = klab::Sin(iPiInv2m);

                iPiInv2m += piInv2m;
            }

            if(inverse == false)
            {          
                for(klab::UInt32 j=0; j<n; ++j)
                {
                    for(klab::UInt32 i=0; i<m; ++i)
                    {
                        fftIn(i, j)   = std::complex<T>(in(i, j));
                        fftIn(m+i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
                    }
                }
                
                fft.transformMatrixColumns(fftIn, fftOut);

                for(klab::UInt32 j=0; j<n; ++j)
                {
                    out(0, j) = (invSqrtM * fftOut(0, j).real());
                    for(klab::UInt32 i=1; i<m; ++i)
                        out(i, j) = sqrt2InvSqrtM * ((fftOut(i, j).real()*cosBuffer[i]) + (fftOut(i, j).imag()*sinBuffer[i]));
                }
            }
            else
            {
                T oneSubSqrt2InvSqrtM = ((klab::TTypeInfo<T>::UNIT-static_cast<T>(klab::SQRT2)) * invSqrtM);
                T sqrt22MInvSqrtM = (static_cast<T>(m<<1) * sqrt2InvSqrtM);

                for(klab::UInt32 j=0; j<n; ++j)
                {
                    for(klab::UInt32 i=0; i<m; ++i)
                    {
                        fftIn(i, j)   = std::complex<T>(in(i, j)*cosBuffer[i], in(i, j)*sinBuffer[i]); 
                        fftIn(m+i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
                    }
                }

                fft.invertMatrixColumns(fftIn, fftOut);

                for(klab::UInt32 j=0; j<n; ++j)
                {
                    for(klab::UInt32 i=0; i<m; ++i)
                        out(i, j) = oneSubSqrt2InvSqrtM*in(0, j) + sqrt22MInvSqrtM*fftOut(i, j).real();
                }
            }
        }
    }
    else                        
    {
        TDCT1D<T> dct;
        if(inverse==false)  dct.transformMatrixColumns(in, out);
        else                dct.invertMatrixColumns(in, out);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFCT1DSpecialisation<std::complex<T> >::Perform(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse)
{
    if(klab::IsPowerOf2(in.n_rows))   
    {
        klab::UInt32 m = in.n_rows;
        klab::UInt32 n = in.n_cols;    

        if(out.n_rows!=m || out.n_cols!=n)  
            out.set_size(m, n);

        out.fill(klab::TTypeInfo<std::complex<T> >::ZERO);

        if(m>0 && n>0)
        {    
            T piInv2m = (static_cast<T>(klab::PI) / static_cast<T>(m<<1));
            T invSqrtM = (klab::TTypeInfo<T>::UNIT / klab::Sqrt(static_cast<T>(m)));
            T sqrt2InvSqrtM = (invSqrtM * static_cast<T>(klab::SQRT2));

            arma::Mat<std::complex<T> > fftIn(m<<1, n);
            arma::Mat<std::complex<T> > fftOut;
            TFFT1D<std::complex<T> > fft;

            std::vector<T> cosBuffer(m);
            std::vector<T> sinBuffer(m);

            T iPiInv2m = 0;
            for(klab::UInt32 i=0; i<m; ++i)
            {
                cosBuffer[i] = klab::Cos(iPiInv2m);
                sinBuffer[i] = klab::Sin(iPiInv2m);

                iPiInv2m += piInv2m;
            }

            if(inverse == false)
            {          
                // Real part.
                for(klab::UInt32 j=0; j<n; ++j)
                {
                    for(klab::UInt32 i=0; i<m; ++i)
                    {
                        fftIn(i, j)   = std::complex<T>(in(i, j).real());
                        fftIn(m+i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
                    }
                }
                
                fft.transformMatrixColumns(fftIn, fftOut);

                for(klab::UInt32 j=0; j<n; ++j)
                {
                    out(0, j) = (invSqrtM * fftOut(0, j).real());
                    for(klab::UInt32 i=1; i<m; ++i)
                        out(i, j) = sqrt2InvSqrtM * ((fftOut(i, j).real()*cosBuffer[i]) + (fftOut(i, j).imag()*sinBuffer[i]));
                }
                // End of real part.

                // Imaginary part.
                for(klab::UInt32 j=0; j<n; ++j)
                {
                    for(klab::UInt32 i=0; i<m; ++i)
                    {
                        fftIn(i, j)   = std::complex<T>(in(i, j).imag());
                        fftIn(m+i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
                    }
                }
                
                fft.transformMatrixColumns(fftIn, fftOut);

                for(klab::UInt32 j=0; j<n; ++j)
                {
                    out(0, j) = std::complex<T>(out(0, j).real(), (invSqrtM * fftOut(0, j).real()));
                    for(klab::UInt32 i=1; i<m; ++i)
                        out(i, j) = std::complex<T>(out(i, j).real(), sqrt2InvSqrtM*((fftOut(i, j).real()*cosBuffer[i]) + (fftOut(i, j).imag()*sinBuffer[i])));
                }
                // End of imaginary part.
            }
            else
            {
                T oneSubSqrt2InvSqrtM = ((klab::TTypeInfo<T>::UNIT-static_cast<T>(klab::SQRT2)) * invSqrtM);
                T sqrt22MInvSqrtM = (static_cast<T>(m<<1) * sqrt2InvSqrtM);

                // Real part.
                for(klab::UInt32 j=0; j<n; ++j)
                {
                    for(klab::UInt32 i=0; i<m; ++i)
                    {
                        fftIn(i, j)   = std::complex<T>(in(i, j).real()*cosBuffer[i], in(i, j).real()*sinBuffer[i]); 
                        fftIn(m+i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
                    } 
                }

                fft.invertMatrixColumns(fftIn, fftOut);

                for(klab::UInt32 j=0; j<n; ++j)
                {
                    for(klab::UInt32 i=0; i<m; ++i)
                        out(i, j) = oneSubSqrt2InvSqrtM*in(0, j).real() + sqrt22MInvSqrtM*fftOut(i, j).real();
                }
                // End of real part.

                // Imaginary part.
                for(klab::UInt32 j=0; j<n; ++j)
                {
                    for(klab::UInt32 i=0; i<m; ++i)
                    {
                        fftIn(i, j)   = std::complex<T>(in(i, j).imag()*cosBuffer[i], in(i, j).imag()*sinBuffer[i]); 
                        fftIn(m+i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
                    } 
                }

                fft.invertMatrixColumns(fftIn, fftOut);

                for(klab::UInt32 j=0; j<n; ++j)
                {
                    for(klab::UInt32 i=0; i<m; ++i)
                        out(i, j) = std::complex<T>(out(i, j).real(), oneSubSqrt2InvSqrtM*in(0, j).imag()+sqrt22MInvSqrtM*fftOut(i, j).real());
                }
                // End of imaginary part.
            }
        }
    }
    else                        
    {
        TDCT1D<std::complex<T> > dct;
        if(inverse==false)  dct.transformMatrixColumns(in, out);
        else                dct.invertMatrixColumns(in, out);
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
