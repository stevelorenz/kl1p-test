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

#ifndef KL1P_SUBSYSTEMOPERATOR_H
#define KL1P_SUBSYSTEMOPERATOR_H

#include "ProxyOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TSubSystemOperator : public TProxyOperator<T, TOut, TOp>
{
public:

    TSubSystemOperator(klab::TSmartPointer<TOp> op);
    TSubSystemOperator(klab::TSmartPointer<TOp> op, const std::vector<klab::UInt32>& indexes);
    TSubSystemOperator(const TSubSystemOperator<T, TOut, TOp>& op);
    virtual ~TSubSystemOperator();    
	
	const std::vector<klab::UInt32>& 	indexes() const;

    virtual void    apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void    applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);

    virtual void    column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void    columnAdjoint(klab::UInt32 i, arma::Col<T>& out);


private:

    TSubSystemOperator();
    TSubSystemOperator<T, TOut, TOp>&   operator=(const TSubSystemOperator<T, TOut, TOp>& op);


private:

	std::vector<klab::UInt32>	_indexes;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TSubSystemOperator<T, TOut, TOp>::TSubSystemOperator(klab::TSmartPointer<TOp> op) : TProxyOperator<T, TOut, TOp>(op),
_indexes()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TSubSystemOperator<T, TOut, TOp>::TSubSystemOperator(klab::TSmartPointer<TOp> op, const std::vector<klab::UInt32>& indexes) : TProxyOperator<T, TOut, TOp>(op!=0?op->m():0, static_cast<klab::UInt32>(indexes.size()), op),
_indexes(indexes)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TSubSystemOperator<T, TOut, TOp>::TSubSystemOperator(const TSubSystemOperator<T, TOut, TOp>& op) : TProxyOperator<T, TOut, TOp>(op),
_indexes(op._indexes)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TSubSystemOperator<T, TOut, TOp>::~TSubSystemOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline const std::vector<klab::UInt32>& TSubSystemOperator<T, TOut, TOp>::indexes() const
{
    return _indexes;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TSubSystemOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());   

    out.set_size(0);

    klab::UInt32 n = this->n();
    if(n > 0)
    {
        arma::Col<T> x(this->_op->n());  
        x.fill(klab::TTypeInfo<T>::ZERO);

        klab::UInt32 size = static_cast<klab::UInt32>(_indexes.size());
        for(klab::UInt32 i=0; i<in.n_rows && i<size; ++i)
        {
            klab::UInt32 index = _indexes[i];
            if(index < x.n_rows)
                x[index] = in[i];
        }

        this->_op->apply(x, out);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TSubSystemOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());   

    klab::UInt32 n = this->n();
    if(n > 0)
    {
        arma::Col<TOut> x;
        this->_op->applyAdjoint(in, x);

        out.set_size(n);    
        klab::UInt32 size = static_cast<klab::UInt32>(_indexes.size());
        for(klab::UInt32 i=0; i<out.n_rows && i<size; ++i)
        {
            klab::UInt32 index = _indexes[i];
            if(index < x.n_rows)    out[i] = x[index];
            else                    out[i] = klab::TTypeInfo<T>::ZERO;
        }
    }
    else
    {
        out.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TSubSystemOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{    
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    klab::UInt32 n = this->n();
    if(n > 0)
    {
        klab::UInt32 index = _indexes[i];
        if(index < this->_op->n())
        {
            this->_op->column(index, out);
        }
        else  
        {
            out.set_size(this->m()); 
            out.fill(klab::TTypeInfo<TOut>::ZERO);
        }
    }
    else
    {
        out.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TSubSystemOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, this->_op==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    klab::UInt32 n = this->n();
    if(n > 0)
    {
        arma::Col<TOut> x(n);
        this->_op->columnAdjoint(i, x);

        out.set_size(n);   
        klab::UInt32 size = static_cast<klab::UInt32>(_indexes.size());
        for(klab::UInt32 i=0; i<out.n_rows && i<size; ++i)
        {
            klab::UInt32 index = _indexes[i];
            if(index < x.n_rows)    out[i] = x[index];
            else                    out[i] = klab::TTypeInfo<T>::ZERO;
        }
    }
    else
    {
        out.set_size(0);
    }    
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
