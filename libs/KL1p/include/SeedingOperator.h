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

#ifndef KL1P_SEEDINGOPERATOR_H
#define KL1P_SEEDINGOPERATOR_H

#include "BlockTridiagonalOperator.h"
#include "NormalRandomMatrixOperator.h"
#include "VarianceShadowOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TSeedingOperator : public TBlockTridiagonalOperator<T, T, TOperator<T, T> >
{
public:
    
    TSeedingOperator(klab::UInt32 blocks, klab::UInt32 m0, klab::UInt32 n0, klab::UInt32 mb, klab::UInt32 nb, const T& diagVariance, const T& lowerVariance, const T& upperVariance);
    TSeedingOperator(klab::UInt32 n, klab::UInt32 blocks, klab::DoubleReal alpha0, klab::DoubleReal alphaB, const T& diagVariance, const T& lowerVariance, const T& upperVariance); 
    TSeedingOperator(const TSeedingOperator<T>& op);
    virtual ~TSeedingOperator();

    klab::UInt32                 countSeededBlocks() const;
    klab::UInt32                 m0() const;
    klab::UInt32                 n0() const;
    klab::UInt32                 mb() const;
    klab::UInt32                 nb() const;
    const T&                            diagonalVariance() const;
    const T&                            lowerVariance() const;
    const T&                            upperVariance() const;


protected:

    void    init(klab::UInt32 blocks, klab::UInt32 m0, klab::UInt32 n0, klab::UInt32 mb, klab::UInt32 nb, const T& diagVariance, const T& lowerVariance, const T& upperVariance);


private:

    TSeedingOperator();
    TSeedingOperator<T>&				operator=(const TSeedingOperator<T>& op);


private:

    klab::UInt32                        _countBlocks;
    klab::UInt32                        _m0;
    klab::UInt32                        _n0;
    klab::UInt32                        _mb;
    klab::UInt32                        _nb;

    T                                   _dVariance;
    T                                   _lVariance;
    T                                   _uVariance;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TSeedingOperatorSpecialisation
{
public:

    static T        GetSigma(const T& variance, klab::UInt32 m, klab::UInt32 n);
    static T        GetVariance(const T& variance);


private:

    TSeedingOperatorSpecialisation();
    TSeedingOperatorSpecialisation(const TSeedingOperatorSpecialisation<T>& spec);
    TSeedingOperatorSpecialisation<T>&	operator=(const TSeedingOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TSeedingOperatorSpecialisation<std::complex<T> >
{
public:

    static std::complex<T>  GetSigma(const std::complex<T>& variance, klab::UInt32 m, klab::UInt32 n);
    static std::complex<T>  GetVariance(const std::complex<T>& variance);


private:

    TSeedingOperatorSpecialisation();
    TSeedingOperatorSpecialisation(const TSeedingOperatorSpecialisation<std::complex<T> >& spec);
    TSeedingOperatorSpecialisation<std::complex<T> >&	operator=(const TSeedingOperatorSpecialisation<std::complex<T> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSeedingOperator<T>::TSeedingOperator(klab::UInt32 blocks, klab::UInt32 m0, klab::UInt32 n0, klab::UInt32 mb, klab::UInt32 nb, const T& diagVariance, const T& lowerVariance, const T& upperVariance) : TBlockTridiagonalOperator<T, T, TOperator<T, T> >(),
_countBlocks(0), _m0(0), _n0(0), _mb(0), _nb(0), _dVariance(klab::TTypeInfo<T>::ZERO), _lVariance(klab::TTypeInfo<T>::ZERO), _uVariance(klab::TTypeInfo<T>::ZERO)
{
    this->init(blocks, m0, n0, mb, nb, diagVariance, lowerVariance, upperVariance);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSeedingOperator<T>::TSeedingOperator(klab::UInt32 n, klab::UInt32 blocks, klab::DoubleReal alpha0, klab::DoubleReal alphaB, const T& diagVariance, const T& lowerVariance, const T& upperVariance) : TBlockTridiagonalOperator<T, T, TOperator<T, T> >(),
_countBlocks(0), _m0(0), _n0(0), _mb(0), _nb(0), _dVariance(klab::TTypeInfo<T>::ZERO), _lVariance(klab::TTypeInfo<T>::ZERO), _uVariance(klab::TTypeInfo<T>::ZERO) 
{
    if(blocks > 0)
    {
        klab::UInt32 nb = n / blocks;
        klab::UInt32 n0 = n - (nb * (blocks-1));
        klab::UInt32 mb = static_cast<klab::UInt32>(alphaB*nb);
        klab::UInt32 m0 = static_cast<klab::UInt32>(alpha0*n0);
        
        this->init(blocks, m0, n0, mb, nb, diagVariance, lowerVariance, upperVariance);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSeedingOperator<T>::TSeedingOperator(const TSeedingOperator<T>& op) : TBlockTridiagonalOperator<T, T, TOperator<T, T> >(op),
_countBlocks(op._countBlocks), _m0(op._m0), _n0(op._n0), _mb(op._mb), _nb(op._nb), _dVariance(op._dVariance), _lVariance(op._lVariance), _uVariance(op._uVariance)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSeedingOperator<T>::~TSeedingOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TSeedingOperator<T>::countSeededBlocks() const
{
    return _countBlocks;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TSeedingOperator<T>::m0() const
{
    return _m0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TSeedingOperator<T>::n0() const
{
    return _n0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TSeedingOperator<T>::mb() const
{
    return _mb;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TSeedingOperator<T>::nb() const
{
    return _nb;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TSeedingOperator<T>::diagonalVariance() const
{
    return _dVariance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TSeedingOperator<T>::lowerVariance() const
{
    return _lVariance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TSeedingOperator<T>::upperVariance() const
{
    return _uVariance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TSeedingOperator<T>::init(klab::UInt32 blocks, klab::UInt32 m0, klab::UInt32 n0, klab::UInt32 mb, klab::UInt32 nb, const T& diagVariance, const T& lowerVariance, const T& upperVariance)
{
    _countBlocks = blocks;
    _m0 = m0;
    _n0 = n0;
    _mb = mb;
    _nb = nb;
    _dVariance = diagVariance;
    _lVariance = lowerVariance;
    _uVariance = upperVariance;

    if(_countBlocks > 0)
    {
        if(_m0>0 && _n0>0)
        {
            klab::UInt32 m = m0 + ((_countBlocks-1) * mb);   
            klab::UInt32 n = n0 + ((_countBlocks-1) * nb);            

            typename TBlockTridiagonalOperator<T, T, TOperator<T, T> >::TOperatorArray diagonal;
            typename TBlockTridiagonalOperator<T, T, TOperator<T, T> >::TOperatorArray lower;
            typename TBlockTridiagonalOperator<T, T, TOperator<T, T> >::TOperatorArray upper;

            diagonal.push_back(new TVarianceShadowOperator<T, T, TOperator<T, T> >(new kl1p::TNormalRandomMatrixOperator<T>(_m0, _n0, klab::TTypeInfo<T>::ZERO, TSeedingOperatorSpecialisation<T>::GetSigma(_dVariance, m, n)), TSeedingOperatorSpecialisation<T>::GetVariance(_dVariance)));

            if(_countBlocks>1 && _mb>0 && _nb>0)
            {
                klab::UInt32 size = _countBlocks-1;
                for(klab::UInt32 i=0; i<size; ++i)
                    diagonal.push_back(new TVarianceShadowOperator<T, T, TOperator<T, T> >(new kl1p::TNormalRandomMatrixOperator<T>(_mb, _nb, klab::TTypeInfo<T>::ZERO, TSeedingOperatorSpecialisation<T>::GetSigma(_dVariance, m, n)), TSeedingOperatorSpecialisation<T>::GetVariance(_dVariance)));

                for(klab::UInt32 i=0; i<size; ++i)
                    lower.push_back(new TVarianceShadowOperator<T, T, TOperator<T, T> >(new kl1p::TNormalRandomMatrixOperator<T>(_mb, (i==0?_n0:_nb), klab::TTypeInfo<T>::ZERO, TSeedingOperatorSpecialisation<T>::GetSigma(_lVariance, m, n)), TSeedingOperatorSpecialisation<T>::GetVariance(_lVariance)));

                for(klab::UInt32 i=0; i<size; ++i)
                    upper.push_back(new TVarianceShadowOperator<T, T, TOperator<T, T> >(new kl1p::TNormalRandomMatrixOperator<T>((i==0?_m0:_mb), _nb, klab::TTypeInfo<T>::ZERO, TSeedingOperatorSpecialisation<T>::GetSigma(_uVariance, m, n)), TSeedingOperatorSpecialisation<T>::GetVariance(_uVariance)));
            }
            else
            {
                _countBlocks = 1;
            }

            this->setTridiagonalArrays(diagonal, lower, upper);
        }
        else
        {
            this->setTridiagonalArrays(typename TBlockTridiagonalOperator<T, T, TOperator<T, T> >::TOperatorArray(), typename TBlockTridiagonalOperator<T, T, TOperator<T, T> >::TOperatorArray(), typename TBlockTridiagonalOperator<T, T, TOperator<T, T> >::TOperatorArray());
            _countBlocks = 0;
        }
    }
    else
    {
        this->setTridiagonalArrays(typename TBlockTridiagonalOperator<T, T, TOperator<T, T> >::TOperatorArray(), typename TBlockTridiagonalOperator<T, T, TOperator<T, T> >::TOperatorArray(), typename TBlockTridiagonalOperator<T, T, TOperator<T, T> >::TOperatorArray());
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TSeedingOperatorSpecialisation<T>::GetSigma(const T& variance, klab::UInt32 m, klab::UInt32 n)
{
    T invN = klab::TTypeInfo<T>::UNIT / static_cast<T>(n);

    return klab::Sqrt(variance*invN);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TSeedingOperatorSpecialisation<T>::GetVariance(const T& variance)
{
    return variance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TSeedingOperatorSpecialisation<std::complex<T> >::GetSigma(const std::complex<T>& variance, klab::UInt32 m, klab::UInt32 n)
{
    T invN = klab::TTypeInfo<T>::UNIT / static_cast<T>(n);

    return std::complex<T>(klab::Sqrt(variance.real()*invN), klab::Sqrt(variance.imag()*invN));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TSeedingOperatorSpecialisation<std::complex<T> >::GetVariance(const std::complex<T>& variance)
{
    return (variance.real() + variance.imag());
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
