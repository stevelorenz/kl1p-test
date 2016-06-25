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

#ifndef KL1P_BASISPURSUITSOLVER_H
#define KL1P_BASISPURSUITSOLVER_H

#include "Operator.h"
#include "ProxyLinearOperator.h"
#include "AdjointOperator.h"
#include "DiagonalOperator.h"
#include "ComplexProxyOperator.h"
#include "MultiplicationOperator.h"
#include "History.h"
#include "BasisPursuitHistoryElement.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KBasisPursuitSolverException, klab::KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorBasisPursuitSolverException, KBasisPursuitSolverException)
KLAB_DECLARE_EXCEPTION(KNullVectorBasisPursuitSolverException, KBasisPursuitSolverException)
KLAB_DECLARE_EXCEPTION(KZeroNormVectorBasisPursuitSolverException, KBasisPursuitSolverException)
KLAB_DECLARE_EXCEPTION(KZeroDualityGapBasisPursuitSolverException, KBasisPursuitSolverException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T, class TOp=TOperator<TCol, TCol> >
class TBasisPursuitSolver
{
public:

    TBasisPursuitSolver();
    TBasisPursuitSolver(const T& tolerance);
    TBasisPursuitSolver(const T& tolerance, klab::UInt32 iterationLimit);
    TBasisPursuitSolver(const T& tolerance, klab::UInt32 iterationLimit, klab::UInt32 backtrackingIterationLimit);
    TBasisPursuitSolver(const TBasisPursuitSolver<T, TCol, TOp>& solver);
    virtual ~TBasisPursuitSolver();

    TBasisPursuitSolver<T, TCol, TOp>&  operator=(const TBasisPursuitSolver<T, TCol, TOp>& solver);

    void                        setTolerance(const T& tolerance);  
    void                        setIterationLimit(klab::UInt32 iterationLimit); 
    void                        setBacktrackingIterationLimit(klab::UInt32 iterationLimit);
    void                        setAlpha(const T& alpha);  
    void                        setBeta(const T& beta);  
    void                        setMu(const T& mu);  

    const T&                    tolerance() const;
    klab::UInt32         iterationLimit() const;
    klab::UInt32         backtrackingIterationLimit() const;
    const T&                    alpha() const;
    const T&                    beta() const;
    const T&                    mu() const;
    const T&                    residualNorm() const;
    const T&                    relativeResidualNorm() const;
    const T&                    dualityGap() const;
    klab::UInt32         iterations() const;

    const klab::TConjugateGradientSystemSolver<T, TCol>&    conjugateGradientSolver() const;
    klab::TConjugateGradientSystemSolver<T, TCol>&          conjugateGradientSolver();

    void                                                    enableHistory(bool enable);
    bool                                                    isHistoryEnabled() const;
    const THistory<TBasisPursuitHistoryElement<T> >&        history() const;

    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, arma::Col<TCol>& x);  // Implicit use of phi' (adjoint matrix of phi) as backward matrix. 
    void        solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x);   // Explicit definition of backward matrix (phiT) to use.


protected: 

    void        solve_RealVersion(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, T& sdg, klab::UInt32& iterations, THistory<TBasisPursuitHistoryElement<T> >& history);


protected:

    static TCol ComputeStepValue(const arma::Col<TCol>& fu1, const arma::Col<TCol>& fu2, const arma::Col<TCol>& lambdaU1, const arma::Col<TCol>& lambdaU2, const arma::Col<TCol>& dLambdaU1, const arma::Col<TCol>& dLambdaU2, const arma::Col<TCol>& dx, const arma::Col<TCol>& du);


private:

    template<class U, class UCol, class UOp>
    friend class    TBasisPursuitSolverSpecialisation;


