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

#ifndef KL1P_AMPSOLVER_H
#define KL1P_AMPSOLVER_H

#include "Operator.h"
#include "AdjointOperator.h"
#include "History.h"
#include "AMPHistoryElement.h"





namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KAMPSolverException, klab::KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorAMPSolverException, KAMPSolverException)
KLAB_DECLARE_EXCEPTION(KNullVectorAMPSolverException, KAMPSolverException)
KLAB_DECLARE_EXCEPTION(KZeroNormVectorAMPSolverException, KAMPSolverException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T, class TOp=TOperator<TCol, TCol> >
class TAMPSolver
{
public:

    TAMPSolver();
    TAMPSolver(const T& tolerance);
    TAMPSolver(const T& tolerance, klab::UInt32 iterationLimit);
    TAMPSolver(const TAMPSolver<T, TCol, TOp>& solver);
    virtual ~TAMPSolver();

    TAMPSolver<T, TCol, TOp>&  operator=(const TAMPSolver<T, TCol, TOp>& solver);

    void                        setTolerance(const T& tolerance);  
    void                        setIterationLimit(klab::UInt32 iterationLimit);  

    const T&                    tolerance() const;
    klab::UInt32         iterationLimit() const;
    const T&                    residualNorm() const;
    const T&                    relativeResidualNorm() const;
    klab::UInt32         iterations() const;

    void                                    enableHistory(bool enable);
    bool                                    isHistoryEnabled() const;
    const THistory<TAMPHistoryElement<T> >& history() const;
    
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, arma::Col<TCol>& x);  // Implicit use of phi' (adjoint matrix of phi) as backward matrix.     
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x);   // Explicit definition of backward matrix (phiT) to use.


private:

    T                   _tolerance;
    klab::UInt32        _iterationLimit;

    T                   _residualNorm;
    T                   _relativeResidualNorm;
    klab::UInt32        _iterations;


    bool                                _isHistoryEnabled;
    THistory<TAMPHistoryElement<T> >    _history;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TAMPSolver<T, TCol, TOp>::TAMPSolver() : 
