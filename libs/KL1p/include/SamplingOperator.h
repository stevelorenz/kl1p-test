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

#ifndef KL1P_SAMPLINGOPERATOR_H
#define KL1P_SAMPLINGOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

typedef std::vector<klab::UInt32>   KSamplingIndicesArray;

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TSamplingOperator : public TOperator<T, T>
{
public:
          
    TSamplingOperator(klab::UInt32 n, const kl1p::KSamplingIndicesArray& indices);
    TSamplingOperator(const TSamplingOperator<T>& op);
    virtual ~TSamplingOperator();    

    const kl1p::KSamplingIndicesArray&  indices() const;         

    virtual void                        apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void                        applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);

    virtual void                        column(klab::UInt32 i, arma::Col<T>& out);
    virtual void                        columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


protected:

    TSamplingOperator();
    TSamplingOperator(klab::UInt32 n);

    void                                set(klab::UInt32 n, const kl1p::KSamplingIndicesArray& indices);


private:

    TSamplingOperator<T>&               operator=(const TSamplingOperator<T>& op);


private:

    kl1p::KSamplingIndicesArray         _indices;
    kl1p::KSamplingIndicesArray         _dual;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSamplingOperator<T>::TSamplingOperator() : TOperator<T>(),
_indices(), _dual()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSamplingOperator<T>::TSamplingOperator(klab::UInt32 n) : TOperator<T>(n),
_indices(), _dual()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSamplingOperator<T>::TSamplingOperator(klab::UInt32 n, const kl1p::KSamplingIndicesArray& indices) : TOperator<T>(static_cast<klab::UInt32>(indices.size()), n),
_indices(indices), _dual(n, n)
{
    klab::UInt32 m = static_cast<klab::UInt32>(_indices.size());
    for(klab::UInt32 i=0; i<m; ++i)
    {
        klab::UInt32 index = _indices[i];
        if(index < n) 
            _dual[index] = i;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSamplingOperator<T>::TSamplingOperator(const TSamplingOperator<T>& op) : TOperator<T>(op),
_indices(op._indices), _dual(op._dual)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSamplingOperator<T>::~TSamplingOperator()
{}

// ---------------------------------------------------------------------------------------------------- //


template<class T>
inline void TSamplingOperator<T>::set(klab::UInt32 n, const kl1p::KSamplingIndicesArray& indices)
{
    _indices = indices;

    klab::UInt32 m = static_cast<klab::UInt32>(_indices.size());
    _dual.resize(n, n);

    for(klab::UInt32 i=0; i<m; ++i)
    {
        klab::UInt32 index = _indices[i];
        if(index < n) 
            _dual[index] = i;
    }

    this->resize(m, n);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const kl1p::KSamplingIndicesArray& TSamplingOperator<T>::indices() const
{
    return _indices;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TSamplingOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());   

    klab::UInt32 m = this->m();  
    klab::UInt32 n = this->n(); 

    if(m > 0)
    {
        out.set_size(m);        
        for(klab::UInt32 i=0; i<m; ++i)
        {
            klab::UInt32 index = _indices[i];
            if(index<n) out[i] = in[index];
            else        out[i] = klab::TTypeInfo<T>::ZERO;
        }
    }
    else
    {
        out.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TSamplingOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());   

    klab::UInt32 m = this->m(); 
    klab::UInt32 n = this->n(); 

    if(m > 0)
    {
        out.set_size(n);  
        out.fill(klab::TTypeInfo<T>::ZERO);

        for(klab::UInt32 i=0; i<m; ++i)
        {
            klab::UInt32 index = _indices[i];
            if(index < n)   
                out[index] = in[i];   
        }
    }
    else
    {
        out.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TSamplingOperator<T>::column(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    klab::UInt32 m = this->m(); 

    out.set_size(m);
    out.fill(klab::TTypeInfo<T>::ZERO);

    klab::UInt32 index = _dual[i];
    if(index < m)   
        out[index] = klab::TTypeInfo<T>::UNIT;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TSamplingOperator<T>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    klab::UInt32 n = this->n(); 

    out.set_size(n);
    out.fill(klab::TTypeInfo<T>::ZERO);

    klab::UInt32 index = _indices[i];
    if(index < n)   
        out[index] = klab::TTypeInfo<T>::UNIT;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
