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

#ifndef KLAB_COMPLEX_H
#define KLAB_COMPLEX_H

#include "TrigoUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TComplex
{
public:

    TComplex();
    TComplex(const T& value);
    TComplex(const T& real, const T& imaginary);
    TComplex(const std::complex<T>& complex);
    TComplex(const TComplex<T>& complex);
    virtual ~TComplex();

    TComplex<T>&        operator=(const T& value);
    TComplex<T>&        operator=(const std::complex<T>& complex);
    TComplex<T>&        operator=(const TComplex<T>& complex);

    bool                operator==(const TComplex<T>& complex) const;
    bool                operator!=(const TComplex<T>& complex) const;
    bool                operator==(const T& value) const;
    bool                operator!=(const T& value) const;
    template<class U>   friend bool operator==(const T& left, const TComplex<T>& right);
    template<class U>   friend bool operator!=(const T& left, const TComplex<T>& right);

    TComplex<T>&        operator+=(const T& value);
    TComplex<T>&        operator+=(const TComplex<T>& complex);
    TComplex<T>&        operator-=(const T& value);
    TComplex<T>&        operator-=(const TComplex<T>& complex);
    TComplex<T>&        operator*=(const T& value);
    TComplex<T>&        operator*=(const TComplex<T>& complex);
    TComplex<T>&        operator/=(const T& value);        
    TComplex<T>&        operator/=(const TComplex<T>& complex);

    TComplex<T>         operator+(const T& value) const;
    TComplex<T>         operator+(const TComplex<T>& complex) const;  
    template<class U>   friend TComplex<U>  operator+(const U& left, const TComplex<U>& right);
    TComplex<T>         operator-(const T& value) const;
    TComplex<T>         operator-(const TComplex<T>& complex) const;  
    template<class U>   friend TComplex<U>  operator-(const U& left, const TComplex<U>& right);
    TComplex<T>         operator*(const T& value) const;
    TComplex<T>         operator*(const TComplex<T>& complex) const;  
    template<class U>   friend TComplex<U>  operator*(const U& left, const TComplex<U>& right);
    TComplex<T>         operator/(const T& value) const;
    TComplex<T>         operator/(const TComplex<T>& complex) const;  
    template<class U>   friend TComplex<U>  operator/(const U& left, const TComplex<U>& right);
    TComplex<T>         operator+() const;
    TComplex<T>         operator-() const;

    void                set(const T& real, const T& imaginary);
    void                setPolar(const T& rho, const T& theta);
    void                setReal(const T& real);
    void                setImaginary(const T& imaginary);

    const T&            real() const;
    const T&            imaginary() const;

    void                conjugue();
    TComplex<T>         conjugate() const;
    T				    absolute() const;
    T				    modulus() const;
	T				    argument() const;
	T				    norm() const;

    bool                equals(const TComplex<T>& complex, const T& epsilon=klab::TTypeInfo<T>::EPSILON) const;

                        operator std::complex<T>();
                        operator std::complex<T>() const;


public:

    template<class U> friend U              Abs(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    Conj(const TComplex<U>& complex);
    template<class U> friend bool           Equals(const TComplex<U>& left, const TComplex<U>& right);
    template<class U> friend bool           Equals(const TComplex<U>& left, const TComplex<U>& right, const U& epsilon);

    template<class U> friend TComplex<U>    Cos(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    CosH(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    Sin(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    SinH(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    Tan(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    TanH(const TComplex<U>& complex);

    template<class U> friend TComplex<U>    Sqrt(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    Exp(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    Log(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    Log10(const TComplex<U>& complex);
    template<class U> friend TComplex<U>    Pow(const TComplex<U>& base, klab::Int32 exponent);
    template<class U> friend TComplex<U>    Pow(const TComplex<U>& base, const TComplex<U>& exponent);
    template<class U> friend TComplex<U>    Pow(const TComplex<U>& base, const U& exponent);
    template<class U> friend TComplex<U>    Pow(const U& base, const TComplex<U>& exponent);

    template<class U> friend std::ostream&  operator<<(std::ostream& os, const TComplex<U>& complex);


private:

    T           _real;
    T           _imaginary;
};

// ---------------------------------------------------------------------------------------------------- //

typedef TComplex<klab::Real>            KComplex;
typedef TComplex<klab::DoubleReal>      KDoubleComplex;

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TTypeInfo<TComplex<T> >
{
public:

    static const TComplex<T>    ZERO;
    static const TComplex<T>    UNIT;
    static const TComplex<T>    MIN;
    static const TComplex<T>    MAX;
    static const int   			PRECISION;
    static const T              DELTA;
    static const T              EPSILON;


private:

    TTypeInfo();
    TTypeInfo(const TTypeInfo<TComplex<T> >& info);
    TTypeInfo<TComplex<T> >&    operator=(const TTypeInfo<TComplex<T> >& info);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>::TComplex() : 
_real(), _imaginary()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>::TComplex(const T& value) : 
_real(value), _imaginary()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>::TComplex(const T& real, const T& imaginary) : 
_real(real), _imaginary(imaginary)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>::TComplex(const std::complex<T>& complex) : 
_real(complex.real()), _imaginary(complex.imag())
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>::TComplex(const TComplex<T>& complex) : 
_real(complex._real), _imaginary(complex._imaginary)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>::~TComplex()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator=(const T& value)
{
    _real      = value;
    _imaginary = klab::TTypeInfo<T>::ZERO;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator=(const std::complex<T>& complex)
{
    _real      = complex.real();
    _imaginary = complex.imag();

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator=(const TComplex<T>& complex)
{
    if(this != &complex)
    {
        _real       = complex._real;
        _imaginary  = complex._imaginary;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TComplex<T>::operator==(const TComplex<T>& complex) const
{
    return this->equals(complex);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TComplex<T>::operator!=(const TComplex<T>& complex) const
{
    return (this->equals(complex) == false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TComplex<T>::operator==(const T& value) const
{
    return (_real==value && _imaginary==klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TComplex<T>::operator!=(const T& value) const
{
    return (_real!=value || _imaginary!=klab::TTypeInfo<T>::ZERO);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool operator==(const T& left, const TComplex<T>& right)
{
    return right.operator==(left);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool operator!=(const T& left, const TComplex<T>& right)
{
    return right.operator!=(left);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator+=(const T& value)
{
    _real += value;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator+=(const TComplex<T>& complex)
{
    _real       += complex._real;
    _imaginary  += complex._imaginary;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator-=(const T& value)
{
    _real -= value;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator-=(const TComplex<T>& complex)
{
    _real       -= complex._real;
    _imaginary  -= complex._imaginary;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator*=(const T& value)
{
    _real       *= value;
    _imaginary  *= value;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator*=(const TComplex<T>& complex)
{
    T tmp       = _real*complex._imaginary  + _imaginary*complex._real;    
    _real       = _real*complex._real       - _imaginary*complex._imaginary;
	_imaginary  = tmp;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator/=(const T& value)
{
    ThrowTraceExceptionIf(KBadArithmeticException, value==0);

    T inv        = klab::TTypeInfo<T>::UNIT / value;
    _real       *= inv;
    _imaginary  *= inv;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>& TComplex<T>::operator/=(const TComplex<T>& complex)
{
    ThrowTraceExceptionIf(KBadArithmeticException, complex._real==klab::TTypeInfo<T>::ZERO && complex._imaginary==klab::TTypeInfo<T>::ZERO);

    T tmp       = _imaginary*complex._real  - _real*complex._imaginary;
	_real       = _real*complex._real       + _imaginary*complex._imaginary;
	_imaginary  = tmp;

	T inv       = klab::TTypeInfo<T>::UNIT / complex.norm();
	_real      *= inv;
	_imaginary *= inv;

	return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator+(const T& value) const
{
    return TComplex<T>(_real+value, _imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator+(const TComplex<T>& complex) const
{
    return TComplex<T>(_real+complex._real, _imaginary+complex._imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> operator+(const T& left, const TComplex<T>& right)
{
    return TComplex<T>(left+right._real, right._imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator-(const T& value) const
{
    return TComplex<T>(_real-value, _imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator-(const TComplex<T>& complex) const
{
    return TComplex<T>(_real-complex._real, _imaginary-complex._imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> operator-(const T& left, const TComplex<T>& right)
{
    return TComplex<T>(left-right._real, 0-right._imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator*(const T& value) const
{
    return TComplex<T>(_real*value, _imaginary*value);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator*(const TComplex<T>& complex) const
{
    return TComplex<T>(_real*complex._real - _imaginary*complex._imaginary, _real*complex._imaginary + _imaginary*complex._real);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> operator*(const T& left, const TComplex<T>& right)
{
    return (TComplex<T>(left) * right);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator/(const T& value) const
{
    ThrowTraceExceptionIf(KBadArithmeticException, value==0);

    T inv = klab::TTypeInfo<T>::UNIT / value;
    return TComplex<T>(_real*inv, _imaginary*inv);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator/(const TComplex<T>& complex) const
{
    ThrowTraceExceptionIf(KBadArithmeticException, complex._real==klab::TTypeInfo<T>::ZERO && complex._imaginary==klab::TTypeInfo<T>::ZERO);

	T inv = klab::TTypeInfo<T>::UNIT / complex.norm();
	return TComplex<T>((_real*complex._real + _imaginary*complex._imaginary)*inv, (_imaginary*complex._real - _real*complex._imaginary)*inv);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> operator/(const T& left, const TComplex<T>& right)
{
    return (TComplex<T>(left) / right);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator+() const
{
    return TComplex<T>(_real, _imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::operator-() const
{
    return TComplex<T>(-_real, -_imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TComplex<T>::set(const T& real, const T& imaginary)
{
    _real       = real;
    _imaginary  = imaginary;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TComplex<T>::setPolar(const T& rho, const T& theta)
{
    _real       = rho * Cos<T>(theta);
    _imaginary  = rho * Sin<T>(theta);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TComplex<T>::setReal(const T& real)
{
    _real = real;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TComplex<T>::setImaginary(const T& imaginary)
{
    _imaginary = imaginary;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TComplex<T>::real() const
{
    return _real;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TComplex<T>::imaginary() const
{
    return _imaginary;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void TComplex<T>::conjugue()
{
    _imaginary *= -klab::TTypeInfo<T>::UNIT;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TComplex<T>::conjugate() const
{
    return TComplex<T>(_real, -klab::TTypeInfo<T>::UNIT*_imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TComplex<T>::absolute() const
{
    return static_cast<T>(Sqrt(this->norm()));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TComplex<T>::modulus() const
{
    return static_cast<T>(Sqrt(this->norm()));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TComplex<T>::argument() const
{
    return ATan2(_imaginary, _real);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TComplex<T>::norm() const
{
    return (_real*_real + _imaginary*_imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool TComplex<T>::equals(const TComplex<T>& complex, const T& epsilon) const
{
    return (klab::Equals(_real, complex._real, epsilon) && klab::Equals(_imaginary, complex._imaginary, epsilon));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>::operator std::complex<T>()
{
    return std::complex<T>(_real, _imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>::operator std::complex<T>() const
{
    return std::complex<T>(_real, _imaginary);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T            Abs(const TComplex<T>& complex)
{
    return complex.absolute();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T>  Conj(const TComplex<T>& complex)
{
    return complex.conjugate();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool         Equals(const TComplex<T>& left, const TComplex<T>& right)
{
    return left.equals(right);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline bool         Equals(const TComplex<T>& left, const TComplex<T>& right, const T& epsilon)
{
    return left.equals(right, epsilon);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Cos(const TComplex<T>& complex)
{
    return TComplex<T>(Cos(complex._real)*CosH(complex._imaginary), -Sin(complex._real)*SinH(complex._imaginary));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> CosH(const TComplex<T>& complex)
{
    return TComplex<T>(CosH(complex._real)*Cos(complex._imaginary), SinH(complex._real)*Sin(complex._imaginary));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Sin(const TComplex<T>& complex)
{
    return TComplex<T>(Sin(complex._real)*CosH(complex._imaginary), Cos(complex._real)*SinH(complex._imaginary));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> SinH(const TComplex<T>& complex)
{
    return TComplex<T>(SinH(complex._real)*Cos(complex._imaginary), CosH(complex._real)*Sin(complex._imaginary));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Tan(const TComplex<T>& complex)
{
    TComplex<T> result = TanH(TComplex<T>(-complex._imaginary, complex._real));
	return TComplex<T>(result._imaginary, -result._real);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> TanH(const TComplex<T>& complex)
{
    T tangent       = Tan(complex._imaginary);
    T sinhResult    = SinH(complex._real);
	T b             = sinhResult * (klab::TTypeInfo<T>::UNIT + tangent*tangent);
	T d             = klab::TTypeInfo<T>::UNIT + (b * sinhResult);

	if(d != klab::TTypeInfo<T>::ZERO)
	{
		T inv       = klab::TTypeInfo<T>::UNIT / d;
        return TComplex<T>((Sqrt(klab::TTypeInfo<T>::UNIT+sinhResult*sinhResult)*b)*inv, tangent*inv);
	}
	else
	{
		return TComplex<T>(sinhResult<klab::TTypeInfo<T>::ZERO ? -klab::TTypeInfo<T>::UNIT : klab::TTypeInfo<T>::UNIT, klab::TTypeInfo<T>::ZERO);
	}
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Sqrt(const TComplex<T>& complex)
{
    if(complex._real == klab::TTypeInfo<T>::ZERO)
	{
        T t = Sqrt(Abs(complex._imaginary)/T(2));
		return TComplex<T>(t, complex._imaginary<klab::TTypeInfo<T>::ZERO?-t:t);
	}
	else
	{
        T t = Sqrt(2 * (complex.absolute() + Abs(complex._real)));   
		T u = t/2;

        ThrowTraceExceptionIf(KBadArithmeticException, t==klab::TTypeInfo<T>::ZERO);

        return (complex._real>klab::TTypeInfo<T>::ZERO ? TComplex<T>(u, complex._imaginary/t) : TComplex<T>(Abs(complex._imaginary)/t, complex._imaginary<klab::TTypeInfo<T>::ZERO?-u:u));
	}
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Exp(const TComplex<T>& complex)
{
    T r = Exp(complex._real);
    return TComplex<T>(r*Cos(complex._imaginary), r*Sin(complex._imaginary));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Log(const TComplex<T>& complex)
{
    return TComplex<T>(Log(complex.absolute()), complex.argument());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Log10(const TComplex<T>& complex)
{
    return (Log(complex) / Log(static_cast<T>(10)));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Pow(const TComplex<T>& base, klab::Int32 exponent)
{
    return Pow(base, TComplex<T>(static_cast<T>(exponent), klab::TTypeInfo<T>::ZERO));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Pow(const TComplex<T>& base, const TComplex<T>& exponent)
{
    return (base==TComplex<T>() ? TComplex<T>() : Exp(exponent*Log(base)));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Pow(const TComplex<T>& base, const T& exponent)
{
    return Pow(base, TComplex<T>(exponent, klab::TTypeInfo<T>::ZERO));
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TComplex<T> Pow(const T& base, const TComplex<T>& exponent)
{
    return Pow(TComplex<T>(base, klab::TTypeInfo<T>::ZERO), exponent);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline std::ostream& operator<<(std::ostream& os, const TComplex<T>& complex)
{
    os<<complex._real<<"+"<<complex._imaginary<<"i";
    return os;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
const TComplex<T> TTypeInfo<TComplex<T> >::ZERO         = TComplex<T>(klab::TTypeInfo<T>::ZERO, klab::TTypeInfo<T>::ZERO);

template<class T> 
const TComplex<T> TTypeInfo<TComplex<T> >::UNIT         = TComplex<T>(klab::TTypeInfo<T>::UNIT, klab::TTypeInfo<T>::ZERO);

template<class T> 
const TComplex<T> TTypeInfo<TComplex<T> >::MIN          = TComplex<T>(klab::TTypeInfo<T>::MIN, klab::TTypeInfo<T>::MIN);

template<class T> 
const TComplex<T> TTypeInfo<TComplex<T> >::MAX          = TComplex<T>(klab::TTypeInfo<T>::MAX, klab::TTypeInfo<T>::MAX);

template<class T> 
const int TTypeInfo<TComplex<T> >::PRECISION   			= klab::TTypeInfo<T>::PRECISION;

template<class T> 
const T TTypeInfo<TComplex<T> >::DELTA                  = klab::TTypeInfo<T>::DELTA;

template<class T> 
const T TTypeInfo<TComplex<T> >::EPSILON                = klab::TTypeInfo<T>::EPSILON;

// ---------------------------------------------------------------------------------------------------- //

}


#endif
