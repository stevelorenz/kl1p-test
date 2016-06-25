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

#ifndef KL1P_BLOCKOPERATORUNITTEST_H
#define KL1P_BLOCKOPERATORUNITTEST_H

#include <cpptest.h>
#include "../include/BlockOperator.h"
#include "../include/MatrixOperator.h"




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

class KBlockOperatorUnitTest : public Test::Suite
{
public:
    
    KBlockOperatorUnitTest();
    virtual ~KBlockOperatorUnitTest();
    
    
protected:

    // Constructor/Affectation tests.
    void    testDefaultConstructor(); 
    void    testCopyConstructor();

    // Methods tests.
    void    testIsZero();
    void    testSum();
    void    testSquaredNormFrobenius();
    void    testCountBlockRows();
    void    testCountBlockColumns();
    void    testBlock();
    void    testIsZeroBlock();
    void    testInBlock();
    void    testApply();
    void    testApplyAdjoint();
    void    testColumn();
    void    testColumnAdjoint();
    void    testApplyBlockVariance();
    void    testApplyBlockVarianceAdjoint();


private:

    KBlockOperatorUnitTest(const KBlockOperatorUnitTest& test);
    KBlockOperatorUnitTest& operator=(const KBlockOperatorUnitTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut=T, class TOp=kl1p::TOperator<T, TOut> >
class TTestBlockOperator : public TBlockOperator<T, TOut, TOp>
{
public:

    TTestBlockOperator();
    TTestBlockOperator(const TTestBlockOperator<T, TOut, TOp>& op);
    virtual ~TTestBlockOperator();

    virtual klab::UInt32                countBlockRows() const;
    virtual klab::UInt32                countBlockColumns() const;
    virtual klab::TSmartPointer<TOp>    block(klab::UInt32 i, klab::UInt32 j) const;


private:

    TTestBlockOperator<T, TOut, TOp>&   operator=(const TTestBlockOperator<T, TOut, TOp>& op);


private:

    klab::TSmartPointer<TOp>    _op00;
    klab::TSmartPointer<TOp>    _op01;
    klab::TSmartPointer<TOp>    _op02;
    klab::TSmartPointer<TOp>    _op03;

    klab::TSmartPointer<TOp>    _op10;
    klab::TSmartPointer<TOp>    _op11;
    klab::TSmartPointer<TOp>    _op12;
    klab::TSmartPointer<TOp>    _op13;

    klab::TSmartPointer<TOp>    _op20;
    klab::TSmartPointer<TOp>    _op21;
    klab::TSmartPointer<TOp>    _op22;
    klab::TSmartPointer<TOp>    _op23;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TTestBlockOperator<T, TOut, TOp>::TTestBlockOperator() : TBlockOperator<T, TOut, TOp>(), 
_op00(0), _op01(0), _op02(0), _op03(0), 
_op10(0), _op11(0), _op12(0), _op13(0), 
_op20(0), _op21(0), _op22(0), _op23(0) 
{
    arma::Mat<T> matrix00(3, 3);
    arma::Mat<T> matrix01(3, 4);
    arma::Mat<T> matrix02(3, 5);
    arma::Mat<T> matrix03(3, 6);
    arma::Mat<T> matrix10(4, 3);
    arma::Mat<T> matrix11(4, 4);
    arma::Mat<T> matrix12(4, 5);
    arma::Mat<T> matrix13(4, 6);
    arma::Mat<T> matrix20(5, 3);
    arma::Mat<T> matrix21(5, 4);
    arma::Mat<T> matrix22(5, 5);
    arma::Mat<T> matrix23(5, 6);

    matrix00(0, 0) = T(1.0);
    matrix00(0, 1) = T(-2.0);
    matrix00(0, 2) = T(3.0);
    matrix00(1, 0) = T(4.0);
    matrix00(1, 1) = T(-5.0);
    matrix00(1, 2) = T(6.0);
    matrix00(2, 0) = T(7.0);
    matrix00(2, 1) = T(-8.0);
    matrix00(2, 2) = T(9.0);

    matrix01(0, 0) = T(-12.0);
    matrix01(0, 1) = T(11.0);
    matrix01(0, 2) = T(10.0);
    matrix01(0, 3) = T(-9.0);
    matrix01(1, 0) = T(-8.0);
    matrix01(1, 1) = T(7.0);
    matrix01(1, 2) = T(6.0);
    matrix01(1, 3) = T(5.0);
    matrix01(2, 0) = T(4.0);
    matrix01(2, 1) = T(3.0);
    matrix01(2, 2) = T(-2.0);
    matrix01(2, 3) = T(1.0);

    matrix02(0, 0) = T(0.0);
    matrix02(0, 1) = T(0.1);
    matrix02(0, 2) = T(0.2);
    matrix02(0, 3) = T(-0.3);
    matrix02(0, 4) = T(0.4);
    matrix02(1, 0) = T(1.0);
    matrix02(1, 1) = T(1.1);
    matrix02(1, 2) = T(1.2);
    matrix02(1, 3) = T(1.3);
    matrix02(1, 4) = T(1.4);
    matrix02(2, 0) = T(-2.0);
    matrix02(2, 1) = T(2.1);
    matrix02(2, 2) = T(2.2);
    matrix02(2, 3) = T(2.3);
    matrix02(2, 4) = T(2.4);

    matrix03(0, 0) = T(1.0);
    matrix03(0, 1) = T(1.2);
    matrix03(0, 2) = T(-1.4);
    matrix03(0, 3) = T(-1.6);
    matrix03(0, 4) = T(1.8);
    matrix03(0, 5) = T(-2.0);
    matrix03(1, 0) = T(2.2);
    matrix03(1, 1) = T(2.4);
    matrix03(1, 2) = T(2.6);
    matrix03(1, 3) = T(2.8);
    matrix03(1, 4) = T(3.0);
    matrix03(1, 5) = T(3.2);
    matrix03(2, 0) = T(-3.4);
    matrix03(2, 1) = T(3.6);
    matrix03(2, 2) = T(3.8);
    matrix03(2, 3) = T(4.0);
    matrix03(2, 4) = T(4.2);
    matrix03(2, 5) = T(-4.4);

    matrix10(0, 0) = T(3.2);
    matrix10(0, 1) = T(3.1);
    matrix10(0, 2) = T(3.0);
    matrix10(1, 0) = T(2.2);
    matrix10(1, 1) = T(2.1);
    matrix10(1, 2) = T(2.0);
    matrix10(2, 0) = T(1.2);
    matrix10(2, 1) = T(-1.1);
    matrix10(2, 2) = T(1.0);
    matrix10(3, 0) = T(0.2);
    matrix10(3, 1) = T(0.1);
    matrix10(3, 2) = T(0.0);

    matrix11(0, 0) = T(0.0);
    matrix11(0, 1) = T(1.0);
    matrix11(0, 2) = T(2.0);
    matrix11(0, 3) = T(-3.0);
    matrix11(1, 0) = T(0.1);
    matrix11(1, 1) = T(1.1);
    matrix11(1, 2) = T(2.1);
    matrix11(1, 3) = T(3.1);
    matrix11(2, 0) = T(-0.2);
    matrix11(2, 1) = T(1.2);
    matrix11(2, 2) = T(2.2);
    matrix11(2, 3) = T(-3.2);
    matrix11(3, 0) = T(0.3);
    matrix11(3, 1) = T(1.3);
    matrix11(3, 2) = T(2.3);
    matrix11(3, 3) = T(3.3);

    matrix12(0, 0) = T(-1.0);
    matrix12(0, 1) = T(2.0);
    matrix12(0, 2) = T(-3.0);
    matrix12(0, 3) = T(-4.0);
    matrix12(0, 4) = T(5.0);
    matrix12(1, 0) = T(6.0);
    matrix12(1, 1) = T(7.0);
    matrix12(1, 2) = T(8.0);
    matrix12(1, 3) = T(9.0);
    matrix12(1, 4) = T(10.0);
    matrix12(2, 0) = T(11.0);
    matrix12(2, 1) = T(12.0);
    matrix12(2, 2) = T(-13.0);
    matrix12(2, 3) = T(14.0);
    matrix12(2, 4) = T(15.0);
    matrix12(3, 0) = T(-16.0);
    matrix12(3, 1) = T(17.0);
    matrix12(3, 2) = T(18.0);
    matrix12(3, 3) = T(19.0);
    matrix12(3, 4) = T(-20.0);

    matrix13(0, 0) = T(0.1);
    matrix13(0, 1) = T(2.0);
    matrix13(0, 2) = T(0.3);
    matrix13(0, 3) = T(-4.0);
    matrix13(0, 4) = T(-0.5);
    matrix13(0, 5) = T(6.0);
    matrix13(1, 0) = T(-0.7);
    matrix13(1, 1) = T(8.0);
    matrix13(1, 2) = T(0.9);
    matrix13(1, 3) = T(10.0);
    matrix13(1, 4) = T(-0.11);
    matrix13(1, 5) = T(-12.0);
    matrix13(2, 0) = T(0.13);
    matrix13(2, 1) = T(14.0);
    matrix13(2, 2) = T(0.15);
    matrix13(2, 3) = T(-16.0);
    matrix13(2, 4) = T(-0.17);
    matrix13(2, 5) = T(18.0);
    matrix13(3, 0) = T(0.19);
    matrix13(3, 1) = T(20.0);
    matrix13(3, 2) = T(-0.21);
    matrix13(3, 3) = T(22.0);
    matrix13(3, 4) = T(-0.23);
    matrix13(3, 5) = T(24.0);

    matrix20(0, 0) = T(1.0);
    matrix20(0, 1) = T(2.0);
    matrix20(0, 2) = T(3.0);
    matrix20(1, 0) = T(4.0);
    matrix20(1, 1) = T(5.0);
    matrix20(1, 2) = T(6.0);
    matrix20(2, 0) = T(7.0);
    matrix20(2, 1) = T(8.0);
    matrix20(2, 2) = T(9.0);
    matrix20(3, 0) = T(10.0);
    matrix20(3, 1) = T(11.0);
    matrix20(3, 2) = T(12.0);
    matrix20(4, 0) = T(13.0);
    matrix20(4, 1) = T(14.0);
    matrix20(4, 2) = T(15.0);

    matrix21(0, 0) = T(0.0);
    matrix21(0, 1) = T(0.1);
    matrix21(0, 2) = T(-0.2);
    matrix21(0, 3) = T(0.3);
    matrix21(1, 0) = T(1.0);
    matrix21(1, 1) = T(1.1);
    matrix21(1, 2) = T(-1.2);
    matrix21(1, 3) = T(1.3);
    matrix21(2, 0) = T(2.0);
    matrix21(2, 1) = T(2.1);
    matrix21(2, 2) = T(2.2);
    matrix21(2, 3) = T(2.3);
    matrix21(3, 0) = T(3.0);
    matrix21(3, 1) = T(3.1);
    matrix21(3, 2) = T(-3.2);
    matrix21(3, 3) = T(3.3);
    matrix21(4, 0) = T(4.0);
    matrix21(4, 1) = T(4.1);
    matrix21(4, 2) = T(4.2);
    matrix21(4, 3) = T(4.3);

    matrix22(0, 0) = T(-4.4);
    matrix22(0, 1) = T(4.3);
    matrix22(0, 2) = T(4.2);
    matrix22(0, 3) = T(-4.1);
    matrix22(0, 4) = T(4.0);
    matrix22(1, 0) = T(3.4);
    matrix22(1, 1) = T(3.3);
    matrix22(1, 2) = T(3.2);
    matrix22(1, 3) = T(-3.1);
    matrix22(1, 4) = T(3.0);
    matrix22(2, 0) = T(2.4);
    matrix22(2, 1) = T(-2.3);
    matrix22(2, 2) = T(2.2);
    matrix22(2, 3) = T(2.1);
    matrix22(2, 4) = T(2.0);
    matrix22(3, 0) = T(1.4);
    matrix22(3, 1) = T(1.3);
    matrix22(3, 2) = T(1.2);
    matrix22(3, 3) = T(1.1);
    matrix22(3, 4) = T(-1.0);
    matrix22(4, 0) = T(0.4);
    matrix22(4, 1) = T(0.3);
    matrix22(4, 2) = T(0.2);
    matrix22(4, 3) = T(0.1);
    matrix22(4, 4) = T(0.0);

    matrix23(0, 0) = T(-30.0);
    matrix23(0, 1) = T(29.0);
    matrix23(0, 2) = T(28.0);
    matrix23(0, 3) = T(27.0);
    matrix23(0, 4) = T(26.0);
    matrix23(0, 5) = T(25.0);
    matrix23(1, 0) = T(24.0);
    matrix23(1, 1) = T(23.0);
    matrix23(1, 2) = T(-22.0);
    matrix23(1, 3) = T(21.0);
    matrix23(1, 4) = T(-20.0);
    matrix23(1, 5) = T(19.0);
    matrix23(2, 0) = T(-18.0);
    matrix23(2, 1) = T(-17.0);
    matrix23(2, 2) = T(16.0);
    matrix23(2, 3) = T(15.0);
    matrix23(2, 4) = T(14.0);
    matrix23(2, 5) = T(-13.0);
    matrix23(3, 0) = T(12.0);
    matrix23(3, 1) = T(11.0);
    matrix23(3, 2) = T(10.0);
    matrix23(3, 3) = T(9.0);
    matrix23(3, 4) = T(8.0);
    matrix23(3, 5) = T(7.0);
    matrix23(4, 0) = T(-6.0);
    matrix23(4, 1) = T(5.0);
    matrix23(4, 2) = T(4.0);
    matrix23(4, 3) = T(-3.0);
    matrix23(4, 4) = T(2.0);
    matrix23(4, 5) = T(1.0);


    _op00 = new kl1p::TMatrixOperator<T>(matrix00);
    _op01 = new kl1p::TMatrixOperator<T>(matrix01);
    _op02 = new kl1p::TMatrixOperator<T>(matrix02);
    _op03 = new kl1p::TMatrixOperator<T>(matrix03);
    _op10 = new kl1p::TMatrixOperator<T>(matrix10);
    _op11 = new kl1p::TMatrixOperator<T>(matrix11);
    _op12 = new kl1p::TMatrixOperator<T>(matrix12);
    _op13 = new kl1p::TMatrixOperator<T>(matrix13);
    _op20 = new kl1p::TMatrixOperator<T>(matrix20);
    _op21 = new kl1p::TMatrixOperator<T>(matrix21);
    _op22 = new kl1p::TMatrixOperator<T>(matrix22);
    _op23 = new kl1p::TMatrixOperator<T>(matrix23);

    klab::UInt32 m = klab::Max(_op00->m()+_op10->m()+_op20->m(), klab::Max(_op01->m()+_op11->m()+_op21->m(), klab::Max(_op02->m()+_op12->m()+_op22->m(), _op03->m()+_op13->m()+_op23->m())));
    klab::UInt32 n = klab::Max(_op00->n()+_op01->n()+_op02->n()+_op03->n(), klab::Max(_op10->n()+_op11->n()+_op12->n()+_op13->n(), _op20->n()+_op21->n()+_op22->n()+_op23->n()));
    this->resize(m, n);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TTestBlockOperator<T, TOut, TOp>::TTestBlockOperator(const TTestBlockOperator<T, TOut, TOp>& op) : TBlockOperator<T, TOut, TOp>(op),
_op00(op._op00), _op01(op._op01), _op02(op._op02), _op03(op._op03), 
_op10(op._op10), _op11(op._op11), _op12(op._op12), _op13(op._op13), 
_op20(op._op20), _op21(op._op21), _op22(op._op22), _op23(op._op23) 
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline TTestBlockOperator<T, TOut, TOp>::~TTestBlockOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TTestBlockOperator<T, TOut, TOp>::countBlockRows() const
{
    return 3;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::UInt32 TTestBlockOperator<T, TOut, TOp>::countBlockColumns() const
{
    return 4;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TOut, class TOp>
inline klab::TSmartPointer<TOp> TTestBlockOperator<T, TOut, TOp>::block(klab::UInt32 i, klab::UInt32 j) const
{
    klab::TSmartPointer<TOp> ret = 0;

    if(i == 0)
    {
        if(j==0)        ret = _op00;
        else if(j==1)   ret = _op01;
        else if(j==2)   ret = _op02;
        else if(j==3)   ret = _op03;
        else            ThrowTraceException(KOutOfBoundOperatorException);
    }
    else if(i == 1)
    {
        if(j==0)        ret = _op10;
        else if(j==1)   ret = _op11;
        else if(j==2)   ret = _op12;
        else if(j==3)   ret = _op13;
        else            ThrowTraceException(KOutOfBoundOperatorException);
    }
    else if(i == 2)
    {
        if(j==0)        ret = _op20;
        else if(j==1)   ret = _op21;
        else if(j==2)   ret = _op22;
        else if(j==3)   ret = _op23;
        else            ThrowTraceException(KOutOfBoundOperatorException);
    }
    else
    {
        ThrowTraceException(KOutOfBoundOperatorException);
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
