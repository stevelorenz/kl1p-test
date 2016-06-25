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

#ifndef KLAB_FWHT1D_H
#define KLAB_FWHT1D_H

#include "DWHT1D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KFWHTException, KWalshHadamardException)
KLAB_DECLARE_EXCEPTION(KSizePowerOf2FWHTException, KFWHTException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TFWHT1D
{
public:

    TFWHT1D();
    TFWHT1D(const TFWHT1D<T>& fwht);
    virtual ~TFWHT1D();

    TFWHT1D<T>&	operator=(const TFWHT1D<T>& fwht);

    void        transform(const arma::Col<T>& in, arma::Col<T>& out);
    void        invert(const arma::Col<T>& in, arma::Col<T>& out);

    void        transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);  // Compute FWHT on every columns of the matrix.    
    void        invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);     // Compute inverse FWHT on every columns of the matrix.


protected:

    void        perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse=false);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFWHT1D<T>::TFWHT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFWHT1D<T>::TFWHT1D(const TFWHT1D<T>& fwht)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFWHT1D<T>::~TFWHT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TFWHT1D<T>& TFWHT1D<T>::operator=(const TFWHT1D<T>& fwht)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFWHT1D<T>::transform(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->transformMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFWHT1D<T>::invert(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->invertMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFWHT1D<T>::transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFWHT1D<T>::invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TFWHT1D<T>::perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;    

    if(out.n_rows!=m || out.n_cols!=n)  
        out.set_size(m, n);

    out.fill(klab::TTypeInfo<T>::ZERO);

    if(m>0 && n>0)
    {     
        ThrowTraceExceptionIf(KSizePowerOf2FWHTException, klab::IsPowerOf2(m)==false);

        out = in;

        T invM = klab::TTypeInfo<T>::UNIT / T(m);
        klab::UInt32 logM = static_cast<klab::UInt32>(klab::Log2(m)+0.5);	// To avoid rounding error.        

        for(klab::UInt32 j=0; j<n; ++j)
        {                
            for(klab::UInt32 im=0; im<logM; ++im)
            {
                klab::UInt32 pow2Im  = (1<<im);
                klab::UInt32 pow2Im1 = (1<<(im+1));

                for(klab::UInt32 i=0; i<m; i+=pow2Im1)
                {
                    for(klab::UInt32 k=0; k<pow2Im; ++k)
                    {
                        T tmp              = out(i+k, j);
                        out(i+k, j)       += out(i+k+pow2Im, j);
                        out(i+k+pow2Im, j) = (tmp - out(i+k+pow2Im, j));
                    }
                }
            }

            if(inverse)
            {
                for(klab::UInt32 i=0; i<m; ++i)                
                    out(i, j) *= invM;
            }
        }
    } 
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
