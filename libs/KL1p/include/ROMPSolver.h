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

#ifndef KL1P_ROMPSOLVER_H
#define KL1P_ROMPSOLVER_H

#include "Operator.h"
#include "SubSystemOperator.h"
#include "ProxyLinearOperator.h"
#include "AdjointOperator.h"
#include "History.h"
#include "ROMPHistoryElement.h"





namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KROMPSolverException, klab::KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorROMPSolverException, KROMPSolverException)
KLAB_DECLARE_EXCEPTION(KNullVectorROMPSolverException, KROMPSolverException)
KLAB_DECLARE_EXCEPTION(KZeroNormVectorROMPSolverException, KROMPSolverException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T, class TOp=TOperator<TCol, TCol> >
class TROMPSolver
{
public:

    TROMPSolver();
    TROMPSolver(const T& tolerance);
    TROMPSolver(const T& tolerance, klab::UInt32 iterationLimit);
    TROMPSolver(const T& tolerance, klab::UInt32 iterationLimit, klab::UInt32 maxCoeffAddedEachIterations);
    TROMPSolver(const TROMPSolver<T, TCol, TOp>& solver);
    virtual ~TROMPSolver();

    TROMPSolver<T, TCol, TOp>&  operator=(const TROMPSolver<T, TCol, TOp>& solver);

    void                        setTolerance(const T& tolerance);  
    void                        setIterationLimit(klab::UInt32 iterationLimit);  
    void                        setMaxCoeffAddedEachIterations(klab::UInt32 count);

    const T&                    tolerance() const;
    klab::UInt32         iterationLimit() const;
    klab::UInt32         maxCoeffAddedEachIterations() const;
    const T&                    residualNorm() const;
    const T&                    relativeResidualNorm() const;
    klab::UInt32         iterations() const;
    klab::UInt32         sparsity() const;

    const klab::TLeastSquareSystemSolver<T, TCol>&  leastSquareSolver() const;
    klab::TLeastSquareSystemSolver<T, TCol>&        leastSquareSolver();

    void                                        enableHistory(bool enable);
    bool                                        isHistoryEnabled() const;
    const THistory<TROMPHistoryElement<T> >&    history() const;
    
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x);    // Implicit use of phi' (adjoint matrix of phi) as backward matrix.     
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x); // Explicit definition of backward matrix (phiT) to use.


private:

    T                   _tolerance;
    klab::UInt32        _iterationLimit;
    klab::UInt32        _maxCoeffAddedEachIterations;    

    T                   _residualNorm;
    T                   _relativeResidualNorm;
    klab::UInt32        _iterations;
    klab::UInt32        _sparsity;

    klab::TLeastSquareSystemSolver<T, TCol> _leastSquareSolver;

    bool                                    _isHistoryEnabled;
    THistory<TROMPHistoryElement<T> >       _history;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TROMPSolver<T, TCol, TOp>::TROMPSolver() : 
