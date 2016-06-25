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

#ifndef KL1P_EMBPSOLVER_H
#define KL1P_EMBPSOLVER_H

#include "Operator.h"
#include "History.h"
#include "EMBPHistoryElement.h"
#include "AdjointOperator.h"
#include "ComplexProxyOperator.h"
#include "BlockOperator.h"
#include "AdjointBlockOperator.h"
#include "ComplexProxyBlockOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KEMBPSolverException, klab::KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorEMBPSolverException, KEMBPSolverException)
KLAB_DECLARE_EXCEPTION(KNullVectorEMBPSolverException, KEMBPSolverException)
KLAB_DECLARE_EXCEPTION(KZeroNormVectorEMBPSolverException, KEMBPSolverException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T, class TOp=TOperator<TCol, TCol> >
class TEMBPSolver
{
public:

    TEMBPSolver();
    TEMBPSolver(const T& tolerance);
    TEMBPSolver(const T& tolerance, klab::UInt32 iterationLimit);
    TEMBPSolver(const TEMBPSolver<T, TCol, TOp>& solver);
    virtual ~TEMBPSolver();

    TEMBPSolver<T, TCol, TOp>&  operator=(const TEMBPSolver<T, TCol, TOp>& solver);

    void                        setTolerance(const T& tolerance);  
    void                        setIterationLimit(klab::UInt32 iterationLimit);  
    void                        setNoiseVariance(const T& noise);
    void                        setMessageDamping(const T& damping);
    void                        setLearningDamping(const T& damping);
    void                        enableDampingLearning(bool enable);
    void                        enableParameterLearning(bool enable);
    void                        enableHomogeneous(bool enable);

    const T&                    tolerance() const;
    klab::UInt32         iterationLimit() const;
    const T&                    noiseVariance() const;
    const T&                    messageDamping() const;
    const T&                    learningDamping() const;
    bool                        isDampingLearningEnabled() const;
    bool                        isParameterLearningEnabled() const;
    bool                        isHomogeneousEnabled() const;
    const T&                    residualNorm() const;
    const T&                    relativeResidualNorm() const;
    klab::UInt32         iterations() const;

    void                                        enableHistory(bool enable);
    bool                                        isHistoryEnabled() const;
    const THistory<TEMBPHistoryElement<T> >&    history() const;
    
    void            solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x);    // Implicit use of phi' (adjoint matrix of phi) as backward matrix.     
    void            solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x); // Explicit definition of backward matrix (phiT) to use.
    void            solve(const arma::Col<TCol>& y, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phi, klab::UInt32 sparsity, arma::Col<TCol>& x);   // Implicit use of phi' (adjoint matrix of phi) as backward matrix.     
    void            solve(const arma::Col<TCol>& y, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phi, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phiT, klab::UInt32 sparsity, arma::Col<TCol>& x);   // Explicit definition of backward matrix (phiT) to use.


protected:

    void            solveEMBP(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, klab::UInt32& iterations, THistory<TEMBPHistoryElement<T> >& history);
    void            solveEMBP(const arma::Col<TCol>& y, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phi, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, klab::UInt32& iterations, THistory<TEMBPHistoryElement<T> >& history);
    void            solveEMBP_Homogeneous(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, klab::UInt32& iterations, THistory<TEMBPHistoryElement<T> >& history);
    void            solveEMBP_Generic(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, klab::UInt32& iterations, THistory<TEMBPHistoryElement<T> >& history);


protected:

    static void     ComputeFa_Homogeneous(const TCol& u, const arma::Col<TCol>& v, const TCol& rho, const TCol& mean, const TCol& sigma, arma::Col<TCol>& out);
    static void     ComputeFb_Homogeneous(const TCol& u, const arma::Col<TCol>& v, const TCol& rho, const TCol& mean, const TCol& sigma, arma::Col<TCol>& out);
    static TCol     ComputeRhoLearning_Homogeneous(const TCol& rho, const TCol& u, const arma::Col<TCol>& v, const arma::Col<TCol>& fa, const TCol& alpha, const TCol& mean, const TCol& sigma);
    static TCol     ComputeNoiseLearning_Homogeneous(const TCol& noise, const arma::Col<TCol>& y, const arma::Col<TCol>& w, const TCol& gamma);

    static void     ComputeFa_Generic(const arma::Col<TCol>& u, const arma::Col<TCol>& v, const TCol& rho, const TCol& mean, const TCol& sigma, arma::Col<TCol>& out);
    static void     ComputeFb_Generic(const arma::Col<TCol>& u, const arma::Col<TCol>& v, const TCol& rho, const TCol& mean, const TCol& sigma, arma::Col<TCol>& out);
    static TCol     ComputeRhoLearning_Generic(const TCol& rho, const arma::Col<TCol>& u, const arma::Col<TCol>& v, const arma::Col<TCol>& fa, const TCol& alpha, const TCol& mean, const TCol& sigma);
    static TCol     ComputeNoiseLearning_Generic(const TCol& noise, const arma::Col<TCol>& y, const arma::Col<TCol>& w, const arma::Col<TCol>& gamma);

    static void     ComputeDamping(const arma::Col<TCol>& u, const arma::Col<TCol>& v, const TCol& damp, arma::Col<TCol>& out);
    static TCol     ComputeMeanLearning(const arma::Col<TCol>& fa, const TCol& rho);
    static TCol     ComputeSigmaLearning(const arma::Col<TCol>& fa, const arma::Col<TCol>& fb, const TCol& rho, const TCol& mean);
    static TCol     ComputeVarianceLearning(const arma::Col<TCol>& fa, const arma::Col<TCol>& fb, const TCol& rho);
    


private:

    template<class U, class UCol, class UOp>
    friend class    TEMBPSolverSpecialisation;


private:

    T                   _tolerance;
    klab::UInt32        _iterationLimit; 

    T                   _noiseVariance;         // Estimation of the variance vector of the noise.
    T                   _messageDamping;        // Damping of the messages. 
    T                   _learningDamping;       // Damping coefficient of the learning.       
    bool                _useDampingLearning;  
    bool                _useParameterLearning;
    bool                _useHomogeneous;        // Use algorithm version made for homogeneous matrix.

    T                   _residualNorm;
    T                   _relativeResidualNorm;
    klab::UInt32        _iterations;

    bool                                _isHistoryEnabled;
    THistory<TEMBPHistoryElement<T> >   _history;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
class TEMBPSolverSpecialisation
{
public:

    static void     Solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, TEMBPSolver<T, TCol, TOp>& solver);
    static void     Solve(const arma::Col<TCol>& y, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phi, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, TEMBPSolver<T, TCol, TOp>& solver);


