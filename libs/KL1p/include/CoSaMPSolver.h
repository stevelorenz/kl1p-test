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

#ifndef KL1P_COSAMPSOLVER_H
#define KL1P_COSAMPSOLVER_H

#include "Operator.h"
#include "SubSystemOperator.h"
#include "ProxyLinearOperator.h"
#include "AdjointOperator.h"
#include "History.h"
#include "CoSaMPHistoryElement.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KCoSaMPSolverException, klab::KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorCoSaMPSolverException, KCoSaMPSolverException)
KLAB_DECLARE_EXCEPTION(KNullVectorCoSaMPSolverException, KCoSaMPSolverException)
KLAB_DECLARE_EXCEPTION(KZeroNormVectorCoSaMPSolverException, KCoSaMPSolverException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T, class TOp=TOperator<TCol, TCol> >
class TCoSaMPSolver
{
public:

    TCoSaMPSolver();
    TCoSaMPSolver(const T& tolerance);
    TCoSaMPSolver(const T& tolerance, klab::UInt32 iterationLimit);
    TCoSaMPSolver(const TCoSaMPSolver<T, TCol, TOp>& solver);
    virtual ~TCoSaMPSolver();

    TCoSaMPSolver<T, TCol, TOp>&    operator=(const TCoSaMPSolver<T, TCol, TOp>& solver);

    void                        setTolerance(const T& tolerance);  
    void                        setIterationLimit(klab::UInt32 iterationLimit);  

    const T&                    tolerance() const;
    klab::UInt32         iterationLimit() const;
    const T&                    residualNorm() const;
    const T&                    relativeResidualNorm() const;
    klab::UInt32         iterations() const;

    const klab::TLeastSquareSystemSolver<T, TCol>&  leastSquareSolver() const;
    klab::TLeastSquareSystemSolver<T, TCol>&        leastSquareSolver();

    void                                        enableHistory(bool enable);
    bool                                        isHistoryEnabled() const;
    const THistory<TCoSaMPHistoryElement<T> >&  history() const;
    
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x);    // Implicit use of phi' (adjoint matrix of phi) as backward matrix.     
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x); // Explicit definition of backward matrix (phiT) to use.


