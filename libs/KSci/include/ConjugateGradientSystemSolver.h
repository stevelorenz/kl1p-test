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

#ifndef KLAB_CONJUGATEGRADIENTSYSTEMSOLVER_H
#define KLAB_CONJUGATEGRADIENTSYSTEMSOLVER_H

#include "MatrixLinearOperator.h"
#include "ComplexProxyLinearOperator.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KConjugateGradientException, KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorConjugateGradientException, KConjugateGradientException)
KLAB_DECLARE_EXCEPTION(KIncompatibleSizeConjugateGradientException, KConjugateGradientException)
KLAB_DECLARE_EXCEPTION(KZeroNormConjugateGradientException, KConjugateGradientException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T>
class TConjugateGradientSystemSolver
{
public:

    TConjugateGradientSystemSolver();
	TConjugateGradientSystemSolver(const T& tolerance);
    TConjugateGradientSystemSolver(const T& tolerance, klab::UInt32 iterationLimit);
    TConjugateGradientSystemSolver(const TConjugateGradientSystemSolver<T, TCol>& solver);
    virtual ~TConjugateGradientSystemSolver();

    TConjugateGradientSystemSolver<T, TCol>&    operator=(const TConjugateGradientSystemSolver<T, TCol>& solver);

    void                            	setTolerance(const T& tolerance);
    void                            	setIterationLimit(klab::UInt32 limit);

    const T&         					tolerance() const;
    klab::UInt32             	iterationLimit() const;
    const T&         					residual() const;
    klab::UInt32              	countIterations() const;


    template<class TOperator>
	void                solve(const TOperator& op, const arma::Col<TCol>& b, arma::Col<TCol>& x);
	template<class TOperator>
	void                solve(const TOperator& op, const arma::Col<TCol>& b, const arma::Col<TCol>& x0, arma::Col<TCol>& x);
	
	void                solve(const arma::Mat<TCol>& a, const arma::Col<TCol>& b, arma::Col<TCol>& x);
    void                solve(const arma::Mat<TCol>& a, const arma::Col<TCol>& b, const arma::Col<TCol>& x0, arma::Col<TCol>& x);


private:

    T                   _tolerance;
    klab::UInt32        _iterationLimit;
	
    T                   _residual;
	klab::UInt32		_nIterations;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOperator>
class TConjugateGradientSystemSolverSpecialization
{
public:

    static void     SolveConjugateGradient(const TOperator& op, const arma::Col<TCol>& b, const arma::Col<TCol>& x0, arma::Col<TCol>& x, const T& tolerance, klab::UInt32 iterationLimit, T& residual, klab::UInt32& nIterations);
    

private:

    TConjugateGradientSystemSolverSpecialization();
    TConjugateGradientSystemSolverSpecialization(const TConjugateGradientSystemSolverSpecialization<T, TCol, TOperator>& spec);
    TConjugateGradientSystemSolverSpecialization<T, TCol, TOperator>&   operator=(const TConjugateGradientSystemSolverSpecialization<T, TCol, TOperator>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
class TConjugateGradientSystemSolverSpecialization<T, std::complex<T>, TOperator>
{
public:

    static void     SolveConjugateGradient(const TOperator& op, const arma::Col<std::complex<T> >& b, const arma::Col<std::complex<T> >& x0, arma::Col<std::complex<T> >& x, const T& tolerance, klab::UInt32 iterationLimit, T& residual, klab::UInt32& nIterations);


private:

    TConjugateGradientSystemSolverSpecialization();
    TConjugateGradientSystemSolverSpecialization(const TConjugateGradientSystemSolverSpecialization<T, std::complex<T>, TOperator>& spec);
    TConjugateGradientSystemSolverSpecialization<T, std::complex<T>, TOperator>&    operator=(const TConjugateGradientSystemSolverSpecialization<T, std::complex<T>, TOperator>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TConjugateGradientSystemSolver<T, TCol>::TConjugateGradientSystemSolver() : 
_tolerance(klab::TTypeInfo<T>::EPSILON), _iterationLimit(0), 
_residual(klab::TTypeInfo<T>::ZERO), _nIterations(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TConjugateGradientSystemSolver<T, TCol>::TConjugateGradientSystemSolver(const T& tolerance) : 
_tolerance(tolerance), _iterationLimit(0), 
_residual(klab::TTypeInfo<T>::ZERO), _nIterations(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TConjugateGradientSystemSolver<T, TCol>::TConjugateGradientSystemSolver(const T& tolerance, klab::UInt32 iterationLimit) : 
_tolerance(tolerance), _iterationLimit(iterationLimit), 
_residual(klab::TTypeInfo<T>::ZERO), _nIterations(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TConjugateGradientSystemSolver<T, TCol>::TConjugateGradientSystemSolver(const TConjugateGradientSystemSolver<T, TCol>& solver) : 
_tolerance(solver._tolerance), _iterationLimit(solver._iterationLimit), 
_residual(solver._residual), _nIterations(solver._nIterations)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TConjugateGradientSystemSolver<T, TCol>::~TConjugateGradientSystemSolver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TConjugateGradientSystemSolver<T, TCol>& TConjugateGradientSystemSolver<T, TCol>::operator=(const TConjugateGradientSystemSolver<T, TCol>& solver)
{
    if(this != &solver)
    {
        _tolerance      = solver._tolerance;
        _iterationLimit = solver._iterationLimit;

        _residual    = solver._residual;
        _nIterations = solver._nIterations;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline void TConjugateGradientSystemSolver<T, TCol>::setTolerance(const T& tolerance)
{
    _tolerance = tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline void TConjugateGradientSystemSolver<T, TCol>::setIterationLimit(klab::UInt32 limit)
{
    _iterationLimit = limit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TConjugateGradientSystemSolver<T, TCol>::tolerance() const
{
    return _tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline klab::UInt32 TConjugateGradientSystemSolver<T, TCol>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TConjugateGradientSystemSolver<T, TCol>::residual() const
{
    return _residual;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline klab::UInt32 TConjugateGradientSystemSolver<T, TCol>::countIterations() const
{
    return _nIterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
template<class TOperator>
inline void TConjugateGradientSystemSolver<T, TCol>::solve(const TOperator& op, const arma::Col<TCol>& b, arma::Col<TCol>& x)
{
    arma::Col<TCol> x0(op.n());
    x0.fill(klab::TTypeInfo<TCol>::ZERO);

    this->solve<TOperator>(op, b, x0, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
template<class TOperator>
inline void TConjugateGradientSystemSolver<T, TCol>::solve(const TOperator& op, const arma::Col<TCol>& b, const arma::Col<TCol>& x0, arma::Col<TCol>& x)
{
    x = x0;

    _residual    = klab::TTypeInfo<T>::MAX;
    _nIterations = 0;       

    TConjugateGradientSystemSolverSpecialization<T, TCol, TOperator>::SolveConjugateGradient(op, b, x0, x, _tolerance, _iterationLimit, _residual, _nIterations);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline void TConjugateGradientSystemSolver<T, TCol>::solve(const arma::Mat<TCol>& a, const arma::Col<TCol>& b, arma::Col<TCol>& x)
{
    klab::TMatrixLinearOperator<TCol> op(a);
    this->solve<klab::TMatrixLinearOperator<TCol> >(op, b, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline void TConjugateGradientSystemSolver<T, TCol>::solve(const arma::Mat<TCol>& a, const arma::Col<TCol>& b, const arma::Col<TCol>& x0, arma::Col<TCol>& x)
{
    klab::TMatrixLinearOperator<TCol> op(a);
    this->solve<klab::TMatrixLinearOperator<TCol> >(op, b, x0, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOperator>
inline void TConjugateGradientSystemSolverSpecialization<T, TCol, TOperator>::SolveConjugateGradient(const TOperator& op, const arma::Col<TCol>& b, const arma::Col<TCol>& x0, arma::Col<TCol>& x, const T& tolerance, klab::UInt32 iterationLimit, T& residual, klab::UInt32& nIterations)
{
    klab::UInt32 m = op.m();
	klab::UInt32 n = op.n();

    ThrowTraceExceptionIf(KNullOperatorConjugateGradientException, m==0 || n==0);
    ThrowTraceExceptionIf(KIncompatibleSizeConjugateGradientException, m != n);
    ThrowTraceExceptionIf(KIncompatibleSizeConjugateGradientException, b.n_rows != m);  
    ThrowTraceExceptionIf(KIncompatibleSizeConjugateGradientException, x0.n_rows != n);   

    arma::Col<TCol> xt = x0;
    arma::Col<TCol> ax;
    op.apply(xt, ax);

    arma::Col<TCol> r = b - ax;
    arma::Col<TCol> d = r;

    TCol delta  = klab::TTypeInfo<TCol>::ZERO;
    TCol delta0 = klab::TTypeInfo<TCol>::ZERO;
    for(klab::UInt32 i=0; i<r.n_rows; ++i)
    {
        delta  += r[i] * r[i];
        delta0 += b[i] * b[i];
    }

    ThrowTraceExceptionIf(KZeroNormConjugateGradientException, delta0==klab::TTypeInfo<TCol>::ZERO);
    
    residual       = klab::Sqrt(static_cast<T>(delta/delta0));
    TCol delta0Tol = delta0 * static_cast<TCol>(tolerance*tolerance);

    klab::UInt32 limit = (iterationLimit>0 ? iterationLimit : n);
    while(nIterations<limit && delta>delta0Tol)
    {
        op.apply(d, ax);

        TCol dq = klab::TTypeInfo<TCol>::ZERO;
        for(klab::UInt32 i=0; i<ax.n_rows; ++i)
            dq  += d[i] * ax[i];

        ThrowTraceExceptionIf(KZeroNormConjugateGradientException, dq==klab::TTypeInfo<TCol>::ZERO);

        TCol alpha = delta / dq;
        xt += alpha * d;
        r  -= alpha * ax;

        TCol invDelta = klab::TTypeInfo<TCol>::UNIT / delta;
        delta         = klab::TTypeInfo<TCol>::ZERO;
        for(klab::UInt32 i=0; i<r.n_rows; ++i)
            delta  += r[i] * r[i];
        
        d = r + ((delta*invDelta) * d); // Note : Variable 'invDelta' used here corresponds to inverse of delta-value from PREVIOUS iteration, whereas variable 'delta' corresponds to delta-value from CURRENT iteration.

        T res = klab::Sqrt(static_cast<T>(delta/delta0));
        if(res < residual)
        {
            x        = xt;
            residual = res;
        }

        ++nIterations;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
inline void TConjugateGradientSystemSolverSpecialization<T, std::complex<T>, TOperator>::SolveConjugateGradient(const TOperator& op, const arma::Col<std::complex<T> >& b, const arma::Col<std::complex<T> >& x0, arma::Col<std::complex<T> >& x, const T& tolerance, klab::UInt32 iterationLimit, T& residual, klab::UInt32& nIterations)
{
    klab::UInt32 m = op.m();
	klab::UInt32 n = op.n();

    ThrowTraceExceptionIf(KNullOperatorConjugateGradientException, m==0 || n==0);
    ThrowTraceExceptionIf(KIncompatibleSizeConjugateGradientException, m != n);
    ThrowTraceExceptionIf(KIncompatibleSizeConjugateGradientException, b.n_rows != m);  
    ThrowTraceExceptionIf(KIncompatibleSizeConjugateGradientException, x0.n_rows != n);   

    arma::Col<T> cb(b.n_rows<<1);
    arma::Col<T> cx0(x0.n_rows<<1);
    arma::Col<T> cx;  

    for(klab::UInt32 i=0; i<b.n_rows; ++i)
    {
        cb[i]          = b[i].real();
        cb[b.n_rows+i] = b[i].imag();
    }

    for(klab::UInt32 i=0; i<x0.n_rows; ++i)
    {
        cx0[i]           = x0[i].real();
        cx0[x0.n_rows+i] = x0[i].imag();
    }

    cx = cx0;
    TConjugateGradientSystemSolverSpecialization<T, T, klab::TComplexProxyLinearOperator<T, TOperator> >::SolveConjugateGradient(klab::TComplexProxyLinearOperator<T, TOperator>(op), cb, cx0, cx, tolerance, iterationLimit, residual, nIterations);

    klab::UInt32 nx = cx.n_rows >> 1;
    for(klab::UInt32 i=0; i<nx; ++i)
        x[i] = std::complex<T>(cx[i], cx[nx+i]);    
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