private:

    TEMBPSolverSpecialisation();
    TEMBPSolverSpecialisation(const TEMBPSolverSpecialisation<T, TCol, TOp>& spec);
    TEMBPSolverSpecialisation<T, TCol, TOp>&    operator=(const TEMBPSolverSpecialisation<T, TCol, TOp>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
class TEMBPSolverSpecialisation<T, std::complex<TCol>, TOp>
{
public:

    static void     Solve(const arma::Col<std::complex<TCol> >& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<std::complex<TCol> >& x, TEMBPSolver<T, std::complex<TCol>, TOp>& solver);
    static void     Solve(const arma::Col<std::complex<TCol> >& y, klab::TSmartPointer<TBlockOperator<std::complex<TCol>, std::complex<TCol>, TOp> > phi, klab::TSmartPointer<TBlockOperator<std::complex<TCol>, std::complex<TCol>, TOp> > phiT, klab::UInt32 sparsity, arma::Col<std::complex<TCol> >& x, TEMBPSolver<T, std::complex<TCol>, TOp>& solver);


private:

    TEMBPSolverSpecialisation();
    TEMBPSolverSpecialisation(const TEMBPSolverSpecialisation<T, std::complex<TCol>, TOp>& spec);
    TEMBPSolverSpecialisation<T, std::complex<TCol>, TOp>&  operator=(const TEMBPSolverSpecialisation<T, std::complex<TCol>, TOp>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TEMBPSolver<T, TCol, TOp>::TEMBPSolver() : 
_tolerance(static_cast<T>(1e-6)), _iterationLimit(1000), 
_noiseVariance(klab::TTypeInfo<T>::ZERO), _messageDamping(static_cast<T>(0.5)), _learningDamping(static_cast<T>(0.5)), _useDampingLearning(false), _useParameterLearning(false), _useHomogeneous(false),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TEMBPSolver<T, TCol, TOp>::TEMBPSolver(const T& tolerance) : 
_tolerance(tolerance), _iterationLimit(1000), 
_noiseVariance(klab::TTypeInfo<T>::ZERO), _messageDamping(static_cast<T>(0.5)), _learningDamping(static_cast<T>(0.5)), _useDampingLearning(false), _useParameterLearning(false), _useHomogeneous(false),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0), 
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TEMBPSolver<T, TCol, TOp>::TEMBPSolver(const T& tolerance, klab::UInt32 iterationLimit) : 
_tolerance(tolerance), _iterationLimit(iterationLimit), 
_noiseVariance(klab::TTypeInfo<T>::ZERO), _messageDamping(static_cast<T>(0.5)), _learningDamping(static_cast<T>(0.5)), _useDampingLearning(false), _useParameterLearning(false), _useHomogeneous(false),
_residualNorm(klab::TTypeInfo<T>::ZERO), _relativeResidualNorm(klab::TTypeInfo<T>::ZERO), _iterations(0),
_isHistoryEnabled(false), _history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TEMBPSolver<T, TCol, TOp>::TEMBPSolver(const TEMBPSolver<T, TCol, TOp>& solver) : 
_tolerance(solver._tolerance), _iterationLimit(solver._iterationLimit), 
_noiseVariance(solver._noiseVariance), _messageDamping(solver._messageDamping), _learningDamping(solver._learningDamping), _useDampingLearning(solver._useDampingLearning), _useParameterLearning(solver._useParameterLearning), _useHomogeneous(solver._useHomogeneous),
_residualNorm(solver._residualNorm), _relativeResidualNorm(solver._relativeResidualNorm), _iterations(solver._iterations), 
_isHistoryEnabled(solver._isHistoryEnabled), _history(solver._history)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TEMBPSolver<T, TCol, TOp>::~TEMBPSolver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TEMBPSolver<T, TCol, TOp>& TEMBPSolver<T, TCol, TOp>::operator=(const TEMBPSolver<T, TCol, TOp>& solver)
{
    if(this != &solver)
    {
        _tolerance      = solver._tolerance;
        _iterationLimit = solver._iterationLimit;

        _noiseVariance        = solver._noiseVariance;
        _messageDamping       = solver._messageDamping;
        _learningDamping      = solver._learningDamping;
        _useDampingLearning   = solver._useDampingLearning;
        _useParameterLearning = solver._useParameterLearning;
        _useHomogeneous       = solver._useHomogeneous;

        _residualNorm = solver._residualNorm;
        _relativeResidualNorm = solver._relativeResidualNorm;
        _iterations = solver._iterations;

        _isHistoryEnabled = solver._isHistoryEnabled;
        _history          = solver._history;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::setTolerance(const T& tolerance)
{
    _tolerance = tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::setIterationLimit(klab::UInt32 iterationLimit)
{
    _iterationLimit = iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::setNoiseVariance(const T& noise)
{
    _noiseVariance = noise;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::setMessageDamping(const T& damping)
{
    _messageDamping = damping;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::setLearningDamping(const T& damping)
{
    _learningDamping = damping;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::enableDampingLearning(bool enable)
{
    _useDampingLearning = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::enableParameterLearning(bool enable)
{
    _useParameterLearning = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::enableHomogeneous(bool enable)
{
    _useHomogeneous = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TEMBPSolver<T, TCol, TOp>::tolerance() const
{
    return _tolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TEMBPSolver<T, TCol, TOp>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TEMBPSolver<T, TCol, TOp>::noiseVariance() const
{
    return _noiseVariance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TEMBPSolver<T, TCol, TOp>::messageDamping() const
{
    return _messageDamping;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TEMBPSolver<T, TCol, TOp>::learningDamping() const
{
    return _learningDamping;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TEMBPSolver<T, TCol, TOp>::isDampingLearningEnabled() const
{
    return _useDampingLearning;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TEMBPSolver<T, TCol, TOp>::isParameterLearningEnabled() const
{
    return _useParameterLearning;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TEMBPSolver<T, TCol, TOp>::isHomogeneousEnabled() const
{
    return _useHomogeneous;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TEMBPSolver<T, TCol, TOp>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const T& TEMBPSolver<T, TCol, TOp>::relativeResidualNorm() const
{
    return _relativeResidualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline klab::UInt32 TEMBPSolver<T, TCol, TOp>::iterations() const
{
    return _iterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::enableHistory(bool enable)
{
    _isHistoryEnabled = enable;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline bool TEMBPSolver<T, TCol, TOp>::isHistoryEnabled() const
{
    return _isHistoryEnabled;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline const THistory<TEMBPHistoryElement<T> >& TEMBPSolver<T, TCol, TOp>::history() const
{
    return _history;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::UInt32 sparsity, arma::Col<TCol>& x)
{ 
    this->solve(y, phi, klab::TSmartPointer<TOp>(new TAdjointOperator<TCol, TCol, TOp>(phi)), sparsity, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x)
{   
    TEMBPSolverSpecialisation<T, TCol, TOp>::Solve(y, phi, phiT, sparsity, x, *this);    
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phi, klab::UInt32 sparsity, arma::Col<TCol>& x)
{ 
    this->solve(y, phi, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> >(new TAdjointBlockOperator<TCol, TCol, TOp, TBlockOperator<TCol, TCol, TOp> >(phi)), sparsity, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::solve(const arma::Col<TCol>& y, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phi, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phiT, klab::UInt32 sparsity, arma::Col<TCol>& x)
{   
    TEMBPSolverSpecialisation<T, TCol, TOp>::Solve(y, phi, phiT, sparsity, x, *this);    
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::solveEMBP(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, klab::UInt32& iterations, THistory<TEMBPHistoryElement<T> >& history)
{
    if(_useHomogeneous) this->solveEMBP_Homogeneous(y, phi, phiT, sparsity, x, residualNorm, relativeResidualNorm, iterations, history);
    else                this->solveEMBP_Generic(y, phi, phiT, sparsity, x, residualNorm, relativeResidualNorm, iterations, history);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::solveEMBP(const arma::Col<TCol>& y, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phi, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, klab::UInt32& iterations, THistory<TEMBPHistoryElement<T> >& history)
{
    residualNorm = klab::TTypeInfo<T>::ZERO;
    relativeResidualNorm = klab::TTypeInfo<T>::ZERO;
    iterations = 0;
    history.clear();

    ThrowTraceExceptionIf(KNullVectorEMBPSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorEMBPSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorEMBPSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0); 

    klab::UInt32 m = y.n_rows;   
    klab::UInt32 n = phi->n();
    klab::UInt32 k = klab::Min(sparsity, n);  
    klab::UInt32 mb = phi->countBlockRows();
    klab::UInt32 nb = phi->countBlockColumns();

    if(n > 0)
    {      
        if(k > 0)
        {
            x.set_size(n);
            x.fill(klab::TTypeInfo<TCol>::ZERO);

            TCol invN      = (klab::TTypeInfo<TCol>::UNIT / static_cast<TCol>(n));
            TCol alpha     = (static_cast<TCol>(m) / static_cast<TCol>(n)); // Measurement density.
            TCol rho       = (static_cast<TCol>(k) / static_cast<TCol>(n)); // Estimation of the signal density.
            TCol mean      = klab::TTypeInfo<TCol>::ZERO;                   // Estimation of the mean of the Gaussian.
            TCol sigma     = klab::TTypeInfo<TCol>::UNIT;                   // Estimation of the sigma (sqrt(variance)) of the Gaussian.
            TCol variance  = (sigma*sigma);                                 // Estimation of the variance of the Gaussian.
            TCol noise     = _noiseVariance;
            TCol mdamping  = static_cast<TCol>(_messageDamping);
            TCol pdamping  = static_cast<TCol>(_learningDamping);

            std::vector<klab::UInt32> mSizes(mb);
            for(klab::UInt32 i=0; i<mb; ++i)
            {
                klab::TSmartPointer<TOp> op = phi->block(i, 0);
                ThrowTraceExceptionIf(KNullOperatorException, op==0);

                mSizes[i] = op->m();
            }

            std::vector<klab::UInt32> nSizes(nb);
            for(klab::UInt32 j=0; j<nb; ++j)
            {
                klab::TSmartPointer<TOp> op = phi->block(0, j);
                ThrowTraceExceptionIf(KNullOperatorException, op==0);

                nSizes[j] = op->n();
            }

            arma::Col<TCol> uP(nb);
            for(klab::UInt32 i=0; i<uP.n_rows; ++i)
                uP[i] = klab::KRandom::Instance().generate<TCol>(klab::TTypeInfo<TCol>::ZERO, klab::TTypeInfo<TCol>::UNIT);

            arma::Col<TCol> u(n);
            for(klab::UInt32 j=0, k=0; j<nb; ++j)
            {
                klab::UInt32 nOp = nSizes[j];
                for(klab::UInt32 i=0; i<nOp && k<u.n_rows; ++i, ++k)
                    u[k] = uP[j];
            }

            arma::Col<TCol> gammaQ(mb);
            for(klab::UInt32 i=0; i<gammaQ.n_rows; ++i)
                gammaQ[i] = klab::KRandom::Instance().generate<TCol>(klab::TTypeInfo<TCol>::ZERO+klab::TTypeInfo<TCol>::EPSILON, klab::TTypeInfo<TCol>::UNIT);

            arma::Col<TCol> gamma(m);
            for(klab::UInt32 i=0, k=0; i<mb; ++i)
            {
                klab::UInt32 mOp = mSizes[i];
                for(klab::UInt32 j=0; j<mOp && k<gamma.n_rows; ++j, ++k)
                    gamma[k] = gammaQ[i];
            }

            arma::Col<TCol> v(n);        
            for(klab::UInt32 i=0; i<v.n_rows; ++i)
                v[i] = -klab::TTypeInfo<T>::UNIT + (static_cast<TCol>(2) * klab::KRandom::Instance().generate<TCol>(klab::TTypeInfo<TCol>::ZERO, klab::TTypeInfo<TCol>::UNIT));

            arma::Col<TCol> w(y);               

            T rNorm = static_cast<T>(arma::norm(y, 2));
            residualNorm = rNorm;
            ThrowTraceExceptionIf(KZeroNormVectorEMBPSolverException, residualNorm==klab::TTypeInfo<T>::ZERO);

            T invYNorm = (klab::TTypeInfo<T>::UNIT / residualNorm);
            relativeResidualNorm = (residualNorm * invYNorm); 
            TCol avgDiff = klab::TTypeInfo<TCol>::MAX;

            if(_isHistoryEnabled)
                history.push(TEMBPHistoryElement<T>(residualNorm));            

            arma::Col<TCol> fa;
            TEMBPSolver<T, TCol, TOp>::ComputeFa_Generic(u, v, rho, mean, sigma, fa);
            x = fa;

            while(iterations<_iterationLimit && rNorm>_tolerance)  
            {
                arma::Col<TCol> invGammaQ(gammaQ.n_rows);
                for(klab::UInt32 i=0; i<invGammaQ.n_rows; ++i)
                {
                    TCol gammaQNoise = static_cast<TCol>(gammaQ[i]+noise);
                    if(gammaQNoise == klab::TTypeInfo<TCol>::ZERO)
                        gammaQNoise = klab::TTypeInfo<TCol>::EPSILON;

                    invGammaQ[i]  = klab::TTypeInfo<TCol>::UNIT / gammaQNoise;
                    invGammaQ[i] *= static_cast<TCol>(mSizes[i]);
                    invGammaQ[i] *= invN;
                }

                arma::Col<TCol> invGamma(gamma.n_rows);
                for(klab::UInt32 i=0; i<invGamma.n_rows; ++i)
                {
                    TCol gammaNoise = static_cast<TCol>(gamma[i]+noise);
                    if(gammaNoise == klab::TTypeInfo<TCol>::ZERO)
                        gammaNoise = klab::TTypeInfo<TCol>::EPSILON;

                    invGamma[i] = klab::TTypeInfo<TCol>::UNIT / gammaNoise;
                }

                phiT->applyBlockVariance(invGammaQ, uP);
                for(klab::UInt32 j=0, k=0; j<nb; ++j)
                {
                    klab::UInt32 nOp = nSizes[j];
                    for(klab::UInt32 i=0; i<nOp && k<u.n_rows; ++i, ++k)
                        u[k] = uP[j];
                }

                arma::Col<TCol> ywInvGamma(y.n_rows);
                for(klab::UInt32 i=0; i<ywInvGamma.n_rows; ++i)
                    ywInvGamma[i] = (y[i]-w[i]) * invGamma[i];

                phiT->apply(ywInvGamma, v);

                for(klab::UInt32 i=0; i<v.n_rows; ++i)
                    v[i] += fa[i] * u[i];

                arma::Col<TCol> fb;
                TEMBPSolver<T, TCol, TOp>::ComputeFb_Generic(u, v, rho, mean, sigma, fb);               

                arma::Col<TCol> fbP(nb);
                fbP.fill(klab::TTypeInfo<TCol>::ZERO);
                for(klab::UInt32 i=0, k=0, size=nSizes[0]; i<fb.n_rows; ++i)
                {
                    if(i >= size)
                    {
                        ++k;
                        size += nSizes[k];
                    }

                    fbP[k] += fb[i];
                }

                for(klab::UInt32 i=0; i<fbP.n_rows; ++i)
                    fbP[i] *= invN;

                arma::Col<TCol> gammaQ2;
                phi->applyBlockVariance(fbP, gammaQ2);
                for(klab::UInt32 i=0, k=0; i<mb; ++i)
                {
                    klab::UInt32 mOp = mSizes[i];
                    for(klab::UInt32 j=0; j<mOp && k<gamma.n_rows; ++j, ++k)
                        gamma[k] = gammaQ2[i];
                }

                arma::Col<TCol> previousFa;
                if(iterations>1 && _useDampingLearning)
                    previousFa = fa;

                TEMBPSolver<T, TCol, TOp>::ComputeFa_Generic(u, v, rho, mean, sigma, fa);

                arma::Col<TCol> ys;
                phi->apply(fa, ys);

                arma::Col<TCol> phiFa(ys.n_rows);
                for(klab::UInt32 i=0; i<phiFa.n_rows; ++i)
                    phiFa[i] = ys[i] - (ywInvGamma[i] * gamma[i]);

                TEMBPSolver<T, TCol, TOp>::ComputeDamping(w, phiFa, mdamping, w);

                TEMBPSolver<T, TCol, TOp>::ComputeDamping(gammaQ, gammaQ2, mdamping, gammaQ);
                for(klab::UInt32 i=0, k=0; i<mb; ++i)
                {
                    klab::UInt32 mOp = mSizes[i];
                    for(klab::UInt32 j=0; j<mOp && k<gamma.n_rows; ++j, ++k)
                        gamma[k] = gammaQ[i];
                }

                rNorm = static_cast<T>(arma::norm(y-ys, 2));   
                if(rNorm < residualNorm)
                {
                    x = fa;
                    residualNorm = rNorm;
                    relativeResidualNorm = (residualNorm * invYNorm); 
                }

                if(rNorm > _tolerance)
                {                   
                    if(iterations>1 && _useDampingLearning)
                    {
                        TCol lastAvgDiff = avgDiff;    
                        avgDiff = klab::TTypeInfo<TCol>::ZERO;
                        for(klab::UInt32 i=0; i<fa.n_rows; ++i)
                            avgDiff += klab::Abs(previousFa[i]-fa[i]);

                        avgDiff *= invN;
                        if(avgDiff > lastAvgDiff)    
                        {
                            mdamping -= static_cast<TCol>(0.05);
                            if(mdamping < static_cast<TCol>(0.05))
                                mdamping = static_cast<TCol>(0.05);
                        }
                        else
                        {
                            mdamping += static_cast<TCol>(0.05);
                            if(mdamping > static_cast<TCol>(0.95))
                                mdamping = static_cast<TCol>(0.95);
                        }
                    }

                    if(_useParameterLearning)
                    {
                        TCol rho2  = (pdamping*rho) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeRhoLearning_Generic(rho, u, v, fa, alpha, mean, sigma));                                
                        TCol mean2 = (pdamping*mean) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeMeanLearning(fa, rho));                        
                        sigma      = (pdamping*sigma) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeSigmaLearning(fa, fb, rho, mean)); 
                        variance   = sigma*sigma;

                        if(noise > klab::TTypeInfo<TCol>::ZERO) // If _noiseVariance attribute equals zero, the measurement is considered to be noiseless.    
                            noise = (pdamping*noise) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeNoiseLearning_Generic(noise, y, w, gamma));   

                        rho  = rho2;
                        mean = mean2;

                        TEMBPSolver<T, TCol, TOp>::ComputeFa_Generic(u, v, rho, mean, sigma, fa);
                        TEMBPSolver<T, TCol, TOp>::ComputeFb_Generic(u, v, rho, mean, sigma, fb);                            
                    }
                }

                ++iterations;

                if(_isHistoryEnabled)
                    history.push(TEMBPHistoryElement<T>(rNorm));
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

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::solveEMBP_Homogeneous(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, klab::UInt32& iterations, THistory<TEMBPHistoryElement<T> >& history)
{
    residualNorm = klab::TTypeInfo<T>::ZERO;
    relativeResidualNorm = klab::TTypeInfo<T>::ZERO;
    iterations = 0;
    history.clear();

    ThrowTraceExceptionIf(KNullVectorEMBPSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorEMBPSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorEMBPSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0); 

    klab::UInt32 m = y.n_rows;   
    klab::UInt32 n = phi->n();
    klab::UInt32 k = klab::Min(sparsity, n);  

    if(n > 0)
    {      
        if(k > 0)
        {
            x.set_size(n);
            x.fill(klab::TTypeInfo<TCol>::ZERO);

            TCol invN      = (klab::TTypeInfo<TCol>::UNIT / static_cast<TCol>(n));
            TCol alpha     = (static_cast<TCol>(m) / static_cast<TCol>(n)); // Measurement density.
            TCol rho       = (static_cast<TCol>(k) / static_cast<TCol>(n)); // Estimation of the signal density.
            TCol mean      = klab::TTypeInfo<TCol>::ZERO;                   // Estimation of the mean of the Gaussian.
            TCol sigma     = klab::TTypeInfo<TCol>::UNIT;                   // Estimation of the sigma (sqrt(variance)) of the Gaussian.
            TCol variance  = (sigma*sigma);                                 // Estimation of the variance of the Gaussian.
            TCol noise     = _noiseVariance;
            TCol mdamping  = static_cast<TCol>(_messageDamping);
            TCol pdamping  = static_cast<TCol>(_learningDamping);

            TCol u     = klab::KRandom::Instance().generate<TCol>(klab::TTypeInfo<TCol>::ZERO, klab::TTypeInfo<TCol>::UNIT);
            TCol gamma = klab::TTypeInfo<TCol>::ZERO;
            while(klab::Equals(gamma, klab::TTypeInfo<TCol>::ZERO))
                gamma = static_cast<TCol>(0.5) + (static_cast<TCol>(0.5) * klab::KRandom::Instance().generate<TCol>(klab::TTypeInfo<TCol>::ZERO, klab::TTypeInfo<TCol>::UNIT));           

            arma::Col<TCol> v(n);        
            for(klab::UInt32 i=0; i<v.n_rows; ++i)
                v[i] = -klab::TTypeInfo<TCol>::UNIT + (static_cast<TCol>(2) * klab::KRandom::Instance().generate<TCol>(klab::TTypeInfo<T>::ZERO, klab::TTypeInfo<TCol>::UNIT));

            arma::Col<TCol> w(y);       
         
            T rNorm = static_cast<T>(arma::norm(y, 2));
            residualNorm = rNorm;
            ThrowTraceExceptionIf(KZeroNormVectorEMBPSolverException, residualNorm==klab::TTypeInfo<T>::ZERO);

            T invYNorm = (klab::TTypeInfo<T>::UNIT / residualNorm);
            relativeResidualNorm = (residualNorm * invYNorm);     
            TCol avgDiff = klab::TTypeInfo<TCol>::MAX;

            if(_isHistoryEnabled)
                history.push(TEMBPHistoryElement<T>(residualNorm));

            arma::Col<TCol> fa;
            TEMBPSolver<T, TCol, TOp>::ComputeFa_Homogeneous(u, v, rho, mean, sigma, fa);
            x = fa;

            while(iterations<_iterationLimit && rNorm>_tolerance)  
            {
                TCol gammaNoise = static_cast<TCol>(gamma+noise);
                if(gammaNoise == klab::TTypeInfo<TCol>::ZERO)
                    gammaNoise = klab::TTypeInfo<TCol>::EPSILON;

                TCol invGamma = klab::TTypeInfo<TCol>::UNIT / gammaNoise;
                u = (alpha * invGamma);

                arma::Col<TCol> ywInvGamma(y.n_rows);
                for(klab::UInt32 i=0; i<ywInvGamma.n_rows; ++i)
                    ywInvGamma[i] = (y[i]-w[i]) * invGamma;

                phiT->apply(ywInvGamma, v);

                for(klab::UInt32 i=0; i<v.n_rows; ++i)
                    v[i] += fa[i] * u;

                arma::Col<TCol> fb;
                TEMBPSolver<T, TCol, TOp>::ComputeFb_Homogeneous(u, v, rho, mean, sigma, fb);

                TCol a = klab::TTypeInfo<TCol>::ZERO;
                for(klab::UInt32 i=0; i<fb.n_rows; ++i)
                    a += fb[i];
                a *= invN;

                gamma = (mdamping*gamma) + ((klab::TTypeInfo<TCol>::UNIT-mdamping)*a);

                arma::Col<TCol> previousFa;
                if(iterations>1 && _useDampingLearning)
                    previousFa = fa;

                TEMBPSolver<T, TCol, TOp>::ComputeFa_Homogeneous(u, v, rho, mean, sigma, fa);

                arma::Col<TCol> ys;                               
                phi->apply(fa, ys);

                arma::Col<TCol> phiFa(ys.n_rows);
                for(klab::UInt32 i=0; i<phiFa.n_rows; ++i)
                    phiFa[i] = ys[i] - (ywInvGamma[i] * gamma);

                TEMBPSolver<T, TCol, TOp>::ComputeDamping(w, phiFa, mdamping, w);                                
                
                rNorm = static_cast<T>(arma::norm(y-ys, 2));   
                if(rNorm < residualNorm)
                {
                    x = fa;
                    residualNorm = rNorm;
                    relativeResidualNorm = (residualNorm * invYNorm); 
                }

                if((iterations+1)<_iterationLimit && rNorm>_tolerance)
                {                   
                    if(iterations>1 && _useDampingLearning)
                    {
                        TCol lastAvgDiff = avgDiff;
                        avgDiff = klab::TTypeInfo<TCol>::ZERO;
                        for(klab::UInt32 i=0; i<fa.n_rows; ++i)
                            avgDiff += klab::Abs(previousFa[i]-fa[i]);

                        avgDiff *= invN;
                        if(avgDiff > lastAvgDiff)    
                        {
                            mdamping -= static_cast<TCol>(0.05);
                            if(mdamping < static_cast<TCol>(0.05))
                                mdamping = static_cast<TCol>(0.05);
                        }
                        else
                        {
                            mdamping += static_cast<TCol>(0.05);
                            if(mdamping > static_cast<TCol>(0.95))
                                mdamping = static_cast<TCol>(0.95);
                        }
                    }

                    if(_useParameterLearning)
                    {
                        TCol rho2  = (pdamping*rho) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeRhoLearning_Homogeneous(rho, u, v, fa, alpha, mean, sigma));  
                        TCol mean2 = (pdamping*mean) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeMeanLearning(fa, rho));                        
                        sigma      = (pdamping*sigma) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeSigmaLearning(fa, fb, rho, mean));   
                        variance   = sigma*sigma;

                        if(noise > klab::TTypeInfo<TCol>::ZERO) // If _noiseVariance attribute equals zero, the measurement is considered to be noiseless. 
                            noise = (pdamping*noise) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeNoiseLearning_Homogeneous(noise, y, w, gamma));  

                        rho  = rho2;
                        mean = mean2;

                        TEMBPSolver<T, TCol, TOp>::ComputeFa_Homogeneous(u, v, rho, mean, sigma, fa);
                        TEMBPSolver<T, TCol, TOp>::ComputeFb_Homogeneous(u, v, rho, mean, sigma, fb);                            
                    }
                }
                       
                ++iterations;

                if(_isHistoryEnabled)
                    history.push(TEMBPHistoryElement<T>(rNorm));
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

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::solveEMBP_Generic(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, T& residualNorm, T& relativeResidualNorm, klab::UInt32& iterations, THistory<TEMBPHistoryElement<T> >& history)
{
    residualNorm = klab::TTypeInfo<T>::ZERO;
    relativeResidualNorm = klab::TTypeInfo<T>::ZERO;
    iterations = 0;
    history.clear();

    ThrowTraceExceptionIf(KNullVectorEMBPSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullOperatorEMBPSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullOperatorEMBPSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0); 

    klab::UInt32 m = y.n_rows;   
    klab::UInt32 n = phi->n();
    klab::UInt32 k = klab::Min(sparsity, n);  

    if(n > 0)
    {      
        if(k > 0)
        {
            x.set_size(n);
            x.fill(klab::TTypeInfo<TCol>::ZERO);

            TCol invN      = (klab::TTypeInfo<TCol>::UNIT / static_cast<TCol>(n));
            TCol alpha     = (static_cast<TCol>(m) / static_cast<TCol>(n)); // Measurement density.
            TCol rho       = (static_cast<TCol>(k) / static_cast<TCol>(n)); // Estimation of the signal density.
            TCol mean      = klab::TTypeInfo<TCol>::ZERO;                   // Estimation of the mean of the Gaussian.
            TCol sigma     = klab::TTypeInfo<TCol>::UNIT;                   // Estimation of the sigma (sqrt(variance)) of the Gaussian.
            TCol variance  = (sigma*sigma);                                 // Estimation of the variance of the Gaussian.
            TCol noise     = _noiseVariance;
            TCol mdamping  = static_cast<TCol>(_messageDamping);
            TCol pdamping  = static_cast<TCol>(_learningDamping);

            arma::Col<TCol> u(n); 
            for(klab::UInt32 i=0; i<u.n_rows; ++i)
                u[i] = klab::KRandom::Instance().generate<TCol>(klab::TTypeInfo<TCol>::ZERO, klab::TTypeInfo<TCol>::UNIT);

            arma::Col<TCol> gamma(m); 
            for(klab::UInt32 i=0; i<gamma.n_rows; ++i)
                gamma[i] = klab::KRandom::Instance().generate<TCol>(klab::TTypeInfo<TCol>::ZERO+klab::TTypeInfo<TCol>::EPSILON, klab::TTypeInfo<TCol>::UNIT);

            arma::Col<TCol> v(n);        
            for(klab::UInt32 i=0; i<v.n_rows; ++i)
                v[i] = -klab::TTypeInfo<T>::UNIT + (static_cast<TCol>(2) * klab::KRandom::Instance().generate<TCol>(klab::TTypeInfo<TCol>::ZERO, klab::TTypeInfo<TCol>::UNIT));

            arma::Col<TCol> w(y);   

            T rNorm = static_cast<T>(arma::norm(y, 2));
            residualNorm = rNorm;
            ThrowTraceExceptionIf(KZeroNormVectorEMBPSolverException, residualNorm==klab::TTypeInfo<T>::ZERO);

            T invYNorm = (klab::TTypeInfo<T>::UNIT / residualNorm);
            relativeResidualNorm = (residualNorm * invYNorm); 
            TCol avgDiff = klab::TTypeInfo<TCol>::MAX;

            if(_isHistoryEnabled)
                history.push(TEMBPHistoryElement<T>(residualNorm));            

            arma::Col<TCol> fa;
            TEMBPSolver<T, TCol, TOp>::ComputeFa_Generic(u, v, rho, mean, sigma, fa);
            x = fa;

            while(iterations<_iterationLimit && rNorm>_tolerance)  
            {
                arma::Col<TCol> invGamma(gamma.n_rows);
                for(klab::UInt32 i=0; i<invGamma.n_rows; ++i)
                {
                    TCol gammaNoise = static_cast<TCol>(gamma[i]+noise);
                    if(gammaNoise == klab::TTypeInfo<TCol>::ZERO)
                        gammaNoise = klab::TTypeInfo<TCol>::EPSILON;

                    invGamma[i] = klab::TTypeInfo<TCol>::UNIT / gammaNoise;
                }

                // Apply (Phi.^2)' * invGamma. 
                for(klab::UInt32 i=0; i<n; ++i)
                {       
                    arma::Col<TCol> col;
                    phiT->columnAdjoint(i, col);

                    u[i] = klab::TTypeInfo<TCol>::ZERO;
                    for(klab::UInt32 j=0; j<col.n_rows; ++j)
                        u[i] += invGamma[j] * col[j] * col[j];
                }

                arma::Col<TCol> ywInvGamma(y.n_rows);
                for(klab::UInt32 i=0; i<ywInvGamma.n_rows; ++i)
                    ywInvGamma[i] = (y[i]-w[i]) * invGamma[i];

                phiT->apply(ywInvGamma, v);

                for(klab::UInt32 i=0; i<v.n_rows; ++i)
                    v[i] += fa[i] * u[i];

                arma::Col<TCol> fb;
                TEMBPSolver<T, TCol, TOp>::ComputeFb_Generic(u, v, rho, mean, sigma, fb);
                
                // Apply (Phi.^2) * Fb. 
                arma::Col<TCol> gamma2(m);
                for(klab::UInt32 i=0; i<m; ++i)
                {
                    arma::Col<TCol> col;
                    phi->columnAdjoint(i, col);

                    gamma2[i] = klab::TTypeInfo<TCol>::ZERO;
                    for(klab::UInt32 j=0; j<col.n_rows; ++j)
                        gamma2[i] += fb[j] * col[j] * col[j];
                }

                arma::Col<TCol> previousFa;
                if(iterations>1 && _useDampingLearning)
                    previousFa = fa;

                TEMBPSolver<T, TCol, TOp>::ComputeFa_Generic(u, v, rho, mean, sigma, fa);

                arma::Col<TCol> ys;
                phi->apply(fa, ys);

                arma::Col<TCol> phiFa(ys.n_rows);
                for(klab::UInt32 i=0; i<phiFa.n_rows; ++i)
                    phiFa[i] = ys[i] - (ywInvGamma[i] * gamma2[i]);

                TEMBPSolver<T, TCol, TOp>::ComputeDamping(w, phiFa, mdamping, w);
                TEMBPSolver<T, TCol, TOp>::ComputeDamping(gamma, gamma2, mdamping, gamma);

                rNorm = static_cast<T>(arma::norm(y-ys, 2));   
                if(rNorm < residualNorm)
                {
                    x = fa;
                    residualNorm = rNorm;
                    relativeResidualNorm = (residualNorm * invYNorm); 
                }

                if(rNorm > _tolerance)
                {                   
                    if(iterations>1 && _useDampingLearning)
                    {
                        TCol lastAvgDiff = avgDiff;    
                        avgDiff = klab::TTypeInfo<TCol>::ZERO;
                        for(klab::UInt32 i=0; i<fa.n_rows; ++i)
                            avgDiff += klab::Abs(previousFa[i]-fa[i]);

                        avgDiff *= invN;
                        if(avgDiff > lastAvgDiff)    
                        {
                            mdamping -= static_cast<TCol>(0.05);
                            if(mdamping < static_cast<TCol>(0.05))
                                mdamping = static_cast<TCol>(0.05);
                        }
                        else
                        {
                            mdamping += static_cast<TCol>(0.05);
                            if(mdamping > static_cast<TCol>(0.95))
                                mdamping = static_cast<TCol>(0.95);
                        }
                    }

                    if(_useParameterLearning)
                    {
                        TCol rho2  = (pdamping*rho) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeRhoLearning_Generic(rho, u, v, fa, alpha, mean, sigma));                                
                        TCol mean2 = (pdamping*mean) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeMeanLearning(fa, rho));                        
                        sigma      = (pdamping*sigma) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeSigmaLearning(fa, fb, rho, mean)); 
                        variance   = sigma*sigma;

                        if(noise > klab::TTypeInfo<TCol>::ZERO) // If _noiseVariance attribute equals zero, the measurement is considered to be noiseless.    
                            noise = (pdamping*noise) + (pdamping*TEMBPSolver<T, TCol, TOp>::ComputeNoiseLearning_Generic(noise, y, w, gamma));   

                        rho  = rho2;
                        mean = mean2;

                        TEMBPSolver<T, TCol, TOp>::ComputeFa_Generic(u, v, rho, mean, sigma, fa);
                        TEMBPSolver<T, TCol, TOp>::ComputeFb_Generic(u, v, rho, mean, sigma, fb);                            
                    }
                } 

                ++iterations;

                if(_isHistoryEnabled)
                    history.push(TEMBPHistoryElement<T>(rNorm));
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

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::ComputeFa_Homogeneous(const TCol& u, const arma::Col<TCol>& v, const TCol& rho, const TCol& mean, const TCol& sigma, arma::Col<TCol>& out)
{
    TCol variance      = sigma*sigma;
    TCol invVariance   = klab::TTypeInfo<TCol>::UNIT / variance;
    TCol meanInvVar    = mean * invVariance;
    TCol mmInv2var     = (mean*mean) / (static_cast<TCol>(2)*variance);
    TCol rho_1         = (klab::TTypeInfo<TCol>::UNIT - rho);
    TCol ivu           = invVariance + u;
    TCol inv2Ivu       = klab::TTypeInfo<TCol>::UNIT / (static_cast<TCol>(2)*ivu);
    TCol rsIvuSqrtPow3 = rho / (sigma * klab::Sqrt(klab::Pow(ivu, 3)));
    TCol rsIvuSqrt     = rho / (sigma * klab::Sqrt(ivu));

    out.set_size(v.n_rows);
    for(klab::UInt32 i=0; i<out.n_rows; ++i)
    {
        TCol v1 = v[i] + meanInvVar;        

        TCol part1 = v1 * rsIvuSqrtPow3;
        TCol part2 = rho_1*klab::Exp((-v1*v1*inv2Ivu) + mmInv2var) + rsIvuSqrt; 

        out[i] = part1 / part2;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::ComputeFb_Homogeneous(const TCol& u, const arma::Col<TCol>& v, const TCol& rho, const TCol& mean, const TCol& sigma, arma::Col<TCol>& out)
{
    TCol variance      = sigma*sigma;
    TCol invVariance   = klab::TTypeInfo<TCol>::UNIT / variance;
    TCol meanInvVar    = mean * invVariance;
    TCol mmInv2var     = (mean*mean) / (static_cast<TCol>(2)*variance);
    TCol rho_1         = (klab::TTypeInfo<TCol>::UNIT - rho);
    TCol ivu           = invVariance + u;
    TCol invIvu        = klab::TTypeInfo<TCol>::UNIT / ivu;
    TCol inv2Ivu       = invIvu * static_cast<TCol>(0.5);
    TCol rsIvuSqrtPow3 = rho / (sigma * klab::Sqrt(klab::Pow(ivu, 3)));
    TCol rsIvuSqrt     = rho / (sigma * klab::Sqrt(ivu));

    out.set_size(v.n_rows);
    for(klab::UInt32 i=0; i<out.n_rows; ++i)
    {
        TCol v1             = v[i] + meanInvVar;
        TCol v12InvIvu      = v1*v1*invIvu;
        TCol expV12InvIvu   = klab::Exp(-v12InvIvu*static_cast<TCol>(0.5) + mmInv2var);
        TCol r1ExpV12InvIvu = rho_1 * expV12InvIvu;

        TCol part1 = r1ExpV12InvIvu + rsIvuSqrt;
        TCol part2 = part1 + (r1ExpV12InvIvu * v12InvIvu);
        
        out[i] = (rsIvuSqrtPow3*part2) / (part1*part1);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCol TEMBPSolver<T, TCol, TOp>::ComputeRhoLearning_Homogeneous(const TCol& rho, const TCol& u, const arma::Col<TCol>& v, const arma::Col<TCol>& fa, const TCol& alpha, const TCol& mean, const TCol& sigma)
{
    klab::UInt32 n = klab::Min(v.n_rows, fa.n_rows);

    TCol variance      = sigma*sigma;
    TCol invVariance   = klab::TTypeInfo<TCol>::UNIT / variance;
    TCol meanInvVar    = mean * invVariance;
    TCol mmInv2var     = (mean*mean) / (static_cast<TCol>(2)*variance);
    TCol rho_1         = (klab::TTypeInfo<TCol>::UNIT - rho);
    TCol ivu           = invVariance + u;
    TCol invIvu        = klab::TTypeInfo<TCol>::UNIT / ivu;
    TCol rsIvuSqrtPow3 = rho / (sigma * klab::Sqrt(klab::Pow(ivu, 3)));
    TCol rsIvuSqrt     = rho / (sigma * klab::Sqrt(ivu));

    TCol up   = klab::TTypeInfo<TCol>::ZERO;
    TCol down = klab::TTypeInfo<TCol>::ZERO;
    for(klab::UInt32 i=0; i<n; ++i)
    {
        TCol v1             = v[i] + meanInvVar;  
        TCol invV1          = klab::TTypeInfo<TCol>::UNIT / v1;
        TCol v12InvIvu      = v1*v1*invIvu;
        TCol expV12InvIvu   = klab::Exp(-v12InvIvu*static_cast<TCol>(0.5) + mmInv2var);
        TCol r1ExpV12InvIvu = rho_1 * expV12InvIvu;
        TCol invPart        = klab::TTypeInfo<TCol>::UNIT / (r1ExpV12InvIvu + rsIvuSqrt);

        up   += ivu * invV1 * fa[i];
        down += expV12InvIvu * invPart;
    }

    TCol ret = up/down;
    if(ret>alpha)                               ret = alpha;
    else if(ret<klab::TTypeInfo<TCol>::ZERO)    ret = klab::TTypeInfo<TCol>::ZERO;

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCol TEMBPSolver<T, TCol, TOp>::ComputeNoiseLearning_Homogeneous(const TCol& noise, const arma::Col<TCol>& y, const arma::Col<TCol>& w, const TCol& gamma)
{
    if(noise > klab::TTypeInfo<TCol>::ZERO)
    {
        klab::UInt32 n = klab::Min(y.n_rows, w.n_rows);

        TCol invNoise        = klab::TTypeInfo<TCol>::UNIT / noise;
        TCol gammaInvNoise   = gamma * invNoise;
        TCol gammaInvNoise_1 = gammaInvNoise + klab::TTypeInfo<TCol>::UNIT;
        TCol invGammaInvNoise_1 = klab::TTypeInfo<TCol>::UNIT / gammaInvNoise_1;
        TCol invSqGammaInvNoise_1 = invGammaInvNoise_1*invGammaInvNoise_1;

        TCol up   = klab::TTypeInfo<TCol>::ZERO;
        TCol down = klab::TTypeInfo<TCol>::ZERO;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            TCol yw = y[i]-w[i];

            up   += (yw*yw) * invSqGammaInvNoise_1;
	        down += invGammaInvNoise_1;
        }

        return (up/down);
    }
    else
    {
        return klab::TTypeInfo<TCol>::ZERO;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::ComputeFa_Generic(const arma::Col<TCol>& u, const arma::Col<TCol>& v, const TCol& rho, const TCol& mean, const TCol& sigma, arma::Col<TCol>& out)
{
    TCol variance      = sigma*sigma;
    TCol invVariance   = klab::TTypeInfo<TCol>::UNIT / variance;
    TCol meanInvVar    = mean * invVariance;
    TCol mmInv2var     = (mean*mean) / (static_cast<TCol>(2)*variance);
    TCol rho_1         = (klab::TTypeInfo<TCol>::UNIT - rho);    

    out.set_size(klab::Min(u.n_rows, v.n_rows));
    for(klab::UInt32 i=0; i<out.n_rows; ++i)
    {
        TCol ivu           = invVariance + u[i];
        TCol inv2Ivu       = klab::TTypeInfo<TCol>::UNIT / (static_cast<TCol>(2)*ivu);
        TCol rsIvuSqrtPow3 = rho / (sigma * klab::Sqrt(klab::Pow(ivu, 3)));
        TCol rsIvuSqrt     = rho / (sigma * klab::Sqrt(ivu));
        TCol v1            = v[i] + meanInvVar;        

        TCol part1 = v1 * rsIvuSqrtPow3;
        TCol part2 = rho_1*klab::Exp((-v1*v1*inv2Ivu) + mmInv2var) + rsIvuSqrt; 

        out[i] = part1 / part2;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::ComputeFb_Generic(const arma::Col<TCol>& u, const arma::Col<TCol>& v, const TCol& rho, const TCol& mean, const TCol& sigma, arma::Col<TCol>& out)
{
    TCol variance      = sigma*sigma;
    TCol invVariance   = klab::TTypeInfo<TCol>::UNIT / variance;
    TCol meanInvVar    = mean * invVariance;
    TCol mmInv2var     = (mean*mean) / (static_cast<TCol>(2)*variance);
    TCol rho_1         = (klab::TTypeInfo<TCol>::UNIT - rho);    

    out.set_size(klab::Min(u.n_rows, v.n_rows));
    for(klab::UInt32 i=0; i<out.n_rows; ++i)
    {
        TCol ivu            = invVariance + u[i];
        TCol invIvu         = klab::TTypeInfo<TCol>::UNIT / ivu;
        TCol inv2Ivu        = invIvu * static_cast<TCol>(0.5);
        TCol rsIvuSqrtPow3  = rho / (sigma * klab::Sqrt(klab::Pow(ivu, 3)));
        TCol rsIvuSqrt      = rho / (sigma * klab::Sqrt(ivu));
        TCol v1             = v[i] + meanInvVar;
        TCol v12InvIvu      = v1*v1*invIvu;
        TCol expV12InvIvu   = klab::Exp(-v12InvIvu*static_cast<TCol>(0.5) + mmInv2var);
        TCol r1ExpV12InvIvu = rho_1 * expV12InvIvu;

        TCol part1 = r1ExpV12InvIvu + rsIvuSqrt;
        TCol part2 = part1 + (r1ExpV12InvIvu * v12InvIvu);
        
        out[i] = (rsIvuSqrtPow3*part2) / (part1*part1);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCol TEMBPSolver<T, TCol, TOp>::ComputeRhoLearning_Generic(const TCol& rho, const arma::Col<TCol>& u, const arma::Col<TCol>& v, const arma::Col<TCol>& fa, const TCol& alpha, const TCol& mean, const TCol& sigma)
{
    klab::UInt32 n = klab::Min(u.n_rows, klab::Min(v.n_rows, fa.n_rows));

    TCol variance    = sigma*sigma;
    TCol invVariance = klab::TTypeInfo<TCol>::UNIT / variance;
    TCol meanInvVar  = mean * invVariance;
    TCol mmInv2var   = (mean*mean) / (static_cast<TCol>(2)*variance);
    TCol rho_1       = (klab::TTypeInfo<TCol>::UNIT - rho);    

    TCol up   = klab::TTypeInfo<TCol>::ZERO;
    TCol down = klab::TTypeInfo<TCol>::ZERO;
    for(klab::UInt32 i=0; i<n; ++i)
    {
        TCol ivu            = invVariance + u[i];
        TCol invIvu         = klab::TTypeInfo<TCol>::UNIT / ivu;
        TCol rsIvuSqrtPow3  = rho / (sigma * klab::Sqrt(klab::Pow(ivu, 3)));
        TCol rsIvuSqrt      = rho / (sigma * klab::Sqrt(ivu));
        TCol v1             = v[i] + meanInvVar;  
        TCol invV1          = klab::TTypeInfo<TCol>::UNIT / v1;
        TCol v12InvIvu      = v1*v1*invIvu;
        TCol expV12InvIvu   = klab::Exp(-v12InvIvu*static_cast<TCol>(0.5) + mmInv2var);
        TCol r1ExpV12InvIvu = rho_1 * expV12InvIvu;
        TCol invPart        = klab::TTypeInfo<TCol>::UNIT / (r1ExpV12InvIvu + rsIvuSqrt);

        up   += ivu * invV1 * fa[i];
        down += expV12InvIvu * invPart;
    }

    TCol ret = up/down;
    if(ret>alpha)                               ret = alpha;
    else if(ret<klab::TTypeInfo<TCol>::ZERO)    ret = klab::TTypeInfo<TCol>::ZERO;

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCol TEMBPSolver<T, TCol, TOp>::ComputeNoiseLearning_Generic(const TCol& noise, const arma::Col<TCol>& y, const arma::Col<TCol>& w, const arma::Col<TCol>& gamma)
{
    if(noise > klab::TTypeInfo<TCol>::ZERO)
    {
        klab::UInt32 n = klab::Min(y.n_rows, klab::Min(w.n_rows, gamma.n_rows));

        TCol invNoise = klab::TTypeInfo<TCol>::UNIT / noise;        

        TCol up   = klab::TTypeInfo<TCol>::ZERO;
        TCol down = klab::TTypeInfo<TCol>::ZERO;
        for(klab::UInt32 i=0; i<n; ++i)
        {
            TCol yw = y[i]-w[i];
            TCol gammaInvNoise = gamma[i] * invNoise;
            TCol gammaInvNoise_1 = gammaInvNoise + klab::TTypeInfo<TCol>::UNIT;
            TCol invGammaInvNoise_1 = klab::TTypeInfo<TCol>::UNIT / gammaInvNoise_1;
            TCol invSqGammaInvNoise_1 = invGammaInvNoise_1*invGammaInvNoise_1;            

            up   += (yw*yw) * invSqGammaInvNoise_1;
	        down += invGammaInvNoise_1;
        }

        return (up/down);
    }
    else
    {
        return klab::TTypeInfo<TCol>::ZERO;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolver<T, TCol, TOp>::ComputeDamping(const arma::Col<TCol>& u, const arma::Col<TCol>& v, const TCol& damp, arma::Col<TCol>& out)
{
    klab::UInt32 n = klab::Min(u.n_rows, v.n_rows);
    if(out.n_rows != n)
        out.set_size(n);

    TCol damp_1 = klab::TTypeInfo<TCol>::UNIT - damp;
    
    for(klab::UInt32 i=0; i<n; ++i)
        out[i] = (damp*u[i]) + (damp_1*v[i]);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCol TEMBPSolver<T, TCol, TOp>::ComputeMeanLearning(const arma::Col<TCol>& fa, const TCol& rho)
{
    TCol invN   = klab::TTypeInfo<TCol>::UNIT / static_cast<TCol>(fa.n_rows);
    TCol invRho = klab::TTypeInfo<TCol>::UNIT / rho;

    TCol av = klab::TTypeInfo<TCol>::ZERO;
    for(klab::UInt32 i=0; i<fa.n_rows; ++i)
        av += fa[i];

    return (av*invN*invRho);  
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCol TEMBPSolver<T, TCol, TOp>::ComputeSigmaLearning(const arma::Col<TCol>& fa, const arma::Col<TCol>& fb, const TCol& rho, const TCol& mean)
{
    klab::UInt32 n = klab::Min(fa.n_rows, fb.n_rows);
    TCol invNRho   = klab::TTypeInfo<TCol>::UNIT / (rho*static_cast<TCol>(n));
    TCol mean2     = mean*mean;
    
    TCol av = klab::TTypeInfo<TCol>::ZERO;
    for(klab::UInt32 i=0; i<n; ++i)
        av += (fa[i]*fa[i]) + fb[i];

    av *= invNRho;

    return klab::Sqrt(klab::Abs(av-mean2));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline TCol TEMBPSolver<T, TCol, TOp>::ComputeVarianceLearning(const arma::Col<TCol>& fa, const arma::Col<TCol>& fb, const TCol& rho)
{
    klab::UInt32 n = klab::Min(fa.n_rows, fb.n_rows);
    TCol invN      = klab::TTypeInfo<TCol>::UNIT / static_cast<TCol>(n);
    TCol invRho    = klab::TTypeInfo<TCol>::UNIT / rho;

    TCol av = klab::TTypeInfo<TCol>::ZERO;
    for(klab::UInt32 i=0; i<n; ++i)
        av += fb[i] + (fa[i]*fa[i]);

    av *= invN;

    TCol ava = klab::TTypeInfo<TCol>::ZERO;
    for(klab::UInt32 i=0; i<fa.n_rows; ++i)
        ava += fa[i];

    ava *= invN;

    return (klab::Abs(av - (ava*ava*invRho)) * invRho);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolverSpecialisation<T, TCol, TOp>::Solve(const arma::Col<TCol>& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, TEMBPSolver<T, TCol, TOp>& solver)
{
    solver.solveEMBP(y, phi, phiT, sparsity, x, solver._residualNorm, solver._relativeResidualNorm, solver._iterations, solver._history);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolverSpecialisation<T, TCol, TOp>::Solve(const arma::Col<TCol>& y, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phi, klab::TSmartPointer<TBlockOperator<TCol, TCol, TOp> > phiT, klab::UInt32 sparsity, arma::Col<TCol>& x, TEMBPSolver<T, TCol, TOp>& solver)
{
    solver.solveEMBP(y, phi, phiT, sparsity, x, solver._residualNorm, solver._relativeResidualNorm, solver._iterations, solver._history);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolverSpecialisation<T, std::complex<TCol>, TOp>::Solve(const arma::Col<std::complex<TCol> >& y, klab::TSmartPointer<TOp> phi, klab::TSmartPointer<TOp> phiT, klab::UInt32 sparsity, arma::Col<std::complex<TCol> >& x, TEMBPSolver<T, std::complex<TCol>, TOp>& solver)
{        
    ThrowTraceExceptionIf(KNullVectorEMBPSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullVectorEMBPSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullVectorEMBPSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0); 

    klab::UInt32 n  = y.n_rows;
    klab::UInt32 rn = (n<<1); 
      
    arma::Col<TCol> ry(rn);
    arma::Col<TCol> rx;
    for(klab::UInt32 i=0; i<n; ++i)
    {
        ry[i]   = y[i].real();
        ry[n+i] = y[i].imag();
    }

    TEMBPSolver<TCol, TCol> embp(solver.tolerance(), solver.iterationLimit());
    embp.setNoiseVariance(solver.noiseVariance());
    embp.setMessageDamping(solver.messageDamping());
    embp.setLearningDamping(solver.learningDamping());
    embp.enableDampingLearning(solver.isDampingLearningEnabled());
    embp.enableParameterLearning(solver.isParameterLearningEnabled());
    embp.enableHomogeneous(solver.isHomogeneousEnabled());
    embp.enableHistory(solver.isHistoryEnabled());

    embp.solveEMBP(ry, new TComplexProxyOperator<TCol, TCol, TOp>(phi), new TComplexProxyOperator<TCol, TCol, TOp>(phiT), (sparsity<<1), rx, solver._residualNorm, solver._relativeResidualNorm, solver._iterations, solver._history);
    
    x.set_size(rx.n_rows>>1);
    for(klab::UInt32 i=0; i<x.n_rows; ++i)
        x[i] = std::complex<TCol>(rx[i], rx[x.n_rows+i]); 
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOp>
inline void TEMBPSolverSpecialisation<T, std::complex<TCol>, TOp>::Solve(const arma::Col<std::complex<TCol> >& y, klab::TSmartPointer<TBlockOperator<std::complex<TCol>, std::complex<TCol>, TOp> > phi, klab::TSmartPointer<TBlockOperator<std::complex<TCol>, std::complex<TCol>, TOp> > phiT, klab::UInt32 sparsity, arma::Col<std::complex<TCol> >& x, TEMBPSolver<T, std::complex<TCol>, TOp>& solver)
{
    ThrowTraceExceptionIf(KNullVectorEMBPSolverException, y.n_rows==0);
    ThrowTraceExceptionIf(KNullVectorEMBPSolverException, phi==0 || phi->m()==0 || phi->n()==0);    
    ThrowTraceExceptionIf(KNullVectorEMBPSolverException, phiT==0 || phiT->m()==0 || phiT->n()==0); 

    klab::UInt32 n  = y.n_rows;
    klab::UInt32 rn = (n<<1); 
      
    arma::Col<TCol> ry(rn);
    arma::Col<TCol> rx;

    klab::UInt32 mb = phi->countBlockRows();   
    for(klab::UInt32 i=0, k=0, l=0; i<mb; ++i)
    {
        klab::TSmartPointer<TOp> op = phi->block(i, 0);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        klab::UInt32 mOp = op->m();
        for(klab::UInt32 j=0; j<mOp; ++j, ++k, ++l)
        {
            ry[l]     = y[k].real();
            ry[l+mOp] = y[k].imag();
        }

        l += mOp;
    }

    TEMBPSolver<TCol, TCol> embp(solver.tolerance(), solver.iterationLimit());
    embp.setNoiseVariance(solver.noiseVariance());
    embp.setMessageDamping(solver.messageDamping());
    embp.setLearningDamping(solver.learningDamping());
    embp.enableDampingLearning(solver.isDampingLearningEnabled());
    embp.enableParameterLearning(solver.isParameterLearningEnabled());
    embp.enableHomogeneous(solver.isHomogeneousEnabled());
    embp.enableHistory(solver.isHistoryEnabled());

    klab::TSmartPointer<TBlockOperator<TCol, TCol, TOperator<TCol, TCol> > > rPhi  = new TComplexProxyBlockOperator<TCol, TCol, TOp, TBlockOperator<std::complex<TCol>, std::complex<TCol>, TOp> >(phi);
    klab::TSmartPointer<TBlockOperator<TCol, TCol, TOperator<TCol, TCol> > > rPhiT = new TComplexProxyBlockOperator<TCol, TCol, TOp, TBlockOperator<std::complex<TCol>, std::complex<TCol>, TOp> >(phiT);
    embp.solveEMBP(ry, rPhi, rPhiT, (sparsity<<1), rx, solver._residualNorm, solver._relativeResidualNorm, solver._iterations, solver._history);
    
    x.set_size(rx.n_rows>>1);
    klab::UInt32 nb = phi->countBlockColumns();  
    for(klab::UInt32 j=0, k=0, l=0; j<nb; ++j)
    {
        klab::TSmartPointer<TOp> op = phi->block(0, j);
        ThrowTraceExceptionIf(KNullOperatorException, op==0);

        klab::UInt32 nOp = op->n();
        for(klab::UInt32 i=0; i<nOp; ++i, ++k, ++l)
            x[k] = std::complex<TCol>(rx[l], rx[l+nOp]);

        l += nOp;
    }
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