private:

    T                   _tolerance;
    klab::UInt32        _iterationLimit; 

    T                   _residualNorm;  
    T                   _relativeResidualNorm; 
    klab::UInt32        _iterations;

    klab::TLeastSquareSystemSolver<T, TCol> _leastSquareSolver;

    bool                                _isHistoryEnabled;
    THistory<TCoSaMPHistoryElement<T> > _history;

};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCoSaMPSolver<T, TCol, TOp>::TCoSaMPSolver() : 
_tolerance(static_cast<T>(1e-6)), _iterationLimit(50), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCoSaMPSolver<T, TCol, TOp>::TCoSaMPSolver(const T& tolerance) : 
_tolerance(tolerance), _iterationLimit(50), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCoSaMPSolver<T, TCol, TOp>::TCoSaMPSolver(const T& tolerance, klab::UInt32 iterationLimit) : 
_tolerance(tolerance), _iterationLimit(iterationLimit), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCoSaMPSolver<T, TCol, TOp>::TCoSaMPSolver(const TCoSaMPSolver<T, TCol, TOp>& solver) : 
_tolerance(solver._tolerance), _iterationLimit(solver._iterationLimit), 
_residualNorm(solver._residualNorm), _relativeResidualNorm(solver._relativeResidualNorm), _iterations(solver._iterations), 
_leastSquareSolver(solver._leastSquareSolver),
_isHistoryEnabled(solver._isHistoryEnabled), _history(solver._history)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCoSaMPSolver<T, TCol, TOp>::~TCoSaMPSolver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCoSaMPSolver<T, TCol, TOp>& TCoSaMPSolver<T, TCol, TOp>::operator=(const TCoSaMPSolver<T, TCol, TOp>& solver)
{
    if(this != &solver)
    {
        _tolerance      = solver._tolerance;
        _iterationLimit = solver._iterationLimit;

        _residualNorm   = solver._residualNorm;
        _relativeResidualNorm  = solver._relativeResidualNorm;
        _iterations     = solver._iterations;

        _leastSquareSolver = solver._leastSquareSolver;

        _isHistoryEnabled = solver._isHistoryEnabled;
        _history          = solver._history;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TCoSaMPSolver<T, TCol, TOp>::setTolerance(const T& tolerance)
{
    _tolerance = tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TCoSaMPSolver<T, TCol, TOp>::setIterationLimit(klab::UInt32 iterationLimit)
{
    _iterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TCoSaMPSolver<T, TCol, TOp>::tolerance() const
{
    return _tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TCoSaMPSolver<T, TCol, TOp>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TCoSaMPSolver<T, TCol, TOp>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TCoSaMPSolver<T, TCol, TOp>::relativeResidualNorm() const
{
    return _relativeResidualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TCoSaMPSolver<T, TCol, TOp>::iterations() const
{
    return _iterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const klab::TLeastSquareSystemSolver<T, TCol>& TCoSaMPSolver<T, TCol, TOp>::leastSquareSolver() const
{
    return _leastSquareSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::TLeastSquareSystemSolver<T, TCol>& TCoSaMPSolver<T, TCol, TOp>::leastSquareSolver()
{
    return _leastSquareSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TCoSaMPSolver<T, TCol, TOp>::enableHistory(bool enable)
{
    _isHistoryEnabled = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TCoSaMPSolver<T, TCol, TOp>::isHistoryEnabled() const
{
    return _isHistoryEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const THistory<TCoSaMPHistoryElement<T> >& TCoSaMPSolver<T, TCol, TOp>::history() const
{
    return _history;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TCoSaMPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x)
{ 
    this->solve(y, phi, klab::TSmartPointer<TOp>(new TAdjointOperator<TCol>(phi)), sparsity, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TCoSaMPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x)
{
    _residualNorm = klab::TTypeInfo<T>::ZERO;
    _relativeResidualNorm = klab::TTypeInfo<T>::ZERO;
    _iterations = 0;
    _history.clear(); 

    ThrowTraceExceptionIf(KNullVectorCoSaMPSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorCoSaMPSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorCoSaMPSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0);  

    klab::UInt32 m = y.n_rows;
    klab::UInt32 n = phi->n();
    klab::UInt32 k = klab::Min(sparsity, n); 
    klab::UInt32 k2= ((2*k)>n ? n : (2*k)-1);

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

            T yNorm = static_cast<T>(arma::norm(y, 2));
            ThrowTraceExceptionIf(KZeroNormVectorCoSaMPSolverException, yNorm == klab::TTypeInfo<T>::ZERO);

            T invYNorm = klab::TTypeInfo<T>::UNIT / yNorm;
            _residualNorm = static_cast<T>(arma::norm(residual, 2));
            _relativeResidualNorm = _residualNorm * invYNorm;

            if(_isHistoryEnabled)
                _history.push(TCoSaMPHistoryElement<T>(_residualNorm));

            T previousRNorm  = _residualNorm;
            T previousUNorm  = klab::TTypeInfo<T>::MAX;
            T previousB0Norm = klab::TTypeInfo<T>::MAX;
            
            bool loop = true;
            while(_iterations<_iterationLimit && _residualNorm>_tolerance && loop)
            {
                // Form signal proxy.
                arma::Col<TCol> u; 
                phiT->apply(residual, u);

                std::vector<klab::TArrayElement<T> > sortedAbsU;
                for(klab::UInt32 i=0; i<u.n_rows; ++i)
                    sortedAbsU.push_back(klab::TArrayElement<T>(i, static_cast<T>(klab::Abs(u[i]))));

                std::sort(sortedAbsU.rbegin(), sortedAbsU.rend());  // std::partial_sort cannot be used here because we must take components equal to sortedAbsU[2*k-1] but where i>(2*k-1) too.

                T su2K = sortedAbsU[k2].value();

                // Identify large components.
                std::vector<klab::UInt32> j0;
                for(klab::UInt32 i=0; i<static_cast<klab::UInt32>(sortedAbsU.size()) && sortedAbsU[i].value()>klab::TTypeInfo<T>::ZERO && sortedAbsU[i].value()>=su2K; ++i)
                    j0.push_back(sortedAbsU[i].i());

                // Merge supports.
                klab::UInt32 j0Size = static_cast<klab::UInt32>(j0.size());
                for(klab::UInt32 i=0; i<j0Size; ++i)
                {
                    klab::UInt32 index = j0[i];
                    if(indexesSet.find(index) == indexesSet.end())
                    {
                        indexes.push_back(index);
                        indexesSet.insert(index);
                    }
                }

                // Signal estimation by least-squares.
                arma::Col<TCol> b0;
                klab::TSmartPointer<TSubSystemOperator<TCol, TCol, TOp> > phiSubI = new TSubSystemOperator<TCol, TCol, TOp>(phi, indexes);
                _leastSquareSolver.template solve<TProxyLinearOperator<TCol, TSubSystemOperator<TCol, TCol, TOp> > >(TProxyLinearOperator<TCol, TSubSystemOperator<TCol, TCol, TOp> >(phiSubI), y, b0);

                std::vector<klab::TArrayElement<T> > sortedAbsB0;
                for(klab::UInt32 i=0; i<b0.n_rows; ++i)
                    sortedAbsB0.push_back(klab::TArrayElement<T>(i, static_cast<T>(klab::Abs(b0[i]))));

                std::sort(sortedAbsB0.rbegin(), sortedAbsB0.rend());    // std::partial_sort cannot be used here because we must take components equal to sortedAbsB0[k-1] but where i>(k-1) too.

                T suK = sortedAbsB0[k-1].value();   

                // Prune to obtaine next approximation.
                std::vector<klab::UInt32> bIndexes;
                indexes.clear();
                for(klab::UInt32 i=0; i<static_cast<klab::UInt32>(sortedAbsB0.size()) && sortedAbsB0[i].value()>klab::TTypeInfo<T>::ZERO && sortedAbsB0[i].value()>=suK; ++i)
                {
                    klab::UInt32 index = sortedAbsB0[i].i();

                    indexes.push_back(phiSubI->indexes()[index]);
                    bIndexes.push_back(index);
                }

                indexesSet.clear();
                
                klab::UInt32 indexesSize = static_cast<klab::UInt32>(indexes.size());
                b.set_size(indexesSize);
                for(klab::UInt32 i=0; i<indexesSize; ++i)
                {
                    indexesSet.insert(indexes[i]);
                    b[i] = b0[bIndexes[i]];
                }

                // Update current samples.
                arma::Col<TCol> ySub;
                TSubSystemOperator<TCol, TCol, TOp> phiSubI2(phi, indexes);
                phiSubI2.apply(b, ySub);
                residual = y - ySub; 

                T residualNorm = static_cast<T>(arma::norm(residual, 2));
                if(residualNorm < _residualNorm)
                {
                    _residualNorm = residualNorm;
                    _relativeResidualNorm = (_residualNorm * invYNorm);

                    x.fill(klab::TTypeInfo<TCol>::ZERO);
                    klab::UInt32 indexesSize = static_cast<klab::UInt32>(indexes.size());
                    for(klab::UInt32 i=0; i<indexesSize && i<b.n_rows; ++i)
                        x[indexes[i]] = b[i];
                }

                T uNorm  = static_cast<T>(arma::norm(u, 2));
                T b0Norm = static_cast<T>(arma::norm(b0, 2));              
                loop = (klab::Equals(residualNorm, previousRNorm)==false || klab::Equals(uNorm, previousUNorm)==false || klab::Equals(b0Norm, previousB0Norm)==false);
                previousRNorm  = residualNorm;
                previousUNorm  = uNorm;
                previousB0Norm = b0Norm;

                ++_iterations;

                if(_isHistoryEnabled)
                    _history.push(TCoSaMPHistoryElement<T>(_residualNorm));
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
