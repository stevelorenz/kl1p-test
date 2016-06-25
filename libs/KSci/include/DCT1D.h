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

#ifndef KLAB_DCT1D_H
#define KLAB_DCT1D_H

#include "TrigoUtil.h"
#include "ArmadilloUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KCosineTransformException, KException)
KLAB_DECLARE_EXCEPTION(KDCTException, KCosineTransformException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDCT1D
{
public:

    TDCT1D();
    TDCT1D(const TDCT1D<T>& dct);
    virtual ~TDCT1D();

    TDCT1D<T>&  operator=(const TDCT1D<T>& dct);

    void        transform(const arma::Col<T>& in, arma::Col<T>& out);
    void        invert(const arma::Col<T>& in, arma::Col<T>& out);

    void        transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);  // Compute DCT on every columns of the matrix.    
    void        invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);     // Compute inverse DCT on every columns of the matrix.


protected:

    void        perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse=false);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDCT1DSpecialisation
{
public:

    static void     Perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse);

private:

    TDCT1DSpecialisation();
    TDCT1DSpecialisation(const TDCT1DSpecialisation<T>& dct);
    TDCT1DSpecialisation<T>&    operator=(const TDCT1DSpecialisation<T>& dct);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDCT1DSpecialisation<std::complex<T> >
{
public:

    static void     Perform(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse);

private:

    TDCT1DSpecialisation();
    TDCT1DSpecialisation(const TDCT1DSpecialisation<T>& dct);
    TDCT1DSpecialisation<T>&    operator=(const TDCT1DSpecialisation<T>& dct);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT1D<T>::TDCT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT1D<T>::TDCT1D(const TDCT1D<T>& dct)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT1D<T>::~TDCT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDCT1D<T>& TDCT1D<T>::operator=(const TDCT1D<T>& dct)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT1D<T>::transform(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->transformMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT1D<T>::invert(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->invertMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT1D<T>::transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    TDCT1DSpecialisation<T>::Perform(in, out, false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT1D<T>::invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    TDCT1DSpecialisation<T>::Perform(in, out, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT1DSpecialisation<T>::Perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;    

    if(out.n_rows!=m || out.n_cols!=n)  
        out.set_size(m, n);

    out.fill(klab::TTypeInfo<T>::ZERO);

    if(m>0 && n>0)
    {      
        T invM      = (klab::TTypeInfo<T>::UNIT / static_cast<T>(m));
        T sqrt2InvM = klab::Sqrt(static_cast<T>(2)*invM);
        T piInv2m   = (static_cast<T>(klab::PI) / static_cast<T>(m<<1));

        for(klab::UInt32 j=0; j<n; ++j)
        {            
            for(klab::UInt32 i=0; i<m; ++i)
            {
                T iPiInv2m = klab::TTypeInfo<T>::ZERO; 
                if(inverse == false)
                    iPiInv2m = (i * piInv2m);

                for(klab::UInt32 k=0; k<m; ++k)
                {
                    if(inverse == false)
                    {
                        out(i, j) += (in(k, j) * klab::Cos(static_cast<T>((k<<1)+1)*iPiInv2m)); 
                    }
                    else
                    {
                        T kPiInv2m = (k * piInv2m);
                        out(i, j) += (in(k, j) * klab::Cos(static_cast<T>((i<<1)+1)*kPiInv2m));   

                        if(k == 0)
                            out(i, j) *= static_cast<T>(klab::INV_SQRT2);
                    }              
                }

                out(i, j) *= sqrt2InvM; 
            }

            if(inverse == false)
                out(0, j) *= static_cast<T>(klab::INV_SQRT2);
        }        
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDCT1DSpecialisation<std::complex<T> >::Perform(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;    

    if(out.n_rows!=m || out.n_cols!=n)  
        out.set_size(m, n);

    out.fill(klab::TTypeInfo<std::complex<T> >::ZERO);

    if(m>0 && n>0)
    {      
        T invM      = (klab::TTypeInfo<T>::UNIT / static_cast<T>(m));
        T sqrt2InvM = klab::Sqrt(static_cast<T>(2)*invM);
        T piInv2m   = (static_cast<T>(klab::PI) / static_cast<T>(m<<1));

        for(klab::UInt32 j=0; j<n; ++j)
        {            
            for(klab::UInt32 i=0; i<m; ++i)
            {
                T iPiInv2m = klab::TTypeInfo<T>::ZERO; 
                if(inverse == false)
                    iPiInv2m = (i * piInv2m);

                for(klab::UInt32 k=0; k<m; ++k)
                {
                    if(inverse == false)
                    {
                        T cosA     = klab::Cos(static_cast<T>((k<<1)+1) * iPiInv2m);
                        out(i, j) += std::complex<T>(cosA*in(k, j).real(), cosA*in(k, j).imag());
                    }
                    else
                    {
                        T kPiInv2m = (k * piInv2m);                        
                        T cosA     = klab::Cos(static_cast<T>((i<<1)+1) * kPiInv2m);
                        out(i, j) += std::complex<T>(cosA*in(k, j).real(), cosA*in(k, j).imag());

                        if(k == 0)
                            out(i, j) *= static_cast<T>(klab::INV_SQRT2);
                    }              
                }

                out(i, j) *= sqrt2InvM; 

                if(inverse==false && i==0)
                    out(i, j) *= static_cast<T>(klab::INV_SQRT2);
            }
        }        
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
