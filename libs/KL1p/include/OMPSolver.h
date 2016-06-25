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

#ifndef KL1P_OMPSOLVER_H
#define KL1P_OMPSOLVER_H

#include "Operator.h"
#include "SubSystemOperator.h"
#include "ProxyLinearOperator.h"
#include "AdjointOperator.h"
#include "History.h"
#include "OMPHistoryElement.h"

namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KOMPSolverException, klab::KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorOMPSolverException, KOMPSolverException)
KLAB_DECLARE_EXCEPTION(KNullVectorOMPSolverException, KOMPSolverException)
KLAB_DECLARE_EXCEPTION(KZeroNormVectorOMPSolverException, KOMPSolverException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T, class TOp=TOperator<TCol, TCol> >
class TOMPSolver
{
public:

    TOMPSolver();
    TOMPSolver(const T& tolerance);
    TOMPSolver(const T& tolerance, klab::UInt32 iterationLimit);
    TOMPSolver(const TOMPSolver<T, TCol, TOp>& solver);
    virtual ~TOMPSolver();

    TOMPSolver<T, TCol, TOp>&   operator=(const TOMPSolver<T, TCol, TOp>& solver);

    void                        setTolerance(const T& tolerance);
    void                        setIterationLimit(klab::UInt32 iterationLimit);

    const T&                    tolerance() const;
    klab::UInt32         iterationLimit() const;
    const T&                    residualNorm() const;
    const T&                    relativeResidualNorm() const;
    klab::UInt32         sparsity() const;
    klab::UInt32         iterations() const;

    const klab::TLeastSquareSystemSolver<T, TCol>&  leastSquareSolver() const;
    klab::TLeastSquareSystemSolver<T, TCol>&        leastSquareSolver();

    void                                        enableHistory(bool enable);
    bool                                        isHistoryEnabled() const;
    const THistory<TOMPHistoryElement<T> >&     history() const;

    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x);    // Implicit use of phi' (adjoint matrix of phi) as backward matrix.
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x); // Explicit definition of backward matrix (phiT) to use.


protected:

    void        solveOMP(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x);


private:

    T                   _tolerance;
    klab::UInt32        _iterationLimit;

    T                   _residualNorm;
    T                   _relativeResidualNorm;
    klab::UInt32        _sparsity;
    klab::UInt32        _iterations;

    klab::TLeastSquareSystemSolver<T, TCol> _leastSquareSolver;

    bool                                    _isHistoryEnabled;
    THistory<TOMPHistoryElement<T> >        _history;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TOMPSolver<T, TCol, TOp>::TOMPSolver() :
