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

#ifndef KL1P_COLUMNJOINTOPERATOR_H
#define KL1P_COLUMNJOINTOPERATOR_H

#include "BlockOperator.h"
#include "ResizingOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TColumnJointOperator : public TBlockOperator<T, TOut, TOp>  
{
public:

	typedef std::vector<klab::TSmartPointer<TOp> >	TOperatorArray;
	
	
public:
      
	TColumnJointOperator(klab::TSmartPointer<TOp> op);
	TColumnJointOperator(klab::TSmartPointer<TOp> op1, klab::TSmartPointer<TOp> op2);
	TColumnJointOperator(klab::TSmartPointer<TOp> op1, klab::TSmartPointer<TOp> op2, klab::TSmartPointer<TOp> op3);
    TColumnJointOperator(const typename TColumnJointOperator<T, TOut, TOp>::TOperatorArray& ops);
    TColumnJointOperator(const TColumnJointOperator<T, TOut, TOp>& op);
    virtual ~TColumnJointOperator();   

	virtual bool                        isZero();
	virtual klab::UInt32                countBlockRows() const;
    virtual klab::UInt32                countBlockColumns() const;
    virtual klab::TSmartPointer<TOp>    block(klab::UInt32 i, klab::UInt32 j) const;
    virtual bool                        isZeroBlock(klab::UInt32 i, klab::UInt32 j) const;
    virtual klab::TSmartPointer<TOp>    inBlock(klab::UInt32 i, klab::UInt32 j) const;  

    virtual void				        apply(const arma::Col<T>& in, arma::Col<TOut>& out);
    virtual void				        applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out);
    virtual void				        column(klab::UInt32 i, arma::Col<TOut>& out);
    virtual void				        columnAdjoint(klab::UInt32 i, arma::Col<T>& out);

    virtual void                        applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void                        applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


protected:

    void                                updateVarianceMatrix();


private:

    TColumnJointOperator();
    TColumnJointOperator<T, TOut, TOp>& operator=(const TColumnJointOperator<T, TOut, TOp>& op);


private:

    typename TColumnJointOperator<T, TOut, TOp>::TOperatorArray   _operators;

    arma::Col<T>                        _variances;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TColumnJointOperator<T, TOut, TOp>::TColumnJointOperator(klab::TSmartPointer<TOp> op) : TBlockOperator<T, TOut, TOp>(op!=0?op->m():0, op!=0?op->n():0),
