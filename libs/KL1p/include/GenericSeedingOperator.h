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

#ifndef KL1P_GENERICSEEDINGOPERATOR_H
#define KL1P_GENERICSEEDINGOPERATOR_H

#include "BlockTridiagonalOperator.h"
#include "RandomPermutationOperator.h"
#include "RandomDownSamplingOperator.h"
#include "ScalingOperator.h"
#include "VarianceShadowOperator.h"
#include "MultiplicationOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TGenericSeedingOperator : public TBlockTridiagonalOperator<T, TOut, TOp>
{
public:
    
    TGenericSeedingOperator(klab::TSmartPointer<TOp> op, klab::UInt32 blocks, klab::UInt32 m0, klab::UInt32 mb, const T& diagVariance, const T& lowerVariance, const T& upperVariance); 
    TGenericSeedingOperator(const TGenericSeedingOperator<T, TOut, TOp>& op);
    virtual ~TGenericSeedingOperator();

    klab::UInt32                 countSeededBlocks() const;
    klab::UInt32                 m0() const;
    klab::UInt32                 mb() const;
    const T&                            diagonalVariance() const;
    const T&                            lowerVariance() const;
    const T&                            upperVariance() const;


protected:

    void    init(klab::TSmartPointer<TOp> op, klab::UInt32 blocks, klab::UInt32 m0, klab::UInt32 mb, const T& diagVariance, const T& lowerVariance, const T& upperVariance);


private:

    TGenericSeedingOperator();
    TGenericSeedingOperator<T, TOut, TOp>&	operator=(const TGenericSeedingOperator<T, TOut, TOp>& op);


private:

    klab::UInt32                        _countBlocks;
    klab::UInt32                        _m0;
    klab::UInt32                        _mb;

    T                                   _dVariance;
    T                                   _lVariance;
    T                                   _uVariance;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGenericSeedingOperatorSpecialisation
{
public:

    static T        GetVariance(const T& variance);


private:

    TGenericSeedingOperatorSpecialisation();
    TGenericSeedingOperatorSpecialisation(const TGenericSeedingOperatorSpecialisation<T>& spec);
    TGenericSeedingOperatorSpecialisation<T>&	operator=(const TGenericSeedingOperatorSpecialisation<T>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TGenericSeedingOperatorSpecialisation<std::complex<T> >
{
public:

    static std::complex<T>  GetVariance(const std::complex<T>& variance);


private:

    TGenericSeedingOperatorSpecialisation();
    TGenericSeedingOperatorSpecialisation(const TGenericSeedingOperatorSpecialisation<std::complex<T> >& spec);
    TGenericSeedingOperatorSpecialisation<std::complex<T> >&	operator=(const TGenericSeedingOperatorSpecialisation<std::complex<T> >& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TGenericSeedingOperator<T, TOut, TOp>::TGenericSeedingOperator(klab::TSmartPointer<TOp> op, klab::UInt32 blocks, klab::UInt32 m0, klab::UInt32 mb, const T& diagVariance, const T& lowerVariance, const T& upperVariance) : TBlockTridiagonalOperator<T, T, TOp>(),
_countBlocks(0), _m0(0), _mb(0), _dVariance(klab::TTypeInfo<T>::ZERO), _lVariance(klab::TTypeInfo<T>::ZERO), _uVariance(klab::TTypeInfo<T>::ZERO)
{
    this->init(op, blocks, m0, mb, diagVariance, lowerVariance, upperVariance);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TGenericSeedingOperator<T, TOut, TOp>::TGenericSeedingOperator(const TGenericSeedingOperator<T, TOut, TOp>& op) : TBlockTridiagonalOperator<T, T, TOp>(op),
_countBlocks(op._countBlocks), _m0(op._m0), _mb(op._mb), _dVariance(op._dVariance), _lVariance(op._lVariance), _uVariance(op._uVariance)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TGenericSeedingOperator<T, TOut, TOp>::~TGenericSeedingOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TGenericSeedingOperator<T, TOut, TOp>::countSeededBlocks() const
{
    return _countBlocks;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TGenericSeedingOperator<T, TOut, TOp>::m0() const
{
    return _m0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TGenericSeedingOperator<T, TOut, TOp>::mb() const
{
    return _mb;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline const T& TGenericSeedingOperator<T, TOut, TOp>::diagonalVariance() const
{
    return _dVariance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline const T& TGenericSeedingOperator<T, TOut, TOp>::lowerVariance() const
{
    return _lVariance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline const T& TGenericSeedingOperator<T, TOut, TOp>::upperVariance() const
{
    return _uVariance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TGenericSeedingOperator<T, TOut, TOp>::init(klab::TSmartPointer<TOp> op, klab::UInt32 blocks, klab::UInt32 m0, klab::UInt32 mb, const T& diagVariance, const T& lowerVariance, const T& upperVariance)
{
    _countBlocks = blocks;
    _m0 = m0;
    _mb = mb;
    _dVariance = diagVariance;
    _lVariance = lowerVariance;
    _uVariance = upperVariance;

    if(_countBlocks>0 && op!=0)
    {
        klab::UInt32 mOp = op->m();
        klab::UInt32 nOp = op->n();

        if(_m0>0 && nOp>0)
        {
            klab::UInt32 m = m0 + ((_countBlocks-1) * mb);   
            klab::UInt32 n = nOp * _countBlocks;  

            typename TBlockTridiagonalOperator<T, T, TOp>::TOperatorArray diagonal;
            typename TBlockTridiagonalOperator<T, T, TOp>::TOperatorArray lower;
            typename TBlockTridiagonalOperator<T, T, TOp>::TOperatorArray upper;

            klab::TSmartPointer<TOperator<T, TOut> > blockOp = new TScalingOperator<T, TOut, TOperator<T, TOut> >(klab::TSmartPointer<TOperator<T, TOut> >(new TRandomDownSamplingOperator<T>(_m0, mOp)) * klab::TSmartPointer<TOperator<T, TOut> >(new TRandomPermutationOperator<T>(mOp)) * klab::TSmartPointer<TOperator<T, TOut> >(op) * klab::TSmartPointer<TOperator<T, TOut> >(new TRandomPermutationOperator<T>(nOp)), klab::Sqrt(TGenericSeedingOperatorSpecialisation<T>::GetVariance(_dVariance)));
            diagonal.push_back(new TVarianceShadowOperator<T, T, TOp>(blockOp, TGenericSeedingOperatorSpecialisation<T>::GetVariance(_dVariance)));

            if(_countBlocks>1 && _mb>0)
            {
                klab::UInt32 size = _countBlocks-1;
                for(klab::UInt32 i=0; i<size; ++i)
                {
                    blockOp = new TScalingOperator<T, TOut, TOperator<T, TOut> >(klab::TSmartPointer<TOperator<T, TOut> >(new TRandomDownSamplingOperator<T>(_mb, mOp)) * klab::TSmartPointer<TOperator<T, TOut> >(new TRandomPermutationOperator<T>(mOp)) * klab::TSmartPointer<TOperator<T, TOut> >(op) * klab::TSmartPointer<TOperator<T, TOut> >(new TRandomPermutationOperator<T>(nOp)), klab::Sqrt(TGenericSeedingOperatorSpecialisation<T>::GetVariance(_dVariance)));
                    diagonal.push_back(new TVarianceShadowOperator<T, T, TOperator<T, T> >(blockOp, TGenericSeedingOperatorSpecialisation<T>::GetVariance(_dVariance)));
                }

                for(klab::UInt32 i=0; i<size; ++i)
                {
                    blockOp = new TScalingOperator<T, TOut, TOperator<T, TOut> >(klab::TSmartPointer<TOperator<T, TOut> >(new TRandomDownSamplingOperator<T>(_mb, mOp)) * klab::TSmartPointer<TOperator<T, TOut> >(new TRandomPermutationOperator<T>(mOp)) * klab::TSmartPointer<TOperator<T, TOut> >(op) * klab::TSmartPointer<TOperator<T, TOut> >(new TRandomPermutationOperator<T>(nOp)), klab::Sqrt(TGenericSeedingOperatorSpecialisation<T>::GetVariance(_lVariance)));
                    lower.push_back(new TVarianceShadowOperator<T, T, TOperator<T, T> >(blockOp, TGenericSeedingOperatorSpecialisation<T>::GetVariance(_lVariance)));
                }                    

                for(klab::UInt32 i=0; i<size; ++i)
                {
                    blockOp = new TScalingOperator<T, TOut, TOperator<T, TOut> >(klab::TSmartPointer<TOperator<T, TOut> >(new TRandomDownSamplingOperator<T>((i==0?_m0:_mb), mOp)) * klab::TSmartPointer<TOperator<T, TOut> >(new TRandomPermutationOperator<T>(mOp)) * klab::TSmartPointer<TOperator<T, TOut> >(op) * klab::TSmartPointer<TOperator<T, TOut> >(new TRandomPermutationOperator<T>(nOp)), klab::Sqrt(TGenericSeedingOperatorSpecialisation<T>::GetVariance(_uVariance)));
                    upper.push_back(new TVarianceShadowOperator<T, T, TOperator<T, T> >(blockOp, TGenericSeedingOperatorSpecialisation<T>::GetVariance(_uVariance)));
                }                     
            }
            else
            {
                _countBlocks = 1;
            }

            this->setTridiagonalArrays(diagonal, lower, upper);
        }
        else
        {
            _countBlocks = 0;
            this->setTridiagonalArrays(typename TBlockTridiagonalOperator<T, T, TOp>::TOperatorArray(), typename TBlockTridiagonalOperator<T, T, TOp>::TOperatorArray(), typename TBlockTridiagonalOperator<T, T, TOp>::TOperatorArray());
        }
    }
    else
    {
        _countBlocks = 0;
        this->setTridiagonalArrays(typename TBlockTridiagonalOperator<T, T, TOp>::TOperatorArray(), typename TBlockTridiagonalOperator<T, T, TOp>::TOperatorArray(), typename TBlockTridiagonalOperator<T, T, TOp>::TOperatorArray());
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TGenericSeedingOperatorSpecialisation<T>::GetVariance(const T& variance)
{
    return variance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::complex<T> TGenericSeedingOperatorSpecialisation<std::complex<T> >::GetVariance(const std::complex<T>& variance)
{
    return (variance.real() + variance.imag());
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
