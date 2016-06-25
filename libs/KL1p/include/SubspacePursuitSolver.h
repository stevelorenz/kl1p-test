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

#ifndef KL1P_SUBSPACEPURSUITSOLVER_H
#define KL1P_SUBSPACEPURSUITSOLVER_H

#include "Operator.h"
#include "MultiplicationOperator.h"
#include "SubSystemOperator.h"
#include "ProxyLinearOperator.h"
#include "AdjointOperator.h"
#include "History.h"
#include "SubspacePursuitHistoryElement.h"





namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KSubspacePursuitSolverException, klab::KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorSubspacePursuitSolverException, KSubspacePursuitSolverException)
KLAB_DECLARE_EXCEPTION(KNullVectorSubspacePursuitSolverException, KSubspacePursuitSolverException)
KLAB_DECLARE_EXCEPTION(KZeroNormVectorSubspacePursuitSolverException, KSubspacePursuitSolverException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T, class TOp=TOperator<TCol, TCol> >
class TSubspacePursuitSolver
{
public:

    TSubspacePursuitSolver();
    TSubspacePursuitSolver(const T& tolerance);
    TSubspacePursuitSolver(const T& tolerance, klab::UInt32 iterationLimit);
    TSubspacePursuitSolver(const TSubspacePursuitSolver<T, TCol, TOp>& solver);
    virtual ~TSubspacePursuitSolver();

    TSubspacePursuitSolver<T, TCol, TOp>&   operator=(const TSubspacePursuitSolver<T, TCol, TOp>& solver);

    void                        setTolerance(const T& tolerance);  
    void                        setIterationLimit(klab::UInt32 iterationLimit);  

    const T&                    tolerance() const;
    klab::UInt32         iterationLimit() const;
    const T&                    residualNorm() const;
    const T&                    relativeResidualNorm() const;
    klab::UInt32         iterations() const;

    const klab::TConjugateGradientSystemSolver<T, TCol>&    conjugateGradientSolver() const;
    klab::TConjugateGradientSystemSolver<T, TCol>&          conjugateGradientSolver();

    void                                                    enableHistory(bool enable);
    bool                                                    isHistoryEnabled() const;
    const THistory<TSubspacePursuitHistoryElement<T> >&     history() const;
    
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x);    // Implicit use of phi' (adjoint matrix of phi) as backward matrix.     
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x); // Explicit definition of backward matrix (phiT) to use.


private:

    T                   _tolerance;
    klab::UInt32        _iterationLimit;  

    T                   _residualNorm;
    T                   _relativeResidualNorm;
    klab::UInt32        _iterations;           

    klab::TConjugateGradientSystemSolver<T, TCol>   _conjugateGradientSolver; 

    bool                                            _isHistoryEnabled;
    THistory<TSubspacePursuitHistoryElement<T> >    _history;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSubspacePursuitSolver<T, TCol, TOp>::TSubspacePursuitSolver() : 