_tolerance(static_cast<T>(1e-6)), _iterationLimit(1000),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TAMPSolver<T, TCol, TOp>::TAMPSolver(const T& tolerance) : 
_tolerance(tolerance), _iterationLimit(1000), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TAMPSolver<T, TCol, TOp>::TAMPSolver(const T& tolerance, klab::UInt32 iterationLimit) : 
_tolerance(tolerance), _iterationLimit(iterationLimit), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TAMPSolver<T, TCol, TOp>::TAMPSolver(const TAMPSolver<T, TCol, TOp>& solver) : 
_tolerance(solver._tolerance), _iterationLimit(solver._iterationLimit), 
_residualNorm(solver._residualNorm), _relativeResidualNorm(solver._relativeResidualNorm), _iterations(solver._iterations), 
_isHistoryEnabled(solver._isHistoryEnabled), _history(solver._history)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TAMPSolver<T, TCol, TOp>::~TAMPSolver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TAMPSolver<T, TCol, TOp>& TAMPSolver<T, TCol, TOp>::operator=(const TAMPSolver<T, TCol, TOp>& solver)
{
    if(this != &solver)
    {
        _tolerance      = solver._tolerance;
        _iterationLimit = solver._iterationLimit;

        _residualNorm  = solver._residualNorm;
        _relativeResidualNorm = solver._relativeResidualNorm;
        _iterations    = solver._iterations;

        _isHistoryEnabled = solver._isHistoryEnabled;
        _history          = solver._history;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TAMPSolver<T, TCol, TOp>::setTolerance(const T& tolerance)
{
    _tolerance = tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TAMPSolver<T, TCol, TOp>::setIterationLimit(klab::UInt32 iterationLimit)
{
    _iterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TAMPSolver<T, TCol, TOp>::tolerance() const
{
    return _tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TAMPSolver<T, TCol, TOp>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TAMPSolver<T, TCol, TOp>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TAMPSolver<T, TCol, TOp>::relativeResidualNorm() const
{
    return _relativeResidualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TAMPSolver<T, TCol, TOp>::iterations() const
{
    return _iterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TAMPSolver<T, TCol, TOp>::enableHistory(bool enable)
{
    _isHistoryEnabled = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TAMPSolver<T, TCol, TOp>::isHistoryEnabled() const
{
    return _isHistoryEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const THistory<TAMPHistoryElement<T> >& TAMPSolver<T, TCol, TOp>::history() const
{
    return _history;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TAMPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, arma::Col<TCol>& x)
{ 
    this->solve(y, phi, klab::TSmartPointer<TOp>(new TAdjointOperator<TCol>(phi)), x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TAMPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x)
{   
    _residualNorm  = klab::TTypeInfo<T>::ZERO;
    _relativeResidualNorm = klab::TTypeInfo<T>::ZERO;
    _iterations = 0;
    _history.clear();

    ThrowTraceExceptionIf(KNullVectorAMPSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorAMPSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorAMPSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0);     

    klab::UInt32 m = y.n_rows;   
    klab::UInt32 n = phi->n();
    T invM = klab::TTypeInfo<T>::UNIT / static_cast<T>(m);

    if(n > 0)
    {         
        x.set_size(n);
        x.fill(klab::TTypeInfo<TCol>::ZERO);

        arma::Col<TCol> residual(y);
        arma::Col<TCol> x1(x);

        T yNorm = static_cast<T>(arma::norm(y, 2));
        ThrowTraceExceptionIf(KZeroNormVectorAMPSolverException, yNorm == klab::TTypeInfo<T>::ZERO);

        T invYNorm             = klab::TTypeInfo<T>::UNIT / yNorm;
        T residualNorm         = static_cast<T>(arma::norm(residual, 2));
        T relativeResidualNorm = residualNorm * invYNorm;
        _residualNorm          = residualNorm;
        _relativeResidualNorm  = relativeResidualNorm;

        if(_isHistoryEnabled)
            _history.push(TAMPHistoryElement<T>(residualNorm));

        while(_iterations<_iterationLimit && _residualNorm>_tolerance)
        {           
            // Pre-threshold value.
            arma::Col<TCol> u; 
            phiT->apply(residual, u);
            arma::Col<TCol> gamma = x1 + u;

            // Find m-th largest coefficient of gamma.
            std::vector<klab::TArrayElement<T> > absGamma;
            for(klab::UInt32 i=0; i<gamma.n_rows; ++i)
                absGamma.push_back(klab::TArrayElement<T>(i, klab::Abs(gamma[i])));

            std::partial_sort(absGamma.begin(), absGamma.begin()+m, absGamma.end(), std::greater<klab::TArrayElement<T> >());   // Sort m greatest values only.
            T threshold = absGamma[m-1].value();

            // Estimate the signal by soft thresholding.
			x1.fill(klab::TTypeInfo<TCol>::ZERO);
            klab::UInt32 sparsity = 0;
            for(; sparsity<m-1 && absGamma[sparsity].value()>klab::TTypeInfo<T>::ZERO && absGamma[sparsity].value()>threshold; ++sparsity)
            {                
				klab::UInt32 index = absGamma[sparsity].i();
                x1[index] = gamma[index] * (klab::TTypeInfo<T>::UNIT - (threshold/absGamma[sparsity].value()));
            }

            T sparsityInvM = static_cast<T>(sparsity) * invM;

            // Update the residual.
            arma::Col<TCol> y2; 
            phi->apply(x1, y2);
            arma::Col<TCol> res = y - y2;

            residual *= static_cast<TCol>(sparsityInvM);
            residual  = res + residual;   

            residualNorm         = static_cast<T>(arma::norm(res, 2));
            relativeResidualNorm = residualNorm * invYNorm;            

            ++_iterations;

            if(residualNorm < _residualNorm)
            {
                x = x1;
                _residualNorm         = residualNorm;
                _relativeResidualNorm = relativeResidualNorm; 
            }

            if(_isHistoryEnabled)
                _history.push(TAMPHistoryElement<T>(residualNorm));
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