private:

    T                   _tolerance;
    klab::UInt32        _iterationLimit; 
    klab::UInt32        _backtrackingIterationLimit;
    T                   _alpha;
    T                   _beta;
    T                   _mu;

    T                   _residualNorm;
    T                   _relativeResidualNorm;
    T                   _sdg;
    klab::UInt32        _iterations;

    klab::TConjugateGradientSystemSolver<T, TCol>   _conjugateGradientSolver;

    bool                                            _isHistoryEnabled;
    THistory<TBasisPursuitHistoryElement<T> >       _history;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
class TBasisPursuitSolverSpecialisation
{
public:

    static void     Solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x, TBasisPursuitSolver<T, TCol, TOp>& solver);    


private:

    TBasisPursuitSolverSpecialisation();
    TBasisPursuitSolverSpecialisation(const TBasisPursuitSolverSpecialisation<T, TCol, TOp>& spec);
    TBasisPursuitSolverSpecialisation<T, TCol, TOp>&    operator=(const TBasisPursuitSolverSpecialisation<T, TCol, TOp>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
class TBasisPursuitSolverSpecialisation<T, std::complex<TCol>, TOp>
{
public:

    static void     Solve(const arma::Col<std::complex<TCol> >& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<std::complex<TCol> >& x, TBasisPursuitSolver<T, std::complex<TCol>, TOp>& solver);


private:

    TBasisPursuitSolverSpecialisation();
    TBasisPursuitSolverSpecialisation(const TBasisPursuitSolverSpecialisation<T, std::complex<TCol>, TOp>& spec);
    TBasisPursuitSolverSpecialisation<T, std::complex<TCol>, TOp>&  operator=(const TBasisPursuitSolverSpecialisation<T, std::complex<TCol>, TOp>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TBasisPursuitSolver<T, TCol, TOp>::TBasisPursuitSolver() : 
_tolerance(static_cast<T>(1e-6)), _iterationLimit(50), _backtrackingIterationLimit(32), _alpha(static_cast<T>(0.01)), _beta(static_cast<T>(0.5)), _mu(static_cast<T>(10.0)),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _sdg(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_conjugateGradientSolver(static_cast<T>(1e-6), 200),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TBasisPursuitSolver<T, TCol, TOp>::TBasisPursuitSolver(const T& tolerance) : 
_tolerance(tolerance), _iterationLimit(50), _backtrackingIterationLimit(32), _alpha(static_cast<T>(0.01)), _beta(static_cast<T>(0.5)), _mu(static_cast<T>(10.0)), 
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _sdg(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_conjugateGradientSolver(static_cast<T>(1e-6), 200),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TBasisPursuitSolver<T, TCol, TOp>::TBasisPursuitSolver(const T& tolerance, klab::UInt32 iterationLimit) : 
_tolerance(tolerance), _iterationLimit(iterationLimit), _backtrackingIterationLimit(32), _alpha(static_cast<T>(0.01)), _beta(static_cast<T>(0.5)), _mu(static_cast<T>(10.0)),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _sdg(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_conjugateGradientSolver(static_cast<T>(1e-6), 200),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TBasisPursuitSolver<T, TCol, TOp>::TBasisPursuitSolver(const T& tolerance, klab::UInt32 iterationLimit, klab::UInt32 backtrackingIterationLimit) : 
_tolerance(tolerance), _iterationLimit(iterationLimit), _backtrackingIterationLimit(backtrackingIterationLimit), _alpha(static_cast<T>(0.01)), _beta(static_cast<T>(0.5)), _mu(static_cast<T>(10.0)),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _sdg(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_conjugateGradientSolver(static_cast<T>(1e-6), 200),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TBasisPursuitSolver<T, TCol, TOp>::TBasisPursuitSolver(const TBasisPursuitSolver<T, TCol, TOp>& solver) : 
_tolerance(solver._tolerance), _iterationLimit(solver._iterationLimit), _backtrackingIterationLimit(solver._backtrackingIterationLimit), _alpha(solver._alpha), _beta(solver._beta), _mu(solver._mu),
_residualNorm(solver._residualNorm), _relativeResidualNorm(solver._relativeResidualNorm), _sdg(solver._sdg), _iterations(solver._iterations), 
_conjugateGradientSolver(solver._conjugateGradientSolver),
_isHistoryEnabled(solver._isHistoryEnabled), _history(solver._history)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TBasisPursuitSolver<T, TCol, TOp>::~TBasisPursuitSolver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TBasisPursuitSolver<T, TCol, TOp>& TBasisPursuitSolver<T, TCol, TOp>::operator=(const TBasisPursuitSolver<T, TCol, TOp>& solver)
{
    if(this != &solver)
    {
        _tolerance      = solver._tolerance;
        _iterationLimit = solver._iterationLimit;
        _backtrackingIterationLimit = solver._backtrackingIterationLimit;
        _alpha          = solver._alpha;
        _beta           = solver._beta;
        _mu             = solver._mu;

        _residualNorm         = solver._residualNorm;
        _relativeResidualNorm = solver._relativeResidualNorm;
        _sdg                  = solver._sdg;
        _iterations           = solver._iterations;

        _conjugateGradientSolver = solver._conjugateGradientSolver;

        _isHistoryEnabled = solver._isHistoryEnabled;
        _history          = solver._history;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::setTolerance(const T& tolerance)
{
    _tolerance = tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::setIterationLimit(klab::UInt32 iterationLimit)
{
    _iterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::setBacktrackingIterationLimit(klab::UInt32 iterationLimit)
{
    _backtrackingIterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::setAlpha(const T& alpha)
{
    _alpha = alpha;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::setBeta(const T& beta)
{
    _beta = beta;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::setMu(const T& mu)
{
    _mu = mu;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TBasisPursuitSolver<T, TCol, TOp>::tolerance() const
{
    return _tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TBasisPursuitSolver<T, TCol, TOp>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TBasisPursuitSolver<T, TCol, TOp>::backtrackingIterationLimit() const
{
    return _backtrackingIterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TBasisPursuitSolver<T, TCol, TOp>::alpha() const
{
    return _alpha;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TBasisPursuitSolver<T, TCol, TOp>::beta() const
{
    return _beta;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TBasisPursuitSolver<T, TCol, TOp>::mu() const
{
    return _mu;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TBasisPursuitSolver<T, TCol, TOp>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TBasisPursuitSolver<T, TCol, TOp>::relativeResidualNorm() const
{
    return _relativeResidualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TBasisPursuitSolver<T, TCol, TOp>::dualityGap() const
{
    return _sdg;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TBasisPursuitSolver<T, TCol, TOp>::iterations() const
{
    return _iterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const klab::TConjugateGradientSystemSolver<T, TCol>& TBasisPursuitSolver<T, TCol, TOp>::conjugateGradientSolver() const
{
    return _conjugateGradientSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::TConjugateGradientSystemSolver<T, TCol>& TBasisPursuitSolver<T, TCol, TOp>::conjugateGradientSolver()
{
    return _conjugateGradientSolver;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::enableHistory(bool enable)
{
    _isHistoryEnabled = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TBasisPursuitSolver<T, TCol, TOp>::isHistoryEnabled() const
{
    return _isHistoryEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const THistory<TBasisPursuitHistoryElement<T> >& TBasisPursuitSolver<T, TCol, TOp>::history() const
{
    return _history;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, arma::Col<TCol>& x)
{ 
    this->solve(y, phi, klab::TSmartPointer<TOp>(new TAdjointOperator<TCol>(phi)), x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x)
{
    TBasisPursuitSolverSpecialisation<T, TCol, TOp>::Solve(y, phi, phiT, x, *this);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolver<T, TCol, TOp>::solve_RealVersion(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, T& sdg, klab::UInt32& iterations, THistory<TBasisPursuitHistoryElement<T> >& history)
{   
    residualNorm         = klab::TTypeInfo<T>::ZERO;
    relativeResidualNorm = klab::TTypeInfo<T>::ZERO;
    sdg                  = klab::TTypeInfo<T>::ZERO;
    iterations           = 0;
    history.clear();

    ThrowTraceExceptionIf(KNullVectorBasisPursuitSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorBasisPursuitSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorBasisPursuitSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0); 

    klab::UInt32 m = y.n_rows; 
    klab::UInt32 n = phi->n();

    if(n > 0)
    {         
        x.set_size(n);
        x.fill(klab::TTypeInfo<TCol>::ZERO);

        typedef kl1p::TMultiplicationOperator<TCol, TCol, TCol, TOp, kl1p::TMultiplicationOperator<TCol, TCol, TCol, kl1p::TDiagonalOperator<TCol>, TOp> >  KAtAOperator;

        bool earlyStop = false;

        arma::Col<TCol> x0;
        phiT->apply(y, x0);
        arma::Col<TCol> u(x0.n_rows);
        x = x0;

        T maxX0 = klab::TTypeInfo<T>::MIN;
        for(klab::UInt32 i=0; i<x0.n_rows; ++i)
        {
            T absX0 = klab::Abs(x0[i]);
            if(absX0 > maxX0)
                maxX0 = absX0;

            u[i] = static_cast<TCol>(absX0 * static_cast<T>(0.95));
        }

        maxX0 *= static_cast<T>(0.1);
        for(klab::UInt32 i=0; i<u.n_rows; ++i)
            u[i] += maxX0;

        arma::Col<TCol> fu1( x - u);
        arma::Col<TCol> fu2(-x - u);
        arma::Col<TCol> invFu1(fu1.n_rows);
        arma::Col<TCol> invFu2(fu2.n_rows);       
        for(klab::UInt32 i=0; i<invFu1.n_rows; ++i)
        {
            if(fu1[i] == klab::TTypeInfo<TCol>::ZERO)
                fu1[i] = klab::TTypeInfo<TCol>::EPSILON;

            if(fu2[i] == klab::TTypeInfo<TCol>::ZERO)
                fu2[i] = klab::TTypeInfo<TCol>::EPSILON;

            invFu1[i] = (klab::TTypeInfo<TCol>::UNIT / fu1[i]);  
            invFu2[i] = (klab::TTypeInfo<TCol>::UNIT / fu2[i]); 
        }

        arma::Col<TCol> lambdaU1(u.n_rows);
        arma::Col<TCol> lambdaU2(u.n_rows);
        for(klab::UInt32 i=0; i<lambdaU1.n_rows; ++i)
        {
            lambdaU1[i] = -invFu1[i];
            lambdaU2[i] = -invFu2[i];
        }

        arma::Col<TCol> v;
        arma::Col<TCol> atv;
        arma::Col<TCol> residual;
        phi->apply(lambdaU1-lambdaU2, v);
        v = -v;
        phiT->apply(v, atv);
        phi->apply(x, residual);
        residual -= y;

        sdg = -(arma::dot(fu1, lambdaU1) + arma::dot(fu2, lambdaU2));
        ThrowTraceExceptionIf(KZeroDualityGapBasisPursuitSolverException, sdg==klab::TTypeInfo<T>::ZERO);

        T tau = (_mu * (x.n_rows<<1)) / sdg;
        T invTau = (klab::TTypeInfo<T>::UNIT / tau);

        arma::Col<TCol> rCent(n<<1);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            rCent[i]   = -(lambdaU1[i] * fu1[i]) - invTau;  
            rCent[n+i] = -(lambdaU2[i] * fu2[i]) - invTau;
        }

        arma::Col<TCol> rDual(n<<1);
        for(klab::UInt32 i=0; i<n; ++i)
        {
            rDual[i]   = (lambdaU1[i]-lambdaU2[i]) + atv[i];
            rDual[n+i] = klab::TTypeInfo<TCol>::UNIT - (lambdaU1[i]+lambdaU2[i]);
        }

        arma::Col<TCol> rCol(rCent.n_rows + rDual.n_rows + residual.n_rows);
        for(klab::UInt32 i=0; i<rDual.n_rows; ++i)
            rCol[i] = rDual[i];

        for(klab::UInt32 i=0; i<rCent.n_rows; ++i)
            rCol[rDual.n_rows+i] = rCent[i];

        for(klab::UInt32 i=0; i<residual.n_rows; ++i)
            rCol[rDual.n_rows+rCent.n_rows+i] = residual[i];

        T yNorm = static_cast<T>(arma::norm(y, 2));
        ThrowTraceExceptionIf(KZeroNormVectorBasisPursuitSolverException, yNorm==klab::TTypeInfo<T>::ZERO);
        T invYNorm = klab::TTypeInfo<T>::UNIT / yNorm;

         residualNorm = static_cast<T>(arma::norm(rCol, 2));
         relativeResidualNorm = residualNorm * invYNorm; 

        if(_isHistoryEnabled)
            history.push(TBasisPursuitHistoryElement<T>(residualNorm, sdg));   

        while(iterations<_iterationLimit && sdg>_tolerance && earlyStop==false)
        {
            arma::Col<TCol> w1(n);
            arma::Col<TCol> w2(n);
            arma::Col<TCol> w3 = -residual;
            for(klab::UInt32 i=0; i<w1.n_rows; ++i)
            {
                w1[i] = (-invTau * (-invFu1[i] + invFu2[i])) - atv[i];
                w2[i] = -klab::TTypeInfo<TCol>::UNIT - (invTau*(invFu1[i]+invFu2[i]));
            }

            arma::Col<TCol> lambdaU1InvFu1(n);
            arma::Col<TCol> lambdaU2InvFu2(n);
            for(klab::UInt32 i=0; i<lambdaU1InvFu1.n_rows; ++i)
            {
                lambdaU1InvFu1[i] = (lambdaU1[i] * invFu1[i]);
                lambdaU2InvFu2[i] = (lambdaU2[i] * invFu2[i]);
            }

            arma::Col<TCol> sigma1(-lambdaU1InvFu1 - lambdaU2InvFu2);
            arma::Col<TCol> sigma2( lambdaU1InvFu1 - lambdaU2InvFu2);
            arma::Col<TCol> sigmaX(n);
            arma::Col<TCol> invSigma1(sigma1.n_rows);
            arma::Col<TCol> invSigmaX(n);
            for(klab::UInt32 i=0; i<sigmaX.n_rows; ++i)
            {
                if(sigma1[i] == klab::TTypeInfo<TCol>::ZERO)
                    sigma1[i] = klab::TTypeInfo<TCol>::EPSILON;
                
                invSigma1[i] = (klab::TTypeInfo<TCol>::UNIT / sigma1[i]);
                sigmaX[i]    = sigma1[i] - ((sigma2[i]*sigma2[i])*invSigma1[i]);
                if(sigmaX[i] == klab::TTypeInfo<TCol>::ZERO)
                    sigmaX[i] = klab::TTypeInfo<TCol>::EPSILON;
                
                invSigmaX[i] = (klab::TTypeInfo<TCol>::UNIT / sigmaX[i]);
            }

            arma::Col<TCol> waIn(n);
            arma::Col<TCol> waOut;
            for(klab::UInt32 i=0; i<waIn.n_rows; ++i)
                waIn[i] = (w1[i]*invSigmaX[i]) - (w2[i]*sigma2[i])/(sigmaX[i]*sigma1[i]);

            phi->apply(waIn, waOut);
            arma::Col<TCol> w1p(waOut - w3);            

            arma::Col<TCol> dv;
            arma::Col<TCol> atdv;   
            klab::TSmartPointer<KAtAOperator> ataOp = new KAtAOperator(phi, new kl1p::TMultiplicationOperator<TCol, TCol, TCol, kl1p::TDiagonalOperator<TCol>, TOp>(new kl1p::TDiagonalOperator<TCol>(invSigmaX), phiT));
            _conjugateGradientSolver.template solve<TProxyLinearOperator<TCol, KAtAOperator> >(kl1p::TProxyLinearOperator<TCol, KAtAOperator>(ataOp), w1p, dv);
            phiT->apply(dv, atdv);

            arma::Col<TCol> dx(n);
            for(klab::UInt32 i=0; i<dx.n_rows; ++i)
                dx[i] = ((w1[i] - ((w2[i]*sigma2[i])*invSigma1[i]) - atdv[i]) * invSigmaX[i]);

            arma::Col<TCol> adx;
            phi->apply(dx, adx);

            arma::Col<TCol> du(n);
            for(klab::UInt32 i=0; i<du.n_rows; ++i)
                du[i] = ((w2[i] - (sigma2[i]*dx[i])) * invSigma1[i]);

            arma::Col<TCol> dLambdaU1(n);
            arma::Col<TCol> dLambdaU2(n);
            for(klab::UInt32 i=0; i<dLambdaU1.n_rows; ++i)
            {
                dLambdaU1[i] = ((lambdaU1[i]*invFu1[i])*(du[i]-dx[i]) - lambdaU1[i] - (invTau*invFu1[i]));
                dLambdaU2[i] = ((lambdaU2[i]*invFu2[i])*(dx[i]+du[i]) - lambdaU2[i] - (invTau*invFu2[i]));
            }


            // Backtracking line search.   
            arma::Col<TCol> xp;
            arma::Col<TCol> up;
            arma::Col<TCol> vp;
            arma::Col<TCol> atvp;
            arma::Col<TCol> lambdaU1p;
            arma::Col<TCol> lambdaU2p;           
            arma::Col<TCol> fu1p;
            arma::Col<TCol> fu2p;
            arma::Col<TCol> resp;

            TCol s = TBasisPursuitSolver<T, TCol, TOp>::ComputeStepValue(fu1, fu2, lambdaU1, lambdaU2, dLambdaU1, dLambdaU2, dx, du);
                  
            earlyStop = (earlyStop || klab::Equals(s, klab::TTypeInfo<TCol>::ZERO));
            if(earlyStop == false)
            {
                bool blsCondition = true;
                for(klab::UInt32 iBls=0; iBls<_backtrackingIterationLimit && blsCondition && klab::Equals(s, klab::TTypeInfo<TCol>::ZERO)==false; ++iBls)
                {
                    xp        = x + s*dx;
                    up        = u + s*du;
                    vp        = v + s*dv;
                    atvp      = atv + s*atdv;
                    lambdaU1p = lambdaU1 + s*dLambdaU1;
                    lambdaU2p = lambdaU2 + s*dLambdaU2;
                    resp      = residual + s*adx;               
                    fu1p      =  xp-up;
                    fu2p      = -xp-up;
                    
                    arma::Col<TCol> rcp(n<<1);
                    for(klab::UInt32 i=0; i<n; ++i)
                    {
                        rcp[i]   = -(lambdaU1p[i] * fu1p[i]) - invTau;  
                        rcp[n+i] = -(lambdaU2p[i] * fu2p[i]) - invTau;
                    }

                    arma::Col<TCol> rdp(n<<1);
                    for(klab::UInt32 i=0; i<n; ++i)
                    {
                        rdp[i]   = (lambdaU1p[i]-lambdaU2p[i]) + atvp(i);
                        rdp[n+i] = klab::TTypeInfo<TCol>::UNIT - (lambdaU1p[i]+lambdaU2p[i]);
                    }

                    arma::Col<TCol> rColp(rcp.n_rows + rdp.n_rows + resp.n_rows);
                    for(klab::UInt32 i=0; i<rdp.n_rows; ++i)
                        rColp[i] = rdp[i];

                    for(klab::UInt32 i=0; i<rcp.n_rows; ++i)
                        rColp[rdp.n_rows+i] = rcp[i];

                    for(klab::UInt32 i=0; i<resp.n_rows; ++i)
                        rColp[rdp.n_rows+rcp.n_rows+i] = resp[i];

                    T resNormp = static_cast<T>(arma::norm(rColp, 2));
                    blsCondition = (resNormp > ((klab::TTypeInfo<T>::UNIT-(_alpha*s))*residualNorm));

                    s *= _beta;
                }

                if(blsCondition == false)
                    x = xp;

                // Prepare next iteration.
                u        = up;
                v        = vp;
                atv      = atvp;
                fu1      = fu1p;
                fu2      = fu2p;
                lambdaU1 = lambdaU1p;
                lambdaU2 = lambdaU2p;
                residual = resp;

                for(klab::UInt32 i=0; i<invFu1.n_rows; ++i)
                {
                    if(fu1[i] == klab::TTypeInfo<TCol>::ZERO)
                        fu1[i] = klab::TTypeInfo<TCol>::EPSILON;

                    if(fu2[i] == klab::TTypeInfo<TCol>::ZERO)
                        fu2[i] = klab::TTypeInfo<TCol>::EPSILON;
                    
                    invFu1[i] = (klab::TTypeInfo<TCol>::UNIT / fu1[i]);  
                    invFu2[i] = (klab::TTypeInfo<TCol>::UNIT / fu2[i]); 
                }

                // Surrogate duality gap.
                sdg = -(arma::dot(fu1, lambdaU1) + arma::dot(fu2, lambdaU2));
                ThrowTraceExceptionIf(KZeroDualityGapBasisPursuitSolverException, sdg==klab::TTypeInfo<T>::ZERO);

                tau = (_mu * (x.n_rows<<1)) / sdg;
                invTau = (klab::TTypeInfo<T>::UNIT / tau);

                for(klab::UInt32 i=0; i<n; ++i)
                {
                    rCent[i]   = -(lambdaU1[i] * fu1[i]) - invTau;  
                    rCent[n+i] = -(lambdaU2[i] * fu2[i]) - invTau;
                }

                for(klab::UInt32 i=0; i<n; ++i)
                {
                    rDual[i]   = (lambdaU1[i]-lambdaU2[i]) + atv[i];
                    rDual[n+i] = klab::TTypeInfo<TCol>::UNIT - (lambdaU1[i]+lambdaU2[i]);
                }

                for(klab::UInt32 i=0; i<rDual.n_rows; ++i)
                    rCol[i] = rDual[i];

                for(klab::UInt32 i=0; i<rCent.n_rows; ++i)
                    rCol[rDual.n_rows+i] = rCent[i];

                for(klab::UInt32 i=0; i<residual.n_rows; ++i)
                    rCol[rDual.n_rows+rCent.n_rows+i] = residual[i];

                residualNorm = static_cast<T>(arma::norm(rCol, 2));
                relativeResidualNorm = residualNorm * invYNorm; 
            }                

            ++iterations;

            if(_isHistoryEnabled)
                history.push(TBasisPursuitHistoryElement<T>(residualNorm, sdg));  
        }
    }
    else
    {
        x.set_size(0);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCol TBasisPursuitSolver<T, TCol, TOp>::ComputeStepValue(const arma::Col<TCol>& fu1, const arma::Col<TCol>& fu2, const arma::Col<TCol>& lambdaU1, const arma::Col<TCol>& lambdaU2, const arma::Col<TCol>& dLambdaU1, const arma::Col<TCol>& dLambdaU2, const arma::Col<TCol>& dx, const arma::Col<TCol>& du)
{
    std::vector<klab::UInt32> indp;
    std::vector<klab::UInt32> indn;
    for(klab::UInt32 i=0; i<dLambdaU1.n_rows; ++i)
    {
        if(dLambdaU1[i] < klab::TTypeInfo<TCol>::ZERO)
            indp.push_back(i);

        if(dLambdaU2[i] < klab::TTypeInfo<TCol>::ZERO)
            indn.push_back(i);
    }

    TCol s = klab::TTypeInfo<TCol>::UNIT;
    klab::UInt32 size = static_cast<klab::UInt32>(indp.size());
    for(klab::UInt32 i=0; i<size; ++i)
    {
        TCol value = (-lambdaU1[indp[i]] / dLambdaU1[indp[i]]);
        if(value < s)
            s = value;
    }

    size = static_cast<klab::UInt32>(indn.size());
    for(klab::UInt32 i=0; i<size; ++i)
    {
        TCol value = (-lambdaU2[indn[i]] / dLambdaU2[indn[i]]);
        if(value < s)
            s = value;
    }

    indp.clear();
    indn.clear();
    for(klab::UInt32 i=0; i<dx.n_rows; ++i)
    {
        if((dx[i]-du[i]) > klab::TTypeInfo<TCol>::ZERO)
            indp.push_back(i);

        if((-dx[i]-du[i]) > klab::TTypeInfo<TCol>::ZERO)
            indn.push_back(i);
    }

    size = static_cast<klab::UInt32>(indp.size());
    for(klab::UInt32 i=0; i<size; ++i)
    {
        TCol value = (-fu1[indp[i]] / (dx[indp[i]]-du[indp[i]]));
        if(value < s)
            s = value;
    }

    size = static_cast<klab::UInt32>(indn.size());
    for(klab::UInt32 i=0; i<size; ++i)
    {
        TCol value = (-fu2[indn[i]] / (-dx[indn[i]]-du[indn[i]]));
        if(value < s)
            s = value;
    }

    return (static_cast<TCol>(0.99) * s);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolverSpecialisation<T, TCol, TOp>::Solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<TCol>& x, TBasisPursuitSolver<T, TCol, TOp>& solver)
{
    solver.solve_RealVersion(y, phi, phiT, x, solver._residualNorm, solver._relativeResidualNorm, solver._sdg, solver._iterations, solver._history);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TBasisPursuitSolverSpecialisation<T, std::complex<TCol>, TOp>::Solve(const arma::Col<std::complex<TCol> >& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, arma::Col<std::complex<TCol> >& x, TBasisPursuitSolver<T, std::complex<TCol>, TOp>& solver)
{
    ThrowTraceExceptionIf(KNullVectorBasisPursuitSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorBasisPursuitSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorBasisPursuitSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0); 

    klab::UInt32 n  = y.n_rows;
    klab::UInt32 rn = (n<<1); 
      
    arma::Col<TCol> ry(rn);
    arma::Col<TCol> rx;
    for(klab::UInt32 i=0; i<n; ++i)
    {
        ry[i]   = y[i].real();
        ry[n+i] = y[i].imag();
    }

    TBasisPursuitSolver<TCol, TCol> bp(solver.tolerance(), solver.iterationLimit(), solver.backtrackingIterationLimit());
    bp.setAlpha(solver.alpha());
    bp.setBeta(solver.beta());
    bp.setMu(solver.mu());
    bp.enableHistory(solver.isHistoryEnabled());
    bp.conjugateGradientSolver().setTolerance(solver.conjugateGradientSolver().tolerance());
    bp.conjugateGradientSolver().setIterationLimit(solver.conjugateGradientSolver().iterationLimit());

    bp.solve_RealVersion(ry, new TComplexProxyOperator<TCol, TCol, TOp>(phi), new TComplexProxyOperator<TCol, TCol, TOp>(phiT), rx, solver._residualNorm, solver._relativeResidualNorm, solver._sdg, solver._iterations, solver._history);

    // Note: solver._conjugateGradientSolver out parameters are not updated (unable to edit these parameters out of the TConjugateGradientSolver class) !
    
    x.set_size(rx.n_rows>>1);
    for(klab::UInt32 i=0; i<x.n_rows; ++i)
        x[i] = std::complex<TCol>(rx[i], rx[x.n_rows+i]); 
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
