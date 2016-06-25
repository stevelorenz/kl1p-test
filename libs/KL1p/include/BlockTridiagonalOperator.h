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

#ifndef KL1P_BLOCKTRIDIAGONALOPERATOR_H
#define KL1P_BLOCKTRIDIAGONALOPERATOR_H

#include "BlockOperator.h"
#include "ResizingOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=TOperator<T, TOut> >
class TBlockTridiagonalOperator : public TBlockOperator<T, TOut, TOp>
{
public:

	typedef std::vector<klab::TSmartPointer<TOp> >	TOperatorArray;
	
	
public:
      
    TBlockTridiagonalOperator(const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& diagonal, const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& lower, const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& upper);
    TBlockTridiagonalOperator(const TBlockTridiagonalOperator<T, TOut, TOp>& op);
    virtual ~TBlockTridiagonalOperator(); 

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

    TBlockTridiagonalOperator();

    void                                setTridiagonalArrays(const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& diagonal, const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& lower, const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& upper);
    void                                updateVarianceMatrix();


private:

    TBlockTridiagonalOperator<T, TOut, TOp>&    operator=(const TBlockTridiagonalOperator<T, TOut, TOp>& op);


private:

    typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray    _diagonal;
    typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray    _lower;
    typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray    _upper;

