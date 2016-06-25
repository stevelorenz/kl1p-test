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

#ifndef KLAB_LINEAROPERATOR_H
#define KLAB_LINEAROPERATOR_H

#include "MathsUtil.h"
#include "ArmadilloUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //
    
KLAB_DECLARE_EXCEPTION(KLinearOperatorException, KMathsException)
KLAB_DECLARE_EXCEPTION(KIncompatibleSizeLinearOperatorException, KLinearOperatorException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
class TLinearOperator
{
public:

    TLinearOperator();
	TLinearOperator(klab::UInt32 n);
    TLinearOperator(klab::UInt32 m, klab::UInt32 n);
    TLinearOperator(const TLinearOperator<T, TChild>& op);
    virtual ~TLinearOperator();

    TLinearOperator<T, TChild>&	operator=(const TLinearOperator<T, TChild>& op);

    klab::UInt32	m() const;
    klab::UInt32	n() const;

    void			apply(const arma::Col<T>& in, arma::Col<T>& out) const;			// To override.
	void			applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) const;  // To override.


private:

    klab::UInt32    _m;
    klab::UInt32    _n;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TLinearOperator<T, TChild>::TLinearOperator() : _m(0), _n(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TLinearOperator<T, TChild>::TLinearOperator(klab::UInt32 n) : _m(n), _n(n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TLinearOperator<T, TChild>::TLinearOperator(klab::UInt32 m, klab::UInt32 n) : _m(m), _n(n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TLinearOperator<T, TChild>::TLinearOperator(const TLinearOperator<T, TChild>& op) : _m(op._m), _n(op._n)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TLinearOperator<T, TChild>::~TLinearOperator()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TLinearOperator<T, TChild>& TLinearOperator<T, TChild>::operator=(const TLinearOperator<T, TChild>& op)
{
    if(this != &op)
    {
        _m = op._m;
        _n = op._n;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline klab::UInt32 TLinearOperator<T, TChild>::m() const
{
    return _m;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline klab::UInt32 TLinearOperator<T, TChild>::n() const
{
    return _n;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline void TLinearOperator<T, TChild>::apply(const arma::Col<T>& in, arma::Col<T>& out) const
{
    static_cast<const TChild&>(*this).apply(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline void TLinearOperator<T, TChild>::applyAdjoint(const arma::Col<T>& in, arma::Col<T>& out) const 
{
    static_cast<const TChild&>(*this).applyAdjoint(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
