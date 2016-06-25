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

#ifndef KL1P_SL0SOLVER_H
#define KL1P_SL0SOLVER_H

#include "Operator.h"
#include "AdjointOperator.h"
#include "MultiplicationOperator.h"
#include "ProxyLinearOperator.h"
#include "History.h"
#include "SL0HistoryElement.h"





namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KSL0SolverException, klab::KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorSL0SolverException, KSL0SolverException)
KLAB_DECLARE_EXCEPTION(KNullVectorSL0SolverException, KSL0SolverException)
KLAB_DECLARE_EXCEPTION(KZeroNormVectorSL0SolverException, KSL0SolverException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T, class TOp=TOperator<TCol, TCol> >
class TSL0Solver
{
public:

    TSL0Solver();
    TSL0Solver(const T& tolerance);
    TSL0Solver(const T& tolerance, klab::UInt32 iterationLimit);
    TSL0Solver(const T& tolerance, klab::UInt32 iterationLimit, const T& sigmaStepFactor);
    TSL0Solver(const T& tolerance, klab::UInt32 iterationLimit, const T& sigmaStepFactor, const T& mu0);
    TSL0Solver(const T& tolerance, klab::UInt32 iterationLimit, const T& sigmaStepFactor, const T& mu0, klab::UInt32 innerIterationLimit);
    TSL0Solver(const TSL0Solver<T, TCol, TOp>& solver);
    virtual ~TSL0Solver();

    TSL0Solver<T, TCol, TOp>&  operator=(const TSL0Solver<T, TCol, TOp>& solver);

    void                        setTolerance(const T& tolerance);     
    void                        setSigmaStepFactor(const T& sigmaStepFactor);  
    void                        setMu0(const T& mu0);       
    void                        setIterationLimit(klab::UInt32 iterationLimit);
    void                        setInnerIterationLimit(klab::UInt32 iterationLimit); 

    const T&                    tolerance() const;    
    const T&                    sigmaStepFactor() const;
    const T&                    mu0() const;    
    klab::UInt32         iterationLimit() const;
    klab::UInt32         innerIterationLimit() const;
    const T&                    sigma() const;
    klab::UInt32         iterations() const;

    const klab::TConjugateGradientSystemSolver<T, TCol>&    conjugateGradientSolver() const;
    klab::TConjugateGradientSystemSolver<T, TCol>&          conjugateGradientSolver();

    void                                    enableHistory(bool enable);
    bool                                    isHistoryEnabled() const;
    const THistory<TSL0HistoryElement<T> >& history() const;
    
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, arma::Col<TCol>& x);  // Implicit use of phi' (adjoint matrix of phi) as backward matrix.     
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x);   // Explicit definition of backward matrix (phiT) to use.


private:

    T                   _tolerance;
    T                   _sigmaStepFactor;
    T                   _mu0;
    klab::UInt32        _iterationLimit;
    klab::UInt32        _innerIterationLimit;

    T                   _sigma;
    klab::UInt32        _iterations;

    klab::TConjugateGradientSystemSolver<T, TCol>   _conjugateGradientSolver; 

    bool                                _isHistoryEnabled;
    THistory<TSL0HistoryElement<T> >    _history;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSL0Solver<T, TCol, TOp>::TSL0Solver() : 
