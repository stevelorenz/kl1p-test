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

#ifndef KL1P_MATRIXOPERATOR_H
#define KL1P_MATRIXOPERATOR_H

#include "Operator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TMatrixOperator : public TOperator<T>
{
public:
    
    TMatrixOperator(const arma::Mat<T>& matrix, bool normalize=false);
    TMatrixOperator(const TMatrixOperator<T>& op);
    virtual ~TMatrixOperator();    

    const arma::Mat<T>& matrix() const;
	
	void				normalize();
	bool				isNormalized() const;
	
    virtual T       	squaredNormFrobenius();

    virtual void        apply(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void        applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out);
    virtual void        column(klab::UInt32 i, arma::Col<T>& out);
    virtual void        columnAdjoint(klab::UInt32 i, arma::Col<T>& out);
    virtual void        toMatrix(arma::Mat<T>& out);
    virtual void        toMatrixAdjoint(arma::Mat<T>& out);


protected:

    TMatrixOperator();

    arma::Mat<T>&       matrixReference();	


private:

    TMatrixOperator<T>& operator=(const TMatrixOperator<T>& op);


private:

    arma::Mat<T>        _matrix;
	bool				_isNormalized;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::TSmartPointer<kl1p::TOperator<T, T> >  ToOperator(const arma::Mat<T>& matrix)
{
    return new kl1p::TMatrixOperator<T>(matrix);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixOperator<T>::TMatrixOperator() : TOperator<T>(), 
_matrix(), _isNormalized(false)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixOperator<T>::TMatrixOperator(const arma::Mat<T>& matrix, bool normalize) : TOperator<T>(matrix.n_rows, matrix.n_cols), 
_matrix(matrix), _isNormalized(normalize)
{
	if(normalize)
		this->normalize();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixOperator<T>::TMatrixOperator(const TMatrixOperator<T>& op) : TOperator<T>(op), 
_matrix(op._matrix), _isNormalized(op._isNormalized)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TMatrixOperator<T>::~TMatrixOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const arma::Mat<T>& TMatrixOperator<T>::matrix() const
{
    return _matrix;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TMatrixOperator<T>::normalize()
{
	_isNormalized = false;
	
	for(klab::UInt32 j=0; j<_matrix.n_cols; ++j)
	{
		T sqNorm = klab::TTypeInfo<T>::ZERO;
		for(klab::UInt32 i=0; i<_matrix.n_rows; ++i)
			sqNorm += klab::Conj(_matrix(i, j)) * _matrix(i, j);
			
		if(sqNorm != klab::TTypeInfo<T>::ZERO)
		{
			T invNorm = klab::TTypeInfo<T>::UNIT / klab::Sqrt(sqNorm);
			for(klab::UInt32 i=0; i<_matrix.n_rows; ++i)
				_matrix(i, j) *= invNorm;
				
			if(j == 0)	_isNormalized  = true;
			else		_isNormalized &= true;
		}
	}	
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TMatrixOperator<T>::isNormalized() const
{
	return _isNormalized;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TMatrixOperator<T>::squaredNormFrobenius()
{
	if(_isNormalized)	return this->n();
	else				return TOperator<T>::squaredNormFrobenius();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TMatrixOperator<T>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->n());

    out = _matrix * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TMatrixOperator<T>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KIncompatibleSizeOperatorException, in.n_rows!=this->m());

    out = arma::trans(_matrix) * in;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TMatrixOperator<T>::column(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->n());

    out.set_size(this->m());
    for(klab::UInt32 j=0; j<out.n_rows; ++j)
        out[j] = _matrix(j, i);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TMatrixOperator<T>::columnAdjoint(klab::UInt32 i, arma::Col<T>& out)
{
    ThrowTraceExceptionIf(KOutOfBoundOperatorException, i>=this->m());

    out.set_size(this->n());
    for(klab::UInt32 j=0; j<out.n_rows; ++j)
        out[j] = klab::Conj(_matrix(i, j));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TMatrixOperator<T>::toMatrix(arma::Mat<T>& out)
{
    out = _matrix;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TMatrixOperator<T>::toMatrixAdjoint(arma::Mat<T>& out)
{
    out = arma::trans(_matrix);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline arma::Mat<T>& TMatrixOperator<T>::matrixReference()
{
    return _matrix;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