_tolerance(static_cast<T>(1e-6)), _iterationLimit(klab::TTypeInfo<klab::UInt32>::MAX),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _sparsity(0), _iterations(0),
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TOMPSolver<T, TCol, TOp>::TOMPSolver(const T& tolerance) :
_tolerance(tolerance), _iterationLimit(klab::TTypeInfo<klab::UInt32>::MAX),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _sparsity(0), _iterations(0),
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TOMPSolver<T, TCol, TOp>::TOMPSolver(const T& tolerance, klab::UInt32 iterationLimit) :
_tolerance(tolerance), _iterationLimit(iterationLimit),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _sparsity(0), _iterations(0),
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TOMPSolver<T, TCol, TOp>::TOMPSolver(const TOMPSolver<T, TCol, TOp>& solver) :
_tolerance(solver._tolerance), _iterationLimit(solver._iterationLimit),
_residualNorm(solver._residualNorm), _relativeResidualNorm(solver._relativeResidualNorm), _sparsity(solver._sparsity), _iterations(solver._iterations),
_leastSquareSolver(solver._leastSquareSolver),
_isHistoryEnabled(solver._isHistoryEnabled), _history(solver._history)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TOMPSolver<T, TCol, TOp>::~TOMPSolver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TOMPSolver<T, TCol, TOp>& TOMPSolver<T, TCol, TOp>::operator=(const TOMPSolver<T, TCol, TOp>& solver)
{
    if(this != &solver)
    {
        _tolerance      = solver._tolerance;
        _iterationLimit = solver._iterationLimit;

        _residualNorm = solver._residualNorm;
        _relativeResidualNorm = solver._relativeResidualNorm;
        _sparsity = solver._sparsity;
        _iterations = solver._iterations;

        _leastSquareSolver = solver._leastSquareSolver;

        _isHistoryEnabled = solver._isHistoryEnabled;
        _history          = solver._history;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TOMPSolver<T, TCol, TOp>::setTolerance(const T& tolerance)
{
    _tolerance = tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TOMPSolver<T, TCol, TOp>::setIterationLimit(klab::UInt32 iterationLimit)
{
    _iterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TOMPSolver<T, TCol, TOp>::tolerance() const
{
    return _tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TOMPSolver<T, TCol, TOp>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TOMPSolver<T, TCol, TOp>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TOMPSolver<T, TCol, TOp>::relativeResidualNorm() const
{
    return _relativeResidualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TOMPSolver<T, TCol, TOp>::sparsity() const
{
    return _sparsity;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TOMPSolver<T, TCol, TOp>::iterations() const
{
    return _iterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const klab::TLeastSquareSystemSolver<T, TCol>& TOMPSolver<T, TCol, TOp>::leastSquareSolver() const
{
    return _leastSquareSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::TLeastSquareSystemSolver<T, TCol>& TOMPSolver<T, TCol, TOp>::leastSquareSolver()
{
    return _leastSquareSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TOMPSolver<T, TCol, TOp>::enableHistory(bool enable)
{
    _isHistoryEnabled = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TOMPSolver<T, TCol, TOp>::isHistoryEnabled() const
{
    return _isHistoryEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const THistory<TOMPHistoryElement<T> >& TOMPSolver<T, TCol, TOp>::history() const
{
    return _history;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TOMPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x)
{
    this->solve(y, phi, klab::TSmartPointer<TOp>(new TAdjointOperator<TCol>(phi)), sparsity, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TOMPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x)
{
    this->solveOMP(y, phi, phiT, sparsity, x);
}

// ---------------------------------------------------------------------------------------------------- //

// Implementation OMP-Algorithm
template<class T, class TCol, class TOp>
inline void TOMPSolver<T, TCol, TOp>::solveOMP(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x)
{
    _residualNorm  = klab::TTypeInfo<T>::ZERO;
    _relativeResidualNorm = klab::TTypeInfo<T>::ZERO;
    _sparsity = 0;
    _iterations = 0;
    _history.clear();

    ThrowTraceExceptionIf(KNullVectorOMPSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorOMPSolverException, phi==0 || phi->m()==0 || phi->n()==0);
    ThrowTraceExceptionIf(KNullOperatorOMPSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0);

    klab::UInt32 m = y.n_rows;
    klab::UInt32 n = phi->n();
    klab::UInt32 k = klab::Min(sparsity, n);

    if(n > 0)
    {
        if(k > 0)
        {
            x.set_size(n);
            x.fill(klab::TTypeInfo<TCol>::ZERO);

            std::vector<klab::UInt32> indexes;
            std::set<klab::UInt32>    indexesSet;
            arma::Col<TCol>           residual(y);
            arma::Col<TCol>           b;

            _residualNorm = static_cast<T>(arma::norm(residual, 2));
            ThrowTraceExceptionIf(KZeroNormVectorOMPSolverException, _residualNorm==klab::TTypeInfo<T>::ZERO);

            T invYNorm = (klab::TTypeInfo<T>::UNIT / _residualNorm);
            _relativeResidualNorm = (_residualNorm * invYNorm);

            if(_isHistoryEnabled)
                _history.push(TOMPHistoryElement<T>(_residualNorm, _sparsity));

            klab::UInt32 sparsity = 0;
            klab::UInt32 sparsityLimit  = klab::Min(k, n);
            klab::UInt32 iterationLimit = klab::Min(_iterationLimit, sparsityLimit<<1);

            bool loop = true;
            while(_iterations<iterationLimit && _sparsity<sparsityLimit && _residualNorm>_tolerance && loop)
            {
                arma::Col<TCol> u; 
                phiT->apply(residual, u);

                klab::UInt32 index = 0;
                T maxValue = klab::Abs(u[0]);
                for(klab::UInt32 i=1; i<u.n_rows; ++i)
                {
                    T value = klab::Abs(u[i]);
                    if(value > maxValue)
                    {
                        maxValue = value;
                        index    = i;
                    }
                }

                loop = false;
                if(indexesSet.find(index) == indexesSet.end())
                {
                    indexes.push_back(index);
                    indexesSet.insert(index);
                    loop = true;

                    klab::TSmartPointer<TSubSystemOperator<TCol, TCol, TOp> > phiSubI = new TSubSystemOperator<TCol, TCol, TOp>(phi, indexes);
                    _leastSquareSolver.template solve<TProxyLinearOperator<TCol, TSubSystemOperator<TCol, TCol, TOp> > >(TProxyLinearOperator<TCol, TSubSystemOperator<TCol, TCol, TOp> >(phiSubI), y, b);

                    arma::Col<TCol> ySub;
                    phiSubI->apply(b, ySub);
                    residual = y - ySub;

                    T residualNorm = static_cast<T>(arma::norm(residual, 2));
                    loop = (residualNorm < _residualNorm);
                    if(loop)
                    {
                        _residualNorm = residualNorm;
                        _relativeResidualNorm = (_residualNorm * invYNorm);
                        _sparsity = static_cast<klab::UInt32>(indexes.size());

                        x.fill(klab::TTypeInfo<TCol>::ZERO);
                        klab::UInt32 indexesSize = static_cast<klab::UInt32>(indexes.size());
                        for(klab::UInt32 i=0; i<indexesSize && i<b.n_rows; ++i)
                            x[indexes[i]] = b[i];
                    }
                }

                ++_iterations;

                if(_isHistoryEnabled)
                    _history.push(TOMPHistoryElement<T>(_residualNorm, _sparsity));
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