_tolerance(static_cast<T>(1e-6)), _sigmaStepFactor(static_cast<T>(0.5)), _mu0(static_cast<T>(2)), _iterationLimit(50), _innerIterationLimit(3),
_sigma(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_conjugateGradientSolver(static_cast<T>(1e-6), 200), 
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSL0Solver<T, TCol, TOp>::TSL0Solver(const T& tolerance) : 
_tolerance(tolerance>0?tolerance:klab::TTypeInfo<T>::EPSILON), _sigmaStepFactor(static_cast<T>(0.5)), _mu0(static_cast<T>(2)), _iterationLimit(50), _innerIterationLimit(3),
_sigma(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_conjugateGradientSolver(static_cast<T>(1e-6), 200), 
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSL0Solver<T, TCol, TOp>::TSL0Solver(const T& tolerance, klab::UInt32 iterationLimit) : 
_tolerance(tolerance>0?tolerance:klab::TTypeInfo<T>::EPSILON), _sigmaStepFactor(static_cast<T>(0.5)), _mu0(static_cast<T>(2)), _iterationLimit(iterationLimit), _innerIterationLimit(3),
_sigma(klab::TTypeInfo<T>::ZERO), _iterations(0),
_conjugateGradientSolver(static_cast<T>(1e-6), 200), 
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSL0Solver<T, TCol, TOp>::TSL0Solver(const T& tolerance, klab::UInt32 iterationLimit, const T& sigmaStepFactor) : 
_tolerance(tolerance>0?tolerance:klab::TTypeInfo<T>::EPSILON), _sigmaStepFactor(sigmaStepFactor>0?sigmaStepFactor:klab::TTypeInfo<T>::EPSILON), _mu0(static_cast<T>(2)), _iterationLimit(iterationLimit), _innerIterationLimit(3),
_sigma(klab::TTypeInfo<T>::ZERO), _iterations(0),
_conjugateGradientSolver(static_cast<T>(1e-6), 200), 
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSL0Solver<T, TCol, TOp>::TSL0Solver(const T& tolerance, klab::UInt32 iterationLimit, const T& sigmaStepFactor, const T& mu0) : 
_tolerance(tolerance>0?tolerance:klab::TTypeInfo<T>::EPSILON), _sigmaStepFactor(sigmaStepFactor>0?sigmaStepFactor:klab::TTypeInfo<T>::EPSILON), _mu0(mu0), _iterationLimit(iterationLimit), _innerIterationLimit(3),
_sigma(klab::TTypeInfo<T>::ZERO), _iterations(0),
_conjugateGradientSolver(static_cast<T>(1e-6), 200), 
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSL0Solver<T, TCol, TOp>::TSL0Solver(const T& tolerance, klab::UInt32 iterationLimit, const T& sigmaStepFactor, const T& mu0, klab::UInt32 innerIterationLimit) : 
_tolerance(tolerance>0?tolerance:klab::TTypeInfo<T>::EPSILON), _sigmaStepFactor(sigmaStepFactor>0?sigmaStepFactor:klab::TTypeInfo<T>::EPSILON), _mu0(mu0), _iterationLimit(iterationLimit), _innerIterationLimit(innerIterationLimit),
_sigma(klab::TTypeInfo<T>::ZERO), _iterations(0),
_conjugateGradientSolver(static_cast<T>(1e-6), 200), 
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSL0Solver<T, TCol, TOp>::TSL0Solver(const TSL0Solver<T, TCol, TOp>& solver) : 
_tolerance(solver._tolerance), _sigmaStepFactor(solver._sigmaStepFactor), _mu0(solver._mu0), _iterationLimit(solver._iterationLimit), _innerIterationLimit(solver._innerIterationLimit),
_sigma(solver._sigma), _iterations(solver._iterations), 
_conjugateGradientSolver(solver._conjugateGradientSolver), 
_isHistoryEnabled(solver._isHistoryEnabled), _history(solver._history)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSL0Solver<T, TCol, TOp>::~TSL0Solver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSL0Solver<T, TCol, TOp>& TSL0Solver<T, TCol, TOp>::operator=(const TSL0Solver<T, TCol, TOp>& solver)
{
    if(this != &solver)
    {
        _tolerance      = solver._tolerance;
        _sigmaStepFactor= solver._sigmaStepFactor;
        _mu0            = solver._mu0;
        _iterationLimit = solver._iterationLimit;
        _innerIterationLimit = solver._innerIterationLimit;

        _sigma                = solver._sigma;
        _iterations           = solver._iterations;

        _conjugateGradientSolver = solver._conjugateGradientSolver;

        _isHistoryEnabled = solver._isHistoryEnabled;
        _history          = solver._history;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSL0Solver<T, TCol, TOp>::setTolerance(const T& tolerance)
{
    _tolerance = tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSL0Solver<T, TCol, TOp>::setSigmaStepFactor(const T& sigmaStepFactor)
{
    _sigmaStepFactor = (sigmaStepFactor>0 ? sigmaStepFactor : klab::TTypeInfo<T>::EPSILON);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSL0Solver<T, TCol, TOp>::setMu0(const T& mu0)
{
    _mu0 = mu0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSL0Solver<T, TCol, TOp>::setIterationLimit(klab::UInt32 iterationLimit)
{
    _iterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSL0Solver<T, TCol, TOp>::setInnerIterationLimit(klab::UInt32 iterationLimit)
{
    _innerIterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TSL0Solver<T, TCol, TOp>::tolerance() const
{
    return _tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TSL0Solver<T, TCol, TOp>::sigmaStepFactor() const
{
    return _sigmaStepFactor;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TSL0Solver<T, TCol, TOp>::mu0() const
{
    return _mu0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TSL0Solver<T, TCol, TOp>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TSL0Solver<T, TCol, TOp>::innerIterationLimit() const
{
    return _innerIterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TSL0Solver<T, TCol, TOp>::sigma() const
{
    return _sigma;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TSL0Solver<T, TCol, TOp>::iterations() const
{
    return _iterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const klab::TConjugateGradientSystemSolver<T, TCol>& TSL0Solver<T, TCol, TOp>::conjugateGradientSolver() const
{
    return _conjugateGradientSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::TConjugateGradientSystemSolver<T, TCol>& TSL0Solver<T, TCol, TOp>::conjugateGradientSolver()
{
    return _conjugateGradientSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSL0Solver<T, TCol, TOp>::enableHistory(bool enable)
{
    _isHistoryEnabled = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TSL0Solver<T, TCol, TOp>::isHistoryEnabled() const
{
    return _isHistoryEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const THistory<TSL0HistoryElement<T> >& TSL0Solver<T, TCol, TOp>::history() const
{
    return _history;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSL0Solver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, arma::Col<TCol>& x)
{ 
    this->solve(y, phi, klab::TSmartPointer<TOp>(new TAdjointOperator<TCol>(phi)), x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSL0Solver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x)
{   
    _sigma  = klab::TTypeInfo<T>::ZERO;
    _iterations = 0;
    _history.clear();

    ThrowTraceExceptionIf(KNullVectorSL0SolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorSL0SolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorSL0SolverException, phiT==0 || phiT->m()==0 || phiT->n()==0); 

    klab::UInt32 m = y.n_rows;   
    klab::UInt32 n = phi->n();

    if(n > 0)
    {    
        TProxyLinearOperator<TCol> cgOp(phi*phiT);

        arma::Col<TCol> u, v;

        _conjugateGradientSolver.solve(cgOp, y, u);
        phiT->apply(u, x);

        klab::UInt32 n = x.n_rows;

        T maxAbsX = klab::TTypeInfo<T>::ZERO;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            T value = klab::Abs(x[i]);
            if(value > maxAbsX)
                maxAbsX = value;
        }

        _sigma = maxAbsX * static_cast<T>(2);

        if(_isHistoryEnabled)
            _history.push(TSL0HistoryElement<T>(_sigma));

        while(_iterations<_iterationLimit && _sigma>_tolerance)
        {
            TCol invSqSigma = klab::TTypeInfo<TCol>::UNIT / static_cast<TCol>(_sigma*_sigma);

            for(klab::UInt32 k=0; k<_innerIterationLimit; ++k) 
            {   
                arma::Col<TCol> delta(n);
                for(klab::UInt32 i=0; i<n; ++i)
                {
                    TCol z = -(x[i] * klab::Conj(x[i])) * invSqSigma;
                    delta[i] = x[i] * klab::Exp(z);
                }

                x -= _mu0 * delta;

                phi->apply(x, u);
                u -= y;

                _conjugateGradientSolver.template solve<TProxyLinearOperator<TCol> >(cgOp, u, v);
                phiT->apply(v, u);

                x -= u;                
            }

            _sigma *= _sigmaStepFactor;

            ++_iterations;

            if(_isHistoryEnabled)
                _history.push(TSL0HistoryElement<T>(_sigma));
        }
    }
    else
    {
        x.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
