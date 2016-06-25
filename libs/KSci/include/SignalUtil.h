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

#ifndef KLAB_SIGNALUTIL_H
#define KLAB_SIGNALUTIL_H

#include "TrigoUtil.h"
#include "ArmadilloUtil.h"
#include "ThresholdedCountFilter1D.h"
#include "ThresholdedCountFilter2D.h"
#include "FFT1D.h"
#include "FFT2D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     SquaredError(const arma::Col<T>& x0, const arma::Col<T>& x)
{
    klab::DoubleReal ret = 0.0;

    klab::UInt32 n0 = x0.n_rows;
    klab::UInt32 n  = x.n_rows;

    klab::UInt32 nMin = klab::Min(n0, n);
    klab::UInt32 nMax = klab::Max(n0, n);

    if(nMax > 0)
    {
        for(klab::UInt32 i=0; i<nMin; ++i)
        {
            T diff = x0[i] - x[i];
            ret += diff * diff;
        }

        if(n0 > n)
        {
            for(klab::UInt32 i=nMin; i<n0; ++i)
                ret += x0[i] * x0[i];
        }
        else if(n0 < n)
        {
            for(klab::UInt32 i=nMin; i<n; ++i)
                ret += x[i] * x[i];
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     SquaredError(const arma::Mat<T>& x0, const arma::Mat<T>& x)
{
    klab::DoubleReal ret = 0.0;

    klab::UInt32 m0 = x0.n_rows;
    klab::UInt32 m  = x.n_rows;
    klab::UInt32 n0 = x0.n_cols;
    klab::UInt32 n  = x.n_cols;

    klab::UInt32 mMin = klab::Min(n0, m);
    klab::UInt32 mMax = klab::Max(n0, m);
    klab::UInt32 nMin = klab::Min(n0, n);
    klab::UInt32 nMax = klab::Max(n0, n);

    if(mMax>0 && nMax>0)
    {
        for(klab::UInt32 i=0; i<mMin; ++i)
        {
            for(klab::UInt32 j=0; j<nMin; ++j)
            {
                T diff = x0(i, j) - x(i, j);
                ret += diff * diff;
            }
        }

        if(m0 > m)
        {
            for(klab::UInt32 i=mMin; i<m0; ++i)
            {
                for(klab::UInt32 j=0; j<nMin; ++j)
                    ret += x0(i, j) * x0(i, j);
            }
        }
        else if(m0 < m)
        {
            for(klab::UInt32 i=mMin; i<m; ++i)
            {
                for(klab::UInt32 j=0; j<nMin; ++j)
                    ret += x(i, j) * x(i, j);
            }
        }

        if(n0 > n)
        {
            for(klab::UInt32 i=0; i<m0; ++i)
            {
                for(klab::UInt32 j=nMin; j<n0; ++j)
                    ret += x0(i, j) * x0(i, j);
            }
        }
        else if(n0 < n)
        {
            for(klab::UInt32 i=0; i<m; ++i)
            {
                for(klab::UInt32 j=nMin; j<n; ++j)
                    ret += x(i, j) * x(i, j);
            }
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     RootSquaredError(const arma::Col<T>& x0, const arma::Col<T>& x)
{
    klab::DoubleReal ret = 0.0;

    klab::UInt32 n0 = x0.n_rows;
    klab::UInt32 n  = x.n_rows;

    klab::UInt32 nMin = klab::Min(n0, n);
    klab::UInt32 nMax = klab::Max(n0, n);

    if(nMax > 0)
    {
        for(klab::UInt32 i=0; i<nMin; ++i)
        {
            T diff = x0[i] - x[i];
            ret += klab::Sqrt(static_cast<klab::DoubleReal>(diff) * static_cast<klab::DoubleReal>(diff));
        }

        if(n0 > n)
        {
            for(klab::UInt32 i=nMin; i<n0; ++i)
                ret += klab::Sqrt(static_cast<klab::DoubleReal>(x0[i]) * static_cast<klab::DoubleReal>(x0[i]));  
        }
        else if(n0 < n)
        {
            for(klab::UInt32 i=nMin; i<n; ++i)
                ret += klab::Sqrt(static_cast<klab::DoubleReal>(x[i]) * static_cast<klab::DoubleReal>(x[i]));  
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     RootSquaredError(const arma::Mat<T>& x0, const arma::Mat<T>& x)
{
    klab::DoubleReal ret = 0.0;

    klab::UInt32 m0 = x0.n_rows;
    klab::UInt32 m  = x.n_rows;
    klab::UInt32 n0 = x0.n_cols;
    klab::UInt32 n  = x.n_cols;

    klab::UInt32 mMin = klab::Min(n0, m);
    klab::UInt32 mMax = klab::Max(n0, m);
    klab::UInt32 nMin = klab::Min(n0, n);
    klab::UInt32 nMax = klab::Max(n0, n);

    if(mMax>0 && nMax>0)
    {
        for(klab::UInt32 i=0; i<mMin; ++i)
        {
            for(klab::UInt32 j=0; j<nMin; ++j)
            {
                T diff = x0(i, j) - x(i, j);
                ret += klab::Sqrt(static_cast<klab::DoubleReal>(diff) * static_cast<klab::DoubleReal>(diff));
            }
        }

        if(m0 > m)
        {
            for(klab::UInt32 i=mMin; i<m0; ++i)
            {
                for(klab::UInt32 j=0; j<nMin; ++j)
                    ret += klab::Sqrt(static_cast<klab::DoubleReal>(x0(i, j)) * static_cast<klab::DoubleReal>(x0(i, j))); 
            }
        }
        else if(m0 < m)
        {
            for(klab::UInt32 i=mMin; i<m; ++i)
            {
                for(klab::UInt32 j=0; j<nMin; ++j)
                    ret += klab::Sqrt(static_cast<klab::DoubleReal>(x(i, j)) * static_cast<klab::DoubleReal>(x(i, j))); 
            }
        }

        if(n0 > n)
        {
            for(klab::UInt32 i=0; i<m0; ++i)
            {
                for(klab::UInt32 j=nMin; j<n0; ++j)
                    ret += klab::Sqrt(static_cast<klab::DoubleReal>(x0(i, j)) * static_cast<klab::DoubleReal>(x0(i, j))); 
            }
        }
        else if(n0 < n)
        {
            for(klab::UInt32 i=0; i<m; ++i)
            {
                for(klab::UInt32 j=nMin; j<n; ++j)
                    ret += klab::Sqrt(static_cast<klab::DoubleReal>(x(i, j)) * static_cast<klab::DoubleReal>(x(i, j))); 
            }
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     SqrtSquaredError(const arma::Col<T>& x0, const arma::Col<T>& x)
{
    return klab::Sqrt(klab::SquaredError(x0, x));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     SqrtSquaredError(const arma::Mat<T>& x0, const arma::Mat<T>& x)
{
    return klab::Sqrt(klab::SquaredError(x0, x));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     MeanSquaredError(const arma::Col<T>& x0, const arma::Col<T>& x)
{
    klab::DoubleReal ret = 0.0;

    klab::UInt32 nMax = klab::Max(x0.n_rows, x.n_rows);

    if(nMax > 0)
        ret = klab::SquaredError(x0, x) / nMax;

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     MeanSquaredError(const arma::Mat<T>& x0, const arma::Mat<T>& x)
{
    klab::DoubleReal ret = 0.0;

    klab::UInt32 mMax = klab::Max(x0.n_rows, x.n_rows);
    klab::UInt32 nMax = klab::Max(x0.n_cols, x.n_cols);

    if(mMax>0 && nMax>0)
        ret = klab::SquaredError(x0, x) / (mMax*nMax);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     RootMeanSquaredError(const arma::Col<T>& x0, const arma::Col<T>& x)
{
    klab::DoubleReal ret = 0.0;

    klab::UInt32 nMax = klab::Max(x0.n_rows, x.n_rows);

    if(nMax > 0)
        ret = klab::RootSquaredError(x0, x) / nMax;

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     RootMeanSquaredError(const arma::Mat<T>& x0, const arma::Mat<T>& x)
{
    klab::DoubleReal ret = 0.0;

    klab::UInt32 mMax = klab::Max(x0.n_rows, x.n_rows);
    klab::UInt32 nMax = klab::Max(x0.n_cols, x.n_cols);

    if(mMax>0 && nMax>0)
        ret = klab::RootSquaredError(x0, x) / (mMax*nMax);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     SNR(const arma::Col<T>& x0, const arma::Col<T>& x)
{
    klab::DoubleReal ret = klab::DOUBLEREAL_INFINITY;

    klab::DoubleReal err    = klab::SqrtSquaredError(x0, x);
    klab::DoubleReal x0Norm = klab::SqrtSquaredError(x0, arma::Col<T>());

    if(klab::Equals(x0Norm, 0.0) && err>0.0)    ret = 0.0;
    else if(err > 0.0)                          ret = 20.0 * klab::Log10(x0Norm / err);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     SNR(const arma::Mat<T>& x0, const arma::Mat<T>& x)
{
    klab::DoubleReal ret = klab::DOUBLEREAL_INFINITY;

    klab::DoubleReal err    = klab::SqrtSquaredError(x0, x);
    klab::DoubleReal x0Norm = klab::SqrtSquaredError(x0, arma::Mat<T>());

    if(klab::Equals(x0Norm, 0.0) && err>0.0)    ret = 0.0;
    else if(err > 0.0)                          ret = 20.0 * klab::Log10(x0Norm / err);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     PSNR(const arma::Col<T>& x0, const arma::Col<T>& x)
{
    klab::DoubleReal ret = klab::DOUBLEREAL_INFINITY;

    klab::DoubleReal err = klab::MeanSquaredError(x0, x);

    klab::UInt32 n0 = x0.n_rows;
    klab::UInt32 n  = x.n_rows;

    T max1 = 0.0;
    for(klab::UInt32 i=0; i<n0; ++i)
        max1 = klab::Max(max1, x0[i]);

    T max2 = 0.0;
    for(klab::UInt32 i=0; i<n; ++i)
        max2 = klab::Max(max2, x[i]);

    T maxBoth = klab::Max(max1, max2);
    
    if(klab::Equals(maxBoth, 0.0) && err>0.0)   ret = 0.0;
    else if(err > 0.0)                          ret = 10.0 * klab::Log10(static_cast<klab::DoubleReal>(maxBoth*maxBoth) / err);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::DoubleReal     PSNR(const arma::Mat<T>& x0, const arma::Mat<T>& x)
{
    klab::DoubleReal ret = klab::DOUBLEREAL_INFINITY;

    klab::DoubleReal err = klab::MeanSquaredError(x0, x);

    klab::UInt32 m0 = x0.n_rows;
    klab::UInt32 m  = x.n_rows;
    klab::UInt32 n0 = x0.n_cols;
    klab::UInt32 n  = x.n_cols;

    T max1 = 0.0;
    for(klab::UInt32 i=0; i<m0; ++i)
    {
        for(klab::UInt32 j=0; j<n0; ++j)
            max1 = klab::Max(max1, x0(i, j));
    }

    T max2 = 0.0;
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
            max2 = klab::Max(max2, x(i, j));
    }

    T maxBoth = klab::Max(max1, max2);

    if(klab::Equals(maxBoth, 0.0) && err>0.0)   ret = 0.0;
    else if(err > 0.0)                          ret = 10.0 * klab::Log10(static_cast<klab::DoubleReal>(maxBoth*maxBoth) / err);

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Sparsify(arma::Col<T>& x, klab::DoubleReal sparsityRatio)
{
    if(x.n_rows > 0)
    {
        klab::DoubleReal ratio = ((sparsityRatio>=0.0) ? ((sparsityRatio<=1.0)?sparsityRatio:1.0) : 0.0);

        TThresholdedCountFilter1D<T, TAbsoluteThresholdedCountFilter1DReverseComparator<T> > filter(static_cast<klab::UInt32>(ratio * x.n_rows));
        filter.apply(x);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Sparsify(arma::Mat<T>& x, klab::DoubleReal sparsityRatio)
{
    if(x.n_rows>0 && x.n_cols>0)
    {
        klab::DoubleReal ratio = ((sparsityRatio>=0.0) ? ((sparsityRatio<=1.0)?sparsityRatio:1.0) : 0.0);

        TThresholdedCountFilter2D<T, TAbsoluteThresholdedCountFilter2DReverseComparator<T> > filter(static_cast<klab::UInt32>(ratio * x.n_rows * x.n_cols));
        filter.apply(x);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Sparsify(const arma::Col<T>& in, klab::DoubleReal sparsityRatio, arma::Col<T>& out)
{
    out = in;
    Sparsify(out, sparsityRatio);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Sparsify(const arma::Mat<T>& in, klab::DoubleReal sparsityRatio, arma::Mat<T>& out)
{
    out = in;
    Sparsify(out, sparsityRatio);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Convolve(const arma::Col<T>& u, const arma::Col<T>& v, arma::Col<T>& out)
{
    if(u.n_rows>0 && v.n_rows>0)
    {
        klab::UInt32 n = u.n_rows + v.n_rows - 1;
        out.set_size(n);

        arma::Col<std::complex<T> > left(n);
        arma::Col<std::complex<T> > right(n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            if(i<u.n_rows) left[i] = u[i];
            else           left[i] = klab::TTypeInfo<std::complex<T> >::ZERO;

            if(i<v.n_rows) right[i] = v[i];
            else           right[i] = klab::TTypeInfo<std::complex<T> >::ZERO;
        }
         
        klab::TFFT1D<std::complex<T> > fft;

        arma::Col<std::complex<T> > a;         
        fft.transform(left, a);

        arma::Col<std::complex<T> > b;
        fft.transform(right, b);

        for(klab::UInt32 i=0; i<n; ++i)
            a[i] *= b[i];

        fft.invert(a, b);
        
        for(klab::UInt32 i=0; i<n; ++i)
            out[i] = b[i].real();
    }
    else
    {
        out.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Convolve(const arma::Col<std::complex<T> >& u, const arma::Col<std::complex<T> >& v, arma::Col<std::complex<T> >& out)
{
    if(u.n_rows>0 && v.n_rows>0)
    {
        klab::UInt32 n = u.n_rows + v.n_rows - 1;
        out.set_size(n);

        arma::Col<std::complex<T> > left(n);
        arma::Col<std::complex<T> > right(n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            if(i<u.n_rows) left[i] = u[i];
            else           left[i] = klab::TTypeInfo<std::complex<T> >::ZERO;

            if(i<v.n_rows) right[i] = v[i];
            else           right[i] = klab::TTypeInfo<std::complex<T> >::ZERO;
        }
         
        klab::TFFT1D<std::complex<T> > fft;

        arma::Col<std::complex<T> > a;         
        fft.transform(left, a);

        arma::Col<std::complex<T> > b;
        fft.transform(right, b);

        for(klab::UInt32 i=0; i<n; ++i)
            a[i] *= b[i];

        fft.invert(a, out);
    }
    else
    {
        out.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Convolve(const arma::Mat<T>& u, const arma::Mat<T>& v, arma::Mat<T>& out)
{
    if(u.n_rows>0 && u.n_cols>0 && v.n_rows>0 && v.n_cols>0)
    {
        klab::UInt32 m = u.n_rows + v.n_rows - 1;
        klab::UInt32 n = u.n_cols + v.n_cols - 1;
        out.set_size(m, n);

        arma::Mat<std::complex<T> > left(m, n);
        arma::Mat<std::complex<T> > right(m, n);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                if(i<u.n_rows && j<u.n_cols)    left(i, j) = u(i, j);
                else                            left(i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;

                if(i<v.n_rows && j<v.n_cols)    right(i, j) = v(i, j);
                else                            right(i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
            }
        }
         
        klab::TFFT2D<std::complex<T> > fft;

        arma::Mat<std::complex<T> > a;         
        fft.transform(left, a);

        arma::Mat<std::complex<T> > b;
        fft.transform(right, b);

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
                a(i, j) *= b(i, j);
        }

        fft.invert(a, b);
        
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
                out(i, j) = b(i, j).real();
        }
    }
    else
    {
        out.set_size(0, 0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Convolve(const arma::Mat<std::complex<T> >& u, const arma::Mat<std::complex<T> >& v, arma::Mat<std::complex<T> >& out)
{
    if(u.n_rows>0 && u.n_cols>0 && v.n_rows>0 && v.n_cols>0)
    {
        klab::UInt32 m = u.n_rows + v.n_rows - 1;
        klab::UInt32 n = u.n_cols + v.n_cols - 1;
        out.set_size(m, n);

        arma::Mat<std::complex<T> > left(m, n);
        arma::Mat<std::complex<T> > right(m, n);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                if(i<u.n_rows && j<u.n_cols)    left(i, j) = u(i, j);
                else                            left(i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;

                if(i<v.n_rows && j<v.n_cols)    right(i, j) = v(i, j);
                else                            right(i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
            }
        }
         
        klab::TFFT2D<std::complex<T> > fft;

        arma::Mat<std::complex<T> > a;         
        fft.transform(left, a);

        arma::Mat<std::complex<T> > b;
        fft.transform(right, b);

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
                a(i, j) *= b(i, j);
        }

        fft.invert(a, out);
    }
    else
    {
        out.set_size(0, 0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 CrossCorrelate(const arma::Col<T>& u, const arma::Col<T>& v, arma::Col<T>& out)
{
    if(u.n_rows>0 && v.n_rows>0)
    {
        klab::UInt32 nx = klab::Max(u.n_rows, v.n_rows);
        klab::UInt32 n  = ((nx<<1) - 1);
        out.set_size(n);

        arma::Col<std::complex<T> > left(n);
        arma::Col<std::complex<T> > right(n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            if(i<u.n_rows) left[i] = u[i];
            else           left[i] = klab::TTypeInfo<std::complex<T> >::ZERO;

            if(i<v.n_rows) right[i] = v[i];
            else           right[i] = klab::TTypeInfo<std::complex<T> >::ZERO;
        }
         
        klab::TFFT1D<std::complex<T> > fft;

        arma::Col<std::complex<T> > a;         
        fft.transform(left, a);

        arma::Col<std::complex<T> > b;
        fft.transform(right, b);

        for(klab::UInt32 i=0; i<n; ++i)
            a[i] *= klab::Conj(b[i]);

        fft.invert(a, b);        

        // FFT shift.
        for(klab::UInt32 i=0; i<nx-1; ++i)
            out[i] = b[i+nx].real();

        for(klab::UInt32 i=0; i<nx; ++i)
            out[nx+i-1] = b[i].real();  
    }
    else
    {
        out.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 CrossCorrelate(const arma::Col<std::complex<T> >& u, const arma::Col<std::complex<T> >& v, arma::Col<std::complex<T> >& out)
{
    if(u.n_rows>0 && v.n_rows>0)
    {
        klab::UInt32 nx = klab::Max(u.n_rows, v.n_rows);
        klab::UInt32 n  = ((nx<<1) - 1);
        out.set_size(n);

        arma::Col<std::complex<T> > left(n);
        arma::Col<std::complex<T> > right(n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            if(i<u.n_rows) left[i] = u[i];
            else           left[i] = klab::TTypeInfo<std::complex<T> >::ZERO;

            if(i<v.n_rows) right[i] = v[i];
            else           right[i] = klab::TTypeInfo<std::complex<T> >::ZERO;
        }
         
        klab::TFFT1D<std::complex<T> > fft;

        arma::Col<std::complex<T> > a;         
        fft.transform(left, a);

        arma::Col<std::complex<T> > b;
        fft.transform(right, b);

        for(klab::UInt32 i=0; i<n; ++i)
            a[i] *= klab::Conj(b[i]);

        fft.invert(a, b); 

        // FFT shift.
        for(klab::UInt32 i=0; i<nx-1; ++i)
            out[i] = b[i+nx];

        for(klab::UInt32 i=0; i<nx; ++i)
            out[nx+i-1] = b[i];  
    }
    else
    {
        out.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 CrossCorrelate(const arma::Mat<T>& u, const arma::Mat<T>& v, arma::Mat<T>& out)
{
    if(u.n_rows>0 && u.n_cols>0 && v.n_rows>0 && v.n_cols>0)
    {
        klab::UInt32 mx = klab::Max(u.n_rows, v.n_rows);
        klab::UInt32 nx = klab::Max(u.n_cols, v.n_cols);
        klab::UInt32 m  = ((mx<<1) - 1);
        klab::UInt32 n  = ((nx<<1) - 1);
        out.set_size(m, n);

        arma::Mat<std::complex<T> > left(m, n);
        arma::Mat<std::complex<T> > right(m, n);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                if(i<u.n_rows && j<u.n_cols)    left(i, j) = u(i, j);
                else                            left(i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;

                if(i<v.n_rows && j<v.n_cols)    right(i, j) = v(i, j);
                else                            right(i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
            }
        }
         
        klab::TFFT2D<std::complex<T> > fft;

        arma::Mat<std::complex<T> > a;         
        fft.transform(left, a);

        arma::Mat<std::complex<T> > b;
        fft.transform(right, b);

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
                a(i, j) *= klab::Conj(b(i, j));
        }

        fft.invert(a, b);

        // FFT shift.
        klab::UInt32 halfM = m>>1;
        klab::UInt32 halfN = n>>1;
        for (klab::UInt32 i=0; i<m; ++i) 
        {
            klab::UInt32 i2 = (i+halfM)%m;
            for(klab::UInt32 j=0; j<n; ++j) 
            {
                klab::UInt32 j2 = (j+halfN)%n;
                out(i2, j2) = b(i, j).real();
            }
        }
    }
    else
    {
        out.set_size(0, 0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 CrossCorrelate(const arma::Mat<std::complex<T> >& u, const arma::Mat<std::complex<T> >& v, arma::Mat<std::complex<T> >& out)
{
    if(u.n_rows>0 && u.n_cols>0 && v.n_rows>0 && v.n_cols>0)
    {
        klab::UInt32 mx = klab::Max(u.n_rows, v.n_rows);
        klab::UInt32 nx = klab::Max(u.n_cols, v.n_cols);
        klab::UInt32 m  = ((mx<<1) - 1);
        klab::UInt32 n  = ((nx<<1) - 1);
        out.set_size(m, n);

        arma::Mat<std::complex<T> > left(m, n);
        arma::Mat<std::complex<T> > right(m, n);
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                if(i<u.n_rows && j<u.n_cols)    left(i, j) = u(i, j);
                else                            left(i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;

                if(i<v.n_rows && j<v.n_cols)    right(i, j) = v(i, j);
                else                            right(i, j) = klab::TTypeInfo<std::complex<T> >::ZERO;
            }
        }
         
        klab::TFFT2D<std::complex<T> > fft;

        arma::Mat<std::complex<T> > a;         
        fft.transform(left, a);

        arma::Mat<std::complex<T> > b;
        fft.transform(right, b);

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
                a(i, j) *= klab::Conj(b(i, j));
        }

        fft.invert(a, b);

        // FFT shift.
        klab::UInt32 halfM = m>>1;
        klab::UInt32 halfN = n>>1;
        for (klab::UInt32 i=0; i<m; ++i) 
        {
            klab::UInt32 i2 = (i+halfM)%m;
            for(klab::UInt32 j=0; j<n; ++j) 
            {
                klab::UInt32 j2 = (j+halfN)%n;
                out(i2, j2) = b(i, j);
            }
        }
    }
    else
    {
        out.set_size(0, 0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T                    Correlation(const arma::Col<T>& u, const arma::Col<T>& v)
{
    if(u.n_rows>0 && v.n_rows>0)
    {
        klab::UInt32 n = klab::Max(u.n_rows, v.n_rows);
        T invN = klab::TTypeInfo<T>::UNIT / static_cast<T>(n);

        T uMean = klab::TTypeInfo<T>::ZERO;
        for(klab::UInt32 i=0; i<u.n_rows; ++i)
            uMean += u[i];
        uMean *= invN;

        T vMean = klab::TTypeInfo<T>::ZERO;
        for(klab::UInt32 i=0; i<v.n_rows; ++i)
            vMean += v[i];
        vMean *= invN;

        arma::Col<T> f(n);
        arma::Col<T> g(n);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            if(i<u.n_rows) f[i] = klab::Conj(u[i]-uMean);
            else           f[i] = klab::Conj(-uMean);

            if(i<v.n_rows) g[i] = v[i] - vMean;
            else           g[i] = -vMean;
        }

        T normF = arma::norm(f, 2);
        T normG = arma::norm(g, 2);
        
        if(klab::Equals(normF, klab::TTypeInfo<T>::ZERO))
        {
            // If norm(f) and norm(g) are both zero, then the two input vectors u and v are filled with a constant value. 
            if(klab::Equals(normG, klab::TTypeInfo<T>::ZERO))   return (klab::Equals(u[0], v[0]) ? klab::TTypeInfo<T>::UNIT : klab::TTypeInfo<T>::ZERO);
            else                                                return klab::TTypeInfo<T>::ZERO;    
        }
        else if(klab::Equals(normG, klab::TTypeInfo<T>::ZERO))
        {
            return klab::TTypeInfo<T>::ZERO;    
        }
        else
        {
            f /= normF; 
            g /= normG;

            return arma::dot(f, g); 
        }
    }
    else
    {
        return klab::TTypeInfo<T>::ZERO;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T                    Correlation(const arma::Mat<T>& u, const arma::Mat<T>& v)
{
    if(u.n_rows>0 && u.n_cols>0 && v.n_rows>0 && v.n_cols>0)
    {
        klab::UInt32 m = klab::Max(u.n_rows, v.n_rows);
        klab::UInt32 n = klab::Max(u.n_cols, v.n_cols);
        klab::UInt32 mn = m*n;
        T invMN = klab::TTypeInfo<T>::UNIT / static_cast<T>(mn);

        T uMean = klab::TTypeInfo<T>::ZERO;
        for(klab::UInt32 i=0; i<u.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<u.n_cols; ++j)
                uMean += u(i, j);
        }
        uMean *= invMN;

        T vMean = klab::TTypeInfo<T>::ZERO;
        for(klab::UInt32 i=0; i<v.n_rows; ++i)
        {
            for(klab::UInt32 j=0; j<v.n_cols; ++j)
                vMean += v(i, j);
        }
        vMean *= invMN;

        arma::Col<T> f(mn);
        arma::Col<T> g(mn);

        klab::UInt32 k = 0;
        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j, ++k)
            {
                if(i<u.n_rows && j<u.n_cols)    f[k] = klab::Conj(u(i, j)-uMean);
                else                            f[k] = klab::Conj(-uMean);

                if(i<v.n_rows && j<v.n_cols)    g[k] = v(i, j) - vMean;
                else                            g[k] = -vMean;
            }
        }

        T normF = arma::norm(f, 2);
        T normG = arma::norm(g, 2);
        
        if(klab::Equals(normF, klab::TTypeInfo<T>::ZERO))
        {
            // If norm(f) and norm(g) are both zero, then the two input vectors u and v are filled with a constant value. 
            if(klab::Equals(normG, klab::TTypeInfo<T>::ZERO))   return (klab::Equals(u[0], v[0]) ? klab::TTypeInfo<T>::UNIT : klab::TTypeInfo<T>::ZERO);
            else                                                return klab::TTypeInfo<T>::ZERO;    
        }
        else if(klab::Equals(normG, klab::TTypeInfo<T>::ZERO))
        {
            return klab::TTypeInfo<T>::ZERO;    
        }
        else
        {
            f /= normF; 
            g /= normG;

            return arma::dot(f, g); 
        }
    }
    else
    {
        return klab::TTypeInfo<T>::ZERO;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Downsample(const arma::Col<T>& in, klab::UInt32 factor, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KBadArithmeticException, factor==0);

    if(factor > 1)
    {
        T tn = static_cast<T>(in.n_rows) / static_cast<T>(factor);
        klab::UInt32 n = static_cast<klab::UInt32>(tn);
        if((tn-T(n)) > 1e-6)
            ++n;

        out.set_size(n);

        for(klab::UInt32 i=0; i<n; ++i)
            out[i] = in[static_cast<klab::UInt32>(i*factor)];
    }
    else
    {
        out = in;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Downsample(const arma::Mat<T>& in,  klab::UInt32 factor, arma::Mat<T>& out)
{
    ThrowTraceExceptionIf(KBadArithmeticException, factor==0);

    if(factor > 1)
    {
        T tm = static_cast<T>(in.n_rows) / static_cast<T>(factor);
        T tn = static_cast<T>(in.n_cols) / static_cast<T>(factor);      

        klab::UInt32 m = static_cast<klab::UInt32>(tm);
        if((tm-T(m)) > 1e-6)
            ++m;

        klab::UInt32 n = static_cast<klab::UInt32>(tn);
        if((tn-T(n)) > 1e-6)
            ++n;

        out.set_size(m, n);

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
                out(i, j) = in(static_cast<klab::UInt32>(i*factor), static_cast<klab::UInt32>(j*factor));
        }
    }
    else
    {
        out = in;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Upsample(const arma::Col<T>& in, klab::UInt32 factor, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KBadArithmeticException, factor==0);

    if(factor > 1)
    {
        klab::UInt32 n = (in.n_rows * factor);
        out.set_size(n);

        for(klab::UInt32 i=0; i<n; ++i)
        {
            if((i%factor)==0)   out[i] = in[i/factor];
            else                out[i] = klab::TTypeInfo<T>::ZERO;
        }
    }
    else
    {
        out = in;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void                 Upsample(const arma::Mat<T>& in,  klab::UInt32 factor, arma::Mat<T>& out)
{
    ThrowTraceExceptionIf(KBadArithmeticException, factor==0);

    if(factor > 1)
    {
        klab::UInt32 m = (in.n_rows * factor);
        klab::UInt32 n = (in.n_cols * factor);
        out.set_size(m, n);

        for(klab::UInt32 i=0; i<m; ++i)
        {
            for(klab::UInt32 j=0; j<n; ++j)
            {
                if((i%factor)==0 && (j%factor)==0)  out(i, j) = in(i/factor, j/factor);
                else                                out(i, j) = klab::TTypeInfo<T>::ZERO;
            }
        }
    }
    else
    {
        out = in;
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