    arma::Col<T>                        _varianceDiagonal;
    arma::Col<T>                        _varianceLower;
    arma::Col<T>                        _varianceUpper;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockTridiagonalOperator<T, TOut, TOp>::TBlockTridiagonalOperator() : TBlockOperator<T, TOut, TOp>(),
_diagonal(), _lower(), _upper(),
_varianceDiagonal(), _varianceLower(), _varianceUpper()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockTridiagonalOperator<T, TOut, TOp>::TBlockTridiagonalOperator(const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& diagonal, const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& lower, const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& upper) : TBlockOperator<T, TOut, TOp>(),
_diagonal(), _lower(), _upper(),
_varianceDiagonal(), _varianceLower(), _varianceUpper()
{
    this->setTridiagonalArrays(diagonal, lower, upper);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockTridiagonalOperator<T, TOut, TOp>::TBlockTridiagonalOperator(const TBlockTridiagonalOperator<T, TOut, TOp>& op) : TBlockOperator<T, TOut, TOp>(op),
_diagonal(op._diagonal), _lower(op._lower), _upper(op._upper),
_varianceDiagonal(op._varianceDiagonal), _varianceLower(op._varianceLower), _varianceUpper(op._varianceUpper)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TBlockTridiagonalOperator<T, TOut, TOp>::~TBlockTridiagonalOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline bool TBlockTridiagonalOperator<T, TOut, TOp>::isZero()
{
    bool ret = true;
    
    klab::UInt32 size = static_cast<klab::UInt32>(_diagonal.size());
    for(klab::UInt32 i=0; i<size && ret; ++i)
        ret = _diagonal[i]->isZero();

    size = static_cast<klab::UInt32>(_lower.size());
    for(klab::UInt32 i=0; i<size && ret; ++i)
        ret = _lower[i]->isZero();

    size = static_cast<klab::UInt32>(_upper.size());
    for(klab::UInt32 i=0; i<size && ret; ++i)
        ret = _upper[i]->isZero();

    return ret;
}


// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TBlockTridiagonalOperator<T, TOut, TOp>::countBlockRows() const
{
    return static_cast<klab::UInt32>(_diagonal.size());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TBlockTridiagonalOperator<T, TOut, TOp>::countBlockColumns() const
{
    return static_cast<klab::UInt32>(_diagonal.size());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TBlockTridiagonalOperator<T, TOut, TOp>::block(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _diagonal.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    if(i==j)        return _diagonal[i];
    else if(i==j+1) return _lower[j]; 
    else if(i+1==j) return _upper[i]; 
    else            return new kl1p::TZeroOperator<T>(_diagonal[i]->m(), _diagonal[j]->n());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline bool TBlockTridiagonalOperator<T, TOut, TOp>::isZeroBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _diagonal.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    if(i==j)        return _diagonal[i]->isZero();
    else if(i==j+1) return _lower[j]->isZero(); 
    else if(i+1==j) return _upper[i]->isZero(); 
    else            return true;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TBlockTridiagonalOperator<T, TOut, TOp>::inBlock(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _diagonal.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m() || j>=this->n());    

    return TBlockOperator<T, TOut, TOp>::inBlock(i, j);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockTridiagonalOperator<T, TOut, TOp>::apply(const arma::Col<T>& in, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _diagonal.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    klab::UInt32 size = static_cast<klab::UInt32>(_diagonal.size());
    for(klab::UInt32 i=0, km=0, kn=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _diagonal[i];
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

    size = static_cast<klab::UInt32>(_lower.size());
    for(klab::UInt32 i=0, km=_diagonal[0]->m(), kn=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _lower[i];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(op->isZero() == false)
        {
            arma::Col<T> subIn(op->n());
            for(klab::UInt32 j=0; j<subIn.n_rows; ++j, ++kn)
                subIn[j] = in[kn];

            arma::Col<TOut> subOut;
            op->apply(subIn, subOut);

            for(klab::UInt32 j=0; j<subOut.n_rows; ++j, ++km)
                out[km] += subOut[j];
        }
        else
        {
            km += op->m();
            kn += op->n();
        }
    }

    size = static_cast<klab::UInt32>(_upper.size());
    for(klab::UInt32 i=0, km=0, kn=_diagonal[0]->n(); i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _upper[i];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(op->isZero() == false)
        {
            arma::Col<T> subIn(op->n());
            for(klab::UInt32 j=0; j<subIn.n_rows; ++j, ++kn)
                subIn[j] = in[kn];

            arma::Col<TOut> subOut;
            op->apply(subIn, subOut);

            for(klab::UInt32 j=0; j<subOut.n_rows; ++j, ++km)
                out[km] += subOut[j];
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
inline void TBlockTridiagonalOperator<T, TOut, TOp>::applyAdjoint(const arma::Col<TOut>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _diagonal.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m()); 

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    klab::UInt32 size = static_cast<klab::UInt32>(_diagonal.size());
    for(klab::UInt32 i=0, km=0, kn=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _diagonal[i];
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

    size = static_cast<klab::UInt32>(_lower.size());
    for(klab::UInt32 i=0, km=_diagonal[0]->m(), kn=0; i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _lower[i];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(op->isZero() == false)
        {
            arma::Col<TOut> subIn(op->m());
            for(klab::UInt32 j=0; j<subIn.n_rows; ++j, ++km)
                subIn[j] = in[km];

            arma::Col<T> subOut;
            op->applyAdjoint(subIn, subOut);

            for(klab::UInt32 j=0; j<subOut.n_rows; ++j, ++kn)
                out[kn] += subOut[j];
        }
        else
        {
            km += op->m();
            kn += op->n();
        }
    }

    size = static_cast<klab::UInt32>(_upper.size());
    for(klab::UInt32 i=0, km=0, kn=_diagonal[0]->n(); i<size; ++i)
    {
        klab::TSmartPointer<TOp> op = _upper[i];
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        if(op->isZero() == false)
        {
            arma::Col<TOut> subIn(op->m());
            for(klab::UInt32 j=0; j<subIn.n_rows; ++j, ++km)
                subIn[j] = in[km];

            arma::Col<T> subOut;
            op->applyAdjoint(subIn, subOut);

            for(klab::UInt32 j=0; j<subOut.n_rows; ++j, ++kn)
                out[kn] += subOut[j];
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
inline void TBlockTridiagonalOperator<T, TOut, TOp>::column(klab::UInt32 i, arma::Col<TOut>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _diagonal.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n()); 

    out.set_size(this->m());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    bool found = false;
    klab::UInt32 size = static_cast<klab::UInt32>(_diagonal.size());
    for(klab::UInt32 j=0, km=0, kn=0; j<size && found==false; ++j)
    {
         klab::TSmartPointer<TOp> op = _diagonal[j];
         ThrowTraceExceptionIf(KNullOperatorException, op==0);

         if(i < (kn+op->n()))  
         {
            found = true;    

            arma::Col<TOut> subOut;
            op->column(i-kn, subOut);
            for(klab::UInt32 l=0; l<subOut.n_rows && (km+l)<out.n_rows; ++l)
                out[km+l] = subOut[l];

            if(j < (size-1))
            {
                klab::Int32 km2 = km + op->m();
                _lower[j]->column(i-kn, subOut);
                for(klab::UInt32 l=0; l<subOut.n_rows && (km2+l)<out.n_rows; ++l)
                    out[km2+l] = subOut[l];
            }

            if(j > 0)
            {
                klab::Int32 km3 = km - _diagonal[j-1]->m();
                _upper[j-1]->column(i-kn, subOut);
                for(klab::UInt32 l=0; l<subOut.n_rows && (km3+l)<out.n_rows; ++l)
                    out[km3+l] = subOut[l];
            }
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
inline void TBlockTridiagonalOperator<T, TOut, TOp>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _diagonal.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    out.set_size(this->n());
    out.fill(klab::TTypeInfo<TOut>::ZERO);

    bool found = false;
    klab::UInt32 size = static_cast<klab::UInt32>(_diagonal.size());
    for(klab::UInt32 j=0, km=0, kn=0; j<size && found==false; ++j)
    {
         klab::TSmartPointer<TOp> op = _diagonal[j];
         ThrowTraceExceptionIf(KNullOperatorException, op==0);

         if(i < (km+op->m()))  
         {
            found = true;    

            arma::Col<TOut> subOut;
            op->columnAdjoint(i-km, subOut);
            for(klab::UInt32 l=0; l<subOut.n_rows && (kn+l)<out.n_rows; ++l)
                out[kn+l] = subOut[l];

            if(j > 0)
            {
                klab::Int32 kn2 = kn  - _diagonal[j-1]->n();
                _lower[j-1]->columnAdjoint(i-km, subOut);
                for(klab::UInt32 l=0; l<subOut.n_rows && (kn2+l)<out.n_rows; ++l)
                    out[kn2+l] = subOut[l];
            }

            if(j < (size-1))
            {
                klab::Int32 kn3 = kn + op->n();
                _upper[j]->columnAdjoint(i-km, subOut);
                for(klab::UInt32 l=0; l<subOut.n_rows && (kn3+l)<out.n_rows; ++l)
                    out[kn3+l] = subOut[l];
            }
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
inline void TBlockTridiagonalOperator<T, TOut, TOp>::applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _diagonal.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockColumns()); 

    if(_varianceDiagonal.n_rows == 0)
        this->updateVarianceMatrix();

    out.set_size(this->countBlockRows());
    if(in.n_rows > 1)
    {
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
        {
            if(i==0)                    out[i] = (_varianceDiagonal[i]*in[i]) + (_varianceUpper[i]*in[i+1]);
            else if(i>=(in.n_rows-1))   out[i] = (_varianceLower[i]*in[i-1]) + (_varianceDiagonal[i]*in[i]);
            else                        out[i] = (_varianceLower[i]*in[i-1]) + (_varianceDiagonal[i]*in[i]) + (_varianceUpper[i]*in[i+1]);
        }
    }
    else if(in.n_rows == 1)
    {
        out[0] = _varianceDiagonal[0] * in[0];
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockTridiagonalOperator<T, TOut, TOp>::applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _diagonal.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockRows()); 

    if(_varianceDiagonal.n_rows == 0)
        this->updateVarianceMatrix();

    out.set_size(this->countBlockRows());
    if(in.n_rows > 1)
    {
        for(klab::UInt32 i=0; i<out.n_rows; ++i)
        {
            if(i==0)                    out[i] = (_varianceDiagonal[i]*in[i]) + (_varianceLower[i+1]*in[i+1]);
            else if(i>=(in.n_rows-1))   out[i] = (_varianceUpper[i-1]*in[i-1]) + (_varianceDiagonal[i]*in[i]);
            else                        out[i] = (_varianceUpper[i-1]*in[i-1]) + (_varianceDiagonal[i]*in[i]) + (_varianceLower[i+1]*in[i+1]);
        }
    }
    else if(in.n_rows == 1)
    {
        out[0] = _varianceDiagonal[0] * in[0];
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockTridiagonalOperator<T, TOut, TOp>::setTridiagonalArrays(const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& diagonal, const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& lower, const typename TBlockTridiagonalOperator<T, TOut, TOp>::TOperatorArray& upper)
{
    _diagonal.clear();
    _lower.clear();
    _upper.clear();

    if(diagonal.size() > 0)
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;

        std::vector<klab::UInt32> rowSizes;
        std::vector<klab::UInt32> colSizes;

        klab::UInt32 size = static_cast<klab::UInt32>(diagonal.size());
        for(klab::UInt32 i=0; i<size; ++i)
        {        
            klab::TSmartPointer<TOp> op = diagonal[i];
            if(op != 0)
            {
                rowSizes.push_back(op->m());
                colSizes.push_back(op->n());
            }
        }

        size = klab::Min(static_cast<klab::UInt32>(diagonal.size()), static_cast<klab::UInt32>(lower.size()));
        for(klab::UInt32 i=0; i<size; ++i)
        {        
            klab::TSmartPointer<TOp> op = lower[i];
            if(op != 0)
            {
                rowSizes[i+1] = klab::Max(rowSizes[i+1], op->m());
                colSizes[i]   = klab::Max(colSizes[i], op->n());
            }
        }

        size = klab::Min(static_cast<klab::UInt32>(diagonal.size()), static_cast<klab::UInt32>(upper.size()));
        for(klab::UInt32 i=0; i<size; ++i)
        {        
            klab::TSmartPointer<TOp> op = upper[i];
            if(op != 0)
            {
                rowSizes[i]   = klab::Max(rowSizes[i], op->m());
                colSizes[i+1] = klab::Max(colSizes[i+1], op->n());
            }
        }

        
        for(klab::UInt32 i=0; i<static_cast<klab::UInt32>(rowSizes.size()); ++i)
            m += rowSizes[i];

        for(klab::UInt32 i=0; i<static_cast<klab::UInt32>(colSizes.size()); ++i)
            n += colSizes[i];

        this->resize(m, n);


        size = static_cast<klab::UInt32>(diagonal.size());
        for(klab::UInt32 i=0; i<size; ++i)
        {
            if(rowSizes[i]>0 && colSizes[i]>0)
            {
                klab::TSmartPointer<TOp> op = diagonal[i];
                if(op!=0)   _diagonal.push_back((op->m()==rowSizes[i] && op->n()==colSizes[i]) ? op : new kl1p::TResizingOperator<T, TOut, TOp>(rowSizes[i], colSizes[i], op));  
                else        _diagonal.push_back(new kl1p::TZeroOperator<T>(rowSizes[i], colSizes[i]));
            }
        }

        klab::UInt32 diagSize = static_cast<klab::UInt32>(_diagonal.size());
        if(diagSize > 0)
        {
            size = klab::Min(diagSize-1, static_cast<klab::UInt32>(lower.size()));
            for(klab::UInt32 i=0; i<size; ++i)
            {
                if(rowSizes[i+1]>0 && colSizes[i]>0)
                {
                    klab::TSmartPointer<TOp> op = lower[i];
                    if(op!=0)   _lower.push_back((op->m()==rowSizes[i+1] && op->n()==colSizes[i]) ? op : new kl1p::TResizingOperator<T, TOut, TOp>(rowSizes[i+1], colSizes[i], op));    
                    else        _lower.push_back(new kl1p::TZeroOperator<T>(rowSizes[i+1], colSizes[i]));
                }
            }

            for(klab::UInt32 i=size; i<diagSize-1; ++i)
            {
                if(rowSizes[i+1]>0 && colSizes[i]>0)    
                    _lower.push_back(new kl1p::TZeroOperator<T>(rowSizes[i+1], colSizes[i]));
            }


            size = klab::Min(diagSize-1, static_cast<klab::UInt32>(upper.size()));
            for(klab::UInt32 i=0; i<size; ++i)
            {
                if(rowSizes[i]>0 && colSizes[i+1]>0)
                {
                    klab::TSmartPointer<TOp> op = upper[i];
                    if(op!=0)   _upper.push_back((op->m()==rowSizes[i] && op->n()==colSizes[i+1]) ? op : new kl1p::TResizingOperator<T, TOut, TOp>(rowSizes[i], colSizes[i+1], op));
                    else        _upper.push_back(new kl1p::TZeroOperator<T>(rowSizes[i], colSizes[i+1]));
                }
            }

            for(klab::UInt32 i=size; i<diagSize-1; ++i)
            {
                if(rowSizes[i]>0 && colSizes[i+1]>0)
                    _upper.push_back(new kl1p::TZeroOperator<T>(rowSizes[i], colSizes[i+1]));
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TBlockTridiagonalOperator<T, TOut, TOp>::updateVarianceMatrix()
{
    klab::UInt32 size = static_cast<klab::UInt32>(_diagonal.size());
    _varianceDiagonal.set_size(size);
    _varianceLower.set_size(size);
    _varianceUpper.set_size(size);

    if(size > 0)
    {
        for(klab::UInt32 i=0; i<size; ++i)
            _varianceDiagonal[i] = _diagonal[i]->variance();

        _varianceLower[0] = klab::TTypeInfo<T>::ZERO;
        for(klab::UInt32 i=0; i<size-1; ++i)
            _varianceLower[i+1] = _lower[i]->variance();

        _varianceUpper[size-1] = klab::TTypeInfo<T>::ZERO;
        for(klab::UInt32 i=0; i<size-1; ++i)
            _varianceUpper[i] = _upper[i]->variance();
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