_operators(),
_variances()
{
    if(op != 0)
        _operators.push_back(op);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TColumnJointOperator<T, TOut, TOp>::TColumnJointOperator(klab::TSmartPointer<TOp> op1, klab::TSmartPointer<TOp> op2) : TBlockOperator<T, TOut, TOp>(),
_operators(),
_variances()
{
    klab::UInt32 m = (op1!=0?op1->m():0) + (op2!=0?op2->m():0);
    klab::UInt32 n = klab::Max(op1!=0?op1->n():0, op2!=0?op2->n():0);
    this->resize(m, n);

    if(op1 != 0)
        _operators.push_back(op1->n()==n ? op1 : new TResizingOperator<T, TOut, TOp>(op1->m(), n, op1));

    if(op2 != 0)
        _operators.push_back(op2->n()==n ? op2 : new TResizingOperator<T, TOut, TOp>(op2->m(), n, op2));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TColumnJointOperator<T, TOut, TOp>::TColumnJointOperator(klab::TSmartPointer<TOp> op1, klab::TSmartPointer<TOp> op2, klab::TSmartPointer<TOp> op3) : TBlockOperator<T, TOut, TOp>(),
_operators(),
_variances()
{
    klab::UInt32 m = (op1!=0?op1->m():0) + (op2!=0?op2->m():0) + (op3!=0?op3->m():0);
    klab::UInt32 n = klab::Max(klab::Max(op1!=0?op1->n():0, op2!=0?op2->n():0), op3!=0?op3->n():0);
    this->resize(m, n);

    if(op1 != 0)
        _operators.push_back(op1->n()==n ? op1 : new TResizingOperator<T, TOut, TOp>(op1->m(), n, op1));

    if(op2 != 0)
        _operators.push_back(op2->n()==n ? op2 : new TResizingOperator<T, TOut, TOp>(op2->m(), n, op2));

    if(op3 != 0)
        _operators.push_back(op3->n()==n ? op3 : new TResizingOperator<T, TOut, TOp>(op3->m(), n, op3));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TColumnJointOperator<T, TOut, TOp>::TColumnJointOperator(const typename TColumnJointOperator<T, TOut, TOp>::TOperatorArray& ops) : TBlockOperator<T, TOut, TOp>(),
_operators(),
_variances()
{
    klab::UInt32 m = 0;
    klab::UInt32 n = 0;

    klab::UInt32 size = static_cast<klab::UInt32>(ops.size());
    for(klab::UInt32 i=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = ops[i];
        if(op != 0)
        {
            m += op->m();
            n  = klab::Max(n, op->n());
        }
    }

    this->resize(m, n);
    
    for(klab::UInt32 i=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = ops[i];
        if(op != 0)
            _operators.push_back(op->n()==n ? op : new TResizingOperator<T, TOut, TOp>(op->m(), n, op));  
    } 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TColumnJointOperator<T, TOut, TOp>::TColumnJointOperator(const TColumnJointOperator<T, TOut, TOp>& op) : TBlockOperator<T, TOut, TOp>(op),
_operators(op._operators),
_variances(op._variances)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TColumnJointOperator<T, TOut, TOp>::~TColumnJointOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline bool TColumnJointOperator<T, TOut, TOp>::isZero()
{
    bool ret = true;
    
    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 i=0; i<size && ret; ++i)
        ret = _operators[i]->isZero();

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TColumnJointOperator<T, TOut, TOp>::countBlockRows() const
{
    return static_cast<klab::UInt32>(_operators.size());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TColumnJointOperator<T, TOut, TOp>::countBlockColumns() const
{
    return (_operators.size()>0 ? 1 : 0);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TColumnJointOperator<T, TOut, TOp>::block(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    return _operators[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline bool TColumnJointOperator<T, TOut, TOp>::isZeroBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    return _operators[i]->isZero();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TColumnJointOperator<T, TOut, TOp>::inBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m() || j>=this->n());    

    klab::UInt32 m = this->countBlockRows();

    klab::UInt32 s = 0;
    bool found = false;
    klab::UInt32 ib = 0;
    for(; ib<m && found==false; ++ib)
    {
        s += _operators[ib]->m();
        found = (i<s);       
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);

    return _operators[ib-1];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TColumnJointOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 i=0, k=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _operators[i];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(op->isZero() == false)
        {
            arma::Col<TOut> subOut;
            op->apply(in, subOut);

            for(klab::UInt32 j=0; j<subOut.n_rows; ++j, ++k)
                out[k] = subOut[j];
        }
        else
        {
            k += op->m();
        }
    }    
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TColumnJointOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<T>::ZERO);

    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 i=0, k=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _operators[i];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(op->isZero() == false)
        {
            arma::Col<TOut> subIn(op->m());
            for(klab::UInt32 j=0; j<subIn.n_rows; ++j, ++k)
                subIn[j] = in[k];

            arma::Col<T> subOut;
            op->applyAdjoint(subIn, subOut);

            for(klab::UInt32 j=0; j<subOut.n_rows; ++j)
                out[j] += subOut[j];
        }
        else
        {
            k += op->m();
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TColumnJointOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n()); 

    out.set_size(this->m());

    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 j=0, k=0; j<size; ++j)
    {
        klab::TSmartPointer<TOp> op = _operators[j];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        arma::Col<TOut> subCol;
        op->column(i, subCol);

        for(klab::UInt32 l=0; l<subCol.n_rows; ++l, ++k)
            out[k] = subCol[l];
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TColumnJointOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    bool found = false;
    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 j=0, k=0; j<size && found==false; ++j)
    {
         klab::TSmartPointer<TOp> op = _operators[j];
         ThrowTraceExceptionIf(KNullOperatorException, op==0);

         if(i < (k+op->m()))  
         {
             op->columnAdjoint(i-k, out);
             found = true;
         }
         else
         {
             k += op->m();
         }
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TColumnJointOperator<T, TOut, TOp>::applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockColumns()); 

    if(_variances.n_rows == 0)
        this->updateVarianceMatrix();

    klab::UInt32 n = static_cast<klab::UInt32>(_operators.size());

    out.set_size(n);
    for(klab::UInt32 i=0; i<n; ++i)
        out[i] = in[0] * _variances[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TColumnJointOperator<T, TOut, TOp>::applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockRows()); 

    if(_variances.n_rows == 0)
        this->updateVarianceMatrix();

    klab::UInt32 n = static_cast<klab::UInt32>(_operators.size());

    out.set_size(1);
    out[0] = klab::TTypeInfo<T>::ZERO;
    for(klab::UInt32 i=0; i<n; ++i)
        out[0] += in[i] * _variances[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TColumnJointOperator<T, TOut, TOp>::updateVarianceMatrix()
{
    klab::UInt32 n = static_cast<klab::UInt32>(_operators.size());

    _variances.set_size(n);
    for(klab::UInt32 i=0; i<n; ++i)
    {
        klab::TSmartPointer<TOp> op = _operators[i];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        _variances[i] = op->variance();
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