_tolerance(static_cast<T>(1e-6)), _iterationLimit(klab::TTypeInfo<klab::UInt32>::MAX), _maxCoeffAddedEachIterations(0), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), _sparsity(0),
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TROMPSolver<T, TCol, TOp>::TROMPSolver(const T& tolerance) : 
_tolerance(tolerance), _iterationLimit(klab::TTypeInfo<klab::UInt32>::MAX), _maxCoeffAddedEachIterations(0), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), _sparsity(0),
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TROMPSolver<T, TCol, TOp>::TROMPSolver(const T& tolerance, klab::UInt32 iterationLimit) : 
_tolerance(tolerance), _iterationLimit(iterationLimit), _maxCoeffAddedEachIterations(0), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), _sparsity(0),
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TROMPSolver<T, TCol, TOp>::TROMPSolver(const T& tolerance, klab::UInt32 iterationLimit, klab::UInt32 maxCoeffAddedEachIterations) : 
_tolerance(tolerance), _iterationLimit(iterationLimit), _maxCoeffAddedEachIterations(maxCoeffAddedEachIterations), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), _sparsity(0),
_leastSquareSolver(30, static_cast<T>(100000000), static_cast<T>(1e-6), static_cast<T>(1e-6)),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TROMPSolver<T, TCol, TOp>::TROMPSolver(const TROMPSolver<T, TCol, TOp>& solver) : 
_tolerance(solver._tolerance), _iterationLimit(solver._iterationLimit), _maxCoeffAddedEachIterations(solver._maxCoeffAddedEachIterations), 
_residualNorm(solver._residualNorm), _relativeResidualNorm(solver._relativeResidualNorm), _iterations(solver._iterations), _sparsity(solver._sparsity),
_leastSquareSolver(solver._leastSquareSolver),
_isHistoryEnabled(solver._isHistoryEnabled), _history(solver._history)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TROMPSolver<T, TCol, TOp>::~TROMPSolver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TROMPSolver<T, TCol, TOp>& TROMPSolver<T, TCol, TOp>::operator=(const TROMPSolver<T, TCol, TOp>& solver)
{
    if(this != &solver)
    {
        _tolerance                   = solver._tolerance;
        _iterationLimit              = solver._iterationLimit;
        _maxCoeffAddedEachIterations = solver._maxCoeffAddedEachIterations;

        _residualNorm  = solver._residualNorm;
        _relativeResidualNorm = solver._relativeResidualNorm;
        _iterations    = solver._iterations;
        _sparsity      = solver._sparsity;

        _leastSquareSolver = solver._leastSquareSolver;

        _isHistoryEnabled = solver._isHistoryEnabled;
        _history          = solver._history;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TROMPSolver<T, TCol, TOp>::setTolerance(const T& tolerance)
{
    _tolerance = tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TROMPSolver<T, TCol, TOp>::setIterationLimit(klab::UInt32 iterationLimit)
{
    _iterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TROMPSolver<T, TCol, TOp>::setMaxCoeffAddedEachIterations(klab::UInt32 count)
{
    _maxCoeffAddedEachIterations = count;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TROMPSolver<T, TCol, TOp>::tolerance() const
{
    return _tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TROMPSolver<T, TCol, TOp>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TROMPSolver<T, TCol, TOp>::maxCoeffAddedEachIterations() const
{
    return _maxCoeffAddedEachIterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TROMPSolver<T, TCol, TOp>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TROMPSolver<T, TCol, TOp>::relativeResidualNorm() const
{
    return _relativeResidualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TROMPSolver<T, TCol, TOp>::iterations() const
{
    return _iterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TROMPSolver<T, TCol, TOp>::sparsity() const
{
    return _sparsity;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const klab::TLeastSquareSystemSolver<T, TCol>& TROMPSolver<T, TCol, TOp>::leastSquareSolver() const
{
    return _leastSquareSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::TLeastSquareSystemSolver<T, TCol>& TROMPSolver<T, TCol, TOp>::leastSquareSolver()
{
    return _leastSquareSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TROMPSolver<T, TCol, TOp>::enableHistory(bool enable)
{
    _isHistoryEnabled = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TROMPSolver<T, TCol, TOp>::isHistoryEnabled() const
{
    return _isHistoryEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const THistory<TROMPHistoryElement<T> >& TROMPSolver<T, TCol, TOp>::history() const
{
    return _history;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TROMPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x)
{ 
    this->solve(y, phi, klab::TSmartPointer<TOp>(new TAdjointOperator<TCol>(phi)), sparsity, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TROMPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x)
{   
    _residualNorm  = klab::TTypeInfo<T>::ZERO;
    _relativeResidualNorm = klab::TTypeInfo<T>::ZERO;
    _iterations = 0;
    _sparsity   = 0;
    _history.clear();

    ThrowTraceExceptionIf(KNullVectorROMPSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorROMPSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorROMPSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0);  

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
            ThrowTraceExceptionIf(KZeroNormVectorROMPSolverException, _residualNorm==klab::TTypeInfo<T>::ZERO);

            T invYNorm = (klab::TTypeInfo<T>::UNIT / _residualNorm);            
            _relativeResidualNorm = (_residualNorm * invYNorm);

            if(_isHistoryEnabled)
                _history.push(TROMPHistoryElement<T>(_residualNorm, _sparsity));
			
            klab::UInt32 sparsityLimit  = klab::Min(k, n);
            klab::UInt32 iterationLimit = klab::Min(_iterationLimit, sparsityLimit<<1);            
            klab::UInt32 q              = (_maxCoeffAddedEachIterations==0 ? sparsityLimit : _maxCoeffAddedEachIterations);

            bool loop = true;
            while(_iterations<iterationLimit && _sparsity<sparsityLimit && _residualNorm>_tolerance && loop)
            {                    
                // Choose a set J of the n biggest coordinates in magnitude of the observation vector u = A' * residual, 
                // or all of its nonzero coordinates, whichever set is smaller.
                arma::Col<TCol> u; 
                phiT->apply(residual, u);

                std::vector<klab::TArrayElement<T> > absU;
                for(klab::UInt32 i=0; i<u.n_rows; ++i)
                    absU.push_back(klab::TArrayElement<T>(i, klab::Abs(u[i])));

                std::partial_sort(absU.begin(), absU.begin()+k, absU.end(), std::greater<klab::TArrayElement<T> >());   // Sort k greatest values only.

                // Choose J0 with the maximal energy.
                klab::UInt32 w = 0;             
                T         best = -klab::TTypeInfo<T>::UNIT;
                std::vector<klab::UInt32> j0;
                while(w < k)
                {
                    klab::UInt32 firstW = w;
                    T             first = absU[firstW].value();                        
                    T            energy = klab::TTypeInfo<T>::ZERO;                                 
                    while(w<k && absU[w].value()>=(static_cast<T>(0.5)*first) && (w-firstW)<q)
                    {
                        energy += absU[w].value() * absU[w].value();
                        ++w;
                    }

                    if(energy > best)
                    {
                        best = energy;

                        j0.clear();
                        for(klab::UInt32 i=firstW; i<w; ++i)   
                            j0.push_back(absU[i].i());
                    }
                }

                // Add the set J0 to the index set and update the residual.
                loop = false;
                klab::UInt32 j0Size = static_cast<klab::UInt32>(j0.size());
                for(klab::UInt32 i=0; i<j0Size; ++i)
                {
                    klab::UInt32 index = j0[i];
                    if(indexesSet.find(index) == indexesSet.end())
                    {
                        indexes.push_back(index);
                        indexesSet.insert(index);
                        loop = true;
                    }
                }

                if(loop)
                {
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
                    _history.push(TROMPHistoryElement<T>(_residualNorm, _sparsity));
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