_tolerance(static_cast<T>(1e-6)), _iterationLimit(50),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_conjugateGradientSolver(static_cast<T>(1e-6), 200),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSubspacePursuitSolver<T, TCol, TOp>::TSubspacePursuitSolver(const T& tolerance) : 
_tolerance(tolerance), _iterationLimit(50), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_conjugateGradientSolver(static_cast<T>(1e-6), 200),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSubspacePursuitSolver<T, TCol, TOp>::TSubspacePursuitSolver(const T& tolerance, klab::UInt32 iterationLimit) : 
_tolerance(tolerance), _iterationLimit(iterationLimit),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_conjugateGradientSolver(static_cast<T>(1e-6), 200),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSubspacePursuitSolver<T, TCol, TOp>::TSubspacePursuitSolver(const TSubspacePursuitSolver<T, TCol, TOp>& solver) : 
_tolerance(solver._tolerance), _iterationLimit(solver._iterationLimit), 
_residualNorm(solver._residualNorm), _relativeResidualNorm(solver._relativeResidualNorm), _iterations(solver._iterations), 
_conjugateGradientSolver(solver._conjugateGradientSolver),
_isHistoryEnabled(solver._isHistoryEnabled), _history(solver._history)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSubspacePursuitSolver<T, TCol, TOp>::~TSubspacePursuitSolver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TSubspacePursuitSolver<T, TCol, TOp>& TSubspacePursuitSolver<T, TCol, TOp>::operator=(const TSubspacePursuitSolver<T, TCol, TOp>& solver)
{
    if(this != &solver)
    {
        _tolerance      = solver._tolerance;
        _iterationLimit = solver._iterationLimit;

        _residualNorm  = solver._residualNorm;
        _relativeResidualNorm = solver._relativeResidualNorm;
        _iterations    = solver._iterations;

        _conjugateGradientSolver = solver._conjugateGradientSolver;

        _isHistoryEnabled = solver._isHistoryEnabled;
        _history          = solver._history;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSubspacePursuitSolver<T, TCol, TOp>::setTolerance(const T& tolerance)
{
    _tolerance = tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSubspacePursuitSolver<T, TCol, TOp>::setIterationLimit(klab::UInt32 iterationLimit)
{
    _iterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TSubspacePursuitSolver<T, TCol, TOp>::tolerance() const
{
    return _tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TSubspacePursuitSolver<T, TCol, TOp>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TSubspacePursuitSolver<T, TCol, TOp>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TSubspacePursuitSolver<T, TCol, TOp>::relativeResidualNorm() const
{
    return _relativeResidualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TSubspacePursuitSolver<T, TCol, TOp>::iterations() const
{
    return _iterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const klab::TConjugateGradientSystemSolver<T, TCol>& TSubspacePursuitSolver<T, TCol, TOp>::conjugateGradientSolver() const
{
    return _conjugateGradientSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::TConjugateGradientSystemSolver<T, TCol>& TSubspacePursuitSolver<T, TCol, TOp>::conjugateGradientSolver()
{
    return _conjugateGradientSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSubspacePursuitSolver<T, TCol, TOp>::enableHistory(bool enable)
{
    _isHistoryEnabled = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TSubspacePursuitSolver<T, TCol, TOp>::isHistoryEnabled() const
{
    return _isHistoryEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const THistory<TSubspacePursuitHistoryElement<T> >& TSubspacePursuitSolver<T, TCol, TOp>::history() const
{
    return _history;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSubspacePursuitSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x)
{ 
    this->solve(y, phi, klab::TSmartPointer<TOp>(new TAdjointOperator<TCol>(phi)), sparsity, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TSubspacePursuitSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x)
{   
    _residualNorm  = klab::TTypeInfo<T>::ZERO;
    _relativeResidualNorm = klab::TTypeInfo<T>::ZERO;
    _iterations = 0;
    _history.clear();

    ThrowTraceExceptionIf(KNullVectorSubspacePursuitSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorSubspacePursuitSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorSubspacePursuitSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0);

    klab::UInt32 m = y.n_rows;
    klab::UInt32 n = phi->n();
    klab::UInt32 k = klab::Min(sparsity, n);        

    if(n > 0)
    {
        if(k > 0)
        {           
            x.set_size(n);
            x.fill(klab::TTypeInfo<TCol>::ZERO);

            typedef kl1p::TMultiplicationOperator<TCol, TCol, TCol, kl1p::TAdjointOperator<TCol, TCol, TOp>, kl1p::TSubSystemOperator<TCol, TCol, TOp> >    KAtAOperator;
            
            std::vector<klab::UInt32> indexes;
            std::set<klab::UInt32>    indexesSet;
            arma::Col<TCol>           residual(y);
            arma::Col<TCol>           b;

            T yNorm = static_cast<T>(arma::norm(y, 2));
            ThrowTraceExceptionIf(KZeroNormVectorSubspacePursuitSolverException, yNorm == klab::TTypeInfo<T>::ZERO);

            T invYNorm = klab::TTypeInfo<T>::UNIT / yNorm;
            _residualNorm = static_cast<T>(arma::norm(residual, 2));
            _relativeResidualNorm = _residualNorm * invYNorm;

            if(_isHistoryEnabled)
                _history.push(TSubspacePursuitHistoryElement<T>(_residualNorm));

            bool loop = true;
            while(_iterations<_iterationLimit && _residualNorm>_tolerance && loop)
            { 
                // Find T^{\prime} and add it to \hat{T}.
                arma::Col<TCol> u; 
                phiT->apply(residual, u);

                std::vector<klab::TArrayElement<T> > absU;
                for(klab::UInt32 i=0; i<u.n_rows; ++i)
                    absU.push_back(klab::TArrayElement<T>(i, klab::Abs(u[i])));

                std::partial_sort(absU.begin(), absU.begin()+k, absU.end(), std::greater<klab::TArrayElement<T> >());   // Sort k greatest values only.

                std::vector<klab::UInt32> uIndexes;
                for(klab::UInt32 i=0; i<k; ++i)
                    uIndexes.push_back(absU[i].i());

                std::sort(uIndexes.begin(), uIndexes.end());

                klab::UInt32 uIndexesSize = static_cast<klab::UInt32>(uIndexes.size());
                for(klab::UInt32 i=0; i<uIndexesSize; ++i)
                {
                    klab::UInt32 index = uIndexes[i];
                    if(indexesSet.find(index) == indexesSet.end())
                    {
                        indexes.push_back(index);
                        indexesSet.insert(index);
                    }
                }
                               
                // Identify large components.
                klab::TSmartPointer<TSubSystemOperator<TCol, TCol, TOp> > phiSubI = new TSubSystemOperator<TCol, TCol, TOp>(phi, indexes);
                TProxyLinearOperator<TCol, KAtAOperator> cgOp(new KAtAOperator(new kl1p::TAdjointOperator<TCol, TCol, TOp>(phiSubI), phiSubI));    

                arma::Col<TCol> ySub;
                arma::Col<TCol> b0;
                phiSubI->applyAdjoint(y, ySub);                
                _conjugateGradientSolver.template solve<TProxyLinearOperator<TCol, KAtAOperator> >(cgOp, ySub, b0);

                std::vector<klab::TArrayElement<T> > absB0;
                for(klab::UInt32 i=0; i<b0.n_rows; ++i)
                    absB0.push_back(klab::TArrayElement<T>(i, static_cast<T>(klab::Abs(b0[i]))));

                std::partial_sort(absB0.begin(), absB0.begin()+k, absB0.end(), std::greater<klab::TArrayElement<T> >());    // Sort k greatest values only.

                indexes.clear();
                for(klab::UInt32 i=0; i<k; ++i)
                    indexes.push_back(phiSubI->indexes()[absB0[i].i()]);

                std::sort(indexes.begin(), indexes.end());

                // Calculate the residual.
                klab::TSmartPointer<TSubSystemOperator<TCol, TCol, TOp> > phiSubI2 = new TSubSystemOperator<TCol, TCol, TOp>(phi, indexes);
                TProxyLinearOperator<TCol, KAtAOperator> cgOp2(new KAtAOperator(new kl1p::TAdjointOperator<TCol, TCol, TOp>(phiSubI2), phiSubI2));    
                
                phiSubI2->applyAdjoint(y, ySub);                
                _conjugateGradientSolver.template solve<TProxyLinearOperator<TCol, KAtAOperator> >(cgOp2, ySub, b);

                phiSubI2->apply(b, ySub);
                residual = y - ySub; 
 				
                T residualNorm = static_cast<T>(arma::norm(residual, 2));
                loop = (residualNorm < _residualNorm);
                if(loop)
                {
                    _residualNorm = residualNorm;
                    _relativeResidualNorm = (_residualNorm * invYNorm);

                    x.fill(klab::TTypeInfo<TCol>::ZERO);
                    klab::UInt32 indexesSize = static_cast<klab::UInt32>(indexes.size());
                    for(klab::UInt32 i=0; i<indexesSize && i<b.n_rows; ++i)
                        x[indexes[i]] = b[i];
                }

                ++_iterations;

                if(_isHistoryEnabled)
                    _history.push(TSubspacePursuitHistoryElement<T>(_residualNorm));
            }
        }
        else
        {
            x.set_size(n);
            x.fill(klab::TTypeInfo<TCol>::ZERO);
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
