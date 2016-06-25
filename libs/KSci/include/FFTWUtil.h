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

#ifndef KLAB_FFTWUTIL_H
#define KLAB_FFTWUTIL_H

#include "ArmadilloUtil.h"




#if defined(KSCI_ENABLE_DYNAMIC_FFTW) || defined(KSCI_ENABLE_STATIC_FFTW)

#include <fftw3.h>

namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class KFFTWModule : public klab::TSingleton<KFFTWModule<T> >
{
public:

    typedef fftw_complex        TFFTWComplex;
    typedef klab::DoubleReal    TFFTWReal;    


public:

    KFFTWModule();
    virtual ~KFFTWModule();

    bool                isLoaded() const;
    KModuleFunction     function(const std::string& name);


private:
    
    KFFTWModule(const KFFTWModule<T>& module);
    KFFTWModule<T>&     operator=(const KFFTWModule<T>& module);

private:

    klab::KModule       _module;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline KFFTWModule<T>::KFFTWModule() : klab::TSingleton<KFFTWModule<T> >(),
_module("libfftw3-3")
{
    _module.load();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline KFFTWModule<T>::~KFFTWModule()
{
    _module.clean();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool KFFTWModule<T>::isLoaded() const
{
    return _module.isLoaded();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline KModuleFunction KFFTWModule<T>::function(const std::string& name)
{
    return _module.function(name);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool             ComputeFFTW1D_MatrixColumns(const arma::Mat<std::complex<T> >& in, arma::Mat<std::complex<T> >& out, bool inverse, bool shift)
{
    try
    {
        if(in.n_rows>0 && in.n_cols>0)
        {
#if defined(KSCI_ENABLE_DYNAMIC_FFTW)
            typedef void*       (*FFTWMallocFunc)(size_t);
            typedef fftw_plan   (*FFTWPlanDft1dFunc)(int, KFFTWModule<T>::TFFTWComplex*, KFFTWModule<T>::TFFTWComplex*, int, unsigned);
            typedef void        (*FFTWExecuteFunc)(const fftw_plan);
            typedef void        (*FFTWDestroyPlanFunc)(fftw_plan);
            typedef void        (*FFTWFreeFunc)(void*);

            KFFTWModule<T>& fftw = KFFTWModule<T>::Instance();
            if(fftw.isLoaded() == false)
                return false;

            FFTWMallocFunc fftw_malloc = static_cast<FFTWMallocFunc>(fftw.function("fftw_malloc"));
            FFTWPlanDft1dFunc fftw_plan_dft_1d = static_cast<FFTWPlanDft1dFunc>(fftw.function("fftw_plan_dft_1d"));
            FFTWExecuteFunc fftw_execute = static_cast<FFTWExecuteFunc>(fftw.function("fftw_execute"));
            FFTWDestroyPlanFunc fftw_destroy_plan = static_cast<FFTWDestroyPlanFunc>(fftw.function("fftw_destroy_plan"));
            FFTWFreeFunc fftw_free = static_cast<FFTWFreeFunc>(fftw.function("fftw_free"));
#endif

            KFFTWModule<T>::TFFTWComplex* fftwIn = static_cast<KFFTWModule<T>::TFFTWComplex*>(fftw_malloc(sizeof(KFFTWModule<T>::TFFTWComplex)*in.n_rows));
            KFFTWModule<T>::TFFTWComplex* fftwOut = static_cast<KFFTWModule<T>::TFFTWComplex*>(fftw_malloc(sizeof(KFFTWModule<T>::TFFTWComplex)*in.n_rows));
            fftw_plan plan = fftw_plan_dft_1d(in.n_rows, fftwIn, fftwOut, inverse?FFTW_BACKWARD:FFTW_FORWARD, FFTW_ESTIMATE);
            
            klab::UInt32 halfM = in.n_rows >> 1;
            klab::UInt32 mEven = in.n_rows % 2;

            out.set_size(in.n_rows, in.n_cols);
            for(klab::UInt32 j=0; j<in.n_cols; ++j)
            {
                for(klab::UInt32 i=0; i<in.n_rows; ++i)
                {
                    klab::UInt32 i2 = i;
                    if(shift && inverse)
                        i2 = i<(halfM+mEven) ? i+halfM : i-halfM-mEven; 

                    fftwIn[i][0] = static_cast<KFFTWModule<T>::TFFTWReal>(in(i2, j).real());
                    fftwIn[i][1] = static_cast<KFFTWModule<T>::TFFTWReal>(in(i2, j).imag());
                }

                fftw_execute(plan); 

                for(klab::UInt32 i=0; i<out.n_rows; ++i)
                {
                    klab::UInt32 i2 = i;
                    if(shift && inverse==false)
                        i2 = i<(halfM+mEven) ? i+halfM : i-halfM-mEven; 

                    out(i2, j) = std::complex<T>(static_cast<T>(fftwOut[i][0]), static_cast<T>(fftwOut[i][1]));
                }

                if(inverse)
                {
                    T invM = klab::TTypeInfo<T>::UNIT / static_cast<T>(out.n_rows);
                    for(klab::UInt32 i=0; i<out.n_rows; ++i)
                        out(i, j) *= invM;
                }
            }

            fftw_destroy_plan(plan);
            fftw_free(fftwOut);
            fftw_free(fftwIn);          

            return true;
        }
        else
        {
            out.set_size(in.n_rows, in.n_cols);

            return true;
        }
    }
    catch(...)
    {
        return false;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool             ComputeFFTW1D_MatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse, bool shift)
{
    if(in.n_rows>0 && in.n_cols>0)
    {
        if(inverse == false)
        {
            arma::Mat<std::complex<T> > inc(in.n_rows, in.n_cols);
            arma::Mat<std::complex<T> > outc;

            for(klab::UInt32 i=0; i<inc.n_rows; ++i)
            {
                for(klab::UInt32 j=0; j<inc.n_cols; ++j)
                    inc(i, j) = in(i, j);
            }

            if(ComputeFFTW1D_MatrixColumns(inc, outc, inverse, false))
            {
                out.set_size(outc.n_rows, outc.n_cols);

                klab::UInt32 halfM = out.n_rows>>1;
                for(klab::UInt32 j=0; j<out.n_cols; ++j)
                {
                    for(klab::UInt32 i=0; i<=halfM; ++i)
                        out(i, j) = outc(i, j).real();

                    for(klab::UInt32 i=halfM+1; i<out.n_rows; ++i)
                        out(i, j) = outc(i-halfM, j).imag();
                }

                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            arma::Mat<std::complex<T> > inc(in.n_rows, in.n_cols);
            arma::Mat<std::complex<T> > outc;

            klab::UInt32 halfM = inc.n_rows>>1;
            for(klab::UInt32 j=0; j<inc.n_cols; ++j)
            {
                inc(0, j) = in(0, j);
                for(klab::UInt32 i=1; i<=halfM; ++i)
                {                    
                    T real      = in(i, j);
                    T imaginary = 0.0;
                    if(i+halfM < inc.n_rows)
                        imaginary = in(i+halfM, j);

                    inc(i, j) = std::complex<T>(real,  imaginary);
                    inc(inc.n_rows-i, j) = std::complex<T>(real, -imaginary);
                }
            }

            if(ComputeFFTW1D_MatrixColumns(inc, outc, inverse, false))
            {
                out.set_size(outc.n_rows, outc.n_cols);

                for(klab::UInt32 i=0; i<out.n_rows; ++i)
                {
                    for(klab::UInt32 j=0; j<out.n_cols; ++j)
                        out(i, j) = outc(i, j).real();
                }

                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        out.set_size(in.n_rows, in.n_cols);

        return true;
    }
}

// ---------------------------------------------------------------------------------------------------- //

}

#else

namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool             ComputeFFTW1D_MatrixColumns(const arma::Mat<T>& in, arma::Mat<T>& out, bool inverse, bool shift)
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

}

#endif


#endif
