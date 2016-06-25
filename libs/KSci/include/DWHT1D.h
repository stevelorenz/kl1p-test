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

#ifndef KLAB_DWHT1D_H
#define KLAB_DWHT1D_H

#include "TrigoUtil.h"
#include "ArmadilloUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KWalshHadamardException, KException)
KLAB_DECLARE_EXCEPTION(KDWHTException, KWalshHadamardException)
KLAB_DECLARE_EXCEPTION(KSizePowerOf2DWHTException, KDWHTException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TDWHT1D
{
public:

    TDWHT1D();
    TDWHT1D(const TDWHT1D<T>& dwht);
    virtual ~TDWHT1D();

    TDWHT1D<T>&	operator=(const TDWHT1D<T>& dwht);

    void        transform(const arma::Col<T>& in, arma::Col<T>& out);
    void        invert(const arma::Col<T>& in, arma::Col<T>& out);

    void        transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);  // Compute DWHT on every columns of the matrix.    
    void        invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out);     // Compute inverse DWHT on every columns of the matrix.


protected:

    void        perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse=false);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDWHT1D<T>::TDWHT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDWHT1D<T>::TDWHT1D(const TDWHT1D<T>& dwht)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDWHT1D<T>::~TDWHT1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TDWHT1D<T>& TDWHT1D<T>::operator=(const TDWHT1D<T>& dwht)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDWHT1D<T>::transform(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->transformMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDWHT1D<T>::invert(const arma::Col<T>& in, arma::Col<T>& out)
{
    this->invertMatrixColumns(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDWHT1D<T>::transformMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDWHT1D<T>::invertMatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    this->perform(in, out, true);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TDWHT1D<T>::perform(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse)
{
    klab::UInt32 m = in.n_rows;
    klab::UInt32 n = in.n_cols;    

    if(out.n_rows!=m || out.n_cols!=n)  
        out.set_size(m, n);

    out.fill(klab::TTypeInfo<T>::ZERO);

    if(m>0 && n>0)
    {      
        ThrowTraceExceptionIf(KSizePowerOf2DWHTException, klab::IsPowerOf2(m)==false);

        T invM = klab::TTypeInfo<T>::UNIT / T(m);
        for(klab::UInt32 j=0; j<n; ++j)
        {
            for(klab::UInt32 k=0; k<m; ++k)
            {
                T value = klab::TTypeInfo<T>::ZERO;
                for(klab::UInt32 i=0; i<m; ++i)
                {
                    klab::UInt32 minKM = klab::Min(k, m);

                    klab::UInt32 bkm = 0;
                    for(klab::UInt32 mask=1; mask<=minKM; mask<<=1)
                        bkm += (((k&mask)>0 && (i&mask)>0) ? 1 : 0);

                    value += (in(i, j) * (bkm%2==0 ? T(1) : T(-1)));
                }

                out(k, j) = value;

                if(inverse)
                    out(k, j) *= invM;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
