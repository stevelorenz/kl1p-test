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

#ifndef KL1P_JOINTOPERATOR_H
#define KL1P_JOINTOPERATOR_H

#include "BlockOperator.h"
#include "RowJointOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=kl1p::TOperator<T, TOut> >
class TJointOperator : public TBlockOperator<T, TOut, TOp>
{
public:

	typedef std::vector<klab::TSmartPointer<TOp> >	TOperatorArray;
	
	
public:

    TJointOperator(klab::TSmartPointer<TOp> op);
    TJointOperator(klab::UInt32 blockRows, klab::UInt32 blockColumns, const typename TJointOperator<T, TOut, TOp>::TOperatorArray& ops);
    TJointOperator(const TJointOperator<T, TOut, TOp>& op);
    virtual ~TJointOperator();   

    virtual klab::UInt32                countBlockRows() const;
    virtual klab::UInt32                countBlockColumns() const;
    virtual klab::TSmartPointer<TOp>    block(klab::UInt32 i, klab::UInt32 j) const;

    virtual void                        applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void                        applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out);


protected:

    void                                updateVarianceMatrix();


private:

    TJointOperator<T, TOut>&            operator=(const TJointOperator<T, TOut>& op);


private:

    std::vector<klab::TSmartPointer<TRowJointOperator<T, TOut, TOp> > > _rows;

    arma::Mat<T>                        _varianceMatrix;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TJointOperator<T, TOut, TOp>::TJointOperator(klab::TSmartPointer<TOp> op) : TBlockOperator<T, TOut, TOp>(),
_rows(),
_varianceMatrix()
{
    if(op != 0)
    {
        _rows.push_back(new TRowJointOperator<T, TOut, TOp>(op));
        this->resize(op->m(), op->n());
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TJointOperator<T, TOut, TOp>::TJointOperator(klab::UInt32 blockRows, klab::UInt32 blockColumns, const typename TJointOperator<T, TOut, TOp>::TOperatorArray& ops) : TBlockOperator<T, TOut, TOp>(),
_rows(),
_varianceMatrix()
{
    if(blockRows>0 && blockColumns>0 && ops.size()>0)
    {
        klab::UInt32 m = 0;
        klab::UInt32 n = 0;

        std::vector<klab::UInt32> rowSizes(blockRows, 0);
        std::vector<klab::UInt32> colSizes(blockColumns, 0);

        klab::UInt32 size = static_cast<klab::UInt32>(ops.size());
        for(klab::UInt32 i=0, k=0; i<blockRows && k<size; ++i)
        {        
            for(klab::UInt32 j=0; j<blockColumns; ++j, ++k)
            {
                klab::TSmartPointer<TOp> op = ops[k];
                if(op != 0)
                {
                    rowSizes[i] = klab::Max(rowSizes[i], op->m());
                    colSizes[j] = klab::Max(colSizes[j], op->n());
                }
            }
        }

        for(klab::UInt32 i=0; i<blockRows; ++i)
            m += rowSizes[i];

        for(klab::UInt32 i=0; i<blockColumns; ++i)
            n += colSizes[i];

        this->resize(m, n);


        for(klab::UInt32 i=0, k=0; i<blockRows; ++i)
        {     
            if(rowSizes[i] > 0)
            {
                typename TRowJointOperator<T, TOut, TOp>::TOperatorArray cols;
                for(klab::UInt32 j=0; j<blockColumns; ++j, ++k)
                {
                    if(colSizes[j] > 0)
                    {
                        if(k < size)
                        {
                            klab::TSmartPointer<TOp> op = ops[k];
                            if(op != 0)
                            {
                                if(op->m()==rowSizes[i] && op->n()==colSizes[j])    cols.push_back(op);
                                else                                                cols.push_back(new TResizingOperator<T, TOut, TOp>(rowSizes[i], colSizes[j], op));
                            }
                            else
                            {
                                cols.push_back(new kl1p::TZeroOperator<T>(rowSizes[i], colSizes[j]));
                            }
                        }
                        else
                        {
                            cols.push_back(new kl1p::TZeroOperator<T>(rowSizes[i], colSizes[j]));
                        }
                    }
                }

                _rows.push_back(new TRowJointOperator<T, TOut, TOp>(cols));
            }
            else
            {
                k += blockColumns;
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TJointOperator<T, TOut, TOp>::TJointOperator(const TJointOperator<T, TOut, TOp>& op) : TBlockOperator<T, TOut, TOp>(op),
_rows(op._rows),
_varianceMatrix(op._varianceMatrix)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TJointOperator<T, TOut, TOp>::~TJointOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TJointOperator<T, TOut, TOp>::countBlockRows() const
{
    return static_cast<klab::UInt32>(_rows.size());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TJointOperator<T, TOut, TOp>::countBlockColumns() const
{
    if(_rows.size()>0)  return _rows[0]->countBlockColumns();
    else                return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TJointOperator<T, TOut, TOp>::block(klab::UInt32 i, klab::UInt32 j) const
{
    ThrowTraceExceptionIf(KNullOperatorException, _rows.size()==0);
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->countBlockRows() || j>=this->countBlockColumns());

    return _rows[i]->block(0, j);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TJointOperator<T, TOut, TOp>::applyBlockVariance(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _rows.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockColumns()); 

    if(_varianceMatrix.n_rows==0 || _varianceMatrix.n_cols==0)
        this->updateVarianceMatrix();

    out = _varianceMatrix * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TJointOperator<T, TOut, TOp>::applyBlockVarianceAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KNullOperatorException, _rows.size()==0);
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->countBlockRows()); 

    if(_varianceMatrix.n_rows==0 || _varianceMatrix.n_cols==0)
        this->updateVarianceMatrix();

    out = arma::trans(_varianceMatrix) * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline void TJointOperator<T, TOut, TOp>::updateVarianceMatrix()
{
    klab::UInt32 m = this->countBlockRows();
    klab::UInt32 n = this->countBlockColumns();

    _varianceMatrix.set_size(m, n);
    for(klab::UInt32 i=0; i<m; ++i)
    {
        for(klab::UInt32 j=0; j<n; ++j)
        {
            klab::TSmartPointer<TOp> op = this->block(i, j);
            ThrowTraceExceptionIf(KNullOperatorException, op==0);

            _varianceMatrix(i, j) = op->variance();
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
