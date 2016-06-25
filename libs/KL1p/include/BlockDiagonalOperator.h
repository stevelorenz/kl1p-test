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

#ifndef KL1P_BLOCKDIAGONALOPERATOR_H
#define KL1P_BLOCKDIAGONALOPERATOR_H

#include "BlockOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TBlockDiagonalOperator : public TBlockOperator<T, TOut, TOp>
{
public:

	typedef std::vector<klab::TSmartPointer<TOp> >	TOperatorArray;
	
	
public:
      
	TBlockDiagonalOperator(klab::TSmartPointer<TOp> op);
	TBlockDiagonalOperator(klab::TSmartPointer<TOp> op1, klab::TSmartPointer<TOp> op2);
	TBlockDiagonalOperator(klab::TSmartPointer<TOp> op1, klab::TSmartPointer<TOp> op2, klab::TSmartPointer<TOp> op3);
    TBlockDiagonalOperator(const typename TBlockDiagonalOperator<T, TOut, TOp>::TOperatorArray& ops);
    TBlockDiagonalOperator(const TBlockDiagonalOperator<T, TOut, TOp>& op);
    virtual ~TBlockDiagonalOperator(); 

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

    TBlockDiagonalOperator();
    TBlockDiagonalOperator<T, TOut, TOp>&	operator=(const TBlockDiagonalOperator<T, TOut, TOp>& op);


private:

    typename TBlockDiagonalOperator<T, TOut, TOp>::TOperatorArray   _operators;

    arma::Col<T>                        _variances;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockDiagonalOperator<T, TOut, TOp>::TBlockDiagonalOperator(klab::TSmartPointer<TOp> op) : TBlockOperator<T, TOut, TOp>(op!=0?op->m():0, op!=0?op->n():0),
_operators(),
_variances()
{
    if(op != 0)
        _operators.push_back(op);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockDiagonalOperator<T, TOut, TOp>::TBlockDiagonalOperator(klab::TSmartPointer<TOp> op1, klab::TSmartPointer<TOp> op2) : TBlockOperator<T, TOut, TOp>(),
_operators(),
_variances()
{
    klab::UInt32 m = (op1!=0?op1->m():0) + (op2!=0?op2->m():0);
    klab::UInt32 n = (op1!=0?op1->n():0) + (op2!=0?op2->n():0);
    this->resize(m, n);

    if(op1 != 0)
        _operators.push_back(op1);

    if(op2 != 0)
        _operators.push_back(op2);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockDiagonalOperator<T, TOut, TOp>::TBlockDiagonalOperator(klab::TSmartPointer<TOp> op1, klab::TSmartPointer<TOp> op2, klab::TSmartPointer<TOp> op3) : TBlockOperator<T, TOut, TOp>(),
_operators(),
_variances()
{
    klab::UInt32 m = (op1!=0?op1->m():0) + (op2!=0?op2->m():0) + (op3!=0?op3->m():0);
    klab::UInt32 n = (op1!=0?op1->n():0) + (op2!=0?op2->n():0) + (op3!=0?op3->n():0);
    this->resize(m, n);

    if(op1 != 0)
        _operators.push_back(op1);

    if(op2 != 0)
        _operators.push_back(op2);

    if(op3 != 0)
        _operators.push_back(op3);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockDiagonalOperator<T, TOut, TOp>::TBlockDiagonalOperator(const typename TBlockDiagonalOperator<T, TOut, TOp>::TOperatorArray& ops) : TBlockOperator<T, TOut, TOp>(),
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
            n += op->n();

            _operators.push_back(op);            
        }
    }

    this->resize(m, n);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockDiagonalOperator<T, TOut, TOp>::TBlockDiagonalOperator(const TBlockDiagonalOperator<T, TOut, TOp>& op) : TBlockOperator<T, TOut, TOp>(op),
_operators(op._operators),
_variances(op._variances)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockDiagonalOperator<T, TOut, TOp>::~TBlockDiagonalOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline bool TBlockDiagonalOperator<T, TOut, TOp>::isZero()
{
    bool ret = true;
    
    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 i=0; i<size && ret; ++i)
        ret = _operators[i]->isZero();

    return ret;
}


// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TBlockDiagonalOperator<T, TOut, TOp>::countBlockRows() const
{
    return static_cast<klab::UInt32>(_operators.size());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TBlockDiagonalOperator<T, TOut, TOp>::countBlockColumns() const
{
    return static_cast<klab::UInt32>(_operators.size());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TBlockDiagonalOperator<T, TOut, TOp>::block(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    if(i==j)    return _operators[i];
    else        return new kl1p::TZeroOperator<T>(_operators[i]->m(), _operators[j]->n());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline bool TBlockDiagonalOperator<T, TOut, TOp>::isZeroBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    return (i!=j || _operators[i]->isZero());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TBlockDiagonalOperator<T, TOut, TOp>::inBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m() || j>=this->n());    

    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();

    klab::UInt32 s = 0;
    bool found = false;
    klab::UInt32 ib = 0;
    for(; ib<m && found==false; ++ib)
    {
        s += _operators[ib]->m();
        found = (i<s);       
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);

    s = 0;
    found = false;
    klab::UInt32 jb = 0;
    for(; jb<n && found==false; ++jb)
    {
        s += _operators[jb]->n();
        found = (j<s);       
    }

    ThrowTraceExceptionIf(KDefectOperatorException, found==false);

    return this->block(ib-1, jb-1);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockDiagonalOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 i=0, km=0, kn=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _operators[i];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(op->isZero() == false)
        {
            arma::Col<T> subIn(op->n());
            for(klab::UInt32 j=0; j<subIn.n_rows; ++j, ++kn)
                subIn[j] = in[kn];

            arma::Col<TOut> subOut;
            op->apply(subIn, subOut);

            for(klab::UInt32 j=0; j<subOut.n_rows; ++j, ++km)
                out[km] = subOut[j];
        }
        else
        {
            km += op->m();
            kn += op->n();
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockDiagonalOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 i=0, km=0, kn=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _operators[i];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(op->isZero() == false)
        {
            arma::Col<TOut> subIn(op->m());
            for(klab::UInt32 j=0; j<subIn.n_rows; ++j, ++km)
                subIn[j] = in[km];

            arma::Col<T> subOut;
            op->applyAdjoint(subIn, subOut);

            for(klab::UInt32 j=0; j<subOut.n_rows; ++j, ++kn)
                out[kn] = subOut[j];
        }
        else
        {
            km += op->m();
            kn += op->n();
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockDiagonalOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    bool found = false;
    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 j=0, km=0, kn=0; j<size && found==false; ++j)
    {
         klab::TSmartPointer<TOp> op = _operators[j];
         ThrowTraceExceptionIf(KNullOperatorException, op==0);

         if(i < (kn+op->n()))  
         {
            arma::Col<TOut> subOut;
            op->column(i-kn, subOut);
            found = true;

            for(klab::UInt32 l=0; l<subOut.n_rows && (km+l)<out.n_rows; ++l)
                out[km+l] = subOut[l];
         }
         else
         {
             km += op->m();
             kn += op->n();
         }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockDiagonalOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    bool found = false;
    klab::UInt32 size = static_cast<klab::UInt32>(_operators.size());
    for(klab::UInt32 j=0, km=0, kn=0; j<size && found==false; ++j)
    {
         klab::TSmartPointer<TOp> op = _operators[j];
         ThrowTraceExceptionIf(KNullOperatorException, op==0);

         if(i < (km+op->m()))  
         {
            arma::Col<T> subOut;
            op->columnAdjoint(i-km, subOut);
            found = true;

            for(klab::UInt32 l=0; l<subOut.n_rows && (kn+l)<out.n_rows; ++l)
                out[kn+l] = subOut[l];
         }
         else
         {
             km += op->m();
             kn += op->n();
         }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockDiagonalOperator<T, TOut, TOp>::applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockColumns()); 

    if(_variances.n_rows == 0)
        this->updateVarianceMatrix();

    klab::UInt32 n = static_cast<klab::UInt32>(_operators.size());

    out.set_size(n);
    for(klab::UInt32 i=0; i<n; ++i)
        out[i] = in[i] * _variances[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockDiagonalOperator<T, TOut, TOp>::applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _operators.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockRows()); 

    if(_variances.n_rows == 0)
        this->updateVarianceMatrix();

    klab::UInt32 n = static_cast<klab::UInt32>(_operators.size());

    out.set_size(n);
    for(klab::UInt32 i=0; i<n; ++i)
        out[i] = in[i] * _variances[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockDiagonalOperator<T, TOut, TOp>::updateVarianceMatrix()
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
