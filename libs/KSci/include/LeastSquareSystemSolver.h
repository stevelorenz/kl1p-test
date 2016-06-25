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

#ifndef KLAB_LEASTSQUARESYSTEMSOLVER_H
#define KLAB_LEASTSQUARESYSTEMSOLVER_H

#include "MatrixLinearOperator.h"
#include "ComplexProxyLinearOperator.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KLeastSquareException, KException)
KLAB_DECLARE_EXCEPTION(KNullOperatorLeastSquareException, KLeastSquareException)
KLAB_DECLARE_EXCEPTION(KIncompatibleSizeLeastSquareException, KLeastSquareException)
KLAB_DECLARE_EXCEPTION(KZeroNormLeastSquareException, KLeastSquareException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol=T>
class TLeastSquareSystemSolver
{
public:

    TLeastSquareSystemSolver();
    TLeastSquareSystemSolver(klab::UInt32 iterationLimit);
    TLeastSquareSystemSolver(klab::UInt32 iterationLimit, const T& condLimit);
    TLeastSquareSystemSolver(klab::UInt32 iterationLimit, const T& condLimit, const T& aTolerance, const T& bTolerance);
    TLeastSquareSystemSolver(const TLeastSquareSystemSolver<T, TCol>& solver);
    virtual ~TLeastSquareSystemSolver();

    TLeastSquareSystemSolver<T, TCol>&  operator=(const TLeastSquareSystemSolver<T, TCol>& solver);

    void                setATolerance(const T& tol);
    void                setBTolerance(const T& tol);
    void                setCondLimit(const T& limit);
    void                setIterationLimit(klab::UInt32 limit);

    const T&            aTolerance() const;
    const T&            bTolerance() const;
    const T&            condLimit() const;
    klab::UInt32 iterationLimit() const;
    klab::UInt32 countIterations() const;
    const T&            aNorm() const;
    const T&            aCond() const;
    const T&            rNorm() const;
    const T&            arNorm() const;
    const T&            xNorm() const;

    template<class TOperator>
    klab::UInt32        solve(const TOperator& op, const arma::Col<TCol>& b, arma::Col<TCol>& x);
    klab::UInt32        solve(const arma::Mat<TCol>& a, const arma::Col<TCol>& b, arma::Col<TCol>& x);


protected:

    template<class U, class UCol, class TOperator>
    friend class        TLeastSquareSystemSolverSpecialization;


private:

    T                   _aTolerance;
    T                   _bTolerance;
    T                   _condLimit; 
    klab::UInt32        _iterationLimit;
    klab::UInt32        _iterations;   
    T                   _aNorm;
    T                   _aCond;
    T                   _rNorm;
    T                   _arNorm;
    T                   _xNorm;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOperator>
class TLeastSquareSystemSolverSpecialization
{
public:

    static klab::UInt32 SolveLeastSquare(const TOperator& op, const arma::Col<TCol>& b, arma::Col<TCol>& x, const T& aTolerance, const T& bTolerance, const T& condLimit, klab::UInt32 iterationLimit, klab::UInt32& iterations, T& aNorm, T& aCond, T& rNorm, T& arNorm, T& xNorm);


private:

    TLeastSquareSystemSolverSpecialization();
    TLeastSquareSystemSolverSpecialization(const TLeastSquareSystemSolverSpecialization<T, TCol, TOperator>& spec);
    TLeastSquareSystemSolverSpecialization<T, TCol, TOperator>&   operator=(const TLeastSquareSystemSolverSpecialization<T, TCol, TOperator>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
class TLeastSquareSystemSolverSpecialization<T, std::complex<T>, TOperator>
{
public:

    static klab::UInt32 SolveLeastSquare(const TOperator& op, const arma::Col<std::complex<T> >& b, arma::Col<std::complex<T> >& x, const T& aTolerance, const T& bTolerance, const T& condLimit, klab::UInt32 iterationLimit, klab::UInt32& iterations, T& aNorm, T& aCond, T& rNorm, T& arNorm, T& xNorm);


private:

    TLeastSquareSystemSolverSpecialization();
    TLeastSquareSystemSolverSpecialization(const TLeastSquareSystemSolverSpecialization<T, std::complex<T>, TOperator>& spec);
    TLeastSquareSystemSolverSpecialization<T, std::complex<T>, TOperator>&  operator=(const TLeastSquareSystemSolverSpecialization<T, std::complex<T>, TOperator>& spec);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TLeastSquareSystemSolver<T, TCol>::TLeastSquareSystemSolver() : 
_aTolerance(klab::TTypeInfo<T>::EPSILON), _bTolerance(klab::TTypeInfo<T>::EPSILON), _condLimit(static_cast<T>(100000000)), _iterationLimit(0), 
_iterations(0), 
_aNorm(klab::TTypeInfo<T>::ZERO), _aCond(klab::TTypeInfo<T>::ZERO), _rNorm(klab::TTypeInfo<T>::ZERO), _arNorm(klab::TTypeInfo<T>::ZERO), _xNorm(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TLeastSquareSystemSolver<T, TCol>::TLeastSquareSystemSolver(klab::UInt32 iterationLimit) : 
_aTolerance(klab::TTypeInfo<T>::EPSILON), _bTolerance(klab::TTypeInfo<T>::EPSILON), _condLimit(static_cast<T>(100000000)), _iterationLimit(iterationLimit), 
_iterations(0), 
_aNorm(klab::TTypeInfo<T>::ZERO), _aCond(klab::TTypeInfo<T>::ZERO), _rNorm(klab::TTypeInfo<T>::ZERO), _arNorm(klab::TTypeInfo<T>::ZERO), _xNorm(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TLeastSquareSystemSolver<T, TCol>::TLeastSquareSystemSolver(klab::UInt32 iterationLimit, const T& condLimit) : 
_aTolerance(klab::TTypeInfo<T>::EPSILON), _bTolerance(klab::TTypeInfo<T>::EPSILON), _condLimit(condLimit), _iterationLimit(iterationLimit), 
_iterations(0), 
_aNorm(klab::TTypeInfo<T>::ZERO), _aCond(klab::TTypeInfo<T>::ZERO), _rNorm(klab::TTypeInfo<T>::ZERO), _arNorm(0.0), _xNorm(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TLeastSquareSystemSolver<T, TCol>::TLeastSquareSystemSolver(klab::UInt32 iterationLimit, const T& condLimit, const T& aTolerance, const T& bTolerance) : 
_aTolerance(aTolerance), _bTolerance(bTolerance), _condLimit(condLimit), _iterationLimit(iterationLimit), 
_iterations(0), 
_aNorm(klab::TTypeInfo<T>::ZERO), _aCond(klab::TTypeInfo<T>::ZERO), _rNorm(klab::TTypeInfo<T>::ZERO), _arNorm(klab::TTypeInfo<T>::ZERO), _xNorm(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TLeastSquareSystemSolver<T, TCol>::TLeastSquareSystemSolver(const TLeastSquareSystemSolver<T, TCol>& solver) : 
_aTolerance(solver._aTolerance), _bTolerance(solver._bTolerance), _condLimit(solver._condLimit), _iterationLimit(solver._iterationLimit), 
_iterations(solver._iterations), 
_aNorm(solver._aNorm), _aCond(solver._aCond), _rNorm(solver._rNorm), _arNorm(solver._arNorm), _xNorm(solver._xNorm)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TLeastSquareSystemSolver<T, TCol>::~TLeastSquareSystemSolver()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline TLeastSquareSystemSolver<T, TCol>& TLeastSquareSystemSolver<T, TCol>::operator=(const TLeastSquareSystemSolver<T, TCol>& solver)
{
    if(this != &solver)
    {
        _aTolerance     = solver._aTolerance;
        _bTolerance     = solver._bTolerance;
        _condLimit      = solver._condLimit;
        _iterationLimit = solver._iterationLimit;

        _iterations    = solver._iterations;

        _aNorm          = solver._aNorm;
        _aCond          = solver._aCond;
        _rNorm          = solver._rNorm;
        _arNorm         = solver._arNorm;
        _xNorm          = solver._xNorm;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline void TLeastSquareSystemSolver<T, TCol>::setATolerance(const T& tol)
{
    _aTolerance = tol;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline void TLeastSquareSystemSolver<T, TCol>::setBTolerance(const T& tol)
{
    _bTolerance = tol;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline void TLeastSquareSystemSolver<T, TCol>::setCondLimit(const T& limit)
{
    _condLimit = limit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline void TLeastSquareSystemSolver<T, TCol>::setIterationLimit(klab::UInt32 limit)
{
    _iterationLimit = limit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TLeastSquareSystemSolver<T, TCol>::aTolerance() const
{
    return _aTolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TLeastSquareSystemSolver<T, TCol>::bTolerance() const
{
    return _bTolerance;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TLeastSquareSystemSolver<T, TCol>::condLimit() const
{
    return _condLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline klab::UInt32 TLeastSquareSystemSolver<T, TCol>::iterationLimit() const
{
    return _iterationLimit;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline klab::UInt32 TLeastSquareSystemSolver<T, TCol>::countIterations() const
{
    return _iterations;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TLeastSquareSystemSolver<T, TCol>::aNorm() const
{
    return _aNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TLeastSquareSystemSolver<T, TCol>::aCond() const
{
    return _aCond;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TLeastSquareSystemSolver<T, TCol>::rNorm() const
{
    return _rNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TLeastSquareSystemSolver<T, TCol>::arNorm() const
{
    return _arNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline const T& TLeastSquareSystemSolver<T, TCol>::xNorm() const
{
    return _xNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
template<class TOperator>
inline klab::UInt32 TLeastSquareSystemSolver<T, TCol>::solve(const TOperator& op, const arma::Col<TCol>& b, arma::Col<TCol>& x)
{
    return TLeastSquareSystemSolverSpecialization<T, TCol, TOperator>::SolveLeastSquare(op, b, x, _aTolerance>klab::TTypeInfo<T>::ZERO?_aTolerance:klab::TTypeInfo<T>::EPSILON, _bTolerance>klab::TTypeInfo<T>::ZERO?_bTolerance:klab::TTypeInfo<T>::EPSILON, _condLimit>klab::TTypeInfo<T>::ZERO?_condLimit:static_cast<T>(100000000), (_iterationLimit>0)?_iterationLimit:4*op.n(), _iterations, _aNorm, _aCond, _rNorm, _arNorm, _xNorm);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol>
inline klab::UInt32 TLeastSquareSystemSolver<T, TCol>::solve(const arma::Mat<TCol>& a, const arma::Col<TCol>& b, arma::Col<TCol>& x)
{
    klab::TMatrixLinearOperator<TCol> op(a);
    return this->solve<TMatrixLinearOperator<TCol> >(op, b, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TCol, class TOperator>
inline klab::UInt32 TLeastSquareSystemSolverSpecialization<T, TCol, TOperator>::SolveLeastSquare(const TOperator& op, const arma::Col<TCol>& b, arma::Col<TCol>& x, const T& aTolerance, const T& bTolerance, const T& condLimit, klab::UInt32 iterationLimit, klab::UInt32& iterations, T& aNorm, T& aCond, T& rNorm, T& arNorm, T& xNorm)
{
	klab::UInt32 m = op.m();
	klab::UInt32 n = op.n();

    ThrowTraceExceptionIf(KNullOperatorLeastSquareException, m==0 || n==0);
    ThrowTraceExceptionIf(KIncompatibleSizeLeastSquareException, b.n_rows != m);    
	
    iterations = 0;
    aNorm       = klab::TTypeInfo<T>::ZERO;
    aCond       = klab::TTypeInfo<T>::ZERO;
    rNorm       = klab::TTypeInfo<T>::ZERO;
    arNorm      = klab::TTypeInfo<T>::ZERO;
    xNorm       = klab::TTypeInfo<T>::ZERO;

    x.set_size(n);
    x.fill(klab::TTypeInfo<TCol>::ZERO);

    bool useSE = false; //(m > n);  

    arma::Col<TCol> u(b);
    arma::Col<TCol> v(n);
    arma::Col<TCol> w(n);
    arma::Col<TCol> se(useSE?n:1);  
    arma::Col<TCol> opResult;

    v.fill(klab::TTypeInfo<TCol>::ZERO);
    if(useSE)
        se.fill(klab::TTypeInfo<TCol>::ZERO);   

    TCol alpha = klab::TTypeInfo<TCol>::ZERO;
    TCol beta  = arma::norm(u, 2);
    ThrowTraceExceptionIf(KZeroNormLeastSquareException, beta==klab::TTypeInfo<TCol>::ZERO);
    TCol invAlpha = klab::TTypeInfo<TCol>::ZERO;  
    TCol invBeta  = klab::TTypeInfo<TCol>::UNIT / beta;    

    if(beta > klab::TTypeInfo<TCol>::ZERO)
    {
        u *= invBeta;
        op.applyAdjoint(u, v);

        alpha = arma::norm(v, 2);
        ThrowTraceExceptionIf(KZeroNormLeastSquareException, alpha==klab::TTypeInfo<TCol>::ZERO);
        invAlpha = klab::TTypeInfo<TCol>::UNIT / alpha;
    }

    if(alpha > klab::TTypeInfo<TCol>::ZERO)
    {
        v *= invAlpha;
        w  = v;
    }

    arNorm = alpha * beta;
    rNorm  = beta;

    TCol arNorm0 = arNorm;
    TCol rhoBar  = alpha;
    TCol phiBar  = beta;
    TCol bNorm   = beta;
    TCol invBNorm= invBeta;
    TCol dNorm   = klab::TTypeInfo<TCol>::ZERO;
    TCol dxMax   = klab::TTypeInfo<TCol>::ZERO;
    TCol sn2     = klab::TTypeInfo<TCol>::ZERO;
    TCol cs2     =-klab::TTypeInfo<TCol>::UNIT;
    TCol z       = klab::TTypeInfo<TCol>::ZERO;
    TCol xNorm1  = klab::TTypeInfo<TCol>::ZERO;
    TCol res2    = klab::TTypeInfo<TCol>::ZERO;
    TCol psi     = klab::TTypeInfo<TCol>::ZERO;
    TCol cTolerance = (condLimit>klab::TTypeInfo<TCol>::ZERO) ? (klab::TTypeInfo<TCol>::UNIT/condLimit) : klab::TTypeInfo<TCol>::ZERO;

    klab::UInt32 maxDx = 0;

    klab::UInt32 stopCode = 0;
    iterations = 0;
    while(iterations<iterationLimit && stopCode==0) 
    {
        u *= -alpha;

        op.apply(v, opResult);
        u += opResult;

        beta = arma::norm(u, 2);
        ThrowTraceExceptionIf(KZeroNormLeastSquareException, beta==klab::TTypeInfo<TCol>::ZERO);
        invBeta = klab::TTypeInfo<TCol>::UNIT / beta;   

        aNorm = klab::Sqrt(aNorm*aNorm + alpha*alpha + beta*beta);

        if(beta > klab::TTypeInfo<TCol>::ZERO)
        {
            u *= invBeta;
            v *= -beta;

            op.applyAdjoint(u, opResult);
            v += opResult;

            alpha = arma::norm(v, 2);
            if(alpha > klab::TTypeInfo<TCol>::ZERO)
			{
				invAlpha = klab::TTypeInfo<TCol>::UNIT / alpha;
                v *= invAlpha;
			}
        }

        TCol rho = klab::Sqrt(rhoBar*rhoBar + beta*beta);
        ThrowTraceExceptionIf(KZeroNormLeastSquareException, rho==klab::TTypeInfo<TCol>::ZERO);
        TCol invRho = klab::TTypeInfo<TCol>::UNIT / rho;

        TCol cs = rhoBar * invRho;
        TCol sn = beta * invRho;
        TCol theta = sn * alpha;
        TCol phi = cs * phiBar;
        TCol tau = sn * phi;

        rhoBar = -cs * alpha;
        phiBar =  sn * phiBar;

        TCol t1     =  phi   * invRho;
        TCol t2     = -theta * invRho;
        TCol t3     =  invRho;
        TCol dkNorm = klab::TTypeInfo<TCol>::ZERO;

        if(useSE)
        {
            for(klab::UInt32 i=0; i<n; ++i)
            {
                TCol wi = w[i];
                x[i] = t1*wi + x[i];
                w[i] = t2*wi + v[i];
                TCol t = (t3*wi) * (t3*wi);

                se[i]  += t;
                dkNorm += t;
            }
        }
        else
        {
            for(klab::UInt32 i=0; i<n; ++i)
            {
                TCol wi = w[i];
                x[i] = t1*wi + x[i];
                w[i] = t2*wi + v[i];

                dkNorm += (t3*wi) * (t3*wi);
            }
        }

        dkNorm = klab::Sqrt(dkNorm);
        dNorm  = klab::Sqrt(dNorm*dNorm + dkNorm*dkNorm);

        TCol dxk = klab::Abs(phi*dkNorm);
        if(dxMax < dxk)
        {
            dxMax = dxk;
            maxDx = iterations;
        }

        TCol delta  =  sn2 * rho;
        TCol gamBar = -cs2 * rho;
        ThrowTraceExceptionIf(KZeroNormLeastSquareException, gamBar==klab::TTypeInfo<TCol>::ZERO);
        TCol invGamBar = klab::TTypeInfo<TCol>::UNIT / gamBar;

        TCol rhs   = phi - delta*z;
        TCol zBar  = rhs * invGamBar;
        xNorm      = klab::Sqrt(xNorm1*xNorm1 + zBar*zBar);
        TCol gamma = klab::Sqrt(gamBar*gamBar + theta*theta);
        ThrowTraceExceptionIf(KZeroNormLeastSquareException, gamma==klab::TTypeInfo<TCol>::ZERO);
        TCol invGamma = klab::TTypeInfo<TCol>::UNIT / gamma;

        cs2    = gamBar * invGamma;
        sn2    = theta * invGamma;
        z      = rhs * invGamma;
        xNorm1 = klab::Sqrt(xNorm1*xNorm1 + z*z);

        aCond  = aNorm * dNorm;
        res2   = klab::Sqrt(res2*res2 + psi*psi);
        rNorm  = klab::Sqrt(res2*res2 + phiBar*phiBar);
        arNorm = alpha * klab::Abs(tau);
        
        TCol alfOpt = klab::Sqrt(rNorm/(dNorm*xNorm));
        TCol test1  = rNorm * invBNorm;
        TCol test2  = (rNorm>klab::TTypeInfo<TCol>::ZERO) ? (arNorm/(aNorm*rNorm)) : klab::TTypeInfo<TCol>::ZERO;
        TCol test3  = klab::TTypeInfo<TCol>::UNIT / aCond;
        arNorm      = test2;

        TCol rTolerance = bTolerance + (aTolerance*aNorm*xNorm*invBNorm);
        t1  = test1 / (klab::TTypeInfo<TCol>::UNIT + (aNorm*xNorm*invBNorm));        
        t3  = klab::TTypeInfo<TCol>::UNIT + test3;
        t2  = klab::TTypeInfo<TCol>::UNIT + test2;
        t1 += klab::TTypeInfo<TCol>::UNIT;

        ++iterations;

        stopCode = 0;
        if(iterations >= iterationLimit)        stopCode = 5;   // The iteration limit was reached.
        if(t3 <= klab::TTypeInfo<TCol>::UNIT)   stopCode = 4;   // An estimate of cond(Abar) has exceeded condLimit. The system A*x = b appears to be ill-conditioned. Otherwise, there could be an error in operator apply or applyAdjoint methods.
        if(t2 <= klab::TTypeInfo<TCol>::UNIT)   stopCode = 2;   // Damp is zero.  The system A*x = b is probably not compatible.  A least-squares solution has been obtained that is sufficiently accurate, given the value of aTolerance.
        if(t1 <= klab::TTypeInfo<TCol>::UNIT)   stopCode = 1;   // The equations A*x = b are probably compatible.  Norm(A*x - b) is sufficiently small, given the values of aTolerance and bTolerance.
        if(test3 <= cTolerance)                 stopCode = 4;   // An estimate of cond(Abar) has exceeded condLimit. The system A*x = b appears to be ill-conditioned. Otherwise, there could be an error in operator apply or applyAdjoint methods.
        if(test2 <= aTolerance)                 stopCode = 2;   // Damp is zero.  The system A*x = b is probably not compatible.  A least-squares solution has been obtained that is sufficiently accurate, given the value of aTolerance.
        if(test1 <= rTolerance)                 stopCode = 1;   // The equations A*x = b are probably compatible.  Norm(A*x - b) is sufficiently small, given the values of aTolerance and bTolerance.

        if(useSE)
        {
            TCol t = rNorm / klab::Sqrt(static_cast<TCol>(m-n));
            for(klab::UInt32 i=0; i<n; ++i)
                se[i] = t * klab::Sqrt(se[i]);
        }
    } 

    return stopCode;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOperator>
inline klab::UInt32 TLeastSquareSystemSolverSpecialization<T, std::complex<T>, TOperator>::SolveLeastSquare(const TOperator& op, const arma::Col<std::complex<T> >& b, arma::Col<std::complex<T> >& x, const T& aTolerance, const T& bTolerance, const T& condLimit, klab::UInt32 iterationLimit, klab::UInt32& iterations, T& aNorm, T& aCond, T& rNorm, T& arNorm, T& xNorm)
{
    klab::UInt32 m = op.m();
	klab::UInt32 n = op.n();

    ThrowTraceExceptionIf(KNullOperatorLeastSquareException, m==0 || n==0);
    ThrowTraceExceptionIf(KIncompatibleSizeLeastSquareException, b.n_rows != m);    

	arma::Col<T> cb(b.n_rows<<1);
    for(klab::UInt32 i=0; i<b.n_rows; ++i)
    {
        cb[i]          = b[i].real();
        cb[b.n_rows+i] = b[i].imag();
    }

    arma::Col<T> cx;  
    klab::UInt32 ret = TLeastSquareSystemSolverSpecialization<T, T, klab::TComplexProxyLinearOperator<T, TOperator> >::SolveLeastSquare(klab::TComplexProxyLinearOperator<T, TOperator>(op), cb, cx, aTolerance, bTolerance, condLimit, iterationLimit, iterations, aNorm, aCond, rNorm, arNorm, xNorm);

    klab::UInt32 nx = cx.n_rows >> 1;
    x.set_size(nx);
    for(klab::UInt32 i=0; i<nx; ++i)
        x[i] = std::complex<T>(cx[i], cx[nx+i]);  

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
